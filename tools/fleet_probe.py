#!/usr/bin/env python3
"""Thin CLI wrapper around ``try_pragma_compare.try_candidates_detailed``.

A fleet agent normally writes its own throwaway batch script to send a
handful of candidate bodies through the runner and then re-derives a summary
from the raw JSON.  That is pure overhead: the runner already returns
everything needed (``status``, ``mismatch_kind``, ``similarity_score``,
``raw_similarity_score``, ``first_diff_offset``, the instruction text at the
first difference, sizes, ``link_verified``, ``diagnostic``) per attempt in
``attempts[]`` (including prior-attempt count, futility, and link status).  This
script takes one JSON description of a batch, calls the runner once, and prints
a compact table plus a one-line verdict per function, so an agent reads a
table instead of a raw JSON blob.  Compiler/link diagnostics are collapsed to
single-line table cells and truncated to fit the table.

Input (default form) -- a JSON file:

    {
      "source": "disasm/src/4AC10.c",
      "declarations": "extern Gfx *D_800D0510;\\n",
      "companion_edits": [
        {"function": "func_8004A020", "old": "old text", "new": "new text"}
      ],
      "candidates": [
        {"function": "func_8004A010", "label": "wrapper:guard-return:u8-arg",
         "body": "void func_8004A010(s32 arg0) { ... }"},
        {"function": "func_8004A010", "label": "wrapper:assign-then-return",
         "body": "..."}
      ]
    }

``source`` may be given on the command line instead
(``--source disasm/src/X.c``); a value there overrides the JSON file's.
``declarations`` is optional; ``--declarations-file PATH`` overrides/serves
it too.

Input (directory form) -- a directory of ``<label>.c`` files, one candidate
per file, each starting with a metadata comment line naming the owner:

    # function: func_8004A010
    void func_8004A010(s32 arg0) { ... }

The file's stem (without ``.c``) becomes the label.  ``--source`` is
required in this form, since the directory carries no such field.

Usage:
    tools/fleet_probe.py batch.json
    tools/fleet_probe.py batch.json --gate
    tools/fleet_probe.py variants_dir/ --source disasm/src/4AC10.c
    tools/fleet_probe.py batch.json --json out.json

Nothing here talks to the ROM gate unless ``--gate`` is passed: the default
is a probe-only batch (``gate: false``), matching the §2.5 hand loop's "one
probe-only batch first" rule.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

import try_pragma_compare as runner

REPO_ROOT = Path(__file__).resolve().parent.parent

FUNCTION_HEADER_RE = re.compile(r"^#\s*function:\s*(\S+)\s*$")
# Fallback: guess the owner from the first top-level definition/declaration
# in the body, e.g. "s32 func_8004A010(..." or "void func_8004A010(...".
FUNCTION_GUESS_RE = re.compile(r"\b(func_[0-9A-Fa-f]+)\s*\(")


class InputError(Exception):
    """A malformed batch description; reported on stderr, not a traceback."""


def _resolve_source(raw: str) -> Path:
    path = Path(raw)
    if not path.is_absolute():
        path = REPO_ROOT / path
    return path


def _load_json_batch(
    path: Path,
) -> tuple[
    str | None,
    str | None,
    list[tuple[str, str]],
    list[str],
    list[dict[str, str]] | None,
]:
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except json.JSONDecodeError as exc:
        raise InputError(f"{path}: invalid JSON ({exc})") from exc
    if not isinstance(payload, dict):
        raise InputError(f"{path}: top-level JSON value must be an object")
    source = payload.get("source")
    if source is not None and not isinstance(source, str):
        raise InputError(f"{path}: 'source' must be a string")
    declarations = payload.get("declarations")
    if declarations is not None and not isinstance(declarations, str):
        raise InputError(f"{path}: 'declarations' must be a string")
    companion_edits = payload.get("companion_edits")
    if companion_edits is not None:
        if not isinstance(companion_edits, list):
            raise InputError(f"{path}: 'companion_edits' must be a list")
        validated_edits: list[dict[str, str]] = []
        for index, edit in enumerate(companion_edits):
            if not isinstance(edit, dict):
                raise InputError(f"{path}: companion_edits[{index}] must be an object")
            if any(not isinstance(edit.get(field), str) for field in ("function", "old", "new")):
                raise InputError(
                    f"{path}: companion_edits[{index}] must contain string "
                    "fields 'function', 'old', and 'new'"
                )
            if not edit["function"]:
                raise InputError(f"{path}: companion_edits[{index}] 'function' must not be empty")
            validated_edits.append(
                {field: edit[field] for field in ("function", "old", "new")}
            )
    else:
        validated_edits = None
    candidates = payload.get("candidates")
    if not isinstance(candidates, list) or not candidates:
        raise InputError(f"{path}: 'candidates' must be a non-empty list")
    blocks: list[tuple[str, str]] = []
    labels: list[str] = []
    for index, entry in enumerate(candidates):
        if not isinstance(entry, dict):
            raise InputError(f"{path}: candidates[{index}] must be an object")
        function = entry.get("function")
        body = entry.get("body")
        if not isinstance(function, str) or not function:
            raise InputError(f"{path}: candidates[{index}] missing 'function'")
        if not isinstance(body, str) or not body:
            raise InputError(f"{path}: candidates[{index}] missing 'body'")
        label = entry.get("label")
        labels.append(label if isinstance(label, str) and label else f"candidate{index}")
        blocks.append((function, body))
    return source, declarations, blocks, labels, validated_edits


def _load_directory_batch(path: Path) -> tuple[list[tuple[str, str]], list[str]]:
    files = sorted(p for p in path.glob("*.c") if p.is_file())
    if not files:
        raise InputError(f"{path}: no *.c files found")
    blocks: list[tuple[str, str]] = []
    labels: list[str] = []
    for file_path in files:
        text = file_path.read_text(encoding="utf-8")
        lines = text.splitlines(keepends=True)
        function = None
        body_start = 0
        for offset, line in enumerate(lines):
            stripped = line.strip()
            if not stripped:
                body_start = offset + 1
                continue
            match = FUNCTION_HEADER_RE.match(stripped)
            if match:
                function = match.group(1)
                body_start = offset + 1
            break
        body = "".join(lines[body_start:])
        if function is None:
            guess = FUNCTION_GUESS_RE.search(body)
            if guess is None:
                raise InputError(
                    f"{file_path}: no '# function: func_...' header and no "
                    "func_XXXXXXXX(...) found to guess one"
                )
            function = guess.group(1)
        blocks.append((function, body))
        labels.append(file_path.stem)
    return blocks, labels


def load_batch(
    input_path: Path,
    *,
    source_override: str | None,
    declarations_override: str | None,
) -> tuple[
    Path,
    str | None,
    list[tuple[str, str]],
    list[str],
    list[dict[str, str]] | None,
]:
    """Return source, declarations, candidates, labels, and companion edits."""
    if input_path.is_dir():
        blocks, labels = _load_directory_batch(input_path)
        source = source_override
        declarations = declarations_override
        companion_edits = None
    else:
        source, declarations, blocks, labels, companion_edits = _load_json_batch(input_path)
        if source_override:
            source = source_override
        if declarations_override is not None:
            declarations = declarations_override
    if not source:
        raise InputError(
            "no 'source' in the batch JSON and no --source given; "
            "required to know which file the candidates replace pragmas in"
        )
    return _resolve_source(source), declarations, blocks, labels, companion_edits


def _compact_text(value: object) -> str | None:
    """Return a single-line representation suitable for the CLI table."""
    if value is None:
        return None
    text = re.sub(r"\s+", " ", str(value)).strip()
    return text or None


def _fmt(value: object, width: int) -> str:
    text = _compact_text(value) or "-"
    if len(text) > width:
        text = text[: width - 1] + "…"
    return f"{text:<{width}}"


COLUMNS = [
    ("FUNCTION", 16),
    ("LABEL", 28),
    ("STATUS", 16),
    ("SIM", 6),
    ("RAW", 6),
    ("PRIOR", 5),
    ("LINK", 28),
    ("MISMATCH", 24),
    ("FUTILITY", 34),
    ("DIAGNOSTIC", 48),
    ("EXP", 5),
    ("ACT", 5),
    ("DIFF@", 6),
    ("EXPECTED", 26),
    ("ACTUAL", 26),
]


def _score_text(value: object) -> str:
    if isinstance(value, (int, float)):
        return f"{value:.4f}"
    return "-"


def _link_text(attempt: dict[str, object]) -> str:
    """Format link-shape verification and its reason for one table cell."""
    verified = attempt.get("link_verified")
    status = "yes" if verified is True else "no" if verified is False else "?"
    mismatch = _compact_text(attempt.get("link_mismatch"))
    return f"{status}:{mismatch}" if mismatch else status


def _diagnostic_text(attempt: dict[str, object]) -> str | None:
    """Choose a short useful diagnostic, including link-only failures."""
    diagnostic = _compact_text(attempt.get("diagnostic"))
    if diagnostic:
        return diagnostic
    link_mismatch = _compact_text(attempt.get("link_mismatch"))
    link_detail = _compact_text(attempt.get("link_detail"))
    if link_mismatch or link_detail:
        return ": ".join(part for part in (link_mismatch, link_detail) if part)
    return _compact_text(attempt.get("reason"))


def format_table(attempts: list[dict[str, object]]) -> str:
    header = " ".join(_fmt(name, width) for name, width in COLUMNS)
    lines = [header, "-" * len(header)]
    for attempt in attempts:
        row = [
            attempt.get("function"),
            attempt.get("label"),
            attempt.get("status"),
            _score_text(attempt.get("similarity_score")),
            _score_text(attempt.get("raw_similarity_score")),
            attempt.get("prior_attempts"),
            _link_text(attempt),
            attempt.get("mismatch_kind"),
            attempt.get("futility"),
            _diagnostic_text(attempt),
            attempt.get("expected_size"),
            attempt.get("actual_size"),
            attempt.get("first_diff_offset"),
            attempt.get("expected_instruction_text"),
            attempt.get("actual_instruction_text"),
        ]
        lines.append(" ".join(_fmt(value, width) for (_, width), value in zip(COLUMNS, row)))
    return "\n".join(lines)


def _label_of(attempt: dict[str, object]) -> str:
    label = attempt.get("label")
    return label if isinstance(label, str) and label else "(unlabeled)"


def _has_register_tie_futility(attempts: list[dict[str, object]]) -> bool:
    """Return whether the runner explicitly declared register-tie futility."""
    return any(
        isinstance(futility := attempt.get("futility"), str)
        and futility.startswith("register-tie")
        for attempt in attempts
    )


def summarize_function(function: str, attempts: list[dict[str, object]]) -> str:
    accepted = [a for a in attempts if a.get("status") == "accepted"]
    if accepted:
        attempt = accepted[0]
        return f"{function}: ACCEPTED via {_label_of(attempt)} link={_link_text(attempt)}"
    probe_matches = [a for a in attempts if a.get("status") == "probe_match"]
    if probe_matches:
        attempt = probe_matches[0]
        return (
            f"{function}: PROBE MATCH via {_label_of(attempt)} link={_link_text(attempt)} "
            "(gate not run -- pass --gate)"
        )
    scored = [a for a in attempts if isinstance(a.get("similarity_score"), (int, float))]
    if not scored:
        statuses = sorted({str(a.get("status")) for a in attempts})
        diagnostic = _diagnostic_text(attempts[-1]) if attempts else None
        detail = f"; diagnostic={diagnostic}" if diagnostic else ""
        return f"{function}: no scored attempts ({len(attempts)} tried; status: {', '.join(statuses)}{detail})"
    best = max(
        scored,
        key=lambda a: (
            float(a.get("similarity_score") or 0.0),
            float(a.get("raw_similarity_score") or 0.0),
        ),
    )
    sim = best.get("similarity_score")
    raw = best.get("raw_similarity_score")
    verdict = (
        f"{function}: best={_label_of(best)} status={best.get('status')} "
        f"sim={_score_text(sim)} raw={_score_text(raw)} link={_link_text(best)} "
        f"mismatch={best.get('mismatch_kind')}"
    )
    futility = _compact_text(best.get("futility"))
    if futility:
        verdict += f" futility={futility}"
    if _has_register_tie_futility(attempts):
        verdict += " -- register tie — stop"
    elif best.get("mismatch_kind") == "register_allocation_only" and isinstance(sim, (int, float)) and sim >= 0.99:
        verdict += " -- possible register tie (advisory; runner futility not set)"
    return verdict


def summarize(attempts: list[dict[str, object]]) -> str:
    by_function: dict[str, list[dict[str, object]]] = {}
    order: list[str] = []
    for attempt in attempts:
        function = str(attempt.get("function"))
        if function not in by_function:
            by_function[function] = []
            order.append(function)
        by_function[function].append(attempt)
    return "\n".join(summarize_function(function, by_function[function]) for function in order)


def run(
    input_path: Path,
    *,
    source_override: str | None,
    declarations_override: str | None,
    gate: bool,
    probe_workers: int | None,
) -> dict[str, object]:
    source_path, declarations, blocks, labels, companion_edits = load_batch(
        input_path, source_override=source_override, declarations_override=declarations_override
    )
    if not source_path.exists():
        raise InputError(f"source file does not exist: {source_path}")
    return runner.try_candidates_detailed(
        source_path,
        blocks,
        probe_workers=probe_workers,
        labels=labels,
        gate=gate,
        declarations=declarations,
        companion_edits=companion_edits,
    )


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("input", type=Path, help="batch JSON file, or a directory of <label>.c candidates")
    parser.add_argument("--source", help="repo-relative source path (overrides/serves the batch)")
    parser.add_argument("--declarations-file", type=Path, help="file of shared extern/prototype lines")
    parser.add_argument(
        "--gate", action="store_true",
        help="run the full ROM gate (default: probe-only, gate: false)",
    )
    parser.add_argument("--workers", type=int, default=None, help="probe_workers override")
    parser.add_argument("--json", type=Path, help="also write the raw runner result as JSON to this path")
    args = parser.parse_args(argv)

    declarations_override = None
    if args.declarations_file is not None:
        declarations_override = args.declarations_file.read_text(encoding="utf-8")

    try:
        result = run(
            args.input,
            source_override=args.source,
            declarations_override=declarations_override,
            gate=args.gate,
            probe_workers=args.workers,
        )
    except InputError as exc:
        print(f"fleet_probe: {exc}", file=sys.stderr)
        return 2

    attempts = result.get("attempts")
    if not isinstance(attempts, list):
        attempts = []

    print(format_table(attempts))
    print()
    print(summarize(attempts))

    batch_status = result.get("batch_status")
    accepted = result.get("accepted")
    print()
    print(f"batch_status={batch_status} gate={result.get('gate')} accepted={accepted}")

    futility_summary = result.get("futility_summary")
    if isinstance(futility_summary, dict) and futility_summary:
        print("futility_summary:")
        for function, reason in futility_summary.items():
            print(f"  {function}: {_compact_text(reason) or '-'}")

    if args.json:
        args.json.write_text(json.dumps(result, indent=2, default=str), encoding="utf-8")
        print(f"raw result written to {args.json}")

    # Probe-only rejection is expected during the hand-decompilation loop and
    # remains nonfatal.  A runner-internal result is infrastructure failure,
    # even though it may still carry attempts useful for diagnosis.
    if (
        result.get("batch_status") == "runner_internal_error"
        or result.get("status") == "runner_internal_error"
    ):
        print("fleet_probe: runner internal error", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
