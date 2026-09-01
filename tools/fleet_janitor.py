#!/usr/bin/env python3
"""Recover a fleet checkout from crashed agents, without a human in the loop.

An agent killed mid-transaction leaves state that silently corrupts the next
agent's work rather than failing loudly:

* **An installed, uncommitted body.** The worst case. The ROM gate builds the
  whole tree, so a half-finished body in one file makes *every other* agent's
  gate fail for reasons they cannot see. AGENTS.md Sec 1.2 tells a clean agent
  to report ``tooling-blocked`` and stop when it notices; unattended, nobody
  notices.
* **A dead file claim.** ``claims.json`` entries outlive the process that took
  them, so a fresh agent is warned off a file nobody is working on.
* **Stale probe trees and pruned worktrees**, which accumulate until they
  bury the ``git status`` signal Sec 1.2 depends on.

The uncommitted-body case splits in two, and the split is what makes this
safe to automate:

* **Recoverable** -- every pragma the file dropped has an ``accepted`` runner
  attempt on record. This is finished, proven work whose session died before
  committing. It is never discarded; ``clean`` leaves it in place and reports
  it so the integrator can land it.
* **Orphaned** -- some dropped pragma has no ``accepted`` attempt. Nothing
  proves this body matches, and the pre-commit provenance hook would reject
  it anyway. ``clean --revert-orphaned`` restores the file, after saving the
  discarded content under ``.fleet-janitor-backups/`` so a wrong call is
  always recoverable.

Usage:
    python3 tools/fleet_janitor.py scan
    python3 tools/fleet_janitor.py clean
    python3 tools/fleet_janitor.py clean --revert-orphaned
"""

from __future__ import annotations

import argparse
import json
import os
import shutil
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import check_decomp_provenance as provenance  # noqa: E402
import file_claims  # noqa: E402

REPO_ROOT = Path(__file__).resolve().parent.parent
BACKUP_DIR = REPO_ROOT / ".fleet-janitor-backups"


def git(*args: str, check: bool = True) -> str:
    env = {k: v for k, v in os.environ.items()
           if k not in {"GIT_DIR", "GIT_INDEX_FILE", "GIT_WORK_TREE", "GIT_OBJECT_DIRECTORY"}}
    proc = subprocess.run(["git", *args], cwd=REPO_ROOT, env=env,
                          capture_output=True, text=True)
    if check and proc.returncode != 0:
        raise RuntimeError(f"git {' '.join(args)}: {(proc.stderr or proc.stdout).strip()[:300]}")
    return proc.stdout or ""


def dirty_sources() -> list[str]:
    """Tracked, modified files under ``disasm/src``."""
    out = git("status", "--porcelain", "--", "disasm/src")
    paths = []
    for line in out.splitlines():
        if not line.strip():
            continue
        code, path = line[:2], line[3:].strip().strip('"')
        if "D" in code and not (REPO_ROOT / path).exists():
            continue
        paths.append(path)
    return paths


def classify_source(path: str, accepted: set[str]) -> tuple[str, list[str]]:
    """Return ``(verdict, functions)`` for one dirty source.

    ``recoverable`` when every dropped pragma is backed by an ``accepted``
    runner attempt, ``orphaned`` when any is not, ``no-pragma-change`` when
    the edit drops none (a comment or formatting change, harmless).
    """
    diff = git("diff", "HEAD", "--", path)
    dropped = provenance.removed_pragma_functions(diff)
    if not dropped:
        return "no-pragma-change", []
    unproven = sorted(set(dropped) - accepted)
    if unproven:
        return "orphaned", unproven
    return "recoverable", sorted(set(dropped))


def dead_claims() -> list[tuple[str, dict]]:
    try:
        claims = file_claims.list_claims()
    except Exception:
        return []
    now = time.time()
    return [(key, entry) for key, entry in claims.items()
            if not file_claims.is_live(entry, now=now)]


def prunable_worktrees() -> list[str]:
    out = git("worktree", "list", check=False)
    return [line.split()[0] for line in out.splitlines() if "prunable" in line]


def stale_probe_dirs() -> list[Path]:
    roots = (REPO_ROOT / "disasm" / "probes", REPO_ROOT / "disasm" / "build" / "probes")
    cutoff = time.time() - float(os.environ.get("PRAGMA_PROBE_STALE_SECONDS", 3600))
    found: list[Path] = []
    for root in roots:
        if not root.is_dir():
            continue
        for child in root.glob(".pragma_probe_*"):
            try:
                if child.stat().st_mtime < cutoff:
                    found.append(child)
            except OSError:
                continue
    return found


def survey() -> dict[str, object]:
    accepted = provenance.accepted_functions()
    sources = []
    for path in dirty_sources():
        verdict, functions = classify_source(path, accepted)
        sources.append({"path": path, "verdict": verdict, "functions": functions})
    return {
        "sources": sources,
        "dead_claims": dead_claims(),
        "prunable_worktrees": prunable_worktrees(),
        "stale_probe_dirs": stale_probe_dirs(),
    }


def report(state: dict[str, object]) -> bool:
    """Print the survey. Returns True when anything needs attention."""
    dirty = False
    for entry in state["sources"]:
        verdict = entry["verdict"]
        if verdict == "no-pragma-change":
            print(f"  ok        {entry['path']} (edit drops no pragma)")
            continue
        dirty = True
        mark = "RECOVER" if verdict == "recoverable" else "ORPHAN "
        print(f"  {mark}   {entry['path']}")
        for function in entry["functions"]:
            suffix = "accepted on record" if verdict == "recoverable" else "NO accepted attempt"
            print(f"              {function} — {suffix}")
    for key, entry in state["dead_claims"]:
        dirty = True
        print(f"  DEAD      claim on {key} (owner {entry.get('owner')})")
    for path in state["prunable_worktrees"]:
        dirty = True
        print(f"  PRUNABLE  worktree {path}")
    for path in state["stale_probe_dirs"]:
        dirty = True
        print(f"  STALE     probe tree {path}")
    if not dirty:
        print("  nothing to clean")
    return dirty


def backup(path: str) -> Path:
    BACKUP_DIR.mkdir(exist_ok=True)
    stamp = time.strftime("%Y%m%dT%H%M%SZ", time.gmtime())
    target = BACKUP_DIR / f"{Path(path).name}.{stamp}"
    shutil.copy2(REPO_ROOT / path, target)
    return target


def clean(state: dict[str, object], revert_orphaned: bool) -> int:
    acted = 0

    for entry in state["sources"]:
        if entry["verdict"] != "orphaned":
            continue
        if not revert_orphaned:
            print(f"  kept      {entry['path']} (orphaned; pass --revert-orphaned to restore)")
            continue
        saved = backup(entry["path"])
        git("checkout", "HEAD", "--", entry["path"])
        print(f"  reverted  {entry['path']} (backup: {saved.relative_to(REPO_ROOT)})")
        acted += 1

    for entry in state["sources"]:
        if entry["verdict"] == "recoverable":
            print(f"  left      {entry['path']} — proven work, land it with integrate_fleet.py")

    for key, _ in state["dead_claims"]:
        try:
            file_claims.release(key, force=True)
            print(f"  released  dead claim on {key}")
            acted += 1
        except Exception as error:
            print(f"  WARN      could not release {key}: {error}")

    if state["prunable_worktrees"]:
        git("worktree", "prune", check=False)
        print(f"  pruned    {len(state['prunable_worktrees'])} worktree(s)")
        acted += 1

    for path in state["stale_probe_dirs"]:
        shutil.rmtree(path, ignore_errors=True)
        print(f"  removed   {path}")
        acted += 1

    return acted


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    sub.add_parser("scan", help="report stale state, change nothing")
    p_clean = sub.add_parser("clean", help="act on stale state")
    p_clean.add_argument(
        "--revert-orphaned", action="store_true",
        help="restore sources whose dropped pragmas have no accepted attempt "
             "(content is saved under .fleet-janitor-backups/ first)")
    p_clean.add_argument("--json", action="store_true", help="also print the survey as JSON")
    args = parser.parse_args(argv)

    state = survey()
    print(f"fleet janitor: {REPO_ROOT}")
    needs = report(state)
    if args.command == "scan":
        return 1 if needs else 0

    print()
    acted = clean(state, args.revert_orphaned)
    print(f"\n{acted} action(s) taken")
    if args.json:
        print(json.dumps({
            "sources": state["sources"],
            "dead_claims": [k for k, _ in state["dead_claims"]],
            "prunable_worktrees": state["prunable_worktrees"],
        }, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
