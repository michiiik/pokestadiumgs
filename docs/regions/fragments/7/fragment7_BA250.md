# Region notes -- disasm/src/fragments/7/fragment7_BA250.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## func_83001A3C requeue 2026-09-02 (2026-09-02)

requeue: Fresh 90-instruction call-sequence owner; two runner batches submitted (8 candidates each, host CC checks enabled), no link_verified/full-ROM acceptance. First batch all compile_failed due candidate declarations conflicting with existing file prototype func_818057D0(s32, void *, void *) and malformed aggregate variant; do not repeat. Clean batch best normalized similarity 0.8478, raw 0.2826, 78/92 matched, expected 90 instructions/360 bytes vs actual 92/368; mismatch_kind operand_or_scheduling_drift, first_diff_fingerprint [operand_or_scheduling_drift,3,0,0x27bdffb8,0x27bdffb0], expected frame -72 vs actual -80. Best alternate normalized 0.8125/raw 0.5208, first diff instruction 8, expected float spill 64(sp) vs actual 68(sp); halfword aggregate spelling emitted lh/sh instead of required lwl/lwr + sw. Attempted families: m2c drafts, exact helper prototypes, u8 pointer arithmetic with 56-byte stride and -18 offset, s16[4] locals, u32 aggregate copies, nested vs combined mode guards, declaration/prototype cleanup, source arithmetic variants. Next action: materially different ABI/layout hypothesis—model the 8-byte local as a named two-word aggregate or byte-addressed temporary that forces the compiler unaligned lwl/lwr sequence, while reducing live locals to restore the exact 0x48 frame; then vary declaration order/temporary lifetimes and re-submit >=8 distinct candidates.

## 2026-09-05

func_83008844: plateau at 1.0 (raw 1.0), mismatch section_layout_drift; tried families: jump_table_map; tie-pool no

## 2026-09-05

func_83000F98: matched (call_chain:three-arg:if-else), 4 iterations, agent codex

## 2026-09-05

func_830074C8: plateau at 0.0 (raw None), mismatch unknown; tried families: dispatcher_switch; tie-pool no

## 2026-09-05

func_830080AC: plateau at 1.0 (raw 0.95), mismatch immediate_drift; tried families: call-chain; tie-pool no

## 2026-09-05

func_83006798: time cap at 0.4953 (raw 0.1589) after 2400s, mismatch section_layout_drift; tried families: dispatcher_switch; tie-pool no

## 2026-09-05

func_83000020: matched (unclassified:init:struct-distinct-rhs-pointer), 3 iterations, agent codex

## 2026-09-05

func_83007100: matched (call_sequence:abi-pointers:local-state), 2 iterations, agent codex

## 2026-09-05

func_83000F04: plateau at 0.9474 (raw 0.9474), mismatch instruction_drift; tried families: call_sequence; tie-pool no

## 2026-09-06

func_83000058: matched (constant-map:record-struct:reverse-compare), 4 iterations, agent codex

## 2026-09-06

func_830080AC: matched (call-chain:stack-layout:struct-pair), 1 iterations, agent codex

## 2026-09-06

func_8300A50C: plateau at 0.0 (raw None), mismatch unknown; tried families: call_chain; tie-pool no

## 2026-09-06

func_8300A208: plateau at 0.0 (raw None), mismatch unknown; tried families: call_chain; tie-pool no

## 2026-09-06

TYPE CONFLICT: func_800088DC is extern void func_800088DC(void), not extern void func_800088DC()

## 2026-09-06

TYPE CONFLICT: func_818017A8 is extern void func_818017A8(void), not extern void func_818017A8()

## 2026-09-06

TYPE CONFLICT: func_80008648 is extern void func_80008648(void), not extern void func_80008648()

## 2026-09-06

TYPE CONFLICT: StageLoader_WaitForRetrace is extern void StageLoader_WaitForRetrace(void), not extern void StageLoader_WaitForRetrace()

## func_83007044: stored candidate genuinely wrong, not a stale-fix replay (2026-09-06) (2026-09-06)

Flagged as section_layout_drift 'stale_past_fix' at raw 0.9787 (the lowest score in this triage batch, and notably not 1.0 like its peers). The file's .rodata subsegment split (0xC9D30, covering jtbl_8300FBC4/FB00/FB18/FB6C/FB84/FBA8/D_8300FBA4) IS complete and correctly places jtbl_8300FB6C when spat auto-migrates it into func_83007044's own .s (confirmed via objdump: the dispatcher and all five case bodies' instruction sequences match the oracle exactly). Replayed the fleet's stored 0.9787 candidate ('dispatcher_switch:full-range:case-zero-s32-cast') unmodified through a from-scratch make COMPARE=1 gate: it compiles and links cleanly but the ROM does not match (deterministic, reproduced twice). Given the sub-1.0 raw score already flagged this as the shakiest of the batch, the candidate is simply wrong somewhere the isolated probe didn't catch -- do not replay it again without re-deriving the case values from jtbl_8300FB6C's actual words.

## 2026-09-07

func_8300A754: matched (call_sequence:struct_ret_first:canonical), 3 iterations, agent gemini

## 2026-09-07

func_830009D8: matched (call_sequence:substate_s32_pad5:typed_substate_s32_args), 1 iterations, agent gemini

## 2026-09-07

func_830016BC: time cap at 0.9608 (raw 0.8039) after 2415s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-07

func_83001DAC: matched (call_sequence:nested-status:pointer-reload-nonzero), 5 iterations, agent codex

## 2026-09-07

func_830073F8: time cap at 0.9808 (raw 0.7308) after 2409s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-07

func_83004218: matched (call_sequence:lookup:compare-switch), 7 iterations, agent codex
