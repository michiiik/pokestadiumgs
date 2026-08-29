#!/usr/bin/env python3
"""Focused regression tests for candidate diagnostics and family filtering."""

from __future__ import annotations

import io
import json
import os
import sys
import tempfile
import time
import unittest
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

    def test_probe_sources_compile_with_direct_recipe(self) -> None:
        repo_root = Path(__file__).resolve().parent.parent
        probe_root = runner._probe_root(repo_root)
        with tempfile.TemporaryDirectory(prefix=".pragma_probe_", dir=probe_root) as directory:
            source = Path(directory) / "owner.c"
            source.write_text("void owner(void) {}\n")
            completed = mock.Mock(returncode=0, stdout="")
            with mock.patch.object(
                runner,
                "_probe_compile_recipe",
                return_value=["cc", "-o", runner._RECIPE_OBJECT, runner._RECIPE_SOURCE],
            ), mock.patch.object(runner.subprocess, "run", return_value=completed) as run:
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
                with mock.patch.object(runner.subprocess, "run", return_value=completed) as run:
                    runner._make_object(tracked_source, capture=True)
                self.assertEqual(run.call_args.args[0][0], "make")

    def test_probe_worker_default_and_clamping(self) -> None:
        with mock.patch.dict(os.environ, {}, clear=True):
            self.assertEqual(runner._resolve_probe_workers(None, 50), 10)
        with mock.patch.dict(os.environ, {"PRAGMA_PROBE_WORKERS": "3"}):
            self.assertEqual(runner._resolve_probe_workers(None, 50), 3)
            self.assertEqual(runner._resolve_probe_workers(20, 2), 2)

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
                runner.subprocess,
                "run",
                side_effect=runner.subprocess.TimeoutExpired("make", 1),
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

    def test_text_size_difference_is_layout_drift(self) -> None:
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
        self.assertEqual(verdict["link_mismatch"], "section_layout_drift")

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
                "link_verified": True,
                "link_mismatch": None,
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
            self.assertTrue(row["attempts"][0]["link_verified"])

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

    def test_mixed_unverified_and_verified_hits_share_combined_gate(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "synthetic.c"
            source.write_text(
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_a.s")\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/synthetic/func_b.s")\n'
            )
            with mock.patch.object(
                runner, "probe_candidates",
                return_value=[
                    {"index": 0, "function": "func_a", "status": "probe_match"},
                    {"index": 1, "function": "func_b", "status": "probe_match", "link_verified": True},
                ],
            ), mock.patch.object(
                runner, "rebuild_source_object", return_value=0,
            ), mock.patch.object(
                runner, "_try_candidate_detailed", return_value=(0, "accepted"),
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
            sequential_gate.assert_called_once()
            full_compare.assert_called_once()
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
        ):
            response = mcp.call_tool("try_pragma_candidates", {
                "candidates": [{"function": "func_a", "code": "void func_a(void) {}"}],
                "declarations": "extern u8 D_1;",
                "gate": False,
            })
        self.assertFalse(response["isError"])
        self.assertEqual(captured["source"], owner.source_path)
        self.assertEqual(captured["declarations"], "extern u8 D_1;")
        self.assertEqual(json.loads(response["content"][0]["text"])["source"], "disasm/src/synthetic.c")


class SweepTests(unittest.TestCase):
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
