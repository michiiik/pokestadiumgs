# Region notes -- disasm/src/fragments/51/fragment51_275E40.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-30 fleet box handoff (2026-08-30)

func_86300DD4 remains requeue after box expiry; no accepted candidate and no ROM gate was run for this owner. Expected shape is 73 instructions with a 0x40 frame. Best probe was call-chain:loop:post-mul-materialized-predicate: 73 instructions, similarity 0.9589, raw similarity 0.6712, mismatch_kind=instruction_drift; first loop difference expected slt at,v0,v1 before mul.s, while the candidate scheduled mul.s first. Strongest layout near-match used constant -8 stack-address adjustments: 73 instructions, similarity 0.9452, raw similarity 0.7945, with call argument slots corrected, but loop scheduling and FPU allocation still differed. Earlier aggregate array/struct/local-padding forms raised the frame to 0x48 or 0x50; while/for/preincrement forms unrolled or added branches; volatile sp30 did not resolve the schedule. The final permute_candidate transaction timed out at 60 seconds with best score 355 and installed nothing. Next action: resume this owner with a materially different compiler-faithful loop/FPU scheduling hypothesis preserving the target blez, slt, mul.s, bnel order, then gate the first probe hit.

## 2026-08-31 fleet box requeue (2026-08-31)

requeue func_86300DD4: two candidates were attempted; one had a malformed scratch label and one was rejected, so no gate ran. Best new result was normalized/raw 0.8947/0.6316, operand_or_scheduling_drift, 292 expected versus 304 actual bytes, first diff offset 25 (expected lui $a2, actual lui $v0). Next action is to preserve the proven 0x40 frame while finding a loop form that emits slt -> mul.s -> bnel; avoid added declarations or explicit temporaries that inflate the frame.

## 2026-08-31 successor box requeue (2026-08-31)

requeue func_86300DD4: four valid probes, no link_verified candidate or ROM gate. Best improved to normalized/raw 0.9324/0.6757, 292 expected versus 296 actual bytes, with the recurring operand/scheduling drift at offset 25: expected lui $a2, actual lui $v0. Tried for increment-expression, do-loop increment-before-multiply, stores-before-state, and post-increment condition forms. Next action is declaration/allocation ordering that keeps D_863075D8 in $a2 while preserving the 0x40 frame.

## 2026-08-31 third successor box requeue (2026-08-31)

requeue func_86300DD4: four declaration/lifetime-order variants; no link_verified candidate or ROM gate. Best regressed to normalized/raw 0.8533/0.5733, 300 bytes versus 292 expected, and disrupted the proven 0x40 frame. Persistent drift remains around keeping D_863075D8 in $a2 while preserving slt -> mul.s -> bnel. Next action is a different formal/global lifetime strategy, not more loop-form variants.

## Wave 7 handoff (2026-08-31)

Wave 7 handoff: func_86301E54 remains unresolved after 9 serial CC_CHECK=1 probes across global/address, volatility, float, and call-order shapes. Best normalized/raw similarity was 0.7200/0.6200; the stable operand_or_scheduling_drift includes expected -0x20 frame versus actual -0x28. Next action is a typed padded state overlay matching m2c field ordering and the store/call/store sequence while preserving the exact 0x20 frame.
