#!/usr/bin/env python3
"""Smoke tests for tools/qet_collab_session.py."""

from __future__ import annotations

import importlib.util
import json
import sys
import tempfile
import unittest
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[1]
TOOL_PATH = REPO_ROOT / "tools" / "qet_collab_session.py"


def load_tool_module():
    spec = importlib.util.spec_from_file_location("qet_collab_session", TOOL_PATH)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"Could not load {TOOL_PATH}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


BASE_QET = """<project title="Base" version="0.200.1">
    <diagram order="1"><shapes><shape type="Rectangle" /></shapes></diagram>
    <diagram order="2"><shapes><shape type="Rectangle" /></shapes></diagram>
</project>
"""

FOLIO_1_QET = """<project title="Base" version="0.200.1">
    <diagram order="1"><elements><element uuid="{a}" type="embed://import/a.elmt" /></elements></diagram>
    <diagram order="2"><shapes><shape type="Rectangle" /></shapes></diagram>
    <collection><category name="import"><element name="a.elmt"><definition /></element></category></collection>
</project>
"""

FOLIO_2_QET = """<project title="Base" version="0.200.1">
    <diagram order="1"><shapes><shape type="Rectangle" /></shapes></diagram>
    <diagram order="2"><elements><element uuid="{b}" type="embed://import/b.elmt" /></elements></diagram>
    <collection><category name="import"><element name="b.elmt"><definition /></element></category></collection>
</project>
"""


class QetCollabSessionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tool = load_tool_module()

    def write_file(self, root: Path, name: str, content: str) -> Path:
        path = root / name
        path.write_text(content, encoding="utf-8")
        return path

    def test_checkout_creates_working_copy_and_manifest(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            master = self.write_file(root, "Proyecto.qet", BASE_QET)
            workspace = root / "JW_QET_COLLAB"

            result = self.tool.checkout_session(master, workspace, "Juan Perez", force=False)
            manifest_path = Path(result["manifest_path"])

            self.assertTrue(Path(result["baseline_path"]).exists())
            self.assertTrue(Path(result["working_path"]).exists())
            self.assertTrue(manifest_path.exists())
            self.assertEqual(json.loads(manifest_path.read_text(encoding="utf-8"))["user_slug"], "Juan_Perez")

    def test_submit_copies_working_file_to_incoming(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            master = self.write_file(root, "Proyecto.qet", BASE_QET)
            workspace = root / "JW_QET_COLLAB"
            checkout = self.tool.checkout_session(master, workspace, "usuario_1", force=False)
            working_path = Path(checkout["working_path"])
            working_path.write_text(FOLIO_1_QET, encoding="utf-8")

            result = self.tool.submit_session(Path(checkout["manifest_path"]), force=False)

            self.assertEqual(Path(result["incoming_path"]).read_text(encoding="utf-8"), FOLIO_1_QET)
            self.assertTrue(Path(result["manifest_path"]).exists())
            self.assertEqual(result["status"], "submitted")

    def test_merge_session_manifests_publishes_different_folios(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            master = self.write_file(root, "Proyecto.qet", BASE_QET)
            workspace = root / "JW_QET_COLLAB"

            checkout_1 = self.tool.checkout_session(master, workspace, "usuario_1", force=False)
            checkout_2 = self.tool.checkout_session(master, workspace, "usuario_2", force=False)
            Path(checkout_1["working_path"]).write_text(FOLIO_1_QET, encoding="utf-8")
            Path(checkout_2["working_path"]).write_text(FOLIO_2_QET, encoding="utf-8")
            submit_1 = self.tool.submit_session(Path(checkout_1["manifest_path"]), force=False)
            submit_2 = self.tool.submit_session(Path(checkout_2["manifest_path"]), force=False)
            output = workspace / "04_PUBLISHED" / "Publicado.qet"

            result = self.tool.merge_session_manifests(
                [Path(submit_1["manifest_path"]), Path(submit_2["manifest_path"])],
                None,
                output,
                force=False,
                dry_run=False,
                key_mode="order",
            )

            self.assertTrue(result["ok"])
            self.assertEqual(result["changed_diagrams"], ["order:1", "order:2"])
            self.assertTrue(output.exists())

    def test_help_header_is_spanish(self):
        help_text = self.tool.build_parser().format_help()

        self.assertIn("uso:", help_text)
        self.assertNotIn("usage:", help_text)


if __name__ == "__main__":
    unittest.main()
