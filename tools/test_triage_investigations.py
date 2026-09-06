#!/usr/bin/env python3
"""Tests for tools/triage_investigations.py.

Every fixture here is written to a tempdir -- the real
``disasm/probe-stats/`` and ``docs/regions/`` trees are never touched.
Covers each of the three detectors' true-positive and true-negative cases,
the region-notes tie-pool parser, and the dedup/state-tracking machinery.
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

import pragma_targets as targets  # noqa: E402
import triage_investigations as ti  # noqa: E402


# ---------------------------------------------------------------------------
# Fixture helpers (mirrors tools/test_pragma_targets_hardness.py's style)
# ---------------------------------------------------------------------------


def _pragma(function: str) -> str:
    return f'#pragma GLOBAL_ASM("asm/us/nonmatchings/x/{function}.s")\n'


def _write_asm(path: Path, function: str, instruction_count: int = 6) -> None:
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


def _attempt(
    function: str,
    *,
    status: str = "probe_rejected",
    similarity_score: "float | None" = None,
    raw_similarity_score: "float | None" = None,
    mismatch_kind: "str | None" = None,
    label: str = "family:test",
    **extra: object,
) -> dict[str, object]:
    row: dict[str, object] = {"function": function, "status": status, "label": label}
    if similarity_score is not None:
        row["similarity_score"] = similarity_score
    if raw_similarity_score is not None:
        row["raw_similarity_score"] = raw_similarity_score
    if mismatch_kind is not None:
        row["mismatch_kind"] = mismatch_kind
    row.update(extra)
    return row


def _batch(attempts: list[dict], *, timestamp: "str | None" = None, source: str = "s.c") -> dict:
    row: dict[str, object] = {"source": source, "attempts": attempts}
    if timestamp is not None:
        row["timestamp"] = timestamp
    return row


def _write_stats(path: Path, batches: list[dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as handle:
        for batch in batches:
            handle.write(json.dumps(batch) + "\n")


class _StubOwner:
    """A minimal stand-in for pragma_targets.Owner (just the ``.source``
    attribute the detectors read once an owner passes every other check)."""

    def __init__(self, source: str = "disasm/src/stub.c"):
        self.source = source


def _always_live(_function: str) -> _StubOwner:
    """A permissive ``find_owner`` fixture: every function is still a live
    pragma owner. Used by tests that exercise a detector's OWN exclusion
    logic (tie-pool/permuter/score-shape), where "is this owner still
    unresolved" is not what's under test."""
    return _StubOwner()


class _RepoFixture:
    """A synthetic checkout: disasm/src + disasm/asm/us/nonmatchings + rom.yaml."""

    def __init__(self, tmp_root: Path):
        self.root = tmp_root
        self.source_root = self.root / "disasm" / "src"
        self.asm_root = self.root / "disasm" / "asm" / "us" / "nonmatchings"
        self.source_root.mkdir(parents=True)

    def add_plain_owner(self, function: str, source_name: str = "plain.c") -> None:
        path = self.source_root / source_name
        existing = path.read_text() if path.exists() else ""
        path.write_text(existing + _pragma(function))
        _write_asm(self.asm_root / "x" / f"{function}.s", function)

    def add_jump_table_owner(self, function: str, table: str, source_name: str) -> None:
        path = self.source_root / source_name
        existing = path.read_text() if path.exists() else ""
        path.write_text(existing + _pragma(function))
        _write_jump_table_asm(self.asm_root / "x" / f"{function}.s", function, table)

    def write_rom_yaml(self, ready_source_keys: list[str]) -> None:
        yaml_path = self.root / "disasm" / "yamls" / "us" / "rom.yaml"
        yaml_path.parent.mkdir(parents=True, exist_ok=True)
        lines = [f"    - [0x100, .rodata, {key}]\n" for key in ready_source_keys]
        yaml_path.write_text("subsegments:\n" + "".join(lines))

    def owner_index(self):
        return targets.owner_index(self.source_root, repo_root=self.root, refresh=True)


class _RepoFixtureTestCase(unittest.TestCase):
    """Base class wiring the REPO_ROOT/cache patches every real-fixture
    detector test needs (see tools/test_pragma_targets_hardness.py's
    ListTargetsHardnessTests._list for the precedent this mirrors)."""

    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self.fixture = _RepoFixture(Path(self._tmp.name))

    def _patches(self, index):
        return (
            mock.patch.object(targets, "REPO_ROOT", self.fixture.root),
            mock.patch.object(targets, "_CLASSIFICATION_CACHE", {}),
            mock.patch.object(targets, "_RODATA_OWNER_CACHE", {}),
        )


# ---------------------------------------------------------------------------
# load_owner_attempts / _is_permuter_attempt
# ---------------------------------------------------------------------------


class LoadOwnerAttemptsTests(unittest.TestCase):
    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self.stats = Path(self._tmp.name) / "probe-stats.jsonl"

    def test_normalizes_fields_and_groups_by_function(self) -> None:
        _write_stats(self.stats, [
            _batch([
                _attempt("func_A", similarity_score=0.5, raw_similarity_score=0.4, mismatch_kind="instruction_drift"),
                _attempt("func_B", similarity_score=1.0, raw_similarity_score=1.0, mismatch_kind="register_allocation_only"),
            ], timestamp="2026-09-01T00:00:00+00:00", source="disasm/src/x.c"),
            _batch([_attempt("func_A", similarity_score=0.9, raw_similarity_score=0.6, mismatch_kind="instruction_drift")],
                   timestamp="2026-09-02T00:00:00+00:00", source="disasm/src/x.c"),
        ])
        by_owner = ti.load_owner_attempts([self.stats])
        self.assertEqual(len(by_owner["func_A"]), 2)
        self.assertEqual(len(by_owner["func_B"]), 1)
        first = by_owner["func_A"][0]
        self.assertEqual(first["similarity_score"], 0.5)
        self.assertEqual(first["raw_similarity_score"], 0.4)
        self.assertEqual(first["mismatch_kind"], "instruction_drift")
        self.assertEqual(first["source"], "disasm/src/x.c")
        self.assertFalse(first["is_permuter"])

    def test_malformed_rows_are_skipped_not_raised(self) -> None:
        self.stats.write_text('not json\n{"attempts": "not a list"}\n{"attempts": [1, 2]}\n')
        by_owner = ti.load_owner_attempts([self.stats])
        self.assertEqual(by_owner, {})

    def test_permuter_field_marks_attempt(self) -> None:
        _write_stats(self.stats, [_batch([
            _attempt("func_A", similarity_score=0.9, raw_similarity_score=0.5, permute_budget_seconds=60.0),
        ])])
        by_owner = ti.load_owner_attempts([self.stats])
        self.assertTrue(by_owner["func_A"][0]["is_permuter"])

    def test_permuter_exact_label_marks_attempt(self) -> None:
        _write_stats(self.stats, [_batch([
            _attempt("func_A", similarity_score=0.9, raw_similarity_score=0.5, label="permuter:zero"),
            _attempt("func_A", similarity_score=0.9, raw_similarity_score=0.5, label="permute:some-label"),
        ])])
        by_owner = ti.load_owner_attempts([self.stats])
        self.assertTrue(all(attempt["is_permuter"] for attempt in by_owner["func_A"]))

    def test_descriptive_permuter_substring_in_label_is_not_flagged(self) -> None:
        # A hand-written hypothesis merely *named* after the permuter must
        # not count as a real permuter attempt (see the module docstring
        # comment on _PERMUTER_EXACT_LABELS/_PERMUTER_LABEL_PREFIX).
        _write_stats(self.stats, [_batch([
            _attempt("func_A", similarity_score=0.9, raw_similarity_score=0.5,
                      label="call_sequence:permuter-shape:exact"),
        ])])
        by_owner = ti.load_owner_attempts([self.stats])
        self.assertFalse(by_owner["func_A"][0]["is_permuter"])


# ---------------------------------------------------------------------------
# Region-notes tie-pool parsing
# ---------------------------------------------------------------------------


class RegionTiePoolStatusTests(unittest.TestCase):
    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self.docs_root = Path(self._tmp.name) / "docs" / "regions"
        self.docs_root.mkdir(parents=True)

    def _write(self, name: str, text: str) -> None:
        (self.docs_root / name).write_text(text)

    def test_parses_tie_pool_no(self) -> None:
        self._write("a.md", (
            "## 2026-09-01\n\n"
            "func_A: plateau at 0.95 (raw 0.5), mismatch register_allocation_only; "
            "tried families: loop; tie-pool no\n"
        ))
        status = ti.load_region_tie_pool_status(self.docs_root)
        self.assertEqual(status["func_A"], {"ever_yes": False, "last_yes": False})

    def test_parses_tie_pool_yes_and_time_cap_variant(self) -> None:
        self._write("a.md", (
            "## 2026-09-01\n\n"
            "func_A: time cap at 1.0 (raw 0.95) after 2400s, mismatch register_allocation_only; "
            "tried families: loop; tie-pool yes\n"
        ))
        status = ti.load_region_tie_pool_status(self.docs_root)
        self.assertEqual(status["func_A"], {"ever_yes": True, "last_yes": True})

    def test_ever_yes_sticky_across_later_no(self) -> None:
        self._write("a.md", (
            "## 2026-09-01\n\n"
            "func_A: plateau at 1.0 (raw 0.95), mismatch register_allocation_only; "
            "tried families: loop; tie-pool yes\n\n"
            "## 2026-09-02\n\n"
            "func_A: plateau at 0.7 (raw 0.3), mismatch instruction_drift; "
            "tried families: call_sequence; tie-pool no\n"
        ))
        status = ti.load_region_tie_pool_status(self.docs_root)
        self.assertTrue(status["func_A"]["ever_yes"])
        self.assertFalse(status["func_A"]["last_yes"])

    def test_accepted_lines_and_type_conflicts_are_ignored(self) -> None:
        self._write("a.md", (
            "## 2026-09-01\n\n"
            "func_A: matched (family:label), 3 iterations, agent codex\n"
            "TYPE CONFLICT: D_X is extern u8 D_X, not extern u8 D_Y\n"
        ))
        status = ti.load_region_tie_pool_status(self.docs_root)
        self.assertEqual(status, {})

    def test_missing_docs_root_returns_empty(self) -> None:
        status = ti.load_region_tie_pool_status(self.docs_root / "does-not-exist")
        self.assertEqual(status, {})


# ---------------------------------------------------------------------------
# Signature 1: jump-table-shaped rejection
# ---------------------------------------------------------------------------


class JumpTableStaleRejectionTests(_RepoFixtureTestCase):
    def test_stale_past_fix_is_flagged_when_subsegment_now_exists(self) -> None:
        self.fixture.add_jump_table_owner("func_ready", "jtbl_80020000", "ready.c")
        self.fixture.write_rom_yaml(["ready"])
        index = self.fixture.owner_index()
        owners_attempts = {
            "func_ready": [
                {"function": "func_ready", "similarity_score": 1.0, "raw_similarity_score": 1.0,
                 "mismatch_kind": "section_layout_drift", "label": "m2c:switch", "status": "probe_rejected",
                 "timestamp": None, "source": None, "is_permuter": False, "_order": 0},
            ],
        }
        patches = self._patches(index)
        with patches[0], patches[1], patches[2], mock.patch.object(targets, "owner_index", return_value=index):
            findings = ti.detect_jump_table_stale_rejections(
                owners_attempts, find_owner=index.get, repo_root=self.fixture.root,
            )
        self.assertEqual(len(findings), 1)
        finding = findings[0]
        self.assertEqual(finding["owners"], ["func_ready"])
        self.assertEqual(finding["evidence"]["classification"], "stale_past_fix")
        self.assertEqual(finding["evidence"]["jump_table_status"], "ready")

    def test_still_unready_owner_is_not_flagged(self) -> None:
        self.fixture.add_jump_table_owner("func_blocked", "jtbl_80021000", "blocked.c")
        self.fixture.write_rom_yaml([])  # no subsegment for "blocked" -> unready
        index = self.fixture.owner_index()
        owners_attempts = {
            "func_blocked": [
                {"function": "func_blocked", "similarity_score": 1.0, "raw_similarity_score": 1.0,
                 "mismatch_kind": "section_layout_drift", "label": "m2c:switch", "status": "probe_rejected",
                 "timestamp": None, "source": None, "is_permuter": False, "_order": 0},
            ],
        }
        patches = self._patches(index)
        with patches[0], patches[1], patches[2]:
            findings = ti.detect_jump_table_stale_rejections(
                owners_attempts, find_owner=index.get, repo_root=self.fixture.root,
            )
        self.assertEqual(findings, [])

    def test_no_qualifying_attempt_is_not_flagged(self) -> None:
        self.fixture.add_jump_table_owner("func_ready", "jtbl_80020000", "ready.c")
        self.fixture.write_rom_yaml(["ready"])
        index = self.fixture.owner_index()
        # raw similarity below threshold -> does not qualify at all.
        owners_attempts = {
            "func_ready": [
                {"function": "func_ready", "similarity_score": 0.9, "raw_similarity_score": 0.5,
                 "mismatch_kind": "section_layout_drift", "label": "m2c:switch", "status": "probe_rejected",
                 "timestamp": None, "source": None, "is_permuter": False, "_order": 0},
            ],
        }
        patches = self._patches(index)
        with patches[0], patches[1], patches[2]:
            findings = ti.detect_jump_table_stale_rejections(
                owners_attempts, find_owner=index.get, repo_root=self.fixture.root,
            )
        self.assertEqual(findings, [])

    def test_already_resolved_owner_is_skipped(self) -> None:
        # No pragma left for this function at all -- find_owner returns None.
        index = self.fixture.owner_index()
        owners_attempts = {
            "func_gone": [
                {"function": "func_gone", "similarity_score": 1.0, "raw_similarity_score": 1.0,
                 "mismatch_kind": "section_layout_drift", "label": "m2c:switch", "status": "probe_rejected",
                 "timestamp": None, "source": None, "is_permuter": False, "_order": 0},
            ],
        }
        patches = self._patches(index)
        with patches[0], patches[1], patches[2]:
            findings = ti.detect_jump_table_stale_rejections(
                owners_attempts, find_owner=index.get, repo_root=self.fixture.root,
            )
        self.assertEqual(findings, [])

    def test_wrong_mismatch_kind_is_not_flagged(self) -> None:
        self.fixture.add_jump_table_owner("func_ready", "jtbl_80020000", "ready.c")
        self.fixture.write_rom_yaml(["ready"])
        index = self.fixture.owner_index()
        owners_attempts = {
            "func_ready": [
                {"function": "func_ready", "similarity_score": 1.0, "raw_similarity_score": 1.0,
                 "mismatch_kind": "instruction_drift", "label": "m2c:switch", "status": "probe_rejected",
                 "timestamp": None, "source": None, "is_permuter": False, "_order": 0},
            ],
        }
        patches = self._patches(index)
        with patches[0], patches[1], patches[2]:
            findings = ti.detect_jump_table_stale_rejections(
                owners_attempts, find_owner=index.get, repo_root=self.fixture.root,
            )
        self.assertEqual(findings, [])

    def test_no_jump_table_in_current_asm_is_new_occurrence_not_applicable(self) -> None:
        # section_layout_drift recorded, but the owner's *current* assembly
        # has no jump table at all -- classified new_occurrence with an
        # explicit not_applicable status rather than silently mislabeled
        # "stale_past_fix".
        self.fixture.add_plain_owner("func_plain", "plain.c")
        index = self.fixture.owner_index()
        owners_attempts = {
            "func_plain": [
                {"function": "func_plain", "similarity_score": 0.98, "raw_similarity_score": 0.97,
                 "mismatch_kind": "section_layout_drift", "label": "m2c:x", "status": "probe_rejected",
                 "timestamp": None, "source": None, "is_permuter": False, "_order": 0},
            ],
        }
        patches = self._patches(index)
        with patches[0], patches[1], patches[2]:
            findings = ti.detect_jump_table_stale_rejections(
                owners_attempts, find_owner=index.get, repo_root=self.fixture.root,
            )
        self.assertEqual(len(findings), 1)
        self.assertEqual(findings[0]["evidence"]["classification"], "new_occurrence")
        self.assertEqual(findings[0]["evidence"]["jump_table_status"], "not_applicable")
        self.assertFalse(findings[0]["evidence"]["has_jump_table"])


# ---------------------------------------------------------------------------
# Signature 2: register-allocation tie needing permuter escalation
# ---------------------------------------------------------------------------


class RegisterTiePermuterCandidateTests(unittest.TestCase):
    def _owners_attempts(self, attempts):
        result = {}
        for attempt in attempts:
            result.setdefault(attempt["function"], []).append({
                "function": attempt["function"],
                "similarity_score": attempt.get("similarity_score"),
                "raw_similarity_score": attempt.get("raw_similarity_score"),
                "mismatch_kind": attempt.get("mismatch_kind"),
                "label": attempt.get("label", "family:test"),
                "status": attempt.get("status", "probe_rejected"),
                "timestamp": attempt.get("timestamp"),
                "source": attempt.get("source"),
                "is_permuter": attempt.get("is_permuter", False),
                "_order": attempt.get("_order", 0),
            })
        return result

    def test_fresh_untried_tie_is_flagged(self) -> None:
        owners_attempts = self._owners_attempts([
            dict(function="func_841125A4", similarity_score=1.0, raw_similarity_score=0.95,
                 mismatch_kind="register_allocation_only"),
        ])
        findings = ti.detect_register_tie_permuter_candidates(
            owners_attempts, region_tie_pool_status={}, find_owner=_always_live,
        )
        self.assertEqual(len(findings), 1)
        self.assertEqual(findings[0]["owners"], ["func_841125A4"])
        self.assertEqual(findings[0]["evidence"]["best_similarity_score"], 1.0)

    def test_already_tie_pool_escalated_is_not_flagged(self) -> None:
        owners_attempts = self._owners_attempts([
            dict(function="func_A", similarity_score=1.0, raw_similarity_score=0.7,
                 mismatch_kind="register_allocation_only"),
        ])
        findings = ti.detect_register_tie_permuter_candidates(
            owners_attempts,
            region_tie_pool_status={"func_A": {"ever_yes": True, "last_yes": True}},
            find_owner=_always_live,
        )
        self.assertEqual(findings, [])

    def test_already_permuter_tried_is_not_flagged(self) -> None:
        attempts = self._owners_attempts([
            dict(function="func_A", similarity_score=1.0, raw_similarity_score=0.7,
                 mismatch_kind="register_allocation_only"),
        ])
        attempts["func_A"].append({
            "function": "func_A", "similarity_score": 0.9, "raw_similarity_score": 0.4,
            "mismatch_kind": "register_allocation_only", "label": "permuter:zero",
            "status": "permute_rejected", "timestamp": None, "source": None,
            "is_permuter": True, "_order": 1,
        })
        findings = ti.detect_register_tie_permuter_candidates(
            attempts, region_tie_pool_status={}, find_owner=_always_live,
        )
        self.assertEqual(findings, [])

    def test_below_similarity_threshold_is_not_flagged(self) -> None:
        owners_attempts = self._owners_attempts([
            dict(function="func_A", similarity_score=0.90, raw_similarity_score=0.7,
                 mismatch_kind="register_allocation_only"),
        ])
        findings = ti.detect_register_tie_permuter_candidates(
            owners_attempts, region_tie_pool_status={}, find_owner=_always_live,
        )
        self.assertEqual(findings, [])

    def test_best_attempt_not_a_tie_is_not_flagged(self) -> None:
        # The owner's *best* attempt is an ordinary drift near-miss; an
        # earlier, worse register-allocation-only attempt must not leak
        # this owner into the finding set.
        owners_attempts = self._owners_attempts([
            dict(function="func_A", similarity_score=0.80, raw_similarity_score=0.79,
                 mismatch_kind="register_allocation_only"),
            dict(function="func_A", similarity_score=0.97, raw_similarity_score=0.6,
                 mismatch_kind="instruction_drift"),
        ])
        findings = ti.detect_register_tie_permuter_candidates(
            owners_attempts, region_tie_pool_status={}, find_owner=_always_live,
        )
        self.assertEqual(findings, [])

    def test_already_resolved_owner_is_not_flagged(self) -> None:
        # A tie recorded in history for an owner whose GLOBAL_ASM pragma is
        # already gone (decompiled/accepted since) has nothing left to
        # escalate.
        owners_attempts = self._owners_attempts([
            dict(function="func_A", similarity_score=1.0, raw_similarity_score=0.95,
                 mismatch_kind="register_allocation_only"),
        ])
        findings = ti.detect_register_tie_permuter_candidates(
            owners_attempts, region_tie_pool_status={}, find_owner=lambda _f: None,
        )
        self.assertEqual(findings, [])


# ---------------------------------------------------------------------------
# Signature 3: suspicious cross-owner score clustering
# ---------------------------------------------------------------------------


class ScoreClusteringTests(unittest.TestCase):
    def _owners_attempts(self, rows):
        result = {}
        for index, row in enumerate(rows):
            result.setdefault(row["function"], []).append({
                "function": row["function"],
                "similarity_score": row.get("similarity_score"),
                "raw_similarity_score": row.get("raw_similarity_score"),
                "mismatch_kind": row.get("mismatch_kind", "operand_or_scheduling_drift"),
                "label": row.get("label", "family:test"),
                "status": row.get("status", "probe_rejected"),
                "timestamp": row.get("timestamp"),
                "source": row.get("source"),
                "is_permuter": False,
                "_order": index,
            })
        return result

    def test_identical_suspicious_pair_across_two_owners_is_flagged(self) -> None:
        # The real func_84111248/func_841112C8 precedent: 0.8125/0.125.
        owners_attempts = self._owners_attempts([
            dict(function="func_84111248", similarity_score=0.8125, raw_similarity_score=0.125,
                 source="disasm/src/fragments/79/fragment79_37A6E0.c"),
            dict(function="func_841112C8", similarity_score=0.8125, raw_similarity_score=0.125,
                 source="disasm/src/fragments/79/fragment79_37A6E0.c"),
        ])
        same_file_owner = _StubOwner(source="disasm/src/fragments/79/fragment79_37A6E0.c")
        findings = ti.detect_score_clustering(owners_attempts, find_owner=lambda _f: same_file_owner)
        self.assertEqual(len(findings), 1)
        finding = findings[0]
        self.assertEqual(finding["owners"], ["func_84111248", "func_841112C8"])
        self.assertEqual(finding["evidence"]["similarity_score"], 0.8125)
        self.assertEqual(finding["evidence"]["raw_similarity_score"], 0.125)
        self.assertEqual(finding["source"], "disasm/src/fragments/79/fragment79_37A6E0.c")

    def test_shared_pair_that_is_not_suspicious_is_not_flagged(self) -> None:
        # Same pair shared by two owners, but similarity/raw are close
        # together (ratio ~1x) -- an ordinary shared-difficulty near-miss,
        # not a normalized-metric artifact.
        owners_attempts = self._owners_attempts([
            dict(function="func_A", similarity_score=0.60, raw_similarity_score=0.58),
            dict(function="func_B", similarity_score=0.60, raw_similarity_score=0.58),
        ])
        findings = ti.detect_score_clustering(owners_attempts, find_owner=_always_live)
        self.assertEqual(findings, [])

    def test_close_but_not_identical_scores_are_not_flagged(self) -> None:
        owners_attempts = self._owners_attempts([
            dict(function="func_A", similarity_score=0.8125, raw_similarity_score=0.125),
            dict(function="func_B", similarity_score=0.8120, raw_similarity_score=0.125),
        ])
        findings = ti.detect_score_clustering(owners_attempts, find_owner=_always_live)
        self.assertEqual(findings, [])

    def test_single_owner_is_never_a_cluster(self) -> None:
        owners_attempts = self._owners_attempts([
            dict(function="func_A", similarity_score=0.8125, raw_similarity_score=0.125),
        ])
        findings = ti.detect_score_clustering(owners_attempts, find_owner=_always_live)
        self.assertEqual(findings, [])

    def test_uses_best_scoring_attempt_per_owner_not_earliest(self) -> None:
        owners_attempts = self._owners_attempts([
            dict(function="func_A", similarity_score=0.30, raw_similarity_score=0.29, timestamp="2026-09-01T00:00:00+00:00"),
            dict(function="func_A", similarity_score=0.8125, raw_similarity_score=0.125, timestamp="2026-09-02T00:00:00+00:00"),
            dict(function="func_B", similarity_score=0.8125, raw_similarity_score=0.125, timestamp="2026-09-01T00:00:00+00:00"),
        ])
        findings = ti.detect_score_clustering(owners_attempts, find_owner=_always_live)
        self.assertEqual(len(findings), 1)
        self.assertEqual(findings[0]["owners"], ["func_A", "func_B"])

    def test_a_later_lower_scoring_attempt_does_not_erase_the_shared_plateau(self) -> None:
        # The real func_84111248/func_841112C8 precedent, distilled: both
        # owners plateau at the identical (0.8125, 0.125) pair across
        # several batches, then func_A alone gets a handful of later,
        # strictly worse exploratory attempts (a dead-end hypothesis nobody
        # tried against func_B). Picking "most recent by clock time" would
        # silently lose this real cluster; the owner's *best* attempt must
        # win instead.
        owners_attempts = self._owners_attempts([
            dict(function="func_A", similarity_score=0.8125, raw_similarity_score=0.125, timestamp="2026-08-28T00:00:00+00:00"),
            dict(function="func_A", similarity_score=0.5625, raw_similarity_score=0.0938, timestamp="2026-08-29T00:00:00+00:00"),
            dict(function="func_B", similarity_score=0.8125, raw_similarity_score=0.125, timestamp="2026-08-28T00:00:00+00:00"),
        ])
        findings = ti.detect_score_clustering(owners_attempts, find_owner=_always_live)
        self.assertEqual(len(findings), 1)
        self.assertEqual(findings[0]["owners"], ["func_A", "func_B"])
        self.assertEqual(findings[0]["evidence"]["similarity_score"], 0.8125)

    def test_already_resolved_owner_dropped_from_cluster(self) -> None:
        # func_B is already decompiled/accepted (no longer a live pragma
        # owner); the remaining single owner can no longer form a cluster.
        owners_attempts = self._owners_attempts([
            dict(function="func_A", similarity_score=0.8125, raw_similarity_score=0.125),
            dict(function="func_B", similarity_score=0.8125, raw_similarity_score=0.125),
        ])
        findings = ti.detect_score_clustering(
            owners_attempts,
            find_owner=lambda function: _StubOwner() if function == "func_A" else None,
        )
        self.assertEqual(findings, [])


# ---------------------------------------------------------------------------
# State / dedup
# ---------------------------------------------------------------------------


class AcceptedFunctionsTests(unittest.TestCase):
    def test_detects_any_accepted_attempt(self) -> None:
        owners_attempts = {
            "func_A": [
                {"function": "func_A", "similarity_score": 0.8, "raw_similarity_score": 0.7,
                 "mismatch_kind": "instruction_drift", "label": None, "status": "probe_rejected",
                 "timestamp": None, "source": None, "is_permuter": False, "_order": 0},
                {"function": "func_A", "similarity_score": None, "raw_similarity_score": None,
                 "mismatch_kind": None, "label": None, "status": "accepted",
                 "timestamp": None, "source": None, "is_permuter": False, "_order": 1},
            ],
            "func_B": [
                {"function": "func_B", "similarity_score": 0.8, "raw_similarity_score": 0.7,
                 "mismatch_kind": "instruction_drift", "label": None, "status": "probe_rejected",
                 "timestamp": None, "source": None, "is_permuter": False, "_order": 0},
            ],
        }
        self.assertEqual(ti.accepted_functions(owners_attempts), {"func_A"})

    def test_run_scan_excludes_owner_accepted_in_the_ledger_even_if_pragma_still_live(self) -> None:
        # The real func_84111248/func_841112C8/func_841125A4 precedent: the
        # shared ledger recorded an acceptance before the merge that removes
        # the GLOBAL_ASM pragma reached this checkout. find_owner() alone
        # (still live on disk) must not be enough to keep flagging it.
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        root = Path(tmp.name)
        stats = root / "probe-stats.jsonl"
        _write_stats(stats, [_batch([
            _attempt("func_A", similarity_score=0.8125, raw_similarity_score=0.125),
            _attempt("func_B", similarity_score=0.8125, raw_similarity_score=0.125),
            _attempt("func_A", status="accepted"),
        ])])
        report = ti.run_scan(
            repo_root=root,
            stats_paths=[stats],
            docs_root=root / "docs" / "regions",
            state_path=root / "triage_state.json",
            find_owner=_always_live,
        )
        self.assertEqual(report["findings"], [])


class StateDedupTests(unittest.TestCase):
    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self.root = Path(self._tmp.name)
        self.stats = self.root / "probe-stats.jsonl"
        self.state_path = self.root / "triage_state.json"
        self.docs_root = self.root / "docs" / "regions"

    def _scan(self, **kwargs):
        return ti.run_scan(
            repo_root=self.root,
            stats_paths=[self.stats],
            docs_root=self.docs_root,
            state_path=self.state_path,
            find_owner=_always_live,
            **kwargs,
        )

    def test_repeat_scan_suppresses_unchanged_finding(self) -> None:
        _write_stats(self.stats, [_batch([
            _attempt("func_A", similarity_score=0.8125, raw_similarity_score=0.125),
            _attempt("func_B", similarity_score=0.8125, raw_similarity_score=0.125),
        ])])
        first = self._scan()
        self.assertEqual(len(first["findings"]), 1)
        self.assertFalse(first["findings"][0]["seen"])

        second = self._scan()
        self.assertEqual(second["findings"], [])
        self.assertEqual(second["suppressed_seen"], 1)

    def test_include_seen_shows_suppressed_finding_again(self) -> None:
        _write_stats(self.stats, [_batch([
            _attempt("func_A", similarity_score=0.8125, raw_similarity_score=0.125),
            _attempt("func_B", similarity_score=0.8125, raw_similarity_score=0.125),
        ])])
        self._scan()
        second = self._scan(include_seen=True)
        self.assertEqual(len(second["findings"]), 1)
        self.assertTrue(second["findings"][0]["seen"])

    def test_meaningfully_changed_data_is_reported_again(self) -> None:
        _write_stats(self.stats, [_batch([
            _attempt("func_A", similarity_score=0.8125, raw_similarity_score=0.125),
            _attempt("func_B", similarity_score=0.8125, raw_similarity_score=0.125),
        ])])
        self._scan()
        # A fresh attempt lands for func_B changing its most-recent pair --
        # the cluster's evidence (and fingerprint) changes accordingly.
        _write_stats(self.stats, [
            _batch([
                _attempt("func_A", similarity_score=0.8125, raw_similarity_score=0.125),
                _attempt("func_B", similarity_score=0.8125, raw_similarity_score=0.125),
            ], timestamp="2026-09-01T00:00:00+00:00"),
            _batch([
                _attempt("func_B", similarity_score=0.95, raw_similarity_score=0.10),
            ], timestamp="2026-09-02T00:00:00+00:00"),
        ])
        third = self._scan()
        # The old cluster no longer exists (func_B moved on); nothing to
        # report and nothing wrongly suppressed either.
        self.assertEqual(third["findings"], [])

    def test_reset_state_forces_redisplay(self) -> None:
        _write_stats(self.stats, [_batch([
            _attempt("func_A", similarity_score=0.8125, raw_similarity_score=0.125),
            _attempt("func_B", similarity_score=0.8125, raw_similarity_score=0.125),
        ])])
        self._scan()
        reset = self._scan(reset_state=True)
        self.assertEqual(len(reset["findings"]), 1)
        self.assertFalse(reset["findings"][0]["seen"])

    def test_state_file_persists_across_runs(self) -> None:
        _write_stats(self.stats, [_batch([
            _attempt("func_A", similarity_score=0.8125, raw_similarity_score=0.125),
            _attempt("func_B", similarity_score=0.8125, raw_similarity_score=0.125),
        ])])
        self._scan()
        self.assertTrue(self.state_path.exists())
        state = json.loads(self.state_path.read_text())
        self.assertEqual(len(state), 1)


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------


class CliTests(unittest.TestCase):
    """End-to-end argument-parsing/output-format smoke tests.

    ``main()`` has no dependency-injection hook for ``find_owner`` (nor
    should it -- that's a detector-internals seam, not a CLI concept), so
    these use a real ``_RepoFixture`` with real pragma owners and patch
    ``pragma_targets``'s globals the same way the other real-fixture tests
    do, rather than weakening the assertions to avoid owner resolution.
    """

    def setUp(self) -> None:
        self._tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self._tmp.cleanup)
        self.fixture = _RepoFixture(Path(self._tmp.name))
        self.fixture.add_plain_owner("func_A", "shared.c")
        self.fixture.add_plain_owner("func_B", "shared.c")
        self.stats = self.fixture.root / "probe-stats.jsonl"
        self.state_path = self.fixture.root / "triage_state.json"
        self.docs_root = self.fixture.root / "docs" / "regions"
        _write_stats(self.stats, [_batch([
            _attempt("func_A", similarity_score=0.8125, raw_similarity_score=0.125),
            _attempt("func_B", similarity_score=0.8125, raw_similarity_score=0.125),
        ])])

    def _run_cli(self, argv):
        index = self.fixture.owner_index()
        import contextlib
        import io
        with mock.patch.object(targets, "REPO_ROOT", self.fixture.root), \
             mock.patch.object(targets, "owner_index", return_value=index), \
             mock.patch.object(targets, "_CLASSIFICATION_CACHE", {}), \
             mock.patch.object(targets, "_RODATA_OWNER_CACHE", {}), \
             contextlib.redirect_stdout(io.StringIO()) as out:
            code = ti.main(argv)
        return code, out.getvalue()

    def test_scan_json_output_is_parseable(self) -> None:
        argv = [
            "scan", "--json",
            "--repo-root", str(self.fixture.root),
            "--stats", str(self.stats),
            "--state", str(self.state_path),
            "--docs-root", str(self.docs_root),
        ]
        code, stdout = self._run_cli(argv)
        self.assertEqual(code, 0)
        report = json.loads(stdout)
        self.assertEqual(len(report["findings"]), 1)
        self.assertEqual(report["findings"][0]["signature"], "score_clustering")

    def test_scan_table_output_does_not_crash(self) -> None:
        argv = [
            "scan", "--table",
            "--repo-root", str(self.fixture.root),
            "--stats", str(self.stats),
            "--state", str(self.state_path),
            "--docs-root", str(self.docs_root),
        ]
        code, out = self._run_cli(argv)
        self.assertEqual(code, 0)
        self.assertIn("triage scan:", out)


if __name__ == "__main__":
    unittest.main()
