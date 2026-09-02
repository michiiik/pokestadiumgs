#!/usr/bin/env python3
"""Fast single-candidate probe for interactive hand-decompilation iteration.

``tools/fleet_probe.py`` is built around batches: a coding agent (or a
human) that wants to try one small change to one candidate body still has
to write a whole batch JSON and read back a table. During the §2.5 hand
loop -- and especially when an agent (Codex/Kimi/Claude Code) is iterating
on a single candidate many times in one turn -- that overhead dominates.
This tool wraps exactly one candidate: it writes a one-candidate batch JSON
to a temp file, shells out to ``tools/fleet_probe.py`` once (probe-only,
``--no-auto-gate``, a bounded timeout), and renders a compact report from
the single resulting attempt. Typical wall time is close to the probe
runner's own per-candidate cost (about a second), not the ~5 minutes of a
driver batch cycle.

This is a probe-only tool: it never passes ``--gate`` to fleet_probe.py, so
it never touches the ROM gate and never installs anything.

Usage:
    tools/probe_one.py --source disasm/src/X.c --function func_X \\
        --body body.c [--declarations decls.h] [--label L] \\
        [--json out.json] [--max-diff N]

    echo '...' | tools/probe_one.py --source disasm/src/X.c \\
        --function func_X --body -

Exit codes:
    0 -- the probe ran (accepted, probe_match, or probe_rejected -- a
         rejection is an expected, informative outcome, not a tool failure)
    1 -- the candidate failed to compile
    2 -- a preflight or infrastructure problem: bad body shape, a
         fleet_probe/runner error, a timeout, or a status this tool cannot
         make sense of

The rendering logic (diff excerpt, frame/instruction-count lines, first
mismatch, normalized-only-match warning) is a standalone copy of the same
logic in ``tools/container_agent.py`` (``_build_feedback`` /
``_render_best_candidates``), kept separate so this tool has no import
dependency on the driver.
"""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
import tempfile
from pathlib import Path

TOOLS_DIR = Path(__file__).resolve().parent
REPO_ROOT = TOOLS_DIR.parent
FLEET_PROBE_REL = "tools/fleet_probe.py"

DEFAULT_LABEL = "probe"
DEFAULT_TIMEOUT = 120.0
DEFAULT_MAX_DIFF = 60
COMPILE_ERROR_MAX_LINES = 30

# Statuses fleet_probe/try_pragma_compare can report for a single attempt
# that mean the probe actually ran and produced a real verdict.
_RAN_STATUSES = {"accepted", "probe_match", "probe_rejected"}


# ---------------------------------------------------------------------------
# Body-shape guard
# ---------------------------------------------------------------------------

def check_body_shape(body: str, function: str) -> str | None:
    """Return an error message if ``body`` is not a complete function
    definition for ``function``, else ``None``.

    A candidate body must contain the function name immediately followed by
    ``(`` somewhere before the first ``{`` -- i.e. it looks like a full
    ``ReturnType func_X(...) { ... }`` definition, not a bare statement
    block (which would compile-fail or, worse, silently redefine something
    else once spliced into the source).
    """
    if not body.strip():
        return "body is empty"
    brace_index = body.find("{")
    if brace_index == -1:
        return "body has no '{' -- not a complete function definition"
    header = body[:brace_index]
    if not re.search(re.escape(function) + r"\s*\(", header):
        return (
            f"body does not contain '{function}(' before the first '{{' -- "
            "bodies must be complete function definitions (return type, "
            "name, parameter list, and braces), not a bare statement block"
        )
    return None


# ---------------------------------------------------------------------------
# Batch construction
# ---------------------------------------------------------------------------

def build_batch_payload(
    *, source: str, function: str, body: str, label: str, declarations: str | None
) -> dict[str, object]:
    payload: dict[str, object] = {
        "source": source,
        "candidates": [{"function": function, "label": label, "body": body}],
    }
    if declarations:
        payload["declarations"] = declarations
    return payload


# ---------------------------------------------------------------------------
# Runner invocation (isolated so tests can stub it)
# ---------------------------------------------------------------------------

def run_probe_subprocess(
    batch_path: Path, result_path: Path, *, repo_root: Path, timeout: float
) -> subprocess.CompletedProcess:
    """Run ``tools/fleet_probe.py`` once, probe-only, on one batch file."""
    cmd = [
        sys.executable,
        FLEET_PROBE_REL,
        str(batch_path),
        "--no-auto-gate",
        "--json",
        str(result_path),
    ]
    return subprocess.run(
        cmd, cwd=repo_root, capture_output=True, text=True, timeout=timeout,
    )


# ---------------------------------------------------------------------------
# Diagnostics helpers (standalone copies of container_agent.py's rendering)
# ---------------------------------------------------------------------------

def is_normalized_only_match(attempt: dict) -> bool:
    """Whether ``attempt`` is a normalized-only match: the shape (opcode
    sequence) lines up but registers/immediates/fields do not, and it was
    not actually accepted. Mirrors container_agent.py's
    ``_is_normalized_only_match``, kept as a standalone copy.
    """
    if attempt.get("normalized_only_match") is True:
        return True
    if attempt.get("normalized_only") is True:
        return True
    diagnostic = attempt.get("diagnostic")
    if isinstance(diagnostic, str) and "normalized_only_match" in diagnostic:
        return True
    similarity = attempt.get("similarity_score")
    raw = attempt.get("raw_similarity_score")
    status = attempt.get("status")
    if (
        isinstance(similarity, (int, float)) and similarity >= 0.999
        and status != "accepted"
        and isinstance(raw, (int, float)) and raw < 0.95
    ):
        return True
    return False


def render_diff_excerpt(
    assembly_diff: list[dict], max_entries: int, already_truncated: bool
) -> list[str]:
    """Render the first ``max_entries`` non-exact-match entries of
    ``assembly_diff``, with one line of exact-match context immediately
    before the first mismatch, marking truncation.
    """
    lines: list[str] = []
    context_line: str | None = None
    shown = 0
    truncated = already_truncated
    for entry in assembly_diff:
        if entry.get("exact_match"):
            context_line = f"  @{entry.get('expected_offset')}: {entry.get('expected')}  (match)"
            continue
        line = (
            f"  @{entry.get('expected_offset')}: expected `{entry.get('expected')}`"
            f"  actual `{entry.get('actual')}`"
        )
        if shown >= max_entries:
            truncated = True
            break
        if shown == 0 and context_line:
            lines.append(context_line)
        lines.append(line)
        shown += 1
    if truncated and lines:
        lines.append("  ... (diff truncated)")
    elif truncated and not lines:
        lines.append("  (diff truncated -- no entries fit)")
    return lines


def _fmt_score(value: object) -> str:
    if isinstance(value, (int, float)):
        return f"{value:.4f}"
    return "-"


def render_report(attempt: dict, *, max_diff: int) -> list[str]:
    lines: list[str] = []
    lines.append(f"function: {attempt.get('function')}   label: {attempt.get('label')}")
    lines.append(f"status: {attempt.get('status')}")

    probe_reason = attempt.get("probe_reason")
    if probe_reason:
        lines.append(f"probe_reason: {probe_reason}")

    similarity = attempt.get("similarity_score")
    raw = attempt.get("raw_similarity_score")
    if similarity is not None or raw is not None:
        lines.append(f"similarity: {_fmt_score(similarity)}   raw: {_fmt_score(raw)}")

    mismatch_kind = attempt.get("mismatch_kind")
    if mismatch_kind:
        lines.append(f"mismatch_kind: {mismatch_kind}")

    futility = attempt.get("futility")
    if futility:
        lines.append(f"futility: {futility}")

    expected_size = attempt.get("expected_size")
    actual_size = attempt.get("actual_size")
    if expected_size is not None and actual_size is not None and expected_size != actual_size:
        lines.append(f"frame: expected {expected_size} bytes, actual {actual_size}")

    expected_count = attempt.get("expected_instruction_count")
    actual_count = attempt.get("actual_instruction_count")
    if expected_count is not None or actual_count is not None:
        lines.append(f"instructions: expected {expected_count}, actual {actual_count}")

    first_diff_offset = attempt.get("first_diff_offset")
    if first_diff_offset is not None:
        lines.append(
            f"first mismatch at offset {first_diff_offset}: "
            f"expected `{attempt.get('expected_instruction_text')}` "
            f"actual `{attempt.get('actual_instruction_text')}`"
        )

    if is_normalized_only_match(attempt):
        lines.append("")
        lines.append(
            "*** NORMALIZED-ONLY MATCH: the opcode shape matches but "
            f"immediates/registers/fields differ (raw={_fmt_score(raw)}) -- "
            "vary constants, field offsets and operand order, not structure. ***"
        )

    assembly_diff = attempt.get("assembly_diff")
    if isinstance(assembly_diff, list) and assembly_diff:
        diff_lines = render_diff_excerpt(
            assembly_diff, max_diff, bool(attempt.get("assembly_diff_truncated"))
        )
        if diff_lines:
            lines.append("")
            lines.append("diff:")
            lines.extend(diff_lines)

    if attempt.get("status") == "compile_failed":
        diagnostic = attempt.get("diagnostic")
        diag_text = diagnostic if isinstance(diagnostic, str) else ""
        diag_all_lines = diag_text.splitlines()
        shown_lines = diag_all_lines[:COMPILE_ERROR_MAX_LINES]
        lines.append("")
        lines.append("compiler error (first "
                      f"{COMPILE_ERROR_MAX_LINES} lines):")
        lines.extend(shown_lines if shown_lines else ["(no diagnostic text)"])
        if len(diag_all_lines) > COMPILE_ERROR_MAX_LINES:
            lines.append("... (truncated)")

    diagnostic = attempt.get("diagnostic")
    if diagnostic and attempt.get("status") not in ("compile_failed",):
        lines.append("")
        lines.append(f"diagnostic: {diagnostic}")

    return lines


def exit_code_for_attempt(attempt: dict) -> int:
    status = attempt.get("status")
    if status == "compile_failed":
        return 1
    if status in _RAN_STATUSES:
        return 0
    return 2


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def _read_body(raw: str) -> str:
    if raw == "-":
        return sys.stdin.read()
    return Path(raw).read_text(encoding="utf-8")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("--source", required=True, help="repo-relative source .c path")
    parser.add_argument("--function", required=True, help="the GLOBAL_ASM owner, e.g. func_X")
    parser.add_argument(
        "--body", required=True,
        help="path to a file with the complete candidate function definition, or '-' for stdin",
    )
    parser.add_argument("--declarations", help="path to a file of shared extern/prototype lines")
    parser.add_argument("--label", default=DEFAULT_LABEL, help="candidate label (default: probe)")
    parser.add_argument("--json", type=Path, help="also write the raw attempt dict as JSON here")
    parser.add_argument(
        "--max-diff", type=int, default=DEFAULT_MAX_DIFF,
        help=f"max non-exact-match diff entries to show (default {DEFAULT_MAX_DIFF})",
    )
    parser.add_argument(
        "--timeout", type=float, default=DEFAULT_TIMEOUT,
        help=f"fleet_probe.py subprocess timeout in seconds (default {DEFAULT_TIMEOUT})",
    )
    args = parser.parse_args(argv)

    try:
        body = _read_body(args.body)
    except OSError as exc:
        print(f"probe_one: could not read --body: {exc}", file=sys.stderr)
        return 2

    shape_error = check_body_shape(body, args.function)
    if shape_error:
        print(f"probe_one: {shape_error}", file=sys.stderr)
        return 2

    declarations = None
    if args.declarations:
        try:
            declarations = Path(args.declarations).read_text(encoding="utf-8")
        except OSError as exc:
            print(f"probe_one: could not read --declarations: {exc}", file=sys.stderr)
            return 2

    payload = build_batch_payload(
        source=args.source,
        function=args.function,
        body=body,
        label=args.label,
        declarations=declarations,
    )

    with tempfile.TemporaryDirectory(prefix="probe_one_") as tmp_dir:
        tmp_path = Path(tmp_dir)
        batch_path = tmp_path / "batch.json"
        result_path = tmp_path / "result.json"
        batch_path.write_text(json.dumps(payload, indent=2), encoding="utf-8")

        try:
            proc = run_probe_subprocess(
                batch_path, result_path, repo_root=REPO_ROOT, timeout=args.timeout
            )
        except subprocess.TimeoutExpired:
            print(
                f"probe_one: fleet_probe.py timed out after {args.timeout}s",
                file=sys.stderr,
            )
            return 2
        except OSError as exc:
            print(f"probe_one: failed to run fleet_probe.py: {exc}", file=sys.stderr)
            return 2

        if proc.returncode == 2:
            # fleet_probe's own preflight/InputError path.
            stderr_text = (proc.stderr or "").strip()
            print(f"probe_one: fleet_probe preflight failed:\n{stderr_text}", file=sys.stderr)
            return 2
        if proc.returncode not in (0, 1):
            print(
                f"probe_one: fleet_probe.py exited {proc.returncode}\n"
                f"stdout:\n{proc.stdout}\nstderr:\n{proc.stderr}",
                file=sys.stderr,
            )
            return 2
        if proc.returncode == 1:
            # fleet_probe reports its own runner_internal_error here; the
            # probe did not produce a real verdict.
            print(
                "probe_one: fleet_probe.py reported a runner internal error\n"
                f"stdout:\n{proc.stdout}\nstderr:\n{proc.stderr}",
                file=sys.stderr,
            )
            return 2

        if not result_path.exists():
            print(
                "probe_one: fleet_probe.py exited 0 but wrote no result JSON\n"
                f"stdout:\n{proc.stdout}\nstderr:\n{proc.stderr}",
                file=sys.stderr,
            )
            return 2

        try:
            result = json.loads(result_path.read_text(encoding="utf-8"))
        except json.JSONDecodeError as exc:
            print(f"probe_one: could not parse result JSON: {exc}", file=sys.stderr)
            return 2

        attempts = result.get("attempts")
        if not isinstance(attempts, list) or not attempts:
            print(
                f"probe_one: no attempts in result (batch_status={result.get('batch_status')})",
                file=sys.stderr,
            )
            return 2

        attempt = next(
            (a for a in attempts if isinstance(a, dict) and a.get("label") == args.label),
            attempts[0],
        )

        print("\n".join(render_report(attempt, max_diff=args.max_diff)))

        if args.json:
            args.json.write_text(json.dumps(attempt, indent=2, default=str), encoding="utf-8")
            print(f"\nraw attempt written to {args.json}")

        return exit_code_for_attempt(attempt)


if __name__ == "__main__":
    raise SystemExit(main())
