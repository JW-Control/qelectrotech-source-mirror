#!/usr/bin/env python3
"""Incremental JW-QET merge extension for folios created after checkout.

The stable qet_folio_merge engine intentionally rejected any change to the set
of folios. This module keeps that conservative behavior for deletions and
renumbering, but allows a session to append new folios at the end of the
baseline. Existing folio merge rules and embedded-element 3-way handling stay
unchanged.
"""

from __future__ import annotations

import copy
import xml.etree.ElementTree as ET
from pathlib import Path
from typing import Any

import qet_folio_merge as engine


def _numeric_order(key: str) -> int | None:
    if not key.startswith("order:"):
        return None
    try:
        return int(key.split(":", 1)[1])
    except ValueError:
        return None


def _change_sort_key(item: tuple[str, engine.DiagramChange]) -> tuple[int, int | str]:
    key = item[0]
    order = _numeric_order(key)
    return (0, order) if order is not None else (1, key)


def _insert_diagram_after_last(root: ET.Element, node: ET.Element) -> None:
    items = list(root)
    last_diagram_index: int | None = None
    collection_index: int | None = None

    for index, child in enumerate(items):
        kind = engine.local_name(child.tag)
        if kind == "diagram":
            last_diagram_index = index
        elif kind == "collection" and collection_index is None:
            collection_index = index

    clone = copy.deepcopy(node)
    if last_diagram_index is not None:
        root.insert(last_diagram_index + 1, clone)
    elif collection_index is not None:
        root.insert(collection_index, clone)
    else:
        root.append(clone)


def _validate_append_only_additions(
    source_path: Path,
    base_diagrams: dict[str, engine.DiagramEntry],
    source_diagrams: dict[str, engine.DiagramEntry],
    conflicts: list[str],
) -> tuple[list[str], bool]:
    missing = sorted(set(base_diagrams) - set(source_diagrams))
    if missing:
        conflicts.append(
            f"{source_path}: se eliminaron o renumeraron folios de la baseline: {', '.join(missing)}"
        )
        return [], False

    added = [key for key in source_diagrams if key not in base_diagrams]
    if not added:
        return [], True

    base_orders = [order for order in (_numeric_order(key) for key in base_diagrams) if order is not None]
    max_base = max(base_orders, default=0)
    invalid = [
        key
        for key in added
        if _numeric_order(key) is None or _numeric_order(key) <= max_base
    ]
    if invalid:
        conflicts.append(
            f"{source_path}: por ahora solo se admite agregar folios al final del proyecto; "
            f"revisa {', '.join(invalid)}"
        )
        return added, False
    return added, True


def detect_changes_allow_appended_folios(
    base_path: Path,
    source_paths: list[Path],
    mode: str,
) -> tuple[ET.ElementTree, dict[str, engine.DiagramChange], list[str], list[str]]:
    tree = engine.parse_qet(base_path)
    root = tree.getroot()
    baseline = copy.deepcopy(root)
    base_diagrams = engine.diagram_map(root, mode)
    changes: dict[str, engine.DiagramChange] = {}
    warnings: list[str] = []
    conflicts: list[str] = []

    for source_path in source_paths:
        source_root = engine.parse_qet(source_path).getroot()
        source_diagrams = engine.diagram_map(source_root, mode)
        added, valid_shape = _validate_append_only_additions(
            source_path, base_diagrams, source_diagrams, conflicts
        )
        if not valid_shape:
            continue
        if added:
            warnings.append(
                f"{source_path}: folios nuevos a integrar: {', '.join(added)}"
            )

        diffs = engine.global_differences(baseline, source_root)
        if diffs:
            warnings.append(
                f"{source_path}: diferencias globales: {', '.join(diffs)}"
            )

        changed: list[str] = []
        for key, entry in source_diagrams.items():
            base_entry = base_diagrams.get(key)
            if base_entry is not None and engine.signature(entry.node) == engine.signature(base_entry.node):
                continue

            changed.append(key)
            previous = changes.get(key)
            if previous is None:
                changes[key] = engine.DiagramChange(source_path, key, entry.node)
            elif engine.signature(previous.node) != engine.signature(entry.node):
                conflicts.append(
                    f"folio {key} se modifico de forma distinta en {previous.source} y {source_path}"
                )

        warnings.append(
            f"{source_path}: folios modificados: {', '.join(changed)}"
            if changed
            else f"{source_path}: no se detectaron cambios de folio"
        )
        engine.merge_collection(
            root,
            baseline,
            source_root,
            engine.used_embed_types(source_diagrams, changed),
            conflicts,
            warnings,
        )

    return tree, changes, warnings, conflicts


def merge_projects(
    base_path: Path,
    source_paths: list[Path],
    output_path: Path,
    key_mode: str,
    force: bool,
    dry_run: bool,
) -> dict[str, Any]:
    if output_path.exists() and not force and not dry_run:
        raise engine.QetToolError(
            f"La salida ya existe: {output_path}. Usa --force para sobrescribir."
        )

    tree, changes, warnings, conflicts = detect_changes_allow_appended_folios(
        base_path, source_paths, key_mode
    )
    root = tree.getroot()
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

    current_diagrams = engine.diagram_map(root, key_mode)
    added_to_master: list[str] = []
    for key, change in sorted(changes.items(), key=_change_sort_key):
        if key in current_diagrams:
            engine.replace_diagram(root, current_diagrams[key], change.node)
        else:
            _insert_diagram_after_last(root, change.node)
            added_to_master.append(key)
        current_diagrams = engine.diagram_map(root, key_mode)

    if not dry_run:
        output_path.parent.mkdir(parents=True, exist_ok=True)
        ET.indent(tree, space="    ")
        tree.write(output_path, encoding="utf-8", xml_declaration=False)

    return {
        "ok": True,
        "base": str(base_path),
        "sources": [str(path) for path in source_paths],
        "output": str(output_path),
        "dry_run": dry_run,
        "changed_diagrams": sorted(changes),
        "added_diagrams": sorted(added_to_master),
        "warnings": sorted(set(warnings)),
        "conflicts": [],
        "collection_elements": engine.collection_element_names(root),
    }
