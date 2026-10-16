# Region notes -- src/fragments/49/fragment49_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-15

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-09-15

func_86100874: time cap at 0.9655 (raw 0.5517) after 2402s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-16

func_86108B28: matched (call_sequence:bubble:byte-temp-exact), 1 iterations, agent codex

## 2026-09-16

func_86103B74: matched (call_sequence:scale:block_local_before_position), 5 iterations, agent codex

## 2026-09-20

func_86101E04: matched (float_math:compound-scale:seed-limit-with-coefficient), 2 iterations, agent unbiased

## 2026-09-20

func_861024C8: matched (call_chain:early_return:recomputed_field_addresses), 1 iterations, agent unbiased

## 2026-09-20

func_8610320C: matched (state_field_access:stack-offset:unused-word-before-latch), 4 iterations, agent unbiased

## 2026-09-20

func_86100F1C: matched (call_chain:object-representation:typed-union-coordinate-fields), 3 iterations, agent unbiased

## 2026-09-20

func_86107EBC: matched (call_sequence:raw-gfx:decomp-permuter-no-locals), 9 iterations, agent codex

## 2026-09-20

func_86102E8C: matched (call_sequence:verified:cached-floats), 2 iterations, agent codex

## 2026-09-29

func_86100120: matched (bounded_lookup:typed-merge:reload-index-after-guard), 2 iterations, agent unbiased

## 2026-09-29

func_86100020: matched (constant_map:byte-parameter:direct-expression), 1 iterations, agent unbiased

## 2026-09-29

func_86105C30: plateau at 1.0 (raw 0.9524), mismatch immediate_drift; tried families: call_chain; tie-pool yes

## 2026-09-29

func_86106044: matched (call_chain:position-first:all-position-stores-before-scale), 2 iterations, agent unbiased

## 2026-09-29

func_861072AC: matched (call_chain:call-result-expression:scale-load-in-call-comma), 7 iterations, agent unbiased

## 2026-09-30

func_86102D50: matched (call_chain:joint-selection:explicit-else-for-both-latches), 2 iterations, agent unbiased

## 2026-09-30

func_86102C08: plateau at 0.0 (raw None), mismatch unknown; tried families: call_chain; tie-pool no; 6 iteration(s) with a suspicious identical batch-wide failure

## 2026-09-30

func_8610109C: matched (large_mixed:collision:flexible-record-index), 1 iterations, agent codex

## 2026-10-04

func_86102FF0: plateau at 1.0 (raw 0.981), mismatch register_allocation_only; tried families: call_chain; tie-pool yes

## 2026-10-04

func_8610916C: matched (call_chain:cursor-rebase:reuse-cursor-after-lookup), 2 iterations, agent unbiased

## 2026-10-04

func_86105508: plateau at 1.0 (raw 0.9727), mismatch immediate_drift; tried families: call_chain; tie-pool yes

## 2026-10-16 guarded record dispatch

func_861049C0: accepted by the normal native candidate runner with link verification and a full-ROM match (MD5 1561c75d11cedf356a8ddb1a4a5f9d5d). Indexing (*(u8 (**)[0x2C])&D_8610AD20) before adding 0x8DE0 reproduces the context/index register order; direct integer sums did not. A void ** local retains the pointer at sp+0x1C across both calls. The empty padding helper reproduces the verified duplicate jr/nop tail. Accepted-only redundant declaration cleanup passed another full-ROM gate. No evidence-backed name was available.

## 2026-10-16

func_861000B8: matched (stack-buffer:s8-record:padding-tail), native runner accept on the private baseline; IDO frame 0x28, s8[4] buffer at sp+0x24, callee passes (&data, 0x7F, *(f32*)((u8*)arg0+0x48), -364.4109191894531f, D_8610AA84), data[1]=0, then func_800277C4(arg1, arg0->[0x23], &data); duplicate jr/nop tail via empty func_861000B8_padding(). Callers' void (void*, u16) prototype retained (2 call sites in this file). No evidence-backed name.
