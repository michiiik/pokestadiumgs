#!/usr/bin/env python3
"""Focused regression tests for candidate diagnostics and family filtering."""

from __future__ import annotations

import io
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

import scan_asm_families as scanner
import try_pragma_compare as runner
import xmatch_stadium1 as stadium1

ASM_PROCESSOR_DIR = Path(__file__).resolve().parent.parent / "disasm" / "tools" / "asm-processor"
sys.path.insert(0, str(ASM_PROCESSOR_DIR))
import asm_processor  # noqa: E402


class ScannerTests(unittest.TestCase):
    def test_source_owners_ignores_isolated_pragma_probe_trees(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source_root = root / "src"
            asm_root = root / "asm"
            source_root.mkdir()
            (asm_root / "test").mkdir(parents=True)
            pragma = '#pragma GLOBAL_ASM("asm/us/nonmatchings/test/func_a.s")\n'
            (source_root / "tracked.c").write_text(pragma)
            probe = source_root / ".pragma_probe_race" / "tracked.c"
            probe.parent.mkdir()
            probe.write_text(pragma)
            (asm_root / "test" / "func_a.s").write_text("glabel func_a\n")

            owners = scanner.source_owners(source_root, asm_root)

        self.assertEqual(len(owners), 1)
        self.assertEqual(owners[0][1], source_root / "tracked.c")

    def test_stadium1_near_matches_are_ranked_without_being_transfers(self) -> None:
        gs = {
            "func_gs": {
                "w": [0x24010005, 0x10200001, 0x03E00008, 0x00000000],
            }
        }
        s1 = {
            "func_s1_best": {
                "w": [0x24010007, 0x10200001, 0x03E00008, 0x00000000],
                "seg": "fragment31",
                "vram": 0x81000000,
            },
            "func_s1_other": {
                "w": [0x03E00008, 0x00000000, 0x00000000, 0x00000000],
                "seg": "fragment31",
                "vram": 0x81000010,
            },
        }
        rows = stadium1.near_matches("func_gs", gs, s1, minimum=0.2, limit=2)
        self.assertEqual(rows[0]["function"], "func_s1_best")
        self.assertGreater(rows[0]["similarity"], rows[1]["similarity"])

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

    def test_bundle_exposes_stadium1_reference_without_claiming_a_match(self) -> None:
        owner = scanner.Owner(
            function="func_wrap",
            source="synthetic.c",
            asm="synthetic.s",
            label="func_wrap",
            family="direct_wrapper",
            confidence=1.0,
            instruction_count=2,
            stadium1_match=["DisplayList_SetFlagInRange", "normalised evidence"],
            candidate_codes=["void func_wrap(void) {}"],
            candidate_labels=["wrapper-void"],
        )
        bundle = scanner.render_bundle([owner])
        self.assertIn("stadium1: DisplayList_SetFlagInRange", bundle)


class AsmProcessorPaddingTests(unittest.TestCase):
    def test_c_function_padding_generates_exact_text_block(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "padding.c"
            source.write_text("void func(void) {}\n#pragma C_FUNCTION_PADDING(12)\n")
            output = io.BytesIO()
            functions, dependencies = asm_processor.run(
                ["-O2", str(source)], outfile=output
            )

        self.assertEqual(dependencies, [])
        self.assertEqual(len(functions), 1)
        self.assertEqual(functions[0].data[".text"][1], 12)
        self.assertIn(b"_asmpp_func", output.getvalue())

    def test_c_function_padding_rejects_non_word_size(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "padding.c"
            source.write_text("#pragma C_FUNCTION_PADDING(10)\n")
            with self.assertRaises(SystemExit):
                asm_processor.run(["-O2", str(source)], outfile=io.BytesIO())


class RunnerTests(unittest.TestCase):
    def test_mismatch_diagnostics_decode_instruction_and_classify_drift(self) -> None:
        expected = bytes.fromhex("24040001 03e00008")
        actual = bytes.fromhex("24050001 03e00008")
        with mock.patch.object(runner, "_object_symbol", return_value=(0, len(actual))):
            details = runner._function_mismatch_details(
                Path("synthetic.o"), "func_a", expected, actual
            )
        self.assertEqual(details["first_diff_instruction"], 0)
        self.assertEqual(details["mismatch_kind"], "operand_or_scheduling_drift")
        self.assertEqual(details["expected_instruction_text"], "addiu $a0, $zero, 1")
        self.assertEqual(details["actual_instruction_text"], "addiu $a1, $zero, 1")

    def test_mismatch_diagnostics_identify_symbol_size_drift(self) -> None:
        expected = bytes.fromhex("03e00008 00000000")
        actual = bytes.fromhex("03e00008")
        with mock.patch.object(runner, "_object_symbol", return_value=(0, len(actual))):
            details = runner._function_mismatch_details(
                Path("synthetic.o"), "func_a", expected, actual
            )
        self.assertEqual(details["mismatch_kind"], "symbol_size_drift")
        self.assertEqual(details["first_diff_offset"], len(actual))

    def test_probe_one_keeps_live_source_unchanged(self) -> None:
        repo_root = Path(__file__).resolve().parent.parent
        source_parent = repo_root / "disasm" / "src"
        with tempfile.TemporaryDirectory(dir=source_parent) as directory:
            source = Path(directory) / "synthetic.c"
            original = '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
            source.write_text(original)
            with mock.patch.object(
                runner,
                "_make_object",
                return_value=(0, Path(directory) / "probe.o", ""),
            ), mock.patch.object(
                runner,
                "_function_bytes",
                return_value=b"matching-bytes",
            ):
                result = runner._probe_one(
                    source,
                    "func_a",
                    "void func_a(void) {}",
                    b"matching-bytes",
                )
            self.assertEqual(result["status"], "probe_match")
            self.assertEqual(source.read_text(), original)

    def test_probe_rejection_skips_full_compare(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_b.s")\n'
            )
            with mock.patch.object(
                runner,
                "probe_candidates",
                return_value=[
                    {"index": 0, "function": "func_a", "status": "probe_rejected"},
                    {"index": 1, "function": "func_b", "status": "probe_rejected"},
                ],
            ), mock.patch.object(runner, "_try_candidate_detailed") as full_gate:
                result = runner.try_candidates_detailed(
                    source,
                    [("func_a", "void func_a(void) {}"), ("func_b", "void func_b(void) {}")],
                )
            self.assertEqual(result["batch_status"], "no_candidate_accepted")
            full_gate.assert_not_called()
            self.assertTrue(all(item["status"] == "probe_rejected" for item in result["attempts"]))

    def test_probe_hit_is_sent_to_sequential_full_gate(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
            )
            with mock.patch.object(
                runner,
                "probe_candidates",
                return_value=[
                    {"index": 0, "function": "func_a", "status": "probe_match"},
                ],
            ), mock.patch.object(
                runner,
                "rebuild_source_object",
                return_value=0,
            ), mock.patch.object(
                runner,
                "_try_candidate_detailed",
                return_value=(0, "accepted"),
            ), mock.patch.object(
                runner,
                "compare_current_tree",
                return_value=0,
            ) as full_compare:
                result = runner.try_candidates_detailed(
                    source,
                    [("func_a", "void func_a(void) {}")],
                )
            self.assertEqual(result["accepted"], ["func_a"])
            self.assertEqual(result["attempts"][0]["probe_status"], "probe_match")
            full_compare.assert_called_once()

    def test_probe_variants_after_winner_are_reported_skipped(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
            )
            with mock.patch.object(
                runner,
                "probe_candidates",
                return_value=[
                    {"index": 0, "function": "func_a", "status": "probe_match"},
                    {"index": 1, "function": "func_a", "status": "probe_rejected"},
                ],
            ), mock.patch.object(
                runner,
                "rebuild_source_object",
                return_value=0,
            ), mock.patch.object(
                runner,
                "_try_candidate_detailed",
                return_value=(0, "accepted"),
            ), mock.patch.object(
                runner,
                "compare_current_tree",
                return_value=0,
            ):
                result = runner.try_candidates_detailed(
                    source,
                    [
                        ("func_a", "void func_a(void) {}"),
                        ("func_a", "void func_a(void) { return; }"),
                    ],
                )
        self.assertEqual([item["status"] for item in result["attempts"]], ["accepted", "skipped"])
        self.assertEqual(result["attempts"][1]["probe_status"], "probe_rejected")

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
