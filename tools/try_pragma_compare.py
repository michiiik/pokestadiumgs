#!/usr/bin/env python3
"""Try C replacements for GLOBAL_ASM pragmas.

Usage:
    tools/try_pragma_compare.py disasm/src/229E0.c func_80025CBC candidate.c
    tools/try_pragma_compare.py --bundle disasm/src/229E0.c candidates.txt

The single-candidate form replaces exactly one pragma line.  A failed
COMPARE=1 restores the source file byte-for-byte; a successful comparison
keeps it.  The candidate file is deleted after the attempt unless
--keep-candidate is passed.

Bundle files contain blocks of this form, which are tested independently:

    /* candidate: func_80025D44 */
    extern s32 func_80019378(void);
    s32 func_80025D44(void) { return func_80019378(); }
    /* end candidate */

Bundle candidates are tested sequentially in the live checkout.  Every test
starts from the same baseline, and only the first successful candidate for a
function is retained; later variants for that function are skipped.
"""

from __future__ import annotations

import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


def source_object_path(source_path: Path) -> tuple[Path, Path]:
    repo_root = Path(__file__).resolve().parent.parent
    relative = source_path.resolve().relative_to(repo_root / "disasm")
    return repo_root, repo_root / "disasm" / "build" / relative.with_suffix(".o")


def rebuild_source_object(source_path: Path) -> int:
    repo_root, object_path = source_object_path(source_path)
    object_path.unlink(missing_ok=True)
    result = subprocess.run(
        ["make", "-C", "disasm", str(object_path.relative_to(repo_root / "disasm"))],
        cwd=repo_root,
        env={**os.environ, "MIPS_BINUTILS_PREFIX": os.environ.get(
            "MIPS_BINUTILS_PREFIX", "/Users/michaegg/homebrew/bin/mips-linux-gnu-"
        )},
        text=True,
    )
    return result.returncode


def invalidate_link_outputs(repo_root: Path) -> None:
    build = repo_root / "disasm" / "build"
    for name in ("pokestadiumgs-us.elf", "pokestadiumgs-us.z64", "pokestadiumgs-us.map"):
        (build / name).unlink(missing_ok=True)


def try_candidate(source_path: Path, function: str, candidate: str) -> int:
    result, _ = _try_candidate_detailed(source_path, function, candidate)
    return result


def _try_candidate_detailed(source_path: Path, function: str, candidate: str) -> tuple[int, str]:
    """Run one candidate and identify the phase that accepted or rejected it."""
    source = source_path.read_text()
    candidate = candidate.rstrip() + "\n"

    pragma = re.compile(
        rf'^#pragma GLOBAL_ASM\("asm/us/nonmatchings/[^\"]+/{re.escape(function)}\.s"\)$',
        re.MULTILINE,
    )
    source_after, count = pragma.subn(candidate.rstrip("\n"), source, count=1)
    if count != 1:
        print(f"could not find exactly one pragma for {function}", file=sys.stderr)
        return 2, "invalid_pragma"

    with tempfile.NamedTemporaryFile(
        mode="w", encoding="utf-8", dir=source_path.parent, delete=False
    ) as tmp:
        tmp.write(source)
        backup_path = Path(tmp.name)

    source_path.write_text(source_after)
    if rebuild_source_object(source_path) != 0:
        source_path.write_text(source)
        rebuild_source_object(source_path)
        backup_path.unlink(missing_ok=True)
        return 2, "compile_failed"
    invalidate_link_outputs(Path(__file__).resolve().parent.parent)
    env = os.environ.copy()
    env.setdefault("MIPS_BINUTILS_PREFIX", "/Users/michaegg/homebrew/bin/mips-linux-gnu-")
    result = subprocess.run(
        ["make", "-C", "disasm", "COMPARE=1", "-j2"],
        cwd=Path(__file__).resolve().parent.parent,
        env=env,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
    )
    print(result.stdout, end="")

    if result.returncode != 0:
        shutil.copyfile(backup_path, source_path)
        # Force make to rebuild the restored object instead of reusing the
        # rejected candidate object, regardless of filesystem timestamp
        # resolution.
        os.utime(source_path, None)
        rebuild_source_object(source_path)
        print(f"REJECTED {function}: restored GLOBAL_ASM")
        outcome = "compare_rejected"
    else:
        print(f"ACCEPTED {function}: source replacement kept")
        outcome = "accepted"

    backup_path.unlink(missing_ok=True)
    return result.returncode, outcome


def compare_current_tree(repo_root: Path) -> int:
    invalidate_link_outputs(repo_root)
    env = os.environ.copy()
    env.setdefault("MIPS_BINUTILS_PREFIX", "/Users/michaegg/homebrew/bin/mips-linux-gnu-")
    result = subprocess.run(
        ["make", "-C", "disasm", "COMPARE=1", "-j2"],
        cwd=repo_root,
        env=env,
        text=True,
    )
    return result.returncode


def try_candidates_detailed(source_path: Path, blocks: list[tuple[str, str]]) -> dict[str, object]:
    """Try candidates and retain the first winner per function.

    ``attempts`` records whether each hypothesis compiled, compared, or was
    skipped.  ``accepted`` is only populated when the final combined compare
    also keeps the batch in the source tree.
    """
    repo_root = Path(__file__).resolve().parent.parent
    baseline = source_path.read_text()
    accepted: dict[str, str] = {}
    attempts: list[dict[str, object]] = []
    for index, (function, candidate) in enumerate(blocks):
        if function in accepted:
            print(f"SKIPPED {function}: earlier candidate accepted")
            attempts.append({
                "index": index,
                "function": function,
                "status": "skipped",
                "reason": "earlier candidate accepted",
            })
            continue
        source_path.write_text(baseline)
        os.utime(source_path, None)
        rebuild_source_object(source_path)
        result, outcome = _try_candidate_detailed(source_path, function, candidate)
        attempts.append({
            "index": index,
            "function": function,
            "status": outcome,
            "exit_code": result,
        })
        if result == 0:
            accepted[function] = candidate

    combined = baseline
    for function, candidate in accepted.items():
        pragma = re.compile(
            rf'^#pragma GLOBAL_ASM\("asm/us/nonmatchings/[^"]+/{re.escape(function)}\.s"\)$',
            re.MULTILINE,
        )
        combined, count = pragma.subn(candidate.rstrip("\n"), combined, count=1)
        if count != 1:
            source_path.write_text(baseline)
            os.utime(source_path, None)
            rebuild_source_object(source_path)
            return {
                "status": 2,
                "accepted": [],
                "attempts": attempts,
                "batch_status": "invalid_pragma",
            }
    source_path.write_text(combined)
    os.utime(source_path, None)
    if rebuild_source_object(source_path) != 0:
        source_path.write_text(baseline)
        os.utime(source_path, None)
        rebuild_source_object(source_path)
        return {
            "status": 2,
            "accepted": [],
            "attempts": attempts,
            "batch_status": "combined_compile_failed",
        }
    if accepted:
        print(f"checking {len(accepted)} accepted candidate(s) together")
        result = compare_current_tree(repo_root)
        if result != 0:
            source_path.write_text(baseline)
            os.utime(source_path, None)
            rebuild_source_object(source_path)
            print("combined candidate batch rejected: restored baseline")
            return {
                "status": result,
                "accepted": [],
                "attempts": attempts,
                "batch_status": "combined_compare_rejected",
            }
    else:
        source_path.write_text(baseline)
        os.utime(source_path, None)
        rebuild_source_object(source_path)
        compare_current_tree(repo_root)
        print("no candidate accepted")
        return {
            "status": 1,
            "accepted": [],
            "attempts": attempts,
            "batch_status": "no_candidate_accepted",
        }
    return {
        "status": 0,
        "accepted": list(accepted),
        "attempts": attempts,
        "batch_status": "accepted",
    }


def try_candidates(source_path: Path, blocks: list[tuple[str, str]]) -> tuple[int, list[str]]:
    """Compatibility wrapper returning the historical two-tuple."""
    result = try_candidates_detailed(source_path, blocks)
    return int(result["status"]), list(result["accepted"])


def main() -> int:
    keep_candidate = "--keep-candidate" in sys.argv
    args = [arg for arg in sys.argv[1:] if arg != "--keep-candidate"]

    if len(args) == 3 and args[0] == "--bundle":
        source_path = Path(args[1])
        bundle_path = Path(args[2])
        bundle = bundle_path.read_text()
        blocks = re.findall(
            r"/\*\s*candidate:\s*([A-Za-z_]\w*)\s*\*/(.*?)/\*\s*end candidate\s*\*/",
            bundle,
            flags=re.DOTALL,
        )
        if not blocks:
            print("candidate bundle contains no candidate blocks", file=sys.stderr)
            return 2
        result, _ = try_candidates(source_path, blocks)
        if not keep_candidate:
            bundle_path.unlink(missing_ok=True)
        return result

    if len(args) == 3:
        source_path = Path(args[0])
        function = args[1]
        candidate_path = Path(args[2])
        result = try_candidate(source_path, function, candidate_path.read_text())
        if not keep_candidate:
            candidate_path.unlink(missing_ok=True)
        return result

    print(__doc__.strip(), file=sys.stderr)
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
