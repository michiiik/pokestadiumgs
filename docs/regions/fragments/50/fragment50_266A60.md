# Region notes -- disasm/src/fragments/50/fragment50_266A60.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-29 fleet box (2026-08-29)

Accepted owners: func_86203ED8 with call-chain:nested-guard:raw-u8-direct-corrected (raw u8 offsets; commits 387cd65, link_verified:true and full COMPARE=1 gate); func_86201620 with call-chain:list-walker:s1-inside-loop (loop-carried s1 load shape; commit 387cd65, link_verified:true and full gate); func_86201DE4 with gbi:pipe-combine-displaylist:s32-args using gDPPipeSync, gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238), and gSPDisplayList (commit c80c6ec, link_verified:true and full gate); func_862014B8 with gbi:pipe-segment-env-displaylist:s32-args using gDPPipeSync, gSPSegment segment 0xF, gDPSetEnvColor alpha 0x80, and gSPDisplayList (commit 9567842, link_verified:true and full gate); func_86204A00 with call-chain:state-dispatch:switch-raw (commit 4ffb938, link_verified:true and full gate); func_862007FC with call-sequence:conditional-record:pad-local:duplicate-tail, including s16 pad local and func_862007FC_padding for the duplicate jr/nop tail (commit 2e021fb, link_verified:true and full gate). Deferred func_86203B08 after 12 probes: best similarity 0.8, operand_or_scheduling_drift from float stack-slot placement (&sp28 was sp+0x2C or sp+0x34 instead of oracle sp+0x28). Deferred func_8620157C after 12 probes: normalized similarity 1.0 but raw 0.6829, immediate_drift; its source-local forward prototype was extern s32 func_8620157C(s32), and companion_edits cannot edit a still-GLOBAL_ASM target. Deferred func_8620050C after 12 probes: best similarity 0.9762, instruction_drift; only initialization order differed (oracle ori s4,s4,0x1D9C precedes loop-counter zeroing).

## 2026-08-30 successor box (2026-08-30)

Accepted func_862005B4 with call-sequence:vector-record-loop:hybrid-offset-pad-exact:gate. Accepted spelling uses the active s32,s32,s32 prototype, local Point/Record overlays, s32 pad[2] to retain the 0x48 frame, cross[3], hybrid offset expressions for the three cross-product point arguments, and indexed Point access for the final dot product. Runner evidence: probe_status=probe_match, link_verified=true, status=accepted, gate=true, gate_runs=1, gate_mode=combined, gate_seconds=1.269, install_compiles=1; full COMPARE=1 gate passed and source installed. func_86204F20 was accepted earlier in this box with call-chain:fade-switch:explicit-state-default:gate; link_verified=true, gate_runs=1, gate_mode=combined, install_compiles=1, full COMPARE=1 passed. Requeue func_862009E4: best padded 5-float local struct shape was 60/60, normalized similarity 1.0, raw 0.9833, immediate_drift at instruction 35 (oracle lwc1 $f8,72($a0) vs candidate lwc1 $f10,0($v0)); 45-second permuter timed out with no output. Next action: vary compiler-faithful call-argument evaluation/declaration shape to swap those loads. Requeue func_86203DE8: best observed for-stride scan similarity 0.9167, raw 0.2167, operand_or_scheduling_drift from instruction 0; m2c/direct-cast overlays expanded to 67-81 instructions. Next action: recover the global-pointer/address and mask-constant register shape before retrying. Requeue func_8620169C: best call-chain:shuffle:permuter-pointer-short was 60/61, similarity 0.9672, raw 0.7705, instruction_drift at instruction 8 (oracle addiu $s3,$s3,0 vs candidate move $s0,$zero); later swap-tail register allocation also differs. Next action: force the source-level global-address setup and temporary declaration shape. Requeue func_86203C58: best direct-global-address was 62/62, similarity/raw 0.9677, instruction_drift at instruction 13 (oracle ori $s4,0x1D9C before loop-index zeroing; candidate move $s1,$zero). Next action: change the source initialization/constant-use ordering; do not gate the near miss.

## 2026-08-31 wave 18 requeue (2026-08-31)

Requeue func_86203F50 after 60 runner probes plus a 120-second, 2-thread permuter pass (score 180 to 170, no zero). The semantic twin is fragment49 func_86107EBC. Use real gbi.h gDPSetPrimColor/gDPSetEnvColor macros, byte formals arg3..arg8, and extern void func_87F06240(s32, s32, f32, f32, s32). Critical ABI finding: arg3 must be u8 (u16 produces the same code; color semantics favor u8); s32 arg3 delays the prologue and yields 344 bytes. Best spelling adds s32 temp_a2 = arg2 beside the separate sp24 spill: expected/actual size 348, normalized similarity 1.0000, raw 0.7816, immediate_drift only; every opcode and register matches but the candidate frame is -0x38 instead of oracle -0x30, incoming homes are all +8, and candidate sp24 is sp+0x20 instead of oracle sp+0x24. Direct u8-arg3/sp24 form has frame -0x28 and 0.9540/0.7126 but different else-call scheduling. Tried declaration-order/formal-copy subsets, volatile/array/address-taken locals, pad locals, temp reuse/lifetime forms, old-style callee prototype, K&R definition, and permuter. Reusing temp_a2 removes the spill; volatile pointer reaches -0x30 but expands/reorders to 372 bytes. Next action: start from gbi:number-draw:u8-arg3-copy-a2-only and find a compiler-faithful single-spill layout that shifts sp24 from +0x20 to +0x24 while reducing the frame from 0x38 to 0x30; inspect IDO local allocation or a sibling winner before more broad variants. No probe hit, link verification, gate, or source install. Tooling note: isolated worktree oracle symlink bootstrap succeeded and all probe descriptors were healthy with zero EMFILE/Too many open files errors; draft/permuter additionally required ignored read-only links for disasm/tools/m2c, decomp-permuter, and decomp-venv, which the worktree bootstrap did not create automatically.

## 2026-09-07

func_8620218C: time cap at 0.652 (raw 0.228) after 2400s, mismatch instruction_drift; tried families: call-chain; tie-pool no

## 2026-09-07

func_86202574: matched (call-sequence:nested-list:raw-byte-offset), 1 iterations, agent codex

## 2026-09-07

func_86201418: time cap at 0.9667 (raw 0.7667) after 2430s, mismatch operand_or_scheduling_drift; tried families: call-sequence; tie-pool no

## 2026-09-07

func_86203D50: matched (call-sequence:raw-fields:direct-global-exact), 1 iterations, agent codex

## 2026-09-07

func_86203BA8: plateau at 0.8947 (raw 0.3684), mismatch operand_or_scheduling_drift; tried families: state-field; tie-pool no

## 2026-09-07

func_86201790: time cap at 0.9231 (raw 0.5) after 2423s, mismatch operand_or_scheduling_drift; tried families: state-field; tie-pool no

## 2026-09-07

func_8620157C: matched (call-chain:resource-scale:arg-first-product), 2 iterations, agent codex
