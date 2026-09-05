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

## Fleet box 2026-09-01 (tree-1) requeues (2026-09-01)

Accepted through the runner and full ROM gate: func_84126200 and func_84126260 (compare-dispatch pair over ptr=D_841951F8[arg0]: if (ptr[0xA] < ptr[3]) branch A else branch B, forwarding arg0 into func_841260D4 with swapped literal/ptr[8] operands per branch -- see AGENTS §4 compare-dispatch row, now 2 more instances). func_84129D3C (byte-argument loop guard: for (i=0;i<4;i++) if (func_84129C8C((u8)i)) return 1; return 0;). func_8413882C (bounded-lookup guard-return over the same D_841951F8[arg0] flag: if (ptr[0x12]!=0) { if (ptr[0xA]<ptr[3]) return arg1>=ptr[3]; return arg1<ptr[3]; } return 1; -- note the outer guard had to be phrased as ptr[0x12]!=0 wrapping the real logic, NOT the mirror 'if (ptr[0x12]==0) return 1;' guard-clause-first form: IDO picks beql for the first shape and bnel for the second, and only the wrapping form byte-matched). func_84126320 (s32 wrapper forwarding into func_84126200(void-returning)/func_84126064(s32): the accepted shape lets the true-branch call the void func_84126200(arg0) as a bare statement and 'falls off the end' of the s32 function -- IDO leaves v0 with func_84126200's last callee's leftover value and the bytes match; only the inline-pointer-expression form ((u8 *) D_841951F8[arg0])[0x12] hit this exactly, a named 'u8 *ptr' local did not). func_84124DEC (predicate branch on D_841951BC; the only fix needed over the literal-transcribed body was commuting the equality compare to 'arg0 == D_841951BC' instead of 'D_841951BC == arg0' to resolve a register_allocation_only tie at raw 0.9545, and explicitly declaring both func_84134E00(u8) and func_84134E30(s32) in the batch declarations -- see tooling note below).

## Fleet box 2026-09-01 (tree-1) requeues and tooling notes (2026-09-01)

Tooling notes: (1) tools/permute_candidate.py fails immediately with ModuleNotFoundError: No module named 'toml' in this checkout (disasm/tools/decomp-permuter's own dependency, not pip-installable here without --break-system-packages on the system Python) -- the permuter escape hatch is unavailable in gs-fleet-1 right now, worth fixing centrally. (2) When a probe candidate calls a same-file function defined LATER in the file and that callee is NOT named in the batch's own declarations string, the runner's auto-injected forward declaration is a full duplicate of the callee's actual body (not a prototype), which IDO then rejects as a hard redeclaration/incompatible-return-type error at the callee's real definition site -- reproduced repeatedly for func_84134E00 across several batches with different (and even empty) declarations blocks, and only fixed by explicitly listing every later-defined same-file callee (both func_84134E00 and func_84134E30) in the batch declarations myself. This contradicts the documented 'you do NOT need to hand-declare cross-file callees... the runner injects a declaration when every file agrees' guidance for same-file forward references and cost several wasted batches; worth a look from the tooling side.

## Fleet box 2026-09-01 (tree-1) permuter-verified acceptances (2026-09-01)

Confirmed the permuter is working (fix in 9e9a92b0): func_84137CA4 (flag-clear-sequence, three D_84199D81 bit clears) had plateaued for waves at sim 1.0000/raw 0.5833, a pure register tie at the first instruction (lui $t6 vs $v0). A 300s permuter pass timed out (base_score 65, best_score 10, no zero) but its best output showed a re-read of *addr before the first clear; combined with the region's verified 16-bit AND-mask literal form (0xFFFE/0xFFFD/0xFFFB, not 0xFE/0xFD/0xFB), that closed it: accepted via state_field_access:flag-clear-sequence:reread-first:mask16-all, gate accepted, ROM MD5 1561c75d11cedf356a8ddb1a4a5f9d5d, commit 5557ce4a. func_8412BF4C (bounded-lookup guard, requeued at 0.9268/164-vs-160 bytes) stayed pinned at exactly one extra instruction (raw 0.7805, first diff always the 'b .L8412BFDC' branch's displacement, 26 vs 27) across every loop-form/index-type hand variant; its call to func_84124EFC was also blocked by a wrong void return type on that still-ASM callee (see below). A 70s permuter pass on the closest hand candidate found a zero score by casting the loop index: '((unsigned long) i) + 5' instead of 'i + 5'. Accepted via bounded_lookup:guard-loop:permuter-ulong-index-cast, gate accepted, same ROM MD5, commit c7ad81e5.

## Fleet box 2026-09-01 (tree-1) callee-ABI fix and companion-edit acceptances (2026-09-01)

func_84124EFC was declared 'extern void func_84124EFC(u8, u8 *);' but its .s branches on $v0 after the jal: it is a 0xFF-sentinel byte scan returning 1/0. Decompiled it directly (scan_sentinel:while-ptr-inc, exact byte match) and retyped its return to s32 via a companion edit to the ONLY other declaration in the file (func_8412517C's forward extern at the time) -- gate accepted, commit 61512039. This is the AGENTS Sec.2.5 step5 callee-ABI-hypothesis-failure case, but note the companion_edits mechanism could NOT fix func_84124EFC's own extern in the same batch as its own pragma-replacement candidate: apply_companion_edits runs on the untouched on-disk baseline before the primary candidate substitution, so 'function is still a GLOBAL_ASM pragma owner' always fires for a self-referential edit. The workaround: attach the edit to a DIFFERENT already-accepted anchor function (func_8412517C) whose text block happens to contain the stale extern line, since the check only looks at whether the NAMED anchor function is still pragma-owned, not what text the edit touches. Separately, func_841262C4 needed the same trick against func_84126260 (already-accepted, so no workaround needed) to retype it void->s32 for a 0-vs-value predicate: accepted via guard:no-ptr-local:zero-lt, commit 2ad7220a.

## Fleet box 2026-09-01 (tree-1) register-tie requeues (2026-09-01)

func_841351EC (state-field table-copy, D_84195208/D_84195200 record fields into a 0x10-stride output): hand variants closed most of the gap (raw 0.5000 -> 0.9000) by indexing the two lookup tables with arg1 directly instead of a separate s32 'index' local reused for the pointer-arithmetic multiply -- keep 'index' for the *0x10 offset only, index D_84195208/D_84195200 with arg1. Exact size match (80/80) throughout. A 240s permuter pass on the raw arg1-index-everywhere form only reached best_score 10 (not zero; log shows base_score 60, one output at score 10 rewriting the multiply's index var to arg1, matching what the 0.9 hand candidate already does) -- did not close it further. Runner reports futility register-tie: 10 prior attempts at >=0.99 register_allocation_only, explicit stop; final mismatch is the last field load lw $t4 vs $t3 at instruction ~69/80 bytes (the last of the three field copies, D_84195208[arg1]+0x50). Next action: permuter with a longer budget (300s+) seeded from the raw=0.9000 candidate (state-field:table-copy:permuter-arg1-index in probe stats), or a hand hypothesis that changes which temp register holds the third field's loaded value (e.g. reusing the first record pointer local explicitly for the third access instead of re-indexing D_84195208[arg1]). func_841267B4 (state-field shift-clamp: u16 a=rec[0x28], b=rec[0x26]; result = a>>arg1; if (a < b+result) result = a-b; return u16): fresh owner (prior_attempts=2), 8 variants probed, best sim 0.9500/raw 0.5000, exact size match 80/80, pure register tie at the very first field load (lhu $a2 vs $v1 at rec+0x28). Not yet permuter-tried -- next agent should run tools/permute_candidate.py on the u16-locals candidate before more hand variants.

## 2026-09-02 wave 53 (2026-09-02)

- requeue `func_84126850`: sixteen fresh explicit-width, declaration-order, mask-reuse, and lifetime variants all preserved the exact 80-byte size. Best normalized/raw similarity was 0.9000/0.4500. The first difference is instruction 29: expected `andi a1, a1, 0xffff`, while variants allocate the masked value in `a2` or `a3`. The body shape and size are stable; this is a formal/local register-allocation tie. Next action: seed the permuter from `state-clamp:explicit-s32:old-low-first`, or materially alter the second formal's width/old-value lifetime to make IDO reuse `a1`; do not repeat declaration-order-only variants.

## 2026-09-05

func_84126568: matched (state-field:three-guards:u8-pointer), 3 iterations, agent codex

## 2026-09-05

func_84126064: plateau at 0.9655 (raw 0.5862), mismatch operand_or_scheduling_drift; tried families: state-field; tie-pool no

## 2026-09-05

func_841362E4: time cap at 0.9643 (raw 0.8929) after 2606s, mismatch operand_or_scheduling_drift; tried families: state-field; tie-pool no

## 2026-09-05

func_8412CBE8: time cap at 0.8559 (raw 0.4144) after 2400s, mismatch instruction_drift; tried families: call_sequence; tie-pool no

## 2026-09-05

func_841284A4: matched (call-sequence:guards:combined-assignment), 3 iterations, agent codex

## 2026-09-05

func_84132778: plateau at 0.9292 (raw 0.8142), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-05

func_84128B4C: matched (call-sequence:prologue:status-address-first), 9 iterations, agent codex

## 2026-09-05

TYPE CONFLICT: D_841951BF is extern u8 D_841951BD, D_841951BF, not extern u8 D_841951E6, D_841951BF

## 2026-09-05

TYPE CONFLICT: D_841951BF is extern s32 D_841951BF, not extern u8 D_841951E6, D_841951BF

## 2026-09-05

func_8413B468: time cap at 0.9783 (raw 0.837) after 2631s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## func_84136D84 assembler-artifact plateau (2026-09-05)

func_84136D84: plateau at 0.8571 (raw 0.1429) across iterations 0-5 on array-indexing/struct-field/pointer-cast families, then 0.6667 (raw 0.6667) on the separate-symbol family at iter 6; requeued. Ground truth is a genuine assembler artifact: one lui $at shared across four %lo relocations to distinct symbols (D_84186160/64/68/6C), a shape found in only 2 functions in the whole ROM (here and func_80031564, neither solved) and not reproduced by any C spelling tried under this file's current IDO flags (array indexing, typed struct fields, separate externs, raw pointer casts). Do not retry array-indexing/struct-field spellings first -- despite scoring highest similarity (0.8571) they are the worst raw/structural match (0.1429); the separate-symbol family scores lower similarity but far higher raw match (0.6667) and is the right starting point. Next action: investigate whether $at-sharing across distinct relocations is a build-flag/scheduling issue rather than a pure C-source issue (e.g. per-file IDO flags), or defer as an assembler-limitation skip.
