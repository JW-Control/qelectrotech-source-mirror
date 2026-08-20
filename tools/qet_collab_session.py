#!/usr/bin/env python3
"""Gestiona sesiones colaborativas offline para proyectos QET.

Esta herramienta no modifica el formato .qet. Crea copias de trabajo y un
manifiesto sidecar .jwqet.json que luego puede reutilizar una UI dentro de QET.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import shutil
import sys
from datetime import datetime
from pathlib import Path
from typing import Any

TOOL_DIR = Path(__file__).resolve().parent
if str(TOOL_DIR) not in sys.path:
    sys.path.insert(0, str(TOOL_DIR))

from qet_folio_merge import QetToolError, merge_projects, print_merge_text  # noqa: E402

SCHEMA = "jw-qet-collab-session.v1"
MANIFEST_SUFFIX = ".jwqet.json"
WORKSPACE_DIRS = {
    "00_MASTER",
    "01_BASELINES",
    "02_WORKING",
    "03_INCOMING",
    "04_PUBLISHED",
    "05_ARCHIVE",
    "06_LOGS",
}


class SpanishArgumentParser(argparse.ArgumentParser):
    """ArgumentParser with Spanish help headings."""

    def format_usage(self) -> str:
        return super().format_usage().replace("usage:", "uso:", 1)

    def format_help(self) -> str:
        return super().format_help().replace("usage:", "uso:", 1)


def now_iso() -> str:
    return datetime.now().astimezone().replace(microsecond=0).isoformat()


def timestamp() -> str:
    return datetime.now().strftime("%Y%m%d_%H%M%S")


def user_slug(user: str) -> str:
    slug = re.sub(r"[^A-Za-z0-9_.-]+", "_", user.strip()).strip("._-")
    return slug or "usuario"


def file_sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def require_qet_file(path: Path, label: str) -> Path:
    if not path.exists():
        raise QetToolError(f"{label} no existe: {path}")
    if not path.is_file():
        raise QetToolError(f"{label} no es un archivo: {path}")
    if path.suffix.lower() != ".qet":
        raise QetToolError(f"{label} debe ser un archivo .qet: {path}")
    return path


def manifest_path_for(qet_path: Path) -> Path:
    return Path(str(qet_path) + MANIFEST_SUFFIX)


def unique_path(path: Path) -> Path:
    if not path.exists():
        return path
    for index in range(2, 1000):
        candidate = path.with_name(f"{path.stem}-{index}{path.suffix}")
        if not candidate.exists():
            return candidate
    raise QetToolError(f"No se pudo generar una ruta unica para: {path}")


def write_json(path: Path, payload: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(payload, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")


def read_manifest(path: Path) -> dict[str, Any]:
    if not path.exists():
        raise QetToolError(f"El manifiesto no existe: {path}")
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except json.JSONDecodeError as exc:
        raise QetToolError(f"Manifiesto JSON invalido en {path}: {exc}") from exc

    if payload.get("schema") != SCHEMA:
        raise QetToolError(f"Manifiesto no compatible en {path}: {payload.get('schema')!r}")
    return payload


def guarded_copy(source: Path, destination: Path, force: bool) -> None:
    if destination.exists() and not force:
        raise QetToolError(f"La salida ya existe: {destination}. Usa --force para sobrescribir.")
    destination.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, destination)


def relative_to_workspace(path: Path, workspace_path: Path) -> str | None:
    """Return a portable POSIX-style path when *path* lives in the workspace."""
    try:
        return path.resolve().relative_to(workspace_path.resolve()).as_posix()
    except ValueError:
        return None


def portable_workspace_suffix(stored_path: str | None) -> Path | None:
    """Extract 00_MASTER/... or another known workspace suffix from any drive.

    Windows absolute paths stored by the original MVP (for example G:\\... or
    H:\\...) are intentionally parsed as text so a manifest can be consumed on
    a PC where Google Drive uses a different drive letter.
    """
    if not stored_path:
        return None

    normalized = str(stored_path).replace("\\", "/")
    parts = [part for part in normalized.split("/") if part and part != "."]
    for index, part in enumerate(parts):
        if part in WORKSPACE_DIRS:
            return Path(*parts[index:])
    return None


def infer_workspace_from_manifest(manifest_path: Path) -> Path | None:
    """Infer the shared JW_QET_COLLAB root from a working/incoming sidecar."""
    manifest_path = manifest_path.resolve()
    for parent in manifest_path.parents:
        if parent.name in {"02_WORKING", "03_INCOMING"}:
            return parent.parent
    return None


def resolve_workspace(manifest_path: Path, manifest: dict[str, Any]) -> Path:
    """Resolve the workspace on the current PC, independent of drive letter."""
    inferred = infer_workspace_from_manifest(manifest_path)
    if inferred is not None:
        return inferred

    stored_workspace = manifest.get("workspace_path")
    if stored_workspace:
        stored = Path(stored_workspace)
        if stored.exists():
            return stored.resolve()

    raise QetToolError(
        "No se pudo determinar el workspace colaborativo desde el manifiesto: "
        f"{manifest_path}"
    )


def resolve_manifest_member(
    manifest_path: Path,
    manifest: dict[str, Any],
    absolute_field: str,
    relative_field: str,
    label: str,
    *,
    qet_required: bool = False,
    prefer_sidecar_qet: bool = False,
) -> Path:
    """Resolve a manifest path using the workspace visible on this PC.

    Resolution order deliberately favors portable workspace-relative paths over
    absolute paths saved on the originating machine. This makes G:/ and H:/
    mounts interoperable while keeping old v1 manifests usable.
    """
    workspace = resolve_workspace(manifest_path, manifest)

    if prefer_sidecar_qet and str(manifest_path).endswith(MANIFEST_SUFFIX):
        sibling_qet = Path(str(manifest_path)[: -len(MANIFEST_SUFFIX)])
        if sibling_qet.exists():
            return require_qet_file(sibling_qet, label) if qet_required else sibling_qet

    relative_value = manifest.get(relative_field)
    if relative_value:
        relative_path = Path(str(relative_value).replace("\\", "/"))
        candidate = workspace / relative_path
        if candidate.exists() or not qet_required:
            return require_qet_file(candidate, label) if qet_required else candidate

    stored_value = manifest.get(absolute_field)
    suffix = portable_workspace_suffix(stored_value)
    if suffix is not None:
        candidate = workspace / suffix
        if candidate.exists() or not qet_required:
            return require_qet_file(candidate, label) if qet_required else candidate

    if stored_value:
        stored_path = Path(stored_value)
        if stored_path.exists() or not qet_required:
            return require_qet_file(stored_path, label) if qet_required else stored_path

    raise QetToolError(f"No se pudo resolver {label.lower()} desde: {manifest_path}")


def checkout_session(master_path: Path, workspace_path: Path, user: str, force: bool) -> dict[str, Any]:
    master_path = require_qet_file(master_path, "El maestro")
    workspace_path = workspace_path.resolve()
    stamp = timestamp()
    slug = user_slug(user)
    workspace_path.mkdir(parents=True, exist_ok=True)

    baseline_dir = workspace_path / "01_BASELINES"
    working_dir = workspace_path / "02_WORKING" / slug
    incoming_dir = workspace_path / "03_INCOMING" / slug
    published_dir = workspace_path / "04_PUBLISHED"
    logs_dir = workspace_path / "06_LOGS"

    baseline_path = unique_path(baseline_dir / f"{stamp}_{master_path.name}")
    working_name = f"{master_path.stem}_{slug}_{stamp}{master_path.suffix}"
    working_path = unique_path(working_dir / working_name)
    incoming_path = incoming_dir / working_path.name

    master_hash = file_sha256(master_path)
    guarded_copy(master_path, baseline_path, force)
    guarded_copy(baseline_path, working_path, force)

    manifest = {
        "schema": SCHEMA,
        "created_at": now_iso(),
        "status": "checked_out",
        "user": user,
        "user_slug": slug,
        "master_path": str(master_path.resolve()),
        "workspace_path": str(workspace_path),
        "baseline_path": str(baseline_path.resolve()),
        "working_path": str(working_path.resolve()),
        "incoming_path": str(incoming_path.resolve()),
        "published_dir": str(published_dir.resolve()),
        "logs_dir": str(logs_dir.resolve()),
        "master_relpath": relative_to_workspace(master_path, workspace_path),
        "baseline_relpath": relative_to_workspace(baseline_path, workspace_path),
        "working_relpath": relative_to_workspace(working_path, workspace_path),
        "incoming_relpath": relative_to_workspace(incoming_path, workspace_path),
        "published_relpath": relative_to_workspace(published_dir, workspace_path),
        "logs_relpath": relative_to_workspace(logs_dir, workspace_path),
        "master_sha256": master_hash,
        "baseline_sha256": file_sha256(baseline_path),
        "working_sha256": file_sha256(working_path),
    }

    manifest_path = manifest_path_for(working_path)
    write_json(manifest_path, manifest)
    write_json(logs_dir / f"{stamp}_checkout_{slug}.json", manifest | {"manifest_path": str(manifest_path.resolve())})
    manifest["manifest_path"] = str(manifest_path.resolve())
    return manifest


def submit_session(manifest_path: Path, force: bool) -> dict[str, Any]:
    manifest_path = manifest_path.resolve()
    manifest = read_manifest(manifest_path)
    workspace = resolve_workspace(manifest_path, manifest)

    working_path = resolve_manifest_member(
        manifest_path,
        manifest,
        "working_path",
        "working_relpath",
        "La copia de trabajo",
        qet_required=True,
        prefer_sidecar_qet=True,
    )
    incoming_path = resolve_manifest_member(
        manifest_path,
        manifest,
        "incoming_path",
        "incoming_relpath",
        "La entrega del usuario",
    )

    guarded_copy(working_path, incoming_path, force)
    submitted = manifest | {
        "status": "submitted",
        "submitted_at": now_iso(),
        "workspace_path": str(workspace),
        "working_path": str(working_path.resolve()),
        "incoming_path": str(incoming_path.resolve()),
        "working_relpath": relative_to_workspace(working_path, workspace),
        "incoming_relpath": relative_to_workspace(incoming_path, workspace),
        "working_sha256": file_sha256(working_path),
        "incoming_sha256": file_sha256(incoming_path),
    }
    incoming_manifest_path = manifest_path_for(incoming_path)
    write_json(incoming_manifest_path, submitted | {"manifest_path": str(incoming_manifest_path.resolve())})

    logs_dir = workspace / "06_LOGS"
    write_json(
        logs_dir / f"{timestamp()}_submit_{manifest['user_slug']}.json",
        submitted | {"manifest_path": str(incoming_manifest_path.resolve())},
    )
    submitted["manifest_path"] = str(incoming_manifest_path.resolve())
    return submitted


def resolve_baseline(
    manifest_records: list[tuple[Path, dict[str, Any]]], explicit_base: Path | None
) -> Path:
    if explicit_base is not None:
        base_path = require_qet_file(explicit_base, "La baseline")
    else:
        first_path, first_manifest = manifest_records[0]
        base_path = resolve_manifest_member(
            first_path,
            first_manifest,
            "baseline_path",
            "baseline_relpath",
            "La baseline",
            qet_required=True,
        )

    expected_hashes = {manifest["baseline_sha256"] for _, manifest in manifest_records}
    actual_hash = file_sha256(base_path)
    if actual_hash not in expected_hashes:
        raise QetToolError(
            f"La baseline indicada no coincide con los manifiestos: {base_path}"
        )
    if len(expected_hashes) > 1:
        raise QetToolError("Los manifiestos no parten de la misma baseline.")
    return base_path


def default_output_path(
    manifest_path: Path, manifest: dict[str, Any], base_path: Path
) -> Path:
    workspace = resolve_workspace(manifest_path, manifest)
    published_dir = workspace / "04_PUBLISHED"
    return published_dir / f"{timestamp()}_{base_path.stem}_published.qet"


def merge_session_manifests(
    manifest_paths: list[Path],
    base_path: Path | None,
    output_path: Path | None,
    force: bool,
    dry_run: bool,
    key_mode: str,
) -> dict[str, Any]:
    manifest_records = [(path.resolve(), read_manifest(path.resolve())) for path in manifest_paths]
    if not manifest_records:
        raise QetToolError("Se requiere al menos un manifiesto para publicar.")

    baseline_path = resolve_baseline(manifest_records, base_path)
    sources = [
        resolve_manifest_member(
            manifest_path,
            manifest,
            "incoming_path",
            "incoming_relpath",
            "La entrega del usuario",
            qet_required=True,
            prefer_sidecar_qet=True,
        )
        for manifest_path, manifest in manifest_records
    ]

    first_manifest_path, first_manifest = manifest_records[0]
    final_output = output_path or default_output_path(
        first_manifest_path, first_manifest, baseline_path
    )
    result = merge_projects(baseline_path, sources, final_output, key_mode, force, dry_run)
    result["manifests"] = [str(path) for path, _ in manifest_records]
    result["workspace"] = str(resolve_workspace(first_manifest_path, first_manifest))

    logs_dir = resolve_workspace(first_manifest_path, first_manifest) / "06_LOGS"
    write_json(logs_dir / f"{timestamp()}_merge.json", result)
    return result


def print_checkout_text(result: dict[str, Any]) -> None:
    print("Copia de trabajo colaborativa creada.")
    print(f"  usuario: {result['user']}")
    print(f"  maestro: {result['master_path']}")
    print(f"  baseline: {result['baseline_path']}")
    print(f"  copia local: {result['working_path']}")
    print(f"  entrega: {result['incoming_path']}")
    print(f"  manifiesto: {result['manifest_path']}")


def print_submit_text(result: dict[str, Any]) -> None:
    print("Entrega colaborativa preparada.")
    print(f"  usuario: {result['user']}")
    print(f"  copia local: {result['working_path']}")
    print(f"  entrega: {result['incoming_path']}")
    print(f"  manifiesto: {result['manifest_path']}")


def command_checkout(args: argparse.Namespace) -> int:
    result = checkout_session(Path(args.master), Path(args.workspace), args.user, args.force)
    if args.json:
        print(json.dumps(result, indent=2, ensure_ascii=False))
    else:
        print_checkout_text(result)
    return 0


def command_submit(args: argparse.Namespace) -> int:
    result = submit_session(Path(args.manifest), args.force)
    if args.json:
        print(json.dumps(result, indent=2, ensure_ascii=False))
    else:
        print_submit_text(result)
    return 0


def command_merge(args: argparse.Namespace) -> int:
    result = merge_session_manifests(
        [Path(path) for path in args.manifests],
        Path(args.base) if args.base else None,
        Path(args.output) if args.output else None,
        args.force,
        args.dry_run,
        args.key,
    )
    if args.json:
        print(json.dumps(result, indent=2, ensure_ascii=False))
    else:
        print_merge_text(result)
    return 0 if result["ok"] else 2


def build_parser() -> argparse.ArgumentParser:
    parser = SpanishArgumentParser(
        description="Gestiona copias colaborativas offline para proyectos .qet.",
        add_help=False,
    )
    parser.add_argument("-h", "--help", action="help", help="muestra esta ayuda y sale.")
    parser._positionals.title = "argumentos posicionales"
    parser._optionals.title = "opciones"
    subparsers = parser.add_subparsers(
        dest="command",
        required=True,
        title="comandos",
        parser_class=SpanishArgumentParser,
    )

    checkout = subparsers.add_parser(
        "checkout",
        help="Crea baseline, copia local y manifiesto desde un maestro .qet.",
        add_help=False,
    )
    checkout.add_argument("-h", "--help", action="help", help="muestra esta ayuda y sale.")
    checkout._positionals.title = "argumentos posicionales"
    checkout._optionals.title = "opciones"
    checkout.add_argument("--master", required=True, help="Archivo maestro .qet.")
    checkout.add_argument("--workspace", required=True, help="Carpeta colaborativa local o compartida.")
    checkout.add_argument("--user", required=True, help="Nombre del usuario/editor.")
    checkout.add_argument("--force", action="store_true", help="Sobrescribe salidas si ya existen.")
    checkout.add_argument("--json", action="store_true", help="Imprime JSON para automatizacion.")
    checkout.set_defaults(func=command_checkout)

    submit = subparsers.add_parser(
        "submit",
        help="Copia la version local editada a 03_INCOMING.",
        add_help=False,
    )
    submit.add_argument("-h", "--help", action="help", help="muestra esta ayuda y sale.")
    submit._positionals.title = "argumentos posicionales"
    submit._optionals.title = "opciones"
    submit.add_argument("--manifest", required=True, help="Manifiesto .jwqet.json de la copia local.")
    submit.add_argument("--force", action="store_true", help="Sobrescribe la entrega si ya existe.")
    submit.add_argument("--json", action="store_true", help="Imprime JSON para automatizacion.")
    submit.set_defaults(func=command_submit)

    merge = subparsers.add_parser(
        "merge",
        help="Fusiona entregas usando manifiestos colaborativos.",
        add_help=False,
    )
    merge.add_argument("-h", "--help", action="help", help="muestra esta ayuda y sale.")
    merge._positionals.title = "argumentos posicionales"
    merge._optionals.title = "opciones"
    merge.add_argument("--base", help="Baseline .qet explicita. Si se omite usa el manifiesto.")
    merge.add_argument("--output", help="Archivo .qet publicado. Si se omite usa 04_PUBLISHED.")
    merge.add_argument("--key", choices=("order", "position"), default="order", help="Estrategia de folio.")
    merge.add_argument("--force", action="store_true", help="Sobrescribe la salida si ya existe.")
    merge.add_argument("--dry-run", action="store_true", help="Analiza sin escribir salida.")
    merge.add_argument("--json", action="store_true", help="Imprime JSON para automatizacion.")
    merge.add_argument("manifests", nargs="+", help="Manifiestos .jwqet.json enviados.")
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
