#!/usr/bin/env python3
"""Target discovery, assembly access, and m2c drafts for pragma-backed owners.

The candidate runner needs a source path and a function name.  This module
answers the questions that come before that call:

* which tracked source owns a ``GLOBAL_ASM`` pragma (``find_owner``);
* what the target assembly looks like (``function_asm``);
* which owners are small/simple enough to batch next (``list_targets``);
* what m2c proposes as a first C draft (``draft_candidates``).

Usage:
    tools/pragma_targets.py owner func_8410AE50
    tools/pragma_targets.py asm func_8410AE50
    tools/pragma_targets.py targets --max-instructions 12 --family direct_wrapper
    tools/pragma_targets.py draft func_8410AE50

Everything here is read-only with respect to tracked sources.  Drafts are
hypotheses: send them through ``try_pragma_candidates`` like any other
candidate.
"""

from __future__ import annotations

import argparse
import difflib
import json
import os
import re
import subprocess
import threading
import sys
from dataclasses import dataclass
from pathlib import Path

import probe_stats
import scan_asm_families as scanner
import try_pragma_compare as runner

REPO_ROOT = Path(__file__).resolve().parent.parent
DISASM_ROOT = REPO_ROOT / "disasm"
SOURCE_ROOT = DISASM_ROOT / "src"
ASM_ROOT = DISASM_ROOT / "asm" / "us" / "nonmatchings"
M2C_SCRIPT = DISASM_ROOT / "tools" / "m2c" / "m2c.py"
CONTEXT_CACHE_ROOT = DISASM_ROOT / "build" / "m2c-context"
SYMBOL_INDEX_HEADER = CONTEXT_CACHE_ROOT / "repo-prototypes.h"

PRAGMA_RE = re.compile(r'^#pragma GLOBAL_ASM\("(asm/us/nonmatchings/([^"]+)/([A-Za-z_]\w*)\.s)"\)$', re.M)

DRAFT_VARIANTS: dict[str, list[str]] = {
    "m2c": [],
    "m2c-no-casts": ["--no-casts"],
    "m2c-gotos": ["--gotos-only"],
}


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
) -> dict[str, object]:
    """Rank remaining owners by size so small same-shape batches are easy to pick."""
    owners = list(owner_index().values())
    if source:
        wanted = source.replace("\\", "/").removeprefix("./")
        owners = [owner for owner in owners if owner.source == wanted or owner.source.endswith("/" + wanted)]
    rows: list[dict[str, object]] = []
    family_counts: dict[str, int] = {}
    for owner in owners:
        if not owner.asm_path.exists():
            continue
        row = _classify_owner(owner)
        count = int(row["instructions"])
        if max_instructions is not None and count > max_instructions:
            continue
        if min_instructions is not None and count < min_instructions:
            continue
        family_counts[str(row["family"])] = family_counts.get(str(row["family"]), 0) + 1
        if family and row["family"] != family:
            continue
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


def _m2c_python() -> str:
    return os.environ.get("M2C_PYTHON") or sys.executable


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
    if not M2C_SCRIPT.exists():
        raise FileNotFoundError(
            f"m2c is not installed at {M2C_SCRIPT}; run tools/setup_decomp_tools.sh"
        )
    context_path = preprocessed_context(owner) if context else None
    names = variants or ["m2c", "m2c-no-casts"]
    drafts: list[dict[str, object]] = []
    for name in names:
        flags = DRAFT_VARIANTS.get(name)
        if flags is None:
            drafts.append({"label": name, "code": None, "error": "unknown variant"})
            continue
        command = [_m2c_python(), str(M2C_SCRIPT), "--target", "mips-ido-c"]
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
    draft = commands.add_parser("draft", help="run m2c over a pragma's assembly")
    draft.add_argument("function")
    draft.add_argument("--variant", action="append", dest="variants")
    draft.add_argument("--no-context", action="store_true")
    similar = commands.add_parser("similar", help="rank accepted candidates by opcode-shape similarity")
    similar.add_argument("function")
    similar.add_argument("--limit", type=int, default=3)
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
        ), indent=2))
    elif args.command == "similar":
        print(json.dumps(similar_solved(args.function, limit=args.limit), indent=2))
    elif args.command == "draft":
        result = draft_candidates(args.function, variants=args.variants, context=not args.no_context)
        for item in result["drafts"]:
            print(f"/* {item['label']} */")
            print(item["code"] or f"/* error: {item['error']} */")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
