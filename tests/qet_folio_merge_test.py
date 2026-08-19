#!/usr/bin/env python3
"""Smoke tests for tools/qet_folio_merge.py."""

from __future__ import annotations

import importlib.util
import sys
import tempfile
import unittest
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[1]
TOOL_PATH = REPO_ROOT / "tools" / "qet_folio_merge.py"


def load_tool_module():
    spec = importlib.util.spec_from_file_location("qet_folio_merge", TOOL_PATH)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"Could not load {TOOL_PATH}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


BASE_QET = """<project title="Base" version="0.200.1">
    <properties savedfilename="base.qet" />
    <diagram order="1"><shapes><shape type="Rectangle" /></shapes></diagram>
    <diagram order="2"><shapes><shape type="Rectangle" /></shapes></diagram>
    <collection><category name="import"><names><name lang="en">Imported</name></names></category></collection>
</project>
"""

FOLIO_1_QET = """<project title="Base" version="0.200.1">
    <properties savedfilename="folio_1.qet" />
    <diagram order="1"><elements><element uuid="{a}" type="embed://import/a.elmt" /></elements></diagram>
    <diagram order="2"><shapes><shape type="Rectangle" /></shapes></diagram>
    <collection><category name="import"><element name="a.elmt"><definition /></element></category></collection>
</project>
"""

FOLIO_2_QET = """<project title="Base" version="0.200.1">
    <properties savedfilename="folio_2.qet" />
    <diagram order="1"><shapes><shape type="Rectangle" /></shapes></diagram>
    <diagram order="2"><elements><element uuid="{b}" type="embed://import/b.elmt" /></elements></diagram>
    <collection><category name="import"><element name="b.elmt"><definition /></element></category></collection>
</project>
"""

EMPTY_ELEMENT_INFOS_QET = """<project title="Base" version="0.200.1">
    <diagram order="1">
        <elements>
            <element uuid="{a}" type="embed://import/a.elmt">
                <elementInformations />
                <dynamic_texts />
            </element>
        </elements>
    </diagram>
</project>
"""

WITHOUT_ELEMENT_INFOS_QET = """<project title="Base" version="0.200.1">
    <diagram order="1">
        <elements>
            <element uuid="{a}" type="embed://import/a.elmt">
                <dynamic_texts />
            </element>
        </elements>
    </diagram>
</project>
"""

FOLIO_1_CONFLICT_QET = """<project title="Base" version="0.200.1">
    <properties savedfilename="folio_1_conflict.qet" />
    <diagram order="1"><elements><element uuid="{c}" type="embed://import/c.elmt" /></elements></diagram>
    <diagram order="2"><shapes><shape type="Rectangle" /></shapes></diagram>
    <collection><category name="import"><element name="c.elmt"><definition /></element></category></collection>
</project>
"""

CONDUCTOR_QET = """<project title="Conductor" version="0.200.1">
    <diagram order="1">
        <elements>
            <element uuid="{11111111-1111-1111-1111-111111111111}" type="embed://import/a.elmt" />
            <element uuid="{22222222-2222-2222-2222-222222222222}" type="embed://import/a.elmt" />
        </elements>
        <conductors>
            <conductor
                element1="{11111111-1111-1111-1111-111111111111}"
                terminal1="{aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa}"
                terminalname1="L"
                element2="{22222222-2222-2222-2222-222222222222}"
                terminal2="{bbbbbbbb-bbbb-bbbb-bbbb-bbbbbbbbbbbb}"
                terminalname2="N"
                type="multi" />
        </conductors>
    </diagram>
    <collection>
        <category name="import">
            <element name="a.elmt">
                <definition>
                    <description>
                        <terminal uuid="{aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa}" name="L" />
                        <terminal uuid="{bbbbbbbb-bbbb-bbbb-bbbb-bbbbbbbbbbbb}" name="N" />
                    </description>
                </definition>
            </element>
        </category>
    </collection>
</project>
"""

BROKEN_CONDUCTOR_QET = """<project title="Conductor" version="0.200.1">
    <diagram order="1">
        <elements>
            <element uuid="{11111111-1111-1111-1111-111111111111}" type="embed://import/a.elmt" />
            <element uuid="{22222222-2222-2222-2222-222222222222}" type="embed://import/a.elmt" />
        </elements>
        <conductors>
            <conductor
                element1="{11111111-1111-1111-1111-111111111111}"
                terminal1="{aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa}"
                terminalname1="L"
                element2="{22222222-2222-2222-2222-222222222222}"
                terminal2="{cccccccc-cccc-cccc-cccc-cccccccccccc}"
                terminalname2="N"
                type="multi" />
        </conductors>
    </diagram>
    <collection>
        <category name="import">
            <element name="a.elmt">
                <definition>
                    <description>
                        <terminal uuid="{aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa}" name="L" />
                        <terminal uuid="{bbbbbbbb-bbbb-bbbb-bbbb-bbbbbbbbbbbb}" name="N" />
                    </description>
                </definition>
            </element>
        </category>
    </collection>
</project>
"""


class QetFolioMergeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tool = load_tool_module()

    def write_file(self, root: Path, name: str, content: str) -> Path:
        path = root / name
        path.write_text(content, encoding="utf-8")
        return path

    def test_merges_different_folios_and_embedded_collection(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            base = self.write_file(root, "base.qet", BASE_QET)
            folio_1 = self.write_file(root, "folio_1.qet", FOLIO_1_QET)
            folio_2 = self.write_file(root, "folio_2.qet", FOLIO_2_QET)
            output = root / "merged.qet"

            result = self.tool.merge_projects(
                base,
                [folio_1, folio_2],
                output,
                "order",
                force=False,
                dry_run=False,
            )

            self.assertTrue(result["ok"])
            self.assertEqual(result["changed_diagrams"], ["order:1", "order:2"])
            self.assertEqual(result["collection_elements"], ["a.elmt", "b.elmt"])

            merged = self.tool.parse_qet(output).getroot()
            diagrams = self.tool.diagram_map(merged, "order")
            self.assertEqual(self.tool.child_count(diagrams["order:1"].node, "elements", "element"), 1)
            self.assertEqual(self.tool.child_count(diagrams["order:2"].node, "elements", "element"), 1)

    def test_rejects_conflicting_change_on_same_folio(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            base = self.write_file(root, "base.qet", BASE_QET)
            folio_1 = self.write_file(root, "folio_1.qet", FOLIO_1_QET)
            conflict = self.write_file(root, "folio_1_conflict.qet", FOLIO_1_CONFLICT_QET)
            output = root / "merged.qet"

            result = self.tool.merge_projects(
                base,
                [folio_1, conflict],
                output,
                "order",
                force=False,
                dry_run=False,
            )

            self.assertFalse(result["ok"])
            self.assertFalse(output.exists())
            self.assertIn("folio order:1 se modifico de forma distinta", result["conflicts"][0])

    def test_help_header_is_spanish(self):
        help_text = self.tool.build_parser().format_help()

        self.assertIn("uso:", help_text)
        self.assertNotIn("usage:", help_text)

    def test_empty_element_informations_is_not_semantic(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            with_infos = self.write_file(root, "with_infos.qet", EMPTY_ELEMENT_INFOS_QET)
            without_infos = self.write_file(root, "without_infos.qet", WITHOUT_ELEMENT_INFOS_QET)

            with_diagram = self.tool.diagram_map(self.tool.parse_qet(with_infos).getroot(), "order")[
                "order:1"
            ].node
            without_diagram = self.tool.diagram_map(
                self.tool.parse_qet(without_infos).getroot(),
                "order",
            )["order:1"].node

            self.assertEqual(
                self.tool.canonical_signature(with_diagram),
                self.tool.canonical_signature(without_diagram),
            )

    def test_text_line_endings_are_not_semantic(self):
        left = self.tool.ET.fromstring("<informations>uno\n\ndos</informations>")
        right = self.tool.ET.fromstring("<informations>uno\r\r\ndos</informations>")

        self.assertEqual(
            self.tool.canonical_signature(left),
            self.tool.canonical_signature(right),
        )

    def test_conductor_endpoints_are_validated_against_collection(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            path = self.write_file(root, "conductor.qet", CONDUCTOR_QET)

            project = self.tool.analyze_project(path, "order")
            diagram = project["diagrams"][0]
            conductor = diagram["conductors"][0]

            self.assertTrue(conductor["valid"])
            self.assertEqual(diagram["conductor_warnings"], [])
            self.assertTrue(all(endpoint["terminal_ok"] for endpoint in conductor["endpoints"]))

    def test_invalid_conductor_terminal_is_reported(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            path = self.write_file(root, "broken_conductor.qet", BROKEN_CONDUCTOR_QET)

            project = self.tool.analyze_project(path, "order")
            diagram = project["diagrams"][0]

            self.assertFalse(diagram["conductors"][0]["valid"])
            self.assertTrue(
                any("terminal2 no existe" in warning for warning in diagram["conductor_warnings"])
            )


if __name__ == "__main__":
    unittest.main()
