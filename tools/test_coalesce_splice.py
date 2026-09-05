#!/usr/bin/env python3
"""Unit tests for the ELF32 reader/writer and the function-splice logic.

These build small synthetic MIPS ELF32 relocatable objects entirely in
Python (no compiler or assembler involved) so the splice arithmetic --
byte replacement, symbol-offset shifting, relocation translation -- is
covered without depending on a MIPS toolchain being installed. The
mechanism's actual compiler-facing behavior is exercised separately, by
hand, against the real IDO port and GNU as (see the PR description for that
verification trail); this file is about not regressing the object-surgery
math itself.
"""
from __future__ import annotations

import struct
import sys
import unittest
from pathlib import Path

_DISASM_TOOLS = Path(__file__).resolve().parent.parent / "disasm" / "tools"
sys.path.insert(0, str(_DISASM_TOOLS))
import elf32  # noqa: E402
import coalesce_splice  # noqa: E402

# Real compiled objects from this repo's own build, checked in as opaque
# binary fixtures -- not because build output normally belongs in the
# source tree, but because both bugs these cover (NOBITS/.bss sizing,
# section-relative jump-table relocations) were only reproducible against
# real IDO/GNU-as output; a from-scratch synthetic object risks missing
# whatever real-toolchain quirk actually triggers each one.
_TESTDATA = Path(__file__).resolve().parent / "testdata" / "coalesce_splice"
_MAIN_O = _TESTDATA / "main.o"  # has a real .bss (SHT_NOBITS) section
_CE80_O = _TESTDATA / "CE80.o"  # has a real jump table in .rodata (R_MIPS_32)
_95C0_O = _TESTDATA / "95C0.o"  # .strtab has "_Printf" as a suffix of "HAL_Printf"
_229E0_O = _TESTDATA / "229E0.o"  # .rel.text is not offset-sorted (D_800D1AD8)
_6DDA0_O = _TESTDATA / "6DDA0.o"  # smaller instance of the same (D_80128BF0/4/8)
_C2C0_O = _TESTDATA / "C2C0.o"  # func_8000B770 (size 0) sits inside func_8000B6C0

R_MIPS_32 = 2


R_MIPS_HI16 = 5
R_MIPS_LO16 = 6
SHT_PROGBITS = 1
SHT_SYMTAB = 2
SHT_STRTAB = 3
SHT_REL = 9
STT_FUNC = 2
STT_SECTION = 3
STB_GLOBAL = 1


def _add_section_symbol(obj: elf32.Elf32Object, section_name: str) -> int:
    """Append a local STT_SECTION symbol for ``section_name`` and return its index.

    ``make_object`` never creates one (its relocations always target named
    symbols), but production objects always have one per section, and
    ``coalesce_splice.py``'s section-relative handling looks it up by type,
    not by name -- an empty name is exactly what real objects use for this.
    """
    symbols = obj.symbols()
    shndx = obj.section_index(section_name)
    symbols.append(
        elf32.Symbol(name="", value=0, size=0, info=(STT_SECTION), other=0, shndx=shndx)
    )
    obj.set_symbols(symbols)
    return len(symbols) - 1


def _strtab(names: list[str]) -> tuple[bytes, dict[str, int]]:
    blob = bytearray(b"\x00")
    offsets = {"": 0}
    for name in names:
        offsets[name] = len(blob)
        blob.extend(name.encode("latin1") + b"\x00")
    return bytes(blob), offsets


def make_object(
    functions: list[tuple[str, bytes]],
    relocations: dict[str, list[tuple[int, str, int]]],
    text_padding: int = 0,
):
    """Build a minimal one-.text-section MIPS ELF32 object.

    ``functions``: ordered list of (name, text_bytes) placed back to back in
    .text. ``relocations``: function name -> list of (offset_within_function,
    symbol_name, reloc_type); the symbol may or may not be one of the
    functions (external data symbols get a synthetic UNDEF entry).
    ``text_padding``: zero bytes appended past the last function, belonging
    to no symbol -- what a real assembler leaves behind when it rounds .text
    up to the section's own alignment.
    """
    text = bytearray()
    func_layout = {}
    for name, body in functions:
        func_layout[name] = (len(text), len(body))
        text.extend(body)
    text.extend(b"\x00" * text_padding)

    extra_syms = set()
    for name, refs in relocations.items():
        for _, sym_name, _ in refs:
            if sym_name not in func_layout:
                extra_syms.add(sym_name)

    sym_names = [name for name, _ in functions] + sorted(extra_syms)
    strtab_data, name_off = _strtab(sym_names)

    sym_index = {"": 0}
    sym_entries = [struct.pack(">3I2BH", 0, 0, 0, 0, 0, 0)]  # null symbol
    text_shndx = 4  # filled in after we know section order (see below)
    for name, _ in functions:
        value, size = func_layout[name]
        sym_index[name] = len(sym_entries)
        sym_entries.append(
            struct.pack(
                ">3I2BH", name_off[name], value, size, (STB_GLOBAL << 4) | STT_FUNC, 0, text_shndx
            )
        )
    for name in sorted(extra_syms):
        sym_index[name] = len(sym_entries)
        sym_entries.append(
            struct.pack(">3I2BH", name_off[name], 0, 0, (STB_GLOBAL << 4) | STT_FUNC, 0, elf32.SHN_UNDEF)
        )
    symtab_data = b"".join(sym_entries)

    rel_entries = []
    for name, refs in relocations.items():
        base, _ = func_layout[name]
        for offset, sym_name, rel_type in refs:
            rel_entries.append(
                elf32.Relocation(offset=base + offset, sym_index=sym_index[sym_name], type=rel_type)
            )
    rel_entries.sort(key=lambda r: r.offset)
    rel_data = b"".join(struct.pack(">2I", r.offset, r.r_info()) for r in rel_entries)

    section_names = ["", ".symtab", ".strtab", ".shstrtab", ".text", ".rel.text"]
    shstr_data, shname_off = _strtab([n for n in section_names if n])

    sections = [
        elf32.Section("", 0, 0, 0, 0, 0, 0, 0, b""),
        elf32.Section(".symtab", SHT_SYMTAB, 0, 0, 2, 1, 4, 16, symtab_data),
        elf32.Section(".strtab", SHT_STRTAB, 0, 0, 0, 0, 1, 0, strtab_data),
        elf32.Section(".shstrtab", SHT_STRTAB, 0, 0, 0, 0, 1, 0, shstr_data),
        elf32.Section(".text", SHT_PROGBITS, 0x6, 0, 0, 0, 16, 0, bytes(text)),
        elf32.Section(".rel.text", SHT_REL, 0, 0, 1, 4, 4, 8, rel_data),
    ]
    obj = elf32.Elf32Object(e_type=1, e_machine=8, e_version=1, e_entry=0, e_flags=0x1000_0001, sections=sections)
    return obj


class RoundTripTest(unittest.TestCase):
    def test_build_then_parse_preserves_everything(self):
        obj = make_object(
            [("func_a", b"\x00" * 8), ("func_b", b"\x11" * 12)],
            {"func_a": [(0, "D_1000", R_MIPS_HI16), (4, "D_1000", R_MIPS_LO16)]},
        )
        data = elf32.build(obj)
        reparsed = elf32.parse(data)

        names = {s.name for s in reparsed.sections}
        self.assertEqual(names, {"", ".symtab", ".strtab", ".shstrtab", ".text", ".rel.text"})
        self.assertEqual(reparsed.section(".text").data, obj.section(".text").data)

        symbols = {s.name: s for s in reparsed.symbols()}
        self.assertEqual(symbols["func_a"].value, 0)
        self.assertEqual(symbols["func_a"].size, 8)
        self.assertEqual(symbols["func_b"].value, 8)
        self.assertEqual(symbols["func_b"].size, 12)

        relocs = reparsed.relocations(".rel.text")
        self.assertEqual(len(relocs), 2)
        self.assertEqual(relocs[0].offset, 0)
        self.assertEqual(relocs[0].type, R_MIPS_HI16)
        self.assertEqual(relocs[1].offset, 4)
        self.assertEqual(relocs[1].type, R_MIPS_LO16)

    def test_rebuild_keeps_section_file_offsets(self):
        """Sections must not slide when an earlier one shrinks.

        IRIX ``.mdebug`` addresses its own sub-tables by *absolute file
        offset* (cbFdOffset/cbSymOffset/cbSsOffset in its header), and
        asm-processor reads them back out of the object after this module
        has rewritten it (``--convert-statics``, which every C file in this
        repo is built with). Repacking sections tightly after a fold shrinks
        .text would leave those pointers aimed at the wrong bytes -- either
        mis-naming every converted static or tripping asm_processor's own
        ``symbol_name_offset_end != -1`` assert mid-build.
        """
        original = _MAIN_O.read_bytes()
        obj = elf32.parse(original)
        text = obj.section(".text").data
        obj.set_section_data(".text", text[:-16])

        rebuilt = elf32.parse(elf32.build(obj))
        before = {s.name: s.file_offset for s in elf32.parse(original).sections}
        after = {s.name: s.file_offset for s in rebuilt.sections}
        self.assertEqual(before, after)
        self.assertEqual(len(rebuilt.section(".text").data), len(text) - 16)

    def test_readelf_accepts_the_output(self):
        import shutil
        import subprocess
        import tempfile

        readelf = shutil.which("mips-linux-gnu-readelf") or shutil.which("readelf")
        if readelf is None:
            self.skipTest("no readelf available in this environment")

        obj = make_object([("func_a", b"\x00" * 8)], {})
        data = elf32.build(obj)
        with tempfile.NamedTemporaryFile(suffix=".o") as f:
            f.write(data)
            f.flush()
            result = subprocess.run(
                [readelf, "-a", f.name], capture_output=True, text=True, timeout=30
            )
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertNotIn("Warning", result.stdout + result.stderr)
        self.assertNotIn("Error", result.stdout + result.stderr)
        self.assertIn("func_a", result.stdout)


class SpliceEqualSizeTest(unittest.TestCase):
    def test_replaces_bytes_and_relocations_in_place(self):
        outer = make_object(
            [("func_a", b"\xAA" * 8), ("func_b", b"\xBB" * 4)],
            {
                "func_a": [(0, "D_1000", R_MIPS_HI16), (4, "D_1000", R_MIPS_LO16)],
                # func_b already references D_2000 elsewhere in the same
                # file, exactly like func_84136D84's neighbors already
                # reference D_84186164/68/6C in the real file -- this is
                # what makes it safe for the fold to drop D_2000's own
                # relocation and keep only a literal immediate for it.
                "func_b": [(0, "D_2000", R_MIPS_HI16)],
            },
        )
        inner = make_object(
            [("func_a", b"\xCC" * 8)],
            {"func_a": [(0, "D_1000", R_MIPS_HI16), (4, "D_2000", R_MIPS_LO16)]},
        )
        result = elf32.parse(
            coalesce_splice.splice_function(elf32.build(outer), elf32.build(inner), "func_a")
        )

        self.assertEqual(result.section(".text").data, b"\xCC" * 8 + b"\xBB" * 4)
        symbols = {s.name: s for s in result.symbols()}
        self.assertEqual(symbols["func_a"].value, 0)
        self.assertEqual(symbols["func_a"].size, 8)
        # func_b's own offset is untouched since nothing shrank.
        self.assertEqual(symbols["func_b"].value, 8)

        relocs = {(r.offset, r.type) for r in result.relocations(".rel.text")}
        self.assertIn((0, R_MIPS_HI16), relocs)
        self.assertIn((4, R_MIPS_LO16), relocs)
        # The new D_2000 relocation resolved to the outer object's own
        # existing symbol table entry for it, not a stray/duplicate one.
        by_offset = {r.offset: r for r in result.relocations(".rel.text")}
        target_name = result.symbols()[by_offset[4].sym_index].name
        self.assertEqual(target_name, "D_2000")


class SpliceShrinkTest(unittest.TestCase):
    def test_shrinking_shifts_later_symbols_and_relocations(self):
        # func_a: 6 words unfolded -> folds to 4 words (mirrors the real
        # func_84136D84 shape at a smaller scale). func_b sits right after
        # it and must end up 8 bytes earlier once func_a shrinks.
        outer = make_object(
            [("func_a", b"\xAA" * 24), ("func_b", b"\xBB" * 4)],
            {
                "func_a": [
                    (0, "D_1000", R_MIPS_HI16),
                    (4, "D_1000", R_MIPS_LO16),
                    (8, "D_2000", R_MIPS_HI16),
                    (12, "D_2000", R_MIPS_LO16),
                    (16, "D_3000", R_MIPS_HI16),
                    (20, "D_3000", R_MIPS_LO16),
                ],
                "func_b": [(0, "D_4000", R_MIPS_HI16)],
            },
        )
        inner = make_object(
            [("func_a", b"\xCC" * 16)],
            {"func_a": [(0, "D_1000", R_MIPS_HI16), (4, "D_1000", R_MIPS_LO16)]},
        )
        result = elf32.parse(
            coalesce_splice.splice_function(elf32.build(outer), elf32.build(inner), "func_a")
        )

        self.assertEqual(result.section(".text").data, b"\xCC" * 16 + b"\xBB" * 4)
        symbols = {s.name: s for s in result.symbols()}
        self.assertEqual(symbols["func_a"].size, 16)
        self.assertEqual(symbols["func_b"].value, 16)  # was 24, shifted by -8

        relocs = sorted((r.offset, r.type) for r in result.relocations(".rel.text"))
        # Only func_a's first pair survives (the rest were literal
        # immediates with no relocation at all in a real fold); func_b's
        # own relocation shifts down by the same 8 bytes as its symbol.
        self.assertEqual(relocs, [(0, R_MIPS_HI16), (4, R_MIPS_LO16), (16, R_MIPS_HI16)])
        by_offset = {r.offset: r for r in result.relocations(".rel.text")}
        self.assertEqual(result.symbols()[by_offset[16].sym_index].name, "D_4000")

    def test_shrink_across_an_alignment_boundary_retrims_trailing_padding(self):
        """The bug that kept func_84136D84 from landing, at small scale.

        IDO rounds .text up to the section's own alignment, so its length is
        ``align_up(content_end, 16)`` -- here 28 bytes of functions plus 4
        bytes of padding. Folding func_a from 24 to 12 bytes moves the
        content end back across the 16-byte boundary, so the section has to
        end up 16 bytes long, not ``32 - 12 = 20``: carrying the old padding
        along unchanged leaves a section 4 bytes too long, attributable to no
        symbol at all, which silently shifts every later object in the link
        and fails the whole-ROM compare.
        """
        outer = make_object(
            [("func_a", b"\xAA" * 24), ("func_b", b"\xBB" * 4)],
            {"func_a": [(0, "D_1000", R_MIPS_HI16), (4, "D_1000", R_MIPS_LO16)]},
            text_padding=4,
        )
        self.assertEqual(len(outer.section(".text").data), 32)
        inner = make_object([("func_a", b"\xCC" * 12)], {})

        result = elf32.parse(
            coalesce_splice.splice_function(elf32.build(outer), elf32.build(inner), "func_a")
        )

        text = result.section(".text").data
        self.assertEqual(len(text), 16)
        self.assertEqual(text, b"\xCC" * 12 + b"\xBB" * 4)
        symbols = {s.name: s for s in result.symbols()}
        self.assertEqual(symbols["func_b"].value, 12)

    def test_shrink_within_an_alignment_boundary_keeps_the_section_length(self):
        """Same layout, a fold too small to cross the boundary.

        28 bytes of content plus 4 of padding, func_a 24 -> 20: the content
        end moves to 24, which still rounds up to 32, so the section keeps
        its length and simply pads more.
        """
        outer = make_object(
            [("func_a", b"\xAA" * 24), ("func_b", b"\xBB" * 4)],
            {"func_a": [(0, "D_1000", R_MIPS_HI16), (4, "D_1000", R_MIPS_LO16)]},
            text_padding=4,
        )
        inner = make_object([("func_a", b"\xCC" * 20)], {})

        result = elf32.parse(
            coalesce_splice.splice_function(elf32.build(outer), elf32.build(inner), "func_a")
        )

        text = result.section(".text").data
        self.assertEqual(len(text), 32)
        self.assertEqual(text, b"\xCC" * 20 + b"\xBB" * 4 + b"\x00" * 8)

    def test_non_zero_trailing_bytes_are_never_retrimmed_away(self):
        """Only zero padding is padding; anything else is a hard stop."""
        outer = make_object(
            [("func_a", b"\xAA" * 24), ("func_b", b"\xBB" * 4)],
            {"func_a": [(0, "D_1000", R_MIPS_HI16), (4, "D_1000", R_MIPS_LO16)]},
            text_padding=4,
        )
        patched = bytearray(outer.section(".text").data)
        patched[-1] = 0x99
        outer.set_section_data(".text", bytes(patched))
        inner = make_object([("func_a", b"\xCC" * 12)], {})

        with self.assertRaises(coalesce_splice.SpliceError):
            coalesce_splice.splice_function(elf32.build(outer), elf32.build(inner), "func_a")

    def test_unpadded_sections_are_left_exactly_as_they_were(self):
        """A section whose length is not ``align_up(content, align)``.

        Nothing this project's toolchain emits, but the retrim rule must not
        invent padding for an object it was not written for -- it falls back
        to the plain head+folded+tail length instead.
        """
        outer = make_object(
            [("func_a", b"\xAA" * 24), ("func_b", b"\xBB" * 4)],
            {"func_a": [(0, "D_1000", R_MIPS_HI16), (4, "D_1000", R_MIPS_LO16)]},
        )
        self.assertEqual(len(outer.section(".text").data), 28)  # not a multiple of 16
        inner = make_object([("func_a", b"\xCC" * 12)], {})

        result = elf32.parse(
            coalesce_splice.splice_function(elf32.build(outer), elf32.build(inner), "func_a")
        )

        self.assertEqual(result.section(".text").data, b"\xCC" * 12 + b"\xBB" * 4)


class SpliceErrorTest(unittest.TestCase):
    def test_missing_function_in_outer_is_an_error(self):
        outer = make_object([("func_a", b"\x00" * 8)], {})
        inner = make_object([("func_other", b"\x00" * 8)], {})
        with self.assertRaises(coalesce_splice.SpliceError):
            coalesce_splice.splice_function(elf32.build(outer), elf32.build(inner), "func_other")

    def test_missing_function_in_inner_is_an_error(self):
        outer = make_object([("func_a", b"\x00" * 8)], {})
        inner = make_object([("func_other", b"\x00" * 8)], {})
        with self.assertRaises(coalesce_splice.SpliceError):
            coalesce_splice.splice_function(elf32.build(outer), elf32.build(inner), "func_a")

    def test_unresolvable_relocation_symbol_is_an_error(self):
        # The inner (folded) object references a symbol the outer object
        # (compiled from the same file) never itself references -- refuse
        # to guess rather than fabricate a new symbol table entry.
        outer = make_object([("func_a", b"\x00" * 8)], {})
        inner = make_object(
            [("func_a", b"\x00" * 8)],
            {"func_a": [(0, "D_NEVER_SEEN", R_MIPS_HI16)]},
        )
        with self.assertRaises(coalesce_splice.SpliceError):
            coalesce_splice.splice_function(elf32.build(outer), elf32.build(inner), "func_a")

    def test_zero_size_inner_function_is_an_error(self):
        outer = make_object([("func_a", b"\x00" * 8)], {})
        inner = make_object([("func_a", b"")], {})
        with self.assertRaises(coalesce_splice.SpliceError):
            coalesce_splice.splice_function(elf32.build(outer), elf32.build(inner), "func_a")

    def test_inner_section_relative_self_reference_is_refused(self):
        # Hardening test: name-based translation of a folded relocation is
        # only sound for a real, uniquely-named symbol. Every SHT_NULL and
        # STT_SECTION symbol conventionally shares the empty name (real
        # objects in this repo have several), so a naive name->index map
        # would silently resolve an inner section-relative self-reference
        # (e.g. a jump table entirely local to the folded function) to
        # whichever of the outer object's several same-named section
        # symbols happens to be enumerated last -- not an error, but a
        # wrong symbol reference. This must be refused instead.
        outer = make_object([("func_a", b"\xAA" * 8), ("func_b", b"\xBB" * 8)], {})
        # Give outer more than one empty-named symbol, matching real
        # objects, so a naive lookup would "succeed" (silently, on the
        # wrong one) rather than simply finding nothing.
        _add_section_symbol(outer, ".text")
        _add_section_symbol(outer, ".text")

        inner = make_object([("func_a", b"\xCC" * 8)], {})
        inner_text_index = inner.section_index(".text")
        inner_symbols = inner.symbols()
        inner_symbols.append(
            elf32.Symbol(name="", value=0, size=0, info=STT_SECTION, other=0, shndx=inner_text_index)
        )
        inner.set_symbols(inner_symbols)
        inner.set_relocations(
            ".rel.text",
            [elf32.Relocation(offset=0, sym_index=len(inner_symbols) - 1, type=R_MIPS_HI16)],
        )

        with self.assertRaises(coalesce_splice.SpliceError) as ctx:
            coalesce_splice.splice_function(elf32.build(outer), elf32.build(inner), "func_a")
        self.assertIn("section-relative", str(ctx.exception))


@unittest.skipUnless(_MAIN_O.is_file(), f"missing test fixture {_MAIN_O}")
class RealObjectBssRoundTripTest(unittest.TestCase):
    """Regression test for a real bug: build() used to zero every .bss.

    ``main.o`` (this repo's own compiled ``disasm/src/main.c``) has a real
    0x2b80-byte ``.bss`` (SHT_NOBITS) section. A naive parse+build round
    trip used to silently truncate it to 0, which -- for any file this
    mechanism is used on that has bss anywhere -- would corrupt that file's
    bss layout in the final linked ROM without any error at all.
    """

    def test_bss_size_and_layout_survive_a_round_trip(self):
        original = _MAIN_O.read_bytes()
        parsed = elf32.parse(original)
        bss = parsed.section(".bss")
        self.assertIsNotNone(bss)
        self.assertGreater(bss.nobits_size, 0)
        self.assertEqual(bss.data, b"")  # NOBITS never carries file bytes

        rebuilt = elf32.build(parsed)
        reparsed = elf32.parse(rebuilt)
        rebuilt_bss = reparsed.section(".bss")
        self.assertEqual(rebuilt_bss.nobits_size, bss.nobits_size)
        self.assertEqual(rebuilt_bss.data, b"")

        # Every other section's size must also be untouched by the round trip.
        for sec in parsed.sections[1:]:
            match = reparsed.section(sec.name)
            self.assertIsNotNone(match, sec.name)
            if sec.type == elf32.SHT_NOBITS:
                self.assertEqual(match.nobits_size, sec.nobits_size, sec.name)
            else:
                self.assertEqual(match.data, sec.data, sec.name)

    def test_splicing_an_unrelated_function_preserves_bss(self):
        # The splice path is the one actually used in production; confirm
        # it doesn't lose .bss either, not just a bare parse+build.
        original = _MAIN_O.read_bytes()
        parsed = elf32.parse(original)
        bss_size = parsed.section(".bss").nobits_size
        target = next(s for s in parsed.symbols() if s.info & 0xF == 2 and s.size > 0)

        inner = make_object([(target.name, b"\x00" * target.size)], {})
        result = elf32.parse(
            coalesce_splice.splice_function(original, elf32.build(inner), target.name)
        )
        self.assertEqual(result.section(".bss").nobits_size, bss_size)


@unittest.skipUnless(_CE80_O.is_file(), f"missing test fixture {_CE80_O}")
class RealObjectJumpTableTest(unittest.TestCase):
    """Regression test for a real bug: jump-table targets weren't shifted.

    ``CE80.o`` (this repo's own compiled ``disasm/src/CE80.c``) has a real
    8-entry jump table in ``.rodata`` (``R_MIPS_32`` relocations against the
    ``.text`` section symbol, per a real ``switch`` statement in
    ``func_8000E750``) whose case targets all fall inside that same
    function. ``func_8000E1E4`` sits immediately before it in ``.text`` --
    shrinking func_8000E1E4 must shift every one of those jump-table words
    (and func_8000E750's own start address) by exactly the same delta.
    """

    def test_shrinking_an_earlier_function_shifts_the_jump_table(self):
        original = _CE80_O.read_bytes()
        outer = elf32.parse(original)
        symbols = {s.name: s for s in outer.symbols()}
        shrink_target = symbols["func_8000E1E4"]
        table_owner = symbols["func_8000E750"]
        # Fixture assumption this test depends on: the jump table's owner
        # begins exactly where the shrink target ends, so every table entry
        # is provably inside table_owner and must shift by the same delta.
        self.assertEqual(shrink_target.value + shrink_target.size, table_owner.value)

        rodata = outer.section(".rodata")
        original_targets = [
            struct.unpack_from(">I", rodata.data, off)[0] for off in range(0, 0x20, 4)
        ]
        for target in original_targets:
            self.assertGreaterEqual(target, table_owner.value)
            self.assertLess(target, table_owner.value + table_owner.size)

        delta = -16
        new_size = shrink_target.size + delta
        inner = make_object([(shrink_target.name, b"\x00" * new_size)], {})
        result = elf32.parse(
            coalesce_splice.splice_function(original, elf32.build(inner), shrink_target.name)
        )

        result_symbols = {s.name: s for s in result.symbols()}
        self.assertEqual(result_symbols[shrink_target.name].size, new_size)
        self.assertEqual(result_symbols["func_8000E750"].value, table_owner.value + delta)

        result_rodata = result.section(".rodata")
        new_targets = [
            struct.unpack_from(">I", result_rodata.data, off)[0] for off in range(0, 0x20, 4)
        ]
        self.assertEqual(new_targets, [t + delta for t in original_targets])

        # And the relocations themselves are still R_MIPS_32 against the
        # .text section symbol -- the fix rewrites the encoded value in
        # place, it doesn't touch the relocation entries' own bookkeeping.
        rel_rodata = result.relocations(".rel.rodata")
        text_index = result.section_index(".text")
        # IDO's own object apparently emits more than one local STT_SECTION
        # symbol for .text (observed: two, at different indices) -- any of
        # them is a legitimate "the .text section itself" reference, so
        # accept membership in that set rather than assuming a single index.
        text_sym_indices = {
            i for i, s in enumerate(result.symbols())
            if (s.info & 0xF) == 3 and s.shndx == text_index
        }
        self.assertTrue(text_sym_indices)
        thirty_two_bit_relocs = [r for r in rel_rodata if r.offset < 0x20]
        self.assertEqual(len(thirty_two_bit_relocs), 8)
        for rel in thirty_two_bit_relocs:
            self.assertEqual(rel.type, R_MIPS_32)
            self.assertIn(rel.sym_index, text_sym_indices)

    def test_shrinking_the_jump_table_owner_itself_is_refused(self):
        # Regression test for a real (merge-blocking) bug: shrinking
        # func_8000E750 -- the function that *owns* the jump table, not
        # just an earlier neighbor -- moved every one of its own case
        # targets into [lo, hi), the range being replaced. The original fix
        # only handled targets >= hi (shift) and silently left [lo, hi)
        # targets untouched: no error, and all 8 .rodata words stayed at
        # their stale pre-fold values. This must now be a hard refusal,
        # since the fold does not track how in-function offsets moved.
        original = _CE80_O.read_bytes()
        outer = elf32.parse(original)
        table_owner = {s.name: s for s in outer.symbols()}["func_8000E750"]

        new_size = table_owner.size - 16
        inner = make_object([(table_owner.name, b"\x00" * new_size)], {})

        with self.assertRaises(coalesce_splice.SpliceError) as ctx:
            coalesce_splice.splice_function(original, elf32.build(inner), table_owner.name)
        message = str(ctx.exception)
        self.assertIn("func_8000E750", message)
        self.assertIn("inside the function's own", message)


class HiLoSupersededPairingTest(unittest.TestCase):
    """Hardening test for the HI16/LO16 pairing logic's own bookkeeping.

    Not reachable through any real object in this repo today (checked
    against all 82 objects this repo's own build currently produces), but a
    compiler emitting two independent %hi computations for the same base
    symbol -- e.g. two array elements landing on different pages -- before
    either is consumed by its %lo is a real, structurally valid shape.
    ``active_hi`` used to be overwritten by a second HI16 for the same
    symbol before the first was ever paired, silently discarding the first
    one's correction. It must now refuse rather than guess.
    """

    def test_second_hi16_before_first_is_consumed_is_refused(self):
        # func_a: 8 bytes, at offset 0 -- the fold target, shrinking by 8.
        # func_b: sits after it, contains two HI16 relocations for the same
        # section-relative "symbol" (D_TARGET, whose value happens to fall
        # after the fold point so a correction is actually needed) with no
        # LO16 between them.
        outer = make_object(
            [("func_a", b"\xAA" * 8), ("func_b", b"\xBB" * 8)],
            {
                "func_b": [
                    (0, "D_TARGET", R_MIPS_HI16),
                    (4, "D_TARGET", R_MIPS_HI16),  # supersedes the first, unconsumed
                ],
            },
        )
        # make_object's D_TARGET is a real (UNDEF) named symbol, not a
        # section symbol, and make_object never creates one at all --
        # fabricate the .text-section-relative shape by hand: add a real
        # STT_SECTION symbol and point the relocations at it instead.
        text_sym_index = _add_section_symbol(outer, ".text")
        rel_text = outer.relocations(".rel.text")
        retargeted = [
            elf32.Relocation(offset=r.offset, sym_index=text_sym_index, type=r.type)
            for r in rel_text
        ]
        outer.set_relocations(".rel.text", retargeted)
        # Bake a real %hi field (0x8419, i.e. an addend of 0x84190000+,
        # past the fold point) into both HI16 instruction words.
        text_data = bytearray(outer.section(".text").data)
        struct.pack_into(">I", text_data, 8, 0x3C010000 | 0x8419)  # func_b+0: lui $at,0x8419
        struct.pack_into(">I", text_data, 12, 0x3C010000 | 0x8419)  # func_b+4: lui $at,0x8419 (dup)
        outer.set_section_data(".text", bytes(text_data))

        inner = make_object([("func_a", b"\xCC" * 4)], {})  # shrinks func_a by 4 bytes
        with self.assertRaises(coalesce_splice.SpliceError) as ctx:
            coalesce_splice.splice_function(elf32.build(outer), elf32.build(inner), "func_a")
        message = str(ctx.exception)
        self.assertIn("second R_MIPS_HI16", message)


@unittest.skipUnless(_95C0_O.is_file(), f"missing test fixture {_95C0_O}")
class RealObjectStrtabSubstringTest(unittest.TestCase):
    """Regression test for a reachable crash: elf32.set_symbols only ever
    checked the *first* substring hit for a symbol's name in .strtab, and
    bailed with a plain (uncaught, by coalesce_cc.py) ValueError if that
    hit wasn't a real entry boundary -- rather than continuing to search
    for the symbol's own actual occurrence elsewhere in the table.

    ``95C0.o`` (this repo's own compiled object) has both ``HAL_Printf\\0``
    and ``_Printf\\0`` in its string table: looking up ``_Printf`` finds it
    first as a non-boundary suffix of ``HAL_Printf``, which is exactly the
    shape that used to raise.
    """

    def test_strtab_lookup_skips_past_a_non_boundary_substring_match(self):
        original = _95C0_O.read_bytes()
        obj = elf32.parse(original)
        symbols = obj.symbols()
        printf_index = next(i for i, s in enumerate(symbols) if s.name == "_Printf")

        # This is exactly what set_symbols has to do internally: find
        # "_Printf"'s own offset in .strtab. Confirm the hazard is real for
        # this fixture (a naive first-hit find() lands mid-"HAL_Printf",
        # not NUL-preceded) before confirming the fix walks past it.
        strtab = obj.section(".strtab").data
        naive_hit = strtab.find(b"_Printf\x00")
        self.assertGreater(naive_hit, 0)
        self.assertNotEqual(strtab[naive_hit - 1], 0)  # the false-hit shape

        # set_symbols is exactly what splice_function calls; a bare
        # round-trip (no actual value changes) already exercises the
        # lookup for every symbol, including this one.
        obj.set_symbols(symbols)
        rebuilt = elf32.parse(elf32.build(obj))
        self.assertEqual(rebuilt.symbols()[printf_index].name, "_Printf")

    def test_splicing_an_unrelated_function_does_not_crash(self):
        # End-to-end: this is what actually broke coalesce_cc.py -- any
        # opt-in in a file sharing this .strtab shape couldn't build at
        # all, regardless of what function was being folded.
        original = _95C0_O.read_bytes()
        outer = elf32.parse(original)
        text_index = outer.section_index(".text")
        target = next(
            s for s in outer.symbols() if (s.info & 0xF) == STT_FUNC and s.shndx == text_index
        )
        inner = make_object([(target.name, b"\x00" * target.size)], {})
        result = coalesce_splice.splice_function(original, elf32.build(inner), target.name)
        rebuilt = elf32.parse(result)
        names = {s.name for s in rebuilt.symbols()}
        self.assertIn("_Printf", names)
        self.assertIn("HAL_Printf", names)


class _RelTextOrderPreservationMixin:
    """Shared body for the two real fixtures exercising the same bug:
    resorting .rel.text by r_offset can change which R_MIPS_LO16 a given
    R_MIPS_HI16 pairs with under GNU ld's own "next same-symbol entry in
    *table order*" rule, for relocations this splice never even touches.
    """

    fixture: Path
    shrink_target_name: str

    def test_untouched_relocations_keep_their_original_relative_table_order(self):
        original = self.fixture.read_bytes()
        outer = elf32.parse(original)
        symbols = {s.name: s for s in outer.symbols()}
        shrink_target = symbols[self.shrink_target_name]

        original_relocs = outer.relocations(".rel.text")
        # Every relocation entirely outside the fold range, identified by
        # (symbol, type) and kept in original table order -- this is
        # exactly the sequence GNU ld's own HI16/LO16 pairing depends on.
        untouched_order = [
            (r.sym_index, r.type)
            for r in original_relocs
            if not (shrink_target.value <= r.offset < shrink_target.value + shrink_target.size)
        ]
        self.assertGreater(len(untouched_order), 0)  # fixture sanity check

        delta = -8
        new_size = shrink_target.size + delta
        inner = make_object([(shrink_target.name, b"\x00" * new_size)], {})
        result = elf32.parse(
            coalesce_splice.splice_function(original, elf32.build(inner), shrink_target.name)
        )
        new_order = [(r.sym_index, r.type) for r in result.relocations(".rel.text")]

        # The untouched sequence must appear in the new table as a
        # contiguous subsequence in the *same relative order* -- not
        # resorted by (post-shift) offset. assertEqual on the full
        # extracted subsequence (rather than just "is a subsequence")
        # catches both reordering and any accidental drop/duplication.
        new_subsequence = [pair for pair in new_order if pair in set(untouched_order)]
        self.assertEqual(new_subsequence, untouched_order)

    def test_hi16_lo16_pairs_decode_to_the_same_addend_as_before(self):
        # The concrete, reviewer-verified failure mode: resorting changes
        # the *decoded* addend for real HI16/LO16 pairs in these two
        # fixtures. Confirm splice_function's actual output decodes
        # identically to the original for every HI16/LO16 pair that isn't
        # part of the folded function itself.
        original = self.fixture.read_bytes()
        outer = elf32.parse(original)
        symbols = {s.name: s for s in outer.symbols()}
        shrink_target = symbols[self.shrink_target_name]
        text = outer.section(".text").data

        def decode_pairs(relocs, text_bytes):
            pairs = {}
            pending = None
            for r in relocs:
                word = struct.unpack_from(">I", text_bytes, r.offset)[0]
                if r.type == R_MIPS_HI16:
                    pending = (r.sym_index, word & 0xFFFF)
                elif r.type == R_MIPS_LO16 and pending is not None:
                    sym_index, hi_field = pending
                    if sym_index == r.sym_index:
                        lo_field = word & 0xFFFF
                        signed_lo = lo_field - 0x10000 if lo_field & 0x8000 else lo_field
                        pairs.setdefault(sym_index, []).append((hi_field << 16) + signed_lo)
                    pending = None
            return pairs

        # Exclude the fold target's own relocations: this test's synthetic
        # inner has none of its own (a real fold would, translated from
        # its own real compile), so any pair entirely inside the target's
        # own range would legitimately vanish -- that's not what this test
        # is checking. This mirrors the same [lo, hi) filter the other
        # test in this mixin uses.
        lo, hi = shrink_target.value, shrink_target.value + shrink_target.size
        outer_relocs = [r for r in outer.relocations(".rel.text") if not (lo <= r.offset < hi)]
        original_pairs = decode_pairs(outer_relocs, text)

        delta = -8
        new_size = shrink_target.size + delta
        inner = make_object([(shrink_target.name, b"\x00" * new_size)], {})
        result = elf32.parse(
            coalesce_splice.splice_function(original, elf32.build(inner), shrink_target.name)
        )
        new_lo, new_hi = lo, lo + new_size
        result_relocs = [
            r for r in result.relocations(".rel.text") if not (new_lo <= r.offset < new_hi)
        ]
        new_pairs = decode_pairs(result_relocs, result.section(".text").data)

        # Every symbol whose pairs we decoded before must decode to
        # exactly the same addends after (the fold target's own size
        # change never touches a *named*-symbol relocation's addend --
        # only section-relative ones need the delta applied).
        for sym_index, addends in original_pairs.items():
            self.assertEqual(
                new_pairs.get(sym_index), addends,
                f"symbol index {sym_index} ({outer.symbols()[sym_index].name}): "
                f"addends changed from {addends} to {new_pairs.get(sym_index)}",
            )


@unittest.skipUnless(_229E0_O.is_file(), f"missing test fixture {_229E0_O}")
class RealObject229E0RelTextOrderTest(_RelTextOrderPreservationMixin, unittest.TestCase):
    fixture = _229E0_O
    shrink_target_name = "func_80021DE0"  # first function; ends well before
    # D_800D1AD8's relocations start, so this exercises pure offset-shift +
    # order preservation for a real, previously-misordered HI16/LO16 group.


@unittest.skipUnless(_6DDA0_O.is_file(), f"missing test fixture {_6DDA0_O}")
class RealObject6DDA0RelTextOrderTest(_RelTextOrderPreservationMixin, unittest.TestCase):
    fixture = _6DDA0_O
    shrink_target_name = "func_8006D268"  # last function; every D_80128BF0/4/8
    # relocation is before it, so shrinking it leaves them all untouched and
    # exercises the "before the fold point, must not move at all" case.


@unittest.skipUnless(_C2C0_O.is_file(), f"missing test fixture {_C2C0_O}")
class RealObjectInFunctionNamedSymbolTest(unittest.TestCase):
    """Defense-in-depth test (optional hardening, not a reachable bug through
    the real coalesce_cc.py path today): a named .text symbol placed
    strictly *inside* the range being replaced -- not the fold target's own
    symbol, not the .text section symbol -- used to be neither shifted nor
    refused.

    ``C2C0.o`` (this repo's own compiled object) has exactly this shape:
    ``func_8000B770`` (size 0) sits at offset 176, inside
    ``func_8000B6C0``'s own [0, 192) range. Only reachable via a stray
    ``GLOBAL_ASM``-authored placeholder symbol in practice (IDO's own
    compiles never produce it), but cheap to refuse outright.
    """

    def test_shrinking_the_outer_function_is_refused(self):
        original = _C2C0_O.read_bytes()
        outer = elf32.parse(original)
        symbols = {s.name: s for s in outer.symbols()}
        outer_func = symbols["func_8000B6C0"]
        inner_symbol = symbols["func_8000B770"]
        # Fixture assumption this test depends on.
        self.assertTrue(
            outer_func.value <= inner_symbol.value < outer_func.value + outer_func.size
        )

        new_size = outer_func.size - 8
        inner = make_object([(outer_func.name, b"\x00" * new_size)], {})
        with self.assertRaises(coalesce_splice.SpliceError) as ctx:
            coalesce_splice.splice_function(original, elf32.build(inner), outer_func.name)
        self.assertIn("func_8000B770", str(ctx.exception))


if __name__ == "__main__":
    unittest.main()
