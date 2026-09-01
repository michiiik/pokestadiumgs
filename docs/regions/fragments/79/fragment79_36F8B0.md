# Region notes -- disasm/src/fragments/79/fragment79_36F8B0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-30 fleet box handoff (2026-08-30)

Accepted in 43d47f89: func_84102750 label call-sequence:nested-guards:direct-index; direct-index nested guards with void * temp_v1/temp_v0 and explicit (s32)(u32) address arithmetic. link_verified=true and full make -C disasm COMPARE=1 ROM gate passed; ROM md5 1561c75d11cedf356a8ddb1a4a5f9d5d.

Accepted in 43d47f89: func_84103478 label call-chain:particle-loop:mask-local-for-loop; local s32 mask/i, u8 *record, 0x9C stride, explicit mask checks and child reload. link_verified=true and full ROM gate passed with the same md5.

requeue func_84101AF4: best normalized similarity 0.9420, raw 0.4928, operand_or_scheduling_drift; first-diff fingerprint frame addiu -40 expected vs -48 actual. Tried explicit scale/types, sp20 integer scratch, reused temp, and declaration-order variants. Next action: materially different struct/ABI or compiler-order hypothesis, then gate any hit.

requeue func_841027B4: label call-chain:battle-animation:duplicated-switch-reload-child reached exact 360/360 size and normalized similarity 1.0000 but raw 0.8222; register_allocation_only at first differing add.s expected add.s $f4,$f16,$f18 vs actual add.s $f4,$f18,$f16. No runner futility flag; a 45-second four-thread permuter run made no improvement. Next action: new declaration/temporary or float expression-order hypothesis, or a longer permuter run.

tooling-blocked func_84100260: pointer-return candidates conflict with the existing extern void declaration; companion_edits cannot edit a still-GLOBAL_ASM pragma owner. Preserve for a runner-supported ABI/prototype resolution.

register-tie/stuck skip: func_841032F0, func_841005E0, func_8410291C, func_84101A08, per assignment. layout-prerequisite defer: func_841029DC, func_84102B3C, func_841013F4. Display-list/gbi prerequisite defer: func_841031F4, func_84102D38, func_84102E84. Also leave prior drift owners func_84100174 and func_84100710 for requeue; not resolved in this box.

## 2026-09-02 fleet box handoff (2026-09-02)

requeue func_84100B3C (fresh owner, 8 candidates attempted). All candidates were probe_rejected with link_verified unset; mismatch_kind operand_or_scheduling_drift and identical first-diff fingerprint at instruction 3: expected addiu $sp,$sp,-64, actual frames -40 (chain:structural:direct; sim 0.6329 raw 0.3544, size 316), -48 (chain:structural:assign; sim 0.8375 raw 0.3125, size 320; best normalized), -40 (chain:abi:void-temp; sim 0.8025 raw 0.3580, size 324; best raw), -40 (chain:types:s32-index; sim 0.8077 raw 0.1923, size 312), -56 (chain:control:guarded; sim 0.7308 raw 0.2436, size 312), -48 (chain:decl-order:locals; sim 0.7778 raw 0.3086, size 324), -24 (chain:copy:explicit-u8; sim 0.7632 raw 0.3158, size 304), -56 (chain:cast:address; sim 0.7564 raw 0.2821, size 312). Expected size 300 for every attempt; no futility/register-tie or layout prerequisite. Attempted structural chain, assign-then-return, void-temp ABI, s32 index, guarded control flow, declaration order, explicit u8 copy, and address casts. Next materially different action: use a compiler-shaped local scratch overlay/padding arrangement that forces the exact 0x40 frame and stack slots at sp+0x28/sp+0x34/sp+0x38/sp+0x40, then submit a fresh 8+ batch; preserve exact func_8410A4F8(u8,u8,u8,u8) and func_84100710(u8*,s32) declarations.
