#!/usr/bin/env python3
"""Unit tests for tools/file_brief.py, against a small synthetic .c source.

The synthetic file lives outside disasm/src, so pragma_targets (which only
scans the real tracked tree) will not know its owners; the tests confirm the
graceful text-scan fallback as well as the parsing itself.
"""

from __future__ import annotations

import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import file_brief  # noqa: E402

SYNTHETIC_SOURCE = """#include "global.h"

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/TESTFILE/func_80000010.s")

extern u8 D_80010000[];
extern s32 func_80000100(s32 arg0);
void func_80000000(s32 arg0, s32 idx) {
    s32 v = *(s32 *)(D_80010000 + idx * 112);
    gSPDisplayList(D_80010000, v);
    gDPSetFillColor(D_80010000, arg0);
    func_80000100(v);
}

extern u8 D_80010000[];
u8 func_80000080(s32 arg0) {
    return (u8)(arg0 * 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/TESTFILE/func_80000100.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/TESTFILE/func_80000200.s")
#endif
"""


class ParseFunctionsTests(unittest.TestCase):
    def test_finds_all_definitions_with_bodies(self) -> None:
        functions = file_brief.parse_functions(SYNTHETIC_SOURCE)
        names = [f.name for f in functions]
        self.assertEqual(names, ["func_80000000", "func_80000080"])

    def test_signature_and_return_type(self) -> None:
        functions = file_brief.parse_functions(SYNTHETIC_SOURCE)
        by_name = {f.name: f for f in functions}
        self.assertEqual(by_name["func_80000080"].ret.strip(), "u8")
        self.assertEqual(by_name["func_80000080"].params.strip(), "s32 arg0")
        self.assertIn("u8 func_80000080(s32 arg0)", by_name["func_80000080"].signature)

    def test_start_line_matches_source(self) -> None:
        functions = file_brief.parse_functions(SYNTHETIC_SOURCE)
        by_name = {f.name: f for f in functions}
        expected_line = SYNTHETIC_SOURCE[: SYNTHETIC_SOURCE.index("void func_80000000")].count("\n") + 1
        self.assertEqual(by_name["func_80000000"].start_line, expected_line)

    def test_body_spans_the_whole_definition(self) -> None:
        functions = file_brief.parse_functions(SYNTHETIC_SOURCE)
        by_name = {f.name: f for f in functions}
        body = by_name["func_80000000"].body
        self.assertTrue(body.startswith("void func_80000000"))
        self.assertTrue(body.rstrip().endswith("}"))
        self.assertIn("func_80000100(v);", body)


class OwnerLocalSectionTests(unittest.TestCase):
    def test_reports_leading_rodata_with_manual_layout_warning(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            source = root / "disasm/src/X.c"
            source.parent.mkdir(parents=True)
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/X/func_80000010.s")\n')
            asm = root / "disasm/asm/us/nonmatchings/X/func_80000010.s"
            asm.parent.mkdir(parents=True)
            asm.write_text(
                ".section .rodata\n"
                ".align 2\n"
                "dlabel D_80001000\n"
                "    /* 001000 80001000 */ .asciz \"BUFFER\"\n"
                ".section .text\n"
                "glabel func_80000010\n"
            )
            brief = file_brief.build_brief(source)

        sections = brief["owner_local_sections"]
        self.assertEqual(len(sections), 1)
        self.assertEqual(sections[0]["name"], ".rodata")
        self.assertEqual(sections[0]["alignment"], 4)
        self.assertEqual(sections[0]["rom_start"], "0x1000")
        self.assertEqual(sections[0]["symbols"], ["D_80001000"])
        rendered = file_brief.render_text(brief)
        self.assertIn("manual-layout-required", rendered)
        self.assertIn("D_80001000", rendered)


class ParsePragmasTests(unittest.TestCase):
    def test_finds_all_remaining_pragmas_in_order(self) -> None:
        pragmas = file_brief.parse_pragmas(SYNTHETIC_SOURCE)
        self.assertEqual(
            [function for _line, function in pragmas],
            ["func_80000010", "func_80000100", "func_80000200"],
        )

    def test_first_pragma_line_is_before_first_function(self) -> None:
        pragmas = file_brief.parse_pragmas(SYNTHETIC_SOURCE)
        functions = file_brief.parse_functions(SYNTHETIC_SOURCE)
        self.assertLess(pragmas[0][0], functions[0].start_line)


class ExternBlockTests(unittest.TestCase):
    def test_deduplicates_repeated_externs(self) -> None:
        externs = file_brief.extern_block(SYNTHETIC_SOURCE)
        self.assertEqual(externs.count("extern u8 D_80010000[];"), 1)
        self.assertIn("extern s32 func_80000100(s32 arg0);", externs)

    def test_preserves_first_seen_order(self) -> None:
        externs = file_brief.extern_block(SYNTHETIC_SOURCE)
        self.assertLess(
            externs.index("extern u8 D_80010000[];"),
            externs.index("extern s32 func_80000100(s32 arg0);"),
        )


class SymbolUsageTests(unittest.TestCase):
    def test_counts_distinct_bodies_not_total_occurrences(self) -> None:
        functions = file_brief.parse_functions(SYNTHETIC_SOURCE)
        usage = dict(file_brief.symbol_usage(functions))
        # D_80010000 appears 3 times textually in func_80000000's body alone,
        # but only in that one solved body -> count is 1, not 3.
        self.assertEqual(usage["D_80010000"], 1)
        self.assertEqual(usage["func_80000100"], 1)

    def test_excludes_self_reference(self) -> None:
        functions = file_brief.parse_functions(SYNTHETIC_SOURCE)
        usage = dict(file_brief.symbol_usage(functions))
        self.assertNotIn("func_80000000", usage)


class StrideCandidateTests(unittest.TestCase):
    def test_separates_record_from_pointer_strides(self) -> None:
        functions = file_brief.parse_functions(SYNTHETIC_SOURCE)
        record, pointer = file_brief.stride_candidates(functions)
        record_pairs = {(ident, literal) for ident, literal, _count in record}
        pointer_pairs = {(ident, literal) for ident, literal, _count in pointer}
        self.assertIn(("idx", "112"), record_pairs)
        self.assertIn(("arg0", "4"), pointer_pairs)
        self.assertNotIn(("idx", "112"), pointer_pairs)


class SdkMacroTests(unittest.TestCase):
    def test_finds_gsp_and_gdp_macros(self) -> None:
        functions = file_brief.parse_functions(SYNTHETIC_SOURCE)
        macros = dict(file_brief.sdk_macros(functions))
        self.assertEqual(macros["gSPDisplayList"], 1)
        self.assertEqual(macros["gDPSetFillColor"], 1)


class LaterDefinedFunctionsTests(unittest.TestCase):
    def test_functions_after_first_remaining_pragma_are_flagged(self) -> None:
        functions = file_brief.parse_functions(SYNTHETIC_SOURCE)
        pragmas = file_brief.parse_pragmas(SYNTHETIC_SOURCE)
        later = file_brief.later_defined_functions(functions, pragmas[0][0])
        names = [f.name for f in later]
        self.assertEqual(names, ["func_80000000", "func_80000080"])

    def test_no_remaining_pragmas_means_empty(self) -> None:
        functions = file_brief.parse_functions(SYNTHETIC_SOURCE)
        later = file_brief.later_defined_functions(functions, None)
        self.assertEqual(later, [])


class RemainingOwnersFallbackTests(unittest.TestCase):
    def test_falls_back_to_text_scan_for_an_untracked_file(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source_path = Path(tmp) / "synthetic.c"
            source_path.write_text(SYNTHETIC_SOURCE)
            pragmas = file_brief.parse_pragmas(SYNTHETIC_SOURCE)
            rows = file_brief.remaining_owners_table(source_path, pragmas)
        names = {row["function"] for row in rows}
        self.assertEqual(names, {"func_80000010", "func_80000100", "func_80000200"})
        self.assertTrue(all(row["instructions"] is None for row in rows))


class RemainingOwnerHistoryTests(unittest.TestCase):
    def test_retains_probe_history_from_pragma_targets(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source_path = Path(tmp) / "synthetic.c"
            source_path.write_text(SYNTHETIC_SOURCE)
            pragmas = file_brief.parse_pragmas(SYNTHETIC_SOURCE)
            target = {
                "function": "func_80000010",
                "instructions": 18,
                "family": "bounded_lookup",
                "prior_attempts": 7,
                "best_similarity": 0.9876,
                "best_raw_similarity": 0.8123,
                "best_mismatch_kind": "immediate_drift",
                "last_attempt": "2026-08-29T01:02:03+00:00",
                "hardness": "drift",
            }
            with mock.patch.object(
                file_brief.pragma_targets,
                "list_targets",
                return_value={"targets": [target]},
            ):
                rows = file_brief.remaining_owners_table(source_path, pragmas)

        row = rows[0]
        self.assertEqual(row["prior_attempts"], 7)
        self.assertEqual(row["best_similarity"], 0.9876)
        self.assertEqual(row["best_raw_similarity"], 0.8123)
        self.assertEqual(row["best_mismatch_kind"], "immediate_drift")
        self.assertEqual(row["last_attempt"], "2026-08-29T01:02:03+00:00")
        self.assertEqual(row["hardness"], "drift")


class BuildBriefAndRenderTests(unittest.TestCase):
    def test_build_brief_end_to_end_on_synthetic_file(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source_path = Path(tmp) / "synthetic.c"
            source_path.write_text(SYNTHETIC_SOURCE)
            brief = file_brief.build_brief(source_path)

        self.assertEqual(brief["counts"]["solved"], 2)
        self.assertEqual(brief["counts"]["remaining"], 3)
        self.assertEqual(len(brief["solved_functions"]), 2)
        self.assertTrue(any(row["function"] == "func_80000010" for row in brief["remaining_owners"]))

    def test_render_text_includes_every_section_header(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source_path = Path(tmp) / "synthetic.c"
            source_path.write_text(SYNTHETIC_SOURCE)
            brief = file_brief.build_brief(source_path)
        text = file_brief.render_text(brief)
        for heading in (
            "already-decompiled functions",
            "extern/prototype block",
            "func_/D_ symbols referenced",
            "record-stride-like constants",
            "SDK macros already used",
            "owner-local rodata sections",
            "functions defined later in the file",
            "remaining owners",
        ):
            self.assertIn(heading, text)

    def test_render_text_includes_owner_probe_history(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source_path = Path(tmp) / "synthetic.c"
            source_path.write_text(SYNTHETIC_SOURCE)
            brief = file_brief.build_brief(source_path)
        brief["remaining_owners"][0].update(
            {
                "prior_attempts": 7,
                "best_similarity": 0.9876,
                "best_raw_similarity": 0.8123,
                "best_mismatch_kind": "immediate_drift",
                "last_attempt": "2026-08-29T01:02:03+00:00",
                "hardness": "drift",
            }
        )

        text = file_brief.render_text(brief)
        self.assertIn("attempts=7 best=0.9876 raw=0.8123", text)
        self.assertIn("mismatch=immediate_drift", text)
        self.assertIn("last=2026-08-29T01:02:03+00:00 hardness=drift", text)

    def test_main_writes_json_when_requested(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source_path = Path(tmp) / "synthetic.c"
            source_path.write_text(SYNTHETIC_SOURCE)
            json_path = Path(tmp) / "out.json"
            exit_code = file_brief.main([str(source_path), "--json", str(json_path)])
            self.assertEqual(exit_code, 0)
            self.assertTrue(json_path.exists())

    def test_main_reports_missing_file(self) -> None:
        exit_code = file_brief.main(["/no/such/file.c"])
        self.assertEqual(exit_code, 2)


if __name__ == "__main__":
    unittest.main()
