# Region notes -- disasm/src/fragments/66/fragment66_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-29 fleet box (2026-08-29)

Accepted func_82E02828 with label call-chain:state-switch:local-state. Spelling: s32 state = arg0; switch (arg0); case 0 checks StageContext_GetFadeMode() == 0 and sets state = 1; case 1 calls func_82E030B0, then when D_82E05440 != 0 sets state = 2 before StageFade_StartFromTransparent(5) and func_800225C4(0xA); case 2 checks StageContext_GetFadeMode() == 1 and sets state = 3. Probe and gated result had link_verified true; the combined full ROM gate accepted with one gate run. Deferred func_82E04734 after two probe batches: state-field:record-struct:array-index reached normalized similarity 1.0 but raw similarity 0.1667 with register-allocation-only drift, so it was not gated. Deferred func_82E00700 after 12 variants: best compiling result was 0.8667 similarity and 0.7667 raw with instruction drift; other m2c-shaped variants hit old IDO declaration-after-statement compile errors. Deferred func_82E047C4 after 7 gbi-macro variants: best was about 0.83 similarity and 0.425 raw with instruction drift; the command stream used gbi.h macros but still missed the expected auxiliary register setup around s7 = 0xF0. Do not use words.w0 or words.w1 if revisiting.

## 2026-08-29 fleet box continuation (2026-08-29)

Accepted func_82E02658 with label call-sequence:array-symbol-address:exact-shape. The m2c call-sequence spelling matched after changing the final indexed record expression from the pointer value D_82E07600 to the symbol address: (*(s32 **)((u8 *)&D_82E07600 + (D_82E06164 * 4)))[2]. This removed two extra loads and aligned the branch target. Probe was exact with link_verified=true; full COMPARE=1 gate accepted with ROM MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. func_82E02378 remains a register-allocation tie after 20 variants: repeated first diff expected addiu $at,1 versus actual addiu $v1,1, best normalized/raw 0.8841/0.7246; do not reopen in this box. func_82E01898 reproduced runner probe_unavailable/list index out of range for 8 well-formed candidates; treat as diagnostics-path evidence, not a source rejection. func_82E02508 reached 0.9419/0.9070 with the m2c initializer after correcting D_82E07600 to its existing void * declaration; its first diff was post-initialization scheduling around main_pool_push_state and was not gated. Keep all user-provided exhausted/dispatcher skip owners unchanged.

## 2026-08-29 fleet box final diagnostics

Deferred func_82E02508 for this box. After func_82E02658 was installed, retrying the otherwise promising initializer exposed declaration-context failures: without declarations the target had undefined symbols and a duplicate main_pool_push_state; injected file-scope declarations conflicted with later D_82E07604/D_82E07608 declarations; block-scope externs reproduced the same CFE redeclarations. Preserve the 0.9419/0.9070 probe result, and improve the runner to inject only declarations visible before the target or to isolate candidate declarations from later file declarations. Final skip list for this box: func_82E02378 (20-variant register tie), func_82E01898 (8-variant probe_unavailable diagnostics defect), func_82E02508 (declaration-context defect), plus the previously listed exhausted and dispatcher/jump-table owners.

## 2026-09-02 fleet box func_82E0292C (2026-09-02)

requeue: prepared 8 novel compiler-faithful call-sequence candidates in /private/tmp/gs48_func_82E0292C_batch.json; no runner invoked and therefore no scores/fingerprint yet. Assembly fingerprint: 81 instructions, frame 0x48, func_80055948(3), func_80055EF0 output at sp+0x24 with mode from arg1 halfword, D_82E07610 set from byte sp+0x31, then display-list/resource setup and cleanup. Attempted families: locals-before-calls, explicit flag temporary, ternary flag, pointer/address-mask, stack argument, declaration order, segment temporary, split cleanup. Next action: run the batch through the runner in a serialized transaction, then record normalized/raw score, mismatch kind, first-diff fingerprint, and gate status.

## Wave 48 coordinator replay (2026-09-02)

requeue; the original 8 call-sequence candidates reached best similarity 0.9753 raw 0.8765 with an 8-byte frame overshoot, expected -0x48 versus actual -0x50. A focused byte-workspace repair improved raw similarity to 0.9136 with exact 324-byte size, but still mismatched at instruction 12: expected sw ,76(sp), actual addiu ,3. The repair tried byte workspace, named status field at offset 0xD, pointer status, explicit byte, status temporary, ternary, and reordered forms. Next action: force the target formal home stores through an address-taken or accepted prototype/lifetime shape without adding locals, then gate the first link-verified hit.

## 2026-09-02 fleet box final handoff (2026-09-02)

requeue: prepared 8 novel formal-home/lifetime candidates in /private/tmp/gs49_func_82E0292C_batch.json; runner intentionally not invoked per box instruction. Prior best remains normalized 0.9630, raw 0.9136 at exact 324-byte owner size. Stable fingerprint: instruction 3/offset 12 expected sw $a0, 0x48($sp) but prior actual addiu $a0, $zero, 3; corresponding expected instruction 6/offset 24 sw $a1, 0x4C($sp) was absent. Attempted hypotheses in this batch: address-taken arg0, address-taken arg1, both anchors, post-call formal reads, volatile formal anchors, explicit home writes after first call, and opaque arg0 lifetime. All preserve the 0x20 byte workspace/status-byte model and exact signature; no candidate/declarations identity was repeated from full probe history. Next action: run this batch through the serialized runner; if home-store candidates still drift, investigate compiler parameter-spill scheduling or accepted prototype/lifetime idioms.

## 2026-09-02 fleet box count correction (2026-09-02)

Correction: the JSON batch contains 9 candidates (not 8); all are novel and JSON-validated.

## Wave 49 coordinator replay (2026-09-02)

requeue; 9 formal-home candidates compared after the prior 0.9630 normalized and 0.9136 raw near miss. Best new result was 0.8642 normalized and 0.7407 raw, with the target home store still displaced and frame or early-call drift. Tried formal-address, formal-lifetime, formal-home, and address-anchor variants. No link verification or gate. Next action: model the compiler emitted formal-home stores without adding address-anchor locals, likely by matching the original parameter use and one byte workspace exactly.

## 2026-09-02 fleet box formal-home batch (2026-09-02)

requeue: prepared 8 novel complete-function candidates in /private/tmp/gs50_func_82E0292C_batch.json; no runner invoked per instruction. Prior best remains normalized 0.9630, raw 0.9136 at exact 324-byte owner size. Stable fingerprint: instruction 3/offset 12 expected sw $a0, 0x48($sp) and instruction 6/offset 24 expected sw $a1, 0x4C($sp), with prior actual addiu $a0,$zero,3 and absent second home store. Attempted hypotheses: comma-expression formal anchors in both orders, post-call comma anchors, conditional self-use of each formal, logical anchor branches, and short-circuit formal anchor; all retain u8 work[0x20], status work[0xD], exact s32/s16* signature, and shared real declarations. Next action: run this batch through the serialized runner; if still displaced, investigate compiler parameter-spill scheduling or accepted prototype/lifetime idioms.

## Wave 50 coordinator replay (2026-09-02)

requeue; 8 formal-home candidates compared with no link verification. Every result repeated the same instruction-12 fingerprint: expected sw ,76(sp), actual addiu ,3, with best similarity 0.8148 raw 0.7037 and exact target size 324 versus candidate 292. Next action: change the function parameter-use model to emit both formal home stores before func_80055948 while retaining the exact byte workspace; consider a permuter or accepted companion ABI hypothesis.
