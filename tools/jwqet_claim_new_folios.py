#!/usr/bin/env python3
"""Claim folios created in a JW-QET working copy after checkout.

This is an incremental compatibility helper for collaboration workflow v2.
Existing folios keep the reservation model chosen at checkout. Folios that do
not exist in the session baseline may be claimed by the current profile so the
existing guarded submit flow can transport them without weakening protection
for any pre-existing folio.

For now only append-only additions are accepted. Deleting folios or inserting a
new folio in the middle of the baseline remains a conflict and must be handled
explicitly in a later workflow revision.
"""

from __future__ import annotations

import argparse
import json
import os
import sys
import xml.etree.ElementTree as ET
from pathlib import Path
from typing import Any

MANIFEST_SUFFIX = ".jwqet.json"
WORKSPACE_MARKERS = {
    "00_MASTER",
    "01_BASELINES",
    "02_WORKING",
    "03_INCOMING",
    "04_PUBLISHED",
    "05_ARCHIVE",
    "06_LOGS",
    ".jwqet",
}


class ClaimError(RuntimeError):
    pass


def load_json(path: Path) -> dict[str, Any]:
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except FileNotFoundError as exc:
        raise ClaimError(f"No existe: {path}") from exc
    except json.JSONDecodeError as exc:
        raise ClaimError(f"JSON invalido en {path}: {exc}") from exc
    if not isinstance(payload, dict):
        raise ClaimError(f"Se esperaba un objeto JSON en {path}")
    return payload


def write_json_atomic(path: Path, payload: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_name(path.name + ".tmp")
    temp.write_text(json.dumps(payload, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    os.replace(temp, path)


def infer_workspace(working: Path) -> Path:
    for parent in working.resolve().parents:
        if parent.name == "02_WORKING":
            return parent.parent
    raise ClaimError(f"No se pudo localizar el workspace desde: {working}")


def portable_suffix(value: str | None) -> Path | None:
    if not value:
        return None
    parts = [part for part in str(value).replace("\\", "/").split("/") if part and part != "."]
    for index, part in enumerate(parts):
        if part in WORKSPACE_MARKERS:
            return Path(*parts[index:])
    return None


def resolve_member(
    workspace: Path,
    manifest: dict[str, Any],
    relative_field: str,
    absolute_field: str,
    label: str,
) -> Path:
    relative = str(manifest.get(relative_field, "")).strip()
    if relative:
        candidate = workspace / Path(relative.replace("\\", "/"))
        if candidate.exists():
            return candidate.resolve()

    stored = str(manifest.get(absolute_field, "")).strip()
    suffix = portable_suffix(stored)
    if suffix is not None:
        candidate = workspace / suffix
        if candidate.exists():
            return candidate.resolve()

    if stored:
        candidate = Path(stored)
        if candidate.exists():
            return candidate.resolve()

    raise ClaimError(f"No se pudo resolver {label} desde el manifiesto.")


def diagram_keys(path: Path) -> list[str]:
    try:
        root = ET.parse(path).getroot()
    except FileNotFoundError as exc:
        raise ClaimError(f"No existe el proyecto: {path}") from exc
    except ET.ParseError as exc:
        raise ClaimError(f"XML invalido en {path}: {exc}") from exc

    keys: list[str] = []
    for position, node in enumerate(
        [child for child in list(root) if child.tag.rsplit("}", 1)[-1] == "diagram"],
        start=1,
    ):
        order = (node.get("order") or "").strip()
        key = f"order:{order}" if order else f"position:{position}"
        if key in keys:
            raise ClaimError(f"Clave de folio duplicada en {path}: {key}")
        keys.append(key)
    return keys


def numeric_order(key: str) -> int | None:
    if not key.startswith("order:"):
        return None
    try:
        return int(key.split(":", 1)[1])
    except ValueError:
        return None


def append_only_new_folios(baseline_keys: list[str], working_keys: list[str]) -> list[str]:
    baseline_set = set(baseline_keys)
    working_set = set(working_keys)

    missing = [key for key in baseline_keys if key not in working_set]
    if missing:
        raise ClaimError(
            "La copia elimina o renumera folios de la baseline; esta operacion todavia no esta soportada: "
            + ", ".join(missing)
        )

    added = [key for key in working_keys if key not in baseline_set]
    if not added:
        return []

    base_orders = [order for order in (numeric_order(key) for key in baseline_keys) if order is not None]
    max_base = max(base_orders, default=0)
    invalid = [key for key in added if numeric_order(key) is None or numeric_order(key) <= max_base]
    if invalid:
        raise ClaimError(
            "Por ahora los folios nuevos deben agregarse al final del proyecto. Revisa: "
            + ", ".join(invalid)
        )
    return added


def reserved_owner(reservations: dict[str, Any], folio: str, current_user: str) -> str | None:
    profiles = reservations.get("profiles", {})
    if not isinstance(profiles, dict):
        return None
    for slug, raw_entry in profiles.items():
        entry = raw_entry if isinstance(raw_entry, dict) else {}
        user = str(entry.get("user") or slug)
        if user.casefold() == current_user.casefold():
            continue
        folios = entry.get("folios", [])
        if isinstance(folios, list) and folio in folios:
            return user
    return None


def unique_in_order(values: list[str]) -> list[str]:
    result: list[str] = []
    for value in values:
        if value not in result:
            result.append(value)
    return result


def claim(working: Path, dry_run: bool = False) -> dict[str, Any]:
    working = working.resolve()
    if working.suffix.lower() != ".qet" or not working.is_file():
        raise ClaimError(f"La copia de trabajo no es un .qet valido: {working}")

    manifest_path = Path(str(working) + MANIFEST_SUFFIX)
    manifest = load_json(manifest_path)
    if int(manifest.get("workflow_version", 0)) < 2:
        raise ClaimError("La sesion no usa el workflow colaborativo v2.")
    if manifest.get("status") != "checked_out":
        raise ClaimError(
            f"La copia no esta editable; estado actual: {manifest.get('status', 'desconocido')}"
        )

    workspace = infer_workspace(working)
    baseline = resolve_member(
        workspace,
        manifest,
        "baseline_relpath",
        "baseline_path",
        "la baseline colaborativa",
    )
    baseline_keys = diagram_keys(baseline)
    working_keys = diagram_keys(working)
    added = append_only_new_folios(baseline_keys, working_keys)

    user = str(manifest.get("user", "")).strip()
    user_slug = str(manifest.get("user_slug", "")).strip()
    if not user or not user_slug:
        raise ClaimError("El manifiesto no contiene un perfil colaborativo valido.")

    reservations_path = workspace / ".jwqet" / "reservations.json"
    reservations = load_json(reservations_path) if reservations_path.exists() else {
        "schema": "jw-qet-reservations.v1",
        "profiles": {},
    }

    collisions: list[str] = []
    for folio in added:
        owner = reserved_owner(reservations, folio, user)
        if owner:
            collisions.append(f"{folio} -> {owner}")
    if collisions:
        raise ClaimError(
            "No se pueden reservar los folios nuevos porque otro perfil ya reclama esas claves: "
            + "; ".join(collisions)
        )

    reserved = [
        str(value)
        for value in manifest.get("reserved_folios", [])
        if isinstance(value, str)
    ]
    reserved = unique_in_order(reserved + added)
    created = [
        str(value)
        for value in manifest.get("created_folios", [])
        if isinstance(value, str)
    ]
    created = unique_in_order(created + added)

    result = {
        "working": str(working),
        "baseline": str(baseline),
        "user": user,
        "added_folios": added,
        "reserved_folios": reserved,
        "created_folios": created,
        "changed": bool(added),
        "dry_run": dry_run,
    }
    if dry_run or not added:
        return result

    manifest["reserved_folios"] = reserved
    manifest["created_folios"] = created
    manifest["new_folio_claim_version"] = 1
    write_json_atomic(manifest_path, manifest)

    profiles = reservations.setdefault("profiles", {})
    if not isinstance(profiles, dict):
        profiles = {}
        reservations["profiles"] = profiles
    entry = profiles.get(user_slug, {})
    if not isinstance(entry, dict):
        entry = {}
    entry["user"] = user
    entry["user_slug"] = user_slug
    entry["folios"] = reserved
    profiles[user_slug] = entry
    write_json_atomic(reservations_path, reservations)
    return result


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Reserva para el perfil actual los folios creados localmente despues del checkout."
    )
    parser.add_argument("working", help="Ruta del .qet dentro de 02_WORKING/<perfil>")
    parser.add_argument("--dry-run", action="store_true", help="Solo mostrar lo que se reservaria")
    parser.add_argument("--json", action="store_true", help="Imprimir resultado JSON")
    return parser


def main(argv: list[str] | None = None) -> int:
    args = build_parser().parse_args(argv)
    try:
        result = claim(Path(args.working), args.dry_run)
        if args.json:
            print(json.dumps(result, indent=2, ensure_ascii=False))
        elif not result["added_folios"]:
            print("No se detectaron folios nuevos respecto de la baseline.")
        else:
            action = "Se reservarian" if args.dry_run else "Folios nuevos reservados"
            print(f"{action}: {', '.join(result['added_folios'])}")
            print(f"Perfil: {result['user']}")
            print("La copia puede continuar con el flujo protegido de entrega.")
        return 0
    except ClaimError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
