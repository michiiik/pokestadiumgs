# Region notes -- disasm/src/fragments/34/fragment34_1C5AA0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-30 fleet box (2026-08-30)

Accepted: func_88509870 with label call-sequence:state-wrapper:final-load-order:reversed-operands. Probe matched with link_verified=true; full gate accepted with combined gate mode and one full ROM COMPARE=1 run. The matching spelling uses nested timer guards and reverses the final field+0xC plus field+4 addition operands.

Requeue: func_885095EC. Best probe similarity 0.9683 normalized / 0.6508 raw; frame mismatch remained expected -0x28 versus actual -0x30, with expected stack spill at sp+0x1C versus actual sp+0x18. Next action: reduce compiler spills while preserving the m2c float branch and single index spill; do not gate the near-match.

Requeue: func_88508CAC. Best probe similarity 1.0 normalized / 0.8529 raw; register-allocation-only residual at the angle update and final float-to-int temporaries. Next action: recover the exact typed/raw overlay or scratch live ranges; prior overlay and permutation variants did not close it.

Requeue: func_8850974C. Best probe similarity about 0.4096 normalized / 0.2048 raw; the unrolled loop draft lost the expected base-pointer setup. Next action: preserve the incrementing record pointer and re-derive the source shape from the complete assembly before probing again.

Requeue: func_88509418. Best probe similarity 0.9583 normalized / 0.375 raw; target retains an entry sw a0,0(sp) and the raw switch/stride draft does not. Next action: determine the ABI spill-producing formal/source shape before retrying.

Requeue: func_8850ABCC. Best probe similarity 0.8507 normalized / 0.3582 raw; global-state float sequence remains register/constant scheduling drift. Next action: recover the global overlay/source declaration shape that keeps the address in v1 and preserves the target constant order.

Requeue: func_8850A2F4. Best probe similarity 0.9118 normalized / 0.5294 raw; float countdown source remains operand/scheduling drift. Next action: derive the target integer temporary order around the two axis calculations.

Requeue: func_8850AAA8 and func_8850A988. Both clamped-float variants retain constant-load scheduling drift around the divisor and threshold constants. Next action: use a materially different source evaluation/lifetime hypothesis.

Register-tie skip list for this box: func_88508B98, func_88508490, func_88508B10, func_88509538, func_8850A614, func_885087D4, func_88508D34. Layout-prerequisite deferred list: func_8850AEA8, func_88508E34, func_8850CED8, func_8850A0EC, func_885084EC.
