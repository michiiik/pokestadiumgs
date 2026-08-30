# Region notes -- disasm/src/fragments/43/fragment43_1E5A10.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: _bzero-then-forward call chain (AGENTS.md §4) (2026-08-28)

`_bzero(dst, N); v0 = ctor(a, b); dst[0] = v0; dispatch(field, &callback, dst);` -- the callback is referenced by address even when it is still an unsolved sibling. Evidence: 5 (`func_8AC02C80/02FCC/03334/02770/02830`). Limit: `_bzero` may come before or after the constructor; word stores precede byte stores.

## Requeue: func_8AC00028 (2026-08-30) (2026-08-30)

Runner futility after 20 recorded attempts: best packed unaligned copy-loop candidates matched the 244-byte span at normalized similarity 0.8197 / raw 0.5410 but repeated operand_or_scheduling_drift at offset 57 (expected lui v1, actual lui v0). Tried packed struct assignments, m2c/goto forms, pointer/address order, branch polarity, global-end comparison, index loops, and bounded permuter runs (best permuter score 2105); requeue with a materially different register-allocation hypothesis.
