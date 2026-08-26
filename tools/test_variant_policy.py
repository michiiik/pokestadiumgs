#!/usr/bin/env python3
"""Regression tests for tools/variant_policy.py."""

from __future__ import annotations

import json
import tempfile
import unittest
from pathlib import Path
from unittest import mock

import variant_policy as vp


def _write_stats(path: Path, records: list[dict[str, object]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as handle:
        for record in records:
            handle.write(json.dumps(record) + "\n")


def _attempt(label: str, status: str, diagnostic: str | None = None) -> dict[str, object]:
    return {"function": "func_80000000", "label": label, "status": status, "diagnostic": diagnostic}


class ClassifyDiagnosticTests(unittest.TestCase):
    def test_none_and_empty_are_class_none(self) -> None:
        self.assertEqual(vp.classify_diagnostic(None), vp.CLASS_NONE)
        self.assertEqual(vp.classify_diagnostic(""), vp.CLASS_NONE)

    def test_operand_and_pointer_messages_bucket_together(self) -> None:
        self.assertEqual(
            vp.classify_diagnostic("cfe: Error: Unacceptable operand of '+'."),
            vp.CLASS_POINTER_OPERAND,
        )
        self.assertEqual(
            vp.classify_diagnostic("cfe: Error: incompatible pointer conversion"),
            vp.CLASS_POINTER_OPERAND,
        )

    def test_undefined_and_redeclaration_are_distinct(self) -> None:
        self.assertEqual(
            vp.classify_diagnostic("cfe: Error: 'D_80000004' undefined; reoccurrences will not be reported."),
            vp.CLASS_UNDEFINED,
        )
        self.assertEqual(
            vp.classify_diagnostic("cfe: Error: redeclaration of 'func_80000000'"),
            vp.CLASS_REDECLARATION,
        )

    def test_anonymous_and_named_no_prototype_calls_are_distinct(self) -> None:
        self.assertEqual(
            vp.classify_diagnostic(
                "cfe: Error: No prototype for the call to an anonymous function."
            ),
            vp.CLASS_NO_PROTOTYPE_ANON,
        )
        self.assertEqual(
            vp.classify_diagnostic(
                "cfe: Error: No prototype for the call to func_80000000."
            ),
            vp.CLASS_NO_PROTOTYPE_FUNC,
        )

    def test_only_the_first_cfe_error_is_considered(self) -> None:
        text = (
            "cfe: Error: Syntax Error, expected...\n"
            "cfe: Error: 'D_80000004' undefined; reoccurrences will not be reported."
        )
        self.assertEqual(vp.classify_diagnostic(text), vp.CLASS_SYNTAX)


class LabelVariantTests(unittest.TestCase):
    def test_plain_m2c_label_returns_the_type_spelling(self) -> None:
        self.assertEqual(vp.label_variant("m2c:ptr-void"), "ptr-void")
        self.assertEqual(vp.label_variant("m2c:ptr-void:compile-retry"), "ptr-void")
        self.assertEqual(vp.label_variant("m2c-gotos:s32-s32"), "s32-s32")

    def test_fnptr_cast_suffix_takes_priority_over_the_base_spelling(self) -> None:
        self.assertEqual(vp.label_variant("m2c:u8-void:fnptr-cast"), "fnptr-cast")

    def test_non_m2c_labels_are_not_variants(self) -> None:
        self.assertIsNone(vp.label_variant("manual:hand-written"))
        self.assertIsNone(vp.label_variant("permute:m2c:u8-void"))


class VariantPolicyAggregationTests(unittest.TestCase):
    def test_from_stats_aggregates_attempts_accepted_and_probe_match(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats_path = Path(directory) / "probe-stats.jsonl"
            _write_stats(stats_path, [
                {"attempts": [
                    _attempt("m2c:ptr-void:compile-retry", "compile_failed", "cfe: Error: Unacceptable operand of '+'."),
                    _attempt("m2c:ptr-void:compile-retry", "compile_failed", "cfe: Error: Unacceptable operand of '-'."),
                    _attempt("m2c:u8-void", "accepted"),
                    _attempt("m2c:u8-void", "probe_match"),
                    _attempt("m2c:u8-void", "probe_rejected"),
                ]},
            ])
            policy = vp.VariantPolicy.from_stats(stats_path)

        ptr_void = policy.stats_for("ptr-void", vp.CLASS_POINTER_OPERAND)
        self.assertEqual(ptr_void.attempts, 2)
        self.assertEqual(ptr_void.accepted, 0)
        self.assertEqual(ptr_void.success, 0)

        u8_void = policy.stats_for("u8-void", vp.CLASS_NONE)
        self.assertEqual(u8_void.attempts, 3)
        self.assertEqual(u8_void.accepted, 1)
        self.assertEqual(u8_void.probe_match, 1)
        self.assertEqual(u8_void.success, 2)

    def test_from_stats_merges_multiple_paths(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            first = root / "a.jsonl"
            second = root / "b.jsonl"
            _write_stats(first, [{"attempts": [_attempt("m2c:s32-s32", "compile_failed")]}])
            _write_stats(second, [{"attempts": [_attempt("m2c:s32-s32", "compile_failed")]}])
            policy = vp.VariantPolicy.from_stats([first, second])

        self.assertEqual(policy.stats_for("s32-s32", vp.CLASS_NONE).attempts, 2)

    def test_missing_stats_files_yield_an_empty_but_non_permissive_aggregate(self) -> None:
        # A missing file is not an error, and an empty aggregate still gates
        # exactly like an explicit VariantPolicy({}) would: everything counts
        # as unexplored (0 < min_attempts), so nothing is dropped yet.
        policy = vp.VariantPolicy.from_stats(Path("/nonexistent/probe-stats.jsonl"))
        self.assertEqual(
            policy.allowed_retry_variants(vp.CLASS_POINTER_OPERAND, ["ptr-void"]),
            ("ptr-void",),
        )


class AllowedRetryVariantsTests(unittest.TestCase):
    def test_permissive_policy_allows_everything(self) -> None:
        policy = vp.VariantPolicy.permissive()
        self.assertEqual(
            policy.allowed_retry_variants(vp.CLASS_POINTER_OPERAND, ["ptr-void", "ptr-s32", "u32-void"]),
            ("ptr-void", "ptr-s32", "u32-void"),
        )

    def test_default_policy_is_permissive(self) -> None:
        self.assertEqual(
            vp.DEFAULT_POLICY.allowed_retry_variants(vp.CLASS_POINTER_OPERAND, ["ptr-void"]),
            ("ptr-void",),
        )

    def test_unexplored_variant_is_allowed_regardless_of_class(self) -> None:
        policy = vp.VariantPolicy({("ptr-void", vp.CLASS_POINTER_OPERAND): vp.VariantStats(attempts=5)})
        self.assertEqual(
            policy.allowed_retry_variants(vp.CLASS_POINTER_OPERAND, ["ptr-void"], min_attempts=30),
            ("ptr-void",),
        )

    def test_explored_variant_with_zero_success_is_dropped(self) -> None:
        policy = vp.VariantPolicy({
            ("ptr-void", vp.CLASS_POINTER_OPERAND): vp.VariantStats(attempts=738, accepted=0, probe_match=0),
        })
        self.assertEqual(
            policy.allowed_retry_variants(vp.CLASS_POINTER_OPERAND, ["ptr-void"], min_attempts=30),
            (),
        )

    def test_explored_variant_with_any_success_is_kept(self) -> None:
        policy = vp.VariantPolicy({
            ("s32-s32", vp.CLASS_NONE): vp.VariantStats(attempts=2089, accepted=14, probe_match=198),
        })
        self.assertEqual(
            policy.allowed_retry_variants(vp.CLASS_NONE, ["s32-s32"], min_attempts=30),
            ("s32-s32",),
        )

    def test_gating_is_per_diagnostic_class(self) -> None:
        # The trio has plenty of pointer_operand evidence against it, but no
        # recorded evidence at all for a different class -- it should stay
        # allowed for that other, unexplored class.
        policy = vp.VariantPolicy({
            ("ptr-void", vp.CLASS_POINTER_OPERAND): vp.VariantStats(attempts=419, accepted=0, probe_match=0),
        })
        self.assertEqual(
            policy.allowed_retry_variants(vp.CLASS_POINTER_OPERAND, ["ptr-void"]), (),
        )
        self.assertEqual(
            policy.allowed_retry_variants(vp.CLASS_UNDEFINED, ["ptr-void"]), ("ptr-void",),
        )

    def test_real_probe_stats_evidence_blocks_the_pointer_trio(self) -> None:
        """End-to-end shape of the issue's cited numbers: 738 attempts, 0 wins."""
        with tempfile.TemporaryDirectory() as directory:
            stats_path = Path(directory) / "probe-stats.jsonl"
            records = []
            for _ in range(419):
                records.append({"attempts": [
                    _attempt("m2c:ptr-void:compile-retry", "compile_failed", "cfe: Error: Unacceptable operand of '+'.")
                ]})
            for _ in range(173):
                records.append({"attempts": [
                    _attempt("m2c:ptr-s32:compile-retry", "compile_failed", "cfe: Error: Unacceptable operand of '+'.")
                ]})
            for _ in range(146):
                records.append({"attempts": [
                    _attempt("m2c:u32-void:compile-retry", "compile_failed", "cfe: Error: Unacceptable operand of '+'.")
                ]})
            _write_stats(stats_path, records)
            policy = vp.VariantPolicy.from_stats(stats_path)

        self.assertEqual(
            policy.allowed_retry_variants(
                vp.CLASS_POINTER_OPERAND, ["ptr-void", "ptr-s32", "u32-void"],
            ),
            (),
        )


class DefaultStatsPathsTests(unittest.TestCase):
    def test_only_existing_paths_are_returned_current_first(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            current = root / "probe-stats" / "probe-stats.jsonl"
            legacy = root / "build" / "probe-stats.jsonl"
            with mock.patch.object(vp, "STATS_PATH_CURRENT", current), \
                 mock.patch.object(vp, "STATS_PATH_LEGACY", legacy):
                self.assertEqual(vp.default_stats_paths(), ())

                legacy.parent.mkdir(parents=True)
                legacy.write_text("")
                self.assertEqual(vp.default_stats_paths(), (legacy,))

                current.parent.mkdir(parents=True)
                current.write_text("")
                self.assertEqual(vp.default_stats_paths(), (current, legacy))


if __name__ == "__main__":
    unittest.main()
