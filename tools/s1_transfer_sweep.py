#!/usr/bin/env python3
"""Transplant finished Stadium 1 C bodies onto matching Stadium 2 pragmas.

``tools/s1_transfer.json`` (built by ``xmatch_stadium1.py``) maps a GS
``func_XXXXXXXX`` to a named Stadium 1 (S1) function by machine-code match.
When that S1 function already has a finished C body in the S1 decomp tree
(rather than still being a ``GLOBAL_ASM`` stub there), the S1 source --
compiled by the same IDO 7.1 -- is a very strong first candidate for the GS
pragma.  This tool:

  1. resolves the S1 function named in the transfer evidence and pulls its
     C body out of the S1 tree by brace matching;
  2. aligns the GS ``.s`` instruction words against the S1 ROM's words for
     that function (same normalised shape required by ``xmatch_stadium1``);
  3. decodes, from the aligned S1 machine words, which S1 global each
     ``jal``/``%hi``/``%lo`` in the GS assembly refers to, and pairs that
     with the GS operand's own symbol name (already spelled out in the
     ``.s`` file) to build an S1-name -> GS-name rename table;
  4. pulls in any S1 struct/typedef/enum the body needs, S1_-prefixed so it
     never collides with a GS type of the same name;
  5. renames the S1 body (word-boundary substitution) and hands it to the
     existing candidate runner -- never writes tracked sources itself.

``--near-matches`` runs a looser variant of the same pipeline for pragmas
that have no exact S1 transfer entry: it ranks Stadium 1 bodies of the
identical instruction count by normalised similarity and, above
``--near-min-similarity``, transfers the best one the same way (labelled
``s1-near:<S1 name>:<score>`` rather than ``s1:transfer``).

Usage:
    tools/s1_transfer_sweep.py --dry-run --limit 15
    tools/s1_transfer_sweep.py --dry-run --function func_800015C0
    tools/s1_transfer_sweep.py --limit 50 --json build/s1_transfer.json
    tools/s1_transfer_sweep.py --no-gate --source disasm/src/229E0.c
    tools/s1_transfer_sweep.py --near-matches --dry-run --limit 50

Sources with uncommitted changes are skipped, mirroring ``sweep_targets``:
another session may be mid-transaction in them.

This worktree's ``disasm/asm/us/nonmatchings`` tree may not be fully
extracted (splat has not been run here).  When a GS ``.s`` file the GS
pragma needs is missing locally, this tool falls back to *reading* (never
writing) the same path from the sibling checkout this worktree was branched
from, guessed by stripping ``-wt-*`` from this repo's directory name, or
overridden with ``--gs-asm-fallback``.  Pass ``--no-gs-asm-fallback`` to
disable this and treat a missing local ``.s`` as ``gs_asm_missing``.
"""

from __future__ import annotations

import argparse
import bisect
import collections
import json
import os
import re
import sys
import time
from dataclasses import dataclass, field
from pathlib import Path
from typing import Callable, Iterable

import dedupe_externs
import pragma_targets as targets
import try_pragma_compare as runner
import xmatch_stadium1 as xmatch

REPO_ROOT = targets.REPO_ROOT
S1_TRANSFER_PATH = REPO_ROOT / "tools" / "s1_transfer.json"
GS_INCLUDE_ROOT = REPO_ROOT / "disasm" / "include"
GS_ULTRALIB_INCLUDE_ROOT = REPO_ROOT / "disasm" / "lib" / "ultralib" / "include"
GS_YAML_PATH = REPO_ROOT / "disasm" / "yamls" / "us" / "rom.yaml"
GS_SRC_ROOT = REPO_ROOT / "disasm" / "src"
GS_LINKER_SCRIPTS_ROOT = REPO_ROOT / "disasm" / "linker_scripts" / "us"

EVIDENCE_RE = re.compile(r"Stadium 1 (\S+) @ 0x([0-9A-Fa-f]+)")

CONTROL_KEYWORDS = {
    "if", "for", "while", "switch", "return", "sizeof", "else", "do",
    "goto", "case", "default", "break", "continue",
}

# Type names IDO's own C89 front end (and libultra's own headers) already
# know without any declaration of ours -- an extern naming anything outside
# this set (plus whatever a GS header defines, plus whatever S1_-prefixed
# type this run itself emits) cannot possibly compile.
_BUILTIN_C_TYPES = {
    "u8", "s8", "u16", "s16", "u32", "s32", "u64", "s64", "f32", "f64",
    "void", "char", "int", "short", "long", "float", "double",
    "unsigned", "signed", "size_t", "ssize_t", "uintptr_t", "intptr_t",
}


# --------------------------------------------------------------------------
# GS .s parsing
# --------------------------------------------------------------------------

_LINE_RE = re.compile(
    r"^\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s*\*/\s*(\S+)\s*(.*?)\s*$"
)
_HI_RE = re.compile(r"%hi\((\w+)\)")
_LO_RE = re.compile(r"%lo\((\w+)\)")


@dataclass(frozen=True)
class SourceInstr:
    index: int
    vram: int
    word: int
    mnemonic: str
    operands: str
    hi_sym: str | None = None
    lo_sym: str | None = None
    jal_sym: str | None = None


@dataclass(frozen=True)
class ParsedAsm:
    """A splat ``.s`` disassembly, one entry per instruction plus the raw words.

    ``words`` is exactly ``[i.word for i in instructions]``, kept alongside
    for the many call sites (alignment, address decoding) that only care
    about the machine words and not the per-instruction symbol operands.
    """
    instructions: list[SourceInstr]
    words: list[int]


def parse_gs_asm(text: str) -> ParsedAsm:
    """Parse a splat ``.s`` disassembly into one entry per instruction.

    Only lines carrying the ``/* offset vram word */`` comment are
    instructions; ``glabel``/``.L...:`` lines are skipped, which is exactly
    what distinguishes a label from code here.  Generic over any splat
    ``.s`` file -- nothing here is specific to GS or to a transfer source.
    """
    out: list[SourceInstr] = []
    index = 0
    for line in text.splitlines():
        match = _LINE_RE.match(line)
        if not match:
            continue
        vram = int(match.group(1), 16)
        word = int(match.group(2), 16)
        mnemonic = match.group(3)
        operands = match.group(4)
        hi = _HI_RE.search(operands)
        lo = _LO_RE.search(operands)
        jal_sym = None
        if mnemonic in ("jal", "j"):
            candidate = operands.split(",")[0].strip()
            if re.fullmatch(r"[A-Za-z_]\w*", candidate):
                jal_sym = candidate
        out.append(SourceInstr(
            index=index, vram=vram, word=word, mnemonic=mnemonic,
            operands=operands,
            hi_sym=hi.group(1) if hi else None,
            lo_sym=lo.group(1) if lo else None,
            jal_sym=jal_sym,
        ))
        index += 1
    return ParsedAsm(instructions=out, words=[instr.word for instr in out])


# --------------------------------------------------------------------------
# Address decoding from aligned machine words
# --------------------------------------------------------------------------

def decode_jal_target(word: int) -> int:
    """Absolute call target of a ``jal``/``j`` word (top nibble is fixed by convention)."""
    return ((word & 0x03FFFFFF) << 2) | 0x80000000


def decode_hilo_address(hi_word: int, lo_word: int) -> int:
    """Combine a ``lui`` word and the word carrying its paired ``%lo`` immediate."""
    hi16 = hi_word & 0xFFFF
    lo16 = lo_word & 0xFFFF
    if lo16 & 0x8000:
        lo16 -= 0x10000
    return ((hi16 << 16) + lo16) & 0xFFFFFFFF


def decode_targets(
    words: list[int],
    *,
    jal_indices: Iterable[int] = (),
    hilo_pairs: Iterable[tuple[int, int]] = (),
) -> dict[int, int]:
    """Decode call targets and ``%hi``/``%lo`` pairs out of ``words``.

    ``jal_indices`` are indices of ``jal``/``j`` words, decoded directly.
    ``hilo_pairs`` are ``(hi_index, lo_index)`` -- the index of the word
    carrying the ``%hi`` half and the index of the word carrying its paired
    ``%lo`` half -- combined into one address.  Returns ``{index ->
    address}``, keyed by the ``%lo`` index for a hi/lo pair so the result
    lines up with the operand that actually names the symbol.  Generic over
    whose words these are: pass a GS instruction's own words to decode what
    it targets, or another program's words at the same indices (as
    ``decode_s1_addresses`` does) to decode what that instruction encodes
    over there.
    """
    out: dict[int, int] = {}
    for i in jal_indices:
        if 0 <= i < len(words):
            out[i] = decode_jal_target(words[i])
    for hi_index, lo_index in hilo_pairs:
        if 0 <= hi_index < len(words) and 0 <= lo_index < len(words):
            out[lo_index] = decode_hilo_address(words[hi_index], words[lo_index])
    return out


@dataclass
class AddressDecodeResult:
    addresses: dict[int, int]          # gs instruction index -> decoded address
    unresolved: list[int]              # indices with a symbol operand we could not decode


def decode_s1_addresses(gs_instrs: list[SourceInstr], s1_words: list[int]) -> AddressDecodeResult:
    """Decode, per GS instruction with a symbol operand, the S1 address it targets.

    ``jal``/``j`` decode directly.  ``%hi``/``%lo`` decode by pairing on the
    GS operand's *symbol name*, not on which register holds it: the GS
    ``.s`` already spells the same symbol on both the ``%hi`` and the
    ``%lo`` line, so the nearest preceding ``%hi`` naming the same symbol as
    a given ``%lo`` is its partner, however many registers the value moved
    through in between (a ``move``/``addu $reg, $reg, $zero`` copy of the
    base no longer breaks the pairing, since the copy's destination
    register is never consulted).  The pairing stays live across several
    ``%lo`` consumers of the same symbol, so a ``%hi`` is not used up on
    first use.
    """
    unresolved: list[int] = []
    jal_indices: list[int] = []
    hilo_pairs: list[tuple[int, int]] = []
    pending_hi: dict[str, int] = {}  # symbol name -> gs index of the %hi instruction
    for instr in gs_instrs:
        if instr.index >= len(s1_words):
            continue
        if instr.jal_sym is not None:
            jal_indices.append(instr.index)
            continue
        if instr.hi_sym is not None:
            pending_hi[instr.hi_sym] = instr.index
        if instr.lo_sym is not None:
            hi_index = pending_hi.get(instr.lo_sym)
            if hi_index is None:
                unresolved.append(instr.index)
                continue
            hilo_pairs.append((hi_index, instr.index))
    addresses = decode_targets(s1_words, jal_indices=jal_indices, hilo_pairs=hilo_pairs)
    return AddressDecodeResult(addresses=addresses, unresolved=unresolved)


# --------------------------------------------------------------------------
# Loose alignment (for a near-match transfer, where bodies are not byte-identical)
# --------------------------------------------------------------------------

def _opcode_class(word: int) -> tuple[int, ...]:
    """Coarse instruction classification for a loose alignment check.

    The raw 6-bit opcode, further split by the function field for SPECIAL
    (opcode 0) so unrelated register-only ops (``add`` vs ``sub``, say) are
    not treated as interchangeable just because neither carries a
    relocation.
    """
    op = word >> 26
    if op == 0:
        return (0, word & 0x3F)
    return (op,)


def _is_reloc_bearing(word: int) -> bool:
    """True for any opcode class that is not a register-only SPECIAL/COPz op.

    Mirrors ``xmatch.norm``'s own classification: everything else either
    carries a jump/branch target, a ``lui`` high half, or an immediate that
    might encode part of an address.
    """
    op = word >> 26
    return op not in (0, 0x10, 0x11)


@dataclass(frozen=True)
class Alignment:
    """Result of positionally aligning two equal-length instruction-word lists."""
    length: int
    strict: bool
    ok: bool
    first_mismatch: int | None = None


def align_words(gs_words: list[int], other_words: list[int], *, strict: bool) -> Alignment | None:
    """Positionally align two same-length instruction-word lists.

    Returns ``None`` only when the lengths differ -- there is no
    position-by-position alignment to report in that case.  Otherwise
    always returns an ``Alignment``; check ``.ok`` (and, on failure,
    ``.first_mismatch``) rather than treating a non-``None`` result as
    success.

    ``strict=True`` requires every masked (relocation-normalised) word to
    agree -- the verbatim-transfer comparison ``xmatch`` calls "identical".
    ``strict=False`` (a near-match transfer, where the two bodies come from
    independently compiled, merely similar sources) instead requires only
    that every instruction carrying a relocatable operand land on an
    instruction of the same opcode class in the other list, so a rename map
    built from the pairing is still trustworthy even though the bodies are
    not byte-identical.
    """
    if len(gs_words) != len(other_words):
        return None
    for i, (g, o) in enumerate(zip(gs_words, other_words)):
        if strict:
            if xmatch.norm(g) != xmatch.norm(o):
                return Alignment(length=len(gs_words), strict=True, ok=False, first_mismatch=i)
            continue
        if (_is_reloc_bearing(g) or _is_reloc_bearing(o)) and _opcode_class(g) != _opcode_class(o):
            return Alignment(length=len(gs_words), strict=False, ok=False, first_mismatch=i)
    return Alignment(length=len(gs_words), strict=strict, ok=True)


# --------------------------------------------------------------------------
# S1 symbol tables
# --------------------------------------------------------------------------

_ALL_SYM_RE = re.compile(r"^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;(.*)$")

# A containment match (address falls inside a symbol's span rather than at
# its start) is only trusted within this many bytes: past that, matching the
# nearest preceding symbol is more likely wrong than useful.
_MAX_CONTAINMENT_SPAN = 0x2000


@dataclass
class S1SymbolTable:
    all_by_addr: dict[int, str]
    func_by_addr: dict[int, str]
    sorted_addrs: list[int]
    names: set[str]
    func_names: set[str]


def load_s1_symbols(s1_root: Path) -> S1SymbolTable:
    s1d = s1_root / "disasm"
    # ``symbol_addrs_ultralib.txt`` is entirely ultralib function symbols
    # (tagged ``defined:true``, not ``type:func``), so every entry from it
    # counts as a function; the other two files mix functions and data and
    # rely on the ``type:func``/``func_<addr>`` tag.
    paths = [
        (s1_root / "disasm" / "linker_scripts" / "us" / "symbol_addrs.txt", False),
        (s1d / "linker_scripts" / "us" / "symbol_addrs_code.txt", False),
        (s1d / "linker_scripts" / "us" / "symbol_addrs_ultralib.txt", True),
    ]
    all_by_addr: dict[int, str] = {}
    func_by_addr: dict[int, str] = {}
    for path, all_functions in paths:
        if not path.exists():
            continue
        for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
            match = _ALL_SYM_RE.match(line)
            if not match:
                continue
            name, addr_text, rest = match.group(1), match.group(2), match.group(3)
            addr = int(addr_text, 16)
            all_by_addr.setdefault(addr, name)
            if all_functions or "type:func" in rest or re.fullmatch(r"func_[0-9A-Fa-f]{6,8}", name):
                func_by_addr.setdefault(addr, name)
    return S1SymbolTable(
        all_by_addr=all_by_addr,
        func_by_addr=func_by_addr,
        sorted_addrs=sorted(all_by_addr),
        names=set(all_by_addr.values()),
        func_names=set(func_by_addr.values()),
    )


def resolve_s1_symbol(
    symtab: S1SymbolTable, addr: int, *, is_call: bool, body_identifiers: set[str] | None = None
) -> tuple[str, int] | None:
    """Return ``(name, offset)`` for the S1 symbol occupying ``addr``.

    ``symbol_addrs*.txt`` is a curated *override* list, not a full symbol
    table: it holds names splat could not derive on its own.  A symbol
    splat auto-names from its own address (``D_<ADDR>`` / ``func_<ADDR>``)
    is never listed there, so an exact-address miss falls back to that
    synthesized spelling -- accepted only when it is actually the spelling
    the S1 body uses, per ``body_identifiers``, so a genuinely unresolved
    address is still reported rather than guessed.

    Functions must land exactly on a symbol.  Data may fall inside a
    symbol's range; the caller decides whether a nonzero offset is still
    safe to rename.
    """
    exact = symtab.all_by_addr.get(addr)
    if exact is not None:
        return (exact, 0)
    if is_call:
        synthesized = f"func_{addr:08X}"
        if body_identifiers is not None and synthesized in body_identifiers:
            return (synthesized, 0)
        return None
    index = bisect.bisect_right(symtab.sorted_addrs, addr) - 1
    if index >= 0:
        base = symtab.sorted_addrs[index]
        offset = addr - base
        if offset <= _MAX_CONTAINMENT_SPAN:
            return (symtab.all_by_addr[base], offset)
    synthesized = f"D_{addr:08X}"
    if body_identifiers is not None and synthesized in body_identifiers:
        return (synthesized, 0)
    return None


def make_symbol_lookup(
    symtab: S1SymbolTable, body_identifiers: set[str]
) -> Callable[[int], str | None]:
    """Bind ``resolve_s1_symbol`` into the single-argument shape ``build_rename_map`` wants.

    Tries an exact-address match first (valid whether the address came from
    a call or a data reference), then the ``func_<ADDR>``/``D_<ADDR>``
    synthesized spellings splat would have used, in that order.  Returns a
    name only when it is safe to substitute at offset 0; a containment
    match at a nonzero offset is deliberately not returned, since renaming
    the base symbol there would be wrong.
    """
    def lookup(addr: int) -> str | None:
        for is_call in (True, False):
            resolved = resolve_s1_symbol(symtab, addr, is_call=is_call, body_identifiers=body_identifiers)
            if resolved is not None and resolved[1] == 0:
                return resolved[0]
        return None
    return lookup


# --------------------------------------------------------------------------
# Comment stripping
# --------------------------------------------------------------------------

def strip_comments(text: str) -> str:
    """Remove ``//`` and ``/* */`` comments, honoring string/char literals.

    Each comment is replaced by a single space so the tokens on either side
    of it never fuse together (``int/*x*/y`` must not become ``inty``); a
    block comment's internal newlines are collapsed away with it, which a C
    compiler does not care about.  Used to keep comment text -- which can
    carry non-ASCII bytes, or an identifier that happens to collide with a
    rename map, or per-caller wording that makes two occurrences of the
    same struct fail to look identical to each other -- out of every piece
    of C this tool emits.
    """
    out: list[str] = []
    index = 0
    length = len(text)
    in_string: str | None = None
    while index < length:
        char = text[index]
        if in_string:
            out.append(char)
            if char == "\\" and index + 1 < length:
                out.append(text[index + 1])
                index += 2
                continue
            if char == in_string:
                in_string = None
            index += 1
            continue
        two = text[index:index + 2]
        if two == "//":
            index += 2
            while index < length and text[index] != "\n":
                index += 1
            out.append(" ")
            continue
        if two == "/*":
            end = text.find("*/", index + 2)
            index = end + 2 if end != -1 else length
            out.append(" ")
            continue
        if char in "\"'":
            in_string = char
            out.append(char)
            index += 1
            continue
        out.append(char)
        index += 1
    return "".join(out)


# --------------------------------------------------------------------------
# Brace-matched extraction (S1 function bodies, struct/typedef definitions)
# --------------------------------------------------------------------------

def extract_braced_block(text: str, open_brace_index: int) -> str:
    """Return ``text[open_brace_index:end+1]`` for the ``{`` at that index.

    Tracks string/char literals and comments so a ``}`` inside either does
    not end the block early.
    """
    depth = 0
    index = open_brace_index
    length = len(text)
    in_string: str | None = None
    in_comment: str | None = None
    while index < length:
        char = text[index]
        if in_comment == "line":
            if char == "\n":
                in_comment = None
            index += 1
            continue
        if in_comment == "block":
            if text[index:index + 2] == "*/":
                in_comment = None
                index += 2
                continue
            index += 1
            continue
        if in_string:
            if char == "\\":
                index += 2
                continue
            if char == in_string:
                in_string = None
            index += 1
            continue
        two = text[index:index + 2]
        if two == "//":
            in_comment = "line"
            index += 2
            continue
        if two == "/*":
            in_comment = "block"
            index += 2
            continue
        if char in "\"'":
            in_string = char
            index += 1
            continue
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0:
                return text[open_brace_index:index + 1]
        index += 1
    raise ValueError("unterminated brace block")


_NESTED_STRUCT_RE = re.compile(r"\b(struct|union)\b\s*\{")


def find_anonymous_members(type_def: str) -> list[str]:
    """Names (``struct``/``union``) of any anonymous nested struct/union member.

    A C11 anonymous struct/union member -- a nested ``struct { ... };`` or
    ``union { ... };`` with no declarator between the closing brace and the
    ``;`` -- is not accepted by IDO's C89 front end.  Synthesizing a
    declarator would silently change every access site's syntax (``x.xx``
    would have to become ``x.s.xx``), so this only detects the case; the
    caller decides what to do (mark the type unsupported rather than emit
    invalid C).  Only scans *nested* struct/union members: the type's own
    outer brace (which may itself be anonymous, as in ``typedef union {
    ... } Name;``) is excluded since that shape is handled elsewhere.
    """
    stripped = strip_comments(type_def)
    open_brace = stripped.find("{")
    if open_brace < 0:
        return []
    try:
        outer = extract_braced_block(stripped, open_brace)
    except ValueError:
        return []
    interior = outer[1:-1]
    found: list[str] = []
    for match in _NESTED_STRUCT_RE.finditer(interior):
        try:
            block = extract_braced_block(interior, match.end() - 1)
        except ValueError:
            continue
        end = match.end() - 1 + len(block)
        rest = interior[end:end + 40]
        if re.match(r"\s*;", rest):
            found.append(match.group(1))
    return found


_GENERIC_FUNC_DEF_RE = re.compile(
    r"(?m)^[ \t]*(?:static\s+)?[A-Za-z_][\w \t\*]*?\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{"
)


def index_function_files(c_paths: list[Path]) -> dict[str, Path]:
    """One-time scan: which ``.c`` file defines each top-level function name."""
    index: dict[str, Path] = {}
    for path in c_paths:
        try:
            text = path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        for match in _GENERIC_FUNC_DEF_RE.finditer(text):
            name = match.group(1)
            if name in CONTROL_KEYWORDS or name in index:
                continue
            index[name] = path
    return index


def find_function_definition(name: str, path: Path) -> tuple[str, bool] | None:
    """Return ``(full_definition_text, is_static)`` for ``name`` in ``path``."""
    try:
        text = path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return None
    pattern = re.compile(
        r"(?m)^[ \t]*((?:static\s+)?[A-Za-z_][^;{}]*?\b" + re.escape(name) + r"\s*\([^;{}]*\))\s*\{"
    )
    for match in pattern.finditer(text):
        brace_index = match.end() - 1
        try:
            body = extract_braced_block(text, brace_index)
        except ValueError:
            continue
        signature = match.group(1)
        full = text[match.start():brace_index] + body
        is_static = bool(re.match(r"\s*static\b", signature))
        return full, is_static
    return None


# --------------------------------------------------------------------------
# Type (struct/typedef/enum) indexing
# --------------------------------------------------------------------------

_TYPEDEF_OPEN_RE = re.compile(r"typedef\s+(?:struct|union|enum)\b[^{};]*\{")
_STRUCT_OPEN_RE = re.compile(r"\b(struct|union|enum)\s+(\w+)\s*\{")
_SIMPLE_TYPEDEF_RE = re.compile(r"(?m)^[ \t]*typedef\b[^{};]*;[ \t]*$")


def _simple_typedef_name(decl: str) -> str | None:
    """The declared name of a non-braced ``typedef <decl>;`` body.

    For a plain alias (``typedef unsigned char u8``) the name is the last
    identifier token.  For a function-pointer typedef
    (``typedef void (*Foo)(int)``) or an array typedef (``typedef u64
    Foo[4]``) it is not -- the last token is a parameter/element type, so
    those shapes are matched explicitly first.
    """
    fptr = re.search(r"\(\s*\*\s*(\w+)\s*\)\s*\(", decl)
    if fptr:
        return fptr.group(1)
    array = re.search(r"(\w+)\s*(?:\[[^\]]*\])+\s*$", decl)
    if array:
        return array.group(1)
    tokens = re.findall(r"\w+", decl)
    return tokens[-1] if tokens else None


def index_type_definitions(texts: list[str]) -> dict[str, str]:
    """name -> full definition text (comments stripped), across every text given."""
    index: dict[str, str] = {}
    for text in texts:
        for match in _TYPEDEF_OPEN_RE.finditer(text):
            try:
                block = extract_braced_block(text, match.end() - 1)
            except ValueError:
                continue
            end = match.end() - 1 + len(block)
            semi = text.find(";", end)
            if semi < 0:
                continue
            trailer = text[end:semi]
            names = [part.strip().lstrip("*").strip() for part in trailer.split(",")]
            full = strip_comments(text[match.start():semi + 1]).strip()
            for name in names:
                if name and re.fullmatch(r"[A-Za-z_]\w*", name) and name not in index:
                    index[name] = full
        for match in _STRUCT_OPEN_RE.finditer(text):
            name = match.group(2)
            if name in index:
                continue
            try:
                block = extract_braced_block(text, match.end() - 1)
            except ValueError:
                continue
            end = match.end() - 1 + len(block)
            semi = text.find(";", end)
            full_end = semi + 1 if 0 <= semi <= end + 2 else end
            index[name] = strip_comments(text[match.start():full_end]).strip()
        for match in _SIMPLE_TYPEDEF_RE.finditer(text):
            line = strip_comments(match.group(0))
            inner = re.match(r"[ \t]*typedef\s+(.*?)\s*;[ \t]*$", line)
            if not inner:
                continue
            name = _simple_typedef_name(inner.group(1))
            if name and name not in index:
                index[name] = line.strip()
    return index


def _collect_referenced_types(
    seed_names: set[str], type_index: dict[str, str], *, max_depth: int = 8
) -> dict[str, str]:
    """Transitively pull in types referenced by the seed types, bounded by depth.

    ``depth`` counts hops from the seed set: the seeds themselves are depth 0
    and always collected; a type reached only through ``max_depth + 1`` hops
    is left out (its name stays unrenamed rather than pulling in an
    unbounded chain of nested definitions).
    """
    collected: dict[str, str] = {}
    frontier = {name for name in seed_names if name in type_index}
    depth = 0
    while frontier:
        if depth > max_depth:
            break
        next_frontier: set[str] = set()
        for name in frontier:
            if name in collected:
                continue
            definition = type_index[name]
            collected[name] = definition
            for ident in re.findall(r"\b[A-Za-z_]\w*\b", definition):
                if ident != name and ident in type_index and ident not in collected:
                    next_frontier.add(ident)
        frontier = next_frontier
        depth += 1
    return collected


def order_types(type_defs: dict[str, str]) -> list[str]:
    """Dependency order (a type's own dependents come after it)."""
    order: list[str] = []
    done: set[str] = set()

    def dependencies(definition: str) -> set[str]:
        # A pointer only needs a forward declaration, so it must not force a
        # complete-definition dependency. This breaks the common S1 graph-node
        # cycle where a record embeds GraphNode by value while GraphNode points
        # back to that record.
        result: set[str] = set()
        for match in re.finditer(r"\b[A-Za-z_]\w*\b", definition):
            name = match.group(0)
            if name not in type_defs:
                continue
            suffix = definition[match.end():]
            if re.match(r"\s*\*", suffix):
                continue
            result.add(name)
        return result

    def visit(name: str, stack: frozenset[str]) -> None:
        if name in done or name not in type_defs or name in stack:
            return
        stack = stack | {name}
        for ident in dependencies(type_defs[name]):
            if ident != name:
                visit(ident, stack)
        if name not in done:
            done.add(name)
            order.append(name)

    for name in type_defs:
        visit(name, frozenset())
    return order


def collect_type_definitions(
    body: str, header_index: dict[str, str], prefix: str, *, max_depth: int = 8
) -> list[str]:
    """Pull in, prefix, and dependency-order every type ``body`` references.

    Scans ``body`` (comment-stripped) for identifiers that name a type in
    ``header_index``, transitively follows those types' own referenced
    types up to ``max_depth`` hops, renames every collected type
    (definition text and cross-references between them alike) by
    prepending ``prefix`` to its name so it can never collide with a
    same-named type in the destination tree, and returns the definitions in
    dependency order (a type's dependents come after it, so pasting the
    list top to bottom always compiles).  Generic over the source of
    ``header_index`` -- nothing here is specific to Stadium 1, and a caller
    that also wants to skip re-emitting a type the destination tree already
    defines identically should filter ``header_index`` (or the result)
    itself before/after calling this.
    """
    stripped = strip_comments(body)
    seed_names = {ident for ident in re.findall(r"\b[A-Za-z_]\w*\b", stripped) if ident in header_index}
    type_defs = _collect_referenced_types(seed_names, header_index, max_depth=max_depth)
    rename_map = {name: f"{prefix}{name}" for name in type_defs}
    ordered = order_types(type_defs)
    return [apply_rename(type_defs[name], rename_map) for name in ordered]


def forward_type_declarations(type_defs: dict[str, str], rename_map: dict[str, str]) -> list[str]:
    """Return forward typedefs for named aggregate definitions.

    Pointer fields may refer to a typedef whose complete definition appears
    later (or participates in a cycle).  A forward typedef keeps those fields
    valid while the ordered complete definitions still handle by-value edges.
    Anonymous aggregates are intentionally omitted because they cannot be
    forward-declared under the eventual alias without changing their type.
    """
    forwards: list[str] = []
    open_re = re.compile(r"^\s*typedef\s+(struct|union|enum)\s+([A-Za-z_]\w*)\s*\{")
    alias_re = re.compile(r"\}\s*([A-Za-z_]\w*)\s*;\s*$", re.S)
    for definition in type_defs.values():
        opening = open_re.match(definition)
        closing = alias_re.search(definition)
        if opening is None or closing is None:
            continue
        kind, tag = opening.groups()
        alias = closing.group(1)
        renamed_tag = apply_rename(tag, rename_map)
        renamed_alias = apply_rename(alias, rename_map)
        forwards.append(f"typedef {kind} {renamed_tag} {renamed_alias};")
    return forwards


def _strip_named_aggregate_typedef(definition: str) -> str:
    """Render a named aggregate body without redeclaring its forward typedef."""
    match = re.match(
        r"^\s*typedef\s+(struct|union|enum)\s+([A-Za-z_]\w*)\s*(\{.*\})\s*([A-Za-z_]\w*)\s*;\s*$",
        definition,
        re.S,
    )
    if match is None:
        return definition
    kind, tag, body, _alias = match.groups()
    return f"{kind} {tag} {body};"


def _normalize_ws(text: str) -> str:
    return re.sub(r"\s+", " ", text).strip()


def _normalize_type_definition(definition: str) -> str:
    """Normalize aggregate typedefs to their installed struct spelling.

    Transferred declarations are initially collected from Stadium 1 as
    ``typedef struct Name { ... } Name;`` units, while accepted candidates
    are installed in GS sources with the forward typedef followed by a
    stripped ``struct Name { ... };`` definition.  Those forms describe the
    same aggregate and must compare equal when deciding whether a definition
    is already present in the owner source.
    """
    rendered = _strip_named_aggregate_typedef(definition)
    # S1 declarations often carry explanatory field comments that are not
    # part of the type.  Ignore them when comparing against a definition
    # already installed in the GS owner, while retaining the original text
    # for any definition that still needs to be emitted.
    rendered = re.sub(r"/\*.*?\*/", "", rendered, flags=re.S)
    rendered = re.sub(r"//[^\n]*", "", rendered)
    return _normalize_ws(rendered)


# --------------------------------------------------------------------------
# extern declarations for mapped data globals
# --------------------------------------------------------------------------

_EXTERN_LINE_RE = re.compile(r"(?m)^[ \t]*extern\b[^;{}]*;")
_EXTERN_TRAILING_NAME_RE = re.compile(r"([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*;\s*$")


def index_extern_declarations(texts: list[str]) -> dict[str, str]:
    index: dict[str, str] = {}
    for text in texts:
        for match in _EXTERN_LINE_RE.finditer(text):
            line = strip_comments(match.group(0)).strip()
            trail = _EXTERN_TRAILING_NAME_RE.search(line)
            if not trail:
                continue
            name = trail.group(1)
            if name not in index:
                index[name] = line
    return index


def _extern_type_token(decl: str) -> str | None:
    """The base type name of an ``extern <type> <name>[...];`` declaration.

    A best-effort heuristic (multi-word types like ``unsigned char`` yield
    just the last word), deliberately conservative: getting it wrong only
    ever means treating a fine type as unknown and falling back to a safer
    spelling, never the other way around.
    """
    body = re.sub(r"^\s*extern\s+", "", decl).strip()
    body = body.rstrip(";").strip()
    body = re.sub(r"\[[^\]]*\]\s*$", "", body).strip()
    tokens = body.split()
    if len(tokens) < 2:
        return None
    type_tokens = tokens[:-1]
    if not type_tokens:
        return None
    return type_tokens[-1].strip("*")


def _is_known_extern_type(type_token: str, gs_type_index: dict[str, str], emitted_type_names: set[str]) -> bool:
    if type_token in _BUILTIN_C_TYPES:
        return True
    if type_token in gs_type_index:
        return True
    if type_token.startswith("S1_") and type_token[len("S1_"):] in emitted_type_names:
        return True
    return False


def _fallback_extern_decl(decl: str, name: str) -> str:
    """Widest safe spelling for a symbol whose S1 type could not be carried over."""
    trail = _EXTERN_TRAILING_NAME_RE.search(decl)
    array_suffix = trail.group(2) if trail and trail.group(2) else None
    if array_suffix:
        return f"extern u8 {name}{array_suffix};"
    return f"extern s32 {name};"


# --------------------------------------------------------------------------
# Macro indexing
# --------------------------------------------------------------------------

_DEFINE_RE = re.compile(r"(?m)^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)(\([^)]*\))?[ \t]*(.*?)[ \t]*$")


def index_macro_definitions(texts: list[str]) -> dict[str, tuple[str, str, bool]]:
    """name -> (params_text_or_empty, expansion, is_multiline).

    ``params_text_or_empty`` is the parenthesised parameter list verbatim
    (including the parens) for a function-like macro, or ``""`` for an
    object-like one.  A trailing ``\\`` continuation on the captured line
    marks ``is_multiline``, so a caller can refuse to carry a multi-line
    expansion across rather than emit a truncated one.
    """
    index: dict[str, tuple[str, str, bool]] = {}
    for text in texts:
        stripped = strip_comments(text)
        for match in _DEFINE_RE.finditer(stripped):
            name = match.group(1)
            if name in index:
                continue
            params = match.group(2) or ""
            value = match.group(3)
            index[name] = (params, value, value.endswith("\\"))
    return index


# --------------------------------------------------------------------------
# Renaming
# --------------------------------------------------------------------------

def rename_identifiers(text: str, mapping: dict[str, str]) -> str:
    """Word-boundary substitution of every key in ``mapping`` within ``text``.

    Longer names are substituted first so renaming ``Foo`` to ``A`` cannot
    accidentally create a substring that then matches a separate ``Foobar``
    -> ``B`` rule (or vice versa).  Generic string rewriting -- callers
    build ``mapping`` however suits them (a symbol rename table, a type
    prefix table, or both merged together).
    """
    if not mapping:
        return text
    pattern = re.compile(
        r"\b(" + "|".join(re.escape(name) for name in sorted(mapping, key=len, reverse=True)) + r")\b"
    )
    return pattern.sub(lambda m: mapping[m.group(0)], text)


apply_rename = rename_identifiers


# --------------------------------------------------------------------------
# Rename-map construction from aligned machine words
# --------------------------------------------------------------------------

@dataclass(frozen=True)
class RenameMap:
    mapping: dict[str, str]
    unmapped: list[str]


def build_rename_map(
    parsed_gs: ParsedAsm,
    other_words: list[int],
    symbol_lookup: Callable[[int], str | None],
    extra: dict[str, str],
) -> RenameMap:
    """Build an other-name -> GS-name rename table from aligned machine words.

    For each GS instruction carrying a ``jal``/``%hi``/``%lo`` symbol
    operand, decode (via the same symbol-name %hi/%lo pairing
    ``decode_s1_addresses`` uses) the address the *other* program's word at
    the same index encodes, resolve it to a name with
    ``symbol_lookup(address)``, and pair that name with the GS operand's
    own symbol text.  ``extra`` seeds the map (typically the transferred
    function's own name) and is never overridden.  An address
    ``symbol_lookup`` cannot name, or one that would map to two different
    GS names, is recorded in ``unmapped`` instead of the mapping.  Generic
    over what ``other_words`` came from and how ``symbol_lookup`` resolves
    an address -- nothing here is specific to Stadium 1.
    """
    mapping = dict(extra)
    unmapped: list[str] = []
    decode = decode_s1_addresses(parsed_gs.instructions, other_words)
    for index in decode.unresolved:
        unmapped.append(f"index {index}: unpaired %lo (no preceding %hi naming the same symbol)")
    for instr in parsed_gs.instructions:
        if instr.jal_sym is None and instr.hi_sym is None and instr.lo_sym is None:
            continue
        addr = decode.addresses.get(instr.index)
        gs_operand_name = instr.jal_sym or instr.hi_sym or instr.lo_sym
        if addr is None:
            continue  # already recorded via decode.unresolved
        name = symbol_lookup(addr)
        if name is None:
            unmapped.append(f"{gs_operand_name} (address 0x{addr:08X} unresolved)")
            continue
        existing = mapping.get(name)
        if existing is not None and existing != gs_operand_name:
            unmapped.append(f"{name} maps to both {existing} and {gs_operand_name}")
            continue
        mapping[name] = gs_operand_name
    return RenameMap(mapping=mapping, unmapped=unmapped)


def sanitize_candidate_text(text: str) -> str:
    """Make transferred text encodable by asm-processor's EUC-JP writer.

    Stadium 1 comments occasionally contain Unicode punctuation (for example
    an em dash).  IDO receives the generated candidate through
    asm-processor, whose EUC-JP output encoding rejects those code points
    before the compiler can inspect the body.  Replacement is lossless for
    code and only changes otherwise-irrelevant source text; the generated
    candidate still goes through the normal isolated probe and full gate.
    """
    return text.encode("euc_jp", errors="replace").decode("euc_jp")


def referenced_type_names(declarations: list[str], type_index: dict[str, str]) -> set[str]:
    """Return indexed type names mentioned by declaration units.

    A transferred body can use a mapped global without mentioning the global's
    S1 type itself.  In that case the type only appears in the generated
    ``extern`` declaration (for example ``extern unk_D_800A62E0 D_800CD020``)
    and must still be pulled into the candidate's declaration block.
    """
    names: set[str] = set()
    for declaration in declarations:
        for ident in re.findall(r"\b[A-Za-z_]\w*\b", declaration):
            if ident in type_index:
                names.add(ident)
    return names


# --------------------------------------------------------------------------
# S1 context: everything built once per run
# --------------------------------------------------------------------------

S1_ROM_RELPATHS = xmatch.S1_ROM_RELPATHS


def find_s1_rom(s1_root: Path) -> Path | None:
    candidates = [s1_root / relpath for relpath in S1_ROM_RELPATHS]
    candidates += [s1_root / "disasm" / "baseroms" / relpath for relpath in S1_ROM_RELPATHS]
    candidates += [s1_root / "disasm" / "baseroms" / "us" / relpath for relpath in S1_ROM_RELPATHS]
    for candidate in candidates:
        if candidate.exists():
            return candidate
    return None


def _guess_gs_asm_fallback_root() -> Path | None:
    """The checkout this worktree was branched from, read-only, for ``.s`` files.

    ``disasm/asm/us/nonmatchings`` is generated (gitignored) and this
    worktree may not have run splat extraction locally.  The ``.s`` for any
    given owner is deterministic from the ROM + yaml, so it is safe to read
    (never write) the same relative path from the sibling checkout.
    """
    name = REPO_ROOT.name
    if "-wt-" not in name:
        return None
    candidate = REPO_ROOT.parent / name.split("-wt-")[0]
    return candidate if candidate.is_dir() else None


def gs_asm_text(owner: targets.Owner, fallback_root: Path | None) -> tuple[str, str] | None:
    if owner.asm_path.exists():
        return owner.asm_path.read_text(encoding="utf-8", errors="replace"), "worktree"
    if fallback_root is not None:
        candidate = fallback_root / owner.asm
        if candidate.exists():
            return candidate.read_text(encoding="utf-8", errors="replace"), str(fallback_root)
    return None


@dataclass
class S1Context:
    root: Path
    s1_functions: dict[str, dict]
    symtab: S1SymbolTable
    type_index: dict[str, str]
    extern_index: dict[str, str]
    macro_index: dict[str, tuple[str, str, bool]]
    gs_type_index: dict[str, str]
    gs_macro_index: dict[str, tuple[str, str, bool]]
    func_file_index: dict[str, Path]
    gs_asm_fallback: Path | None


def _read_texts(paths: list[Path]) -> list[str]:
    out = []
    for path in paths:
        try:
            out.append(path.read_text(encoding="utf-8", errors="replace"))
        except OSError:
            continue
    return out


def build_s1_context(s1_root: Path, *, gs_asm_fallback: Path | None, verbose: bool = True) -> S1Context:
    rom_path = find_s1_rom(s1_root)
    if rom_path is None:
        raise FileNotFoundError(
            f"no Stadium 1 ROM found under {s1_root} (checked {S1_ROM_RELPATHS} directly "
            f"and under disasm/baseroms/); pass --s1-root"
        )
    s1d = s1_root / "disasm"
    s1_functions = xmatch.load_functions(
        str(rom_path),
        [str(s1d / "pokestadium-us.yaml")],
        [str(s1d / "linker_scripts" / "us" / name) for name in
         ("symbol_addrs_code.txt", "symbol_addrs_ultralib.txt")],
        "S1",
        verbose=verbose,
    )
    symtab = load_s1_symbols(s1_root)

    def _is_lib(path: Path) -> bool:
        return any(part.startswith("lib") for part in path.parts)

    c_paths = [p for p in (s1d / "src").rglob("*.c") if not _is_lib(p.relative_to(s1d / "src"))]
    h_paths = [p for p in (s1d / "src").rglob("*.h") if not _is_lib(p.relative_to(s1d / "src"))]
    h_paths += list((s1d / "include").rglob("*.h"))

    header_texts = _read_texts(h_paths)
    c_texts = _read_texts(c_paths)
    type_index = index_type_definitions(header_texts + c_texts)
    extern_index = index_extern_declarations(header_texts + c_texts)
    macro_index = index_macro_definitions(header_texts + c_texts)
    func_file_index = index_function_files(c_paths)
    symtab.func_names.update(func_file_index)

    gs_header_paths = list(GS_INCLUDE_ROOT.rglob("*.h")) if GS_INCLUDE_ROOT.is_dir() else []
    if GS_ULTRALIB_INCLUDE_ROOT.is_dir():
        gs_header_paths += list(GS_ULTRALIB_INCLUDE_ROOT.rglob("*.h"))
    gs_header_texts = _read_texts(gs_header_paths)
    gs_type_index = index_type_definitions(gs_header_texts)
    gs_macro_index = index_macro_definitions(gs_header_texts)

    return S1Context(
        root=s1_root,
        s1_functions=s1_functions,
        symtab=symtab,
        type_index=type_index,
        extern_index=extern_index,
        macro_index=macro_index,
        gs_type_index=gs_type_index,
        gs_macro_index=gs_macro_index,
        func_file_index=func_file_index,
        gs_asm_fallback=gs_asm_fallback,
    )


def build_gs_context() -> dict[str, dict]:
    """Load every GS ROM function's decoded machine words.

    Mirrors what ``xmatch_stadium1.main()`` does for the GS side of its own
    match: same ROM search order (``xmatch.GS_ROM_CANDIDATES``), same yaml
    and symbol tables.  Only needed for ``--near-matches`` (the transfer-map
    path never needs the GS ROM, only the GS ``.s`` files).  Raises
    ``FileNotFoundError`` with a clear message when no GS ROM is available
    -- there is no sensible fallback for it.
    """
    gs_rom = next((path for path in xmatch.GS_ROM_CANDIDATES if os.path.exists(path)), None)
    if gs_rom is None:
        raise FileNotFoundError(
            f"no Stadium 2 ROM found for --near-matches (checked {xmatch.GS_ROM_CANDIDATES}); "
            f"build one or point tools/xmatch_stadium1.py's GS_ROM_CANDIDATES at it"
        )
    return xmatch.load_functions(
        gs_rom,
        [str(GS_YAML_PATH)],
        [str(GS_LINKER_SCRIPTS_ROOT / name) for name in
         ("symbol_addrs_code.txt", "symbol_addrs_ultralib.txt")],
        "GS",
        src_dir=str(GS_SRC_ROOT),
    )


# --------------------------------------------------------------------------
# Transfer map
# --------------------------------------------------------------------------

def load_transfer_map(path: Path = S1_TRANSFER_PATH) -> dict[str, tuple[str, str]]:
    data = json.loads(path.read_text(encoding="utf-8"))
    out: dict[str, tuple[str, str]] = {}
    for gs_name, value in data.get("functions", {}).items():
        if isinstance(value, list) and len(value) == 2:
            out[gs_name] = (str(value[0]), str(value[1]))
    return out


def build_s1_reverse_index(transfer_map: dict[str, tuple[str, str]]) -> dict[str, str]:
    """S1 function name -> GS function id, for cross-referencing callees."""
    out: dict[str, str] = {}
    for gs_name, (_, evidence) in transfer_map.items():
        match = EVIDENCE_RE.search(evidence)
        if match:
            out.setdefault(match.group(1), gs_name)
    return out


# --------------------------------------------------------------------------
# Candidate generation
# --------------------------------------------------------------------------

@dataclass
class TransferResult:
    function: str
    outcome: str
    detail: str = ""
    s1_name: str | None = None
    symbol_map: dict[str, str] = field(default_factory=dict)
    unmapped_symbols: list[str] = field(default_factory=list)
    declarations: str = ""
    # Complete declaration units, kept separate so source groups can merge
    # multiline typedefs atomically instead of deduplicating their lines.
    declaration_units: list[str] = field(default_factory=list)
    variants: list[tuple[str, str]] = field(default_factory=list)
    unsupported_types: list[str] = field(default_factory=list)
    unresolved_extern_types: list[str] = field(default_factory=list)
    unresolved_macros: list[str] = field(default_factory=list)
    similarity: float | None = None


def generate_candidate(
    function: str,
    owner: targets.Owner,
    ctx: S1Context,
    transfer_map: dict[str, tuple[str, str]],
    s1_reverse_index: dict[str, str],
    *,
    strict: bool = False,
) -> TransferResult:
    entry = transfer_map.get(function)
    if entry is None:
        return TransferResult(function, "no_transfer_entry")
    _, evidence = entry
    match = EVIDENCE_RE.search(evidence)
    if not match:
        return TransferResult(function, "evidence_unparseable", detail=evidence)
    s1_name = match.group(1)
    return _build_transfer_result(
        function, owner, ctx, s1_name, s1_reverse_index,
        strict=strict, align_strict=True, label="s1:transfer",
    )


def generate_near_match_candidate(
    function: str,
    owner: targets.Owner,
    ctx: S1Context,
    s1_name: str,
    similarity: float,
    s1_reverse_index: dict[str, str],
    *,
    strict: bool = False,
) -> TransferResult:
    """Same pipeline as ``generate_candidate``, for a near (not exact) S1 body.

    Alignment is loose (``align_strict=False``): only instructions carrying
    a relocatable operand need to land on the same opcode class in ``s1_name``'s
    body, since the two bodies come from independently compiled, merely
    similar sources rather than the same one.
    """
    return _build_transfer_result(
        function, owner, ctx, s1_name, s1_reverse_index,
        strict=strict, align_strict=False, label=f"s1-near:{s1_name}:{similarity:.2f}",
        similarity=similarity,
    )


def _build_transfer_result(
    function: str,
    owner: targets.Owner,
    ctx: S1Context,
    s1_name: str,
    s1_reverse_index: dict[str, str],
    *,
    strict: bool,
    align_strict: bool,
    label: str,
    similarity: float | None = None,
) -> TransferResult:
    s1_func = ctx.s1_functions.get(s1_name)
    if s1_func is None:
        return TransferResult(function, "s1_function_missing", s1_name=s1_name,
                               detail=f"{s1_name} not found among S1 ROM functions", similarity=similarity)

    home = ctx.func_file_index.get(s1_name)
    definition = find_function_definition(s1_name, home) if home is not None else None
    if definition is None:
        return TransferResult(function, "s1_body_missing", s1_name=s1_name,
                               detail=f"no C definition found for {s1_name} under S1 disasm/src",
                               similarity=similarity)
    full_definition, is_static = definition
    # Comments never travel: they can carry a rename-map identifier or a
    # non-ASCII byte that would otherwise leak into the candidate, and are
    # the reason two occurrences of the same struct (pulled in by two
    # different transferred functions, each with a per-caller comment) used
    # to look different enough to defeat cross-candidate deduplication.
    full_definition = strip_comments(full_definition)

    asm = gs_asm_text(owner, ctx.gs_asm_fallback)
    if asm is None:
        return TransferResult(function, "gs_asm_missing", s1_name=s1_name,
                               detail=str(owner.asm_path), similarity=similarity)
    asm_text, asm_source = asm
    parsed_gs = parse_gs_asm(asm_text)
    if not parsed_gs.instructions:
        return TransferResult(function, "gs_asm_unparseable", s1_name=s1_name, similarity=similarity)

    gs_words = parsed_gs.words
    s1_words = list(s1_func["w"])
    alignment = align_words(gs_words, s1_words, strict=align_strict)
    if alignment is None:
        return TransferResult(
            function, "alignment_failed", s1_name=s1_name,
            detail=f"instruction count differs: gs={len(gs_words)} s1={len(s1_words)} (asm from {asm_source})",
            similarity=similarity,
        )
    if not alignment.ok:
        g, o = gs_words[alignment.first_mismatch], s1_words[alignment.first_mismatch]
        kind = "differs" if align_strict else "opcode class differs"
        return TransferResult(
            function, "alignment_failed", s1_name=s1_name,
            detail=f"instruction {alignment.first_mismatch} {kind}: gs=0x{g:08X} s1=0x{o:08X}",
            similarity=similarity,
        )

    body_identifiers = set(re.findall(r"\b[A-Za-z_]\w*\b", full_definition))

    lookup = make_symbol_lookup(ctx.symtab, body_identifiers)
    renamed = build_rename_map(parsed_gs, s1_words, lookup, {s1_name: owner.function})
    symbol_map = renamed.mapping
    unmapped = list(renamed.unmapped)

    # Cross-reference: an S1 global used in the body but not resolved above
    # (e.g. inside a struct-literal initializer with no matching instruction)
    # may still be nameable via another entry in the transfer map.
    for ident in sorted(body_identifiers):
        if ident in symbol_map or ident not in ctx.symtab.names:
            continue
        other_gs = s1_reverse_index.get(ident)
        if other_gs is not None and other_gs in targets.owner_index():
            symbol_map[ident] = other_gs
        else:
            unmapped.append(f"{ident} (S1 global, no resolvable GS mapping)")

    if strict and unmapped:
        return TransferResult(
            function, "unmapped_symbols_strict", s1_name=s1_name,
            detail="; ".join(unmapped[:5]), symbol_map=symbol_map, unmapped_symbols=unmapped,
            similarity=similarity,
        )

    # Gather mapped extern declarations before collecting types.  A body can
    # use a global without spelling its S1 type, so the extern itself may be
    # the only seed for a required declaration (notably the scheduler state).
    extern_declarations: list[str] = []
    seen_raw_externs: set[str] = set()
    for s1_sym, gs_sym in symbol_map.items():
        if s1_sym == s1_name or s1_sym in ctx.symtab.func_names:
            continue
        decl = ctx.extern_index.get(s1_sym)
        if decl is None or decl in seen_raw_externs:
            continue
        seen_raw_externs.add(decl)
        extern_declarations.append(decl)

    # Types the body or its mapped extern declarations need, S1_-prefixed
    # unless GS (or the owner source itself) already has an identical
    # definition under the same name.  A genuine C11 anonymous struct/union
    # member (IDO's C89 front end rejects it, and synthesizing a declarator
    # would change every access site's syntax) is excluded from what gets
    # emitted and reported instead, so the resulting compile failure -- the
    # type is still referenced, just never defined -- is explainable.
    candidate_type_names = {ident for ident in body_identifiers if ident in ctx.type_index}
    candidate_type_names.update(referenced_type_names(extern_declarations, ctx.type_index))
    # Stadium 1 display/geo records commonly reach vector and matrix typedefs
    # through five or more nested record layers. Keep the bound finite, but
    # include those real dependencies instead of emitting fields with unknown
    # unprefixed types.
    type_defs = _collect_referenced_types(candidate_type_names, ctx.type_index, max_depth=8)
    try:
        owner_text = owner.source_path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        owner_text = ""
    owner_type_index = index_type_definitions([owner_text]) if owner_text else {}
    combined_gs_type_index = {**ctx.gs_type_index, **owner_type_index}

    # The owner may already carry an S1-prefixed definition copied by an
    # earlier transfer (or a hand-written equivalent in the same C file).
    # Compare against both the repository headers and the owner source after
    # applying the complete provisional S1 rename map.  Otherwise a perfectly
    # compatible definition is emitted a second time and IDO rejects the
    # candidate before it can reach the byte probe.
    provisional_type_rename = {name: f"S1_{name}" for name in type_defs}
    type_rename: dict[str, str] = {}
    kept_type_defs: dict[str, str] = {}
    unsupported_types: list[str] = []
    for name, type_def in type_defs.items():
        if find_anonymous_members(type_def):
            unsupported_types.append(name)
            continue
        gs_def = owner_type_index.get(name) or ctx.gs_type_index.get(name)
        if gs_def is not None and _normalize_type_definition(gs_def) == _normalize_type_definition(type_def):
            continue
        renamed_name = provisional_type_rename[name]
        prefixed_gs_def = owner_type_index.get(renamed_name) or ctx.gs_type_index.get(renamed_name)
        if prefixed_gs_def is not None:
            renamed_definition = apply_rename(type_def, provisional_type_rename)
            if _normalize_type_definition(prefixed_gs_def) == _normalize_type_definition(renamed_definition):
                type_rename[name] = renamed_name
                continue
        type_rename[name] = renamed_name
        kept_type_defs[name] = type_def

    # Object-like S1 macros the body -- or a type definition the body pulled
    # in, such as an array bound inside a struct field (S1_Fragment's
    # ``data[RELOCATIONS_SIZE]``) -- needs, carried along verbatim unless GS
    # defines the same name to something else, in which case the S1
    # spelling is prefixed like a type.  A macro whose expansion is not a
    # single physical line is left unresolved rather than risk emitting a
    # truncated definition.
    macro_seed_identifiers = set(body_identifiers)
    for type_def in type_defs.values():
        macro_seed_identifiers.update(re.findall(r"\b[A-Za-z_]\w*\b", type_def))
    macro_decls: list[str] = []
    macro_rename: dict[str, str] = {}
    unresolved_macros: list[str] = []
    for ident in sorted(macro_seed_identifiers):
        macro = ctx.macro_index.get(ident)
        if macro is None:
            continue
        params, value, multiline = macro
        gs_macro = ctx.gs_macro_index.get(ident)
        if gs_macro is not None and _normalize_ws(gs_macro[1]) == _normalize_ws(value):
            continue  # GS already defines it identically
        if multiline:
            unresolved_macros.append(ident)
            continue
        if gs_macro is not None:
            new_name = f"S1_{ident}"
            macro_rename[ident] = new_name
            macro_decls.append(f"#define {new_name}{params} {value}".rstrip())
        else:
            macro_decls.append(f"#define {ident}{params} {value}".rstrip())

    rename_map = dict(symbol_map)
    rename_map.update(type_rename)
    rename_map.update(macro_rename)

    ordered_type_defs = [
        _strip_named_aggregate_typedef(apply_rename(kept_type_defs[name], rename_map))
        for name in order_types(kept_type_defs)
    ]
    forward_type_defs = forward_type_declarations(kept_type_defs, rename_map)

    extra_externs: list[str] = []
    seen_externs: set[str] = set()
    unresolved_extern_types: list[str] = []
    emitted_type_names = set(kept_type_defs)
    for s1_sym, gs_sym in symbol_map.items():
        if s1_sym == s1_name or s1_sym in ctx.symtab.func_names:
            continue
        decl = ctx.extern_index.get(s1_sym)
        if decl is None:
            continue
        renamed_decl = apply_rename(decl, rename_map)
        if renamed_decl in seen_externs:
            continue
        seen_externs.add(renamed_decl)
        type_token = _extern_type_token(renamed_decl)
        if type_token is not None and not _is_known_extern_type(type_token, combined_gs_type_index, emitted_type_names):
            unresolved_extern_types.append(f"{gs_sym}: {type_token}")
            renamed_decl = _fallback_extern_decl(renamed_decl, gs_sym)
        extra_externs.append(renamed_decl)

    declaration_units = macro_decls + forward_type_defs + ordered_type_defs + extra_externs
    declarations = "\n".join(sanitize_candidate_text(unit) for unit in declaration_units)
    if declarations:
        declarations += "\n"

    renamed_definition = sanitize_candidate_text(apply_rename(full_definition, rename_map))

    combined = declarations + renamed_definition
    if any(ord(char) > 0x7F for char in combined):
        return TransferResult(
            function, "non_ascii", s1_name=s1_name,
            detail="non-ASCII byte remains in the candidate text outside comments",
            symbol_map=symbol_map, unmapped_symbols=unmapped, similarity=similarity,
        )

    variants: list[tuple[str, str]] = [(label, renamed_definition.strip() + "\n")]
    if is_static:
        nostatic = re.sub(r"^\s*static\s+", "", renamed_definition, count=1)
        variants.append((f"{label}-nostatic", nostatic.strip() + "\n"))

    return TransferResult(
        function, "candidate", s1_name=s1_name, symbol_map=symbol_map,
        unmapped_symbols=unmapped, declarations=declarations,
        declaration_units=declaration_units, variants=variants,
        unsupported_types=unsupported_types, unresolved_extern_types=unresolved_extern_types,
        unresolved_macros=unresolved_macros, similarity=similarity,
    )


# --------------------------------------------------------------------------
# Selection
# --------------------------------------------------------------------------

def select_functions(
    transfer_map: dict[str, tuple[str, str]],
    *,
    functions: list[str] | None,
    source: str | None,
    limit: int | None,
    allow_dirty: bool = False,
) -> list[str]:
    owners = targets.owner_index()
    dirty = dedupe_externs.dirty_sources()
    pool = functions if functions else sorted(transfer_map)
    wanted_source = source.replace("\\", "/").removeprefix("./") if source else None
    selected: list[str] = []
    for function in pool:
        if function not in transfer_map:
            continue
        owner = owners.get(function)
        if owner is None:
            continue
        if wanted_source and owner.source != wanted_source and not owner.source.endswith("/" + wanted_source):
            continue
        if not allow_dirty and owner.source_path.resolve() in dirty:
            continue
        selected.append(function)
    if limit is not None:
        selected = selected[:limit]
    return selected


def select_near_match_functions(
    transfer_map: dict[str, tuple[str, str]],
    *,
    functions: list[str] | None,
    source: str | None,
    limit: int | None,
) -> list[str]:
    """Pragma owners not already covered by an exact S1 transfer entry."""
    owners = targets.owner_index()
    dirty = dedupe_externs.dirty_sources()
    pool = functions if functions else sorted(owners)
    wanted_source = source.replace("\\", "/").removeprefix("./") if source else None
    selected: list[str] = []
    for function in pool:
        if function in transfer_map:
            continue
        owner = owners.get(function)
        if owner is None:
            continue
        if wanted_source and owner.source != wanted_source and not owner.source.endswith("/" + wanted_source):
            continue
        if owner.source_path.resolve() in dirty:
            continue
        selected.append(function)
    if limit is not None:
        selected = selected[:limit]
    return selected


def merge_declarations(units: list[str]) -> str:
    """Merge complete declarations without splitting multiline definitions."""
    seen: set[str] = set()
    merged: list[str] = []
    for unit in units:
        normalized = unit.strip()
        if not normalized or normalized in seen:
            continue
        seen.add(normalized)
        merged.append(normalized)
    return "\n".join(merged) + ("\n" if merged else "")


def _declaration_unit_symbol(unit: str) -> str | None:
    """Return the typedef/extern symbol introduced by one declaration unit."""
    text = unit.strip()
    if not text:
        return None
    function_pointer = re.search(r"\(\*\s*([A-Za-z_]\w*)\s*\)", text)
    if function_pointer:
        return function_pointer.group(1)
    aggregate_alias = re.search(r"}\s*([A-Za-z_]\w*)\s*;\s*$", text, re.S)
    if aggregate_alias:
        return aggregate_alias.group(1)
    named_definition = re.search(
        r"\b(?:struct|union|enum)\s+([A-Za-z_]\w*)\s*\{.*\}\s*;\s*$", text, re.S
    )
    if named_definition:
        return named_definition.group(1)
    trailing_name = re.search(r"\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*;\s*$", text, re.S)
    return trailing_name.group(1) if trailing_name else None


def _declaration_unit_symbols(units: list[str]) -> dict[str, str]:
    symbols: dict[str, str] = {}
    for unit in units:
        name = _declaration_unit_symbol(unit)
        if name is None:
            continue
        existing = symbols.get(name)
        if existing is None or ("{" not in existing and "{" in unit):
            symbols[name] = unit
    return symbols


def _declaration_conflicts(existing: dict[str, str], incoming: dict[str, str]) -> bool:
    for name, unit in incoming.items():
        previous = existing.get(name)
        if previous is None or previous.strip() == unit.strip():
            continue
        # A forward typedef and its later complete definition are compatible;
        # the complete unit wins when the group is rendered.
        if "{" not in previous or "{" not in unit:
            continue
        return True
    return False


def partition_transfer_results(results: list[TransferResult]) -> list[list[TransferResult]]:
    """Partition candidates into declaration-compatible connected groups.

    The runner accepts one shared declaration block for a source group.  It is
    tempting to merge every non-conflicting result, but unrelated declarations
    can still break an otherwise valid candidate (for example a bad function
    pointer typedef or a source-local type defined later in the file).  Keep
    candidates together when they share declaration symbols, and keep the
    declaration-free candidates together; disjoint declaration sets are
    independent probe groups and should not contaminate one another.
    """
    groups: list[list[TransferResult]] = []
    group_symbols: list[dict[str, str]] = []
    for result in results:
        units = result.declaration_units or ([result.declarations] if result.declarations else [])
        symbols = _declaration_unit_symbols(units)
        for index, existing in enumerate(group_symbols):
            existing_results = groups[index]
            existing_units = [
                unit
                for prior in existing_results
                for unit in (prior.declaration_units or ([prior.declarations] if prior.declarations else []))
            ]
            shares_declarations = bool(set(existing) & set(symbols))
            both_empty = not existing_units and not units
            same_unparsed_units = (
                not existing and not symbols and bool(existing_units) and bool(units)
                and {unit.strip() for unit in existing_units} == {unit.strip() for unit in units}
            )
            if not (shares_declarations or both_empty or same_unparsed_units):
                continue
            if _declaration_conflicts(existing, symbols):
                continue
            groups[index].append(result)
            for name, unit in symbols.items():
                if name not in existing or ("{" not in existing[name] and "{" in unit):
                    existing[name] = unit
            break
        else:
            groups.append([result])
            group_symbols.append(dict(symbols))
    return groups


# --------------------------------------------------------------------------
# Near-match selection
# --------------------------------------------------------------------------

def bucket_s1_by_length(ctx: S1Context) -> dict[int, list[str]]:
    """S1 functions with a finished C body, grouped by instruction count.

    Only bodies ``generate_near_match_candidate`` could actually use -- an
    S1 function still a ``GLOBAL_ASM`` stub in its own tree contributes
    nothing.  Bucketing by exact length up front is what keeps ranking a
    whole tree of remaining GS pragmas against several thousand S1 bodies
    affordable: only same-length bodies are ever scored against each other.
    """
    buckets: dict[int, list[str]] = collections.defaultdict(list)
    for name in ctx.func_file_index:
        func = ctx.s1_functions.get(name)
        if func is not None:
            buckets[len(func["w"])].append(name)
    return buckets


def find_near_match(
    gs_words: list[int], s1_length_buckets: dict[int, list[str]], ctx: S1Context, *, minimum: float
) -> tuple[str, float] | None:
    """Best identical-length, decompiled S1 body for ``gs_words``, or ``None``.

    Ties break on name for determinism.  Returns ``None`` when there is no
    same-length candidate with a C body, or the best one scores below
    ``minimum``.
    """
    candidates = s1_length_buckets.get(len(gs_words), [])
    best: tuple[str, float] | None = None
    for name in candidates:
        score = xmatch.similarity(gs_words, ctx.s1_functions[name]["w"])
        if best is None or score > best[1] or (score == best[1] and name < best[0]):
            best = (name, score)
    if best is None or best[1] < minimum:
        return None
    return best


# --------------------------------------------------------------------------
# Driver
# --------------------------------------------------------------------------

def _run_source_group_once(
    source_path: Path,
    results: list[TransferResult],
    *,
    gate: bool,
    workers: int | None,
) -> dict[str, object]:
    blocks: list[tuple[str, str]] = []
    labels: list[str] = []
    for result in results:
        for label, code in result.variants:
            blocks.append((result.function, code))
            labels.append(label)
    if not blocks:
        return {"attempts": [], "accepted": []}
    declaration_units: list[str] = []
    for result in results:
        if result.declaration_units:
            declaration_units.extend(sanitize_candidate_text(unit) for unit in result.declaration_units)
        elif result.declarations:
            # Keep compatibility with callers/tests that construct a result
            # using only the legacy rendered declaration block.
            declaration_units.append(sanitize_candidate_text(result.declarations))
    declarations = merge_declarations(declaration_units) or None
    probe = runner.try_candidates_detailed(
        source_path, blocks, labels=labels, declarations=declarations, gate=False, probe_workers=workers
    )
    gate_blocks: list[tuple[str, str]] = []
    gate_labels: list[str] = []
    for attempt in probe["attempts"]:
        if attempt.get("status") == "probe_match":
            index = int(attempt["index"])
            gate_blocks.append(blocks[index])
            gate_labels.append(labels[index])
    if not gate_blocks:
        return probe
    return runner.try_candidates_detailed(
        source_path, gate_blocks, labels=gate_labels, declarations=declarations, gate=gate, probe_workers=workers
    )


def run_source_group(
    source_path: Path,
    results: list[TransferResult],
    *,
    gate: bool,
    workers: int | None,
) -> dict[str, object]:
    groups = partition_transfer_results(results)
    attempts: list[dict[str, object]] = []
    accepted: list[str] = []
    statuses: list[str] = []
    for group in groups:
        result = _run_source_group_once(source_path, group, gate=gate, workers=workers)
        attempts.extend(result.get("attempts", []))
        accepted.extend(str(name) for name in result.get("accepted", []))
        if result.get("batch_status") is not None:
            statuses.append(str(result["batch_status"]))
    if not attempts:
        return {"attempts": [], "accepted": []}
    return {
        "attempts": attempts,
        "accepted": accepted,
        "batch_status": "accepted" if accepted else (
            statuses[0] if len(set(statuses)) == 1 and statuses else "no_candidate_accepted"
        ),
    }


def sweep(
    functions: list[str],
    *,
    ctx: S1Context,
    transfer_map: dict[str, tuple[str, str]],
    s1_reverse_index: dict[str, str],
    gate: bool,
    workers: int | None,
    strict: bool,
) -> dict[str, object]:
    started = time.monotonic()
    owners = targets.owner_index()
    by_source: dict[Path, list[TransferResult]] = collections.defaultdict(list)
    outcome_counts: collections.Counter = collections.Counter()
    vanished = 0
    for function in functions:
        owner = owners.get(function)
        if owner is None:
            vanished += 1
            continue
        result = generate_candidate(function, owner, ctx, transfer_map, s1_reverse_index, strict=strict)
        outcome_counts[result.outcome] += 1
        if result.outcome == "candidate":
            by_source[owner.source_path].append(result)

    accepted: list[str] = []
    touched_sources: list[str] = []
    attempts: list[dict[str, object]] = []
    for source_path, results in by_source.items():
        try:
            result = run_source_group(source_path, results, gate=gate, workers=workers)
        except Exception as error:  # one broken source must not end the sweep
            print(f"{source_path}: sweep failed: {error}", file=sys.stderr)
            continue
        attempts.extend(result.get("attempts", []))
        if result.get("accepted"):
            accepted.extend(str(name) for name in result["accepted"])
            touched_sources.append(str(source_path.relative_to(REPO_ROOT)))

    return {
        "requested": len(functions),
        "vanished": vanished,
        "outcome_counts": dict(sorted(outcome_counts.items())),
        "accepted": accepted,
        "touched_sources": sorted(set(touched_sources)),
        "attempts": attempts,
        "elapsed_seconds": round(time.monotonic() - started, 1),
    }


def sweep_near_matches(
    functions: list[str],
    *,
    ctx: S1Context,
    gs_functions: dict[str, dict],
    s1_reverse_index: dict[str, str],
    minimum: float,
    gate: bool,
    workers: int | None,
    strict: bool,
) -> dict[str, object]:
    started = time.monotonic()
    owners = targets.owner_index()
    buckets = bucket_s1_by_length(ctx)
    by_source: dict[Path, list[TransferResult]] = collections.defaultdict(list)
    outcome_counts: collections.Counter = collections.Counter()
    vanished = 0
    for function in functions:
        owner = owners.get(function)
        if owner is None:
            vanished += 1
            continue
        gs_func = gs_functions.get(function)
        if gs_func is None:
            outcome_counts["gs_function_missing"] += 1
            continue
        found = find_near_match(list(gs_func["w"]), buckets, ctx, minimum=minimum)
        if found is None:
            outcome_counts["near_no_candidate"] += 1
            continue
        s1_name, score = found
        result = generate_near_match_candidate(function, owner, ctx, s1_name, score, s1_reverse_index, strict=strict)
        outcome_counts[result.outcome] += 1
        if result.outcome == "candidate":
            by_source[owner.source_path].append(result)

    accepted: list[str] = []
    touched_sources: list[str] = []
    attempts: list[dict[str, object]] = []
    for source_path, results in by_source.items():
        try:
            result = run_source_group(source_path, results, gate=gate, workers=workers)
        except Exception as error:
            print(f"{source_path}: sweep failed: {error}", file=sys.stderr)
            continue
        attempts.extend(result.get("attempts", []))
        if result.get("accepted"):
            accepted.extend(str(name) for name in result["accepted"])
            touched_sources.append(str(source_path.relative_to(REPO_ROOT)))

    return {
        "requested": len(functions),
        "vanished": vanished,
        "outcome_counts": dict(sorted(outcome_counts.items())),
        "accepted": accepted,
        "touched_sources": sorted(set(touched_sources)),
        "attempts": attempts,
        "elapsed_seconds": round(time.monotonic() - started, 1),
    }


def dry_run(
    functions: list[str],
    *,
    ctx: S1Context,
    transfer_map: dict[str, tuple[str, str]],
    s1_reverse_index: dict[str, str],
    strict: bool,
    show_text: bool,
) -> dict[str, object]:
    owners = targets.owner_index()
    outcome_counts: collections.Counter = collections.Counter()
    rows: list[dict[str, object]] = []
    for function in functions:
        owner = owners.get(function)
        if owner is None:
            outcome_counts["owner_missing"] += 1
            continue
        result = generate_candidate(function, owner, ctx, transfer_map, s1_reverse_index, strict=strict)
        outcome_counts[result.outcome] += 1
        row: dict[str, object] = {
            "function": function,
            "s1_name": result.s1_name,
            "outcome": result.outcome,
            "detail": result.detail,
            "symbol_map": result.symbol_map,
            "unmapped_symbols": result.unmapped_symbols,
            "unsupported_types": result.unsupported_types,
            "unresolved_extern_types": result.unresolved_extern_types,
            "unresolved_macros": result.unresolved_macros,
            "labels": [label for label, _ in result.variants],
        }
        if show_text:
            row["declarations"] = result.declarations
            row["variants"] = result.variants
        rows.append(row)
    return {"outcome_counts": dict(sorted(outcome_counts.items())), "rows": rows}


def dry_run_near_matches(
    functions: list[str],
    *,
    ctx: S1Context,
    gs_functions: dict[str, dict],
    s1_reverse_index: dict[str, str],
    minimum: float,
    strict: bool,
    show_text: bool,
) -> dict[str, object]:
    owners = targets.owner_index()
    buckets = bucket_s1_by_length(ctx)
    outcome_counts: collections.Counter = collections.Counter()
    rows: list[dict[str, object]] = []
    for function in functions:
        owner = owners.get(function)
        if owner is None:
            outcome_counts["owner_missing"] += 1
            continue
        gs_func = gs_functions.get(function)
        if gs_func is None:
            outcome_counts["gs_function_missing"] += 1
            continue
        found = find_near_match(list(gs_func["w"]), buckets, ctx, minimum=minimum)
        if found is None:
            outcome_counts["near_no_candidate"] += 1
            continue
        s1_name, score = found
        result = generate_near_match_candidate(function, owner, ctx, s1_name, score, s1_reverse_index, strict=strict)
        outcome_counts[result.outcome] += 1
        row: dict[str, object] = {
            "function": function,
            "s1_name": result.s1_name,
            "similarity": result.similarity,
            "outcome": result.outcome,
            "detail": result.detail,
            "symbol_map": result.symbol_map,
            "unmapped_symbols": result.unmapped_symbols,
            "unsupported_types": result.unsupported_types,
            "unresolved_extern_types": result.unresolved_extern_types,
            "unresolved_macros": result.unresolved_macros,
            "labels": [label for label, _ in result.variants],
        }
        if show_text:
            row["declarations"] = result.declarations
            row["variants"] = result.variants
        rows.append(row)
    return {"outcome_counts": dict(sorted(outcome_counts.items())), "rows": rows}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--function", action="append", dest="functions", help="restrict to this GS function (repeatable)")
    parser.add_argument("--source", help="restrict to owners of this GS source path")
    parser.add_argument("--limit", type=int, help="maximum functions to consider")
    parser.add_argument("--no-gate", action="store_true", help="probe only; never edit tracked sources")
    parser.add_argument("--dry-run", action="store_true", help="generate and print candidates; call no runner")
    parser.add_argument("--strict", action="store_true", help="do not emit a candidate when any symbol is unmapped")
    parser.add_argument(
        "--allow-dirty",
        action="store_true",
        help="include explicitly selected dirty sources (for same-session validation; default skips them)",
    )
    parser.add_argument("--workers", type=int)
    parser.add_argument("--json", type=Path, help="write the summary to this file")
    parser.add_argument("--s1-root", type=Path, default=Path(xmatch.DEFAULT_S1))
    parser.add_argument("--gs-asm-fallback", type=Path, help="read-only fallback root for missing GS .s files")
    parser.add_argument("--no-gs-asm-fallback", action="store_true", help="disable the GS .s fallback lookup")
    parser.add_argument("--show-text", action="store_true", help="(--dry-run) also print declarations/candidate text")
    parser.add_argument("--transfer-map", type=Path, default=S1_TRANSFER_PATH)
    parser.add_argument(
        "--near-matches", action="store_true",
        help="for pragmas with no exact S1 transfer entry, transfer the best same-length, "
             "similar S1 body instead",
    )
    parser.add_argument(
        "--near-min-similarity", type=float, default=0.85,
        help="minimum normalised instruction similarity for --near-matches (default: 0.85)",
    )
    args = parser.parse_args()

    transfer_map = load_transfer_map(args.transfer_map)
    s1_reverse_index = build_s1_reverse_index(transfer_map)

    if args.no_gs_asm_fallback:
        gs_asm_fallback = None
    elif args.gs_asm_fallback is not None:
        gs_asm_fallback = args.gs_asm_fallback
    else:
        gs_asm_fallback = _guess_gs_asm_fallback_root()

    try:
        ctx = build_s1_context(args.s1_root, gs_asm_fallback=gs_asm_fallback, verbose=not args.dry_run)
    except FileNotFoundError as error:
        print(f"error: {error}", file=sys.stderr)
        return 1

    if args.near_matches:
        try:
            gs_functions = build_gs_context()
        except FileNotFoundError as error:
            print(f"error: {error}", file=sys.stderr)
            return 1
        functions = select_near_match_functions(
            transfer_map, functions=args.functions, source=args.source, limit=args.limit
        )
        if args.dry_run:
            result = dry_run_near_matches(
                functions, ctx=ctx, gs_functions=gs_functions, s1_reverse_index=s1_reverse_index,
                minimum=args.near_min_similarity, strict=args.strict, show_text=args.show_text,
            )
        else:
            result = sweep_near_matches(
                functions, ctx=ctx, gs_functions=gs_functions, s1_reverse_index=s1_reverse_index,
                minimum=args.near_min_similarity, gate=not args.no_gate, workers=args.workers, strict=args.strict,
            )
        text = json.dumps(result, indent=2)
        if args.json:
            args.json.write_text(text + "\n")
        print(text)
        return 0

    functions = select_functions(
        transfer_map,
        functions=args.functions,
        source=args.source,
        limit=args.limit,
        allow_dirty=args.allow_dirty,
    )

    if args.dry_run:
        result = dry_run(
            functions, ctx=ctx, transfer_map=transfer_map, s1_reverse_index=s1_reverse_index,
            strict=args.strict, show_text=args.show_text,
        )
        text = json.dumps(result, indent=2)
        if args.json:
            args.json.write_text(text + "\n")
        print(text)
        return 0

    result = sweep(
        functions, ctx=ctx, transfer_map=transfer_map, s1_reverse_index=s1_reverse_index,
        gate=not args.no_gate, workers=args.workers, strict=args.strict,
    )
    text = json.dumps(result, indent=2)
    if args.json:
        args.json.write_text(text + "\n")
    print(text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
