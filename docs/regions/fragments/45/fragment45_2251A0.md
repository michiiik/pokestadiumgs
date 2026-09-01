# Region notes -- disasm/src/fragments/45/fragment45_2251A0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-31 fleet box requeue (2026-08-31)

requeue func_8AB02240: eight candidates across macro, loop, frame, and ABI hypotheses; no link_verified hit or ROM gate. Best normalized/raw similarity was 0.8676/0.7353 with operand_or_scheduling_drift: expected 268 bytes/67 instructions versus actual 272/68, first diff expected sw $a3,68(sp) versus actual sw $a0,56(sp); expected sll/sra $a3 before gDPSetEnvColor while actual used andi directly. Next action is to resolve the caller/helper ABI and formal-width ordering, especially arg3 and func_8AB01FC8.

## 2026-08-31 successor box requeue (2026-08-31)

requeue func_8AB02240: eight materially different ABI/local candidates; no link_verified candidate or ROM gate. Best was normalized/raw 0.8696/0.7101, 268 expected versus 276 actual bytes, first diff expected sw $s3,40(sp) versus actual sw $t6,0($s5). The helper is strongly indicated as six s16 parameters; next action is to model the pre-macro $s3 sign-extension/local lifetime and exact declaration order.

## 2026-08-31 third successor box requeue (2026-08-31)

requeue func_8AB02240: three exact-six-s16 ABI/local variants; no link_verified candidate or ROM gate. Best remains normalized/raw 0.8696/0.7101; runner reports stuck at 16 attempts, expected 268 bytes versus actual 324, first diff expected sw $a3,68(sp) versus actual sw $a0,56(sp). Next action is to revisit caller formal typing/order and force the pre-macro $s3 sign-extension/local lifetime.

## Wave 8 handoff (2026-08-31)

Wave 8 handoff: func_8AB0234C remains unresolved after 3 serial CC_CHECK=1 probes. Best normalized/raw similarity was 1.0000/0.8500 and was rejected as register_allocation_only with the expected $a1 versus actual $v1; another candidate reached 0.9500/0.7500 with operand scheduling drift. Next action is declaration/local ordering that forces expected $a0/$a1 constant staging before retrying successor owners. No link_verified candidate or ROM gate.

## Fleet requeue: func_8AB00FF8 (2026-08-31)

Requeue after 20 CC_CHECK probes. Best normalized/raw similarity was 0.8537/0.4268 with 328 expected versus 304 actual bytes; the key mismatch is scheduling around lui t3, 0xFB00 and coordinate-load ordering. No link-verified hit, install, or full-ROM gate. Resume this same owner only with a materially different scheduling/register model.

## Wave 26 requeue (2026-09-01) (2026-09-01)

requeue func_8AB01140: 60 probe-only candidates across fill-vs-env opcode correction, raw byte packing, struct/array/union locals, named/volatile fields, packed expression groupings, helper cast/prototype forms, and corrected gSPTextureRectangle coordinates. Best labels gbi:envcolor:struct-color-pad:correct-rect and gbi:envcolor:array2:multiline are exact 328-byte/82-instruction size (expected=actual) with normalized similarity 0.9878, raw similarity 0.5488, mismatch_kind operand_or_scheduling_drift. First mismatch at offset 93: expected lbu $t8,1($t0), actual lbu $t7,0($t0); remaining eight color-pack operand/scheduling differences. No link_verified hit, no gate, no source edit or commit. Next action: model the color as a typed named 4-byte overlay/cast backed by the existing 8-byte stack local, preserving the target local offset and normal gDPSetEnvColor field-access scheduler; investigate declaration order/ABI rather than repeating raw pointer indexing.

## 2026-09-02 worker requeue: func_8AB0234C (2026-09-02)

register-tie requeue: submitted 8 distinct compiling call_sequence candidates varying declaration order, formal/local widths, branch order, explicit temporaries, and constant staging. All had expected=actual 160 bytes, 40 instructions, normal_return, and no link_verified candidate or ROM gate. Best normalized/raw similarity was 1.0000/0.8500 (variant 1), mismatch_kind register_allocation_only, first-diff fingerprint [register_allocation_only,25,6,0x24050002,0x24030002]: expected instruction 6 addiu $a1,$zero,2 but actual addiu $v1,$zero,2; subsequent differences kept $v1 where target uses $a1, plus expected beq $v0,$a1 versus actual $v1,$v0. Other variants reached at most 0.75 normalized/0.625 raw and introduced operand_or_scheduling_drift from reordered control flow or earlier register choices. Repaired permuter ran 45 seconds on the strongest compiling body, timed out at score 40 with no improvement. Next action: materially different permuter/ABI model that preserves the original nested control-flow shape while forcing the compiler to allocate the second discriminator in $a1 (possibly exact callee declaration/call-site staging or a verified permuter rewrite); then resubmit any score-0 body through the runner for automatic full-ROM gating.
