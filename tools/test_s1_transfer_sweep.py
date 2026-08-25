#!/usr/bin/env python3
"""Unit tests for tools/s1_transfer_sweep.py.

Everything here is mock-based: no ROM, no compiler, no MCP.  Where the
module under test would read a real S1 checkout or call the candidate
runner, tests monkeypatch the relevant module attribute instead.
"""

from __future__ import annotations

import tempfile
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

    def test_block_comment_before_definition_is_not_part_of_signature(self):
        text = (
            "/*\n"
            "  0x02: Jump to address\n"
            "    cmd+0x04: void *jumpTarget\n"
            "*/\n"
            "void Jump(void) {\n"
            "    return;\n"
            "}\n"
        )
        with mock.patch.object(Path, "read_text", return_value=text):
            result = sweep.find_function_definition("Jump", Path("dummy.c"))
        self.assertIsNotNone(result)
        full, is_static = result
        self.assertFalse(is_static)
        self.assertTrue(full.startswith("void Jump(void) {"))
        self.assertNotIn("jumpTarget", full)

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
        parsed = sweep.parse_gs_asm(self.ASM)
        self.assertIsInstance(parsed, sweep.ParsedAsm)
        self.assertEqual(parsed.words, [i.word for i in parsed.instructions])
        instrs = parsed.instructions
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
        instrs = sweep.parse_gs_asm(self.ASM).instructions
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
        gs_instrs = sweep.parse_gs_asm(self.asm_for_pairing()).instructions
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
        ).instructions
        s1_words = [0x3C018009, 0x8C20FFFC]
        result = sweep.decode_s1_addresses(gs_instrs, s1_words)
        self.assertEqual(result.addresses[1], 0x8008FFFC)

    def test_unpaired_lo_is_reported(self):
        gs_instrs = sweep.parse_gs_asm(
            "glabel func_TEST\n"
            "    /* 000000 80000000 8C20FFFC */  lw   $v0, %lo(D_8009FFFC)($at)\n"
        ).instructions
        result = sweep.decode_s1_addresses(gs_instrs, [0x8C20FFFC])
        self.assertEqual(result.unresolved, [0])
        self.assertEqual(result.addresses, {})

    def test_pairs_by_symbol_name_across_a_register_move(self):
        # lui $t7, %hi(D_X) ; addu $t8, $t7, $zero ; lw $t8, %lo(D_X)($t8)
        # The %lo consumer's base register ($t8) is not the lui's own
        # destination ($t7) -- only matching by symbol *name* (not by
        # tracking the register through the move) can still pair these.
        gs_instrs = sweep.parse_gs_asm(
            "glabel func_TEST\n"
            "    /* 000000 80000000 3C0F800B */  lui   $t7, %hi(D_800BB4A0)\n"
            "    /* 000004 80000004 01E0C021 */  addu  $t8, $t7, $zero\n"
            "    /* 000008 80000008 8F18B4A0 */  lw    $t8, %lo(D_800BB4A0)($t8)\n"
        ).instructions
        s1_words = [0x3C0F8010, 0x01E0C021, 0x8F182000]
        result = sweep.decode_s1_addresses(gs_instrs, s1_words)
        self.assertEqual(result.addresses[2], 0x80102000)
        self.assertEqual(result.unresolved, [])

    @staticmethod
    def asm_for_pairing() -> str:
        return (
            "glabel func_TEST\n"
            "    /* 000000 80000000 3C0F800B */  lui   $t7, %hi(D_800BB4A0)\n"
            "    /* 000004 80000004 25EFB4A0 */  addiu $t7, $t7, %lo(D_800BB4A0)\n"
        )


class DecodeTargetsTest(unittest.TestCase):
    def test_jal_and_hilo_together(self):
        words = [0x0C01F040, 0x3C0F800B, 0x25EFB4A0]
        result = sweep.decode_targets(words, jal_indices=[0], hilo_pairs=[(1, 2)])
        self.assertEqual(result[0], sweep.decode_jal_target(words[0]))
        self.assertEqual(result[2], sweep.decode_hilo_address(words[1], words[2]))

    def test_out_of_range_indices_ignored(self):
        result = sweep.decode_targets([0x0C01F040], jal_indices=[5], hilo_pairs=[(0, 9)])
        self.assertEqual(result, {})

    def test_empty_inputs(self):
        self.assertEqual(sweep.decode_targets([1, 2, 3]), {})


class AlignWordsTest(unittest.TestCase):
    def test_strict_requires_exact_normalised_match(self):
        alignment = sweep.align_words([0x27BDFFE8, 0x00000000], [0x27BDFFE8, 0x00000000], strict=True)
        self.assertTrue(alignment.ok)

    def test_strict_reports_first_mismatch(self):
        alignment = sweep.align_words([0x27BDFFE8, 0x00000000], [0x00000000, 0x00000000], strict=True)
        self.assertFalse(alignment.ok)
        self.assertEqual(alignment.first_mismatch, 0)

    def test_length_mismatch_returns_none(self):
        self.assertIsNone(sweep.align_words([1], [1, 2], strict=True))

    def test_loose_allows_reloc_bearing_words_to_differ_in_immediate(self):
        # Same opcode class (lui, same rt) at index 0; only the high half differs.
        alignment = sweep.align_words([0x3C0F800B], [0x3C0F800C], strict=False)
        self.assertTrue(alignment.ok)

    def test_loose_requires_same_opcode_class_for_reloc_bearing_words(self):
        jal = 0x0C01F040
        lui = 0x3C0F800B
        alignment = sweep.align_words([jal], [lui], strict=False)
        self.assertFalse(alignment.ok)
        self.assertEqual(alignment.first_mismatch, 0)

    def test_loose_ignores_non_reloc_bearing_opcode_differences(self):
        add = 0x00000020  # add $zero, $zero, $zero (SPECIAL, funct 0x20)
        sub = 0x00000022  # sub $zero, $zero, $zero (SPECIAL, funct 0x22)
        alignment = sweep.align_words([add], [sub], strict=False)
        self.assertTrue(alignment.ok)


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


class MakeSymbolLookupTest(unittest.TestCase):
    def test_exact_match(self):
        symtab = sweep.S1SymbolTable(
            all_by_addr={0x80100000: "gFoo"}, func_by_addr={}, sorted_addrs=[0x80100000],
            names={"gFoo"}, func_names=set(),
        )
        lookup = sweep.make_symbol_lookup(symtab, set())
        self.assertEqual(lookup(0x80100000), "gFoo")

    def test_containment_offset_not_returned(self):
        symtab = sweep.S1SymbolTable(
            all_by_addr={0x80100000: "gFoo"}, func_by_addr={}, sorted_addrs=[0x80100000],
            names={"gFoo"}, func_names=set(),
        )
        lookup = sweep.make_symbol_lookup(symtab, set())
        self.assertIsNone(lookup(0x80100004))

    def test_unresolvable_returns_none(self):
        symtab = sweep.S1SymbolTable(
            all_by_addr={}, func_by_addr={}, sorted_addrs=[], names=set(), func_names=set(),
        )
        lookup = sweep.make_symbol_lookup(symtab, set())
        self.assertIsNone(lookup(0x80999999))


class BuildRenameMapTest(unittest.TestCase):
    def test_maps_jal_and_hilo_via_lookup(self):
        asm = (
            "glabel func_TEST\n"
            "    /* 000000 80000000 0C01F040 */  jal   SomeFunc\n"
            "    /* 000004 80000004 3C0F800B */  lui   $t7, %hi(D_X)\n"
            "    /* 000008 80000008 25EFB4A0 */  addiu $t7, $t7, %lo(D_X)\n"
        )
        parsed = sweep.parse_gs_asm(asm)
        other_words = [0x0C020000, 0x3C0F8010, 0x25EF2000]
        call_target = sweep.decode_jal_target(other_words[0])
        data_target = sweep.decode_hilo_address(other_words[1], other_words[2])

        def lookup(addr):
            if addr == call_target:
                return "OtherFunc"
            if addr == data_target:
                return "D_OTHER"
            return None

        result = sweep.build_rename_map(parsed, other_words, lookup, {})
        self.assertEqual(result.mapping["OtherFunc"], "SomeFunc")
        self.assertEqual(result.mapping["D_OTHER"], "D_X")
        self.assertEqual(result.unmapped, [])

    def test_unresolved_address_recorded(self):
        parsed = sweep.parse_gs_asm("glabel func_TEST\n    /* 000000 80000000 0C01F040 */  jal   SomeFunc\n")
        result = sweep.build_rename_map(parsed, [0x0C020000], lambda addr: None, {})
        self.assertEqual(len(result.unmapped), 1)
        self.assertIn("unresolved", result.unmapped[0])

    def test_extra_seeds_and_is_never_overridden(self):
        parsed = sweep.parse_gs_asm("glabel func_TEST\n")
        result = sweep.build_rename_map(parsed, [], lambda addr: None, {"Foo": "func_TEST"})
        self.assertEqual(result.mapping, {"Foo": "func_TEST"})

    def test_colliding_names_recorded_as_unmapped(self):
        asm = (
            "glabel func_TEST\n"
            "    /* 000000 80000000 0C01F040 */  jal   FuncA\n"
            "    /* 000004 80000004 0C020000 */  jal   FuncB\n"
        )
        parsed = sweep.parse_gs_asm(asm)
        other_words = [0x0C030000, 0x0C030000]  # both call the same other-side target
        result = sweep.build_rename_map(parsed, other_words, lambda addr: "SameName", {})
        self.assertTrue(any("maps to both" in m for m in result.unmapped))


class RenameIdentifiersTest(unittest.TestCase):
    def test_word_boundary_rename(self):
        text = "D_8009 + D_80090 + D_8009X"
        renamed = sweep.rename_identifiers(text, {"D_8009": "GS_Foo"})
        self.assertEqual(renamed, "GS_Foo + D_80090 + D_8009X")

    def test_prefix_name_not_corrupted_by_longer_replacement_first(self):
        # Renaming the longer name first must not create a substring that
        # then accidentally matches the shorter name's pattern.
        text = "Foo(Foobar())"
        renamed = sweep.rename_identifiers(text, {"Foo": "A", "Foobar": "B"})
        self.assertEqual(renamed, "A(B())")

    def test_empty_map_is_noop(self):
        self.assertEqual(sweep.rename_identifiers("abc", {}), "abc")

    def test_apply_rename_is_an_alias(self):
        self.assertIs(sweep.apply_rename, sweep.rename_identifiers)


class StripCommentsTest(unittest.TestCase):
    def test_line_comment_removed(self):
        self.assertEqual(sweep.strip_comments("int x; // trailing\nint y;"), "int x;  \nint y;")

    def test_block_comment_removed_without_fusing_tokens(self):
        self.assertEqual(sweep.strip_comments("int/*c*/x;"), "int x;")

    def test_multiline_block_comment_collapsed(self):
        result = sweep.strip_comments("a /* line1\nline2 */ b;")
        self.assertNotIn("line1", result)
        self.assertNotIn("line2", result)
        self.assertIn("a", result)
        self.assertIn("b;", result)

    def test_comment_marker_inside_string_preserved(self):
        text = 'char *s = "not // a comment";'
        self.assertEqual(sweep.strip_comments(text), text)

    def test_non_ascii_comment_removed(self):
        result = sweep.strip_comments("u8 a; // note — something\n")
        self.assertTrue(all(ord(c) < 128 for c in result))
        self.assertNotIn("note", result)


class FindAnonymousMembersTest(unittest.TestCase):
    def test_detects_anonymous_struct_member_in_union(self):
        # The real S1 MtxF shape: typedef union { MtxF_t mf; struct {...}; } MtxF;
        type_def = (
            "typedef union {\n"
            "    MtxF_t mf;\n"
            "    struct {\n"
            "        float xx, yx;\n"
            "    };\n"
            "} MtxF;\n"
        )
        self.assertEqual(sweep.find_anonymous_members(type_def), ["struct"])

    def test_named_nested_member_not_flagged(self):
        type_def = "typedef struct {\n    struct { s32 x; } named;\n} Outer;\n"
        self.assertEqual(sweep.find_anonymous_members(type_def), [])

    def test_plain_struct_has_no_anonymous_member(self):
        type_def = "typedef struct Foo {\n    s32 x;\n} Foo;\n"
        self.assertEqual(sweep.find_anonymous_members(type_def), [])

    def test_anonymous_outer_union_itself_not_flagged(self):
        # The outer typedef's own anonymous union brace is a different,
        # already-handled shape and must not itself be reported.
        type_def = "typedef union {\n    s32 a;\n    f32 b;\n} Num;\n"
        self.assertEqual(sweep.find_anonymous_members(type_def), [])


class CommentStrippingDedupTest(unittest.TestCase):
    """Regression test for the stray-struct-member-lines bug.

    Two functions transferring the same S1 struct used to emit
    near-duplicate declaration blocks that differed only in a per-caller
    comment (because the comment mentioned a function name that was in one
    caller's rename map but not the other's), which defeated
    ``merge_declarations``'s line-level dedup and let bare member lines
    leak out after the struct's closing brace.  Comments are gone by the
    time a type reaches ``index_type_definitions``, so this can no longer
    happen.
    """

    def test_two_rename_maps_produce_identical_text(self):
        header = (
            "typedef struct S1_Shared {\n"
            "    /* 0x00 */ u16 state; // FuncA/FuncB's dispatch\n"
            "} S1_Shared;\n"
        )
        index = sweep.index_type_definitions([header])
        text_a = sweep.apply_rename(index["S1_Shared"], {"FuncA": "func_800AAAAA"})
        text_b = sweep.apply_rename(index["S1_Shared"], {"FuncB": "func_800BBBBB"})
        self.assertEqual(text_a, text_b)
        self.assertNotIn("FuncA", text_a)
        self.assertNotIn("//", text_a)


class ExternTypeValidationTest(unittest.TestCase):
    def test_builtin_type_token(self):
        self.assertEqual(sweep._extern_type_token("extern u32 D_800A0000;"), "u32")

    def test_array_type_token(self):
        self.assertEqual(sweep._extern_type_token("extern f32 D_800A0000[0x10];"), "f32")

    def test_pointer_type_token_strips_star(self):
        self.assertEqual(sweep._extern_type_token("extern Gfx* D_800A0000;"), "Gfx")

    def test_unresolved_s1_type_rejected(self):
        self.assertFalse(sweep._is_known_extern_type("unk_D_800A62E0", {}, set()))

    def test_gs_header_type_accepted(self):
        gs_type_index = {"OSMesg": "typedef long OSMesg;"}
        self.assertTrue(sweep._is_known_extern_type("OSMesg", gs_type_index, set()))

    def test_emitted_s1_prefixed_type_accepted(self):
        self.assertTrue(sweep._is_known_extern_type("S1_Foo", {}, {"Foo"}))

    def test_builtin_always_accepted(self):
        self.assertTrue(sweep._is_known_extern_type("u8", {}, set()))

    def test_fallback_array_uses_u8(self):
        decl = sweep._fallback_extern_decl("extern unk_X D_800A0000[0x10];", "D_800A0000")
        self.assertEqual(decl, "extern u8 D_800A0000[0x10];")

    def test_fallback_scalar_uses_s32(self):
        decl = sweep._fallback_extern_decl("extern unk_X D_800A0000;", "D_800A0000")
        self.assertEqual(decl, "extern s32 D_800A0000;")


class MacroIndexTest(unittest.TestCase):
    def test_object_like_macro(self):
        index = sweep.index_macro_definitions(["#define RELOCATIONS_SIZE 1\n"])
        self.assertEqual(index["RELOCATIONS_SIZE"], ("", "1", False))

    def test_function_like_macro_single_line(self):
        text = "#define SINS(x) gSineTable[(u16) (x) >> 4]\n"
        index = sweep.index_macro_definitions([text])
        params, value, multiline = index["SINS"]
        self.assertEqual(params, "(x)")
        self.assertFalse(multiline)
        self.assertIn("gSineTable", value)

    def test_space_before_paren_is_object_like_not_function_like(self):
        # #define NAME (x) -- the space means this is an object-like macro
        # whose expansion happens to start with a parenthesised (x), not a
        # function-like macro taking a parameter x.
        index = sweep.index_macro_definitions(["#define NAME (x)\n"])
        params, value, _ = index["NAME"]
        self.assertEqual(params, "")
        self.assertEqual(value, "(x)")

    def test_multiline_macro_flagged(self):
        index = sweep.index_macro_definitions(["#define FOO(x) ((x) + \\\n    1)\n"])
        self.assertTrue(index["FOO"][2])

    def test_comment_in_macro_stripped(self):
        index = sweep.index_macro_definitions(["#define BAR 1 // note\n"])
        self.assertEqual(index["BAR"][1], "1")


class ApplyRenameTest(unittest.TestCase):
    """Kept under its original name: ``apply_rename`` is a public alias."""

    def test_word_boundary_rename(self):
        text = "D_8009 + D_80090 + D_8009X"
        renamed = sweep.apply_rename(text, {"D_8009": "GS_Foo"})
        self.assertEqual(renamed, "GS_Foo + D_80090 + D_8009X")

    def test_prefix_name_not_corrupted_by_longer_replacement_first(self):
        text = "Foo(Foobar())"
        renamed = sweep.apply_rename(text, {"Foo": "A", "Foobar": "B"})
        self.assertEqual(renamed, "A(B())")

    def test_empty_map_is_noop(self):
        self.assertEqual(sweep.apply_rename("abc", {}), "abc")

    def test_sanitize_candidate_text_replaces_unencodable_punctuation(self):
        self.assertEqual(sweep.sanitize_candidate_text("/* CPU \u2014 player */\n"), "/* CPU ? player */\n")


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

    def test_anonymous_typedef_name_after_brace_indexed(self):
        # typedef union { ... } MtxF; -- the name comes after the closing
        # brace; it must still be the index key (this shape already worked
        # before the anonymous-member fix; the fix is about the nested
        # struct member inside it, covered by FindAnonymousMembersTest).
        header = "typedef union {\n    s32 a;\n    f32 b;\n} MtxF;\n"
        index = sweep.index_type_definitions([header])
        self.assertIn("MtxF", index)
        self.assertTrue(index["MtxF"].rstrip().endswith("} MtxF;"))

    def test_transitive_collection_with_s1_prefix(self):
        header = (
            "typedef struct Inner {\n    s32 x;\n} Inner;\n\n"
            "typedef struct Outer {\n    Inner inner;\n} Outer;\n"
        )
        index = sweep.index_type_definitions([header])
        collected = sweep._collect_referenced_types({"Outer"}, index, max_depth=4)
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
        collected = sweep._collect_referenced_types({"E"}, index, max_depth=1)
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
        collected = sweep._collect_referenced_types({"A"}, index)
        self.assertIn("F", collected)

    def test_referenced_types_include_extern_only_state_types(self):
        index = sweep.index_type_definitions([
            "typedef struct SchedulerState { s32 shutdownCounter; } SchedulerState;\n"
        ])
        declarations = ["extern SchedulerState D_800CD020;"]
        self.assertEqual(sweep.referenced_type_names(declarations, index), {"SchedulerState"})

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


class PublicCollectTypeDefinitionsTest(unittest.TestCase):
    """The stable, generic (body, header_index, prefix) -> list[str] API."""

    def test_prefixes_and_orders_referenced_types(self):
        header = (
            "typedef struct Inner {\n    s32 x;\n} Inner;\n\n"
            "typedef struct Outer {\n    Inner inner;\n} Outer;\n"
        )
        index = sweep.index_type_definitions([header])
        body = "void Foo(Outer *o) { return; }"
        result = sweep.collect_type_definitions(body, index, "S1_")
        self.assertEqual(len(result), 2)
        inner_pos = next(i for i, d in enumerate(result) if "typedef struct S1_Inner" in d)
        outer_pos = next(i for i, d in enumerate(result) if "typedef struct S1_Outer" in d)
        self.assertLess(inner_pos, outer_pos)
        self.assertIn("S1_Inner inner;", result[outer_pos])

    def test_ignores_identifiers_only_in_comments(self):
        index = sweep.index_type_definitions(["typedef struct Foo { s32 x; } Foo;\n"])
        body = "void Bar(void) { // mentions Foo only in a comment\n    return;\n}"
        result = sweep.collect_type_definitions(body, index, "S1_")
        self.assertEqual(result, [])

    def test_no_referenced_types_yields_empty_list(self):
        index = sweep.index_type_definitions(["typedef struct Foo { s32 x; } Foo;\n"])
        result = sweep.collect_type_definitions("void Bar(void) { return; }", index, "S1_")
        self.assertEqual(result, [])


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

    def test_partitions_disjoint_declarations_to_avoid_cross_contamination(self):
        first = sweep.TransferResult(
            function="func_A", outcome="candidate",
            declaration_units=["typedef struct S1_A { s32 x; } S1_A;"],
        )
        second = sweep.TransferResult(
            function="func_B", outcome="candidate",
            declaration_units=["typedef struct S1_B { s32 y; } S1_B;"],
        )
        no_declarations = sweep.TransferResult(function="func_C", outcome="candidate")
        another_no_declarations = sweep.TransferResult(function="func_D", outcome="candidate")

        groups = sweep.partition_transfer_results([first, second, no_declarations, another_no_declarations])

        self.assertEqual(
            [[result.function for result in group] for group in groups],
            [["func_A"], ["func_B"], ["func_C", "func_D"]],
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
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            owner = self._make_owner("func_TEST", "glabel func_TEST\n", tmp_path)
            transfer_map = {"func_TEST": ("Foo", "Stadium 1 Foo @ 0x80100000 (text); match class identical; 0 instructions")}
            ctx = mock.Mock()
            ctx.s1_functions = {"Foo": {"vram": 0x80100000, "seg": "text", "w": ()}}
            ctx.func_file_index = {}  # Foo is still GLOBAL_ASM in S1: no .c defines it
            result = sweep.generate_candidate("func_TEST", owner, ctx, transfer_map, {})
        self.assertEqual(result.outcome, "s1_body_missing")


class _FullContextTestCase(unittest.TestCase):
    """Shared scaffolding for tests that exercise the full candidate pipeline."""

    def _make_owner(self, function: str, asm_text: str, tmp_path: Path):
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

    def _make_ctx(self, tmp_path: Path, s1_name: str, s1_body: str, s1_words: tuple[int, ...], **overrides):
        (tmp_path / "s1.c").write_text(s1_body, encoding="utf-8")
        ctx = mock.Mock()
        ctx.s1_functions = {s1_name: {"vram": 0x80100000, "seg": "text", "w": s1_words}}
        ctx.func_file_index = {s1_name: tmp_path / "s1.c"}
        ctx.gs_asm_fallback = None
        ctx.symtab = overrides.pop("symtab", sweep.S1SymbolTable(
            all_by_addr={}, func_by_addr={}, sorted_addrs=[], names=set(), func_names=set(),
        ))
        ctx.type_index = overrides.pop("type_index", {})
        ctx.extern_index = overrides.pop("extern_index", {})
        ctx.macro_index = overrides.pop("macro_index", {})
        ctx.gs_type_index = overrides.pop("gs_type_index", {})
        ctx.gs_macro_index = overrides.pop("gs_macro_index", {})
        return ctx


class ExternFallbackAndTravelIntegrationTest(_FullContextTestCase):
    """End-to-end (a)/(c)/(d) fixes: an unresolved extern type, an anonymous
    typedef member, and a macro travel across generate_candidate's full
    pipeline for one function -- the real production shapes from
    disasm/build/probe-stats.jsonl."""

    def _asm_and_s1_words(self):
        # lui $at, %hi(D_800CD020) ; nop ; addiu $at, $at, %lo(D_800CD020)
        # S1-side words decode (hi=0x8020, lo=0x0000) -> 0x80200000, which
        # the symtab maps to data symbol "D_800A62E0".
        asm_text = (
            "glabel func_TEST\n"
            "    /* 000000 80000000 3C010000 */  lui   $at, %hi(D_800CD020)\n"
            "    /* 000004 80000004 00000000 */  nop\n"
            "    /* 000008 80000008 24210001 */  addiu $at, $at, %lo(D_800CD020)\n"
        )
        s1_words = (0x3C018020, 0x00000000, 0x24210000)
        return asm_text, s1_words

    def test_unresolved_extern_type_falls_back_and_is_recorded(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            asm_text, s1_words = self._asm_and_s1_words()
            owner = self._make_owner("func_TEST", asm_text, tmp_path)
            symtab = sweep.S1SymbolTable(
                all_by_addr={0x80200000: "D_800A62E0"}, func_by_addr={},
                sorted_addrs=[0x80200000], names={"D_800A62E0"}, func_names=set(),
            )
            ctx = self._make_ctx(
                tmp_path, "Foo",
                "void Foo(void) {\n    D_800A62E0.field = 1;\n}\n",
                s1_words,
                symtab=symtab,
                extern_index={"D_800A62E0": "extern unk_D_800A62E0 D_800A62E0;"},
            )
            transfer_map = {"func_TEST": ("Foo", "Stadium 1 Foo @ 0x80100000 (text); match class identical; 3 instructions")}
            result = sweep.generate_candidate("func_TEST", owner, ctx, transfer_map, {})

        self.assertEqual(result.outcome, "candidate")
        self.assertEqual(result.symbol_map["D_800A62E0"], "D_800CD020")
        self.assertEqual(result.unresolved_extern_types, ["D_800CD020: unk_D_800A62E0"])
        self.assertIn("extern s32 D_800CD020;", result.declarations)
        self.assertNotIn("unk_D_800A62E0", result.declarations)

    def test_anonymous_member_type_excluded_and_macro_travels(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            asm_text, s1_words = self._asm_and_s1_words()
            owner = self._make_owner("func_TEST", asm_text, tmp_path)
            symtab = sweep.S1SymbolTable(
                all_by_addr={0x80200000: "D_800A62E0"}, func_by_addr={},
                sorted_addrs=[0x80200000], names={"D_800A62E0"}, func_names=set(),
            )
            ctx = self._make_ctx(
                tmp_path, "Foo",
                (
                    "void Foo(void) {\n"
                    "    MtxF m;\n"
                    "    char buf[FOO_SIZE];\n"
                    "    D_800A62E0.field = 1;\n"
                    "}\n"
                ),
                s1_words,
                symtab=symtab,
                extern_index={"D_800A62E0": "extern unk_D_800A62E0 D_800A62E0;"},
                type_index={
                    "MtxF": (
                        "typedef union {\n"
                        "    MtxF_t mf;\n"
                        "    struct {\n"
                        "        float xx, yx;\n"
                        "    };\n"
                        "} MtxF;"
                    ),
                },
                macro_index={"FOO_SIZE": ("", "4", False)},
            )
            transfer_map = {"func_TEST": ("Foo", "Stadium 1 Foo @ 0x80100000 (text); match class identical; 3 instructions")}
            result = sweep.generate_candidate("func_TEST", owner, ctx, transfer_map, {})

        self.assertEqual(result.outcome, "candidate")
        self.assertEqual(result.unsupported_types, ["MtxF"])
        self.assertNotIn("typedef union", result.declarations)
        self.assertIn("#define FOO_SIZE 4", result.declarations)
        self.assertEqual(result.unresolved_extern_types, ["D_800CD020: unk_D_800A62E0"])

    def test_macro_prefixed_when_gs_defines_it_differently(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            asm_text, s1_words = self._asm_and_s1_words()
            owner = self._make_owner("func_TEST", asm_text, tmp_path)
            ctx = self._make_ctx(
                tmp_path, "Foo",
                "void Foo(void) {\n    char buf[FOO_SIZE];\n}\n",
                s1_words,
                macro_index={"FOO_SIZE": ("", "4", False)},
                gs_macro_index={"FOO_SIZE": ("", "999", False)},
            )
            transfer_map = {"func_TEST": ("Foo", "Stadium 1 Foo @ 0x80100000 (text); match class identical; 3 instructions")}
            result = sweep.generate_candidate("func_TEST", owner, ctx, transfer_map, {})

        self.assertEqual(result.outcome, "candidate")
        self.assertIn("#define S1_FOO_SIZE 4", result.declarations)
        self.assertIn("S1_FOO_SIZE", result.variants[0][1])

    def test_macro_not_repeated_when_gs_defines_it_identically(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            asm_text, s1_words = self._asm_and_s1_words()
            owner = self._make_owner("func_TEST", asm_text, tmp_path)
            ctx = self._make_ctx(
                tmp_path, "Foo",
                "void Foo(void) {\n    char buf[FOO_SIZE];\n}\n",
                s1_words,
                macro_index={"FOO_SIZE": ("", "4", False)},
                gs_macro_index={"FOO_SIZE": ("", "4", False)},
            )
            transfer_map = {"func_TEST": ("Foo", "Stadium 1 Foo @ 0x80100000 (text); match class identical; 3 instructions")}
            result = sweep.generate_candidate("func_TEST", owner, ctx, transfer_map, {})

        self.assertEqual(result.outcome, "candidate")
        self.assertNotIn("#define", result.declarations)

    def test_macro_used_only_inside_a_pulled_in_type_still_travels(self):
        # The real S1_Fragment shape: RELOCATIONS_SIZE only ever appears
        # inside the struct's own field, never in the transferred function
        # body itself -- the body only names the struct type.
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            asm_text, s1_words = self._asm_and_s1_words()
            owner = self._make_owner("func_TEST", asm_text, tmp_path)
            ctx = self._make_ctx(
                tmp_path, "Foo",
                "void Foo(Fragment *f) {\n    return;\n}\n",
                s1_words,
                type_index={
                    "Fragment": (
                        "typedef struct Fragment {\n"
                        "    char data[RELOCATIONS_SIZE];\n"
                        "} Fragment;"
                    ),
                },
                macro_index={"RELOCATIONS_SIZE": ("", "1", False)},
            )
            transfer_map = {"func_TEST": ("Foo", "Stadium 1 Foo @ 0x80100000 (text); match class identical; 3 instructions")}
            result = sweep.generate_candidate("func_TEST", owner, ctx, transfer_map, {})

        self.assertEqual(result.outcome, "candidate")
        self.assertIn("#define RELOCATIONS_SIZE 1", result.declarations)


class AsciiGuardTest(_FullContextTestCase):
    def test_non_ascii_in_code_yields_non_ascii_outcome(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            asm_text = "glabel func_TEST\n    /* 000000 80000000 27BDFFE8 */  addiu $sp, $sp, -0x18\n"
            owner = self._make_owner("func_TEST", asm_text, tmp_path)
            ctx = self._make_ctx(
                tmp_path, "Foo",
                'void Foo(void) {\n    char *s = "café";\n}\n',
                (0x27BDFFE8,),
            )
            transfer_map = {"func_TEST": ("Foo", "Stadium 1 Foo @ 0x80100000 (text); match class identical; 1 instructions")}
            result = sweep.generate_candidate("func_TEST", owner, ctx, transfer_map, {})
        self.assertEqual(result.outcome, "non_ascii")

    def test_non_ascii_comment_does_not_block_candidate(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            asm_text = "glabel func_TEST\n    /* 000000 80000000 27BDFFE8 */  addiu $sp, $sp, -0x18\n"
            owner = self._make_owner("func_TEST", asm_text, tmp_path)
            ctx = self._make_ctx(
                tmp_path, "Foo",
                'void Foo(void) {\n    // note — dash\n    return;\n}\n',
                (0x27BDFFE8,),
            )
            transfer_map = {"func_TEST": ("Foo", "Stadium 1 Foo @ 0x80100000 (text); match class identical; 1 instructions")}
            result = sweep.generate_candidate("func_TEST", owner, ctx, transfer_map, {})
        self.assertEqual(result.outcome, "candidate")
        self.assertTrue(all(ord(c) < 128 for c in result.variants[0][1]))


class GenerateCandidateTypeDedupTest(unittest.TestCase):
    def test_prefixed_typedef_matches_installed_stripped_struct(self):
        """Do not emit a second S1 type when the owner has its stripped form."""
        import tempfile

        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            asm_path = tmp_path / "func_TEST.s"
            asm_path.write_text(
                "glabel func_TEST\n"
                "    /* 000000 80000000 00000000 */  nop\n"
            )
            owner_source = tmp_path / "source.c"
            owner_source.write_text(
                "struct S1_Foo {\n"
                "    s32 value;\n"
                "};\n"
            )
            s1_source = tmp_path / "s1.c"
            s1_source.write_text(
                "void FooFunc(void) {\n"
                "    Foo value;\n"
                "    (void)value.value;\n"
                "}\n"
            )
            owner = mock.Mock(
                function="func_TEST",
                asm_path=asm_path,
                asm=str(asm_path),
                source_path=owner_source,
            )
            ctx = mock.Mock()
            ctx.s1_functions = {"FooFunc": {"w": [0]}}
            ctx.func_file_index = {"FooFunc": s1_source}
            ctx.gs_asm_fallback = None
            ctx.symtab = sweep.S1SymbolTable(
                all_by_addr={}, func_by_addr={}, sorted_addrs=[],
                names=set(), func_names=set(),
            )
            ctx.extern_index = {}
            ctx.type_index = sweep.index_type_definitions([
                "typedef struct Foo {\n"
                "    s32 value;\n"
                "} Foo;\n"
            ])
            ctx.gs_type_index = {}
            ctx.macro_index = {}
            ctx.gs_macro_index = {}

            result = sweep.generate_candidate(
                "func_TEST",
                owner,
                ctx,
                {"func_TEST": ("FooFunc", "Stadium 1 FooFunc @ 0x80100000 (text); match class identical; 1 instructions")},
                {},
            )

        self.assertEqual(result.outcome, "candidate")
        self.assertEqual(result.declaration_units, [])
        self.assertNotIn("S1_Foo", result.declarations)

    def test_prefixed_typedef_matches_installed_struct_ignoring_comments(self):
        installed = """struct S1_Foo {
            /* GS comment */
            s32 value; // owner spelling
        };"""
        transferred = """typedef struct Foo {
            /* S1 comment */
            s32 value; // source spelling
        } Foo;"""
        self.assertEqual(
            sweep._normalize_type_definition(installed),
            sweep._normalize_type_definition(sweep.apply_rename(transferred, {"Foo": "S1_Foo"})),
        )


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


class SelectNearMatchFunctionsTest(unittest.TestCase):
    def test_excludes_functions_already_in_transfer_map(self):
        transfer_map = {"func_A": ("A", "...")}
        owners = {
            "func_A": mock.Mock(source="s.c", source_path=Path("/repo/a.c")),
            "func_B": mock.Mock(source="s.c", source_path=Path("/repo/b.c")),
        }
        with mock.patch.object(sweep.targets, "owner_index", return_value=owners), \
             mock.patch.object(sweep.dedupe_externs, "dirty_sources", return_value=set()):
            selected = sweep.select_near_match_functions(transfer_map, functions=None, source=None, limit=None)
        self.assertEqual(selected, ["func_B"])

    def test_dirty_source_skipped(self):
        transfer_map: dict[str, tuple[str, str]] = {}
        owner_a = mock.Mock(source="s.c", source_path=Path("/repo/a.c"))
        with mock.patch.object(sweep.targets, "owner_index", return_value={"func_A": owner_a}), \
             mock.patch.object(sweep.dedupe_externs, "dirty_sources", return_value={Path("/repo/a.c")}):
            selected = sweep.select_near_match_functions(transfer_map, functions=None, source=None, limit=None)
        self.assertEqual(selected, [])


class NearMatchRankingTest(unittest.TestCase):
    def test_bucket_by_length_only_includes_decompiled_bodies(self):
        ctx = mock.Mock()
        ctx.func_file_index = {"Foo": Path("foo.c")}
        ctx.s1_functions = {
            "Foo": {"w": (1, 2, 3)},
            "Bar": {"w": (1, 2)},  # not in func_file_index -> still GLOBAL_ASM in S1
        }
        buckets = sweep.bucket_s1_by_length(ctx)
        self.assertEqual(buckets, {3: ["Foo"]})

    def test_find_near_match_picks_best_and_requires_identical_length(self):
        ctx = mock.Mock()
        ctx.s1_functions = {
            "Close": {"w": (0x27BDFFE8, 0x00000000, 0x00000001)},
            "Exact": {"w": (0x27BDFFE8, 0x00000000, 0x00000000)},
        }
        buckets = {3: ["Close", "Exact"]}
        gs_words = [0x27BDFFE8, 0x00000000, 0x00000000]
        result = sweep.find_near_match(gs_words, buckets, ctx, minimum=0.85)
        self.assertEqual(result[0], "Exact")
        self.assertEqual(result[1], 1.0)

    def test_find_near_match_below_threshold_returns_none(self):
        ctx = mock.Mock()
        ctx.s1_functions = {"Weird": {"w": (1, 2, 3)}}
        buckets = {3: ["Weird"]}
        result = sweep.find_near_match([9, 9, 9], buckets, ctx, minimum=0.85)
        self.assertIsNone(result)

    def test_find_near_match_no_same_length_candidate(self):
        ctx = mock.Mock()
        ctx.s1_functions = {}
        result = sweep.find_near_match([1, 2, 3], {}, ctx, minimum=0.85)
        self.assertIsNone(result)


class GenerateNearMatchCandidateTest(_FullContextTestCase):
    def test_label_includes_s1_name_and_score(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            asm_text = (
                "glabel func_TEST\n"
                "    /* 000000 80000000 27BDFFE8 */  addiu $sp, $sp, -0x18\n"
                "    /* 000004 80000004 00000000 */  nop\n"
            )
            owner = self._make_owner("func_TEST", asm_text, tmp_path)
            ctx = self._make_ctx(
                tmp_path, "Foo", "void Foo(void) {\n    return;\n}\n", (0x27BDFFE8, 0x00000000),
            )
            result = sweep.generate_near_match_candidate("func_TEST", owner, ctx, "Foo", 0.91, {})
        self.assertEqual(result.outcome, "candidate")
        self.assertEqual(result.similarity, 0.91)
        self.assertEqual(result.variants[0][0], "s1-near:Foo:0.91")

    def test_loose_alignment_tolerates_differing_register_only_words(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            asm_text = "glabel func_TEST\n    /* 000000 80000000 00000020 */  add $zero, $zero, $zero\n"
            owner = self._make_owner("func_TEST", asm_text, tmp_path)
            # A different (but same opcode class -- SPECIAL) register-only S1 word.
            ctx = self._make_ctx(
                tmp_path, "Foo", "void Foo(void) {\n    return;\n}\n", (0x00000022,),
            )
            result = sweep.generate_near_match_candidate("func_TEST", owner, ctx, "Foo", 0.5, {})
        self.assertEqual(result.outcome, "candidate")

    def test_strict_alignment_would_reject_the_same_words(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            asm_text = "glabel func_TEST\n    /* 000000 80000000 0C01F040 */  jal SomeFunc\n"
            owner = self._make_owner("func_TEST", asm_text, tmp_path)
            ctx = self._make_ctx(
                tmp_path, "Foo", "void Foo(void) {\n    return;\n}\n", (0x3C0F800B,),  # lui, not jal
            )
            transfer_map = {"func_TEST": ("Foo", "Stadium 1 Foo @ 0x80100000 (text); match class identical; 1 instructions")}
            strict_result = sweep.generate_candidate("func_TEST", owner, ctx, transfer_map, {})
            near_result = sweep.generate_near_match_candidate("func_TEST", owner, ctx, "Foo", 0.5, {})
        self.assertEqual(strict_result.outcome, "alignment_failed")
        self.assertEqual(near_result.outcome, "alignment_failed")  # jal vs lui differs in opcode class too


class BuildGsContextTest(unittest.TestCase):
    def test_missing_rom_raises_clear_error(self):
        with mock.patch.object(sweep.os.path, "exists", return_value=False):
            with self.assertRaises(FileNotFoundError) as cm:
                sweep.build_gs_context()
        self.assertIn("Stadium 2 ROM", str(cm.exception))


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

    def test_dry_run_near_matches_never_touches_runner(self):
        owner = mock.Mock(function="func_TEST", source_path=Path("/repo/source.c"))
        ctx = mock.Mock()
        ctx.func_file_index = {}
        with mock.patch.object(sweep.targets, "owner_index", return_value={"func_TEST": owner}), \
             mock.patch.object(sweep.runner, "try_candidates_detailed") as fake_runner:
            result = sweep.dry_run_near_matches(
                ["func_TEST"], ctx=ctx, gs_functions={}, s1_reverse_index={},
                minimum=0.85, strict=False, show_text=False,
            )
        fake_runner.assert_not_called()
        self.assertEqual(result["outcome_counts"], {"gs_function_missing": 1})


if __name__ == "__main__":
    unittest.main()
