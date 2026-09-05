#!/usr/bin/env python3
"""Unit tests for the shared-page ``lui $at`` coalescing mechanism.

``coalesce_lui.py`` lives under ``disasm/tools`` (alongside the other
build-time tooling it plugs into -- asm-processor, the IDO port) rather than
under top-level ``tools/``; this mirrors ``tools/test_pragma_tools.py``'s own
``sys.path`` trick for importing the vendored ``asm_processor`` module.
"""
from __future__ import annotations

import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

_DISASM_TOOLS = Path(__file__).resolve().parent.parent / "disasm" / "tools"
sys.path.insert(0, str(_DISASM_TOOLS))
import coalesce_lui  # noqa: E402


# The real func_84136D84 shape: IDO's -S output before any transform, for
#     extern void *D_84186160, *D_84186164, *D_84186168, *D_8418616C;
#     void func_84136D84(void) {
#         D_84186160 = 0; D_84186164 = 0; D_84186168 = 0; D_8418616C = 0;
#     }
FUNC_84136D84_S = """\
\t.verstamp\t7 10
\t.option\tpic0
\t.extern\tD_84186160 4
\t.extern\tD_84186164 4
\t.extern\tD_84186168 4
\t.extern\tD_8418616C 4
\t.text\t
\t.align\t2
\t.file\t2 "f.c"
\t.globl\tfunc_84136D84
\t.loc\t2 2
 #   1\textern void *D_84186160, *D_84186164, *D_84186168, *D_8418616C;
 #   2\tvoid func_84136D84(void) {
\t.ent\tfunc_84136D84 2
func_84136D84:
\t.option\tO2
\t.frame\t$sp, 0, $31
\t.loc\t2 2
\t.loc\t2 3
 #   3\t    D_84186160 = 0;
\tsw\t$0, D_84186160
\t.loc\t2 4
 #   4\t    D_84186164 = 0;
\tsw\t$0, D_84186164
\t.loc\t2 5
 #   5\t    D_84186168 = 0;
\tsw\t$0, D_84186168
\t.loc\t2 6
 #   6\t    D_8418616C = 0;
\tsw\t$0, D_8418616C
\t.loc\t2 7
 #   7\t}
\t.livereg\t0x0000FF0E,0x00000FFF
\tj\t$31
\t.end\tfunc_84136D84
"""

ADDRESS_MAP = {
    "D_84186160": 0x84186160,
    "D_84186164": 0x84186164,
    "D_84186168": 0x84186168,
    "D_8418616C": 0x8418616C,
}


class HiLoTest(unittest.TestCase):
    def test_hi16_no_rounding_needed(self):
        self.assertEqual(coalesce_lui.hi16(0x84186160), 0x8418)

    def test_hi16_rounds_up_for_negative_lo(self):
        # A %lo whose sign bit is set (>= 0x8000) needs the %hi bumped by one,
        # exactly like the real MIPS %hi/%lo convention.
        self.assertEqual(coalesce_lui.hi16(0x84188500), 0x8419)

    def test_lo16_masks_low_bits(self):
        self.assertEqual(coalesce_lui.lo16(0x84186164), 0x6164)


class SignedLo16LiteralTest(unittest.TestCase):
    """Regression test for a real bug: the folded literal must be a signed
    16-bit immediate, not the raw unsigned hex value.

    MIPS load/store immediates are a signed 16-bit field. GNU as parses a
    bare offset literal by its own numeric range, not by the target field's
    width, so for any address whose low 16 bits have bit 15 set (roughly
    half of all possible addresses) the unsigned hex form reads as too
    large for a direct signed-immediate encoding and `as` falls back to
    macro expansion -- which then hard-fails inside `.set noat` (reproduced
    directly below, and independently by hand: `.set noat; sw $0,
    0x9000($at)` under this project's exact assembler flags errors with
    "macro used $at after '.set noat'"). The old code's own comment
    claiming "assemblers accept this unsigned" was simply wrong.
    """

    def test_bit15_clear_stays_unsigned_hex(self):
        self.assertEqual(coalesce_lui._lo16_immediate_literal(0x84186164), "0x6164")

    def test_bit15_set_becomes_signed_decimal(self):
        # lo16(0x84178500) == 0x8500, which has bit 15 set.
        literal = coalesce_lui._lo16_immediate_literal(0x84178500)
        self.assertEqual(literal, "-31488")  # 0x8500 - 0x10000
        self.assertEqual(int(literal) & 0xFFFF, 0x8500)

    def test_fold_emits_signed_literal_for_a_bit15_set_operand(self):
        # A minimal two-store run sharing a %hi page, where the second
        # symbol's low 16 bits have bit 15 set -- exactly the shape the
        # unsigned-hex bug corrupted.
        source = (
            "\t.ent\tfunc_signbit 2\n"
            "func_signbit:\n"
            "\tsw\t$0, D_84186160\n"
            "\tsw\t$0, D_84178500\n"
            "\tj\t$31\n"
            "\t.end\tfunc_signbit\n"
        )
        address_map = {"D_84186160": 0x84186160, "D_84178500": 0x84178500}
        folded, count = coalesce_lui.fold_source(source, {"func_signbit"}, address_map)
        self.assertEqual(count, 1)
        self.assertIn("\tsw\t$0, -31488($at)\t# D_84178500\n", folded)
        self.assertNotIn("0x8500", folded)

    @unittest.skipUnless(shutil.which("mips-linux-gnu-as"), "no MIPS GNU as available")
    def test_folded_bit15_set_operand_actually_assembles(self):
        # End-to-end reproduction of the reviewer's exact failure and fix,
        # through this project's real assembler flags (see coalesce_cc.py's
        # _as_binary invocation).
        snippet = (
            "\t.text\n"
            "\t.align\t2\n"
            "\t.globl\tfunc_signbit\n"
            "func_signbit:\n"
            "\t.set\tnoat\n"
            "\tlui\t$at, 0x8418\n"
            "\tsw\t$0, %s($at)\n"
            "\t.set\tat\n"
            "\tj\t$31\n"
            "\t.size\tfunc_signbit, . - func_signbit\n"
        )
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)

            unsigned_path = tmp_path / "unsigned.s"
            unsigned_path.write_text(snippet % "0x8500")
            unsigned_result = subprocess.run(
                ["mips-linux-gnu-as", "-march=vr4300", "-32", "-G0", "-EB",
                 "-o", str(tmp_path / "unsigned.o"), str(unsigned_path)],
                capture_output=True, text=True, timeout=30,
            )
            self.assertNotEqual(unsigned_result.returncode, 0)
            self.assertIn("noat", unsigned_result.stderr)

            signed_literal = coalesce_lui._lo16_immediate_literal(0x84178500)
            signed_path = tmp_path / "signed.s"
            signed_path.write_text(snippet % signed_literal)
            signed_object = tmp_path / "signed.o"
            signed_result = subprocess.run(
                ["mips-linux-gnu-as", "-march=vr4300", "-32", "-G0", "-EB",
                 "-o", str(signed_object), str(signed_path)],
                capture_output=True, text=True, timeout=30,
            )
            self.assertEqual(signed_result.returncode, 0, signed_result.stderr)

            objcopy = shutil.which("mips-linux-gnu-objcopy")
            if objcopy:
                text_bin = tmp_path / "signed.text.bin"
                subprocess.run(
                    [objcopy, "-O", "binary", "--only-section=.text",
                     str(signed_object), str(text_bin)],
                    check=True, timeout=30,
                )
                data = text_bin.read_bytes()
                # lui $at,0x8418 ; jr $31 ; sw $0,0x8500($at) (delay slot)
                # -- GNU as's default .set reorder moves the independent
                # store into the branch delay slot, exactly like the real
                # func_84136D84 ground truth this mechanism targets.
                self.assertEqual(
                    data[:12].hex(), "3c018418" + "03e00008" + "ac208500"
                )


class FoldGenuineCaseTest(unittest.TestCase):
    """The real func_84136D84 shape must fold when opted in."""

    def test_folds_when_opted_in_and_addresses_resolve(self):
        folded, count = coalesce_lui.fold_source(
            FUNC_84136D84_S, {"func_84136D84"}, ADDRESS_MAP
        )
        self.assertEqual(count, 3)
        self.assertIn("\t.set\tnoat\n", folded)
        self.assertIn("\tlui\t$at, %hi(D_84186160)\n", folded)
        # First operand keeps a fully symbolic %lo pair.
        self.assertIn("\tsw\t$0, %lo(D_84186160)($at)\n", folded)
        # Every subsequent operand becomes a literal immediate off the same
        # $at (this sidesteps a relocation-duplication bug in this project's
        # IDO port when %lo() is repeated for a *different* symbol -- see the
        # module docstring).
        self.assertIn("\tsw\t$0, 0x6164($at)", folded)
        self.assertIn("\tsw\t$0, 0x6168($at)", folded)
        self.assertIn("\tsw\t$0, 0x616c($at)", folded)
        self.assertIn("\t.set\tat\n", folded)
        # Only one lui remains for the whole run.
        self.assertEqual(folded.count("\tlui\t$at"), 1)
        # No bare (unfolded) macro-form store should survive.
        self.assertNotIn("\tsw\t$0, D_84186164\n", folded)
        # Directive/comment lines inside the run are preserved, not dropped.
        self.assertIn(" #   6\t    D_8418616C = 0;\n", folded)
        self.assertIn("\t.livereg\t0x0000FF0E,0x00000FFF\n", folded)
        self.assertIn("\tj\t$31\n", folded)
        self.assertIn("\t.end\tfunc_84136D84\n", folded)

    def test_lines_outside_the_run_are_untouched(self):
        folded, _ = coalesce_lui.fold_source(
            FUNC_84136D84_S, {"func_84136D84"}, ADDRESS_MAP
        )
        for line in (
            "\t.verstamp\t7 10\n",
            "\t.extern\tD_84186160 4\n",
            "\t.globl\tfunc_84136D84\n",
            "\t.ent\tfunc_84136D84 2\n",
            "func_84136D84:\n",
            "\t.option\tO2\n",
            "\t.frame\t$sp, 0, $31\n",
        ):
            self.assertIn(line, folded)


class FoldMustNotApplyTest(unittest.TestCase):
    """Cases the fold must leave completely untouched."""

    def test_not_opted_in_leaves_source_byte_identical(self):
        # Same shape, same resolvable addresses -- but the function is not in
        # the allow-list. This is the hard safety requirement: opt-in is
        # mandatory, not merely a hint.
        folded, count = coalesce_lui.fold_source(FUNC_84136D84_S, set(), ADDRESS_MAP)
        self.assertEqual(count, 0)
        self.assertEqual(folded, FUNC_84136D84_S)

    def test_opted_in_but_addresses_unknown_does_not_fold(self):
        folded, count = coalesce_lui.fold_source(
            FUNC_84136D84_S, {"func_84136D84"}, {}
        )
        self.assertEqual(count, 0)
        self.assertEqual(folded, FUNC_84136D84_S)

    def test_mismatched_pages_does_not_fold(self):
        # Two stores whose symbols land on different 64K pages: sharing one
        # lui across them would compute the wrong address for one of them.
        source = (
            "\t.ent\tfunc_two_pages 2\n"
            "func_two_pages:\n"
            "\tsw\t$0, D_84186160\n"
            "\tsw\t$0, D_84186164\n"
            "\tj\t$31\n"
            "\t.end\tfunc_two_pages\n"
        )
        bad_map = {
            "D_84186160": 0x84186160,
            "D_84186164": 0x84190164,  # different %hi page from the above
        }
        folded, count = coalesce_lui.fold_source(
            source, {"func_two_pages"}, bad_map
        )
        self.assertEqual(count, 0)
        self.assertEqual(folded, source)

    def test_partial_run_within_a_larger_mismatch_still_folds_only_that_pair(self):
        # func_84136D84's own four stores, but with the *second* symbol
        # pushed onto a different page. The run splits: D_84186160 alone
        # can't fold (no partner left on its page), but D_84186168/D_8418616C
        # still share a page and fold as their own two-element run. This
        # documents real behavior -- the safety property under test
        # elsewhere is that a symbol never gets folded onto the wrong page,
        # not that one mismatch blanks out an entire function.
        bad_map = dict(ADDRESS_MAP)
        bad_map["D_84186164"] = 0x84190164
        folded, count = coalesce_lui.fold_source(
            FUNC_84136D84_S, {"func_84136D84"}, bad_map
        )
        self.assertEqual(count, 1)
        self.assertIn("\tsw\t$0, D_84186160\n", folded)  # unfolded, alone
        self.assertIn("\tsw\t$0, D_84186164\n", folded)  # unfolded, alone
        self.assertIn("\tlui\t$at, %hi(D_84186168)\n", folded)
        self.assertIn("\tsw\t$0, %lo(D_84186168)($at)\n", folded)
        self.assertIn("\tsw\t$0, 0x616c($at)", folded)

    def test_single_symbol_run_does_not_fold(self):
        source = (
            "\t.ent\tfunc_solo 2\n"
            "func_solo:\n"
            "\tsw\t$0, D_84186160\n"
            "\tj\t$31\n"
            "\t.end\tfunc_solo\n"
        )
        folded, count = coalesce_lui.fold_source(
            source, {"func_solo"}, ADDRESS_MAP
        )
        self.assertEqual(count, 0)
        self.assertEqual(folded, source)

    def test_at_clobbering_instruction_breaks_the_run(self):
        # An ordinary (non-macro-memop) instruction between two stores must
        # end the run -- it might clobber $at, so nothing after it may be
        # folded onto the lui before it.
        source = (
            "\t.ent\tfunc_break 2\n"
            "func_break:\n"
            "\tsw\t$0, D_84186160\n"
            "\taddiu\t$at, $zero, 1\n"
            "\tsw\t$0, D_84186164\n"
            "\tj\t$31\n"
            "\t.end\tfunc_break\n"
        )
        folded, count = coalesce_lui.fold_source(
            source, {"func_break"}, ADDRESS_MAP
        )
        self.assertEqual(count, 0)
        self.assertEqual(folded, source)

    def test_only_the_named_function_is_touched_in_a_multi_function_file(self):
        # A second, unrelated function with the exact same foldable shape
        # must be left alone when only the first is opted in.
        source = FUNC_84136D84_S + "\n" + FUNC_84136D84_S.replace(
            "func_84136D84", "func_other"
        )
        folded, count = coalesce_lui.fold_source(
            source, {"func_84136D84"}, ADDRESS_MAP
        )
        self.assertEqual(count, 3)
        # The untouched sibling keeps its bare macro-form stores verbatim.
        self.assertIn("\tsw\t$0, D_84186164\n", folded)
        self.assertIn("\t.ent\tfunc_other 2\n", folded)


class FoldGapToleranceTest(unittest.TestCase):
    def test_directive_and_comment_gaps_do_not_break_the_run(self):
        # This is exactly FUNC_84136D84_S's shape: .loc/comment lines sit
        # between every pair of stores and must not prevent folding.
        folded, count = coalesce_lui.fold_source(
            FUNC_84136D84_S, {"func_84136D84"}, ADDRESS_MAP
        )
        self.assertEqual(count, 3)


class MarkerAndIntrospectionTest(unittest.TestCase):
    def test_find_coalesce_markers(self):
        source = (
            "#pragma COALESCE_AT_LUI(func_84136D84)\n"
            "extern void *D_84186160;\n"
            "void func_84136D84(void) { D_84186160 = 0; }\n"
        )
        self.assertEqual(coalesce_lui.find_coalesce_markers(source), {"func_84136D84"})

    def test_find_coalesce_markers_none_present(self):
        self.assertEqual(coalesce_lui.find_coalesce_markers("void f(void) {}\n"), set())

    def test_find_coalesce_markers_multiple(self):
        source = (
            "#pragma COALESCE_AT_LUI(func_a)\n"
            "void func_a(void) {}\n"
            "#pragma COALESCE_AT_LUI(func_b)\n"
            "void func_b(void) {}\n"
        )
        self.assertEqual(
            coalesce_lui.find_coalesce_markers(source), {"func_a", "func_b"}
        )

    def test_functions_defined(self):
        self.assertEqual(
            coalesce_lui.functions_defined(FUNC_84136D84_S), {"func_84136D84"}
        )


class AddressResolutionTest(unittest.TestCase):
    def test_parse_symbol_addrs(self, tmp_path=None):
        import tempfile

        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "symbol_addrs.txt"
            path.write_text(
                "entry_bss = 0x800A7E80; // size:0x400\n"
                "D_83503E80 = 0x83503E80;\n"
                "\n"
                "// a comment line\n"
                "gIdleThread = 0x800A8280; // size:0x1B0\n"
            )
            addrs = coalesce_lui.parse_symbol_addrs([path])
        self.assertEqual(addrs["entry_bss"], 0x800A7E80)
        self.assertEqual(addrs["D_83503E80"], 0x83503E80)
        self.assertEqual(addrs["gIdleThread"], 0x800A8280)
        self.assertEqual(len(addrs), 3)

    def test_parse_symbol_addrs_first_file_wins(self):
        import tempfile

        with tempfile.TemporaryDirectory() as tmp:
            first = Path(tmp) / "a.txt"
            second = Path(tmp) / "b.txt"
            first.write_text("D_X = 0x1000;\n")
            second.write_text("D_X = 0x2000;\n")
            addrs = coalesce_lui.parse_symbol_addrs([first, second])
        self.assertEqual(addrs["D_X"], 0x1000)

    def test_parse_linker_map_matches_only_bare_symbol_rows(self):
        import tempfile

        map_text = (
            ".text           0x80000400    0xa7a80 load address 0x00001000\n"
            " .text          0x00000000        0x0 build/asm/us/header.o\n"
            " .bss           0x00000000        0x0 build/asm/us/header.o\n"
            "                0x00000000       0x18 build/asm/us/header.o\n"
            "                0x84186160                D_84186160\n"
            "                0x84186164                D_84186164\n"
            "                0x84186168                D_84186168\n"
            "                0x8418616c                D_8418616C\n"
        )
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "pokestadiumgs-us.map"
            path.write_text(map_text)
            addrs = coalesce_lui.parse_linker_map(path)
        self.assertEqual(
            addrs,
            {
                "D_84186160": 0x84186160,
                "D_84186164": 0x84186164,
                "D_84186168": 0x84186168,
                "D_8418616C": 0x8418616C,
            },
        )

    def test_parse_linker_map_missing_file_returns_empty(self):
        self.assertEqual(
            coalesce_lui.parse_linker_map(Path("/nonexistent/path.map")), {}
        )

    def test_resolve_repo_addresses_prefers_symbol_addrs_over_map(self):
        import tempfile

        with tempfile.TemporaryDirectory() as tmp:
            repo_root = Path(tmp)
            linker_scripts = repo_root / "disasm" / "linker_scripts" / "us"
            linker_scripts.mkdir(parents=True)
            (linker_scripts / "symbol_addrs.txt").write_text("D_SHARED = 0x1000;\n")

            build = repo_root / "disasm" / "build"
            build.mkdir(parents=True)
            (build / "pokestadiumgs-us.map").write_text(
                "                0x00002000                D_SHARED\n"
                "                0x84186160                D_MAP_ONLY\n"
            )

            addrs = coalesce_lui.resolve_repo_addresses(repo_root)
        # symbol_addrs.txt is authoritative when both sources name a symbol.
        self.assertEqual(addrs["D_SHARED"], 0x1000)
        # The map fills in a dlabel that symbol_addrs.txt does not carry.
        self.assertEqual(addrs["D_MAP_ONLY"], 0x84186160)


class FloatMacroMemOpTest(unittest.TestCase):
    """``l.s``/``s.s`` (and ``l.d``/``s.d``) are IDO's `-S` spelling for a
    floating-point macro-form load/store -- the same shape ``sw``/``lw`` get
    for an integer global, just via the pseudo-mnemonic IDO always uses for
    FP memory ops. GNU as accepts both spellings identically (`l.s`/`s.s`
    assemble to plain `lwc1`/`swc1`; confirmed directly with
    mips-linux-gnu-as), so a run of these should fold exactly like the
    integer case. Reproduces the func_86600E00 shape: a computed `f32` value
    broadcast to two adjacent globals sharing one `%hi` page."""

    BLOCK = (
        "\t.ent\tfunc_float_broadcast 2\n"
        "func_float_broadcast:\n"
        "\tl.s\t$f0, D_86606750\n"
        "\ts.s\t$f0, D_86607444\n"
        "\ts.s\t$f0, D_86607440\n"
        "\tj\t$31\n"
        "\t.end\tfunc_float_broadcast\n"
    )
    ADDRESS_MAP = {
        "D_86606750": 0x86606750,
        "D_86607444": 0x86607444,
        "D_86607440": 0x86607440,
    }

    def test_float_store_run_folds(self):
        folded, count = coalesce_lui.fold_source(
            self.BLOCK, {"func_float_broadcast"}, self.ADDRESS_MAP
        )
        # All three ops (the load and both stores) resolve to the same %hi
        # page, so this is one run of three -- two folds saved, matching
        # fold_source's existing counting convention (len(ops) - 1).
        self.assertEqual(count, 2)
        self.assertIn("\tlui\t$at, %hi(D_86606750)\n", folded)
        self.assertIn("\tl.s\t$f0, %lo(D_86606750)($at)\n", folded)
        self.assertIn("D_86607444", folded)
        self.assertIn("D_86607440", folded)

    @unittest.skipUnless(shutil.which("mips-linux-gnu-as"), "no MIPS GNU as available")
    def test_folded_float_snippet_actually_assembles(self):
        folded, count = coalesce_lui.fold_source(
            self.BLOCK, {"func_float_broadcast"}, self.ADDRESS_MAP
        )
        self.assertEqual(count, 2)
        snippet = coalesce_lui.prepare_snippet_for_gnu_as(folded, {})
        with tempfile.TemporaryDirectory() as tmp:
            snippet_path = Path(tmp) / "func_float_broadcast.s"
            snippet_path.write_text(snippet)
            result = subprocess.run(
                ["mips-linux-gnu-as", "-march=vr4300", "-32", "-G0", "-EB",
                 "-o", str(Path(tmp) / "func_float_broadcast.o"), str(snippet_path)],
                capture_output=True, text=True, timeout=30,
            )
            self.assertEqual(result.returncode, 0, result.stderr)


class PrepareSnippetForGnuAsTest(unittest.TestCase):
    """``.alias``/``.noalias`` (register-only IDO optimizer hints) must be
    stripped like the rest of ``_GNU_AS_INCOMPATIBLE``, or GNU as rejects the
    snippet outright with "unknown pseudo-op" for any opted-in function whose
    body IDO decorates with them -- independent of whether a fold even
    applies. Reproduces the func_82507BFC/func_82507C48 shape (an `if (g ==
    a || g == b) { ...write several other globals... }` guard, which IDO
    brackets with alias hints around the final read-modify-write)."""

    BLOCK = (
        "\t.ent\tfunc_alias_shape 2\n"
        "func_alias_shape:\n"
        "\t.option\tO2\n"
        "\t.frame\t$sp, 0, $31\n"
        "\t.noalias\t$3,$sp\n"
        "\tlh\t$2, 0($3)\n"
        "\tsw\t$0, D_84186160\n"
        "\tsw\t$0, D_84186164\n"
        "\t.noalias\t$2,$3\n"
        "\t.noalias\t$2,$sp\n"
        "\tlhu\t$15, 0($2)\n"
        "\t.alias\t$2,$3\n"
        "\t.alias\t$2,$sp\n"
        "\t.alias\t$3,$sp\n"
        "\tj\t$31\n"
        "\t.end\tfunc_alias_shape\n"
    )

    def test_alias_and_noalias_lines_are_stripped(self):
        snippet = coalesce_lui.prepare_snippet_for_gnu_as(self.BLOCK, {})
        self.assertNotIn(".alias", snippet)
        self.assertNotIn(".noalias", snippet)
        # The real instructions around them survive untouched.
        self.assertIn("\tlh\t$2, 0($3)\n", snippet)
        self.assertIn("\tlhu\t$15, 0($2)\n", snippet)

    @unittest.skipUnless(shutil.which("mips-linux-gnu-as"), "no MIPS GNU as available")
    def test_alias_shape_snippet_actually_assembles(self):
        folded, count = coalesce_lui.fold_source(
            self.BLOCK, {"func_alias_shape"}, ADDRESS_MAP
        )
        self.assertEqual(count, 1)
        snippet = coalesce_lui.prepare_snippet_for_gnu_as(folded, {})
        with tempfile.TemporaryDirectory() as tmp:
            snippet_path = Path(tmp) / "func_alias_shape.s"
            snippet_path.write_text(snippet)
            result = subprocess.run(
                ["mips-linux-gnu-as", "-march=vr4300", "-32", "-G0", "-EB",
                 "-o", str(Path(tmp) / "func_alias_shape.o"), str(snippet_path)],
                capture_output=True, text=True, timeout=30,
            )
            self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == "__main__":
    unittest.main()
