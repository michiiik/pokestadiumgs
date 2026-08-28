#!/usr/bin/env python3
"""Regression tests for the runner-diagnostics work (issues 4 and 5a):

* prior-attempt context and futility detection (``_annotate_prior_attempts``
  and friends) -- Deliverable A;
* the ``normalized_only_match`` flag folded into ``_function_mismatch_details``
  -- Deliverable B;
* the fallback-prototype scanner that reuses a callee's real signature when
  it is defined or declared anywhere in the target source, instead of
  synthesizing a blind default -- Deliverable C (AGENTS.md Sec 5,
  ``func_8005D92C``).

All of these are pure-Python; none of them run the real compiler pipeline
(see AGENTS.md Sec 3.1/5 and this task's own constraints), so every test
here works against synthetic strings/files and in-memory dicts.
"""

from __future__ import annotations

import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import try_pragma_compare as runner  # noqa: E402
import variant_policy  # noqa: E402


def _write_stats(path: Path, batches: list[dict[str, object]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as handle:
        for batch in batches:
            handle.write(json.dumps(batch) + "\n")


def _batch(timestamp: str, attempts: list[dict[str, object]]) -> dict[str, object]:
    return {"schema_version": 2, "timestamp": timestamp, "attempts": attempts}


def _attempt(function: str, similarity_score: float, mismatch_kind: str | None, **extra: object) -> dict[str, object]:
    row = {"function": function, "similarity_score": similarity_score, "mismatch_kind": mismatch_kind}
    row.update(extra)
    return row


class PriorAttemptHistoryTests(unittest.TestCase):
    """Deliverable A: prior_attempts / best_prior / futility."""

    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        root = Path(self._tmp.name)
        self.current = root / "probe-stats" / "probe-stats.jsonl"
        self.legacy = root / "build" / "probe-stats.jsonl"
        patcher_current = mock.patch.object(variant_policy, "STATS_PATH_CURRENT", self.current)
        patcher_legacy = mock.patch.object(variant_policy, "STATS_PATH_LEGACY", self.legacy)
        patcher_current.start()
        patcher_legacy.start()
        self.addCleanup(patcher_current.stop)
        self.addCleanup(patcher_legacy.stop)

    def test_no_stats_files_is_silent_and_cheap(self) -> None:
        # A fresh worktree has no disasm/probe-stats/ at all.
        history = runner._load_prior_attempt_history()
        self.assertEqual(history, {})
        result: dict[str, object] = {"attempts": [{"function": "func_80000000"}]}
        runner._annotate_prior_attempts(result)
        attempt = result["attempts"][0]
        self.assertEqual(attempt["prior_attempts"], 0)
        self.assertIsNone(attempt["best_prior"])
        self.assertIsNone(attempt["futility"])
        self.assertEqual(result["futility_summary"], {})

    def test_prior_attempts_counted_across_current_and_legacy_files(self) -> None:
        _write_stats(self.current, [
            _batch("2026-01-01T00:00:00Z", [_attempt("func_80000000", 0.5, "immediate_drift")]),
        ])
        _write_stats(self.legacy, [
            _batch("2025-12-01T00:00:00Z", [_attempt("func_80000000", 0.7, "immediate_drift")]),
        ])
        history = runner._load_prior_attempt_history()
        self.assertEqual(len(history["func_80000000"]), 2)

    def test_best_prior_picks_highest_similarity_and_carries_raw_score(self) -> None:
        _write_stats(self.current, [
            _batch("2026-01-01T00:00:00Z", [
                _attempt("func_80000000", 0.5, "immediate_drift", label="a", raw_similarity_score=0.4),
                _attempt("func_80000000", 0.95, "register_allocation_only", label="b", raw_similarity_score=0.6),
            ]),
        ])
        result: dict[str, object] = {"attempts": [{"function": "func_80000000"}]}
        runner._annotate_prior_attempts(result)
        attempt = result["attempts"][0]
        self.assertEqual(attempt["prior_attempts"], 2)
        best = attempt["best_prior"]
        self.assertEqual(best["similarity_score"], 0.95)
        self.assertEqual(best["raw_similarity_score"], 0.6)
        self.assertEqual(best["mismatch_kind"], "register_allocation_only")
        self.assertEqual(best["label"], "b")
        self.assertEqual(best["timestamp"], "2026-01-01T00:00:00Z")

    def test_best_prior_falls_back_to_legacy_exact_similarity_score_field(self) -> None:
        # Older stats rows only have exact_similarity_score, not the newer
        # raw_similarity_score name; the reader must tolerate that.
        _write_stats(self.current, [
            _batch("2026-01-01T00:00:00Z", [
                _attempt("func_80000000", 0.99, "register_allocation_only", exact_similarity_score=0.63),
            ]),
        ])
        result: dict[str, object] = {"attempts": [{"function": "func_80000000"}]}
        runner._annotate_prior_attempts(result)
        self.assertEqual(result["attempts"][0]["best_prior"]["raw_similarity_score"], 0.63)

    def test_register_tie_futility_at_six_prior_attempts(self) -> None:
        attempts = [
            _attempt("func_80000000", 0.99, "register_allocation_only", label=f"v{i}")
            for i in range(6)
        ]
        _write_stats(self.current, [_batch("2026-01-01T00:00:00Z", attempts)])
        result: dict[str, object] = {"attempts": [{"function": "func_80000000"}]}
        runner._annotate_prior_attempts(result)
        futility = result["attempts"][0]["futility"]
        self.assertIsNotNone(futility)
        self.assertIn("register-tie: 6 prior attempts", futility)
        self.assertIn("register_allocation_only", futility)
        self.assertEqual(result["futility_summary"], {"func_80000000": futility})

    def test_no_futility_below_six_register_ties(self) -> None:
        attempts = [
            _attempt("func_80000000", 0.99, "register_allocation_only", label=f"v{i}")
            for i in range(5)
        ]
        _write_stats(self.current, [_batch("2026-01-01T00:00:00Z", attempts)])
        result: dict[str, object] = {"attempts": [{"function": "func_80000000"}]}
        runner._annotate_prior_attempts(result)
        self.assertIsNone(result["attempts"][0]["futility"])
        self.assertEqual(result["futility_summary"], {})

    def test_stuck_futility_at_fifteen_attempts_below_point_nine(self) -> None:
        attempts = [
            _attempt("func_80000000", 0.6, "immediate_drift", label=f"v{i}")
            for i in range(15)
        ]
        _write_stats(self.current, [_batch("2026-01-01T00:00:00Z", attempts)])
        result: dict[str, object] = {"attempts": [{"function": "func_80000000"}]}
        runner._annotate_prior_attempts(result)
        futility = result["attempts"][0]["futility"]
        self.assertEqual(futility, "stuck: 15 attempts, best 0.6")

    def test_no_stuck_futility_when_best_at_or_above_point_nine(self) -> None:
        attempts = [
            _attempt("func_80000000", 0.9, "immediate_drift", label=f"v{i}")
            for i in range(15)
        ]
        _write_stats(self.current, [_batch("2026-01-01T00:00:00Z", attempts)])
        result: dict[str, object] = {"attempts": [{"function": "func_80000000"}]}
        runner._annotate_prior_attempts(result)
        self.assertIsNone(result["attempts"][0]["futility"])

    def test_unrelated_function_is_unaffected(self) -> None:
        attempts = [
            _attempt("func_80000000", 0.99, "register_allocation_only", label=f"v{i}")
            for i in range(6)
        ]
        _write_stats(self.current, [_batch("2026-01-01T00:00:00Z", attempts)])
        result: dict[str, object] = {"attempts": [{"function": "func_ZZZZZZZZ"}]}
        runner._annotate_prior_attempts(result)
        attempt = result["attempts"][0]
        self.assertEqual(attempt["prior_attempts"], 0)
        self.assertIsNone(attempt["best_prior"])
        self.assertIsNone(attempt["futility"])


class NormalizedOnlyMatchTests(unittest.TestCase):
    """Deliverable B: the normalized_only_match flag on a fake details dict."""

    def test_flags_high_normalized_low_raw_score(self) -> None:
        details: dict[str, object] = {
            "similarity_score": 1.0,
            "raw_similarity_score": 0.63,
            "mismatch_kind": "register_allocation_only",
        }
        runner._annotate_normalized_only_match(details)
        self.assertTrue(details["normalized_only_match"])
        self.assertIn("raw_similarity_score=0.63", details["diagnostic"])
        self.assertIn("similarity_score=1.0", details["diagnostic"])
        self.assertIn("normalized_only_match", details["diagnostic"])

    def test_does_not_flag_when_raw_score_is_also_high(self) -> None:
        details: dict[str, object] = {
            "similarity_score": 1.0,
            "raw_similarity_score": 1.0,
            "mismatch_kind": None,
        }
        runner._annotate_normalized_only_match(details)
        self.assertFalse(details["normalized_only_match"])
        self.assertNotIn("normalized_only_match:", details["diagnostic"])

    def test_does_not_flag_low_normalized_score(self) -> None:
        details: dict[str, object] = {
            "similarity_score": 0.5,
            "raw_similarity_score": 0.3,
            "mismatch_kind": "instruction_drift",
        }
        runner._annotate_normalized_only_match(details)
        self.assertFalse(details["normalized_only_match"])

    def test_missing_scores_do_not_crash(self) -> None:
        details: dict[str, object] = {"mismatch_kind": "instruction_drift"}
        runner._annotate_normalized_only_match(details)
        self.assertFalse(details["normalized_only_match"])
        self.assertIn("mismatch_kind=instruction_drift", details["diagnostic"])

    def test_gate_warning_prints_only_for_flagged_attempts(self) -> None:
        attempts = [
            {"function": "func_A", "normalized_only_match": True, "similarity_score": 1.0, "raw_similarity_score": 0.63},
            {"function": "func_B", "normalized_only_match": False, "similarity_score": 1.0, "raw_similarity_score": 1.0},
        ]
        with mock.patch("sys.stderr") as fake_stderr:
            runner._print_normalized_only_match_warnings(attempts)
        printed = "".join(call.args[0] for call in fake_stderr.write.call_args_list if call.args)
        self.assertIn("func_A", printed)
        self.assertIn("raw_similarity_score=0.63", printed)
        self.assertNotIn("func_B", printed)


class PrototypeScannerTests(unittest.TestCase):
    """Deliverable C: scan_source_for_callee_signature and friends."""

    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)

    def _write_source(self, text: str) -> str:
        path = Path(self._tmp.name) / "synthetic.c"
        path.write_text(text)
        return path.read_text()

    def test_finds_definition_sharing_a_line_with_an_earlier_statement(self) -> None:
        # This is the exact AGENTS.md Sec 5 shape: disasm/src/585D0.c has
        # ``extern u8 D_80128574[]; u8 func_8005D92C(s32 index) { ... }`` --
        # a definition whose line begins with an unrelated earlier statement,
        # which a line-anchored scan (``^...`` per line) would miss.
        source = self._write_source(
            "extern u8 D_80128574[]; u8 func_8005D92C(s32 index) { return D_80128574[index * 112]; }\n"
        )
        signature = runner.scan_source_for_callee_signature(source, "func_8005D92C")
        self.assertEqual(signature, "u8 func_8005D92C(s32 index)")

    def test_finds_a_definition_defined_later_in_the_file(self) -> None:
        source = self._write_source(
            "s32 func_80057A80(s32 arg0) {\n"
            "    return func_8005D92C(arg0);\n"
            "}\n"
            "\n"
            "u8 func_8005D92C(s32 index) {\n"
            "    return 0;\n"
            "}\n"
        )
        signature = runner.scan_source_for_callee_signature(source, "func_8005D92C")
        self.assertEqual(signature, "u8 func_8005D92C(s32 index)")

    def test_prefers_a_real_definition_over_a_plain_prototype(self) -> None:
        source = self._write_source(
            "extern s32 func_8005D92C(s32);\n"
            "u8 func_8005D92C(s32 index) { return 0; }\n"
        )
        signature = runner.scan_source_for_callee_signature(source, "func_8005D92C")
        self.assertEqual(signature, "u8 func_8005D92C(s32 index)")

    def test_falls_back_to_a_plain_prototype_when_no_definition_exists(self) -> None:
        source = self._write_source("extern u8 func_8005D92C(s32);\n")
        signature = runner.scan_source_for_callee_signature(source, "func_8005D92C")
        # The raw signature keeps whatever the source actually wrote (here,
        # including "extern"); _as_extern_declaration is what normalizes it
        # to exactly one "extern" when injecting it as a declaration.
        self.assertEqual(signature, "extern u8 func_8005D92C(s32)")
        self.assertEqual(
            runner._as_extern_declaration(signature), "extern u8 func_8005D92C(s32);"
        )

    def test_returns_none_for_a_callee_not_in_the_file(self) -> None:
        source = self._write_source("u8 func_8005D92C(s32 index) { return 0; }\n")
        self.assertIsNone(runner.scan_source_for_callee_signature(source, "func_ABCDEF01"))

    def test_ignores_a_mere_call_site(self) -> None:
        source = self._write_source(
            "s32 func_wrap(void) { s32 result = func_8005D92C(1); return result; }\n"
        )
        self.assertIsNone(runner.scan_source_for_callee_signature(source, "func_8005D92C"))

    def test_ignores_a_call_inside_a_condition(self) -> None:
        source = self._write_source(
            "s32 func_wrap(void) { if (func_8005D92C(1)) { return 1; } return 0; }\n"
        )
        self.assertIsNone(runner.scan_source_for_callee_signature(source, "func_8005D92C"))


class MissingCalleeDeclarationTests(unittest.TestCase):
    """Deliverable C: the pipeline that injects the scanned signature."""

    def test_injects_the_real_signature_for_an_undeclared_forward_call(self) -> None:
        baseline = (
            "s32 func_80057A80(s32 arg0) { return func_8005D92C(arg0); }\n"
            "extern u8 D_1[]; u8 func_8005D92C(s32 index) { return D_1[index]; }\n"
        )
        blocks = [("func_80057A80", "s32 func_80057A80(s32 arg0) { return func_8005D92C(arg0); }")]
        augmented = runner._augment_blocks_with_callee_declarations(blocks, "", baseline)
        function, candidate = augmented[0]
        self.assertEqual(function, "func_80057A80")
        self.assertIn("extern u8 func_8005D92C(s32 index);", candidate)

    def test_keeps_behavior_identical_for_a_callee_not_in_the_file(self) -> None:
        baseline = "s32 func_80057A80(s32 arg0) { return func_8005D92C(arg0); }\n"
        original_candidate = "s32 func_80057A80(s32 arg0) { return func_8005D92C(arg0); }"
        blocks = [("func_80057A80", original_candidate)]
        augmented = runner._augment_blocks_with_callee_declarations(blocks, "", baseline)
        # Nothing found anywhere in the file: no default is guessed, and the
        # candidate text is untouched (byte-identical), matching historical
        # behavior for this case.
        self.assertEqual(augmented, blocks)

    def test_does_not_emit_a_conflicting_fallback_when_the_candidate_already_declares_it(self) -> None:
        baseline = "u8 func_8005D92C(s32 index) { return 0; }\n"
        candidate = (
            "extern s32 func_8005D92C(s32);\n"
            "s32 func_X(s32 a) { return func_8005D92C(a); }"
        )
        blocks = [("func_X", candidate)]
        augmented = runner._augment_blocks_with_callee_declarations(blocks, "", baseline)
        function, result_candidate = augmented[0]
        # The candidate's own (possibly wrong) declaration is left exactly
        # as given -- no second, conflicting extern is layered on top of it.
        self.assertEqual(result_candidate, candidate)
        self.assertEqual(result_candidate.count("func_8005D92C("), 2)

    def test_does_not_emit_a_conflicting_fallback_when_shared_declarations_cover_it(self) -> None:
        baseline = "u8 func_8005D92C(s32 index) { return 0; }\n"
        shared = "extern s32 func_8005D92C(s32);"
        candidate = "s32 func_X(s32 a) { return func_8005D92C(a); }"
        blocks = [("func_X", candidate)]
        augmented = runner._augment_blocks_with_callee_declarations(blocks, shared, baseline)
        function, result_candidate = augmented[0]
        self.assertEqual(result_candidate.count("extern"), 1)
        self.assertIn(shared, result_candidate)

    def test_does_not_declare_the_target_function_itself(self) -> None:
        baseline = "s32 func_X(s32 a) { return a; }\n"
        candidate = "s32 func_X(s32 a) { return func_X(a - 1) + 1; }"
        blocks = [("func_X", candidate)]
        augmented = runner._augment_blocks_with_callee_declarations(blocks, "", baseline)
        self.assertEqual(augmented, blocks)


if __name__ == "__main__":
    unittest.main()
