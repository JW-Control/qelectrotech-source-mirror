#!/usr/bin/env python3
"""Analiza y fusiona proyectos QET por folio con merge 3-way de elementos embebidos."""
from __future__ import annotations

import argparse
import copy
import hashlib
import json
import sys
import xml.etree.ElementTree as ET
from dataclasses import dataclass
from pathlib import Path
from typing import Any


class QetToolError(RuntimeError):
    pass


class SpanishArgumentParser(argparse.ArgumentParser):
    def format_usage(self) -> str:
        return super().format_usage().replace("usage:", "uso:", 1)

    def format_help(self) -> str:
        return super().format_help().replace("usage:", "uso:", 1)


@dataclass(frozen=True)
class DiagramEntry:
    key: str
    index: int
    node: ET.Element


@dataclass(frozen=True)
class DiagramChange:
    source: Path
    key: str
    node: ET.Element


def local_name(tag: str) -> str:
    return tag.rsplit("}", 1)[-1] if "}" in tag else tag


def children(node: ET.Element | None, name: str | None = None) -> list[ET.Element]:
    if node is None:
        return []
    result = [c for c in list(node) if isinstance(c.tag, str)]
    return result if name is None else [c for c in result if local_name(c.tag) == name]


def first(node: ET.Element | None, name: str) -> ET.Element | None:
    return next((c for c in children(node) if local_name(c.tag) == name), None)


def text(value: str | None) -> str:
    if value is None:
        return ""
    value = value.replace("\r\n", "\n").replace("\r", "\n")
    return "" if not value.strip() else value


def ignorable(node: ET.Element) -> bool:
    return (
        local_name(node.tag) == "elementInformations"
        and not node.attrib
        and not text(node.text)
        and not children(node)
    )


def signature(node: ET.Element) -> tuple[Any, ...]:
    return (
        local_name(node.tag),
        tuple(sorted(node.attrib.items())),
        text(node.text),
        tuple(signature(c) for c in children(node) if not ignorable(c)),
    )


def fingerprint(node: ET.Element, length: int = 16) -> str:
    return hashlib.sha256(repr(signature(node)).encode()).hexdigest()[:length]


def parse_qet(path: Path) -> ET.ElementTree:
    if not path.exists():
        raise QetToolError(f"El archivo no existe: {path}")
    try:
        tree = ET.parse(path)
    except ET.ParseError as exc:
        raise QetToolError(f"XML invalido en {path}: {exc}") from exc
    if local_name(tree.getroot().tag) != "project":
        raise QetToolError(f"Se esperaba raiz <project> en {path}")
    return tree


def diagram_key(node: ET.Element, index: int, mode: str) -> str:
    if mode == "position":
        return f"position:{index + 1}"
    return f"order:{node.get('order')}" if node.get("order") else f"position:{index + 1}"


def diagram_map(root: ET.Element, mode: str) -> dict[str, DiagramEntry]:
    result: dict[str, DiagramEntry] = {}
    for index, node in enumerate(children(root, "diagram")):
        key = diagram_key(node, index, mode)
        if key in result:
            raise QetToolError(f"Clave de folio duplicada {key}")
        result[key] = DiagramEntry(key, index, node)
    return result


def top_key(node: ET.Element, index: int) -> tuple[str, str]:
    value = node.get("name") or node.get("title") or node.get("order") or str(index)
    return local_name(node.tag), value


def global_differences(base: ET.Element, source: ET.Element) -> list[str]:
    differences: list[str] = []
    if dict(base.attrib) != dict(source.attrib):
        differences.append("atributos de raiz")
    skip = {"diagram", "collection"}
    b = [c for c in children(base) if local_name(c.tag) not in skip]
    s = [c for c in children(source) if local_name(c.tag) not in skip]
    bm = {top_key(c, i): c for i, c in enumerate(b)}
    sm = {top_key(c, i): c for i, c in enumerate(s)}
    for key in sorted(set(bm) | set(sm)):
        if key not in bm:
            differences.append(f"agregado global <{key[0]}>")
        elif key not in sm:
            differences.append(f"eliminado global <{key[0]}>")
        elif signature(bm[key]) != signature(sm[key]):
            differences.append(f"modificado global <{key[0]}>")
    return sorted(set(differences))


def collection_key(node: ET.Element) -> tuple[str, str]:
    value = node.get("name") or node.get("lang") or node.get("uuid")
    return local_name(node.tag), value or repr(tuple(sorted(node.attrib.items())))


def find_match(parent: ET.Element | None, source: ET.Element) -> ET.Element | None:
    key = collection_key(source)
    return next((c for c in children(parent) if collection_key(c) == key), None)


def subtree_types(node: ET.Element, parts: list[str]) -> set[str]:
    result: set[str] = set()
    for child in children(node):
        kind = local_name(child.tag)
        if kind == "category":
            name = child.get("name")
            result |= subtree_types(child, parts + ([name] if name else []))
        elif kind == "element" and child.get("name"):
            result.add("embed://" + "/".join(parts + [child.get("name", "")]))
    return result


def used_embed_types(diagrams: dict[str, DiagramEntry], changed: list[str]) -> set[str]:
    result: set[str] = set()
    for key in changed:
        entry = diagrams.get(key)
        for element in children(first(entry.node if entry else None, "elements"), "element"):
            element_type = element.get("type", "")
            if element_type.startswith("embed://"):
                result.add(element_type)
    return result


def category_shell(source: ET.Element) -> ET.Element:
    shell = ET.Element(source.tag, dict(source.attrib))
    shell.text = source.text
    for child in children(source):
        if local_name(child.tag) not in {"category", "element"}:
            shell.append(copy.deepcopy(child))
    return shell


def replace_child(parent: ET.Element, old: ET.Element, new: ET.Element) -> None:
    items = list(parent)
    try:
        index = items.index(old)
    except ValueError as exc:
        raise QetToolError("Error interno reemplazando elemento embebido") from exc
    parent.remove(old)
    parent.insert(index, copy.deepcopy(new))


def merge_collection_nodes(
    destination: ET.Element,
    baseline: ET.Element | None,
    source: ET.Element,
    parts: list[str],
    path: str,
    allowed: set[str],
    conflicts: list[str],
    warnings: list[str],
) -> None:
    for src in children(source):
        kind = local_name(src.tag)
        key = collection_key(src)
        dst = find_match(destination, src)
        base = find_match(baseline, src)
        child_path = f"{path}/{kind}[{key[1]}]"

        if kind == "category":
            name = src.get("name")
            next_parts = parts + ([name] if name else [])
            if not (subtree_types(src, next_parts) & allowed):
                continue
            if dst is None:
                dst = category_shell(src)
                destination.append(dst)
            merge_collection_nodes(dst, base, src, next_parts, child_path, allowed, conflicts, warnings)
            continue

        if kind != "element":
            continue
        name = src.get("name")
        if not name:
            continue
        element_type = "embed://" + "/".join(parts + [name])
        if element_type not in allowed:
            continue

        src_sig = signature(src)
        if dst is None:
            if base is None:
                destination.append(copy.deepcopy(src))
                warnings.append(f"elemento embebido agregado desde folio modificado: {element_type}")
            elif src_sig == signature(base):
                destination.append(copy.deepcopy(src))
            else:
                conflicts.append(f"conflicto real de elemento embebido en {child_path}")
            continue

        dst_sig = signature(dst)
        if base is None:
            if dst_sig != src_sig:
                conflicts.append(f"conflicto real de elemento embebido en {child_path}")
            continue

        base_sig = signature(base)
        src_changed = src_sig != base_sig
        dst_changed = dst_sig != base_sig
        if not src_changed:
            continue
        if not dst_changed:
            replace_child(destination, dst, src)
            warnings.append(f"elemento embebido actualizado desde folio modificado: {element_type}")
        elif dst_sig != src_sig:
            conflicts.append(f"conflicto real de elemento embebido en {child_path}")


def merge_collection(
    destination_root: ET.Element,
    baseline_root: ET.Element,
    source_root: ET.Element,
    allowed: set[str],
    conflicts: list[str],
    warnings: list[str],
) -> None:
    if not allowed:
        return
    source = first(source_root, "collection")
    if source is None:
        return
    baseline = first(baseline_root, "collection")
    destination = first(destination_root, "collection")
    if destination is None:
        destination = ET.Element(source.tag, dict(source.attrib))
        destination_root.append(destination)
    merge_collection_nodes(destination, baseline, source, [], "/project/collection", allowed, conflicts, warnings)


def replace_diagram(root: ET.Element, old: DiagramEntry, new: ET.Element) -> None:
    items = list(root)
    try:
        index = items.index(old.node)
    except ValueError as exc:
        raise QetToolError(f"No se encontro el folio {old.key}") from exc
    root.remove(old.node)
    root.insert(index, copy.deepcopy(new))


def detect_changes(
    base_path: Path, source_paths: list[Path], mode: str
) -> tuple[ET.ElementTree, dict[str, DiagramChange], list[str], list[str]]:
    tree = parse_qet(base_path)
    root = tree.getroot()
    baseline = copy.deepcopy(root)
    base_diagrams = diagram_map(root, mode)
    changes: dict[str, DiagramChange] = {}
    warnings: list[str] = []
    conflicts: list[str] = []

    for source_path in source_paths:
        source_root = parse_qet(source_path).getroot()
        source_diagrams = diagram_map(source_root, mode)
        missing = sorted(set(base_diagrams) - set(source_diagrams))
        added = sorted(set(source_diagrams) - set(base_diagrams))
        if missing or added:
            conflicts.append(
                f"{source_path}: cambio el conjunto de folios; faltan={missing or '-'} agregados={added or '-'}"
            )
            continue

        diffs = global_differences(baseline, source_root)
        if diffs:
            warnings.append(f"{source_path}: diferencias globales: {', '.join(diffs)}")

        changed: list[str] = []
        for key, entry in source_diagrams.items():
            if signature(entry.node) == signature(base_diagrams[key].node):
                continue
            changed.append(key)
            previous = changes.get(key)
            if previous is None:
                changes[key] = DiagramChange(source_path, key, entry.node)
            elif signature(previous.node) != signature(entry.node):
                conflicts.append(
                    f"folio {key} se modifico de forma distinta en {previous.source} y {source_path}"
                )

        warnings.append(
            f"{source_path}: folios modificados: {', '.join(changed)}"
            if changed else f"{source_path}: no se detectaron cambios de folio"
        )
        merge_collection(
            root,
            baseline,
            source_root,
            used_embed_types(source_diagrams, changed),
            conflicts,
            warnings,
        )
    return tree, changes, warnings, conflicts


def collection_element_names(root: ET.Element) -> list[str]:
    collection = first(root, "collection")
    if collection is None:
        return []
    result: list[str] = []
    stack = [collection]
    while stack:
        node = stack.pop()
        for child in children(node):
            if local_name(child.tag) == "element" and child.get("name"):
                result.append(child.get("name", ""))
            stack.append(child)
    return sorted(result)


def merge_projects(
    base_path: Path,
    source_paths: list[Path],
    output_path: Path,
    key_mode: str,
    force: bool,
    dry_run: bool,
) -> dict[str, Any]:
    if output_path.exists() and not force and not dry_run:
        raise QetToolError(f"La salida ya existe: {output_path}. Usa --force para sobrescribir.")
    tree, changes, warnings, conflicts = detect_changes(base_path, source_paths, key_mode)
    root = tree.getroot()
    if conflicts:
        return {
            "ok": False,
            "base": str(base_path),
            "sources": [str(p) for p in source_paths],
            "output": str(output_path),
            "changed_diagrams": sorted(changes),
            "warnings": sorted(set(warnings)),
            "conflicts": sorted(set(conflicts)),
        }
    base_diagrams = diagram_map(root, key_mode)
    for key, change in sorted(changes.items()):
        replace_diagram(root, base_diagrams[key], change.node)
        base_diagrams = diagram_map(root, key_mode)
    if not dry_run:
        output_path.parent.mkdir(parents=True, exist_ok=True)
        ET.indent(tree, space="    ")
        tree.write(output_path, encoding="utf-8", xml_declaration=False)
    return {
        "ok": True,
        "base": str(base_path),
        "sources": [str(p) for p in source_paths],
        "output": str(output_path),
        "dry_run": dry_run,
        "changed_diagrams": sorted(changes),
        "warnings": sorted(set(warnings)),
        "conflicts": [],
        "collection_elements": collection_element_names(root),
    }


def analyze_project(path: Path, key_mode: str) -> dict[str, Any]:
    root = parse_qet(path).getroot()
    diagrams = diagram_map(root, key_mode)
    return {
        "path": str(path),
        "title": root.get("title", ""),
        "version": root.get("version", ""),
        "diagram_count": len(diagrams),
        "diagrams": [
            {
                "key": entry.key,
                "index": entry.index + 1,
                "order": entry.node.get("order", ""),
                "title": entry.node.get("title", ""),
                "fingerprint": fingerprint(entry.node),
            }
            for entry in diagrams.values()
        ],
        "collection_element_count": len(collection_element_names(root)),
        "collection_elements": collection_element_names(root),
    }


def print_analysis_text(projects: list[dict[str, Any]]) -> None:
    for project in projects:
        print(f"Proyecto: {project['path']}")
        print(
            f"  titulo={project['title']!r} version={project['version']!r} "
            f"folios={project['diagram_count']} elementos_coleccion={project['collection_element_count']}"
        )
        for diagram in project["diagrams"]:
            print(
                f"  folio {diagram['key']} indice={diagram['index']} "
                f"order={diagram['order']!r} fp={diagram['fingerprint']}"
            )
        print()


def print_merge_text(result: dict[str, Any]) -> None:
    print(f"Estado del merge: {'OK' if result['ok'] else 'CONFLICTO'}")
    print(f"  base: {result['base']}")
    print(f"  salida: {result['output']}")
    print("  fuentes:")
    for source in result["sources"]:
        print(f"    {source}")
    print(f"  folios modificados: {', '.join(result['changed_diagrams']) or '-'}")
    for warning in result["warnings"]:
        print(f"  advertencia: {warning}")
    for conflict in result["conflicts"]:
        print(f"  conflicto: {conflict}")


def build_parser() -> argparse.ArgumentParser:
    parser = SpanishArgumentParser(add_help=False)
    parser.add_argument("-h", "--help", action="help")
    parser.add_argument("--key", choices=("order", "position"), default="order")
    subs = parser.add_subparsers(dest="command", required=True, parser_class=SpanishArgumentParser)
    analyze = subs.add_parser("analyze", add_help=False)
    analyze.add_argument("-h", "--help", action="help")
    analyze.add_argument("files", nargs="+")
    analyze.add_argument("--json", action="store_true")
    merge = subs.add_parser("merge", add_help=False)
    merge.add_argument("-h", "--help", action="help")
    merge.add_argument("--base", required=True)
    merge.add_argument("--output", required=True)
    merge.add_argument("--force", action="store_true")
    merge.add_argument("--dry-run", action="store_true")
    merge.add_argument("--json", action="store_true")
    merge.add_argument("sources", nargs="+")
    return parser


def main(argv: list[str] | None = None) -> int:
    args = build_parser().parse_args(argv)
    try:
        if args.command == "analyze":
            result = [analyze_project(Path(p), args.key) for p in args.files]
            print(json.dumps(result, indent=2, ensure_ascii=False) if args.json else "", end="")
            if not args.json:
                print_analysis_text(result)
            return 0
        result = merge_projects(
            Path(args.base), [Path(p) for p in args.sources], Path(args.output),
            args.key, args.force, args.dry_run,
        )
        print(json.dumps(result, indent=2, ensure_ascii=False) if args.json else "", end="")
        if not args.json:
            print_merge_text(result)
        return 0 if result["ok"] else 2
    except QetToolError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
