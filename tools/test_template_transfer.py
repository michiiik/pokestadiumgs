#!/usr/bin/env python3
"""Focused regression tests for the template-transfer candidate generator."""

from __future__ import annotations

import os
import tempfile
import unittest
from pathlib import Path
from unittest import mock

import pragma_targets as targets
import s1_transfer_sweep as sweep
import sweep_targets
import template_transfer

# Synthetic transactions must never land in the real stats file.
_STATS_ISOLATION = mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": ""})


def setUpModule() -> None:
    _STATS_ISOLATION.start()


def tearDownModule() -> None:
    _STATS_ISOLATION.stop()


# --------------------------------------------------------------------------
# Shared synthetic fixtures
#
# Two same-shape wrapper functions: adjust the stack, load the address of a
# global via lui/addiu (%hi/%lo), call a callee, load a plain immediate,
# restore the stack, return.  ``func_target`` (the pragma being solved) and
# ``func_winner`` (a previously accepted candidate) differ only in which
# global/callee they reference and in the plain immediate's value -- exactly
# the shape a template transfer is meant to close.
# --------------------------------------------------------------------------

TARGET_ASM = (
    "glabel func_target\n"
    "    /* 000000 80001000 27BDFFE8 */  addiu $sp, $sp, -0x18\n"
    "    /* 000004 80001004 3C048008 */  lui   $a0, %hi(NewGlobal)\n"
    "    /* 000008 80001008 24845678 */  addiu $a0, $a0, %lo(NewGlobal)\n"
    "    /* 00000C 8000100C 0C002000 */  jal   NewCallee\n"
    "    /* 000010 80001010 24050020 */   addiu $a1, $zero, 0x20\n"
    "    /* 000014 80001014 27BD0018 */  addiu $sp, $sp, 0x18\n"
    "    /* 000018 80001018 03E00008 */  jr    $ra\n"
    "    /* 00001C 8000101C 00000000 */   nop\n"
)

WINNER_ASM = (
    "glabel func_winner\n"
    "    /* 000000 80002000 27BDFFE8 */  addiu $sp, $sp, -0x18\n"
    "    /* 000004 80002004 3C049001 */  lui   $a0, %hi(OldGlobal)\n"
    "    /* 000008 80002008 24841234 */  addiu $a0, $a0, %lo(OldGlobal)\n"
    "    /* 00000C 8000200C 0C002500 */  jal   OldCallee\n"
    "    /* 000010 80002010 24050018 */   addiu $a1, $zero, 0x18\n"
    "    /* 000014 80002014 27BD0018 */  addiu $sp, $sp, 0x18\n"
    "    /* 000018 80002018 03E00008 */  jr    $ra\n"
    "    /* 00001C 8000201C 00000000 */   nop\n"
)

WINNER_CODE = (
    "extern s32 OldGlobal;\n"
    "\n"
    "s32 func_winner(void) {\n"
    "    OldCallee(&OldGlobal, 0x18);\n"
    "    return 0;\n"
    "}\n"
)


def _parsed(asm_text: str) -> sweep.ParsedAsm:
    return sweep.parse_gs_asm(asm_text)


class AlignAndMapTest(unittest.TestCase):
    def test_symbol_rename_maps_jal_and_hilo(self) -> None:
        rename_map, immediates, ok, inconsistent, notes = template_transfer.align_and_map(
            _parsed(TARGET_ASM), _parsed(WINNER_ASM), "func_winner", "func_target", WINNER_CODE,
        )
        self.assertTrue(ok)
        self.assertFalse(inconsistent)
        self.assertEqual(rename_map["func_winner"], "func_target")
        self.assertEqual(rename_map["OldGlobal"], "NewGlobal")
        self.assertEqual(rename_map["OldCallee"], "NewCallee")
        # The plain immediate (0x18 -> 0x20) is reported as an immediate
        # substitution, not folded into the rename map.
        self.assertEqual(len(immediates), 1)
        self.assertEqual(immediates[0]["winner_value"], 0x18)
        self.assertEqual(immediates[0]["target_value"], 0x20)
        self.assertTrue(immediates[0]["located"])
        self.assertEqual(immediates[0]["spelling"], "0x18")
        self.assertEqual(immediates[0]["replacement"], "0x20")
        self.assertEqual(notes, [])

    def test_inconsistent_rename_detected(self) -> None:
        # Two winner instructions both name OldGlobal via %hi/%lo, but the
        # target names a *different* symbol at each of those indices.
        target = _parsed(
            "glabel func_target\n"
            "    /* 000000 80001000 3C048008 */  lui   $a0, %hi(FirstGlobal)\n"
            "    /* 000004 80001004 24845678 */  addiu $a0, $a0, %lo(FirstGlobal)\n"
            "    /* 000008 80001008 3C058009 */  lui   $a1, %hi(SecondGlobal)\n"
            "    /* 00000C 8000100C 24a51234 */  addiu $a1, $a1, %lo(SecondGlobal)\n"
        )
        winner = _parsed(
            "glabel func_winner\n"
            "    /* 000000 80002000 3C049001 */  lui   $a0, %hi(SharedGlobal)\n"
            "    /* 000004 80002004 24849abc */  addiu $a0, $a0, %lo(SharedGlobal)\n"
            "    /* 000008 80002008 3C059002 */  lui   $a1, %hi(SharedGlobal)\n"
            "    /* 00000C 8000200C 24a5def0 */  addiu $a1, $a1, %lo(SharedGlobal)\n"
        )
        rename_map, immediates, ok, inconsistent, notes = template_transfer.align_and_map(
            target, winner, "func_winner", "func_target", "",
        )
        self.assertTrue(inconsistent)
        self.assertTrue(any("maps to both" in note for note in notes))

    def test_target_missing_symbol_fails_alignment(self) -> None:
        # Winner names a %hi/%lo symbol; target's instruction at the same
        # index carries a plain (non-symbol) immediate instead.
        target = _parsed(
            "glabel func_target\n"
            "    /* 000000 80001000 3C048008 */  lui   $a0, 0x8008\n"
            "    /* 000004 80001004 24845678 */  addiu $a0, $a0, 0x5678\n"
        )
        winner = _parsed(
            "glabel func_winner\n"
            "    /* 000000 80002000 3C049001 */  lui   $a0, %hi(OldGlobal)\n"
            "    /* 000004 80002004 24841234 */  addiu $a0, $a0, %lo(OldGlobal)\n"
        )
        _, _, ok, inconsistent, notes = template_transfer.align_and_map(
            target, winner, "func_winner", "func_target", "",
        )
        self.assertFalse(ok)
        self.assertFalse(inconsistent)
        self.assertTrue(any("no symbol operand" in note for note in notes))

    def test_branch_offset_difference_is_ignored(self) -> None:
        target = _parsed(
            "glabel func_target\n"
            "    /* 000000 80001000 10400003 */  beq  $v0, $zero, .L80001010\n"
        )
        winner = _parsed(
            "glabel func_winner\n"
            "    /* 000000 80002000 10400007 */  beq  $v0, $zero, .L80002020\n"
        )
        rename_map, immediates, ok, inconsistent, notes = template_transfer.align_and_map(
            target, winner, "func_winner", "func_target", "",
        )
        self.assertTrue(ok)
        self.assertFalse(inconsistent)
        self.assertEqual(immediates, [])
        self.assertEqual(notes, [])

    def test_unhandled_opcode_difference_fails_alignment(self) -> None:
        # A `lui` with a bare (non-%hi) constant that differs is not a
        # relocation, a branch, or a literal-bearing op in this module's
        # list -- nothing here can safely rename or substitute it.
        target = _parsed(
            "glabel func_target\n"
            "    /* 000000 80001000 3C048008 */  lui  $a0, 0x8008\n"
        )
        winner = _parsed(
            "glabel func_winner\n"
            "    /* 000000 80002000 3C049001 */  lui  $a0, 0x9001\n"
        )
        _, _, ok, inconsistent, notes = template_transfer.align_and_map(
            target, winner, "func_winner", "func_target", "",
        )
        self.assertFalse(ok)
        self.assertFalse(inconsistent)
        self.assertTrue(any("unhandled opcode difference" in note for note in notes))


class ImmediateSubstitutionTest(unittest.TestCase):
    def test_locates_unique_literal_and_substitutes(self) -> None:
        target = _parsed(
            "glabel func_target\n"
            "    /* 000000 80001000 24050020 */  addiu $a1, $zero, 0x20\n"
        )
        winner = _parsed(
            "glabel func_winner\n"
            "    /* 000000 80002000 24050018 */  addiu $a1, $zero, 0x18\n"
        )
        body = "void func_winner(void) { Call(0x18); }\n"
        _, immediates, ok, inconsistent, _ = template_transfer.align_and_map(
            target, winner, "func_winner", "func_target", body,
        )
        self.assertTrue(ok)
        self.assertFalse(inconsistent)
        self.assertTrue(immediates[0]["located"])
        rewritten = template_transfer._apply_immediates(body, immediates)
        self.assertIn("Call(0x20)", rewritten)
        self.assertNotIn("0x18", rewritten)

    def test_unlocated_when_literal_is_not_uniquely_present(self) -> None:
        target = _parsed(
            "glabel func_target\n"
            "    /* 000000 80001000 24050020 */  addiu $a1, $zero, 0x20\n"
        )
        winner = _parsed(
            "glabel func_winner\n"
            "    /* 000000 80002000 24050018 */  addiu $a1, $zero, 0x18\n"
        )
        # 0x18 never appears in the body at all.
        body = "void func_winner(void) { Call(99); }\n"
        _, immediates, ok, inconsistent, notes = template_transfer.align_and_map(
            target, winner, "func_winner", "func_target", body,
        )
        # Alignment itself still succeeds -- an unlocated immediate is a
        # diagnostic, not an alignment failure -- but it must not be
        # silently substituted.
        self.assertTrue(ok)
        self.assertFalse(inconsistent)
        self.assertFalse(immediates[0]["located"])
        self.assertTrue(any("not uniquely located" in note for note in notes))
        rewritten = template_transfer._apply_immediates(body, immediates)
        self.assertEqual(rewritten, body)

    def test_unlocated_when_literal_appears_more_than_once(self) -> None:
        target = _parsed(
            "glabel func_target\n"
            "    /* 000000 80001000 24050020 */  addiu $a1, $zero, 0x20\n"
        )
        winner = _parsed(
            "glabel func_winner\n"
            "    /* 000000 80002000 24050018 */  addiu $a1, $zero, 0x18\n"
        )
        body = "void func_winner(void) { Call(0x18); CallAgain(0x18); }\n"
        _, immediates, *_ = template_transfer.align_and_map(
            target, winner, "func_winner", "func_target", body,
        )
        self.assertFalse(immediates[0]["located"])


class GenerateTemplateCandidatesTest(unittest.TestCase):
    def _owner(self) -> targets.Owner:
        return targets.Owner("func_target", "disasm/src/wrapper.c", "asm/us/nonmatchings/wrapper/func_target.s")

    def test_declarations_are_renamed_and_split(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            winner_path = Path(directory) / "func_winner.s"
            winner_path.write_text(WINNER_ASM)
            row = {
                "function": "func_winner", "similarity": 0.95, "same_length": True,
                "label": "m2c:s32-s32", "code": WINNER_CODE,
            }
            with mock.patch.object(
                targets, "require_owner", return_value=self._owner()
            ), mock.patch.object(
                sweep, "gs_asm_text", return_value=(TARGET_ASM, "worktree")
            ), mock.patch.object(
                template_transfer, "find_templates", return_value=[row]
            ), mock.patch.object(
                template_transfer, "winner_asm_index", return_value={"func_winner": winner_path}
            ):
                candidates = template_transfer.generate_template_candidates("func_target")

        self.assertEqual(len(candidates), 1)
        candidate = candidates[0]
        self.assertEqual(candidate.outcome, "candidate")
        self.assertEqual(candidate.label, "template:func_winner:0.95")
        self.assertEqual(candidate.declarations, "extern s32 NewGlobal;\n")
        self.assertIn("func_target", candidate.code)
        self.assertIn("NewCallee(&NewGlobal, 0x20)", candidate.code)
        self.assertNotIn("OldGlobal", candidate.code)
        self.assertNotIn("OldCallee", candidate.code)
        self.assertEqual(candidate.rename_map["func_winner"], "func_target")

    def test_winner_asm_missing_is_reported(self) -> None:
        row = {
            "function": "func_winner", "similarity": 0.95, "same_length": True,
            "label": "m2c:s32-s32", "code": WINNER_CODE,
        }
        with mock.patch.object(
            targets, "require_owner", return_value=self._owner()
        ), mock.patch.object(
            sweep, "gs_asm_text", return_value=(TARGET_ASM, "worktree")
        ), mock.patch.object(
            template_transfer, "find_templates", return_value=[row]
        ), mock.patch.object(
            template_transfer, "winner_asm_index", return_value={}
        ):
            candidates = template_transfer.generate_template_candidates("func_target")
        self.assertEqual(candidates[0].outcome, "winner_asm_missing")

    def test_target_asm_missing_is_reported(self) -> None:
        with mock.patch.object(
            targets, "require_owner", return_value=self._owner()
        ), mock.patch.object(sweep, "gs_asm_text", return_value=None):
            candidates = template_transfer.generate_template_candidates("func_target")
        self.assertEqual(len(candidates), 1)
        self.assertEqual(candidates[0].outcome, "winner_asm_missing")

    def test_find_templates_filters_by_same_length_and_minimum(self) -> None:
        rows = [
            {"function": "func_short", "similarity": 0.99, "same_length": False, "label": "x", "code": ""},
            {"function": "func_exact", "similarity": 0.92, "same_length": True, "label": "x", "code": ""},
        ]
        with mock.patch.object(targets, "similar_solved", return_value=rows) as similar:
            result = template_transfer.find_templates("func_target", limit=3, minimum=0.9)
        self.assertEqual([row["function"] for row in result], ["func_exact"])
        self.assertEqual(similar.call_args.kwargs["minimum"], 0.9)


class DriverProbeThenGateTest(unittest.TestCase):
    def test_probes_then_gates_only_probe_matches(self) -> None:
        candidate_a = template_transfer.TemplateCandidate(
            function="func_a", label="template:winner_a:0.95", code="s32 func_a(void) { return 1; }\n",
            declarations="", rename_map={}, immediates=[], outcome="candidate",
        )
        candidate_b = template_transfer.TemplateCandidate(
            function="func_b", label="template:winner_b:0.93", code="s32 func_b(void) { return 2; }\n",
            declarations="", rename_map={}, immediates=[], outcome="candidate",
        )
        owner_a = targets.Owner("func_a", "disasm/src/wrapper.c", "asm/us/nonmatchings/wrapper/func_a.s")
        owner_b = targets.Owner("func_b", "disasm/src/wrapper.c", "asm/us/nonmatchings/wrapper/func_b.s")
        calls: list[bool] = []

        def fake_try_candidates(source_path, blocks, *, labels=None, declarations=None, gate=True, probe_workers=None):
            calls.append(gate)
            if not gate:
                return {
                    "attempts": [
                        {"index": 0, "function": "func_a", "status": "probe_match"},
                        {"index": 1, "function": "func_b", "status": "probe_rejected"},
                    ],
                    "accepted": [],
                }
            self.assertEqual(len(blocks), 1)
            self.assertEqual(blocks[0][0], "func_a")
            return {"attempts": [{"index": 0, "function": "func_a", "status": "accepted"}], "accepted": ["func_a"]}

        with mock.patch.object(
            targets, "owner_index", return_value={"func_a": owner_a, "func_b": owner_b},
        ), mock.patch.object(
            template_transfer.dedupe_externs, "dirty_sources", return_value=set(),
        ), mock.patch.object(
            template_transfer, "generate_template_candidates",
            side_effect=lambda function, **kwargs: [candidate_a if function == "func_a" else candidate_b],
        ), mock.patch.object(
            template_transfer.runner, "try_candidates_detailed", side_effect=fake_try_candidates,
        ):
            result = template_transfer.sweep(["func_a", "func_b"], gate=True, workers=1)

        self.assertEqual(calls, [False, True])
        self.assertEqual(result["accepted"], ["func_a"])
        self.assertEqual(result["outcome_counts"], {"candidate": 2})


class DryRunNoRunnerTest(unittest.TestCase):
    def test_dry_run_never_calls_the_runner(self) -> None:
        owner = targets.Owner("func_a", "disasm/src/wrapper.c", "asm/us/nonmatchings/wrapper/func_a.s")
        candidate = template_transfer.TemplateCandidate(
            function="func_a", label="template:winner_a:0.95", code="s32 func_a(void) { return 1; }\n",
            declarations="", rename_map={"winner_a": "func_a"}, immediates=[], outcome="candidate",
        )

        def fail_if_called(*args, **kwargs):
            raise AssertionError("dry-run must never call the runner")

        with mock.patch.object(
            targets, "owner_index", return_value={"func_a": owner},
        ), mock.patch.object(
            template_transfer, "generate_template_candidates", return_value=[candidate],
        ), mock.patch.object(
            template_transfer.runner, "try_candidates_detailed", side_effect=fail_if_called,
        ):
            result = template_transfer.dry_run(["func_a"])

        self.assertEqual(result["outcome_counts"], {"candidate": 1})
        self.assertEqual(result["rows"][0]["function"], "func_a")
        self.assertEqual(result["rows"][0]["candidates"][0]["rename_map_size"], 1)


class SweepTargetsTemplatesOrderingTest(unittest.TestCase):
    def test_templates_prepend_ahead_of_m2c_labels(self) -> None:
        rows = [
            {"function": "func_a", "source": "disasm/src/fragments/1/a.c", "family": "call_sequence"},
        ]
        template_candidate = template_transfer.TemplateCandidate(
            function="func_a", label="template:func_done:0.95", code="s32 func_a(void) { return 1; }\n",
            declarations="", rename_map={"func_done": "func_a"}, immediates=[], outcome="candidate",
        )
        captured: dict[str, object] = {}

        def fake_try_candidates(source_path, blocks, *, labels=None, declarations=None, gate=True, probe_workers=None):
            captured["labels"] = list(labels or [])
            return {"status": 1, "accepted": [], "attempts": [], "batch_status": "no_candidate_accepted"}

        with mock.patch.object(
            sweep_targets.targets, "list_targets",
            return_value={"matched": 1, "targets": rows, "truncated": False},
        ), mock.patch.object(
            sweep_targets.dedupe_externs, "dirty_sources", return_value=set(),
        ), mock.patch.object(
            sweep_targets, "draft_variants",
            return_value=([("m2c:s32-s32", "void func_a(void) {}")], "draft"),
        ), mock.patch.object(
            sweep_targets.runner, "try_candidates_detailed", side_effect=fake_try_candidates,
        ), mock.patch.object(
            template_transfer, "generate_template_candidates", return_value=[template_candidate],
        ):
            sweep_targets.sweep(
                max_instructions=None, min_instructions=None, family=None, source=None,
                limit=10, gate=False, workers=1, templates=True,
            )

        labels = captured["labels"]
        self.assertIn("template:func_done:0.95", labels)
        self.assertIn("m2c:s32-s32", labels)
        self.assertLess(labels.index("template:func_done:0.95"), labels.index("m2c:s32-s32"))

    def test_templates_off_by_default_adds_no_template_labels(self) -> None:
        rows = [
            {"function": "func_a", "source": "disasm/src/fragments/1/a.c", "family": "call_sequence"},
        ]
        captured: dict[str, object] = {}

        def fake_try_candidates(source_path, blocks, *, labels=None, declarations=None, gate=True, probe_workers=None):
            captured["labels"] = list(labels or [])
            return {"status": 1, "accepted": [], "attempts": [], "batch_status": "no_candidate_accepted"}

        with mock.patch.object(
            sweep_targets.targets, "list_targets",
            return_value={"matched": 1, "targets": rows, "truncated": False},
        ), mock.patch.object(
            sweep_targets.dedupe_externs, "dirty_sources", return_value=set(),
        ), mock.patch.object(
            sweep_targets, "draft_variants",
            return_value=([("m2c:s32-s32", "void func_a(void) {}")], "draft"),
        ), mock.patch.object(
            sweep_targets.runner, "try_candidates_detailed", side_effect=fake_try_candidates,
        ), mock.patch.object(
            template_transfer, "generate_template_candidates",
        ) as generate:
            sweep_targets.sweep(
                max_instructions=None, min_instructions=None, family=None, source=None,
                limit=10, gate=False, workers=1,
            )

        generate.assert_not_called()
        self.assertEqual(captured["labels"], ["m2c:s32-s32"])


if __name__ == "__main__":
    unittest.main()
