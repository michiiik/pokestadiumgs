# Region notes -- disasm/src/fragments/79/fragment79_3BEAF0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## func_8414F8B4 fleet box 2026-09-02 (2026-09-02)

requeue: fresh owner, 0 prior probe attempts and no prior candidate identity/history entries found across disasm/probe-stats and disasm/build. Best normalized/raw scores: unavailable (no runner invoked by assignment); mismatch/fingerprint: unavailable. Prepared 8 distinct call_sequence candidates in /private/tmp/gs49_func_8414F8B4_batch.json with shared declarations for func_84154B24(void) -> u8 and func_8414F2F4(void *). Assembly model and attempted hypotheses: raw offset addressing, assign-then-return versus guard-return, local pointer/index versus direct arithmetic, shifted entry pointer, explicit field temporaries, branch polarity, hoisted product, and signed division spelling. Next action: run the JSON batch through the authorized probe runner in a later box, read first-diff diagnostics, then change hypothesis family based on mismatch kind and gate any link-verified hit.

## Wave 49 coordinator replay (2026-09-02)

requeue; 8 fresh call-sequence candidates compared with no link verification. Best call-sequence:raw-offset:guard-return-order reached similarity 0.9143 raw 0.5714, exact 136-byte owner size versus candidate 140, with late register allocation drift at instruction 53: expected lhu ,2(), actual lhu ,2(). Tried raw-offset, typed-record, explicit-field, post-call-index, branch-negate, hoisted-amount, and one-based-index forms. Next action: preserve the expected v0 result lifetime through a minimal declaration-order or direct-return repair, then gate a link-verified hit.
