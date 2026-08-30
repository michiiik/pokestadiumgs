# Region notes -- disasm/src/fragments/43/fragment43_1E5A10.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: _bzero-then-forward call chain (AGENTS.md §4) (2026-08-28)

`_bzero(dst, N); v0 = ctor(a, b); dst[0] = v0; dispatch(field, &callback, dst);` -- the callback is referenced by address even when it is still an unsolved sibling. Evidence: 5 (`func_8AC02C80/02FCC/03334/02770/02830`). Limit: `_bzero` may come before or after the constructor; word stores precede byte stores.

## Requeue: func_8AC00028 (2026-08-30) (2026-08-30)

Runner futility after 20 recorded attempts: best packed unaligned copy-loop candidates matched the 244-byte span at normalized similarity 0.8197 / raw 0.5410 but repeated operand_or_scheduling_drift at offset 57 (expected lui v1, actual lui v0). Tried packed struct assignments, m2c/goto forms, pointer/address order, branch polarity, global-end comparison, index loops, and bounded permuter runs (best permuter score 2105); requeue with a materially different register-allocation hypothesis.

## Requeue: func_8AC00028 (2026-08-30 follow-up) (2026-08-30)

requeue: func_8AC00028 remains unresolved after this 60-minute box. Probe-only best stayed at normalized similarity 0.8197; best raw similarity improved to 0.7705 with the scalar end-address plus u8 lane-pointer hypothesis, but it still mismatched at offset 96 (expected addiu $v0,$v0,0; actual addiu $t2,$t2,0). The packed-struct scalar variant preserved the target high-half sequence but mismatched at offset 97 (expected addiu $v0,$v0,0; actual addiu $v1,$v1,0). The recurring baseline fingerprint remains operand_or_scheduling_drift at offset 57 (expected lui $v1, actual lui $v0). Attempted families in this box: early scalar s32/u32 loop-end lifetime, explicit register scalar, u8 versus packed lane pointers, target/reverse initializer order, declaration/prologue order, direct/global-end compare forms, do/goto loop forms, packed copy-loop bodies, and a 120-second bounded permuter run (best score 1945; prior box best 2105). Earlier box families preserved in the preceding note include packed structs, m2c/goto, pointer/address order, branch polarity, global-end comparison, index loops, and aggregate block copies. Next action: requeue this owner with a materially different source-shape hypothesis for the low-half address scheduling, or investigate an allocator/tooling-supported way to constrain the end-address temporary; do not install or gate a non-hit.
