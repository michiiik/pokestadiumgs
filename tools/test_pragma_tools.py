#!/usr/bin/env python3
"""Focused regression tests for candidate diagnostics and family filtering."""

from __future__ import annotations

import tempfile
import unittest
from pathlib import Path
from unittest import mock

import scan_asm_families as scanner
import try_pragma_compare as runner


class ScannerTests(unittest.TestCase):
    def test_wrapper_unknown_loaded_global_prefers_pointer_hypothesis(self) -> None:
        asm = """
        glabel func_wrap
            /* 000000 80000000 */ addiu $sp, $sp, -0x18
            /* 000004 80000004 */ or $a1, $a0, $zero
            /* 000008 80000008 */ lui $a0, %hi(D_80000040)
            /* 00000C 8000000C */ jal func_worker
            /* 000010 80000010 */ lw $a0, %lo(D_80000040)($a0)
            /* 000014 80000014 */ jr $ra
            /* 000018 80000018 */ nop
        """
        label, instructions, _ = scanner.parse_instructions(asm)
        owner = scanner.Owner(
            function=label,
            source="synthetic.c",
            asm="synthetic.s",
            label=label,
            family="direct_wrapper",
            confidence=1.0,
            instruction_count=len(instructions),
            calls=["func_worker"],
        )
        candidates = scanner.wrapper_candidates(owner, instructions)
        self.assertIn("extern void * D_80000040;", candidates[0])
        self.assertTrue(any("extern u32 D_80000040;" in candidate for candidate in candidates))

    def test_wrapper_uses_old_style_decl_when_target_is_called_elsewhere(self) -> None:
        asm = """
        glabel func_wrap
            /* 000000 80000000 */ addiu $sp, $sp, -0x18
            /* 000004 80000004 */ or $a1, $a0, $zero
            /* 000008 80000008 */ jal func_worker
            /* 00000C 8000000C */ nop
            /* 000010 80000010 */ jr $ra
            /* 000014 80000014 */ nop
        """
        label, instructions, _ = scanner.parse_instructions(asm)
        owner = scanner.Owner(
            function=label,
            source="synthetic.c",
            asm="synthetic.s",
            label=label,
            family="direct_wrapper",
            confidence=1.0,
            instruction_count=len(instructions),
            calls=["func_worker"],
            function_declarations={"func_worker": "extern void func_worker(void);"},
            function_uses={"func_worker"},
        )
        candidates = scanner.wrapper_candidates(owner, instructions)
        self.assertIn("extern void func_worker();", candidates[0])

    def test_wrapper_preserves_outgoing_stack_argument(self) -> None:
        asm = """
        glabel func_wrap
            /* 000000 80000000 */ addiu $sp, $sp, -0x20
            /* 000004 80000004 */ lui $t6, %hi(D_80000040)
            /* 000008 80000008 */ addiu $t6, $t6, %lo(D_80000040)
            /* 00000C 8000000C */ sw $t6, 0x10($sp)
            /* 000010 80000010 */ addiu $a1, $zero, 4
            /* 000014 80000014 */ addiu $a2, $zero, 4
            /* 000018 80000018 */ jal func_worker
            /* 00001C 8000001C */ addiu $a3, $zero, 422
            /* 000020 80000020 */ jr $ra
            /* 000024 80000024 */ nop
        """
        label, instructions, _ = scanner.parse_instructions(asm)
        owner = scanner.Owner(
            function=label,
            source="synthetic.c",
            asm="synthetic.s",
            label=label,
            family="direct_wrapper",
            confidence=1.0,
            instruction_count=len(instructions),
            calls=["func_worker"],
        )
        candidates = scanner.wrapper_candidates(owner, instructions)
        self.assertIn("&D_80000040", candidates[0])
        self.assertIn("func_worker(arg0, 4, 4, 422, &D_80000040)", candidates[0])

    def test_lookup_emits_multiple_labeled_variants(self) -> None:
        asm = """
        glabel func_80000000
            /* 000000 80000000 04800003 */ bltz $a0, .Ldone
            /* 000004 80000004 28810004 */ slti $at, $a0, 4
            /* 000008 80000008 10200001 */ beqz $at, .Ldone
            /* 00000C 8000000C 00047080 */ sll $t6, $a0, 2
            /* 000010 80000010 3C018000 */ lui $at, %hi(D_80000040)
            /* 000014 80000014 002E0821 */ addu $at, $at, $t6
            /* 000018 80000018 8C200040 */ lw $zero, %lo(D_80000040)($at)
        .Ldone:
            /* 00001C 8000001C 03E00008 */ jr $ra
            /* 000020 80000020 00001025 */ or $v0, $zero, $zero
        """
        label, instructions, labels = scanner.parse_instructions(asm)
        accesses = scanner.extract_memory_accesses(instructions)
        owner = scanner.Owner(
            function=label,
            source="synthetic.c",
            asm="synthetic.s",
            label=label,
            family="bounded_lookup",
            confidence=1.0,
            instruction_count=len(instructions),
            globals=["D_80000040"],
            memory_accesses=accesses,
            bounds=[4],
            branches=3,
        )
        owner.candidate_codes = scanner.bounded_lookup_candidates(owner, instructions)
        self.assertGreater(len(owner.candidate_codes), 1)
        self.assertEqual(len(owner.candidate_codes), len(owner.candidate_labels))

    def test_lookup_rejects_long_state_machine_shape(self) -> None:
        instructions = [scanner.Instruction("nop", "", index) for index in range(40)]
        owner = scanner.Owner(
            function="func_long",
            source="synthetic.c",
            asm="synthetic.s",
            label="func_long",
            family="bounded_lookup",
            confidence=1.0,
            instruction_count=40,
            globals=["D_80000040"],
            bounds=[4],
            branches=0,
        )
        self.assertEqual(scanner.bounded_lookup_candidates(owner, instructions), [])
        self.assertTrue(any("suppressed" in note for note in owner.notes))


class RunnerTests(unittest.TestCase):
    def test_diagnostics_mark_later_variants_skipped(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
            )
            with mock.patch.object(runner, "rebuild_source_object", return_value=0), \
                    mock.patch.object(runner, "compare_current_tree", return_value=0), \
                    mock.patch.object(
                        runner,
                        "_try_candidate_detailed",
                        return_value=(0, "accepted"),
                    ):
                result = runner.try_candidates_detailed(
                    source,
                    [("func_a", "void func_a(void) {}"), ("func_a", "void func_a(void) {}")],
                )
        self.assertEqual(result["status"], 0)
        self.assertEqual(result["accepted"], ["func_a"])
        self.assertEqual(
            [attempt["status"] for attempt in result["attempts"]],
            ["accepted", "skipped"],
        )

    def test_diagnostics_preserve_compare_rejection_reason(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
            )
            with mock.patch.object(runner, "rebuild_source_object", return_value=0), \
                    mock.patch.object(runner, "compare_current_tree", return_value=0), \
                    mock.patch.object(
                        runner,
                        "_try_candidate_detailed",
                        return_value=(2, "compare_rejected"),
                    ):
                result = runner.try_candidates_detailed(
                    source,
                    [("func_a", "void func_a(void) {}")],
                )
        self.assertEqual(result["status"], 1)
        self.assertEqual(result["batch_status"], "no_candidate_accepted")
        self.assertEqual(result["attempts"][0]["status"], "compare_rejected")


if __name__ == "__main__":
    unittest.main()
