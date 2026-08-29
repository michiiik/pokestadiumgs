# Region notes -- disasm/src/fragments/82/fragment82_4238F0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-29 (2026-08-29)

Accepted func_82D04B84 with gbi:display-list:nested-color:raw-fields. Use gSPDisplayList(D_800D0510++, D_82D071D8), raw u8/s16 field accesses, nested sp24 color selection, and direct helper calls. Probe hit had link_verified:true; gate accepted with one combined full COMPARE=1 run. Do not replace the display-list macro with words.w0/w1 stores.

Accepted func_82D065C0 with state:dispatch-switch:s32-count. The winning spelling uses a u8 * argument, a switch on arg0[0] with cases 2/3/5/4, then an s32 count temporary from offset 0xC and explicit flag-byte updates at offsets 0xB/0xA. Probe hit had link_verified:true; gate accepted with one combined full COMPARE=1 run.

Deferred func_82D05D74 after two five-variant batches: best 0.9167 normalized and 0.7708 raw, operand_or_scheduling_drift, expected 196 bytes versus actual 200. Deferred func_82D0639C after one five-variant batch: best 0.8136 normalized and 0.678 raw, operand_or_scheduling_drift. Deferred func_82D03778 because the existing earlier func_80044270 call creates a declaration-context conflict and the no-declaration form stayed at 0.8261 normalized/0.4783 raw with a frame mismatch. Deferred func_82D05C90 because source-order extern/type context conflicts persisted and it calls deferred jump-table owner func_82D05BD8. Do not reopen tie-heavy func_82D068A0 without a new hypothesis; its prior best was a register-allocation-only tie at 1.0 normalized/0.95 raw after 45 attempts. User-deferred jump/dispatcher owners remain untouched: func_82D068F0, func_82D06CC0, func_82D06514, func_82D05BD8.

## 2026-08-29 fleet box (2026-08-29)

Accepted func_82D03BEC with label init-sequence:mul-int-direct:sp34. Source uses a single s32 sp34 spill, D_80087E50 lookup times integer 2, D_82D07280 increment 0x2000, and the existing helper calls; probe link_verified:true and full combined COMPARE=1 gate accepted. No evidence-backed name applied. Deferred this box: func_82D03A5C after gbi.h macro candidates (best 0.90 normalized / 0.72 raw, 95 emitted vs 100 expected; operand_or_scheduling_drift); func_82D02F78 after m2c call-sequence candidates (best 0.9565 normalized / 0.6696 raw, 115 emitted vs 115 expected but frame/scheduling drift); func_82D02DA8 after gbi.h macro candidates (best 0.8182 normalized / 0.6942 raw, 121 emitted vs 116 expected); func_82D03144 after six-local candidates (best 0.925 normalized / 0.7417 raw, 120 emitted vs 120 expected); func_82D06150 was unavailable in the runner with repeated list index out of range diagnostics. User-deferred jump-table owners and documented tie/deferred owners were not reopened.

## 2026-08-29 fleet box (2026-08-29, second box)

No owner was accepted in this 45-variant probe-only box, so no link-verified/full-ROM gate or ROM MD5 is available. Deferred fresh owners:

- `func_82D049A0`: 16 variants plus a 120-second permuter run. The best gSPDisplayList/switch spelling was exact size (484/484), normalized similarity 1.0 and raw similarity 0.8430, `register_allocation_only`; first diff offset 141/instruction 35 was `lbu $v0, $s1, 0` expected versus `lbu $v1, $s1, 0` emitted, with later temporary-register allocation differences. The permuter improved its score but did not reach zero; its raw-word macro output was not adopted. Keep the u8 state switch, u16 table declarations, and gSPDisplayList macro spelling, but leave this owner deferred.
- `func_82D03598`: 10 variants. The best expression-spill spelling was normalized 0.9000/raw 0.8583, 476 emitted bytes versus 480 expected, `operand_or_scheduling_drift`; first diff offset 35/instruction 8 was the branch target 107 expected versus 106 emitted. Five/six-local variants also changed the frame (typically -0x50/-0x58 instead of -0x48). Leave deferred.
- `func_82D03380`: 18 variants. The best declaration-order spelling (`sp64`, `sp60`, `temp_a0`, `sp58`, `sp54`, `sp50`) was exact size (536/536), normalized/raw 0.9925, `instruction_drift`; first diff offset 488/instruction 122 was `lh $a0, $sp, 74` expected versus `lw $a0, $sp, 72` emitted. An array-overlay variant normalized to 1.0 but raw similarity fell to 0.7687 and changed the frame, so it is not a candidate. Leave deferred.
- `func_82D0599C`: one gbi.h macro candidate failed to compile because `D_82D07198` is declared later in the source (along with missing-prototype diagnostics); no probe score or gate was produced. Preserve the gSPDisplayList/gDPFillRectangle macro approach if revisited after resolving source-order declarations.

No new cross-file source-shape pattern was established. Do not reopen the documented exhausted/tie owners or jump/dispatcher owners without their prerequisites; do not replace gbi macros with `words.w0`/`words.w1` stores.
