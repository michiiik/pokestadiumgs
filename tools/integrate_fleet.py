#!/usr/bin/env python3
"""Land fleet branches onto master without a human in the loop.

The ROM gate is a real oracle, not a heuristic: ``make -C disasm COMPARE=1``
ends in ``md5sum -c disasm/baseroms/us/checksum.md5``, a single line naming
one hash.  A merge whose rebuilt ROM still hashes to it is correct by
construction, so integration needs no review -- *provided* nothing in the
branch can weaken the check that proves it.

That is the whole job of this tool:

1. **Refuse** a branch that touches a trust anchor (the checksum, the compare
   rule, the provenance hook and its script, this file) or that introduces a
   gate-bypass environment variable.  These are exactly the changes the hash
   cannot detect, because they are changes to the hash check.
2. **Merge** the branch onto an integration branch.
3. **Prove** it: full ``COMPARE=1`` rebuild with the host syntax check on,
   the tools test suite, and a provenance sweep over every pragma the merge
   removed.
4. **Land or park.**  A proven merge fast-forwards master.  A failure parks
   the branch, restores master, and writes the reason to the log.

Nothing here bypasses a hook, and a refusal is never downgraded to a warning.

Usage:
    python3 tools/integrate_fleet.py land --branches 'fleet/*'
    python3 tools/integrate_fleet.py land --branches 'fleet/*' --dry-run
    python3 tools/integrate_fleet.py check --branch fleet/w1-f24
"""

from __future__ import annotations

import argparse
import fnmatch
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent

# Paths whose modification would weaken the proof rather than be caught by it.
TRUST_ANCHORS = (
    "disasm/baseroms/",
    "disasm/Makefile",
    ".githooks/",
    "tools/check_decomp_provenance.py",
    "tools/integrate_fleet.py",
)

# Each of these disables a part of the chain that proves a body is correct.
BYPASS_PATTERNS = (
    r"\bDECOMP_PROVENANCE_SKIP\b",
    r"\bPRAGMA_CLAIMS_SKIP\b",
    r"\bSKIP_TOOL_TESTS\b",
    r"\bPRAGMA_GATE_CC_CHECK\s*=\s*0",
    r"\bPRAGMA_PROBE_STATS\s*=\s*(?:$|[\"']\s*[\"'])",
    r"\bPRAGMA_FUTILITY_OVERRIDE\b",
)

LOG_PATH = REPO_ROOT / "docs" / "FLEET_INTEGRATION_LOG.md"

# Generated files that never block integration. ``COVERAGE.md`` is rewritten
# from the index by ``.githooks/pre-commit.d/10-coverage.sh`` on every commit,
# and the git index is shared by every session in the checkout (AGENTS.md
# Sec 1.3), so a session that exits mid-work routinely leaves a stale staged
# copy behind. Treating that as a dirty tree would wedge unattended
# integration until a human intervened -- exactly what this tool exists to
# avoid -- and it cannot mask a real problem, because the value is derived
# from the tree the ROM gate then rebuilds.
IGNORED_WHEN_DIRTY = ("COVERAGE.md",)

# Generated files whose merge conflicts are resolved by regenerating them
# rather than by parking the branch. Every fleet branch carries a
# hook-regenerated COVERAGE.md computed from its own worktree, so *every*
# parallel branch conflicts here and nowhere else; AGENTS.md Sec 1.3 already
# prescribes taking the integration branch's copy. Regenerating from the
# merged tree is strictly better than either side, because it is the only
# value that describes what actually merged.
REGENERATED_ON_CONFLICT = {"COVERAGE.md": ["python3", "tools/update_coverage.py"]}


class IntegrationError(RuntimeError):
    pass


def git(*args: str, check: bool = True, capture: bool = True) -> str:
    """Run a git command in the repo, with the hook's exported env stripped.

    ``.githooks/pre-commit`` exports ``GIT_DIR``/``GIT_INDEX_FILE``; inheriting
    those here would point this tool at a hook's temporary index (AGENTS.md
    Sec 1.3).
    """
    env = {k: v for k, v in os.environ.items()
           if k not in {"GIT_DIR", "GIT_INDEX_FILE", "GIT_WORK_TREE", "GIT_OBJECT_DIRECTORY"}}
    proc = subprocess.run(
        ["git", *args], cwd=REPO_ROOT, env=env,
        capture_output=capture, text=True,
    )
    if check and proc.returncode != 0:
        raise IntegrationError(
            f"git {' '.join(args)} failed ({proc.returncode}): "
            f"{(proc.stderr or proc.stdout or '').strip()[:400]}"
        )
    return (proc.stdout or "") if capture else ""


def run(cmd: list[str], *, timeout: int, env_extra: dict[str, str] | None = None) -> tuple[bool, str]:
    env = dict(os.environ)
    for key in ("GIT_DIR", "GIT_INDEX_FILE", "GIT_WORK_TREE", "GIT_OBJECT_DIRECTORY"):
        env.pop(key, None)
    env.update(env_extra or {})
    try:
        proc = subprocess.run(
            cmd, cwd=REPO_ROOT, env=env, capture_output=True, text=True, timeout=timeout
        )
    except subprocess.TimeoutExpired:
        return False, f"timed out after {timeout}s"
    output = (proc.stdout or "") + (proc.stderr or "")
    return proc.returncode == 0, output


def changed_paths(base: str, branch: str) -> list[str]:
    out = git("diff", "--name-only", f"{base}...{branch}")
    return [line.strip() for line in out.splitlines() if line.strip()]


def touched_anchors(paths: list[str]) -> list[str]:
    hits = []
    for path in paths:
        for anchor in TRUST_ANCHORS:
            if path == anchor or path.startswith(anchor):
                hits.append(f"{path} (anchor: {anchor})")
    return hits


def introduced_bypasses(base: str, branch: str) -> list[str]:
    """Bypass tokens appearing on ADDED lines of the branch diff."""
    diff = git("diff", "--unified=0", f"{base}...{branch}")
    hits: list[str] = []
    for line in diff.splitlines():
        if not line.startswith("+") or line.startswith("+++"):
            continue
        for pattern in BYPASS_PATTERNS:
            if re.search(pattern, line):
                hits.append(f"{pattern} -> {line.strip()[:120]}")
    return hits


def screen(base: str, branch: str) -> list[str]:
    """Static refusals: the changes the ROM hash provably cannot catch."""
    reasons: list[str] = []
    paths = changed_paths(base, branch)
    if not paths:
        reasons.append("branch has no changes against the base")
    reasons += [f"touches trust anchor: {hit}" for hit in touched_anchors(paths)]
    reasons += [f"introduces gate bypass: {hit}" for hit in introduced_bypasses(base, branch)]
    return reasons


def prove(gate_timeout: int) -> list[str]:
    """Everything the merged tree must survive. Empty list means proven."""
    failures: list[str] = []

    ok, out = run(["make", "-C", "disasm", "COMPARE=1"],
                  timeout=gate_timeout, env_extra={"RUN_CC_CHECK": "1"})
    if not ok or "OK" not in out:
        tail = "\n".join(out.strip().splitlines()[-12:])
        failures.append(f"ROM gate failed:\n{tail}")

    ok, out = run(["bash", "tools/run_tests.sh"], timeout=600)
    if not ok:
        tail = "\n".join(out.strip().splitlines()[-12:])
        failures.append(f"tools test suite failed:\n{tail}")

    ok, out = run(["python3", "tools/check_decomp_provenance.py"], timeout=300)
    if not ok:
        tail = "\n".join(out.strip().splitlines()[-12:])
        failures.append(f"decomp provenance check failed:\n{tail}")

    return failures


def log_result(entries: list[dict[str, object]]) -> None:
    if not entries:
        return
    LOG_PATH.parent.mkdir(parents=True, exist_ok=True)
    if not LOG_PATH.exists():
        LOG_PATH.write_text(
            "# Fleet integration log\n\n"
            "Written by `tools/integrate_fleet.py`. One row per branch per run:\n"
            "what landed, what was parked, and why. This is the record that\n"
            "replaces a human reviewer, so it is append-only.\n"
        )
    stamp = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
    lines = [f"\n## {stamp}\n"]
    for entry in entries:
        verdict = entry["verdict"]
        lines.append(f"\n### {entry['branch']} — **{verdict}**\n")
        if entry.get("head"):
            lines.append(f"\n- head: `{entry['head']}`\n")
        for reason in entry.get("reasons", []):
            first = str(reason).strip().splitlines()[0]
            lines.append(f"- {first}\n")
    with LOG_PATH.open("a") as handle:
        handle.writelines(lines)


def conflicted_paths() -> list[str]:
    out = git("diff", "--name-only", "--diff-filter=U")
    return [line.strip() for line in out.splitlines() if line.strip()]


def resolve_generated_conflicts() -> tuple[bool, str]:
    """Resolve a conflict that is purely in regenerated files.

    Returns ``(True, note)`` when every conflicted path was regenerated and
    the merge was committed, ``(False, reason)`` when anything else conflicted
    and the caller should abort and park. A real source conflict is never
    resolved here: two sessions disagreeing about a function body is exactly
    the case an unattended run must not guess at.
    """
    paths = conflicted_paths()
    if not paths:
        return False, "merge failed with no conflicted paths"
    unexpected = [path for path in paths if path not in REGENERATED_ON_CONFLICT]
    if unexpected:
        return False, f"merge conflict in {', '.join(sorted(unexpected))}"

    for path in paths:
        ok, out = run(REGENERATED_ON_CONFLICT[path], timeout=300)
        if not ok:
            return False, f"could not regenerate {path}: {out.strip()[-200:]}"
        git("add", "--", path)

    commit = subprocess.run(
        ["git", "commit", "--no-edit"], cwd=REPO_ROOT, capture_output=True, text=True,
        env={k: v for k, v in os.environ.items()
             if k not in {"GIT_DIR", "GIT_INDEX_FILE", "GIT_WORK_TREE", "GIT_OBJECT_DIRECTORY"}},
    )
    if commit.returncode != 0:
        return False, f"merge commit failed: {(commit.stdout + commit.stderr).strip()[:200]}"
    return True, f"regenerated on conflict: {', '.join(sorted(paths))}"


def blocking_dirt(status_porcelain: str) -> list[str]:
    """Working-tree entries that must stop an unattended merge.

    Everything except the regenerated files in ``IGNORED_WHEN_DIRTY``: a real
    uncommitted source change would make a gate failure ambiguous between the
    merge and the local edit, which is the one thing an unattended run cannot
    resolve.
    """
    blocking: list[str] = []
    for line in status_porcelain.splitlines():
        if not line.strip():
            continue
        path = line[3:].strip().strip('"')
        if path in IGNORED_WHEN_DIRTY:
            continue
        blocking.append(line)
    return blocking


def resolve_branches(pattern: str) -> list[str]:
    out = git("for-each-ref", "--format=%(refname:short)", "refs/heads/")
    names = [n.strip() for n in out.splitlines() if n.strip()]
    return sorted(n for n in names if fnmatch.fnmatch(n, pattern))


def land(pattern: str, base: str, gate_timeout: int, dry_run: bool) -> int:
    blocking = blocking_dirt(git("status", "--porcelain"))
    if blocking:
        raise IntegrationError(
            "working tree is dirty; integration needs a clean tree so a gate "
            "failure can only come from the merge:\n" + "\n".join(blocking)[:600]
        )

    original = git("rev-parse", "--abbrev-ref", "HEAD").strip()
    branches = resolve_branches(pattern)
    if not branches:
        print(f"no branches match {pattern!r}")
        return 0

    entries: list[dict[str, object]] = []
    landed = parked = 0

    for branch in branches:
        head = git("rev-parse", "--short", branch).strip()
        print(f"\n=== {branch} ({head}) ===")

        reasons = screen(base, branch)
        if reasons:
            for reason in reasons:
                print(f"  REFUSED: {reason}")
            entries.append({"branch": branch, "head": head,
                            "verdict": "refused", "reasons": reasons})
            parked += 1
            continue

        if dry_run:
            print("  screened clean (dry run: not merging)")
            entries.append({"branch": branch, "head": head,
                            "verdict": "screened-clean (dry run)", "reasons": []})
            continue

        git("checkout", base, capture=True)
        merge = subprocess.run(
            ["git", "merge", "--no-ff", "--no-edit", branch],
            cwd=REPO_ROOT, capture_output=True, text=True,
        )
        if merge.returncode != 0:
            resolved, reason = resolve_generated_conflicts()
            if not resolved:
                git("merge", "--abort", check=False)
                print(f"  PARKED: {reason}")
                entries.append({"branch": branch, "head": head,
                                "verdict": "parked", "reasons": [reason]})
                parked += 1
                continue
            print(f"  {reason}")

        print("  merged; proving...")
        failures = prove(gate_timeout)
        if failures:
            for failure in failures:
                print(f"  PARKED: {failure.splitlines()[0]}")
            git("reset", "--hard", f"{base}@{{1}}", check=False)
            git("checkout", base, capture=True)
            entries.append({"branch": branch, "head": head,
                            "verdict": "parked", "reasons": failures})
            parked += 1
            continue

        print("  PROVEN: ROM byte-identical, tests and provenance clean — landed")
        entries.append({"branch": branch, "head": head, "verdict": "landed", "reasons": []})
        landed += 1

    if original and original != git("rev-parse", "--abbrev-ref", "HEAD").strip():
        git("checkout", original, capture=True, check=False)

    log_result(entries)
    print(f"\nlanded {landed}, parked {parked}, of {len(branches)} branch(es)")
    print(f"log: {LOG_PATH.relative_to(REPO_ROOT)}")
    return 0 if parked == 0 else 1


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)

    p_land = sub.add_parser("land", help="screen, merge, prove and land branches")
    p_land.add_argument("--branches", default="fleet/*", help="glob over local branches")
    p_land.add_argument("--base", default="master")
    p_land.add_argument("--gate-timeout", type=int, default=1800)
    p_land.add_argument("--dry-run", action="store_true",
                        help="screen only; never merge or build")

    p_check = sub.add_parser("check", help="screen one branch without merging")
    p_check.add_argument("--branch", required=True)
    p_check.add_argument("--base", default="master")

    args = parser.parse_args(argv)
    try:
        if args.command == "check":
            reasons = screen(args.base, args.branch)
            if reasons:
                for reason in reasons:
                    print(f"REFUSED: {reason}")
                return 1
            print(f"{args.branch}: screened clean")
            return 0
        return land(args.branches, args.base, args.gate_timeout, args.dry_run)
    except IntegrationError as error:
        print(f"integrate_fleet: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
