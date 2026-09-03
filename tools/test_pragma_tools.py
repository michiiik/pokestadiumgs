#!/usr/bin/env python3
"""Focused regression tests for candidate diagnostics and family filtering."""

from __future__ import annotations

import io
import json
import os
import signal
import subprocess
import sys
import tempfile
import time
import unittest
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from unittest import mock

import scan_asm_families as scanner
import try_pragma_compare as runner
import xmatch_stadium1 as stadium1

ASM_PROCESSOR_DIR = Path(__file__).resolve().parent.parent / "disasm" / "tools" / "asm-processor"
sys.path.insert(0, str(ASM_PROCESSOR_DIR))
import asm_processor  # noqa: E402

# The runner records probe statistics to disasm/probe-stats/probe-stats.jsonl
# (see tools/probe_stats.py) by default.  Synthetic test transactions must
# never land in that file, because it is the data set used for family-level
# candidate tuning.
_STATS_ISOLATION = mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": ""})

# A gated try_candidates_detailed() call also claims its source path (see
# try_pragma_compare._claim_or_refuse / tools/file_claims.py) in the real
# disasm/probe-stats/claims.json by default.  These synthetic /tmp source
# paths must never land there either -- point the whole module at a
# throwaway registry instead.
_CLAIMS_REGISTRY_DIR = tempfile.TemporaryDirectory()
_CLAIMS_ISOLATION = mock.patch.dict(
    os.environ, {"PRAGMA_CLAIMS_REGISTRY": str(Path(_CLAIMS_REGISTRY_DIR.name) / "claims.json")}
)


def setUpModule() -> None:
    _STATS_ISOLATION.start()
    _CLAIMS_ISOLATION.start()


def tearDownModule() -> None:
    # Stop in reverse (LIFO) order: both patch the same os.environ dict, and
    # each one's stop() restores its own start()-time snapshot of the whole
    # dict, not just the key it set. Stopping _STATS_ISOLATION first would
    # have _CLAIMS_ISOLATION.stop() then restore a snapshot that still
    # includes PRAGMA_PROBE_STATS="" -- silently disabling probe-stats
    # again for every module that runs after this one.
    _CLAIMS_ISOLATION.stop()
    _STATS_ISOLATION.stop()
    _CLAIMS_REGISTRY_DIR.cleanup()


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

    def _bounded_lookup_multiplier_stride_owner(self) -> tuple[scanner.Owner, list[scanner.Instruction]]:
        """A synthetic manifest matching the proven ``blez``/``sll``-``subu`` shape.

        This mirrors the verified ``func_800637C0``-family owners: a byte
        argument masked at entry, a compound ``arg0 > 0 && arg0 < N`` range
        check built from two branches, and a 22-byte record stride built
        from a ``sll``/``subu`` chain rather than a single shift.
        """
        asm = """
        glabel func_80000100
            /* 000000 80000000 AFA40000 */ sw $a0, 0x0($sp)
            /* 000004 80000004 308400FF */ andi $a0, $a0, 0xff
            /* 000008 80000008 1880000B */ blez $a0, .Ldone
            /* 00000C 8000000C 288100FC */  slti $at, $a0, 0xfc
            /* 000010 80000010 10200009 */ beqz $at, .Ldone
            /* 000014 80000014 00047080 */  sll $t6, $a0, 2
            /* 000018 80000018 01C47023 */ subu $t6, $t6, $a0
            /* 00001C 8000001C 000E7080 */ sll $t6, $t6, 2
            /* 000020 80000020 01C47023 */ subu $t6, $t6, $a0
            /* 000024 80000024 000E7040 */ sll $t6, $t6, 1
            /* 000028 80000028 3C028000 */ lui $v0, %hi(D_80000200)
            /* 00002C 8000002C 004E1021 */ addu $v0, $v0, $t6
            /* 000030 80000030 03E00008 */ jr $ra
            /* 000034 80000034 90420200 */  lbu $v0, %lo(D_80000200)($v0)
        .Ldone:
            /* 000038 80000038 00001025 */ or $v0, $zero, $zero
            /* 00003C 8000003C 03E00008 */ jr $ra
            /* 000040 80000040 00000000 */  nop
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
            globals=["D_80000200"],
            memory_accesses=accesses,
            bounds=[252],
            branches=2,
        )
        return owner, instructions

    def test_lookup_primary_variant_is_guard_return_with_recovered_stride(self) -> None:
        owner, instructions = self._bounded_lookup_multiplier_stride_owner()
        owner.candidate_codes = scanner.bounded_lookup_candidates(owner, instructions)
        self.assertTrue(owner.candidate_codes)
        self.assertTrue(owner.candidate_labels[0].startswith("lookup-guard-"))
        primary = owner.candidate_codes[0]
        # A byte argument (the entry `andi $a0, $a0, 0xff`), a compound
        # `arg0 > 0` (from `blez`) plus upper-bound condition, and the
        # 22-byte stride recovered from the sll/subu chain (not the naive
        # single-`sll` shift, which would silently truncate it to 4).
        self.assertIn("u8 func_80000100(u8 arg0)", primary)
        self.assertIn(
            "if (arg0 > 0 && arg0 < 252) return D_80000200[arg0 * 22]; return 0;",
            primary,
        )

    def test_lookup_secondary_variant_is_the_assign_then_return_shape(self) -> None:
        owner, instructions = self._bounded_lookup_multiplier_stride_owner()
        owner.candidate_codes = scanner.bounded_lookup_candidates(owner, instructions)
        self.assertGreater(len(owner.candidate_codes), 1)
        self.assertTrue(owner.candidate_labels[1].startswith("lookup-init-"))
        secondary = owner.candidate_codes[1]
        self.assertIn(
            "u8 result = 0; if (arg0 > 0 && arg0 < 252) result = D_80000200[arg0 * 22]; return result;",
            secondary,
        )

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

    def test_multi_call_wrapper_emits_ordered_void_calls(self) -> None:
        asm = """
        glabel func_wrap
            /* 000000 80000000 */ addiu $sp, $sp, -0x18
            /* 000004 80000004 */ addiu $a0, $zero, 1
            /* 000008 80000008 */ jal func_first
            /* 00000C 8000000C */ nop
            /* 000010 80000010 */ addiu $a0, $zero, 2
            /* 000014 80000014 */ jal func_second
            /* 000018 80000018 */ nop
            /* 00001C 8000001C */ jr $ra
            /* 000020 80000020 */ nop
        """
        label, instructions, _ = scanner.parse_instructions(asm)
        owner = scanner.Owner(
            function=label,
            source="synthetic.c",
            asm="synthetic.s",
            label=label,
            family="multi_call_wrapper",
            confidence=1.0,
            instruction_count=len(instructions),
            calls=["func_first", "func_second"],
        )
        candidates = scanner.multi_call_wrapper_candidates(owner, instructions)
        self.assertEqual(len(candidates), len(scanner.MULTI_CALL_PARAMETER_TYPES))
        self.assertIn("func_first(1);", candidates[0])
        self.assertIn("func_second(2);", candidates[0])

    def test_multi_call_wrapper_emits_long_setup_and_address_global_variant(self) -> None:
        asm = """
        glabel func_setup
            /* 000000 80000000 */ addiu $sp, $sp, -0x18
            /* 000004 80000004 */ lui $a0, %hi(D_80000040)
            /* 000008 80000008 */ addiu $a0, $a0, %lo(D_80000040)
            /* 00000C 8000000C */ jal func_first
            /* 000010 80000010 */ nop
            /* 000014 80000014 */ jal func_second
            /* 000018 80000018 */ nop
            /* 00001C 8000001C */ jal func_third
            /* 000020 80000020 */ nop
            /* 000024 80000024 */ jal func_fourth
            /* 000028 80000028 */ nop
            /* 00002C 8000002C */ jr $ra
            /* 000030 80000030 */ nop
        """
        label, instructions, _ = scanner.parse_instructions(asm)
        owner = scanner.Owner(
            function=label,
            source="synthetic.c",
            asm="synthetic.s",
            label=label,
            family="multi_call_wrapper",
            confidence=1.0,
            instruction_count=len(instructions),
            calls=["func_first", "func_second", "func_third", "func_fourth"],
        )
        candidates = scanner.multi_call_wrapper_candidates(owner, instructions)
        self.assertEqual(len(candidates), len(scanner.MULTI_CALL_PARAMETER_TYPES))
        self.assertIn("extern u8 D_80000040[];", candidates[0])
        self.assertIn("func_first(&D_80000040);", candidates[0])
        self.assertIn("func_fourth();", candidates[0])


class ClassifyCallSequenceShapeTests(unittest.TestCase):
    """Sub-families split out of the call_sequence/unclassified catch-alls.

    Each fixture is built to fail every pre-existing family's rule (a
    non-``SIMPLE_WRAPPER_OPS`` instruction, a branch, or an extra call) so it
    actually reaches the new rules instead of being claimed by
    ``direct_wrapper``/``multi_call_wrapper``/``constant_map``/etc. first --
    those pre-existing rules and their owners must stay exactly as they were.
    """

    def test_dispatcher_switch_is_a_jump_table_with_calls(self) -> None:
        # "sll" is outside SIMPLE_WRAPPER_OPS, so this cannot be mistaken for
        # a direct_wrapper despite having exactly one call.
        instructions = [scanner.Instruction("sll", "$t0, $a0, 2", 0)]
        family, confidence, notes = scanner.classify(
            instructions,
            calls=["func_worker"],
            globals_=[],
            jump_tables=["jtbl_80020000"],
            accesses=[],
            bounds=[],
            loops=False,
        )
        self.assertEqual(family, "dispatcher_switch")
        self.assertGreater(confidence, 0.7)
        self.assertTrue(any("switch" in note for note in notes))

    def test_large_mixed_is_a_size_cutoff(self) -> None:
        instructions = [scanner.Instruction("nop", "", index) for index in range(300)]
        family, confidence, notes = scanner.classify(
            instructions, calls=[], globals_=[], jump_tables=[], accesses=[], bounds=[], loops=False
        )
        self.assertEqual(family, "large_mixed")
        self.assertTrue(any("300" in note for note in notes))

    def test_float_math_needs_no_calls_and_float_ops(self) -> None:
        instructions = [
            scanner.Instruction("lwc1", "$f0, 0x0($a0)", 0),
            scanner.Instruction("lwc1", "$f2, 0x4($a0)", 1),
            scanner.Instruction("add.s", "$f0, $f0, $f2", 2),
            scanner.Instruction("swc1", "$f0, 0x0($a1)", 3),
            scanner.Instruction("jr", "$ra", 4),
            scanner.Instruction("nop", "", 5),
        ]
        family, confidence, notes = scanner.classify(
            instructions, calls=[], globals_=[], jump_tables=[], accesses=[], bounds=[], loops=False
        )
        self.assertEqual(family, "float_math")
        self.assertTrue(any("float" in note for note in notes))

    def test_predicate_is_short_boolean_result_no_calls(self) -> None:
        instructions = [
            scanner.Instruction("slt", "$v0, $a0, $a1", 0),
            scanner.Instruction("jr", "$ra", 1),
            scanner.Instruction("nop", "", 2),
        ]
        family, confidence, notes = scanner.classify(
            instructions, calls=[], globals_=[], jump_tables=[], accesses=[], bounds=[], loops=False
        )
        self.assertEqual(family, "predicate")

    def test_init_sequence_is_one_or_two_calls_with_narrow_field_stores(self) -> None:
        # "sb"/"sh" are outside SIMPLE_WRAPPER_OPS, so this single-call owner
        # cannot be mistaken for direct_wrapper.
        instructions = [
            scanner.Instruction("sb", "$a2, 0x0($a1)", 0),
            scanner.Instruction("sh", "$a3, 0x2($a1)", 1),
            scanner.Instruction("jal", "func_worker", 2),
            scanner.Instruction("nop", "", 3),
            scanner.Instruction("jr", "$ra", 4),
            scanner.Instruction("nop", "", 5),
        ]
        accesses = [
            scanner.MemoryAccess("sb", 0, "a1", 0),
            scanner.MemoryAccess("sh", 2, "a1", 1),
        ]
        family, confidence, notes = scanner.classify(
            instructions,
            calls=["func_worker"],
            globals_=[],
            jump_tables=[],
            accesses=accesses,
            bounds=[],
            loops=False,
        )
        self.assertEqual(family, "init_sequence")

    def test_call_chain_is_three_plus_calls_with_little_side_effect(self) -> None:
        # A branch keeps this from matching multi_call_wrapper (which
        # requires no control-flow branches).
        instructions = [
            scanner.Instruction("jal", "func_a", 0),
            scanner.Instruction("nop", "", 1),
            scanner.Instruction("jal", "func_b", 2),
            scanner.Instruction("nop", "", 3),
            scanner.Instruction("beqz", "$v0, .Lskip", 4),
            scanner.Instruction("jal", "func_c", 5),
            scanner.Instruction("nop", "", 6),
            scanner.Instruction("jr", "$ra", 7),
            scanner.Instruction("nop", "", 8),
        ]
        family, confidence, notes = scanner.classify(
            instructions,
            calls=["func_a", "func_b", "func_c"],
            globals_=[],
            jump_tables=[],
            accesses=[],
            bounds=[],
            loops=False,
        )
        self.assertEqual(family, "call_chain")

    def test_state_machine_is_no_calls_many_branches_over_state(self) -> None:
        # A non-empty ``globals_`` keeps this from matching the pre-existing
        # constant_map rule, which requires branches with *no* globals.
        instructions = [scanner.Instruction("beqz", "$a0, .L", index) for index in range(5)]
        family, confidence, notes = scanner.classify(
            instructions,
            calls=[],
            globals_=["D_80001234"],
            jump_tables=[],
            accesses=[],
            bounds=[],
            loops=False,
        )
        self.assertEqual(family, "state_machine")

    def test_call_sequence_and_unclassified_remain_the_final_fallbacks(self) -> None:
        # A branchy multi-call owner outside every new shape's rule still
        # falls into call_sequence, and a no-call/no-evidence owner still
        # falls into unclassified -- the two historical catch-alls are
        # narrowed, not removed.
        branchy_calls = [
            scanner.Instruction("jal", "func_a", 0),
            scanner.Instruction("nop", "", 1),
            scanner.Instruction("beqz", "$v0, .Lskip", 2),
            scanner.Instruction("jal", "func_b", 3),
            scanner.Instruction("nop", "", 4),
            scanner.Instruction("jr", "$ra", 5),
            scanner.Instruction("nop", "", 6),
        ]
        family, _confidence, _notes = scanner.classify(
            branchy_calls,
            calls=["func_a", "func_b"],
            globals_=[],
            jump_tables=[],
            accesses=[],
            bounds=[],
            loops=False,
        )
        self.assertEqual(family, "call_sequence")

        family, _confidence, _notes = scanner.classify(
            [scanner.Instruction("or", "$v0, $zero, $zero", 0), scanner.Instruction("jr", "$ra", 1)],
            calls=[],
            globals_=[],
            jump_tables=[],
            accesses=[],
            bounds=[],
            loops=False,
        )
        self.assertEqual(family, "unclassified")


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

    def test_c_function_padding_allows_single_nop(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "padding.c"
            source.write_text("#pragma C_FUNCTION_PADDING(4)\n")
            output = io.BytesIO()
            functions, dependencies = asm_processor.run(
                ["-O2", str(source)], outfile=output
            )

        self.assertEqual(dependencies, [])
        self.assertEqual(len(functions), 1)
        self.assertEqual(functions[0].data[".text"][1], 4)

    def test_c_function_padding_rejects_non_word_size(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "padding.c"
            source.write_text("#pragma C_FUNCTION_PADDING(10)\n")
            with self.assertRaises(SystemExit):
                asm_processor.run(["-O2", str(source)], outfile=io.BytesIO())


class RunnerTests(unittest.TestCase):
    def test_tail_diagnostics_distinguish_duplicate_return_and_padding(self) -> None:
        duplicate = bytes.fromhex("03e00008 00000000 03e00008 00000000")
        padding = bytes.fromhex("03e00008 00000000 00000000 00000000")
        self.assertEqual(runner._classify_tail_bytes(duplicate), "duplicate_jr_nop_tail")
        self.assertEqual(runner._classify_tail_bytes(padding), "jr_nop_plus_alignment")

    def test_mismatch_diagnostics_decode_instruction_and_classify_drift(self) -> None:
        expected = bytes.fromhex("24040001 03e00008 00000000")
        actual = bytes.fromhex("24050001 03e00008 00000000")
        with mock.patch.object(runner, "_object_symbol", return_value=(0, len(actual))):
            details = runner._function_mismatch_details(
                Path("synthetic.o"), "func_a", expected, actual
            )
        self.assertEqual(details["first_diff_instruction"], 0)
        # Same opcode stream and immediates, only the destination register
        # differs: the whole-body class outranks the first-instruction one.
        self.assertEqual(details["mismatch_kind"], "register_allocation_only")
        self.assertEqual(details["register_only_similarity_score"], 1.0)
        self.assertEqual(details["expected_instruction_text"], "addiu $a0, $zero, 1")
        self.assertEqual(details["actual_instruction_text"], "addiu $a1, $zero, 1")
        self.assertEqual(details["expected_tail_kind"], "normal_return")
        self.assertEqual(details["total_instructions"], 3)
        self.assertEqual(details["matched_instructions"], 3)
        self.assertEqual(details["exact_instruction_matches"], 2)
        self.assertEqual(details["similarity_score"], 1.0)
        self.assertEqual(details["exact_similarity_score"], 0.6667)
        self.assertEqual(details["assembly_diff"][0]["expected_offset"], 0)
        self.assertTrue(details["assembly_diff"][0]["normalized_match"])

    def test_instruction_normalization_preserves_shape(self) -> None:
        self.assertEqual(
            runner._normalise_instruction_text("lw v0,4(a1)"),
            runner._normalise_instruction_text("lw t7,12(a0)"),
        )
        self.assertEqual(
            runner._normalise_instruction_text("lwc1 f0,4(a0)"),
            runner._normalise_instruction_text("lwc1 f31,12(a1)"),
        )
        self.assertNotEqual(
            runner._normalise_instruction_text("lw v0,4(a1)"),
            runner._normalise_instruction_text("sw t7,12(a0)"),
        )

    def test_probe_rejections_are_ranked_without_reordering_attempts(self) -> None:
        attempts = [
            {"index": 0, "function": "func_a", "status": "probe_rejected", "similarity_score": 0.5},
            {"index": 1, "function": "func_a", "status": "probe_rejected", "similarity_score": 0.9},
            {"index": 2, "function": "func_a", "status": "probe_rejected", "similarity_score": 0.7},
        ]
        ranking = runner._rank_probe_rejections(
            attempts,
            [("func_a", "first"), ("func_a", "second"), ("func_a", "third")],
        )
        self.assertEqual([item["index"] for item in ranking["func_a"]], [1, 2, 0])
        self.assertEqual([item["similarity_rank"] for item in attempts], [3, 1, 2])

    def test_mismatch_diagnostics_classify_immediate_drift(self) -> None:
        # addiu $a0, $zero, 1 versus addiu $a0, $zero, 2: same registers, only
        # the constant differs.
        expected = bytes.fromhex("24040001 03e00008 00000000")
        actual = bytes.fromhex("24040002 03e00008 00000000")
        details = runner._function_mismatch_details(
            Path("synthetic.o"), "func_a", expected, actual, actual_symbol_size=len(actual)
        )
        self.assertEqual(details["mismatch_kind"], "immediate_drift")
        self.assertEqual(details["actual_size"], len(actual))
        self.assertEqual(details["similarity_score"], 1.0)
        self.assertLess(details["register_only_similarity_score"], 1.0)

    def test_disassembler_decodes_vr4300_64bit_operations(self) -> None:
        if not Path(runner._binutils_tool("objdump")).exists():
            self.skipTest("MIPS binutils objdump is not installed")
        # dsll $v0, $v0, 0 is a MIPS III (VR4300) instruction that a 32-bit
        # ISA setting decodes as a bare .word, which would poison the score.
        texts = runner._disassemble_bytes(bytes.fromhex("00021038 03e00008 00000000"))
        self.assertEqual(len(texts), 3)
        self.assertTrue(texts[0].startswith("dsll"), texts)

    def test_probe_recipe_is_parsed_and_substituted(self) -> None:
        source = runner._RECIPE_SOURCE
        obj = runner._RECIPE_OBJECT
        make_output = "\n".join([
            f'printf "Compiling: {source} -> {obj}\\n"',
            f"gcc -fsyntax-only -I probes/.pragma_probe_recipe/ -o {obj} {source}",
            f".venv/bin/python3 tools/asm-processor/build.py cc -- as -- -c -I {runner._RECIPE_DIRECTORY} -o {obj} {source}",
            ":",
        ])
        recipe = runner._parse_probe_recipe(make_output)
        self.assertIsNotNone(recipe)
        self.assertEqual(recipe[0], ".venv/bin/python3")
        command = runner._substitute_probe_recipe(
            recipe,
            "probes/.pragma_probe_x1/owner.c",
            "build/probes/.pragma_probe_x1/owner.o",
        )
        self.assertEqual(command[-1], "probes/.pragma_probe_x1/owner.c")
        self.assertEqual(command[command.index("-o") + 1], "build/probes/.pragma_probe_x1/owner.o")
        self.assertEqual(command[command.index("-I") + 1], "probes/.pragma_probe_x1/")
        self.assertIsNone(runner._parse_probe_recipe(":\n:\n"))

    def test_compare_capture_replaces_malformed_utf8(self) -> None:
        decoded = b"diagnostic \xff\n".decode("utf-8", "replace")

        with mock.patch.object(
            runner, "_run_bounded_process_group", return_value=(1, decoded, False)
        ):
            result, output = runner._run_compare(Path("/tmp/repo"))
        self.assertEqual(result, 1)
        self.assertIn("diagnostic \ufffd", output)

    def test_probe_sources_compile_with_direct_recipe(self) -> None:
        repo_root = Path(__file__).resolve().parent.parent
        probe_root = runner._probe_root(repo_root)
        with tempfile.TemporaryDirectory(prefix=".pragma_probe_", dir=probe_root) as directory:
            source = Path(directory) / "owner.c"
            source.write_text("void owner(void) {}\n")
            with mock.patch.object(
                runner,
                "_probe_compile_recipe",
                return_value=["cc", "-o", runner._RECIPE_OBJECT, runner._RECIPE_SOURCE],
            ), mock.patch.object(
                runner, "_run_bounded_process_group", return_value=(0, "", False)
            ) as run:
                result, object_path, _ = runner._make_object(source, capture=True)
            self.assertEqual(result, 0)
            command = run.call_args.args[0]
            self.assertEqual(command[0], "cc")
            self.assertEqual(command[-1], source.relative_to(repo_root / "disasm").as_posix())
            self.assertEqual(run.call_args.kwargs["cwd"], repo_root / "disasm")
            self.assertEqual(object_path.parent.name, Path(directory).name)
            # Tracked sources keep using make so the Makefile's own rules apply.
            with tempfile.TemporaryDirectory(dir=repo_root / "disasm" / "src") as tracked:
                tracked_source = Path(tracked) / "owner.c"
                tracked_source.write_text("void owner(void) {}\n")
                with mock.patch.object(
                    runner, "_run_bounded_process_group", return_value=(0, "", False)
                ) as run:
                    runner._make_object(tracked_source, capture=True)
                self.assertEqual(run.call_args.args[0][0], "make")

    def test_probe_worker_default_and_clamping(self) -> None:
        with mock.patch.dict(os.environ, {}, clear=True):
            with mock.patch.object(runner.resource, "getrlimit", return_value=(256, 256)):
                self.assertEqual(runner._resolve_probe_workers(None, 50), 4)
        with mock.patch.dict(os.environ, {"PRAGMA_PROBE_WORKERS": "3"}):
            with mock.patch.object(runner.resource, "getrlimit", return_value=(256, 256)):
                self.assertEqual(runner._resolve_probe_workers(None, 50), 3)
                self.assertEqual(runner._resolve_probe_workers(20, 50), 12)
                self.assertEqual(runner._resolve_probe_workers(20, 2), 2)

    def test_probe_workers_disable_when_descriptor_headroom_is_exhausted(self) -> None:
        with mock.patch.object(runner.resource, "getrlimit", return_value=(256, 256)), mock.patch.object(
            runner, "_open_file_descriptor_count", return_value=244
        ):
            self.assertEqual(runner._resolve_probe_workers(4, 50), 0)

    def test_linked_path_selects_its_checkout_for_runner_outputs(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory) / "worktree"
            source = root / "disasm" / "src" / "synthetic.c"
            source.parent.mkdir(parents=True)
            (root / ".git").write_text("gitdir: /tmp/worktrees/synthetic\n")
            self.assertEqual(runner._repo_root_for_path(source), root)
            self.assertEqual(runner._scratch_root(root), root / "disasm" / "scratch")

    def test_scratch_symlink_is_rejected(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory) / "worktree"
            (root / "disasm").mkdir(parents=True)
            target = Path(directory) / "outside"
            target.mkdir()
            (root / "disasm" / "scratch").symlink_to(target, target_is_directory=True)
            with self.assertRaisesRegex(RuntimeError, "scratch root"):
                runner._scratch_root(root)

    def test_enforced_claim_refusal_is_not_cached(self) -> None:
        import file_claims

        source = Path(tempfile.mkdtemp()) / "synthetic.c"
        source.parent.mkdir(exist_ok=True)
        key = file_claims.registry_key(source)
        runner._CLAIMED_SOURCE_PATHS.discard(key)
        try:
            with mock.patch.dict(os.environ, {"CLAIMS_OWNER": "owner-a"}, clear=False):
                self.assertIsNone(runner._claim_or_refuse(source))
            with mock.patch.dict(
                os.environ,
                {"CLAIMS_OWNER": "owner-b", "PRAGMA_CLAIMS_ENFORCE": "1"},
                clear=False,
            ):
                self.assertIn("claimed by owner-a", runner._claim_or_refuse(source) or "")
                self.assertIn("claimed by owner-a", runner._claim_or_refuse(source) or "")
        finally:
            runner._CLAIMED_SOURCE_PATHS.discard(key)

    def test_binutils_timeout_is_treated_as_unavailable(self) -> None:
        with mock.patch.object(
            runner, "_run_bounded_process_group", return_value=(124, "", True)
        ):
            self.assertIsNone(runner._object_symbol(Path("/tmp/synthetic.o"), "func_a"))

    def test_bootstrap_timeout_kills_and_reaps_descendants(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            child_pid_path = root / "child.pid"
            script = (
                "import pathlib,subprocess,sys,time; "
                "child=subprocess.Popen([sys.executable,'-c','import time; time.sleep(60)']); "
                "pathlib.Path(sys.argv[1]).write_text(str(child.pid)); time.sleep(60)"
            )
            started = time.monotonic()
            with mock.patch.dict(
                os.environ,
                {"PRAGMA_COMPARE_TIMEOUT": "0.8", "PRAGMA_BOOTSTRAP_TERM_SECONDS": "0.2"},
            ):
                with self.assertRaisesRegex(RuntimeError, "timed out during descendant test"):
                    runner._bootstrap_command(
                        root,
                        [sys.executable, "-c", script, str(child_pid_path)],
                        "descendant test",
                    )
            self.assertLess(time.monotonic() - started, 4.0)
            self.assertTrue(child_pid_path.is_file())
            child_pid = int(child_pid_path.read_text())

            def child_exists() -> bool:
                try:
                    os.kill(child_pid, 0)
                    return True
                except ProcessLookupError:
                    return False

            deadline = time.monotonic() + 2.0
            while child_exists() and time.monotonic() < deadline:
                time.sleep(0.02)
            if child_exists():
                os.kill(child_pid, signal.SIGKILL)
                self.fail(f"bootstrap descendant {child_pid} survived process-group cleanup")

    def test_compare_timeout_kills_and_reaps_descendants(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            child_pid_path = root / "compare-child.pid"
            script = (
                "import pathlib,subprocess,sys,time; "
                "child=subprocess.Popen([sys.executable,'-c','import time; time.sleep(60)']); "
                "pathlib.Path(sys.argv[1]).write_text(str(child.pid)); time.sleep(60)"
            )
            real_popen = runner.subprocess.Popen

            def spawn_descendant(command, **kwargs):
                return real_popen(
                    [sys.executable, "-c", script, str(child_pid_path)], **kwargs
                )

            with mock.patch.object(
                runner, "_ensure_worktree_gate_prerequisites"
            ), mock.patch.object(runner, "_ensure_worktree_oracles"), mock.patch.object(
                runner.subprocess, "Popen", side_effect=spawn_descendant
            ), mock.patch.dict(
                os.environ,
                {"PRAGMA_COMPARE_TIMEOUT": "0.8", "PRAGMA_BOOTSTRAP_TERM_SECONDS": "0.2"},
            ):
                result, output = runner._run_compare(root)
            self.assertEqual(result, 124)
            self.assertIn("compare timed out", output)
            self._assert_process_exited(child_pid_path, "compare")

    def test_make_object_timeout_kills_and_reaps_descendants(self) -> None:
        repo_root = Path(__file__).resolve().parent.parent
        with tempfile.TemporaryDirectory(dir=repo_root / "disasm" / "src") as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text("void synthetic(void) {}\n")
            child_pid_path = Path(directory) / "compile-child.pid"
            script = (
                "import pathlib,subprocess,sys,time; "
                "child=subprocess.Popen([sys.executable,'-c','import time; time.sleep(60)']); "
                "pathlib.Path(sys.argv[1]).write_text(str(child.pid)); time.sleep(60)"
            )
            real_popen = runner.subprocess.Popen

            def spawn_descendant(command, **kwargs):
                return real_popen(
                    [sys.executable, "-c", script, str(child_pid_path)], **kwargs
                )

            with mock.patch.object(
                runner.subprocess, "Popen", side_effect=spawn_descendant
            ), mock.patch.dict(
                os.environ,
                {"PRAGMA_COMPILE_TIMEOUT": "0.8", "PRAGMA_BOOTSTRAP_TERM_SECONDS": "0.2"},
            ):
                result, _, output = runner._make_object(source, capture=True)
            self.assertEqual(result, 124)
            self.assertIn("compile timed out", output)
            self._assert_process_exited(child_pid_path, "compile")

    def _assert_process_exited(self, pid_path: Path, description: str) -> None:
        self.assertTrue(pid_path.is_file())
        pid = int(pid_path.read_text())

        def process_exists() -> bool:
            try:
                os.kill(pid, 0)
                return True
            except ProcessLookupError:
                return False

        deadline = time.monotonic() + 2.0
        while process_exists() and time.monotonic() < deadline:
            time.sleep(0.02)
        if process_exists():
            os.kill(pid, signal.SIGKILL)
            self.fail(f"{description} descendant {pid} survived process-group cleanup")

    def test_worktree_build_environment_reuses_primary_venv(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            venv = main / ".venv" / "bin"
            git_dir = main / ".git" / "worktrees" / "lane"
            venv.mkdir(parents=True)
            worktree.mkdir()
            (venv / "python3").symlink_to("/usr/bin/python3")
            git_dir.mkdir(parents=True)
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            relocated = worktree / "relocated-venv"
            (relocated / "bin").mkdir(parents=True)
            (relocated / "bin" / "python3").symlink_to("/usr/bin/python3")
            local_venv = worktree / "disasm" / ".venv"
            local_venv.parent.mkdir(parents=True)
            local_venv.symlink_to(relocated, target_is_directory=True)
            with mock.patch.dict(os.environ, {}, clear=True):
                environment = runner._object_build_environment(worktree)
            self.assertEqual(environment["VENV"], str((main / ".venv").resolve()))
            self.assertEqual(
                environment["PYTHON"], str((main / ".venv").resolve() / "bin" / "python3")
            )
            self.assertNotEqual(environment["PYTHON"], "/usr/bin/python3")

    def test_primary_build_environment_prefers_root_venv(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            root_python = root / ".venv" / "bin" / "python3"
            historical_python = root / "disasm" / ".venv" / "bin" / "python3"
            for python in (root_python, historical_python):
                python.parent.mkdir(parents=True)
                python.write_text("python\n")
                python.chmod(0o755)
            with mock.patch.dict(os.environ, {}, clear=True):
                environment = runner._object_build_environment(root)
            self.assertEqual(environment["VENV"], str(root / ".venv"))
            self.assertEqual(environment["PYTHON"], str(root_python))

    def test_primary_build_environment_honors_shared_venv_override(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory) / "root"
            override = Path(directory) / "override"
            for venv in (override, root / ".venv", root / "disasm" / ".venv"):
                python = venv / "bin" / "python3"
                python.parent.mkdir(parents=True)
                python.write_text("python\n")
                python.chmod(0o755)
            with mock.patch.dict(
                os.environ, {"PRAGMA_SHARED_VENV": str(override)}, clear=True
            ):
                environment = runner._object_build_environment(root)
            self.assertEqual(environment["VENV"], str(override))
            self.assertEqual(environment["PYTHON"], str(override / "bin" / "python3"))

    def test_relative_shared_venv_override_is_anchored_before_make_chdir(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory) / "root"
            override = root / "custom-venv"
            python = override / "bin" / "python3"
            python.parent.mkdir(parents=True)
            python.write_text("python\n")
            python.chmod(0o755)
            (root / "disasm").mkdir()
            with mock.patch.dict(
                os.environ, {"PRAGMA_SHARED_VENV": "custom-venv"}, clear=True
            ):
                environment = runner._object_build_environment(root)
            self.assertEqual(environment["VENV"], str(override.resolve()))
            self.assertEqual(environment["PYTHON"], str(override.resolve() / "bin" / "python3"))
            self.assertEqual(
                Path(environment["VENV"]),
                (root / "disasm" / Path(environment["VENV"])).resolve(),
            )

    def test_linked_build_environment_honors_shared_venv_override(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            override = Path(directory) / "override"
            git_dir = main / ".git" / "worktrees" / "lane"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            for venv in (override, main / ".venv", main / "disasm" / ".venv"):
                python = venv / "bin" / "python3"
                python.parent.mkdir(parents=True)
                python.write_text("python\n")
                python.chmod(0o755)
            with mock.patch.dict(
                os.environ, {"PRAGMA_SHARED_VENV": str(override)}, clear=True
            ):
                environment = runner._object_build_environment(worktree)
            self.assertEqual(environment["VENV"], str(override))
            self.assertEqual(environment["PYTHON"], str(override / "bin" / "python3"))

    def test_worktree_oracle_links_primary_nonmatchings(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            oracle = main / "disasm" / "asm" / "us" / "nonmatchings"
            git_dir = main / ".git" / "worktrees" / "lane"
            oracle.mkdir(parents=True)
            worktree.mkdir()
            git_dir.mkdir(parents=True)
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            runner._ensure_worktree_oracles(worktree)
            local = worktree / "disasm" / "asm" / "us" / "nonmatchings"
            self.assertTrue(local.is_symlink())
            self.assertEqual(local.resolve(), oracle.resolve())

    def test_worktree_oracle_overlays_missing_owner_directory(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            oracle = main / "disasm" / "asm" / "us" / "nonmatchings" / "fragments" / "20" / "owner"
            git_dir = main / ".git" / "worktrees" / "lane"
            oracle.mkdir(parents=True)
            (oracle / "func_a.s").write_text("")
            (worktree / "disasm" / "asm" / "us" / "nonmatchings" / "fragments").mkdir(parents=True)
            worktree.mkdir(exist_ok=True)
            git_dir.mkdir(parents=True)
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            source = worktree / "disasm" / "src" / "owner.c"
            source.parent.mkdir(parents=True)
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/owner/func_a.s")\n')
            runner._ensure_worktree_oracles(worktree, source)
            local = worktree / "disasm" / "asm" / "us" / "nonmatchings" / "fragments" / "20" / "owner"
            self.assertTrue(local.is_symlink())
            self.assertEqual(local.resolve(), oracle.resolve())

    def test_worktree_oracle_preserves_private_extraction(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "lane"
            shared = main / "disasm" / "asm" / "us" / "nonmatchings" / "primary_only"
            shared.mkdir(parents=True)
            git_dir.mkdir(parents=True)
            local = worktree / "disasm" / "asm" / "us" / "nonmatchings"
            local.mkdir(parents=True)
            oracle = local / "local" / "func.s"
            oracle.parent.mkdir()
            oracle.write_text("local oracle\n")
            marker = worktree / "disasm" / "build" / ".pragma_private_gate_bootstrap.json"
            runner._write_gate_bootstrap_marker(
                marker,
                {
                    "schema": 2,
                    "outputs": {"asm_oracles": runner._private_asm_manifest(worktree)},
                },
            )
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            runner._ensure_worktree_oracles(worktree, full_tree=True)
            self.assertFalse((local / "primary_only").exists())

    def _oracle_worktree(self, directory: str):
        """A worktree with a private oracle tree plus a primary checkout."""
        main = Path(directory) / "main"
        worktree = Path(directory) / "worktree"
        git_dir = main / ".git" / "worktrees" / "lane"
        git_dir.mkdir(parents=True)
        shared = main / "disasm" / "asm" / "us" / "nonmatchings" / "owner"
        shared.mkdir(parents=True)
        (shared / "func_a.s").write_text("glabel func_a\n")
        (shared / "func_b.s").write_text("glabel func_b\n")
        local = worktree / "disasm" / "asm" / "us" / "nonmatchings" / "owner"
        local.mkdir(parents=True)
        # The private extraction produced func_a but never produced func_b.
        (local / "func_a.s").write_text("glabel func_a\n")
        source = worktree / "disasm" / "src" / "owner.c"
        source.parent.mkdir(parents=True)
        source.write_text(
            '#pragma GLOBAL_ASM("asm/us/nonmatchings/owner/func_a.s")\n'
            '#pragma GLOBAL_ASM("asm/us/nonmatchings/owner/func_b.s")\n'
        )
        (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
        return main, worktree, source

    def test_marker_rejects_a_dependency_the_extraction_never_produced(self) -> None:
        # Regression: a required oracle that is missing on disk is also absent
        # from the manifest, so `recorded.get(key) != _file_fingerprint(path)`
        # compared None against None and the marker validated a tree that
        # cannot compile.
        with tempfile.TemporaryDirectory() as directory:
            _, worktree, source = self._oracle_worktree(directory)
            marker = {
                "schema": 2,
                "outputs": {"asm_oracles": runner._private_asm_manifest(worktree)},
            }
            recorded = marker["outputs"]["asm_oracles"]
            self.assertNotIn(
                "disasm/asm/us/nonmatchings/owner/func_b.s", recorded,
                "fixture must model an oracle the extraction never produced",
            )
            self.assertFalse(
                runner._private_asm_marker_usable(
                    worktree, marker, source_path=source, full_tree=False
                )
            )

    def test_marker_still_accepts_a_complete_private_extraction(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            _, worktree, source = self._oracle_worktree(directory)
            local = worktree / "disasm" / "asm" / "us" / "nonmatchings" / "owner"
            (local / "func_b.s").write_text("glabel func_b\n")
            marker = {
                "schema": 2,
                "outputs": {"asm_oracles": runner._private_asm_manifest(worktree)},
            }
            self.assertTrue(
                runner._private_asm_marker_usable(
                    worktree, marker, source_path=source, full_tree=False
                )
            )

    def test_missing_oracle_is_backfilled_from_primary_as_a_real_file(self) -> None:
        # The bootstrap must not record an extraction that cannot compile.
        # The backfilled file has to be a real file: _private_asm_manifest
        # skips symlinks and _remove_shared_asm_overlays deletes them.
        with tempfile.TemporaryDirectory() as directory:
            _, worktree, _ = self._oracle_worktree(directory)
            unresolved = runner._backfill_missing_private_oracles(worktree)
            self.assertEqual(unresolved, [])
            restored = worktree / "disasm" / "asm" / "us" / "nonmatchings" / "owner" / "func_b.s"
            self.assertTrue(restored.is_file())
            self.assertFalse(restored.is_symlink())
            self.assertEqual(restored.read_text(), "glabel func_b\n")
            # ... and it is now recorded, so the marker validates.
            recorded = runner._private_asm_manifest(worktree)
            self.assertIn("disasm/asm/us/nonmatchings/owner/func_b.s", recorded)

    def test_backfill_reports_an_oracle_the_primary_cannot_supply(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main, worktree, _ = self._oracle_worktree(directory)
            (main / "disasm" / "asm" / "us" / "nonmatchings" / "owner" / "func_b.s").unlink()
            self.assertEqual(
                runner._backfill_missing_private_oracles(worktree),
                ["owner/func_b.s"],
            )

    def test_backfill_replaces_a_symlinked_oracle_with_a_real_file(self) -> None:
        # A symlink overlay does not survive the next bootstrap, so it must be
        # materialised rather than left in place.
        with tempfile.TemporaryDirectory() as directory:
            main, worktree, _ = self._oracle_worktree(directory)
            local = worktree / "disasm" / "asm" / "us" / "nonmatchings" / "owner" / "func_b.s"
            local.symlink_to(main / "disasm" / "asm" / "us" / "nonmatchings" / "owner" / "func_b.s")
            self.assertEqual(runner._backfill_missing_private_oracles(worktree), [])
            self.assertFalse(local.is_symlink())
            self.assertTrue(local.is_file())

    def test_unrelated_build_failure_is_not_the_candidate_s_fault(self) -> None:
        # The real output that made every re-gate report compare_rejected:
        # the gate builds the whole tree, an untouched file failed the host
        # clang check, and the candidate under test was blamed for it.
        output = (
            "src/fragments/22/fragment22_14B090.c:315:23: error: too few "
            "arguments to function call, expected 2, have 0\n"
            "make: *** [build/src/fragments/22/fragment22_14B090.o] Error 1\n"
            "make: *** Waiting for unfinished jobs....\n"
        )
        self.assertEqual(
            runner._unrelated_build_failures(output, "build/src/585D0.o"),
            ["build/src/fragments/22/fragment22_14B090.o"],
        )

    def test_candidate_s_own_object_failing_is_still_its_fault(self) -> None:
        output = "make: *** [build/src/585D0.o] Error 1\n"
        self.assertEqual(runner._unrelated_build_failures(output, "build/src/585D0.o"), [])

    def test_rom_target_failure_alone_is_not_an_unrelated_failure(self) -> None:
        # The ROM/ELF target fails as a consequence of anything upstream and
        # names no source, so it must not be read as an unrelated breakage.
        output = "make: *** [build/pokestadiumgs-us.z64] Error 1\n"
        self.assertEqual(runner._unrelated_build_failures(output, "build/src/585D0.o"), [])

    def test_failed_make_targets_handles_sub_make_prefixes(self) -> None:
        output = (
            "make[1]: *** [build/src/a.o] Error 1\n"
            "make: *** [build/src/b.o] Error 2\n"
        )
        self.assertEqual(
            runner._failed_make_targets(output), ["build/src/a.o", "build/src/b.o"]
        )

    def test_gate_environment_broken_is_not_a_rejection_or_a_resend_block(self) -> None:
        # The whole point of the distinct status: it must not poison the
        # futility fingerprints, and must not stop the body being re-sent
        # once the environment is repaired.
        self.assertNotIn("gate_environment_broken", runner._REJECTED_ATTEMPT_STATUSES)
        self.assertNotIn("gate_environment_broken", runner._DUPLICATE_BLOCKING_STATUSES)

    def test_synthetic_sources_never_reach_the_shared_probe_stats_ledger(self) -> None:
        # A test's temp-dir source, and a scratch copy, teach a later run
        # nothing. 227 such rows had accumulated in the primary checkout's
        # shared ledger before this guard.
        with mock.patch.dict(os.environ, {}, clear=False):
            os.environ.pop("PRAGMA_PROBE_STATS", None)
            self.assertFalse(runner._is_recordable_source(Path("/var/folders/x/T/tmp1/synthetic.c")))
            self.assertFalse(
                runner._is_recordable_source(
                    Path("/repo/disasm/scratch/tmpabcd/synthetic.c")
                )
            )
            self.assertTrue(runner._is_recordable_source(Path("/repo/disasm/src/585D0.c")))
            self.assertTrue(runner._is_recordable_source(Path("disasm/src/585D0.c")))

    def test_an_explicit_stats_destination_accepts_any_source(self) -> None:
        # container_merge --fresh-history and the runner's own row-shaping
        # tests both point PRAGMA_PROBE_STATS at a file they own; the guard
        # protects the shared default ledger, not a chosen destination.
        with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": "/tmp/history.jsonl"}):
            self.assertTrue(
                runner._is_recordable_source(Path("/var/folders/x/T/tmp1/synthetic.c"))
            )

    def test_record_probe_stats_writes_nothing_for_a_synthetic_source(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text("void func_a(void) {}\n")
            ledger = Path(directory) / "shared" / "probe-stats.jsonl"
            attempts = [{"index": 0, "function": "func_a", "status": "compare_rejected"}]
            with mock.patch.dict(os.environ, {}, clear=False):
                os.environ.pop("PRAGMA_PROBE_STATS", None)
                with mock.patch.object(runner, "_probe_stats_target", return_value=ledger):
                    runner._record_probe_stats(source, attempts, None)
                    self.assertFalse(
                        ledger.exists(), "a synthetic source must not reach the ledger"
                    )
                    # A real tracked source still records, so the guard has
                    # not simply disabled the writer.
                    runner._record_probe_stats(
                        Path("/repo/disasm/src/585D0.c"), attempts, None
                    )
                    self.assertTrue(ledger.exists())

    def test_worktree_gate_prerequisites_are_built_privately(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "lane"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            baserom = main / "disasm" / "baseroms" / "us" / "baserom.z64"
            baserom.parent.mkdir(parents=True)
            baserom.write_bytes(b"private immutable rom")
            venv = main / ".venv" / "bin" / "python3"
            venv.parent.mkdir(parents=True)
            venv.write_text("python")
            venv.chmod(0o755)
            for relative in ("yamls/us/header.yaml", "yamls/us/rom.yaml"):
                path = worktree / "disasm" / relative
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(relative)
            compiler_platform = "macos" if sys.platform == "darwin" else "linux"
            compiler = worktree / "disasm" / "tools" / "ido" / compiler_platform / "5.3" / "cc"
            compiler.parent.mkdir(parents=True)
            compiler.write_text("compiler")
            compiler.chmod(0o755)
            lib_makefile = worktree / "disasm" / "lib" / "ultralib" / "Makefile"
            lib_makefile.parent.mkdir(parents=True)
            lib_makefile.write_text("all:\n\t@true\n")
            tracked_asm = worktree / "disasm" / "asm" / "us" / "nonmatchings" / "alias.s"
            tracked_asm.parent.mkdir(parents=True)
            tracked_asm.write_text("tracked alias\n")

            # Mutable primary outputs must never be used as bootstrap inputs.
            primary_lib_sentinel = main / "disasm" / "lib" / "ultralib" / "build" / "primary-only"
            primary_lib_sentinel.parent.mkdir(parents=True)
            primary_lib_sentinel.write_text("do not copy")
            primary_linker_sentinel = main / "disasm" / "build" / "linker_scripts" / "primary-only"
            primary_linker_sentinel.parent.mkdir(parents=True)
            primary_linker_sentinel.write_text("do not copy")

            calls = []

            def bootstrap(repo_root, command, description, *, environment=None):
                self.assertEqual(repo_root, worktree)
                calls.append((description, command, environment))
                if description == "tracked assembly safety check":
                    return ""
                if description == "tracked assembly listing":
                    return "disasm/asm/us/nonmatchings/alias.s\0"
                if description == "local ROM extraction":
                    for name in ("undefined_syms_auto.ld", "undefined_funcs_auto.ld"):
                        path = worktree / "disasm" / "linker_scripts" / "us" / "auto" / name
                        path.parent.mkdir(parents=True, exist_ok=True)
                        path.write_text(f"source {name}\n")
                    generated_asm = (
                        worktree
                        / "disasm"
                        / "asm"
                        / "us"
                        / "nonmatchings"
                        / "generated"
                        / "func.s"
                    )
                    generated_asm.parent.mkdir(parents=True, exist_ok=True)
                    generated_asm.write_text("generated oracle\n")
                    tracked_asm.write_text("splat replacement\n")
                elif description == "private libultra build":
                    archive = worktree / "disasm" / "lib" / "ultralib" / "build" / "L" / "libultra" / "libultra.a"
                    archive.parent.mkdir(parents=True, exist_ok=True)
                    archive.write_bytes(b"locally built archive")
                elif description == "local auto linker preprocessing":
                    for name in ("undefined_syms_auto.ld", "undefined_funcs_auto.ld"):
                        path = worktree / "disasm" / "build" / "linker_scripts" / "us" / "auto" / name
                        path.parent.mkdir(parents=True, exist_ok=True)
                        path.write_text(f"local output {name}\n")
                return ""

            with mock.patch.object(runner, "_bootstrap_command", side_effect=bootstrap):
                runner._ensure_worktree_gate_prerequisites(worktree)

            local_baserom = worktree / "disasm" / "baseroms" / "us" / "baserom.z64"
            self.assertEqual(local_baserom.read_bytes(), baserom.read_bytes())
            self.assertFalse(local_baserom.is_symlink())
            self.assertEqual(list(local_baserom.parent.glob(".baserom.z64.*.tmp")), [])
            self.assertEqual(tracked_asm.read_text(), "tracked alias\n")
            self.assertFalse((worktree / "disasm" / "lib" / "ultralib" / "build" / "primary-only").exists())
            self.assertFalse((worktree / "disasm" / "build" / "linker_scripts" / "primary-only").exists())
            descriptions = [description for description, _, _ in calls]
            self.assertIn("local tool setup", descriptions)
            self.assertIn("local ROM extraction", descriptions)
            self.assertIn("tracked assembly listing", descriptions)
            self.assertIn("private libultra build", descriptions)
            self.assertIn("local auto linker preprocessing", descriptions)
            make_environments = [environment for description, _, environment in calls if description.startswith(("local ", "private "))]
            self.assertTrue(make_environments)
            self.assertTrue(all(environment["VENV"] == str((main / ".venv").resolve()) for environment in make_environments))
            self.assertTrue(
                all(
                    environment["PYTHON"]
                    == str((main / ".venv").resolve() / "bin" / "python3")
                    for environment in make_environments
                )
            )

            # Proven private outputs are reusable without invoking setup/build.
            calls.clear()
            with mock.patch.object(runner, "_bootstrap_command", side_effect=bootstrap):
                runner._ensure_worktree_gate_prerequisites(worktree)
            self.assertEqual(calls, [])

            # A missing locally extracted oracle invalidates the marker and
            # forces extraction instead of silently borrowing primary ASM.
            generated_asm = (
                worktree
                / "disasm"
                / "asm"
                / "us"
                / "nonmatchings"
                / "generated"
                / "func.s"
            )
            generated_asm.unlink()
            calls.clear()
            with mock.patch.object(runner, "_bootstrap_command", side_effect=bootstrap):
                runner._ensure_worktree_gate_prerequisites(worktree)
            self.assertIn("local ROM extraction", [description for description, _, _ in calls])
            self.assertTrue(generated_asm.is_file())

            # A dirty lib source invalidates provenance and forces a new local
            # extraction/build rather than reusing the archive.
            dirty = worktree / "disasm" / "lib" / "ultralib" / "src" / "dirty.c"
            dirty.parent.mkdir(parents=True)
            dirty.write_text("void dirty(void) {}\n")
            calls.clear()
            with mock.patch.object(runner, "_bootstrap_command", side_effect=bootstrap):
                runner._ensure_worktree_gate_prerequisites(worktree)
            descriptions = [description for description, _, _ in calls]
            self.assertIn("local ROM extraction", descriptions)
            self.assertIn("private libultra build", descriptions)

    def test_worktree_gate_rebuilds_corrupt_owned_archive(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "lane"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            primary_baserom = main / "disasm" / "baseroms" / "us" / "baserom.z64"
            primary_baserom.parent.mkdir(parents=True)
            primary_baserom.write_bytes(b"rom")
            compiler_platform = "macos" if sys.platform == "darwin" else "linux"
            compiler = worktree / "disasm" / "tools" / "ido" / compiler_platform / "5.3" / "cc"
            compiler.parent.mkdir(parents=True)
            compiler.write_text("compiler")
            compiler.chmod(0o755)
            auto_sources = tuple(
                worktree / "disasm" / "linker_scripts" / "us" / "auto" / name
                for name in ("undefined_syms_auto.ld", "undefined_funcs_auto.ld")
            )
            auto_outputs = tuple(
                worktree / "disasm" / "build" / "linker_scripts" / "us" / "auto" / name
                for name in ("undefined_syms_auto.ld", "undefined_funcs_auto.ld")
            )
            for path in (*auto_sources, *auto_outputs):
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(f"valid {path.name}\n")
            asm_oracle = worktree / "disasm" / "asm" / "us" / "nonmatchings" / "func.s"
            asm_oracle.parent.mkdir(parents=True)
            asm_oracle.write_text("private oracle\n")
            lib_build = worktree / "disasm" / "lib" / "ultralib" / "build"
            lib_build.mkdir(parents=True)
            runner._write_gate_bootstrap_marker(
                runner._lib_build_owner_path(lib_build), runner._LIB_BUILD_OWNERSHIP
            )
            archive = lib_build / "L" / "libultra" / "libultra.a"
            archive.parent.mkdir(parents=True)
            archive.write_bytes(b"original archive")
            identity = {"schema": 2, "inputs_sha256": "stable"}
            marker = worktree / "disasm" / "build" / ".pragma_private_gate_bootstrap.json"
            runner._write_gate_bootstrap_marker(
                marker,
                {
                    "schema": 2,
                    "identity": identity,
                    "outputs": {
                        "auto_sources": runner._output_manifest(worktree, auto_sources),
                        "auto_outputs": runner._output_manifest(worktree, auto_outputs),
                        "libultra": runner._output_manifest(worktree, (archive,)),
                        "asm_oracles": runner._private_asm_manifest(worktree),
                    },
                },
            )
            archive.write_bytes(b"x")
            calls = []

            def bootstrap(repo_root, command, description, *, environment=None):
                calls.append(description)
                if description == "private libultra build":
                    archive.parent.mkdir(parents=True, exist_ok=True)
                    archive.write_bytes(b"rebuilt archive")
                elif description == "local auto linker preprocessing":
                    for path in auto_outputs:
                        path.parent.mkdir(parents=True, exist_ok=True)
                        path.write_text(f"rebuilt {path.name}\n")
                return ""

            with mock.patch.object(runner, "_gate_bootstrap_identity", return_value=identity), mock.patch.object(
                runner, "_bootstrap_command", side_effect=bootstrap
            ):
                runner._ensure_worktree_gate_prerequisites(worktree)
            self.assertEqual(calls, ["private libultra build"])
            self.assertEqual(archive.read_bytes(), b"rebuilt archive")

            auto_outputs[0].write_bytes(b"x")
            calls.clear()
            with mock.patch.object(runner, "_gate_bootstrap_identity", return_value=identity), mock.patch.object(
                runner, "_bootstrap_command", side_effect=bootstrap
            ):
                runner._ensure_worktree_gate_prerequisites(worktree)
            self.assertEqual(calls, ["local auto linker preprocessing"])
            self.assertEqual(auto_outputs[0].read_text(), f"rebuilt {auto_outputs[0].name}\n")

    def test_worktree_gate_preserves_unowned_lib_build(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "lane"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            sentinel = worktree / "disasm" / "lib" / "ultralib" / "build" / "foreign-output"
            sentinel.parent.mkdir(parents=True)
            sentinel.write_text("preserve me")
            with mock.patch.object(
                runner,
                "_gate_bootstrap_identity",
                return_value={"schema": 2, "inputs_sha256": "stable"},
            ):
                with self.assertRaisesRegex(RuntimeError, "unowned libultra build tree.*preserved"):
                    runner._ensure_worktree_gate_prerequisites(worktree)
            self.assertEqual(sentinel.read_text(), "preserve me")

    def test_worktree_gate_prerequisites_refuse_dirty_tracked_asm(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "lane"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            for relative in ("yamls/us/header.yaml", "yamls/us/rom.yaml"):
                path = worktree / "disasm" / relative
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(relative)
            with mock.patch.object(
                runner,
                "_bootstrap_command",
                return_value=" M disasm/asm/us/nonmatchings/alias.s\n",
            ):
                with self.assertRaisesRegex(RuntimeError, "refused to re-extract.*tracked assembly"):
                    runner._ensure_worktree_gate_prerequisites(worktree)
            self.assertFalse((worktree / "disasm" / "baseroms" / "us" / "baserom.z64").exists())

    def test_worktree_gate_prerequisites_refuse_symlinked_output(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "lane"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            primary_baserom = main / "disasm" / "baseroms" / "us" / "baserom.z64"
            primary_baserom.parent.mkdir(parents=True)
            primary_baserom.write_bytes(b"rom")
            local_baserom = worktree / "disasm" / "baseroms" / "us" / "baserom.z64"
            local_baserom.parent.mkdir(parents=True)
            local_baserom.symlink_to(primary_baserom)
            with self.assertRaisesRegex(RuntimeError, "refused symlinked baserom destination"):
                runner._ensure_worktree_gate_prerequisites(worktree)
            self.assertEqual(primary_baserom.read_bytes(), b"rom")

    def test_worktree_gate_prerequisites_restore_asm_after_extract_failure(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "lane"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            baserom = main / "disasm" / "baseroms" / "us" / "baserom.z64"
            baserom.parent.mkdir(parents=True)
            baserom.write_bytes(b"rom")
            for relative in ("yamls/us/header.yaml", "yamls/us/rom.yaml"):
                path = worktree / "disasm" / relative
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(relative)
            tracked_asm = worktree / "disasm" / "asm" / "us" / "nonmatchings" / "alias.s"
            tracked_asm.parent.mkdir(parents=True)
            tracked_asm.write_text("tracked alias\n")
            descriptions = []

            def bootstrap(repo_root, command, description, *, environment=None):
                descriptions.append(description)
                if description == "tracked assembly safety check":
                    return ""
                if description == "tracked assembly listing":
                    return "disasm/asm/us/nonmatchings/alias.s\0"
                if description == "local ROM extraction":
                    tracked_asm.write_text("partial extraction\n")
                    raise RuntimeError("synthetic extraction failure")
                return ""

            with mock.patch.object(runner, "_bootstrap_command", side_effect=bootstrap):
                with self.assertRaisesRegex(RuntimeError, "synthetic extraction failure"):
                    runner._ensure_worktree_gate_prerequisites(worktree)
            self.assertEqual(tracked_asm.read_text(), "tracked alias\n")
            self.assertIn("tracked assembly listing", descriptions)

    def test_worktree_gate_snapshot_restores_broken_tracked_symlink(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            worktree = Path(directory)
            alias = worktree / "disasm" / "asm" / "us" / "nonmatchings" / "alias.s"
            alias.parent.mkdir(parents=True)
            alias.symlink_to("missing_target.s")
            with mock.patch.object(
                runner,
                "_bootstrap_command",
                return_value="disasm/asm/us/nonmatchings/alias.s\0",
            ):
                snapshot = runner._snapshot_tracked_asm(worktree)
            alias.unlink()
            alias.write_text("splat replacement\n")
            with mock.patch.object(runner, "_tracked_asm_changes", return_value=""):
                runner._restore_tracked_asm(worktree, snapshot)
            self.assertTrue(alias.is_symlink())
            self.assertEqual(os.readlink(alias), "missing_target.s")

    def test_compare_reports_private_bootstrap_failure_without_running_make(self) -> None:
        with mock.patch.object(
            runner,
            "_ensure_worktree_gate_prerequisites",
            side_effect=RuntimeError("synthetic private bootstrap failure"),
        ), mock.patch.object(runner, "_run_bounded_process_group") as run:
            result, output = runner._run_compare(Path("/tmp/repo"))
        self.assertEqual(result, 2)
        self.assertIn("synthetic private bootstrap failure", output)
        run.assert_not_called()

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
        probe_root = runner._probe_root(repo_root)
        before = set(probe_root.glob(".pragma_probe_*"))
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
                "_function_byte_views",
                return_value=(len(b"matching-bytes"), b"matching-bytes", b"matching-bytes"),
            ):
                result = runner._probe_one(
                    source,
                    "func_a",
                    "void func_a(void) {}",
                    b"matching-bytes",
                )
            self.assertEqual(result["status"], "probe_match")
            self.assertEqual(source.read_text(), original)
            self.assertEqual(set(probe_root.glob(".pragma_probe_*")), before)

    def test_probe_only_never_runs_full_gate_or_writes_source(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            original = '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
            source.write_text(original)
            with mock.patch.object(
                runner,
                "probe_candidates",
                return_value=[
                    {
                        "index": 0,
                        "function": "func_a",
                        "status": "probe_match",
                    }
                ],
            ), mock.patch.object(runner, "_try_candidate_detailed") as full_gate, mock.patch.object(
                runner, "compare_current_tree"
            ) as full_compare:
                result = runner.try_candidates_detailed(
                    source,
                    [("func_a", "void func_a(void) {}")],
                    gate=False,
                )
            self.assertEqual(result["batch_status"], "probe_only")
            self.assertEqual(result["probe_matches"], ["func_a"])
            self.assertEqual(result["accepted"], [])
            self.assertFalse(result["gate"])
            self.assertEqual(source.read_text(), original)
            full_gate.assert_not_called()
            full_compare.assert_not_called()

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

    def test_probe_fallback_is_limited_to_unavailable_function(self) -> None:
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
                    {
                        "index": 1,
                        "function": "func_b",
                        "status": "probe_unavailable",
                        "probe_reason": "missing_function_bytes",
                    },
                ],
            ), mock.patch.object(
                runner, "rebuild_source_object", return_value=0
            ), mock.patch.object(
                runner,
                "_try_candidate_detailed",
                return_value=(0, "accepted"),
            ) as full_gate, mock.patch.object(
                runner, "compare_current_tree", return_value=0
            ):
                result = runner.try_candidates_detailed(
                    source,
                    [
                        ("func_a", "void func_a(void) {}"),
                        ("func_b", "void func_b(void) {}"),
                    ],
                )
            self.assertEqual(result["accepted"], ["func_b"])
            full_gate.assert_called_once()
            self.assertEqual(full_gate.call_args.args[1], "func_b")

    def test_compile_timeout_is_reported_and_cleaned(self) -> None:
        repo_root = Path(__file__).resolve().parent.parent
        source_parent = repo_root / "disasm" / "src"
        with tempfile.TemporaryDirectory(dir=source_parent) as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text("void synthetic(void) {}\n")
            with mock.patch.object(
                runner,
                "_run_bounded_process_group",
                return_value=(124, "", True),
            ):
                result, object_path, output = runner._make_object(source, capture=True)
            self.assertEqual(result, 124)
            self.assertIn("compile timed out", output)
            self.assertFalse(object_path.exists())

    def test_compile_diagnostic_keeps_first_error_and_tail(self) -> None:
        output = (
            "warning before\n"
            "cfe: Error 123: bad candidate type\n"
            "  offending expression\n"
            "cfe: Warning 709: func_focus has an incompatible argument\n"
            + ("warning after\n" * 500)
        )
        diagnostic = runner._compile_diagnostic(output, tail_chars=120, focus="func_focus")
        self.assertIn("Error 123: bad candidate type", diagnostic)
        self.assertIn("func_focus has an incompatible argument", diagnostic)
        self.assertIn("warning after", diagnostic)

    def test_probe_stats_jsonl_records_candidate_text(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats_path = Path(directory) / "probe-stats.jsonl"
            attempts = [{
                "index": 0,
                "function": "func_a",
                "status": "compare_rejected",
                "probe_status": "probe_match",
                "mismatch_kind": "operand_or_scheduling_drift",
                "first_diff_offset": 4,
                "first_diff_instruction": 1,
                "expected_instruction": "0x24040001",
                "actual_instruction": "0x24050001",
                "expected_instruction_text": "addiu $a0, $zero, 1",
                "actual_instruction_text": "addiu $a1, $zero, 1",
                "prior_attempts": 7,
                "best_prior": {
                    "similarity_score": 0.95,
                    "mismatch_kind": "immediate_drift",
                },
                "futility": "repeated-drift: 12 prior rejected attempts",
                "repeated_drift": "repeated-drift: 12 prior rejected attempts",
                "assembly_diff": [{
                    "expected": "addiu $a0,$zero,1",
                    "actual": "addiu $a1,$zero,1",
                    "normalized_match": False,
                }],
                "assembly_diff_truncated": False,
                "diagnostic": "incompatible pointer conversion",
            }]
            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": str(stats_path)}):
                runner._record_probe_stats(
                    Path("synthetic.c"),
                    attempts,
                    ["wrapper-void"],
                    [("func_a", "void func_a(void) {}")],
                    "extern void helper(void);",
                )
            row = json.loads(stats_path.read_text())
            # New batch-level provenance fields (tools/probe_stats.py schema 2).
            self.assertEqual(row["schema_version"], 2)
            self.assertIn("timestamp", row)
            self.assertIn("batch_id", row)
            self.assertIn("worktree", row)
            self.assertEqual(row["counts"], {"wrapper-void:compare_rejected": 1})
            self.assertEqual(row["attempts"][0]["label"], "wrapper-void")
            self.assertEqual(row["attempts"][0]["candidate"], "void func_a(void) {}")
            self.assertEqual(row["attempts"][0]["diagnostic"], "incompatible pointer conversion")
            self.assertEqual(row["attempts"][0]["declarations"], "extern void helper(void);")
            self.assertEqual(row["attempts"][0]["first_diff_instruction"], 1)
            self.assertEqual(row["attempts"][0]["expected_instruction"], "0x24040001")
            self.assertEqual(row["attempts"][0]["prior_attempts"], 7)
            self.assertEqual(
                row["attempts"][0]["best_prior"],
                {"similarity_score": 0.95, "mismatch_kind": "immediate_drift"},
            )
            self.assertEqual(
                row["attempts"][0]["futility"],
                "repeated-drift: 12 prior rejected attempts",
            )
            self.assertEqual(
                row["attempts"][0]["repeated_drift"],
                "repeated-drift: 12 prior rejected attempts",
            )
            self.assertEqual(
                row["attempts"][0]["first_diff_fingerprint"],
                '["operand_or_scheduling_drift",4,1,"0x24040001","0x24050001"]',
            )
            # assembly_diff/assembly_diff_truncated are runtime-only (AGENTS.md)
            # and must never reach the persisted file.
            self.assertNotIn("assembly_diff", row["attempts"][0])
            self.assertNotIn("assembly_diff_truncated", row["attempts"][0])

    def test_linked_worktree_probe_stats_default_to_primary_ledger(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "lane"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            primary_stats = main / "disasm" / "probe-stats" / "probe-stats.jsonl"
            local_stats = worktree / "disasm" / "probe-stats" / "probe-stats.jsonl"
            attempts = [{"function": "func_shared", "status": "accepted"}]
            with mock.patch.object(runner, "RUNNER_REPO_ROOT", worktree), mock.patch.object(
                runner.probe_stats, "_git_head", return_value="deadbeef"
            ), mock.patch.dict(os.environ, {}, clear=True):
                runner._record_probe_stats(
                    worktree / "disasm" / "src" / "owner.c",
                    attempts,
                    ["shared:accepted"],
                )
            row = json.loads(primary_stats.read_text())
            self.assertEqual(row["attempts"][0]["function"], "func_shared")
            self.assertFalse(local_stats.exists())

    def test_primary_probe_stats_append_is_concurrency_safe(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "lane"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            primary_stats = main / "disasm" / "probe-stats" / "probe-stats.jsonl"

            def record(index: int) -> None:
                runner._record_probe_stats(
                    worktree / "disasm" / "src" / "owner.c",
                    [{"function": f"func_{index}", "status": "accepted"}],
                    [f"parallel:{index}"],
                )

            with mock.patch.object(runner, "RUNNER_REPO_ROOT", worktree), mock.patch.object(
                runner.probe_stats, "_git_head", return_value="deadbeef"
            ), mock.patch.dict(os.environ, {}, clear=True):
                with ThreadPoolExecutor(max_workers=8) as pool:
                    list(pool.map(record, range(24)))
            rows = [json.loads(line) for line in primary_stats.read_text().splitlines()]
            self.assertEqual(len(rows), 24)
            self.assertEqual(
                {row["attempts"][0]["function"] for row in rows},
                {f"func_{index}" for index in range(24)},
            )

    def test_linked_worktree_prior_history_reads_primary_ledger(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "lane"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            primary_stats = main / "disasm" / "probe-stats" / "probe-stats.jsonl"
            primary_stats.parent.mkdir(parents=True)
            primary_stats.write_text(
                json.dumps(
                    {
                        "timestamp": "2026-08-31T00:00:00Z",
                        "attempts": [{"function": "func_shared", "status": "accepted"}],
                    }
                )
                + "\n"
            )
            with mock.patch.object(runner, "RUNNER_REPO_ROOT", worktree), mock.patch.object(
                runner.variant_policy,
                "STATS_PATH_CURRENT",
                worktree / "disasm" / "probe-stats" / "probe-stats.jsonl",
            ), mock.patch.object(
                runner.variant_policy,
                "STATS_PATH_LEGACY",
                worktree / "disasm" / "build" / "probe-stats.jsonl",
            ), mock.patch.dict(os.environ, {}, clear=True):
                history = runner._load_prior_attempt_history()
            self.assertEqual(history["func_shared"][0]["status"], "accepted")

    def test_linked_worktree_history_merges_and_dedupes_old_local_ledgers(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "lane"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            primary_current = main / "disasm" / "probe-stats" / "probe-stats.jsonl"
            primary_legacy = main / "disasm" / "build" / "probe-stats.jsonl"
            local_current = worktree / "disasm" / "probe-stats" / "probe-stats.jsonl"
            local_legacy = worktree / "disasm" / "build" / "probe-stats.jsonl"

            def batch(batch_id: str, function: str) -> dict[str, object]:
                return {
                    "batch_id": batch_id,
                    "timestamp": "2026-08-31T00:00:00Z",
                    "attempts": [{"function": function, "status": "accepted"}],
                }

            shared = batch("shared-batch", "func_shared")
            for path, rows in (
                (primary_current, [shared, batch("primary-active", "func_primary")]),
                (primary_legacy, [batch("primary-legacy", "func_primary_legacy")]),
                (local_current, [shared, batch("local-active", "func_local")]),
                (local_legacy, [batch("local-legacy", "func_local_legacy")]),
            ):
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text("".join(json.dumps(row) + "\n" for row in rows))

            with mock.patch.object(runner, "RUNNER_REPO_ROOT", worktree), mock.patch.object(
                runner.variant_policy, "STATS_PATH_CURRENT", local_current
            ), mock.patch.object(
                runner.variant_policy, "STATS_PATH_LEGACY", local_legacy
            ), mock.patch.dict(os.environ, {}, clear=True):
                history = runner._load_prior_attempt_history()
            self.assertEqual(
                set(history),
                {
                    "func_shared",
                    "func_primary",
                    "func_primary_legacy",
                    "func_local",
                    "func_local_legacy",
                },
            )
            self.assertEqual(len(history["func_shared"]), 1)

    def test_migrated_legacy_history_without_batch_id_is_counted_once(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            current = root / "probe-stats" / "probe-stats.jsonl"
            legacy = root / "build" / "probe-stats.jsonl"
            marker = current.parent / ".migrated-from-legacy"
            legacy.parent.mkdir(parents=True)
            legacy.write_text(
                json.dumps(
                    {
                        "timestamp": "2026-08-31T00:00:00Z",
                        "attempts": [
                            {
                                "function": "func_legacy",
                                "status": "probe_rejected",
                                "similarity_score": 0.75,
                                "assembly_diff": [{"expected": "a", "actual": "b"}],
                                "assembly_diff_truncated": False,
                                "diagnostic": "x" * 3000,
                            }
                        ],
                    }
                )
                + "\n"
            )
            result = runner.probe_stats.migrate_legacy(
                legacy_path=legacy, target_path=current, marker_path=marker
            )
            self.assertTrue(result["migrated"])
            with mock.patch.object(
                runner.variant_policy, "STATS_PATH_CURRENT", current
            ), mock.patch.object(
                runner.variant_policy, "STATS_PATH_LEGACY", legacy
            ), mock.patch.dict(os.environ, {}, clear=True):
                history = runner._load_prior_attempt_history()
            self.assertEqual(len(history["func_legacy"]), 1)
            self.assertEqual(
                len(history["func_legacy"][0]["diagnostic"]),
                runner.probe_stats.DIAGNOSTIC_MAX_CHARS,
            )

    def test_raw_migration_identity_preserves_distinct_lossy_batches(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            current = root / "probe-stats" / "probe-stats.jsonl"
            legacy = root / "build" / "probe-stats.jsonl"
            migration_source = root / "migration-source.jsonl"
            marker = current.parent / ".migrated-from-legacy"

            def raw_batch(actual: str) -> dict[str, object]:
                return {
                    "timestamp": "2026-08-31T00:00:00Z",
                    "attempts": [
                        {
                            "function": "func_legacy",
                            "status": "probe_rejected",
                            "diagnostic": "x" * 3000,
                            "assembly_diff": [{"expected": "same", "actual": actual}],
                        }
                    ],
                }

            first = raw_batch("first")
            second = raw_batch("second")
            migration_source.write_text(json.dumps(first) + "\n")
            legacy.parent.mkdir(parents=True)
            legacy.write_text(json.dumps(first) + "\n" + json.dumps(second) + "\n")
            result = runner.probe_stats.migrate_legacy(
                legacy_path=migration_source,
                target_path=current,
                marker_path=marker,
            )
            self.assertTrue(result["migrated"])
            migrated = json.loads(current.read_text())
            provenance = migrated[runner.probe_stats.MIGRATION_PROVENANCE_KEY]
            self.assertEqual(provenance["sha256"], runner.probe_stats.raw_batch_sha256(first))

            with mock.patch.object(
                runner.variant_policy, "STATS_PATH_CURRENT", current
            ), mock.patch.object(
                runner.variant_policy, "STATS_PATH_LEGACY", legacy
            ), mock.patch.dict(os.environ, {}, clear=True):
                history = runner._load_prior_attempt_history()
            self.assertEqual(len(history["func_legacy"]), 2)

    def test_pre_provenance_migrated_copy_pairs_with_raw_legacy(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            current = root / "probe-stats" / "probe-stats.jsonl"
            legacy = root / "build" / "probe-stats.jsonl"
            raw = {
                "timestamp": "2026-08-31T00:00:00Z",
                "attempts": [
                    {
                        "function": "func_legacy",
                        "status": "probe_rejected",
                        "diagnostic": "x" * 3000,
                        "assembly_diff": [{"expected": "a", "actual": "b"}],
                    }
                ],
            }
            current.parent.mkdir(parents=True)
            current.write_text(json.dumps(runner.probe_stats.shape_legacy_batch(raw)) + "\n")
            (current.parent / runner.probe_stats.MIGRATION_MARKER_NAME).write_text(
                f"migrated 1 batches (1 attempts) from {legacy} to {current} "
                "on 2026-08-31T00:00:00Z\n"
            )
            legacy.parent.mkdir(parents=True)
            legacy.write_text(json.dumps(raw) + "\n")
            with mock.patch.object(
                runner.variant_policy, "STATS_PATH_CURRENT", current
            ), mock.patch.object(
                runner.variant_policy, "STATS_PATH_LEGACY", legacy
            ), mock.patch.dict(os.environ, {}, clear=True):
                history = runner._load_prior_attempt_history()
            self.assertEqual(len(history["func_legacy"]), 1)

    def test_pre_provenance_ambiguous_shapes_preserve_raw_multiplicity(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            current = root / "probe-stats" / "probe-stats.jsonl"
            legacy = root / "build" / "probe-stats.jsonl"

            def raw_batch(actual: str) -> dict[str, object]:
                return {
                    "timestamp": "2026-08-31T00:00:00Z",
                    "attempts": [
                        {
                            "function": "func_legacy",
                            "status": "probe_rejected",
                            "assembly_diff": [{"expected": "same", "actual": actual}],
                        }
                    ],
                }

            raw_batches = [raw_batch("first"), raw_batch("second")]
            shaped = runner.probe_stats.shape_legacy_batch(raw_batches[0])
            current.parent.mkdir(parents=True)
            current.write_text(json.dumps(shaped) + "\n" + json.dumps(shaped) + "\n")
            (current.parent / runner.probe_stats.MIGRATION_MARKER_NAME).write_text(
                f"migrated 2 batches (2 attempts) from {legacy} to {current} "
                "on 2026-08-31T00:00:00Z\n"
            )
            legacy.parent.mkdir(parents=True)
            legacy.write_text("".join(json.dumps(batch) + "\n" for batch in raw_batches))
            with mock.patch.object(
                runner.variant_policy, "STATS_PATH_CURRENT", current
            ), mock.patch.object(
                runner.variant_policy, "STATS_PATH_LEGACY", legacy
            ), mock.patch.dict(os.environ, {}, clear=True):
                history = runner._load_prior_attempt_history()
            self.assertEqual(len(history["func_legacy"]), 2)

    def test_pre_provenance_upgrade_never_cross_pairs_worktree_legacy(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "lane"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            primary_current = main / "disasm" / "probe-stats" / "probe-stats.jsonl"
            primary_legacy = main / "disasm" / "build" / "probe-stats.jsonl"
            local_current = worktree / "disasm" / "probe-stats" / "probe-stats.jsonl"
            local_legacy = worktree / "disasm" / "build" / "probe-stats.jsonl"
            raw = {
                "timestamp": "2026-08-31T00:00:00Z",
                "attempts": [
                    {
                        "function": "func_legacy",
                        "status": "probe_rejected",
                        "assembly_diff": [{"expected": "a", "actual": "b"}],
                    }
                ],
            }
            primary_current.parent.mkdir(parents=True)
            primary_current.write_text(
                json.dumps(runner.probe_stats.shape_legacy_batch(raw)) + "\n"
            )
            (primary_current.parent / runner.probe_stats.MIGRATION_MARKER_NAME).write_text(
                f"migrated 1 batches (1 attempts) from {primary_legacy} "
                f"to {primary_current} on 2026-08-31T00:00:00Z\n"
            )
            local_legacy.parent.mkdir(parents=True)
            local_legacy.write_text(json.dumps(raw) + "\n")
            with mock.patch.object(runner, "RUNNER_REPO_ROOT", worktree), mock.patch.object(
                runner.variant_policy, "STATS_PATH_CURRENT", local_current
            ), mock.patch.object(
                runner.variant_policy, "STATS_PATH_LEGACY", local_legacy
            ), mock.patch.dict(os.environ, {}, clear=True):
                history = runner._load_prior_attempt_history()
            self.assertEqual(len(history["func_legacy"]), 2)

    def test_prior_history_streams_ledgers_in_two_bounded_passes(self) -> None:
        path = Path("/synthetic/probe-stats.jsonl")
        calls = 0

        def batches(_paths: object):
            nonlocal calls
            calls += 1
            for index in range(200):
                yield path, {
                    "batch_id": f"batch-{index}",
                    "attempts": [
                        {"function": f"func_{index}", "status": "probe_rejected"}
                    ],
                }

        with mock.patch.object(
            runner, "_probe_stats_history_paths", return_value=(path,)
        ), mock.patch.object(
            runner.probe_stats, "iter_batches_with_paths", side_effect=batches
        ):
            history = runner._load_prior_attempt_history()

        self.assertEqual(calls, 2)
        self.assertEqual(len(history), 200)
        self.assertEqual(history["func_199"][0]["status"], "probe_rejected")

    def test_unverified_probe_hit_uses_sequential_gate_without_duplicate_compare(self) -> None:
        # An unverified probe hit (no ``link_verified`` key, e.g. baseline
        # shape unavailable) still uses the historical sequential gate.  That
        # gate already verified exactly this source text, so a single
        # sequential winner does not get a second, redundant combined
        # ``compare_current_tree`` run.
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
            ) as sequential_gate, mock.patch.object(
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
            sequential_gate.assert_called_once()
            full_compare.assert_not_called()
            self.assertEqual(result["timing"]["gate_mode"], "sequential")

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


def _section_entry(name: str, size: int, *, flags: str = "AX", type_: str = "PROGBITS") -> dict[str, object]:
    return {"name": name, "type": type_, "size": size, "flags": flags}


def _symbol_entry(value: int, size: int, type_: str, ndx: str, name: str) -> dict[str, object]:
    return {"value": value, "size": size, "type": type_, "ndx": ndx, "name": name}


def _relocation_shape(
    text: bytes,
    relocations: list[tuple[int, str, int]],
    *,
    target_value: int = 0,
    relocation_section: str = ".rel.text",
) -> dict[str, object]:
    return {
        "sections": {".text": _section_entry(".text", len(text))},
        "section_names": {1: ".text", 2: ".data"},
        "symbols": {
            2: _symbol_entry(0, len(text), "FUNC", "1", "func_a"),
            5: _symbol_entry(target_value, 0, "NOTYPE", "2", "target"),
        },
        "relocations": {relocation_section: relocations},
        "text": text,
    }


class LinkShapeTests(unittest.TestCase):
    """Synthetic, mock-based coverage for the link-shape verification helpers."""

    def test_parse_readelf_sections_reads_size_type_and_flags(self) -> None:
        text = "\n".join([
            "  [ 1] .text             PROGBITS        00000000 000034 020d20 01  AX  0   0 16",
            "  [ 3] .rodata           PROGBITS        00000000 000100 000020 00   A  0   0 16",
            "  [ 4] .bss              NOBITS          00000000 000120 000010 00  WA  0   0 8",
        ])
        sections = runner._parse_readelf_sections(text)
        self.assertEqual(sections[1]["name"], ".text")
        self.assertEqual(sections[1]["size"], 0x020d20)
        self.assertEqual(sections[1]["flags"], "AX")
        self.assertEqual(sections[3]["name"], ".rodata")
        self.assertEqual(sections[3]["size"], 0x20)
        self.assertEqual(sections[4]["type"], "NOBITS")
        self.assertIn("A", sections[4]["flags"])

    def test_parse_readelf_symbols_reads_hex_and_decimal_sizes(self) -> None:
        text = "\n".join([
            "     2: 0000082c    48 FUNC    GLOBAL DEFAULT    1 func_8002260C",
            "    13: 00000000     0 NOTYPE  GLOBAL DEFAULT  UND jtbl_829173B0",
            "     1: 00000000 0x20d20 SECTION LOCAL  DEFAULT    1 .text",
        ])
        symbols = runner._parse_readelf_symbols(text)
        self.assertEqual(
            symbols[2],
            {"value": 0x82c, "size": 48, "type": "FUNC", "ndx": "1", "name": "func_8002260C"},
        )
        self.assertEqual(symbols[13]["ndx"], "UND")
        self.assertEqual(symbols[13]["name"], "jtbl_829173B0")
        self.assertEqual(symbols[1]["size"], 0x20d20)
        self.assertEqual(symbols[1]["type"], "SECTION")
        self.assertEqual(symbols[1]["name"], ".text")

    def test_parse_readelf_relocations_extracts_symbol_index_from_info(self) -> None:
        text = "\n".join([
            "Relocation section '.rel.text' at offset 0x4cc80 contains 3 entries:",
            " Offset     Info    Type            Sym.Value  Sym. Name",
            "00000844  0004ff04 R_MIPS_26              00000000   func_80018728",
        ])
        relocations = runner._parse_readelf_relocations(text)
        self.assertIn(".rel.text", relocations)
        self.assertEqual(relocations[".rel.text"], [(0x844, "R_MIPS_26", 0x4ff)])

    def test_identical_shapes_are_verified(self) -> None:
        text = b"\x00" * 8
        shape = {
            "sections": {".text": _section_entry(".text", len(text))},
            "section_names": {1: ".text"},
            "symbols": {2: _symbol_entry(0, 8, "FUNC", "1", "func_a")},
            "relocations": {},
            "text": text,
        }
        symbol = runner._shape_symbol(shape, "func_a")
        verdict = runner._compare_link_shape(shape, shape, symbol, symbol)
        self.assertEqual(verdict["link_verified"], True)

    def test_extra_section_in_candidate_is_layout_drift(self) -> None:
        text = b"\x00" * 8
        baseline = {
            "sections": {".text": _section_entry(".text", len(text))},
            "section_names": {1: ".text"},
            "symbols": {2: _symbol_entry(0, 8, "FUNC", "1", "func_a")},
            "relocations": {},
            "text": text,
        }
        candidate = {
            "sections": {
                ".text": _section_entry(".text", len(text)),
                ".rodata": _section_entry(".rodata", 0x20, flags="A"),
            },
            "section_names": {1: ".text", 2: ".rodata"},
            "symbols": {2: _symbol_entry(0, 8, "FUNC", "1", "func_a")},
            "relocations": {},
            "text": text,
        }
        expected_symbol = runner._shape_symbol(baseline, "func_a")
        actual_symbol = runner._shape_symbol(candidate, "func_a")
        verdict = runner._compare_link_shape(baseline, candidate, expected_symbol, actual_symbol)
        self.assertFalse(verdict["link_verified"])
        self.assertEqual(verdict["link_mismatch"], "section_layout_drift")

    def test_text_size_difference_is_recoverable_text_layout_drift(self) -> None:
        baseline = {
            "sections": {".text": _section_entry(".text", 8)},
            "section_names": {1: ".text"},
            "symbols": {2: _symbol_entry(0, 8, "FUNC", "1", "func_a")},
            "relocations": {},
            "text": b"\x00" * 8,
        }
        candidate = {
            "sections": {".text": _section_entry(".text", 12)},
            "section_names": {1: ".text"},
            "symbols": {2: _symbol_entry(0, 12, "FUNC", "1", "func_a")},
            "relocations": {},
            "text": b"\x00" * 12,
        }
        verdict = runner._compare_link_shape(baseline, candidate, (0, 8), (0, 12))
        self.assertEqual(verdict["link_mismatch"], "text_layout_drift")
        self.assertFalse(verdict["link_verified"])

    def test_relocation_target_mismatch_is_relocation_drift(self) -> None:
        text = bytes.fromhex("0c000000 00000000")  # jal (addend 0); nop delay slot

        def shape(reloc_symbol_name: str) -> dict[str, object]:
            return {
                "sections": {".text": _section_entry(".text", len(text))},
                "section_names": {1: ".text"},
                "symbols": {
                    2: _symbol_entry(0, 8, "FUNC", "1", "func_a"),
                    5: _symbol_entry(0, 0, "NOTYPE", "UND", reloc_symbol_name),
                },
                "relocations": {".rel.text": [(0, "R_MIPS_26", 5)]},
                "text": text,
            }

        baseline = shape("func_target_a")
        candidate = shape("func_target_b")
        expected_symbol = runner._shape_symbol(baseline, "func_a")
        actual_symbol = runner._shape_symbol(candidate, "func_a")
        verdict = runner._compare_link_shape(baseline, candidate, expected_symbol, actual_symbol)
        self.assertEqual(verdict["link_mismatch"], "relocation_drift")

    def test_section_symbol_addend_normalizes_like_local_func_symbol(self) -> None:
        # Baseline references the function via the ``.text`` SECTION symbol
        # with an in-place addend of 0x20; candidate references a local FUNC
        # symbol whose value is 0x20 with an in-place addend of 0.  Both
        # resolve to the same ``.text``+0x20 target.
        baseline_text = bytes.fromhex("0c000008 00000000")  # jal +0x20; nop
        candidate_text = bytes.fromhex("0c000000 00000000")  # jal +0; nop
        baseline = {
            "sections": {".text": _section_entry(".text", len(baseline_text))},
            "section_names": {1: ".text"},
            "symbols": {
                2: _symbol_entry(0, 8, "FUNC", "1", "func_a"),
                3: _symbol_entry(0, 0, "SECTION", "1", ".text"),
            },
            "relocations": {".rel.text": [(0, "R_MIPS_26", 3)]},
            "text": baseline_text,
        }
        candidate = {
            "sections": {".text": _section_entry(".text", len(candidate_text))},
            "section_names": {1: ".text"},
            "symbols": {
                2: _symbol_entry(0, 8, "FUNC", "1", "func_a"),
                4: _symbol_entry(0x20, 4, "FUNC", "1", "func_target"),
            },
            "relocations": {".rel.text": [(0, "R_MIPS_26", 4)]},
            "text": candidate_text,
        }
        expected_symbol = runner._shape_symbol(baseline, "func_a")
        actual_symbol = runner._shape_symbol(candidate, "func_a")
        verdict = runner._compare_link_shape(baseline, candidate, expected_symbol, actual_symbol)
        self.assertEqual(verdict["link_verified"], True)

    def test_intra_text_branch_relocation_is_ignored(self) -> None:
        text = bytes.fromhex("10200001 00000000")  # beq $at, $zero, +1; nop
        baseline = {
            "sections": {".text": _section_entry(".text", len(text))},
            "section_names": {1: ".text"},
            "symbols": {
                2: _symbol_entry(0, 8, "FUNC", "1", "func_a"),
                3: _symbol_entry(0, 0, "SECTION", "1", ".text"),
            },
            "relocations": {".rel.text": [(0, "R_MIPS_PC16", 3)]},
            "text": text,
        }
        candidate = {
            "sections": {".text": _section_entry(".text", len(text))},
            "section_names": {1: ".text"},
            "symbols": {2: _symbol_entry(0, 8, "FUNC", "1", "func_a")},
            "relocations": {},
            "text": text,
        }
        expected_symbol = runner._shape_symbol(baseline, "func_a")
        actual_symbol = runner._shape_symbol(candidate, "func_a")
        verdict = runner._compare_link_shape(baseline, candidate, expected_symbol, actual_symbol)
        self.assertEqual(verdict["link_verified"], True)

    def test_missing_shape_is_unverified(self) -> None:
        verdict = runner._compare_link_shape(None, None, None, None)
        self.assertIsNone(verdict["link_verified"])
        self.assertEqual(verdict["link_mismatch"], "shape_unavailable")

    def test_relocation_fields_only_promotes_hi16_lo16_addend_spelling(self) -> None:
        expected = bytes.fromhex("3c080000 250800a4")
        actual = bytes.fromhex("3c080000 2508000c")
        relocations = [(0, "R_MIPS_HI16", 5), (4, "R_MIPS_LO16", 5)]
        baseline = _relocation_shape(expected, relocations, target_value=0)
        candidate = _relocation_shape(actual, relocations, target_value=0x98)
        self.assertTrue(
            runner._relocation_fields_only_match(
                baseline, candidate, (0, 8), (0, 8), expected, actual
            )
        )

    def test_relocation_fields_only_rejects_non_field_instruction_changes(self) -> None:
        expected = bytes.fromhex("3c080000 250800a4")
        relocations = [(0, "R_MIPS_HI16", 5), (4, "R_MIPS_LO16", 5)]
        baseline = _relocation_shape(expected, relocations)
        for actual in (
            bytes.fromhex("3c090000 250800a4"),  # register change
            bytes.fromhex("34080000 250800a4"),  # opcode change
        ):
            with self.subTest(actual=actual.hex()):
                candidate = _relocation_shape(actual, relocations)
                self.assertFalse(
                    runner._relocation_fields_only_match(
                        baseline, candidate, (0, 8), (0, 8), expected, actual
                    )
                )

    def test_relocation_fields_only_rejects_topology_mismatch(self) -> None:
        expected = bytes.fromhex("3c080000 250800a4")
        actual = bytes.fromhex("3c080000 2508000c")
        baseline = _relocation_shape(
            expected, [(0, "R_MIPS_HI16", 5), (4, "R_MIPS_LO16", 5)]
        )
        variants = (
            [(0, "R_MIPS_HI16", 5)],
            [(0, "R_MIPS_HI16", 5), (0, "R_MIPS_LO16", 5)],
            [(0, "R_MIPS_HI16", 5), (4, "R_MIPS_GPREL16", 5)],
        )
        for relocations in variants:
            with self.subTest(relocations=relocations):
                candidate = _relocation_shape(actual, relocations)
                self.assertFalse(
                    runner._relocation_fields_only_match(
                        baseline, candidate, (0, 8), (0, 8), expected, actual
                    )
                )

    def test_relocation_fields_only_rejects_unknown_rela_and_missing_shape(self) -> None:
        expected = bytes.fromhex("3c080000")
        actual = bytes.fromhex("3c080001")
        baseline = _relocation_shape(expected, [(0, "R_MIPS_HI16", 5)])
        variants = (
            _relocation_shape(actual, [(0, "R_MIPS_UNKNOWN", 5)]),
            _relocation_shape(
                actual, [(0, "R_MIPS_HI16", 5)], relocation_section=".rela.text"
            ),
            _relocation_shape(actual, [(4, "R_MIPS_HI16", 5)]),
            None,
        )
        for candidate in variants:
            with self.subTest(candidate=candidate):
                self.assertFalse(
                    runner._relocation_fields_only_match(
                        baseline, candidate, (0, 4), (0, 4), expected, actual
                    )
                )

    def test_probe_promotes_relocation_fields_only_but_forces_unverified(self) -> None:
        expected = bytes.fromhex("3c080000 250800a4")
        actual = bytes.fromhex("3c080000 2508000c")
        relocations = [(0, "R_MIPS_HI16", 5), (4, "R_MIPS_LO16", 5)]
        baseline = _relocation_shape(expected, relocations, target_value=0)
        candidate = _relocation_shape(actual, relocations, target_value=0x98)
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n')
            with mock.patch.object(
                runner, "_make_object", return_value=(0, Path(directory) / "probe.o", ""),
            ), mock.patch.object(
                runner, "_function_byte_views", return_value=(8, actual, actual),
            ), mock.patch.object(
                runner, "_object_link_shape", return_value=candidate,
            ):
                result = runner._probe_one(
                    source, "func_a", "void func_a(void) {}", expected,
                    expected_shape=baseline,
                )
        self.assertEqual(result["status"], "probe_match")
        self.assertEqual(result["probe_reason"], "relocation_fields_only")
        self.assertTrue(result["relocation_masked"])
        self.assertFalse(result["link_verified"])

    def test_probe_promotes_masked_match_despite_section_content_drift(self) -> None:
        expected = bytes.fromhex("3c080000 250800a4")
        actual = bytes.fromhex("3c080000 2508000c")
        relocations = [(0, "R_MIPS_HI16", 5), (4, "R_MIPS_LO16", 5)]
        baseline = _relocation_shape(expected, relocations, target_value=0)
        candidate = _relocation_shape(actual, relocations, target_value=0x98)
        baseline["sections"][".data"] = {
            **_section_entry(".data", 4, flags="WA"), "bytes": b"\0\0\0\0",
        }
        candidate["sections"][".data"] = {
            **_section_entry(".data", 4, flags="WA"), "bytes": b"\0\0\0\x0c",
        }
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n')
            with mock.patch.object(
                runner, "_make_object", return_value=(0, Path(directory) / "probe.o", ""),
            ), mock.patch.object(
                runner, "_function_byte_views", return_value=(8, actual, actual),
            ), mock.patch.object(
                runner, "_object_link_shape", return_value=candidate,
            ):
                result = runner._probe_one(
                    source, "func_a", "void func_a(void) {}", expected,
                    expected_shape=baseline,
                )
        self.assertEqual(result["status"], "probe_match")
        self.assertEqual(result["probe_reason"], "relocation_fields_only")
        self.assertTrue(result["relocation_masked"])
        self.assertFalse(result["link_verified"])
        self.assertEqual(result["link_mismatch"], "section_content_drift")

    def test_probe_one_reports_link_verified_with_expected_shape(self) -> None:
        expected_bytes = b"\x00" * 8
        baseline_shape = {
            "sections": {}, "section_names": {}, "symbols": {}, "relocations": {}, "text": expected_bytes,
        }
        candidate_shape = {
            "sections": {}, "section_names": {}, "symbols": {}, "relocations": {}, "text": expected_bytes,
        }
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n')
            with mock.patch.object(
                runner, "_make_object", return_value=(0, Path(directory) / "probe.o", ""),
            ), mock.patch.object(
                runner, "_function_byte_views",
                return_value=(len(expected_bytes), expected_bytes, expected_bytes),
            ), mock.patch.object(
                runner, "_object_link_shape", return_value=candidate_shape,
            ) as shape_call, mock.patch.object(
                runner, "_shape_symbol", return_value=(0, 8),
            ):
                result = runner._probe_one(
                    source, "func_a", "void func_a(void) {}", expected_bytes,
                    expected_shape=baseline_shape,
                )
        self.assertEqual(result["status"], "probe_match")
        self.assertTrue(result["link_verified"])
        self.assertIsInstance(result["probe_seconds"], float)
        shape_call.assert_called_once()

    def test_probe_one_rejects_section_layout_drift(self) -> None:
        expected_bytes = b"\x00" * 8
        baseline_shape = {
            "sections": {".text": _section_entry(".text", 8)},
            "section_names": {1: ".text"},
            "symbols": {2: _symbol_entry(0, 8, "FUNC", "1", "func_a")},
            "relocations": {},
            "text": expected_bytes,
        }
        candidate_shape = {
            "sections": {
                ".text": _section_entry(".text", 8),
                ".rodata": _section_entry(".rodata", 0x10, flags="A"),
            },
            "section_names": {1: ".text", 2: ".rodata"},
            "symbols": {2: _symbol_entry(0, 8, "FUNC", "1", "func_a")},
            "relocations": {},
            "text": expected_bytes,
        }
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n')
            with mock.patch.object(
                runner, "_make_object", return_value=(0, Path(directory) / "probe.o", ""),
            ), mock.patch.object(
                runner, "_function_byte_views",
                return_value=(len(expected_bytes), expected_bytes, expected_bytes),
            ), mock.patch.object(
                runner, "_object_link_shape", return_value=candidate_shape,
            ), mock.patch.object(
                runner, "_shape_symbol", return_value=(0, 8),
            ), mock.patch.object(
                runner, "_function_mismatch_details", return_value={},
            ):
                result = runner._probe_one(
                    source, "func_a", "void func_a(void) {}", expected_bytes,
                    expected_shape=baseline_shape,
                )
        self.assertEqual(result["status"], "probe_rejected")
        self.assertEqual(result["probe_reason"], "section_layout_drift")
        self.assertEqual(result["mismatch_kind"], "section_layout_drift")

    def test_probe_exact_bytes_leaves_section_content_drift_unverified(self) -> None:
        expected = b"\0" * 4
        baseline = _relocation_shape(expected, [])
        candidate = _relocation_shape(expected, [])
        baseline["sections"][".data"] = {
            **_section_entry(".data", 4, flags="WA"), "bytes": b"\0\0\0\0",
        }
        candidate["sections"][".data"] = {
            **_section_entry(".data", 4, flags="WA"), "bytes": b"\0\0\0\x04",
        }
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n')
            with mock.patch.object(
                runner, "_make_object", return_value=(0, Path(directory) / "probe.o", ""),
            ), mock.patch.object(
                runner, "_function_byte_views", return_value=(4, expected, expected),
            ), mock.patch.object(
                runner, "_object_link_shape", return_value=candidate,
            ):
                result = runner._probe_one(
                    source, "func_a", "void func_a(void) {}", expected,
                    expected_shape=baseline,
                )
        self.assertEqual(result["status"], "probe_match")
        self.assertFalse(result["link_verified"])
        self.assertEqual(result["link_mismatch"], "section_content_drift")

    def test_probe_rejects_masked_match_with_section_layout_drift(self) -> None:
        expected = bytes.fromhex("3c080000")
        actual = bytes.fromhex("3c080001")
        relocations = [(0, "R_MIPS_HI16", 5)]
        baseline = _relocation_shape(expected, relocations)
        candidate = _relocation_shape(actual, relocations)
        candidate["sections"][".rodata"] = _section_entry(
            ".rodata", 0x10, flags="A"
        )
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n')
            with mock.patch.object(
                runner, "_make_object", return_value=(0, Path(directory) / "probe.o", ""),
            ), mock.patch.object(
                runner, "_function_byte_views", return_value=(4, actual, actual),
            ), mock.patch.object(
                runner, "_object_link_shape", return_value=candidate,
            ), mock.patch.object(
                runner, "_function_mismatch_details", return_value={},
            ):
                result = runner._probe_one(
                    source, "func_a", "void func_a(void) {}", expected,
                    expected_shape=baseline,
                )
        self.assertEqual(result["status"], "probe_rejected")
        self.assertEqual(result["probe_reason"], "section_layout_drift")

    def test_probe_one_without_expected_shape_leaves_link_verified_none(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n')
            with mock.patch.object(
                runner, "_make_object", return_value=(0, Path(directory) / "probe.o", ""),
            ), mock.patch.object(
                runner, "_function_byte_views", return_value=(8, b"\x00" * 8, b"\x00" * 8),
            ), mock.patch.object(runner, "_object_link_shape") as shape_call:
                result = runner._probe_one(source, "func_a", "void func_a(void) {}", b"\x00" * 8)
        self.assertIsNone(result["link_verified"])
        shape_call.assert_not_called()

    def test_probe_stats_records_timing_and_link_verified(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats_path = Path(directory) / "probe-stats.jsonl"
            attempts = [{
                "index": 0,
                "function": "func_a",
                "status": "accepted",
                "probe_status": "probe_match",
                "link_verified": False,
                "link_mismatch": None,
                "relocation_masked": True,
                "probe_seconds": 0.01,
            }]
            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": str(stats_path)}):
                runner._record_probe_stats(
                    Path("synthetic.c"),
                    attempts,
                    ["m2c:s32-s32"],
                    [("func_a", "void func_a(void) {}")],
                    timing={"probe_seconds": 1.5, "gate_runs": 1},
                )
            row = json.loads(stats_path.read_text())
            self.assertEqual(row["timing"], {"probe_seconds": 1.5, "gate_runs": 1})
            self.assertFalse(row["attempts"][0]["link_verified"])
            self.assertTrue(row["attempts"][0]["relocation_masked"])

    def test_probe_stats_records_batch_status(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats_path = Path(directory) / "probe-stats.jsonl"
            attempts = [{
                "index": 0,
                "function": "func_a",
                "status": "combined_compile_failed",
                "probe_status": "probe_match",
            }]
            with mock.patch.dict(os.environ, {"PRAGMA_PROBE_STATS": str(stats_path)}):
                runner._record_probe_stats(
                    Path("synthetic.c"),
                    attempts,
                    ["m2c:s32-s32"],
                    [("func_a", "void func_a(void) {}")],
                    timing={"probe_seconds": 0.5},
                    batch_status="combined_compile_failed",
                )
            row = json.loads(stats_path.read_text())
            self.assertEqual(row["batch_status"], "combined_compile_failed")

    def test_ensure_baseline_object_caches_and_rebuilds_on_mtime_change(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            object_path = Path(directory) / "synthetic.o"
            source.write_text("void synthetic(void) {}\n")
            object_path.write_bytes(b"stub")
            key = source.resolve()
            runner._BASELINE_OBJECT_STATE.pop(key, None)
            try:
                with mock.patch.object(runner, "rebuild_source_object", return_value=0) as rebuild:
                    self.assertTrue(runner._ensure_baseline_object(source, object_path))
                    self.assertEqual(rebuild.call_count, 1)
                    self.assertTrue(runner._ensure_baseline_object(source, object_path))
                    self.assertEqual(rebuild.call_count, 1)
                    later = time.time() + 5
                    later_ns = int(later * 1_000_000_000)
                    os.utime(source, ns=(later_ns, later_ns))
                    self.assertTrue(runner._ensure_baseline_object(source, object_path))
                    self.assertEqual(rebuild.call_count, 2)
            finally:
                runner._BASELINE_OBJECT_STATE.pop(key, None)

    def test_ensure_baseline_object_failed_rebuild_is_not_cached(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            object_path = Path(directory) / "synthetic.o"
            source.write_text("void synthetic(void) {}\n")
            object_path.write_bytes(b"stub")
            key = source.resolve()
            runner._BASELINE_OBJECT_STATE.pop(key, None)
            try:
                with mock.patch.object(runner, "rebuild_source_object", return_value=1):
                    self.assertFalse(runner._ensure_baseline_object(source, object_path))
                self.assertNotIn(key, runner._BASELINE_OBJECT_STATE)
            finally:
                runner._BASELINE_OBJECT_STATE.pop(key, None)


class GateFlowTests(unittest.TestCase):
    """Combined-gate-with-sequential-fallback coverage for ``try_candidates_detailed``."""

    def test_single_link_verified_hit_uses_combined_gate_once(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n')
            with mock.patch.object(
                runner, "probe_candidates",
                return_value=[
                    {"index": 0, "function": "func_a", "status": "probe_match", "link_verified": True},
                ],
            ), mock.patch.object(
                runner, "rebuild_source_object", return_value=0,
            ), mock.patch.object(
                runner, "_try_candidate_detailed",
            ) as sequential_gate, mock.patch.object(
                runner, "compare_current_tree", return_value=0,
            ) as full_compare:
                result = runner.try_candidates_detailed(
                    source, [("func_a", "void func_a(void) { return; }")],
                )
            sequential_gate.assert_not_called()
            full_compare.assert_called_once()
            self.assertEqual(result["accepted"], ["func_a"])
            self.assertEqual(result["attempts"][0]["probe_status"], "probe_match")
            self.assertEqual(result["attempts"][0]["status"], "accepted")
            self.assertEqual(result["timing"]["gate_runs"], 1)
            self.assertEqual(result["timing"]["gate_mode"], "combined")
            text = source.read_text()
            self.assertIn("void func_a(void) { return; }", text)
            self.assertNotIn("GLOBAL_ASM", text)

    def test_two_link_verified_hits_share_one_combined_gate(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_b.s")\n'
            )
            with mock.patch.object(
                runner, "probe_candidates",
                return_value=[
                    {"index": 0, "function": "func_a", "status": "probe_match", "link_verified": True},
                    {"index": 1, "function": "func_b", "status": "probe_match", "link_verified": True},
                ],
            ), mock.patch.object(
                runner, "rebuild_source_object", return_value=0,
            ), mock.patch.object(
                runner, "_try_candidate_detailed",
            ) as sequential_gate, mock.patch.object(
                runner, "compare_current_tree", return_value=0,
            ) as full_compare:
                result = runner.try_candidates_detailed(
                    source,
                    [
                        ("func_a", "void func_a(void) { return; }"),
                        ("func_b", "void func_b(void) { return; }"),
                    ],
                )
            sequential_gate.assert_not_called()
            full_compare.assert_called_once()
            self.assertEqual(sorted(result["accepted"]), ["func_a", "func_b"])

    def test_combined_gate_failure_falls_back_to_sequential_per_function(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_b.s")\n'
            )

            def fake_sequential(source_path: Path, function: str, candidate: str) -> tuple[int, str]:
                if function == "func_a":
                    return 0, "accepted"
                return 2, "compare_rejected"

            with mock.patch.object(
                runner, "probe_candidates",
                return_value=[
                    {"index": 0, "function": "func_a", "status": "probe_match", "link_verified": True},
                    {"index": 1, "function": "func_b", "status": "probe_match", "link_verified": True},
                ],
            ), mock.patch.object(
                runner, "rebuild_source_object", return_value=0,
            ), mock.patch.object(
                runner, "_try_candidate_detailed", side_effect=fake_sequential,
            ) as sequential_gate, mock.patch.object(
                runner, "compare_current_tree", return_value=1,
            ) as full_compare:
                result = runner.try_candidates_detailed(
                    source,
                    [
                        ("func_a", "void func_a(void) { return; }"),
                        ("func_b", "void func_b(void) { return; }"),
                    ],
                )
            self.assertEqual(sequential_gate.call_count, 2)
            self.assertEqual(full_compare.call_count, 1)
            self.assertEqual(result["timing"]["gate_mode"], "combined_then_sequential")
            self.assertIn("func_a", result["accepted"])
            func_b_attempt = next(item for item in result["attempts"] if item["function"] == "func_b")
            self.assertEqual(func_b_attempt["status"], "compare_rejected")
            self.assertIn("void func_a(void) { return; }", source.read_text())

    def test_deferred_variant_is_tried_after_earlier_variant_rejected_sequentially(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n')
            candidate0 = "void func_a(void) { int variant0; }"
            candidate1 = "void func_a(void) { int variant1; }"

            def fake_sequential(source_path: Path, function: str, candidate: str) -> tuple[int, str]:
                if "variant0" in candidate:
                    return 2, "compare_rejected"
                return 0, "accepted"

            with mock.patch.object(
                runner, "probe_candidates",
                return_value=[
                    {"index": 0, "function": "func_a", "status": "probe_match", "link_verified": True},
                    {"index": 1, "function": "func_a", "status": "probe_match", "link_verified": True},
                ],
            ), mock.patch.object(
                runner, "rebuild_source_object", return_value=0,
            ), mock.patch.object(
                runner, "_try_candidate_detailed", side_effect=fake_sequential,
            ) as sequential_gate, mock.patch.object(
                runner, "compare_current_tree", return_value=1,
            ):
                result = runner.try_candidates_detailed(
                    source, [("func_a", candidate0), ("func_a", candidate1)],
                )
            self.assertEqual(sequential_gate.call_count, 2)
            called_candidates = [call.args[2] for call in sequential_gate.call_args_list]
            self.assertEqual(called_candidates, [candidate0, candidate1])
            self.assertIn("func_a", result["accepted"])

    def test_mixed_masked_hit_is_gated_before_link_verified_combined_path(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_b.s")\n'
            )
            events: list[str] = []

            def sequential_gate(*args: object) -> tuple[int, str]:
                events.append("sequential")
                return 0, "accepted"

            def combined_gate(*args: object) -> int:
                events.append("combined")
                return 0

            with mock.patch.object(
                runner, "probe_candidates",
                return_value=[
                    {
                        "index": 0,
                        "function": "func_a",
                        "status": "probe_match",
                        "probe_reason": "relocation_fields_only",
                        "relocation_masked": True,
                        "link_verified": False,
                        "link_mismatch": "section_content_drift",
                    },
                    {"index": 1, "function": "func_b", "status": "probe_match", "link_verified": True},
                ],
            ), mock.patch.object(
                runner, "rebuild_source_object", return_value=0,
            ), mock.patch.object(
                runner, "_try_candidate_detailed", side_effect=sequential_gate,
            ) as sequential_gate, mock.patch.object(
                runner, "compare_current_tree", side_effect=combined_gate,
            ) as full_compare:
                result = runner.try_candidates_detailed(
                    source,
                    [
                        ("func_a", "void func_a(void) { return; }"),
                        ("func_b", "void func_b(void) { return; }"),
                    ],
                )
            sequential_gate.assert_called_once()
            full_compare.assert_called_once()
            self.assertEqual(events, ["sequential", "combined"])
            self.assertEqual(sorted(result["accepted"]), ["func_a", "func_b"])

    def test_incremental_install_drops_conflicting_winner(self) -> None:
        # Three link-verified hits for three different functions: the
        # second candidate's declaration only conflicts with the first once
        # both are installed together, mirroring the real m2c prototype
        # conflict (fragment 60: six verified winners, one shared-callee
        # prototype mismatch, ``combined_compile_failed`` lost all six).
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_b.s")\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_c.s")\n'
            )
            candidate_a = "void func_a(void) { int a; }"
            candidate_b = "void func_b(void) { int b; }"
            candidate_c = "void func_c(void) { int c; }"

            def fake_rebuild(path: Path) -> int:
                text = Path(path).read_text()
                return 1 if candidate_a in text and candidate_b in text else 0

            with mock.patch.object(
                runner, "probe_candidates",
                return_value=[
                    {"index": 0, "function": "func_a", "status": "probe_match", "link_verified": True},
                    {"index": 1, "function": "func_b", "status": "probe_match", "link_verified": True},
                    {"index": 2, "function": "func_c", "status": "probe_match", "link_verified": True},
                ],
            ), mock.patch.object(
                runner, "rebuild_source_object", side_effect=fake_rebuild,
            ), mock.patch.object(
                runner, "_try_candidate_detailed",
            ) as sequential_gate, mock.patch.object(
                runner, "compare_current_tree", return_value=0,
            ) as full_compare:
                result = runner.try_candidates_detailed(
                    source,
                    [
                        ("func_a", candidate_a),
                        ("func_b", candidate_b),
                        ("func_c", candidate_c),
                    ],
                )
            sequential_gate.assert_not_called()
            full_compare.assert_called_once()
            self.assertEqual(sorted(result["accepted"]), ["func_a", "func_c"])
            dropped = next(item for item in result["attempts"] if item["function"] == "func_b")
            self.assertEqual(dropped["status"], "combined_compile_failed")
            self.assertEqual(dropped["probe_status"], "probe_match")
            self.assertEqual(dropped["reason"], "conflicts with an earlier winner in this batch")
            text = source.read_text()
            self.assertIn(candidate_a, text)
            self.assertIn(candidate_c, text)
            self.assertIn('GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_b.s")', text)
            self.assertGreaterEqual(result["timing"]["install_compiles"], 3)

    def test_final_install_drops_conflicting_sequential_winner(self) -> None:
        # Two link-verified hits: the combined compare rejects, so both are
        # gated individually and each passes alone.  The final incremental
        # install then discovers they conflict when combined and drops the
        # second rather than reverting the whole batch.
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_b.s")\n'
            )
            candidate_a = "void func_a(void) { int a; }"
            candidate_b = "void func_b(void) { int b; }"
            both_seen = {"count": 0}

            def fake_rebuild(path: Path) -> int:
                text = Path(path).read_text()
                if candidate_a in text and candidate_b in text:
                    both_seen["count"] += 1
                    return 0 if both_seen["count"] == 1 else 1
                return 0

            def fake_sequential(source_path: Path, function: str, candidate: str) -> tuple[int, str]:
                return 0, "accepted"

            with mock.patch.object(
                runner, "probe_candidates",
                return_value=[
                    {"index": 0, "function": "func_a", "status": "probe_match", "link_verified": True},
                    {"index": 1, "function": "func_b", "status": "probe_match", "link_verified": True},
                ],
            ), mock.patch.object(
                runner, "rebuild_source_object", side_effect=fake_rebuild,
            ), mock.patch.object(
                runner, "_try_candidate_detailed", side_effect=fake_sequential,
            ), mock.patch.object(
                runner, "compare_current_tree", return_value=1,
            ):
                result = runner.try_candidates_detailed(
                    source,
                    [("func_a", candidate_a), ("func_b", candidate_b)],
                )
            self.assertEqual(result["accepted"], ["func_a"])
            dropped = next(item for item in result["attempts"] if item["function"] == "func_b")
            self.assertEqual(dropped["status"], "combined_compile_failed")
            accepted_statuses = [
                item["function"] for item in result["attempts"]
                if item["status"] == "accepted"
            ]
            self.assertEqual(sorted(accepted_statuses), sorted(result["accepted"]))

    def test_final_combined_compare_rejection_reverts_accepted_statuses(self) -> None:
        # Two unverified hits are each individually gated and accepted, but
        # the final combined ROM compare (needed because they were never
        # tested together) rejects the pair.  Every attempt still marked
        # ``accepted`` afterward must be rewritten so stats never claim a
        # function that no longer owns its replacement in the file.
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_b.s")\n'
            )

            def fake_sequential(source_path: Path, function: str, candidate: str) -> tuple[int, str]:
                return 0, "accepted"

            with mock.patch.object(
                runner, "probe_candidates",
                return_value=[
                    {"index": 0, "function": "func_a", "status": "probe_match"},
                    {"index": 1, "function": "func_b", "status": "probe_match"},
                ],
            ), mock.patch.object(
                runner, "rebuild_source_object", return_value=0,
            ), mock.patch.object(
                runner, "_try_candidate_detailed", side_effect=fake_sequential,
            ), mock.patch.object(
                runner, "compare_current_tree", return_value=1,
            ) as full_compare:
                result = runner.try_candidates_detailed(
                    source,
                    [
                        ("func_a", "void func_a(void) { return; }"),
                        ("func_b", "void func_b(void) { return; }"),
                    ],
                )
            full_compare.assert_called_once()
            self.assertEqual(result["accepted"], [])
            self.assertEqual(result["batch_status"], "combined_compare_rejected")
            for attempt in result["attempts"]:
                self.assertEqual(attempt["status"], "combined_compare_rejected")


import dedupe_externs  # noqa: E402
import sweep_targets  # noqa: E402
import permute_candidate  # noqa: E402
import pragma_targets as targets  # noqa: E402
import try_pragma_compare_mcp as mcp  # noqa: E402
import variant_policy  # noqa: E402


class TargetDiscoveryTests(unittest.TestCase):
    def test_linked_worktree_draft_uses_primary_readonly_m2c(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "draft"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            script = main / "disasm" / "tools" / "m2c" / "m2c.py"
            script.parent.mkdir(parents=True)
            script.write_text("# primary read-only m2c\n")
            asm = worktree / "disasm" / "asm" / "us" / "nonmatchings" / "x" / "func_a.s"
            asm.parent.mkdir(parents=True)
            asm.write_text("glabel func_a\n  jr $ra\n   nop\n")
            owner = targets.Owner(
                "func_a",
                "disasm/src/x.c",
                "disasm/asm/us/nonmatchings/x/func_a.s",
            )
            completed = mock.Mock(returncode=0, stdout="void func_a(void) {}\n", stderr="")
            with mock.patch.object(targets, "REPO_ROOT", worktree), mock.patch.object(
                targets, "DISASM_ROOT", worktree / "disasm"
            ), mock.patch.object(targets, "_ASM_FALLBACK_ROOT", None), mock.patch.object(
                targets, "require_owner", return_value=owner
            ), mock.patch.object(
                targets, "function_asm", return_value={"instruction_count": 2}
            ), mock.patch.object(
                targets, "similar_solved", return_value=[]
            ), mock.patch.object(
                targets.subprocess, "run", return_value=completed
            ) as run, mock.patch.dict(os.environ, {}, clear=True):
                result = targets.draft_candidates(
                    "func_a", variants=["m2c"], context=False
                )

            self.assertEqual(result["drafts"][0]["code"], completed.stdout)
            command = run.call_args.args[0]
            self.assertEqual(Path(command[1]), script.resolve())
            self.assertEqual(run.call_args.kwargs["cwd"], worktree)
            self.assertEqual(
                run.call_args.kwargs["env"]["PYTHONDONTWRITEBYTECODE"], "1"
            )
            self.assertFalse((worktree / "disasm" / "tools" / "m2c").exists())

    def test_m2c_explicit_overrides_remain_authoritative(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            script = root / "custom" / "m2c.py"
            script.parent.mkdir()
            script.write_text("# override\n")
            with mock.patch.object(targets, "REPO_ROOT", root), mock.patch.dict(
                os.environ,
                {
                    "PRAGMA_M2C_SCRIPT": "custom/m2c.py",
                    "M2C_PYTHON": "custom/python3",
                },
                clear=True,
            ):
                self.assertEqual(targets.m2c_script(), script.resolve())
                self.assertEqual(
                    targets._m2c_python(), str((root / "custom" / "python3").resolve())
                )

    def test_readonly_tool_environment_forces_no_bytecode(self) -> None:
        with mock.patch.dict(
            os.environ, {"PYTHONDONTWRITEBYTECODE": "0", "TOOL_OPTION": "preserved"}, clear=True
        ):
            environment = targets.readonly_tool_environment()
        self.assertEqual(environment["PYTHONDONTWRITEBYTECODE"], "1")
        self.assertEqual(environment["TOOL_OPTION"], "preserved")

    def test_owner_index_maps_functions_to_sources(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source_root = root / "disasm" / "src"
            source_root.mkdir(parents=True)
            (source_root / "a.c").write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/a/func_a.s")\n'
                'void done(void) {}\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/a/func_b.s")\n'
            )
            probe = source_root / ".pragma_probe_x"
            probe.mkdir()
            (probe / "a.c").write_text('#pragma GLOBAL_ASM("asm/us/nonmatchings/a/func_z.s")\n')
            index = targets.owner_index(source_root, repo_root=root)
        self.assertEqual(sorted(index), ["func_a", "func_b"])
        self.assertEqual(index["func_a"].source, "disasm/src/a.c")
        self.assertEqual(index["func_a"].asm, "disasm/asm/us/nonmatchings/a/func_a.s")

    def test_repository_symbol_header_prefers_definitions_and_skips_s1_types(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source_root = root / "src"
            source_root.mkdir()
            (source_root / "a.c").write_text(
                "s32 func_a(s32 arg0) { return arg0; }\n"
                "typedef struct S1_Local S1_Local;\n"
                "S1_Local *func_s1(S1_Local *arg0) { return arg0; }\n"
                "typedef struct LocalOnly LocalOnly;\n"
                "LocalOnly *func_abc(LocalOnly *arg0) { return arg0; }\n"
            )
            (source_root / "b.c").write_text(
                "extern void func_a(void);\n"
                "extern s32 D_80000010;\n"
                "extern LocalOnly *D_80000014;\n"
            )
            header = root / "build" / "prototypes.h"
            generated = targets.repository_symbol_header(
                source_root=source_root, output_path=header, refresh=True,
            )
            text = generated.read_text()
        self.assertIn("s32 func_a(s32 arg0);", text)
        self.assertNotIn("void func_a(void);", text)
        self.assertIn("extern s32 D_80000010;", text)
        self.assertNotIn("func_s1", text)
        self.assertNotIn("func_abc", text)
        self.assertNotIn("D_80000014", text)

    def test_host_preprocess_command_strips_check_only_flags(self) -> None:
        check = [
            "gcc", "-MMD", "-MP", "-fsyntax-only", "-Iinclude", "-I", runner._RECIPE_DIRECTORY,
            "-o", runner._RECIPE_OBJECT, runner._RECIPE_SOURCE,
        ]
        command = runner.host_preprocess_command(check, "src/fragments/79/")
        self.assertEqual(
            command,
            ["gcc", "-Iinclude", "-I", "src/fragments/79/", "-E", "-P", "-D__attribute__(x)="],
        )

    def test_parse_check_recipe_finds_syntax_check_line(self) -> None:
        output = "\n".join([
            f"gcc -fsyntax-only -o {runner._RECIPE_OBJECT} {runner._RECIPE_SOURCE}",
            f"cc -c -o {runner._RECIPE_OBJECT} {runner._RECIPE_SOURCE}",
        ])
        self.assertEqual(runner._parse_check_recipe(output)[0], "gcc")
        self.assertEqual(runner._parse_probe_recipe(output)[0], "cc")


class PrototypeFallbackTests(unittest.TestCase):
    """``pragma_targets`` fallback prototype synthesis (item 3 of the issue).

    These never touch the real ``disasm/asm`` tree: it is mostly generated
    by the splat extraction step and is not fully materialized in every
    checkout, so every fixture here is a temp-dir ``.s`` file built by hand.
    """

    def test_infer_prototype_shape_single_argument_used_return(self) -> None:
        # $a0 is copied into $s0 before anything else touches it (a real
        # read-before-write use), $a1-$a3 are only ever written (callee
        # argument setup) before being read, and $v0 is loaded before the
        # final jr $ra.
        asm = (
            "glabel func_80021ED8\n"
            "    /* 0 80021ED8 0 */  addiu $sp, $sp, -0x20\n"
            "    /* 0 80021EDC 0 */  or    $s0, $a0, $zero\n"
            "    /* 0 80021EE0 0 */  or    $a1, $zero, $zero\n"
            "    /* 0 80021EE4 0 */  lw    $v0, 0x0($s0)\n"
            "    /* 0 80021EE8 0 */  jr    $ra\n"
            "    /* 0 80021EEC 0 */   nop\n"
        )
        self.assertEqual(targets.infer_prototype_shape(asm), (1, "s32"))
        self.assertEqual(
            targets.synthesize_fallback_prototype("func_80021ED8", asm),
            "s32 func_80021ED8(); /* synthesized */",
        )

    def test_infer_prototype_shape_void_leaf_with_no_argument_reads(self) -> None:
        asm = (
            "glabel func_80000100\n"
            "    /* 0 0 0 */  addiu $sp, $sp, -0x10\n"
            "    /* 0 0 0 */  sw    $ra, 0xc($sp)\n"
            "    /* 0 0 0 */  or    $a0, $zero, $zero\n"
            "    /* 0 0 0 */  jal   func_80000200\n"
            "    /* 0 0 0 */   nop\n"
            "    /* 0 0 0 */  lw    $ra, 0xc($sp)\n"
            "    /* 0 0 0 */  jr    $ra\n"
            "    /* 0 0 0 */   nop\n"
        )
        self.assertEqual(targets.infer_prototype_shape(asm), (0, "void"))

    def test_infer_prototype_shape_skips_leading_unused_argument_registers(self) -> None:
        # Only $a2 is ever read; arity still reports the highest qualifying
        # register index (3), not a count of distinct registers used.
        asm = (
            "glabel func_80000200\n"
            "    /* 0 0 0 */  addiu $sp, $sp, -0x10\n"
            "    /* 0 0 0 */  or    $v0, $a2, $zero\n"
            "    /* 0 0 0 */  jr    $ra\n"
            "    /* 0 0 0 */   nop\n"
        )
        self.assertEqual(targets.infer_prototype_shape(asm), (3, "s32"))

    def test_infer_prototype_shape_stack_argument_before_prologue_is_unprototyped(self) -> None:
        asm = (
            "glabel func_80000300\n"
            "    /* 0 0 0 */  lw    $t0, 0x10($sp)\n"
            "    /* 0 0 0 */  addiu $sp, $sp, -0x10\n"
            "    /* 0 0 0 */  jr    $ra\n"
            "    /* 0 0 0 */   nop\n"
        )
        self.assertEqual(targets.infer_prototype_shape(asm), (None, "void"))
        self.assertEqual(
            targets.synthesize_fallback_prototype("func_80000300", asm),
            "void func_80000300(); /* synthesized */",
        )

    def test_infer_prototype_shape_local_frame_offset_is_not_a_stack_argument(self) -> None:
        # Once the prologue has adjusted $sp, a later 0x18($sp) access is a
        # local variable slot, not an incoming stack argument -- it must not
        # trigger the unprototyped fallback.
        asm = (
            "glabel func_80000400\n"
            "    /* 0 0 0 */  addiu $sp, $sp, -0x20\n"
            "    /* 0 0 0 */  sw    $s0, 0x18($sp)\n"
            "    /* 0 0 0 */  lw    $s0, 0x18($sp)\n"
            "    /* 0 0 0 */  jr    $ra\n"
            "    /* 0 0 0 */   nop\n"
        )
        arity, return_type = targets.infer_prototype_shape(asm)
        self.assertIsNotNone(arity)
        self.assertEqual(return_type, "void")

    def test_repository_fallback_symbol_header_skips_declared_and_owned_symbols(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source_root = root / "src"
            source_root.mkdir()
            asm_root = root / "asm"
            (asm_root / "test").mkdir(parents=True)
            symbol_addrs = root / "symbol_addrs_code.txt"

            # Already declared in a tracked source: no synthesis wanted.
            (source_root / "owner.c").write_text(
                "extern void func_80000010(s32);\n"
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/test/func_80000020.s")\n'
            )
            # A live pragma owner: no synthesis wanted (its own candidate is
            # what will eventually define it).
            (asm_root / "test" / "func_80000020.s").write_text(
                "glabel func_80000020\n"
                "    /* 0 0 0 */  jr $ra\n"
                "    /* 0 0 0 */   nop\n"
            )
            # Genuinely undeclared and unowned: gets a synthesized line.
            (asm_root / "test" / "func_80000030.s").write_text(
                "glabel func_80000030\n"
                "    /* 0 0 0 */  or $v0, $a0, $zero\n"
                "    /* 0 0 0 */  jr $ra\n"
                "    /* 0 0 0 */   nop\n"
            )
            symbol_addrs.write_text(
                "func_80000010 = 0x80000010; // type:func\n"
                "func_80000020 = 0x80000020; // type:func\n"
                "func_80000030 = 0x80000030; // type:func\n"
                "D_80000040 = 0x80000040; // type:data\n"
            )
            output_path = root / "fallback.h"
            generated = targets.repository_fallback_symbol_header(
                source_root=source_root,
                symbol_addrs_path=symbol_addrs,
                asm_root=asm_root,
                output_path=output_path,
                repo_root=root,
            )
            text = generated.read_text()

        self.assertIn("func_80000030(); /* synthesized */", text)
        self.assertNotIn("func_80000010", text)
        self.assertNotIn("func_80000020", text)
        self.assertNotIn("D_80000040", text)

    def test_repository_fallback_symbol_header_without_symbol_addrs_is_just_the_guard(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            output_path = root / "fallback.h"
            generated = targets.repository_fallback_symbol_header(
                source_root=root / "src",
                symbol_addrs_path=root / "missing_symbol_addrs.txt",
                asm_root=root / "asm",
                output_path=output_path,
                repo_root=root,
            )
            text = generated.read_text()
        self.assertIn("PRAGMA_REPO_PROTOTYPES_FALLBACK_H", text)


class DeclarationTests(unittest.TestCase):
    def test_declarations_probe_every_candidate_and_install_once(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_b.s")\n'
            )
            probed: list[tuple[str, str]] = []

            def fake_probe(source_path, blocks, workers=None, companion_edits=None):
                probed.extend(blocks)
                return [
                    {"index": index, "function": function, "status": "probe_match"}
                    for index, (function, _) in enumerate(blocks)
                ]

            with mock.patch.object(runner, "probe_candidates", side_effect=fake_probe), mock.patch.object(
                runner, "rebuild_source_object", return_value=0
            ), mock.patch.object(
                runner, "_try_candidate_detailed", return_value=(0, "accepted")
            ), mock.patch.object(runner, "compare_current_tree", return_value=0):
                result = runner.try_candidates_detailed(
                    source,
                    [("func_a", "void func_a(void) {}"), ("func_b", "void func_b(void) {}")],
                    declarations="extern s32 D_1;\n",
                )
            self.assertEqual(result["accepted"], ["func_a", "func_b"])
            self.assertTrue(all(code.startswith("extern s32 D_1;\n") for _, code in probed))
            installed = source.read_text()
            self.assertEqual(installed.count("extern s32 D_1;"), 1)
            self.assertLess(installed.index("extern s32 D_1;"), installed.index("void func_a"))


class DedupeExternTests(unittest.TestCase):
    def test_duplicate_top_level_externs_are_removed_once(self) -> None:
        text = (
            "extern u8 D_1;\n"
            "void f(void) {\n    extern u8 D_1;\n}\n"
            "/* extern u8 D_1; */\n"
            "extern u8  D_1;\n"
            "extern void g(u8, u8);\n"
            "extern void g(u8, u8);\n"
        )
        result, removed = dedupe_externs.dedupe_text(text)
        self.assertEqual(removed, ["extern u8 D_1;", "extern void g(u8, u8);"])
        lines = result.splitlines()
        self.assertEqual(lines.count("extern u8 D_1;"), 1)
        self.assertIn("    extern u8 D_1;", lines)  # function-local declaration untouched
        self.assertIn("/* extern u8 D_1; */", lines)  # commented text untouched
        self.assertEqual(lines.count("extern void g(u8, u8);"), 1)


class PermuterWrapperTests(unittest.TestCase):
    def test_candidate_source_applies_companions_after_owner_substitution(self) -> None:
        source = (
            "extern void func_a(void);\n"
            '#pragma GLOBAL_ASM("asm/us/nonmatchings/x/func_a.s")\n'
            "void caller(u8 *arg0) { func_a(); }\n"
        )
        candidate = "s32 func_a(u8 *arg0) { return arg0[0]; }"
        result = permute_candidate._candidate_source(
            source,
            "func_a",
            candidate,
            companion_edits=[
                {
                    "function": "func_a",
                    "old": "extern void func_a(void);",
                    "new": "extern s32 func_a(u8 *);",
                },
                {
                    "function": "caller",
                    "old": "void caller(u8 *arg0) { func_a(); }",
                    "new": "void caller(u8 *arg0) { func_a(arg0); }",
                },
            ],
        )
        self.assertNotIn("GLOBAL_ASM", result)
        self.assertIn("extern s32 func_a(u8 *);", result)
        self.assertIn(candidate, result)
        self.assertIn("void caller(u8 *arg0) { func_a(arg0); }", result)

    def test_timed_out_permuter_group_gets_bounded_sigkill_fallback(self) -> None:
        class TimedProcess:
            pid = 12345

            def __init__(self) -> None:
                self.waits = 0

            def wait(self, timeout=None):
                self.waits += 1
                if self.waits < 2:
                    raise subprocess.TimeoutExpired("permuter", timeout)
                return 0

            def kill(self) -> None:
                raise AssertionError("direct kill should not be needed")

        process = TimedProcess()
        with mock.patch.object(permute_candidate.os, "killpg") as killpg:
            permute_candidate._terminate_process_group(process, grace=0.01)
        self.assertEqual(
            [call.args[1] for call in killpg.call_args_list],
            [signal.SIGTERM, signal.SIGKILL],
        )
        self.assertEqual(process.waits, 2)

    def test_linked_worktree_permuter_uses_primary_tools_and_private_cwd(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "permute"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            permuter_root = main / "disasm" / "tools" / "decomp-permuter"
            permuter_root.mkdir(parents=True)
            permuter_script = permuter_root / "permuter.py"
            permuter_script.write_text("# primary read-only permuter\n")
            (permuter_root / "strip_other_fns.py").write_text(
                "def strip_other_fns(source, function):\n    return source\n"
            )
            python = main / "disasm" / "tools" / "decomp-venv" / "bin" / "python3"
            python.parent.mkdir(parents=True)
            python.write_text("#!/bin/sh\n")
            python.chmod(0o755)
            work_dir = worktree / "disasm" / "build" / "permuter" / "func_a-test"
            work_dir.mkdir(parents=True)
            owner = targets.Owner("func_a", "disasm/src/x.c", "disasm/asm/x/func_a.s")

            class FinishedProcess:
                pid = 999999
                stdout: list[str] = []

                def wait(self, timeout=None):
                    return 0

            primary_before = {path.relative_to(main) for path in main.rglob("*")}
            with mock.patch.object(targets, "REPO_ROOT", worktree), mock.patch.object(
                permute_candidate, "REPO_ROOT", worktree
            ), mock.patch.object(
                permute_candidate, "DISASM_ROOT", worktree / "disasm"
            ), mock.patch.object(
                targets, "require_owner", return_value=owner
            ), mock.patch.object(
                permute_candidate, "build_work_directory", return_value=work_dir
            ), mock.patch.object(
                permute_candidate, "_collect_outputs", return_value=[]
            ), mock.patch.object(
                permute_candidate.subprocess, "Popen", return_value=FinishedProcess()
            ) as popen, mock.patch.dict(os.environ, {}, clear=True):
                result = permute_candidate.permute(
                    "func_a", "void func_a(void) {}", seconds=60, keep=True
                )
                stripped = permute_candidate._strip_other_functions(
                    "void func_a(void) {}", "func_a", permuter_root
                )

            command = popen.call_args.args[0]
            self.assertEqual(Path(command[0]), python.resolve())
            self.assertEqual(Path(command[1]), permuter_script.resolve())
            self.assertEqual(popen.call_args.kwargs["cwd"], work_dir)
            self.assertEqual(
                popen.call_args.kwargs["env"]["PYTHONDONTWRITEBYTECODE"], "1"
            )
            self.assertEqual(result["work_dir"], str(work_dir.relative_to(worktree)))
            self.assertEqual(stripped, "void func_a(void) {}\n")
            self.assertEqual(
                {path.relative_to(main) for path in main.rglob("*")}, primary_before
            )
            self.assertFalse(
                (worktree / "disasm" / "tools" / "decomp-permuter").exists()
            )
            self.assertFalse(
                (worktree / "disasm" / "tools" / "decomp-venv").exists()
            )

    def test_permuter_explicit_interpreter_override_remains_authoritative(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            with mock.patch.object(permute_candidate, "REPO_ROOT", root), mock.patch.dict(
                os.environ, {"PERMUTER_PYTHON": "custom/python3"}, clear=True
            ):
                self.assertEqual(
                    permute_candidate._permuter_python(),
                    str((root / "custom" / "python3").resolve()),
                )

    def test_extract_function_returns_only_the_target_body(self) -> None:
        code = (
            "extern u8 D_1;\nvoid other(void) { if (D_1) { D_1 = 0; } }\n"
            "void target(u8 *arg0, s16 a1)\n{\n  *((s16 *) (arg0 + 0x9A)) = a1;\n}\n"
            "void later(void);\n"
        )
        body = permute_candidate.extract_function(code, "target")
        self.assertTrue(body.startswith("void target("))
        self.assertTrue(body.rstrip().endswith("}"))
        self.assertNotIn("later", body)
        self.assertNotIn("other", body)

    def test_compile_script_substitutes_include_directory(self) -> None:
        compiler, flags = permute_candidate._split_recipe([
            "python3", "build.py", "--flag", "/ido/cc", "--", "as", "-32", "--",
            "-c", "-I", runner._RECIPE_DIRECTORY, "-O2", "-o", runner._RECIPE_OBJECT, runner._RECIPE_SOURCE,
        ])
        self.assertEqual(compiler, "/ido/cc")
        self.assertEqual(flags, ["-c", "-I", runner._RECIPE_DIRECTORY, "-O2"])
        script = permute_candidate.compile_script_text(compiler, flags, "src/x/")
        self.assertIn("-I src/x/ -O2 \"$@\"", script)
        self.assertIn("exec /ido/cc", script)


class McpDispatchTests(unittest.TestCase):
    def test_tool_list_covers_every_handler(self) -> None:
        self.assertEqual({tool["name"] for tool in mcp.TOOLS}, set(mcp.HANDLERS))

    def test_unknown_owner_is_a_tool_error_not_a_crash(self) -> None:
        with mock.patch.object(targets, "find_owner", return_value=None):
            response = mcp.call_tool("find_owner", {"function": "func_nope"})
        self.assertTrue(response["isError"])
        self.assertIn("func_nope", response["content"][0]["text"])

    def test_source_is_resolved_from_function_owner(self) -> None:
        owner = targets.Owner("func_a", "disasm/src/synthetic.c", "disasm/asm/us/nonmatchings/s/func_a.s")
        captured = {}

        def fake_try(source, blocks, **kwargs):
            captured["source"] = source
            captured["declarations"] = kwargs.get("declarations")
            return {"status": 1, "accepted": [], "attempts": [], "batch_status": "probe_only"}

        with mock.patch.object(targets, "find_owner", return_value=owner), mock.patch.object(
            runner, "try_candidates_detailed", side_effect=fake_try
        ), mock.patch.object(runner, "validate_candidate_batch", return_value=[]):
            response = mcp.call_tool("try_pragma_candidates", {
                "candidates": [{"function": "func_a", "code": "void func_a(void) {}"}],
                "declarations": "extern u8 D_1;",
                "gate": False,
            })
        self.assertFalse(response["isError"])
        self.assertEqual(captured["source"], owner.source_path)
        self.assertEqual(captured["declarations"], "extern u8 D_1;")
        self.assertEqual(json.loads(response["content"][0]["text"])["source"], "disasm/src/synthetic.c")

    def test_permuter_forwards_companion_edits(self) -> None:
        edits = [{
            "function": "caller",
            "old": "void caller(void) { func_a(); }",
            "new": "void caller(void) { (void)func_a(); }",
        }]
        with mock.patch.object(
            permute_candidate,
            "permute",
            return_value={"function": "func_a", "outputs": [], "best_score": 1},
        ) as permute:
            response = mcp.call_tool("permute_candidate", {
                "function": "func_a",
                "code": "s32 func_a(void) { return 0; }",
                "companion_edits": edits,
                "seconds": 5,
            })
        self.assertFalse(response["isError"])
        self.assertEqual(permute.call_args.kwargs["companion_edits"], edits)


class SweepTests(unittest.TestCase):
    def test_linked_worktree_sweep_draft_uses_shared_m2c_and_local_cwd(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            main = Path(directory) / "main"
            worktree = Path(directory) / "worktree"
            git_dir = main / ".git" / "worktrees" / "sweep"
            git_dir.mkdir(parents=True)
            worktree.mkdir()
            (worktree / ".git").write_text(f"gitdir: {git_dir}\n")
            script = main / "disasm" / "tools" / "m2c" / "m2c.py"
            script.parent.mkdir(parents=True)
            script.write_text("# primary m2c\n")
            asm = worktree / "disasm" / "asm" / "func_a.s"
            asm.parent.mkdir(parents=True)
            asm.write_text("glabel func_a\n")
            source = worktree / "disasm" / "src" / "x.c"
            source.parent.mkdir(parents=True)
            source.write_text('#pragma GLOBAL_ASM("asm/func_a.s")\n')
            owner = targets.Owner("func_a", "disasm/src/x.c", "disasm/asm/func_a.s")
            completed = mock.Mock(returncode=0, stdout="raw draft\n", stderr="")
            with mock.patch.object(targets, "REPO_ROOT", worktree), mock.patch.object(
                targets, "require_owner", return_value=owner
            ), mock.patch.object(
                targets, "preprocessed_context", return_value=None
            ), mock.patch.object(
                sweep_targets, "rewrite_draft", return_value="void func_a(void) {}"
            ), mock.patch.object(
                sweep_targets,
                "prepare_candidate_declarations",
                return_value="void func_a(void) {}",
            ), mock.patch.object(
                sweep_targets.subprocess, "run", return_value=completed
            ) as run, mock.patch.dict(os.environ, {}, clear=True):
                variants, raw = sweep_targets.draft_variants(
                    "func_a", context=False, variant_names=("s32-s32",)
                )

            self.assertEqual(raw, completed.stdout)
            self.assertEqual(variants[0][1], "void func_a(void) {}")
            self.assertEqual(Path(run.call_args.args[0][1]), script.resolve())
            self.assertEqual(run.call_args.kwargs["cwd"], worktree)
            self.assertEqual(
                run.call_args.kwargs["env"]["PYTHONDONTWRITEBYTECODE"], "1"
            )

    def test_rewrite_draft_inlines_fields_and_resolves_unknown_types(self) -> None:
        draft = (
            "extern M2C_UNK D_1;\n"
            "M2C_UNK func_b(s32);                         /* extern */\n"
            "void func_a(void *arg0) {\n"
            "    M2C_FIELD(arg0, s16 *, 0x9A) = 1;\n"
            "    func_b(D_1);\n"
            "}\n"
        )
        code = sweep_targets.rewrite_draft(draft, sweep_targets.VARIANTS["u8-void"])
        self.assertIn("extern u8 D_1;", code)
        self.assertIn("extern void func_b(s32);", code)
        self.assertIn("(*(s16 *)((u8 *)(arg0) + (0x9A))) = 1;", code)
        self.assertNotIn("M2C_", code)
        self.assertNotIn("/* extern */", code)
        self.assertIsNone(sweep_targets.rewrite_draft("M2C_ERROR(x)", sweep_targets.VARIANTS["u8-void"]))

    def test_padding_retry_only_for_clean_prefix_matches(self) -> None:
        clean = {
            "mismatch_kind": "symbol_size_drift", "diff_offsets": [],
            "expected_size": 24, "actual_size": 16, "expected_tail_kind": "jr_nop_plus_alignment",
        }
        self.assertEqual(sweep_targets.padding_retry(clean), 8)
        self.assertIsNone(sweep_targets.padding_retry({**clean, "diff_offsets": [4]}))
        self.assertIsNone(sweep_targets.padding_retry({**clean, "expected_tail_kind": "normal_return"}))
        self.assertIsNone(sweep_targets.padding_retry({**clean, "mismatch_kind": "instruction_drift"}))

    def test_duplicate_tail_retry_uses_empty_helpers_per_eight_bytes(self) -> None:
        clean = {
            "mismatch_kind": "symbol_size_drift", "diff_offsets": [],
            "expected_size": 80, "actual_size": 56,
            "expected_tail_kind": "duplicate_jr_nop_tail",
        }
        self.assertEqual(sweep_targets.duplicate_tail_helper_count(clean), 3)
        code = sweep_targets.append_duplicate_tail_helpers(
            "func_test", "void func_test(void) {}", 3
        )
        self.assertEqual(
            code,
            "void func_test(void) {}\n"
            "void func_test_padding(void) {}\n"
            "void func_test_padding2(void) {}\n"
            "void func_test_padding3(void) {}\n",
        )
        self.assertIsNone(
            sweep_targets.duplicate_tail_helper_count({**clean, "diff_offsets": [8]})
        )
        self.assertIsNone(
            sweep_targets.duplicate_tail_helper_count(
                {**clean, "expected_tail_kind": "jr_nop_plus_alignment"}
            )
        )
        self.assertIsNone(
            sweep_targets.duplicate_tail_helper_count({**clean, "expected_size": 78})
        )

    def test_fragment_range_and_compile_failure_variant_selection(self) -> None:
        self.assertEqual(sweep_targets.parse_fragment_range("17-32"), (17, 32))
        with self.assertRaises(ValueError):
            sweep_targets.parse_fragment_range("32-17")
        names = sweep_targets.compile_failure_variant_names("incompatible pointer conversion")
        self.assertIn("ptr-void", names)
        self.assertIn("ptr-s32", names)

    def test_family_variant_policy_keeps_rare_spellings_out_of_first_pass(self) -> None:
        call_variants = sweep_targets.FAMILY_VARIANTS["multi_call_wrapper"]
        self.assertEqual(call_variants[0], "u8-void")
        self.assertEqual(call_variants, ("u8-void", "s32-s32"))
        self.assertNotIn("u8-narrow-void", call_variants)
        self.assertNotIn("ptr-void", sweep_targets.FAMILY_VARIANTS["call_sequence"])
        self.assertEqual(
            sweep_targets.FAMILY_VARIANTS["bounded_lookup"],
            ("u8-void", "s32-s32", "u8-arg"),
        )
        narrow = sweep_targets.rewrite_draft(
            "M2C_UNK func_a(M2C_UNK arg0);\n",
            sweep_targets.VARIANTS["s16-narrow-void"],
        )
        self.assertIn("s16 arg0", narrow)

    def test_mismatch_shift_sixteen_selects_halfword_retries(self) -> None:
        attempt = {
            "status": "probe_rejected",
            "assembly_diff": [
                {"expected": "sll\tv0,a0,0x10", "actual": "sll\tv1,a0,0x2"},
            ],
        }
        self.assertEqual(
            sweep_targets.mismatch_variant_names(attempt),
            ("s16-void", "s16-narrow-void"),
        )
        self.assertEqual(
            sweep_targets.mismatch_variant_names({
                "status": "probe_rejected",
                "assembly_diff": [{"expected": "sll\tv0,a0,0x2"}],
            }),
            (),
        )

    def test_immediate_drift_rewrites_only_visible_literal(self) -> None:
        repairs = sweep_targets.immediate_repair_candidates(
            "s32 func_a(void) { return value + 0x100; }\n",
            {
                "status": "probe_rejected",
                "mismatch_kind": "immediate_drift",
                "assembly_diff": [{
                    "expected": "addiu\tv0,v0,0x101",
                    "actual": "addiu\tv0,v0,0x100",
                }],
            },
        )
        self.assertEqual(len(repairs), 1)
        self.assertIn("0x101", repairs[0][1])
        self.assertNotIn("0x100", repairs[0][1])

    def test_immediate_drift_ignores_opcode_and_zero_repairs(self) -> None:
        base = {
            "status": "probe_rejected",
            "mismatch_kind": "immediate_drift",
            "assembly_diff": [{
                "expected": "lw\tv0,0x104(a0)",
                "actual": "sw\tv0,0x100(a0)",
            }],
        }
        self.assertEqual(
            sweep_targets.immediate_repair_candidates("return value + 0x100;", base), []
        )
        base["assembly_diff"] = [{
            "expected": "addiu\tv0,v0,0x0",
            "actual": "addiu\tv0,v0,0x0",
        }]
        self.assertEqual(
            sweep_targets.immediate_repair_candidates("return value;", base), []
        )

    def test_stack_slot_retry_reorders_only_descending_local_declarations(self) -> None:
        candidate = (
            "s32 func_a(void) {\n"
            "    s32 sp28;\n"
            "    s16 sp26;\n"
            "    s16 sp24;\n"
            "    sp28 = 1;\n"
            "    return sp24;\n"
            "}\n"
        )
        rewritten = sweep_targets.stack_slot_order_candidate(
            candidate,
            {"status": "probe_rejected", "mismatch_kind": "immediate_drift"},
        )
        self.assertIsNotNone(rewritten)
        self.assertLess(rewritten.index("s16 sp24"), rewritten.index("s16 sp26"))
        self.assertLess(rewritten.index("s16 sp26"), rewritten.index("s32 sp28"))
        self.assertIn("sp28 = 1;", rewritten)
        self.assertIsNone(
            sweep_targets.stack_slot_order_candidate(
                candidate,
                {"status": "probe_rejected", "mismatch_kind": "register_allocation_only"},
            )
        )

    def test_bounded_lookup_u8_argument_variant_rewrites_only_function_parameter(self) -> None:
        draft = (
            "u8 func_80073600(s32 arg0) {\n"
            "    s32 temp_a0;\n"
            "    temp_a0 = arg0 & 0xFF;\n"
            "    return temp_a0;\n"
            "}\n"
        )
        code = sweep_targets.rewrite_draft(draft, sweep_targets.VARIANTS["u8-arg"])
        self.assertIn("u8 func_80073600(u8 arg0)", code)
        self.assertNotIn("temp_a0", code)

    def test_compile_failure_candidates_rewrite_and_deduplicate_diagnostics(self) -> None:
        draft = (
            "extern M2C_UNK D_1;\n"
            "void func_a(void) { M2C_FIELD(D_1, s16 *, 0x4) = 1; }\n"
        )
        candidates = sweep_targets.compile_failure_candidates(draft, [
            "incompatible pointer conversion",
            "incompatible pointer conversion",
            "unknown type M2C_UNK",
        ])
        labels = [label for label, _ in candidates]
        self.assertEqual(len(labels), len(set(labels)))
        self.assertIn("m2c:ptr-void:compile-retry", labels)
        self.assertIn("m2c:s32-s32:compile-retry", labels)
        self.assertTrue(all("M2C_" not in code for _, code in candidates))

    def test_compile_failure_retries_use_only_first_cfe_type_error(self) -> None:
        warning_then_undefined = (
            "cfe: Warning 835: pointer conversion warning\n"
            "cfe: Error: 'D_80000004' undefined; reoccurrences will not be reported."
        )
        self.assertEqual(
            sweep_targets.compile_failure_variant_names(warning_then_undefined), ()
        )
        self.assertIn(
            "ptr-void",
            sweep_targets.compile_failure_variant_names(
                "cfe: Error: Unacceptable operand of '+'."
            ),
        )

    def test_prepare_candidate_declarations_uses_owner_and_index_spellings(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "owner.c"
            source.write_text(
                '#include "global.h"\n'
                "extern u16 D_80000004;\n"
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/test/func_80000000.s")\n'
                "extern u8 D_80000008;\n"
                "s32 func_80000010(s32 arg0) { return arg0; }\n"
            )
            index = root / "repo-prototypes.h"
            index.write_text(
                "extern u32 D_8000000C;\n"
                "s32 func_80000010(s32 arg0);\n"
            )
            candidate = (
                "extern s32 D_80000008;\n"
                "void func_80000000(void) {\n"
                "    D_80000008 = D_8000000C;\n"
                "    func_80000010(1);\n"
                "}\n"
            )
            with mock.patch.object(
                sweep_targets.targets, "repository_symbol_header", return_value=index
            ):
                prepared = sweep_targets.prepare_candidate_declarations(
                    "func_80000000", source, candidate
                )

        self.assertIn("extern u8 D_80000008;", prepared)
        self.assertIn("extern u32 D_8000000C;", prepared)
        self.assertIn("s32 func_80000010(s32 arg0);", prepared)
        self.assertNotIn("extern s32 D_80000008;", prepared)
        self.assertNotIn("extern u16 D_80000004;", prepared)

    def test_split_candidate_declarations_deduplicates_m2c_prefix(self) -> None:
        declarations, body = sweep_targets.split_candidate_declarations(
            "extern s32 helper(s32);\nextern s32 helper(s32);\n\nvoid func_a(void) {}\n"
        )
        self.assertEqual(declarations, "extern s32 helper(s32);\n")
        self.assertEqual(body, "void func_a(void) {}\n")

    def test_split_candidate_declarations_hoists_prototype_line(self) -> None:
        declarations, body = sweep_targets.split_candidate_declarations(
            "s32 (*func_80003240(s32 *))(s32);\n"
            "s32 func_b(s32);\n"
            "void func_a(void) { func_b(1); }\n"
        )
        self.assertIn("s32 (*func_80003240(s32 *))(s32);", declarations)
        self.assertIn("s32 func_b(s32);", declarations)
        self.assertEqual(body, "void func_a(void) { func_b(1); }\n")

    def test_partition_gate_batches_defers_conflicting_smaller_group(self) -> None:
        # Two functions share declarations that agree on ``helper``'s
        # prototype (the larger group); a third function's declarations
        # disagree, so it must be deferred rather than gated -- gating it
        # would install a prototype that conflicts with the one the larger
        # group already committed and fail to compile.
        gate_batches = {
            "extern s32 helper(s32);": [
                ("func_a", "void func_a(void) {}", "m2c:x"),
                ("func_b", "void func_b(void) {}", "m2c:x"),
            ],
            "extern u8 helper(s32);": [
                ("func_c", "void func_c(void) {}", "m2c:x"),
            ],
        }
        family_of = {"func_a": "fam", "func_b": "fam", "func_c": "fam"}
        summary = sweep_targets.collections.defaultdict(sweep_targets.collections.Counter)
        active = sweep_targets.partition_gate_batches(
            gate_batches, source_rel="disasm/src/a.c", family_of=family_of, summary=summary
        )
        self.assertEqual(len(active), 1)
        declarations, batch = active[0]
        self.assertEqual(declarations, "extern s32 helper(s32);")
        self.assertEqual(sorted(function for function, _, _ in batch), ["func_a", "func_b"])
        self.assertEqual(summary["fam"]["deferred_conflicting_prototype"], 1)

    def test_callee_unprototyped_variant_rewrites_returned_function_params(self) -> None:
        code = "s32 (*func_80003240(s32 *))(s32);\nvoid func_a(void) {}\n"
        rewritten = sweep_targets.callee_unprototyped_variant(code)
        self.assertIsNotNone(rewritten)
        self.assertIn("s32 (*func_80003240(s32 *))();", rewritten)
        self.assertIsNone(sweep_targets.callee_unprototyped_variant("void func_a(void) {}\n"))

    def test_compile_failure_variant_names_with_no_policy_keeps_old_behavior(self) -> None:
        # Existing tests (and any caller that omits ``policy``) must see the
        # exact pre-policy result: this is what makes the policy an opt-in.
        names = sweep_targets.compile_failure_variant_names("incompatible pointer conversion")
        self.assertIn("ptr-void", names)
        self.assertIn("ptr-s32", names)
        self.assertIn("u32-void", names)

    def test_compile_failure_variant_names_dropped_when_policy_has_evidence_against_it(self) -> None:
        # A policy carrying the issue's own cited evidence (738 attempts, 0
        # accepted/probe_match) must drop the whole trio automatically.
        policy = variant_policy.VariantPolicy({
            (name, variant_policy.CLASS_POINTER_OPERAND): variant_policy.VariantStats(
                attempts=200, accepted=0, probe_match=0,
            )
            for name in ("ptr-void", "ptr-s32", "u32-void")
        })
        names = sweep_targets.compile_failure_variant_names(
            "cfe: Error: Unacceptable operand of '+'.", policy=policy,
        )
        self.assertEqual(names, ())

    def test_compile_failure_variant_names_kept_when_policy_has_no_evidence_yet(self) -> None:
        # An empty/unexplored policy allows the same diagnostic-suggested
        # names through -- min_attempts gating only bites once there is
        # enough recorded history to judge.
        policy = variant_policy.VariantPolicy({})
        names = sweep_targets.compile_failure_variant_names(
            "cfe: Error: Unacceptable operand of '+'.", policy=policy,
        )
        self.assertIn("ptr-void", names)

    def test_compile_failure_variant_names_skips_trio_for_field_cast_operand_error(self) -> None:
        # The offending line is the M2C_FIELD-derived cast shape
        # (``rewrite_draft``'s ``(*(TYPE)((u8 *)(...) + (...)))``): a
        # pointer-width retry cannot fix this, so the trio should not be
        # suggested even with a fully permissive policy.
        diagnostic = (
            "cfe: Error: probes/x.c, line 12: Unacceptable operand of '+'.\n"
            "     (*(s32 *)((u8 *)(sp1c) + (0x4))) = 1;\n"
            " ------------------^\n"
        )
        self.assertEqual(sweep_targets.compile_failure_variant_names(diagnostic), ())

    def test_compile_failure_variant_names_keeps_trio_for_plain_operand_error(self) -> None:
        diagnostic = (
            "cfe: Error: probes/x.c, line 65: Unacceptable operand of '+'.\n"
            "     func_87C013CC(arg0 + 0x38, arg0);\n"
            " ------------------^\n"
        )
        names = sweep_targets.compile_failure_variant_names(diagnostic)
        self.assertIn("ptr-void", names)

    def test_fnptr_cast_candidate_rewrites_dereferenced_global_call(self) -> None:
        code = "void func_a(s32 arg0) {\n    (*D_800A0000)(arg0);\n}\n"
        rewritten = sweep_targets.fnptr_cast_candidate(code)
        self.assertIsNotNone(rewritten)
        self.assertIn("((void (*)())(D_800A0000))(arg0);", rewritten)

    def test_fnptr_cast_candidate_rewrites_indexed_table_call_with_used_result(self) -> None:
        code = (
            "s32 func_a(s32 arg0) {\n"
            "    s32 result;\n"
            "    result = table[arg0](arg0, 1);\n"
            "    return result;\n"
            "}\n"
        )
        rewritten = sweep_targets.fnptr_cast_candidate(code)
        self.assertIsNotNone(rewritten)
        self.assertIn("((s32 (*)())(table[arg0]))(arg0, 1);", rewritten)

    def test_fnptr_cast_candidate_returns_none_for_ordinary_calls(self) -> None:
        self.assertIsNone(sweep_targets.fnptr_cast_candidate("void func_a(void) { func_b(1); }\n"))

    def test_prepare_candidate_declarations_uses_fallback_header_before_synthesizing(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "owner.c"
            source.write_text(
                '#include "global.h"\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/test/func_80000000.s")\n'
            )
            candidate = (
                "void func_80000000(void) {\n"
                "    func_80000010(1);\n"
                "}\n"
            )
            fallback_header = root / "fallback.h"
            fallback_header.write_text("s32 func_80000010(); /* synthesized */\n")
            with mock.patch.object(
                sweep_targets.targets, "repository_symbol_header", return_value=None,
            ), mock.patch.object(
                sweep_targets.targets, "repository_fallback_symbol_header",
                return_value=fallback_header,
            ):
                sweep_targets._SYMBOL_INDEX_CACHE = None
                sweep_targets._FALLBACK_SYMBOL_INDEX_CACHE = None
                prepared = sweep_targets.prepare_candidate_declarations(
                    "func_80000000", source, candidate,
                )
        self.assertIn("s32 func_80000010(); /* synthesized */", prepared)

    def test_prepare_candidate_declarations_synthesizes_undeclared_global_as_byte_array(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "owner.c"
            source.write_text(
                '#include "global.h"\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/test/func_80000000.s")\n'
            )
            candidate = (
                "void func_80000000(void) {\n"
                "    D_87F00000 = 1;\n"
                "}\n"
            )
            with mock.patch.object(
                sweep_targets.targets, "repository_symbol_header", return_value=None,
            ), mock.patch.object(
                sweep_targets.targets, "repository_fallback_symbol_header", return_value=None,
            ):
                sweep_targets._SYMBOL_INDEX_CACHE = None
                sweep_targets._FALLBACK_SYMBOL_INDEX_CACHE = None
                prepared = sweep_targets.prepare_candidate_declarations(
                    "func_80000000", source, candidate,
                )
        self.assertIn("extern u8 D_87F00000[]; /* synthesized fallback */", prepared)

    def test_prepare_candidate_declarations_never_synthesizes_for_owner_declared_symbol(self) -> None:
        # A symbol the owner source already declares above the pragma must
        # never fall through to a synthesized guess, even if it happens to
        # look like an undeclared global.
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "owner.c"
            source.write_text(
                '#include "global.h"\n'
                "extern u16 D_87F00000;\n"
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/test/func_80000000.s")\n'
            )
            candidate = "void func_80000000(void) {\n    D_87F00000 = 1;\n}\n"
            with mock.patch.object(
                sweep_targets.targets, "repository_symbol_header", return_value=None,
            ), mock.patch.object(
                sweep_targets.targets, "repository_fallback_symbol_header", return_value=None,
            ):
                sweep_targets._SYMBOL_INDEX_CACHE = None
                sweep_targets._FALLBACK_SYMBOL_INDEX_CACHE = None
                prepared = sweep_targets.prepare_candidate_declarations(
                    "func_80000000", source, candidate,
                )
        # The owner already declares it above the pragma, so it is visible
        # in place without needing to be echoed into the prefix -- what
        # matters here is that it must never fall through to a synthesized
        # guess.
        self.assertNotIn("synthesized fallback", prepared)

    def test_previously_attempted_labels_returns_function_label_pairs(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats = Path(directory) / "stats.jsonl"
            stats.write_text("\n".join([
                json.dumps({"attempts": [
                    {"function": "func_a", "label": "m2c:u8-void", "status": "compare_rejected"},
                    {"function": "func_a", "label": "manual:x", "status": "compare_rejected"},
                ]}),
                json.dumps({"attempts": [
                    {"function": "func_b", "label": "m2c:s32-s32", "status": "accepted"},
                ]}),
            ]) + "\n")
            pairs = sweep_targets.previously_attempted_labels(stats_path=stats)
        self.assertEqual(pairs, {("func_a", "m2c:u8-void"), ("func_b", "m2c:s32-s32")})

    def test_sweep_skips_draft_when_every_variant_label_already_attempted(self) -> None:
        rows = [
            {"function": "func_a", "source": "disasm/src/fragments/1/a.c", "family": "call_sequence"},
        ]
        skip_attempts = {
            ("func_a", f"m2c:{name}") for name in sweep_targets.FAMILY_VARIANTS["call_sequence"]
        }
        with mock.patch.object(
            sweep_targets.targets, "list_targets",
            return_value={"matched": 1, "targets": rows, "truncated": False},
        ), mock.patch.object(
            sweep_targets.dedupe_externs, "dirty_sources", return_value=set(),
        ), mock.patch.object(
            sweep_targets, "draft_variants",
        ) as draft:
            result = sweep_targets.sweep(
                max_instructions=None, min_instructions=None, family=None, source=None,
                limit=10, gate=False, workers=1, skip_attempts=skip_attempts,
            )
        draft.assert_not_called()
        self.assertEqual(result["summary"]["call_sequence"]["skipped_attempted"], 1)
        self.assertIsInstance(result["draft_seconds"], (int, float))

    def test_sweep_drafts_only_remaining_variant_labels(self) -> None:
        rows = [
            {"function": "func_a", "source": "disasm/src/fragments/1/a.c", "family": "call_sequence"},
        ]
        all_names = sweep_targets.FAMILY_VARIANTS["call_sequence"]
        skip_attempts = {("func_a", f"m2c:{all_names[0]}")}
        with mock.patch.object(
            sweep_targets.targets, "list_targets",
            return_value={"matched": 1, "targets": rows, "truncated": False},
        ), mock.patch.object(
            sweep_targets.dedupe_externs, "dirty_sources", return_value=set(),
        ), mock.patch.object(
            sweep_targets, "draft_variants", return_value=([], None),
        ) as draft:
            sweep_targets.sweep(
                max_instructions=None, min_instructions=None, family=None, source=None,
                limit=10, gate=False, workers=1, skip_attempts=skip_attempts,
            )
        draft.assert_called_once()
        self.assertEqual(draft.call_args.args[0], "func_a")
        self.assertEqual(draft.call_args.kwargs["variant_names"], tuple(all_names[1:]))

    def test_sweep_summary_includes_timing_rollup(self) -> None:
        rows = [
            {"function": "func_a", "source": "disasm/src/fragments/1/a.c", "family": "call_sequence"},
        ]

        def fake_try_candidates(source_path, blocks, *, labels=None, declarations=None, gate=True, probe_workers=None):
            if not gate:
                return {
                    "status": 0,
                    "accepted": [],
                    "attempts": [{"index": 0, "function": "func_a", "status": "probe_match"}],
                    "batch_status": "probe_only",
                    "timing": {
                        "probe_seconds": 0.02, "gate_seconds": 0.0, "gate_runs": 0, "install_compiles": 0,
                    },
                }
            return {
                "status": 0,
                "accepted": ["func_a"],
                "attempts": [{"index": 0, "function": "func_a", "status": "accepted"}],
                "batch_status": "accepted",
                "timing": {
                    "probe_seconds": 0.0, "gate_seconds": 0.3, "gate_runs": 1, "install_compiles": 2,
                },
            }

        with mock.patch.object(
            sweep_targets.targets, "list_targets",
            return_value={"matched": 1, "targets": rows, "truncated": False},
        ), mock.patch.object(
            sweep_targets.dedupe_externs, "dirty_sources", return_value=set(),
        ), mock.patch.object(
            sweep_targets, "draft_variants",
            return_value=([("m2c:u8-void", "void func_a(void) {}")], "draft"),
        ), mock.patch.object(
            sweep_targets.runner, "try_candidates_detailed", side_effect=fake_try_candidates,
        ):
            result = sweep_targets.sweep(
                max_instructions=None, min_instructions=None, family=None, source=None,
                limit=10, gate=True, workers=1,
            )
        self.assertEqual(result["timing"]["gate_runs"], 1)
        self.assertEqual(result["timing"]["install_compiles"], 2)
        self.assertAlmostEqual(result["timing"]["probe_seconds"], 0.02)
        self.assertAlmostEqual(result["timing"]["gate_seconds"], 0.3)

    def test_near_miss_permutes_and_gates_score_zero(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats = Path(directory) / "stats.jsonl"
            stats.write_text(json.dumps({
                "source": "disasm/src/synthetic.c",
                "attempts": [
                    {
                        "function": "func_a",
                        "label": "m2c:s32-s32",
                        "status": "compare_rejected",
                        "similarity_score": 0.91,
                        "candidate": "void func_a(void) { int low; }",
                        "declarations": "extern void helper(void);",
                    },
                    {
                        "function": "func_a",
                        "label": "m2c:ptr-void",
                        "status": "compare_rejected",
                        "similarity_score": 0.95,
                        "candidate": "void func_a(void) { int best; }",
                        "declarations": "extern void helper(void);",
                    },
                    {
                        "function": "func_a",
                        "label": "manual:unrelated",
                        "status": "compare_rejected",
                        "similarity_score": 0.99,
                        "candidate": "void func_a(void) { int wrong; }",
                    },
                ],
            }) + "\n")
            owner = targets.Owner("func_a", "disasm/src/synthetic.c", "asm/us/nonmatchings/synthetic/func_a.s")
            with mock.patch.object(targets, "require_owner", return_value=owner), mock.patch.object(
                sweep_targets.permute_candidate,
                "permute",
                return_value={"outputs": [{"score": "0", "code": "void func_a(void) {}"}]},
            ) as permute, mock.patch.object(
                sweep_targets.runner,
                "try_candidates_detailed",
                return_value={"accepted": ["func_a"], "batch_status": "accepted"},
            ) as gate:
                result = sweep_targets.near_miss(
                    stats_path=stats, seconds=45.0, label_prefixes=("m2c:",)
                )
            self.assertEqual(result["accepted"], ["func_a"])
            permute.assert_called_once()
            self.assertEqual(permute.call_args.args[:2], ("func_a", "void func_a(void) { int best; }"))
            self.assertEqual(permute.call_args.kwargs["seconds"], 45.0)
            gate.assert_called_once()

    def test_large_sweep_only_permutes_rejects_at_or_above_similarity_threshold(self) -> None:
        # ``func_high`` (0.75) is above the 0.7 large-mode floor and should
        # reach the permuter with the flat --large-seconds budget; ``func_low``
        # (0.5) should never reach ``permute_candidate.permute`` at all.
        rows = [
            {"function": "func_high", "source": "disasm/src/fragments/9/big.c", "family": "loop_or_state_machine"},
            {"function": "func_low", "source": "disasm/src/fragments/9/big.c", "family": "loop_or_state_machine"},
        ]

        def fake_draft_variants(function, context=True, family=None, variant_names=None, extra_m2c_args=(), label_prefix="m2c"):
            return [(f"{label_prefix}:s32-s32", f"s32 {function}(void) {{ return 0; }}\n")], "draft\n"

        probe_result = {
            "attempts": [
                {"index": 0, "function": "func_high", "status": "probe_rejected", "similarity_score": 0.75},
                {"index": 1, "function": "func_low", "status": "probe_rejected", "similarity_score": 0.5},
            ],
        }

        with mock.patch.object(
            sweep_targets.targets, "list_targets",
            return_value={"matched": len(rows), "targets": rows, "truncated": False},
        ), mock.patch.object(
            sweep_targets.dedupe_externs, "dirty_sources", return_value=set(),
        ), mock.patch.object(
            sweep_targets, "draft_variants", side_effect=fake_draft_variants,
        ), mock.patch.object(
            sweep_targets.runner, "try_candidates_detailed", return_value=probe_result,
        ) as probe, mock.patch.object(
            sweep_targets.permute_candidate, "permute",
            return_value={"outputs": [], "already_matching": False},
        ) as permute:
            result = sweep_targets.large_sweep(large_seconds=180.0)

        probe.assert_called_once()
        permute.assert_called_once()
        self.assertEqual(permute.call_args.args[0], "func_high")
        self.assertEqual(permute.call_args.kwargs["seconds"], 180.0)
        self.assertEqual(result["drafted"], 2)
        self.assertEqual(result["probed"], 2)
        self.assertEqual(result["permuted"], 1)

    def test_near_miss_default_considers_every_label(self) -> None:
        # Without a label restriction, the highest-scoring attempt across
        # every label (including a non-``m2c:`` one) is the candidate: the
        # ``manual:unrelated`` row at 0.99 outranks both ``m2c:`` rows.
        with tempfile.TemporaryDirectory() as directory:
            stats = Path(directory) / "stats.jsonl"
            stats.write_text(json.dumps({
                "source": "disasm/src/synthetic.c",
                "attempts": [
                    {
                        "function": "func_a",
                        "label": "m2c:s32-s32",
                        "status": "compare_rejected",
                        "similarity_score": 0.91,
                        "candidate": "void func_a(void) { int low; }",
                        "declarations": "extern void helper(void);",
                    },
                    {
                        "function": "func_a",
                        "label": "m2c:ptr-void",
                        "status": "compare_rejected",
                        "similarity_score": 0.95,
                        "candidate": "void func_a(void) { int best; }",
                        "declarations": "extern void helper(void);",
                    },
                    {
                        "function": "func_a",
                        "label": "manual:unrelated",
                        "status": "compare_rejected",
                        "similarity_score": 0.99,
                        "candidate": "void func_a(void) { int wrong; }",
                    },
                ],
            }) + "\n")
            owner = targets.Owner("func_a", "disasm/src/synthetic.c", "asm/us/nonmatchings/synthetic/func_a.s")
            with mock.patch.object(targets, "require_owner", return_value=owner), mock.patch.object(
                sweep_targets.permute_candidate,
                "permute",
                return_value={"outputs": [{"score": "0", "code": "void func_a(void) {}"}]},
            ) as permute, mock.patch.object(
                sweep_targets.runner,
                "try_candidates_detailed",
                return_value={"accepted": ["func_a"], "batch_status": "accepted"},
            ) as gate:
                result = sweep_targets.near_miss(stats_path=stats, seconds=45.0)
            self.assertEqual(result["accepted"], ["func_a"])
            permute.assert_called_once()
            self.assertEqual(permute.call_args.args[:2], ("func_a", "void func_a(void) { int wrong; }"))
            gate.assert_called_once()

    def test_near_miss_parallel_permutes_and_gates_each_output(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats = Path(directory) / "stats.jsonl"
            stats.write_text(json.dumps({
                "source": "disasm/src/synthetic.c",
                "attempts": [
                    {
                        "function": "func_a", "label": "m2c:s32-s32", "status": "compare_rejected",
                        "similarity_score": 0.95, "candidate": "void func_a(void) { int a; }",
                    },
                    {
                        "function": "func_b", "label": "m2c:u8-void", "status": "compare_rejected",
                        "similarity_score": 0.93, "candidate": "void func_b(void) { int b; }",
                    },
                ],
            }) + "\n")
            owner_a = targets.Owner("func_a", "disasm/src/synthetic.c", "asm/us/nonmatchings/synthetic/func_a.s")
            owner_b = targets.Owner("func_b", "disasm/src/synthetic.c", "asm/us/nonmatchings/synthetic/func_b.s")
            owners = {"func_a": owner_a, "func_b": owner_b}
            with mock.patch.object(
                targets, "require_owner", side_effect=lambda function: owners[function]
            ), mock.patch.object(
                sweep_targets.permute_candidate,
                "permute",
                return_value={"outputs": [{"score": "0", "code": "void func(void) {}"}]},
            ) as permute, mock.patch.object(
                sweep_targets.runner,
                "try_candidates_detailed",
                return_value={"accepted": ["func_x"], "batch_status": "accepted"},
            ) as gate:
                result = sweep_targets.near_miss(
                    stats_path=stats, seconds=10.0, parallel=2, label_prefixes=("m2c:",)
                )
            self.assertEqual(permute.call_count, 2)
            self.assertEqual(gate.call_count, 2)
            self.assertEqual(sorted(result["accepted"]), ["func_x", "func_x"])
            self.assertEqual(result["candidates"], 2)

    def test_permute_outcome_is_written_to_probe_stats(self) -> None:
        owner = targets.Owner(
            "func_a", "disasm/src/synthetic.c", "asm/us/nonmatchings/synthetic/func_a.s"
        )
        row = {
            "function": "func_a",
            "candidate": "void func_a(void) {}",
            "label": "m2c:s32-s32",
            "similarity_score": 0.94,
            "mismatch_kind": "immediate_drift",
        }
        with mock.patch.object(targets, "require_owner", return_value=owner), mock.patch.object(
            sweep_targets.permute_candidate,
            "permute",
            return_value={"outputs": [{"score": "0.25", "code": "void func_a(void) { int x; }"}]},
        ), mock.patch.object(
            sweep_targets.runner,
            "try_candidates_detailed",
            return_value={"accepted": [], "batch_status": "compare_rejected"},
        ), mock.patch.object(sweep_targets.runner, "_record_probe_stats") as record:
            result = sweep_targets.permute_and_gate(
                [row], seconds=45.0, kind_seconds=120.0, threads=1, workers=1, parallel=1,
            )
        self.assertEqual(result["accepted"], [])
        record.assert_called_once()
        recorded = record.call_args.args[1][0]
        self.assertEqual(recorded["status"], "permute_rejected")
        self.assertEqual(recorded["permute_score"], 0.25)
        self.assertEqual(recorded["permute_budget_seconds"], 120.0)
        self.assertEqual(
            recorded["permute_input_digest"],
            sweep_targets._candidate_digest(row["candidate"], row.get("declarations")),
        )

    def test_near_miss_skip_permuted_excludes_prior_permute_attempts(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats = Path(directory) / "stats.jsonl"
            stats.write_text("\n".join([
                json.dumps({"attempts": [
                    {
                        "function": "func_a", "label": "m2c:s32-s32", "status": "compare_rejected",
                        "similarity_score": 0.95, "candidate": "void func_a(void) {}",
                    },
                    {
                        "function": "func_a", "label": "permute:m2c:s32-s32", "status": "compare_rejected",
                        "similarity_score": 0.5, "candidate": "void func_a(void) {}",
                    },
                ]}),
                json.dumps({"attempts": [
                    {
                        "function": "func_b", "label": "m2c:u8-void", "status": "compare_rejected",
                        "similarity_score": 0.92, "candidate": "void func_b(void) {}",
                    },
                ]}),
            ]) + "\n")
            with mock.patch.object(
                targets, "require_owner", return_value=mock.MagicMock()
            ), mock.patch.object(
                sweep_targets.permute_candidate, "permute", return_value={"outputs": []}
            ) as permute:
                result = sweep_targets.near_miss(stats_path=stats, label_prefixes=("m2c:",))
            self.assertEqual(result["skipped_permuted"], 1)
            self.assertEqual(result["candidates"], 1)
            self.assertEqual(result["skipped_solved"], 0)
            permute.assert_called_once()
            self.assertEqual(permute.call_args.args[0], "func_b")

    def test_near_miss_requeues_new_candidate_after_prior_permute(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats = Path(directory) / "stats.jsonl"
            stats.write_text("\n".join([
                json.dumps({"timestamp": "2026-09-01T00:00:00Z", "attempts": [{
                    "function": "func_a", "label": "m2c:old", "status": "probe_rejected",
                    "similarity_score": 0.95, "candidate": "void func_a(void) { int old; }",
                }]}),
                json.dumps({"timestamp": "2026-09-01T00:01:00Z", "attempts": [{
                    "function": "func_a", "label": "permute:m2c:old", "status": "permute_rejected",
                    "similarity_score": 0.95, "candidate": "void func_a(void) { int old; }",
                }]}),
                json.dumps({"timestamp": "2026-09-01T00:02:00Z", "attempts": [{
                    "function": "func_a", "label": "m2c:new", "status": "probe_rejected",
                    "similarity_score": 0.95, "candidate": "void func_a(void) { int new_body; }",
                }]}),
            ]) + "\n")
            with mock.patch.object(
                targets, "require_owner", return_value=mock.MagicMock()
            ), mock.patch.object(
                sweep_targets.permute_candidate, "permute", return_value={"outputs": []}
            ) as permute:
                result = sweep_targets.near_miss(
                    stats_path=stats, label_prefixes=("m2c:",), seconds=10.0
                )
            self.assertEqual(result["candidates"], 1)
            permute.assert_called_once()
            self.assertEqual(
                permute.call_args.args[:2],
                ("func_a", "void func_a(void) { int new_body; }"),
            )

    def test_near_miss_skips_function_after_full_gate_acceptance(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats = Path(directory) / "stats.jsonl"
            stats.write_text("\n".join([
                json.dumps({"attempts": [{
                    "function": "func_done",
                    "label": "m2c:s32-s32",
                    "status": "accepted",
                    "similarity_score": 1.0,
                    "candidate": "void func_done(void) {}",
                }]}),
                json.dumps({"attempts": [{
                    "function": "func_done",
                    "label": "m2c:ptr-void",
                    "status": "compare_rejected",
                    "similarity_score": 0.99,
                    "candidate": "void func_done(void) {}",
                }]}),
            ]) + "\n")
            with mock.patch.object(sweep_targets.permute_candidate, "permute") as permute:
                result = sweep_targets.near_miss(stats_path=stats, limit=10)
            self.assertEqual(result["candidates"], 0)
            permute.assert_not_called()

    def test_near_miss_skips_owner_no_longer_holding_pragma(self) -> None:
        # A later run may already have installed a full-gate winner for a
        # function since these stats were recorded; the owner check must
        # reject it before a permuter budget is spent, not after.
        with tempfile.TemporaryDirectory() as directory:
            stats = Path(directory) / "stats.jsonl"
            stats.write_text(json.dumps({
                "source": "disasm/src/synthetic.c",
                "attempts": [{
                    "function": "func_a",
                    "label": "m2c:s32-s32",
                    "status": "compare_rejected",
                    "similarity_score": 0.95,
                    "candidate": "void func_a(void) {}",
                }],
            }) + "\n")
            with mock.patch.object(
                targets, "require_owner",
                side_effect=KeyError("no GLOBAL_ASM pragma owns func_a"),
            ), mock.patch.object(
                sweep_targets.permute_candidate, "permute",
            ) as permute:
                result = sweep_targets.near_miss(stats_path=stats, label_prefixes=("m2c:",))
            self.assertEqual(result["skipped_solved"], 1)
            self.assertEqual(result["candidates"], 0)
            permute.assert_not_called()

    def test_near_miss_kind_seconds_gives_longer_budget(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            stats = Path(directory) / "stats.jsonl"
            stats.write_text(json.dumps({
                "source": "disasm/src/synthetic.c",
                "attempts": [
                    {
                        "function": "func_a", "label": "m2c:s32-s32", "status": "compare_rejected",
                        "similarity_score": 0.95, "candidate": "void func_a(void) {}",
                        "mismatch_kind": "register_allocation_only",
                    },
                    {
                        "function": "func_b", "label": "m2c:u8-void", "status": "compare_rejected",
                        "similarity_score": 0.93, "candidate": "void func_b(void) {}",
                        "mismatch_kind": "instruction_drift",
                    },
                ],
            }) + "\n")
            owner_a = targets.Owner("func_a", "disasm/src/synthetic.c", "asm/us/nonmatchings/synthetic/func_a.s")
            owner_b = targets.Owner("func_b", "disasm/src/synthetic.c", "asm/us/nonmatchings/synthetic/func_b.s")
            owners = {"func_a": owner_a, "func_b": owner_b}
            calls: dict[str, float] = {}

            def fake_permute(function: str, candidate: str, **kwargs: object) -> dict[str, object]:
                calls[function] = kwargs["seconds"]
                return {"outputs": []}

            with mock.patch.object(
                targets, "require_owner", side_effect=lambda function: owners[function]
            ), mock.patch.object(
                sweep_targets.permute_candidate, "permute", side_effect=fake_permute,
            ):
                sweep_targets.near_miss(
                    stats_path=stats, seconds=10.0, kind_seconds=90.0, label_prefixes=("m2c:",)
                )
            self.assertEqual(calls["func_a"], 90.0)
            self.assertEqual(calls["func_b"], 10.0)


class SimilarSolvedTests(unittest.TestCase):
    def test_solved_shapes_rank_by_opcode_similarity(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            asm_root = root / "asm"
            (asm_root / "x").mkdir(parents=True)
            (asm_root / "x" / "func_done.s").write_text(
                "glabel func_done\n"
                "    /* 0 0 0 */  lw $v0, 0($a0)\n"
                "    /* 0 0 0 */  jr $ra\n"
                "    /* 0 0 0 */  nop\n"
            )
            (asm_root / "x" / "func_new.s").write_text(
                "glabel func_new\n"
                "    /* 0 0 0 */  lw $v0, 4($a0)\n"
                "    /* 0 0 0 */  jr $ra\n"
                "    /* 0 0 0 */  nop\n"
            )
            stats = root / "stats.jsonl"
            stats.write_text(json.dumps({"source": "s.c", "counts": {}, "attempts": [
                {"function": "func_done", "status": "accepted", "candidate": "s32 func_done(s32 *a) { return a[0]; }", "declarations": "extern s32 D_DONE;", "label": "load"},
                {"function": "func_lost", "status": "probe_rejected", "candidate": "void func_lost(void) {}"},
            ]}) + "\n")
            with mock.patch.object(targets, "ASM_ROOT", asm_root), mock.patch.object(targets, "_SOLVED_CACHE", None):
                rows = targets.solved_shapes(stats)
                self.assertEqual([row["function"] for row in rows], ["func_done"])
                self.assertEqual(rows[0]["declarations"], "extern s32 D_DONE;")
                owner = targets.Owner("func_new", "disasm/src/s.c", "x/func_new.s")
                with mock.patch.object(targets, "require_owner", return_value=owner), mock.patch.object(
                    targets.Owner, "asm_path", property(lambda self: asm_root / "x" / "func_new.s")
                ), mock.patch.object(targets, "STATS_PATH", stats):
                    ranked = targets.similar_solved("func_new")
            self.assertEqual(ranked[0]["function"], "func_done")
            self.assertEqual(ranked[0]["similarity"], 1.0)
            self.assertTrue(ranked[0]["same_length"])

    def test_solved_shapes_falls_back_to_a_second_asm_root(self) -> None:
        # A winner missing from the primary (local) asm root -- as in a
        # worktree with only a partial extraction -- is still found via a
        # second, fallback root, without shadowing a winner the primary root
        # already has.
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            primary = root / "primary"
            fallback = root / "fallback"
            (primary / "x").mkdir(parents=True)
            (fallback / "x").mkdir(parents=True)
            (primary / "x" / "func_local.s").write_text(
                "glabel func_local\n"
                "    /* 0 0 0 */  lw $v0, 0($a0)\n"
                "    /* 0 0 0 */  jr $ra\n"
                "    /* 0 0 0 */  nop\n"
            )
            (fallback / "x" / "func_remote.s").write_text(
                "glabel func_remote\n"
                "    /* 0 0 0 */  sw $v0, 0($a0)\n"
                "    /* 0 0 0 */  jr $ra\n"
                "    /* 0 0 0 */  nop\n"
            )
            stats = root / "stats.jsonl"
            stats.write_text(json.dumps({"source": "s.c", "counts": {}, "attempts": [
                {"function": "func_local", "status": "accepted", "candidate": "s32 func_local(s32 *a) { return a[0]; }", "label": "load"},
                {"function": "func_remote", "status": "accepted", "candidate": "void func_remote(s32 *a) { a[0] = 1; }", "label": "store"},
            ]}) + "\n")
            with mock.patch.object(targets, "_SOLVED_CACHE", None):
                rows = targets.solved_shapes(stats, asm_roots=[primary, fallback])
        self.assertEqual({row["function"] for row in rows}, {"func_local", "func_remote"})


if __name__ == "__main__":
    unittest.main()
