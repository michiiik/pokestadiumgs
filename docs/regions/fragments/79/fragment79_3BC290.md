# Region notes -- disasm/src/fragments/79/fragment79_3BC290.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Skip list: dispatcher owners (no `.rodata` subsegment in this file yet) (2026-08-28)

A C `switch` in these would emit its own jtbl into the owner's `.rodata` and shift the ROM (`section_layout_drift`). Do NOT spend time here until the file gets a `.rodata` subsegment (`tools/add_rodata_subsegments.py for-jtbl` + re-split + gate the still-assembly owner):

- `func_8414D198`
- `func_8414E880`
- `func_8414DD94`

Note `func_8414E880` is already *called* by solved `func_8414ED5C`/`func_8414EDB4` (`extern void func_8414E880(s32)`), so it must stay assembly; only its decompilation is blocked by the subsegment.

## Shared callee conventions (verified by reading fragment79_3B7EA0.c + func_84149D54.s)

- `u8 func_84154B24(void)` — no-arg selector; returns u8 (the "current side" index; siblings do `sp1E = 1 - sp1F` for the other side).
- `u8 *func_84154B64(u8)` — record lookup by side index; records hold the pair fields: `u16 @0x28`, `u16 @0x2A`, byte flags at `0x17`/`0x18` (`0x10` = active bit, `0x20`/`0x40` bits, `0x6F` used as a magic arg), and callers index 16-bit arrays at record+0x28/0x2A.
- `u8 func_80062D20(u8)` — categorizer ("kind") of a byte; returns small constants (0x1A/0x27/0x4B/0x4C/0x50/0x59/0x6F/0x90/0x91/0x97/0x9B/0x30/0x13/0x5B/0x10/0x12/0x57/0x5A/0xDE/0xEF appear across owners).
- `u8 func_84154B18(void)` — no-arg counter; results compared to 2.
- `s32 func_841556C4(u8 *rec, u8 magic)` — callers pass `(pB, 0x6F)`; nonzero result skips the following store.
- `void func_8414DB14(u8 *base, u8 side)` — called by `func_8414DC58` with `(arg0 + 4, arg1)`.
- `void func_8414DC58(s32, u8)`, `void func_8414EB90(s32)`, `void func_8414EA4C(s32)` — switch-dispatch helpers called by `func_8414EC18`; all three are pragma owners in this file.
- Declarations used in the batches: put ALL of the above (except `func_8414DB14/DC58/EB90/EA4C` when they are the target's own file) plus `func_84154B24` in the `declarations` argument — the runner only injects same-file solved callees.

## Analyzed shapes with ready-to-run candidate batches (2026-08-28)

These batches were prepared during the previous box and were executed in order
on 2026-08-29 with the runner available. They remain useful as the baseline for
future hypotheses; do not repeat the already-decompiled owners listed in the
results below.

- `batch1.json` (14 cands): record-family `func_8414CA00` (4), `func_8414CA80` (3), `func_8414CEE0` (3), `func_8414CF74` (1), `func_8414CD18` (3). CEE0/CF74 are near-identical siblings — reuse the winner's spelling. Decls: `extern void func_84149D54(void *, u8, u8); extern void func_84149D0C(void *);` (the shared record helpers from `fragment79_3B7EA0.c`).
- `batch2.json` (11 cands): `func_8414CB10`, `func_8414D610` (clamp u16 bgez polarity), `func_8414E760` (dual-global notify), `func_8414E224`, `func_8414ECE0`, `func_8414EB90` (formula u8-blend), `func_8414D910` (callseq two-path store), `func_8414E508` (h-word zeroing pair with `beql` returns — see §5 bnel/beql note in AGENTS.md; the branch-likely lowerings here look IDO-natural). Decls include `extern u8 *D_841951F8[]` etc.
- `batch3.json` (6 cands): `func_8414E5B0` / `func_8414E7D8` — 42-instr siblings: `v = func_84154B24(); inv = 1 - v; pA = func_84154B64(v); pB = func_84154B64(inv);` then E5B0: `if (v == arg0[5]) { if (pA[0x28] + *(u16*)(arg0+v*2+0x16) < pA[0x2A]) { if (*(u16*)(arg0+inv*2+0xE) < *(u16*)(arg0+v*2+0x16)) { *(s32*)(arg0+v*4+0x38) *= 2; } } }`; E7D8: chained `if (pA[0x28] < *(u16*)(arg0+inv*2+0xE)) store; else if (inv == arg0[5]) { if (pA[0x28] < 2*val) store; }` where store = `*(s32*)(arg0+v*4+0x38) *= 2`. The else-if-chain vs disjunction variants are both included.
- `batch4.json` (6 cands): `func_8414D9B8` (3): `kind = func_80062D20(arg0[inv+6]); if (kind ∉ {0x1A,0x27,0x4B,0x50,0x91}) { if (arg0[v+6] != 0x4C) *(u16*)(arg0+4+inv*2+0xA) *= 2; else if (func_84154B18() != 2) same store; }` — the five `beq`-to-end constants form the guard; store is `lhu; sll 1; sh` (×2). `func_8414CE08` (3): clamp/mid helper `mid = (pA[0x28]+pB[0x28]) >> 1; d1 = min(mid, pA[0x2A]) - pA[0x28]; d2 = min(mid, pB[0x2A]) - pB[0x28];` then `if (d1 > 0) *(u16*)(arg0+arg1*2+0x16) = d1; else *(u16*)(arg0+arg1*2+0x1E) = -d1;` and d2 at 0x12/0xE (`sh` of `negu`). min written as `(mid < x) ? mid : x` ternary; if-form variant included.
- `batch5.json` (10 cands): `func_8414D51C` (2): `kind = func_80062D20(arg0[arg1+6]); if (kind ∈ {0x27,0x4B,0x97}) pA[0x17] toggle bit 0x10 (clear 0xFFEF / set 0x10) via flags temp; else if (kind == 0x9B) { if (pA[0x17]&0x10) pA[0x17] &= 0xFF8F; else { pA[0x17] |= 0x10; if (sp1B == 0x13) pA[0x17] |= 0x40; else if (sp1B == 0x5B) pA[0x17] |= 0x20; } }` — sp1B = arg0[arg1+6] reloaded for the inner compares. `func_8414E658` (2): `if (v == arg0[5]) { if (*(u16*)(arg0+4+inv*2+0xA) < pA[0x28]) { if (func_841556C4(pB, 0x6F) == 0) *(u16*)(arg0+4+v*2+0xA) *= 3; } } else if (2*val < pA[0x28]) { same; }` — note first path plain compare, second path `sll 1` before `slt` (`(u16)(x*2)`). `func_8414DA70` (2): `pA = func_84154B64(v); func_84154B64(inv);` (result DISCARDED — call kept), `sum = (u16)(*(u16*)(arg0+4+v*2+0x1A) + *(u16*)(arg0+4+inv*2+0xA)); store; if (sum > pA[0x28]) store pA[0x28];` `func_8414EC18` (1): switch on `func_80062D20(arg0[s0+6])`: 0x30 → `*(u16*)(arg0+s0*2+0x1E) = 0`; 0x59/0x90 → `func_8414DC58(arg0, s0)`; 0x6F → `func_8414EB90(arg0)`; 0x9B → `func_8414EA4C(arg0)`. `func_8414DC58` (1): `if (pA[0x28] >= *(u16*)(arg0+inv*2+0xE))` switch on kind: 0x27/0x4B/0x91 → `if (arg1 != func_84154B24() || (pB[0x17] & 0x10)) func_8414DB14((u8*)arg0+4, arg1);`; 0x50 → `if (!(pB[0x18] & 0x20)) call;`; default → call. `func_8414EA4C` (2): `if (v == arg0[5])` switch on `arg0[v+6]`: 0x10/0x12/0x57 (and 0xEF variant) → `if (pB[0x17]&0x20) *(u16*)(arg0+4+v*2+0xA) = 0;`; 0x59/0x5A/0xDE → `if (pB[0x17]&0x40) same-store;`; default → `if (pB[0x17]&0x10) same-store;`; else branch (v != arg0[5]) → `if (!(pB[0x17]&0x10)) *(u16*)(arg0+4+inv*2+0xA) = 0;`.

## Runner results for the prepared batches (2026-08-29)

The five batches ran probe-only, in order, for **47 variants across 21
candidate owners** (14 + 11 + 6 + 6 + 10). There were **0 new accepted
owners and 0 gate runs**. Eight attempts were `probe_unavailable` with
`probe_reason=invalid_pragma`, because these owners are already C definitions
in this file: `func_8414CA00` (4), `func_8414CEE0` (3), and `func_8414CF74`
(1). This is not a runner outage and those candidates must not be retried.

The 39 scored rejects were 34 `operand_or_scheduling_drift`, 2
`register_allocation_only`, 2 `instruction_drift`, and 1 `immediate_drift`.
Best result and first differing shape per remaining owner:

- `func_8414CA80`: 0.8611/0.4167, operand/scheduling; `andi $a2, $a2, 255` expected vs `andi $a1, $a1, 255`.
- `func_8414CD18`: 0.9268/0.4634, operand/scheduling; frame `-88` expected vs `-104`.
- `func_8414CB10`: 0.9600/0.1600, operand/scheduling; frame `-16` expected vs `-8`.
- `func_8414D610`: 1.0000/0.8571, register allocation; `lbu $t7, $sp, 31` expected vs `$t6`; runner reports register-tie stop after six prior attempts.
- `func_8414E760`: 1.0000/0.6667, immediate drift; frame `-40` expected vs `-32`.
- `func_8414E224`: 0.9697/0.8788, operand/scheduling; branch offset `9` expected vs `8`.
- `func_8414ECE0`: 0.8065/0.6452, operand/scheduling; `lbu $t1, $sp, 31` expected vs `$t0`.
- `func_8414EB90`: 0.5938/0.3438, operand/scheduling; expected stack reload into `$a1` vs `$a3`.
- `func_8414D910`: 0.9286/0.4524, operand/scheduling; `sw $s1, $sp, 24` expected vs `sw $s0, $sp, 20`.
- `func_8414E508`: 0.7143/0.2857, operand/scheduling; expected `lw $a2, $sp, 24` vs `$a1`.
- `func_8414E5B0`: 0.8837/0.5116, operand/scheduling; `sb $t7, $sp, 30` expected vs `sb $v0, $sp, 31`.
- `func_8414E7D8`: 0.8571/0.4524, operand/scheduling; `lbu $a2, $sp, 30` expected vs `$a0`.
- `func_8414D9B8`: 0.8039/0.3529, operand/scheduling; frame `-40` expected vs `-32`.
- `func_8414CE08`: 0.9259/0.4259, operand/scheduling; frame `-40` expected vs `-56`.
- `func_8414D51C`: 0.7541/0.4918, instruction drift; `lw $t6, $sp, 32` expected vs `lbu $t6, $sp, 39`.
- `func_8414E658`: 0.8788/0.3030, operand/scheduling; `sw $ra, $sp, 20` expected vs `sw $ra, $sp, 28`.
- `func_8414DA70`: 0.8537/0.4634, operand/scheduling; `lw $t8, $sp, 32` expected vs `$a1`.
- `func_8414EC18`: 0.7647/0.3333, operand/scheduling; frame `-32` expected vs `-40`.
- `func_8414DC58`: 0.7975/0.3165, operand/scheduling; frame `-56` expected vs `-48`.
- `func_8414EA4C`: 0.7901/0.2840, operand/scheduling; frame `-48` expected vs `-32`.

No new winning spelling was established, so no source owner was installed or
gated in this box. The dispatcher skip list above remains unchanged.

### Not yet analyzed (next box): `func_8414CB74` (105, switch + IDO-4x-unrolled loop with remainder pre-loop + `blezl` chains — save for last), `func_8414D008` (100), `func_8414D348` (117), `func_8414D720` (124, already `extern void func_8414D720(s32, u8)`), `func_8414DB14` (81, callee of DC58), `func_8414E2A8` (152), `func_8414EB90` (81, callee of EC18), `func_8414E224` (in batch2), `func_8414D910` (in batch2), `func_8414CB10` (in batch2).

## Blockers this box (2026-08-28)

- **No probes ever ran**: every `python3 tools/fleet_probe.py ...` attempt (~12×, all batch files) was denied by the permission layer ("Tool requires permission, but background agents cannot prompt"). `ls`/`cat`/`git`/`pwd` are allowlisted and work; `python3` is deny-cached despite `Bash(python3 *)` in `.qwen/settings.json`. 32 owners remain; the 5 batches above (48 candidates over 21 owners) just need a runner.
- If the wall persists for your box too, write the analysis into this file (`write_file`, since `region_notes.py` is python3-blocked) and commit it directly with `git commit --only docs/regions/fragments/79/fragment79_3BC290.md -m "..."`.

## 2026-09-07

func_8414CB10: time cap at 0.92 (raw 0.16) after 2418s, mismatch operand_or_scheduling_drift; tried families: state; tie-pool no

## 2026-09-07

func_8414D610: matched (call_sequence:clamp:u8-index-explicit-diff), 1 iterations, agent codex

## 2026-09-07

func_8414E760: matched (call_sequence:dual_notify:pad4-or), 2 iterations, agent codex

## 2026-09-07

func_8414ECE0: plateau at 0.9677 (raw 0.871), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-07

TYPE CONFLICT: func_84154B24 is extern u8 func_84154B24(void), not extern u8 func_84154B24()
