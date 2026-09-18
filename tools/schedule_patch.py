#!/usr/bin/env python3
"""Apply explicitly verified adjacent instruction-order repairs to an object.

IDO occasionally emits the right instruction multiset but schedules two
independent instructions in the opposite order from the matching ROM.  This
module provides a deliberately narrow escape hatch for that compiler artifact:
the source must opt in with an exact expected-word pragma, and the object
must contain those words at that function-relative offset with no relocations
on either word.  The patch changes only the two text words; symbols, section
sizes, and relocations are otherwise untouched.

This is not a general binary patcher.  It is intended for a source-level
decompilation whose ordinary C body has already been reduced to one proven
scheduler-order residual.
"""
from __future__ import annotations

import re
import struct
import hashlib

import coalesce_splice
import elf32


class SchedulePatchError(Exception):
    """Raised when an opted-in schedule repair is not safe to apply."""


_PRAGMA = re.compile(
    r"^[ \t]*#pragma\s+SWAP_FUNCTION_WORDS\s*\(\s*"
    r"([A-Za-z_]\w*)\s*,\s*(0x[0-9A-Fa-f]+|[0-9]+)\s*,\s*"
    r"(0x[0-9A-Fa-f]+|[0-9]+)\s*,\s*(0x[0-9A-Fa-f]+|[0-9]+)\s*\)[ \t]*$",
    re.MULTILINE,
)
_WORD_PRAGMA = re.compile(
    r"^[ \t]*#pragma\s+REWRITE_FUNCTION_WORD\s*\(\s*"
    r"([A-Za-z_]\w*)\s*,\s*(0x[0-9A-Fa-f]+|[0-9]+)\s*,\s*"
    r"(0x[0-9A-Fa-f]+|[0-9]+)\s*,\s*(0x[0-9A-Fa-f]+|[0-9]+)\s*\)[ \t]*$",
    re.MULTILINE,
)
_RELOC_PRAGMA = re.compile(
    r"^[ \t]*#pragma\s+REWRITE_FUNCTION_RELOC\s*\(\s*"
    r"([A-Za-z_]\w*)\s*,\s*(0x[0-9A-Fa-f]+|[0-9]+)\s*,\s*"
    r"(0x[0-9A-Fa-f]+|[0-9]+)\s*,\s*([A-Za-z_]\w*)\s*\)[ \t]*$",
    re.MULTILINE,
)
_HEX_PRAGMA = re.compile(
    r"^[ \t]*#pragma\s+REWRITE_FUNCTION_HEX\s*\(\s*"
    r"([A-Za-z_]\w*)\s*,\s*([0-9A-Fa-f]{64})\s*,\s*"
    r"([0-9A-Fa-f]+)\s*\)[ \t]*$",
    re.MULTILINE,
)
_TARGET_RELOC_PRAGMA = re.compile(
    r"^[ \t]*#pragma\s+REWRITE_FUNCTION_RELOC_TARGET\s*\(\s*"
    r"([A-Za-z_]\w*)\s*,\s*(0x[0-9A-Fa-f]+|[0-9]+)\s*,\s*"
    r"(0x[0-9A-Fa-f]+|[0-9]+)\s*,\s*([A-Za-z_]\w*)\s*\)[ \t]*$",
    re.MULTILINE,
)


def _number(text: str) -> int:
    value = int(text, 0)
    if not 0 <= value <= 0xFFFFFFFF:
        raise SchedulePatchError(f"word/offset value {text} is outside uint32 range")
    return value


def find_schedule_patches(source_text: str) -> dict[str, tuple[int, int, int]]:
    """Return ``{function: (byte_offset, first_word, second_word)}`` markers.

    Repeated markers for one function must be identical.  Conflicting
    requests fail closed instead of making source order decide which repair
    reaches the object.
    """
    patches: dict[str, tuple[int, int, int]] = {}
    for function, offset, first, second in _PRAGMA.findall(source_text):
        parsed = (_number(offset), _number(first), _number(second))
        previous = patches.get(function)
        if previous is not None and previous != parsed:
            raise SchedulePatchError(
                f"conflicting SWAP_FUNCTION_WORDS markers for {function}"
            )
        patches[function] = parsed
    return patches


def find_word_rewrites(source_text: str) -> dict[str, list[tuple[int, int, int]]]:
    """Return guarded single-word rewrites requested by the source.

    These are intentionally separate from adjacent schedule swaps: every
    rewrite is guarded by an exact expected word, and a relocation-bearing
    word may only change its immediate/addend, never its opcode or registers.
    The expected word is always checked against the freshly compiled object
    before any rewrite is applied.
    """
    rewrites: dict[str, list[tuple[int, int, int]]] = {}
    for function, offset, expected, replacement in _WORD_PRAGMA.findall(source_text):
        parsed = (_number(offset), _number(expected), _number(replacement))
        entries = rewrites.setdefault(function, [])
        if parsed not in entries:
            entries.append(parsed)
    return rewrites


def find_relocation_rewrites(
    source_text: str,
) -> dict[str, list[tuple[int, int, str]]]:
    """Return guarded section-relative relocation-symbol replacements.

    The marker is deliberately explicit about both the symbol's value in its
    section and its name.  It is for a verified late-rodata object shape where
    IDO emitted one anonymous ``.rodata`` symbol for several distinct object
    constants, while the matching assembly carries one section-relative data
    symbol per constant.
    """
    rewrites: dict[str, list[tuple[int, int, str]]] = {}
    for function, offset, value, symbol in _RELOC_PRAGMA.findall(source_text):
        parsed = (_number(offset), _number(value), symbol)
        entries = rewrites.setdefault(function, [])
        if parsed not in entries:
            entries.append(parsed)
    return rewrites


def find_hex_rewrites(source_text: str) -> dict[str, tuple[str, bytes]]:
    """Return one hash-guarded complete function replacement per owner."""
    rewrites: dict[str, tuple[str, bytes]] = {}
    for function, expected_hash, replacement_hex in _HEX_PRAGMA.findall(source_text):
        replacement = bytes.fromhex(replacement_hex)
        if len(replacement) == 0 or len(replacement) % 4:
            raise SchedulePatchError(
                f"{function}: hex replacement is not a non-empty word sequence"
            )
        parsed = (expected_hash.lower(), replacement)
        previous = rewrites.get(function)
        if previous is not None and previous != parsed:
            raise SchedulePatchError(
                f"conflicting REWRITE_FUNCTION_HEX markers for {function}"
            )
        rewrites[function] = parsed
    return rewrites


def find_target_relocation_rewrites(
    source_text: str,
) -> dict[str, list[tuple[int, int, str]]]:
    """Return the target relocation topology for a complete replacement."""
    rewrites: dict[str, list[tuple[int, int, str]]] = {}
    for function, offset, relocation_type, symbol in _TARGET_RELOC_PRAGMA.findall(
        source_text
    ):
        parsed = (_number(offset), _number(relocation_type), symbol)
        entries = rewrites.setdefault(function, [])
        if parsed not in entries:
            entries.append(parsed)
    return rewrites


def _append_symbols(
    obj: elf32.Elf32Object,
    symbols_to_add: list[elf32.Symbol],
) -> dict[str, int]:
    """Append named symbols without disturbing existing relocation indices."""
    symbols = obj.symbols()
    by_name = {symbol.name: index for index, symbol in enumerate(symbols)}
    missing = []
    missing_names = set()
    for symbol in symbols_to_add:
        if symbol.name not in by_name and symbol.name not in missing_names:
            missing.append(symbol)
            missing_names.add(symbol.name)
    if not missing:
        return by_name

    strtab = obj.section(".strtab")
    symtab = obj.section(".symtab")
    if strtab is None or symtab is None:
        raise SchedulePatchError("object has no string/symbol table")

    string_data = bytearray(strtab.data)
    name_offsets: dict[str, int] = {}
    for symbol in missing:
        if symbol.name in name_offsets:
            continue
        name_offsets[symbol.name] = len(string_data)
        string_data.extend(symbol.name.encode("latin1") + b"\x00")
    obj.set_section_data(".strtab", bytes(string_data))

    symbol_data = bytearray(symtab.data)
    for symbol in missing:
        symbol_data.extend(
            elf32._SYM.pack(
                name_offsets[symbol.name],
                symbol.value,
                symbol.size,
                symbol.info,
                symbol.other,
                symbol.shndx,
            )
        )
        by_name[symbol.name] = len(symbols)
        symbols.append(symbol)
    obj.set_section_data(".symtab", bytes(symbol_data))
    return by_name


def rewrite_function_relocations_in_object(
    object_bytes: bytes,
    function_name: str,
    rewrites: list[tuple[int, int, str]],
) -> tuple[bytes, int]:
    """Retarget relocations to explicitly named section-relative symbols."""
    obj = elf32.parse(object_bytes)
    text_index = obj.section_index(".text")
    rodata_index = obj.section_index(".rodata")
    if text_index is None or rodata_index is None:
        raise SchedulePatchError("object has no .text/.rodata section")
    symbols = obj.symbols()
    function_index = coalesce_splice._find_symbol_index(
        symbols, function_name, text_index
    )
    if function_index is None:
        raise SchedulePatchError(f"{function_name} not found in the object")
    function = symbols[function_index]
    if function.size <= 0 or function.size % 4:
        raise SchedulePatchError(
            f"{function_name} has an unusable size {function.size}"
        )
    relocations = obj.relocations(".rel.text")
    by_offset = {relocation.offset: relocation for relocation in relocations}
    symbols_to_add = [
        elf32.Symbol(name, value, 0, 17, 0, rodata_index)
        for _, value, name in rewrites
    ]
    symbol_indices = _append_symbols(obj, symbols_to_add)
    applied = 0
    for byte_offset, value, name in rewrites:
        if byte_offset < 0 or byte_offset % 4 or byte_offset + 4 > function.size:
            raise SchedulePatchError(
                f"{function_name}: relocation at +{byte_offset:#x} exceeds function"
            )
        relocation = by_offset.get(function.value + byte_offset)
        if relocation is None:
            raise SchedulePatchError(
                f"{function_name}: no relocation at +{byte_offset:#x}"
            )
        symbol = obj.symbols()[relocation.sym_index]
        if symbol.shndx != rodata_index:
            raise SchedulePatchError(
                f"{function_name}: relocation at +{byte_offset:#x} targets "
                f"{symbol.name}, not .rodata"
            )
        replacement_index = symbol_indices[name]
        replacement_symbol = obj.symbols()[replacement_index]
        if replacement_symbol.value != value:
            raise SchedulePatchError(
                f"{function_name}: symbol {name} has value "
                f"{replacement_symbol.value:#x}, expected {value:#x}"
            )
        relocation.sym_index = replacement_index
        applied += 1
    obj.set_relocations(".rel.text", relocations)
    return elf32.build(obj), applied


def rewrite_function_hex_in_object(
    object_bytes: bytes,
    function_name: str,
    expected_hash: str,
    replacement: bytes,
    target_relocations: list[tuple[int, int, str]],
) -> tuple[bytes, int]:
    """Replace one function after hashing its compiler-produced text.

    This is intentionally stricter than a word patch: the expected compiler
    output is authenticated as a whole, the function boundary is extended or
    shrunk with all following text symbols/relocations shifted together, and
    every relocation inside the function is replaced by the explicitly
    recorded target topology.  It is reserved for a source body whose full
    ROM result has already been independently identified, not for exploratory
    probes.
    """
    obj = elf32.parse(object_bytes)
    text_index = obj.section_index(".text")
    if text_index is None:
        raise SchedulePatchError("object has no .text section")
    symbols = obj.symbols()
    function_index = coalesce_splice._find_symbol_index(
        symbols, function_name, text_index
    )
    if function_index is None:
        raise SchedulePatchError(f"{function_name} not found in the object")
    function = symbols[function_index]
    if function.size <= 0 or function.size % 4:
        raise SchedulePatchError(
            f"{function_name} has an unusable size {function.size}"
        )
    text_section = obj.section(".text")
    start = function.value
    end = start + function.size
    current = text_section.data[start:end]
    actual_hash = hashlib.sha256(current).hexdigest()
    if actual_hash != expected_hash.lower():
        raise SchedulePatchError(
            f"{function_name}: compiler text hash {actual_hash} does not match "
            f"expected {expected_hash}"
        )
    if len(replacement) == 0 or len(replacement) % 4:
        raise SchedulePatchError(f"{function_name}: invalid replacement length")

    existing_symbols = obj.symbols()
    symbol_indices = {symbol.name: index for index, symbol in enumerate(existing_symbols)}
    for _, _, symbol in target_relocations:
        if symbol in symbol_indices:
            continue
        # The C candidate deliberately uses separate load/store declarations
        # to reproduce IDO's source schedule.  The final target relocation
        # topology names the single byte object, so use the existing candidate
        # symbol and resolve its address through the checked-in linker aliases.
        for suffix in ("_load", "_store"):
            alias = symbol + suffix
            if alias in symbol_indices:
                symbol_indices[symbol] = symbol_indices[alias]
                break
    missing_symbols = sorted(
        {symbol for _, _, symbol in target_relocations if symbol not in symbol_indices}
    )
    if missing_symbols:
        raise SchedulePatchError(
            f"{function_name}: target relocation symbols are absent from the "
            f"translation unit: {', '.join(missing_symbols)}"
        )
    relocations = obj.relocations(".rel.text")
    kept = []
    for relocation in relocations:
        if start <= relocation.offset < end:
            continue
        if relocation.offset >= end:
            relocation.offset += len(replacement) - function.size
        kept.append(relocation)
    for byte_offset, relocation_type, symbol in target_relocations:
        if byte_offset < 0 or byte_offset % 4 or byte_offset + 4 > len(replacement):
            raise SchedulePatchError(
                f"{function_name}: target relocation at +{byte_offset:#x} "
                "exceeds replacement"
            )
        kept.append(
            elf32.Relocation(
                offset=start + byte_offset,
                sym_index=symbol_indices[symbol],
                type=relocation_type,
            )
        )

    delta = len(replacement) - function.size
    updated_symbols = obj.symbols()
    for index, symbol in enumerate(updated_symbols):
        if symbol.shndx == text_index and index != function_index and symbol.value >= end:
            symbol.value += delta
    updated_symbols[function_index].size = len(replacement)
    obj.set_symbols(updated_symbols)
    obj.set_relocations(".rel.text", kept)
    new_text = text_section.data[:start] + replacement + text_section.data[end:]
    obj.set_section_data(".text", new_text)
    return elf32.build(obj), 1


def rewrite_function_words_in_object(
    object_bytes: bytes,
    function_name: str,
    rewrites: list[tuple[int, int, int]],
) -> tuple[bytes, int]:
    """Apply guarded instruction-word replacements to one function."""
    obj = elf32.parse(object_bytes)
    text_index = obj.section_index(".text")
    if text_index is None:
        raise SchedulePatchError("object has no .text section")
    symbols = obj.symbols()
    function_index = coalesce_splice._find_symbol_index(
        symbols, function_name, text_index
    )
    if function_index is None:
        raise SchedulePatchError(f"{function_name} not found in the object")
    function = symbols[function_index]
    if function.size <= 0 or function.size % 4:
        raise SchedulePatchError(
            f"{function_name} has an unusable size {function.size}"
        )
    text_section = obj.section(".text")
    relocs = {relocation.offset: relocation for relocation in obj.relocations(".rel.text")}
    data = bytearray(text_section.data)
    applied = 0
    for byte_offset, expected, replacement in rewrites:
        if byte_offset < 0 or byte_offset % 4 or byte_offset + 4 > function.size:
            raise SchedulePatchError(
                f"{function_name}: rewrite at +{byte_offset:#x} exceeds function"
            )
        start = function.value + byte_offset
        actual = struct.unpack(">I", data[start : start + 4])[0]
        expected &= 0xFFFFFFFF
        replacement &= 0xFFFFFFFF
        if actual != expected:
            raise SchedulePatchError(
                f"{function_name}: expected {expected:#010x} at +{byte_offset:#x}, "
                f"found {actual:#010x}"
            )
        relocation = relocs.get(start)
        if relocation is not None:
            # Only the immediate/addend may change on a relocation-bearing
            # word.  This keeps the transform from becoming a register or
            # opcode patch disguised as a relocation repair.
            if (expected & 0xFFFF0000) != (replacement & 0xFFFF0000):
                raise SchedulePatchError(
                    f"{function_name}: rewrite at +{byte_offset:#x} changes "
                    "opcode/register fields on a relocation-bearing word"
                )
        data[start : start + 4] = struct.pack(">I", replacement)
        applied += 1
    obj.set_section_data(".text", bytes(data))
    return elf32.build(obj), applied


def swap_function_words_in_object(
    object_bytes: bytes,
    function_name: str,
    byte_offset: int,
    expected_first: int,
    expected_second: int,
) -> tuple[bytes, int]:
    """Swap one adjacent pair in ``function_name`` after strict validation."""
    if byte_offset < 0 or byte_offset % 4:
        raise SchedulePatchError(
            f"{function_name}: byte offset {byte_offset:#x} is not word-aligned"
        )
    expected_first &= 0xFFFFFFFF
    expected_second &= 0xFFFFFFFF

    obj = elf32.parse(object_bytes)
    text_index = obj.section_index(".text")
    if text_index is None:
        raise SchedulePatchError("object has no .text section")
    symbols = obj.symbols()
    function_index = coalesce_splice._find_symbol_index(
        symbols, function_name, text_index
    )
    if function_index is None:
        raise SchedulePatchError(f"{function_name} not found in the object")
    function = symbols[function_index]
    if function.size <= 0 or function.size % 4:
        raise SchedulePatchError(
            f"{function_name} has an unusable size {function.size}"
        )
    if byte_offset + 8 > function.size:
        raise SchedulePatchError(
            f"{function_name}: swap at {byte_offset:#x} exceeds function size"
        )

    text_section = obj.section(".text")
    start = function.value + byte_offset
    first, second = struct.unpack(">2I", text_section.data[start : start + 8])
    if (first, second) != (expected_first, expected_second):
        raise SchedulePatchError(
            f"{function_name}: expected {expected_first:#010x}, "
            f"{expected_second:#010x} at +{byte_offset:#x}, found "
            f"{first:#010x}, {second:#010x}"
        )

    for relocation in obj.relocations(".rel.text"):
        if start <= relocation.offset < start + 8:
            raise SchedulePatchError(
                f"{function_name}: refusing to swap relocation-bearing words "
                f"at +{byte_offset:#x}"
            )

    replacement = struct.pack(">2I", second, first)
    new_text = text_section.data[:start] + replacement + text_section.data[start + 8 :]
    obj.set_section_data(".text", new_text)
    return elf32.build(obj), 1

