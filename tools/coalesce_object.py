#!/usr/bin/env python3
"""Fold shared-page ``lui $at`` runs in *compiled object code*.

This replaces the text-level round trip ``coalesce_cc.py`` used to perform
(recompile with ``-S``, extract the function's ``.s`` block, fold the text,
re-assemble that block on its own, splice the result back in). That round
trip loses IDO's own ``cc -c`` instruction scheduling, because IDO's ``-S``
output is written *before* its assembler fills branch delay slots and the
text is not a faithful record of the object it would have produced:

    From C, ``cc -c`` compiles ``func_82300A78``
    (``fragments/19/fragment19_121100.c``) with ``li $t7, 3`` hoisted *above*
    the ``bne`` and the following macro store's ``lui $at`` scheduled into
    the branch delay slot -- exactly what ground truth has. Feeding IDO's own
    ``-S`` text for that same function back through GNU ``as`` *or* through
    IDO's own assembler (measured both ways, with and without ``-O2``) yields
    ``bne`` + ``nop`` with ``li $t7, 3`` left after the branch: one
    instruction longer, every time.

So the text round trip only ever worked for a *straight-line* function --
``func_84136D84``, the mechanism's original worked example, has no branch at
all, which is why this never surfaced there. Any opted-in function with a
branch came back one instruction long and could never match.

This module takes the other route: the object produced by the completely
normal ``cc -c`` invocation already contains the correct, fully scheduled
machine code; it is only carrying redundant ``lui $at`` instructions. So fold
*that*, in place, with no second assembler pass anywhere:

1. Find the function's words in ``.text`` and its own ``.rel.text`` entries.
2. Recognise the macro pairs the assembler expanded -- ``lui $at, %hi(S)``
   carrying an ``R_MIPS_HI16`` for ``S``, immediately followed by a memory op
   based on ``$at`` carrying an ``R_MIPS_LO16`` for the same ``S``.
3. Group maximal runs of consecutive such pairs whose symbols all resolve,
   via the same address map, to one ``%hi`` page (and, when the pragma named
   a symbol list, are all in it -- an op outside the list both refuses to
   fold and cuts the run, exactly as in ``coalesce_lui.fold_source``).
4. Delete every ``lui`` after the run's first, rewrite the orphaned memory
   ops' 16-bit displacement to the plain literal that reaches their symbol
   off the surviving ``$at``, and drop the relocations that described them.
5. Repair every PC-relative branch whose distance the deletions changed.

Step 5 is the part a text fold got for free and the reason this cannot be a
pure byte patch: removing an instruction moves everything after it. The
result is handed to ``coalesce_splice.replace_function_bytes``, which already
knows how to install a *shorter* function body into an object (section
padding, symbol values, relocation offsets, section-relative addends).

Why the displacement becomes a plain literal rather than a second symbolic
``%lo``: that is the pre-existing decision documented in ``coalesce_lui``'s
module docstring -- this project's IDO port emits a spurious extra relocation
for every ``%lo`` after the first whose symbol does not match the preceding
``%hi``'s. Here it also falls out naturally: there is no relocation left to
emit, because the fold simply deletes the ones it no longer needs.
"""
from __future__ import annotations

import re
import struct

import coalesce_lui
import coalesce_splice
import elf32

R_MIPS_HI16 = 5
R_MIPS_LO16 = 6
R_MIPS_26 = 4

_AT = 1

# Memory-op primary opcodes whose base register field this fold understands.
# Deliberately the same instruction set ``coalesce_lui._MACRO_MEM_OP`` matches
# at the text level (lb/lh/lw/lbu/lhu/sb/sh/sw plus the single- and
# double-precision coprocessor loads and stores), so the two layers agree on
# what a foldable macro pair even is.
_MEM_OPCODES = {
    0x20: "lb", 0x21: "lh", 0x23: "lw", 0x24: "lbu", 0x25: "lhu",
    0x28: "sb", 0x29: "sh", 0x2B: "sw",
    0x31: "lwc1", 0x35: "ldc1", 0x39: "swc1", 0x3D: "sdc1",
}

# Primary opcodes of the PC-relative branches whose 16-bit displacement has to
# be repaired when instructions are removed between them and their target.
# 0x01 is REGIMM (bltz/bgez/bltzal/bgezal and their likely forms); 0x10-0x13
# are the coprocessor branch spaces, where rs == 8 selects BCzF/BCzT/BCzFL/
# BCzTL (any other rs there is not a branch at all).
_BRANCH_OPCODES = {0x04, 0x05, 0x06, 0x07, 0x14, 0x15, 0x16, 0x17, 0x01}
_COP_OPCODES = {0x10, 0x11, 0x12, 0x13}
_JUMP_OPCODES = {0x02, 0x03}  # j / jal -- absolute, never PC-relative


# splat names an unnamed data label after its own address (``D_82305EC2`` at
# 0x82305EC2), and ``undefined_syms_auto.ld`` literally writes that identity
# out as ``D_82305EC2 = 0x82305EC2;``. That makes the name a free, independent
# check on the address map -- see ``_verify_address``.
_ADDRESS_SHAPED_NAME = re.compile(r"^[A-Za-z]+_([0-9A-F]{8})$")


class FoldError(Exception):
    """Raised when a function cannot be folded safely; never a silent wrong fold."""


def _verify_address(symbol: str, address: int) -> None:
    """Reject an address map that disagrees with an address-shaped symbol name.

    The fold's correctness rests entirely on the address map: it replaces a
    relocation with a literal displacement, so a wrong address becomes wrong
    *bytes* in a linked ROM, with no relocation left for the linker to catch
    it. ``resolve_repo_addresses`` will fall back to a linked ``.map`` from a
    sibling checkout when this one has not been built yet, and that map can
    be from a different ELF -- a skewed one was what first produced a wrong
    fold here (``D_84186160`` resolving to 0x84186170, a uniform +0x10 shift,
    which silently produced a ROM 16 bytes long).

    Most of the symbols this fold ever touches are splat's own
    address-derived labels, so the name states the answer independently of
    any map. Where it does, hold the map to it; a renamed, evidence-backed
    symbol simply has no such claim to check and passes through.
    """
    match = _ADDRESS_SHAPED_NAME.match(symbol)
    if match is None:
        return
    claimed = int(match.group(1), 16)
    if claimed != address:
        raise FoldError(
            f"address map says {symbol} is at {address:#010x}, but the symbol's "
            f"own name says {claimed:#010x} -- refusing to fold against a map "
            "that disagrees with the tree (a stale or foreign linked .map?)"
        )


def _is_lui_at(word: int) -> bool:
    # lui $at, imm -- opcode 0x0F, rs field unused (0), rt == $at.
    return (word >> 16) == ((0x0F << 10) | _AT)


def _is_mem_op_based_on_at(word: int) -> bool:
    opcode = word >> 26
    base = (word >> 21) & 0x1F
    return opcode in _MEM_OPCODES and base == _AT


def _is_pc_relative_branch(word: int) -> bool:
    opcode = word >> 26
    if opcode in _BRANCH_OPCODES:
        return True
    if opcode in _COP_OPCODES:
        return ((word >> 21) & 0x1F) == 8
    return False


def _sign_extend16(value: int) -> int:
    value &= 0xFFFF
    return value - 0x10000 if value & 0x8000 else value


def _relocations_by_offset(relocations, symbols, lo: int, hi: int):
    """``{function-relative offset: [(symbol_name, type), ...]}`` for one function."""
    by_offset: dict[int, list[tuple[str, int]]] = {}
    for rel in relocations:
        if not (lo <= rel.offset < hi):
            continue
        if rel.sym_index >= len(symbols):
            raise FoldError("a relocation has an out-of-range symbol index")
        by_offset.setdefault(rel.offset - lo, []).append(
            (symbols[rel.sym_index].name, rel.type)
        )
    return by_offset


def _single_reloc(by_offset, offset: int, wanted_type: int):
    """The one relocation of ``wanted_type`` at ``offset``, or ``None``.

    More than one relocation on the same word is not something this fold
    knows how to reason about, so such a word is simply never treated as part
    of a macro pair (it falls out of every run) rather than folded on a guess.
    """
    entries = by_offset.get(offset)
    if not entries or len(entries) != 1:
        return None
    name, rel_type = entries[0]
    if rel_type != wanted_type or not name:
        return None
    return name


def _is_control_transfer(word: int) -> bool:
    """A branch, a ``j``/``jal``, or a ``jr``/``jalr`` -- anything with a delay slot."""
    if _is_pc_relative_branch(word) or (word >> 26) in _JUMP_OPCODES:
        return True
    if (word >> 26) == 0:  # SPECIAL: jr / jalr
        return (word & 0x3F) in (0x08, 0x09)
    return False


def _macro_pairs(words, by_offset):
    """``{lui index: (mem-op index, symbol)}`` for every macro pair in the function.

    The mem op is normally the very next instruction, but IDO's scheduler can
    hoist a ``lui`` *above* a control transfer and leave its store in the
    delay slot -- ``func_84136D84``'s last store is exactly that
    (``lui $at, %hi(D_8418616C)`` / ``jr $ra`` / ``sw ..., %lo(D_8418616C)``).
    Requiring strict adjacency silently drops that pair, which folds the
    function one ``lui`` short of ground truth, so a single intervening
    control transfer is allowed: its delay slot executes before the jump
    takes effect, and neither a branch nor a jump writes ``$at``, so the
    surviving ``lui``'s value is still live at the store.
    """
    pairs: dict[int, tuple[int, str]] = {}
    for index in range(len(words) - 1):
        if not _is_lui_at(words[index]):
            continue
        hi_symbol = _single_reloc(by_offset, index * 4, R_MIPS_HI16)
        if hi_symbol is None:
            continue
        candidates = [index + 1]
        if _is_control_transfer(words[index + 1]):
            candidates.append(index + 2)
        for op_index in candidates:
            if op_index >= len(words):
                continue
            if not _is_mem_op_based_on_at(words[op_index]):
                continue
            if _single_reloc(by_offset, op_index * 4, R_MIPS_LO16) != hi_symbol:
                continue
            pairs[index] = (op_index, hi_symbol)
            break
    return pairs


def plan_runs(words, by_offset, address_map, symbol_filter=None):
    """Maximal foldable runs, as ``[[(index, symbol), ...], ...]``.

    A run is consecutive macro pairs (``lui`` at ``i``, its op at ``i + 1``,
    the next pair starting at ``i + 2``) whose symbols all resolve in
    ``address_map`` to the same ``%hi`` page and, when ``symbol_filter`` is
    not ``None``, are all in it. Only runs of two or more pairs are returned,
    since a single pair has no redundant ``lui`` to drop.
    """
    pairs = _macro_pairs(words, by_offset)
    runs = []
    index = 0
    while index < len(words):
        if index not in pairs:
            index += 1
            continue
        run = []
        cursor = index
        while cursor in pairs:
            op_index, symbol = pairs[cursor]
            if symbol_filter is not None and symbol not in symbol_filter:
                break
            address = address_map.get(symbol)
            if address is None:
                break
            _verify_address(symbol, address)
            if run and coalesce_lui.hi16(address) != coalesce_lui.hi16(
                address_map[run[0][2]]
            ):
                break
            run.append((cursor, op_index, symbol))
            cursor = op_index + 1
        if len(run) >= 2:
            runs.append(run)
            index = cursor
        else:
            index += 1
    return runs


def _check_not_in_a_delay_slot(words, index: int) -> None:
    """Refuse to delete an instruction that sits in a delay slot.

    Every control transfer counts, ``jr``/``jalr`` included: removing a delay
    slot changes *what executes*, not merely where it sits, so this is a hard
    stop rather than a shorter fold.
    """
    if index == 0:
        return
    previous = words[index - 1]
    if _is_control_transfer(previous):
        raise FoldError(
            f"instruction {index} is in a branch delay slot; removing it would "
            "change what executes, not just where it sits"
        )


def _repair_branches(words, keep, old_to_new, function_name):
    """Rewrite surviving PC-relative displacements for the new instruction layout."""
    repaired = []
    count = len(words)
    for old_index in keep:
        word = words[old_index]
        if not _is_pc_relative_branch(word):
            repaired.append(word)
            continue
        target = old_index + 1 + _sign_extend16(word & 0xFFFF)
        if not (0 <= target <= count):
            raise FoldError(
                f"{function_name}: a branch at instruction {old_index} leaves the "
                f"function (target {target}); this fold cannot re-target it"
            )
        if target not in old_to_new:
            raise FoldError(
                f"{function_name}: a branch at instruction {old_index} targets "
                f"instruction {target}, which the fold removes"
            )
        displacement = old_to_new[target] - old_to_new[old_index] - 1
        if not (-0x8000 <= displacement <= 0x7FFF):  # pragma: no cover - arithmetic guard
            raise FoldError(f"{function_name}: repaired branch displacement out of range")
        repaired.append((word & 0xFFFF0000) | (displacement & 0xFFFF))
    return repaired


def fold_function_words(words, by_offset, address_map, symbol_filter, function_name):
    """Return ``(new_words, kept_relocations, folds_applied)`` for one function.

    ``kept_relocations`` is ``[(new byte offset, symbol, type)]``: every
    relocation the function still needs, with offsets already expressed
    against the new, shorter body.
    """
    runs = plan_runs(words, by_offset, address_map, symbol_filter)
    if not runs:
        return list(words), None, 0

    removed: set[int] = set()
    rewritten: dict[int, int] = {}
    folds = 0
    for run in runs:
        for index, op_index, symbol in run[1:]:
            _check_not_in_a_delay_slot(words, index)
            removed.add(index)
            # $at holds hi16(base) << 16, and every symbol in the run shares
            # that page, so the plain low half of this symbol's own address
            # is exactly the displacement that reaches it -- the same value
            # coalesce_lui._lo16_immediate_literal renders as assembly text.
            rewritten[op_index] = coalesce_lui.lo16(address_map[symbol])
            folds += 1

    keep = [i for i in range(len(words)) if i not in removed]
    old_to_new = {old: new for new, old in enumerate(keep)}
    old_to_new[len(words)] = len(keep)  # a branch to the end of the function

    staged = list(words)
    for index, displacement in rewritten.items():
        staged[index] = (staged[index] & 0xFFFF0000) | (displacement & 0xFFFF)

    new_words = _repair_branches(staged, keep, old_to_new, function_name)

    kept_relocations = []
    for old_index in keep:
        if old_index in rewritten:
            continue  # its %lo is now a literal: the relocation is gone
        for name, rel_type in by_offset.get(old_index * 4, []):
            kept_relocations.append((old_to_new[old_index] * 4, name, rel_type))
    return new_words, kept_relocations, folds


def fold_function_in_object(
    object_bytes: bytes,
    function_name: str,
    address_map: dict[str, int],
    symbol_filter=None,
) -> tuple[bytes, int]:
    """Fold ``function_name`` in place inside a compiled object.

    Returns ``(new_object_bytes, folds_applied)``; ``folds_applied == 0``
    means nothing about the object changed, which callers treat as an error
    for an explicitly opted-in function (see ``coalesce_cc.py``).
    """
    obj = elf32.parse(object_bytes)
    text_index = obj.section_index(".text")
    if text_index is None:
        raise FoldError("object has no .text section")
    symbols = obj.symbols()
    func_index = coalesce_splice._find_symbol_index(symbols, function_name, text_index)
    if func_index is None:
        raise FoldError(f"{function_name} not found (or undefined) in the object")
    func = symbols[func_index]
    lo, hi = func.value, func.value + func.size
    if func.size <= 0 or func.size % 4:
        raise FoldError(f"{function_name} has an unusable size {func.size}")
    text = obj.section(".text").data
    if hi > len(text):
        raise FoldError(f"{function_name} runs past the end of .text")

    words = list(struct.unpack(">%dI" % (func.size // 4), text[lo:hi]))
    by_offset = _relocations_by_offset(obj.relocations(".rel.text"), symbols, lo, hi)

    # An intra-function absolute jump would need its baked-in 26-bit target
    # re-pointed, which nothing here does. IDO uses `b` for local control flow
    # and reserves j/jal for calls, so this is a guard, not a live path.
    for index, word in enumerate(words):
        if (word >> 26) in _JUMP_OPCODES and _single_reloc(
            by_offset, index * 4, R_MIPS_26
        ) is None and by_offset.get(index * 4):
            raise FoldError(
                f"{function_name}: an absolute jump at instruction {index} carries a "
                "relocation this fold cannot re-target"
            )

    new_words, kept_relocations, folds = fold_function_words(
        words, by_offset, address_map, symbol_filter, function_name
    )
    if folds == 0:
        return object_bytes, 0

    new_bytes = struct.pack(">%dI" % len(new_words), *new_words)
    return (
        coalesce_splice.replace_function_bytes(
            object_bytes, function_name, new_bytes, kept_relocations
        ),
        folds,
    )
