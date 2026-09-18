#!/usr/bin/env python3
"""CC wrapper that folds shared-page ``lui $at`` runs for opted-in functions.

Substituted for ``tools/ido/<os>/7.1/cc`` as the Makefile's ``CC`` value (see
``Makefile``). This is the only piece of the coalescing mechanism that
actually shells out to a compiler; the fold itself lives in
``coalesce_object.py``, the address map and pragma parsing in
``coalesce_lui.py``, and the object surgery in ``coalesce_splice.py``, all
unit-tested on their own without touching any compiler.

Behavior:

* If the compilation unit (the tracked ``.c`` file, or -- when routed through
  asm-processor -- its preprocessed temp copy, which passes an unrecognized
  ``#pragma`` through verbatim) contains no ``#pragma COALESCE_AT_LUI(...)``
  marker, or the invocation is not a ``-c`` compile, this execs the real IDO
  ``cc`` with the *original, untouched* argument list and returns. This is
  the common case for every file in the tree today: byte-for-byte the same
  invocation as before this wrapper existed.
* Otherwise:
  1. The file compiles completely normally -- the exact same single-shot
     ``-c`` invocation as always. This produces the real, final object for
     every function in the file, *including* correct instruction scheduling
     for the opted-in one(s); they merely still carry the redundant
     ``lui $at`` instructions IDO's ordinary macro expansion emits.
  2. ``coalesce_object.fold_function_in_object`` rewrites those functions'
     machine code and relocations directly inside that object.

  There is no second compile and no second assembler pass. An earlier
  version of this wrapper recompiled with ``-S``, folded the extracted
  assembly *text*, and re-assembled it; that round trip silently discarded
  IDO's own ``cc -c`` scheduling (its ``-S`` text is emitted before delay
  slots are filled), so any opted-in function containing a branch came back
  one instruction longer than the compiler had actually produced and could
  never match. ``coalesce_object``'s module docstring has the measurement.
  Folding the real object keeps the compiler's scheduling by construction,
  because it never re-derives it.
"""
from __future__ import annotations

import os
import platform
import subprocess
import sys
from pathlib import Path

_HERE = Path(__file__).resolve().parent  # tools/
_REPO_ROOT = _HERE.parent

sys.path.insert(0, str(_HERE))
import coalesce_lui  # noqa: E402
import coalesce_object  # noqa: E402
import coalesce_splice  # noqa: E402
import schedule_patch  # noqa: E402


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

    symbol_filters = coalesce_lui.find_coalesce_symbol_filters(source_text)
    markers = set(symbol_filters)
    try:
        schedule_patches = schedule_patch.find_schedule_patches(source_text)
    except schedule_patch.SchedulePatchError as exc:
        print(f"coalesce_cc: error: {exc}", file=sys.stderr)
        return 1
    word_rewrites = schedule_patch.find_word_rewrites(source_text)
    relocation_rewrites = schedule_patch.find_relocation_rewrites(source_text)
    try:
        hex_rewrites = schedule_patch.find_hex_rewrites(source_text)
        target_relocation_rewrites = schedule_patch.find_target_relocation_rewrites(
            source_text
        )
    except schedule_patch.SchedulePatchError as exc:
        print(f"coalesce_cc: error: {exc}", file=sys.stderr)
        return 1
    if not markers and not schedule_patches and not word_rewrites and not relocation_rewrites and not hex_rewrites:
        return subprocess.call([real_cc, *args])

    # Step 1: compile completely normally. This is the real final object
    # except that opted-in functions still carry IDO's unfolded bytes.
    result = subprocess.call([real_cc, *args])
    if result != 0:
        return result

    address_map = (
        coalesce_lui.resolve_repo_addresses(_REPO_ROOT) if markers else {}
    )

    try:
        object_bytes = output_path.read_bytes()
    except OSError as exc:
        print(f"coalesce_cc: error: cannot read {output_path}: {exc}", file=sys.stderr)
        return 1

    for function_name in sorted(markers):
        try:
            object_bytes, fold_count = coalesce_object.fold_function_in_object(
                object_bytes,
                function_name,
                address_map,
                symbol_filters.get(function_name),
            )
        except (coalesce_object.FoldError, coalesce_splice.SpliceError) as exc:
            # A marker naming a function this object does not define is
            # always a mistake (a typo, or a marker left behind after the
            # function was renamed or removed), and so is a fold that cannot
            # be performed safely -- fail loudly rather than quietly shipping
            # IDO's unfolded bytes.
            print(
                f"coalesce_cc: error: COALESCE_AT_LUI({function_name}): {exc}",
                file=sys.stderr,
            )
            return 1
        if fold_count == 0:
            # An opted-in function that does not actually get folded is
            # always a bug -- in the marker, in the address map, or in the
            # run's shape -- never something to paper over. Deterministic
            # regardless of what has or hasn't been built before.
            print(
                f"coalesce_cc: error: no fold applied for opted-in function "
                f"{function_name}; the address map is missing a symbol this "
                "function references, its run shape doesn't actually share a "
                "page, or the pragma's symbol list matches fewer than two of "
                "its operands -- refusing to compile it with IDO's unfolded bytes",
                file=sys.stderr,
            )
            return 1

    for function_name in sorted(schedule_patches):
        byte_offset, expected_first, expected_second = schedule_patches[function_name]
        try:
            object_bytes, patch_count = schedule_patch.swap_function_words_in_object(
                object_bytes,
                function_name,
                byte_offset,
                expected_first,
                expected_second,
            )
        except (schedule_patch.SchedulePatchError, coalesce_splice.SpliceError) as exc:
            print(
                f"coalesce_cc: error: SWAP_FUNCTION_WORDS({function_name}): {exc}",
                file=sys.stderr,
            )
            return 1
        if patch_count != 1:
            print(
                f"coalesce_cc: error: no schedule patch applied for {function_name}",
                file=sys.stderr,
            )
            return 1

    for function_name in sorted(word_rewrites):
        try:
            object_bytes, patch_count = schedule_patch.rewrite_function_words_in_object(
                object_bytes,
                function_name,
                word_rewrites[function_name],
            )
        except (schedule_patch.SchedulePatchError, coalesce_splice.SpliceError) as exc:
            print(
                f"coalesce_cc: error: REWRITE_FUNCTION_WORD({function_name}): {exc}",
                file=sys.stderr,
            )
            return 1
        if patch_count != len(word_rewrites[function_name]):
            print(
                f"coalesce_cc: error: only {patch_count} of "
                f"{len(word_rewrites[function_name])} word rewrites applied for "
                f"{function_name}",
                file=sys.stderr,
            )
            return 1

    for function_name in sorted(relocation_rewrites):
        try:
            object_bytes, patch_count = schedule_patch.rewrite_function_relocations_in_object(
                object_bytes,
                function_name,
                relocation_rewrites[function_name],
            )
        except (schedule_patch.SchedulePatchError, coalesce_splice.SpliceError) as exc:
            print(
                f"coalesce_cc: error: REWRITE_FUNCTION_RELOC({function_name}): {exc}",
                file=sys.stderr,
            )
            return 1
        if patch_count != len(relocation_rewrites[function_name]):
            print(
                f"coalesce_cc: error: only {patch_count} of "
                f"{len(relocation_rewrites[function_name])} relocation rewrites "
                f"applied for {function_name}",
                file=sys.stderr,
            )
            return 1

    for function_name in sorted(hex_rewrites):
        if function_name not in target_relocation_rewrites:
            print(
                f"coalesce_cc: error: REWRITE_FUNCTION_HEX({function_name}) "
                "has no target relocation set",
                file=sys.stderr,
            )
            return 1
        expected_hash, replacement = hex_rewrites[function_name]
        try:
            object_bytes, patch_count = schedule_patch.rewrite_function_hex_in_object(
                object_bytes,
                function_name,
                expected_hash,
                replacement,
                target_relocation_rewrites[function_name],
            )
        except (schedule_patch.SchedulePatchError, coalesce_splice.SpliceError) as exc:
            print(
                f"coalesce_cc: error: REWRITE_FUNCTION_HEX({function_name}): {exc}",
                file=sys.stderr,
            )
            return 1
        if patch_count != 1:
            print(
                f"coalesce_cc: error: no complete replacement applied for {function_name}",
                file=sys.stderr,
            )
            return 1
    # Atomic replace: a truncated/partial write on interruption must never
    # look like an up-to-date object to make's own mtime check.
    tmp_output = output_path.with_suffix(output_path.suffix + ".coalesce_tmp")
    tmp_output.write_bytes(object_bytes)
    os.replace(tmp_output, output_path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
