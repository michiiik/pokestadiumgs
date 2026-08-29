# Region notes -- disasm/src/fragments/79/fragment79_3B7EA0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Fleet box 2026-08-29 (2026-08-29)

Accepted owners: func_8414978C via call-sequence:tie:base-pointer-after-guard; u8 *ptr initialized after the arg0[1] guard, then raw pointer fields and a four-argument func_80063454 test. func_84148AC8 via call-sequence:loop:for; s32 i, direct D_84195208[arg0[0]][i + 5] byte assignment, func_841487A8 call, four iterations. func_84148A4C via call-sequence:loop:do-s32-byte-mask; u8 *value from func_84154B64, s32 i starting at 1, do/while through i != 0xFC, i & 0xFF passed to caller-local s32 func_800643CC declaration, and func_841487A8 on nonzero. All three were probe_match with link_verified:true and then accepted by gate=true, gate_mode=combined, gate_runs=1, install_compiles=1, exit_code=0. No evidence-backed semantic renames applied. Deferred: func_8414A180 (11 variants, best normalized 0.9583/raw 0.4792, saved-arg/base load ordering drift); func_841496C0 (14 variants, best normalized 1.0/raw 0.9804, register_allocation_only with one addu operand-order difference; stop tie-heavy); func_84148C74 (28 variants, local-record/stack-pointer drift, no exact hit); func_841486B0 (31 variants, stack-slot/register drift, no exact hit); func_84149D54 (10 variants in this box, multiply/temporary scheduling drift, no exact hit). Dispatcher/jump-table and larger fresh call-sequence owners were not attempted.

## Attempt-count correction (2026-08-29)

Runner-reported prior_attempts at handoff are: func_8414A180 11, func_841496C0 14, func_84148C74 22, func_841486B0 31, and func_84149D54 10. These counts include the runner's recorded compile/probe submissions; the earlier prose count for 84148C74 was an overcount and should be read as 22 recorded attempts.
