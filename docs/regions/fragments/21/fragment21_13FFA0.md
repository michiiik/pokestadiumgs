# Region notes -- disasm/src/fragments/21/fragment21_13FFA0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## func_82501754 tooling-blocked preflight (2026-08-30)

tooling-blocked (box preflight, no candidate submitted): func_82501754 is a fresh 48-instruction call_sequence/state mapper with prior_attempts=0. Assembly reads *(u16 *)arg0 at field 0 and maps 0x100 -> 1, 0x101 -> 2, 0x300 -> 4, 0x301 -> 8, all other values -> 0. For a nonzero flag it ORs the flag into byte D_82508FD8, derives a s32 boolean from (*(s16 *)D_82508680 != 0), then calls func_80055F6C(&D_82508FCC, bool), func_80051D64(0x14, 0), and func_80054E48(3). Prepared first probe family: u16 *arg0; s32 result initialized to 0; switch with the four literal cases; s16 *D_82508680; u8 D_82508FD8; D_82508FCC as the address passed to func_80055F6C with its exact two-argument prototype. Score/fingerprint: n/a because no probe was legally run. The shared checkout contained foreign modified source files fragment11_E1E10.c and fragment50_266A60.c plus live disasm/probes/.pragma_probe_1im54o1g, so AGENTS.md §1.2 prohibited a runner/build transaction. Next action: resume this owner first after the foreign install/probe transaction is committed or isolated; probe switch-vs-if mapping, global D_82508FCC scalar/byte-array address spelling, and boolean explicit-if vs direct comparison, then full-gate the first probe hit. No other owner was skipped in this box; keep the coordinator ordinary-retry skip list (func_82500CF0, func_82502E20, func_82500D24, func_82502E60, func_8250008C, func_82500120, func_82502854, func_825038A4, func_82501034, func_825003DC, func_82503750, func_82500EF4, func_825045EC, func_82502DDC) unchanged.

## func_82501754 tooling-blocked recheck (2026-08-30)

tooling-blocked (2026-08-30 14:00Z, resumed box): no candidate was submitted and no ROM gate ran. The assigned source is clean and the temporary .pragma_probe directory is clear, but foreign modified source installs remain under live claims in disasm/src/fragments/11/fragment11_E1E10.c and disasm/src/fragments/50/fragment50_266A60.c; live claims also cover fragments/44/fragment44_1EE290.c, fragments/46/fragment46_code.c, and fragments/52/fragment52_27E4E0.c. Under AGENTS.md §1.2, a shared runner transaction is unsafe until those installs are committed or isolated. func_82501754 remains fresh with prior_attempts=0; the read-only m2c draft confirms u16 *arg0, a s32 result mapping 0x100/0x101/0x300/0x301 to 1/2/4/8, u8 D_82508FD8, s16 *D_82508680, scalar s32 D_82508FCC, and calls func_80055F6C(&D_82508FCC, bool), func_80051D64(0x14, 0), func_80054E48(3). No accepted owner or gate evidence. Next action: when the foreign source installs are committed or isolated, probe switch-vs-if mapping, scalar-versus-byte-array D_82508FCC spelling, and explicit-if versus direct comparison; full-gate the first link-verified hit. Do not repeat the ordinary-retry skip list from the prior handoff.

## 2026-08-31 tooling-blocked-owner requeue (2026-08-31)

requeue func_82501754: runner work was finally available; four probe batches and 19 candidates were attempted. Best switch:scalar:ternary-bool reached normalized/raw 0.9167/0.6042 with exact 192/192-byte size, but no link_verified candidate or ROM gate. Compile failures confirmed D_82508680 needs an s32 address model with explicit (s16 *) casting. Next action is to preserve the switch mapping while targeting register allocation around lhu/result initialization and the boolean temporary.

## Fleet box 2026-08-31: mapping helper requeued (2026-08-31)

No accepted owner. func_82501754 received 11 serial CC_CHECK-enabled candidates; best switch:scalar:boolean-init-before-flag was 0.8958 normalized / 0.7917 raw, exact 192-byte size, with instruction drift at offset 24: expected lui $t6 but actual or $a1,$zero,$zero. Next spelling: preserve the switch and scalar address model, but move boolean zero initialization after the flag-address/load scheduling point. Keep the prior ordinary-retry skip list unchanged.

## Fleet box 2026-08-31: mapping helper requeued (2026-08-31)

requeue: func_82501754 received 7 new serial CC_CHECK-enabled candidates. Best normalized/raw similarity was 0.8958/0.7500 at exact 192 bytes, with persistent instruction drift at offset 16: expected or v1,zero,zero versus actual lui a0,0. Next action: force a0/D_82508FCC address formation after the switch via an explicit call wrapper or separate post-branch assignment while preserving the scalar model and explicit (s16 *)D_82508680 cast.

## Wave 11 handoff (2026-08-31)

No accepted owner. func_82504524 received 12 CC_CHECK-enabled probes. Best normalized/raw similarity was 0.6400/0.1400; the persistent first mismatch is expected lui $a2 versus actual lui $a1. Next action is a declaration and global address model that places D_82508F68 in $a2 and D_82508680 in $a3. No link_verified candidate or ROM gate.
