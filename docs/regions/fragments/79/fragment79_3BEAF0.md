# Region notes -- disasm/src/fragments/79/fragment79_3BEAF0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## func_8414F8B4 fleet box 2026-09-02 (2026-09-02)

requeue: fresh owner, 0 prior probe attempts and no prior candidate identity/history entries found across disasm/probe-stats and disasm/build. Best normalized/raw scores: unavailable (no runner invoked by assignment); mismatch/fingerprint: unavailable. Prepared 8 distinct call_sequence candidates in /private/tmp/gs49_func_8414F8B4_batch.json with shared declarations for func_84154B24(void) -> u8 and func_8414F2F4(void *). Assembly model and attempted hypotheses: raw offset addressing, assign-then-return versus guard-return, local pointer/index versus direct arithmetic, shifted entry pointer, explicit field temporaries, branch polarity, hoisted product, and signed division spelling. Next action: run the JSON batch through the authorized probe runner in a later box, read first-diff diagnostics, then change hypothesis family based on mismatch kind and gate any link-verified hit.

## Wave 49 coordinator replay (2026-09-02)

requeue; 8 fresh call-sequence candidates compared with no link verification. Best call-sequence:raw-offset:guard-return-order reached similarity 0.9143 raw 0.5714, exact 136-byte owner size versus candidate 140, with late register allocation drift at instruction 53: expected lhu ,2(), actual lhu ,2(). Tried raw-offset, typed-record, explicit-field, post-call-index, branch-negate, hoisted-amount, and one-based-index forms. Next action: preserve the expected v0 result lifetime through a minimal declaration-order or direct-return repair, then gate a link-verified hit.

## func_8414F8B4 fleet box 2026-09-02 follow-up (2026-09-02)

requeue; prepared 8 novel complete-function candidates in /private/tmp/gs50_func_8414F8B4_batch.json. Best prior: normalized 0.9143, raw 0.5714, exact-size near miss; fingerprint: late lhu expected result in $v0 but actual in $v1 (operand_or_scheduling_drift). Attempted hypotheses: typed State overlay with amount lifetime, field14-before/after amount declaration, guard-early return, product-before-branch, split typed entry overlay, comparison-first branch, shifted-index spelling, and explicit signed-delta division. Next action: run this batch through the authorized probe runner in a later box; use first-diff diagnostics to select the result-lifetime winner, then gate any link-verified candidate. No runner invoked in this box.

## Wave 50 coordinator replay (2026-09-02)

requeue; 8 direct-return candidates compared with no link verification. Best regressed to similarity 0.8824 raw 0.5000, expected 136 bytes versus actual 136, with stack byte/store ordering drift at instruction 24. The prior best remains 0.9143 raw 0.5714 with late lhu v0 versus v1 allocation drift. Next action: preserve the prior raw-offset shape and target only the late result lifetime through a permuter or minimal declaration change.

## 2026-09-02 Wave 51 (2026-09-02)

func_8414F8B4 requeue. Wave 51 tried eight stack/local ordering variants; best current score 0.8571 normalized / 0.4571 raw, while prior history contains 0.9143 / 0.5714. Current variants diverge earlier in the stack/store sequence. Next action: recover the prior 0.9143 body from probe stats and permute that body or test a materially different local-layout family; do not continue the lower-scoring v0-body variants.
