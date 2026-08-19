#!/usr/bin/env python3
"""Analiza y fusiona conservadoramente archivos .qet por folio.

Esta es una herramienta de desarrollo para el fork colaborativo de JW Control.
No modifica QElectroTech ni cambia el formato .qet.
"""

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
    """Error esperado de la herramienta con mensaje corto para usuarios."""


class SpanishArgumentParser(argparse.ArgumentParser):
    """ArgumentParser with Spanish help headings."""

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
    """Devuelve el nombre local del elemento, ignorando namespace XML."""
    if "}" in tag:
        return tag.rsplit("}", 1)[1]
    return tag


def element_children(node: ET.Element, tag_name: str | None = None) -> list[ET.Element]:
    children = [child for child in list(node) if isinstance(child.tag, str)]
    if tag_name is None:
        return children
    return [child for child in children if local_name(child.tag) == tag_name]


def first_child(node: ET.Element, tag_name: str) -> ET.Element | None:
    for child in element_children(node):
        if local_name(child.tag) == tag_name:
            return child
    return None


def descendants(node: ET.Element, tag_name: str) -> list[ET.Element]:
    matches: list[ET.Element] = []
    for child in element_children(node):
        if local_name(child.tag) == tag_name:
            matches.append(child)
        matches.extend(descendants(child, tag_name))
    return matches


def meaningful_text(value: str | None) -> str:
    if value is None:
        return ""
    normalized = value.replace("\r\n", "\n").replace("\r", "\n")
    if normalized.strip() == "":
        return ""
    return normalized


def is_ignorable_empty_node(node: ET.Element) -> bool:
    """Devuelve true para nodos vacios que QET puede omitir al guardar."""
    return (
        local_name(node.tag) == "elementInformations"
        and not node.attrib
        and meaningful_text(node.text) == ""
        and not element_children(node)
    )


def canonical_signature(node: ET.Element) -> tuple[Any, ...]:
    """Construye una firma estructural ignorando espacios de indentacion."""
    return (
        local_name(node.tag),
        tuple(sorted(node.attrib.items())),
        meaningful_text(node.text),
        tuple(
            canonical_signature(child)
            for child in element_children(node)
            if not is_ignorable_empty_node(child)
        ),
    )


def fingerprint(node: ET.Element, length: int = 16) -> str:
    raw = repr(canonical_signature(node)).encode("utf-8")
    return hashlib.sha256(raw).hexdigest()[:length]


def parse_qet(path: Path) -> ET.ElementTree:
    if not path.exists():
        raise QetToolError(f"El archivo no existe: {path}")
    try:
        tree = ET.parse(path)
    except ET.ParseError as exc:
        raise QetToolError(f"XML invalido en {path}: {exc}") from exc

    root = tree.getroot()
    if local_name(root.tag) != "project":
        raise QetToolError(f"Se esperaba raiz <project> en {path}, se encontro <{local_name(root.tag)}>")
    return tree


def diagram_key(diagram: ET.Element, index: int, key_mode: str) -> str:
    if key_mode == "position":
        return f"position:{index + 1}"
    order = diagram.get("order")
    if order:
        return f"order:{order}"
    return f"position:{index + 1}"


def diagram_entries(root: ET.Element, key_mode: str) -> list[DiagramEntry]:
    entries: list[DiagramEntry] = []
    for index, diagram in enumerate(element_children(root, "diagram")):
        entries.append(DiagramEntry(diagram_key(diagram, index, key_mode), index, diagram))
    return entries


def diagram_map(root: ET.Element, key_mode: str) -> dict[str, DiagramEntry]:
    result: dict[str, DiagramEntry] = {}
    for entry in diagram_entries(root, key_mode):
        if entry.key in result:
            raise QetToolError(
                f"Clave de folio duplicada {entry.key}; usa --key position o revisa el archivo."
            )
        result[entry.key] = entry
    return result


def child_count(node: ET.Element, container_name: str, item_name: str) -> int:
    container = first_child(node, container_name)
    if container is None:
        return 0
    return len(element_children(container, item_name))


def collection_terminal_maps(root: ET.Element) -> dict[str, dict[str, str]]:
    collection = first_child(root, "collection")
    if collection is None:
        return {}

    terminal_maps: dict[str, dict[str, str]] = {}

    def visit(parent: ET.Element, path_parts: list[str]) -> None:
        for child in element_children(parent):
            child_name = local_name(child.tag)
            if child_name == "category":
                category_name = child.get("name")
                visit(child, path_parts + ([category_name] if category_name else []))
            elif child_name == "element":
                element_name = child.get("name")
                if not element_name:
                    continue
                element_type = "embed://" + "/".join(path_parts + [element_name])
                terminals: dict[str, str] = {}
                definition = first_child(child, "definition")
                if definition is not None:
                    for terminal in descendants(definition, "terminal"):
                        terminal_uuid = terminal.get("uuid")
                        if terminal_uuid:
                            terminals[terminal_uuid] = terminal.get("name", "")
                terminal_maps[element_type] = terminals

    visit(collection, [])
    return terminal_maps


def conductor_summary(
    diagram: ET.Element,
    element_types: dict[str, str],
    terminal_maps: dict[str, dict[str, str]],
) -> tuple[list[dict[str, Any]], list[str]]:
    conductor_nodes = first_child(diagram, "conductors")
    if conductor_nodes is None:
        return [], []

    conductors: list[dict[str, Any]] = []
    warnings: list[str] = []

    for index, conductor in enumerate(element_children(conductor_nodes, "conductor"), start=1):
        endpoints: list[dict[str, Any]] = []
        for suffix in ("1", "2"):
            element_uuid = conductor.get(f"element{suffix}", "")
            terminal_uuid = conductor.get(f"terminal{suffix}", "")
            terminal_name = conductor.get(f"terminalname{suffix}", "")
            element_type = element_types.get(element_uuid, "")
            element_ok = bool(element_uuid and element_uuid in element_types)
            terminal_ok = False

            if element_ok and terminal_uuid:
                known_terminals = terminal_maps.get(element_type)
                if known_terminals is not None:
                    terminal_ok = terminal_uuid in known_terminals
                else:
                    terminal_ok = True

            if not element_ok:
                warnings.append(
                    f"conductor {index}: element{suffix} no existe en el folio ({element_uuid})"
                )
            elif not terminal_uuid:
                warnings.append(f"conductor {index}: terminal{suffix} no tiene UUID")
            elif not terminal_ok:
                warnings.append(
                    f"conductor {index}: terminal{suffix} no existe en la definicion embebida "
                    f"de {element_type} ({terminal_uuid})"
                )

            endpoints.append(
                {
                    "element_uuid": element_uuid,
                    "element_type": element_type,
                    "terminal_uuid": terminal_uuid,
                    "terminal_name": terminal_name,
                    "element_ok": element_ok,
                    "terminal_ok": terminal_ok,
                }
            )

        conductors.append(
            {
                "index": index,
                "type": conductor.get("type", ""),
                "num": conductor.get("num", ""),
                "endpoints": endpoints,
                "valid": all(endpoint["element_ok"] and endpoint["terminal_ok"] for endpoint in endpoints),
            }
        )

    return conductors, warnings


def diagram_summary(
    diagram: ET.Element,
    key: str,
    index: int,
    terminal_maps: dict[str, dict[str, str]] | None = None,
) -> dict[str, Any]:
    element_nodes = []
    element_types: dict[str, str] = {}
    elements = first_child(diagram, "elements")
    if elements is not None:
        for element in element_children(elements, "element"):
            element_uuid = element.get("uuid", "")
            element_type = element.get("type", "")
            if element_uuid:
                element_types[element_uuid] = element_type
            element_nodes.append(
                {
                    "uuid": element_uuid,
                    "type": element_type,
                    "x": element.get("x", ""),
                    "y": element.get("y", ""),
                }
            )

    conductors, conductor_warnings = conductor_summary(diagram, element_types, terminal_maps or {})
    text_count = child_count(diagram, "inputs", "input") + child_count(diagram, "texts", "text")
    return {
        "key": key,
        "index": index + 1,
        "order": diagram.get("order", ""),
        "title": diagram.get("title", ""),
        "fingerprint": fingerprint(diagram),
        "counts": {
            "elements": child_count(diagram, "elements", "element"),
            "conductors": child_count(diagram, "conductors", "conductor"),
            "texts": text_count,
            "shapes": child_count(diagram, "shapes", "shape"),
            "images": child_count(diagram, "images", "image"),
            "tables": child_count(diagram, "tables", "graphics_table"),
            "terminal_strip_items": child_count(
                diagram,
                "terminal_strip_items",
                "terminal_strip_item",
            ),
        },
        "elements": element_nodes,
        "conductors": conductors,
        "conductor_warnings": conductor_warnings,
    }


def collection_element_names(root: ET.Element) -> list[str]:
    collection = first_child(root, "collection")
    if collection is None:
        return []
    names = [node.get("name", "") for node in descendants(collection, "element")]
    return sorted(name for name in names if name)


def analyze_project(path: Path, key_mode: str) -> dict[str, Any]:
    tree = parse_qet(path)
    root = tree.getroot()
    diagrams = diagram_entries(root, key_mode)
    terminal_maps = collection_terminal_maps(root)
    return {
        "path": str(path),
        "title": root.get("title", ""),
        "version": root.get("version", ""),
        "diagram_count": len(diagrams),
        "diagrams": [
            diagram_summary(entry.node, entry.key, entry.index, terminal_maps)
            for entry in diagrams
        ],
        "collection_element_count": len(collection_element_names(root)),
        "collection_elements": collection_element_names(root),
    }


def format_conductor_endpoint(endpoint: dict[str, Any]) -> str:
    element_uuid = endpoint.get("element_uuid") or "?"
    terminal_name = endpoint.get("terminal_name") or "?"
    terminal_uuid = endpoint.get("terminal_uuid") or "?"
    status = "ok" if endpoint.get("element_ok") and endpoint.get("terminal_ok") else "invalido"
    return f"{element_uuid}:{terminal_name}/{terminal_uuid} ({status})"


def print_analysis_text(projects: list[dict[str, Any]]) -> None:
    for project in projects:
        print(f"Proyecto: {project['path']}")
        print(
            "  "
            f"titulo={project['title']!r} version={project['version']!r} "
            f"folios={project['diagram_count']} "
            f"elementos_coleccion={project['collection_element_count']}"
        )
        for diagram in project["diagrams"]:
            counts = diagram["counts"]
            print(
                "  "
                f"folio {diagram['key']} indice={diagram['index']} "
                f"order={diagram['order']!r} fp={diagram['fingerprint']} "
                f"elementos={counts['elements']} conductores={counts['conductors']} "
                f"textos={counts['texts']} formas={counts['shapes']} "
                f"imagenes={counts['images']} tablas={counts['tables']}"
            )
            for element in diagram["elements"]:
                print(
                    "    "
                    f"elemento uuid={element['uuid']} tipo={element['type']} "
                    f"x={element['x']} y={element['y']}"
                )
            for conductor in diagram["conductors"]:
                endpoints = conductor["endpoints"]
                left = endpoints[0] if endpoints else {}
                right = endpoints[1] if len(endpoints) > 1 else {}
                conductor_num = conductor["num"] or "-"
                state = "ok" if conductor["valid"] else "invalido"
                print(
                    "    "
                    f"conductor #{conductor['index']} {state} num={conductor_num} "
                    f"tipo={conductor['type']!r} "
                    f"{format_conductor_endpoint(left)} -> {format_conductor_endpoint(right)}"
                )
            for warning in diagram["conductor_warnings"]:
                print(f"    advertencia_conductor: {warning}")
        if project["collection_elements"]:
            print("  coleccion:")
            for name in project["collection_elements"]:
                print(f"    {name}")
        print()


def top_level_key(node: ET.Element, index: int) -> tuple[str, str]:
    name_attr = node.get("name") or node.get("title") or node.get("order")
    if name_attr:
        return (local_name(node.tag), name_attr)
    return (local_name(node.tag), str(index))


def describe_global_differences(base_root: ET.Element, source_root: ET.Element) -> list[str]:
    """Reporta diferencias no-folio/no-coleccion sin bloquear el merge."""
    differences: list[str] = []
    if dict(base_root.attrib) != dict(source_root.attrib):
        differences.append("atributos de raiz")

    skipped = {"diagram", "collection"}
    base_children = [
        child for child in element_children(base_root) if local_name(child.tag) not in skipped
    ]
    source_children = [
        child for child in element_children(source_root) if local_name(child.tag) not in skipped
    ]
    base_map = {top_level_key(child, index): child for index, child in enumerate(base_children)}
    source_map = {top_level_key(child, index): child for index, child in enumerate(source_children)}

    for key in sorted(set(base_map) | set(source_map)):
        if key not in base_map:
            differences.append(f"agregado global <{key[0]}>")
        elif key not in source_map:
            differences.append(f"eliminado global <{key[0]}>")
        elif canonical_signature(base_map[key]) != canonical_signature(source_map[key]):
            differences.append(f"modificado global <{key[0]}>")

    return sorted(set(differences))


def collection_child_key(node: ET.Element) -> tuple[str, str]:
    name = node.get("name") or node.get("lang") or node.get("uuid")
    if name:
        return (local_name(node.tag), name)
    return (local_name(node.tag), repr(tuple(sorted(node.attrib.items()))))


def find_collection_child(parent: ET.Element, source_child: ET.Element) -> ET.Element | None:
    source_key = collection_child_key(source_child)
    for child in element_children(parent):
        if collection_child_key(child) == source_key:
            return child
    return None


def merge_collection_children(
    destination_parent: ET.Element,
    source_parent: ET.Element,
    path: str,
    conflicts: list[str],
    warnings: list[str],
) -> None:
    for source_child in element_children(source_parent):
        source_name = local_name(source_child.tag)
        source_key = collection_child_key(source_child)
        match = find_collection_child(destination_parent, source_child)

        if match is None:
            destination_parent.append(copy.deepcopy(source_child))
            continue

        child_path = f"{path}/{source_name}[{source_key[1]}]"
        if source_name in {"category", "names"}:
            merge_collection_children(match, source_child, child_path, conflicts, warnings)
            continue

        if canonical_signature(match) == canonical_signature(source_child):
            continue

        if source_name == "element":
            conflicts.append(f"conflicto de elemento embebido en {child_path}")
        else:
            warnings.append(f"se conservo el nodo de coleccion destino en {child_path}")


def merge_collection(
    base_root: ET.Element,
    source_root: ET.Element,
    conflicts: list[str],
    warnings: list[str],
) -> None:
    source_collection = first_child(source_root, "collection")
    if source_collection is None:
        return

    base_collection = first_child(base_root, "collection")
    if base_collection is None:
        base_root.append(copy.deepcopy(source_collection))
        return

    merge_collection_children(
        base_collection,
        source_collection,
        "/project/collection",
        conflicts,
        warnings,
    )


def replace_diagram(base_root: ET.Element, base_entry: DiagramEntry, source_node: ET.Element) -> None:
    children = list(base_root)
    try:
        current_index = children.index(base_entry.node)
    except ValueError as exc:
        raise QetToolError(
            f"Error interno: no se encontro el folio {base_entry.key} en el arbol base."
        ) from exc
    base_root.remove(base_entry.node)
    base_root.insert(current_index, copy.deepcopy(source_node))


def detect_changes(
    base_path: Path,
    source_paths: list[Path],
    key_mode: str,
) -> tuple[ET.ElementTree, dict[str, DiagramChange], list[str], list[str]]:
    base_tree = parse_qet(base_path)
    base_root = base_tree.getroot()
    base_diagrams = diagram_map(base_root, key_mode)
    changes: dict[str, DiagramChange] = {}
    warnings: list[str] = []
    conflicts: list[str] = []

    for source_path in source_paths:
        source_tree = parse_qet(source_path)
        source_root = source_tree.getroot()
        source_diagrams = diagram_map(source_root, key_mode)

        missing = sorted(set(base_diagrams) - set(source_diagrams))
        added = sorted(set(source_diagrams) - set(base_diagrams))
        if missing or added:
            conflicts.append(
                f"{source_path}: cambio el conjunto de folios; faltan={missing or '-'} agregados={added or '-'}"
            )
            continue

        global_differences = describe_global_differences(base_root, source_root)
        if global_differences:
            warnings.append(f"{source_path}: diferencias globales: {', '.join(global_differences)}")

        changed_keys: list[str] = []
        for key, source_entry in source_diagrams.items():
            base_entry = base_diagrams[key]
            if canonical_signature(source_entry.node) == canonical_signature(base_entry.node):
                continue

            changed_keys.append(key)
            existing = changes.get(key)
            if existing is None:
                changes[key] = DiagramChange(source_path, key, source_entry.node)
                continue

            if canonical_signature(existing.node) != canonical_signature(source_entry.node):
                conflicts.append(
                    f"folio {key} se modifico de forma distinta en {existing.source} y {source_path}"
                )

        if changed_keys:
            warnings.append(f"{source_path}: folios modificados: {', '.join(changed_keys)}")
        else:
            warnings.append(f"{source_path}: no se detectaron cambios de folio")

        merge_collection(base_root, source_root, conflicts, warnings)

    return base_tree, changes, warnings, conflicts


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

    base_tree, changes, warnings, conflicts = detect_changes(base_path, source_paths, key_mode)
    base_root = base_tree.getroot()
    base_diagrams = diagram_map(base_root, key_mode)

    if conflicts:
        return {
            "ok": False,
            "base": str(base_path),
            "sources": [str(path) for path in source_paths],
            "output": str(output_path),
            "changed_diagrams": sorted(changes),
            "warnings": sorted(set(warnings)),
            "conflicts": sorted(set(conflicts)),
        }

    for key, change in sorted(changes.items()):
        replace_diagram(base_root, base_diagrams[key], change.node)
        base_diagrams = diagram_map(base_root, key_mode)

    if not dry_run:
        output_path.parent.mkdir(parents=True, exist_ok=True)
        ET.indent(base_tree, space="    ")
        base_tree.write(output_path, encoding="utf-8", xml_declaration=False)

    return {
        "ok": True,
        "base": str(base_path),
        "sources": [str(path) for path in source_paths],
        "output": str(output_path),
        "dry_run": dry_run,
        "changed_diagrams": sorted(changes),
        "warnings": sorted(set(warnings)),
        "conflicts": [],
        "collection_elements": collection_element_names(base_root),
    }


def print_merge_text(result: dict[str, Any]) -> None:
    status = "OK" if result["ok"] else "CONFLICTO"
    print(f"Estado del merge: {status}")
    print(f"  base: {result['base']}")
    print(f"  salida: {result['output']}")
    print("  fuentes:")
    for source in result["sources"]:
        print(f"    {source}")
    print(f"  folios modificados: {', '.join(result['changed_diagrams']) or '-'}")

    if result.get("collection_elements"):
        print("  elementos de coleccion:")
        for name in result["collection_elements"]:
            print(f"    {name}")

    if result["warnings"]:
        print("  advertencias:")
        for warning in result["warnings"]:
            print(f"    {warning}")

    if result["conflicts"]:
        print("  conflictos:")
        for conflict in result["conflicts"]:
            print(f"    {conflict}")


def command_analyze(args: argparse.Namespace) -> int:
    projects = [analyze_project(Path(path), args.key) for path in args.files]
    if args.json:
        print(json.dumps(projects, indent=2, ensure_ascii=False))
    else:
        print_analysis_text(projects)
    return 0


def command_merge(args: argparse.Namespace) -> int:
    result = merge_projects(
        Path(args.base),
        [Path(path) for path in args.sources],
        Path(args.output),
        args.key,
        args.force,
        args.dry_run,
    )
    if args.json:
        print(json.dumps(result, indent=2, ensure_ascii=False))
    else:
        print_merge_text(result)
    return 0 if result["ok"] else 2


def build_parser() -> argparse.ArgumentParser:
    parser = SpanishArgumentParser(
        description="Analiza y fusiona conservadoramente archivos .qet de QElectroTech por folio.",
        add_help=False,
    )
    parser.add_argument("-h", "--help", action="help", help="muestra esta ayuda y sale.")
    parser.add_argument(
        "--key",
        choices=("order", "position"),
        default="order",
        help="Estrategia para identificar folios. Por defecto usa order; position sirve como respaldo.",
    )
    parser._positionals.title = "argumentos posicionales"
    parser._optionals.title = "opciones"
    subparsers = parser.add_subparsers(
        dest="command",
        required=True,
        title="comandos",
        parser_class=SpanishArgumentParser,
    )

    analyze = subparsers.add_parser(
        "analyze",
        help="Resume la estructura de archivos .qet.",
        add_help=False,
    )
    analyze.add_argument("-h", "--help", action="help", help="muestra esta ayuda y sale.")
    analyze._positionals.title = "argumentos posicionales"
    analyze._optionals.title = "opciones"
    analyze.add_argument("files", nargs="+", help="Archivos .qet a inspeccionar.")
    analyze.add_argument("--json", action="store_true", help="Imprime JSON para automatizacion.")
    analyze.set_defaults(func=command_analyze)

    merge = subparsers.add_parser(
        "merge",
        help="Fusiona cambios de folios sin conflicto en un .qet base.",
        add_help=False,
    )
    merge.add_argument("-h", "--help", action="help", help="muestra esta ayuda y sale.")
    merge._positionals.title = "argumentos posicionales"
    merge._optionals.title = "opciones"
    merge.add_argument("--base", required=True, help="Archivo .qet base.")
    merge.add_argument("--output", required=True, help="Archivo .qet de salida fusionada.")
    merge.add_argument("--force", action="store_true", help="Sobrescribe la salida si ya existe.")
    merge.add_argument("--dry-run", action="store_true", help="Analiza el merge sin escribir salida.")
    merge.add_argument("--json", action="store_true", help="Imprime JSON para automatizacion.")
    merge.add_argument("sources", nargs="+", help="Archivos .qet editados que se van a fusionar.")
    merge.set_defaults(func=command_merge)

    return parser


def main(argv: list[str] | None = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)
    try:
        return args.func(args)
    except QetToolError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
