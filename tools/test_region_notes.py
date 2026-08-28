#!/usr/bin/env python3
"""Unit tests for tools/region_notes.py, and for tools/file_brief.py's use
of it, against a synthetic repository tree under a tempdir.

Every test patches region_notes.REPO_ROOT / SRC_ROOT / REGIONS_ROOT to a
tempdir so nothing ever reads or writes the real docs/regions/ tree.
file_brief.py imports region_notes as the same module object, so the patch
also governs the region-notes calls file_brief makes.
"""

from __future__ import annotations

import io
import json
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import region_notes  # noqa: E402
import file_brief  # noqa: E402

SYNTHETIC_SOURCE = """#include "global.h"

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/TESTFILE/func_80000010.s")

void func_80000000(s32 arg0) {
    return;
}
#endif
"""


class RegionNotesTestCase(unittest.TestCase):
    """Base class: points region_notes' module-level roots at a tempdir."""

    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self.tmp_path = Path(self._tmp.name).resolve()

        self._orig_repo_root = region_notes.REPO_ROOT
        self._orig_src_root = region_notes.SRC_ROOT
        self._orig_regions_root = region_notes.REGIONS_ROOT
        self.addCleanup(self._restore_roots)

        region_notes.REPO_ROOT = self.tmp_path
        region_notes.SRC_ROOT = self.tmp_path / "disasm" / "src"
        region_notes.REGIONS_ROOT = self.tmp_path / "docs" / "regions"

        (self.tmp_path / "disasm" / "src" / "fragments" / "79").mkdir(parents=True)

    def _restore_roots(self) -> None:
        region_notes.REPO_ROOT = self._orig_repo_root
        region_notes.SRC_ROOT = self._orig_src_root
        region_notes.REGIONS_ROOT = self._orig_regions_root

    def source(self, relative: str) -> Path:
        return region_notes.SRC_ROOT / relative


class PathForTests(RegionNotesTestCase):
    def test_top_level_file_maps_under_regions_root(self) -> None:
        path = region_notes.path_for(self.source("4AC10.c"))
        self.assertEqual(path, region_notes.REGIONS_ROOT / "4AC10.md")

    def test_fragment_file_preserves_subdirectory(self) -> None:
        path = region_notes.path_for(self.source("fragments/79/fragment79_393CA0.c"))
        self.assertEqual(
            path,
            region_notes.REGIONS_ROOT / "fragments" / "79" / "fragment79_393CA0.md",
        )

    def test_relative_and_absolute_inputs_agree(self) -> None:
        absolute = self.source("fragments/79/fragment79_393CA0.c")
        relative = "disasm/src/fragments/79/fragment79_393CA0.c"
        # relative is resolved against region_notes.REPO_ROOT (the tmp root)
        self.assertEqual(region_notes.path_for(absolute), region_notes.path_for(relative))

    def test_relative_and_absolute_agree_for_top_level_file(self) -> None:
        absolute = self.source("4AC10.c")
        relative = "disasm/src/4AC10.c"
        self.assertEqual(region_notes.path_for(absolute), region_notes.path_for(relative))

    def test_directory_path_for_fragment_file(self) -> None:
        dir_path = region_notes.directory_path_for(self.source("fragments/79/fragment79_393CA0.c"))
        self.assertEqual(dir_path, region_notes.REGIONS_ROOT / "fragments" / "79.md")

    def test_directory_path_for_top_level_file_is_none(self) -> None:
        dir_path = region_notes.directory_path_for(self.source("4AC10.c"))
        self.assertIsNone(dir_path)

    def test_source_outside_the_repo_falls_back_to_filename(self) -> None:
        with tempfile.TemporaryDirectory() as other:
            outside = Path(other) / "synthetic.c"
            outside.write_text(SYNTHETIC_SOURCE)
            path = region_notes.path_for(outside)
        self.assertEqual(path, region_notes.REGIONS_ROOT / "synthetic.md")


class LoadTests(RegionNotesTestCase):
    def test_load_is_empty_when_neither_file_exists(self) -> None:
        self.assertEqual(region_notes.load(self.source("4AC10.c")), "")

    def test_load_concatenates_directory_then_file_notes(self) -> None:
        source = self.source("fragments/79/fragment79_393CA0.c")
        region_notes.append(source, "file-level fact", heading="File fact")
        dir_path = region_notes.directory_path_for(source)
        dir_path.write_text("# fragments/79 overlay\n\nshared fact\n", encoding="utf-8")

        text = region_notes.load(source)

        self.assertLess(text.index("shared fact"), text.index("file-level fact"))

    def test_load_headings_name_their_origin(self) -> None:
        source = self.source("fragments/79/fragment79_393CA0.c")
        region_notes.append(source, "file-level fact", heading="File fact")
        dir_path = region_notes.directory_path_for(source)
        dir_path.write_text("shared fact\n", encoding="utf-8")

        text = region_notes.load(source)

        self.assertIn("fragments/79.md", text)
        self.assertIn("fragments/79/fragment79_393CA0.md", text)

    def test_load_skips_a_directory_file_that_exists_but_is_empty(self) -> None:
        source = self.source("fragments/79/fragment79_393CA0.c")
        dir_path = region_notes.directory_path_for(source)
        dir_path.parent.mkdir(parents=True, exist_ok=True)
        dir_path.write_text("   \n", encoding="utf-8")

        self.assertEqual(region_notes.load(source), "")


class AppendTests(RegionNotesTestCase):
    def test_append_creates_file_with_standard_header(self) -> None:
        source = self.source("4AC10.c")
        path = region_notes.append(source, "first fact")

        self.assertTrue(path.exists())
        content = path.read_text(encoding="utf-8")
        self.assertIn("Region notes", content)
        self.assertIn("first fact", content)

    def test_append_twice_preserves_earlier_content(self) -> None:
        source = self.source("4AC10.c")
        region_notes.append(source, "first fact", heading="First")
        region_notes.append(source, "second fact", heading="Second")

        content = region_notes.path_for(source).read_text(encoding="utf-8")

        self.assertIn("first fact", content)
        self.assertIn("second fact", content)
        self.assertLess(content.index("first fact"), content.index("second fact"))

    def test_append_with_heading_uses_it_in_the_section_title(self) -> None:
        source = self.source("4AC10.c")
        region_notes.append(source, "fact", heading="RDP texture loads")

        content = region_notes.path_for(source).read_text(encoding="utf-8")

        self.assertIn("## RDP texture loads", content)

    def test_append_without_heading_uses_a_dated_section(self) -> None:
        source = self.source("4AC10.c")
        import datetime

        region_notes.append(source, "fact")

        content = region_notes.path_for(source).read_text(encoding="utf-8")
        today = datetime.date.today().isoformat()
        self.assertIn(f"## {today}", content)

    def test_append_creates_parent_directories_for_fragments(self) -> None:
        source = self.source("fragments/79/fragment79_393CA0.c")
        path = region_notes.append(source, "fact")
        self.assertTrue(path.exists())
        self.assertEqual(path.parent, region_notes.REGIONS_ROOT / "fragments" / "79")


class ListRegionsTests(RegionNotesTestCase):
    def test_empty_when_no_regions_directory(self) -> None:
        self.assertEqual(region_notes.list_regions(), [])

    def test_lists_every_created_notes_file_sorted(self) -> None:
        region_notes.append(self.source("4AC10.c"), "a")
        region_notes.append(self.source("fragments/79/fragment79_393CA0.c"), "b")

        regions = region_notes.list_regions()

        self.assertEqual(regions, sorted(regions))
        self.assertIn(region_notes.REGIONS_ROOT / "4AC10.md", regions)
        self.assertIn(
            region_notes.REGIONS_ROOT / "fragments" / "79" / "fragment79_393CA0.md",
            regions,
        )


class CLITests(RegionNotesTestCase):
    def _run(self, argv: list[str]) -> str:
        buf = io.StringIO()
        with redirect_stdout(buf):
            exit_code = region_notes.main(argv)
        self.assertEqual(exit_code, 0)
        return buf.getvalue()

    def test_show_reports_missing_notes_with_the_path(self) -> None:
        source = str(self.source("4AC10.c"))
        output = self._run(["show", source])
        self.assertIn("no region notes", output)
        self.assertIn("4AC10.md", output)

    def test_append_then_show_round_trips(self) -> None:
        source = str(self.source("4AC10.c"))
        self._run(["append", source, "--text", "a proven spelling", "--heading", "Spelling"])
        output = self._run(["show", source])
        self.assertIn("a proven spelling", output)
        self.assertIn("Spelling", output)

    def test_list_prints_created_files(self) -> None:
        source = str(self.source("4AC10.c"))
        self._run(["append", source, "--text", "x"])
        output = self._run(["list"])
        self.assertIn("4AC10.md", output)


class FileBriefIntegrationTests(RegionNotesTestCase):
    def test_text_output_shows_notes_when_present(self) -> None:
        source_path = self.source("4AC10.c")
        source_path.write_text(SYNTHETIC_SOURCE)
        region_notes.append(source_path, "a proven spelling", heading="Spelling")

        brief = file_brief.build_brief(source_path)
        text = file_brief.render_text(brief)

        self.assertIn("== region notes ==", text)
        self.assertIn("a proven spelling", text)
        self.assertLess(text.index("region notes"), text.index("file brief:"))

    def test_text_output_names_where_notes_would_go_when_absent(self) -> None:
        source_path = self.source("4AC10.c")
        source_path.write_text(SYNTHETIC_SOURCE)

        brief = file_brief.build_brief(source_path)
        text = file_brief.render_text(brief)

        self.assertIn("no region notes yet", text)
        self.assertIn("4AC10.md", text)

    def test_json_includes_region_notes_field(self) -> None:
        source_path = self.source("4AC10.c")
        source_path.write_text(SYNTHETIC_SOURCE)
        region_notes.append(source_path, "a proven spelling", heading="Spelling")

        with tempfile.TemporaryDirectory() as out_dir:
            json_path = Path(out_dir) / "out.json"
            exit_code = file_brief.main([str(source_path), "--json", str(json_path)])
            self.assertEqual(exit_code, 0)
            data = json.loads(json_path.read_text(encoding="utf-8"))

        self.assertIn("region_notes", data)
        self.assertIn("a proven spelling", data["region_notes"])

    def test_json_region_notes_is_empty_string_when_absent(self) -> None:
        source_path = self.source("4AC10.c")
        source_path.write_text(SYNTHETIC_SOURCE)

        with tempfile.TemporaryDirectory() as out_dir:
            json_path = Path(out_dir) / "out.json"
            file_brief.main([str(source_path), "--json", str(json_path)])
            data = json.loads(json_path.read_text(encoding="utf-8"))

        self.assertEqual(data["region_notes"], "")


if __name__ == "__main__":
    unittest.main()
