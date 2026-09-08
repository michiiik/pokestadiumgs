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

## func_84147008: stale jump_table_rejection was a wrong case grouping, not a layout gap (2026-09-07) (2026-09-07)

accepted: func_84147008 (jump_table_map / dispatcher_switch). Triage flagged this as jump_table_stale_rejection / stale_past_fix at 1.0/1.0465. It is NOT the fragment79_393CA0 class of bug: this file's .rodata window (0x3FAA60..0x3FB010) already covers jtbl_8418B5E4 (rom 0x3FAE74), and splat already emits the table as a .late_rodata section inside func_84147008.s, so the owner was genuinely ready.

The real blocker was that no candidate in the 63 recorded attempts ever used the case grouping the table actually encodes. jtbl_8418B5E4 has 19 words (index 0..18, guarded by sltiu $at, $t7, 0x13):
  0,1,2,3,16,17,18 -> .L84147060 (halfword at +0xA, scaled by D_84186F0C)
  4,5,6,7,8        -> .L84147090 (halfword at +0xC, scaled by D_84186F10)
  9..15            -> .L841470BC (function end / default)
The best stored candidate (jump_table_map:switch_u8arg:decl-order-direction-first, 1.0/1.0465) omitted cases 16-18 entirely, so its table was 9 words and the whole segment shifted -> section_layout_drift. Several other stored candidates were reported as probe_match with probe_reason=relocation_fields_only / relocation_masked=true / link_mismatch=section_content_drift; those are the docs/JUMP_TABLES.md section 8 trap in its second form -- the isolated probe masks the jtbl_* words, so a candidate that folds 9..15 into the +0xC block (full_dispatch:grouped_cases, case16_first, explicit_19_cases:grouped_fallthrough) scores a flawless 'match' while encoding a different table. Treat probe_match+relocation_masked on a dispatcher as unverified, not as a result.

Accepted spelling (dispatcher_switch:sign-temps-then-switch):
  var0 = (arg1 == 0xF) ? 1 : -1;   /* u8 arg1; IDO's sw $a1,4($sp)+andi prologue confirms the u8 param */
  var1 = (arg0[1] != 0) ? 1 : -1;
  switch (arg0[0]) { case 0..3,16,17,18: *(s16 *)(arg0+0xA) += D_84186F0C * var0 * var1; break;
                     case 4..8:          *(s16 *)(arg0+0xC) += D_84186F10 * var0 * var1; break; }
No default label (the tail block is just the epilogue; adding 'default: break;' also gates, but the no-default form matches the file's sibling func_84148054 style). D_84186F0C/D_84186F10 declared as file-local externs immediately above the body, matching func_84147FF4/func_84148054 in this file. Verified end to end with container/gate_pr.sh: build/pokestadiumgs-us.z64 md5 1561c75d11cedf356a8ddb1a4a5f9d5d, OK (495s).

## 2026-09-09

func_841450B4: plateau at 0.0 (raw None), mismatch unknown; tried families: init_sequence; tie-pool no

## 2026-09-09

func_8413FBC4: plateau at 0.9655 (raw 0.931), mismatch instruction_drift; tried families: call_sequence; tie-pool no

## 2026-09-09

func_84142DCC: matched (call_sequence:alias-before-index:pointer-increment:reverse-args), 6 iterations, agent codex

## 2026-09-09

func_84146610: matched (state_field_access:table-select:direct-index-2x), 2 iterations, agent codex

## 2026-09-09

func_8413F5A8: plateau at 0.8421 (raw 0.8421), mismatch instruction_drift; tried families: init_sequence; tie-pool no

## 2026-09-09

func_84147FF4: plateau at 0.0 (raw None), mismatch section_layout_drift; tried families: dispatcher_switch; tie-pool no

## 2026-09-09

func_84148054: plateau at 0.0 (raw None), mismatch section_layout_drift; tried families: dispatcher_switch; tie-pool no

## 2026-09-09

func_84145AB4: matched (state_field_access:gfx-postinc:oldstyle-struct-local), 2 iterations, agent codex

## 2026-09-09

func_84145B2C: plateau at 0.0 (raw None), mismatch section_layout_drift; tried families: dispatcher_switch; tie-pool no

## 2026-09-09

func_841410A0: plateau at 0.0 (raw None), mismatch section_layout_drift; tried families: dispatcher_switch; tie-pool no

## 2026-09-09

func_84141020: plateau at 0.0 (raw None), mismatch section_layout_drift; tried families: dispatcher_switch; tie-pool no
