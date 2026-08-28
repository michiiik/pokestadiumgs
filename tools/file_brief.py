#!/usr/bin/env python3
"""Print a "file brief" for one decomp source file: what an agent would
otherwise spend tens of thousands of tokens rediscovering by reading the
whole file, its neighbours, and AGENTS.md.

Pure text parsing of the ``.c`` source (and, via ``pragma_targets``, the
already-split ``.s`` files) -- no compiler is invoked.

Sections printed:

1. Counts -- solved vs. remaining owners in this file.
2. Already-decompiled functions with a one-line signature each.
3. The deduplicated extern/prototype block.
4. Every ``func_``/``D_`` symbol referenced from a solved body, with how
   many distinct solved bodies reference it (a repeated symbol is a hint
   worth checking before guessing a new one).
5. Constants in solved bodies that look like record strides (``* 112``,
   ``* 0x160``, ``idx * N``), separated from the common pointer-width
   strides (``* 2`` / ``* 4`` / ``* 8``) that are usually just pointer math.
6. SDK macros (``gSP*``/``gDP*``/``gu*``/``os*``) already used in this file.
7. Every function DEFINED later in the file than the first still-remaining
   pragma, with its real return type and parameter list -- pass these as
   ``declarations`` so a same-file forward call does not fall back to the
   runner's synthesized ``s32`` prototype and fail on a narrower real
   return type (see AGENTS.md §5, the ``func_8005D92C`` class of bug).
8. Remaining owners (instruction count, family), via
   ``tools/pragma_targets.py``'s existing listing/classification -- this
   script does not re-parse ``.s`` files or re-implement the family
   classifier.

Usage:
    tools/file_brief.py disasm/src/4AC10.c
    tools/file_brief.py disasm/src/4AC10.c --json out.json
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

import pragma_targets
import region_notes

REPO_ROOT = Path(__file__).resolve().parent.parent

PRAGMA_LINE_RE = re.compile(
    r'#pragma\s+GLOBAL_ASM\("asm/us/nonmatchings/([^"]+)/([A-Za-z_]\w*)\.s"\)'
)
FUNCTION_DEF_RE = re.compile(
    r"^(?P<ret>[A-Za-z_][\w\s\*]*?)\s+(?P<name>[A-Za-z_]\w*)\s*\((?P<params>[^;{}]*)\)\s*\{",
    re.MULTILINE,
)
EXTERN_LINE_RE = re.compile(r"^extern\b.*;\s*$")
SYMBOL_REF_RE = re.compile(r"\b(func_[0-9A-Fa-f]+|D_[0-9A-Fa-f]+)\b")
STRIDE_RE = re.compile(r"([A-Za-z_]\w*)\s*\*\s*(0x[0-9A-Fa-f]+|\d+)")
SDK_MACRO_RE = re.compile(r"\b((?:gSP|gDP|gu|os)[A-Za-z0-9_]*)\b")
COMMON_POINTER_STRIDES = {"1", "2", "4", "8"}


def _collapse_ws(text: str) -> str:
    return re.sub(r"\s+", " ", text).strip()


class ParsedFunction:
    __slots__ = ("name", "ret", "params", "start_line", "start", "end", "body")

    def __init__(self, name: str, ret: str, params: str, start_line: int, start: int, end: int, body: str) -> None:
        self.name = name
        self.ret = ret
        self.params = params
        self.start_line = start_line
        self.start = start
        self.end = end
        self.body = body

    @property
    def signature(self) -> str:
        params = _collapse_ws(self.params) or "void"
        return f"{_collapse_ws(self.ret)} {self.name}({params})"


def _find_matching_brace(text: str, open_brace_index: int) -> int:
    """Return the index just past the ``}`` matching the ``{`` at ``open_brace_index``."""
    depth = 0
    for index in range(open_brace_index, len(text)):
        if text[index] == "{":
            depth += 1
        elif text[index] == "}":
            depth -= 1
            if depth == 0:
                return index + 1
    return len(text)


def parse_functions(text: str) -> list[ParsedFunction]:
    """Return every top-level ``ret name(params) { ... }`` definition in file order."""
    functions: list[ParsedFunction] = []
    for match in FUNCTION_DEF_RE.finditer(text):
        open_brace = match.end() - 1
        end = _find_matching_brace(text, open_brace)
        start_line = text.count("\n", 0, match.start()) + 1
        functions.append(
            ParsedFunction(
                name=match.group("name"),
                ret=match.group("ret"),
                params=match.group("params"),
                start_line=start_line,
                start=match.start(),
                end=end,
                body=text[match.start():end],
            )
        )
    return functions


def parse_pragmas(text: str) -> list[tuple[int, str]]:
    """Return ``(line_number, function)`` for every remaining ``GLOBAL_ASM`` pragma, in file order."""
    pragmas: list[tuple[int, str]] = []
    for match in PRAGMA_LINE_RE.finditer(text):
        line_number = text.count("\n", 0, match.start()) + 1
        pragmas.append((line_number, match.group(2)))
    return pragmas


def extern_block(text: str) -> list[str]:
    """Return the deduplicated extern/prototype lines, in first-seen order."""
    seen: dict[str, None] = {}
    for line in text.splitlines():
        stripped = line.strip()
        if EXTERN_LINE_RE.match(stripped):
            seen.setdefault(_collapse_ws(stripped), None)
    return list(seen.keys())


def symbol_usage(functions: list[ParsedFunction]) -> list[tuple[str, int]]:
    """Return ``(symbol, solved_body_count)`` sorted by count desc, name asc."""
    counts: dict[str, int] = {}
    for function in functions:
        referenced = {
            symbol
            for symbol in SYMBOL_REF_RE.findall(function.body)
            if symbol != function.name
        }
        for symbol in referenced:
            counts[symbol] = counts.get(symbol, 0) + 1
    return sorted(counts.items(), key=lambda item: (-item[1], item[0]))


def stride_candidates(functions: list[ParsedFunction]) -> tuple[list[tuple[str, str, int]], list[tuple[str, str, int]]]:
    """Return ``(record_strides, pointer_strides)``, each a list of ``(ident, literal, count)``.

    ``record_strides`` are multiplications by a literal that is not one of
    the common pointer-width strides (1/2/4/8); ``pointer_strides`` are
    those common ones, reported separately since they are usually plain
    pointer arithmetic rather than a record stride.
    """
    counts: dict[tuple[str, str], int] = {}
    for function in functions:
        for ident, literal in STRIDE_RE.findall(function.body):
            counts[(ident, literal)] = counts.get((ident, literal), 0) + 1
    record: list[tuple[str, str, int]] = []
    pointer: list[tuple[str, str, int]] = []
    for (ident, literal), count in counts.items():
        normalized = literal.lower()
        is_common = normalized in COMMON_POINTER_STRIDES or (
            normalized.startswith("0x") and str(int(normalized, 16)) in COMMON_POINTER_STRIDES
        )
        bucket = pointer if is_common else record
        bucket.append((ident, literal, count))
    record.sort(key=lambda row: (-row[2], row[1]))
    pointer.sort(key=lambda row: (-row[2], row[1]))
    return record, pointer


def sdk_macros(functions: list[ParsedFunction]) -> list[tuple[str, int]]:
    counts: dict[str, int] = {}
    for function in functions:
        for macro in SDK_MACRO_RE.findall(function.body):
            counts[macro] = counts.get(macro, 0) + 1
    return sorted(counts.items(), key=lambda item: (-item[1], item[0]))


def later_defined_functions(functions: list[ParsedFunction], first_remaining_line: int | None) -> list[ParsedFunction]:
    if first_remaining_line is None:
        return []
    return [function for function in functions if function.start_line > first_remaining_line]


def remaining_owners_table(source_path: Path, pragmas: list[tuple[int, str]]) -> list[dict[str, object]]:
    """Instruction count + family per remaining owner, via ``pragma_targets``.

    Falls back to a bare name/line listing (family/instructions ``None``)
    when ``pragma_targets`` does not know this file -- e.g. it is not part
    of the tracked ``disasm/src`` tree (a synthetic test file), or its
    ``.s`` files have not been generated yet.
    """
    try:
        rel = source_path.resolve().relative_to(pragma_targets.REPO_ROOT).as_posix()
    except ValueError:
        rel = source_path.as_posix()
    try:
        result = pragma_targets.list_targets(source=rel, limit=len(pragmas) or 1)
    except Exception:
        result = {"matched": 0, "targets": []}
    targets = result.get("targets") if isinstance(result, dict) else None
    if targets:
        rows = [
            {
                "function": row.get("function"),
                "instructions": row.get("instructions"),
                "family": row.get("family"),
            }
            for row in targets
        ]
        known = {row["function"] for row in rows}
        for line_number, function in pragmas:
            if function not in known:
                rows.append({"function": function, "instructions": None, "family": None, "line": line_number})
        return rows
    return [
        {"function": function, "instructions": None, "family": None, "line": line_number}
        for line_number, function in pragmas
    ]


def _display_path(source_path: Path) -> str:
    try:
        return source_path.resolve().relative_to(REPO_ROOT).as_posix()
    except ValueError:
        return source_path.as_posix()


def build_brief(source_path: Path) -> dict[str, object]:
    text = source_path.read_text(encoding="utf-8", errors="replace")
    functions = parse_functions(text)
    pragmas = parse_pragmas(text)
    solved = [function for function in functions if re.fullmatch(r"func_[0-9A-Fa-f]+", function.name)]
    first_remaining_line = pragmas[0][0] if pragmas else None
    record_strides, pointer_strides = stride_candidates(solved or functions)
    return {
        "source": _display_path(source_path),
        "region_notes": region_notes.load(source_path),
        "region_notes_path": _display_path(region_notes.path_for(source_path)),
        "counts": {
            "solved": len(solved),
            "other_defined": len(functions) - len(solved),
            "remaining": len(pragmas),
        },
        "solved_functions": [
            {"function": f.name, "signature": f.signature, "line": f.start_line} for f in (solved or functions)
        ],
        "externs": extern_block(text),
        "symbol_usage": symbol_usage(solved or functions),
        "record_strides": record_strides,
        "pointer_strides": pointer_strides,
        "sdk_macros": sdk_macros(solved or functions),
        "first_remaining_pragma_line": first_remaining_line,
        "later_defined_functions": [
            {"function": f.name, "return_type": _collapse_ws(f.ret), "params": _collapse_ws(f.params) or "void", "line": f.start_line}
            for f in later_defined_functions(functions, first_remaining_line)
        ],
        "remaining_owners": remaining_owners_table(source_path, pragmas),
    }


def _print_section(title: str) -> None:
    print(f"\n== {title} ==")


def render_text(brief: dict[str, object]) -> str:
    lines: list[str] = []

    def emit(text: str = "") -> None:
        lines.append(text)

    emit("== region notes ==")
    if brief["region_notes"]:
        emit(brief["region_notes"])
    else:
        emit(
            "  no region notes yet for this file -- add skip lists and "
            "proven spellings with:"
        )
        emit(
            f"    python3 tools/region_notes.py append {brief['source']} "
            f'--text "..." [--heading "..."]'
        )
        emit(f"  they would live at {brief['region_notes_path']}")

    counts = brief["counts"]
    emit(f"\nfile brief: {brief['source']}")
    emit(
        f"counts: solved={counts['solved']} other_defined={counts['other_defined']} "
        f"remaining={counts['remaining']} total_owners={counts['solved'] + counts['remaining']}"
    )

    emit("\n== already-decompiled functions ==")
    if brief["solved_functions"]:
        for row in brief["solved_functions"]:
            emit(f"  {row['function']:<20} line {row['line']:<5} {row['signature']}")
    else:
        emit("  (none)")

    emit("\n== extern/prototype block (deduplicated) ==")
    if brief["externs"]:
        for line in brief["externs"]:
            emit(f"  {line}")
    else:
        emit("  (none found)")

    emit("\n== func_/D_ symbols referenced, by solved-body count ==")
    if brief["symbol_usage"]:
        for symbol, count in brief["symbol_usage"]:
            noun = "body" if count == 1 else "bodies"
            emit(f"  {symbol:<20} used in {count} solved {noun}")
    else:
        emit("  (none)")

    emit("\n== record-stride-like constants (ident * literal, literal not in {1,2,4,8}) ==")
    if brief["record_strides"]:
        for ident, literal, count in brief["record_strides"]:
            emit(f"  {ident} * {literal:<8} x{count}")
    else:
        emit("  (none found)")
    if brief["pointer_strides"]:
        emit("  common pointer-width strides seen (likely not record strides):")
        for ident, literal, count in brief["pointer_strides"]:
            emit(f"    {ident} * {literal:<8} x{count}")

    emit("\n== SDK macros already used in this file (gSP*/gDP*/gu*/os*) ==")
    if brief["sdk_macros"]:
        for macro, count in brief["sdk_macros"]:
            emit(f"  {macro:<24} x{count}")
    else:
        emit("  (none found)")

    emit("\n== functions defined later in the file than the first remaining pragma ==")
    emit("   (pass matching prototypes in `declarations`; the runner's fallback defaults to s32)")
    if brief["first_remaining_pragma_line"] is None:
        emit("  (no remaining pragmas in this file)")
    elif brief["later_defined_functions"]:
        for row in brief["later_defined_functions"]:
            emit(f"  {row['return_type']} {row['function']}({row['params']})  -- line {row['line']}")
    else:
        emit("  (none: every defined function in this file comes before the first remaining pragma)")

    emit("\n== remaining owners (instructions, family) ==")
    if brief["remaining_owners"]:
        for row in brief["remaining_owners"]:
            instructions = row.get("instructions")
            family = row.get("family")
            extra = f" line {row['line']}" if instructions is None and "line" in row else ""
            emit(
                f"  {row['function']:<20} "
                f"{'instructions=' + str(instructions) if instructions is not None else 'instructions=?'} "
                f"family={family if family is not None else '?'}{extra}"
            )
    else:
        emit("  (none: file fully decompiled)")

    return "\n".join(lines)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("source", type=Path, help="path to a .c source file (repo-relative or absolute)")
    parser.add_argument("--json", type=Path, help="also write the structured brief as JSON to this path")
    args = parser.parse_args(argv)

    source_path = args.source
    if not source_path.is_absolute():
        candidate = REPO_ROOT / source_path
        source_path = candidate if candidate.exists() else source_path
    if not source_path.exists():
        print(f"file_brief: no such file: {args.source}", file=sys.stderr)
        return 2

    brief = build_brief(source_path)
    print(render_text(brief))

    if args.json:
        args.json.write_text(json.dumps(brief, indent=2, default=str), encoding="utf-8")
        print(f"\nstructured brief written to {args.json}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
