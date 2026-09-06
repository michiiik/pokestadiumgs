# Region notes -- disasm/src/fragments/17/fragment17_113A60.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-30 fleet box: func_822072D0 requeue (2026-08-30)

requeue: func_822072D0 (81 instructions, call_sequence). This box made 65 isolated runner probes across batches 1-10; every attempt was probe_rejected with mismatch_kind=operand_or_scheduling_drift, link_verified absent, and no full-ROM gate was run. Best evidence: labels call-sequence:m2c-raw:switch-byte-offsets and call-sequence:implicit-helper-types:m2c-raw reached similarity_score=0.8765, raw_similarity_score=0.3704, expected_size=324, actual_size=324; the repeated first-difference fingerprint is offset 3, expected addiu $sp,$sp,-88 versus actual addiu $sp,$sp,-80. The next early mismatch is expected lw v1,20(a1) before the dispatch setup versus a branch before that load; later bytes are largely the same call/control-flow shape. Exhausted for this box: raw and typed global overlays for D_8220DAAA/D_8220DAC8/D_8220F9D8, if and switch forms, pointer/address-cast and direct-index spellings, preloaded/hoisted table and record pointers, explicit call temporaries, volatile carriers, typed context/resource/pair overlays, implicit versus exact helper prototypes, declaration-order permutations, and semantically live sp54/sp38 carriers. Runner futility_summary is stuck: 65 attempts, best 0.8765; this is not a terminal register-tie or prerequisite result. Carry forward the best m2c raw byte-offset spelling as evidence only, and reserve the oldest requeue owner for the next box. Next action: change the compiler source-shape family materially by revisiting declaration/prototype/temporary lifetime ordering to force the pre-dispatch table-address arithmetic and the target spills at sp+0x54 and sp+0x38; do not repeat the exhausted variants. Skip first: func_82209EA8 remains jump-table-unready and was not selected.

## 2026-08-30 fleet box continuation: final ABI probes (2026-08-30)

requeue: The final ABI-shape batch added 4 probe-only candidates (cumulative 69 isolated probes). All remained probe_rejected with mismatch_kind=operand_or_scheduling_drift and link_verified absent. The register-index spelling improved raw_similarity_score to 0.3951 at similarity_score=0.8765 but produced actual_size=324 with a 0x48 frame, not the expected 0x58; the other old-style/parameter-order variants remained at the 0x50-or-smaller frame. A runner-mediated 90-second permuter pass on the strongest 324-byte candidate timed out without a clean result (best score 1575); its only source change was an artificial no-op condition and is not compiler-faithful. No candidate was installed, named, gated, committed, or pushed. Preserve the prior next action: resume func_822072D0 in a later box with a materially new declaration/prototype/temporary-lifetime hypothesis, not these exhausted ABI/global/volatile variants.

## 2026-08-30 fleet box closure: permuter candidate rejected (2026-08-30)

requeue: The final runner-mediated probe of the 600-second permuter best (score 90) was probe-only and rejected: expected_size=324, actual_size=324, 81/81 normalized instructions, but raw_similarity_score=0.7531, similarity_score=1.0 only because normalization hid register/field differences; mismatch_kind=immediate_drift with first_diff_offset=3, expected addiu $sp,$sp,-88 and actual addiu $sp,$sp,-112. link_verified was absent and no gate ran. The permuter candidate included a non-semantic empty if and is not installable. Cumulative owner evidence is 70 isolated runner probes plus two bounded permuter passes; func_822072D0 remains a requeue, with no source installation or accepted spelling.

## Wave 6 handoff (2026-08-31)

Wave 6 handoff: func_82209F50 unresolved after 10 serial CC_CHECK=1 probes. Best normalized/raw similarity was 1.0000/0.8902 with immediate_drift; expected frame -56 (0x38 bytes), actual -48. Next retry should force the 0x38-byte frame/local lifetime while preserving the m2c float expression and stack spills.

## 2026-08-31 shared-checkout probe guard (2026-08-31)

tooling-blocked: func_822075D0 was selected as the fresh family-unlocking owner (0 prior attempts) and received 9 CC_CHECK=1 probe-only candidates. Best was call-sequence:family-sibling:switch-raw-offsets at similarity 0.8765, raw 0.3704, expected/actual size 324/324; all candidates shared the first-diff fingerprint at offset 3: expected addiu $sp,$sp,-88, actual addiu $sp,$sp,-80. The first model left the sp54/sp38 carriers dead. A second batch with explicit post-call reloads was prepared but not run because the shared checkout has foreign modified source (disasm/src/fragments/20/fragment20_12C460.c), extensive concurrent dirty work, and a live claims entry. Do not probe/build/commit over that guard. Next action: when the checkout is clean and claims are reconciled, run the prepared carrier-lifetime batch, keeping func_822075D0 active; it explicitly reloads sp54 after func_8004C990 and sp38 after func_8004CA60 before record/table address formation. No source candidate was installed or gated.

## 2026-09-02 func_8220A098 box (2026-09-02)

requeue: func_8220A098 (47 instructions, call_sequence). Two CC_CHECK=1 probe-only batches ran (16 candidates total); all candidates were probe_rejected except one compile_failed, with no link_verified result and no full-ROM gate. Best normalized/raw similarity was 0.9362/0.7872 in batch 1 (188/188 bytes), and 0.9362/0.7447 in batch 2 (188/188). Repeated mismatch fingerprint: first_diff_instruction=1, first_diff_offset=1, expected `lui $v0, %hi(D_822106B0)` versus actual `lui $t6, %hi(D_822106B0)`; the strongest forms otherwise preserve the expected 0x30 frame and call sequence. Attempted families: typed-array direct expression with u8/void/s32 argument forms; explicit flag temporary; conditional-negation and zero-subtraction forms; split vector temporaries; explicit base-pointer lifetime/order; explicit destination pointers; negated temp; float second-argument temporary. The flag-first variants drifted at instruction 4 and changed size; one explicit destination form failed CC type checking. Next action: materially change declaration/register lifetime ordering to make the D_822106B0 address carrier allocate in v0 (likely place the array/base expression after an explicit local destination or use compiler-faithful pointer parameter/struct shape), then vary helper prototype spelling/order while preserving the early flag load before frame setup. Do not repeat direct typed-array or simple base-pointer bodies. Historical jump-table-unready func_822072D0/func_822075D0 were not touched. No source candidate installed, named, gated, committed, or pushed.

## 2026-09-02 func_822088FC acceptance (2026-09-02)

accepted: func_822088FC. Nine distinct CC_CHECK=1 candidates were submitted through the runner; hypothesis-2 produced link_verified=true with exact 22/22 instructions, expected_size=actual_size=88, and the combined full-ROM gate accepted it. Best rejected diagnostics included normalized/raw 1.0/0.9091 immediate_drift at first_diff_instruction=3 (expected sw zero,28(sp), actual sw zero,24(sp)); other variants had operand_or_scheduling_drift or instruction_drift. Installed spelling uses result initialized before the helper call, a separate value temporary, and explicit s16 pointer stores through D_8220DA08. Do not touch historical jump-table-unready func_822072D0 or func_822075D0.

## Accepted owner: func_822071E8 (register tie closed) (2026-09-06)

Closed a register_allocation_only tie (11 prior attempts at similarity >=0.99, no permuter attempt on record). tools/permute_candidate.py found a score-0 variant: inlining the 'index' local (used once) directly into the array-subscript expression instead of computing it as a separate assignment first. Verified with tools/fleet_probe.py --gate: accepted, link-verified, full-ROM COMPARE=1 gate MD5 1561c75d11cedf356a8ddb1a4a5f9d5d.

## 2026-09-07

func_8220AC38: plateau at 0.9167 (raw 0.75), mismatch operand_or_scheduling_drift; tried families: state-field; tie-pool no

## 2026-09-07

func_82205A14: matched (state-field:switch:cases-zero-one), 2 iterations, agent codex

## 2026-09-07

func_82206950: plateau at 0.9048 (raw 0.619), mismatch operand_or_scheduling_drift; tried families: state-field; tie-pool no

## 2026-09-07

func_8220A154: matched (call_chain:switch:typed-s32), 2 iterations, agent codex

## 2026-09-07

func_82205A8C: matched (state-field:nested-if:direct-offsets), 1 iterations, agent codex

## 2026-09-07

func_82206124: matched (state-field:early-return:switch-goto-done), 5 iterations, agent codex
