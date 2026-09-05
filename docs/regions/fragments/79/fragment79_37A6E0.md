# Region notes -- disasm/src/fragments/79/fragment79_37A6E0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Unsolved shape: second-formal +0x10 cost (AGENTS.md §5, blocking as of 2026-08-28) (2026-08-28)

Adding a **second formal** to an already-accepted one-parameter function costs +0x10 of `.text` (IDO reserves an incoming-argument save area) regardless of the new parameter's type. This makes the `func_84111E50` fix unviable and leaves `func_841137F8`, `func_8411388C`, `func_8411B160`, `func_84115988` blocked. It is *not* a blanket N->N+1 rule: the same edit on `BattleAnim_ModelDispatch_044` produced zero drift. The probe's link-shape check reports it as `section_layout_drift` before any gate -- always probe a `companion_edits` change rather than reasoning about it.

## Unsolved shape: branch-likely null guard (AGENTS.md §5) (2026-08-28)

A leading null/zero guard that IDO emits as a branch-likely (`bnel`/`beql`) where every C spelling produces a plain `bne` -- `func_84112418`. The §4 guard-polarity row does not cover it.

## Box handoff (2026-08-30)

Accepted through link-verified full-ROM gates in this box: `func_84110F64`, `func_84113920`, `func_84113C54`, `func_8411957C`, `func_8411B304`, `func_8411A258`, `func_84116548`, `func_84116980`, and `func_8411A19C`. The `func_8411DC80` first formal was corrected to `u16` in its existing call sites after its `andi 0xFFFF` mask was confirmed by assembly.

- **requeue:** `func_8411D0A0` remains unresolved after initializer, raw-pointer, and temporary/declaration-order hypotheses plus a bounded permuter run. Best probe: normalized similarity `1.0000`, raw similarity `0.8478`; mismatch kind `register_allocation_only`; first diff instruction 24, expected `lui v1, ...` and produced `lui v0, ...` (the following `D_84191208`/`D_8419120C` pointer registers are swapped). Next action: try a materially different register-allocation spelling for the two post-call global pointer clears, then gate only a link-verified hit.

## Box handoff (2026-08-30, current) (2026-08-30)

Accepted through link-verified full-ROM gates: func_8410C934 and func_8410CAE4. Shared spelling: keep the active s16 third formal, declare func_8410B974 fourth parameter as s32, and read the baseline word home with *(s32 *)((u8 *)&arg2 - 2); C934 passes stack literal 1 and CAE4 passes 0. No evidence-backed names were available.\n\n- **requeue:** func_8410D9B8 and sibling func_8410DEB4 remain unresolved. D9B8 best current probe: normalized 0.9577, raw 0.5070, mismatch section_layout_drift, expected 272 bytes versus actual 284, first differing branch at instruction 12 (expected bc1fl target 0x70, actual target 0x74) caused by the extra trunc.w.s needed when the existing integer func_800371B4 prototype receives a computed float. Next action: obtain an accepted-prototype or ABI spelling for the float helper call without a jalr or source prototype conflict, then retry both siblings.\n\n- **requeue:** func_8410D5CC and sibling func_8410DAC8 remain unresolved. D5CC unrolled threshold-chain probe best: normalized 0.7610, raw 0.3028, mismatch operand_or_scheduling_drift, expected 1004 bytes versus actual 1000, first differing instruction 6 (expected lui 0x3fc0, actual lui 0x3f40); the typed helper cast also introduces jalr. The old-style helper declaration is compile_failed because func_800371B4 already has an accepted integer prototype; the direct integer-prototype spelling scored 0.7450 raw 0.1873 with a -40 expected versus -32 actual frame. Next action: resolve the helper prototype/ABI before repeating the unrolled chain.

## Box handoff (2026-08-30, diagnostic correction) (2026-08-30)

Correction for the D5CC requeue above: the 0.7610/0.3028 result used an incorrect 0.75f initial comparator and is not a valid best. With the verified 1.5f comparator, the typed fnptr-cast chain scored normalized 0.7450, raw 0.4462, section_layout_drift, expected 1004 bytes versus actual 984, first diff instruction 3 (expected frame -40, actual -32). The existing integer-prototype direct spelling scored normalized 0.7450, raw 0.1873, expected 1004 versus actual 940, first diff instruction 0. Requeue next action remains resolving the helper ABI/prototype.

## Accepted owner: func_8411B160 (2026-09-01) (2026-09-01)

Accepted via runner self-gating. Winning family direct:signed-byte: direct *(s8 *)(arg0 + 0x619) comparison, no hoisted record local, direct (*(u8 **)(arg0 + 0x2D4))[0x139D/0x139C] call arguments, existing old-style func_8411E50 call preserved. Valid batch had 8 candidates; prior_attempts was 24 at run time due concurrent/history rows. Earlier best was normalized 0.9730/raw 0.8649 with lbu-vs-lb at instruction 16; signed-byte batch initially frame-drifted when record was local. Final direct candidate link_verified=yes and accepted with auto_gate=true; full ROM gate passed, MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. Futility advised repeated-drift: 13 prior attempts sharing frame fingerprint, but this materially different signed-byte/direct-local hypothesis closed it.

## 2026-09-02 wave 53 (2026-09-02)

- requeue `func_84111C8C`: assembly and compile diagnostics prove this predicate receives the caller's `u8 *arg0`; the file's stale `extern s32 func_84111C8C(void)` and zero-argument call in accepted `func_841122D4` must be changed transactionally to `(u8 *)` and `func_84111C8C(arg0)`. With that companion edit, close variants compile and score. Historical probe stats retain a 0.9630/0.7407 body whose first difference is instruction 13 (`lw v0, 12(a0)` expected versus `lw t7, 12(a0)`), but wave-53 local callback/temp variants regressed to 0.7931/0.6207 and 116 versus expected 108 bytes with the same first register difference. Next action: reconstruct the exact historical `predicate:indirect-callback:combined-guard:A28` body under the working caller companion transaction, then target only the callback/result declaration order; do not continue from the larger local-callback forms.

## 2026-09-05

func_84113560: plateau at 0.0 (raw None), mismatch unknown; tried families: (none); tie-pool no

## 2026-09-05

TYPE CONFLICT: func_84103694 is extern void func_84103694(u8 *, s16), not extern void func_84103694(u8 *, u8)

## 2026-09-05

func_84115D4C: matched (call_sequence:guard:compound-index-temporary), 4 iterations, agent codex

## 2026-09-05

func_84111C8C: plateau at 0.0 (raw None), mismatch unknown; tried families: (none); tie-pool no

## 2026-09-05

func_84111CF8: plateau at 0.8276 (raw 0.7241), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-05

func_84112158: matched (call_sequence:table_stride:s32-index-expression), 3 iterations, agent codex

## 2026-09-05

func_8410F6AC: matched (call_sequence:stack-fifth:global-base), 2 iterations, agent codex

## 2026-09-05

func_84110718: time cap at 0.9796 (raw 0.9592) after 2401s, mismatch instruction_drift; tried families: call_sequence; tie-pool no

## 2026-09-05

TYPE CONFLICT: func_8410E73C is extern void func_8410E73C(u8 *, void *), not extern void func_8410E73C()

## 2026-09-05

func_84116604: matched (call_sequence:guard:direct-fields), 1 iterations, agent codex

## 2026-09-05

func_8411A310: time cap at 0.9796 (raw 0.9796) after 2401s, mismatch instruction_drift; tried families: call_sequence; tie-pool no

## 2026-09-05

func_84117DC4: plateau at 0.0 (raw None), mismatch unknown; tried families: call_sequence; tie-pool no

## 2026-09-05

func_84117CEC: plateau at 0.0 (raw None), mismatch unknown; tried families: call_sequence; tie-pool no

## 2026-09-05

func_8411862C: plateau at 0.0 (raw None), mismatch unknown; tried families: (none); tie-pool no

## 2026-09-05

TYPE CONFLICT: func_8411E164 is extern s32 func_8411E164(s32), not extern s32 func_8411E164()

## 2026-09-05

TYPE CONFLICT: func_8411E164 is extern s32 func_8411E164(u8 *), not extern s32 func_8411E164()

## 2026-09-05

func_8411A964: time cap at 0.963 (raw 0.5741) after 2400s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-05

func_84115E28: matched (call_sequence:guard-return:direct-fields), 1 iterations, agent codex

## 2026-09-06

func_84112464: time cap at 1.0 (raw 0.9844) after 2400s, mismatch immediate_drift; tried families: call_sequence; tie-pool no

## 2026-09-06

func_8411283C: time cap at 0.9531 (raw 0.8281) after 2409s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-06

func_84113D7C: matched (call_sequence:flag-chain:cast-table), 1 iterations, agent codex
