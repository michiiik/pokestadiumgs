# Region notes -- disasm/src/fragments/79/fragment79_3BF4C0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: wrapper called with four registers but only three read (AGENTS.md §4) (2026-08-28)

Declare only the parameters the body reads (`a3` was caller garbage); the fourth formal changes the frame. Evidence: 1 (`func_841518D0`).

## Unsolved shape: table pointer kept in $t7 (AGENTS.md §5) (2026-08-28)

`u8 *p = arg0 + 4; p[arg1 + 8] = 0xFF; p[0] |= 2;` -- IDO keeps the table pointer in `$t7`; no declaration-order/pointer-form variant reproduced it (`func_841523BC`, `func_84151CD8`, likely `func_84151DD4`). Needs a dedicated variant family.
