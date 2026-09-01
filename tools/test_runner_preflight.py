"""Tests for the candidate-batch preflight and declaration synthesis.

These cover the three waste classes measured over a two-hour fleet window
(1205 attempts, 6 accepts): candidate bodies re-sent verbatim (26% of
attempts), batches sent for owners the runner had already flagged futile
(51%), and attempts lost to declarations the runner could have synthesized
(13%).
"""

import os
import unittest
from pathlib import Path
from unittest import mock

import try_pragma_compare as runner


_SOURCE = """
#include "common.h"

extern OSMesgQueue D_800CDA10;
extern u8 D_800CD9D0[];

void func_80001000(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/x/func_80002000.s")
"""


class DataDeclarationScanTests(unittest.TestCase):
    def test_finds_plain_extern(self) -> None:
        self.assertEqual(
            runner.scan_source_for_data_declaration(_SOURCE, "D_800CDA10"),
            "extern OSMesgQueue D_800CDA10",
        )

    def test_keeps_array_extent(self) -> None:
        self.assertEqual(
            runner.scan_source_for_data_declaration(_SOURCE, "D_800CD9D0"),
            "extern u8 D_800CD9D0[]",
        )

    def test_unknown_symbol_is_not_guessed(self) -> None:
        self.assertIsNone(runner.scan_source_for_data_declaration(_SOURCE, "D_DEADBEEF"))

    def test_definition_with_initializer(self) -> None:
        text = "s32 D_80001234[4] = {1, 2, 3, 4};"
        self.assertEqual(
            runner.scan_source_for_data_declaration(text, "D_80001234"),
            "extern s32 D_80001234[4]",
        )


class DeclarationIndexTests(unittest.TestCase):
    def _repo(self, files: dict[str, str], tmp: Path) -> Path:
        src = tmp / "disasm" / "src"
        src.mkdir(parents=True)
        for name, text in files.items():
            (src / name).write_text(text)
        return tmp

    def setUp(self) -> None:
        runner._DECLARATION_INDEX_CACHE.clear()
        runner._DECLARATION_FILE_CACHE.clear()

    def test_indexes_cross_file_symbols(self) -> None:
        import tempfile

        with tempfile.TemporaryDirectory() as raw:
            repo = self._repo({
                "a.c": "extern OSMesgQueue D_800CDA10;\nvoid func_80001000(s32 arg0) {}\n",
                "b.c": "void func_80002000(void) { func_80001000(1); }\n",
            }, Path(raw))
            index = runner._declaration_index(repo)
        self.assertEqual(index["D_800CDA10"], "extern OSMesgQueue D_800CDA10;")
        self.assertIn("func_80001000", index)

    def test_conflicting_spellings_are_dropped_not_guessed(self) -> None:
        import tempfile

        with tempfile.TemporaryDirectory() as raw:
            repo = self._repo({
                "a.c": "extern s32 D_80009999;\n",
                "b.c": "extern f32 D_80009999;\n",
            }, Path(raw))
            index = runner._declaration_index(repo)
        self.assertNotIn("D_80009999", index)


class CandidateIdentityTests(unittest.TestCase):
    def test_whitespace_and_comments_do_not_change_identity(self) -> None:
        a = "void f(void) { return; }"
        b = "void f(void) {\n    /* note */ return;  // trailing\n}"
        self.assertEqual(runner._candidate_identity(a), runner._candidate_identity(b))

    def test_real_change_changes_identity(self) -> None:
        a = "void f(void) { return; }"
        b = "void f(void) { g(); return; }"
        self.assertNotEqual(runner._candidate_identity(a), runner._candidate_identity(b))


class DuplicateCandidateTests(unittest.TestCase):
    def test_rejects_body_already_rejected(self) -> None:
        history = {
            "func_1": [{
                "candidate": "void func_1(void) { return; }",
                "declarations": "",
                "label": "lookup:guard",
                "status": "probe_rejected",
                "similarity_score": 0.5,
                "timestamp": "2026-09-01T07:00:00Z",
            }]
        }
        errors = runner._duplicate_candidate_errors(
            [("func_1", "void func_1(void) {\n  return;\n}")], history
        )
        self.assertEqual(len(errors), 1)
        self.assertIn("already", errors[0])
        self.assertIn("lookup:guard", errors[0])

    def test_allows_resend_of_a_body_that_matched(self) -> None:
        """The discover-then-gate round trip must keep working.

        Replaying the measured window with any prior status blocking
        destroyed five of six accepts, all of them a ``probe_match`` body
        re-sent with ``gate: true``.
        """
        history = {
            "func_1": [{
                "candidate": "void func_1(void) { return; }",
                "declarations": "",
                "status": "probe_match",
            }]
        }
        self.assertEqual(
            runner._duplicate_candidate_errors(
                [("func_1", "void func_1(void) { return; }")], history
            ),
            [],
        )

    def test_allows_resend_under_different_declarations(self) -> None:
        """``func_8822B63C``: same body, grown externs, compile_failed -> accepted."""
        history = {
            "func_1": [{
                "candidate": "void func_1(void) { g(&D_88234910); }",
                "declarations": "extern s32 x;",
                "status": "probe_rejected",
            }]
        }
        self.assertEqual(
            runner._duplicate_candidate_errors(
                [("func_1", "void func_1(void) { g(&D_88234910); }")],
                history,
                "extern s32 x;\nextern u8 D_88234910[];",
            ),
            [],
        )

    def test_same_declarations_still_blocks(self) -> None:
        history = {
            "func_1": [{
                "candidate": "void func_1(void) { return; }",
                "declarations": "extern s32 x;",
                "status": "probe_rejected",
            }]
        }
        errors = runner._duplicate_candidate_errors(
            [("func_1", "void func_1(void) { return; }")], history, "extern s32 x;"
        )
        self.assertEqual(len(errors), 1)

    def test_rejects_duplicate_within_one_batch(self) -> None:
        body = "void func_1(void) { return; }"
        errors = runner._duplicate_candidate_errors(
            [("func_1", body), ("func_1", body)], {}
        )
        self.assertEqual(len(errors), 1)
        self.assertIn("duplicates candidates[0]", errors[0])

    def test_same_body_for_a_different_owner_is_allowed(self) -> None:
        body = "void f(void) { return; }"
        self.assertEqual(
            runner._duplicate_candidate_errors([("func_1", body), ("func_2", body)], {}),
            [],
        )

    def test_new_body_passes(self) -> None:
        history = {"func_1": [{"candidate": "void func_1(void) { return; }",
                               "status": "probe_rejected", "declarations": ""}]}
        self.assertEqual(
            runner._duplicate_candidate_errors(
                [("func_1", "void func_1(void) { g(); }")], history
            ),
            [],
        )


class FutilityWarningTests(unittest.TestCase):
    """Futility warns; it never refuses.

    Blocking on the verdict destroyed every accept in the measured window
    (``func_81303BF4`` closed at ``register-tie: 12``, ``func_8822B63C`` at
    ``stuck: 16``, ``func_80050E88`` at ``repeated-drift: 40``), so the
    verdict is a ranking signal and not a stopping rule.
    """

    def _tie_history(self) -> dict[str, list[dict[str, object]]]:
        return {"func_1": [
            {"mismatch_kind": "register_allocation_only", "similarity_score": 0.995}
            for _ in range(6)
        ]}

    def _stuck_history(self) -> dict[str, list[dict[str, object]]]:
        return {"func_1": [
            {"mismatch_kind": "instruction_drift", "similarity_score": 0.5}
            for _ in range(15)
        ]}

    def test_register_tie_points_at_the_permuter(self) -> None:
        warnings = runner.futility_warnings(
            [("func_1", "void func_1(void) {}")], self._tie_history()
        )
        self.assertEqual(len(warnings), 1)
        self.assertIn("permute_candidate", warnings[0])

    def test_stuck_asks_for_a_new_family(self) -> None:
        warnings = runner.futility_warnings(
            [("func_1", "void func_1(void) {}")], self._stuck_history()
        )
        self.assertEqual(len(warnings), 1)
        self.assertIn("change hypothesis family", warnings[0])

    def test_fresh_owner_is_silent(self) -> None:
        self.assertEqual(
            runner.futility_warnings([("func_1", "void func_1(void) {}")], {"func_1": []}),
            [],
        )

    def test_warning_never_becomes_a_preflight_error(self) -> None:
        import tempfile

        with tempfile.TemporaryDirectory() as raw:
            source = Path(raw) / "x.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/x/func_1.s")\n'
            )
            with mock.patch.object(
                runner, "_load_prior_attempt_history", return_value=self._tie_history()
            ):
                errors = runner.validate_candidate_batch(
                    source, ["func_1"], None, [("func_1", "void func_1(void) {}")]
                )
        self.assertEqual(errors, [])


class MissingDeclarationTests(unittest.TestCase):
    def test_cross_file_callee_used_when_owner_file_is_silent(self) -> None:
        extra = runner._missing_callee_declarations(
            "func_80002000",
            "void func_80002000(void) { func_80001000(1); }",
            "void func_80002000(void);",
            set(),
            {"func_80001000": "extern void func_80001000(s32 arg0);"},
        )
        self.assertIn("extern void func_80001000(s32 arg0);", extra)

    def test_owner_file_wins_over_the_index(self) -> None:
        extra = runner._missing_callee_declarations(
            "func_80002000",
            "void func_80002000(void) { func_80001000(1); }",
            "u8 func_80001000(s32 arg0) { return 0; }",
            set(),
            {"func_80001000": "extern void func_80001000(s32 arg0);"},
        )
        self.assertIn("u8 func_80001000(s32 arg0)", extra)
        self.assertNotIn("extern void func_80001000", extra)

    def test_data_symbol_is_declared(self) -> None:
        extra = runner._missing_callee_declarations(
            "func_80002000",
            "void func_80002000(void) { osRecvMesg(&D_800CDA10); }",
            _SOURCE,
            set(),
            None,
        )
        self.assertIn("extern OSMesgQueue D_800CDA10;", extra)

    def test_already_declared_symbol_is_not_redeclared(self) -> None:
        extra = runner._missing_callee_declarations(
            "func_80002000",
            "void func_80002000(void) { osRecvMesg(&D_800CDA10); }",
            _SOURCE,
            {"D_800CDA10"},
            None,
        )
        self.assertNotIn("D_800CDA10", extra)

    def test_unknown_symbol_is_left_alone(self) -> None:
        extra = runner._missing_callee_declarations(
            "func_80002000",
            "void func_80002000(void) { g(&D_DEADBEEF); }",
            _SOURCE,
            set(),
            None,
        )
        self.assertEqual(extra, "")


if __name__ == "__main__":
    unittest.main()
