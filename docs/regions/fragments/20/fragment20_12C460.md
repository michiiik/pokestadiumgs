# Region notes -- disasm/src/fragments/20/fragment20_12C460.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 6 handoff (2026-08-31)

Wave 6 handoff: func_82605218 unresolved. Best similarity was 0.7374 normalized and 0.2323 raw with operand_or_scheduling_drift; expected 396 bytes but actual 392, with expected sw $ra, $sp, 36 and actual sw $ra, $sp, 28 at the first mismatch. Add the missing 4-byte stack/local shape before changing hypotheses.

## Wave 15 retry (2026-08-31)

requeue: `func_82610D6C` (50 instructions; first selected at 0 attempts) was rerun after the isolated-worktree venv/oracle bootstrap repair. Both raw-`s16` pointer variants reached real probes but matched only 0.9000 normalized / 0.6200 raw, 196 actual versus 200 expected bytes. The durable first difference is offset 28: expected `or $s3, $a0, $zero`, actual `addiu $s0, $zero, 1`. Do not retry either raw spelling; reconstruct the source temporary/local lifetime that preserves the incoming argument in `$s3` before the loop. No link-verified hit or ROM gate.
