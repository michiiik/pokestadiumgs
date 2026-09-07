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

## Wave 16 handoff (2026-08-31) (2026-08-31)

tooling-blocked: func_825003DC was fresh (prior_attempts=0); EMFILE occurred before any probe. The model is six arguments (five s32 values plus an s32* output) with an f32 return. Next action: after descriptor recovery, try explicit sum/end/den temporaries.

## func_82502528 requeue (2026-09-02) (2026-09-02)

requeue: func_82502528 (67 instructions, prior_attempts=0 before this box) received 8 distinct CC_CHECK-enabled runner candidates after one initial 8-candidate preflight batch was rejected for redundant typedef declarations (process/tooling evidence; no source hypothesis counted). Corrected batch attempted raw-pointer while/for forms, explicit count, post-increment loop, typed count/base, guard-loop, s32 selector, and switch selector families. All 8 probe_rejected; no link_verified candidate and no ROM gate. Best normalized/raw score 0.6571/0.1714 (call-sequence:raw:explicit-count), expected/actual size 268/280 bytes. Stable first-diff fingerprint: operand_or_scheduling_drift at offset 3, expected addiu $sp,$sp,-64, actual addiu $sp,$sp,-72; other candidates produced 280-296 byte bodies. The candidate declarations included exact func_82502404(u8 *, u8 *, s16, s32, s32, s32, s32), globals D_82508F68/D_82508F84/D_82508D10/D_82508D12 and selector globals. Attempted hypothesis families: raw pointer arithmetic, declaration/lifetime order, explicit count, typed base/count, if polarity, selector width, switch. Next materially different action: reconstruct the 0x40 frame with compiler-faithful fixed-size local overlays/arrays (likely four stack-passed arguments at 0x10/0x14/0x18 plus saved registers), then vary only local declaration order and callee formal types; do not repeat pointer-heavy bodies.

## 2026-09-07

func_82500CF0: matched (state_field_access:hoisted-index:inner-neq-empty), 3 iterations, agent codex

## 2026-09-07

func_82502E20: plateau at 0.9375 (raw 0.6875), mismatch operand_or_scheduling_drift; tried families: constant_map; tie-pool no

## 2026-09-07

func_82500D24: matched (state-field:switch:index-before-switch), 1 iterations, agent codex

## 2026-09-07

func_82502DDC: time cap at 0.9412 (raw 0.5294) after 2411s, mismatch operand_or_scheduling_drift; tried families: constant_map; tie-pool no

## 2026-09-07

func_82502E60: matched (constant-map:result:offset-plus-base), 1 iterations, agent codex

## 2026-09-07

func_8250008C: MATCHED (register-tie permuter sweep, batch 3). Stored tie candidate 'state_field_access:state-pointer:local' sat at normalized 1.0 / raw 0.6486, register_allocation_only, first diff at offset 17 (expected 'lhu $v0, $v0, 0', actual 'lhu $v1, $v0, 0') after 65 hand attempts. permute_candidate.py round 1 (420s) took the score 75 -> 30; round 2 re-based on that body reached 0. Two permuter artifacts in the landed body are load-bearing register-allocation levers, NOT dead code -- do not 'clean them up': the redundant 'if ((arg0 != 0) && (arg0 == 1))' guard, and the comma-operator store '*((0, state)) = new_var2 + 0x100'. Only whitespace/indent was normalised after the permuter; every token is as the permuter emitted it. Verified with tools/fleet_probe.py (accepted, link_verified=true) and container/gate_pr.sh: MD5 1561c75d11cedf356a8ddb1a4a5f9d5d, OK.
