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
