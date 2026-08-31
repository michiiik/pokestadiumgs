#!/usr/bin/env python3
"""Target discovery, assembly access, and m2c drafts for pragma-backed owners.

The candidate runner needs a source path and a function name.  This module
answers the questions that come before that call:

* which tracked source owns a ``GLOBAL_ASM`` pragma (``find_owner``);
* what the target assembly looks like (``function_asm``);
* which owners are small/simple enough to batch next (``list_targets``);
* which owners are shape-hard rather than merely unattempted, from recorded
  probe history (``load_owner_hardness``, ``targets --skip-ties``);
* which files are worth assigning to a fleet agent next
  (``rank-files``);
* what m2c proposes as a first C draft (``draft_candidates``).

Usage:
    tools/pragma_targets.py owner func_8410AE50
    tools/pragma_targets.py asm func_8410AE50
    tools/pragma_targets.py targets --max-instructions 12 --family direct_wrapper
    tools/pragma_targets.py targets --source disasm/src/585D0.c --skip-ties
    tools/pragma_targets.py rank-files --exclude-recent 4 --json
    tools/pragma_targets.py draft func_8410AE50

Everything here is read-only with respect to tracked sources.  Drafts are
hypotheses: send them through ``try_pragma_candidates`` like any other
candidate.
"""

from __future__ import annotations

import argparse
import collections
import difflib
import json
import os
import re
import subprocess
import threading
import sys
from dataclasses import dataclass
from datetime import datetime, timedelta, timezone
from pathlib import Path

import probe_stats
import scan_asm_families as scanner
import try_pragma_compare as runner
import variant_policy

REPO_ROOT = Path(__file__).resolve().parent.parent
DISASM_ROOT = REPO_ROOT / "disasm"
SOURCE_ROOT = DISASM_ROOT / "src"
ASM_ROOT = DISASM_ROOT / "asm" / "us" / "nonmatchings"
M2C_SCRIPT = DISASM_ROOT / "tools" / "m2c" / "m2c.py"
CONTEXT_CACHE_ROOT = DISASM_ROOT / "build" / "m2c-context"
SYMBOL_INDEX_HEADER = CONTEXT_CACHE_ROOT / "repo-prototypes.h"
FALLBACK_SYMBOL_INDEX_HEADER = CONTEXT_CACHE_ROOT / "repo-prototypes-fallback.h"
SYMBOL_ADDRS_PATH = DISASM_ROOT / "linker_scripts" / "us" / "symbol_addrs_code.txt"

PRAGMA_RE = re.compile(r'^#pragma GLOBAL_ASM\("(asm/us/nonmatchings/([^"]+)/([A-Za-z_]\w*)\.s)"\)$', re.M)

DRAFT_VARIANTS: dict[str, list[str]] = {
    "m2c": [],
    "m2c-no-casts": ["--no-casts"],
    "m2c-gotos": ["--gotos-only"],
}


def readonly_tool_path(relative: Path, *, override_name: str | None = None) -> Path:
    """Resolve an ignored read-only tool from the primary checkout.

    Linked worktrees do not contain the optional ``disasm/tools`` clones.
    Prefer the canonical primary path when it exists instead of requiring a
    mutable directory symlink in each worktree. Relative explicit overrides
    are anchored to this checkout, matching the runner's shared-venv rules.
    """
    if override_name:
        override = os.environ.get(override_name)
        if override:
            path = Path(os.path.expandvars(override)).expanduser()
            if not path.is_absolute():
                path = REPO_ROOT / path
            return path.resolve(strict=False)
    primary = runner._primary_worktree_root(REPO_ROOT)
    if primary is not None:
        shared = (primary / relative).resolve(strict=False)
        if shared.exists():
            return shared
    return (REPO_ROOT / relative).resolve(strict=False)


def readonly_tool_environment() -> dict[str, str]:
    """Return an environment that cannot create bytecode in shared tools."""
    environment = dict(os.environ)
    # This is a safety invariant, not a user-selectable tool option: an
    # inherited ``0`` must not permit a linked runner to mutate the primary
    # checkout's ignored read-only tool trees with ``__pycache__`` files.
    environment["PYTHONDONTWRITEBYTECODE"] = "1"
    return environment


def m2c_script() -> Path:
    return readonly_tool_path(
        Path("disasm/tools/m2c/m2c.py"), override_name="PRAGMA_M2C_SCRIPT"
    )


def _guess_asm_fallback_root() -> Path | None:
    """Read-only fallback root for a partially generated ``disasm/asm`` tree.

    ``disasm/asm/us/nonmatchings`` is generated per-checkout by splat
    extraction; an agent worktree may not have run it locally.  A given
    owner's ``.s`` is deterministic from the ROM + yaml, so it is safe to
    read (never write) the same relative path from the checkout this
    worktree was branched from.  Mirrors
    ``s1_transfer_sweep._guess_gs_asm_fallback_root`` for the
    ``.claude/worktrees/<name>`` layout used by this agent harness; an
    ordinary (non-worktree) checkout has nothing to fall back to and this
    returns ``None``.
    """
    env = os.environ.get("PRAGMA_ASM_FALLBACK_ROOT")
    if env:
        candidate = Path(env)
        return candidate if candidate.is_dir() else None
    parent = REPO_ROOT.parent
    if parent.name == "worktrees" and parent.parent.name == ".claude":
        candidate = parent.parent.parent
        if candidate.is_dir() and (candidate / "disasm" / "asm").is_dir():
            return candidate
    return None


_ASM_FALLBACK_ROOT = _guess_asm_fallback_root()


@dataclass(frozen=True)
class Owner:
    function: str
    source: str  # repository-relative POSIX path
    asm: str  # repository-relative POSIX path

    @property
    def source_path(self) -> Path:
        return REPO_ROOT / self.source

    @property
    def asm_path(self) -> Path:
        primary = REPO_ROOT / self.asm
        if primary.exists() or _ASM_FALLBACK_ROOT is None:
            return primary
        fallback = _ASM_FALLBACK_ROOT / self.asm
        return fallback if fallback.exists() else primary

    def as_dict(self) -> dict[str, object]:
        return {
            "function": self.function,
            "source": self.source,
            "asm": self.asm,
            "asm_exists": self.asm_path.exists(),
        }


_INDEX_SNAPSHOT: tuple[tuple[str, int], ...] | None = None
_INDEX: dict[str, Owner] = {}
_CLASSIFICATION_CACHE: dict[tuple[str, int], dict[str, object]] = {}
_RODATA_OWNER_CACHE: dict[tuple[str, int], set[str]] = {}


def _rodata_subsegment_owners(*, repo_root: Path | None = None) -> set[str]:
    """Return source keys with an explicit US per-file rodata subsegment.

    The jump-table layout work is intentionally not inferred from the data
    blobs: only a dotted ``.rodata``/``.late_rodata`` YAML entry makes a
    source file ready for a C switch.  Missing YAML (notably synthetic test
    roots) is treated as no known entries and remains safe for callers.
    """
    root = repo_root or REPO_ROOT
    yaml_path = root / "disasm" / "yamls" / "us" / "rom.yaml"
    try:
        stamp = yaml_path.stat().st_mtime_ns
    except OSError:
        return set()
    cache_key = (yaml_path.as_posix(), stamp)
    cached = _RODATA_OWNER_CACHE.get(cache_key)
    if cached is not None:
        return cached
    owners: set[str] = set()
    try:
        for line in yaml_path.read_text(encoding="utf-8", errors="replace").splitlines():
            # Per-file entries are [address, .rodata, source-key].  Keep this
            # textual so the helper has no YAML dependency.
            match = re.search(
                r"\[\s*[^,]+,\s*\.(?:rodata|late_rodata)\s*,\s*([^\]\s#]+)",
                line,
            )
            if match:
                owners.add(match.group(1).strip("\"'"))
    except OSError:
        return set()
    _RODATA_OWNER_CACHE[cache_key] = owners
    return owners


def _jump_table_readiness(
    owner: Owner,
    row: dict[str, object],
    *,
    repo_root: Path | None = None,
) -> tuple[bool, bool]:
    """Return ``(ready, unready)`` for an owner's jump-table layout."""
    has_jump_table = bool(row.get("jump_tables"))
    source_key = owner.source.removeprefix("disasm/src/").removesuffix(".c")
    has_subsegment = source_key in _rodata_subsegment_owners(repo_root=repo_root)
    return (has_jump_table and has_subsegment, has_jump_table and not has_subsegment)


def _source_files(source_root: Path) -> list[Path]:
    return [
        path
        for path in sorted(source_root.rglob("*.c"))
        if not any(part.startswith(".pragma_probe_") for part in path.parts)
    ]


def owner_index(
    source_root: Path = SOURCE_ROOT,
    *,
    repo_root: Path = REPO_ROOT,
    refresh: bool = False,
) -> dict[str, Owner]:
    """Return ``{function: Owner}`` for every remaining pragma.

    The scan is cached per process and invalidated by the set of source
    paths and their modification times, so a runner installing a candidate
    (or another session committing one) is reflected on the next call.
    """
    global _INDEX_SNAPSHOT, _INDEX
    files = _source_files(source_root)
    snapshot = tuple((path.as_posix(), path.stat().st_mtime_ns) for path in files)
    custom_root = source_root != SOURCE_ROOT
    if not custom_root and not refresh and snapshot == _INDEX_SNAPSHOT:
        return _INDEX
    index: dict[str, Owner] = {}
    for path in files:
        text = path.read_text(encoding="utf-8", errors="replace")
        source_rel = path.relative_to(repo_root).as_posix()
        for match in PRAGMA_RE.finditer(text):
            function = match.group(3)
            index.setdefault(
                function,
                Owner(function=function, source=source_rel, asm="disasm/" + match.group(1)),
            )
    if not custom_root:
        _INDEX_SNAPSHOT = snapshot
        _INDEX = index
    return index


def find_owner(function: str) -> Owner | None:
    return owner_index().get(function)


def require_owner(function: str) -> Owner:
    owner = find_owner(function)
    if owner is None:
        raise KeyError(f"no GLOBAL_ASM pragma owns {function}")
    return owner


def function_asm(function: str) -> dict[str, object]:
    owner = require_owner(function)
    text = owner.asm_path.read_text(encoding="utf-8")
    _, instructions, _ = scanner.parse_instructions(text)
    return {
        **owner.as_dict(),
        "instruction_count": len(instructions),
        "text": text,
    }


def _classify_owner(owner: Owner) -> dict[str, object]:
    key = (owner.asm, owner.asm_path.stat().st_mtime_ns)
    cached = _CLASSIFICATION_CACHE.get(key)
    if cached is not None:
        return cached
    text = owner.asm_path.read_text(encoding="utf-8")
    _, instructions, labels = scanner.parse_instructions(text)
    calls = scanner.extract_calls(instructions)
    globals_ = scanner.extract_globals(text)
    jump_tables = scanner.extract_jump_tables(text)
    accesses = scanner.extract_memory_accesses(instructions)
    bounds = scanner.extract_bounds(instructions)
    loops = scanner.has_loop(instructions, labels)
    family, confidence, notes = scanner.classify(
        instructions, calls, globals_, jump_tables, accesses, bounds, loops
    )
    row: dict[str, object] = {
        "function": owner.function,
        "source": owner.source,
        "asm": owner.asm,
        "family": family,
        "confidence": confidence,
        "instructions": len(instructions),
        "branches": sum(instruction.op in scanner.BRANCH_OPS for instruction in instructions),
        "loops": loops,
        "calls": calls,
        "globals": globals_,
        "jump_tables": jump_tables,
        "notes": notes,
    }
    _CLASSIFICATION_CACHE[key] = row
    return row


def list_targets(
    *,
    source: str | None = None,
    family: str | None = None,
    max_instructions: int | None = None,
    min_instructions: int | None = None,
    limit: int = 50,
    skip_ties: bool = False,
    stats_paths=None,
    repo_root: Path | None = None,
) -> dict[str, object]:
    """Rank remaining owners by size so small same-shape batches are easy to pick.

    Every row also carries recorded probe-hardness fields (``prior_attempts``,
    ``best_similarity``, ``best_mismatch_kind``, ``best_raw_similarity``,
    ``last_attempt``, and a one-word ``hardness`` label -- see
    ``OwnerHardness``), loaded once for the whole call via
    ``load_owner_hardness(stats_paths)``, not per owner. ``skip_ties=True``
    additionally hides owners whose ``hardness`` is a register-allocation
    tie (``OwnerHardness.is_tie``) -- the ``585D0.c`` shape that a fresh
    agent's time box is unlikely to close.
    """
    owners = list(owner_index().values())
    if source:
        wanted = source.replace("\\", "/").removeprefix("./")
        owners = [owner for owner in owners if owner.source == wanted or owner.source.endswith("/" + wanted)]
    hardness = load_owner_hardness(stats_paths)
    rows: list[dict[str, object]] = []
    family_counts: dict[str, int] = {}
    for owner in owners:
        if not owner.asm_path.exists():
            continue
        row = dict(_classify_owner(owner))  # copy: _classify_owner's cache is shared, never mutate it
        count = int(row["instructions"])
        if max_instructions is not None and count > max_instructions:
            continue
        if min_instructions is not None and count < min_instructions:
            continue
        family_counts[str(row["family"])] = family_counts.get(str(row["family"]), 0) + 1
        if family and row["family"] != family:
            continue
        ready, unready = _jump_table_readiness(owner, row, repo_root=repo_root)
        row["jump_table_ready"] = ready
        row["jump_table_unready"] = unready
        row["jump_table_status"] = "ready" if ready else ("unready" if unready else "not_applicable")
        h = hardness.get(owner.function, _EMPTY_HARDNESS)
        if skip_ties and h.is_tie:
            continue
        row.update(h.as_dict())
        row["hardness"] = h.label
        rows.append(row)
    rows.sort(key=lambda row: (int(row["instructions"]), str(row["source"]), str(row["function"])))
    return {
        "matched": len(rows),
        "family_counts": dict(sorted(family_counts.items())),
        "targets": rows[: max(0, limit)],
        "truncated": len(rows) > limit,
    }


_CONTEXT_CACHE_LOCK = threading.Lock()
_CONTEXT_CACHE_PATH_LOCKS: dict[Path, threading.Lock] = {}
_SYMBOL_INDEX_LOCK = threading.Lock()
_SYMBOL_INDEX_SNAPSHOT: tuple[tuple[str, int], ...] | None = None


def _context_cache_lock(cache_path: Path) -> threading.Lock:
    """One lock per cache file: pooled drafts of the same source must not race."""
    with _CONTEXT_CACHE_LOCK:
        return _CONTEXT_CACHE_PATH_LOCKS.setdefault(cache_path, threading.Lock())


_SYMBOL_RE = re.compile(r"\b(?:func_[0-9A-Fa-f]+|D_[0-9A-Fa-f]+)\b")
_EXTERN_DECL_RE = re.compile(r"\bextern\s+([^;{}]+);")
_CONTEXT_TYPE_NAMES: set[str] | None = None
_CONTEXT_TYPE_LOCK = threading.Lock()

# These are the names that can occur in a declaration without a typedef from
# one of the project's headers.  The generated index is included before the
# owner source, so importing a source-local ``typedef struct ...`` is not
# safe: its name may be absent (or mean something different) in the next
# owner.  Keep this list deliberately broad for the compiler's built-in and
# N64 ABI spellings; project typedefs are added by _context_type_names().
_BUILTIN_CONTEXT_TYPES = {
    "void", "char", "signed", "unsigned", "short", "int", "long", "float",
    "double", "const", "volatile", "restrict", "static", "struct", "union",
    "enum", "_Bool", "bool", "true", "false", "__signed", "__attribute__",
    "u8", "u16", "u32", "u64", "s8", "s16", "s32", "s64", "f32", "f64",
    "size_t", "ptrdiff_t", "intptr_t", "uintptr_t", "wchar_t", "va_list",
}


def _context_type_names() -> set[str]:
    """Return typedef/tag names provided by the global include tree.

    Parsing headers is enough here and avoids making every m2c draft invoke a
    compiler just to decide whether a prototype is portable.  In particular,
    the ``} Alias;`` form catches the multi-line N64 structs such as ``Gfx``
    that a single-line typedef regex would miss.
    """
    global _CONTEXT_TYPE_NAMES
    with _CONTEXT_TYPE_LOCK:
        if _CONTEXT_TYPE_NAMES is not None:
            return _CONTEXT_TYPE_NAMES
        names = set(_BUILTIN_CONTEXT_TYPES)
        roots = (DISASM_ROOT / "include", DISASM_ROOT / "lib" / "ultralib" / "include")
        for root in roots:
            if not root.is_dir():
                continue
            for path in root.rglob("*.h"):
                try:
                    text = path.read_text(encoding="utf-8", errors="replace")
                except OSError:
                    continue
                # Named struct/union/enum tags can be used directly in a
                # prototype even when their typedef alias is not present.
                names.update(re.findall(r"\b(?:struct|union|enum)\s+([A-Za-z_]\w*)", text))
                for match in re.finditer(r"\btypedef\b(.*?);", text, re.S):
                    body = match.group(1)
                    pointer_alias = re.search(r"\(\s*\*\s*([A-Za-z_]\w*)\s*\)", body)
                    if pointer_alias:
                        names.add(pointer_alias.group(1))
                        continue
                    aliases = re.findall(
                        r"\b([A-Za-z_]\w*)\b\s*(?:\[[^\]]*\])?\s*$", body.strip()
                    )
                    if aliases:
                        names.add(aliases[-1])
                names.update(
                    re.findall(r"\}\s*([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*;", text)
                )
        _CONTEXT_TYPE_NAMES = names
        return names


def _declaration_type_fragments(declaration: str) -> list[str]:
    """Extract return/global and parameter type fragments from a prototype."""
    text = declaration.strip().removesuffix(";").strip()
    text = re.sub(r"^extern\s+", "", text)
    function = re.search(r"\bfunc_[0-9A-Fa-f]+\s*\(", text)
    if function:
        fragments = [text[: function.start()].strip()]
        start = function.end() - 1
        end = text.rfind(")")
        if end > start:
            params = text[start + 1 : end]
            # Function prototypes produced from the source tree do not use
            # nested commas except in function-pointer parameters.  Keeping
            # such a parameter as one fragment is conservative: it will be
            # omitted if its callback typedef is not globally known.
            fragments.extend(params.split(","))
        return fragments
    symbol = re.search(r"\bD_[0-9A-Fa-f]+\b", text)
    if symbol:
        return [text[: symbol.start()].strip()]
    return [text]


def _declaration_has_unknown_context_type(declaration: str) -> bool:
    """Whether a declaration references a typedef unavailable to all owners."""
    known = _context_type_names()
    for index, fragment in enumerate(_declaration_type_fragments(declaration)):
        fragment = fragment.strip()
        if not fragment:
            continue
        if index and fragment != "void":
            # Drop the parameter's declarator name (``u8 value`` or
            # ``SomeType *ptr``) before checking the remaining type tokens.
            fragment = re.sub(
                r"(?:\*+\s*|\b[A-Za-z_]\w*\s+)([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?$",
                lambda match: match.group(0)[: match.group(0).rfind(match.group(1))].rstrip(),
                fragment,
            )
        tokens = re.findall(r"\b[A-Za-z_]\w*\b", fragment)
        if any(token not in known for token in tokens):
            return True
    return False


def _normalise_declaration(declaration: str) -> str:
    """Collapse source whitespace while preserving C pointer spelling."""
    return re.sub(r"\s+", " ", declaration.strip())


def _source_symbol_declarations(path: Path) -> tuple[set[str], list[tuple[str, str, bool]]]:
    """Extract simple function/global declarations from one C source.

    The index intentionally records only declarations whose names are tied to
    a ROM symbol.  Bodies and source-local typedefs stay out of the generated
    header; owner-local context already supplies those and importing them
    globally would create more conflicts than it solves.
    """
    text = path.read_text(encoding="utf-8", errors="replace")
    symbols: set[str] = set()
    declarations: list[tuple[str, str, bool]] = []

    for match in _EXTERN_DECL_RE.finditer(text):
        declaration = _normalise_declaration("extern " + match.group(1)) + ";"
        names = _SYMBOL_RE.findall(declaration)
        if len(names) == 1:
            symbols.add(names[0])
            declarations.append((names[0], declaration, False))

    # Most decompiled bodies put the complete signature on the line that
    # opens the body.  Convert that prefix into a prototype.  Splitting after
    # the last semicolon also handles compact ``extern ...; void func(...)``
    # lines already present in the source tree.
    for line in text.splitlines():
        if "{" not in line or "func_" not in line:
            continue
        prefix = line.split("{", 1)[0].rsplit(";", 1)[-1].strip()
        names = _SYMBOL_RE.findall(prefix)
        if len(names) != 1 or not re.search(r"\bfunc_[0-9A-Fa-f]+\s*\(", prefix):
            continue
        declaration = _normalise_declaration(prefix) + ";"
        symbols.add(names[0])
        declarations.append((names[0], declaration, True))

    return symbols, declarations


def repository_symbol_header(
    *,
    source_root: Path = SOURCE_ROOT,
    output_path: Path = SYMBOL_INDEX_HEADER,
    refresh: bool = False,
) -> Path | None:
    """Build a cached header of unambiguous cross-source ROM declarations.

    This is deliberately conservative.  A symbol with conflicting spellings,
    or a declaration that depends on a source-local ``S1_`` type, is omitted;
    m2c can still fall back to its targeted type variants for those owners.
    """
    global _SYMBOL_INDEX_SNAPSHOT
    files = _source_files(source_root)
    snapshot = tuple((path.as_posix(), path.stat().st_mtime_ns) for path in files)
    with _SYMBOL_INDEX_LOCK:
        if not refresh and output_path.exists() and snapshot == _SYMBOL_INDEX_SNAPSHOT:
            return output_path
        by_symbol: dict[str, set[tuple[str, bool]]] = {}
        for path in files:
            _, declarations = _source_symbol_declarations(path)
            for symbol, declaration, is_definition in declarations:
                # Source-local typedefs are not available to every owner
                # context.  Skipping them avoids turning a useful prototype
                # index into a global compile failure; the owner-local source
                # remains available to m2c when it really needs that type.
                if re.search(r"\bS1_[A-Za-z0-9_]*\b", declaration):
                    continue
                if _declaration_has_unknown_context_type(declaration):
                    continue
                by_symbol.setdefault(symbol, set()).add((declaration, is_definition))
        selected: list[str] = []
        for symbol, declarations in sorted(by_symbol.items()):
            definitions = {decl for decl, is_definition in declarations if is_definition}
            spellings = definitions or {decl for decl, _ in declarations}
            if len(spellings) != 1:
                continue
            selected.append(next(iter(spellings)))
        output_path.parent.mkdir(parents=True, exist_ok=True)
        temporary = output_path.with_name(output_path.name + f".{os.getpid()}.tmp")
        body = "\n".join([
            "#ifndef PRAGMA_REPO_PROTOTYPES_H",
            "#define PRAGMA_REPO_PROTOTYPES_H",
            '#include "global.h"',
            "/* Generated from unambiguous declarations in disasm/src. */",
            *selected,
            "#endif",
            "",
        ])
        temporary.write_text(body, encoding="utf-8")
        os.replace(temporary, output_path)
        if source_root == SOURCE_ROOT and output_path == SYMBOL_INDEX_HEADER:
            _SYMBOL_INDEX_SNAPSHOT = snapshot
        return output_path


def all_declared_symbols(source_root: Path = SOURCE_ROOT) -> set[str]:
    """Return every symbol name declared or defined anywhere in ``source_root``.

    Unlike ``repository_symbol_header``'s output, this is not filtered down
    to unambiguous single-spelling declarations -- it only answers "does any
    source say anything about this symbol at all", which is what the
    fallback-prototype synthesizer needs to stay conservative: a symbol with
    conflicting declarations across sources still counts as declared here,
    so it is never given a synthesized old-style prototype on top.
    """
    declared: set[str] = set()
    for path in _source_files(source_root):
        symbols, _ = _source_symbol_declarations(path)
        declared.update(symbols)
    return declared


# ---------------------------------------------------------------------------
# Fallback prototype synthesis
#
# ``repository_symbol_header`` only ever emits a declaration for a symbol
# some tracked source already declares or defines.  A candidate can still
# call a ``func_XXXXXXXX`` that is genuinely undeclared anywhere -- an
# unclaimed leftover in ``symbol_addrs_code.txt`` that no source references
# yet, or a sibling owner nobody has drafted a declaration for -- and IDO
# rejects that call with "No prototype for the call to func_..." or a
# related "undefined" error.  The functions below synthesize a compile-safe,
# old-style (unprototyped) fallback prototype straight from the target's own
# assembly, so a call to it can compile without claiming to know the real
# signature.
# ---------------------------------------------------------------------------

_FUNC_SYMBOL_ADDR_RE = re.compile(
    r"^(func_[0-9A-Fa-f]+)\s*=\s*0x[0-9A-Fa-f]+;\s*//\s*type:func\b", re.M
)
_ASM_FUNC_STEM_RE = re.compile(r"^func_[0-9A-Fa-f]+$")

_ARG_REGISTERS: tuple[str, ...] = ("a0", "a1", "a2", "a3")
_RETURN_REGISTER = "v0"

# Instructions whose operand registers are all reads: no general-purpose
# register is written by the instruction itself.  Stores write memory, not a
# GPR; branches and jumps only read their operands; multiply/divide write
# the implicit hi/lo pair, not a named register; ``mtc1``/``mthi``/``mtlo``
# move a GPR's value *into* somewhere else, so their GPR operand is a read,
# not the generic "first operand is the destination" default below.
_ASM_READ_ONLY_OPS = frozenset({
    "sb", "sh", "sw", "swc1", "sdc1", "swl", "swr",
    "beq", "beql", "bne", "bnel", "beqz", "bnez",
    "bltz", "bltzl", "bgez", "bgezl", "blez", "blezl", "bgtz", "bgtzl",
    "b", "jr", "jalr",
    "mult", "multu", "div", "divu",
    "madd", "maddu", "msub", "msubu",
    "mtc1", "dmtc1", "ctc1", "mthi", "mtlo",
})
_ASM_LOAD_OPS = frozenset({"lb", "lbu", "lh", "lhu", "lw", "lwc1", "ldc1", "lwl", "lwr"})
_ASM_REG_TOKEN_RE = re.compile(r"\$([A-Za-z0-9]+)")
_ASM_SP_OFFSET_RE = re.compile(r",\s*(-?(?:0x[0-9A-Fa-f]+|\d+))\(\$sp\)\s*$")


def _asm_parse_offset(token: str) -> int | None:
    try:
        return int(token, 0)
    except ValueError:
        return None


def infer_prototype_shape(asm_text: str) -> tuple[int | None, str]:
    """Infer a synthesized old-style prototype's arity and return type.

    Returns ``(arity, return_type)``.  ``arity`` is the highest-numbered
    ``$a0..$a3`` register read before it is written anywhere in the
    function (capped at 4 by construction), or ``None`` when the function
    reads a stack-passed argument -- an ``off($sp)`` load with
    ``off >= 0x10`` seen before the function's own prologue adjusts
    ``$sp`` -- meaning it takes more integer arguments than fit in
    registers.  ``return_type`` is ``"s32"`` when ``$v0`` is written
    anywhere before the function's ``jr $ra``, else ``"void"``.

    This is a compile-safety heuristic, not ABI reconstruction: the emitted
    prototype (see ``synthesize_fallback_prototype``) is always the
    old-style, parameter-list-free form regardless of ``arity``, so any call
    site's real argument count still compiles.  ``arity`` exists so the
    heuristic itself stays independently testable and inspectable.
    """
    _, instructions, _ = scanner.parse_instructions(asm_text)
    arg_status: dict[str, str] = {}
    v0_written = False
    prologue_done = False
    stack_args = False
    for instruction in instructions:
        op = instruction.op
        operands = instruction.operands
        if not prologue_done:
            if op == "addiu":
                tokens = scanner.operand_tokens(operands)
                if len(tokens) == 3 and tokens[0] == "$sp" and tokens[1] == "$sp":
                    value = scanner.parse_int(tokens[2])
                    if value is not None and value < 0:
                        prologue_done = True
            if not prologue_done and op in _ASM_LOAD_OPS:
                match = _ASM_SP_OFFSET_RE.search(operands)
                if match:
                    offset = _asm_parse_offset(match.group(1))
                    if offset is not None and offset >= 0x10:
                        stack_args = True
        registers = _ASM_REG_TOKEN_RE.findall(operands)
        if op in _ASM_READ_ONLY_OPS:
            writes, reads = [], registers
        else:
            writes, reads = (registers[:1], registers[1:]) if registers else ([], [])
        # Reads are classified before writes within the same instruction so
        # a self-referencing op (``sll $a0, $a0, 8``) still counts as "read"
        # when it is the register's first appearance: the shift reads the
        # value the caller passed in before overwriting it.
        for register in reads:
            if register in _ARG_REGISTERS and register not in arg_status:
                arg_status[register] = "read"
        for register in writes:
            if register == _RETURN_REGISTER:
                v0_written = True
            if register in _ARG_REGISTERS and register not in arg_status:
                arg_status[register] = "write"
        if op == "jr" and registers[:1] == ["ra"]:
            break
    return_type = "s32" if v0_written else "void"
    if stack_args:
        return None, return_type
    arity = 0
    for index, register in enumerate(_ARG_REGISTERS):
        if arg_status.get(register) == "read":
            arity = index + 1
    return arity, return_type


def synthesize_fallback_prototype(function: str, asm_text: str) -> str:
    """Return a compile-safe, old-style fallback prototype line for ``function``.

    The parameter list is always omitted (``func_X();``, not
    ``func_X(s32, s32);``): an old-style declaration with empty parens tells
    the compiler not to type-check call sites against it at all, so any real
    argument count still compiles.  Only the inferred return type varies.
    """
    _, return_type = infer_prototype_shape(asm_text)
    return f"{return_type} {function}(); /* synthesized */"


def repository_fallback_symbol_header(
    *,
    source_root: Path = SOURCE_ROOT,
    symbol_addrs_path: Path = SYMBOL_ADDRS_PATH,
    asm_root: Path = ASM_ROOT,
    output_path: Path = FALLBACK_SYMBOL_INDEX_HEADER,
    repo_root: Path = REPO_ROOT,
    refresh: bool = False,
) -> Path | None:
    """Build a header of synthesized fallback prototypes, included after the
    source-derived ``repository_symbol_header`` and strictly lower priority
    than it: only a ``func_XXXXXXXX`` with no declaration in any tracked
    source, and no currently-open ``GLOBAL_ASM`` pragma of its own, gets a
    synthesized line here.  A missing ``symbol_addrs_path`` (a test fixture
    that only exercises ``infer_prototype_shape`` directly, for example) is
    not an error: the header is simply just the include guard.
    """
    if not symbol_addrs_path.exists():
        output_path.parent.mkdir(parents=True, exist_ok=True)
        body = "\n".join([
            "#ifndef PRAGMA_REPO_PROTOTYPES_FALLBACK_H",
            "#define PRAGMA_REPO_PROTOTYPES_FALLBACK_H",
            "#endif",
            "",
        ])
        output_path.write_text(body, encoding="utf-8")
        return output_path

    dependency_mtime = symbol_addrs_path.stat().st_mtime_ns
    for path in _source_files(source_root):
        dependency_mtime = max(dependency_mtime, path.stat().st_mtime_ns)
    if not refresh and output_path.exists() and output_path.stat().st_mtime_ns >= dependency_mtime:
        return output_path

    declared = all_declared_symbols(source_root)
    owners = set(owner_index(source_root, repo_root=repo_root, refresh=refresh).keys())
    text = symbol_addrs_path.read_text(encoding="utf-8", errors="replace")
    wanted = [
        match.group(1)
        for match in _FUNC_SYMBOL_ADDR_RE.finditer(text)
        if match.group(1) not in declared and match.group(1) not in owners
    ]
    if not wanted:
        stems: dict[str, Path] = {}
    else:
        stems = {
            path.stem: path
            for path in asm_root.rglob("*.s")
            if _ASM_FUNC_STEM_RE.match(path.stem)
        }

    selected: list[str] = []
    for function in wanted:
        asm_path = stems.get(function)
        if asm_path is None:
            continue
        try:
            asm_text = asm_path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        selected.append(synthesize_fallback_prototype(function, asm_text))

    output_path.parent.mkdir(parents=True, exist_ok=True)
    temporary = output_path.with_name(output_path.name + f".{os.getpid()}.tmp")
    body = "\n".join([
        "#ifndef PRAGMA_REPO_PROTOTYPES_FALLBACK_H",
        "#define PRAGMA_REPO_PROTOTYPES_FALLBACK_H",
        "/* Synthesized old-style fallback prototypes for func_XXXXXXXX symbols with",
        " * no declaration in disasm/src.  See pragma_targets.repository_fallback_symbol_header. */",
        *selected,
        "#endif",
        "",
    ])
    temporary.write_text(body, encoding="utf-8")
    os.replace(temporary, output_path)
    return output_path


def _owner_symbol_header(owner: Owner, symbol_header: Path, *, refresh: bool = False) -> Path:
    """Remove declarations already present in an owner's source context."""
    declared, _ = _source_symbol_declarations(owner.source_path)
    if not declared:
        return symbol_header
    relative = Path(owner.source).with_suffix(".h")
    output_path = CONTEXT_CACHE_ROOT / "owner-prototypes" / relative
    dependency_mtime = max(owner.source_path.stat().st_mtime_ns, symbol_header.stat().st_mtime_ns)
    if not refresh and output_path.exists() and output_path.stat().st_mtime_ns >= dependency_mtime:
        return output_path
    lines = symbol_header.read_text(encoding="utf-8").splitlines()
    filtered = [
        line for line in lines
        if not any(re.search(rf"\b{re.escape(symbol)}\b", line) for symbol in declared)
    ]
    output_path.parent.mkdir(parents=True, exist_ok=True)
    temporary = output_path.with_name(output_path.name + f".{os.getpid()}.{threading.get_ident()}.tmp")
    temporary.write_text("\n".join(filtered) + "\n", encoding="utf-8")
    os.replace(temporary, output_path)
    return output_path


def preprocessed_context(owner: Owner, *, refresh: bool = False) -> Path | None:
    """Return a cached, host-preprocessed copy of the owner's source.

    m2c reads variable types, prototypes, and structs from this file.  It is
    regenerated whenever the tracked source changes.  ``None`` means the host
    preprocess command could not be captured or failed; drafts then run
    without a context.
    """
    symbol_header = repository_symbol_header(refresh=refresh)
    if symbol_header is not None:
        symbol_header = _owner_symbol_header(owner, symbol_header, refresh=refresh)
    check = runner.host_check_recipe(REPO_ROOT)
    if check is None:
        return None
    source_rel = owner.source_path.relative_to(DISASM_ROOT)
    cache_path = CONTEXT_CACHE_ROOT / source_rel.with_suffix(".ctx.c")
    with _context_cache_lock(cache_path):
        return _refresh_preprocessed_context(owner, check, source_rel, cache_path, symbol_header, refresh)


def _refresh_preprocessed_context(
    owner: Owner,
    check: list[str],
    source_rel: Path,
    cache_path: Path,
    symbol_header: Path | None,
    refresh: bool,
) -> Path | None:
    try:
        dependency_mtime = owner.source_path.stat().st_mtime_ns
        if symbol_header is not None:
            dependency_mtime = max(dependency_mtime, symbol_header.stat().st_mtime_ns)
        if (
            not refresh
            and cache_path.exists()
            and cache_path.stat().st_mtime_ns >= dependency_mtime
        ):
            return cache_path
    except OSError:
        pass
    include_directory = source_rel.parent.as_posix() + "/"
    command = runner.host_preprocess_command(check, include_directory)
    if symbol_header is not None:
        command += ["-include", symbol_header.relative_to(DISASM_ROOT).as_posix()]
    command += [source_rel.as_posix()]
    try:
        result = subprocess.run(
            command,
            cwd=DISASM_ROOT,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=runner._command_timeout("PRAGMA_COMPILE_TIMEOUT", 120.0),
        )
    except (OSError, subprocess.TimeoutExpired):
        return None
    if result.returncode != 0:
        return None
    cache_path.parent.mkdir(parents=True, exist_ok=True)
    # Write atomically: another thread's m2c may already be reading the
    # previous context for this source.
    temporary = cache_path.with_name(cache_path.name + f".{os.getpid()}.{threading.get_ident()}.tmp")
    temporary.write_text(result.stdout, encoding="utf-8")
    os.replace(temporary, cache_path)
    return cache_path


# The active probe-stats file at import time (see ``probe_stats.stats_path``
# for the ``PRAGMA_PROBE_STATS`` contract; like the historical constant this
# replaces, it is frozen at import time -- callers that need the *current*
# env-resolved path should use ``probe_stats.stats_path()`` directly).  This
# is also the default single-file target every reader below falls back to;
# ``None``/omitted goes through ``probe_stats`` instead, which additionally
# reads the legacy ``disasm/build/probe-stats.jsonl`` and any rotated file.
STATS_PATH = probe_stats.DEFAULT_STATS_PATH
_SOLVED_CACHE: tuple[tuple[tuple[str, int], ...], list[dict[str, object]]] | None = None


def _opcode_sequence(asm_text: str) -> list[str]:
    _, instructions, _ = scanner.parse_instructions(asm_text)
    return [instruction.op for instruction in instructions]


def solved_shapes(
    stats_path: Path | None = None, *, asm_roots: list[Path] | None = None
) -> list[dict[str, object]]:
    """Return accepted candidates from the stats file with their target opcode shape.

    Winners are the best available evidence of which C spelling IDO turns
    into a given instruction shape.  The ``.s`` files stay in the tree after
    a pragma is replaced, so each winner's shape can still be computed.

    ``asm_roots`` overrides the single ``ASM_ROOT`` scan for where a
    winner's own ``.s`` might live, tried in order -- a caller whose local
    ``nonmatchings`` tree is only partially extracted passes its own root
    followed by a read-only fallback root (see
    ``s1_transfer_sweep.gs_asm_text``), so a winner extracted only in the
    fallback tree is still found.
    """
    global _SOLVED_CACHE
    effective_stats = stats_path or STATS_PATH
    roots = asm_roots or [ASM_ROOT]
    # ``resolve_paths`` also picks up any ``<stem>.<N><suffix>`` rotated
    # sibling of ``effective_stats`` (see ``probe_stats.rotate_if_needed``);
    # an explicit ``stats_path`` reads exactly that file's own history, while
    # the default ``STATS_PATH`` does not additionally pull in the legacy
    # ``disasm/build/`` file -- run ``python3 tools/probe_stats.py migrate``
    # once to fold that history into the new location instead.
    resolved = probe_stats.resolve_paths([effective_stats])
    if not resolved:
        return []
    stamp = tuple(sorted((str(path), path.stat().st_mtime_ns) for path in resolved))
    cache_key = (stamp, tuple(str(root) for root in roots))
    if _SOLVED_CACHE is not None and _SOLVED_CACHE[0] == cache_key:
        return _SOLVED_CACHE[1]
    solved: dict[str, dict[str, object]] = {}
    asm_by_function: dict[str, Path] = {}
    for root in roots:
        if not root.is_dir():
            continue
        for path in root.rglob("*.s"):
            asm_by_function.setdefault(path.stem, path)
    for record in probe_stats.iter_batches([effective_stats]):
        for attempt in record.get("attempts", []):
            if attempt.get("status") != "accepted" or not attempt.get("candidate"):
                continue
            function = str(attempt.get("function"))
            asm_path = asm_by_function.get(function)
            if asm_path is None or function in solved:
                continue
            solved[function] = {
                "function": function,
                "label": attempt.get("label"),
                "code": attempt["candidate"],
                # Candidate declarations are stored separately by the
                # runner so they can be hoisted once per source group. Keep
                # them with the accepted winner when it is reused by the
                # template-transfer path; dropping them turns otherwise
                # valid templates into undefined-global compile failures.
                "declarations": attempt.get("declarations") or "",
                "ops": _opcode_sequence(asm_path.read_text(encoding="utf-8")),
            }
    rows = list(solved.values())
    _SOLVED_CACHE = (cache_key, rows)
    return rows


def similar_solved(
    function: str,
    *,
    limit: int = 3,
    minimum: float = 0.6,
    stats_path: Path | None = None,
    asm_roots: list[Path] | None = None,
    asm_text: str | None = None,
) -> list[dict[str, object]]:
    """Rank previously accepted candidates by opcode-sequence similarity to ``function``.

    ``asm_text`` overrides reading ``owner.asm_path`` directly for the
    target itself -- a caller with its own fallback for a ``.s`` not present
    in this checkout (``s1_transfer_sweep.gs_asm_text``) passes the text it
    already resolved, skipping ``require_owner`` too (its ``owner_index``
    revalidates by rescanning every tracked source's mtime on every call,
    not cheap across a sweep of thousands of targets).  ``stats_path``/
    ``asm_roots`` are threaded straight to ``solved_shapes`` for the same
    reason on the winners' side.
    """
    text = asm_text if asm_text is not None else require_owner(function).asm_path.read_text(encoding="utf-8")
    ops = _opcode_sequence(text)
    ranked: list[dict[str, object]] = []
    for row in solved_shapes(stats_path, asm_roots=asm_roots):
        other = row["ops"]
        if not isinstance(other, list) or not other:
            continue
        ratio = difflib.SequenceMatcher(None, ops, other, autojunk=False).ratio()
        if ratio >= minimum:
            ranked.append({
                "function": row["function"],
                "similarity": round(ratio, 3),
                "same_length": len(other) == len(ops),
                "label": row["label"],
                "code": row["code"],
                "declarations": row.get("declarations", ""),
            })
    ranked.sort(key=lambda row: (-float(row["similarity"]), not row["same_length"], str(row["function"])))
    return ranked[:limit]


# ---------------------------------------------------------------------------
# Owner hardness from recorded probe history
#
# Ranking owners/files by remaining-owner *count* alone treats a
# never-attempted function the same as one that has been probed dozens of
# times and keeps landing on the same unsolvable-by-source-shape register
# swap.  The fleet wave of 2026-08-28 made the difference visible: `585D0.c`
# got 0/12 accepts because its owners' best recorded attempts were mostly
# `register_allocation_only` at `similarity_score` 1.0 after many tries (a
# register-allocation tie -- no C source shape changes that), while
# `4AC10.c` got 6/14 because its owners had few attempts and
# `operand_or_scheduling_drift`/`instruction_drift` best kinds (a real
# semantic gap an agent can still close).  The functions below turn recorded
# probe-stats history into that signal.
# ---------------------------------------------------------------------------

# Kinds where the candidate is still short of a byte match for a reason a
# source-shape rewrite can plausibly fix (a missing statement, a wrong
# offset, a scheduling difference) -- as opposed to `register_allocation_only`
# at high similarity, which is IDO's register allocator picking differently
# for equivalent C, not a gap in the candidate.
DRIFT_MISMATCH_KINDS = frozenset({
    "instruction_drift",
    "operand_or_scheduling_drift",
    "immediate_drift",
})

FRESH_ATTEMPT_THRESHOLD = 5
TIE_SIMILARITY_THRESHOLD = 0.99
TIE_ATTEMPT_THRESHOLD = 6
STUCK_ATTEMPT_THRESHOLD = 15
STUCK_SIMILARITY_THRESHOLD = 0.9


@dataclass(frozen=True)
class OwnerHardness:
    """One owner's aggregated probe-attempt history.

    ``best_similarity``/``best_mismatch_kind``/``best_raw_similarity`` all
    come from the single recorded attempt with the highest
    ``similarity_score`` for this function (ties broken by whichever the
    scan visits first); an owner with no recorded attempts gets the all-zero
    default below, which classifies as ``fresh``.  ``best_raw_similarity``
    reads the runner's `exact_similarity_score` field -- the pre-register-
    normalization match ratio the code and AGENTS.md call "raw" (see the
    ``func_80051610``-style backlog entry: a candidate can score
    ``similarity_score`` 1.0 through register normalisation while its raw
    score is much lower with values swapped between fields).
    """

    prior_attempts: int = 0
    best_similarity: float | None = None
    best_raw_similarity: float | None = None
    best_mismatch_kind: str | None = None
    last_attempt: str | None = None

    def as_dict(self) -> dict[str, object]:
        return {
            "prior_attempts": self.prior_attempts,
            "best_similarity": self.best_similarity,
            "best_mismatch_kind": self.best_mismatch_kind,
            "best_raw_similarity": self.best_raw_similarity,
            "last_attempt": self.last_attempt,
        }

    @property
    def is_fresh(self) -> bool:
        """Few enough attempts that the pool hasn't really been tried yet."""
        return self.prior_attempts < FRESH_ATTEMPT_THRESHOLD

    @property
    def is_tie(self) -> bool:
        """A register-allocation tie: near-1.0 similarity, many tries, same kind.

        This is the ``585D0.c`` shape -- a byte match that no declaration-
        order/temp-width/width rewrite has reached after real effort.  Not
        impossible, but a poor use of a fresh agent's time box.
        """
        return (
            self.best_mismatch_kind == "register_allocation_only"
            and self.best_similarity is not None
            and self.best_similarity >= TIE_SIMILARITY_THRESHOLD
            and self.prior_attempts >= TIE_ATTEMPT_THRESHOLD
        )

    @property
    def is_drift(self) -> bool:
        """A semantic gap (missing statement, wrong offset, wrong schedule)."""
        return (
            self.best_mismatch_kind in DRIFT_MISMATCH_KINDS
            and self.best_similarity is not None
            and self.best_similarity < 1.0
        )

    @property
    def is_stuck(self) -> bool:
        """Heavily attempted with no attempt ever getting close."""
        return self.prior_attempts >= STUCK_ATTEMPT_THRESHOLD and (
            self.best_similarity is None or self.best_similarity < STUCK_SIMILARITY_THRESHOLD
        )

    @property
    def label(self) -> str:
        """One-word hardness summary; always one of fresh/drift/tie/stuck."""
        if self.is_tie:
            return "tie"
        if self.is_stuck:
            return "stuck"
        if self.is_drift:
            return "drift"
        if self.is_fresh:
            return "fresh"
        # An owner with 5-14 attempts whose best kind is neither a
        # recognized drift shape nor a >=0.99 register-allocation tie still
        # needs a label: below a byte match, there is still room for a
        # source-shape change to close (drift-like); at or above it with an
        # unrecognized kind, nothing here explains what a rewrite would
        # change (tie-like).
        if self.best_similarity is not None and self.best_similarity < 1.0:
            return "drift"
        return "tie"


_EMPTY_HARDNESS = OwnerHardness()

_HARDNESS_CACHE: dict[tuple[tuple[str, int], ...], dict[str, OwnerHardness]] = {}


def _resolve_hardness_stats_paths(stats_paths) -> tuple[Path, ...]:
    if stats_paths is None:
        return variant_policy.default_stats_paths()
    if isinstance(stats_paths, (str, Path)):
        return tuple(probe_stats.resolve_paths([Path(stats_paths)]))
    return tuple(probe_stats.resolve_paths([Path(item) for item in stats_paths]))


def load_owner_hardness(stats_paths=None) -> dict[str, OwnerHardness]:
    """Aggregate every function's recorded probe-attempt history, once.

    Reads across every resolved probe-stats file (default:
    ``variant_policy.default_stats_paths()``, i.e. the current and legacy
    locations plus any rotated ``<stem>.<N><suffix>`` sibling of either) in
    a single pass and returns ``{function: OwnerHardness}``.  Call this once
    per invocation and look up owners from the returned mapping -- do not
    call it per owner, it re-parses every batch file each time it actually
    runs.

    ``stats_paths`` may be ``None`` (the default above), a single path (the
    ``--stats`` CLI flag, expanded the same way a default path is: any
    rotated sibling next to it is picked up too), or an iterable of paths.
    Results are cached by the resolved paths' mtimes, so a second call in
    the same process with unchanged files is free.
    """
    paths = _resolve_hardness_stats_paths(stats_paths)
    cache_key = tuple(sorted((str(path), path.stat().st_mtime_ns) for path in paths))
    cached = _HARDNESS_CACHE.get(cache_key)
    if cached is not None:
        return cached

    prior_attempts: dict[str, int] = collections.Counter()
    best_similarity: dict[str, float] = {}
    best_raw_similarity: dict[str, float | None] = {}
    best_mismatch_kind: dict[str, str | None] = {}
    last_attempt: dict[str, str] = {}

    for batch in probe_stats.iter_batches(paths):
        attempts = batch.get("attempts")
        if not isinstance(attempts, list):
            continue
        timestamp = batch.get("timestamp")
        timestamp = timestamp if isinstance(timestamp, str) and timestamp else None
        for attempt in attempts:
            if not isinstance(attempt, dict):
                continue
            function = attempt.get("function")
            if not isinstance(function, str) or not function:
                continue
            prior_attempts[function] += 1
            if timestamp is not None:
                current = last_attempt.get(function)
                if current is None or timestamp > current:
                    last_attempt[function] = timestamp
            score = attempt.get("similarity_score")
            if not isinstance(score, (int, float)):
                continue
            score = float(score)
            if function not in best_similarity or score > best_similarity[function]:
                best_similarity[function] = score
                raw = attempt.get("exact_similarity_score")
                best_raw_similarity[function] = float(raw) if isinstance(raw, (int, float)) else None
                kind = attempt.get("mismatch_kind")
                best_mismatch_kind[function] = kind if isinstance(kind, str) and kind else None

    result: dict[str, OwnerHardness] = {
        function: OwnerHardness(
            prior_attempts=count,
            best_similarity=best_similarity.get(function),
            best_raw_similarity=best_raw_similarity.get(function),
            best_mismatch_kind=best_mismatch_kind.get(function),
            last_attempt=last_attempt.get(function),
        )
        for function, count in prior_attempts.items()
    }
    _HARDNESS_CACHE[cache_key] = result
    return result


def _fragment_number(source: str) -> int | None:
    """Mirrors ``sweep_targets._fragment_number`` without importing it back.

    ``sweep_targets`` already imports this module, so importing it here for
    one regex would be circular; the pattern (``.../fragments/<N>/...``) is
    small enough to keep in sync by inspection.
    """
    match = re.search(r"(?:^|/)fragments/(\d+)(?:/|$)", source.replace("\\", "/"))
    return int(match.group(1)) if match else None


# Repository-location env vars git sets for a hook subprocess's own children
# (GIT_DIR/GIT_INDEX_FILE point at the *enclosing* repo -- e.g. this
# worktree -- when this module itself runs from inside a pre-commit hook or
# test fixture). Left inherited, they override ``cwd`` below and redirect a
# ``repo_root`` fixture repo's git calls onto the enclosing repo instead.
_GIT_ENV_VARS_TO_STRIP = (
    "GIT_DIR", "GIT_WORK_TREE", "GIT_INDEX_FILE", "GIT_COMMON_DIR",
    "GIT_OBJECT_DIRECTORY", "GIT_ALTERNATE_OBJECT_DIRECTORIES",
)


def _git_lines(args: list[str], *, repo_root: Path = REPO_ROOT) -> list[str]:
    env = {key: value for key, value in os.environ.items() if key not in _GIT_ENV_VARS_TO_STRIP}
    try:
        result = subprocess.run(
            ["git", *args],
            cwd=repo_root,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=30,
            env=env,
        )
    except (OSError, subprocess.TimeoutExpired):
        return []
    if result.returncode != 0:
        return []
    return [line for line in result.stdout.splitlines() if line.strip()]


def _recently_touched_sources(hours: float, *, repo_root: Path = REPO_ROOT) -> set[str]:
    """Repo-relative ``disasm/src`` paths touched by a commit in the last ``hours``.

    Formats an absolute ISO-8601 UTC timestamp for ``--since`` rather than
    git's natural-language ``"<N> hours ago"`` form: git's approxidate
    parser silently mis-parses a fractional ``N`` (``--since="4.0 hours
    ago"`` matched the entire multi-year history instead of the last four
    hours -- ``argparse``'s ``--exclude-recent`` is typed ``float``, so a
    whole-number CLI value like ``4`` still becomes ``4.0`` internally).  An
    absolute timestamp has no such ambiguity.
    """
    since = (datetime.now(timezone.utc) - timedelta(hours=hours)).strftime("%Y-%m-%dT%H:%M:%SZ")
    lines = _git_lines(
        ["log", f"--since={since}", "--format=", "--name-only", "--", "disasm/src"],
        repo_root=repo_root,
    )
    return set(lines)


def _dirty_sources(*, repo_root: Path = REPO_ROOT) -> set[str]:
    """Repo-relative ``disasm/src`` paths with uncommitted working-tree changes."""
    lines = _git_lines(["status", "--porcelain", "--", "disasm/src"], repo_root=repo_root)
    paths: set[str] = set()
    for line in lines:
        # Porcelain short format: "XY path" or "XY orig -> new" for a rename.
        chunk = line[3:].strip() if len(line) > 3 else line.strip()
        if " -> " in chunk:
            chunk = chunk.split(" -> ", 1)[1]
        if chunk:
            paths.add(chunk)
    return paths


def rank_files(
    *,
    max_instructions: int = 128,
    exclude_recent_hours: float | None = None,
    fragments: bool = True,
    stats_paths=None,
    repo_root: Path = REPO_ROOT,
) -> dict[str, object]:
    """Score every source file with remaining owners by hardness signal.

    For each source file, counts remaining owners of at most
    ``max_instructions`` instructions, and within those: ``fresh`` (see
    ``OwnerHardness.is_fresh``), ``drift`` (``OwnerHardness.is_drift``), and
    ``ties`` (``OwnerHardness.is_tie``).  Jump-table owners are split into
    ``jump_table_ready`` and ``jump_table_unready`` based on the per-file
    rodata subsegment in ``rom.yaml``.  ``actionable_fresh`` and
    ``actionable_drift`` exclude only the latter; ordinary owners remain
    actionable.  ``score = fresh + drift`` remains available for comparison.
    Rows are sorted by actionable fresh owners first, then total fresh owners,
    so a large file whose fresh pool is mostly layout-blocked cannot displace
    a smaller file with work an agent can actually probe.

    ``exclude_recent_hours``, when given, drops any file touched by a commit
    in that many hours (``git log --since``) or currently dirty in the
    working tree -- both read-only checks against ``repo_root`` (a test
    fixture parameter; every real caller uses the default ``REPO_ROOT``).
    ``fragments=False`` drops ``disasm/src/fragments/...`` files entirely.
    """
    hardness = load_owner_hardness(stats_paths)
    excluded: set[str] = set()
    if exclude_recent_hours is not None:
        excluded |= _recently_touched_sources(exclude_recent_hours, repo_root=repo_root)
        excluded |= _dirty_sources(repo_root=repo_root)

    per_file: dict[str, dict[str, object]] = {}
    for owner in owner_index().values():
        if not owner.asm_path.exists():
            continue
        if not fragments and _fragment_number(owner.source) is not None:
            continue
        if owner.source in excluded:
            continue
        row = _classify_owner(owner)
        if int(row["instructions"]) > max_instructions:
            continue
        entry = per_file.setdefault(
            owner.source,
            {"file": owner.source, "remaining": 0, "fresh": 0, "drift": 0, "ties": 0,
             "jump_table_ready": 0, "jump_table_unready": 0,
             "actionable_fresh": 0, "actionable_drift": 0},
        )
        entry["remaining"] = int(entry["remaining"]) + 1
        ready, unready = _jump_table_readiness(owner, row, repo_root=repo_root)
        entry["jump_table_ready"] = int(entry["jump_table_ready"]) + int(ready)
        entry["jump_table_unready"] = int(entry["jump_table_unready"]) + int(unready)
        h = hardness.get(owner.function, _EMPTY_HARDNESS)
        if h.is_fresh:
            entry["fresh"] = int(entry["fresh"]) + 1
            if not unready:
                entry["actionable_fresh"] = int(entry["actionable_fresh"]) + 1
        if h.is_drift:
            entry["drift"] = int(entry["drift"]) + 1
            if not unready:
                entry["actionable_drift"] = int(entry["actionable_drift"]) + 1
        if h.is_tie:
            entry["ties"] = int(entry["ties"]) + 1

    rows = list(per_file.values())
    for entry in rows:
        entry["score"] = int(entry["fresh"]) + int(entry["drift"])
    rows.sort(
        key=lambda entry: (
            -int(entry["actionable_fresh"]),
            -int(entry["fresh"]),
            -int(entry["actionable_drift"]),
            -int(entry["score"]),
            int(entry["jump_table_unready"]),
            -int(entry["remaining"]),
            str(entry["file"]),
        )
    )
    return {"files": rows}


def _m2c_python() -> str:
    override = os.environ.get("M2C_PYTHON")
    if not override:
        return sys.executable
    expanded = os.path.expandvars(os.path.expanduser(override))
    if os.sep in expanded and not os.path.isabs(expanded):
        return str((REPO_ROOT / expanded).resolve(strict=False))
    return expanded


def draft_candidates(
    function: str,
    *,
    variants: list[str] | None = None,
    context: bool = True,
    extra_args: list[str] | None = None,
) -> dict[str, object]:
    """Run m2c over the owner's assembly and return one draft per variant.

    Drafts use unknown-struct field syntax (``arg0->unk9A``) and guessed
    types; they are starting points for candidate families, never proof.
    """
    owner = require_owner(function)
    script = m2c_script()
    if not script.is_file():
        raise FileNotFoundError(
            f"m2c is not installed at {script}; run tools/setup_decomp_tools.sh"
        )
    context_path = preprocessed_context(owner) if context else None
    names = variants or ["m2c", "m2c-no-casts"]
    drafts: list[dict[str, object]] = []
    for name in names:
        flags = DRAFT_VARIANTS.get(name)
        if flags is None:
            drafts.append({"label": name, "code": None, "error": "unknown variant"})
            continue
        command = [_m2c_python(), str(script), "--target", "mips-ido-c"]
        if context_path is not None:
            command += ["--context", str(context_path)]
        command += flags + list(extra_args or []) + [str(owner.asm_path)]
        try:
            result = subprocess.run(
                command,
                cwd=REPO_ROOT,
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                env=readonly_tool_environment(),
                timeout=runner._command_timeout("PRAGMA_M2C_TIMEOUT", 60.0),
            )
        except subprocess.TimeoutExpired:
            drafts.append({"label": name, "code": None, "error": "m2c timed out"})
            continue
        drafts.append({
            "label": name,
            "code": result.stdout if result.returncode == 0 else None,
            "error": None if result.returncode == 0 else result.stderr[-2000:],
            "warnings": result.stderr[-2000:] if result.returncode == 0 and result.stderr else None,
        })
    asm = function_asm(function)
    return {
        **owner.as_dict(),
        "instruction_count": asm["instruction_count"],
        "context": str(context_path.relative_to(REPO_ROOT)) if context_path else None,
        "drafts": drafts,
        "similar_solved": similar_solved(function),
    }


def _print_rank_files_table(rows: list[dict[str, object]]) -> None:
    header = (
        "FILE", "REMAINING", "READY_FRESH", "FRESH", "DRIFT", "JT_UNREADY", "TIES", "SCORE",
    )
    lines = [header] + [
        (
            str(row["file"]),
            str(row["remaining"]),
            str(row["actionable_fresh"]),
            str(row["fresh"]),
            str(row["drift"]),
            str(row["jump_table_unready"]),
            str(row["ties"]),
            str(row["score"]),
        )
        for row in rows
    ]
    widths = [max(len(line[col]) for line in lines) for col in range(len(header))]
    for line in lines:
        print("  ".join(value.ljust(width) for value, width in zip(line, widths)).rstrip())


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    commands = parser.add_subparsers(dest="command", required=True)
    owner = commands.add_parser("owner", help="print the source that owns a pragma")
    owner.add_argument("function")
    asm = commands.add_parser("asm", help="print the target assembly")
    asm.add_argument("function")
    targets = commands.add_parser("targets", help="rank remaining owners by size")
    targets.add_argument("--source")
    targets.add_argument("--family")
    targets.add_argument("--max-instructions", type=int)
    targets.add_argument("--min-instructions", type=int)
    targets.add_argument("--limit", type=int, default=50)
    targets.add_argument(
        "--skip-ties", action="store_true",
        help="hide owners whose recorded best attempt is a register-allocation tie",
    )
    targets.add_argument("--stats", type=Path, help="probe-stats file (default: variant_policy.default_stats_paths())")
    draft = commands.add_parser("draft", help="run m2c over a pragma's assembly")
    draft.add_argument("function")
    draft.add_argument("--variant", action="append", dest="variants")
    draft.add_argument("--no-context", action="store_true")
    similar = commands.add_parser("similar", help="rank accepted candidates by opcode-shape similarity")
    similar.add_argument("function")
    similar.add_argument("--limit", type=int, default=3)
    rank_files_cmd = commands.add_parser(
        "rank-files", help="score every source file with remaining owners by hardness signal",
    )
    rank_files_cmd.add_argument("--max-instructions", type=int, default=128)
    rank_files_cmd.add_argument(
        "--exclude-recent", type=float, default=None, dest="exclude_recent_hours", metavar="HOURS",
        help="drop files touched by a commit in the last HOURS, or dirty in the working tree",
    )
    fragments_group = rank_files_cmd.add_mutually_exclusive_group()
    fragments_group.add_argument("--fragments", action="store_true", dest="fragments", default=True)
    fragments_group.add_argument("--no-fragments", action="store_false", dest="fragments")
    rank_files_cmd.add_argument("--stats", type=Path, help="probe-stats file (default: variant_policy.default_stats_paths())")
    rank_files_cmd.add_argument("--limit", type=int, default=50)
    rank_files_cmd.add_argument("--json", action="store_true")
    args = parser.parse_args()

    if args.command == "owner":
        found = find_owner(args.function)
        if found is None:
            print(f"no pragma owns {args.function}", file=sys.stderr)
            return 1
        print(json.dumps(found.as_dict(), indent=2))
    elif args.command == "asm":
        print(function_asm(args.function)["text"], end="")
    elif args.command == "targets":
        print(json.dumps(list_targets(
            source=args.source,
            family=args.family,
            max_instructions=args.max_instructions,
            min_instructions=args.min_instructions,
            limit=args.limit,
            skip_ties=args.skip_ties,
            stats_paths=args.stats,
        ), indent=2))
    elif args.command == "similar":
        print(json.dumps(similar_solved(args.function, limit=args.limit), indent=2))
    elif args.command == "draft":
        result = draft_candidates(args.function, variants=args.variants, context=not args.no_context)
        for item in result["drafts"]:
            print(f"/* {item['label']} */")
            print(item["code"] or f"/* error: {item['error']} */")
    elif args.command == "rank-files":
        result = rank_files(
            max_instructions=args.max_instructions,
            exclude_recent_hours=args.exclude_recent_hours,
            fragments=args.fragments,
            stats_paths=args.stats,
        )
        rows = result["files"][: max(0, args.limit)] if args.limit else result["files"]
        if args.json:
            print(json.dumps({**result, "files": rows}, indent=2))
        else:
            _print_rank_files_table(rows)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
