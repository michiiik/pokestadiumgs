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
import json
import os
import re
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

import scan_asm_families as scanner
import try_pragma_compare as runner

REPO_ROOT = Path(__file__).resolve().parent.parent
DISASM_ROOT = REPO_ROOT / "disasm"
SOURCE_ROOT = DISASM_ROOT / "src"
ASM_ROOT = DISASM_ROOT / "asm" / "us" / "nonmatchings"
M2C_SCRIPT = DISASM_ROOT / "tools" / "m2c" / "m2c.py"
CONTEXT_CACHE_ROOT = DISASM_ROOT / "build" / "m2c-context"

PRAGMA_RE = re.compile(r'^#pragma GLOBAL_ASM\("(asm/us/nonmatchings/([^"]+)/([A-Za-z_]\w*)\.s)"\)$', re.M)

DRAFT_VARIANTS: dict[str, list[str]] = {
    "m2c": [],
    "m2c-no-casts": ["--no-casts"],
    "m2c-gotos": ["--gotos-only"],
}


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
        return REPO_ROOT / self.asm

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


def preprocessed_context(owner: Owner, *, refresh: bool = False) -> Path | None:
    """Return a cached, host-preprocessed copy of the owner's source.

    m2c reads variable types, prototypes, and structs from this file.  It is
    regenerated whenever the tracked source changes.  ``None`` means the host
    preprocess command could not be captured or failed; drafts then run
    without a context.
    """
    check = runner.host_check_recipe(REPO_ROOT)
    if check is None:
        return None
    source_rel = owner.source_path.relative_to(DISASM_ROOT)
    cache_path = CONTEXT_CACHE_ROOT / source_rel.with_suffix(".ctx.c")
    try:
        if (
            not refresh
            and cache_path.exists()
            and cache_path.stat().st_mtime_ns >= owner.source_path.stat().st_mtime_ns
        ):
            return cache_path
    except OSError:
        pass
    include_directory = source_rel.parent.as_posix() + "/"
    command = runner.host_preprocess_command(check, include_directory) + [source_rel.as_posix()]
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
    cache_path.write_text(result.stdout, encoding="utf-8")
    return cache_path


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
    elif args.command == "draft":
        result = draft_candidates(args.function, variants=args.variants, context=not args.no_context)
        for item in result["drafts"]:
            print(f"/* {item['label']} */")
            print(item["code"] or f"/* error: {item['error']} */")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
