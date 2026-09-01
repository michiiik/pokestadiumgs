# Region notes -- disasm/src/fragments/53/fragment53_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-30 fleet box (2026-08-30)

Accepted:

- `func_86509D8C`: call-chain state-dispatch raw-offset switch using direct `s32` raw offsets. Probe matched with `link_verified=true` and the full ROM gate accepted in commit `0fb17c05`. The required forward declaration was `extern s32 func_87F02104(void);`. `StageContext_SetClearColor` remains intentionally implicit because this file already used it before the owner; adding a later `void` prototype caused a strict same-file redeclaration failure.

Requeue:

- `func_86508B20`: runner repeated-drift futility after 13 prior rejected attempts sharing the prologue fingerprint `["section_layout_drift",13,3,"0xafb40028","0xafb00018"]` (expected `sw $s4,40(sp)`, actual `sw $s0,24(sp)`). Best candidate was `call-chain:record-loop:direct-conditions:no-final-return` with normalized similarity `0.9853` and raw similarity `0.8824`, expected 67 instructions/268 bytes versus actual 68/272, `mismatch_kind=section_layout_drift`, first diff offset 47 instruction 11 (expected branch `0x1000002f` / `b 0xec`, actual `0x10000030` / `b 0xf0`). Other close candidates reached 0.9286 normalized/0.8143 raw with the same size drift. Attempted families: m2c raw-pointer loop with explicit ABI declarations, direct selector conditions with no final return, `s32`/`u32` return widths, `var_s2` pointer-step variants, `D_8650DB70` pointer/global forms, pointer declaration order, do/while versus while, explicit endpoint local, five-pointer/live-constant forms, and a 45-second runner permuter (best score 490/1055, no exact source). Initial compile failures were context preflight only: missing `D_8650C494` and treating the value-producing `func_8003F114` as void; corrected declarations produced the near-hit. Next materially different hypothesis: reconstruct the original nested outer-control-flow/selector temporary layout and explicitly model the saved `$s4` lifetime (including endpoint/constant reuse) rather than trying more pointer declaration permutations; verify `func_8003F114`'s return ABI from its eventual definition before using its result.

Box totals: 1 accepted owner, 1 requeued owner, 1 full-ROM acceptance, 27 probe candidates attempted after preflight correction plus 45 seconds of permuter exploration; no register-tie futility.

## 2026-08-30 fleet box (continued) (2026-08-30)

Accepted:

- None. No candidate reached link_verified=true, so no full-ROM gate was run and no source pragma was installed.

Requeue:

- `func_86502524`: 78 recorded attempts (54 compiled probes rejected, 24 compile-preflight failures). The best spelling is the global-readback form:

```c
D_8650C498 = D_8650C474 + 0x5C;
D_8650C4B4 = (D_8650C498 - D_8650C4CC) - 0xA;
D_8650D9D4 = (s32)(((sqrtf((f32)((f64)(D_8650C4AC - D_8650C498) / D_8650D6B0)) / D_8650C4B8) + 1.0f) - 2.0f);
func_865020D8();
```

  followed by direct scalar assignments from `D_8650C4F4` to the 12 tail globals in descending address order within each group. It reached normalized/raw similarity `0.9254/0.9254`, `mismatch_kind=instruction_drift`, first diff offset `180`; the candidate is 268 bytes/67 instructions versus 252/63 expected. The prologue and first tail store match; the remaining drift is the four extra address-load instructions needed for the three contiguous float-store groups.

  Attempted materially different families: corrected direct scalar/global-readback forms, explicit integer and float temporaries, pointer and volatile-pointer forms, contiguous arrays, raw offset groups, chained/comma assignments, declaration-order variants, raw symbol-base casts, and a 90-second permuter run. The initial compile failures were preflight-only missing declarations, including `D_8650C4B8`; corrected probes produced the result above.

  Next action: inspect or reconstruct an existing source-level record/alias declaration that makes IDO reuse the address base for each contiguous three-float group while retaining the direct relocation shape. Do not repeat scalar, array, pointer, or declaration-order permutations without new evidence.

- `func_865038A8` remains the coordinator-specified requeue: 34 prior attempts, normalized `1.0` / raw `0.9444`, immediate drift.
- `func_86508B20` remains the existing requeue: best normalized/raw `0.9853/0.8824`, section-layout drift; next hypothesis is the saved `$s4` lifetime and nested control-flow shape recorded above.

Prerequisite skips preserved:

- Jump-table-unready: `func_86501EA0`, `func_86501FA0`, `func_865082C8`, `func_8650515C`. These require the per-file `.rodata` subsegment before switch candidates.

Untouched owners:

- `func_865046A8`, `func_86508780`, `func_86501D6C`, `func_8650863C`, `func_8650455C`, `func_86509318`, `func_8650A278`, `func_86508890`, `func_86500D5C`, `func_86508484`, `func_86502B88`, `func_8650A3E4`, `func_8650A074`, `func_86509E54`, `func_86502958`, `func_86502720`, `func_86503938`, `func_86504EB0`, `func_86500020`, `func_86500EF8`, `func_86506B2C`, `func_86502D80`, `func_86500354`, `func_865020D8`, `func_865040E4`, `func_865059A0`, `func_86503B98`, `func_86500780`, `func_86505EA8`, `func_865064B0`, `func_86508C2C`, `func_86503178`, `func_86504740`, `func_86507AFC`, `func_8650952C`, `func_86501280`, and `func_86506E78`.

Box result: 0 accepted owners, 1 durable requeue, 78 recorded attempts for the active owner, and no source-file changes. Foreign generated `COVERAGE.md` dirt was preserved.

## 2026-08-31 fleet box requeue (2026-08-31)

requeue func_86508B20: six new candidates; no link_verified hit or ROM gate. Best remains normalized/raw 0.9853/0.8824 with operand_or_scheduling_drift: expected sw $s4,40(sp), actual sw $s0,24(sp). Next action is to reconstruct selector lifetime and loop endpoint reuse to force the saved $s4 allocation; do not repeat pointer-declaration permutations.

## 2026-08-31 successor box requeue (2026-08-31)

requeue func_86508B20: seven new selector-lifetime variants across two batches; no link_verified candidate or ROM gate. Best remains normalized/raw 0.9853/0.8824 with expected sw $s4,40(sp) versus actual sw $s0,24(sp). The runner reported repeated-drift advisory, not register-tie futility. Next action is to reconstruct the original nested control flow and compiler temporary structure that keeps selector 1 live through the initial branch while separately reusing $s4 for the endpoint; avoid more direct scalar/pointer declaration permutations.

## 2026-08-31 third successor box requeue (2026-08-31)

requeue func_86508B20: four additional nested selector-lifetime/control-flow variants; no link_verified candidate or ROM gate. Best regressed to normalized/raw 0.8971/0.6912; expected sw $s4,40(sp), actual sw $s0,24(sp). One initial batch had declaration preflight failures and was rerun with corrected declarations. Next action is deeper reconstruction of compiler temporary/register lifetime; avoid direct pointer/scalar permutations.

## Wave 7 handoff (2026-08-31)

## Wave 15 retry handoff (2026-08-31)

requeue: `func_86501D6C` (77 instructions; first selected at 0 attempts) was rerun after the isolated-worktree venv/oracle bootstrap repair. The three float-loop variants were all rejected: best `float-loop:locals-before-globals:explicit` scored 0.5126 normalized / 0.1345 raw, expected 308 bytes but actual 476. Its first difference is offset 1, expected `lui $a3, 0x0000`, actual `lui $t0, 0x0000`; the other variants show the same early global-load/register-lifetime failure. Keep this owner requeued, but change family: recover the real global declaration/load order from the assembly before attempting another loop spelling. No link-verified hit or ROM gate.

Wave 7 handoff: func_86508780 remains unresolved after 9 serial CC_CHECK=1 probes. Best normalized/raw similarity was 0.8824/0.5588; no link_verified candidate or ROM gate. The durable operand_or_scheduling_drift fingerprint at offset 41 is expected sw $s0,24(sp) versus actual sw $ra,20(sp). Next action is to reconstruct the compiler temporary/register lifetime that creates the expected saved $s0 spill; preserve the existing file requeue skip list.

## Wave 25 handoff (2026-09-01)

layout-prerequisite/requeue: `func_86501FA0` selected fresh (0 prior), but file notes identify it as jump-table-unready because it calls `func_86501EA0`; no candidate link-verified. Eight candidates (after 3 initial body-format compile failures) reached best normalized/raw `0.9231/0.5769`, operand_or_scheduling_drift, expected 312 bytes/78 instructions vs actual 308/77 for hoisted-f64; 312-byte forms first differed at offset 137 (`lui $t3/$at` expected vs `lui $t4` actual). Tried direct global float formula, explicit f64 temporaries, operation order, and hoisted globals. Next: prepare/gate per-file `.rodata` subsegment for `func_86501EA0`, then reconstruct exact double constant/global declaration order. No source edit or ROM gate.

## 2026-09-02 worker box (2026-09-02)

requeue func_86501D6C: two probe-only batches of 8 distinct candidates each, host CC checks enabled; no link_verified hit and no full-ROM gate. Batch 1 attempted raw/typed state overlays, explicit f64/f32 temporaries, product hoisting, split guards, compare polarity, while/do/for loop forms, and declaration/order variants. Best normalized/raw 0.5000/0.2069 (state:raw:compare-order), expected 308 bytes vs actual 464, mismatch_kind=operand_or_scheduling_drift, first-diff fingerprint [operand_or_scheduling_drift,1,0,0x3c078651,lui $t1,0x0000] (expected lui $a3,0x0000). Batch 2 attempted explicit counter/global address pointers, volatile counter, counter-first lifetime, raw-offset accesses, loop-base temporary, do-loop, and nested guards. Best normalized/raw 0.3623/0.1232 (state:address:loop-base), expected 308 bytes vs actual 552, same offset-1 fingerprint class (expected lui $a3, actual lui $t1). No register-tie futility. Next materially different action: reconstruct the exact IDO source declaration/global-load scheduling from a matching accepted floating-point loop, especially preserve D_8650C4D4 address in $a3 while loading D_8650C498/D_8650C4CC and retain the assembly\x27s interleaved mul.d/cvt sequence; avoid more pointer lifetime or algebraic loop permutations until that ABI/declaration model is established.

## 2026-09-02 fleet box func_8650455C (2026-09-02)

requeue: func_8650455C is a fresh 83-instruction non-jump-table call_sequence owner. Prepared 8 distinct complete-function candidates in /private/tmp/gs49_func_8650455C_batch.json; no runner invoked per box instruction, so no probe score, normalized/raw similarity, mismatch kind, or first-diff fingerprint exists yet. Assembly fingerprint/source shape: 0x20 frame; void func(s32, void *), reads arg1+0x14; requires arg0 == 2 and D_8650C5EC == 1; when D_8650C494 == 0 increments D_86511698[index*0x38+0x58], wraps at 0x18, then calls func_865040E4(index); writes D_8650DBA8 and D_8650F7C8 at index*0x38 using D_8650C49C[index], with -5/+0x3C adjustment when D_8650C5E8 == -2. Attempted hypotheses in batch: raw-record guard/assign, early guards, typed explicit index, array-index increment-first, raw-offset branch-preserving, temporary float values, post-call offset locals, and explicit casts/literal widths. Next action: run the batch through the fleet probe in a controlled runner transaction, inspect per-candidate diagnostics and link verification, then change only the indicated ABI/declaration/order hypothesis.

## Wave 49 coordinator replay (2026-09-02)

requeue; 8 fresh call-sequence candidates compared with no link verification. Best call-sequence:typed-record:explicit-index reached similarity 0.7470 raw 0.3614, expected 332 bytes versus actual 284, with early branch drift at instruction 8: expected beq ,,76, actual addiu ,,2. Tried raw-record, typed-record, array-index, raw-offset, raw-global, and explicit-cast forms. Next action: recover the target guard and stack frame before refining record fields.
