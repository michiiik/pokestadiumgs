#!/usr/bin/env python3
"""Run decomp-permuter on a near-match candidate without touching tracked source.

Given an owner source, a function, and a C body that already compiles, this
builds a permuter working directory (preprocessed ``base.c`` reduced to the
target function, a ``compile.sh`` that invokes IDO with the Makefile's flags,
and a single-function ``target.o`` assembled from the pragma's ``.s``), then
lets the permuter mutate the body for a bounded wall-clock budget.

Usage:
    tools/permute_candidate.py func_8410AE50 candidate.c --seconds 60 --threads 4

The result lists the best-scoring sources (score 0 means the permuter's
instruction diff is empty).  A score-0 body is still only a candidate: send it
through ``try_pragma_candidates`` for the byte-level probe and the ROM gate.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import shlex
import shutil
import signal
import subprocess
import sys
import tempfile
import threading
import time
from pathlib import Path

import pragma_targets as targets
import try_pragma_compare as runner

REPO_ROOT = targets.REPO_ROOT
DISASM_ROOT = targets.DISASM_ROOT
PERMUTER_ROOT = DISASM_ROOT / "tools" / "decomp-permuter"
PERMUTER_VENV_PYTHON = DISASM_ROOT / "tools" / "decomp-venv" / "bin" / "python3"
WORK_ROOT = DISASM_ROOT / "build" / "permuter"

BASE_SCORE_RE = re.compile(r"base score = (\d+)")
OUTPUT_DIR_RE = re.compile(r"^output-(\d+)-(\d+)$")


def _permuter_root() -> Path:
    return targets.readonly_tool_path(
        Path("disasm/tools/decomp-permuter"), override_name="PRAGMA_PERMUTER_ROOT"
    )


def _permuter_venv_python() -> Path:
    # follow_symlinks=False is load-bearing: this is a venv interpreter, and
    # resolving it to the system Python it points at silently drops the venv's
    # site-packages (see readonly_tool_path).
    return targets.readonly_tool_path(
        Path("disasm/tools/decomp-venv/bin/python3"),
        override_name="PRAGMA_PERMUTER_VENV_PYTHON",
        follow_symlinks=False,
    )


def _permuter_python() -> str:
    override = os.environ.get("PERMUTER_PYTHON")
    if override:
        expanded = os.path.expandvars(os.path.expanduser(override))
        if os.sep in expanded and not os.path.isabs(expanded):
            return str((REPO_ROOT / expanded).resolve(strict=False))
        return expanded
    python = _permuter_venv_python()
    if python.is_file() and os.access(python, os.X_OK):
        return str(python)
    return sys.executable


def _split_recipe(recipe: list[str]) -> tuple[str, list[str]]:
    """Split the asm-processor probe recipe into the IDO binary and its flags.

    The recipe has the shape ``python build.py <asmproc flags> <cc> -- <as
    flags> -- <cc flags> -o OBJ SRC``.  The permuter's ``base.c`` never
    contains ``GLOBAL_ASM`` pragmas, so IDO can be invoked directly.
    """
    separators = [index for index, token in enumerate(recipe) if token == "--"]
    if len(separators) < 2:
        raise ValueError("unexpected probe recipe shape")
    compiler = recipe[separators[0] - 1]
    flags: list[str] = []
    tail = recipe[separators[1] + 1:]
    skip_next = False
    for token in tail:
        if skip_next:
            skip_next = False
            continue
        if token == "-o":
            skip_next = True
            continue
        if token in {runner._RECIPE_SOURCE, runner._RECIPE_OBJECT}:
            continue
        flags.append(token)
    return compiler, flags


def compile_script_text(compiler: str, flags: list[str], include_directory: str) -> str:
    """Render ``compile.sh``; the permuter calls it as ``compile.sh in.c -o out.o``."""
    rendered = " ".join(
        shlex.quote(token.replace(runner._RECIPE_DIRECTORY, include_directory)) for token in flags
    )
    return (
        "#!/bin/sh\n"
        f"cd {shlex.quote(str(DISASM_ROOT))}\n"
        f"exec {shlex.quote(compiler)} {rendered} \"$@\"\n"
    )


def _strip_other_functions(source: str, function: str, permuter_root: Path) -> str:
    # Loading the shared helper as an import can create ``__pycache__`` in the
    # primary checkout. Compile the immutable source directly so all shared
    # tool trees remain read-only even under a fresh linked worktree.
    helper = permuter_root / "strip_other_fns.py"
    namespace: dict[str, object] = {"__name__": "_pragma_strip_other_fns"}
    exec(compile(helper.read_text(), str(helper), "exec"), namespace)
    strip = namespace.get("strip_other_fns")
    if not callable(strip):
        raise RuntimeError(f"invalid decomp-permuter helper: {helper}")
    stripped = strip(source, function)
    if not isinstance(stripped, str):
        raise RuntimeError(f"invalid decomp-permuter helper result: {helper}")
    return "\n".join(
        line for line in stripped.splitlines() if not line.startswith("#pragma GLOBAL_ASM")
    ) + "\n"


def build_work_directory(
    owner: targets.Owner,
    code: str,
    *,
    declarations: str | None = None,
    work_root: Path | None = None,
) -> Path:
    """Materialize base.c, compile.sh, target.o, and function.txt for the permuter."""
    permuter_root = _permuter_root()
    if not permuter_root.is_dir():
        raise FileNotFoundError(
            f"decomp-permuter is not installed at {permuter_root}; run tools/setup_decomp_tools.sh"
        )
    recipes = runner._probe_recipes(REPO_ROOT)
    if recipes["compile"] is None or recipes["check"] is None:
        raise RuntimeError("could not capture the Makefile probe recipes with make -n")

    candidate = runner._declaration_prefix(declarations) + code.rstrip() + "\n"
    substituted = runner._replace_candidate_text(owner.source_path.read_text(), owner.function, candidate)
    if substituted is None:
        raise ValueError(f"{owner.source} does not contain exactly one pragma for {owner.function}")

    work_root = work_root or WORK_ROOT
    work_root.mkdir(parents=True, exist_ok=True)
    work_dir = Path(tempfile.mkdtemp(prefix=f"{owner.function}-", dir=work_root))
    source_rel = owner.source_path.relative_to(DISASM_ROOT)
    include_directory = source_rel.parent.as_posix() + "/"
    substituted_path = work_dir / source_rel.name
    substituted_path.write_text(substituted)

    preprocess = runner.host_preprocess_command(recipes["check"], include_directory) + [str(substituted_path)]
    result = subprocess.run(
        preprocess,
        cwd=DISASM_ROOT,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        timeout=runner._command_timeout("PRAGMA_COMPILE_TIMEOUT", 120.0),
    )
    if result.returncode != 0:
        raise RuntimeError(f"host preprocess failed:\n{result.stderr[-2000:]}")
    (work_dir / "base.c").write_text(
        _strip_other_functions(result.stdout, owner.function, permuter_root)
    )

    compiler, flags = _split_recipe(recipes["compile"])
    script = work_dir / "compile.sh"
    script.write_text(compile_script_text(compiler, flags, include_directory))
    script.chmod(0o755)

    target_s = work_dir / "target.s"
    target_s.write_text(
        (permuter_root / "prelude.inc").read_text() + owner.asm_path.read_text()
    )
    assemble = subprocess.run(
        [runner._binutils_tool("as"), "-march=vr4300", "-mabi=32", str(target_s), "-o", str(work_dir / "target.o")],
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
    )
    if assemble.returncode != 0:
        raise RuntimeError(f"assembling target failed:\n{assemble.stdout[-2000:]}")
    (work_dir / "function.txt").write_text(owner.function)
    return work_dir


def extract_function(code: str, function: str) -> str:
    """Return only ``function``'s definition from a permuter output file.

    ``--no-context-output`` drops declarations above the function, but the
    stripped base still carries prototypes for later owners below it.  A
    candidate for the runner should be the body alone.
    """
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
                return code[match.start():index + 1].strip() + "\n"
        index += 1
    return code


NOISE_RE = re.compile(r"resource_tracker|warnings\.warn|leaked semaphore")


def _collect_outputs(work_dir: Path, function: str, limit: int) -> list[dict[str, object]]:
    outputs: list[dict[str, object]] = []
    for entry in work_dir.iterdir():
        match = OUTPUT_DIR_RE.match(entry.name)
        if not match or not entry.is_dir():
            continue
        source = entry / "source.c"
        if not source.exists():
            continue
        outputs.append({
            "score": int(match.group(1)),
            "code": extract_function(source.read_text(), function),
            "diff": (entry / "diff.txt").read_text()[-4000:] if (entry / "diff.txt").exists() else None,
        })
    outputs.sort(key=lambda item: (int(item["score"]), len(str(item["code"]))))
    return outputs[:limit]


def permute(
    function: str,
    code: str,
    *,
    seconds: float = 60.0,
    threads: int = 4,
    declarations: str | None = None,
    stop_on_zero: bool = True,
    keep: bool = False,
    limit: int = 5,
) -> dict[str, object]:
    """Run the permuter for at most ``seconds`` and return the best outputs."""
    owner = targets.require_owner(function)
    work_dir = build_work_directory(owner, code, declarations=declarations)
    permuter_root = _permuter_root()
    command = [
        _permuter_python(),
        str(permuter_root / "permuter.py"),
        str(work_dir),
        "-j",
        str(max(1, threads)),
        "--best-only",
        "--no-context-output",
        "--quiet",
    ]
    if stop_on_zero:
        command.append("--stop-on-zero")
    started = time.monotonic()
    process = subprocess.Popen(
        command,
        cwd=work_dir,
        env=targets.readonly_tool_environment(),
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        start_new_session=True,
    )
    timed_out = False

    def _killer() -> None:
        nonlocal timed_out
        remaining = seconds - (time.monotonic() - started)
        try:
            process.wait(timeout=max(0.0, remaining))
        except subprocess.TimeoutExpired:
            timed_out = True
            try:
                os.killpg(process.pid, signal.SIGTERM)
            except ProcessLookupError:
                pass

    killer = threading.Thread(target=_killer, daemon=True)
    killer.start()
    log_lines: list[str] = []
    base_score: int | None = None
    already_matching = False
    assert process.stdout is not None
    for line in process.stdout:
        log_lines.append(line.rstrip("\n"))
        match = BASE_SCORE_RE.search(line)
        if match and base_score is None:
            base_score = int(match.group(1))
            if base_score == 0:
                # Nothing to permute: the supplied body already diffs clean.
                already_matching = True
                try:
                    os.killpg(process.pid, signal.SIGTERM)
                except ProcessLookupError:
                    pass
    process.wait()
    killer.join(timeout=1.0)
    outputs = _collect_outputs(work_dir, owner.function, limit)
    log_lines = [line for line in log_lines if line.strip() and not NOISE_RE.search(line)]
    result: dict[str, object] = {
        **owner.as_dict(),
        "base_score": base_score,
        "already_matching": already_matching,
        "best_score": outputs[0]["score"] if outputs else base_score,
        "outputs": outputs,
        "timed_out": timed_out,
        "elapsed_seconds": round(time.monotonic() - started, 1),
        "work_dir": str(work_dir.relative_to(REPO_ROOT)) if keep else None,
        "log_tail": log_lines[-20:],
    }
    if not keep:
        shutil.rmtree(work_dir, ignore_errors=True)
    return result


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("function")
    parser.add_argument("candidate", type=Path, help="file containing the C body (and its externs)")
    parser.add_argument("--declarations", type=Path, help="file with shared extern/prototype lines")
    parser.add_argument("--seconds", type=float, default=60.0)
    parser.add_argument("--threads", type=int, default=4)
    parser.add_argument("--keep", action="store_true", help="keep the work directory under disasm/build/permuter")
    parser.add_argument("--no-stop-on-zero", action="store_true")
    args = parser.parse_args()
    result = permute(
        args.function,
        args.candidate.read_text(),
        seconds=args.seconds,
        threads=args.threads,
        declarations=args.declarations.read_text() if args.declarations else None,
        stop_on_zero=not args.no_stop_on_zero,
        keep=args.keep,
    )
    print(json.dumps(result, indent=2))
    return 0 if result["best_score"] == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
