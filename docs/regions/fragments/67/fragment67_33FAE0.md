# Region notes -- disasm/src/fragments/67/fragment67_33FAE0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Fleet box 2026-08-31: call-sequence helper requeued (2026-08-31)

No accepted owner. func_82904E9C received 15 variants across 4 serial CC_CHECK-enabled batches; best callseq:m2c-shape:no-spill was 0.9091 normalized / 0.8727 raw with operand_or_scheduling_drift at offset 33: expected lbu $v0,$a1,4210 but actual lbu $v1,$a1,4210. Requeue targeting v0/v1 allocation and the expected a1 alias plus stack spill. Preserve the assigned tied/drift/stuck and jump-table skip list.

## Fleet box 2026-09-01: GBI display-list constructor accepted (2026-09-01)

Accepted func_82903BA4 with the compiler-faithful GBI macro spelling: gSPDisplayList(D_800D0510++, D_80094DB8), gDPSetCombine(..., 0xFFFFFF, 0xFFFE793C), gDPSetRenderMode(..., 0x00504240, 0), two Gfx_FillRectRgba calls, gSPDisplayList(..., D_80094D90), then two Gfx_FillRectRgb calls. Probe was link-verified and the sequential full ROM gate passed (MD5 1561c75d11cedf356a8ddb1a4a5f9d5d). Candidate batch had 5 variants; direct macros accepted. This confirms the display-list append macro family in a fragment.

## Fleet box 2026-09-02: func_82902FE0 requeued (2026-09-02)

requeue: func_82902FE0 remains unresolved after 9 distinct state_field_access candidates plus one permuter-derived candidate. Best initial batch normalized=0.9355, raw=0.6129 (state:raw:tables-reversed), operand_or_scheduling_drift, first diff offset 34/instruction 8: expected addu $v1,$v0,$t6, actual addu $a3,$v0,$t6; expected size 120/30 instructions, common actual size 124/31. Permuter: base_score=395, best_score=65 at 60s timeout; its best commute candidate reached normalized=1.0, raw=0.8, 30/30 instructions but was rejected as immediate_drift at offset 43/instruction 10: expected lwc1 $f6,8($a1), actual lwc1 $f6,0($a1), with later field/register differences. Attempted families: raw offset access, typed vector overlay, signed/unsigned s16 index, table pointer declaration order, explicit table offsets, hoisted input temporaries, commuted second add, and permuter randomization. link_verified=false; no full-ROM gate or install occurred. Next materially different action: use the score-65 table-order body as baseline, explicitly materialize input z at offset 8 before table/candidate expressions and separately materialize x at offset 0 only at the assembly-indicated later point; vary temp declaration/lifetime to force expected first z load and v1/a3 pointer allocation. Do not treat normalized 1.0 as acceptance.
