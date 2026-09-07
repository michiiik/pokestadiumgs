# Region notes -- disasm/src/fragments/14/fragment14_FAD40.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 6 handoff (2026-08-31)

Wave 6 handoff: func_813035A0 unresolved after 18 serial CC_CHECK=1 probes. Best normalized/raw similarity was 0.9762/0.1190 with operand_or_scheduling_drift; repeated fingerprint was expected lui $t7, 0x0002 but actual lui $v0, 0x0002. Preserve the 0x20-byte frame and force the late global-base load into a dedicated temporary before retrying.

## Wave 16 handoff (2026-08-31) (2026-08-31)

requeue: func_81302CB4 (fresh, prior_attempts=0; 105 instructions, expected frame 0x28). Best normalized/raw similarity was 0.7429/0.5048 with operand_or_scheduling_drift; first diff expected stack adjustment -40 but actual -48. Tried raw-offset and m2c coordinate-helper shapes; one K&R struct-selector form compile-failed. Next reduce float temporaries/spills, retain sp18 plus saved a1, preserve the one-argument D_8160BD08 call, and reorder declarations.

## Wave handoff (2026-09-02) (2026-09-02)

requeue: func_81303D60 (48 instructions; initially fresh, prior_attempts now 16). Three batches / 24 distinct candidates were probed with host CC checks enabled; no link_verified hit and no full-ROM gate. Batch 1 used 6-argument tail hypotheses and produced frame drift (best normalized/raw 0.8333/0.4792, expected addiu sp,-96 vs actual -56). Batch 2 corrected the tail to eight arguments (four registers plus stack args) and reached best normalized/raw 0.9792/0.8333, expected frame -96 vs actual -72. Batch 3 added an explicit 0x18-byte local gap, producing expected 192-byte size/frame; best normalized/raw remained 0.9792/0.8333, mismatch_kind operand_or_scheduling_drift, first-diff fingerprint at offset 23: expected addiu $a1,$sp,52 but actual addiu $a1,$sp,68 (pad placement variants produced $sp+92). Tried families: raw/index and pointer record arithmetic; six- vs eight-argument helper ABI; state temporary vs conditional expression; declaration-order, explicit pointers, array indexing; explicit 0x18-byte byte/word padding and pad placement. Concrete next action: model the two 8-byte buffers as a typed local overlay or separate fields forced to offsets sp+0x34 and sp+0x3c, while reserving the 0x18 gap after them and keeping saved index at sp+0x5c; then submit a fresh >=8 batch varying only overlay/member offset and declaration order. Do not gate current candidates.

## 2026-09-08

func_81304788: plateau at 0.9841 (raw 0.9683), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-08

func_8130456C: time cap at 0.9552 (raw 0.6119) after 2400s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-08

func_81304884: matched (call_sequence:scan:do-while-record-before-global), 1 iterations, agent codex

## 2026-09-08

func_813031D8: plateau at 0.0 (raw None), mismatch unknown; tried families: call_chain; tie-pool no

## 2026-09-08

func_81304678: matched (constant-map:direct-guard:gotos-inline), 3 iterations, agent codex

## 2026-09-08

func_81302CB4: plateau at 0.819 (raw 0.5429), mismatch operand_or_scheduling_drift; tried families: state_field_access; tie-pool no

## 2026-09-08

func_813033DC: matched (call_sequence:stack-struct:u32-prefix-buffer), 8 iterations, agent codex

## 2026-09-08

func_81304178: matched (call_sequence:field-init:arg1-before-state), 2 iterations, agent codex
