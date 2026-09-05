#!/usr/bin/env python3
"""Regression tests for the probe-hardness additions to tools/pragma_targets.py.

Covers issue 1 of 7 (file/owner selection by recorded probe hardness, not
just remaining-owner counts): ``OwnerHardness`` classification,
``load_owner_hardness``'s single-pass aggregation over a synthetic
probe-stats file, ``targets --skip-ties``/the per-owner ``hardness`` field,
and the new ``rank-files`` mode.  Every stats/source fixture here is written
to a tempdir -- the real ``disasm/probe-stats/`` is never touched.
"""

from __future__ import annotations

import json
import os
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

TOOLS = Path(__file__).resolve().parent
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

import pragma_targets as targets  # noqa: E402


def _pragma(function: str) -> str:
    return f'#pragma GLOBAL_ASM("asm/us/nonmatchings/x/{function}.s")\n'


def _write_asm(path: Path, function: str, instruction_count: int) -> None:
    lines = [f"glabel {function}\n"]
    for _ in range(instruction_count - 1):
        lines.append("    /* 0 0 0 */  addiu $t0, $t0, 1\n")
    lines.append("    /* 0 0 0 */  jr $ra\n")
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("".join(lines))


def _write_jump_table_asm(path: Path, function: str, table: str) -> None:
    lines = [
        f"glabel {function}\n",
        f"    /* 0 0 0 */  lui $at, %hi({table})\n",
        "    /* 0 0 0 */  addiu $t0, $t0, 1\n",
        "    /* 0 0 0 */  jr $ra\n",
    ]
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("".join(lines))


def _write_coalesce_asm(path: Path, function: str, sym1: str, sym2: str, *, interleaved: bool) -> None:
    """A shared-``$at`` lui run for ``coalesce_lui``/``scan_coalesce_sites``.

    ``lui $at, %hi(sym1)`` feeding ``sw ..., %lo(sym1)($at)`` then
    ``sw ..., %lo(sym2)($at)`` -- the shape ``scan_coalesce_sites.py``'s
    ``find_shared_at_runs`` looks for. ``interleaved=True`` inserts an
    unrelated instruction between each step, which is exactly what makes
    the run's line indices non-consecutive (``contiguous=False``).
    """
    gap = ["    /* 0 0 0 */  addiu $t2, $t2, 1\n"] if interleaved else []
    lines = [
        f"glabel {function}\n",
        f"    /* 0 0 0 */  lui $at, %hi({sym1})\n",
        *gap,
        f"    /* 0 0 0 */  sw $t0, %lo({sym1})($at)\n",
        *gap,
        f"    /* 0 0 0 */  sw $t1, %lo({sym2})($at)\n",
        "    /* 0 0 0 */  jr $ra\n",
    ]
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("".join(lines))


def _write_symbol_addrs(root: Path, addrs: dict[str, int]) -> None:
    """A minimal ``symbol_addrs*.txt`` fixture ``coalesce_lui.resolve_repo_addresses`` reads."""
    path = root / "disasm" / "linker_scripts" / "us" / "symbol_addrs_code.txt"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("".join(f"{name} = 0x{addr:X};\n" for name, addr in addrs.items()))


def _attempt(
    function: str,
    *,
    status: str = "probe_rejected",
    similarity_score: float | None = None,
    exact_similarity_score: float | None = None,
    mismatch_kind: str | None = None,
) -> dict[str, object]:
    row: dict[str, object] = {"function": function, "status": status, "label": "m2c:test"}
    if similarity_score is not None:
        row["similarity_score"] = similarity_score
    if exact_similarity_score is not None:
        row["exact_similarity_score"] = exact_similarity_score
    if mismatch_kind is not None:
        row["mismatch_kind"] = mismatch_kind
    return row


def _write_stats(path: Path, batches: list[dict[str, object]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as handle:
        for batch in batches:
            handle.write(json.dumps(batch) + "\n")


def _batch(attempts: list[dict[str, object]], *, timestamp: str | None = None, source: str = "s.c") -> dict[str, object]:
    row: dict[str, object] = {"source": source, "attempts": attempts}
    if timestamp is not None:
        row["timestamp"] = timestamp
    return row


class OwnerHardnessLabelTests(unittest.TestCase):
    """Direct classification tests -- no I/O, just the boolean/label logic."""

    def test_no_attempts_is_fresh(self) -> None:
        hardness = targets.OwnerHardness()
        self.assertTrue(hardness.is_fresh)
        self.assertFalse(hardness.is_tie)
        self.assertFalse(hardness.is_drift)
        self.assertFalse(hardness.is_stuck)
        self.assertEqual(hardness.label, "fresh")

    def test_few_attempts_with_drift_kind_is_fresh_and_drift(self) -> None:
        # The 4AC10.c shape: few attempts, a semantic-gap mismatch kind.
        hardness = targets.OwnerHardness(
            prior_attempts=2, best_similarity=0.94, best_mismatch_kind="instruction_drift",
        )
        self.assertTrue(hardness.is_fresh)
        self.assertTrue(hardness.is_drift)
        self.assertFalse(hardness.is_tie)
        # Priority: a recognized drift kind is the more informative label.
        self.assertEqual(hardness.label, "drift")

    def test_many_attempts_register_allocation_tie_at_high_similarity(self) -> None:
        # The 585D0.c shape: many attempts, stuck at a register-allocation tie.
        hardness = targets.OwnerHardness(
            prior_attempts=20, best_similarity=1.0, best_mismatch_kind="register_allocation_only",
        )
        self.assertTrue(hardness.is_tie)
        self.assertFalse(hardness.is_fresh)
        self.assertFalse(hardness.is_drift)
        self.assertEqual(hardness.label, "tie")

    def test_register_allocation_tie_requires_minimum_attempts(self) -> None:
        # Same kind/similarity as above, but only 5 attempts: not yet a tie
        # (below TIE_ATTEMPT_THRESHOLD) and not fresh either (>=5), so it
        # falls to the near-1.0-similarity fallback bucket.
        hardness = targets.OwnerHardness(
            prior_attempts=5, best_similarity=1.0, best_mismatch_kind="register_allocation_only",
        )
        self.assertFalse(hardness.is_tie)
        self.assertFalse(hardness.is_fresh)
        self.assertEqual(hardness.label, "tie")

    def test_many_attempts_low_similarity_is_stuck(self) -> None:
        hardness = targets.OwnerHardness(prior_attempts=15, best_similarity=0.7, best_mismatch_kind="instruction_drift")
        self.assertTrue(hardness.is_stuck)
        self.assertEqual(hardness.label, "stuck")

    def test_many_attempts_never_scored_is_stuck(self) -> None:
        # Every attempt failed to compile; no similarity was ever recorded.
        hardness = targets.OwnerHardness(prior_attempts=18, best_similarity=None, best_mismatch_kind=None)
        self.assertTrue(hardness.is_stuck)
        self.assertEqual(hardness.label, "stuck")

    def test_moderate_attempts_drift_kind_below_1_is_drift(self) -> None:
        hardness = targets.OwnerHardness(
            prior_attempts=8, best_similarity=0.97, best_mismatch_kind="operand_or_scheduling_drift",
        )
        self.assertTrue(hardness.is_drift)
        self.assertEqual(hardness.label, "drift")


class LoadOwnerHardnessTests(unittest.TestCase):
    def test_aggregates_prior_attempts_best_scores_and_last_timestamp(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats = Path(directory) / "probe-stats.jsonl"
            _write_stats(stats, [
                _batch(
                    [
                        _attempt(
                            "func_A", status="probe_rejected", similarity_score=0.80,
                            exact_similarity_score=0.55, mismatch_kind="operand_or_scheduling_drift",
                        ),
                        _attempt("func_B", status="compile_failed"),
                    ],
                    timestamp="2026-08-27T00:00:00Z",
                ),
                _batch(
                    [
                        _attempt(
                            "func_A", status="probe_rejected", similarity_score=0.94,
                            exact_similarity_score=0.90, mismatch_kind="instruction_drift",
                        ),
                        _attempt("func_B", status="compile_failed"),
                    ],
                    timestamp="2026-08-28T00:00:00Z",
                ),
            ])
            hardness = targets.load_owner_hardness(stats)

        self.assertEqual(hardness["func_A"].prior_attempts, 2)
        self.assertEqual(hardness["func_A"].best_similarity, 0.94)
        self.assertEqual(hardness["func_A"].best_raw_similarity, 0.90)
        self.assertEqual(hardness["func_A"].best_mismatch_kind, "instruction_drift")
        self.assertEqual(hardness["func_A"].last_attempt, "2026-08-28T00:00:00Z")

        # func_B never got a similarity score (every attempt compile_failed):
        # still counted as prior attempts, but no best-* fields to report.
        self.assertEqual(hardness["func_B"].prior_attempts, 2)
        self.assertIsNone(hardness["func_B"].best_similarity)
        self.assertIsNone(hardness["func_B"].best_mismatch_kind)
        self.assertEqual(hardness["func_B"].last_attempt, "2026-08-28T00:00:00Z")

    def test_missing_function_defaults_to_empty_hardness(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats = Path(directory) / "probe-stats.jsonl"
            _write_stats(stats, [_batch([_attempt("func_A", similarity_score=0.5)])])
            hardness = targets.load_owner_hardness(stats)
        self.assertNotIn("func_never_probed", hardness)

    def test_picks_up_rotated_sibling_next_to_explicit_stats_path(self) -> None:
        # Mirrors variant_policy.default_stats_paths()/probe_stats.resolve_paths:
        # an explicit --stats path still pulls in its own "<stem>.<N><suffix>"
        # rotated sibling (item 5 of the issue: probe-stats.1.jsonl next to
        # probe-stats.jsonl).
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            active = root / "probe-stats.jsonl"
            rotated = root / "probe-stats.1.jsonl"
            _write_stats(active, [_batch([_attempt("func_A", similarity_score=0.9)])])
            _write_stats(rotated, [_batch([_attempt("func_A", similarity_score=0.99)])])
            hardness = targets.load_owner_hardness(active)
        self.assertEqual(hardness["func_A"].prior_attempts, 2)
        self.assertEqual(hardness["func_A"].best_similarity, 0.99)

    def test_result_is_cached_by_stats_file_mtime(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats = Path(directory) / "probe-stats.jsonl"
            _write_stats(stats, [_batch([_attempt("func_A", similarity_score=0.5)])])
            first = targets.load_owner_hardness(stats)
            second = targets.load_owner_hardness(stats)
            self.assertIs(first, second)

            # Touch with new content -> new mtime -> cache must not stick.
            import time
            time.sleep(0.01)
            _write_stats(stats, [_batch([_attempt("func_A", similarity_score=0.5), _attempt("func_B", similarity_score=0.5)])])
            third = targets.load_owner_hardness(stats)
        self.assertIn("func_B", third)


class ListTargetsHardnessTests(unittest.TestCase):
    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self.root = Path(self._tmp.name)
        self.source_root = self.root / "disasm" / "src"
        self.asm_root = self.root / "disasm" / "asm" / "us" / "nonmatchings"
        self.source_root.mkdir(parents=True)

        (self.source_root / "a.c").write_text(_pragma("func_fresh") + _pragma("func_tie"))
        _write_asm(self.asm_root / "x" / "func_fresh.s", "func_fresh", 6)
        _write_asm(self.asm_root / "x" / "func_tie.s", "func_tie", 6)

        self.stats = self.root / "probe-stats.jsonl"
        _write_stats(self.stats, [
            _batch([
                _attempt(
                    "func_tie", status="probe_rejected", similarity_score=1.0,
                    exact_similarity_score=1.0, mismatch_kind="register_allocation_only",
                )
                for _ in range(8)
            ]),
        ])

    def _list(self, **kwargs):
        # ``owner_index()``/``Owner.asm_path`` default to the module-level
        # ``SOURCE_ROOT``/``REPO_ROOT`` *bound at function-definition time*,
        # so patching those attributes would not reach a zero-argument
        # ``owner_index()`` call inside ``list_targets``.  Patch the function
        # itself with a fixture built via the explicit-argument form instead
        # (as ``TargetDiscoveryTests`` already does), and patch ``REPO_ROOT``
        # only for ``Owner.asm_path``'s own (non-default-argument) lookup.
        index = targets.owner_index(self.source_root, repo_root=self.root, refresh=True)
        with mock.patch.object(targets, "REPO_ROOT", self.root), \
             mock.patch.object(targets, "owner_index", return_value=index), \
             mock.patch.object(targets, "_CLASSIFICATION_CACHE", {}), \
             mock.patch.object(targets, "_COALESCE_CACHE", {}), \
             mock.patch.object(targets, "_HARDNESS_CACHE", {}):
            return targets.list_targets(stats_paths=self.stats, **kwargs)

    def test_owner_rows_carry_hardness_fields(self) -> None:
        result = self._list()
        rows = {row["function"]: row for row in result["targets"]}
        self.assertEqual(rows["func_fresh"]["prior_attempts"], 0)
        self.assertIsNone(rows["func_fresh"]["best_similarity"])
        self.assertEqual(rows["func_fresh"]["hardness"], "fresh")

        self.assertEqual(rows["func_tie"]["prior_attempts"], 8)
        self.assertEqual(rows["func_tie"]["best_similarity"], 1.0)
        self.assertEqual(rows["func_tie"]["best_mismatch_kind"], "register_allocation_only")
        self.assertEqual(rows["func_tie"]["hardness"], "tie")

    def test_skip_ties_hides_tie_owners_only(self) -> None:
        result = self._list(skip_ties=True)
        functions = {row["function"] for row in result["targets"]}
        self.assertEqual(functions, {"func_fresh"})

    def test_classification_cache_is_not_mutated_by_hardness_fields(self) -> None:
        # list_targets must copy _classify_owner's cached row before adding
        # hardness fields onto it, or a second unrelated caller (or a second
        # call with different stats) would see stale/foreign keys leak in.
        self._list()
        for cached_row in targets._CLASSIFICATION_CACHE.values():
            self.assertNotIn("hardness", cached_row)
            self.assertNotIn("prior_attempts", cached_row)


class RankFilesTests(unittest.TestCase):
    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self.root = Path(self._tmp.name)
        self.source_root = self.root / "disasm" / "src"
        self.asm_root = self.root / "disasm" / "asm" / "us" / "nonmatchings"
        self.source_root.mkdir(parents=True)

        # good.c: two owners, both fresh (never attempted) -- the 4AC10.c
        # shape once probed would show fresh+drift; untouched, it is at
        # least fresh, which is exactly what should outrank a heavily
        # tie'd file with the same remaining-owner count.
        (self.source_root / "good.c").write_text(_pragma("func_g1") + _pragma("func_g2"))
        _write_asm(self.asm_root / "x" / "func_g1.s", "func_g1", 6)
        _write_asm(self.asm_root / "x" / "func_g2.s", "func_g2", 6)

        # bad.c: two owners, both long-attempted register-allocation ties --
        # the 585D0.c shape.
        (self.source_root / "bad.c").write_text(_pragma("func_b1") + _pragma("func_b2"))
        _write_asm(self.asm_root / "x" / "func_b1.s", "func_b1", 6)
        _write_asm(self.asm_root / "x" / "func_b2.s", "func_b2", 6)

        # drift.c: four owners with fewer fresh owners than good.c, but more
        # drift signal overall.  The old composite-score ordering put this
        # file first; fresh-owner priority must keep good.c ahead of it.
        drift_functions = [f"func_d{i}" for i in range(1, 5)]
        (self.source_root / "drift.c").write_text("".join(_pragma(function) for function in drift_functions))
        for function in drift_functions:
            _write_asm(self.asm_root / "x" / f"{function}.s", function, 6)

        # big.c: one owner over the instruction cap -- must not be counted.
        (self.source_root / "big.c").write_text(_pragma("func_big"))
        _write_asm(self.asm_root / "x" / "func_big.s", "func_big", 200)

        # A ready and an unready jump-table file exercise the layout-aware
        # ranking.  The ready file has a dotted .rodata subsegment; the
        # unready file is still a valid source file but needs coordinator
        # layout work before a C switch can be probed.
        (self.source_root / "ready.c").write_text(_pragma("func_ready"))
        _write_jump_table_asm(
            self.asm_root / "x" / "func_ready.s", "func_ready", "jtbl_80020000",
        )
        (self.source_root / "blocked.c").write_text(_pragma("func_blocked"))
        _write_jump_table_asm(
            self.asm_root / "x" / "func_blocked.s", "func_blocked", "jtbl_80021000",
        )
        yaml_path = self.root / "disasm" / "yamls" / "us" / "rom.yaml"
        yaml_path.parent.mkdir(parents=True)
        yaml_path.write_text("subsegments:\n    - [0x100, .rodata, ready]\n")

        tie_attempt = _attempt(
            "func_b1", status="probe_rejected", similarity_score=1.0,
            exact_similarity_score=1.0, mismatch_kind="register_allocation_only",
        )
        tie_attempt2 = dict(tie_attempt, function="func_b2")
        drift_attempts = [
            _attempt(
                function, status="probe_rejected", similarity_score=0.97,
                exact_similarity_score=0.90, mismatch_kind="instruction_drift",
            )
            for function in drift_functions
            for _ in range(8)
        ]
        self.stats = self.root / "probe-stats.jsonl"
        _write_stats(self.stats, [
            _batch(
                [dict(tie_attempt) for _ in range(8)]
                + [dict(tie_attempt2) for _ in range(8)]
                + drift_attempts,
            ),
        ])

    def _rank(self, **kwargs):
        # See ListTargetsHardnessTests._list: owner_index()'s default
        # source_root/repo_root are bound at def-time, so patch the function
        # itself with an explicit-argument fixture rather than the globals.
        index = targets.owner_index(self.source_root, repo_root=self.root, refresh=True)
        with mock.patch.object(targets, "REPO_ROOT", self.root), \
             mock.patch.object(targets, "owner_index", return_value=index), \
             mock.patch.object(targets, "_CLASSIFICATION_CACHE", {}), \
             mock.patch.object(targets, "_COALESCE_CACHE", {}), \
             mock.patch.object(targets, "_HARDNESS_CACHE", {}):
            return targets.rank_files(stats_paths=self.stats, repo_root=self.root, **kwargs)

    def test_fresh_file_outranks_tied_file_with_equal_remaining_count(self) -> None:
        result = self._rank(max_instructions=128)
        by_file = {row["file"]: row for row in result["files"]}
        self.assertEqual(by_file["disasm/src/good.c"]["remaining"], 2)
        self.assertEqual(by_file["disasm/src/good.c"]["fresh"], 2)
        self.assertEqual(by_file["disasm/src/good.c"]["drift"], 0)
        self.assertEqual(by_file["disasm/src/good.c"]["ties"], 0)
        self.assertEqual(by_file["disasm/src/good.c"]["score"], 2)

        self.assertEqual(by_file["disasm/src/bad.c"]["remaining"], 2)
        self.assertEqual(by_file["disasm/src/bad.c"]["fresh"], 0)
        self.assertEqual(by_file["disasm/src/bad.c"]["ties"], 2)
        self.assertEqual(by_file["disasm/src/bad.c"]["score"], 0)

        # Fresh-owner priority: good.c must come before bad.c.
        files_in_order = [row["file"] for row in result["files"]]
        self.assertLess(
            files_in_order.index("disasm/src/good.c"), files_in_order.index("disasm/src/bad.c"),
        )

    def test_fresh_count_outranks_drift_count(self) -> None:
        result = self._rank(max_instructions=128)
        by_file = {row["file"]: row for row in result["files"]}

        fresh_file = by_file["disasm/src/good.c"]
        drift_file = by_file["disasm/src/drift.c"]
        self.assertEqual(fresh_file["fresh"], 2)
        self.assertEqual(fresh_file["drift"], 0)
        self.assertEqual(fresh_file["score"], 2)
        self.assertEqual(drift_file["fresh"], 0)
        self.assertEqual(drift_file["drift"], 4)
        self.assertEqual(drift_file["score"], 4)

        files_in_order = [row["file"] for row in result["files"]]
        # Fresh is the primary key: drift.c's larger composite score cannot
        # outrank good.c when it has fewer fresh owners.
        self.assertLess(
            files_in_order.index("disasm/src/good.c"),
            files_in_order.index("disasm/src/drift.c"),
        )

        # Among files with equal fresh counts, retain the old score
        # tie-breaker: drift.c remains ahead of the all-tie bad.c.
        self.assertLess(
            files_in_order.index("disasm/src/drift.c"),
            files_in_order.index("disasm/src/bad.c"),
        )

    def test_oversized_owner_excluded_by_max_instructions(self) -> None:
        result = self._rank(max_instructions=128)
        files = {row["file"] for row in result["files"]}
        self.assertNotIn("disasm/src/big.c", files)

        result_uncapped = self._rank(max_instructions=256)
        files_uncapped = {row["file"] for row in result_uncapped["files"]}
        self.assertIn("disasm/src/big.c", files_uncapped)

    def test_jump_table_readiness_is_reported_and_affects_order(self) -> None:
        result = self._rank(max_instructions=128)
        by_file = {row["file"]: row for row in result["files"]}

        ready = by_file["disasm/src/ready.c"]
        blocked = by_file["disasm/src/blocked.c"]
        self.assertEqual(ready["jump_table_ready"], 1)
        self.assertEqual(ready["jump_table_unready"], 0)
        self.assertEqual(ready["actionable_fresh"], 1)
        self.assertEqual(blocked["jump_table_ready"], 0)
        self.assertEqual(blocked["jump_table_unready"], 1)
        self.assertEqual(blocked["actionable_fresh"], 0)

        files_in_order = [row["file"] for row in result["files"]]
        self.assertLess(
            files_in_order.index("disasm/src/ready.c"),
            files_in_order.index("disasm/src/blocked.c"),
        )


class CoalesceReadinessTests(unittest.TestCase):
    """The ``coalesce_unready``/``schedulable`` signal added alongside jump-table
    readiness: an owner whose ground-truth asm has an *interleaved*
    shared-``$at`` lui run (``scan_coalesce_sites.py``'s own classification,
    reused rather than reimplemented) must never be schedulable, a
    *contiguous* run must not be excluded, and an owner with no such
    pattern at all must be unaffected (``not_applicable``).
    """

    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self.root = Path(self._tmp.name)
        self.source_root = self.root / "disasm" / "src"
        self.asm_root = self.root / "disasm" / "asm" / "us" / "nonmatchings"
        self.source_root.mkdir(parents=True)

        # Two same-%hi-page symbols every fixture below reuses.
        _write_symbol_addrs(self.root, {"D_80100000": 0x80100000, "D_80100004": 0x80100004})

        (self.source_root / "plain.c").write_text(_pragma("func_plain"))
        _write_asm(self.asm_root / "x" / "func_plain.s", "func_plain", 6)

        (self.source_root / "contiguous.c").write_text(_pragma("func_contiguous"))
        _write_coalesce_asm(
            self.asm_root / "x" / "func_contiguous.s", "func_contiguous",
            "D_80100000", "D_80100004", interleaved=False,
        )

        (self.source_root / "interleaved.c").write_text(_pragma("func_interleaved"))
        _write_coalesce_asm(
            self.asm_root / "x" / "func_interleaved.s", "func_interleaved",
            "D_80100000", "D_80100004", interleaved=True,
        )

        self.stats = self.root / "probe-stats.jsonl"
        _write_stats(self.stats, [])

    def _list(self, **kwargs):
        index = targets.owner_index(self.source_root, repo_root=self.root, refresh=True)
        with mock.patch.object(targets, "REPO_ROOT", self.root), \
             mock.patch.object(targets, "owner_index", return_value=index), \
             mock.patch.object(targets, "_CLASSIFICATION_CACHE", {}), \
             mock.patch.object(targets, "_COALESCE_CACHE", {}), \
             mock.patch.object(targets, "_HARDNESS_CACHE", {}):
            return targets.list_targets(stats_paths=self.stats, **kwargs)

    def _rank(self, **kwargs):
        index = targets.owner_index(self.source_root, repo_root=self.root, refresh=True)
        with mock.patch.object(targets, "REPO_ROOT", self.root), \
             mock.patch.object(targets, "owner_index", return_value=index), \
             mock.patch.object(targets, "_CLASSIFICATION_CACHE", {}), \
             mock.patch.object(targets, "_COALESCE_CACHE", {}), \
             mock.patch.object(targets, "_HARDNESS_CACHE", {}):
            return targets.rank_files(stats_paths=self.stats, repo_root=self.root, **kwargs)

    def test_interleaved_owner_is_unready_and_unschedulable(self) -> None:
        rows = {row["function"]: row for row in self._list()["targets"]}
        row = rows["func_interleaved"]
        self.assertEqual(row["coalesce_status"], "unready")
        self.assertTrue(row["coalesce_unready"])
        self.assertFalse(row["coalesce_ready"])
        self.assertFalse(row["schedulable"])

    def test_contiguous_owner_is_ready_and_schedulable(self) -> None:
        # A genuinely-foldable run must never be caught by the same filter
        # that excludes an interleaved one -- a false exclusion here would
        # silently stop real, solvable work.
        rows = {row["function"]: row for row in self._list()["targets"]}
        row = rows["func_contiguous"]
        self.assertEqual(row["coalesce_status"], "ready")
        self.assertTrue(row["coalesce_ready"])
        self.assertFalse(row["coalesce_unready"])
        self.assertTrue(row["schedulable"])

    def test_owner_with_no_coalesce_pattern_is_unaffected(self) -> None:
        rows = {row["function"]: row for row in self._list()["targets"]}
        row = rows["func_plain"]
        self.assertEqual(row["coalesce_status"], "not_applicable")
        self.assertFalse(row["coalesce_unready"])
        self.assertTrue(row["schedulable"])

    def test_rank_files_counts_and_orders_by_coalesce_readiness(self) -> None:
        result = self._rank(max_instructions=128)
        by_file = {row["file"]: row for row in result["files"]}

        contiguous = by_file["disasm/src/contiguous.c"]
        interleaved = by_file["disasm/src/interleaved.c"]
        self.assertEqual(contiguous["coalesce_ready"], 1)
        self.assertEqual(contiguous["coalesce_unready"], 0)
        self.assertEqual(contiguous["actionable_fresh"], 1)
        self.assertEqual(interleaved["coalesce_ready"], 0)
        self.assertEqual(interleaved["coalesce_unready"], 1)
        self.assertEqual(interleaved["actionable_fresh"], 0)

        files_in_order = [row["file"] for row in result["files"]]
        self.assertLess(
            files_in_order.index("disasm/src/contiguous.c"),
            files_in_order.index("disasm/src/interleaved.c"),
        )

    def test_self_correcting_once_the_site_stops_being_interleaved(self) -> None:
        # The task's core requirement: this is never a static snapshot.
        # Nothing but the ground-truth asm's own shape decides the verdict,
        # so rewriting the same owner's .s to close the gap between the
        # lui and its stores (e.g. a coordinator's real re-split moving the
        # scheduled lui back) flips it schedulable again with no code or
        # list changes -- the same live-computed property
        # _rodata_subsegment_owners already gives the jump-table signal.
        blocked = {row["function"]: row for row in self._list()["targets"]}["func_interleaved"]
        self.assertFalse(blocked["schedulable"])

        _write_coalesce_asm(
            self.asm_root / "x" / "func_interleaved.s", "func_interleaved",
            "D_80100000", "D_80100004", interleaved=False,
        )

        fixed = {row["function"]: row for row in self._list()["targets"]}["func_interleaved"]
        self.assertTrue(fixed["schedulable"])
        self.assertEqual(fixed["coalesce_status"], "ready")

    def test_missing_symbol_addrs_degrades_to_not_applicable_never_a_false_exclusion(self) -> None:
        # An owner whose addresses cannot be resolved at all (e.g. this
        # checkout has not generated the symbol map yet) must never be
        # reported unready -- an unresolved signal fails open, exactly like
        # an unimportable disasm/tools module does.
        (self.root / "disasm" / "linker_scripts" / "us" / "symbol_addrs_code.txt").unlink()
        rows = {row["function"]: row for row in self._list()["targets"]}
        row = rows["func_interleaved"]
        self.assertFalse(row["coalesce_unready"])
        self.assertTrue(row["schedulable"])


class RankFilesFragmentsAndRecentTests(unittest.TestCase):
    """``--no-fragments`` and ``--exclude-recent`` against a real git fixture."""

    _GIT_ENV_VARS_TO_STRIP = (
        "GIT_DIR", "GIT_WORK_TREE", "GIT_INDEX_FILE", "GIT_COMMON_DIR",
        "GIT_OBJECT_DIRECTORY", "GIT_ALTERNATE_OBJECT_DIRECTORIES",
    )

    @classmethod
    def _clean_git_env(cls) -> dict:
        env = dict(os.environ)
        for var in cls._GIT_ENV_VARS_TO_STRIP:
            env.pop(var, None)
        return env

    def _git(self, *args: str, extra_env: dict[str, str] | None = None) -> None:
        env = self._clean_git_env()
        if extra_env:
            env.update(extra_env)
        subprocess.run(
            ["git", "-C", str(self.root), *args],
            check=True, capture_output=True, text=True, env=env,
        )

    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self.root = Path(self._tmp.name)
        self.source_root = self.root / "disasm" / "src"
        self.asm_root = self.root / "disasm" / "asm" / "us" / "nonmatchings"
        (self.source_root / "fragments" / "5").mkdir(parents=True)

        self._git("init", "-q", "-b", "main")
        self._git("config", "user.email", "test@example.com")
        self._git("config", "user.name", "Test")

        (self.source_root / "plain.c").write_text(_pragma("func_plain"))
        _write_asm(self.asm_root / "x" / "func_plain.s", "func_plain", 6)
        (self.source_root / "fragments" / "5" / "fragment5_code.c").write_text(_pragma("func_frag"))
        _write_asm(self.asm_root / "x" / "func_frag.s", "func_frag", 6)
        self._git("add", "-A")
        # Backdate the baseline commit well outside any --exclude-recent
        # window used below: without this, both commits land "now" (a
        # fraction of a second apart) and a 4-hour window would catch both,
        # never letting the fragment file (touched only here) prove it
        # survives while plain.c (touched again below) does not.
        old_date = "2020-01-01T00:00:00"
        self._git(
            "commit", "-q", "-m", "baseline",
            extra_env={"GIT_AUTHOR_DATE": old_date, "GIT_COMMITTER_DATE": old_date},
        )

        # Touch plain.c again "now" so only it falls inside a short recency window.
        (self.source_root / "plain.c").write_text(_pragma("func_plain") + "\n")
        self._git("add", "-A")
        self._git("commit", "-q", "-m", "recent touch")

        self.stats = self.root / "probe-stats.jsonl"
        _write_stats(self.stats, [])

    def _rank(self, **kwargs):
        index = targets.owner_index(self.source_root, repo_root=self.root, refresh=True)
        with mock.patch.object(targets, "REPO_ROOT", self.root), \
             mock.patch.object(targets, "owner_index", return_value=index), \
             mock.patch.object(targets, "_CLASSIFICATION_CACHE", {}), \
             mock.patch.object(targets, "_COALESCE_CACHE", {}), \
             mock.patch.object(targets, "_HARDNESS_CACHE", {}):
            return targets.rank_files(stats_paths=self.stats, repo_root=self.root, **kwargs)

    def test_no_fragments_drops_fragment_files(self) -> None:
        result = self._rank(fragments=False)
        files = {row["file"] for row in result["files"]}
        self.assertIn("disasm/src/plain.c", files)
        self.assertNotIn("disasm/src/fragments/5/fragment5_code.c", files)

    def test_fragments_included_by_default(self) -> None:
        result = self._rank()
        files = {row["file"] for row in result["files"]}
        self.assertIn("disasm/src/fragments/5/fragment5_code.c", files)

    def test_exclude_recent_drops_the_just_committed_file(self) -> None:
        result = self._rank(exclude_recent_hours=4.0)
        files = {row["file"] for row in result["files"]}
        self.assertNotIn("disasm/src/plain.c", files)
        # The fragment file was only touched in the baseline commit, not the
        # "recent touch" commit, so it survives the recency filter.
        self.assertIn("disasm/src/fragments/5/fragment5_code.c", files)


if __name__ == "__main__":
    unittest.main()
