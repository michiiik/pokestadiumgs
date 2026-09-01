# Region notes -- disasm/src/fragments/79/fragment79_393CA0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: record-stride forwarding wrapper (AGENTS.md §4) (2026-08-28)

Record-stride forwarding wrapper (overlay fragments) -- `helper(&BASE[BASE[idx_field] * STRIDE], a0, ...)` with the remaining formals forwarded verbatim; the clamp variant is `idx = BASE[idx_field] - 1; if (idx < 0) idx = LAST;` then the same forward. Evidence: 12 (bases `D_84195280` stride 0x280, `D_84195208`, `D_841951F8`). Limit: argument widths vary per owner (`u8`/`s16`/`u16`, 5th arg stack-passed) -- read each `.s`.

## Verified spelling: pointer-table guard lookup (AGENTS.md §4) (2026-08-28)

Pointer-table guard lookup -- `if (arg0 < 4) { u8 *ptr = D_84186160[arg0]; if (ptr) helper(ptr, ...); }`. Evidence: 2 (`func_84134D80`, `func_84135B8C`). Limit: a `ptr + 8` variant exists; pick by the offset in the `.s`.

## Verified spelling: dead tail longer than one jr/nop pair (AGENTS.md §4) (2026-08-28)

When `symbol_size_drift` is more than 8 bytes short, add N uniquely-named trailing `void <owner>_paddingK(void) {}` helpers; `#pragma C_FUNCTION_PADDING` did not reproduce it. Evidence: 1 (`func_841352DC`). Limit: one owner so far; prefer the pragma first.

## Unsolved shape: incoming-argument stack-home spill (AGENTS.md §5) (2026-08-28)

An incoming-argument stack-home spill (`sw a0, N(sp)` with no intervening call) that no C spelling reproduces -- the single most common dead end in fragment work: 7+ owners in this file alone. Drop an owner as soon as its first diff is this.

## Fleet box 2026-08-30 accepted spelling and requeue (2026-08-30)

Accepted through the runner and full ROM gate: func_84129A80 with exact label init:raw-fields:repeated-direct-pointer. Probe reported probe_match with link_verified=true; the gate reported batch_status=accepted and rebuilt the baseline ROM (MD5 1561c75d11cedf356a8ddb1a4a5f9d5d). Requeue func_8412E220 after 35 probe attempts across five probe-only batches: best label predicate:loop:frame-padding-8:decl-limit-result-ptr, normalized similarity 1.0000/raw 0.7069, exact expected/actual size 232 bytes, mismatch register_allocation_only at expected lw t2, 0x1c(sp) versus actual lw t4, 0x1c(sp). The initial m2c/direct/loop/pointer/guard/raw-offset and declaration variants were immediate_drift with expected frame -0x28 versus actual -0x20; documented frame-padding variants reached the expected frame and size but did not resolve the register tie. The runner futility was repeated-drift after 12 prior rejected attempts sharing fingerprint [immediate_drift,3,0,0x27bdffd8,0x27bdffe0]. Next action: use an address-observable stack-slot layout or the permuter on the exact-size compact frame-padding form; do not repeat the current frame-padding declaration permutations.

## Fleet box 2026-08-30 follow-up (2026-08-30)

Accepted func_84130558 via call-group:status-check:clear-inside-nonzero-state: probe_match with link_verified=true, full ROM gate accepted, rebuilt ROM MD5 1561c75d11cedf356a8ddb1a4a5f9d5d; evidence-backed name BattleAnim_Table_84186004_058 applied in source; commit e5607445. Accepted func_8413202C via compare-dispatch:guard-return:callee-u8-second-s32: probe_match with link_verified=true, full ROM gate accepted with the same rebuilt ROM MD5; no evidence-backed name available; commit d599c787. Requeue func_841255AC after 12 new probe attempts: best ratio:return-u8:reverse:temp-pointer sim 0.9250/raw 0.6500, expected/actual 164/168 bytes, first diff offset 16 expected beq a2, zero, 34 versus actual or a3, a0, zero; preserve the documented incoming-argument stack-home spill skip and do not repeat return-type variants unless the home-spill model changes. Requeue func_84135F94 after 13 probe attempts and a 60-second permuter pass: best state-dispatch:direct-switch:result-first sim 0.9062/raw 0.8438, exact expected/actual size 128 bytes, first diff offset 39 expected beq v0, at, 15 versus actual beq v0, at, 11; remaining issue is case-3/case-4 body layout, with no permuter improvement or candidate output; next action is a materially different compiler-layout hypothesis.

## Fleet box 2026-08-30 acceptance update (2026-08-30)

Supersedes the func_84135F94 requeue above: the recovered case-order 1,2,4,3 spelling state-dispatch:case-order-1243:result-first:direct-field produced a probe_match with link_verified=true and passed the full ROM gate with rebuilt ROM MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. The runner reported register-tie futility for the prior 7 attempts; no evidence-backed name was available. Commit db988435.

## Fleet box 2026-08-30 ratio and state-copy follow-up (2026-08-30)

Accepted func_84125650 through ratio-wrapper:do-loop:raw32:permute-zero-empty-guard. The probe was link_verified=true and the full ROM gate accepted it with rebuilt ROM MD5 1561c75d11cedf356a8ddb1a4a5f9d5d; the compiler tie was resolved by the empty if (!arg0) guard found by a 60-second permuter pass. No evidence-backed name was available. Commit 22e880b9. Requeue func_841358B0 after the aligned-copy probe batch and a 60-second permuter pass: the best direct typed-record candidate was exact-size 232 bytes with normalized similarity 1.0000/raw 0.7241, mismatch register_allocation_only, first diff offset 0 expected lui v0, 0x0000 versus actual lui v1, 0x0000, with the corresponding D_84195280 base and later counter-register swaps. The byte-array overlay was rejected as section_layout_drift because it emitted unaligned lwl/lwr/swl/swr and 264 bytes; aligned u32[0xA0] overlays restored 232 bytes but did not resolve the global/register tie. The permuter timed out at 60 seconds with best score 45. Next action: use a materially different address-observable global/record declaration or defer; do not repeat the aligned-word declaration variants.
## Wave 20 register tie (2026-09-01)

register-tie/requeue: `func_84126E88` received 40 new runner-only variants (43 total attempts) across four batches. The best `pack:u16:baseline-casts` body was exactly 84 bytes with normalized `1.0000` but raw `0.5714`; the stable mismatch at offset 42/instruction 10 is expected `or $t8, $t3, $t5` versus actual `or $t6, $t3, $t5`. Formal-width, explicit-cast, stack-home, sequential-temporary, OR-association, term-order, low-field, multiply/add, and declaration variants did not move the tie; no link verification or gate was attempted. Next action: use the permuter or a materially different ABI/global/address model, not more u16 expression permutations.

## Fleet requeue: func_84135B40 stack-home blocker (2026-09-01) (2026-09-01)

requeue: Fresh owner (prior_attempts=3) received 16 runner-only variants in two eight-candidate batches. Batch 1 forwarding arithmetic/declaration forms all probe_rejected at 76 bytes, normalized/raw 0.8421 (shift-add raw 0.6842), with stable first diff offset 24: expected sw $a0, 24($sp), actual branch setup op/0x1 $at,$v0,2; expected and actual size 76. Batch 2 materially changed to address-observable, volatile, local-copy, and local-slot stack-home hypotheses; best remained 76 bytes normalized/raw 0.8421 with the same fingerprint, while volatile forms changed frame to 80/84 bytes and local-slot one compile_failed due unrelated missing prototype. No link_verified result, auto-gate, acceptance, or full-ROM gate. Attempted families: direct index/ptr temp/mul-add/explicit offset/shift-add; volatile arg/pointer/copy; address-of-arg; local stack copy. Next action: reconstruct the compiler ABI/address-observable incoming argument home spill (or use the permuter on the exact 76-byte forwarding form); do not repeat ordinary arithmetic/declaration variants. Owner remains blocked by documented incoming-argument stack-home spill.
