#!/usr/bin/env python3
"""Sweep small pragma-backed functions through m2c drafts and the candidate runner.

For every remaining owner that passes the size/family filters, this asks m2c
for a ``--valid-syntax`` draft, rewrites it into a few IDO-compilable
variants (raw ``u8 *`` field access, unknown types resolved several ways),
probes all variants per source in isolation, and gates the byte hits through
``COMPARE=1``.  Every attempt lands in the probe stats file, so the run also
measures how well mechanical drafts convert per family.

Usage:
    tools/sweep_targets.py --max-instructions 16                # everything small
    tools/sweep_targets.py --family call_sequence --limit 50    # a sample
    tools/sweep_targets.py --no-gate --source disasm/src/229E0.c

Sources with uncommitted changes are skipped: another session may be
mid-transaction in them.
"""

from __future__ import annotations

import argparse
import collections
import json
import re
import subprocess
import sys
import time
from pathlib import Path

import dedupe_externs
import pragma_targets as targets
import try_pragma_compare as runner

FIELD_RE = re.compile(r"M2C_FIELD\(\s*([^,]+?)\s*,\s*([^,]+?)\s*,\s*([^)]+?)\s*\)")
UNK_GLOBAL_RE = re.compile(r"^extern M2C_UNK (\w+);", re.M)
UNK_FUNCTION_RE = re.compile(r"^M2C_UNK (\w+)\(([^)]*)\);(\s*/\* extern \*/)?", re.M)
UNK_TYPE_RE = re.compile(r"\bM2C_UNK\b")
EMPTY_BLOCK_RE = re.compile(r"\{\s*\}")

VARIANTS: dict[str, dict[str, str]] = {
    # unknown globals, unknown call returns, other unknown types
    "u8-void": {"global": "u8", "call": "void", "type": "s32"},
    "s32-s32": {"global": "s32", "call": "s32", "type": "s32"},
    "ptr-void": {"global": "u8 *", "call": "void", "type": "s32"},
    "u16-s32": {"global": "u16", "call": "s32", "type": "s32"},
}


def rewrite_draft(draft: str, variant: dict[str, str]) -> str | None:
    """Turn an m2c ``--valid-syntax`` draft into plain C for one type guess."""
    if "M2C_ERROR" in draft:
        return None
    text = FIELD_RE.sub(lambda m: f"(*({m.group(2)})((u8 *)({m.group(1)}) + ({m.group(3)})))", draft)
    text = UNK_GLOBAL_RE.sub(lambda m: f"extern {variant['global']} {m.group(1)};", text)
    text = UNK_FUNCTION_RE.sub(lambda m: f"extern {variant['call']} {m.group(1)}({m.group(2)});", text)
    text = UNK_TYPE_RE.sub(variant["type"], text)
    text = re.sub(r"\s*/\* extern \*/", "", text)
    if "M2C_" in text:
        return None
    return text.strip() + "\n"


def padding_retry(attempt: dict[str, object]) -> int | None:
    """Return the C_FUNCTION_PADDING byte count that would complete a prefix match.

    The runner reports ``symbol_size_drift`` when every byte of the shorter
    symbol matches and only the baseline's trailing alignment nops are
    missing; the declarative padding marker reproduces exactly those bytes.
    """
    if attempt.get("mismatch_kind") != "symbol_size_drift" or attempt.get("diff_offsets"):
        return None
    expected = attempt.get("expected_size")
    actual = attempt.get("actual_size")
    if not isinstance(expected, int) or not isinstance(actual, int) or expected <= actual:
        return None
    if attempt.get("expected_tail_kind") not in {"jr_nop_plus_alignment", "nop_only_tail"}:
        return None
    padding = expected - actual
    return padding if padding % 4 == 0 else None


def draft_variants(function: str, context: bool = True) -> tuple[list[tuple[str, str]], str | None]:
    """Return ``[(label, code)]`` variants for one function and the raw draft."""
    owner = targets.require_owner(function)
    context_path = targets.preprocessed_context(owner) if context else None
    command = [sys.executable, str(targets.M2C_SCRIPT), "--target", "mips-ido-c", "--valid-syntax", "--globals", "used"]
    if context_path is not None:
        command += ["--context", str(context_path)]
    result = subprocess.run(command + [str(owner.asm_path)], text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=60)
    if result.returncode != 0 or not result.stdout.strip():
        return [], None
    draft = result.stdout
    seen: set[str] = set()
    variants: list[tuple[str, str]] = []
    for name, variant in VARIANTS.items():
        code = rewrite_draft(draft, variant)
        if code is None or code in seen:
            continue
        seen.add(code)
        variants.append((f"m2c:{name}", code))
    return variants, draft


def previously_attempted(stats_path: Path = targets.STATS_PATH, label_prefix: str = "m2c:") -> set[str]:
    """Functions that already have sweep attempts recorded in the stats file."""
    attempted: set[str] = set()
    if not stats_path.exists():
        return attempted
    for line in stats_path.read_text(encoding="utf-8").splitlines():
        try:
            record = json.loads(line)
        except json.JSONDecodeError:
            continue
        for attempt in record.get("attempts", []):
            label = attempt.get("label") or ""
            if label.startswith(label_prefix) and attempt.get("function"):
                attempted.add(str(attempt["function"]))
    return attempted


def sweep(
    *,
    max_instructions: int | None,
    min_instructions: int | None,
    family: str | None,
    source: str | None,
    limit: int,
    gate: bool,
    workers: int | None,
    skip_functions: set[str] | None = None,
) -> dict[str, object]:
    listing = targets.list_targets(
        source=source,
        family=family,
        max_instructions=max_instructions,
        min_instructions=min_instructions,
        limit=limit,
    )
    dirty = dedupe_externs.dirty_sources()
    by_source: dict[str, list[dict[str, object]]] = collections.defaultdict(list)
    skipped_dirty = 0
    for row in listing["targets"]:
        if (targets.REPO_ROOT / str(row["source"])).resolve() in dirty:
            skipped_dirty += 1
            continue
        by_source[str(row["source"])].append(row)

    summary: dict[str, collections.Counter] = collections.defaultdict(collections.Counter)
    accepted_functions: list[str] = []
    touched_sources: list[str] = []
    started = time.monotonic()
    for source_rel, rows in sorted(by_source.items(), key=lambda item: -len(item[1])):
        blocks: list[tuple[str, str]] = []
        labels: list[str] = []
        family_of: dict[str, str] = {}
        for row in rows:
            function = str(row["function"])
            family_of[function] = str(row["family"])
            if skip_functions and function in skip_functions:
                summary[family_of[function]]["skipped_attempted"] += 1
                continue
            try:
                variants, draft = draft_variants(function)
            except KeyError:
                # Another session replaced this pragma since the target list
                # was captured; it is no longer ours to attempt.
                summary[family_of[function]]["vanished"] += 1
                continue
            except (OSError, subprocess.SubprocessError) as error:
                summary[family_of[function]]["draft_failed"] += 1
                print(f"{function}: draft error: {error}", file=sys.stderr)
                continue
            if draft is None:
                summary[family_of[function]]["draft_failed"] += 1
                continue
            if not variants:
                summary[family_of[function]]["draft_unusable"] += 1
                continue
            for label, code in variants:
                blocks.append((function, code))
                labels.append(label)
        if not blocks:
            continue
        source_path = targets.REPO_ROOT / source_rel
        # Pass 1: probe every variant in isolation.  Pass 2 gates only the
        # hits, plus padding retries for bodies that matched the baseline
        # prefix but stopped short of its trailing alignment nops.
        try:
            probe = runner.try_candidates_detailed(
                source_path, blocks, labels=labels, gate=False, probe_workers=workers
            )
        except Exception as error:  # one broken source must not end the sweep
            print(f"{source_rel}: probe pass failed: {error}", file=sys.stderr)
            summary["_errors"]["probe_pass_failed"] += 1
            continue
        gate_blocks: list[tuple[str, str]] = []
        gate_labels: list[str] = []
        for attempt in probe["attempts"]:
            index = int(attempt["index"])
            padding = padding_retry(attempt)
            if attempt.get("status") == "probe_match":
                gate_blocks.append(blocks[index])
                gate_labels.append(labels[index])
            elif padding:
                function, code = blocks[index]
                gate_blocks.append((function, code.rstrip() + f"\n#pragma C_FUNCTION_PADDING({padding})\n"))
                gate_labels.append(labels[index] + "+padding")
        result = probe
        if gate_blocks:
            try:
                result = runner.try_candidates_detailed(
                    source_path, gate_blocks, labels=gate_labels, gate=gate, probe_workers=workers
                )
            except Exception as error:
                print(f"{source_rel}: gate pass failed: {error}", file=sys.stderr)
                summary["_errors"]["gate_pass_failed"] += 1
                continue
            # Keep the diagnostics of pass 1 for functions that had nothing to gate.
            gated_functions = {function for function, _ in gate_blocks}
            result["attempts"] = list(result["attempts"]) + [
                attempt for attempt in probe["attempts"] if attempt["function"] not in gated_functions
            ]
        per_function: dict[str, dict[str, object]] = {}
        for attempt in result["attempts"]:
            function = str(attempt["function"])
            status = str(attempt.get("status"))
            best = per_function.setdefault(function, {"status": None, "score": -1.0, "kind": None})
            rank = {"accepted": 5, "probe_match": 4, "compare_rejected": 3, "probe_rejected": 2, "compile_failed": 1, "skipped": 0}
            if rank.get(status, 0) > rank.get(str(best["status"]), -1):
                best["status"] = status
            score = attempt.get("similarity_score")
            if isinstance(score, (int, float)) and score > float(best["score"]):
                best["score"] = float(score)
                best["kind"] = attempt.get("mismatch_kind")
        for function, best in per_function.items():
            fam = family_of[function]
            summary[fam]["attempted"] += 1
            summary[fam][f"best:{best['status']}"] += 1
            if best["kind"]:
                summary[fam][f"kind:{best['kind']}"] += 1
            if best["score"] >= 0.9 and best["status"] not in {"accepted", "probe_match"}:
                summary[fam]["near_miss_ge_0.9"] += 1
        if result.get("accepted"):
            accepted_functions.extend(result["accepted"])
            touched_sources.append(source_rel)
        print(
            f"{source_rel}: {len(rows)} targets, {len(blocks)} probes, "
            f"accepted {len(result.get('accepted', []))} ({result['batch_status']})",
            file=sys.stderr,
        )
    return {
        "matched": listing["matched"],
        "skipped_dirty_sources": skipped_dirty,
        "sources": len(by_source),
        "accepted": accepted_functions,
        "touched_sources": sorted(set(touched_sources)),
        "elapsed_seconds": round(time.monotonic() - started, 1),
        "summary": {family: dict(sorted(counter.items())) for family, counter in sorted(summary.items())},
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--max-instructions", type=int)
    parser.add_argument("--min-instructions", type=int)
    parser.add_argument("--family")
    parser.add_argument("--source")
    parser.add_argument("--limit", type=int, default=2000)
    parser.add_argument("--no-gate", action="store_true", help="probe only; never edit tracked sources")
    parser.add_argument("--workers", type=int)
    parser.add_argument("--json", type=Path, help="write the summary to this file")
    parser.add_argument("--skip-attempted", action="store_true", help="skip functions that already have m2c sweep attempts in the stats file")
    args = parser.parse_args()
    result = sweep(
        max_instructions=args.max_instructions,
        min_instructions=args.min_instructions,
        family=args.family,
        source=args.source,
        limit=args.limit,
        gate=not args.no_gate,
        workers=args.workers,
        skip_functions=previously_attempted() if args.skip_attempted else None,
    )
    text = json.dumps(result, indent=2)
    if args.json:
        args.json.write_text(text + "\n")
    print(text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
