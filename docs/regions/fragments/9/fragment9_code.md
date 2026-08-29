# Region notes -- disasm/src/fragments/9/fragment9_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Fleet box 2026-08-29 (2026-08-29)

Accepted, runner-gated spellings (all link_verified=yes, full COMPARE=1, ROM MD5 1561c75d11cedf356a8ddb1a4a5f9d5d):
- func_8FB03328: multi-call:setup:typed-baseline. Keep the s32 sp24 result local and the six-argument func_800082E0 call; direct calls and the D_8FB03DF0 assignment match.
- func_8FB031E0: call-chain:render-loop:typed-record-overlay-34. Use struct { u8 pad[0x34]; s32 index; } *state and the s32 index/30-iteration render loop.
- func_8FB01FCC: call-sequence:reverse-scan:signed-index. Use the padded u16 state overlay, s32 var_s0, raw s8 byte load at var_s2 + 0xC, and signed loop test.
- func_8FB01EC4: call-sequence:reverse-scan:signed-index. Same padded u16 state overlay, s32 var_s0, raw s8 byte load at var_s1 + 0xC, and signed loop test.

Deferred diagnostics:
- func_8FB01C14: 12 variants; best 0.9649 normalized / 0.8421 raw, operand_or_scheduling_drift at offset 13 (expected li t3,20, actual li t0,20); later count loads also emitted lh instead of expected lhu.
- func_8FB001C0: 20 variants; best 0.9524 normalized / 0.8254 raw, operand_or_scheduling_drift at offset 35 (expected beq $v0,$at,24, actual beq $v0,$at,26); branch layout adds a reload before the type-22 path.
- Pre-box exhausted/deferred: func_8FB02454 (11 prior, best 0.8750/0.8750 instruction_drift at offset 16); func_8FB00170 (10 prior, best 1.0000/0.9000 register_allocation_only at offset 45); func_8FB000D0 (12 prior, best 0.9000/0.8500 operand_or_scheduling_drift at offset 31); func_8FB02560 (12 prior, best 0.9762/0.9762 instruction_drift at offset 64); func_8FB02108 (19 prior, best 0.9833/0.9500 instruction_drift at offset 48); func_8FB024BC (5 prior, no recorded best mismatch).
- Untouched fresh non-dispatchers: func_8FB01CF8, func_8FB02698, func_8FB00FE8, func_8FB021F8, func_8FB009C0, func_8FB002BC, func_8FB005E4 (mismatch N/A: not probed in this box).
- Untouched dispatcher/jump-table owners pending .rodata prerequisite: func_8FB03164, func_8FB02608, func_8FB00E40, func_8FB02878, func_8FB01A74, func_8FB00C1C, func_8FB01634, func_8FB011DC, func_8FB02A10 (mismatch N/A: intentionally not probed).

Runner/tooling handoff: the two reverse-scan siblings matched only when the loop index was s32 with a signed test; normalized similarity alone hid the mismatch. Keep reporting raw similarity and first-diff instruction, and gate only link-verified matches. Total distinct candidate variants in this box: 50; one short permuter diagnostic was run for func_8FB01C14 with no score-zero result.
