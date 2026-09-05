#!/usr/bin/env python3
"""Object-level splice: replace one function's compiled bytes in an ``.o``.

Why this exists (see ``coalesce_lui.py``'s module docstring for the full
story): folding a shared-page ``lui $at`` run requires re-assembling the
*whole* changed compilation unit's ``.s`` output, and this project's IDO port
turns out to mis-assemble ordinary compiler-generated numbered branch labels
(``$32`` and friends -- completely unrelated to the fold itself) when a
large, multi-function ``.s`` file is fed back through its assemble-only
(``-c`` on a ``.s`` input) path, even with zero fold applied. That path is
safe only for a small, branch-free snippet -- exactly the shape a foldable
function has.

So instead of re-assembling the whole file, the opted-in function is
compiled *twice*, independently:

1. The real, tracked ``.c`` file compiles completely normally (today's exact
   single-shot ``-c`` invocation, never touched by this module) into
   ``outer.o``. The opted-in function is present there with the *correct*
   size, symbol, and section placement, but the *wrong* (unfolded) bytes.
2. The opted-in function's own isolated source is compiled, folded, and
   assembled by itself (the tiny, branch-free two-stage path that already
   works) into ``inner.o``.

``splice_function`` then copies just that one function's ``.text`` bytes and
``.rel.text`` entries from ``inner.o`` into ``outer.o``, leaving every other
byte of ``outer.o`` -- every other function in the file, all of its
relocations, its symbol table -- untouched. This is the same *shape* of
operation asm-processor's own post-process step already performs for
``GLOBAL_ASM`` placeholders (replace one named function's machine code within
an otherwise-normal object); it is reimplemented narrowly here rather than
reusing that vendored tool directly, since its input model is raw
hand-written assembly text feeding a preprocessing pass, not two already
-compiled objects.
"""
from __future__ import annotations

import struct
from pathlib import Path

import elf32

STT_SECTION = 3
R_MIPS_32 = 2
R_MIPS_26 = 4
R_MIPS_HI16 = 5
R_MIPS_LO16 = 6


class SpliceError(Exception):
    """Raised when the two objects cannot be safely spliced together."""


def _sign_extend16(value: int) -> int:
    value &= 0xFFFF
    return value - 0x10000 if value & 0x8000 else value


def _hi16_field(value: int) -> int:
    return ((value + 0x8000) >> 16) & 0xFFFF


def _lo16_field(value: int) -> int:
    return value & 0xFFFF


def _align_up(value: int, alignment: int) -> int:
    if alignment <= 1:
        return value
    return (value + alignment - 1) // alignment * alignment


def _text_content_end(symbols, text_index: int) -> int:
    """Highest offset any named ``.text`` symbol reaches.

    Everything past this in the section is the assembler's own end-of-section
    alignment padding (see ``_retrim_trailing_padding``), not content.
    """
    end = 0
    for sym in symbols:
        if sym.shndx != text_index or (sym.info & 0xF) == STT_SECTION:
            continue
        end = max(end, sym.value + sym.size)
    return end


def _retrim_trailing_padding(
    new_text: bytes, old_content_end: int, old_len: int, delta: int, alignment: int
) -> bytes:
    """Re-pad a spliced ``.text`` to the length the assembler would have emitted.

    IDO pads ``.text`` up to a multiple of the section's own alignment (16
    here), so a section's length is ``align_up(content_end, 16)`` and NOT the
    length of its content. Splicing in a shorter function moves the content
    end down by ``-delta``, which can move it across an alignment boundary --
    but the naive ``head + folded + tail`` concatenation carries the *old*
    padding along unchanged, leaving a section whose length is
    ``align_up(old_content_end, 16) + delta``. That is 4 bytes too long (and
    no longer 16-aligned at all) whenever the fold crosses a boundary, which
    silently shifts every later object in the link and fails the ROM compare
    -- with the extra bytes attributable to no symbol at all, so nothing else
    in the build notices.

    Recompute the padding from the new content end instead -- but only when
    the input section actually was padded that way (``old_len`` is exactly
    ``align_up(old_content_end, alignment)``). Anything else is a section
    this rule was not written for (a hand-built object, a toolchain that
    pads differently), and gets the old, length-preserving behavior rather
    than a guess.
    """
    if old_len != _align_up(old_content_end, alignment):
        return new_text
    new_content_end = old_content_end + delta
    desired_len = _align_up(new_content_end, alignment)
    if desired_len < new_content_end:  # pragma: no cover - arithmetic guard
        raise SpliceError("computed a .text length shorter than its own content")
    # Everything past the (new) content end is padding by construction, so it
    # must be zeroes. Anything else means content this function cannot see --
    # stop rather than drop or keep bytes that turn out to matter.
    if new_text[new_content_end:].strip(b"\0"):
        raise SpliceError(
            ".text trailing padding is not zero-filled; refusing to retrim it"
        )
    if desired_len <= len(new_text):
        return new_text[:desired_len]
    return new_text + b"\0" * (desired_len - len(new_text))


def splice_function(outer_bytes: bytes, inner_bytes: bytes, function_name: str) -> bytes:
    """Return ``outer_bytes`` with ``function_name``'s bytes replaced from ``inner_bytes``.

    The whole point of folding a redundant ``lui`` is that the function gets
    *shorter*, so the replacement need not be (and for a real fold, never
    is) the same size as the original. Every symbol placed in ``.text``
    after the replaced function, and every relocation targeting an offset
    after it (in any ``.rel``-type section aimed at ``.text``), is shifted
    by the resulting size delta so the rest of the object -- everything
    after this one function -- keeps exactly the addresses it would have
    linked to anyway; nothing about *this* function's own compiled position
    depends on where in the file it happens to sit.

    Raises :class:`SpliceError` (never silently produces a wrong object) if
    the function is missing from either object, or one of its relocations
    targets a symbol the outer object does not itself already reference
    (this project's fold only ever drops relocations -- see
    ``coalesce_lui.fold_source`` -- so the sole remaining one is always for
    a symbol already used elsewhere in the same file; a symbol the normal
    build has never had reason to reference is treated as a hard stop, not
    a guess).
    """
    outer = elf32.parse(outer_bytes)
    inner = elf32.parse(inner_bytes)

    text_index = outer.section_index(".text")
    if text_index is None or inner.section_index(".text") is None:
        raise SpliceError("both objects must have a .text section")

    outer_symbols = outer.symbols()
    inner_symbols = inner.symbols()

    outer_func_index = _find_symbol_index(outer_symbols, function_name, text_index)
    inner_func_index = _find_symbol_index(inner_symbols, function_name, None)
    if outer_func_index is None:
        raise SpliceError(f"{function_name} not found (or undefined) in the outer object")
    if inner_func_index is None:
        raise SpliceError(f"{function_name} not found (or undefined) in the inner object")

    outer_sym = outer_symbols[outer_func_index]
    inner_sym = inner_symbols[inner_func_index]
    old_size = outer_sym.size
    new_size = inner_sym.size
    if old_size <= 0:
        raise SpliceError(f"{function_name} has non-positive outer size {old_size}")
    if new_size <= 0:
        raise SpliceError(
            f"{function_name}'s folded form has non-positive size {new_size} "
            "-- the GNU as snippet is missing a `.size` directive?"
        )

    outer_text_sec = outer.section(".text")
    inner_text_sec = inner.section(".text")
    lo, hi = outer_sym.value, outer_sym.value + old_size
    if hi > len(outer_text_sec.data):
        raise SpliceError(f"{function_name}'s outer range runs past the end of .text")
    ilo, ihi = inner_sym.value, inner_sym.value + new_size
    if ihi > len(inner_text_sec.data):
        raise SpliceError(f"{function_name}'s inner range runs past the end of .text")

    new_text = outer_text_sec.data[:lo] + inner_text_sec.data[ilo:ihi] + outer_text_sec.data[hi:]
    delta = new_size - old_size
    new_text = _retrim_trailing_padding(
        new_text,
        _text_content_end(outer_symbols, text_index),
        len(outer_text_sec.data),
        delta,
        outer_text_sec.addralign,
    )
    outer.set_section_data(".text", new_text)

    # Shift every other symbol placed in .text after the replaced range, and
    # update this function's own size (its own value/offset does not move).
    for i, sym in enumerate(outer_symbols):
        if i == outer_func_index:
            sym.size = new_size
        elif sym.shndx == text_index and sym.value >= hi:
            sym.value += delta
        elif (
            sym.shndx == text_index
            and (sym.info & 0xF) != STT_SECTION
            and lo <= sym.value < hi
        ):
            # A named symbol (e.g. a local label) placed strictly inside
            # the range being replaced -- not the .text section symbol
            # itself (always value 0, handled separately) and not the
            # fold target's own symbol (handled above). Not reachable
            # through this mechanism's real build path today (this fold
            # only ever emits the function's own top-level symbol), but
            # defense-in-depth: refuse rather than leave it silently
            # pointing at a now-meaningless offset inside the replaced body.
            raise SpliceError(
                f"{function_name}: symbol {sym.name!r} sits inside the "
                f"function's own [{lo:#x}, {hi:#x}) range being replaced -- "
                "refusing to splice a function whose in-function layout "
                "this mechanism cannot re-target"
            )
    outer.set_symbols(outer_symbols)

    # Every SHT_NULL and STT_SECTION symbol conventionally has an empty
    # name (confirmed on this repo's own objects: CE80.o alone has four
    # symbols named "" -- the null symbol plus three section symbols), so a
    # plain name -> index dict would silently collapse all of them to
    # whichever one happens to be enumerated last. Name-based translation
    # is only ever sound for a real, uniquely-named symbol; excluding
    # these here makes that collision impossible to hit by accident rather
    # than relying on inner's own fold shape never producing one, and the
    # (currently unreached, since this fold never emits a section-relative
    # self-reference) case below gives a specific error instead of quietly
    # "resolving" to an unrelated section.
    outer_name_to_index = {
        sym.name: i
        for i, sym in enumerate(outer_symbols)
        if sym.name and (sym.info & 0xF) != STT_SECTION
    }

    translated = []
    for rel in inner.relocations(".rel.text"):
        if not (ilo <= rel.offset < ihi):
            continue  # cannot happen in a single-function inner object; skip
            # defensively rather than let it leak into the wrong place.
        if rel.sym_index >= len(inner_symbols):
            raise SpliceError(f"{function_name}: inner relocation has an out-of-range symbol index")
        target_symbol = inner_symbols[rel.sym_index]
        target_name = target_symbol.name
        if not target_name or (target_symbol.info & 0xF) == STT_SECTION:
            raise SpliceError(
                f"{function_name}: a folded relocation references an unnamed "
                "or section-relative symbol -- e.g. a self-contained jump "
                "table or literal pool inside the folded function itself -- "
                "which this mechanism cannot safely re-target by name"
            )
        outer_index = outer_name_to_index.get(target_name)
        if outer_index is None:
            raise SpliceError(
                f"{function_name}: folded relocation references {target_name!r}, "
                "which the outer object (compiled from the same file) has no "
                "symbol table entry for -- refusing to guess"
            )
        translated.append(
            elf32.Relocation(
                offset=lo + (rel.offset - ilo), sym_index=outer_index, type=rel.type
            )
        )

    for sec in outer.sections:
        if sec.type != elf32.SHT_REL or sec.info != text_index:
            continue
        # Preserve IDO's own relocation *table order* here -- do not sort by
        # r_offset. IDO emits .rel.text unsorted in most objects in this
        # repo, and GNU ld pairs a REL R_MIPS_HI16 with the *next
        # same-symbol R_MIPS_LO16 in table order*, not by offset; resorting
        # can therefore change which HI16 a LO16 pairs with for relocations
        # this splice never even touches. Confirmed on real objects in this
        # repo: re-sorting changes the decoded addend for real HI16/LO16
        # pairs in 229E0.o and 6DDA0.o (same %hi either way at today's
        # actual addresses, so it happens not to change the linked bytes
        # right now -- but it is not something to rely on for a symbol
        # whose address could fall differently relative to a page boundary
        # in the future). The function's own removed relocations are
        # replaced in place, at the table position they occupied, by the
        # folded replacements (also in their own original order) --
        # everything before and after that span keeps its original
        # position, just with r_offset shifted where the byte range moved.
        rebuilt: list[elf32.Relocation] = []
        inserted = False
        for rel in outer.relocations(sec.name):
            if lo <= rel.offset < hi:
                if not inserted:
                    rebuilt.extend(translated)
                    inserted = True
                continue  # this entry itself is replaced by `translated`
            if rel.offset >= hi:
                rel = elf32.Relocation(offset=rel.offset + delta, sym_index=rel.sym_index, type=rel.type)
            rebuilt.append(rel)
        if not inserted:
            # The replaced function had no relocations of its own in this
            # table at all (e.g. every operand became a literal immediate)
            # -- insert the new ones just before the first entry that now
            # sits at or after the fold point, keeping them in the same
            # relative table position the function itself occupies.
            insert_at = next((i for i, r in enumerate(rebuilt) if r.offset >= lo), len(rebuilt))
            rebuilt[insert_at:insert_at] = translated
        outer.set_relocations(sec.name, rebuilt)

    # Section-relative relocations -- e.g. a switch statement's jump table,
    # stored as R_MIPS_32 words in .rodata pointing at case labels in .text
    # -- carry no named symbol and no separate addend field (MIPS REL
    # relocations bake the addend into the referenced bytes themselves).
    # `.rel.text`'s own r_offset values are already finalized above; this
    # pass runs across every relocation section (not just ones aimed at
    # .text -- .rel.rodata's own r_offset never moves, since .rodata isn't
    # being resized here, but the *values* its relocations write into
    # .text-space still need the same delta) and rewrites any such target
    # that lands at or after the fold point.
    text_symbol_indices = {
        i for i, sym in enumerate(outer_symbols)
        if (sym.info & 0xF) == STT_SECTION and sym.shndx == text_index
    }
    if text_symbol_indices:
        _shift_section_relative_addends(outer, text_symbol_indices, lo, hi, delta, function_name)

    return elf32.build(outer)


def _classify(value: int, lo: int, hi: int) -> str:
    """Where a decoded .text-relative addend falls relative to the fold.

    ``"before"`` (< lo, unaffected by the splice -- left untouched) and
    ``"after"`` (>= hi, shifted by delta) are safe: the fold only replaces
    bytes in ``[lo, hi)``, so nothing outside that range moves except by a
    uniform amount. ``"inside"`` ([lo, hi), i.e. this addend points *into*
    the very bytes being replaced) is not safe: the fold changes in-function
    instruction offsets in a way this mechanism does not track (it only
    knows the *inner* object's own self-contained relocations, translated
    via ``splice_function``'s own logic elsewhere -- not arbitrary external
    references into the middle of the old body), so a target in this range
    must never be silently shifted *or* silently left alone.
    """
    if value < lo:
        return "before"
    if value < hi:
        return "inside"
    return "after"


def _shift_section_relative_addends(
    outer: elf32.Elf32Object,
    text_symbol_indices: set[int],
    lo: int,
    hi: int,
    delta: int,
    function_name: str,
) -> None:
    """Rewrite the implicit addend of every .text-section-relative relocation
    whose target is at or after ``hi``, in every relocation section, however
    far from ``.text`` its own bytes live. Refuses (raises SpliceError,
    never guesses) any such target that falls *inside* ``[lo, hi)`` -- e.g.
    a switch statement's own jump table, when the function being folded is
    itself the one containing the switch -- since the fold does not track
    how in-function offsets moved, only that the function's overall size
    changed.

    R_MIPS_HI16/R_MIPS_LO16 pairs are handled with the same "one active HI16
    per symbol, shared by every following LO16 until superseded" model real
    MIPS toolchains use for e.g. a shared ``lui`` feeding several stores to
    the same page -- exactly the shape this module's own fold produces
    elsewhere. A LO16 with no active HI16 for its symbol is refused. A
    *second* HI16 for the same symbol before any LO16 has consumed the
    first is also refused (rather than silently discarding the first one's
    correction) -- two independent %hi computations for the same base
    symbol (e.g. two array elements landing on different pages) is a real
    shape a compiler can emit, and guessing which of several pending HI16s
    a given LO16 pairs with is not something this module attempts.
    """
    for sec in outer.sections:
        if sec.type != elf32.SHT_REL:
            continue
        target_index = sec.info
        if target_index <= 0 or target_index >= len(outer.sections):
            continue
        target_section = outer.sections[target_index]
        data = bytearray(target_section.data)
        changed = False
        # sym_index -> {"off": hi r_offset, "field": original hi field, "used": bool}
        active_hi: dict[int, dict] = {}
        hi_decisions: dict[int, str] = {}  # hi r_offset -> classification already applied
        for rel in outer.relocations(sec.name):
            if rel.sym_index not in text_symbol_indices:
                continue
            off = rel.offset
            if rel.type == R_MIPS_32:
                if off + 4 > len(data):
                    continue
                value = struct.unpack_from(">I", data, off)[0]
                where = _classify(value, lo, hi)
                if where == "inside":
                    raise SpliceError(
                        f"{function_name}: an R_MIPS_32 relocation in "
                        f"{sec.name} targets {value:#x}, inside the "
                        f"function's own [{lo:#x}, {hi:#x}) range being "
                        "replaced -- e.g. this function's own jump table -- "
                        "refusing to splice a function whose in-function "
                        "layout this mechanism cannot re-target"
                    )
                if where == "after":
                    struct.pack_into(">I", data, off, (value + delta) & 0xFFFFFFFF)
                    changed = True
            elif rel.type == R_MIPS_26:
                if off + 4 > len(data):
                    continue
                word = struct.unpack_from(">I", data, off)[0]
                addend = (word & 0x03FFFFFF) << 2
                where = _classify(addend, lo, hi)
                if where == "inside":
                    raise SpliceError(
                        f"{function_name}: an R_MIPS_26 relocation in "
                        f"{sec.name} targets {addend:#x}, inside the "
                        f"function's own [{lo:#x}, {hi:#x}) range being "
                        "replaced -- refusing to splice a function whose "
                        "in-function layout this mechanism cannot re-target"
                    )
                if where == "after":
                    new_addend = addend + delta
                    word = (word & 0xFC000000) | ((new_addend >> 2) & 0x03FFFFFF)
                    struct.pack_into(">I", data, off, word)
                    changed = True
            elif rel.type == R_MIPS_HI16:
                if off + 4 > len(data):
                    continue
                pending = active_hi.get(rel.sym_index)
                if pending is not None and not pending["used"]:
                    raise SpliceError(
                        f"{function_name}: a second R_MIPS_HI16 for the "
                        f"same symbol appears in {sec.name} at offset "
                        f"{off:#x} before the one at {pending['off']:#x} "
                        "was paired with any R_MIPS_LO16 -- refusing to "
                        "guess which %lo(s) it belongs to"
                    )
                word = struct.unpack_from(">I", data, off)[0]
                active_hi[rel.sym_index] = {"off": off, "field": word & 0xFFFF, "used": False}
            elif rel.type == R_MIPS_LO16:
                if off + 4 > len(data):
                    continue
                pending = active_hi.get(rel.sym_index)
                if pending is None:
                    raise SpliceError(
                        f"{function_name}: an R_MIPS_LO16 relocation in "
                        f"{sec.name} targets the .text section with no "
                        "preceding R_MIPS_HI16 for it in the same table -- "
                        "refusing to guess its address"
                    )
                pending["used"] = True
                # `pending["field"]` always holds the HI16's *original*
                # field, never a rewritten one -- otherwise a second LO16
                # sharing this HI16 (the same shared-lui shape this
                # module's own fold produces) would have its addend
                # computed against an already-shifted hi, silently
                # corrupting an entry that didn't need shifting at all.
                hi_off, hi_field = pending["off"], pending["field"]
                lo_word = struct.unpack_from(">I", data, off)[0]
                lo_field = lo_word & 0xFFFF
                addend = (hi_field << 16) + _sign_extend16(lo_field)
                where = _classify(addend, lo, hi)
                if where == "inside":
                    raise SpliceError(
                        f"{function_name}: an R_MIPS_HI16/LO16 pair in "
                        f"{sec.name} targets {addend:#x}, inside the "
                        f"function's own [{lo:#x}, {hi:#x}) range being "
                        "replaced -- refusing to splice a function whose "
                        "in-function layout this mechanism cannot re-target"
                    )
                prior_decision = hi_decisions.get(hi_off)
                if prior_decision is not None and prior_decision != where:
                    raise SpliceError(
                        f"{function_name}: R_MIPS_HI16 at offset {hi_off:#x} "
                        f"in {sec.name} is shared by %lo relocations on both "
                        "sides of the fold point -- cannot rewrite it "
                        "consistently"
                    )
                hi_decisions[hi_off] = where
                if where == "after":
                    new_addend = addend + delta
                    new_hi_field = _hi16_field(new_addend)
                    new_lo_field = _lo16_field(new_addend)
                    hi_word = struct.unpack_from(">I", data, hi_off)[0]
                    struct.pack_into(">I", data, hi_off, (hi_word & 0xFFFF0000) | new_hi_field)
                    struct.pack_into(">I", data, off, (lo_word & 0xFFFF0000) | new_lo_field)
                    changed = True
        if changed:
            outer.set_section_data(target_section.name, bytes(data))


def _find_symbol_index(symbols, name: str, required_shndx: int | None):
    for i, symbol in enumerate(symbols):
        if symbol.name != name or symbol.shndx == elf32.SHN_UNDEF:
            continue
        if required_shndx is not None and symbol.shndx != required_shndx:
            continue
        return i
    return None


def splice_function_file(outer_path: Path, inner_path: Path, function_name: str) -> bytes:
    return splice_function(
        Path(outer_path).read_bytes(), Path(inner_path).read_bytes(), function_name
    )
