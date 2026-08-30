# Region notes -- disasm/src/fragments/79/fragment79_3C40B0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## func_841557B0 accepted (2026-08-30)

func_841557B0: accepted by runner full-ROM gate on 2026-08-30 via permute:score0:statement-coalesced. Source spelling is u8 temp_v0 = ((*D_8419E920) - 1) & 0xFF; store it to *D_8419E920; then _bcopy((D_8419E920 + (temp_v0 * 0x19C)) + 4, D_8419E780, 0x19C) with the store and call on one source line. Probe was link_verified=true; gate_runs=1, gate_mode=combined, exit_code=0. Earlier ordinary spellings repeatedly drifted at offset 0x40 (oracle addiu a1,a1,%lo(D_8419E780), candidate sb v0,0(v1)) at best normalized/raw 0.96/0.96; runner reported repeated-drift after 12+ prior rejects. The score-0 permuter output was re-probed and gated; do not treat permuter score alone as proof. No evidence-backed rename was available. Remaining explicit owners must be rechecked with pragma_targets before assignment.

## func_841556C4 accepted (2026-08-30)

func_841556C4: accepted by the runner's full-ROM gate on 2026-08-30 using call_sequence:locals:masked-u8. The winning spelling uses a u8 masked comparison local (var_s3), s32 sentinel/limit locals, a byte-step pointer, and the goto loop; this changed the prior register-only drift (best 0.9714 normalized / 0.8286 raw, first diff offset 0x19, expected andi  vs actual ) into a link-verified probe match. Gate result: accepted, link_verified=true, gate_runs=1, gate_mode=combined, exit_code=0. name_decompiled plan found no evidence-backed rename. The runner also reported repeated-drift from 15 earlier attempts, but this u8 width hypothesis resolved it; do not treat probe or normalized similarity alone as acceptance evidence. Recheck explicit owners with pragma_targets before assignment.
