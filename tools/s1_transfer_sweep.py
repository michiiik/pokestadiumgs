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

Usage:
    tools/s1_transfer_sweep.py --dry-run --limit 15
    tools/s1_transfer_sweep.py --dry-run --function func_800015C0
    tools/s1_transfer_sweep.py --limit 50 --json build/s1_transfer.json
    tools/s1_transfer_sweep.py --no-gate --source disasm/src/229E0.c

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
import re
import sys
import time
from dataclasses import dataclass, field
from pathlib import Path

import dedupe_externs
import pragma_targets as targets
import try_pragma_compare as runner
import xmatch_stadium1 as xmatch

REPO_ROOT = targets.REPO_ROOT
S1_TRANSFER_PATH = REPO_ROOT / "tools" / "s1_transfer.json"
GS_INCLUDE_ROOT = REPO_ROOT / "disasm" / "include"

EVIDENCE_RE = re.compile(r"Stadium 1 (\S+) @ 0x([0-9A-Fa-f]+)")

CONTROL_KEYWORDS = {
    "if", "for", "while", "switch", "return", "sizeof", "else", "do",
    "goto", "case", "default", "break", "continue",
}

# Opcodes that carry a %lo() immediate (the low half of a lui/lo pair): every
# I-type op other than lui itself.  We do not need the exact mnemonic set --
# any instruction whose GS operand text spells %lo(sym) qualifies -- but the
# register that holds the paired hi value always sits in the ``rs`` field
# (bits 25:21), whether the instruction is an arithmetic op consuming it as
# a source register or a load/store consuming it as a base register.


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


def parse_gs_asm(text: str) -> list[SourceInstr]:
    """Parse a splat ``.s`` disassembly into one entry per instruction.

    Only lines carrying the ``/* offset vram word */`` comment are
    instructions; ``glabel``/``.L...:`` lines are skipped, which is exactly
    what distinguishes a label from code here.
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
    return out


# --------------------------------------------------------------------------
# S1 address decoding from aligned machine words
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


def _rt(word: int) -> int:
    return (word >> 16) & 0x1F


def _rs(word: int) -> int:
    return (word >> 21) & 0x1F


@dataclass
class AddressDecodeResult:
    addresses: dict[int, int]          # gs instruction index -> decoded S1 address
    unresolved: list[int]              # indices with a symbol operand we could not decode


def decode_s1_addresses(gs_instrs: list[SourceInstr], s1_words: list[int]) -> AddressDecodeResult:
    """Decode, per GS instruction with a symbol operand, the S1 address it targets.

    ``jal``/``j`` decode directly.  ``%hi``/``%lo`` decode by pairing: a
    ``lui`` records the register it wrote; the next instruction whose ``rs``
    field is that register (an ``addiu``/... consuming it as a source, or a
    load/store using it as a base) is its ``%lo`` partner.  The register
    stays live across several ``%lo`` consumers (a base reused for more than
    one field access), so a hi is not consumed on first use.
    """
    addresses: dict[int, int] = {}
    unresolved: list[int] = []
    pending_hi: dict[int, int] = {}  # register -> gs index of the lui that wrote it
    for instr in gs_instrs:
        if instr.index >= len(s1_words):
            continue
        s1_word = s1_words[instr.index]
        if instr.jal_sym is not None:
            addresses[instr.index] = decode_jal_target(s1_word)
            continue
        if instr.hi_sym is not None:
            pending_hi[_rt(instr.word)] = instr.index
            # A %hi operand can, rarely, also be consumed the same
            # instruction has no %lo, so nothing else to do here.
        if instr.lo_sym is not None:
            hi_index = pending_hi.get(_rs(instr.word))
            if hi_index is None:
                unresolved.append(instr.index)
                continue
            addresses[instr.index] = decode_hilo_address(s1_words[hi_index], s1_word)
    return AddressDecodeResult(addresses=addresses, unresolved=unresolved)


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
    """name -> full definition text, across every header/source given."""
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
            full = text[match.start():semi + 1]
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
            index[name] = text[match.start():full_end]
        for match in _SIMPLE_TYPEDEF_RE.finditer(text):
            line = match.group(0)
            inner = re.match(r"[ \t]*typedef\s+(.*?)\s*;[ \t]*$", line)
            if not inner:
                continue
            name = _simple_typedef_name(inner.group(1))
            if name and name not in index:
                index[name] = line.strip()
    return index


def collect_type_definitions(
    seed_names: set[str], type_index: dict[str, str], *, max_depth: int = 4
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

    def visit(name: str, stack: frozenset[str]) -> None:
        if name in done or name not in type_defs or name in stack:
            return
        stack = stack | {name}
        for ident in re.findall(r"\b[A-Za-z_]\w*\b", type_defs[name]):
            if ident != name and ident in type_defs:
                visit(ident, stack)
        if name not in done:
            done.add(name)
            order.append(name)

    for name in type_defs:
        visit(name, frozenset())
    return order


def _normalize_ws(text: str) -> str:
    return re.sub(r"\s+", " ", text).strip()


# --------------------------------------------------------------------------
# extern declarations for mapped data globals
# --------------------------------------------------------------------------

_EXTERN_LINE_RE = re.compile(r"(?m)^[ \t]*extern\b[^;{}]*;")
_EXTERN_TRAILING_NAME_RE = re.compile(r"([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*;\s*$")


def index_extern_declarations(texts: list[str]) -> dict[str, str]:
    index: dict[str, str] = {}
    for text in texts:
        for match in _EXTERN_LINE_RE.finditer(text):
            line = match.group(0)
            trail = _EXTERN_TRAILING_NAME_RE.search(line)
            if not trail:
                continue
            name = trail.group(1)
            if name not in index:
                index[name] = line.strip()
    return index


# --------------------------------------------------------------------------
# Renaming
# --------------------------------------------------------------------------

def apply_rename(text: str, rename_map: dict[str, str]) -> str:
    if not rename_map:
        return text
    pattern = re.compile(
        r"\b(" + "|".join(re.escape(name) for name in sorted(rename_map, key=len, reverse=True)) + r")\b"
    )
    return pattern.sub(lambda m: rename_map[m.group(0)], text)


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
    gs_type_index: dict[str, str]
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
    func_file_index = index_function_files(c_paths)
    symtab.func_names.update(func_file_index)

    gs_header_texts = _read_texts(list(GS_INCLUDE_ROOT.rglob("*.h"))) if GS_INCLUDE_ROOT.is_dir() else []
    gs_type_index = index_type_definitions(gs_header_texts)

    return S1Context(
        root=s1_root,
        s1_functions=s1_functions,
        symtab=symtab,
        type_index=type_index,
        extern_index=extern_index,
        gs_type_index=gs_type_index,
        func_file_index=func_file_index,
        gs_asm_fallback=gs_asm_fallback,
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

    s1_func = ctx.s1_functions.get(s1_name)
    if s1_func is None:
        return TransferResult(function, "s1_function_missing", s1_name=s1_name,
                               detail=f"{s1_name} not found among S1 ROM functions")

    home = ctx.func_file_index.get(s1_name)
    definition = find_function_definition(s1_name, home) if home is not None else None
    if definition is None:
        return TransferResult(function, "s1_body_missing", s1_name=s1_name,
                               detail=f"no C definition found for {s1_name} under S1 disasm/src")
    full_definition, is_static = definition

    asm = gs_asm_text(owner, ctx.gs_asm_fallback)
    if asm is None:
        return TransferResult(function, "gs_asm_missing", s1_name=s1_name,
                               detail=str(owner.asm_path))
    asm_text, asm_source = asm
    gs_instrs = parse_gs_asm(asm_text)
    if not gs_instrs:
        return TransferResult(function, "gs_asm_unparseable", s1_name=s1_name)

    gs_words = [instr.word for instr in gs_instrs]
    s1_words = list(s1_func["w"])
    if len(gs_words) != len(s1_words):
        return TransferResult(
            function, "alignment_failed", s1_name=s1_name,
            detail=f"instruction count differs: gs={len(gs_words)} s1={len(s1_words)} (asm from {asm_source})",
        )
    for i, (g, s) in enumerate(zip(gs_words, s1_words)):
        if xmatch.norm(g) != xmatch.norm(s):
            return TransferResult(
                function, "alignment_failed", s1_name=s1_name,
                detail=f"instruction {i} differs: gs=0x{g:08X} s1=0x{s:08X}",
            )

    body_identifiers = set(re.findall(r"\b[A-Za-z_]\w*\b", full_definition))

    symbol_map: dict[str, str] = {s1_name: owner.function}
    unmapped: list[str] = []
    decode = decode_s1_addresses(gs_instrs, s1_words)
    for index in decode.unresolved:
        unmapped.append(f"index {index}: unpaired %lo (no preceding %hi to the same register)")
    for instr in gs_instrs:
        if instr.jal_sym is None and instr.hi_sym is None and instr.lo_sym is None:
            continue
        addr = decode.addresses.get(instr.index)
        gs_operand_name = instr.jal_sym or instr.hi_sym or instr.lo_sym
        if addr is None:
            continue  # already recorded via decode.unresolved
        resolved = resolve_s1_symbol(
            ctx.symtab, addr, is_call=instr.jal_sym is not None, body_identifiers=body_identifiers
        )
        if resolved is None:
            unmapped.append(f"{gs_operand_name} (S1 address 0x{addr:08X} unresolved)")
            continue
        s1_sym_name, offset = resolved
        if offset != 0:
            unmapped.append(f"{gs_operand_name} (S1 {s1_sym_name}+0x{offset:X}, not renamed)")
            continue
        existing = symbol_map.get(s1_sym_name)
        if existing is not None and existing != gs_operand_name:
            unmapped.append(f"{s1_sym_name} maps to both {existing} and {gs_operand_name}")
            continue
        symbol_map[s1_sym_name] = gs_operand_name

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
        )

    # Types the body needs, S1_-prefixed unless GS already has an identical
    # definition under the same name.
    candidate_type_names = {
        ident for ident in body_identifiers if ident in ctx.type_index
    }
    type_defs = collect_type_definitions(candidate_type_names, ctx.type_index)
    type_rename: dict[str, str] = {}
    kept_type_defs: dict[str, str] = {}
    for name, type_def in type_defs.items():
        gs_def = ctx.gs_type_index.get(name)
        if gs_def is not None and _normalize_ws(gs_def) == _normalize_ws(type_def):
            continue
        type_rename[name] = f"S1_{name}"
        kept_type_defs[name] = type_def

    rename_map = dict(symbol_map)
    rename_map.update(type_rename)

    ordered_type_defs = [apply_rename(kept_type_defs[name], rename_map) for name in order_types(kept_type_defs)]

    extra_externs: list[str] = []
    seen_externs: set[str] = set()
    for s1_sym, gs_sym in symbol_map.items():
        if s1_sym == s1_name or s1_sym in ctx.symtab.func_names:
            continue
        decl = ctx.extern_index.get(s1_sym)
        if decl is None or decl in seen_externs:
            continue
        seen_externs.add(decl)
        extra_externs.append(apply_rename(decl, rename_map))

    declarations = "\n".join(ordered_type_defs + extra_externs)
    if declarations:
        declarations += "\n"

    renamed_definition = apply_rename(full_definition, rename_map)

    variants: list[tuple[str, str]] = [("s1:transfer", renamed_definition.strip() + "\n")]
    if is_static:
        nostatic = re.sub(r"^\s*static\s+", "", renamed_definition, count=1)
        variants.append(("s1:transfer-nostatic", nostatic.strip() + "\n"))

    return TransferResult(
        function, "candidate", s1_name=s1_name, symbol_map=symbol_map,
        unmapped_symbols=unmapped, declarations=declarations,
        declaration_units=ordered_type_defs + extra_externs, variants=variants,
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


# --------------------------------------------------------------------------
# Driver
# --------------------------------------------------------------------------

def run_source_group(
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
            declaration_units.extend(result.declaration_units)
        elif result.declarations:
            # Keep compatibility with callers/tests that construct a result
            # using only the legacy rendered declaration block.
            declaration_units.append(result.declarations)
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
    parser.add_argument("--workers", type=int)
    parser.add_argument("--json", type=Path, help="write the summary to this file")
    parser.add_argument("--s1-root", type=Path, default=Path(xmatch.DEFAULT_S1))
    parser.add_argument("--gs-asm-fallback", type=Path, help="read-only fallback root for missing GS .s files")
    parser.add_argument("--no-gs-asm-fallback", action="store_true", help="disable the GS .s fallback lookup")
    parser.add_argument("--show-text", action="store_true", help="(--dry-run) also print declarations/candidate text")
    parser.add_argument("--transfer-map", type=Path, default=S1_TRANSFER_PATH)
    args = parser.parse_args()

    transfer_map = load_transfer_map(args.transfer_map)
    s1_reverse_index = build_s1_reverse_index(transfer_map)
    functions = select_functions(transfer_map, functions=args.functions, source=args.source, limit=args.limit)

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
