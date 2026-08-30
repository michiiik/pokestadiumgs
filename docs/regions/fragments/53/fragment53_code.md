# Region notes -- disasm/src/fragments/53/fragment53_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-30 fleet box (2026-08-30)

Accepted:

- `func_86509D8C`: call-chain state-dispatch raw-offset switch using direct `s32` raw offsets. Probe matched with `link_verified=true` and the full ROM gate accepted in commit `0fb17c05`. The required forward declaration was `extern s32 func_87F02104(void);`. `StageContext_SetClearColor` remains intentionally implicit because this file already used it before the owner; adding a later `void` prototype caused a strict same-file redeclaration failure.

Requeue:

- `func_86508B20`: runner repeated-drift futility after 13 prior rejected attempts sharing the prologue fingerprint `["section_layout_drift",13,3,"0xafb40028","0xafb00018"]` (expected `sw $s4,40(sp)`, actual `sw $s0,24(sp)`). Best candidate was `call-chain:record-loop:direct-conditions:no-final-return` with normalized similarity `0.9853` and raw similarity `0.8824`, expected 67 instructions/268 bytes versus actual 68/272, `mismatch_kind=section_layout_drift`, first diff offset 47 instruction 11 (expected branch `0x1000002f` / `b 0xec`, actual `0x10000030` / `b 0xf0`). Other close candidates reached 0.9286 normalized/0.8143 raw with the same size drift. Attempted families: m2c raw-pointer loop with explicit ABI declarations, direct selector conditions with no final return, `s32`/`u32` return widths, `var_s2` pointer-step variants, `D_8650DB70` pointer/global forms, pointer declaration order, do/while versus while, explicit endpoint local, five-pointer/live-constant forms, and a 45-second runner permuter (best score 490/1055, no exact source). Initial compile failures were context preflight only: missing `D_8650C494` and treating the value-producing `func_8003F114` as void; corrected declarations produced the near-hit. Next materially different hypothesis: reconstruct the original nested outer-control-flow/selector temporary layout and explicitly model the saved `$s4` lifetime (including endpoint/constant reuse) rather than trying more pointer declaration permutations; verify `func_8003F114`'s return ABI from its eventual definition before using its result.

Box totals: 1 accepted owner, 1 requeued owner, 1 full-ROM acceptance, 27 probe candidates attempted after preflight correction plus 45 seconds of permuter exploration; no register-tie futility.
