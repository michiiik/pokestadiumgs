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
* structured runner-internal diagnostics for exceptions escaping probe worker
  futures, including full-gate eligibility -- Deliverable D.

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


class ProbeWorkerExceptionTests(unittest.TestCase):
    """Deliverable D: worker exceptions are runner failures, not probe misses."""

    def test_worker_exception_is_structured_and_bounded(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
            )
            with mock.patch.object(
                runner,
                "source_object_path",
                return_value=(None, Path(directory) / "synthetic.o"),
            ), mock.patch.object(
                runner, "_ensure_baseline_object", return_value=True
            ), mock.patch.object(
                runner, "_function_bytes", return_value=b"baseline"
            ), mock.patch.object(
                runner, "_object_link_shape", return_value=None
            ), mock.patch.object(
                runner,
                "_probe_one",
                side_effect=IndexError("list index out of range"),
            ):
                results = runner.probe_candidates(
                    source,
                    [("func_a", "void func_a(void) {}")],
                    workers=1,
                )

        attempt = results[0]
        self.assertEqual(attempt["status"], "runner_internal_error")
        self.assertEqual(attempt["probe_reason"], "runner_internal_error")
        self.assertEqual(attempt["exception_type"], "IndexError")
        self.assertEqual(attempt["phase"], "probe_candidates.future_result")
        self.assertEqual(attempt["context"]["function"], "func_a")
        self.assertEqual(attempt["context"]["candidate_index"], 0)
        self.assertIn("IndexError", attempt["diagnostic"])
        self.assertIn("list index out of range", attempt["diagnostic"])
        self.assertEqual(attempt["traceback"], attempt["diagnostic"])
        self.assertLessEqual(
            len(attempt["diagnostic"]), runner._RUNNER_INTERNAL_ERROR_MAX_CHARS
        )
        self.assertFalse(runner._full_gate_eligible(attempt))
        oversized = runner._bounded_runner_internal_diagnostic(
            "traceback head\n" + ("x" * runner._RUNNER_INTERNAL_ERROR_MAX_CHARS) + "\nexception tail"
        )
        self.assertEqual(len(oversized), runner._RUNNER_INTERNAL_ERROR_MAX_CHARS)
        self.assertIn("traceback head", oversized)
        self.assertIn("runner traceback truncated", oversized)
        self.assertIn("exception tail", oversized)

    def test_internal_error_does_not_fall_back_to_full_gate(self) -> None:
        internal_error = {
            "index": 0,
            "function": "func_a",
            "status": "runner_internal_error",
            "probe_reason": "runner_internal_error",
            "exception_type": "IndexError",
            "phase": "probe_candidates.future_result",
            "context": {"function": "func_a", "candidate_index": 0},
            "diagnostic": "IndexError: list index out of range",
            "traceback": "IndexError: list index out of range",
        }
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
            )
            with mock.patch.object(
                runner, "probe_candidates", return_value=[internal_error]
            ), mock.patch.object(
                runner, "_claim_or_refuse", return_value=None
            ), mock.patch.object(
                runner, "_record_probe_stats"
            ), mock.patch.object(
                runner, "_try_candidate_detailed"
            ) as full_gate, mock.patch.object(
                runner, "compare_current_tree"
            ) as full_compare:
                result = runner.try_candidates_detailed(
                    source,
                    [("func_a", "void func_a(void) {}")],
                )

        self.assertEqual(result["status"], 1)
        self.assertEqual(result["batch_status"], "no_candidate_accepted")
        self.assertEqual(result["attempts"][0]["status"], "runner_internal_error")
        full_gate.assert_not_called()
        full_compare.assert_not_called()

    def test_only_legacy_unavailable_reasons_remain_gate_eligible(self) -> None:
        self.assertTrue(
            runner._full_gate_eligible({
                "status": "probe_unavailable",
                "probe_reason": "baseline_object_unavailable",
            })
        )
        self.assertTrue(
            runner._full_gate_eligible({
                "status": "probe_unavailable",
                "probe_reason": "missing_function_bytes",
            })
        )
        self.assertFalse(
            runner._full_gate_eligible({
                "status": "probe_unavailable",
                "probe_reason": "probe_error",
            })
        )
        self.assertFalse(
            runner._full_gate_eligible({
                "status": "probe_unavailable",
                "probe_reason": "runner_internal_error",
            })
        )

    def test_relocation_masked_match_uses_one_sequential_gate_and_can_reject(self) -> None:
        promoted = {
            "index": 0,
            "function": "func_a",
            "status": "probe_match",
            "probe_reason": "relocation_fields_only",
            "relocation_masked": True,
            "link_verified": False,
            "link_mismatch": "section_content_drift",
        }
        self.assertTrue(runner._full_gate_eligible(promoted))
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
            )
            with mock.patch.object(
                runner, "probe_candidates", return_value=[promoted]
            ), mock.patch.object(
                runner, "_claim_or_refuse", return_value=None
            ), mock.patch.object(
                runner, "rebuild_source_object", return_value=0
            ), mock.patch.object(
                runner, "_try_candidate_detailed", return_value=(2, "compare_rejected")
            ) as sequential_gate, mock.patch.object(
                runner, "compare_current_tree"
            ) as combined_gate:
                result = runner.try_candidates_detailed(
                    source, [("func_a", "void func_a(void) {}")]
                )

        sequential_gate.assert_called_once()
        combined_gate.assert_not_called()
        self.assertEqual(result["attempts"][0]["probe_status"], "probe_match")
        self.assertEqual(result["attempts"][0]["status"], "compare_rejected")
        self.assertEqual(result["timing"]["gate_runs"], 1)
        self.assertEqual(result["timing"]["gate_mode"], "sequential")

    def test_structured_fields_are_persisted_in_probe_stats(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats_path = Path(directory) / "probe-stats.jsonl"
            attempt = runner._runner_internal_error_result(
                IndexError("list index out of range"),
                phase="probe_candidates.future_result",
                context={"function": "func_a", "candidate_index": 0},
            )
            attempt["function"] = "func_a"
            with mock.patch.dict(
                runner.os.environ, {"PRAGMA_PROBE_STATS": str(stats_path)}
            ):
                runner._record_probe_stats(
                    Path("synthetic.c"),
                    [attempt],
                    [None],
                    [("func_a", "void func_a(void) {}")],
                )

            row = json.loads(stats_path.read_text())["attempts"][0]
        self.assertEqual(row["status"], "runner_internal_error")
        self.assertEqual(row["probe_reason"], "runner_internal_error")
        self.assertEqual(row["exception_type"], "IndexError")
        self.assertEqual(row["phase"], "probe_candidates.future_result")
        self.assertEqual(row["context"]["function"], "func_a")
        self.assertIn("list index out of range", row["diagnostic"])
        self.assertIn("list index out of range", row["traceback"])


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

    def test_repeated_first_diff_is_advisory_at_twelve_prior_rejections(self) -> None:
        attempts = [
            _attempt(
                "func_80000000",
                0.95,
                "immediate_drift",
                status="probe_rejected",
                first_diff_offset=8,
                first_diff_instruction=2,
                expected_instruction="0x24040001",
                actual_instruction="0x24040002",
                label=f"v{i}",
            )
            for i in range(12)
        ]
        _write_stats(self.current, [_batch("2026-01-01T00:00:00Z", attempts)])
        result: dict[str, object] = {
            "attempts": [{
                "function": "func_80000000",
                "status": "probe_rejected",
                "mismatch_kind": "immediate_drift",
                "first_diff_offset": 8,
                "first_diff_instruction": 2,
                "expected_instruction": "0x24040001",
                "actual_instruction": "0x24040002",
            }]
        }
        runner._annotate_prior_attempts(result)

        attempt = result["attempts"][0]
        self.assertEqual(attempt["prior_attempts"], 12)
        self.assertEqual(
            attempt["first_diff_fingerprint"],
            '["immediate_drift",8,2,"0x24040001","0x24040002"]',
        )
        self.assertIn("repeated-drift", attempt["repeated_drift"])
        self.assertIn("12 prior rejected attempts", attempt["futility"])
        self.assertEqual(result["futility_summary"], {"func_80000000": attempt["futility"]})
        self.assertEqual(attempt["status"], "probe_rejected")

    def test_compile_failures_do_not_count_as_repeated_drift(self) -> None:
        attempts = [
            _attempt(
                "func_80000000",
                0.95,
                "immediate_drift",
                status="compile_failed",
                first_diff_offset=8,
                first_diff_instruction=2,
                expected_instruction="0x24040001",
                actual_instruction="0x24040002",
            )
            for _ in range(12)
        ]
        _write_stats(self.current, [_batch("2026-01-01T00:00:00Z", attempts)])
        result: dict[str, object] = {"attempts": [{"function": "func_80000000"}]}
        runner._annotate_prior_attempts(result)

        attempt = result["attempts"][0]
        self.assertIsNone(attempt["repeated_drift"])
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


class FunctionMismatchDetailsTests(unittest.TestCase):
    def test_short_instruction_texts_are_bounded_by_text_list_lengths(self) -> None:
        expected = b"\x00\x00\x00\x01" * 3
        actual = b"\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x03"
        with mock.patch.object(
            runner,
            "_instruction_texts",
            side_effect=[["expected instruction"], ["actual instruction"]],
        ):
            details = runner._function_mismatch_details(
                Path("unused.o"),
                "func_synthetic",
                expected,
                actual,
                actual_symbol_size=len(actual),
            )

        self.assertEqual(details["expected_instruction_count"], 1)
        self.assertEqual(details["actual_instruction_count"], 1)
        self.assertTrue(
            any(
                diff["expected"] == "<missing>" or diff["actual"] == "<missing>"
                for diff in details["assembly_diff"]
            )
        )


class InstructionTextAlignmentTests(unittest.TestCase):
    """One instruction text per word, or every derived number is wrong.

    ``objdump`` collapses a run of two or more zero words into a single
    ``...`` line, and zero is ``nop`` on MIPS.  The scores divide a
    word-space match count by a text-space length, so a dropped line used to
    produce raw similarity above 1.0 and a normalised 1.0 that hid a genuine
    mismatch (``func_80047BD4`` in ``disasm/src/47580.c`` reported raw
    1.0513 at normalised 1.0).
    """

    # ``nop`` runs surrounded by real instructions: the exact shape objdump
    # elides.  ``addiu $sp, $sp, -8`` / nop / nop / ``jr $ra`` / nop / nop.
    _NOP_RUN_BODY = (
        b"\x27\xbd\xff\xf8"
        b"\x00\x00\x00\x00"
        b"\x00\x00\x00\x00"
        b"\x03\xe0\x00\x08"
        b"\x00\x00\x00\x00"
        b"\x00\x00\x00\x00"
    )

    def test_disassembler_is_told_not_to_elide_zero_words(self) -> None:
        with mock.patch.object(
            runner, "_run_binutils", return_value=(0, "")
        ) as run_binutils:
            runner._disassemble_bytes(self._NOP_RUN_BODY)
        argv = run_binutils.call_args.args[0]
        self.assertIn("-z", argv)

    def test_instruction_texts_are_one_per_word_over_a_nop_run(self) -> None:
        texts = runner._instruction_texts(self._NOP_RUN_BODY)
        self.assertEqual(len(texts), len(self._NOP_RUN_BODY) // 4)

    def test_short_disassembly_falls_back_to_the_one_to_one_decoder(self) -> None:
        with mock.patch.object(
            runner, "_disassemble_bytes", return_value=["addiu sp,sp,-8", "jr ra"]
        ):
            texts = runner._instruction_texts(self._NOP_RUN_BODY)
        self.assertEqual(len(texts), len(self._NOP_RUN_BODY) // 4)
        # The fallback decoder, not the truncated objdump output.
        self.assertNotIn("addiu sp,sp,-8", texts)

    def test_similarity_scores_stay_within_the_unit_range(self) -> None:
        expected = self._NOP_RUN_BODY
        variants = {
            "identical": expected,
            "one_word_changed": expected[:12] + b"\x03\xe0\x00\x09" + expected[16:],
            "shorter": expected[:-8],
            "longer": expected + b"\x00\x00\x00\x00" * 2,
        }
        for name, actual in variants.items():
            with self.subTest(variant=name):
                details = runner._function_mismatch_details(
                    Path("unused.o"),
                    "func_synthetic",
                    expected,
                    actual,
                    actual_symbol_size=len(actual),
                )
                for key in (
                    "raw_similarity_score",
                    "similarity_score",
                    "register_only_similarity_score",
                    "exact_similarity_score",
                ):
                    self.assertLessEqual(details[key], 1.0, msg=f"{name}/{key}")
                    self.assertGreaterEqual(details[key], 0.0, msg=f"{name}/{key}")
                self.assertEqual(
                    details["expected_instruction_count"], len(expected) // 4
                )
                self.assertEqual(
                    details["actual_instruction_count"], len(actual) // 4
                )

    def test_a_real_difference_is_not_masked_by_an_elided_nop_run(self) -> None:
        expected = self._NOP_RUN_BODY
        # Change the instruction that sits *after* the elided nop run.
        actual = expected[:12] + b"\x03\xe0\x00\x09" + expected[16:]
        details = runner._function_mismatch_details(
            Path("unused.o"),
            "func_synthetic",
            expected,
            actual,
            actual_symbol_size=len(actual),
        )
        self.assertLess(details["raw_similarity_score"], 1.0)
        self.assertEqual(details["first_diff_instruction"], 3)


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
