# Region notes -- disasm/src/fragments/51/fragment51_275E40.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-30 fleet box handoff (2026-08-30)

func_86300DD4 remains requeue after box expiry; no accepted candidate and no ROM gate was run for this owner. Expected shape is 73 instructions with a 0x40 frame. Best probe was call-chain:loop:post-mul-materialized-predicate: 73 instructions, similarity 0.9589, raw similarity 0.6712, mismatch_kind=instruction_drift; first loop difference expected slt at,v0,v1 before mul.s, while the candidate scheduled mul.s first. Strongest layout near-match used constant -8 stack-address adjustments: 73 instructions, similarity 0.9452, raw similarity 0.7945, with call argument slots corrected, but loop scheduling and FPU allocation still differed. Earlier aggregate array/struct/local-padding forms raised the frame to 0x48 or 0x50; while/for/preincrement forms unrolled or added branches; volatile sp30 did not resolve the schedule. The final permute_candidate transaction timed out at 60 seconds with best score 355 and installed nothing. Next action: resume this owner with a materially different compiler-faithful loop/FPU scheduling hypothesis preserving the target blez, slt, mul.s, bnel order, then gate the first probe hit.

## 2026-08-31 fleet box requeue (2026-08-31)

requeue func_86300DD4: two candidates were attempted; one had a malformed scratch label and one was rejected, so no gate ran. Best new result was normalized/raw 0.8947/0.6316, operand_or_scheduling_drift, 292 expected versus 304 actual bytes, first diff offset 25 (expected lui $a2, actual lui $v0). Next action is to preserve the proven 0x40 frame while finding a loop form that emits slt -> mul.s -> bnel; avoid added declarations or explicit temporaries that inflate the frame.
