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


def checkout_session(master_path: Path, workspace_path: Path, user: str, force: bool) -> dict[str, Any]:
    master_path = require_qet_file(master_path, "El maestro")
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
        "workspace_path": str(workspace_path.resolve()),
        "baseline_path": str(baseline_path.resolve()),
        "working_path": str(working_path.resolve()),
        "incoming_path": str(incoming_path.resolve()),
        "published_dir": str(published_dir.resolve()),
        "logs_dir": str(logs_dir.resolve()),
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
    manifest = read_manifest(manifest_path)
    working_path = require_qet_file(Path(manifest["working_path"]), "La copia de trabajo")
    incoming_path = Path(manifest["incoming_path"])

    guarded_copy(working_path, incoming_path, force)
    submitted = manifest | {
        "status": "submitted",
        "submitted_at": now_iso(),
        "incoming_path": str(incoming_path.resolve()),
        "working_sha256": file_sha256(working_path),
        "incoming_sha256": file_sha256(incoming_path),
    }
    incoming_manifest_path = manifest_path_for(incoming_path)
    write_json(incoming_manifest_path, submitted | {"manifest_path": str(incoming_manifest_path.resolve())})

    logs_dir = Path(manifest["logs_dir"])
    write_json(
        logs_dir / f"{timestamp()}_submit_{manifest['user_slug']}.json",
        submitted | {"manifest_path": str(incoming_manifest_path.resolve())},
    )
    submitted["manifest_path"] = str(incoming_manifest_path.resolve())
    return submitted


def resolve_baseline(manifests: list[dict[str, Any]], explicit_base: Path | None) -> Path:
    if explicit_base is not None:
        base_path = require_qet_file(explicit_base, "La baseline")
    else:
        base_path = require_qet_file(Path(manifests[0]["baseline_path"]), "La baseline")

    expected_hashes = {manifest["baseline_sha256"] for manifest in manifests}
    actual_hash = file_sha256(base_path)
    if actual_hash not in expected_hashes:
        raise QetToolError(
            f"La baseline indicada no coincide con los manifiestos: {base_path}"
        )
    if len(expected_hashes) > 1:
        raise QetToolError("Los manifiestos no parten de la misma baseline.")
    return base_path


def default_output_path(manifests: list[dict[str, Any]], base_path: Path) -> Path:
    published_dir = Path(manifests[0]["published_dir"])
    return published_dir / f"{timestamp()}_{base_path.stem}_published.qet"


def merge_session_manifests(
    manifest_paths: list[Path],
    base_path: Path | None,
    output_path: Path | None,
    force: bool,
    dry_run: bool,
    key_mode: str,
) -> dict[str, Any]:
    manifests = [read_manifest(path) for path in manifest_paths]
    if not manifests:
        raise QetToolError("Se requiere al menos un manifiesto para publicar.")

    baseline_path = resolve_baseline(manifests, base_path)
    sources = [
        require_qet_file(Path(manifest["incoming_path"]), "La entrega del usuario")
        for manifest in manifests
    ]
    final_output = output_path or default_output_path(manifests, baseline_path)
    result = merge_projects(baseline_path, sources, final_output, key_mode, force, dry_run)
    result["manifests"] = [str(path) for path in manifest_paths]

    logs_dir = Path(manifests[0]["logs_dir"])
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
