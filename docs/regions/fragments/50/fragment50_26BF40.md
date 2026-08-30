# Region notes -- disasm/src/fragments/50/fragment50_26BF40.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Requeue: func_862055F0 selector transform register tie (2026-08-30)

`requeue func_862055F0`: 21 runner attempts (4 declaration-preflight compile failures, 17 compiling probes), 0 probe matches, 0 link-verified results, 0 gates, and 0 accepts. Best label `permute:state-field:z-before-y-temp` emitted the exact 308-byte size and reached normalized similarity 1.0000 / raw similarity 0.7403 with `register_allocation_only`; runner `futility` and `repeated_drift` were both unset. Fingerprint: `["register_allocation_only",78,19,"0x44811000","0x44816000"]`; first difference at instruction 19 / runner offset 78, expected `op/0x11 $at, $a0, 4096`, actual `op/0x11 $at, $a0, 24576` (the disassembler's FPU-register rendering). Attempted families: raw `u8 *` versus `s32` selector, switch versus if-chain, argument-register reuse, explicit `&D_8620E198` lifetime, pointer/index and reversed-add forms, pointer-increment entry formation, typed target/state overlays, typed 12-byte vector records in a 64-byte bank, float temporary declaration/order variants, and two 120-second permuter runs. The first permuter improved score 605 to 130 by computing Z before storing Y; the second timed out at score 130 with no output.

Best exact-size source spelling:

```c
void func_862055F0(u8 *arg0, s32 arg1, s32 arg2) {
    f32 z;
    f32 scale;
    u8 *entry;
    u8 *bank;
    s32 *global = &D_8620E198;

    arg1 = *(0x73BD2 + (((u8 *)(u32)*global) + (arg1 * 0x18)));
    bank = D_86208F28 + (arg2 << 6);
    entry = bank;
    entry += arg1 * 0xC;
    *(f32 *)(arg0 + 0x48) = *(f32 *)bank - ((*(f32 *)(entry + 0xC) * 18.0f) * (5.0f * *(f32 *)((u8 *)(u32)*global + 0xD8)) * *(f32 *)((u8 *)(u32)*global + 0xCC));
    z = *(f32 *)(bank + 8) - ((*(f32 *)(entry + 0x14) * 18.0f) * (5.0f * *(f32 *)((u8 *)(u32)*global + 0xD8)) * *(f32 *)((u8 *)(u32)*global + 0xCC));
    *(f32 *)(arg0 + 0x4C) = 30.0f;
    *(f32 *)(arg0 + 0x50) = z;
    scale = *(f32 *)((u8 *)(u32)*global + 0xD8) * D_8620E100;
    *(f32 *)(arg0 + 0x5C) = scale;
    *(f32 *)(arg0 + 0x58) = scale;
    *(f32 *)(arg0 + 0x54) = scale;
    switch (arg1) {
        case 0: *(s16 *)(arg0 + 0x44) = -0x6000; return;
        case 1: *(s16 *)(arg0 + 0x44) = 0x6000; return;
        case 2: *(s16 *)(arg0 + 0x44) = -0x2000; return;
        case 3: *(s16 *)(arg0 + 0x44) = 0x2000; return;
    }
}
```

Required declarations are `extern u8 D_86208F28[];`, `extern f32 D_8620E100;`, and the existing `extern s32 D_8620E198;`. Next action: resume this owner before any caller, using the best spelling as a register-tie/permuter base with a longer or macro-guided permutation budget; do not repeat the exhausted raw-pointer, add-order, typed-overlay, or ordinary float-temp families. Only after a link-verified full-ROM acceptance should its exact signature/body be transferred to `func_86205B8C`, `func_86205C8C`, `func_86205D98`, and `func_86206334`. `func_86205D98` is a jump-table dispatcher with `jtbl_8620E104`, so it additionally requires coordinator-owned rodata/layout work and was not probed in this lane.
