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

Bundle candidates are compiled first in isolated temporary source/object
paths.  Those probes run in parallel and never edit the live source.  Only
function-byte hits are tested sequentially in the live checkout with the
full linker/ROM comparison.  The first successful candidate for a function
is retained; later variants for that function are skipped.
"""

from __future__ import annotations

import os
import re
import shutil
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path


def source_object_path(source_path: Path) -> tuple[Path, Path]:
    repo_root = Path(__file__).resolve().parent.parent
    relative = source_path.resolve().relative_to(repo_root / "disasm")
    return repo_root, repo_root / "disasm" / "build" / relative.with_suffix(".o")


def _binutils_tool(name: str) -> str:
    prefix = os.environ.get(
        "MIPS_BINUTILS_PREFIX", "/Users/michaegg/homebrew/bin/mips-linux-gnu-"
    )
    return f"{prefix}{name}"


def _make_object(source_path: Path, *, capture: bool = False) -> tuple[int, Path, str]:
    """Compile one source file through the repository's normal object rule.

    Probe sources live below a hidden temporary directory next to the real
    source.  Their object/dependency files therefore have unique paths and do
    not contend with another probe or alter the tracked source.
    """
    repo_root = Path(__file__).resolve().parent.parent
    relative = source_path.resolve().relative_to(repo_root / "disasm")
    object_path = repo_root / "disasm" / "build" / relative.with_suffix(".o")
    object_path.parent.mkdir(parents=True, exist_ok=True)
    object_path.unlink(missing_ok=True)
    env = {
        **os.environ,
        "MIPS_BINUTILS_PREFIX": os.environ.get(
            "MIPS_BINUTILS_PREFIX", "/Users/michaegg/homebrew/bin/mips-linux-gnu-"
        ),
        "COMPARE": "0",
        "RUN_CC_CHECK": "0",
        "OBJDUMP_BUILD": "0",
        "COLOR": "0",
    }
    kwargs: dict[str, object] = {"cwd": repo_root, "env": env, "text": True}
    if capture:
        kwargs["stdout"] = subprocess.PIPE
        kwargs["stderr"] = subprocess.STDOUT
    result = subprocess.run(
        ["make", "-C", "disasm", str(object_path.relative_to(repo_root / "disasm"))],
        **kwargs,
    )
    output = result.stdout if capture and isinstance(result.stdout, str) else ""
    return result.returncode, object_path, output


def rebuild_source_object(source_path: Path) -> int:
    result, _, _ = _make_object(source_path)
    return result


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


def _object_text(object_path: Path) -> bytes | None:
    """Return the raw relocatable .text section from an object file."""
    with tempfile.TemporaryDirectory(prefix=".pragma_text_") as directory:
        output = Path(directory) / "text.bin"
        result = subprocess.run(
            [_binutils_tool("objcopy"), "--dump-section", f".text={output}", str(object_path)],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
        )
        if result.returncode != 0 or not output.exists():
            return None
        return output.read_bytes()


def _object_symbol(object_path: Path, function: str) -> tuple[int, int] | None:
    """Return a function's section offset and size from a relocatable object."""
    result = subprocess.run(
        [_binutils_tool("nm"), "-S", "--defined-only", str(object_path)],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    if result.returncode != 0:
        return None
    for line in result.stdout.splitlines():
        fields = line.split()
        if len(fields) < 4 or fields[-1] != function or fields[-2].upper() == "U":
            continue
        try:
            return int(fields[0], 16), int(fields[1], 16)
        except ValueError:
            return None
    return None


def _function_bytes(
    object_path: Path,
    function: str,
    span: int | None = None,
) -> bytes | None:
    symbol = _object_symbol(object_path, function)
    text = _object_text(object_path) if symbol is not None else None
    if symbol is None or text is None:
        return None
    offset, symbol_size = symbol
    size = symbol_size if span is None else span
    if size <= 0 or offset < 0 or offset + size > len(text):
        return None
    return text[offset : offset + size]


def _function_mismatch_details(
    object_path: Path,
    function: str,
    expected: bytes,
    actual: bytes | None,
) -> dict[str, object]:
    """Summarize a rejected probe without dumping the candidate object."""
    details: dict[str, object] = {"expected_size": len(expected)}
    symbol = _object_symbol(object_path, function)
    if symbol is not None:
        details["actual_size"] = symbol[1]
    if actual is None:
        details["first_diff_offset"] = None
        return details
    first_diff = next(
        (index for index, (left, right) in enumerate(zip(expected, actual)) if left != right),
        min(len(expected), len(actual)),
    )
    details["first_diff_offset"] = first_diff
    if first_diff < len(expected):
        details["expected_byte"] = f"{expected[first_diff]:02x}"
    if first_diff < len(actual):
        details["actual_byte"] = f"{actual[first_diff]:02x}"
    return details


def _replace_candidate_text(source: str, function: str, candidate: str) -> str | None:
    pragma = re.compile(
        rf'^#pragma GLOBAL_ASM\("asm/us/nonmatchings/[^\"]+/{re.escape(function)}\.s"\)$',
        re.MULTILINE,
    )
    replacement, count = pragma.subn(candidate.rstrip("\n"), source, count=1)
    return replacement if count == 1 else None


def _remove_probe_outputs(object_path: Path) -> None:
    """Remove the temporary object and files produced alongside it."""
    for path in (
        object_path,
        object_path.with_suffix(".d"),
        object_path.with_suffix(".asmproc.d"),
        object_path.with_suffix(".s"),
        object_path.with_suffix(".bin"),
    ):
        path.unlink(missing_ok=True)
    # Each probe gets its own hidden build directory.  Remove it when the
    # compiler left no additional artifacts behind; never touch a normal
    # repository build directory.
    if object_path.parent.name.startswith(".pragma_probe_"):
        try:
            object_path.parent.rmdir()
        except OSError:
            pass


def _probe_one(
    source_path: Path,
    function: str,
    candidate: str,
    expected: bytes | None,
) -> dict[str, object]:
    """Compile one candidate in an isolated temporary source/object pair."""
    baseline = source_path.read_text()
    replacement = _replace_candidate_text(baseline, function, candidate)
    if replacement is None:
        return {
            "status": "probe_unavailable",
            "probe_reason": "invalid_pragma",
        }

    temporary_directory = tempfile.TemporaryDirectory(
        prefix=".pragma_probe_", dir=source_path.parent
    )
    try:
        directory = Path(temporary_directory.name)
        temporary_source = directory / source_path.name
        temporary_source.write_text(replacement)
        result, object_path, output = _make_object(temporary_source, capture=True)
        try:
            if result != 0:
                return {
                    "status": "compile_failed",
                    "exit_code": result,
                    "diagnostic": output[-2000:],
                }
            # The assembler symbol size can include alignment nops while the
            # compiler's relocatable symbol size often stops at the delay
            # slot. Compare the candidate over the baseline owner's span so
            # alignment padding is validated instead of causing a false
            # probe rejection. The full ROM gate remains authoritative.
            actual = _function_bytes(object_path, function, len(expected))
            if expected is None or actual is None:
                return {
                    "status": "probe_unavailable",
                    "probe_reason": "missing_function_bytes",
                }
            if actual != expected:
                diagnostic = {
                    "status": "probe_rejected",
                    "probe_reason": "function_bytes_differ",
                }
                diagnostic.update(
                    _function_mismatch_details(object_path, function, expected, actual)
                )
                return diagnostic
            return {"status": "probe_match"}
        finally:
            _remove_probe_outputs(object_path)
    finally:
        temporary_directory.cleanup()


def probe_candidates(
    source_path: Path,
    blocks: list[tuple[str, str]],
    workers: int | None = None,
) -> list[dict[str, object]]:
    """Parallel-filter candidates without modifying the live source.

    This is only a cheap object-level filter.  A ``probe_match`` is still sent
    through the sequential full linker/ROM comparison before it can be kept.
    """
    results: list[dict[str, object]] = [
        {"index": index, "function": function, "status": "probe_unavailable"}
        for index, (function, _) in enumerate(blocks)
    ]
    try:
        _, baseline_object = source_object_path(source_path)
    except ValueError:
        return results

    if rebuild_source_object(source_path) != 0:
        return results
    expected = {
        function: _function_bytes(baseline_object, function)
        for function in {function for function, _ in blocks}
    }
    if any(value is None for value in expected.values()):
        return results

    if workers is None:
        try:
            workers = int(os.environ.get("PRAGMA_PROBE_WORKERS", "4"))
        except ValueError:
            workers = 4
    workers = max(1, min(workers, len(blocks) or 1))
    with ThreadPoolExecutor(max_workers=workers) as executor:
        futures = {
            executor.submit(
                _probe_one, source_path, function, candidate, expected[function]
            ): index
            for index, (function, candidate) in enumerate(blocks)
        }
        for future in as_completed(futures):
            index = futures[future]
            try:
                result = future.result()
            except Exception as error:  # pragma: no cover - defensive worker boundary
                result = {
                    "status": "probe_unavailable",
                    "probe_reason": "probe_error",
                    "diagnostic": str(error),
                }
            results[index].update(result)
            results[index]["index"] = index
            results[index]["function"] = blocks[index][0]
    return results


def try_candidates_detailed(
    source_path: Path,
    blocks: list[tuple[str, str]],
    *,
    probe_workers: int | None = None,
) -> dict[str, object]:
    """Try candidates and retain the first winner per function.

    Candidates are first compiled in isolated temporary source/object paths.
    Only candidates whose relocatable function bytes equal the baseline are
    sent through the sequential full linker/ROM comparison.  ``accepted`` is
    populated only after that final combined comparison also succeeds.
    """
    repo_root = Path(__file__).resolve().parent.parent
    baseline = source_path.read_text()
    accepted: dict[str, str] = {}
    accepted_indices: dict[str, int] = {}
    attempts = probe_candidates(source_path, blocks, workers=probe_workers)
    probe_unavailable = any(
        attempt["status"] == "probe_unavailable" for attempt in attempts
    )

    # If object-level probing is unavailable (for example in a synthetic unit
    # test or a missing toolchain), preserve the old conservative behavior and
    # send every candidate through the sequential full gate.
    eligible = [
        index for index, attempt in enumerate(attempts)
        if probe_unavailable or attempt["status"] == "probe_match"
    ]
    for index in eligible:
        function, candidate = blocks[index]
        attempt = attempts[index]
        if function in accepted:
            print(f"SKIPPED {function}: earlier candidate accepted")
            attempt.update({
                "status": "skipped",
                "reason": "earlier candidate accepted",
            })
            continue
        source_path.write_text(baseline)
        os.utime(source_path, None)
        rebuild_source_object(source_path)
        result, outcome = _try_candidate_detailed(source_path, function, candidate)
        attempt.update({
            "status": outcome,
            "exit_code": result,
            "probe_status": attempt.get("status"),
        })
        if result == 0:
            accepted[function] = candidate
            accepted_indices[function] = index

    # Probes are intentionally parallel, so variants after a winner may have
    # already compiled.  Report them as skipped for the same user-facing
    # semantics as the old sequential runner while retaining their probe
    # outcome in ``probe_status``.
    for index, (function, _) in enumerate(blocks):
        winner_index = accepted_indices.get(function)
        if winner_index is not None and index > winner_index:
            attempt = attempts[index]
            if attempt["status"] != "skipped":
                attempt.update({
                    "probe_status": attempt.get("status"),
                    "status": "skipped",
                    "reason": "earlier candidate accepted",
                })

    # No probe hit means no source edit was made and no linker invocation is
    # necessary.  This is the main speedup for large rejected candidate sets.
    if not accepted and not probe_unavailable:
        return {
            "status": 1,
            "accepted": [],
            "attempts": attempts,
            "batch_status": "no_candidate_accepted",
            "probe_workers": probe_workers,
        }

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
                "probe_workers": probe_workers,
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
            "probe_workers": probe_workers,
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
                "probe_workers": probe_workers,
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
            "probe_workers": probe_workers,
        }
    return {
        "status": 0,
        "accepted": list(accepted),
        "attempts": attempts,
        "batch_status": "accepted",
        "probe_workers": probe_workers,
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
