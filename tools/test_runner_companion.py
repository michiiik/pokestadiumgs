#!/usr/bin/env python3
"""Tests for the "paired change" companion-edit feature of the MCP runner.

These exercise ``apply_companion_edits`` and the parts of
``try_candidates_detailed`` that can be reached without compiling anything
(the companion edit is validated, and can fail, before any probe or gate
runs). Pure functions on synthetic source text only -- no compiler, no
``make``, and never against the real ``disasm/src`` tree.
"""

from __future__ import annotations

import os
import tempfile
import unittest
from pathlib import Path
from unittest import mock

import try_pragma_compare as runner

# Never let a synthetic test transaction land in the real probe-stats file.
_STATS_ISOLATION = mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": ""})


def setUpModule() -> None:
    _STATS_ISOLATION.start()


def tearDownModule() -> None:
    _STATS_ISOLATION.stop()


# A shrunk stand-in for the real disasm/src/14640.c shape this feature was
# built for: an accepted caller invoking a still-pragma callee with fewer
# arguments than its real signature.
SAMPLE_SOURCE = (
    '#include "global.h"\n\n'
    'extern void func_8001480C(void);\n\n'
    '#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001480C.s")\n\n'
    '#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80018AB0.s")\n\n'
    'void func_80018A74(void) { func_8001480C(); }\n\n'
    'void func_80018A94(s32 arg0) { (void)arg0; }\n'
)


class CandidateBatchPreflightTests(unittest.TestCase):
    def _source_path(self, directory: Path) -> Path:
        source_path = directory / "preflight_test.c"
        source_path.write_text(SAMPLE_SOURCE)
        return source_path

    def test_accepts_active_owner_without_companion_edit(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            errors = runner.validate_candidate_batch(
                self._source_path(Path(tmp)),
                ["func_8001480C"],
            )
        self.assertEqual(errors, [])

    def test_finds_definition_immediately_after_pragma(self) -> None:
        source = (
            '#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001480C.s")\n'
            'void func_80018A74(void) { func_8001480C(); }\n'
        )
        self.assertEqual(
            runner.scan_source_for_callee_signature(source, "func_80018A74"),
            "void func_80018A74(void)",
        )

    def test_rejects_non_owner_candidate(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            errors = runner.validate_candidate_batch(
                self._source_path(Path(tmp)),
                ["func_80018A94"],
            )
        self.assertEqual(len(errors), 1)
        self.assertIn("not an active GLOBAL_ASM owner", errors[0])

    def test_rejects_companion_target_that_is_candidate_owner(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            errors = runner.validate_candidate_batch(
                self._source_path(Path(tmp)),
                ["func_8001480C"],
                [{
                    "function": "func_8001480C",
                    "old": "anything",
                    "new": "anything else",
                }],
            )
        self.assertEqual(len(errors), 1)
        self.assertIn("also a candidate owner", errors[0])

    def test_rejects_companion_target_that_is_still_assembly(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            errors = runner.validate_candidate_batch(
                self._source_path(Path(tmp)),
                ["func_8001480C"],
                [{
                    "function": "func_80018AB0",
                    "old": "void func_80018AB0(void) {}",
                    "new": "void func_80018AB0(void) { (void)0; }",
                }],
            )
        self.assertEqual(len(errors), 1)
        self.assertIn("still a GLOBAL_ASM owner", errors[0])

    def test_rejects_companion_text_not_about_named_definition(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            errors = runner.validate_candidate_batch(
                self._source_path(Path(tmp)),
                ["func_8001480C"],
                [{
                    "function": "func_80018A94",
                    "old": "unrelated text",
                    "new": "also unrelated",
                }],
            )
        self.assertEqual(len(errors), 1)
        self.assertIn("old text does not contain target", errors[0])

    def test_accepts_exact_edit_of_existing_definition(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            errors = runner.validate_candidate_batch(
                self._source_path(Path(tmp)),
                ["func_8001480C"],
                [{
                    "function": "func_80018A94",
                    "old": "void func_80018A94(s32 arg0) { (void)arg0; }",
                    "new": "void func_80018A94(s32 arg0) { (void)arg0; (void)0; }",
                }],
            )
        self.assertEqual(errors, [])

    def test_accepts_retype_of_candidate_owners_stale_extern(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            errors = runner.validate_candidate_batch(
                self._source_path(Path(tmp)),
                ["func_8001480C"],
                [{
                    "function": "func_8001480C",
                    "old": "extern void func_8001480C(void);",
                    "new": "extern s32 func_8001480C(s32 arg0);",
                }],
                [("func_8001480C", "s32 func_8001480C(s32 arg0) { return arg0; }")],
            )
        self.assertEqual(errors, [])


class ApplyCompanionEditsTests(unittest.TestCase):
    def test_no_edits_is_a_no_op(self) -> None:
        text, error = runner.apply_companion_edits(SAMPLE_SOURCE, None)
        self.assertIsNone(error)
        self.assertEqual(text, SAMPLE_SOURCE)

        text, error = runner.apply_companion_edits(SAMPLE_SOURCE, [])
        self.assertIsNone(error)
        self.assertEqual(text, SAMPLE_SOURCE)

    def test_exact_single_match_applies(self) -> None:
        edits = [{
            "function": "func_80018A94",
            "old": "void func_80018A94(s32 arg0) { (void)arg0; }",
            "new": "void func_80018A94(s32 arg0) { (void)arg0; (void)0; }",
        }]
        text, error = runner.apply_companion_edits(SAMPLE_SOURCE, edits)
        self.assertIsNone(error)
        self.assertIn("(void)0;", text)
        # Nothing else in the file moved.
        self.assertIn(
            'void func_80018A74(void) { func_8001480C(); }', text
        )

    def test_multiple_edits_apply_in_order_on_the_working_copy(self) -> None:
        edits = [
            {
                "function": "func_80018A74",
                "old": "void func_80018A74(void) { func_8001480C(); }",
                "new": "void func_80018A74(void) { ((void (*)(void))func_8001480C)(); }",
            },
            {
                "function": "func_80018A94",
                "old": "void func_80018A94(s32 arg0) { (void)arg0; }",
                "new": "void func_80018A94(s32 arg0, s32 arg1) { (void)arg0; (void)arg1; }",
            },
        ]
        text, error = runner.apply_companion_edits(SAMPLE_SOURCE, edits)
        self.assertIsNone(error)
        self.assertIn("((void (*)(void))func_8001480C)();", text)
        self.assertIn("func_80018A94(s32 arg0, s32 arg1)", text)
        # The pragma for the real new candidate is untouched by either edit.
        self.assertIn(
            '#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001480C.s")', text
        )

    def test_missing_old_text_fails(self) -> None:
        edits = [{
            "function": "func_80018A94",
            "old": "this text does not appear anywhere",
            "new": "replacement",
        }]
        text, error = runner.apply_companion_edits(SAMPLE_SOURCE, edits)
        self.assertEqual(text, SAMPLE_SOURCE)
        self.assertIsNotNone(error)
        self.assertIn("not found", error)
        self.assertIn("func_80018A94", error)

    def test_ambiguous_old_text_fails(self) -> None:
        source = SAMPLE_SOURCE + "\nvoid func_80018A94(s32 arg0) { (void)arg0; }\n"
        edits = [{
            "function": "func_80018A94",
            "old": "void func_80018A94(s32 arg0) { (void)arg0; }",
            "new": "void func_80018A94(s32 arg0) { (void)arg0; (void)1; }",
        }]
        text, error = runner.apply_companion_edits(source, edits)
        self.assertEqual(text, source)
        self.assertIsNotNone(error)
        self.assertIn("2 times", error)
        self.assertIn("exactly once", error)

    def test_rejects_edit_on_a_current_pragma_owner(self) -> None:
        # ``function`` names the still-pragma callee; the edit text itself
        # never mentions GLOBAL_ASM, so this is specifically exercising the
        # ownership check rather than the add/remove-pragma guard below.
        edits = [{
            "function": "func_8001480C",
            "old": "void func_80018A74(void) { func_8001480C(); }",
            "new": "void func_80018A74(void) { ((void (*)(void))func_8001480C)(); }",
        }]
        text, error = runner.apply_companion_edits(SAMPLE_SOURCE, edits)
        self.assertEqual(text, SAMPLE_SOURCE)
        self.assertIsNotNone(error)
        self.assertIn("still a", error)
        self.assertIn("GLOBAL_ASM pragma owner", error)

    def test_rejects_edit_that_removes_a_pragma(self) -> None:
        # Same text as the pragma-owner rejection above, but even if the
        # ownership check were skipped this must independently be refused:
        # a companion edit may never add or remove a GLOBAL_ASM pragma.
        edits = [{
            "function": "func_8001480C",
            "old": (
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001480C.s")'
            ),
            "new": "",
        }]
        text, error = runner.apply_companion_edits(SAMPLE_SOURCE, edits)
        self.assertEqual(text, SAMPLE_SOURCE)
        self.assertIsNotNone(error)
        self.assertIn("GLOBAL_ASM", error)

    def test_rejects_edit_that_adds_a_pragma(self) -> None:
        edits = [{
            "function": "func_80018A94",
            "old": "void func_80018A94(s32 arg0) { (void)arg0; }",
            "new": (
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80018A94.s")'
            ),
        }]
        text, error = runner.apply_companion_edits(SAMPLE_SOURCE, edits)
        self.assertEqual(text, SAMPLE_SOURCE)
        self.assertIsNotNone(error)
        self.assertIn("GLOBAL_ASM", error)

    def test_malformed_edit_dict_fails_cleanly(self) -> None:
        text, error = runner.apply_companion_edits(SAMPLE_SOURCE, [{"function": "f"}])
        self.assertEqual(text, SAMPLE_SOURCE)
        self.assertIsNotNone(error)

    def test_working_copy_composes_with_candidate_insertion(self) -> None:
        """The documented order: companion edits first, then the candidate body."""
        edits = [{
            "function": "func_80018A74",
            "old": "void func_80018A74(void) { func_8001480C(); }",
            "new": "void func_80018A74(void) { ((void (*)(void))func_8001480C)(); }",
        }]
        working, error = runner.apply_companion_edits(SAMPLE_SOURCE, edits)
        self.assertIsNone(error)
        candidate = "s32 func_8001480C(s32 arg0) { return arg0; }"
        installed = runner._replace_candidate_text(working, "func_8001480C", candidate)
        self.assertIsNotNone(installed)
        self.assertNotIn(
            '#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001480C.s")',
            installed,
        )
        self.assertIn(
            '#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80018AB0.s")',
            installed,
        )
        self.assertIn("s32 func_8001480C(s32 arg0) { return arg0; }", installed)
        self.assertIn("((void (*)(void))func_8001480C)();", installed)

    def test_candidate_substitution_precedes_self_companion_edit(self) -> None:
        candidate = "s32 func_8001480C(s32 arg0) { return arg0; }"
        replaced = runner._replace_candidate_text(
            SAMPLE_SOURCE, "func_8001480C", candidate
        )
        self.assertIsNotNone(replaced)
        edited, error = runner.apply_companion_edits(replaced, [{
            "function": "func_8001480C",
            "old": "extern void func_8001480C(void);",
            "new": "extern s32 func_8001480C(s32 arg0);",
        }])
        self.assertIsNone(error)
        self.assertIn("extern s32 func_8001480C(s32 arg0);", edited)
        self.assertNotIn(
            '#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001480C.s")',
            edited,
        )


class TryCandidatesDetailedCompanionFailureTests(unittest.TestCase):
    """The public entry point short-circuits on a bad companion edit.

    A failed companion edit is caught before any isolated probe or gate
    runs, so this reaches real ``try_candidates_detailed`` code without
    invoking the compiler.
    """

    def _write_source(self, directory: Path) -> Path:
        source_path = directory / "companion_test.c"
        source_path.write_text(SAMPLE_SOURCE)
        return source_path

    def test_ambiguous_companion_edit_fails_the_whole_batch(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source_path = self._write_source(Path(tmp))
            companion_edits = [{
                "function": "func_80018A94",
                "old": "this text is definitely not present",
                "new": "irrelevant",
            }]
            result = runner.try_candidates_detailed(
                source_path,
                [("func_8001480C", "s32 func_8001480C(s32 arg0) { return arg0; }")],
                gate=True,
                companion_edits=companion_edits,
            )
            self.assertEqual(result["batch_status"], "companion_edit_failed")
            self.assertEqual(result["accepted"], [])
            self.assertEqual(len(result["attempts"]), 1)
            attempt = result["attempts"][0]
            self.assertEqual(attempt["status"], "companion_edit_failed")
            self.assertIn("func_80018A94", attempt["diagnostic"])
            self.assertEqual(attempt["companion_edits"], ["func_80018A94"])
            # Nothing was written: the source is untouched.
            self.assertEqual(source_path.read_text(), SAMPLE_SOURCE)

    def test_probe_only_batch_also_reports_companion_edit_failure(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source_path = self._write_source(Path(tmp))
            companion_edits = [{
                "function": "func_8001480C",
                "old": '#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001480C.s")',
                "new": "void func_8001480C(s32 arg0) { (void)arg0; }",
            }]
            result = runner.try_candidates_detailed(
                source_path,
                [("func_8001480C", "s32 func_8001480C(s32 arg0) { return arg0; }")],
                gate=False,
                companion_edits=companion_edits,
            )
            self.assertEqual(result["batch_status"], "companion_edit_failed")
            self.assertEqual(source_path.read_text(), SAMPLE_SOURCE)

    def test_self_companion_edit_is_installed_after_candidate_gate(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            source_path = self._write_source(Path(tmp))
            companion_edits = [{
                "function": "func_8001480C",
                "old": "extern void func_8001480C(void);",
                "new": "extern s32 func_8001480C(s32 arg0);",
            }]
            candidate = "s32 func_8001480C(s32 arg0) { return arg0; }"
            with mock.patch.object(
                runner,
                "probe_candidates",
                return_value=[{
                    "index": 0,
                    "function": "func_8001480C",
                    "status": "probe_match",
                    "link_verified": True,
                }],
            ), mock.patch.object(
                runner, "rebuild_source_object", return_value=0
            ), mock.patch.object(
                runner, "compare_current_tree", return_value=0
            ):
                result = runner.try_candidates_detailed(
                    source_path,
                    [("func_8001480C", candidate)],
                    companion_edits=companion_edits,
                )
            self.assertEqual(result["accepted"], ["func_8001480C"])
            installed = source_path.read_text()
            self.assertIn("extern s32 func_8001480C(s32 arg0);", installed)
            self.assertIn(candidate, installed)
            self.assertNotIn(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001480C.s")',
                installed,
            )

    def test_backwards_compatible_when_omitted(self) -> None:
        """Omitting companion_edits must not change the shape of a result."""
        with tempfile.TemporaryDirectory() as tmp:
            source_path = self._write_source(Path(tmp))
            # This candidate will fail to probe (no baseline object exists in
            # this throwaway directory), but the point is only that omitting
            # companion_edits never raises and never mentions the feature.
            result = runner.try_candidates_detailed(
                source_path,
                [("func_8001480C", "s32 func_8001480C(s32 arg0) { return arg0; }")],
                gate=False,
            )
            self.assertNotEqual(result.get("batch_status"), "companion_edit_failed")
            for attempt in result["attempts"]:
                self.assertNotIn("companion_edits", attempt)


class RecordProbeStatsCompanionFieldTests(unittest.TestCase):
    """The stats writer persists ``companion_edits`` without a schema change."""

    def test_companion_edits_field_is_written_and_read_back(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            stats_file = Path(tmp) / "probe-stats.jsonl"
            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": str(stats_file)}):
                attempts = [{
                    "function": "func_8001480C",
                    "status": "accepted",
                    "companion_edits": ["func_80018A74"],
                }]
                runner._record_probe_stats(
                    Path("disasm/src/14640.c"),
                    attempts,
                    labels=None,
                    blocks=[("func_8001480C", "s32 func_8001480C(s32 arg0) { return arg0; }")],
                )
            import probe_stats

            batches = list(probe_stats.iter_batches([stats_file]))
            self.assertEqual(len(batches), 1)
            row = batches[0]["attempts"][0]
            self.assertEqual(row["companion_edits"], ["func_80018A74"])

    def test_companion_edits_field_absent_is_tolerated(self) -> None:
        """A reader (e.g. tools/report_candidate_yield.py) must not choke on
        an older row that has no ``companion_edits`` key at all."""
        import probe_stats

        shaped = probe_stats.shape_attempt_row({"function": "func_a", "status": "accepted"})
        self.assertNotIn("companion_edits", shaped)


if __name__ == "__main__":
    unittest.main()
