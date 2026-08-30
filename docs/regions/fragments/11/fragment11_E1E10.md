# Region notes -- disasm/src/fragments/11/fragment11_E1E10.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Fragment 11 E1E10 fleet handoff (2026-08-30)

## 2026-08-30 bounded fleet slot

Accepted owners and gate evidence:

- func_8160B9A0: winning spelling label call-sequence:record-clear:u8ptr:gate. The installed body uses a u8 pointer to arg0 + arg1 * 0xCE8, clears entry[0x20] and the s32 field at entry + 0x78, sets arg0[arg1 + 0xB], and conditionally calls func_800226C0(0x98). Gate result was status 0, accepted [func_8160B9A0], probe_status probe_match, link_verified true, exit_code 0, prior_attempts 8, combined gate_runs 1, gate_seconds 1.432.
- func_8160B8E0: winning spelling label call-sequence:record-copy:struct-final-equality-else:gate. The transfer is a local struct with u32 words[826] assigned from arg1 to entry + 0x20. The copy branch is written as link == 0 || source-link mismatch || source-byte mismatch, with the equal case returning 0. Gate result was status 0, accepted [func_8160B8E0], probe_status probe_match, link_verified true, exit_code 0, prior_attempts 25, combined gate_runs 1, gate_seconds 1.287.
- func_8160A844: winning spelling label call-chain:scratch-loop:formal-end-byte-buffer-plus-pad:gate. A leading u8 pad[4] places the 0x180-byte scratch at the target stack offset; the formal pointer is reused as the end pointer, with source and zeroing aliases advanced by 0x60 and scratch output by 0x3C. Gate result was status 0, accepted [func_8160A844], probe_status probe_match, link_verified true, exit_code 0, prior_attempts 48, combined gate_runs 1, gate_seconds 1.396.
- func_8160A384: winning spelling label call-chain:scratch-copy:record-pointer-loop-leading-pad:gate. A leading u8 pad[4] places the scratch buffer at sp + 0x3C; the loop advances source records by 0xCE8 and scratch records by 0x3C before the B14, 535D4, and 51D64 calls. Gate result was status 0, accepted [func_8160A384], probe_status probe_match, link_verified true, exit_code 0, prior_attempts 8, combined gate_runs 1, gate_seconds 1.386.

Durable requeues:

- requeue func_8160A270. Assembly fact: v0 starts at 2 and the repeated shift/subtract/add sequence computes 0x19D0; bit 0x2 is cleared with mask 0xFFFD at arg0 offsets 0x3E and 0xD26 and at record +0x19D0 offsets 0xD26, 0x1A0E, 0x26F6, and 0x3E. This box reached 42 attempts, best normalized similarity 0.7647 and raw similarity 0.1176, with operand_or_scheduling_drift/stuck diagnostics. Direct constant-address, typed-record, explicit-arithmetic, and register-index spellings were exhausted; next action should preserve the compiler-visible non-folded index arithmetic or use a materially different permuter hypothesis.
- requeue func_8160A780. The corrected loop starts at arg1 after func_80055A74(arg0) and matches normalized instructions at 1.0, but the best raw score was 0.6327. The target keeps the bound in s1, scratch in s2, and result at sp + 0x1AC; tried bodies keep selecting s2/s1 and sp + 0x1B4. Next action needs a materially different variable-lifetime/register-allocation construction; do not repeat current/array declaration permutations.
- requeue func_8160A438. Best candidates were 212 bytes with similarity/raw 0.9623. The first durable mismatch was expected move s0,s3 versus actual addiu s1,s3, followed by the target blezl positive-byte branch versus candidate beqzl. Early-lived-base and explicit-end aliases increased frame size; next action should target a different base/source lifetime arrangement.

Explicit skip list for this box:

- Existing tie/stuck owners skipped: func_8160A6AC, func_8160A94C, func_8160A994, and func_8160B828.
- No jump-table-unready owners were present.
- Untouched fresh owners for the next wave: func_8160A50C, func_8160A9F0, func_8160ABF0, func_8160B128, func_8160B3E0, func_8160B5BC, and func_8160B6E4.
- An explicit-prototype batch was tooling-invalid because the runner already injected duplicate fallback declarations; it was not installed and should not be repeated without fixing the declaration-preflight path.

All accepted results were installed only through the runner after link verification and the combined full-ROM gate.
