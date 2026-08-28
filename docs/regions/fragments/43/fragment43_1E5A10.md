# Region notes -- disasm/src/fragments/43/fragment43_1E5A10.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: _bzero-then-forward call chain (AGENTS.md §4) (2026-08-28)

`_bzero(dst, N); v0 = ctor(a, b); dst[0] = v0; dispatch(field, &callback, dst);` -- the callback is referenced by address even when it is still an unsolved sibling. Evidence: 5 (`func_8AC02C80/02FCC/03334/02770/02830`). Limit: `_bzero` may come before or after the constructor; word stores precede byte stores.
