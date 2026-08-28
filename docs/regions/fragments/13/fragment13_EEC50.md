# Region notes -- disasm/src/fragments/13/fragment13_EEC50.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Unsolved shape: list-scheduler order around a non-zero stack literal (AGENTS.md §5) (2026-08-28)

Forward-call wrappers whose last stack argument is a non-zero literal (`func_8005F37C`; sibling `func_8005F5D4` is in `585D0.c`) get a different list-scheduler order around the call than the accepted `0`-literal siblings; every source reordering gave byte-identical diagnostics.
