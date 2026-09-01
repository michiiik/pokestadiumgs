# Region notes -- disasm/src/fragments/79/fragment79_36F8B0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-30 fleet box handoff (2026-08-30)

Accepted in 43d47f89: func_84102750 label call-sequence:nested-guards:direct-index; direct-index nested guards with void * temp_v1/temp_v0 and explicit (s32)(u32) address arithmetic. link_verified=true and full make -C disasm COMPARE=1 ROM gate passed; ROM md5 1561c75d11cedf356a8ddb1a4a5f9d5d.

Accepted in 43d47f89: func_84103478 label call-chain:particle-loop:mask-local-for-loop; local s32 mask/i, u8 *record, 0x9C stride, explicit mask checks and child reload. link_verified=true and full ROM gate passed with the same md5.

requeue func_84101AF4: best normalized similarity 0.9420, raw 0.4928, operand_or_scheduling_drift; first-diff fingerprint frame addiu -40 expected vs -48 actual. Tried explicit scale/types, sp20 integer scratch, reused temp, and declaration-order variants. Next action: materially different struct/ABI or compiler-order hypothesis, then gate any hit.

requeue func_841027B4: label call-chain:battle-animation:duplicated-switch-reload-child reached exact 360/360 size and normalized similarity 1.0000 but raw 0.8222; register_allocation_only at first differing add.s expected add.s $f4,$f16,$f18 vs actual add.s $f4,$f18,$f16. No runner futility flag; a 45-second four-thread permuter run made no improvement. Next action: new declaration/temporary or float expression-order hypothesis, or a longer permuter run.

tooling-blocked func_84100260: pointer-return candidates conflict with the existing extern void declaration; companion_edits cannot edit a still-GLOBAL_ASM pragma owner. Preserve for a runner-supported ABI/prototype resolution.

register-tie/stuck skip: func_841032F0, func_841005E0, func_8410291C, func_84101A08, per assignment. layout-prerequisite defer: func_841029DC, func_84102B3C, func_841013F4. Display-list/gbi prerequisite defer: func_841031F4, func_84102D38, func_84102E84. Also leave prior drift owners func_84100174 and func_84100710 for requeue; not resolved in this box.
