# Region notes -- disasm/src/fragments/61/fragment61_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Accepted func_86B05484 (2026-08-30)

Accepted func_86B05484 in the 2026-08-30 box via call-chain:object-base. Winning spelling: f32 arg0/f32 arg1/f32 arg2/s32 arg3; u8 *object; u8 *base; f32 scale; assign object->0x1c = 0, compute scale as (f32)((f64)D_86B0D178 * D_86B0DDE8), store it at 0x5c/0x58/0x54, set base = object + 0x24, call func_8003F1DC(base), then store the three float args at 0x48/0x4c/0x50 and s32 arg3 at 0x20, call func_8003F114(base, 0, -1, D_86B0E1A4) and func_8003F210(base, 0). Probe candidate was link_verified=true and the full COMPARE=1 ROM gate passed with checksum 1561c75d11cedf356a8ddb1a4a5f9d5d. The prior m2c-style aliases (sp18/sp24/temp_v0) produced a 0x30 frame / immediate drift; keep the object/base local shape.

## Accepted func_86B052BC (2026-08-30) (2026-08-30)

Accepted func_86B052BC via call-chain:object-base:switch-index-factor:store-y-last. Winning spelling uses the accepted object/base pattern, object setup and scale stores, switch on arg0, random index factor, table stores in +0x48/+0x4C/+0x50 order, and helper order func_8003F114 then func_8003F210. Runner reported link_verified=true and the full COMPARE=1 ROM gate passed; committed in 9d8e35f0.

## Accepted func_86B05194 (2026-08-30) (2026-08-30)

Accepted func_86B05194 via call-chain:callback:global-switch:direct-offsets. Winning spelling uses direct offsets on D_87F119DC, the state-mode switch and callback sequence into accepted func_86B052BC. Runner reported link_verified=true and the full COMPARE=1 ROM gate passed; committed in 5c96b813.

## Requeue func_86B00020 (2026-08-30) (2026-08-30)

requeue func_86B00020: 17 attempts, best normalized 0.7931/raw 0.5000; repeated-drift futility after 14 shared fingerprint ["section_layout_drift",3,0,"0x27bdffc8","0x27bdffd0"], expected frame 0x38 / actual 0x30. Attempted families: m2c/direct call-chain; float vs integer GeoCamera ABI, D_86B0D168 width, and arithmetic parentheses/temp variants. Next materially different hypothesis: force the expected 0x38 frame/formal-home schedule via an explicit used 8-byte padding/local or reconstruct the exact callee/argument ABI, not more expression permutations.

## Requeue func_86B0B500 (2026-08-30) (2026-08-30)

requeue func_86B0B500: 21 recorded attempts; best normalized 0.8387/raw 0.3387, expected 264 bytes versus actual 248, mismatch section_layout_drift with fingerprint ["section_layout_drift",1,0,"0x3c040000","0x3c060000"]. The runner reported stuck futility after 20 attempts with the same first difference (expected start pointer in a0, actual in a2), and expected duplicate_jr_nop_tail versus actual normal_return. Attempted families: raw-pointer scan, explicit end local, typed-record cast, declaration/order variants, and fewer-local forms. Next materially different hypothesis: recover the exact opaque record/global declaration shape and tail layout that schedules start/end in a0/a1 and max in v0; do not repeat raw-pointer register permutations.

## Requeue func_86B0355C (2026-08-30) (2026-08-30)

requeue func_86B0355C: 28 recorded attempts, best normalized 1.0000/raw 0.9216; mismatch immediate_drift fingerprint ["immediate_drift",3,0,"0x27bdffd8","0x27bdffd0"], expected frame 0x28 with spill at 0x18 versus actual frame 0x30 with spill at 0x1c. Attempted families: raw-offset object/base spelling, condition polarity, frame-slot declaration order, m2c-faithful void-pointer typing, and accepted func_86B05484 f32 helper order. Next materially different hypothesis: use the near-miss frame-padding/stack-slot transformation or identify the exact single stack-spilled local shape; do not repeat expression or pointer-type variants.

## Tooling-blocked func_86B0B6CC (2026-08-30) (2026-08-30)

tooling-blocked func_86B0B6CC: selected as the smallest zero-attempt gbi-macro owner (58 instructions). Assembly matches the established fragment60 func_86A0B8A4 shape: void func_86B0B6CC(s32 arg0, s32 arg1), s32 pad[2], s32 temp_v0, guard arg0 == 5, func_8004C990(0x133, 0), then gDPPipeSync, gDPSetEnvColor(0, 0, 0, 0x80), gDPSetCombine(0xFCFFD3FF, 0xFFFEFE38), gSPSegment(0xF, func_8004CA60((u8 *)temp_v0)), gSPDisplayList(D_86B0E7F4), and func_8003CD84. Prepared exact analog plus ABI/layout variants but ran no probes: foreign live installs remained in disasm/src/fragments/11/fragment11_E1E10.c and disasm/src/14640.c, making runner/build activity unsafe under the shared-checkout rules. Next action: when all foreign source installs are clean and no probe transaction is active, run the prepared gbi-macro batch; lead hypothesis is the fragment60 spelling above. No owner is exhausted.
