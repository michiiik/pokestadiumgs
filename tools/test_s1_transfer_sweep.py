#!/usr/bin/env python3
"""Unit tests for tools/s1_transfer_sweep.py.

Everything here is mock-based: no ROM, no compiler, no MCP.  Where the
module under test would read a real S1 checkout or call the candidate
runner, tests monkeypatch the relevant module attribute instead.
"""

from __future__ import annotations

import unittest
from pathlib import Path
from unittest import mock

import s1_transfer_sweep as sweep


class ExtractBracedBlockTest(unittest.TestCase):
    def test_nested_braces(self):
        text = "prefix { a; { b; } c; } suffix"
        start = text.index("{")
        block = sweep.extract_braced_block(text, start)
        self.assertEqual(block, "{ a; { b; } c; }")

    def test_string_containing_brace(self):
        text = 'void f() {\n    char *s = "not a } real brace";\n    return;\n}\ntail'
        start = text.index("{")
        block = sweep.extract_braced_block(text, start)
        self.assertTrue(block.startswith("{"))
        self.assertTrue(block.endswith("}"))
        self.assertIn('"not a } real brace"', block)
        # the closing brace of the string must not have ended the block early
        self.assertIn("return;", block)

    def test_line_comment_containing_brace(self):
        text = "{ // trailing } comment\n  x = 1;\n}"
        block = sweep.extract_braced_block(text, 0)
        self.assertEqual(block, text)

    def test_unterminated_raises(self):
        with self.assertRaises(ValueError):
            sweep.extract_braced_block("{ a; { b;", 0)


class FindFunctionDefinitionTest(unittest.TestCase):
    def test_extracts_full_definition_with_nested_braces_and_string(self):
        text = (
            "#include \"global.h\"\n\n"
            "extern s32 D_80090220;\n\n"
            "void Other(void) {\n    return;\n}\n\n"
            "void MyFunc(s32 arg0) {\n"
            "    char *s = \"a } weird string\";\n"
            "    if (arg0) {\n"
            "        D_80090220 = 1;\n"
            "    }\n"
            "}\n\n"
            "void Tail(void) { return; }\n"
        )
        path = Path("dummy.c")
        with mock.patch.object(Path, "read_text", return_value=text):
            result = sweep.find_function_definition("MyFunc", path)
        self.assertIsNotNone(result)
        full, is_static = result
        self.assertFalse(is_static)
        self.assertTrue(full.startswith("void MyFunc(s32 arg0) {"))
        self.assertIn("a } weird string", full)
        self.assertIn("D_80090220 = 1;", full)
        self.assertNotIn("Tail", full)
        self.assertNotIn("Other", full)

    def test_static_function_detected(self):
        text = "static void Helper(void) {\n    return;\n}\n"
        with mock.patch.object(Path, "read_text", return_value=text):
            result = sweep.find_function_definition("Helper", Path("dummy.c"))
        self.assertIsNotNone(result)
        _, is_static = result
        self.assertTrue(is_static)

    def test_missing_function_returns_none(self):
        text = "void SomethingElse(void) { return; }\n"
        with mock.patch.object(Path, "read_text", return_value=text):
            result = sweep.find_function_definition("NotHere", Path("dummy.c"))
        self.assertIsNone(result)


class ParseGsAsmTest(unittest.TestCase):
    ASM = (
        "glabel func_800015C0\n"
        "    /* 0021C0 800015C0 27BDFFE8 */  addiu       $sp, $sp, -0x18\n"
        "    /* 0021C8 800015C8 3C0F800B */  lui         $t7, %hi(D_800AB4A0)\n"
        "    /* 0021CC 800015CC 25EFB4A0 */  addiu       $t7, $t7, %lo(D_800AB4A0)\n"
        "    /* 00226C 8000166C 0C01F040 */  jal         osCreateMesgQueue\n"
        "    /* 002270 80001670 24060001 */   addiu      $a2, $zero, 0x1\n"
        "  .L80001680:\n"
        "    /* 00227C 8000167C 03E00008 */  jr          $ra\n"
        "    /* 002280 80001680 00000000 */   nop\n"
    )

    def test_word_and_operand_extraction(self):
        instrs = sweep.parse_gs_asm(self.ASM)
        # the .L label line must not become an instruction (7 /* */ lines, 1 label line)
        self.assertEqual(len(instrs), 7)
        self.assertEqual(instrs[0].word, 0x27BDFFE8)
        self.assertEqual(instrs[0].mnemonic, "addiu")
        self.assertIsNone(instrs[0].hi_sym)

        lui = instrs[1]
        self.assertEqual(lui.hi_sym, "D_800AB4A0")
        self.assertEqual(lui.word, 0x3C0F800B)

        lo = instrs[2]
        self.assertEqual(lo.lo_sym, "D_800AB4A0")

        jal = instrs[3]
        self.assertEqual(jal.jal_sym, "osCreateMesgQueue")
        self.assertIsNone(jal.hi_sym)

    def test_index_is_sequential_and_skips_labels(self):
        instrs = sweep.parse_gs_asm(self.ASM)
        self.assertEqual([i.index for i in instrs], list(range(len(instrs))))


class DecodeS1AddressTest(unittest.TestCase):
    def test_decode_jal_target(self):
        # jal osCreateMesgQueue -> word 0x0C01F040 (from the sample above)
        word = 0x0C01F040
        self.assertEqual(sweep.decode_jal_target(word), 0x8007C100)

    def test_decode_hilo_positive(self):
        # lui $t7, 0x800B ; addiu $t7, $t7, 0xB4A0  ->  0x800BB4A0
        hi_word = 0x3C0F800B
        lo_word = 0x25EFB4A0
        self.assertEqual(sweep.decode_hilo_address(hi_word, lo_word), 0x800AB4A0)

    def test_decode_hilo_negative_lo_sign_extends(self):
        # lui $at, 0x8009 ; lw $t0, -4($at)  ->  0x80088FFC (lo16 = 0xFFFC, negative)
        hi_word = 0x3C018009
        lo_word = 0x8D08FFFC  # lw $t0, -4($at)
        self.assertEqual(sweep.decode_hilo_address(hi_word, lo_word), 0x8008FFFC)

    def test_decode_s1_addresses_pairs_lui_addiu_by_register(self):
        gs_instrs = sweep.parse_gs_asm(self.asm_for_pairing())
        # S1 machine words aligned with the same instruction shape, but a
        # different linked address: lui $t7, 0x8010 ; addiu $t7, $t7, 0x2000
        s1_words = [0x3C0F8010, 0x25EF2000]
        result = sweep.decode_s1_addresses(gs_instrs, s1_words)
        self.assertEqual(result.addresses[1], 0x80102000)
        self.assertEqual(result.unresolved, [])

    def test_decode_s1_addresses_lui_lw_pair_negative_lo(self):
        gs_instrs = sweep.parse_gs_asm(
            "glabel func_TEST\n"
            "    /* 000000 80000000 3C018009 */  lui  $at, %hi(D_8009FFFC)\n"
            "    /* 000004 80000004 8C20FFFC */  lw   $v0, %lo(D_8009FFFC)($at)\n"
        )
        s1_words = [0x3C018009, 0x8C20FFFC]
        result = sweep.decode_s1_addresses(gs_instrs, s1_words)
        self.assertEqual(result.addresses[1], 0x8008FFFC)

    def test_unpaired_lo_is_reported(self):
        gs_instrs = sweep.parse_gs_asm(
            "glabel func_TEST\n"
            "    /* 000000 80000000 8C20FFFC */  lw   $v0, %lo(D_8009FFFC)($at)\n"
        )
        result = sweep.decode_s1_addresses(gs_instrs, [0x8C20FFFC])
        self.assertEqual(result.unresolved, [0])
        self.assertEqual(result.addresses, {})

    @staticmethod
    def asm_for_pairing() -> str:
        return (
            "glabel func_TEST\n"
            "    /* 000000 80000000 3C0F800B */  lui   $t7, %hi(D_800BB4A0)\n"
            "    /* 000004 80000004 25EFB4A0 */  addiu $t7, $t7, %lo(D_800BB4A0)\n"
        )


class ResolveS1SymbolTest(unittest.TestCase):
    def setUp(self):
        self.symtab = sweep.S1SymbolTable(
            all_by_addr={0x80100000: "gMemPool", 0x80200000: "SomeFunc"},
            func_by_addr={0x80200000: "SomeFunc"},
            sorted_addrs=[0x80100000, 0x80200000],
            names={"gMemPool", "SomeFunc"},
            func_names={"SomeFunc"},
        )

    def test_exact_data_match(self):
        self.assertEqual(sweep.resolve_s1_symbol(self.symtab, 0x80100000, is_call=False), ("gMemPool", 0))

    def test_exact_call_match(self):
        self.assertEqual(sweep.resolve_s1_symbol(self.symtab, 0x80200000, is_call=True), ("SomeFunc", 0))

    def test_containment_offset_for_data(self):
        self.assertEqual(
            sweep.resolve_s1_symbol(self.symtab, 0x80100004, is_call=False), ("gMemPool", 4)
        )

    def test_containment_too_far_rejected(self):
        self.assertIsNone(sweep.resolve_s1_symbol(self.symtab, 0x80100000 + 0x5000, is_call=False))

    def test_unresolved_call_without_body_identifier(self):
        self.assertIsNone(sweep.resolve_s1_symbol(self.symtab, 0x80300000, is_call=True))

    def test_synthesized_call_name_accepted_when_in_body(self):
        result = sweep.resolve_s1_symbol(
            self.symtab, 0x80300000, is_call=True, body_identifiers={"func_80300000"}
        )
        self.assertEqual(result, ("func_80300000", 0))

    def test_synthesized_data_name_accepted_when_in_body(self):
        result = sweep.resolve_s1_symbol(
            self.symtab, 0x80400010, is_call=False, body_identifiers={"D_80400010"}
        )
        self.assertEqual(result, ("D_80400010", 0))

    def test_synthesized_data_name_rejected_without_body_identifier(self):
        self.assertIsNone(sweep.resolve_s1_symbol(self.symtab, 0x80400010, is_call=False))


class ApplyRenameTest(unittest.TestCase):
    def test_word_boundary_rename(self):
        text = "D_8009 + D_80090 + D_8009X"
        renamed = sweep.apply_rename(text, {"D_8009": "GS_Foo"})
        self.assertEqual(renamed, "GS_Foo + D_80090 + D_8009X")

    def test_prefix_name_not_corrupted_by_longer_replacement_first(self):
        # Renaming the longer name first must not create a substring that
        # then accidentally matches the shorter name's pattern.
        text = "Foo(Foobar())"
        renamed = sweep.apply_rename(text, {"Foo": "A", "Foobar": "B"})
        self.assertEqual(renamed, "A(B())")

    def test_empty_map_is_noop(self):
        self.assertEqual(sweep.apply_rename("abc", {}), "abc")


class TypeIndexTest(unittest.TestCase):
    def test_struct_typedef_indexed(self):
        header = (
            "typedef struct Inner {\n"
            "    s32 x;\n"
            "} Inner;\n\n"
            "typedef struct Outer {\n"
            "    Inner inner;\n"
            "    s32 y;\n"
            "} Outer;\n"
        )
        index = sweep.index_type_definitions([header])
        self.assertIn("Inner", index)
        self.assertIn("Outer", index)
        self.assertIn("Inner inner;", index["Outer"])

    def test_function_pointer_typedef_name_not_last_token(self):
        header = "typedef void (*Callback)(s32 arg0, void* arg1);\n"
        index = sweep.index_type_definitions([header])
        self.assertIn("Callback", index)
        self.assertNotIn("void", index)

    def test_array_typedef_name(self):
        header = "typedef u64 Buffer[4];\n"
        index = sweep.index_type_definitions([header])
        self.assertIn("Buffer", index)

    def test_transitive_collection_with_s1_prefix(self):
        header = (
            "typedef struct Inner {\n    s32 x;\n} Inner;\n\n"
            "typedef struct Outer {\n    Inner inner;\n} Outer;\n"
        )
        index = sweep.index_type_definitions([header])
        collected = sweep.collect_type_definitions({"Outer"}, index, max_depth=4)
        self.assertIn("Outer", collected)
        self.assertIn("Inner", collected)

    def test_depth_bound_stops_expansion(self):
        header = (
            "typedef struct A { s32 x; } A;\n"
            "typedef struct B { A a; } B;\n"
            "typedef struct C { B b; } C;\n"
            "typedef struct D { C c; } D;\n"
            "typedef struct E { D d; } E;\n"
        )
        index = sweep.index_type_definitions([header])
        collected = sweep.collect_type_definitions({"E"}, index, max_depth=1)
        self.assertIn("E", collected)
        self.assertIn("D", collected)
        self.assertNotIn("C", collected)

    def test_default_depth_covers_deep_transfer_dependencies(self):
        header = (
            "typedef struct A { B b; } A;\n"
            "typedef struct B { C c; } B;\n"
            "typedef struct C { D d; } C;\n"
            "typedef struct D { E e; } D;\n"
            "typedef struct E { F f; } E;\n"
            "typedef struct F { s32 value; } F;\n"
        )
        index = sweep.index_type_definitions([header])
        collected = sweep.collect_type_definitions({"A"}, index)
        self.assertIn("F", collected)

    def test_order_types_dependency_first(self):
        defs = {
            "Outer": "typedef struct Outer { Inner inner; } Outer;",
            "Inner": "typedef struct Inner { s32 x; } Inner;",
        }
        order = sweep.order_types(defs)
        self.assertLess(order.index("Inner"), order.index("Outer"))

    def test_order_types_ignores_pointer_back_edges(self):
        defs = {
            "Outer": "typedef struct Outer { Node node; } Outer;",
            "Node": "typedef struct Node { Outer *owner; } Node;",
        }
        order = sweep.order_types(defs)
        self.assertLess(order.index("Node"), order.index("Outer"))

    def test_forward_type_declarations_cover_named_aggregates(self):
        defs = {
            "Outer": "typedef struct Outer { Node *node; } Outer;",
            "Node": "typedef struct Node { s32 value; } Node;",
            "Anonymous": "typedef struct { s32 value; } Anonymous;",
        }
        forwards = sweep.forward_type_declarations(defs, {name: f"S1_{name}" for name in defs})
        self.assertIn("typedef struct S1_Outer S1_Outer;", forwards)
        self.assertIn("typedef struct S1_Node S1_Node;", forwards)
        self.assertNotIn("S1_Anonymous", "\n".join(forwards))

    def test_named_aggregate_definition_uses_existing_forward_typedef(self):
        definition = "typedef struct S1_Node {\n    s32 value;\n} S1_Node;"
        self.assertEqual(
            sweep._strip_named_aggregate_typedef(definition),
            "struct S1_Node {\n    s32 value;\n};",
        )

    def test_s1_prefix_rename_applied_to_definition(self):
        defs = {"Foo": "typedef struct Foo { s32 x; } Foo;"}
        rename_map = {"Foo": "S1_Foo"}
        renamed = sweep.apply_rename(defs["Foo"], rename_map)
        self.assertEqual(renamed, "typedef struct S1_Foo { s32 x; } S1_Foo;")


class MergeDeclarationsTest(unittest.TestCase):
    def test_deduplicates_complete_multiline_units(self):
        first = "typedef struct {\n    s32 x;\n} S1_First;"
        second = "typedef struct {\n    s32 y;\n} S1_Second;"

        merged = sweep.merge_declarations([first, second, first])

        self.assertEqual(merged, first + "\n" + second + "\n")
        self.assertEqual(merged.count("typedef struct {"), 2)
        self.assertIn("s32 x;", merged)
        self.assertIn("s32 y;", merged)

    def test_partitions_conflicting_complete_declarations(self):
        first = sweep.TransferResult(
            function="func_A", outcome="candidate",
            declaration_units=["typedef struct S1_State { s32 x; } S1_State;"],
        )
        second = sweep.TransferResult(
            function="func_B", outcome="candidate",
            declaration_units=["typedef struct S1_State { s16 x; } S1_State;"],
        )
        compatible = sweep.TransferResult(
            function="func_C", outcome="candidate",
            declaration_units=["typedef struct S1_State { s32 x; } S1_State;"],
        )

        groups = sweep.partition_transfer_results([first, second, compatible])

        self.assertEqual(
            [[result.function for result in group] for group in groups],
            [["func_A", "func_C"], ["func_B"]],
        )


class GenerateCandidateAlignmentTest(unittest.TestCase):
    """``generate_candidate`` reports an alignment failure without a full S1Context."""

    def _make_owner(self, function: str, asm_text: str, tmp_path: Path) -> "sweep.targets.Owner":
        asm_path = tmp_path / f"{function}.s"
        asm_path.write_text(asm_text)
        source_path = tmp_path / "source.c"
        source_path.write_text("")
        owner = mock.Mock()
        owner.function = function
        owner.asm_path = asm_path
        owner.asm = str(asm_path)
        owner.source_path = source_path
        return owner

    def test_alignment_failed_reports_first_difference(self):
        import tempfile
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            asm_text = (
                "glabel func_TEST\n"
                "    /* 000000 80000000 27BDFFE8 */  addiu $sp, $sp, -0x18\n"
                "    /* 000004 80000004 00000000 */  nop\n"
            )
            owner = self._make_owner("func_TEST", asm_text, tmp_path)
            transfer_map = {"func_TEST": ("Foo", "Stadium 1 Foo @ 0x80100000 (text); match class identical; 2 instructions")}
            ctx = mock.Mock()
            ctx.s1_functions = {"Foo": {"vram": 0x80100000, "seg": "text", "w": (0x27BDFFE8, 0x00000001)}}
            ctx.func_file_index = {"Foo": tmp_path / "s1.c"}
            (tmp_path / "s1.c").write_text("void Foo(void) {\n    return;\n}\n")
            ctx.gs_asm_fallback = None

            with mock.patch.object(sweep.targets, "require_owner", return_value=owner):
                result = sweep.generate_candidate("func_TEST", owner, ctx, transfer_map, {})
        self.assertEqual(result.outcome, "alignment_failed")
        self.assertIn("instruction 1", result.detail)

    def test_s1_body_missing_when_not_yet_decompiled(self):
        import tempfile
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            owner = self._make_owner("func_TEST", "glabel func_TEST\n", tmp_path)
            transfer_map = {"func_TEST": ("Foo", "Stadium 1 Foo @ 0x80100000 (text); match class identical; 0 instructions")}
            ctx = mock.Mock()
            ctx.s1_functions = {"Foo": {"vram": 0x80100000, "seg": "text", "w": ()}}
            ctx.func_file_index = {}  # Foo is still GLOBAL_ASM in S1: no .c defines it
            result = sweep.generate_candidate("func_TEST", owner, ctx, transfer_map, {})
        self.assertEqual(result.outcome, "s1_body_missing")


class SelectFunctionsTest(unittest.TestCase):
    def test_skips_dirty_and_missing_owner(self):
        transfer_map = {"func_A": ("A", "..."), "func_B": ("B", "...")}
        owner_a = mock.Mock(source="disasm/src/a.c", source_path=Path("/repo/disasm/src/a.c"))
        with mock.patch.object(sweep.targets, "owner_index", return_value={"func_A": owner_a}), \
             mock.patch.object(sweep.dedupe_externs, "dirty_sources", return_value=set()):
            selected = sweep.select_functions(transfer_map, functions=None, source=None, limit=None)
        self.assertEqual(selected, ["func_A"])  # func_B has no owner (already decompiled or vanished)

    def test_limit_applied(self):
        transfer_map = {f"func_{i}": (f"N{i}", "...") for i in range(5)}
        owners = {name: mock.Mock(source="s.c", source_path=Path(f"/repo/{name}.c")) for name in transfer_map}
        with mock.patch.object(sweep.targets, "owner_index", return_value=owners), \
             mock.patch.object(sweep.dedupe_externs, "dirty_sources", return_value=set()):
            selected = sweep.select_functions(transfer_map, functions=None, source=None, limit=2)
        self.assertEqual(len(selected), 2)


class DriverTwoPassTest(unittest.TestCase):
    """The gated (non-dry-run) driver probes first, then gates only probe_match hits."""

    def test_probe_then_gate_with_s1_labels(self):
        result = sweep.TransferResult(
            function="func_TEST", outcome="candidate", s1_name="Foo",
            symbol_map={"Foo": "func_TEST"}, declarations="",
            variants=[("s1:transfer", "void func_TEST(void) {}\n")],
        )
        calls: list[dict[str, object]] = []

        def fake_try_candidates_detailed(source_path, blocks, *, labels=None, declarations=None, gate=True, probe_workers=None):
            calls.append({"blocks": blocks, "labels": labels, "gate": gate})
            if not gate:
                return {"attempts": [{"function": "func_TEST", "index": 0, "status": "probe_match"}], "accepted": []}
            return {"attempts": [{"function": "func_TEST", "index": 0, "status": "accepted"}], "accepted": ["func_TEST"]}

        with mock.patch.object(sweep.runner, "try_candidates_detailed", side_effect=fake_try_candidates_detailed):
            output = sweep.run_source_group(Path("/repo/source.c"), [result], gate=True, workers=None)

        self.assertEqual(len(calls), 2)
        self.assertFalse(calls[0]["gate"])
        self.assertTrue(calls[1]["gate"])
        self.assertTrue(all(str(label).startswith("s1:") for label in calls[0]["labels"]))
        self.assertEqual(output["accepted"], ["func_TEST"])

    def test_no_gate_call_when_nothing_probe_matched(self):
        result = sweep.TransferResult(
            function="func_TEST", outcome="candidate", s1_name="Foo",
            variants=[("s1:transfer", "void func_TEST(void) {}\n")],
        )
        calls: list[bool] = []

        def fake_try_candidates_detailed(source_path, blocks, *, labels=None, declarations=None, gate=True, probe_workers=None):
            calls.append(gate)
            return {"attempts": [{"function": "func_TEST", "index": 0, "status": "compile_failed"}], "accepted": []}

        with mock.patch.object(sweep.runner, "try_candidates_detailed", side_effect=fake_try_candidates_detailed):
            sweep.run_source_group(Path("/repo/source.c"), [result], gate=True, workers=None)

        self.assertEqual(calls, [False])  # only the probe-only pass ran


class DryRunCallsNoRunnerTest(unittest.TestCase):
    def test_dry_run_never_touches_runner(self):
        transfer_map = {"func_TEST": ("Foo", "Stadium 1 Foo @ 0x80100000 (text); match class identical; 0 instructions")}
        owner = mock.Mock(function="func_TEST", source_path=Path("/repo/source.c"))
        ctx = mock.Mock()
        ctx.s1_functions = {}  # forces s1_function_missing, short-circuiting before any file I/O

        with mock.patch.object(sweep.targets, "owner_index", return_value={"func_TEST": owner}), \
             mock.patch.object(sweep.runner, "try_candidates_detailed") as fake_runner:
            result = sweep.dry_run(
                ["func_TEST"], ctx=ctx, transfer_map=transfer_map, s1_reverse_index={},
                strict=False, show_text=False,
            )
        fake_runner.assert_not_called()
        self.assertEqual(result["outcome_counts"], {"s1_function_missing": 1})


if __name__ == "__main__":
    unittest.main()
