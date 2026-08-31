# Region notes -- disasm/src/fragments/52/fragment52_27E4E0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## ROM-gated wave handoff (2026-08-30)

Wave 2026-08-30: accepted func_86401F60. Winning spelling keeps temp_fv1 for the +0x50 field but repeats direct f32 loads from arg0 + 0x48 in each x comparison. Probe was probe_match with link_verified=true; the combined full-ROM gate accepted it with gate_runs=1 and install_compiles=1.

Terminal requeue diagnostics:
- func_864068A4: switch/loop fade-else shape reached 312 bytes and 78 instructions, with best normalized/raw similarity 0.9872/0.9872 and 77/78 instructions matching. First diff was offset 108, instruction 27: expected ori a1,a1,0xffff, actual move a0,zero. The runner reported repeated-drift after 12 prior rejected attempts with fingerprint [instruction_drift,108,27,0x34a5ffff,0x00002025]. A 35-second permuter run ended without output; an explicit goto shape was 304 bytes/76 instructions at 0.8462 normalized and 0.7949 raw, first differing at instruction 10 (expected beqz v1,9, actual beqz v1,15). Requeue for a materially different switch scheduling or allocation shape; the gbi-macro tag is a false positive because this owner has no GBI instructions.
- func_86405CB4: three fixed-stride initialization loops plus the large-offset state tail. Best normalized score was 0.9302 with raw 0.6395 (80/86 matched); first diff offset 45, instruction 11, expected lw s0,0(s2), actual lw s1,0(s2). An ordered-setup variant improved raw similarity to 0.8372 with 76/85 matches but remained 344 bytes/86 instructions versus 340/85. Requeue for a typed context overlay and loop-bound/large-offset scheduling work.
- func_864028B8: raw-field switch body reached exact 372 bytes/93 instructions and 91/93 normalized matches, normalized/raw similarity 0.9785/0.6774. First diff offset 21, instruction 5: expected addiu v1,zero,1, actual addiu t0,zero,1. The 45-second permuter timed out with base score 355 and best score 145. Requeue for a typed overlay or new return-register allocation shape. One earlier batch had a duplicate func_8002781C prototype and was rejected at compile preflight; it is not owner evidence.
- func_86403B3C: raw float/list scan reached 360 bytes/90 instructions versus 376/94, with 0.9362 normalized and 0.7128 raw similarity, 88/94 normalized matches. First diff offset 74, instruction 18 was the floating-register setup; later drift included the missing branch-scheduled duplicate subtraction and shifted stack temporaries. Requeue for a typed overlay and explicit preservation of the floating conditional shape.
- func_86406710: direct raw state-list cleanup reached 384 bytes/96 instructions versus 404/101, with 0.8911 normalized and 0.2871 raw similarity, 90/101 matched. First diff offset 27, instruction 6: expected beq v0,zero,90, actual beq v0,zero,85. Requeue for preserving the expected branch-likely list traversal and global context register flow.

## Wave 16 handoff (2026-08-31) (2026-08-31)

requeue: func_8640633C (prior_attempts=2). A typed overlay reached normalized/raw similarity 0.8269/0.5192 with 86/104 normalized instructions. First diff offset 5: expected lui v1, D_86416C00, actual lui v0. Next declaration/global-base ordering.
