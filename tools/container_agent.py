#!/usr/bin/env python3
"""Single-source-file decompilation driver (GitHub issue #39).

Works on ONE ``disasm/src`` file at a time, one ``GLOBAL_ASM`` owner at a
time, in many short iterations, climbing toward a 1.0 similarity / accepted
match per owner. Candidate *generation* is fully delegated to an external
"generator command" the caller supplies (``--generator-cmd``); this driver
never contains model-specific code. It only:

1. discovers the file's remaining owners (``tools/pragma_targets.py targets``,
   falling back to a regex scan of the source for ``#pragma GLOBAL_ASM``);
2. for the active owner, writes a prompt file (file brief + target assembly +
   this run's best-so-far candidates/diagnostics + the batch JSON contract)
   and shells out to the generator command, substituting ``{prompt}``/
   ``{batch}`` with absolute paths;
3. runs ``tools/fleet_probe.py <batch> --json <result>`` itself and reads the
   result;
4. records per-candidate similarity into ``<out>/state.json``;
5. on acceptance, captures the installed function text (plus the batch's
   declarations/companion_edits) into ``<out>/accepted/<owner>.json`` and a
   ``git diff`` into ``<out>/accepted/<owner>.patch``;
6. on a strong near-miss (best similarity >= 0.95) or a runner-reported
   register-tie diagnostic, launches ``tools/permute_candidate.py`` and polls
   its output directory (never blocks on the subprocess itself), feeding the
   best output back as the next iteration's seed;
7. stops an owner after a similarity plateau, moves to the next owner, and
   stops the whole run at ``--budget-seconds``.

Every subprocess call carries an explicit timeout. The generator, probe, and
permuter invocations each live in their own small function
(``invoke_generator``, ``invoke_probe``, ``invoke_permuter``/``poll_permuter``)
so tests can stub them independently of the loop logic.

Usage:
    tools/container_agent.py --source disasm/src/X.c --out /tmp/run1 \\
        --generator-cmd "my-model-cli --prompt {prompt} --out {batch}"

Test mode (no generator; exercise the loop once with a fixed batch):
    tools/container_agent.py --source disasm/src/X.c --out /tmp/run1 \\
        --candidate-file batch.json
"""

from __future__ import annotations

import argparse
import json
import os
import re
import shlex
import signal
import subprocess
import sys
import time
from datetime import datetime, timezone
from pathlib import Path

TOOLS_DIR = Path(__file__).resolve().parent
REPO_ROOT_DEFAULT = TOOLS_DIR.parent

PRAGMA_RE = re.compile(r'#pragma\s+GLOBAL_ASM\("[^"]*/([A-Za-z_]\w*)\.s"\)')
OUTPUT_DIR_RE = re.compile(r"^output-(\d+)-(\d+)$")

DEFAULT_GENERATOR_TIMEOUT = 600.0
PROBE_TIMEOUT_CAP = 300.0
MISC_TIMEOUT = 60.0
BEST_CANDIDATES_KEPT = 5


# ---------------------------------------------------------------------------
# Small utilities
# ---------------------------------------------------------------------------

def now_iso() -> str:
    return datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


class Logger:
    """Appends timestamped lines to ``<out>/log.txt`` and echoes to stdout."""

    def __init__(self, path: Path) -> None:
        self.path = path
        self.path.parent.mkdir(parents=True, exist_ok=True)

    def log(self, message: str) -> None:
        line = f"[{now_iso()}] {message}"
        print(line)
        with self.path.open("a", encoding="utf-8") as handle:
            handle.write(line + "\n")


def load_json(path: Path) -> dict | None:
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return None


def save_json(path: Path, data: object) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_name(path.name + f".{os.getpid()}.tmp")
    tmp.write_text(json.dumps(data, indent=2, default=str), encoding="utf-8")
    tmp.replace(path)


def _finalize_run(summary: dict, out_dir: Path, stopped_reason: str, started: float) -> None:
    """Stamp ``summary`` with its stop reason/timing and close out its current
    ``runs`` entry (if any), then write ``<out_dir>/summary.json``."""
    summary["stopped_reason"] = stopped_reason
    summary["ended_at"] = now_iso()
    summary["wall_seconds"] = round(time.monotonic() - started, 1)
    if summary.get("runs"):
        summary["runs"][-1]["ended"] = summary["ended_at"]
        summary["runs"][-1]["stop_reason"] = stopped_reason
    save_json(out_dir / "summary.json", summary)


def _new_owner_state() -> dict:
    return {
        "status": "in_progress",
        "best_similarity": 0.0,
        "best_effective_similarity": 0.0,
        "best_raw_similarity": None,
        "best_label": None,
        "iterations": 0,
        "plateau_count": 0,
        "history": [],
        "best_candidates": [],
        "permuter_runs": [],
    }


# ---------------------------------------------------------------------------
# Normalized-only match detection
#
# The probe's ``similarity_score`` is normalized (it can read 1.0, or close
# to it, even while real register/immediate/field differences remain -- see
# ``raw_similarity_score``). An attempt whose diagnostic flags this
# explicitly, or whose normalized score looks perfect/near-perfect while its
# raw score is well below it and it was NOT actually accepted, is a
# "normalized-only match": it must never be allowed to look like a genuine
# near-miss to the driver (best-candidate selection, the improvement test,
# or the permuter trigger).
# ---------------------------------------------------------------------------

def _is_normalized_only_match(attempt: dict) -> bool:
    if attempt.get("normalized_only") is True:
        return True
    diagnostic = attempt.get("diagnostic") or ""
    if "normalized_only_match" in diagnostic:
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


def attempt_rank(attempt: dict) -> tuple[float, float]:
    """Rank key for an attempt (or a ``best_candidates`` entry): ``(effective
    similarity, raw similarity)``.

    Ordinarily ``effective`` is just ``similarity_score``. But a
    normalized-only match (see ``_is_normalized_only_match``) has its
    ``effective`` capped at ``0.9 + 0.1 * raw`` so it can never rank above,
    or tie with, a genuine near-miss -- it always stays below the 0.95
    permuter threshold unless raw itself is already high.
    """
    similarity = attempt.get("similarity_score") or 0.0
    raw = attempt.get("raw_similarity_score")
    raw_value = raw if isinstance(raw, (int, float)) else 0.0
    effective = similarity
    if _is_normalized_only_match(attempt):
        effective = min(similarity, 0.9 + 0.1 * raw_value)
    return (effective, raw_value)


# ---------------------------------------------------------------------------
# Owner discovery
# ---------------------------------------------------------------------------

def discover_owners(repo_dir: Path, source_rel: str, *, timeout: float = MISC_TIMEOUT) -> list[str]:
    """Return the file's remaining GLOBAL_ASM owners, in pragma_targets order.

    Falls back to a regex scan of the source (in file order) when
    ``pragma_targets.py`` is unavailable or reports nothing -- e.g. a
    synthetic test file outside the tracked ``disasm/src`` tree.
    """
    try:
        proc = subprocess.run(
            ["python3", "tools/pragma_targets.py", "targets", "--source", source_rel, "--json"],
            cwd=repo_dir, capture_output=True, text=True, timeout=timeout,
        )
        if proc.returncode == 0 and proc.stdout.strip():
            data = json.loads(proc.stdout)
            owners = [row["function"] for row in data.get("targets", []) if row.get("function")]
            if owners:
                return owners
    except (subprocess.TimeoutExpired, json.JSONDecodeError, OSError, KeyError, ValueError):
        pass
    return discover_owners_fallback(repo_dir, source_rel)


def discover_owners_fallback(repo_dir: Path, source_rel: str) -> list[str]:
    source_path = repo_dir / source_rel
    try:
        text = source_path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return []
    owners: list[str] = []
    for match in PRAGMA_RE.finditer(text):
        name = match.group(1)
        if name not in owners:
            owners.append(name)
    return owners


def file_brief_text(repo_dir: Path, source_rel: str, *, timeout: float = MISC_TIMEOUT) -> str:
    try:
        proc = subprocess.run(
            ["python3", "tools/file_brief.py", source_rel],
            cwd=repo_dir, capture_output=True, text=True, timeout=timeout,
        )
        return proc.stdout
    except (subprocess.TimeoutExpired, OSError) as exc:
        return f"(file_brief.py unavailable: {exc})"


def owner_asm_text(repo_dir: Path, function: str, *, timeout: float = MISC_TIMEOUT) -> str:
    try:
        proc = subprocess.run(
            ["python3", "tools/pragma_targets.py", "asm", function],
            cwd=repo_dir, capture_output=True, text=True, timeout=timeout,
        )
        if proc.returncode == 0:
            return proc.stdout
        return f"(pragma_targets.py asm failed: {proc.stderr.strip()[:500]})"
    except (subprocess.TimeoutExpired, OSError) as exc:
        return f"(pragma_targets.py asm unavailable: {exc})"


# ---------------------------------------------------------------------------
# Prompt construction
# ---------------------------------------------------------------------------

BATCH_CONTRACT = """\
Write a JSON batch file to the path given below (create or overwrite it).
Schema:

{{
  "source": "{source_rel}",
  "declarations": "extern ...;\\n...",   // optional: shared externs/prototypes
  "companion_edits": [                    // optional
    {{"function": "func_...", "old": "exact old text", "new": "new text"}}
  ],
  "candidates": [
    {{"function": "{owner}", "label": "family:shape:hypothesis",
     "body": "<COMPLETE function definition: return type, name, parameter list and braces>"}}
  ]
}}

Rules:
- "body" is the whole function definition that replaces the #pragma line,
  e.g. "f64 {owner}(void *arg0, void *arg1) {{ ... }}" on one or more lines. A bare brace
  block with no signature is a compile failure, not a candidate.
- Every candidate's "function" must be exactly "{owner}".
- Provide between 8 and 16 candidates; each candidate tests exactly ONE
  hypothesis (declaration order, temp widths, index-vs-pointer form,
  guard-return vs assign-then-return, explicit temporaries, old-style callee
  prototypes, ...).
- Give every candidate a distinct, descriptive "label"
  ("<family>:<shape>:<hypothesis>").
- Do not add or remove any "#pragma GLOBAL_ASM" line.
- A companion_edit may only retarget an existing C definition/prototype
  already in the file (or the candidate owner's own stale extern); it must
  not target another still-pragma owner.
- Write ONLY that JSON object (no commentary) to: {batch_path}
"""


def build_prompt(
    *,
    owner: str,
    source_rel: str,
    file_brief: str,
    asm_text: str,
    best_candidates: list[dict],
    permuter_seed: dict | None,
    batch_path: Path,
) -> str:
    parts = [
        f"You are generating candidate C function bodies for one GLOBAL_ASM",
        f"owner, {owner}, in {source_rel}. Read the file brief and the target",
        "assembly below, then write a batch of candidate bodies to the path",
        "given at the end of this prompt.",
        "",
        "== file brief ==",
        file_brief.strip(),
        "",
        f"== target assembly: {owner} ==",
        asm_text.strip(),
    ]
    if best_candidates:
        parts.append("")
        parts.append(
            "== best candidates tried so far this run (highest similarity first; "
            "do not resend these bodies verbatim, but use their diagnostics) =="
        )
        for entry in best_candidates:
            parts.append(
                f"-- label={entry.get('label')} similarity={entry.get('similarity_score')} "
                f"raw={entry.get('raw_similarity_score')} mismatch={entry.get('mismatch_kind')} "
                f"futility={entry.get('futility')}"
            )
            diagnostic = entry.get("diagnostic")
            if diagnostic:
                parts.append(f"   diagnostic: {diagnostic}")
            if entry.get("normalized_only"):
                parts.append(
                    "   NORMALIZED-ONLY MATCH: the shape is right but "
                    f"immediates/registers/fields differ (raw={entry.get('raw_similarity_score')}); "
                    "vary constants, field offsets and operand order, not structure."
                )
            body = entry.get("body")
            if body:
                parts.append("   body:")
                parts.append(body)
        parts.append("")
        parts.append(
            "Change the hypothesis family for any candidate whose diagnostic "
            "repeats one shown above instead of resending the same source shape."
        )
    if permuter_seed:
        parts.append("")
        parts.append(
            "== decomp-permuter output (score="
            f"{permuter_seed.get('score')}; 0 means an instruction-exact match -- "
            "submit it close to verbatim as one candidate) =="
        )
        parts.append(permuter_seed.get("body") or "")
    parts.append("")
    parts.append(BATCH_CONTRACT.format(source_rel=source_rel, owner=owner, batch_path=batch_path))
    return "\n".join(parts)


# ---------------------------------------------------------------------------
# Generator invocation
# ---------------------------------------------------------------------------

def render_generator_command(template: str, prompt_path: Path, batch_path: Path) -> str:
    return template.replace("{prompt}", shlex.quote(str(prompt_path))).replace(
        "{batch}", shlex.quote(str(batch_path))
    )


def invoke_generator(command: str, *, cwd: Path, timeout: float) -> subprocess.CompletedProcess:
    """Run the external generator command once. Isolated so tests can stub it."""
    return subprocess.run(
        command, shell=True, cwd=cwd, capture_output=True, text=True, timeout=timeout,
    )


# ---------------------------------------------------------------------------
# Generator health tracking (quota / rate-limit exhaustion)
# ---------------------------------------------------------------------------

# Whole-phrase, case-insensitive signatures. "429" only matches as a
# standalone token (\b429\b) so reasoning text mentioning an offset like
# "0x429" does not trip it.
QUOTA_SIGNATURES = (
    r"\brate[ -]limit\b",
    r"\bquota\b",
    r"\busage limit\b",
    r"\btoo many requests\b",
    r"\b429\b",
)
_QUOTA_RE = re.compile("|".join(f"(?:{sig})" for sig in QUOTA_SIGNATURES), re.IGNORECASE)


def _decode(text: object) -> str:
    if text is None:
        return ""
    if isinstance(text, bytes):
        return text.decode("utf-8", errors="replace")
    return str(text)


def _looks_like_quota(*texts: object) -> bool:
    combined = " ".join(_decode(t) for t in texts)
    return bool(_QUOTA_RE.search(combined))


def _record_generator_outcome(
    gen_failures: dict,
    *,
    ok: bool,
    quota: bool,
    stderr_tail: str,
    owner: str,
    iteration: int,
    max_failures: int,
    logger: Logger,
) -> bool:
    """Update the run's consecutive-generator-failure counter.

    A successful iteration (generator exited zero AND produced a valid batch)
    resets the counter to zero. Otherwise the counter is incremented by 2 when
    the failure looks like a quota/rate-limit signature, else by 1. Returns
    True once ``max_failures`` is reached, meaning the whole run should stop.
    """
    if ok:
        gen_failures["consecutive"] = 0
        return False

    if quota:
        logger.log(f"{owner}: iter {iteration}: generator output looks like a quota/rate-limit signal")

    increment = 2 if quota else 1
    gen_failures["consecutive"] = gen_failures.get("consecutive", 0) + increment

    tail = stderr_tail.strip()
    if tail:
        logger.log(f"{owner}: iter {iteration}: generator stderr tail: {tail[-500:]}")

    logger.log(
        f"{owner}: iter {iteration}: generator failure count now "
        f"{gen_failures['consecutive']} (limit {max_failures})"
    )
    return max_failures > 0 and gen_failures["consecutive"] >= max_failures


# ---------------------------------------------------------------------------
# Probe invocation
# ---------------------------------------------------------------------------

def invoke_probe(
    repo_dir: Path, batch_path: Path, result_path: Path, *, timeout: float
) -> subprocess.CompletedProcess:
    """Run ``tools/fleet_probe.py`` once. Isolated so tests can stub it."""
    return subprocess.run(
        ["python3", "tools/fleet_probe.py", str(batch_path), "--json", str(result_path)],
        cwd=repo_dir, capture_output=True, text=True, timeout=timeout,
    )


# ---------------------------------------------------------------------------
# Permuter invocation and polling
# ---------------------------------------------------------------------------

def _permuter_work_root(repo_dir: Path) -> Path:
    return repo_dir / "disasm" / "build" / "permuter"


def _snapshot_permuter_dirs(repo_dir: Path, function: str) -> set[str]:
    root = _permuter_work_root(repo_dir)
    if not root.is_dir():
        return set()
    prefix = function + "-"
    return {entry.name for entry in root.iterdir() if entry.is_dir() and entry.name.startswith(prefix)}


def invoke_permuter(
    repo_dir: Path,
    function: str,
    candidate_path: Path,
    declarations_path: Path | None,
    *,
    seconds: float,
    log_path: Path,
) -> subprocess.Popen:
    """Launch ``tools/permute_candidate.py`` in the background.

    Isolated so tests can stub it. The caller must poll (``poll_permuter``)
    rather than block on this process: it keeps its own work directory under
    ``disasm/build/permuter/<function>-<suffix>/`` (``--keep``), which is
    what a poller inspects.
    """
    command = [
        "python3", "tools/permute_candidate.py", function, str(candidate_path),
        "--seconds", str(seconds), "--keep",
    ]
    if declarations_path is not None:
        command += ["--declarations", str(declarations_path)]
    log_path.parent.mkdir(parents=True, exist_ok=True)
    log_handle = log_path.open("w", encoding="utf-8")
    try:
        return subprocess.Popen(
            command, cwd=repo_dir, stdout=log_handle, stderr=subprocess.STDOUT,
            text=True, start_new_session=True,
        )
    finally:
        log_handle.close()


def _terminate_process_group(process: subprocess.Popen, *, grace: float = 5.0) -> None:
    try:
        os.killpg(process.pid, signal.SIGTERM)
    except (ProcessLookupError, PermissionError, OSError):
        return
    try:
        process.wait(timeout=grace)
        return
    except subprocess.TimeoutExpired:
        pass
    try:
        os.killpg(process.pid, signal.SIGKILL)
    except (ProcessLookupError, PermissionError, OSError):
        pass
    try:
        process.wait(timeout=grace)
    except subprocess.TimeoutExpired:
        process.kill()
        try:
            process.wait(timeout=grace)
        except subprocess.TimeoutExpired:
            pass


def _extract_function_body(code: str, function: str) -> str:
    """Return only ``function``'s definition from a permuter output file."""
    header = re.compile(rf"^[^\n;{{}}]*\b{re.escape(function)}\s*\([^;]*?\)\s*\{{", re.M | re.S)
    match = header.search(code)
    if match is None:
        return code
    depth = 0
    index = match.end() - 1
    while index < len(code):
        if code[index] == "{":
            depth += 1
        elif code[index] == "}":
            depth -= 1
            if depth == 0:
                return code[match.start(): index + 1].strip() + "\n"
        index += 1
    return code


def _collect_permuter_outputs(work_dir: Path, function: str) -> list[dict]:
    outputs: list[dict] = []
    try:
        entries = list(work_dir.iterdir())
    except OSError:
        return outputs
    for entry in entries:
        match = OUTPUT_DIR_RE.match(entry.name)
        if not match or not entry.is_dir():
            continue
        source = entry / "source.c"
        if not source.exists():
            continue
        try:
            text = source.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        outputs.append({"score": int(match.group(1)), "code": _extract_function_body(text, function)})
    outputs.sort(key=lambda item: (item["score"], len(item["code"])))
    return outputs


def poll_permuter(
    repo_dir: Path,
    function: str,
    process: subprocess.Popen,
    before_dirs: set[str],
    *,
    budget_seconds: float,
    poll_interval: float = 5.0,
) -> dict:
    """Poll the permuter's kept output directory; never block on the process.

    Checks every ``poll_interval`` seconds for a new
    ``disasm/build/permuter/<function>-<suffix>/`` directory and, once found,
    what it contains, until the process exits or ``budget_seconds`` elapses
    -- whichever comes first. If the budget elapses first, the process (and
    its whole process group) is terminated.
    """
    work_root = _permuter_work_root(repo_dir)
    deadline = time.monotonic() + budget_seconds
    work_dir: Path | None = None
    while True:
        if work_dir is None:
            new = sorted(_snapshot_permuter_dirs(repo_dir, function) - before_dirs)
            if new:
                work_dir = work_root / new[0]
        if process.poll() is not None or time.monotonic() >= deadline:
            break
        time.sleep(poll_interval)

    timed_out = process.poll() is None
    if timed_out:
        _terminate_process_group(process)

    if work_dir is None:
        new = sorted(_snapshot_permuter_dirs(repo_dir, function) - before_dirs)
        if new:
            work_dir = work_root / new[0]

    outputs: list[dict] = []
    if work_dir is not None and work_dir.is_dir():
        outputs = _collect_permuter_outputs(work_dir, function)

    return {
        "timed_out": timed_out,
        "work_dir": str(work_dir) if work_dir else None,
        "outputs": outputs,
        "best": outputs[0] if outputs else None,
    }


def run_permuter(
    repo_dir: Path,
    out_dir: Path,
    owner: str,
    iteration: int,
    body: str,
    declarations: str | None,
    *,
    permuter_seconds: float,
    logger: Logger,
) -> dict | None:
    """Write the permuter's input files, launch it, and poll for a result."""
    tmp_dir = out_dir / "tmp" / "permuter"
    tmp_dir.mkdir(parents=True, exist_ok=True)
    candidate_path = tmp_dir / f"{owner}_iter{iteration}_candidate.c"
    candidate_path.write_text(body, encoding="utf-8")
    declarations_path = None
    if declarations:
        declarations_path = tmp_dir / f"{owner}_iter{iteration}_declarations.h"
        declarations_path.write_text(declarations, encoding="utf-8")

    before = _snapshot_permuter_dirs(repo_dir, owner)
    log_path = tmp_dir / f"{owner}_iter{iteration}_permuter.log"
    try:
        process = invoke_permuter(
            repo_dir, owner, candidate_path, declarations_path,
            seconds=permuter_seconds, log_path=log_path,
        )
    except OSError as exc:
        logger.log(f"{owner}: permuter launch failed: {exc}")
        return None

    result = poll_permuter(repo_dir, owner, process, before, budget_seconds=permuter_seconds + 30.0)
    logger.log(
        f"{owner}: permuter iter {iteration} finished timed_out={result['timed_out']} "
        f"outputs={len(result['outputs'])} best_score={(result['best'] or {}).get('score')}"
    )
    return result


# ---------------------------------------------------------------------------
# Acceptance capture
# ---------------------------------------------------------------------------

def extract_installed_function(source_text: str, function: str) -> str | None:
    header = re.compile(rf"^[^\n;{{}}]*\b{re.escape(function)}\s*\([^;{{}}]*\)\s*\{{", re.M)
    match = header.search(source_text)
    if match is None:
        return None
    depth = 0
    index = match.end() - 1
    while index < len(source_text):
        if source_text[index] == "{":
            depth += 1
        elif source_text[index] == "}":
            depth -= 1
            if depth == 0:
                return source_text[match.start(): index + 1].strip() + "\n"
        index += 1
    return None


def capture_accepted(
    repo_dir: Path,
    out_dir: Path,
    owner: str,
    function: str,
    batch: dict,
    accepted_attempt: dict,
    *,
    source_rel_fallback: str,
    logger: Logger,
) -> None:
    source_rel = batch.get("source") or source_rel_fallback
    source_path = repo_dir / source_rel
    try:
        source_text = source_path.read_text(encoding="utf-8", errors="replace")
    except OSError as exc:
        logger.log(f"{owner}: WARNING could not read {source_rel} after acceptance: {exc}")
        source_text = ""
    body = extract_installed_function(source_text, function) if source_text else None
    if body is None:
        logger.log(f"{owner}: WARNING could not extract installed body for {function} from {source_rel}")
        body = ""

    accepted_batch = {
        "source": source_rel,
        "declarations": batch.get("declarations") or "",
        "companion_edits": batch.get("companion_edits") or [],
        "candidates": [{
            "function": function,
            "label": accepted_attempt.get("label") or "accepted",
            "body": body,
        }],
    }
    accepted_dir = out_dir / "accepted"
    save_json(accepted_dir / f"{function}.json", accepted_batch)

    try:
        diff = subprocess.run(
            ["git", "diff", "--", source_rel],
            cwd=repo_dir, capture_output=True, text=True, timeout=30.0,
        )
        (accepted_dir / f"{function}.patch").write_text(diff.stdout, encoding="utf-8")
    except (subprocess.TimeoutExpired, OSError) as exc:
        logger.log(f"{owner}: WARNING git diff for {function} failed: {exc}")


# ---------------------------------------------------------------------------
# One iteration: run the probe on a batch, record state, react to the result
# ---------------------------------------------------------------------------

def run_iteration(
    *,
    repo_dir: Path,
    out_dir: Path,
    source_rel: str,
    owner: str,
    iteration: int,
    batch: dict,
    batch_path: Path,
    owner_state: dict,
    deadline: float,
    permuter_seconds: float,
    logger: Logger,
) -> str:
    """Probe one batch and update ``owner_state`` in place.

    Returns one of ``"accepted"``, ``"continue"``, ``"budget_expired"``.
    """
    result_path = out_dir / "results" / f"{owner}_iter{iteration}.json"
    result_path.parent.mkdir(parents=True, exist_ok=True)

    remaining_budget = max(1.0, deadline - time.monotonic())
    probe_timeout = max(10.0, min(PROBE_TIMEOUT_CAP, remaining_budget))
    try:
        probe_proc = invoke_probe(repo_dir, batch_path, result_path, timeout=probe_timeout)
    except subprocess.TimeoutExpired:
        logger.log(f"{owner}: iter {iteration}: probe timed out after {probe_timeout:.0f}s")
        owner_state["plateau_count"] += 1
        return "continue"
    except OSError as exc:
        logger.log(f"{owner}: iter {iteration}: probe failed to launch: {exc}")
        owner_state["plateau_count"] += 1
        return "continue"

    result = load_json(result_path)
    if result is None:
        logger.log(
            f"{owner}: iter {iteration}: probe produced no result JSON "
            f"(exit={probe_proc.returncode}): {probe_proc.stderr.strip()[:500]}"
        )
        owner_state["plateau_count"] += 1
        return "continue"

    attempts = result.get("attempts") or []
    scored = [a for a in attempts if isinstance(a.get("similarity_score"), (int, float))]
    iteration_best = max(scored, key=attempt_rank) if scored else None

    owner_state["history"].append({
        "iteration": iteration,
        "timestamp": now_iso(),
        "batch_status": result.get("batch_status"),
        "accepted": result.get("accepted") or [],
        "attempts": [
            {
                "label": a.get("label"),
                "function": a.get("function"),
                "status": a.get("status"),
                "similarity_score": a.get("similarity_score"),
                "raw_similarity_score": a.get("raw_similarity_score"),
                "mismatch_kind": a.get("mismatch_kind"),
                "futility": a.get("futility"),
                "link_verified": a.get("link_verified"),
                "diagnostic": ((a.get("diagnostic") or "")[:500]) or None,
            }
            for a in attempts
        ],
    })
    logger.log(
        f"{owner}: iter {iteration}: {len(attempts)} attempt(s) "
        f"best_similarity={iteration_best.get('similarity_score') if iteration_best else None} "
        f"accepted={result.get('accepted')}"
    )

    accepted_functions = result.get("accepted") or []
    if accepted_functions:
        for function in accepted_functions:
            accepted_attempt = next(
                (a for a in attempts if a.get("function") == function and a.get("status") == "accepted"),
                {},
            )
            capture_accepted(
                repo_dir, out_dir, owner, function, batch, accepted_attempt,
                source_rel_fallback=source_rel, logger=logger,
            )
        owner_state["best_similarity"] = 1.0
        owner_state["best_effective_similarity"] = 1.0
        owner_state["best_raw_similarity"] = 1.0
        owner_state["plateau_count"] = 0
        logger.log(f"{owner}: ACCEPTED ({', '.join(accepted_functions)})")
        return "accepted"

    # Keep a small pool of the best-scoring bodies/diagnostics for the next prompt.
    candidate_bodies = {c.get("label"): c.get("body") for c in batch.get("candidates", [])}
    for attempt in scored:
        label = attempt.get("label")
        body = candidate_bodies.get(label)
        if body is None:
            continue
        owner_state["best_candidates"].append({
            "label": label,
            "similarity_score": attempt.get("similarity_score"),
            "raw_similarity_score": attempt.get("raw_similarity_score"),
            "mismatch_kind": attempt.get("mismatch_kind"),
            "futility": attempt.get("futility"),
            "diagnostic": ((attempt.get("diagnostic") or "")[:500]) or None,
            "body": body,
            "normalized_only": _is_normalized_only_match(attempt),
        })
    owner_state["best_candidates"].sort(key=attempt_rank, reverse=True)
    seen_labels: set[str] = set()
    deduped: list[dict] = []
    for entry in owner_state["best_candidates"]:
        if entry["label"] in seen_labels:
            continue
        seen_labels.add(entry["label"])
        deduped.append(entry)
    owner_state["best_candidates"] = deduped[:BEST_CANDIDATES_KEPT]

    previous_effective = owner_state.get("best_effective_similarity") or 0.0
    previous_raw = owner_state.get("best_raw_similarity") or 0.0
    current_effective, current_raw = attempt_rank(iteration_best) if iteration_best else (0.0, 0.0)
    # A normalized-only match never advances "best" tracking -- not even to
    # its own capped effective value -- so a later genuine near-miss is
    # always free to register as an improvement over whatever came before it.
    is_improvement = (
        iteration_best is not None
        and not _is_normalized_only_match(iteration_best)
        and (
            current_effective > previous_effective + 1e-9
            or (
                abs(current_effective - previous_effective) <= 1e-9
                and current_raw > previous_raw + 1e-9
            )
        )
    )
    if is_improvement:
        owner_state["best_effective_similarity"] = current_effective
        owner_state["best_similarity"] = iteration_best.get("similarity_score") or 0.0
        owner_state["best_raw_similarity"] = iteration_best.get("raw_similarity_score")
        owner_state["best_label"] = iteration_best.get("label")
        owner_state["plateau_count"] = 0
    else:
        owner_state["plateau_count"] = owner_state.get("plateau_count", 0) + 1

    # A strong near-miss or a runner-reported register tie is worth a permuter pass.
    # A normalized-only match never triggers it, no matter how close its
    # capped effective similarity gets to the threshold.
    if iteration_best is not None and permuter_seconds > 0 and time.monotonic() < deadline:
        futility = str(iteration_best.get("futility") or "")
        is_register_tie = futility.startswith("register-tie")
        effective_similarity, _ = attempt_rank(iteration_best)
        is_normalized_only = _is_normalized_only_match(iteration_best)
        if not is_normalized_only and (effective_similarity >= 0.95 or is_register_tie):
            label = iteration_best.get("label")
            body = candidate_bodies.get(label)
            if body:
                budget = min(permuter_seconds, max(0.0, deadline - time.monotonic()))
                if budget >= 10.0:
                    permuter_result = run_permuter(
                        repo_dir, out_dir, owner, iteration, body, batch.get("declarations"),
                        permuter_seconds=budget, logger=logger,
                    )
                    if permuter_result is not None:
                        owner_state["permuter_runs"].append({
                            "iteration": iteration,
                            "label": label,
                            "similarity_score": iteration_best.get("similarity_score") or 0.0,
                            "effective_similarity": effective_similarity,
                            "is_register_tie": is_register_tie,
                            "timed_out": permuter_result.get("timed_out"),
                            "best_score": (permuter_result.get("best") or {}).get("score"),
                        })
                        best_output = permuter_result.get("best")
                        if best_output is not None:
                            owner_state["permuter_seed"] = {
                                "score": best_output.get("score"),
                                "body": best_output.get("code"),
                                "iteration": iteration,
                            }

    if time.monotonic() >= deadline:
        return "budget_expired"
    return "continue"


# ---------------------------------------------------------------------------
# Per-owner loop: generate -> probe -> react, until a terminal state
# ---------------------------------------------------------------------------

def process_owner(
    *,
    repo_dir: Path,
    out_dir: Path,
    source_rel: str,
    owner: str,
    owner_state: dict,
    state: dict,
    state_path: Path,
    deadline: float,
    max_iterations: int,
    plateau: int,
    permuter_seconds: float,
    generator_cmd: str,
    logger: Logger,
    gen_failures: dict | None = None,
    max_generator_failures: int = 3,
    generator_timeout: float = DEFAULT_GENERATOR_TIMEOUT,
) -> str:
    if gen_failures is None:
        gen_failures = {"consecutive": 0}
    file_brief = file_brief_text(repo_dir, source_rel)
    asm_text = owner_asm_text(repo_dir, owner)

    while owner_state["iterations"] < max_iterations:
        if time.monotonic() >= deadline:
            owner_state["status"] = "budget_expired"
            return "budget_expired"

        iteration = owner_state["iterations"]
        batch_path = out_dir / "batches" / f"{owner}_iter{iteration}.json"
        prompt_path = out_dir / "prompts" / f"{owner}_iter{iteration}.txt"
        batch_path.parent.mkdir(parents=True, exist_ok=True)
        prompt_path.parent.mkdir(parents=True, exist_ok=True)

        prompt_text = build_prompt(
            owner=owner, source_rel=source_rel, file_brief=file_brief, asm_text=asm_text,
            best_candidates=owner_state["best_candidates"],
            permuter_seed=owner_state.get("permuter_seed"), batch_path=batch_path,
        )
        prompt_path.write_text(prompt_text, encoding="utf-8")

        remaining_budget = max(1.0, deadline - time.monotonic())
        gen_timeout = max(10.0, min(generator_timeout, remaining_budget))
        command = render_generator_command(generator_cmd, prompt_path, batch_path)
        timed_out = False
        timeout_stderr = ""
        try:
            gen_result = invoke_generator(command, cwd=repo_dir, timeout=gen_timeout)
        except subprocess.TimeoutExpired as exc:
            logger.log(f"{owner}: iter {iteration}: generator timed out after {gen_timeout:.0f}s")
            gen_result = None
            timed_out = True
            timeout_stderr = _decode(getattr(exc, "stderr", None))
        except OSError as exc:
            logger.log(f"{owner}: iter {iteration}: generator failed to launch: {exc}")
            owner_state["status"] = "generator_failed"
            # A launch failure never produced a real exit code, so quota
            # classification (which only applies to a non-zero exit) does
            # not apply here.
            exhausted = _record_generator_outcome(
                gen_failures, ok=False, quota=False, stderr_tail=str(exc),
                owner=owner, iteration=iteration, max_failures=max_generator_failures, logger=logger,
            )
            if exhausted:
                logger.log(
                    f"{owner}: generator exhausted after {gen_failures['consecutive']} consecutive "
                    f"failure(s) (limit {max_generator_failures}); stopping run"
                )
                owner_state["status"] = "generator_failed"
                return "generator_exhausted"
            return "generator_failed"

        if gen_result is not None and gen_result.returncode != 0:
            logger.log(
                f"{owner}: iter {iteration}: generator exited {gen_result.returncode}: "
                f"{(gen_result.stderr or '').strip()[:500]}"
            )

        batch = load_json(batch_path)
        gen_ok = (not timed_out) and gen_result is not None and gen_result.returncode == 0 and batch is not None
        if not gen_ok:
            if batch is None:
                logger.log(f"{owner}: iter {iteration}: no valid batch JSON at {batch_path}")
            # Quota/rate-limit classification only applies to a generator
            # that actually exited non-zero, and only inspects stderr: a
            # timeout's captured output is the model's own (possibly
            # truncated) reasoning text, and an exit-0-but-no-batch failure
            # has no non-zero exit to attribute to a quota signal at all.
            # Either case matching a quota phrase by accident must not
            # double-count a plain timeout or missing-batch failure.
            if timed_out:
                quota = False
                stderr_tail = timeout_stderr
            elif gen_result is not None and gen_result.returncode != 0:
                stderr_text = gen_result.stderr or ""
                quota = _looks_like_quota(stderr_text)
                stderr_tail = stderr_text
            else:
                quota = False
                stderr_tail = (gen_result.stderr or "") if gen_result is not None else ""
            exhausted = _record_generator_outcome(
                gen_failures, ok=False, quota=quota, stderr_tail=stderr_tail,
                owner=owner, iteration=iteration, max_failures=max_generator_failures, logger=logger,
            )
            owner_state["iterations"] += 1
            owner_state["plateau_count"] += 1
            save_json(state_path, state)
            if exhausted:
                logger.log(
                    f"{owner}: generator exhausted after {gen_failures['consecutive']} consecutive "
                    f"failure(s) (limit {max_generator_failures}); stopping run"
                )
                owner_state["status"] = "generator_failed"
                return "generator_exhausted"
            if owner_state["plateau_count"] >= plateau:
                owner_state["status"] = "plateau"
                return "plateau"
            continue

        _record_generator_outcome(
            gen_failures, ok=True, quota=False, stderr_tail="",
            owner=owner, iteration=iteration, max_failures=max_generator_failures, logger=logger,
        )

        status = run_iteration(
            repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
            iteration=iteration, batch=batch, batch_path=batch_path, owner_state=owner_state,
            deadline=deadline, permuter_seconds=permuter_seconds, logger=logger,
        )
        owner_state["iterations"] += 1
        save_json(state_path, state)

        if status == "accepted":
            owner_state["status"] = "accepted"
            return "accepted"
        if status == "budget_expired":
            owner_state["status"] = "budget_expired"
            return "budget_expired"
        if owner_state["plateau_count"] >= plateau:
            owner_state["status"] = "plateau"
            return "plateau"

    owner_state["status"] = "max_iterations"
    return "max_iterations"


# ---------------------------------------------------------------------------
# Test mode: exercise the loop once with a fixed batch, no generator
# ---------------------------------------------------------------------------

def run_test_mode(
    *,
    repo_dir: Path,
    out_dir: Path,
    source_rel: str,
    candidate_file: Path,
    state: dict,
    state_path: Path,
    summary: dict,
    started: float,
    logger: Logger,
) -> int:
    batch = load_json(candidate_file)
    if batch is None:
        logger.log(f"error: could not read candidate file {candidate_file}")
        _finalize_run(summary, out_dir, "invalid_candidate_file", started)
        return 2

    functions = []
    for candidate in batch.get("candidates", []):
        function = candidate.get("function")
        if function and function not in functions:
            functions.append(function)
    owner = functions[0] if functions else None
    if owner is None:
        logger.log(f"error: {candidate_file} has no candidates with a function name")
        _finalize_run(summary, out_dir, "invalid_candidate_file", started)
        return 2

    batch_source = batch.get("source") or source_rel
    logger.log(f"test mode: using {candidate_file} for owner {owner} (source={batch_source})")
    summary["owners_attempted"].append(owner)
    owner_state = state.setdefault(owner, _new_owner_state())

    batch_path = out_dir / "batches" / f"{owner}_iter0.json"
    save_json(batch_path, batch)

    status = run_iteration(
        repo_dir=repo_dir, out_dir=out_dir, source_rel=batch_source, owner=owner, iteration=0,
        batch=batch, batch_path=batch_path, owner_state=owner_state,
        deadline=time.monotonic() + 3600.0, permuter_seconds=0.0, logger=logger,
    )
    owner_state["iterations"] = 1
    owner_state["status"] = "accepted" if status == "accepted" else "test_mode_done"
    save_json(state_path, state)

    summary["iteration_counts"][owner] = owner_state["iterations"]
    summary["best_per_owner"][owner] = owner_state["best_similarity"]
    if status == "accepted":
        summary["matched"].append(owner)
    _finalize_run(summary, out_dir, "test_mode_exit", started)
    logger.log(f"test mode complete: status={status}")
    return 0


# ---------------------------------------------------------------------------
# CLI / main loop
# ---------------------------------------------------------------------------

def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--source", required=True, help="repo-relative source path, e.g. disasm/src/X.c")
    parser.add_argument("--out", required=True, type=Path, help="output directory for state/logs/accepted candidates")
    parser.add_argument("--repo", type=Path, default=REPO_ROOT_DEFAULT, help="repo root (default: parent of tools/)")
    parser.add_argument("--budget-seconds", type=float, default=7200.0)
    parser.add_argument("--max-iterations", type=int, default=200)
    parser.add_argument(
        "--plateau", type=int, default=6,
        help="stop an owner after N consecutive iterations with no best-similarity improvement",
    )
    parser.add_argument("--permuter-seconds", type=float, default=300.0)
    parser.add_argument("--owners", help="comma-separated subset/order of owners to work (default: all, discovered)")
    parser.add_argument(
        "--generator-cmd",
        help='shell command template; "{prompt}" and "{batch}" are substituted with absolute paths',
    )
    parser.add_argument(
        "--candidate-file", type=Path,
        help="test mode: use this batch once for the first owner instead of any generator, then exit",
    )
    parser.add_argument(
        "--generator-timeout", type=float, default=DEFAULT_GENERATOR_TIMEOUT,
        help=(
            "cap in seconds on a single generator invocation; the run's remaining "
            "budget still bounds it further (default: 600). Kimi K3 at high effort "
            "can exceed 10 minutes for one batch -- raise this rather than letting "
            "it time out."
        ),
    )
    parser.add_argument(
        "--max-generator-failures", type=int, default=3,
        help=(
            "stop the whole run after this many consecutive generator failures "
            "(non-zero exit, timeout, or no valid batch JSON); a quota/rate-limit-looking "
            "failure counts double (default: 3)"
        ),
    )
    parser.add_argument(
        "--resume", action="store_true",
        help="resume an existing run in --out (its state.json); without this, a non-empty state.json is an error",
    )
    parser.add_argument(
        "--skip-status", default="accepted",
        help="comma-separated owner statuses to skip when resuming (default: accepted)",
    )
    return parser.parse_args(argv)


def _resolve_source_rel(repo_dir: Path, source: str) -> str:
    path = Path(source)
    if path.is_absolute():
        try:
            return path.resolve().relative_to(repo_dir).as_posix()
        except ValueError:
            return source
    return source


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    repo_dir = args.repo.resolve()
    out_dir = args.out
    out_dir.mkdir(parents=True, exist_ok=True)
    logger = Logger(out_dir / "log.txt")

    source_rel = _resolve_source_rel(repo_dir, args.source)
    started = time.monotonic()
    deadline = started + args.budget_seconds

    state_path = out_dir / "state.json"
    summary_path = out_dir / "summary.json"
    existing_state = load_json(state_path)
    if existing_state:
        if not args.resume:
            logger.log(
                f"error: {state_path} already has a run; pass --resume or use a new --out dir"
            )
            return 2
        state = existing_state
    else:
        state = {}

    prior_summary = load_json(summary_path) if args.resume else None
    runs: list[dict] = list((prior_summary or {}).get("runs") or [])
    generator_desc = args.generator_cmd or (
        f"--candidate-file {args.candidate_file}" if args.candidate_file else None
    )
    runs.append({"started": now_iso(), "ended": None, "generator_cmd": generator_desc, "stop_reason": None})

    summary: dict = {
        "source": source_rel,
        "started_at": now_iso(),
        "budget_seconds": args.budget_seconds,
        "owners_attempted": [],
        "matched": [],
        "best_per_owner": {},
        "iteration_counts": {},
        "stopped_reason": None,
        "runs": runs,
    }

    if args.candidate_file:
        return run_test_mode(
            repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel,
            candidate_file=args.candidate_file, state=state, state_path=state_path,
            summary=summary, started=started, logger=logger,
        )

    if not args.generator_cmd:
        logger.log("error: --generator-cmd is required (or use --candidate-file for a one-shot test)")
        _finalize_run(summary, out_dir, "no_generator", started)
        return 2

    if args.owners:
        owners = [name.strip() for name in args.owners.split(",") if name.strip()]
    else:
        owners = discover_owners(repo_dir, source_rel)

    logger.log(f"discovered {len(owners)} owner(s) for {source_rel}: {', '.join(owners) or '(none)'}")

    skip_statuses = {s.strip() for s in (args.skip_status or "").split(",") if s.strip()}
    gen_failures = {"consecutive": 0}

    stopped_reason = "completed" if owners else "no_owners"
    for owner in owners:
        if time.monotonic() >= deadline:
            stopped_reason = "budget_expired"
            break
        owner_state = state.setdefault(owner, _new_owner_state())
        if owner_state.get("status") in skip_statuses:
            logger.log(f"{owner}: resume: skipping (status={owner_state.get('status')})")
            summary["iteration_counts"][owner] = owner_state["iterations"]
            summary["best_per_owner"][owner] = owner_state["best_similarity"]
            if owner_state.get("status") == "accepted":
                summary["matched"].append(owner)
            continue
        summary["owners_attempted"].append(owner)
        status = process_owner(
            repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
            owner_state=owner_state, state=state, state_path=state_path, deadline=deadline,
            max_iterations=args.max_iterations, plateau=args.plateau,
            permuter_seconds=args.permuter_seconds, generator_cmd=args.generator_cmd, logger=logger,
            gen_failures=gen_failures, max_generator_failures=args.max_generator_failures,
            generator_timeout=args.generator_timeout,
        )
        summary["iteration_counts"][owner] = owner_state["iterations"]
        summary["best_per_owner"][owner] = owner_state["best_similarity"]
        if status == "accepted":
            summary["matched"].append(owner)
        save_json(state_path, state)
        if status == "budget_expired":
            stopped_reason = "budget_expired"
            break
        if status == "generator_exhausted":
            stopped_reason = "generator_exhausted"
            break

    _finalize_run(summary, out_dir, stopped_reason, started)
    logger.log(f"done: matched={summary['matched']} stopped_reason={stopped_reason}")
    return 3 if stopped_reason == "generator_exhausted" else 0


if __name__ == "__main__":
    raise SystemExit(main())
