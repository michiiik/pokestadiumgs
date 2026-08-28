# Region notes -- disasm/src/fragments/79/fragment79_38EFE0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: dual-global notify chain (AGENTS.md §4) (2026-08-28)

`func_8411EF08((u8 *) D_84191208)` -- an `s32`-typed global holding a pointer bit pattern, passed straight through, then the second global. Evidence: 2 (`func_84120A50`, `func_84120CA4`). Limit: only where the global is `s32`-typed but dereferenced.
