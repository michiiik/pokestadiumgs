# Region notes -- disasm/src/fragments/22/fragment22_14B090.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Requeue func_82700EFC after 60-minute box (2026-08-30)

No accepted spelling or gate evidence. The strongest probe-only candidate is a 168-byte, 42-instruction body using a 12-byte `s16 local[6]`, plain `s32` globals with byte-offset casts, and a late volatile reload of the `arg0 + 2` index. It reached normalized similarity `0.9762` and raw similarity `0.5952`, but was rejected as `instruction_drift`.

The stable first-difference fingerprint is `["instruction_drift",4,1,"0x3c0e0000","0xafa50014"]`: the baseline forms `lui t6, %hi(D_82703280)` before homing `a1` at `0x14(sp)`, while the probe emits the home store first and forms the global base in `a1`. The remaining operation sequence is size-correct; later differences are register allocation (`t3`/`v0`, scratch-copy `t7`/`t6`, and table temporaries). The runner recorded repeated-drift futility after more than 90 attempts. No source installation or ROM gate was performed because no candidate reported `link_verified: true`.

Attempted hypothesis families: raw and volatile array spellings; global declaration widths and volatility; `u8`, `s16`, `u16`, pointer, and old-style formal types; index temporaries, declaration order, volatile rereads, and late index assignment; pointer aliases and reduced local storage; local structs, unions, and aggregate-copy forms; and two bounded decomp-permuter passes. The aggregate initializer did not compile under IDO, and pointer aliases that moved the global `lui` ahead of the home store expanded the frame to `0x18`.

Next action: requeue this owner with a materially different compiler-shape hypothesis that preserves the `0x10` frame while forcing the global-base temporary into `t6` before the incoming-argument home store. Do not spend an ordinary retry on the repeated direct-array/index spellings.

## Terminal skips for this handoff

Skip ordinary retries of `func_82700EC8`, `func_82700E38`, `func_82700FA4`, `func_82700FF0`, `func_82700DD0`, `func_82701278`, `func_8270188C`, `func_827010F0`, `func_82702220`, `func_82702810`, and `func_82701DF4` (exhausted, tie, or stuck). Keep `func_82702658` and `func_82701978` deferred until their required per-file `.rodata` subsegments are added; do not change YAML as part of ordinary owner work.
