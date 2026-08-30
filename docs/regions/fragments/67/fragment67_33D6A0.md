# Region notes -- disasm/src/fragments/67/fragment67_33D6A0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-30 Math_StepToF sibling lane (2026-08-30)

accepted func_82901DD4: label permute:noop:case1-and-case4-reorder; exact spelling uses reusable f32 target then step temporaries before each Math_StepToF call, case 1 loads/stores the float before writing state 2, case 4 writes both floats before state 5, and a zero-code do { } while (0) after writing state 3 fixes block scheduling. Probe hit was link_verified=true; full combined ROM gate accepted. accepted func_82902024: transfer the same spelling and semantic targets/steps, but use separate step_first for the first call in cases 2 and 5 and step for the second call; label transfer:math-step:separate-first-step; link_verified=true and full combined ROM gate accepted.

## Requeue func_829012E4 (2026-08-30)

requeue: 11 fresh variants attempted. Best call-sequence:camera-step:s16-x-float-first scored normalized 0.8261, raw 0.5362, operand_or_scheduling_drift; first diff offset 9/instruction 2, expected lh $t6, 2($v0), actual lh $t7, 2($v0), fingerprint [operand_or_scheduling_drift,9,2,0x844e0002,0x844f0002]. Hypotheses tried: direct m2c expression and stack-local declaration orders; four ordered s16 preloads; s16 x/y result locals with float-order swaps; s32 width-preserving result locals. The s16-result shape improves load order but inflates the expected 0x30 frame to 0x40. Next action: preserve direct expressions and force the four initial halfword loads in 2,4,6,8 order without named narrow locals, then separately reproduce sp+0x24/sp+0x28 float spill order; consider a two-field local overlay or comma/assignment sequencing rather than more width variants.
