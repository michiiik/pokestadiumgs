#!/usr/bin/env python3
"""CC wrapper that folds shared-page ``lui $at`` runs for opted-in functions.

Substituted for ``tools/ido/<os>/7.1/cc`` as the Makefile's ``CC`` value (see
``Makefile``). This is the only piece of the coalescing mechanism that
actually shells out to a compiler; the text transform lives in
``coalesce_lui.py`` and the object-level splice in ``coalesce_splice.py``,
both unit-tested on their own without touching any compiler.

Behavior:

* If the compilation unit (the tracked ``.c`` file, or -- when routed through
  asm-processor -- its preprocessed temp copy, which passes an unrecognized
  ``#pragma`` through verbatim) contains no ``#pragma COALESCE_AT_LUI(...)``
  marker, or the invocation is not a ``-c`` compile, this execs the real IDO
  ``cc`` with the *original, untouched* argument list and returns. This is
  the common case for every file in the tree today: byte-for-byte the same
  invocation as before this wrapper existed.
* Otherwise:
  1. The file compiles completely normally first -- the exact same
     single-shot ``-c`` invocation as always. This produces the real,
     final object for every function in the file *except* that the
     opted-in one(s) still have the unfolded (wrong) bytes IDO's ordinary
     macro expansion produces.
  2. A second, throwaway ``-S`` recompile of the same source gets IDO's
     assembly text so the opted-in function's own ``.ent``/``.end`` block
     can be extracted in isolation.
  3. ``coalesce_lui.fold_source`` folds just that extracted block, which
     is then assembled *by itself* with GNU ``as``.

     Why not just re-assemble the whole modified file with ``-c`` (as an
     earlier version of this wrapper did)? Because this project's IDO port
     mis-assembles ordinary compiler-generated numbered branch labels
     (``$32`` and friends -- present in essentially every function with an
     if/loop, completely unrelated to lui-coalescing) when a large,
     multi-function ``.s`` is fed back through its assemble-only path, even
     with zero fold applied. That path is only safe for a small,
     branch-free snippet -- exactly the shape a foldable function has, and
     exactly what gets extracted and assembled alone here.
  4. ``coalesce_splice.splice_function`` copies just that function's
     ``.text`` bytes and relocations from the small GNU-as object into the
     normally-compiled object from step 1, leaving every other byte
     (every other function, all of its relocations, the symbol table)
     untouched.
"""
from __future__ import annotations

import os
import platform
import subprocess
import sys
import tempfile
import uuid
from pathlib import Path

_HERE = Path(__file__).resolve().parent  # tools/
_REPO_ROOT = _HERE.parent

sys.path.insert(0, str(_HERE))
import coalesce_lui  # noqa: E402
import coalesce_splice  # noqa: E402


def _detected_os() -> str:
    system = platform.system()
    if system == "Darwin":
        return "macos"
    if system == "Linux":
        return "linux"
    raise RuntimeError(f"coalesce_cc: unsupported host OS {system!r}")


def _real_cc() -> str:
    override = os.environ.get("COALESCE_REAL_CC")
    if override:
        return override
    return str(_REPO_ROOT / "tools" / "ido" / _detected_os() / "7.1" / "cc")


def _as_binary() -> str:
    # Mirrors the Makefile's own `AS := $(MIPS_BINUTILS_PREFIX)as`, same
    # default, so this never needs a machine-specific path of its own.
    prefix = os.environ.get("MIPS_BINUTILS_PREFIX", "mips-linux-gnu-")
    return prefix + "as"


def _fold_and_splice_one(
    function_name: str,
    asm_text: str,
    extern_sizes: dict[str, int],
    address_map: dict[str, int],
    outer_bytes: bytes,
) -> bytes | None:
    """Fold, assemble, and splice one opted-in function. ``None`` on failure.

    Both failure branches below used to warn and fall back to leaving IDO's
    unfolded bytes in place -- which meant an explicitly opted-in function
    could silently compile *wrong* (in particular: the address map's
    linked-``.map`` fallback in ``coalesce_lui.resolve_repo_addresses`` is
    only populated after some prior build has produced one, so the exact
    same source could fold on an incremental build and silently not fold on
    a clean one). A function named by ``#pragma COALESCE_AT_LUI(...)`` that
    doesn't actually get folded is always a bug -- in the marker, in the
    address map, or in the fold logic -- never something to paper over, so
    both cases are hard failures now: deterministic regardless of what has
    or hasn't been built before.
    """
    block = coalesce_lui.extract_function_block(asm_text, function_name)
    if block is None:
        print(
            f"coalesce_cc: error: COALESCE_AT_LUI names a function IDO never "
            f"emitted: {function_name}",
            file=sys.stderr,
        )
        return None

    folded_block, fold_count = coalesce_lui.fold_source(
        block, {function_name}, address_map
    )
    if fold_count == 0:
        print(
            f"coalesce_cc: error: no fold applied for opted-in function "
            f"{function_name}; the address map is missing a symbol this "
            "function references, or its run shape doesn't actually share "
            "a page -- refusing to compile it with IDO's unfolded bytes",
            file=sys.stderr,
        )
        return None

    snippet = coalesce_lui.prepare_snippet_for_gnu_as(folded_block, extern_sizes)

    with tempfile.TemporaryDirectory(prefix="coalesce_cc_") as tmp:
        tmp_path = Path(tmp)
        snippet_path = tmp_path / f"{function_name}.s"
        snippet_path.write_text(snippet, encoding="latin1")
        inner_obj = tmp_path / f"{function_name}.o"
        as_result = subprocess.call(
            [
                _as_binary(),
                "-march=vr4300",
                "-32",
                "-G0",
                "-EB",
                "-o",
                str(inner_obj),
                str(snippet_path),
            ]
        )
        if as_result != 0:
            print(
                f"coalesce_cc: error: GNU as failed assembling the folded "
                f"form of {function_name}",
                file=sys.stderr,
            )
            return None
        inner_bytes = inner_obj.read_bytes()

    try:
        return coalesce_splice.splice_function(outer_bytes, inner_bytes, function_name)
    except coalesce_splice.SpliceError as error:
        print(f"coalesce_cc: error: {error}", file=sys.stderr)
        return None
    except Exception as error:  # noqa: BLE001 - never let an internal bug in
        # the splice/ELF-parsing code surface as a bare, unexplained Python
        # traceback from a Makefile recipe; a clean compile failure with a
        # message pointing at the responsible function is strictly better
        # than that, even for a bug this broad catch doesn't have a more
        # specific name for yet.
        print(
            f"coalesce_cc: error: splicing {function_name} raised "
            f"{type(error).__name__}: {error}",
            file=sys.stderr,
        )
        return None


def main(argv: list[str]) -> int:
    real_cc = _real_cc()
    args = argv[1:]

    if "-o" not in args or "-c" not in args or not args:
        # Not a normal compile-to-object invocation (e.g. a bare probe using
        # -S/-E directly) -- never our business, pass through untouched.
        return subprocess.call([real_cc, *args])

    out_index = args.index("-o")
    output_path = Path(args[out_index + 1])
    input_path = Path(args[-1])

    try:
        # latin1 is a lossless 1:1 byte<->codepoint mapping: IDO/asm-processor
        # output (and this game's own source, which carries non-ASCII text
        # in places) isn't guaranteed UTF-8, and errors="ignore" would
        # silently drop bytes rather than round-trip them intact.
        source_text = input_path.read_text(encoding="latin1")
    except OSError:
        source_text = ""

    markers = coalesce_lui.find_coalesce_markers(source_text)
    if not markers:
        return subprocess.call([real_cc, *args])

    # Step 1: compile completely normally. This is the real final object
    # except that opted-in functions still carry IDO's unfolded bytes.
    result = subprocess.call([real_cc, *args])
    if result != 0:
        return result

    address_map = coalesce_lui.resolve_repo_addresses(_REPO_ROOT)

    # Step 2: a throwaway -S recompile of the same source, purely to extract
    # the opted-in function(s)' own .ent/.end block(s) in isolation. This
    # IDO port's `-S` mode does not honor `-o` (always writes
    # `<cwd>/<input-basename-stem>.s`), so a uniquely named temp copy of the
    # source -- placed next to the real file so relative `-I` search paths
    # keep resolving exactly as they would for the original -- both avoids
    # racing a concurrent `make -j` job compiling a same-named file
    # elsewhere, and gives a collision-free, predictable output name.
    unique_stem = f".coalesce_{uuid.uuid4().hex}"
    temp_source = input_path.parent / f"{unique_stem}{input_path.suffix}"
    predicted_asm = Path.cwd() / f"{unique_stem}.s"
    try:
        temp_source.write_text(source_text, encoding="latin1")
        s_args = list(args)
        s_args[s_args.index("-c")] = "-S"
        s_args[out_index + 1] = str(predicted_asm)  # ignored by -S, kept for clarity
        s_args[-1] = str(temp_source)
        s_result = subprocess.call([real_cc, *s_args])
        if s_result != 0:
            print(
                "coalesce_cc: error: the -S recompile used to extract "
                "opted-in function(s) for lui-coalescing failed",
                file=sys.stderr,
            )
            return s_result
        if not predicted_asm.is_file():
            print(
                "coalesce_cc: error: expected IDO -S output at "
                f"{predicted_asm} was not produced",
                file=sys.stderr,
            )
            return 1

        asm_text = predicted_asm.read_text(encoding="latin1")
        extern_sizes = coalesce_lui.parse_extern_sizes(asm_text)

        seen = coalesce_lui.functions_defined(asm_text)
        missing = markers - seen
        if missing:
            # A marker naming a function IDO never emitted is always a
            # mistake (a typo, or a marker left behind after the function
            # was renamed/removed) -- fail loudly rather than silently
            # compiling the rest of the file and dropping the marker.
            print(
                "coalesce_cc: error: COALESCE_AT_LUI names never defined in "
                f"this compile unit: {', '.join(sorted(missing))}",
                file=sys.stderr,
            )
            return 1

        outer_bytes = output_path.read_bytes()
        for function_name in sorted(markers):
            outer_bytes = _fold_and_splice_one(
                function_name, asm_text, extern_sizes, address_map, outer_bytes
            )
            if outer_bytes is None:
                return 1
        # Atomic replace: a truncated/partial write on interruption must
        # never look like an up-to-date object to make's own mtime check.
        tmp_output = output_path.with_suffix(output_path.suffix + ".coalesce_tmp")
        tmp_output.write_bytes(outer_bytes)
        os.replace(tmp_output, output_path)
        return 0
    finally:
        temp_source.unlink(missing_ok=True)
        predicted_asm.unlink(missing_ok=True)


if __name__ == "__main__":
    sys.exit(main(sys.argv))
