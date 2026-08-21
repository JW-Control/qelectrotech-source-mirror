#!/usr/bin/env python3
"""Publica una copia JW-QET completa en modo de mantenimiento exclusivo.

Este flujo NO es un merge colaborativo por folios. Se usa cuando una sola PC
reorganiza la estructura global del proyecto (por ejemplo, reordenar, agregar o
eliminar folios) y necesita promover su copia de trabajo completa a 00_MASTER.

La operación es deliberadamente conservadora:
- exige una sesión colaborativa v2 conocida;
- exige que el maestro actual siga siendo el mismo del checkout/baseline;
- bloquea si otro perfil conserva reservas;
- bloquea si existen entregas pendientes de otro perfil;
- archiva el maestro actual antes de reemplazarlo;
- verifica el hash después de publicar;
- deja la copia de trabajo en refresh_required para iniciar una nueva ronda.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import shutil
import sys
import tempfile
import xml.etree.ElementTree as ET
from datetime import datetime
from pathlib import Path
from typing import Any

MANIFEST_SUFFIX = ".jwqet.json"


class ExclusivePublishError(RuntimeError):
    pass


def now_iso() -> str:
    return datetime.now().astimezone().replace(microsecond=0).isoformat()


def timestamp() -> str:
    return datetime.now().strftime("%Y%m%d_%H%M%S")


def load_json(path: Path) -> dict[str, Any]:
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except FileNotFoundError as exc:
        raise ExclusivePublishError(f"No existe: {path}") from exc
    except json.JSONDecodeError as exc:
        raise ExclusivePublishError(f"JSON invalido en {path}: {exc}") from exc
    if not isinstance(payload, dict):
        raise ExclusivePublishError(f"Se esperaba un objeto JSON en {path}")
    return payload


def write_json_atomic(path: Path, payload: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_name(path.name + ".tmp")
    temp.write_text(json.dumps(payload, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    os.replace(temp, path)


def file_sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def infer_workspace(working: Path) -> Path:
    for parent in working.resolve().parents:
        if parent.name == "02_WORKING":
            return parent.parent
    raise ExclusivePublishError(f"No se pudo localizar el workspace desde: {working}")


def master_path(workspace: Path, manifest: dict[str, Any]) -> Path:
    rel = str(manifest.get("master_relpath", "")).strip()
    if rel:
        candidate = workspace / Path(rel.replace("\\", "/"))
        if candidate.is_file():
            return candidate.resolve()

    master_dir = workspace / "00_MASTER"
    candidates = sorted(master_dir.glob("*.qet"))
    if len(candidates) != 1:
        raise ExclusivePublishError(
            f"Se esperaba un unico .qet en 00_MASTER y se encontraron {len(candidates)}."
        )
    return candidates[0].resolve()


def validate_qet(path: Path) -> list[tuple[str, str]]:
    try:
        root = ET.parse(path).getroot()
    except FileNotFoundError as exc:
        raise ExclusivePublishError(f"No existe el proyecto: {path}") from exc
    except ET.ParseError as exc:
        raise ExclusivePublishError(f"XML invalido en {path}: {exc}") from exc
    if root.tag.rsplit("}", 1)[-1] != "project":
        raise ExclusivePublishError(f"La raiz de {path} no es <project>.")

    diagrams: list[tuple[str, str]] = []
    for position, node in enumerate(
        [child for child in list(root) if child.tag.rsplit("}", 1)[-1] == "diagram"],
        start=1,
    ):
        order = (node.get("order") or str(position)).strip()
        title = (node.get("title") or "").strip()
        diagrams.append((order, title))
    if not diagrams:
        raise ExclusivePublishError("La copia de trabajo no contiene folios.")
    return diagrams


def other_reservations(workspace: Path, current_user: str) -> list[str]:
    path = workspace / ".jwqet" / "reservations.json"
    if not path.exists():
        return []
    payload = load_json(path)
    profiles = payload.get("profiles", {})
    if not isinstance(profiles, dict):
        return []

    conflicts: list[str] = []
    for slug, raw in profiles.items():
        entry = raw if isinstance(raw, dict) else {}
        user = str(entry.get("user") or slug)
        if user.casefold() == current_user.casefold():
            continue
        folios = entry.get("folios", [])
        if isinstance(folios, list) and any(isinstance(item, str) and item for item in folios):
            conflicts.append(f"{user}: {', '.join(str(item) for item in folios if isinstance(item, str))}")
    return conflicts


def pending_other_deliveries(workspace: Path, current_user: str) -> list[str]:
    conflicts: list[str] = []
    roots = [workspace / ".jwqet" / "incoming", workspace / "03_INCOMING"]
    seen: set[Path] = set()
    for root in roots:
        if not root.is_dir():
            continue
        for manifest_path in root.rglob(f"*{MANIFEST_SUFFIX}"):
            resolved = manifest_path.resolve()
            if resolved in seen:
                continue
            seen.add(resolved)
            try:
                payload = load_json(resolved)
            except ExclusivePublishError:
                continue
            if payload.get("status") != "submitted":
                continue
            user = str(payload.get("user") or resolved.parent.name)
            if user.casefold() != current_user.casefold():
                conflicts.append(f"{user}: {resolved}")
    return conflicts


def clear_current_reservations(workspace: Path, current_user: str, current_slug: str) -> None:
    path = workspace / ".jwqet" / "reservations.json"
    if not path.exists():
        return
    payload = load_json(path)
    profiles = payload.get("profiles", {})
    if not isinstance(profiles, dict):
        return
    for slug in list(profiles):
        raw = profiles.get(slug)
        entry = raw if isinstance(raw, dict) else {}
        user = str(entry.get("user") or slug)
        if slug == current_slug or user.casefold() == current_user.casefold():
            profiles.pop(slug, None)
    payload["profiles"] = profiles
    payload["updated_at"] = now_iso()
    write_json_atomic(path, payload)


def mark_current_incoming_published(
    workspace: Path, current_user: str, new_master_hash: str
) -> None:
    roots = [workspace / ".jwqet" / "incoming", workspace / "03_INCOMING"]
    seen: set[Path] = set()
    for root in roots:
        if not root.is_dir():
            continue
        for manifest_path in root.rglob(f"*{MANIFEST_SUFFIX}"):
            resolved = manifest_path.resolve()
            if resolved in seen:
                continue
            seen.add(resolved)
            try:
                payload = load_json(resolved)
            except ExclusivePublishError:
                continue
            user = str(payload.get("user") or resolved.parent.name)
            if user.casefold() != current_user.casefold() or payload.get("status") != "submitted":
                continue
            payload["status"] = "published"
            payload["published_at"] = now_iso()
            payload["published_master_sha256"] = new_master_hash
            payload["exclusive_publish"] = True
            write_json_atomic(resolved, payload)


def publish(working: Path, apply: bool) -> dict[str, Any]:
    working = working.resolve()
    if working.suffix.lower() != ".qet" or not working.is_file():
        raise ExclusivePublishError(f"La copia de trabajo no es un .qet valido: {working}")

    manifest_path = Path(str(working) + MANIFEST_SUFFIX)
    manifest = load_json(manifest_path)
    if int(manifest.get("workflow_version", 0)) < 2:
        raise ExclusivePublishError("La sesion no usa el workflow colaborativo v2.")
    if manifest.get("status") not in {"checked_out", "submitted"}:
        raise ExclusivePublishError(
            f"La copia no esta en un estado publicable: {manifest.get('status', 'desconocido')}"
        )

    workspace = infer_workspace(working)
    master = master_path(workspace, manifest)
    diagrams = validate_qet(working)
    user = str(manifest.get("user", "")).strip()
    user_slug = str(manifest.get("user_slug", "")).strip()
    if not user or not user_slug:
        raise ExclusivePublishError("El manifiesto no contiene un perfil colaborativo valido.")

    expected_master = str(manifest.get("master_sha256") or manifest.get("baseline_sha256") or "").strip()
    current_master_hash = file_sha256(master)
    if expected_master and current_master_hash != expected_master:
        raise ExclusivePublishError(
            "El maestro cambio desde que se creo esta copia. No se puede hacer una publicacion exclusiva segura."
        )

    reservations = other_reservations(workspace, user)
    if reservations:
        raise ExclusivePublishError(
            "Otro perfil conserva reservas. Cierra/libera esas sesiones antes de publicar:\n- "
            + "\n- ".join(reservations)
        )

    pending = pending_other_deliveries(workspace, user)
    if pending:
        raise ExclusivePublishError(
            "Hay entregas pendientes de otros perfiles. Publicalas o descartalas antes de continuar:\n- "
            + "\n- ".join(pending)
        )

    result: dict[str, Any] = {
        "workspace": str(workspace),
        "working": str(working),
        "master": str(master),
        "user": user,
        "folio_count": len(diagrams),
        "folios": [{"order": order, "title": title} for order, title in diagrams],
        "master_sha256_before": current_master_hash,
        "working_sha256": file_sha256(working),
        "apply": apply,
    }
    if not apply:
        return result

    history_dir = workspace / ".jwqet" / "history" / "master"
    history_dir.mkdir(parents=True, exist_ok=True)
    archive = history_dir / f"{timestamp()}_{master.name}"
    shutil.copy2(master, archive)
    if file_sha256(archive) != current_master_hash:
        raise ExclusivePublishError("La copia historica del maestro no coincide; se cancela la publicacion.")

    with tempfile.NamedTemporaryFile(delete=False, suffix=".qet") as temp_handle:
        temp_path = Path(temp_handle.name)
    try:
        shutil.copy2(working, temp_path)
        shutil.copy2(temp_path, master)
    finally:
        temp_path.unlink(missing_ok=True)

    new_master_hash = file_sha256(master)
    expected_working_hash = file_sha256(working)
    if new_master_hash != expected_working_hash:
        shutil.copy2(archive, master)
        raise ExclusivePublishError(
            "El hash del maestro publicado no coincide con la copia de trabajo; se restauro el maestro anterior."
        )

    manifest["status"] = "refresh_required"
    manifest["published_at"] = now_iso()
    manifest["published_master_sha256"] = new_master_hash
    manifest["exclusive_publish"] = True
    manifest["exclusive_archive_path"] = str(archive)
    write_json_atomic(manifest_path, manifest)

    mark_current_incoming_published(workspace, user, new_master_hash)
    clear_current_reservations(workspace, user, user_slug)

    log = {
        "event": "exclusive_publish",
        "published_at": now_iso(),
        "user": user,
        "working": str(working),
        "master": str(master),
        "archive": str(archive),
        "master_sha256_before": current_master_hash,
        "master_sha256_after": new_master_hash,
        "folio_count": len(diagrams),
        "folios": result["folios"],
    }
    logs_dir = workspace / ".jwqet" / "logs"
    write_json_atomic(logs_dir / f"{timestamp()}_exclusive_publish_{user_slug}.json", log)

    result["archive"] = str(archive)
    result["master_sha256_after"] = new_master_hash
    result["published"] = True
    return result


def print_result(result: dict[str, Any]) -> None:
    mode = "PUBLICACION EXCLUSIVA LISTA" if result.get("published") else "SIMULACION OK"
    print(mode)
    print(f"Perfil: {result['user']}")
    print(f"Maestro: {result['master']}")
    print(f"Copia: {result['working']}")
    print(f"Folios resultantes: {result['folio_count']}")
    for folio in result["folios"]:
        title = f" - {folio['title']}" if folio["title"] else ""
        print(f"  {folio['order']}{title}")
    if result.get("archive"):
        print(f"Respaldo del maestro anterior: {result['archive']}")
    if not result.get("published"):
        print("No se modifico ningun archivo. Repite con --apply para publicar.")


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Promueve una copia completa a 00_MASTER cuando una sola PC realiza mantenimiento estructural."
    )
    parser.add_argument("working", help="Ruta del .qet dentro de 02_WORKING/<perfil>")
    parser.add_argument("--apply", action="store_true", help="Aplicar la publicacion; sin esta opcion solo valida")
    parser.add_argument("--json", action="store_true", help="Imprimir el resultado en JSON")
    return parser


def main(argv: list[str] | None = None) -> int:
    args = build_parser().parse_args(argv)
    try:
        result = publish(Path(args.working), args.apply)
        if args.json:
            print(json.dumps(result, indent=2, ensure_ascii=False))
        else:
            print_result(result)
        return 0
    except ExclusivePublishError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
