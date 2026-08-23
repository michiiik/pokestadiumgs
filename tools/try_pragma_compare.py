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

Bundle candidates are deliberately tested sequentially in the live checkout;
parallel testing requires isolated build trees and is a separate mode.
"""

from __future__ import annotations

import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


def try_candidate(source_path: Path, function: str, candidate: str) -> int:
    source = source_path.read_text()
    candidate = candidate.rstrip() + "\n"

    pragma = re.compile(
        rf'^#pragma GLOBAL_ASM\("asm/us/nonmatchings/[^\"]+/{re.escape(function)}\.s"\)$',
        re.MULTILINE,
    )
    source_after, count = pragma.subn(candidate.rstrip("\n"), source, count=1)
    if count != 1:
        print(f"could not find exactly one pragma for {function}", file=sys.stderr)
        return 2

    with tempfile.NamedTemporaryFile(
        mode="w", encoding="utf-8", dir=source_path.parent, delete=False
    ) as tmp:
        tmp.write(source)
        backup_path = Path(tmp.name)

    source_path.write_text(source_after)
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
        # The candidate compile can finish within the same filesystem
        # timestamp tick as the restore.  Force make to rebuild the restored
        # object instead of reusing the rejected candidate object.
        os.utime(source_path, None)
        print(f"REJECTED {function}: restored GLOBAL_ASM")
    else:
        print(f"ACCEPTED {function}: source replacement kept")

    backup_path.unlink(missing_ok=True)
    return result.returncode


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
        result = 0
        for function, candidate in blocks:
            result |= try_candidate(source_path, function, candidate)
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
