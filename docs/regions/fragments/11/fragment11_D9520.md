# Region notes -- disasm/src/fragments/11/fragment11_D9520.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 8 handoff (2026-08-31)

Wave 8 handoff: func_8160324C remains unresolved after 12 serial CC_CHECK=1 candidates. Best normalized/raw similarity was 0.3971/0.2059 with operand_or_scheduling_drift. The literal 0xFB000000 requires gDPSetPrimColor rather than gDPSetFillColor, and direct macro forms load D_800D0510 too early. Next action is to preserve float conversion first while expressing the display-list pointer/global update in the established same-file ABI shape; investigate the D_800D0510 u32 declaration versus accepted Gfx * macro users.

## func_816098B0 requeue (2026-09-02) (2026-09-02)

Requeue: submitted 8 distinct call-sequence candidates (raw loop forms, formal widths/casts, separated increments, break scheduling, and GBI macro spelling) with host CC checks enabled. Seven compiled; none link_verified or accepted. Compiled candidates all had expected_size=actual_size=304 bytes, expected/actual instruction counts 76, normal_return tails, normalized similarity 1.0000 but raw similarity 0.6184-0.6447; mismatch_kind=immediate_drift and normalized_only_match=true. First-diff fingerprint was instruction 4 / offset 17: expected 0x8e620000 (lw v0,0(s3)), actual 0x8e630000 (lw v1,0(s3)); subsequent diffs included display-list pointer loads/stores and color byte load/order/register allocation. The GBI candidate compile_failed because its loop locals were outside the generated scope (host CC diagnostic: y undefined), not a valid match. Attempted hypothesis families: direct raw command writes, for/while/do-while nesting, u16 versus s32 formal width, pointer casts, explicit increment/casts, break-based scheduling, and GBI macros. Next materially different action: start from a declaration/order permutation that reserves the display-list pointer as a u32 temp named/declared first and separates each command pointer load into explicit temporaries, then permute allocator-sensitive local declaration order and color-byte load order; use a fresh 8+ candidate batch and inspect raw diffs. Do not treat normalized 1.0 as a hit.

## func_81609344 tooling-blocked (2026-09-02) (2026-09-02)

tooling-blocked: Prepared and validated /private/tmp/gs45_func_81609344.json with 8 distinct call-sequence candidates after assembly analysis. The single mandated background launch (PID 24190) produced exact stderr `zsh:1: nice(5) failed: operation not permitted`; /private/tmp/gs45_func_81609344.log exists but is 0 bytes and /private/tmp/gs45_func_81609344.result.json was not created. No probe ran, so there are no scores, mismatch_kind, first-diff fingerprint, size, futility, or link-state results to report. Attempted families: five-s32 ABI/frame correction, explicit bounds temporaries, split guards, ternary dimensions, dimension declaration order, casts, and precomputed sums. Next action: rerun the same fresh 8+ batch in a host session where process launch is permitted; then inspect raw/normalized scores and first-diff diagnostics before changing source hypotheses.

## Coordinator replay after wave 45 (2026-09-02)

Directly replayed /private/tmp/gs45_func_81609344.json without the host nice wrapper. callseq:s32:explicit-bounds was accepted and full-ROM-gated in the same transaction; baseline md5 1561c75d11cedf356a8ddb1a4a5f9d5d. The accepted owner is installed in fragment11_D9520.c. Other candidates were skipped after the acceptance.
