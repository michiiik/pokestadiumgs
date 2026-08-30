# Region notes -- disasm/src/fragments/46/fragment46_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Unsolved shape: branch-likely null guard (AGENTS.md §5) (2026-08-28)

A leading null/zero guard that IDO emits as a branch-likely (`bnel`/`beql`) where every C spelling produces a plain `bne` (`func_8AE011E0`/`func_8AE01248`). The §4 guard-polarity row does not cover it.

## Fleet box 2026-08-29: accepted owners and deferred near-misses (2026-08-29)

Accepted via MCP full linked ROM gate: func_8AE00380 label camera:temps:u8-ordered (two temporary u8 field pointers, 0xB4 then 0xA8); func_8AE0043C label gbi:display-env:hex-components (gSPDisplayList/gDPSetEnvColor/gSPDisplayList/gSPDisplayList with D_800D0510++); func_8AE03214 label range:ascending:s16 (ascending s16 range chain); func_8AE038DC label callchain:address-global (0x100-byte local buffer and D_8AE083EC as an address-decaying u8 array). Every accepted candidate reported link_verified:true and one combined full COMPARE=1 gate run. Deferred: func_8AE01164 best 0.8387 normalized / 0.4516 raw, instruction_drift around branch-likely scan and unaligned copy; func_8AE012B0 best 0.9091 normalized / 0.5758 raw, operand_or_scheduling_drift around output base and packed copy; func_8AE00230 best 1.0 normalized / 0.9032 raw, exact-size register-allocation tie (oracle v1 versus candidate t8 for D_8AE09B44 pointer store; probe-only companion retyped func_8AE00020 but did not install); func_8AE0605C best 0.8125 normalized / 0.4375 raw, state spill/branch-form drift; func_8AE027B0 best 1.0 normalized / 0.9783 raw, exact-size add.s operand-order register tie. Do not retry tie-pool owners func_8AE00C94, func_8AE032C8, func_8AE002AC, func_8AE00314, func_8AE01738; leave dispatcher_switch/jump-table owners as assembly. gDPSetFillColor was a one-instruction near-miss for 0043C; opcode 0xFB requires gDPSetEnvColor with four component arguments.

## Wave6 lookup ABI and caller requeues (2026-08-30)

Fleet box 2026-08-30 wave6. accepted `func_8AE00E54` via `lookup:scalar-loop:typed-bound-0x38`: `typedef struct { s16 key; u8 pad2[2]; s32 value; u8 pad8[8]; } Fragment46LookupEntry`; `Fragment46LookupEntry *func_8AE00E54(s16)`; plain `for (i = 0; i < 0x38; i++)` over `D_8AE08508`. Probe match had `link_verified:true` and the combined full `COMPARE=1` ROM gate passed. The identical raw-`u8` spelling also probe-matched, but the typed spelling was gated and installed.

requeue caller family after reusing the accepted lookup type/signature. Best probe-only results: `func_8AE018C4` 0.9455 normalized / 0.9273 raw, `func_8AE019A0` 0.9500 / 0.8000, `func_8AE01B88` 0.9259 / 0.8519, `func_8AE01CCC` 0.9508 / 0.9180, `func_8AE01DC0` 0.9474 / 0.9298. Common mismatch was `unaligned_data_drift`, fingerprint begins expected `or $s0, $a1, $zero` versus actual `sra` of the saved signed key at instruction 4; all but `01B88` reached exact size with direct-result `goto` loops, `s16 changed` flag, conditional `D_8AE08504` increment, then flag reset. Attempted families: m2c-style separate result, direct-result pointer loop, structured `while`, `goto`, pointer-formal companion prototype, K&R formals, declaration order, initialized locals, explicit global pointers, and `s32` formal plus `s16` key local. Next hypothesis: preserve the exact direct-result bodies and use source scheduling/permuter work focused only on moving `arg1` into the saved pointer before `arg0` sign extension; for `func_8AE018C4` also resolve the final commutative OR operand order. `func_8AE01A90` remains skipped as the exhausted 46-attempt prior near-miss (best 0.9677 / 0.9516 `operand_or_scheduling_drift`); the accepted callee confirms the record layout already assumed by its field access and does not materially reopen its ABI hypothesis.

## 2026-08-30 fleet box: explicit owners (2026-08-30)

func_8AE0566C — requeue, not reached before box expiry. Assignment targets confirmed prior_attempts=0 and hardness=fresh. Preserve it as a fresh explicit owner for the next wave.

## func_8AE0559C layout prerequisite (2026-08-30)

func_8AE0559C — layout-prerequisite. Assignment targets showed prior_attempts=0 and hardness=fresh. Eight runner probe attempts were made; no candidate reached code generation. Correct field candidates require Fragment46Entry, but the authoritative Fragment46Entry typedef/prototype is later in this same source: a declarations prefix duplicates it, a candidate without the prefix fails on the unknown type, and a void-pointer candidate conflicts with the later Fragment46Entry * prototype. Next action: coordinator/source-layout or runner source-order support must make the authoritative type available before this pragma; no tracked source edit was made.

## func_8AE02398 active requeue (2026-08-30)

func_8AE02398 — requeue. Assignment targets showed prior_attempts=0 and hardness=fresh; it remained the active owner until box expiry and accumulated 40 runner-mediated probe attempts, with no probe match and no gate. Best candidate state-update:switch:common-store: normalized similarity 0.9444, raw similarity 0.7778, expected 54 instructions versus actual 53; first mismatch at offset 40/instruction 10 was expected beql $v0,$zero with the field-8 load in its delay slot versus actual beq $v0,$zero. An exact-size direct-field variant did emit beql and 54 instructions but placed the case target two instructions late and allocated the field-8 load to the wrong register. Attempted typed/raw overlays, switch and goto layouts, branch-polarity and declaration-order variants, explicit halfword accesses, and bounded permutation; next action is a materially different branch-likely/control-flow plus register-allocation hypothesis.

## func_8AE028F8 requeue (2026-08-30)

func_8AE028F8 — requeue, not reached before box expiry. Assignment targets confirmed prior_attempts=0 and hardness=fresh. Next wave should assign it only after reconciling claims and the source target list.

## func_8AE026C8 requeue (2026-08-30)

func_8AE026C8 — requeue, not reached before box expiry. Assignment targets confirmed prior_attempts=0 and hardness=fresh. It shares the func_800504BC family, but this explicit owner was not displaced by the older sibling owner.

## func_8AE04EB8 requeue (2026-08-30)

func_8AE04EB8 — requeue, not reached before box expiry. Assignment targets confirmed prior_attempts=0 and hardness=fresh. It is the explicit gbi owner; next attempt must use real gbi.h macros and callee prototypes.
