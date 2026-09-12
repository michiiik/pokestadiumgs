#!/usr/bin/env python3
"""
make_asm_worklist.py

Build a "what's left" tracker for the Pokémon Stadium 2 decomp: a single,
self-contained HTML page listing every function still stuck as a
``#pragma GLOBAL_ASM`` stub, with its target MIPS assembly inlined so you can
read it off while waiting on resets. No compiler, no server, no Docker.

Run from inside WSL, pointing at the disasm checkout that has already done
``make extract`` (so ``asm/us/nonmatchings/...`` exists):

    python3 make_asm_worklist.py --disasm ~/pokemonStadiumGSRecompPrivate/disasm

It writes ``asm_worklist.html`` in the current directory. Open it in a browser.

Why this and not objdiff: objdiff is a byte-diff tool. A ``#pragma GLOBAL_ASM``
stub assembles to the exact ROM bytes, so objdiff reports 100% "match" and has
no notion of "still needs decompiling". The stubs themselves are the worklist,
and their ``.s`` files are the assembly you need to attempt.
"""

import argparse
import html
import re
import sys
from pathlib import Path

# Matches: #pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_80006540.s")
PRAGMA_RE = re.compile(r'#\s*pragma\s+GLOBAL_ASM\s*\(\s*"([^"]+\.s)"\s*\)')


def collect_stubs(disasm: Path, region: str):
    """Return a list of (owner_c_rel, line, func, asm_rel, asm_path).

    Only includes stubs for ``region`` (``asm/<region>/nonmatchings/...``),
    because the source tree carries stubs for every region but the build
    only compiles one (``VERSION ?= us``, i.e. ``-DVERSION_US=1``).
    """
    prefix = f"asm/{region}/nonmatchings/"
    stubs = []
    for c_path in sorted((disasm / "src").rglob("*.c")):
        text = c_path.read_text(encoding="utf-8", errors="replace")
        for i, line in enumerate(text.splitlines(), start=1):
            m = PRAGMA_RE.search(line)
            if not m:
                continue
            asm_rel = m.group(1)
            if not asm_rel.startswith(prefix):
                continue
            func = Path(asm_rel).stem
            asm_path = disasm / asm_rel
            stubs.append((
                str(c_path.relative_to(disasm)),
                i,
                func,
                asm_rel,
                asm_path,
            ))
    return stubs


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--disasm", type=Path, required=True,
                    help="Path to the 'disasm' directory (repo checkout, post-'make extract')")
    ap.add_argument("--out", type=Path, default=Path("asm_worklist.html"),
                    help="Output HTML path (default: ./asm_worklist.html)")
    ap.add_argument("--region", default="us", choices=["us", "jp", "pal"],
                    help="Region to track (matches the active VERSION; default: us)")
    args = ap.parse_args(argv)

    disasm = args.disasm.resolve()
    if not (disasm / "src").is_dir():
        sys.exit(f"error: {disasm} does not contain a 'src' directory")

    stubs = collect_stubs(disasm, args.region)
    if not stubs:
        sys.exit("error: no `#pragma GLOBAL_ASM` stubs found under src/")

    missing = 0
    rows = []
    for owner, line, func, asm_rel, asm_path in stubs:
        body_lines = 0
        if asm_path.is_file():
            asm = asm_path.read_text(encoding="utf-8", errors="replace")
            # crude size proxy: count non-empty, non-comment, non-label source lines
            for ln in asm.splitlines():
                s = ln.strip()
                if not s or s.startswith((".set", ".text", ".globl",
                                          ".ent", ".end", "/*")):
                    continue
                body_lines += 1
            asm_html = "<pre>" + html.escape(asm) + "</pre>"
        else:
            missing += 1
            asm_html = ("<p class='missing'>.s not found at "
                        + html.escape(asm_rel)
                        + " — run <code>make extract</code> first.</p>")
        rows.append((func, owner, line, body_lines, asm_html))

    rows.sort(key=lambda r: r[0])

    row_html = []
    for func, owner, line, size, asm_html in rows:
        row_html.append(
            f"<details class='fn' data-func='{html.escape(func)}' "
            f"data-owner='{html.escape(owner)}'>"
            f"<summary><span class='sym'>{html.escape(func)}</span>"
            f"<span class='loc'>{html.escape(owner)}:{line}</span>"
            f"<span class='size'>{size} lines</span></summary>"
            f"<div class='body'>{asm_html}</div></details>"
        )

    page = f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Stadium 2 — remaining GLOBAL_ASM functions</title>
<style>
 body {{ font-family: system-ui, sans-serif; margin: 0; background: #0f1115; color: #d7dae0; }}
 header {{ position: sticky; top: 0; background: #161a22; padding: 12px 16px; border-bottom: 1px solid #2a2f3a; }}
 h1 {{ font-size: 18px; margin: 0 0 8px; }}
 .meta {{ color: #8b93a3; font-size: 13px; margin-bottom: 8px; }}
 input {{ width: 100%; box-sizing: border-box; padding: 8px 10px; border-radius: 6px;
          border: 1px solid #2a2f3a; background: #0b0d12; color: #d7dae0; font-size: 14px; }}
 details.fn {{ border-bottom: 1px solid #20252e; }}
 summary {{ display: flex; gap: 14px; align-items: baseline; padding: 7px 16px; cursor: pointer;
            font-family: ui-monospace, monospace; font-size: 13px; }}
 summary:hover {{ background: #1a1f28; }}
 .sym {{ color: #7cc7ff; font-weight: 600; }}
 .loc {{ color: #8b93a3; }}
 .size {{ color: #5c6470; margin-left: auto; }}
 .body {{ padding: 0 16px 12px; }}
 .body pre {{ margin: 0; background: #0b0d12; border: 1px solid #20252e; border-radius: 6px;
              padding: 10px 12px; overflow-x: auto; font-size: 12.5px; line-height: 1.45; }}
 .missing {{ color: #e0a060; }}
</style>
</head>
<body>
<header>
  <h1>Pokémon Stadium 2 — functions still #pragma GLOBAL_ASM</h1>
  <div class="meta">{len(rows)} stubs · {missing} missing .s files (need <code>make extract</code>)</div>
  <input id="q" type="text" placeholder="Filter by symbol or source file (e.g. func_8000 or 7140.c)">
</header>
<div id="list">{''.join(row_html)}</div>
<script>
 const q = document.getElementById('q');
 q.addEventListener('input', () => {{
   const term = q.value.toLowerCase();
   for (const el of document.querySelectorAll('details.fn')) {{
     const hay = (el.dataset.func + ' ' + el.dataset.owner).toLowerCase();
     el.style.display = term && !hay.includes(term) ? 'none' : '';
   }}
 }});
</script>
</body>
</html>
"""
    args.out.write_text(page, encoding="utf-8")
    print(f"wrote {args.out} ({len(rows)} stubs, {missing} missing .s files)")


if __name__ == "__main__":
    main()