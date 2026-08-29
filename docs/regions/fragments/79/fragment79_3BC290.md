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

**Runner was unavailable this whole box** (background agent; `python3`/`fleet_probe.py` permission prompts auto-denied — see end). All batches below are written and *unprobed*; run `python3 tools/fleet_probe.py /tmp/fleet-fragment79_3BC290/batchN.json` in order, gate hits with `--gate`, install, then commit `disasm/src/fragments/79/fragment79_3BC290.c`.

- `batch1.json` (15 cands): record-family `func_8414CA00` (4), `func_8414CA80` (3), `func_8414CEE0` (3), `func_8414CF74` (1), `func_8414CD18` (3). CEE0/CF74 are near-identical siblings — reuse the winner's spelling. Decls: `extern void func_84149D54(void *, u8, u8); extern void func_84149D0C(void *);` (the shared record helpers from `fragment79_3B7EA0.c`).
- `batch2.json` (11 cands): `func_8414CB10`, `func_8414D610` (clamp u16 bgez polarity), `func_8414E760` (dual-global notify), `func_8414E224`, `func_8414ECE0`, `func_8414EB90` (formula u8-blend), `func_8414D910` (callseq two-path store), `func_8414E508` (h-word zeroing pair with `beql` returns — see §5 bnel/beql note in AGENTS.md; the branch-likely lowerings here look IDO-natural). Decls include `extern u8 *D_841951F8[]` etc.
- `batch3.json` (6 cands): `func_8414E5B0` / `func_8414E7D8` — 42-instr siblings: `v = func_84154B24(); inv = 1 - v; pA = func_84154B64(v); pB = func_84154B64(inv);` then E5B0: `if (v == arg0[5]) { if (pA[0x28] + *(u16*)(arg0+v*2+0x16) < pA[0x2A]) { if (*(u16*)(arg0+inv*2+0xE) < *(u16*)(arg0+v*2+0x16)) { *(s32*)(arg0+v*4+0x38) *= 2; } } }`; E7D8: chained `if (pA[0x28] < *(u16*)(arg0+inv*2+0xE)) store; else if (inv == arg0[5]) { if (pA[0x28] < 2*val) store; }` where store = `*(s32*)(arg0+v*4+0x38) *= 2`. The else-if-chain vs disjunction variants are both included.
- `batch4.json` (6 cands): `func_8414D9B8` (3): `kind = func_80062D20(arg0[inv+6]); if (kind ∉ {0x1A,0x27,0x4B,0x50,0x91}) { if (arg0[v+6] != 0x4C) *(u16*)(arg0+4+inv*2+0xA) *= 2; else if (func_84154B18() != 2) same store; }` — the five `beq`-to-end constants form the guard; store is `lhu; sll 1; sh` (×2). `func_8414CE08` (3): clamp/mid helper `mid = (pA[0x28]+pB[0x28]) >> 1; d1 = min(mid, pA[0x2A]) - pA[0x28]; d2 = min(mid, pB[0x2A]) - pB[0x28];` then `if (d1 > 0) *(u16*)(arg0+arg1*2+0x16) = d1; else *(u16*)(arg0+arg1*2+0x1E) = -d1;` and d2 at 0x12/0xE (`sh` of `negu`). min written as `(mid < x) ? mid : x` ternary; if-form variant included.
- `batch5.json` (10 cands): `func_8414D51C` (2): `kind = func_80062D20(arg0[arg1+6]); if (kind ∈ {0x27,0x4B,0x97}) pA[0x17] toggle bit 0x10 (clear 0xFFEF / set 0x10) via flags temp; else if (kind == 0x9B) { if (pA[0x17]&0x10) pA[0x17] &= 0xFF8F; else { pA[0x17] |= 0x10; if (sp1B == 0x13) pA[0x17] |= 0x40; else if (sp1B == 0x5B) pA[0x17] |= 0x20; } }` — sp1B = arg0[arg1+6] reloaded for the inner compares. `func_8414E658` (2): `if (v == arg0[5]) { if (*(u16*)(arg0+4+inv*2+0xA) < pA[0x28]) { if (func_841556C4(pB, 0x6F) == 0) *(u16*)(arg0+4+v*2+0xA) *= 3; } } else if (2*val < pA[0x28]) { same; }` — note first path plain compare, second path `sll 1` before `slt` (`(u16)(x*2)`). `func_8414DA70` (2): `pA = func_84154B64(v); func_84154B64(inv);` (result DISCARDED — call kept), `sum = (u16)(*(u16*)(arg0+4+v*2+0x1A) + *(u16*)(arg0+4+inv*2+0xA)); store; if (sum > pA[0x28]) store pA[0x28];` `func_8414EC18` (1): switch on `func_80062D20(arg0[s0+6])`: 0x30 → `*(u16*)(arg0+s0*2+0x1E) = 0`; 0x59/0x90 → `func_8414DC58(arg0, s0)`; 0x6F → `func_8414EB90(arg0)`; 0x9B → `func_8414EA4C(arg0)`. `func_8414DC58` (1): `if (pA[0x28] >= *(u16*)(arg0+inv*2+0xE))` switch on kind: 0x27/0x4B/0x91 → `if (arg1 != func_84154B24() || (pB[0x17] & 0x10)) func_8414DB14((u8*)arg0+4, arg1);`; 0x50 → `if (!(pB[0x18] & 0x20)) call;`; default → call. `func_8414EA4C` (2): `if (v == arg0[5])` switch on `arg0[v+6]`: 0x10/0x12/0x57 (and 0xEF variant) → `if (pB[0x17]&0x20) *(u16*)(arg0+4+v*2+0xA) = 0;`; 0x59/0x5A/0xDE → `if (pB[0x17]&0x40) same-store;`; default → `if (pB[0x17]&0x10) same-store;`; else branch (v != arg0[5]) → `if (!(pB[0x17]&0x10)) *(u16*)(arg0+4+inv*2+0xA) = 0;`.

### Not yet analyzed (next box): `func_8414CB74` (105, switch + IDO-4x-unrolled loop with remainder pre-loop + `blezl` chains — save for last), `func_8414D008` (100), `func_8414D348` (117), `func_8414D720` (124, already `extern void func_8414D720(s32, u8)`), `func_8414DB14` (81, callee of DC58), `func_8414E2A8` (152), `func_8414EB90` (81, callee of EC18), `func_8414E224` (in batch2), `func_8414D910` (in batch2), `func_8414CB10` (in batch2).

## Blockers this box (2026-08-28)

- **No probes ever ran**: every `python3 tools/fleet_probe.py ...` attempt (~12×, all batch files) was denied by the permission layer ("Tool requires permission, but background agents cannot prompt"). `ls`/`cat`/`git`/`pwd` are allowlisted and work; `python3` is deny-cached despite `Bash(python3 *)` in `.qwen/settings.json`. 32 owners remain; the 5 batches above (48 candidates over 21 owners) just need a runner.
- If the wall persists for your box too, write the analysis into this file (`write_file`, since `region_notes.py` is python3-blocked) and commit it directly with `git commit --only docs/regions/fragments/79/fragment79_3BC290.md -m "..."`.