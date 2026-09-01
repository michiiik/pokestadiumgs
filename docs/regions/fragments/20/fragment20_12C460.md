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
