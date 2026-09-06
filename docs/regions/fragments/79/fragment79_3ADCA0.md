# Region notes -- disasm/src/fragments/79/fragment79_3ADCA0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-05

func_8413F5A8: plateau at 0.0 (raw None), mismatch unknown; tried families: (none); tie-pool no

## 2026-09-05

TYPE CONFLICT: func_8004D19C is extern void func_8004D19C(), not extern void func_8004D19C(s32, s32, s32, s32, s32)

## 2026-09-05

TYPE CONFLICT: func_8004D19C is extern void func_8004D19C(s16, s16, s32, s32, s32), not extern void func_8004D19C(s32, s32, s32, s32, s32)

## 2026-09-05

func_8413E840: matched (float_math:truncate-round:two-s32-explicit-else), 1 iterations, agent codex

## 2026-09-05

func_84147FF4: plateau at 1.0 (raw 1.0), mismatch section_layout_drift; tried families: dispatcher_switch; tie-pool no

## 2026-09-05

func_841482BC: matched (call_chain:fixed_stride:explicit-next-temp), 5 iterations, agent codex

## 2026-09-05

func_84148054: plateau at 1.0 (raw 1.0), mismatch section_layout_drift; tried families: dispatcher_switch; tie-pool no

## Stale section_layout_drift replay: five owners landed (2026-09-06) (2026-09-06)

accepted: func_84140F98, func_84141020, func_841410A0, func_84145B2C, func_84146B0C (all dispatcher_switch/jump-table owners). These are the fleet's own high-scoring candidates recorded in probe-stats on 2026-09-04/05, rejected as 'section_layout_drift' because the file's .rodata subsegment split (jtbl_8418B1D0 +13 more, covering this whole run) predates or postdates individual attempts inconsistently. The isolated probe's stored case-value groupings for func_84140F98, func_84141020, func_84145B2C and func_84146B0C did NOT match the real jump table content byte-for-byte -- classic 'case labels do not appear in the function text' trap (see docs/JUMP_TABLES.md section 8): case 28 misgrouped as default in func_84141020, cases 8/9 swapped in func_84145B2C, and func_84146B0C's back half (cases 14-28) shuffled because the stored candidate assumed one target per case index without noticing the jump table has two 16-bit-duplicate slots (14/15 and 16/17) and a non-terminal pair of unreachable slots (23/24). Re-derived every case mapping directly from each function's jtbl_* .rodata words (not from the stored candidate's assumed order) and reordered case blocks so IDO's per-block code layout matches source order too. All five verified via a from-scratch `make COMPARE=1` (1561c75d..., OK) with only these five pragmas replaced.
