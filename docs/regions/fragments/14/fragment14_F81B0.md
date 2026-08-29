# Region notes -- disasm/src/fragments/14/fragment14_F81B0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Skip list: jtbl / dispatcher owners (no `.rodata` subsegment in this file yet) (2026-08-28)

All of these reference `jtbl_*` globals and are classified `dispatcher_switch`/`jump_table_map`; a C `switch` would emit its table into the owner's `.rodata` and shift the ROM (`section_layout_drift`). Do NOT spend time here until the file gets a `.rodata` subsegment (`tools/add_rodata_subsegments.py for-jtbl` + re-split + gate the still-assembly owner):

- `func_81300B50` (jtbl_813121B4, 20 instr)
- `func_813018FC` (jtbl_81312200, 51 instr)
- `func_813021B4` (jtbl_81312274, 55 instr)
- `func_81300730` (jtbl_81312198, 64 instr)
- `func_81301548` (jtbl_813121DC, 64 instr)
- `func_8130209C` (jtbl_8131224C, 70 instr)
- `func_81301F64` (jtbl_81312224, 78 instr)

## Analyzed shapes with ready-to-run candidate batches (2026-08-28)

Ready JSON batches (not yet probed — runner unavailable during this box) in `tmp/fleet-fragment14_F81B0/`:
- `batch1_000BC.json` — `func_813000BC` (8 instr, "stuck" at 0.7273, 85 prior attempts)
- `batch2_siblings.json` — `func_81301BDC` / `func_81301C54` (30 instr each, prior best 1.0 normalized / 0.9 raw `immediate_drift`)
- `batch3_small.json` — `func_8130150C`, `func_81302290`, `func_813002D0`, `func_81301030`

### func_813000BC — byte flag + "set 1" store pair (run batch1 first; unblocks the siblings)

```c
void func_813000BC(void *arg0, s32 arg1) {
    *(s8 *)((u8 *)arg0 + 0x1A141) = arg1;
    *(s32 *)((u8 *)arg0 + 0x1A16C) = 1;
}
```
Asm pairs `lui $at, 0x20000>>16; addu $at,$at,$a0` twice, storing `sb -0x5EBF` then `sw` (delay slot of `jr`) `-0x5E94` — that is IDO's round-up split of 0x1A141/0x1A16C (`0x20000` base, signed offsets), not a global symbol. `arg0` is the object base pointer (callers are `func_81301BDC/C54` passing `$s0`). No `andi` on `$a1` → `s32` arg1 primary, `u8` variant included. `0x1A148`/`0x1A154`/`0x1A168`/`0x1A16C` are the same object's field cluster used by solved `func_813000E4`/`func_813014D0`/`func_813022D8`.

### func_81301BDC / func_81301C54 — 6-call chain with conditional tail (batch2)

```c
void func_81301BDC(void *arg0, s32 arg1) {
    void *sub = (u8 *)arg0 + 0xD18;
    func_8130C334(sub);
    func_81311AAC((u8 *)arg0 + 0x74, arg1);
    func_8130F2C4(arg0, arg1);
    func_8130B3B8(sub, (u8 *)arg0 + 0x1A154);
    if (func_8130CDD4(sub)) {
        func_813000BC(arg0, 2);
    }
}
```
Key shapes: `arg1` spilled to 0x2C before call 1 (live across it); `sub` computed once (pass 1) and spilled to 0x24 for calls 5-6 (`lw` in delay slots); `0x1A154` materialised `lui 0x1 + ori 0xA154` (argument, not store offset). `func_8130B3B8` is `void (void *, void *)` (extern proven in `fragment14_FF070.c`); the other four callees are still pragmas in other fragment14 files — declare them in `declarations` (signatures above). Prior 1.0-normalized/0.9-raw near miss was `immediate_drift` — these spellings with real prototypes should close it. `func_8130CDD4` is only a *callee* here, so the trailing-nop probe quirk (AGENTS.md §5) does not apply.

### func_8130150C — byte-twin of solved func_813014D0 (batch3)

Asm is shape-identical to already-accepted `func_813014D0` (spill `$a0` at 0x18, `func_8130015C(arg0,0)`, `func_81300350()`, store 0 at `arg0+0x1A168`). Byte-copy the accepted spelling:

```c
void func_8130150C(void *arg0) {
    s32 temp_a0;
    temp_a0 = (s32)arg0;
    func_8130015C(arg0, 0);
    func_81300350();
    *(s32 *)((u8 *)temp_a0 + 0x1A168) = 0;
}
```

### func_81302290 — sign guard then two calls, returns callee's value (batch3)

```c
s32 func_81302290(void *arg0) {
    s8 value = *(s8 *)((u8 *)(*(void **)((u8 *)arg0 + 0x1A148)) + 0x944);
    if (value < 0) {
        return 0;
    }
    func_80055A74(value);
    return func_80055BA8();
}
```
Observed `bgez` skips the `return 0` block → negative-guard polarity (§4 guard/return row). The pointer-chain field load matches accepted `func_813022D8` exactly (+0x1A148 → +0x944). `func_80055A74` is `s32 (s32)` (solved in `517E0.c`); `func_80055BA8` (still pragma) must be declared `s32 func_80055BA8(void)` and its value returned (the `$v0` on the taken path is the callee's result, matching the §5 `func_80055BA8` return-type case).

### func_813002D0 — guard-lookup with two return tails (batch3)

```c
s32 func_813002D0(void *arg0) {
    u8 *base = (u8 *)arg0 + 0x18000;
    s8 idx = *(s8 *)(base + 0x2142);
    s8 value = *(s8 *)(*(void **)(base + 0x2148) + idx + 0x900);
    if (value < 4 && value >= 0) {
        return value;
    }
    return 0;
}
```
Observed tests order `slti 4`/`beqz` then `bltz` → check `< 4` before `>= 0`. TWO `jr ra` tails (guard-return shape, not assign-then-return — the 0.47 raw on prior 11 attempts is the operand order). Same `0x18000` base + `0x2148` chain as solved `func_81300314` (there with `>= -1` bound); note `lw 0x2148` loads before `lb 0x2142`.

### func_81301030 — call chain with reused sub pointer (batch3)

```c
void func_81301030(void *arg0) {
    void *sp20 = (u8 *)arg0 + 0xF630;
    func_8130015C(arg0, 1);
    func_81300350();
    *(s32 *)((u8 *)arg0 + 0x1A168) = 0;
    func_81304C3C(sp20, arg0, func_813002D0(arg0));
    func_81304C58(sp20, (u8 *)arg0 + 0x1A15C);
    *(s32 *)((u8 *)arg0 + 0x1A138) = 0;
}
```
`s0+0xF630` computed once, passed as `a0`, spilled to 0x20, reloaded for both `func_81304C3C` and `func_81304C58` → explicit `sp20` local. `func_813002D0`'s result feeds `a2` of `func_81304C3C`. Final store `0x1A138 = 0` after call 5.

## General notes

- The object pointer family: solved bodies use `s32 arg0` (`func_81300BA0`, `func_81301CE4/1D28/1DD8/1E14/1E80/1EC4/1F08`) or `void *` (`func_813000E4`, `func_813014D0`, `func_813022D8`); both accepted. Offsets recur: `+0x74`, `+0xD18`, `+0xDA8`, `+0xF630`/`+0xF64C`, `+0x15370`, `+0x1A138`–`+0x1A16C`, `+0x18000` base with `+0x2142`/`+0x2148` pointers.
- `func_813022D8(void *)` returns `value >= 0` for the same `+0x1A148`/`+0x944` chain — shape template for `func_81302290`.
- Remaining unanalysed owners (fresh, probed 0x): `func_8130125C` (25, `beql` tail — see §5 branch-likely warning), `func_813013C0`/`func_81301448` (34, twin chains), `func_813022F4` (39, 5 calls incl. `func_8160A270`/`func_8160A384`/`func_80055028`), `func_813011B8` (41), `func_81300F7C` (45), `func_8130183C` (48), `func_8130176C` (52), `func_8130015C` (58 — the file's own dispatcher-ish helper, called by 5+ owners), plus 4 big `call_sequence` owners (66-198 instr).
## Fleet box 2026-08-29 (2026-08-29)

- Accepted func_81302290 with label `call-sequence:sign-guard:raw-pointer-chain:local-prototype`; the s8 sign guard and raw context-pointer chain matched. Probe and gate both reported link_verified:true; the full COMPARE=1 gate accepted it.
- Accepted func_8130150C with label `call-sequence:twin:raw-s32-temp:companion-prototype`; it matched the neighboring 014D0 twin. The transaction added the early same-file prototype `extern void func_8130015C(void *, s32);` before 014D0 to avoid the implicit-declaration collision. Probe and gate reported link_verified:true; the full COMPARE=1 gate accepted it.
- Accepted func_8130125C with label `call-sequence:branch-likely:s8-return:s32-arg`; the branch-likely valid-state polarity matched. Probe and gate reported link_verified:true; the full COMPARE=1 gate accepted it.
- Deferred func_813002D0: best 0.8824 normalized / 0.4118 raw, operand_or_scheduling_drift; repeated register/operand allocation drift. Deferred func_81301030: best 0.9091 / 0.7273 with frame -0x28 versus expected -0x30. Deferred func_813013C0 and func_81301448: best 0.9143 / 0.7429 with frame -0x28 versus expected -0x30. Deferred func_813011B8: best 0.7317 / 0.3902 with frame -0x40 versus expected -0x30. Deferred func_81300F7C after 25 attempts: best 0.9348 / 0.7174, still operand_or_scheduling_drift with extra saved-register/frame layout; no gate attempted. Jump-table and user-specified skip owners remain deferred.

## Fleet box correction (2026-08-29)

- Runner target summary after this box reports func_81300F7C at 30 prior attempts, best 0.9348 normalized / 0.7174 raw; the earlier note saying 25 attempts referred to the pre-batch count. The deferred diagnosis is unchanged.
