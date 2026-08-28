# Region notes -- disasm/src/fragments/46/fragment46_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Unsolved shape: branch-likely null guard (AGENTS.md §5) (2026-08-28)

A leading null/zero guard that IDO emits as a branch-likely (`bnel`/`beql`) where every C spelling produces a plain `bne` (`func_8AE011E0`/`func_8AE01248`). The §4 guard-polarity row does not cover it.
