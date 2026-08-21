#!/usr/bin/env python3
"""Compatibility entry point for JW QET collaboration workspace v2.

The original qet_collab_session module remains the stable session engine. This
wrapper extends workspace discovery so manifests stored below .jwqet/incoming
remain portable between PCs whose shared Drive uses different drive letters,
and opts workflow v2 into the conservative appended-folio merge extension.
"""

from __future__ import annotations

from pathlib import Path

import qet_collab_session as core
from qet_collab_new_folios import merge_projects as merge_projects_v2


def infer_workspace_v2(manifest_path: Path) -> Path | None:
    manifest_path = manifest_path.resolve()
    for parent in manifest_path.parents:
        if parent.name in {"02_WORKING", "03_INCOMING"}:
            return parent.parent
        if parent.name == ".jwqet":
            return parent.parent
    return None


core.infer_workspace_from_manifest = infer_workspace_v2
core.merge_projects = merge_projects_v2


if __name__ == "__main__":
    raise SystemExit(core.main())
