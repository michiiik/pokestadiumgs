# Region notes -- disasm/src/fragments/63/fragment63_312AE0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Requeue: func_87E0F1C4 (2026-08-30)

requeue: parser/state-field owner remains unresolved after raw u8/u16 overlays, typed local State overlays, direct offset expressions, block-local temporaries, tail polarity, loop/control-flow forms, pointer-type variants, and a 60-second permuter run. Best complete-size probe: similarity 0.9388, raw 0.5918, mismatch_kind operand_or_scheduling_drift; first differing instruction is expected lh a1,6(v0) versus actual lh a2,6(v0). Next action: materially change the temporary/register shape to make the s16 cursor load occupy a1 and the data+offset pointer occupy a2, while preserving the 196-byte body and the delayed tail store/return structure. Do not treat normalized similarity as acceptance evidence.

## Requeue: func_87E11534 (2026-08-30)

requeue: byte-record call-sequence owner remains unresolved after typed ABI forms (s32, s32, u8 *, u8, u8), exact companion prototype edits for both accepted callers, do-while/while/initialization-order variants, direct formal-pointer form, and raw s32-pointer m2c form. Best probe: similarity 0.9839, raw 0.9677, 61/62 exact instructions, mismatch_kind operand_or_scheduling_drift; first stable mismatch is expected move s0,a2 versus actual move s2,a0, with the loop counter initialization also scheduled before the expected blez delay slot. Next action: preserve the byte-narrowed fifth stack argument and try a materially different live-range/register shape that makes the record pointer occupy s0 before the argument copies without changing the 0x40 frame/save set. Do not gate the near miss.

## Requeue: func_87E1144C (2026-08-30)

requeue: global-state initializer remains unresolved after volatile base/raw u32 overlays, declaration/value-order variants, and direct-width stores. Best probe: similarity 1.0, raw 0.6552, all 58 normalized instructions matched, mismatch_kind register_allocation_only; first stable mismatch is expected lw t7,0(v0) versus actual lw t6,0(v0), followed by the repeated reload register map. Next action: materially change the live-range/register source shape for the global reload temporaries; do not gate normalized-only matches.

## Requeue: func_87E11A5C (2026-08-30)

requeue: fixed-record call-sequence owner remains unresolved after typed/raw pointer locals, typed formal pointer with an accepted-caller prototype edit, and direct formal/raw pointer variants. Best recorded result remains similarity 0.9565, raw 0.9565, mismatch_kind operand_or_scheduling_drift; prior stable mismatch was the pointer/index register assignment around the 0x28 frame and loop. Next action: materially change the live-range/declaration shape to place the record pointer in s0 and the index in s1 while preserving the branch-likely increment delay slot. Do not gate the near miss.

## 2026-09-08

func_87E110E4: matched (call_sequence:conditional-result:unsigned-index), 8 iterations, agent codex

## 2026-09-08

func_87E12070: matched (call_sequence:temp-reuse:direct-mask), 1 iterations, agent codex

## 2026-09-08

func_87E11924: time cap at 0.8913 (raw 0.5652) after 2400s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-08

func_87E10094: time cap at 0.8125 (raw 0.7292) after 2400s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no
