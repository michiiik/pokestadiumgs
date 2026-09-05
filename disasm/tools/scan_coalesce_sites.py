#!/usr/bin/env python3
"""Scan the ROM's ground-truth disassembly for shared-$at lui-coalescing sites.

Finds every still-``GLOBAL_ASM`` owner whose *ground truth* disassembly
contains a run of 2+ consecutive memory ops (``sw``/``sh``/``sb``/``lw``/
``lh``/``lhu``/``lb``/``lbu``/``swc1``/``lwc1``/``l.s``/``s.s``/``l.d``/
``s.d``) that all use ``$at`` as their base register with a symbolic
``%lo(SYM)`` operand, where the symbols differ from each other and all
resolve -- via ``coalesce_lui.resolve_repo_addresses``/``coalesce_lui.hi16``,
the mechanism's own address-map logic, reused rather than reimplemented here
-- to the same ``%hi`` page. Two classes of match:

* **Contiguous**: the ``lui $at, %hi(SYM0)`` immediately precedes the run
  (zero intervening lines) and the run's own ops are back-to-back (zero
  intervening lines). This is exactly the shape ``coalesce_lui.fold_source``
  already knows how to fold (see its own module docstring) -- reusing its
  ``hi16``/``resolve_repo_addresses`` directly is what makes "contiguous"
  here mean exactly what the fold mechanism itself can handle, rather than a
  reimplementation of the pattern match that could silently drift from it.
* **Interleaved**: the same shared-``$at``, multiple-distinct-symbol shape,
  but with unrelated instructions between the ``lui`` and/or between the
  memory ops themselves (IDO's scheduler hoisting the ``lui`` early). The
  current ``fold_source`` cannot fold these at all -- they are reported
  (``--interleaved``) for completeness/awareness only, never as a candidate.

Ground truth ``.s`` text is read from a primary checkout's ``disasm/asm``
tree (a linked worktree's own copy is normally empty -- see AGENTS.md Sec
1.2, "Worktrees fall back read-only to the sibling checkout for disasm/asm");
pass ``--asm-root`` to point at a different one explicitly (e.g. a worktree
that has completed its own private extraction).

Usage:
    python3 disasm/tools/scan_coalesce_sites.py [--repo-root PATH]
        [--asm-root PATH] [--interleaved] [--json-only]

Output: one JSON object per line (JSONL) to stdout, one per site found
(contiguous by default; add ``--interleaved`` to include those too, each
tagged ``"contiguous": false``). A summary line goes to stderr.
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

_HERE = Path(__file__).resolve().parent  # disasm/tools
_DEFAULT_REPO_ROOT = _HERE.parent.parent  # repo root

sys.path.insert(0, str(_HERE))
import coalesce_lui  # noqa: E402

GLOBAL_ASM_RE = re.compile(
    r'#pragma\s+GLOBAL_ASM\("(asm/us/nonmatchings/([^"]+)/([A-Za-z_]\w*))\.s"\)'
)

# Ground-truth disassembly instruction line, e.g.:
#   /* 032194 80031594 AC201A90 */  sw          $zero, %lo(D_800D1A90)($at)
GT_INSTR_RE = re.compile(
    r'^\s*/\*[^*]*\*/\s+(?P<op>[a-z][a-z0-9.]*)\s+(?P<operands>.+?)\s*(?:/\*.*\*/)?\s*$'
)
LUI_AT_RE = re.compile(r'^\$at,\s*%hi\(([A-Za-z_.$][\w.$]*)\)$')
MEM_AT_RE = re.compile(r'^\$[a-z0-9]+,\s*%lo\(([A-Za-z_.$][\w.$]*)\)\(\$at\)$')
# Mirrors coalesce_lui._MACRO_MEM_OP's own op set (including the float
# pseudo-mnemonics IDO's -S output uses) so "what this scanner calls a site"
# never drifts from "what fold_source can actually fold".
MEM_OPS = {"sw", "sh", "sb", "lw", "lh", "lhu", "lb", "lbu", "swc1", "lwc1",
           "s.s", "l.s", "s.d", "l.d"}
GLABEL_RE = re.compile(r'^glabel\s+([A-Za-z_]\w*)\s*$')


def find_owners(src_root: Path):
    """Yield (c_file, asm_rel_dir, function_name) for every live GLOBAL_ASM owner."""
    for c_file in sorted(src_root.rglob("*.c")):
        try:
            text = c_file.read_text(encoding="utf-8", errors="surrogateescape")
        except OSError:
            continue
        for match in GLOBAL_ASM_RE.finditer(text):
            _, asm_reldir, func = match.groups()
            yield c_file, asm_reldir, func


def extract_function_lines(asm_text: str, function_name: str):
    """Return the raw lines belonging to one glabel block (up to the next glabel)."""
    lines = asm_text.splitlines()
    start = None
    for i, line in enumerate(lines):
        m = GLABEL_RE.match(line.strip())
        if m and m.group(1) == function_name:
            start = i
            break
    if start is None:
        return None
    end = len(lines)
    for j in range(start + 1, len(lines)):
        if GLABEL_RE.match(lines[j].strip()):
            end = j
            break
    return lines[start:end]


def parse_instrs(lines):
    """Parse ground-truth instruction lines into (op, operands), or None."""
    parsed = []
    for line in lines:
        m = GT_INSTR_RE.match(line)
        parsed.append((m.group("op"), m.group("operands").strip()) if m else None)
    return parsed


def find_shared_at_runs(parsed, function_name, addr_map, *, max_gap=40):
    """Yield every shared-$at, distinct-symbol run (contiguous or not).

    A run starts at a `lui $at, %hi(SYM0)` and extends through every
    subsequent `<memop> $reg, %lo(SYMn)($at)` up to (but not including) the
    next instruction that redefines `$at` (a fresh `lui $at, ...`) or a gap
    longer than `max_gap` instructions (a generous bound -- real interleaved
    runs in this ROM are a handful of instructions apart at most; this just
    keeps a pathological function from turning into an unbounded scan).
    """
    sites = []
    n = len(parsed)
    i = 0
    while i < n:
        entry = parsed[i]
        if entry is None:
            i += 1
            continue
        op, operands = entry
        if op == "lui":
            m = LUI_AT_RE.match(operands)
            if m:
                base_sym = m.group(1)
                members = []  # (line_index, op, sym)
                gap = 0
                j = i + 1
                while j < n:
                    ej = parsed[j]
                    if ej is None:
                        gap += 1
                        j += 1
                        if gap > max_gap:
                            break
                        continue
                    jop, joperands = ej
                    if jop == "lui" and "$at" in joperands:
                        break  # $at redefined -- run ends here
                    if jop in MEM_OPS:
                        jm = MEM_AT_RE.match(joperands)
                        if jm:
                            members.append((j, jop, jm.group(1)))
                            j += 1
                            continue
                    if "$at" in joperands:
                        break  # $at clobbered by something else entirely
                    gap += 1
                    j += 1
                    if gap > max_gap:
                        break
                if members and members[0][2] == base_sym:
                    all_syms = [base_sym] + [s for _, _, s in members[1:]]
                    all_ops = [op] + [o for _, o, _ in members[1:]]
                    line_indices = [i] + [ln for ln, _, _ in members]
                    if len(all_syms) >= 2 and len(set(all_syms)) > 1:
                        contiguous = all(
                            line_indices[k] == line_indices[k - 1] + 1
                            for k in range(1, len(line_indices))
                        )
                        addrs = [addr_map.get(s) for s in all_syms]
                        resolved = all(a is not None for a in addrs)
                        same_page = resolved and len(
                            {coalesce_lui.hi16(a) for a in addrs}
                        ) == 1
                        sites.append({
                            "function": function_name,
                            "lui_line_index": i,
                            "symbols": all_syms,
                            "ops": all_ops,
                            "addresses": [
                                (hex(a) if a is not None else None) for a in addrs
                            ],
                            "resolved": resolved,
                            "same_page": same_page,
                            "contiguous": contiguous,
                            "run_length": len(all_syms),
                        })
        i += 1
    return sites


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo-root", type=Path, default=_DEFAULT_REPO_ROOT)
    parser.add_argument("--asm-root", type=Path, default=None,
                         help="disasm/asm root to read ground truth from "
                              "(default: the primary checkout's, read-only)")
    parser.add_argument("--interleaved", action="store_true",
                         help="also emit interleaved (currently unfoldable) sites")
    args = parser.parse_args()

    repo_root = args.repo_root.resolve()
    src_root = repo_root / "disasm" / "src"
    asm_root = args.asm_root
    if asm_root is None:
        primary = coalesce_lui._primary_worktree_root(repo_root)
        if primary is None:
            print("error: could not resolve a primary worktree root for "
                  "disasm/asm; pass --asm-root explicitly", file=sys.stderr)
            sys.exit(1)
        asm_root = primary / "disasm" / "asm"

    addr_map = coalesce_lui.resolve_repo_addresses(repo_root)
    if not addr_map:
        primary = coalesce_lui._primary_worktree_root(repo_root)
        if primary is not None:
            addr_map = coalesce_lui.resolve_repo_addresses(primary)
    print(f"# resolved {len(addr_map)} addresses", file=sys.stderr)

    n_owners = 0
    n_missing_asm = 0
    n_contiguous = 0
    n_interleaved = 0
    n_unresolved = 0

    for c_file, asm_reldir, func in find_owners(src_root):
        n_owners += 1
        asm_path = asm_root / "us" / "nonmatchings" / asm_reldir / f"{func}.s"
        if not asm_path.is_file():
            n_missing_asm += 1
            continue
        try:
            asm_text = asm_path.read_text(encoding="latin1")
        except OSError:
            n_missing_asm += 1
            continue
        lines = extract_function_lines(asm_text, func)
        if lines is None:
            n_missing_asm += 1
            continue
        parsed = parse_instrs(lines)
        for site in find_shared_at_runs(parsed, func, addr_map):
            if not (site["resolved"] and site["same_page"]):
                n_unresolved += 1
                continue
            if site["contiguous"]:
                n_contiguous += 1
            else:
                n_interleaved += 1
                if not args.interleaved:
                    continue
            site["c_file"] = str(c_file.relative_to(repo_root))
            site["asm_path"] = str(asm_path)
            print(json.dumps(site))

    print(
        f"# owners scanned: {n_owners}, missing asm: {n_missing_asm}, "
        f"contiguous sites: {n_contiguous}, interleaved sites: {n_interleaved} "
        f"(fold_source cannot fold these), address-unresolved/cross-page "
        f"runs skipped: {n_unresolved}",
        file=sys.stderr,
    )


if __name__ == "__main__":
    main()
