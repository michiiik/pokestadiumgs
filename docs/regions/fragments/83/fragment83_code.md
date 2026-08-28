# Region notes -- disasm/src/fragments/83/fragment83_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Unsolved shape: incoming-argument stack-home spill (AGENTS.md §5) (2026-08-28)

An incoming-argument stack-home spill (`sw a0, N(sp)` with no intervening call) that no C spelling reproduces -- one of the common dead ends in fragment work (`func_82C02664`). Drop an owner as soon as its first diff is this.
