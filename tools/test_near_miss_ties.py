#!/usr/bin/env python3
"""Unit tests for the register-tie tooling (issue 7/7):

* ``near_miss_kinds.compute_tie_pool`` -- the threshold logic behind
  ``near_miss_kinds.py tag-ties`` (min attempts, min similarity, mismatch
  kind, the ``accepted``-owner exclusion, the ``permute:``-label-seen flag).
* ``near_miss_kinds.resolve_stats_paths`` -- rotated-sibling inclusion.
* ``sweep_targets.load_targets_file`` -- the pure ``--targets-file`` parser.

All against synthetic stats fixtures in a tempdir; nothing here touches the
real ``disasm/probe-stats`` tree or runs a sweep/permuter.
"""

from __future__ import annotations

import json
import sys
import tempfile
import unittest
from pathlib import Path

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import near_miss_kinds as nmk  # noqa: E402
import sweep_targets  # noqa: E402


def _attempt(
    function: str,
    *,
    label: str = "manual:hand-1",
    status: str = "probe_rejected",
    similarity_score: float = 0.99,
    exact_similarity_score: float = 0.8,
    mismatch_kind: str = "register_allocation_only",
) -> dict[str, object]:
    return {
        "function": function,
        "label": label,
        "status": status,
        "similarity_score": similarity_score,
        "exact_similarity_score": exact_similarity_score,
        "mismatch_kind": mismatch_kind,
        "candidate": f"s32 {function}(void) {{ return 0; }}\n",
    }


def _batch(source: str, attempts: list[dict[str, object]], *, timestamp: str) -> dict[str, object]:
    return {"source": source, "timestamp": timestamp, "attempts": attempts}


class ComputeTiePoolTests(unittest.TestCase):
    def test_min_attempts_threshold(self) -> None:
        # 5 attempts: below the default floor of 6, excluded even though the
        # best attempt is a clean register-allocation tie at 0.995.
        rows = [
            _batch("disasm/src/a.c", [
                _attempt("func_below", similarity_score=0.995, label=f"manual:{i}")
                for i in range(5)
            ], timestamp="2026-08-27T00:00:00Z"),
            # 6 attempts: at the floor, included.
            _batch("disasm/src/a.c", [
                _attempt("func_at_floor", similarity_score=0.995, label=f"manual:{i}")
                for i in range(6)
            ], timestamp="2026-08-27T00:00:00Z"),
        ]
        pool = nmk.compute_tie_pool(rows)
        functions = {row["function"] for row in pool}
        self.assertNotIn("func_below", functions)
        self.assertIn("func_at_floor", functions)

    def test_min_similarity_threshold(self) -> None:
        rows = [
            _batch("disasm/src/a.c", [
                _attempt("func_low_sim", similarity_score=0.97, label=f"manual:{i}")
                for i in range(8)
            ], timestamp="2026-08-27T00:00:00Z"),
        ]
        pool = nmk.compute_tie_pool(rows, min_similarity=0.99)
        self.assertEqual(pool, [])
        pool_loose = nmk.compute_tie_pool(rows, min_similarity=0.9)
        self.assertEqual([row["function"] for row in pool_loose], ["func_low_sim"])

    def test_mismatch_kind_filter(self) -> None:
        rows = [
            _batch("disasm/src/a.c", [
                _attempt(
                    "func_immediate_drift", similarity_score=0.995,
                    mismatch_kind="immediate_drift", label=f"manual:{i}",
                )
                for i in range(6)
            ], timestamp="2026-08-27T00:00:00Z"),
        ]
        pool = nmk.compute_tie_pool(rows)
        self.assertEqual(pool, [])
        pool_other_kind = nmk.compute_tie_pool(rows, kind="immediate_drift")
        self.assertEqual([row["function"] for row in pool_other_kind], ["func_immediate_drift"])

    def test_accepted_owner_excluded(self) -> None:
        attempts = [
            _attempt("func_solved", similarity_score=0.99, label=f"manual:{i}")
            for i in range(5)
        ]
        attempts.append(_attempt("func_solved", similarity_score=1.0, status="accepted", label="manual:6"))
        rows = [_batch("disasm/src/a.c", attempts, timestamp="2026-08-27T00:00:00Z")]
        pool = nmk.compute_tie_pool(rows)
        self.assertEqual(pool, [])

    def test_permuted_flag_true_when_permute_label_seen(self) -> None:
        attempts = [
            _attempt("func_tie", similarity_score=0.99, label=f"manual:{i}")
            for i in range(6)
        ]
        attempts.append(_attempt(
            "func_tie", similarity_score=0.6, status="permute_rejected",
            label="permute:manual:0", mismatch_kind="register_allocation_only",
        ))
        rows = [_batch("disasm/src/a.c", attempts, timestamp="2026-08-27T00:00:00Z")]
        pool = nmk.compute_tie_pool(rows)
        self.assertEqual(len(pool), 1)
        self.assertTrue(pool[0]["permuted"])
        # Total attempt count includes the permute attempt itself.
        self.assertEqual(pool[0]["attempts"], 7)

    def test_permuted_flag_false_when_never_permuted(self) -> None:
        rows = [
            _batch("disasm/src/a.c", [
                _attempt("func_tie", similarity_score=0.99, label=f"manual:{i}")
                for i in range(6)
            ], timestamp="2026-08-27T00:00:00Z"),
        ]
        pool = nmk.compute_tie_pool(rows)
        self.assertEqual(len(pool), 1)
        self.assertFalse(pool[0]["permuted"])

    def test_best_similarity_and_raw_similarity_reported(self) -> None:
        attempts = [
            _attempt("func_tie", similarity_score=0.9, exact_similarity_score=0.5, label="manual:0"),
            # Higher normalized similarity wins as "best", carrying its own
            # (lower) raw score along -- the register-tie signature.
            _attempt("func_tie", similarity_score=0.995, exact_similarity_score=0.82, label="manual:1"),
            _attempt("func_tie", similarity_score=0.93, exact_similarity_score=0.6, label="manual:2"),
        ] * 2  # 6 attempts total
        rows = [_batch("disasm/src/a.c", attempts, timestamp="2026-08-27T00:00:00Z")]
        pool = nmk.compute_tie_pool(rows)
        self.assertEqual(len(pool), 1)
        entry = pool[0]
        self.assertEqual(entry["similarity_score"], 0.995)
        self.assertEqual(entry["exact_similarity_score"], 0.82)
        self.assertEqual(entry["label"], "manual:1")

    def test_last_seen_is_latest_batch_timestamp(self) -> None:
        rows = [
            _batch("disasm/src/a.c", [
                _attempt("func_tie", similarity_score=0.99, label=f"manual:{i}") for i in range(3)
            ], timestamp="2026-08-20T00:00:00Z"),
            _batch("disasm/src/a.c", [
                _attempt("func_tie", similarity_score=0.99, label=f"manual:{i}") for i in range(3, 6)
            ], timestamp="2026-08-27T12:30:00Z"),
        ]
        pool = nmk.compute_tie_pool(rows)
        self.assertEqual(pool[0]["last_seen"], "2026-08-27T12:30:00Z")

    def test_sort_order_attempts_desc_then_similarity_desc_then_name(self) -> None:
        rows = [
            _batch("disasm/src/a.c", [
                _attempt("func_b", similarity_score=0.995, label=f"manual:{i}") for i in range(6)
            ], timestamp="2026-08-27T00:00:00Z"),
            _batch("disasm/src/a.c", [
                _attempt("func_a", similarity_score=0.995, label=f"manual:{i}") for i in range(9)
            ], timestamp="2026-08-27T00:00:00Z"),
            _batch("disasm/src/a.c", [
                _attempt("func_c", similarity_score=0.999, label=f"manual:{i}") for i in range(6)
            ], timestamp="2026-08-27T00:00:00Z"),
        ]
        pool = nmk.compute_tie_pool(rows)
        self.assertEqual([row["function"] for row in pool], ["func_a", "func_c", "func_b"])


class ResolveStatsPathsTests(unittest.TestCase):
    def test_explicit_path_includes_rotated_sibling(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            base = Path(tmp) / "probe-stats.jsonl"
            rotated = Path(tmp) / "probe-stats.1.jsonl"
            base.write_text(json.dumps(_batch(
                "disasm/src/a.c",
                [_attempt("func_new", similarity_score=0.99, label=f"manual:{i}") for i in range(6)],
                timestamp="2026-08-27T00:00:00Z",
            )) + "\n")
            rotated.write_text(json.dumps(_batch(
                "disasm/src/a.c",
                [_attempt("func_old", similarity_score=0.99, label=f"manual:{i}") for i in range(6)],
                timestamp="2026-08-20T00:00:00Z",
            )) + "\n")
            paths = nmk.resolve_stats_paths(base)
            self.assertIn(base, paths)
            self.assertIn(rotated, paths)
            rows = list(nmk.sweep.probe_stats.iter_batches(paths))
            pool = nmk.compute_tie_pool(rows)
            functions = {row["function"] for row in pool}
            self.assertEqual(functions, {"func_new", "func_old"})

    def test_no_stats_path_falls_back_to_defaults(self) -> None:
        # No explicit path: delegates to variant_policy.default_stats_paths(),
        # which returns only files that actually exist -- never raises even
        # in a checkout with no probe-stats history at all.
        paths = nmk.resolve_stats_paths(None)
        self.assertIsInstance(paths, list)


class LoadTargetsFileTests(unittest.TestCase):
    def test_parses_one_name_per_line(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "ties.txt"
            path.write_text("func_8005C0B0\nfunc_8005C12C\nfunc_8005C1AC\n")
            names = sweep_targets.load_targets_file(path)
            self.assertEqual(names, {"func_8005C0B0", "func_8005C12C", "func_8005C1AC"})

    def test_ignores_blank_lines_and_comments(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "ties.txt"
            path.write_text(
                "func_a\n"
                "\n"
                "   \n"
                "# a comment line\n"
                "func_b\n"
                "  # indented comment\n"
            )
            names = sweep_targets.load_targets_file(path)
            self.assertEqual(names, {"func_a", "func_b"})

    def test_strips_surrounding_whitespace(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "ties.txt"
            path.write_text("  func_a  \n\tfunc_b\t\n")
            names = sweep_targets.load_targets_file(path)
            self.assertEqual(names, {"func_a", "func_b"})

    def test_empty_file_returns_empty_set(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "ties.txt"
            path.write_text("")
            self.assertEqual(sweep_targets.load_targets_file(path), set())

    def test_duplicate_names_deduplicated(self) -> None:
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "ties.txt"
            path.write_text("func_a\nfunc_a\nfunc_b\n")
            self.assertEqual(sweep_targets.load_targets_file(path), {"func_a", "func_b"})


class TargetsFileTiePoolMutualExclusionArgparseTests(unittest.TestCase):
    """--targets-file and --tie-pool are mutually exclusive, and both require --near-miss.

    Exercises only ``main()``'s ``parser.error`` guard paths (which call
    ``sys.exit(2)`` without touching the runner/permuter), not a real sweep.
    """

    def test_targets_file_and_tie_pool_together_is_an_error(self) -> None:
        argv = sys.argv
        sys.argv = ["sweep_targets.py", "--near-miss", "--targets-file", "x.txt", "--tie-pool"]
        try:
            with self.assertRaises(SystemExit) as ctx:
                sweep_targets.main()
            self.assertEqual(ctx.exception.code, 2)
        finally:
            sys.argv = argv

    def test_targets_file_without_near_miss_is_an_error(self) -> None:
        argv = sys.argv
        sys.argv = ["sweep_targets.py", "--targets-file", "x.txt"]
        try:
            with self.assertRaises(SystemExit) as ctx:
                sweep_targets.main()
            self.assertEqual(ctx.exception.code, 2)
        finally:
            sys.argv = argv


if __name__ == "__main__":
    unittest.main()
