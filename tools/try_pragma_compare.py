#!/usr/bin/env python3
"""Try one C replacement for a GLOBAL_ASM pragma.

Usage:
    tools/try_pragma_compare.py disasm/src/229E0.c func_80025CBC candidate.c

The candidate file replaces exactly one pragma line.  A failed COMPARE=1
restores the source file byte-for-byte; a successful comparison keeps it.
"""

from __future__ import annotations

import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


def main() -> int:
    if len(sys.argv) != 4:
        print(__doc__.strip(), file=sys.stderr)
        return 2

    source_path = Path(sys.argv[1])
    function = sys.argv[2]
    candidate_path = Path(sys.argv[3])
    source = source_path.read_text()
    candidate = candidate_path.read_text().rstrip() + "\n"

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
        print(f"REJECTED {function}: restored GLOBAL_ASM")
    else:
        print(f"ACCEPTED {function}: source replacement kept")

    backup_path.unlink(missing_ok=True)
    return result.returncode


if __name__ == "__main__":
    raise SystemExit(main())
