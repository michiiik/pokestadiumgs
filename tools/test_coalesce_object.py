#!/usr/bin/env python3
"""Tests for the object-level ``lui $at`` fold (``disasm/tools/coalesce_object.py``).

The fixture is the real shape this mechanism exists for: ``func_82300A78``
(``fragments/19/fragment19_121100.c``) as IDO's own ``cc -c`` actually emits
it -- the branch already scheduled, the first macro store's ``lui $at``
already sitting in the branch's delay slot -- and the ground truth this fold
has to reproduce, taken from
``disasm/asm/us/nonmatchings/.../func_82300A78.s``.

That scheduling is the whole point: the previous text-level round trip could
not preserve it, so these tests assert on machine words rather than assembly
text.
"""
from __future__ import annotations

import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "disasm" / "tools"))

import coalesce_object  # noqa: E402
import coalesce_splice  # noqa: E402
import elf32  # noqa: E402

R_MIPS_HI16 = 5
R_MIPS_LO16 = 6

ADDRESSES = {
    "D_82305EB4": 0x82305EB4,
    "D_82305EC2": 0x82305EC2,
    "D_82305EC4": 0x82305EC4,
    "D_82305EC6": 0x82305EC6,
    "D_82305EC8": 0x82305EC8,
}
NARROWED = frozenset({"D_82305EC4", "D_82305EC6", "D_82305EC2"})

# IDO `cc -c` output for the candidate body, verbatim (objdump -dr). Note
# instruction 5: the `lui $at` for the first store is in the `bne`'s delay
# slot, which is exactly what re-assembling IDO's own `-S` text loses.
UNFOLDED_WORDS = [
    0x3C0E0000,  # 0  lui   $t6, %hi(D_82305EB4)
    0x85CE0000,  # 1  lh    $t6, %lo(D_82305EB4)($t6)
    0x24010002,  # 2  li    $at, 2
    0x240F0003,  # 3  li    $t7, 3
    0x15C1000A,  # 4  bne   $t6, $at, +10  -> instruction 15
    0x3C010000,  # 5  lui   $at, %hi(D_82305EB4)   [delay slot]
    0xA42F0000,  # 6  sh    $t7, %lo(D_82305EB4)($at)
    0x3C010000,  # 7  lui   $at, %hi(D_82305EC4)
    0xA4200000,  # 8  sh    $zero, %lo(D_82305EC4)($at)
    0x3C010000,  # 9  lui   $at, %hi(D_82305EC6)
    0xA4200000,  # 10 sh    $zero, %lo(D_82305EC6)($at)
    0x3C010000,  # 11 lui   $at, %hi(D_82305EC2)
    0xA4200000,  # 12 sh    $zero, %lo(D_82305EC2)($at)
    0x3C010000,  # 13 lui   $at, %hi(D_82305EC8)
    0xA4200000,  # 14 sh    $zero, %lo(D_82305EC8)($at)
    0x03E00008,  # 15 jr    $ra
    0x00000000,  # 16 nop
]
UNFOLDED_RELOCS = [
    (0, "D_82305EB4", R_MIPS_HI16),
    (4, "D_82305EB4", R_MIPS_LO16),
    (20, "D_82305EB4", R_MIPS_HI16),
    (24, "D_82305EB4", R_MIPS_LO16),
    (28, "D_82305EC4", R_MIPS_HI16),
    (32, "D_82305EC4", R_MIPS_LO16),
    (36, "D_82305EC6", R_MIPS_HI16),
    (40, "D_82305EC6", R_MIPS_LO16),
    (44, "D_82305EC2", R_MIPS_HI16),
    (48, "D_82305EC2", R_MIPS_LO16),
    (52, "D_82305EC8", R_MIPS_HI16),
    (56, "D_82305EC8", R_MIPS_LO16),
]

# func_82300A78 as the ROM actually has it: 15 instructions, one `lui $at`
# shared by the D_82305EC4/EC6/EC2 stores and a second one reloaded for
# D_82305EC8, and the `bne` displacement shortened from 10 to 8 to match.
GROUND_TRUTH_WORDS = [
    0x3C0E0000, 0x85CE0000, 0x24010002, 0x240F0003,
    0x15C10008,  # bne $t6, $at, +8
    0x3C010000, 0xA42F0000,
    0x3C010000, 0xA4200000,
    0xA4205EC6,  # sh $zero, 0x5EC6($at)
    0xA4205EC2,  # sh $zero, 0x5EC2($at)
    0x3C010000, 0xA4200000,
    0x03E00008, 0x00000000,
]


def _by_offset(relocs):
    out: dict[int, list[tuple[str, int]]] = {}
    for offset, name, rel_type in relocs:
        out.setdefault(offset, []).append((name, rel_type))
    return out


class FoldWordsTest(unittest.TestCase):
    """The transform itself, on the real scheduled instruction stream."""

    def _fold(self, symbol_filter=NARROWED, words=None, relocs=None):
        words = UNFOLDED_WORDS if words is None else words
        relocs = UNFOLDED_RELOCS if relocs is None else relocs
        return coalesce_object.fold_function_words(
            words, _by_offset(relocs), ADDRESSES, symbol_filter, "func_82300A78"
        )

    def test_narrowed_fold_reproduces_ground_truth_exactly(self):
        new_words, _, folds = self._fold()
        self.assertEqual(folds, 2)
        self.assertEqual(new_words, GROUND_TRUTH_WORDS)

    def test_branch_displacement_is_repaired(self):
        new_words, _, _ = self._fold()
        # The `bne` still has to land on the `jr`, which moved two
        # instructions closer: displacement 10 -> 8.
        self.assertEqual(new_words[4] & 0xFFFF, 8)
        target = 4 + 1 + (new_words[4] & 0xFFFF)
        self.assertEqual(new_words[target], 0x03E00008)

    def test_relocations_for_folded_operands_are_dropped(self):
        _, relocations, _ = self._fold()
        names = [name for _, name, _ in relocations]
        self.assertNotIn("D_82305EC6", names)
        self.assertNotIn("D_82305EC2", names)
        # Everything the fold did not touch survives, at its new offset.
        self.assertEqual(
            relocations,
            [
                (0, "D_82305EB4", R_MIPS_HI16),
                (4, "D_82305EB4", R_MIPS_LO16),
                (20, "D_82305EB4", R_MIPS_HI16),
                (24, "D_82305EB4", R_MIPS_LO16),
                (28, "D_82305EC4", R_MIPS_HI16),
                (32, "D_82305EC4", R_MIPS_LO16),
                (44, "D_82305EC8", R_MIPS_HI16),
                (48, "D_82305EC8", R_MIPS_LO16),
            ],
        )

    def test_bare_marker_folds_the_whole_same_page_run(self):
        # Without the pragma's symbol list every one of the five stores is on
        # the same page, so all four redundant luis go and the function comes
        # out *shorter* than ground truth -- which is exactly why the
        # narrowed form exists.
        new_words, _, folds = self._fold(symbol_filter=None)
        self.assertEqual(folds, 4)
        self.assertEqual(len(new_words), len(UNFOLDED_WORDS) - 4)

    def test_unresolvable_symbol_stops_the_fold(self):
        addresses = {k: v for k, v in ADDRESSES.items() if k != "D_82305EC6"}
        new_words, _, folds = coalesce_object.fold_function_words(
            UNFOLDED_WORDS, _by_offset(UNFOLDED_RELOCS), addresses, None, "f"
        )
        # The run is cut at the unresolvable symbol rather than guessed
        # through, so this stays a partial fold and never a wrong one.
        self.assertNotIn(0xA4205EC6, new_words)

    def test_a_single_pair_is_not_folded(self):
        words = UNFOLDED_WORDS[:7] + UNFOLDED_WORDS[15:]
        relocs = [r for r in UNFOLDED_RELOCS if r[0] < 28]
        new_words, relocations, folds = coalesce_object.fold_function_words(
            words, _by_offset(relocs), ADDRESSES, None, "f"
        )
        self.assertEqual(folds, 0)
        self.assertEqual(new_words, words)
        self.assertIsNone(relocations)

    def test_refuses_to_delete_an_instruction_in_a_delay_slot(self):
        # A `lui $at` that is itself a branch delay slot is the second pair
        # of its run here, so the fold would want to remove it -- deleting a
        # delay slot changes what executes, so this must refuse outright.
        words = [
            0x3C010000,  # 0 lui $at, %hi(D_82305EC4)
            0xA4200000,  # 1 sh  $zero, %lo(D_82305EC4)($at)
            0x1000FFFF,  # 2 b   .
            0x3C010000,  # 3 lui $at, %hi(D_82305EC6)   [delay slot]
            0xA4200000,  # 4 sh  $zero, %lo(D_82305EC6)($at)
        ]
        relocs = [
            (0, "D_82305EC4", R_MIPS_HI16), (4, "D_82305EC4", R_MIPS_LO16),
            (12, "D_82305EC6", R_MIPS_HI16), (16, "D_82305EC6", R_MIPS_LO16),
        ]
        # Pairs are not consecutive here (the branch sits between them), so
        # they are not one run and nothing is folded at all -- the delay-slot
        # guard is defence behind that, asserted directly below.
        _, _, folds = coalesce_object.fold_function_words(
            words, _by_offset(relocs), ADDRESSES, None, "f"
        )
        self.assertEqual(folds, 0)
        with self.assertRaises(coalesce_object.FoldError):
            coalesce_object._check_not_in_a_delay_slot(words, 3)

    def test_refuses_a_branch_into_a_removed_instruction(self):
        words = list(UNFOLDED_WORDS)
        words[4] = 0x15C10004  # bne -> instruction 9, a lui the fold removes
        with self.assertRaises(coalesce_object.FoldError):
            self._fold(words=words)

    def test_refuses_a_branch_out_of_the_function(self):
        words = list(UNFOLDED_WORDS)
        words[4] = 0x15C17FFF  # a displacement far past the end
        with self.assertRaises(coalesce_object.FoldError):
            self._fold(words=words)


class AddressMapGuardTest(unittest.TestCase):
    """A map that disagrees with an address-shaped symbol name is refused.

    This is not hypothetical: a sibling checkout's linked ``.map``, built from
    a different ELF, resolved every ``fragments/79`` data label 0x10 high, and
    the fold happily baked those wrong displacements in -- the ROM came out
    16 bytes long with everything after the fold shifted. Nothing downstream
    can catch it, because the fold's whole job is to *remove* the relocation
    the linker would otherwise have used.
    """

    def test_skewed_map_is_refused(self):
        skewed = {name: address + 0x10 for name, address in ADDRESSES.items()}
        with self.assertRaises(coalesce_object.FoldError) as caught:
            coalesce_object.fold_function_words(
                UNFOLDED_WORDS, _by_offset(UNFOLDED_RELOCS), skewed, NARROWED, "f"
            )
        self.assertIn("refusing to fold", str(caught.exception))

    def test_a_renamed_symbol_has_no_claim_to_check(self):
        # An evidence-backed name says nothing about its address, so it must
        # pass through rather than being rejected for "disagreeing".
        coalesce_object._verify_address("BattleAnim_Table_058", 0x84186160)

    def test_an_address_shaped_name_that_agrees_passes(self):
        coalesce_object._verify_address("D_82305EC4", 0x82305EC4)


class DelaySlotStraddledPairTest(unittest.TestCase):
    """``func_84136D84`` (fragments/79), the mechanism's original worked example.

    IDO schedules its last store into the ``jr`` delay slot and hoists that
    store's ``lui $at`` *above* the ``jr``, so the pair is not adjacent. An
    earlier version of this fold required strict adjacency, dropped that
    pair, and produced seven instructions where the ROM has six -- a real
    regression against a function the previous text-level mechanism handled
    correctly, caught by the full ROM compare.
    """

    ADDRESSES = {
        "D_84186160": 0x84186160, "D_84186164": 0x84186164,
        "D_84186168": 0x84186168, "D_8418616C": 0x8418616C,
    }
    WORDS = [
        0x3C010000,  # 0 lui $at, %hi(D_84186160)
        0xAC200000,  # 1 sw  $zero, %lo(D_84186160)($at)
        0x3C010000,  # 2 lui $at, %hi(D_84186164)
        0xAC200000,  # 3 sw  $zero, %lo(D_84186164)($at)
        0x3C010000,  # 4 lui $at, %hi(D_84186168)
        0xAC200000,  # 5 sw  $zero, %lo(D_84186168)($at)
        0x3C010000,  # 6 lui $at, %hi(D_8418616C)
        0x03E00008,  # 7 jr  $ra
        0xAC200000,  # 8 sw  $zero, %lo(D_8418616C)($at)   [delay slot]
    ]
    RELOCS = [
        (0, "D_84186160", R_MIPS_HI16), (4, "D_84186160", R_MIPS_LO16),
        (8, "D_84186164", R_MIPS_HI16), (12, "D_84186164", R_MIPS_LO16),
        (16, "D_84186168", R_MIPS_HI16), (20, "D_84186168", R_MIPS_LO16),
        (24, "D_8418616C", R_MIPS_HI16), (32, "D_8418616C", R_MIPS_LO16),
    ]
    # The ROM's own bytes for this function.
    GROUND_TRUTH = [0x3C010000, 0xAC200000, 0xAC206164, 0xAC206168,
                    0x03E00008, 0xAC20616C]

    def test_reproduces_ground_truth(self):
        new_words, _, folds = coalesce_object.fold_function_words(
            self.WORDS, _by_offset(self.RELOCS), self.ADDRESSES, None,
            "func_84136D84",
        )
        self.assertEqual(folds, 3)
        self.assertEqual(new_words, self.GROUND_TRUTH)

    def test_the_store_stays_in_the_delay_slot(self):
        new_words, _, _ = coalesce_object.fold_function_words(
            self.WORDS, _by_offset(self.RELOCS), self.ADDRESSES, None,
            "func_84136D84",
        )
        jr_index = new_words.index(0x03E00008)
        self.assertEqual(new_words[jr_index + 1], 0xAC20616C)


class RunPlanningTest(unittest.TestCase):
    def test_pairs_must_share_one_symbol_between_hi_and_lo(self):
        # A `lui $at` whose %hi names one symbol followed by an op whose %lo
        # names another is not a macro pair this fold recognises.
        relocs = list(UNFOLDED_RELOCS)
        relocs[7] = (32, "D_82305EC8", R_MIPS_LO16)
        runs = coalesce_object.plan_runs(
            UNFOLDED_WORDS, _by_offset(relocs), ADDRESSES, None
        )
        self.assertTrue(all(all(s != "D_82305EC4" for _, _, s in run) for run in runs))

    def test_a_symbol_outside_the_filter_cuts_the_run(self):
        runs = coalesce_object.plan_runs(
            UNFOLDED_WORDS, _by_offset(UNFOLDED_RELOCS), ADDRESSES, NARROWED
        )
        self.assertEqual(len(runs), 1)
        self.assertEqual(
            [symbol for _, _, symbol in runs[0]],
            ["D_82305EC4", "D_82305EC6", "D_82305EC2"],
        )

    def test_a_word_carrying_two_relocations_is_never_a_pair(self):
        # Two relocations on one word is a shape this fold does not model, so
        # that word simply stops being a macro pair -- D_82305EC4 drops out of
        # the run entirely rather than being folded on a guess. The remaining
        # two pairs are still a legitimate run of their own.
        relocs = list(UNFOLDED_RELOCS) + [(28, "D_82305EC8", R_MIPS_HI16)]
        runs = coalesce_object.plan_runs(
            UNFOLDED_WORDS, _by_offset(relocs), ADDRESSES, NARROWED
        )
        self.assertEqual(
            [[symbol for _, _, symbol in run] for run in runs],
            [["D_82305EC6", "D_82305EC2"]],
        )


@unittest.skipUnless(shutil.which("mips-linux-gnu-as"), "no MIPS GNU as available")
class InObjectTest(unittest.TestCase):
    """End to end over a real ELF, through the shared splice core."""

    def _object(self, words=None, relocs=None):
        return _assemble_fixture(
            UNFOLDED_WORDS if words is None else words,
            UNFOLDED_RELOCS if relocs is None else relocs,
        )

    def test_fold_in_object_matches_ground_truth_and_shifts_the_neighbour(self):
        obj_bytes = self._object()
        folded_bytes, folds = coalesce_object.fold_function_in_object(
            obj_bytes, "func_82300A78", ADDRESSES, NARROWED
        )
        self.assertEqual(folds, 2)
        folded = elf32.parse(folded_bytes)
        symbols = {s.name: s for s in folded.symbols() if s.name}
        self.assertEqual(symbols["func_82300A78"].size, len(GROUND_TRUTH_WORDS) * 4)
        text = folded.section(".text").data
        got = list(struct.unpack(">%dI" % len(GROUND_TRUTH_WORDS),
                                text[:len(GROUND_TRUTH_WORDS) * 4]))
        self.assertEqual(got, GROUND_TRUTH_WORDS)
        # The function after it moved down by exactly the two removed words.
        self.assertEqual(symbols["neighbour"].value, len(GROUND_TRUTH_WORDS) * 4)

    def test_relocation_offsets_follow_the_new_layout(self):
        folded_bytes, _ = coalesce_object.fold_function_in_object(
            self._object(), "func_82300A78", ADDRESSES, NARROWED
        )
        folded = elf32.parse(folded_bytes)
        symbols = folded.symbols()
        got = [
            (rel.offset, symbols[rel.sym_index].name, rel.type)
            for rel in folded.relocations(".rel.text")
        ]
        self.assertEqual(
            got,
            [
                (0, "D_82305EB4", R_MIPS_HI16),
                (4, "D_82305EB4", R_MIPS_LO16),
                (20, "D_82305EB4", R_MIPS_HI16),
                (24, "D_82305EB4", R_MIPS_LO16),
                (28, "D_82305EC4", R_MIPS_HI16),
                (32, "D_82305EC4", R_MIPS_LO16),
                (44, "D_82305EC8", R_MIPS_HI16),
                (48, "D_82305EC8", R_MIPS_LO16),
            ],
        )

    def test_nothing_to_fold_returns_the_object_untouched(self):
        obj_bytes = self._object(
            words=UNFOLDED_WORDS[:7] + UNFOLDED_WORDS[15:],
            relocs=[r for r in UNFOLDED_RELOCS if r[0] < 28],
        )
        folded_bytes, folds = coalesce_object.fold_function_in_object(
            obj_bytes, "func_82300A78", ADDRESSES, None
        )
        self.assertEqual(folds, 0)
        self.assertIs(folded_bytes, obj_bytes)

    def test_unknown_function_is_an_error(self):
        with self.assertRaises(coalesce_object.FoldError):
            coalesce_object.fold_function_in_object(
                self._object(), "func_not_here", ADDRESSES, None
            )


def _assemble_fixture(words, relocs) -> bytes:
    """Assemble the unfolded fixture into a real object with GNU ``as``.

    Hand-building an ELF here would test this file's own ELF writer rather
    than the fold, so the fixture is produced by a real assembler: the exact
    instruction words above, with the ``%hi``/``%lo`` operands written
    symbolically so ``as`` emits the same relocations IDO does, under
    ``.set noreorder``/``.set noat`` so it changes nothing about the stream.
    A second function after it gives the splice's symbol and relocation
    shifting something to move.
    """
    lines = ["\t.set\tnoreorder", "\t.set\tnoat", "\t.text", "\t.globl\tfunc_82300A78",
             "func_82300A78:"]
    symbolic = {(offset, rel_type): name for offset, name, rel_type in relocs}
    for index, word in enumerate(words):
        offset = index * 4
        hi = symbolic.get((offset, R_MIPS_HI16))
        lo = symbolic.get((offset, R_MIPS_LO16))
        if hi is not None:
            lines.append("\tlui\t$%d, %%hi(%s)" % ((word >> 16) & 0x1F, hi))
        elif lo is not None:
            op = "lh" if (word >> 26) == 0x21 else "sh"
            reg = "$%d" % ((word >> 16) & 0x1F)
            if (word >> 21) & 0x1F == 1:
                lines.append("\t%s\t%s, %%lo(%s)($at)" % (op, reg, lo))
            else:
                lines.append("\t%s\t%s, %%lo(%s)($%d)" % (op, reg, lo, (word >> 21) & 0x1F))
        else:
            lines.append("\t.word\t0x%08X" % word)
    lines += [
        "\t.size\tfunc_82300A78, . - func_82300A78",
        "\t.globl\tneighbour",
        "neighbour:",
        "\t.word\t0x03E00008",
        "\t.word\t0x00000000",
        "\t.size\tneighbour, . - neighbour",
        "",
    ]
    with tempfile.TemporaryDirectory(prefix="coalesce_object_test_") as tmp:
        source = Path(tmp) / "fixture.s"
        obj = Path(tmp) / "fixture.o"
        source.write_text("\n".join(lines), encoding="latin1")
        subprocess.run(
            ["mips-linux-gnu-as", "-march=vr4300", "-32", "-G0", "-EB",
             "-o", str(obj), str(source)],
            check=True, capture_output=True,
        )
        return obj.read_bytes()


if __name__ == "__main__":  # pragma: no cover
    unittest.main()
