#!/usr/bin/env python3
"""Host-side merge step for the containerised per-file agent (issue #39).

The container (see ``docs/CONTAINER_AGENT.md``) never commits. It writes its
results to a mounted output directory:

    <out>/state.json               owner -> {best_similarity, iterations,
                                              history[], status}
    <out>/accepted/<owner>.json    a fleet_probe batch JSON with a single
                                    accepted candidate plus declarations /
                                    companion_edits
    <out>/accepted/<owner>.patch
    <out>/log.txt
    <out>/summary.json             owners attempted, matched, best per
                                    owner, iteration counts, wall time
    <out>/probe-stats/probe-stats.jsonl
                                    a copy of the probe-stats history the
                                    container's own runner wrote during the
                                    run (see "import-stats" below)

This script is the "separate, deliberate step" the issue asks for: it never
trusts the container's own verdict. For each ``<out>/accepted/<owner>.json``
it re-runs the real oracle -- ``tools/fleet_probe.py <json> --gate`` -- against
*this* checkout, and only a candidate the host itself just gated is eligible
to be committed. A container that ran against a stale or tampered tree cannot
talk its way past this.

``merge`` itself writes back into ``<out>``:

    <out>/merge-results/<owner>.json
                                    the raw fleet_probe --gate --json result
                                    for each owner, kept (not deleted) so a
                                    failed re-gate can be inspected
    <out>/merge-results/<owner>.commit.log
                                    only when a host re-gate accepted but
                                    ``git commit --only`` then failed: the
                                    full combined stdout+stderr of that
                                    failed commit
    <out>/merge-report.json        owner -> status, plus cc_check_bypassed
                                    and fresh_history flags for this run
                                    (an owner whose commit failed maps to
                                    {"status", "committed": false,
                                    "commit_error": <last 15 lines>} instead
                                    of a bare status string; an owner whose
                                    commit succeeded maps to {"status":
                                    "accepted", "committed": true, "commit":
                                    <sha>} -- see "Idempotency" below).
                                    Cumulative across runs against the same
                                    <out>: an owner not touched this run
                                    (skipped via --owners, or simply not
                                    re-processed) keeps whatever entry a
                                    prior run recorded for it.
    <out>/merge-history.jsonl      only with --fresh-history: this run's own
                                    probe-stats history (see --fresh-history
                                    below)

Two more, on by default, each read from ``<out>`` and never cumulative
across runs (unlike ``owners`` above):

* Region notes -- ``<out>/region-notes/<source with "/" replaced by
  "__">.md``, written by the container driver, is folded into this
  checkout's ``docs/regions/<source>.md`` via ``tools/region_notes.py
  append`` (deduped, only new lines), regardless of whether any owner was
  accepted this run. With ``--commit``, a source this run also committed an
  owner for gets its notes folded into that same land commit
  (``git commit --only <source> docs/regions/<source>.md``); a source with
  new notes but no accept this run gets its own commit, "Record container
  run notes for <source>". Disable with ``--no-notes``. Recorded in
  ``merge-report.json`` as ``notes_applied`` (source -> newly appended
  lines).
* Naming on accept -- after an owner is accepted and committed this run,
  its function is offered to ``tools/name_decompiled.py`` (``plan`` then
  ``apply``, the same evidence-backed rename
  ``tools/try_pragma_compare.py``'s ``PRAGMA_NAME_ON_ACCEPT`` applies
  in-container, done here host-side instead); a successful rename gets its
  own commit, "Name <owner> -> <name>", over whichever ``disasm/src`` /
  ``disasm/include`` files ``apply`` touched (found via ``git status
  --porcelain``, since ``apply`` itself reports only counts). Never fatal --
  a failure is only logged. Disable with ``--no-naming``. Recorded in
  ``merge-report.json`` as ``names`` (owner -> new name).

Idempotency: a second ``merge --commit`` run against the same ``<out>``
must never re-gate (and try to re-install/re-commit) an owner that already
landed. Before re-gating, each owner is checked against two signals and
skipped with status "already_landed" (neither accepted nor rejected, and
never committed again) if either one fires:

* its batch's ``source`` file, read from *this* checkout, no longer
  contains that owner's ``#pragma GLOBAL_ASM(".../<owner>.s")`` line (the
  same shape ``tools/container_agent.py``'s ``PRAGMA_RE`` matches) -- i.e.
  the candidate is already installed in the tree; or
* the previous ``merge-report.json`` in ``<out>`` (if any) already marks
  this owner committed -- either the plain ``"accepted"`` string (the form
  a committed owner got before this fix existed, kept for backward
  compatibility) or an object entry with ``"committed": true``.

``--owners a,b,c`` limits a run to only those owners (by
``accepted/<owner>.json`` stem); every other owner's ``accepted/*.json`` is
left untouched and its prior report entry (if any) is carried forward
unchanged.

Two flags work around problems seen on the first real merge (see the
"merge" section of ``docs/CONTAINER_AGENT.md`` for the full story):

* ``--no-cc-check`` sets ``PRAGMA_GATE_CC_CHECK=0`` for the re-gate, so an
  unrelated file failing the host's clang syntax check cannot make every
  re-gate report ``compare_rejected`` regardless of the candidate. Loud by
  design: prints a warning and records ``cc_check_bypassed: true`` in
  ``merge-report.json``.
* ``--fresh-history`` points ``PRAGMA_PROBE_STATS`` at a per-run history
  file so a prior host attempt on record can never trip the runner's own
  "already rejected" preflight. For each owner, as soon as its re-gate
  accepts -- and *before* that owner's own ``git commit --only`` is even
  attempted -- the accepted line(s) are folded into the host's real
  probe-stats history, because ``tools/check_decomp_provenance.py``'s
  pre-commit hook requires an accepted attempt on record in that real
  history and would otherwise refuse the very commit this merge just
  earned (seen on a real merge: the re-gate accepted, but the commit step
  reported "committed 0/1 accepted owner(s)" because the import only ran
  after every owner's commit had already been attempted).

Usage:
    python3 tools/container_merge.py merge /abs/out
    python3 tools/container_merge.py merge /abs/out --commit
    python3 tools/container_merge.py merge /abs/out --repo . --dry-run
    python3 tools/container_merge.py merge /abs/out --commit --no-cc-check --fresh-history
    python3 tools/container_merge.py merge /abs/out --commit --owners func_A,func_B
    python3 tools/container_merge.py merge /abs/out --commit --no-notes --no-naming
    python3 tools/container_merge.py summary /abs/out
    python3 tools/container_merge.py import-stats /abs/out
    python3 tools/container_merge.py import-stats /abs/out --repo . --dry-run
"""

from __future__ import annotations

import argparse
import dataclasses
import json
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

# Environment variables ``.githooks/pre-commit`` exports for its own
# temporary index; inheriting them here would point a subprocess git call at
# the hook's index instead of this checkout's real one (AGENTS.md Sec 1.3,
# and the same stripping tools/integrate_fleet.py does).
_GIT_ENV_POISON = {"GIT_DIR", "GIT_INDEX_FILE", "GIT_WORK_TREE", "GIT_OBJECT_DIRECTORY"}


def _clean_env() -> dict[str, str]:
    return {k: v for k, v in os.environ.items() if k not in _GIT_ENV_POISON}


@dataclasses.dataclass
class MergeRow:
    owner: str
    source: str | None
    function: str
    status: str  # "accepted" | "rejected" | "error"
    detail: str
    committed: bool
    commit_detail: str
    # Last 15 lines of ``git commit --only``'s combined stdout+stderr, set
    # only when a commit was actually attempted and failed -- distinguishes
    # "accepted but never attempted to commit" (dry-run, missing source,
    # commit=False) from "attempted and failed", and is what ``merge`` prints,
    # records in ``merge-report.json``, and mirrors into
    # ``<out>/merge-results/<owner>.commit.log`` in full.
    commit_error_tail: str = ""
    # ``git rev-parse HEAD`` in ``repo_root`` right after a successful
    # ``git commit --only``, set only when that commit succeeded and the
    # hash could be read back. Recorded in ``merge-report.json`` as this
    # owner's ``"commit"`` field.
    commit_sha: str = ""


def load_accepted_batch(path: Path) -> dict[str, object]:
    """Parse one ``accepted/<owner>.json`` fleet_probe batch file."""
    payload = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(payload, dict):
        raise ValueError("top-level JSON value must be an object")
    return payload


def batch_source(payload: dict[str, object]) -> str | None:
    source = payload.get("source")
    return source if isinstance(source, str) and source else None


def owner_function_name(owner: str, payload: dict[str, object]) -> str:
    """The candidate's owning function, falling back to the file stem."""
    candidates = payload.get("candidates")
    if isinstance(candidates, list) and candidates:
        first = candidates[0]
        if isinstance(first, dict):
            function = first.get("function")
            if isinstance(function, str) and function:
                return function
    return owner


def _first_line(text: str) -> str:
    return text.strip().splitlines()[0] if text and text.strip() else ""


def _tail_lines(text: str, count: int) -> str:
    lines = text.strip("\n").splitlines() if text else []
    return "\n".join(lines[-count:])


# ---------------------------------------------------------------------------
# The two invocations that leave this process: kept as small, single-purpose
# functions so tests can stub each one independently rather than mocking
# subprocess.run generically.
# ---------------------------------------------------------------------------


def run_fleet_probe_gate(
    batch_path: Path,
    *,
    repo_root: Path,
    python_bin: str = sys.executable,
    timeout: int = 1800,
    extra_env: dict[str, str] | None = None,
    result_path: Path | None = None,
) -> dict[str, object]:
    """Re-gate one accepted-candidate batch against ``repo_root``.

    Runs ``tools/fleet_probe.py <batch_path> --gate --json <result>`` and
    returns ``{"returncode", "result", "stdout", "stderr"}``, where
    ``result`` is the parsed raw runner payload (``{}`` if the subprocess
    never wrote one, e.g. an argument-parsing failure).

    ``extra_env`` is overlaid on a cleaned copy of the current environment
    (see ``_clean_env``) before the subprocess runs -- ``merge --no-cc-check``
    and ``merge --fresh-history`` use it to set ``PRAGMA_GATE_CC_CHECK`` /
    ``PRAGMA_PROBE_STATS`` for this one gate call without touching this
    process's own environment.

    ``result_path`` names where the runner's ``--json`` output should land.
    When given, that file is written and **kept** (its parent directory is
    created if needed) so a failed re-gate can be inspected afterward --
    used by ``merge`` to write ``<out>/merge-results/<owner>.json``. When
    omitted, a throwaway temp file is used and deleted before returning.
    """
    if result_path is not None:
        result_path.parent.mkdir(parents=True, exist_ok=True)
        managed_result_path = result_path
        cleanup = False
    else:
        handle = tempfile.NamedTemporaryFile(
            prefix="container_merge_", suffix=".json", delete=False
        )
        managed_result_path = Path(handle.name)
        handle.close()
        cleanup = True
    env = _clean_env()
    if extra_env:
        env.update(extra_env)
    try:
        proc = subprocess.run(
            [
                python_bin,
                str(repo_root / "tools" / "fleet_probe.py"),
                str(batch_path),
                "--gate",
                "--json",
                str(managed_result_path),
            ],
            cwd=repo_root,
            capture_output=True,
            text=True,
            timeout=timeout,
            env=env,
        )
        result: dict[str, object] = {}
        if managed_result_path.exists() and managed_result_path.stat().st_size:
            try:
                parsed = json.loads(managed_result_path.read_text(encoding="utf-8"))
            except json.JSONDecodeError:
                parsed = None
            if isinstance(parsed, dict):
                result = parsed
        return {
            "returncode": proc.returncode,
            "result": result,
            "stdout": proc.stdout or "",
            "stderr": proc.stderr or "",
        }
    finally:
        if cleanup:
            managed_result_path.unlink(missing_ok=True)


def git_commit_only_paths(paths: list[str], message: str, *, repo_root: Path) -> tuple[bool, str]:
    """``git commit --only <p1> <p2> ... -m <message>`` in ``repo_root`` --
    the general form of ``git_commit_only`` for more than one explicit path
    (the region-notes commit needs ``<source>`` alongside
    ``docs/regions/<source>.md``; the naming follow-up commit needs every
    ``disasm/src``/``disasm/include`` file ``tools/name_decompiled.py
    apply`` just touched). AGENTS.md Sec 1.3: the git index is shared by
    every process in a checkout, so a plain ``git add && git commit`` would
    also commit whatever another session has staged -- ``--only`` builds a
    temporary index from HEAD plus exactly the named paths and leaves
    everything else untouched.
    """
    proc = subprocess.run(
        ["git", "commit", "--only", *paths, "-m", message],
        cwd=repo_root,
        capture_output=True,
        text=True,
        env=_clean_env(),
    )
    output = ((proc.stdout or "") + (proc.stderr or "")).strip()
    return proc.returncode == 0, output


def git_commit_only(source: str, message: str, *, repo_root: Path) -> tuple[bool, str]:
    """``git commit --only <source> -m <message>`` in ``repo_root`` -- the
    single-path case of ``git_commit_only_paths``, kept as its own function
    since it is ``process_owner``'s own commit seam."""
    return git_commit_only_paths([source], message, repo_root=repo_root)


def git_rev_parse_head(repo_root: Path) -> str | None:
    """``git rev-parse HEAD`` in ``repo_root``, run immediately after a
    successful ``git_commit_only`` to capture the hash of the commit that
    just landed -- the same small, single-purpose subprocess seam as
    ``git_commit_only`` itself, so tests can stub it independently.

    Returns ``None`` (never raises) if the hash can't be read back for any
    reason -- a missing ``git`` binary, a non-repo ``repo_root``, a non-zero
    exit -- so a hash-recording hiccup never blocks the merge or the commit
    that already succeeded.
    """
    try:
        proc = subprocess.run(
            ["git", "rev-parse", "HEAD"],
            cwd=repo_root,
            capture_output=True,
            text=True,
            env=_clean_env(),
        )
    except OSError:
        return None
    if proc.returncode != 0:
        return None
    sha = (proc.stdout or "").strip()
    return sha or None


# ---------------------------------------------------------------------------
# Idempotency: has this owner already landed?
# ---------------------------------------------------------------------------


def owner_pragma_pattern(owner: str) -> re.Pattern[str]:
    """Same shape as ``tools/container_agent.py``'s ``PRAGMA_RE``, pinned to
    one owner: matches ``#pragma GLOBAL_ASM(".../<owner>.s")``."""
    return re.compile(r'#pragma\s+GLOBAL_ASM\("[^"]*/' + re.escape(owner) + r'\.s"\)')


def source_still_has_pragma(repo_root: Path, source: str, owner: str) -> bool:
    """True iff ``<repo_root>/<source>`` still contains the GLOBAL_ASM
    pragma naming ``owner`` -- i.e. this owner's candidate has not yet been
    installed into this checkout. A missing or unreadable source file is
    treated as "no longer has the pragma": the safer read for idempotency,
    since a merge that can't even find the file to check has nothing left
    to re-gate against it.
    """
    path = repo_root / source
    if not path.is_file():
        return False
    try:
        text = path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return False
    return bool(owner_pragma_pattern(owner).search(text))


def load_previous_report_owners(out_dir: Path) -> dict[str, object]:
    """The ``"owners"`` map of a prior ``<out>/merge-report.json`` run, or
    ``{}`` if there isn't one / it isn't parseable -- the baseline
    ``write_merge_report`` builds this run's report on top of (so an owner
    not touched this run keeps its prior entry), and what
    ``previous_entry_marks_committed`` below reads to decide whether an
    owner has already landed.
    """
    path = out_dir / "merge-report.json"
    if not path.is_file():
        return {}
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return {}
    owners = payload.get("owners") if isinstance(payload, dict) else None
    return dict(owners) if isinstance(owners, dict) else {}


def previous_entry_marks_committed(entry: object) -> bool:
    """Does one owner's entry in a prior ``merge-report.json`` mean that
    owner is already committed?

    * the plain ``"accepted"`` string -- before this fix, that was written
      both for "host re-gate accepted, commit succeeded" and (with
      ``--commit`` not passed) "host re-gate accepted, commit never
      attempted"; treating it as already-committed is the conservative
      read for the bug this fixes (a repeat ``--commit`` run against an
      ``<out>`` that already landed everything), and a genuinely
      never-committed owner is still caught independently by
      ``source_still_has_pragma``.
    * this fix's own ``"already_landed"`` string, so a third run over the
      same ``<out>`` stays a no-op too.
    * an object entry with ``"committed": true`` (this fix's own form for a
      successful commit; the pre-existing failed-commit object form always
      has ``committed: false`` and so is naturally excluded here).
    """
    if entry in ("accepted", "already_landed"):
        return True
    if isinstance(entry, dict):
        return bool(entry.get("committed"))
    return False


# ---------------------------------------------------------------------------
# Region notes: fold <out>/region-notes/<source>.md (written by the
# container driver -- see docs/CONTAINER_AGENT.md Sec 9.5) into this
# checkout's docs/regions/<source>.md, the same "never trust the container,
# redo it against this checkout" spirit as the re-gate itself. Applied after
# every merge run, regardless of whether any owner was accepted this run
# (rejected-everything runs can still carry useful notes), unless
# --no-notes.
# ---------------------------------------------------------------------------


@dataclasses.dataclass
class NotesResult:
    source: str
    appended: list[str] = dataclasses.field(default_factory=list)
    committed: bool = False
    commit_detail: str = ""


def region_notes_source_from_filename(path: Path) -> str:
    """Invert the container driver's own ``<out>/region-notes/<source with
    "/" replaced by "__">.md`` naming back to a source path, e.g.
    ``disasm__src__4AC10.c.md`` -> ``disasm/src/4AC10.c``. ``Path.stem``
    strips exactly one (the trailing ``.md``) suffix, so the real source's
    own ``.c`` survives intact.
    """
    return path.stem.replace("__", "/")


def region_notes_lines(path: Path) -> list[str]:
    """Candidate note lines from a driver-written region-notes file: every
    non-blank line that isn't ``tools/region_notes.py``'s own structural
    markdown (the ``# Region notes -- ...`` file header, or a ``##
    <heading>`` section heading -- see its ``append()``/``load()``), so each
    survivor is one atomic note ready to replay through ``region_notes.py
    append --text``. Returns ``[]`` for a missing or unreadable file.
    """
    try:
        text = path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return []
    lines = []
    for raw in text.splitlines():
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        lines.append(line)
    return lines


def region_notes_target_path(repo_root: Path, source: str) -> Path:
    """``docs/regions/<rel>.md`` for ``source``, mirroring
    ``tools/region_notes.py``'s own ``path_for()``/``_relative_source()``:
    ``source`` relative to ``<repo_root>/disasm/src`` when possible, else
    relative to ``repo_root``, else just its filename -- computed against
    the given ``repo_root`` (never ``region_notes.py``'s own hardcoded
    ``REPO_ROOT``), so a test can point this at a throwaway checkout.
    """
    repo_root = repo_root.resolve()
    src_root = repo_root / "disasm" / "src"
    path = Path(source)
    if not path.is_absolute():
        path = repo_root / path
    try:
        resolved = path.resolve()
    except OSError:
        resolved = path
    for root in (src_root, repo_root):
        try:
            rel = resolved.relative_to(root)
            return (repo_root / "docs" / "regions" / rel).with_suffix(".md")
        except ValueError:
            continue
    return (repo_root / "docs" / "regions" / Path(resolved.name)).with_suffix(".md")


def region_notes_target_relpath(repo_root: Path, source: str) -> str:
    """``region_notes_target_path`` as a ``repo_root``-relative POSIX
    string, ready for ``git commit --only``."""
    target = region_notes_target_path(repo_root, source)
    return target.relative_to(repo_root.resolve()).as_posix()


def existing_region_notes_text(repo_root: Path, source: str) -> str:
    """Current ``docs/regions/<source>.md`` content in ``repo_root`` (``""``
    if it doesn't exist yet or can't be read) -- read once per source before
    appending, so a line already on record is never replayed.
    """
    path = region_notes_target_path(repo_root, source)
    if not path.is_file():
        return ""
    try:
        return path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return ""


def run_region_notes_append(
    source: str,
    text: str,
    *,
    repo_root: Path,
    python_bin: str = sys.executable,
    timeout: int = 60,
) -> tuple[bool, str]:
    """``python3 tools/region_notes.py append <source> --text <text>`` in
    ``repo_root`` -- the same small, single-purpose subprocess seam as
    ``git_commit_only``, so tests can stub it independently. Returns ``(ok,
    combined stdout+stderr)``.
    """
    proc = subprocess.run(
        [
            python_bin,
            str(repo_root / "tools" / "region_notes.py"),
            "append",
            source,
            "--text",
            text,
        ],
        cwd=repo_root,
        capture_output=True,
        text=True,
        timeout=timeout,
        env=_clean_env(),
    )
    output = ((proc.stdout or "") + (proc.stderr or "")).strip()
    return proc.returncode == 0, output


def apply_region_notes(
    out_dir: Path,
    *,
    repo_root: Path,
    commit: bool,
    dry_run: bool,
    rows: list[MergeRow] | None = None,
) -> list[NotesResult]:
    """Fold every ``<out>/region-notes/<source>.md`` the container driver
    wrote into this checkout's ``docs/regions/<source>.md`` -- see this
    module's own "Region notes" section above and
    docs/CONTAINER_AGENT.md Sec 9.5. Runs regardless of whether any owner in
    ``rows`` was accepted this run.

    For a ``source`` this run actually committed at least one owner for
    (``rows`` has a ``committed`` entry naming it), the notes file lands
    alongside that same land commit's message (``git commit --only <source>
    docs/regions/<source>.md``, reusing "Land container match for
    <owner>"). Otherwise, if there is at least one new line to record, it
    gets its own commit, ``"Record container run notes for <source>"``,
    with ``--only`` on just the notes file.

    ``dry_run`` never calls ``region_notes.py append`` or commits anything,
    but still reports what would be appended (same convention as
    ``append_history_lines``).
    """
    notes_dir = out_dir / "region-notes"
    if not notes_dir.is_dir():
        return []

    committed_owner_for_source: dict[str, str] = {}
    for row in rows or []:
        if row.committed and row.source and row.source not in committed_owner_for_source:
            committed_owner_for_source[row.source] = row.owner

    results: list[NotesResult] = []
    for path in sorted(p for p in notes_dir.glob("*.md") if p.is_file()):
        source = region_notes_source_from_filename(path)
        lines = region_notes_lines(path)
        if not lines:
            continue

        existing = existing_region_notes_text(repo_root, source)
        appended: list[str] = []
        for line in lines:
            if line in existing or line in appended:
                continue
            if dry_run:
                appended.append(line)
                continue
            ok, output = run_region_notes_append(source, line, repo_root=repo_root)
            if not ok:
                print(
                    f"container_merge: region notes: append failed for {source}: "
                    f"{_first_line(output)}",
                    file=sys.stderr,
                )
                continue
            appended.append(line)

        result = NotesResult(source=source, appended=appended)
        results.append(result)

        if not appended or not commit or dry_run:
            continue

        notes_rel = region_notes_target_relpath(repo_root, source)
        owner = committed_owner_for_source.get(source)
        if owner:
            message = f"Land container match for {owner}"
            ok, output = git_commit_only_paths([source, notes_rel], message, repo_root=repo_root)
        else:
            message = f"Record container run notes for {source}"
            ok, output = git_commit_only_paths([notes_rel], message, repo_root=repo_root)
        result.committed = ok
        result.commit_detail = output if not ok else "committed"
        if not ok:
            print(
                f"container_merge: region notes: commit failed for {source}: "
                f"{_first_line(output)}",
                file=sys.stderr,
            )

    return results


# ---------------------------------------------------------------------------
# Naming on accept: after an owner is accepted and committed, offer its
# function to tools/name_decompiled.py -- the same evidence-backed rename
# tools/try_pragma_compare.py's own PRAGMA_NAME_ON_ACCEPT applies inside the
# container's runner, done here host-side instead, deliberately: plan first
# (does an evidence-backed name exist?), then apply (does it actually land,
# or refuse on a collision?) -- see docs/CONTAINER_AGENT.md Sec 9.6.
# ---------------------------------------------------------------------------

_NAME_PLAN_ROW_RE = re.compile(r"^(\S+)\s+(\S+)\s")
_NAME_APPLY_ROW_RE = re.compile(r"^\s*(\S+)\s+->\s+(\S+)\s*$")

# The hand-written, splat-preserved linker script aliases.ld's own header
# comment describes (repo-relative, POSIX-style, matching git_status_paths'
# own path convention) -- see append_name_alias below.
_ALIASES_LD_PATH = "disasm/linker_scripts/us/aliases.ld"


def run_name_decompiled_plan(
    function: str,
    *,
    repo_root: Path,
    python_bin: str = sys.executable,
    timeout: int = 300,
) -> dict[str, object]:
    """``python3 tools/name_decompiled.py plan --only <function> --repo-root
    <repo_root>`` -- the same small, stubbable subprocess seam as
    ``run_fleet_probe_gate``. Returns ``{"returncode", "stdout", "stderr"}``.
    """
    proc = subprocess.run(
        [
            python_bin,
            str(repo_root / "tools" / "name_decompiled.py"),
            "plan",
            "--only",
            function,
            "--repo-root",
            str(repo_root),
        ],
        cwd=repo_root,
        capture_output=True,
        text=True,
        timeout=timeout,
        env=_clean_env(),
    )
    return {"returncode": proc.returncode, "stdout": proc.stdout or "", "stderr": proc.stderr or ""}


def run_name_decompiled_apply(
    function: str,
    *,
    repo_root: Path,
    python_bin: str = sys.executable,
    timeout: int = 300,
) -> dict[str, object]:
    """``python3 tools/name_decompiled.py apply --only <function>
    --repo-root <repo_root>`` -- actually mutates ``disasm/src`` etc, so it
    is only ever called after ``run_name_decompiled_plan`` has already found
    an evidence-backed name to offer. Same return shape as
    ``run_name_decompiled_plan``.
    """
    proc = subprocess.run(
        [
            python_bin,
            str(repo_root / "tools" / "name_decompiled.py"),
            "apply",
            "--only",
            function,
            "--repo-root",
            str(repo_root),
        ],
        cwd=repo_root,
        capture_output=True,
        text=True,
        timeout=timeout,
        env=_clean_env(),
    )
    return {"returncode": proc.returncode, "stdout": proc.stdout or "", "stderr": proc.stderr or ""}


def parse_planned_name(function: str, stdout: str) -> str | None:
    """Extract the proposed new name for ``function`` from
    ``name_decompiled.py plan``'s table (its ``print_plan``): the header
    row's first column is always the literal string ``"function"``, never a
    real ``func_...`` name, so it never accidentally matches.
    """
    for line in stdout.splitlines():
        m = _NAME_PLAN_ROW_RE.match(line)
        if m and m.group(1) == function:
            return m.group(2)
    return None


def parse_applied_name(function: str, stdout: str) -> str | None:
    """Extract the new name actually applied for ``function`` from
    ``name_decompiled.py apply``'s own output (``"  old -> new"`` lines --
    see its ``main()``). Returns ``None`` if ``function`` was refused (a
    collision) or not applied at all -- a refused line carries a trailing
    ``": <reason>"`` and so never matches this pattern.
    """
    for line in stdout.splitlines():
        m = _NAME_APPLY_ROW_RE.match(line)
        if m and m.group(1) == function:
            return m.group(2)
    return None


def name_after_commit(function: str, *, repo_root: Path) -> tuple[str | None, str]:
    """After ``function``'s owner has been accepted and committed this run,
    offer it to ``tools/name_decompiled.py``: ``plan`` (does it already have
    an evidence-backed name and no other pragma owner?) then, only if so,
    ``apply`` (does it actually land -- no collision?). Never raises: a
    subprocess failure at either step is reported in the returned detail
    string, exactly like ``PRAGMA_NAME_ON_ACCEPT``'s own ``except
    Exception`` in ``tools/try_pragma_compare.py`` -- naming is a bonus, not
    something that can fail the merge run.

    Returns ``(new_name, detail)``; ``new_name`` is ``None`` whenever no
    rename happened (nothing proposed, or apply refused it), and ``detail``
    is always a human-readable reason.
    """
    try:
        plan = run_name_decompiled_plan(function, repo_root=repo_root)
    except (OSError, subprocess.SubprocessError) as exc:
        return None, f"name_decompiled plan failed to run: {exc}"

    proposed = parse_planned_name(function, str(plan.get("stdout") or ""))
    if not proposed:
        return None, "no evidence-backed name proposed"

    try:
        applied = run_name_decompiled_apply(function, repo_root=repo_root)
    except (OSError, subprocess.SubprocessError) as exc:
        return None, f"name_decompiled apply failed to run: {exc}"

    new_name = parse_applied_name(function, str(applied.get("stdout") or ""))
    if not new_name:
        detail = f"apply did not confirm a rename for {function} (proposed {proposed})"
        stderr_line = _first_line(str(applied.get("stderr") or ""))
        if stderr_line:
            detail += f"; {stderr_line}"
        return None, detail

    return new_name, f"renamed {function} -> {new_name}"


def git_status_paths(repo_root: Path, *, prefixes: tuple[str, ...]) -> list[str]:
    """``git status --porcelain`` in ``repo_root``, filtered to entries
    whose path starts with any of ``prefixes`` (repo-relative, POSIX-style)
    -- used to discover exactly which files ``tools/name_decompiled.py
    apply`` just changed (it reports only counts, never paths) so they can
    be named explicitly to ``git commit --only``. Returns ``[]`` (never
    raises) if ``git status`` itself fails.
    """
    try:
        proc = subprocess.run(
            ["git", "status", "--porcelain"],
            cwd=repo_root,
            capture_output=True,
            text=True,
            env=_clean_env(),
        )
    except OSError:
        return []
    if proc.returncode != 0:
        return []
    paths: set[str] = set()
    for line in (proc.stdout or "").splitlines():
        if len(line) <= 3:
            continue
        entry = line[3:].strip()
        if " -> " in entry:
            entry = entry.split(" -> ", 1)[1]
        entry = entry.strip().strip('"')
        if entry and any(entry.startswith(prefix) for prefix in prefixes):
            paths.add(entry)
    return sorted(paths)


def git_checkout_paths(paths: list[str], *, repo_root: Path) -> bool:
    """``git checkout -- <p1> <p2> ...`` in ``repo_root`` -- discards any
    working-tree modification to each path, restoring it to HEAD's committed
    version. Used to discard ``tools/name_decompiled.py apply``'s rewrite of
    ``disasm/linker_scripts`` (other than ``aliases.ld``, see
    append_name_alias) after a naming rename -- see the caller in
    ``merge()``. Returns False (never raises) on any subprocess failure; the
    caller only logs it, same as every other naming-follow-up step.
    """
    if not paths:
        return True
    try:
        proc = subprocess.run(
            ["git", "checkout", "--", *paths],
            cwd=repo_root,
            capture_output=True,
            text=True,
            env=_clean_env(),
        )
    except OSError:
        return False
    return proc.returncode == 0


def append_name_alias(old: str, new: str, *, repo_root: Path) -> bool:
    """Append ``"<old> = <new>;"`` to ``_ALIASES_LD_PATH``
    (``disasm/linker_scripts/us/aliases.ld``), unless an identical line is
    already there.

    This is the hand-written, splat-preserved compatibility script
    aliases.ld's own header comment describes -- it is what keeps a
    just-renamed function's old name resolvable for a container's
    pre-extracted asm tree, which still calls it by that name until the
    tree itself is regenerated. `tools/name_decompiled.py apply` renames
    ``old``'s entry in ``disasm/linker_scripts/us/symbol_addrs_code.txt``
    too, but `merge()`'s naming step deliberately discards that (see its
    caller): a matched/decompiled owner's symtab entry is never fed to the
    linker, so renaming it there is a no-op at best and, left as an
    uncommitted leftover, was exactly what broke every container launch on
    2026-09-02 -- this alias line is the actual, committed fix, mirroring
    PR #58's hand-applied one.

    Returns whether a line was actually appended (False if it was already
    present, or the file couldn't be read/written). Never raises.
    """
    path = repo_root / _ALIASES_LD_PATH
    line = f"{old} = {new};"
    try:
        existing = path.read_text(encoding="utf-8") if path.is_file() else ""
    except OSError:
        return False
    if any(existing_line.strip() == line for existing_line in existing.splitlines()):
        return False
    try:
        with path.open("a", encoding="utf-8") as f:
            if existing and not existing.endswith("\n"):
                f.write("\n")
            f.write(line + "\n")
    except OSError:
        return False
    return True


# ---------------------------------------------------------------------------
# merge
# ---------------------------------------------------------------------------


def process_owner(
    json_path: Path,
    *,
    repo_root: Path,
    commit: bool,
    dry_run: bool,
    out_dir: Path | None = None,
    extra_env: dict[str, str] | None = None,
    fresh_history: bool = False,
    previous_report: dict[str, object] | None = None,
) -> MergeRow:
    owner = json_path.stem
    try:
        payload = load_accepted_batch(json_path)
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        return MergeRow(owner, None, owner, "error", f"invalid batch: {exc}", False, "")

    source = batch_source(payload)
    function = owner_function_name(owner, payload)

    # Idempotency: never re-gate (and try to re-install/re-commit) an owner
    # that has already landed -- see this module's docstring and
    # previous_entry_marks_committed's own docstring for why each signal is
    # sufficient on its own.
    if source and not source_still_has_pragma(repo_root, source, owner):
        return MergeRow(
            owner, source, function, "already_landed",
            f"{source} no longer has the GLOBAL_ASM pragma for {owner}; already landed",
            False, "",
        )
    if previous_report is not None:
        prev_entry = previous_report.get(owner)
        if prev_entry is not None and previous_entry_marks_committed(prev_entry):
            return MergeRow(
                owner, source, function, "already_landed",
                "already committed per a previous merge-report.json", False, "",
            )

    result_path = out_dir / "merge-results" / f"{owner}.json" if out_dir is not None else None
    gate = run_fleet_probe_gate(
        json_path, repo_root=repo_root, extra_env=extra_env, result_path=result_path
    )
    result = gate.get("result")
    result = result if isinstance(result, dict) else {}
    accepted_functions = result.get("accepted")
    accepted = isinstance(accepted_functions, list) and function in accepted_functions

    if not accepted:
        batch_status = result.get("batch_status") or f"exit={gate.get('returncode')}"
        detail = f"host re-gate did not accept ({batch_status})"
        stderr_line = _first_line(str(gate.get("stderr") or ""))
        if stderr_line:
            detail += f"; {stderr_line}"
        return MergeRow(owner, source, function, "rejected", detail, False, "")

    if not commit or dry_run:
        return MergeRow(owner, source, function, "accepted", "host re-gate accepted", False, "")

    if not source:
        return MergeRow(
            owner, source, function, "accepted",
            "host re-gate accepted but batch has no 'source' to commit",
            False, "commit skipped: missing source",
        )

    if fresh_history and out_dir is not None:
        # Fold this run's --fresh-history accepted line(s) into the host's
        # real probe-stats history BEFORE attempting to commit this owner:
        # tools/check_decomp_provenance.py's pre-commit hook requires an
        # accepted attempt on record in that real history, and with
        # --fresh-history the re-gate above only ever recorded its accept
        # into the private <out>/merge-history.jsonl (see build_gate_env),
        # never the host's real history on its own.
        import_fresh_history_after_accept(out_dir, repo_root=repo_root)

    message = f"Land container match for {owner}"
    ok, commit_output = git_commit_only(source, message, repo_root=repo_root)

    if ok:
        commit_sha = git_rev_parse_head(repo_root) or ""
        return MergeRow(
            owner, source, function, "accepted", "host re-gate accepted",
            True, commit_output or "committed", commit_sha=commit_sha,
        )

    tail = _tail_lines(commit_output, 15)
    commit_detail = "commit failed"
    if out_dir is not None:
        log_dir = out_dir / "merge-results"
        log_dir.mkdir(parents=True, exist_ok=True)
        log_path = log_dir / f"{owner}.commit.log"
        log_path.write_text((commit_output or "") + "\n", encoding="utf-8")
        commit_detail = f"commit failed (see merge-results/{owner}.commit.log)"
    return MergeRow(
        owner, source, function, "accepted", "host re-gate accepted",
        False, commit_detail, commit_error_tail=tail,
    )


COLUMNS = [
    ("OWNER", 22),
    ("SOURCE", 32),
    ("STATUS", 10),
    ("COMMITTED", 9),
    # Wide enough to hold "host re-gate accepted [commit failed (see
    # merge-results/<owner>.commit.log)]" for a reasonably long owner name
    # without truncating away the log path the DETAIL column is meant to
    # surface.
    ("DETAIL", 90),
]


def _cell(value: str, width: int) -> str:
    if len(value) > width:
        value = value[: width - 1] + "…"
    return f"{value:<{width}}"


def format_table(rows: list[MergeRow]) -> str:
    header = " ".join(_cell(name, width) for name, width in COLUMNS)
    lines = [header, "-" * len(header)]
    for row in rows:
        detail = row.detail
        if row.commit_detail:
            detail = f"{detail} [{row.commit_detail}]"
        values = [
            row.owner,
            row.source or "-",
            row.status,
            "yes" if row.committed else "no",
            detail,
        ]
        lines.append(" ".join(_cell(v, w) for v, (_, w) in zip(values, COLUMNS)))
    return "\n".join(lines)


def build_gate_env(out_dir: Path, *, no_cc_check: bool, fresh_history: bool) -> dict[str, str]:
    """Extra environment for each owner's ``fleet_probe.py --gate`` call.

    ``--no-cc-check`` -> ``PRAGMA_GATE_CC_CHECK=0``, skipping
    ``disasm/Makefile``'s host clang syntax check (``RUN_CC_CHECK=1
    CC_CHECK_COMP=gcc``, which is clang on macOS) -- see this module's
    module docstring / the "merge" section of ``docs/CONTAINER_AGENT.md``
    for why an unrelated fragment can fail that check for every owner
    regardless of the candidate. This only ever reaches the one
    ``fleet_probe`` subprocess, never this process's own environment.

    ``--fresh-history`` -> ``PRAGMA_PROBE_STATS=<out>/merge-history.jsonl``,
    a history file dedicated to this merge run (created empty here if it
    does not already exist), so the runner's own preflight ("already
    rejected") only ever sees attempts *this run* made, never a prior host
    re-gate recorded in the real, shared probe-stats history.
    """
    env: dict[str, str] = {}
    if no_cc_check:
        env["PRAGMA_GATE_CC_CHECK"] = "0"
    if fresh_history:
        history_path = out_dir / "merge-history.jsonl"
        history_path.parent.mkdir(parents=True, exist_ok=True)
        if not history_path.exists():
            history_path.touch()
        env["PRAGMA_PROBE_STATS"] = str(history_path)
    return env


def write_merge_report(
    out_dir: Path,
    rows: list[MergeRow],
    *,
    no_cc_check: bool,
    fresh_history: bool,
    notes_results: list[NotesResult] | None = None,
    names: dict[str, str] | None = None,
) -> Path:
    """Write ``<out>/merge-report.json``: owner -> status, plus the flags
    that shaped this run, plus this run's own ``notes_applied`` (source ->
    list of newly appended region-notes lines, omitting any source with
    nothing new) and ``names`` (owner -> new name, for every owner
    ``name_after_commit`` actually renamed this run) -- neither is
    cumulative across runs, exactly like ``cc_check_bypassed`` /
    ``fresh_history`` above them. ``cc_check_bypassed: true`` is the durable
    record
    that every accepted candidate in this run was NOT verified to compile
    cleanly by the host's own clang syntax check -- read this back before
    trusting a ``--no-cc-check`` run's results.

    Cumulative: this run's ``owners`` map is built on top of whatever a
    prior ``merge-report.json`` in ``out_dir`` already recorded (see
    ``load_previous_report_owners``), so an owner not in ``rows`` at all --
    filtered out by ``--owners``, say -- keeps its prior entry rather than
    disappearing from the report.

    Per-owner entry shapes (``rows`` always wins over a prior entry for the
    same owner):

    * an owner whose host re-gate accepted and ``git commit --only`` then
      succeeded maps to an object, ``{"status": "accepted", "committed":
      true, "commit": "<sha>"}`` -- the ``git rev-parse HEAD`` read back
      right after that commit (``process_owner``'s ``commit_sha``); the
      ``"commit"`` key is omitted if the hash couldn't be read back, but
      ``committed`` is still ``true``. A plain ``"accepted"`` string (no
      ``"commit"`` field at all) means the host re-gate accepted but no
      commit was attempted (``--commit`` not passed, ``--dry-run``, or a
      missing ``source`` to commit) -- readers must not treat a bare
      ``"accepted"`` string as proof of a commit having happened; only
      before this fix could it also (ambiguously) mean "committed".
    * an owner whose host re-gate accepted but whose ``git commit --only``
      then failed is recorded as an object,
      ``{"status": "accepted", "committed": false, "commit_error": "<last
      15 line(s) of combined stdout+stderr>"}`` -- so the failure is
      visible without re-running anything; the full output is also kept at
      ``<out>/merge-results/<owner>.commit.log``.
    * an owner skipped this run because it had already landed (see this
      module's docstring / ``previous_entry_marks_committed``) maps to the
      plain string ``"already_landed"``.
    * every other owner (rejected, error) maps to its plain status string.
    """
    owners: dict[str, object] = dict(load_previous_report_owners(out_dir))
    for row in rows:
        if row.status == "already_landed":
            owners[row.owner] = "already_landed"
        elif row.commit_error_tail:
            owners[row.owner] = {
                "status": row.status,
                "committed": row.committed,
                "commit_error": row.commit_error_tail,
            }
        elif row.committed:
            entry: dict[str, object] = {"status": row.status, "committed": True}
            if row.commit_sha:
                entry["commit"] = row.commit_sha
            owners[row.owner] = entry
        else:
            owners[row.owner] = row.status

    notes_applied = {
        nr.source: nr.appended for nr in (notes_results or []) if nr.appended
    }

    report_path = out_dir / "merge-report.json"
    payload = {
        "cc_check_bypassed": bool(no_cc_check),
        "fresh_history": bool(fresh_history),
        "owners": owners,
        "notes_applied": notes_applied,
        "names": dict(names or {}),
    }
    report_path.write_text(
        json.dumps(payload, indent=2, sort_keys=True) + "\n", encoding="utf-8"
    )
    return report_path


def merge(
    out_dir: Path,
    *,
    repo_root: Path,
    commit: bool,
    dry_run: bool,
    no_cc_check: bool = False,
    fresh_history: bool = False,
    owners: set[str] | None = None,
    no_notes: bool = False,
    no_naming: bool = False,
) -> int:
    accepted_dir = out_dir / "accepted"
    json_paths = (
        sorted(p for p in accepted_dir.glob("*.json") if p.is_file())
        if accepted_dir.is_dir()
        else []
    )
    if not json_paths:
        print(f"container_merge: no accepted candidates under {accepted_dir}")
        return 0

    if owners is not None:
        json_paths = [p for p in json_paths if p.stem in owners]
        if not json_paths:
            print(
                f"container_merge: no accepted candidates under {accepted_dir} "
                f"match --owners {','.join(sorted(owners))}"
            )
            return 0

    if no_cc_check:
        print(
            "container_merge: *** WARNING --no-cc-check: the host clang syntax "
            "check (disasm/Makefile RUN_CC_CHECK) is DISABLED for this re-gate "
            "(PRAGMA_GATE_CC_CHECK=0). Any candidate accepted below was NOT "
            "verified to compile cleanly by the host's own check. ***"
        )

    extra_env = build_gate_env(out_dir, no_cc_check=no_cc_check, fresh_history=fresh_history)
    previous_report = load_previous_report_owners(out_dir)

    rows = [
        process_owner(
            path, repo_root=repo_root, commit=commit, dry_run=dry_run,
            out_dir=out_dir, extra_env=extra_env, fresh_history=fresh_history,
            previous_report=previous_report,
        )
        for path in json_paths
    ]

    print(format_table(rows))

    already_landed_rows = [row for row in rows if row.status == "already_landed"]
    rejected = [row for row in rows if row.status not in ("accepted", "already_landed")]
    accepted_rows = [row for row in rows if row.status == "accepted"]
    commit_failures = [
        row for row in accepted_rows
        if commit and not dry_run and row.source and not row.committed
    ]

    print()
    print(
        f"accepted {len(accepted_rows)}/{len(rows)}, rejected {len(rejected)}/{len(rows)}, "
        f"already_landed {len(already_landed_rows)}/{len(rows)}"
    )
    if commit and not dry_run:
        committed = sum(1 for row in rows if row.committed)
        print(f"committed {committed}/{len(accepted_rows)} accepted owner(s)")

    if rejected:
        print(
            f"container_merge: {len(rejected)} container-accepted candidate(s) "
            "failed the host re-gate", file=sys.stderr,
        )
    if commit_failures:
        print(
            f"container_merge: {len(commit_failures)} accepted candidate(s) "
            "failed to commit", file=sys.stderr,
        )
        for row in commit_failures:
            if not row.commit_error_tail:
                continue
            print()
            print(
                f"container_merge: {row.owner}: git commit --only failed "
                "(last 15 line(s) of combined stdout+stderr; full copy at "
                f"merge-results/{row.owner}.commit.log):"
            )
            print(row.commit_error_tail)

    notes_results: list[NotesResult] = []
    if not no_notes:
        notes_results = apply_region_notes(
            out_dir, repo_root=repo_root, commit=commit, dry_run=dry_run, rows=rows,
        )
        appended_total = sum(len(nr.appended) for nr in notes_results)
        if appended_total:
            print()
            for nr in notes_results:
                if not nr.appended:
                    continue
                note_state = "committed" if nr.committed else "not committed"
                print(
                    f"container_merge: region notes: {len(nr.appended)} new line(s) for "
                    f"{nr.source} ({note_state})"
                )

    names: dict[str, str] = {}
    if not no_naming:
        for row in rows:
            if not (row.status == "accepted" and row.committed):
                continue
            new_name, detail = name_after_commit(row.function, repo_root=repo_root)
            if not new_name:
                if detail != "no evidence-backed name proposed":
                    print(f"container_merge: naming {row.function}: {detail}", file=sys.stderr)
                continue

            # `tools/name_decompiled.py apply` also rewrote disasm/linker_scripts
            # in this working tree: row.function's own entry in
            # symbol_addrs_code.txt, and possibly other .ld/.txt files that
            # named it. Discard all of that except aliases.ld (apply's own
            # rewrite of *it* is worth keeping -- e.g. an existing alias whose
            # RHS named row.function now correctly points at new_name
            # instead): a matched/decompiled owner's symtab entry is never fed
            # to the linker, so committing its rename there is pointless, and
            # leaving it uncommitted (the naming commit below only ever
            # touches disasm/src/disasm/include) is exactly what broke every
            # container launch on 2026-09-02 -- a container's pre-extracted
            # asm tree still calls row.function by its old name, and the
            # overlay copies disasm/linker_scripts verbatim.
            linker_changed = git_status_paths(repo_root, prefixes=("disasm/linker_scripts",))
            to_revert = [p for p in linker_changed if p != _ALIASES_LD_PATH]
            if to_revert and not git_checkout_paths(to_revert, repo_root=repo_root):
                print(
                    f"container_merge: naming {row.function} -> {new_name}: failed to "
                    "revert splat-generated symbol table edit(s) under "
                    f"disasm/linker_scripts ({', '.join(to_revert)}); left as-is",
                    file=sys.stderr,
                )
            # ... and add the alias a container's pre-extracted asm tree
            # actually needs: old name -> new name, the same fix PR #58
            # applied by hand.
            if append_name_alias(row.function, new_name, repo_root=repo_root):
                print(
                    f"container_merge: aliased {row.function} -> {new_name} in "
                    f"{_ALIASES_LD_PATH} (symbol_addrs_code.txt is intentionally "
                    "left unrenamed for a matched owner; a container's "
                    "pre-extracted asm tree still calls the old name)"
                )

            if not commit or dry_run:
                # Should not happen (row.committed already implies commit and
                # not dry_run), kept as a defensive guard.
                continue
            changed = git_status_paths(
                repo_root, prefixes=("disasm/src", "disasm/include", _ALIASES_LD_PATH)
            )
            if not changed:
                print(
                    f"container_merge: naming {row.function} -> {new_name}: apply "
                    "reported a rename but no changed files were found under "
                    "disasm/src or disasm/include", file=sys.stderr,
                )
                continue
            ok, output = git_commit_only_paths(
                changed, f"Name {row.function} -> {new_name}", repo_root=repo_root
            )
            if ok:
                names[row.owner] = new_name
                print(f"container_merge: named {row.function} -> {new_name}")
            else:
                print(
                    f"container_merge: naming {row.function} -> {new_name}: commit "
                    f"failed: {_first_line(output)}", file=sys.stderr,
                )

    report_path = write_merge_report(
        out_dir, rows, no_cc_check=no_cc_check, fresh_history=fresh_history,
        notes_results=notes_results, names=names,
    )
    print()
    print(f"container_merge: wrote {report_path}")

    if fresh_history and accepted_rows:
        status_line = import_fresh_history_after_accept(out_dir, repo_root=repo_root)
        if status_line:
            print(status_line)

    print()
    print(
        "container_merge: reminder: run "
        f"'python3 tools/container_merge.py import-stats {out_dir}' to fold this run's "
        "probe-stats history into the host's"
    )

    return 1 if (rejected or commit_failures) else 0


# ---------------------------------------------------------------------------
# import-stats
#
# The container's runner (tools/fleet_probe.py / tools/try_pragma_compare.py,
# via tools/probe_stats.py) records every attempt it probes into a
# PRAGMA_PROBE_STATS-resolved JSONL history -- inside the container's own
# checkout, so it is lost once the container exits. tools/container_agent.py
# copies it out on every state save (see its own "Probe-stats export"
# section) to <out>/probe-stats/probe-stats.jsonl. This command folds that
# copy into *this* checkout's own history, the same way ``merge`` folds an
# accepted candidate into the tree: a deliberate, host-side step, never
# automatic.
#
# tools/probe_stats.py has no "merge two arbitrary JSONL files" helper (its
# own ``migrate_legacy`` is specific to one fixed legacy path) -- so this is
# a careful line-level append: read the host's current history once, skip
# any source line already present verbatim, and append only the rest. Exact
# duplicate lines are common (probe_stats.append_batch writes semantically
# stable ``json.dumps(row, sort_keys=True)`` rows, and re-running
# import-stats on the same out dir, or importing the same run twice from two
# out dirs, must not double-count).
# ---------------------------------------------------------------------------


def _host_probe_stats_path(repo_root: Path) -> Path | None:
    """Resolve the host's probe-stats file the same way the runner does
    (``tools/probe_stats.py``'s ``stats_path()`` / ``tools/container_agent.py``'s
    ``_probe_stats_source_path``): ``PRAGMA_PROBE_STATS`` if set (``""``
    disables it), else ``<repo_root>/disasm/probe-stats/probe-stats.jsonl``.
    """
    value = os.environ.get("PRAGMA_PROBE_STATS")
    if value == "":
        return None
    if value is not None:
        return Path(os.path.expandvars(value)).expanduser()
    return repo_root / "disasm" / "probe-stats" / "probe-stats.jsonl"


def _line_has_accepted_attempt(line: str) -> bool:
    """Cheap-then-exact check: does this JSONL batch line record at least
    one ``attempts[].status == "accepted"`` entry?

    Mirrors ``tools/check_decomp_provenance.py``'s ``accepted_functions``:
    a substring check before ever parsing, since most lines in a history
    are not an accepted attempt at all.
    """
    if '"accepted"' not in line:
        return False
    try:
        batch = json.loads(line)
    except json.JSONDecodeError:
        return False
    if not isinstance(batch, dict):
        return False
    attempts = batch.get("attempts")
    if not isinstance(attempts, list):
        return False
    return any(
        isinstance(attempt, dict) and attempt.get("status") == "accepted"
        for attempt in attempts
    )


def append_history_lines(
    source_path: Path,
    target_path: Path,
    *,
    dry_run: bool = False,
    only_accepted: bool = False,
) -> tuple[int, int, int]:
    """Fold ``source_path``'s probe-stats JSONL lines into ``target_path``.

    A line already present verbatim in ``target_path`` (or repeated within
    ``source_path`` itself) is skipped -- careful line-level dedupe, not a
    blind concatenation, so re-running this against the same source, or
    against the same target from two different sources, never
    double-counts (``probe_stats.append_batch`` writes semantically stable
    ``json.dumps(row, sort_keys=True)`` rows, so an exact duplicate really
    is the same attempt recorded twice).

    ``only_accepted``, when set, considers only lines with at least one
    accepted attempt (see ``_line_has_accepted_attempt``) -- used to import
    evidence for a successful ``--fresh-history`` re-gate without also
    pulling rejected-attempt noise into the host's real history.

    Returns ``(considered, appended, duplicates)`` -- ``considered`` counts
    only lines that pass the ``only_accepted`` filter (when set).
    ``dry_run`` reports what would change but never touches ``target_path``.
    """
    existing_lines: set[str] = set()
    if target_path.is_file():
        for line in target_path.read_text(encoding="utf-8", errors="replace").splitlines():
            line = line.strip()
            if line:
                existing_lines.add(line)

    considered = 0
    new_lines: list[str] = []
    for line in source_path.read_text(encoding="utf-8", errors="replace").splitlines():
        line = line.strip()
        if not line:
            continue
        if only_accepted and not _line_has_accepted_attempt(line):
            continue
        considered += 1
        if line in existing_lines:
            continue
        new_lines.append(line)
        existing_lines.add(line)  # a duplicate within the source file itself only counts once

    duplicates = considered - len(new_lines)

    if not dry_run and new_lines:
        target_path.parent.mkdir(parents=True, exist_ok=True)
        with target_path.open("a", encoding="utf-8") as handle:
            for line in new_lines:
                handle.write(line + "\n")

    return considered, len(new_lines), duplicates


def import_stats(out_dir: Path, *, repo_root: Path, dry_run: bool) -> int:
    source_path = out_dir / "probe-stats" / "probe-stats.jsonl"
    if not source_path.is_file():
        print(f"container_merge: no probe-stats file at {source_path}; nothing to import")
        return 0

    target_path = _host_probe_stats_path(repo_root)
    if target_path is None:
        print(
            "container_merge: host probe-stats is disabled (PRAGMA_PROBE_STATS=\"\"); "
            "nothing to import"
        )
        return 0

    total, new_count, duplicates = append_history_lines(source_path, target_path, dry_run=dry_run)
    print(
        f"container_merge: {source_path}: {total} line(s), {new_count} new, "
        f"{duplicates} already present in {target_path}"
    )

    if dry_run:
        print("container_merge: --dry-run, not writing")
        return 0
    if new_count == 0:
        return 0

    print(f"container_merge: appended {new_count} line(s) to {target_path}")
    return 0


def import_fresh_history_after_accept(out_dir: Path, *, repo_root: Path) -> str | None:
    """After a ``merge --fresh-history`` run where at least one owner's
    host re-gate accepted, fold that run's ``<out>/merge-history.jsonl``
    accepted line(s) into the host's real probe-stats history, using the
    same dedup-append logic as ``import-stats`` (see ``append_history_lines``).

    The host re-gate for ``--fresh-history`` runs against a dedicated,
    empty-per-run history file rather than the host's real one (so a prior
    host attempt can never trip its preflight), which means the accepted
    attempt this run just proved never lands in the host's real history on
    its own. Without this step, ``tools/check_decomp_provenance.py``'s
    pre-commit hook -- which requires an accepted attempt on record in that
    real history -- would refuse the very commit this merge just earned.

    Returns a human-readable status line, or ``None`` if there was nothing
    to do (no fresh-history file for this run).
    """
    source_path = out_dir / "merge-history.jsonl"
    if not source_path.is_file():
        return None

    target_path = _host_probe_stats_path(repo_root)
    if target_path is None:
        return (
            "container_merge: --fresh-history: host probe-stats is disabled "
            "(PRAGMA_PROBE_STATS=\"\"); not imported"
        )

    total, new_count, duplicates = append_history_lines(
        source_path, target_path, only_accepted=True
    )
    return (
        f"container_merge: --fresh-history: {source_path}: {total} accepted line(s), "
        f"{new_count} new, {duplicates} already present in {target_path}"
    )


# ---------------------------------------------------------------------------
# summary
# ---------------------------------------------------------------------------


def load_json_or_none(path: Path) -> object | None:
    if not path.is_file():
        return None
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return None
    return payload


def _fmt_number(value: object) -> str:
    if isinstance(value, bool):
        return str(value)
    if isinstance(value, (int, float)):
        return f"{value:.4f}" if isinstance(value, float) else str(value)
    return "-" if value is None else str(value)


def format_state(state: object) -> str:
    """``state.json``: owner -> {best_similarity, iterations, history[], status}."""
    if not isinstance(state, dict) or not state:
        return "(empty)"
    columns = [
        ("OWNER", 22), ("STATUS", 12), ("BEST_SIMILARITY", 16),
        ("ITERATIONS", 11), ("HISTORY_LEN", 12),
    ]
    lines = [" ".join(f"{name:<{w}}" for name, w in columns)]
    lines.append("-" * len(lines[0]))
    for owner in sorted(state):
        entry = state[owner]
        entry = entry if isinstance(entry, dict) else {}
        history = entry.get("history")
        row = [
            owner,
            str(entry.get("status", "-")),
            _fmt_number(entry.get("best_similarity")),
            str(entry.get("iterations", "-")),
            str(len(history)) if isinstance(history, list) else "-",
        ]
        lines.append(" ".join(_cell(v, w) for v, (_, w) in zip(row, columns)))
    return "\n".join(lines)


def format_summary(summary: object) -> str:
    """Best-effort readable rendering of ``summary.json``.

    The driver's exact schema (owners attempted, matched, best per owner,
    iteration counts, wall time) lives in ``tools/container_agent.py``, owned
    elsewhere; this stays schema-tolerant rather than pinning field names.
    """
    if not isinstance(summary, dict) or not summary:
        return "(empty)"
    lines: list[str] = []
    scalars = {k: v for k, v in summary.items() if not isinstance(v, (dict, list))}
    if scalars:
        width = max(len(str(k)) for k in scalars) + 1
        for key, value in scalars.items():
            lines.append(f"{(str(key) + ':'):<{width}} {value}")
    for key, value in summary.items():
        if isinstance(value, dict) and value:
            lines.append("")
            lines.append(f"{key}:")
            sub_width = max(len(str(k)) for k in value) + 1
            for sub_key, sub_value in value.items():
                lines.append(f"  {(str(sub_key) + ':'):<{sub_width}} {sub_value}")
        elif isinstance(value, list) and value:
            lines.append("")
            lines.append(f"{key}: [{len(value)} item(s)]")
            for item in value[:20]:
                lines.append(f"  - {item}")
            if len(value) > 20:
                lines.append(f"  ... {len(value) - 20} more")
    return "\n".join(lines) if lines else "(empty)"


def summary_command(out_dir: Path) -> int:
    summary_path = out_dir / "summary.json"
    state_path = out_dir / "state.json"
    summary = load_json_or_none(summary_path)
    state = load_json_or_none(state_path)

    if summary is None and state is None:
        print(
            f"container_merge: neither {summary_path} nor {state_path} "
            "found or parseable", file=sys.stderr,
        )
        return 1

    print(f"=== {summary_path} ===")
    print(format_summary(summary) if summary is not None else "(missing)")
    print()
    print(f"=== {state_path} ===")
    print(format_state(state) if state is not None else "(missing)")
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    sub = parser.add_subparsers(dest="command", required=True)

    p_merge = sub.add_parser(
        "merge", help="re-gate accepted container candidates and optionally commit them"
    )
    p_merge.add_argument(
        "out_dir", type=Path,
        help="container output directory (contains accepted/, state.json, summary.json)",
    )
    p_merge.add_argument(
        "--repo", type=Path, default=Path("."), help="host checkout to re-gate/commit against"
    )
    p_merge.add_argument(
        "--commit", action="store_true",
        help="git commit --only <source> for each owner the host re-gate accepts",
    )
    p_merge.add_argument(
        "--dry-run", action="store_true", help="re-gate only; never commit even with --commit"
    )
    p_merge.add_argument(
        "--no-cc-check", action="store_true",
        help=(
            "set PRAGMA_GATE_CC_CHECK=0 for the re-gate, skipping the host clang "
            "syntax check (disasm/Makefile RUN_CC_CHECK); use only to work around "
            "an unrelated file failing that check. Recorded as "
            "cc_check_bypassed: true in <out>/merge-report.json"
        ),
    )
    p_merge.add_argument(
        "--fresh-history", action="store_true",
        help=(
            "point PRAGMA_PROBE_STATS at <out>/merge-history.jsonl for the re-gate "
            "so a prior host attempt on record can never trip the runner's "
            "'already rejected' preflight; a successful accept is then folded "
            "into the host's real probe-stats history"
        ),
    )
    p_merge.add_argument(
        "--owners", type=str, default=None,
        help=(
            "comma-separated list of owner names (accepted/<owner>.json stems) to "
            "limit this run to; every other owner is left untouched and its prior "
            "merge-report.json entry, if any, is carried forward unchanged"
        ),
    )
    p_merge.add_argument(
        "--no-notes", action="store_true",
        help=(
            "skip folding <out>/region-notes/*.md into docs/regions/*.md "
            "(on by default; see docs/CONTAINER_AGENT.md Sec 9.5)"
        ),
    )
    p_merge.add_argument(
        "--no-naming", action="store_true",
        help=(
            "skip offering each committed owner's function to "
            "tools/name_decompiled.py plan/apply (on by default; see "
            "docs/CONTAINER_AGENT.md Sec 9.6)"
        ),
    )

    p_summary = sub.add_parser(
        "summary", help="print summary.json / state.json from a container output directory"
    )
    p_summary.add_argument("out_dir", type=Path)

    p_import_stats = sub.add_parser(
        "import-stats",
        help="append this run's <out>/probe-stats/probe-stats.jsonl into the host's probe-stats history",
    )
    p_import_stats.add_argument(
        "out_dir", type=Path,
        help="container output directory (contains probe-stats/probe-stats.jsonl)",
    )
    p_import_stats.add_argument(
        "--repo", type=Path, default=Path("."), help="host checkout whose probe-stats history to append to"
    )
    p_import_stats.add_argument(
        "--dry-run", action="store_true", help="count lines only; never write to the host history"
    )

    args = parser.parse_args(argv)

    if args.command == "merge":
        owners = None
        if args.owners:
            owners = {name.strip() for name in args.owners.split(",") if name.strip()}
        return merge(
            args.out_dir,
            repo_root=args.repo.resolve(),
            commit=args.commit,
            dry_run=args.dry_run,
            no_cc_check=args.no_cc_check,
            fresh_history=args.fresh_history,
            owners=owners,
            no_notes=args.no_notes,
            no_naming=args.no_naming,
        )
    if args.command == "summary":
        return summary_command(args.out_dir)
    if args.command == "import-stats":
        return import_stats(args.out_dir, repo_root=args.repo.resolve(), dry_run=args.dry_run)

    parser.error(f"unknown command {args.command!r}")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
