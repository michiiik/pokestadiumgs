# Region notes -- disasm/src/fragments/20/fragment20_12C460.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 6 handoff (2026-08-31)

Wave 6 handoff: func_82605218 unresolved. Best similarity was 0.7374 normalized and 0.2323 raw with operand_or_scheduling_drift; expected 396 bytes but actual 392, with expected sw $ra, $sp, 36 and actual sw $ra, $sp, 28 at the first mismatch. Add the missing 4-byte stack/local shape before changing hypotheses.

## Wave 15 retry (2026-08-31)

requeue: `func_82610D6C` (50 instructions; first selected at 0 attempts) was rerun after the isolated-worktree venv/oracle bootstrap repair. Both raw-`s16` pointer variants reached real probes but matched only 0.9000 normalized / 0.6200 raw, 196 actual versus 200 expected bytes. The durable first difference is offset 28: expected `or $s3, $a0, $zero`, actual `addiu $s0, $zero, 1`. Do not retry either raw spelling; reconstruct the source temporary/local lifetime that preserves the incoming argument in `$s3` before the loop. No link-verified hit or ROM gate.

## Wave 16 handoff (2026-08-31) (2026-08-31)

requeue: func_82610D6C. Count-local reached 0.8800/0.5200 at 188 bytes; count-direct-late 0.9000/0.5400 at 196 bytes; base aliases were best at 0.9000/0.6200 at 196 bytes; base-local was 180/204 bytes. First diff offset 28: expected or s3,a0,zero, actual addiu s0,zero,1. Exhausted raw-s16 pointers, count-local, base-alias, and nested-n families. Next emit lh t6,18(a0), move s3,a0, li s0,1 with the 40-byte frame.

## Wave 17 successor handoff (2026-08-31) (2026-08-31)

register-tie: `func_82610D6C`. Correcting the predecessor exit polarity (`result == 0` exits) and preserving multiline source formatting produced an exact-size 200-byte body at 1.0000 normalized / 0.9200 raw similarity. The first true difference is offset 0x50 (runner display 81): expected `addiu $a3, $v0, 48`, actual `addiu $a2, $v0, 48`; the remaining graph is expected `lh $a2, 6($a3)` / `move $a0, $a3` / `sll $a1, $a2, 1` versus actual `$a1/$a2` allocation. The runner terminally reports `register-tie: 13 prior attempts at >=0.99 register_allocation_only`. The durable best spelling is a normally formatted multiline m2c body with `base = arg0; var_s0 = 1; var_s1 = 0;`, then `arg0 += 0x114` inside the positive-count guard; preserve `temp_a3 = temp_v0 + 0x30`, the inner do-loop's index increment before its flag test, and `if (var_s0 != 0) goto block_9` with `block_9` in the null-result `else`. Exhausted raw/count/base aliases, corrected indexed/pointer loops, m2c labels, register qualifiers, declaration and same-line variants, formal pointer mutation, typed overlay/pointer widths, count-limit/volatile/alias families, and two 300-second two-thread permuter runs (best formal-mutation base score 25, no output). Next action: route that spelling to a longer register-tie permuter box; do not resume hand source-shape variants. All probes completed without EMFILE or descriptor/process failures.

## func_82610E34 fresh-box handoff (2026-09-01)

requeue: Fresh owner (prior_attempts=2 at assignment; 18 attempts after two 8-candidate batches) remained unresolved. Batch 1 best call_sequence:guard-loop:typed-base normalized=0.8000 raw=0.5778, mismatch=instruction_drift, fingerprint=diff@20 expected sw $ra, $sp, 36 actual addiu $s0, $zero, 1, expected_size=180 actual_size=176. Attempted families: typed guard/while loop, raw-offset loop, do-while, for-loop/explicit temp, s16 count, pointer-carried loop, early return, s32/raw argument; batch 2 attempted explicit pad/saved-layout declaration ordering (ascending/reverse), break-result, pointer loop, condition-first, two-s16, entry-offset, and s32 pointer ABI. Best stayed 0.8000/0.5778 with same fingerprint; one s32* ABI candidate compile_failed. No link_verified hit, no acceptance, and no runner futility/register-tie verdict. Next action: use permuter or an accepted neighboring 0x28-frame call-sequence spelling to reconstruct the exact saved-register/local declaration order, then send a new 8+ candidate batch; do not retry these bodies/declarations.

## Wave 31 follow-up (2026-09-01) (2026-09-01)

requeue/tooling-blocked: func_82610E34 received two fresh 8-candidate auto-gating-enabled batches (16 candidates total) after the prior 26 recorded attempts. The permuter was attempted first but failed before execution with ModuleNotFoundError: No module named toml in disasm/tools/decomp-permuter. New saved-register declaration/lifetime variants all compiled and probed, but no link_verified hit or acceptance; best normalized/raw 0.8667/0.6444, expected 180 bytes versus actual 172 (43 instructions), mismatch operand_or_scheduling_drift. Stable first fingerprint is offset 33/instruction 8: expected addiu s2,zero,2 then addiu s3,a0,276, actual addiu s2,a0,276 then addiu s3,zero,2; subsequent drift includes missing call setup/temporary scheduling and inner-loop register allocation. Attempted saved-order typed/raw pointer, base/count/entry permutations, result-last, entry lifetime, condition-first, s32 count, bound local, formal pointer, and limit-first declaration orders. No source edit, link verification, auto-gate, or full-ROM gate. Next action: repair/install toml in the isolated permuter environment and run a bounded permuter search on a compiling saved-register candidate; do not repeat these declaration-order batches or touch fragment61.

## Wave 31 continued hand-model (2026-09-01) (2026-09-01)

requeue: Continued func_82610E34 only with a genuinely new control/lifetime model based on initialized result/index/limit locals, inline base expression, and structured while/do/for/break/retry forms; 8 distinct candidates, auto-gating enabled. No link_verified hit or acceptance. Best new-model:control-lifetime:0 reached 0.8889 normalized / 0.7111 raw, 40/45 instructions and 172/180 bytes, mismatch instruction_drift at offset 52/instruction 13: expected li a3,20, actual jal; later differences include call-result/temporary scheduling and inner-loop registers. Runner futility warning now reports repeated-drift after 17 prior rejections of the older offset-33 fingerprint; this is advisory only. Permuter remains tooling-blocked before execution by missing Python toml dependency. Next action: repair the isolated permuter dependency, or derive a fresh call-site argument staging model that preserves the oracle order jal delay-slot zeroing, then submit another 8+ batch; do not replay prior declaration-order or control-lifetime bodies.

## Wave 31 call-argument staging retry (2026-09-01) (2026-09-01)

requeue: func_82610E34 received another fresh 8-candidate batch targeting the latest offset-52 diagnostic with explicit fourth-argument staging and alternate inline base expressions. No candidate link-verified or accepted; auto-gating found no hit. Most variants regressed to the stable older fingerprint at offset 33/instruction 8 (expected li s2,2 then addiu s3,a0,276; actual reversed), normalized/raw 0.8667/0.6444 and 43/45 instructions. One staged-local form compile-failed because IDO rejects declarations after the loop label. No full-ROM gate. Permuter remains blocked only by missing toml. Next action: install/repair toml in the isolated permuter environment, then search a compiling 0x28-frame candidate; hand retries need a genuinely different ABI/lifetime model rather than more literal spellings or control/declaration permutations.

## Wave 31 role-model retry (2026-09-01) (2026-09-01)

requeue: func_82610E34 received 8 fresh legal function-scope candidates using neighbor-style outer do/guard/inner-scan structures and explicit base/result/index/bound roles. No link_verified hit, auto-gate, or full-ROM gate. Best remained 0.8667/0.6444 with 43/45 instructions and the offset-33 register reversal (expected s2=2,s3=arg0+276; actual s2=arg0+276,s3=2). The additional role model did not preserve the requested s3 base mapping; one variant widened the frame. No prior declaration block was replayed. Permuter remains blocked only by missing toml. Next action: use the assembly exact prologue/save order to construct a compiler-specific temporary/aggregate lifetime model, or repair toml and permute a compiling near-match; do not repeat outer-do or literal staging variants.

## Persistent retry with explicit venv (2026-09-01) (2026-09-01)

requeue: Continued func_82610E34 only. Explicit permuter invocation through disasm/tools/decomp-venv/bin/python still failed before execution with ModuleNotFoundError: toml, so no permutation ran. Submitted 8 fresh aggregate-state lifetime candidates with auto-gating enabled, using function-scope state aggregate for base/result/index/bound and neighbor-style outer loop. No link_verified hit, auto-gate, or full-ROM gate. Best normalized/raw remained 0.8667/0.6444, 43/45 instructions, offset 33 reversal expected s2=2 and s3=arg0+276 versus actual s2=arg0+276 and s3=2. Most variants also retain offset 52 call staging drift. No tracked source/tooling edits; temporary candidate removed. Next action: repair the venv toml visibility or derive a genuinely new ABI model with exact prologue register pressure; do not replay aggregate-state or literal-staging forms.

## Persistent formal-base retry (2026-09-01) (2026-09-01)

requeue: func_82610E34 received 8 fresh formal-base/call-argument/lifetime candidates, all legal and auto-gating enabled. No link_verified hit or acceptance. Best normalized similarity 0.9556 but raw 0.2444 due a widened 0x30 frame from extra argument temporaries; the best 0x28-frame forms reached 0.8889/0.6444. Expected register roles remain s0 result, s1 index, s2 bound, s3 base; direct formal-base variants swapped s2/s3 or introduced extra saved state. No full-ROM gate. Explicit venv permuter still unavailable due missing toml. Next action: repair toml visibility or construct a minimal 0x28-frame model with no extra call temporaries while preserving formal pointer lifetime; avoid replaying these formal-base variants.

## Persistent scalar 0x28 retry (2026-09-01) (2026-09-01)

requeue: func_82610E34 received 8 fresh scalar 0x28-frame candidates with arg0 scalar, call-site-derived base, and new function-scope lifetime order; no formal-base or aggregate replay. Auto-gating enabled; no link_verified hit, acceptance, or full-ROM gate. Best 0x28 candidate reached 0.8889 normalized / 0.7111 raw, 40/45 instructions, with instruction drift at offset 52: expected li a3,20 but actual jal. Other candidates retained offset-33 saved-register reversal. One extra-temporary form was excluded from the best due frame widening. Next action: repair toml or derive a new ABI-preserving call wrapper/temporary model; do not repeat this scalar 0x28 family.

## Persistent call-expression retry (2026-09-01) (2026-09-01)

requeue: func_82610E34 received 8 fresh legal call-expression/source-order candidates preserving the 0x28-frame scalar model. Constant-expression variants did not change code generation: best normalized/raw 0.8889/0.7111, 40/45 instructions, with first drift offset 52 where expected li a3,20 is absent before jal; offset-33 register reversal persists in equivalent forms. No link_verified hit, auto-gate, or full-ROM gate. No prior body/declaration replay. Next action: repair toml and permute a compiling near-match, or use a truly different helper ABI/prototype model; further constant-expression spellings are exhausted.

## Persistent ABI-model retry (2026-09-01) (2026-09-01)

requeue: func_82610E34 received 8 fresh typed-record ABI candidates with local record overlays and changed pointer/field interpretation; no prior body replay. Auto-gating enabled, no link_verified hit, acceptance, or full-ROM gate. Best normalized/raw 0.9111/0.7333, 41/45 instructions, with offset-52 instruction drift (expected li a3,20 before jal; actual jal) and later inner scan scheduling differences. Some variants retained 0x28 frame; others widened due typed pressure. Offset-33 register reversal was improved in the best typed forms but not eliminated across the batch. Next action: repair toml and run permuter on a compiling 0x28 typed-record candidate, or derive a callee prototype/return ABI variant without adding saved locals.

## func_82610E34 ABI wrapper retry (2026-09-01)

requeue
Persistent ABI-model retry (2026-09-01): submitted 8 fresh callee-wrapper:typed-fnptr candidates with auto-gating enabled. The candidates used direct typed function-pointer calls to vary prototype/call lowering and local lifetimes; none replayed prior typed-record bodies. No link_verified result, no auto-gated acceptance, and no full-ROM gate evidence. Best result was normalized 0.8511 / raw 0.4043, with actual size 0x30 (47 instructions) instead of the required 0x28 frame (45 instructions); first mismatch was offset 3, expected addiu sp,sp,-40 but actual addiu sp,sp,-48, and the call lowered to jalr s4 rather than the required direct jal with li a3,20. The function-pointer ABI introduced a saved s4, so this family is rejected as frame-incompatible. The explicit venv permuter invocation remains tooling-blocked by ModuleNotFoundError: toml. Next action: repair/use the available decomp environment without changing tracked tooling, then permute an exact 0x28-frame candidate or try a new direct-callee prototype/lifetime spelling that retains only s0-s3 and emits a3=20 before jal.

## func_82610E34 bounded permuter retry (2026-09-01)

requeue
Bounded permuter and fresh hand batch (2026-09-01): explicit PERMUTER_PYTHON/PYTHONPATH setup ran for 10 seconds and timed out normally; best permuter score 1185/1420, no zero. Submitted 8 new permute-guided:abi-lifetime-short candidates with auto-gating enabled; no link_verified hit, no acceptance, no full-ROM gate. Best hand candidates preserved 45-instruction comparison span but still began with result initialization at offset 20 instead of the expected saved ra store; offset 52 remained expected li a3,20 versus actual jal, and offset-33 s2/s3 reversal persisted. Other variants widened to 0x30 or used unsupported one-line declarations and compile-failed. Next action: a new direct-call ABI model that forces all four arguments into temporaries only after the exact s0-s3/ra save sequence, or run a longer permuter budget later; do not replay these bodies.

## Wave 32 handoff (2026-09-01) (2026-09-01)

Accepted func_8260E1B4 (call_sequence, digit-print helper): the fix was two independent, compounding hypotheses. (1) the leading pair-sums `sp24=arg0[0x10]+arg0[0x14]` / `sp26=arg0[0x12]+arg0[0x16]` must be written with operands SWAPPED (later offset first, e.g. `arg0[0x14]+arg0[0x10]`) to match IDO's load-second-operand-first scheduling. (2) the two s16 locals must be DECLARED in reverse order versus their store order (declare the variable used in the SECOND store first, the one used in the FIRST store second) -- i.e. `s16 sp26; s16 sp24;` even though sp24 is assigned first in the body -- to land in the correct stack slots. Winning spelling used the D_ tables as `extern u8 D_XXXX[]` with `idx = *(s16*)(arg0+2) * 2; *(s16 *)(D_TABLE + idx)` (raw byte-address doubling), not a typed s16[] array subscript (both compiled, u8-byte scored slightly higher raw and was the one that gated). Add "declare-swap + sum-operand-swap" as a new §4 candidate row: any owner in this file with two adjacent sh-stores of a two-field sum should try this combination before other hypotheses.

## Wave 32 handoff (2026-09-01) continued (2026-09-01)

requeue: func_82614BD0 (call_sequence, master-dispatch wrapper calling func_82613A4C..func_826144EC(s0) plus a conditional func_82614630(&D_8261DA4C) and tail func_8261479C/func_826148D4). Correct structure recovered and reaches 272/272 bytes (exact size) at 0.9706 normalized / 0.9559 raw with the flag test written via pointer math off the already-loaded base (`*(u16 *)((u8 *)s0 + 4) & 1`, NOT the direct `D_8261A494` global -- that regresses hard to 0.85/0.79). Stuck at a single repeated first-diff fingerprint (offset 197, instr ~49: expected `lui $t8` for the D_8261DA4C value-read, actual `lui $a0` -- the compiler CSEs the value-read lui with the later &D_8261DA4C address-of lui into one, while the real object keeps two separate lui computations). Tried: value into an explicit temp before the check, address-of into a temp before the check, both together, `if(x)` vs `if(x!=0)`, `*(s16*)&D_8261DA4C` dereference, u8*/void* base pointer for s0, s16*/void* param type for func_82614630 -- 12 attempts share this exact fingerprint (repeated-drift). Next action: this needs either the permuter (blocked elsewhere in this file by missing toml in disasm/tools/decomp-venv) or a genuinely different accessor for the value-read side (e.g. the real source may reference a DIFFERENT symbol that happens to alias D_8261DA4C's address, the same trick that fixed func_8260E1B4's D_8261A494 case) -- do not repeat value-before/after-address orderings on the same D_8261DA4C symbol name.

## Wave 32 handoff (2026-09-01) func_826131A4 (2026-09-01)

requeue: func_826131A4 (call_sequence, 77 instr, 'reset scan' function: increments arg0[6], scans children at arg0[0x34F4 + i*4] for one with a positive s16 at child+0xC (sets found=0 and breaks early if so, otherwise arg0+=4 each non-matching iteration); if arg0[6] >= D_826157B0 (a global s16 threshold) AND no qualifying child was found, reads pool=arg0[0x110], and if pool[0x9C]==7 calls func_80054E10(pool+0x900) (a bool-ish return); sets arg0[2]=0x10 on success else 0x13, resets arg0[6]=0, then unconditionally loops func_826078B4(arg0[0x34F4+i*4]) for i in 0..arg0[0x18) with the count RELOADED FROM MEMORY every iteration (not cached, unlike the first loop's cached v1), and finally calls func_800226C0(0x69)). Logic fully reconstructed and compiles, but best probe result is only 0.8182 normalized / 0.5195 raw, actual size 292 bytes vs expected 308 (4 instructions short). First diff at instr ~7: expected `or $s2,$a0,$zero` (arg0 saved to callee-saved s2 very early, before the count/blez check) but actual puts it in $a1. 8 attempts covering nested-if vs &&-combined breaks, result-polarity swap, s32*/void* pool type, cached vs reloaded second-loop count, while(1) vs do-while first loop, u8/s32 found type, and a single combined early-return condition all land at the same or a worse fingerprint. Next action: reorder the two leading field loads (arg0[6], arg0[0x18]) to happen BEFORE the pointer-to-s2 assignment in source (matches real instruction order lh/lh/or-s2, not or-s2 first), and/or try declaring found as the very first local (register-pressure ordering) before retrying; do not repeat the 8 combinations above.

## Wave 32 func_826131A4 follow-up (2026-09-01) (2026-09-01)

requeue: func_826131A4 received 8 more source-reordering variants (field-loads-before-s2-assign, found-declared-first, count-loaded-late, ++ increment-expression form, block-scoped s0 locals) targeting the arg0->s2 register choice. All still land at the same or a slightly worse fingerprint: best stayed 0.8182/0.3636-0.5065, actual 292 vs expected 308 bytes, s2/a1 register choice unaffected by source order -- this looks like a genuine IDO allocator tie, not a source-shape problem. 17 total attempts now on this owner. Do not retry further source reorderings; next agent should try the permuter (after the toml dependency is fixed elsewhere in this file) or accept this owner needs a fundamentally different control-flow decomposition (e.g. splitting the scan loop into its own static helper) before it will match.

## Wave 32 permuter results (2026-09-01) (2026-09-01)

accepted: func_82614BD0 (call_sequence, master-dispatch wrapper). The permuter (now working repo-wide as of commit 9e9a92b0 -- readonly_tool_path was symlink-resolving decomp-venv's Python to the system interpreter, hiding the venv's toml install) found a score-0 candidate in 44.2s from base score 275: insert a dead `if (D_8261DA4C) {}` (no else, empty body, condition without != 0) immediately after the `func_8261479C(s0);` call and before `func_826148D4(s0);`. This forces IDO to keep the value-read lui for D_8261DA4C separate from the later &D_8261DA4C address-of lui instead of CSE-ing them, resolving the offset-197 fingerprint that 12 prior hand attempts shared. Sent as an 8-candidate batch (the exact permuter body plus 7 close variants: !=0 form, before-call placement, braceless if, u8* base form, double-after ordering, score-10 new_var-pointer form, if/else-empty form); the exact permuter spelling (label permute:dead-check:D_8261DA4C-after-call-noeq) link-verified and auto-gated (make -C disasm COMPARE=1 OK). Committed ace7e1ac.

## Wave 32 permuter results (2026-09-01) func_826131A4 (2026-09-01)

requeue: func_826131A4 (call_sequence, 'reset scan', 77 instr, 308 expected bytes) sent through the permuter for 300s (4 threads, stop-on-zero) on the best recorded hand candidate (callseq:reset-scan:v1:break-nested, 0.8182/0.5195, 292 actual bytes). Base permuter score 2200; best found was 1285 after the full 300s budget -- timed_out:true, never reached zero. The permuter's own mutations at that score (unrelated unsigned int new_var wrapping the count>0 test as an assignment-expression, arg0-vs-s2 base-pointer swaps on the tail loop bound/reset store, a dummy label) do not resemble a clean source hypothesis and were NOT sent to try_pragma_candidates (no zero score = no probe per the standing rule). This is stronger evidence that the offset-7 arg0->s2/a1 register choice (17 prior hand attempts, all landing on the same tie) is a genuine hard allocator tie the permuter itself struggles to close in a 300s/4-thread budget, not a shape the permuter will trivially solve like func_82614BD0's CSE tie was. Next action: rerun the permuter with a longer budget (900s+) and/or more threads on this same candidate before trying further hand source-shape variants; do not repeat the 17 previously-exhausted hand hypotheses.

## func_82610E34: its permuter records are void (2026-09-01) (2026-09-01)

The 16 permuter attempts recorded for func_82610E34 on 2026-08-31 all fell inside the window where the permuter was dead: readonly_tool_path symlink-resolved decomp-venv's interpreter to the system Python, so every run died on ModuleNotFoundError before doing any work (3f654bb8 introduced it, 9e9a92b0 fixed it). Those attempts carry no information and must not be read as 'the permuter already failed here'. This is one of only two owners repo-wide affected.

Re-run it. The permuter now converts: it closed func_82614BD0 in this same file from base score 275 to zero in 44 seconds, and that body gated and landed.

## Wave 46 func_82610FF8 fresh batch (2026-09-02)

requeue: fresh owner (prior_attempts=0), no probe run in this worker. Assembly is a 99-instruction call_sequence with frame 0x28: increment s16 field +6 and guard against D_82615768; choose state 3 when s16 +0x12 > 0 else 5; clear +6/+8/+0x18; scan records at arg0+0x114 via func_82604C40(1,i,records,0x14), accept entries whose s16 +0x32 != -1 into pointer table +0x34F4 with s16 count at +0x18; call kinds 2 and 3, then func_826078B4 over pointer table and func_800226C0(0x69). Batch hypotheses cover raw offsets, explicit limit/count temporaries, declaration/lifetime order, loop forms, shift-vs-multiply indexing, and call-order scheduling. Scores/fingerprint: none yet; next action replay OUT with runner, then classify first-diff (expected likely operand_or_scheduling_drift or register_allocation_only) and retain accepted candidate only after link/full-ROM gate. tooling-blocked: no evidence. register-tie: not reported. layout-prerequisite: none.

## Coordinator replay after wave 46 (2026-09-02)

Direct replay of the worker batch scored two candidates and compile-failed the rest. Best normalized/raw similarity 0.8182/0.2828; expected 396 versus actual 364 and a stable -40 expected versus -48 actual frame drift. No link verification or gate. Requeue with a new frame/lifetime model and corrected declarations.

## 2026-09-03

func_82607AA0: time cap at 0.0 (raw None) after 2408s, mismatch unknown; tried families: state_field_access; tie-pool no

## 2026-09-03

func_8260BD50: time cap at 0.0 (raw None) after 2409s, mismatch unknown; tried families: call_sequence; tie-pool no

## 2026-09-03

func_8260E2C4: matched (call_sequence:record-overlay:typed-base), 1 iterations, agent codex

## 2026-09-03

func_8260E140: matched (init_sequence:abi:byte-pointer-s32-home), 1 iterations, agent codex

## 2026-09-03

func_82610C84: matched (call_sequence:stack-home:cast-bzero), 1 iterations, agent codex

## 2026-09-03

func_82604720: matched (call_sequence:arguments:halfword-casts), 1 iterations, agent codex

## 2026-09-03

func_82604628: matched (constant-map:switch:inline-mask-temp), 3 iterations, agent codex

## 2026-09-03

func_82610E34: time cap at 0.9556 (raw 0.8444) after 2412s, mismatch instruction_drift; tried families: call-sequence, permuter; tie-pool no

## 2026-09-04

func_82604C08: time cap at 0.9286 (raw 0.6429) after 1214s, mismatch operand_or_scheduling_drift; tried families: constant-map; tie-pool no

## 2026-09-04

func_82606E90: time cap at 0.9286 (raw 0.5714) after 1214s, mismatch operand_or_scheduling_drift; tried families: constant-map; tie-pool no

## 2026-09-04

func_826119A4: time cap at 0.875 (raw 0.5625) after 1213s, mismatch instruction_drift; tried families: constant-map; tie-pool no

## 2026-09-04

func_8260F49C: matched (call_sequence:record-offset:three-arg-stepcast), 1 iterations, agent codex

## 2026-09-04

func_82608270: time cap at 0.95 (raw 0.15) after 1212s, mismatch operand_or_scheduling_drift; tried families: state_field_access; tie-pool no

## 2026-09-04

func_826049A0: time cap at 1.0 (raw 1.0) after 1210s, mismatch section_layout_drift; tried families: dispatcher_switch; tie-pool no

## 2026-09-04

func_82605E04: time cap at 0.95 (raw 0.1833) after 1215s, mismatch operand_or_scheduling_drift; tried families: state-field; tie-pool no

## 2026-09-04

func_82605EF4: time cap at 0.7167 (raw 0.1167) after 1209s, mismatch operand_or_scheduling_drift; tried families: bounded_lookup; tie-pool no

## 2026-09-04

func_82613C64: matched (call_sequence:switch-dispatch:temp-a2-before-clear), 1 iterations, agent codex

## 2026-09-04

func_8260E03C: time cap at 0.0 (raw None) after 1200s, mismatch unknown; tried families: dispatcher_switch; tie-pool no

## 2026-09-04

func_82605110: time cap at 0.9545 (raw 0.8788) after 1215s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no
