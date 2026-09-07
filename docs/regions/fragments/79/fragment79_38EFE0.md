# Region notes -- disasm/src/fragments/79/fragment79_38EFE0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: dual-global notify chain (AGENTS.md §4) (2026-08-28)

`func_8411EF08((u8 *) D_84191208)` -- an `s32`-typed global holding a pointer bit pattern, passed straight through, then the second global. Evidence: 2 (`func_84120A50`, `func_84120CA4`). Limit: only where the global is `s32`-typed but dereferenced.

## Requeue: func_841204BC call-live float scheduling (2026-08-30)

requeue. 90 recorded attempts in this box: 84 probe_rejected and 6 compile_failed; 0 probe matches, 0 gates, 0 accepts. Best normalized: permute:top-3 at 0.9048 normalized / 0.3810 raw, exact 336-byte size, operand_or_scheduling_drift, fingerprint ["operand_or_scheduling_drift",3,0,"0x27bdffa8","0x27bdffa0"] (expected frame -88, actual -96). Best raw: call-sequence:typed-state:f32 pad[2];:direct-y at 0.8333 normalized / 0.5476 raw, exact 336-byte size, first diff instruction 13 / fingerprint ["operand_or_scheduling_drift",55,13,"0xe7b20054","0xe7b20040"] (expected spill sp+0x54, actual sp+0x40). Strong structural finding: sp+0x40 and sp+0x44 are the y/z fields of the 12-byte local vector rooted at sp+0x3C, not separate locals. A correct-frame 332-byte overlap-vector spelling (call-sequence:overlap-vec:temp-z-first, 0.8690 / 0.5238) reloads both call-live floats immediately; target reloads the 0x610 float immediately but delays the 0x608 float until table math. Tried m2c raw forms, u16/s16 ABI variants, typed vector/state overlays, overlap folding, table/store order, declaration order, frame/slot padding, packed locals, live-range copies, volatile saved-current/saved-both forms, and one completed 300-second permuter pass (best permuter score 1570, no zero); a second permuter was terminated at box end before producing output. Next materially different hypothesis: start from the persisted exact-size best-raw typed-state:direct-y candidate and use explicit PERM_GENERAL/PERM_LINESWAP choices around temporary extraction and the two output expressions to target the sp+0x54/sp+0x50 live ranges; do not repeat broad pad/declaration-order batches.

## Requeue: func_84123034 float scheduler (2026-09-01) (2026-09-01)

requeue. Wave 27 probe-only work on func_84123034 (float_math), 21 candidate variants, 0 probe matches/gates/accepts. All candidates had exact 284-byte owner size and normal return tail. Initial raw-offset/base/index/pointer/overlay spellings reached normalized 0.8592 (raw 0.6761-0.7042), operand_or_scheduling_drift at expected field load 0x5EC versus actual 0x5F0 (instruction 18). Reordering the independent multiply sequence to D,F,A,B,C before the additions improved to normalized 0.9577/raw 0.7746. Best observed spelling was a typed local overlay covering fields 0x24, 0x2C and 0x5E4..0x5F8, with additions written as A+D and B+E (label float_math:overlay:target-operands): normalized 0.9577/raw 0.8732, exact size, with first remaining mismatch at instruction 54 (expected load field 0x5F8, actual load field 0x24) in the final position update; a repeat of a nearby overlay spelling measured raw 0.8169, so preserve as hypothesis rather than proof. Other swap-D/E raw best 0.8310. Explicit four-local temporary variants regressed to normalized 0.507/raw 0.169 due FPU register pressure. No source edits. Next action: resume from typed-overlay target-operands spelling, then vary only the final position-update expression/field overlay and FPU declaration/register lifetime; do not replay broad raw-offset batches.

## Requeue: func_84122DD8 call-sequence (2026-09-02) (2026-09-02)

requeue. Two probe-only batches (16 candidates) on func_84122DD8, prior fresh attempt was 1 before this box; 0 matches/gates/accepts. Best current normalized 0.7105 / raw 0.3421, expected 152 bytes/38 instructions vs actual 148/37, mismatch_kind instruction_drift, first-diff fingerprint ["instruction_drift",8,2,"0xc4840028","0xafb00018"] (target lwc1 arg0+0x28; candidates saved s0 at sp+0x18). Attempted families: clamp guard-return, comparison reversal, explicit difference temp, inverted guard, pointer alias, literal cast, typed live-current/load-order variants. Target keeps a0 in stack slot across func_841204BC and schedules current load before base load; next action: materially different ABI/lifetime spelling that forces stack preservation (possibly explicit saved pointer/local aggregate), then vary FPU declaration order to reproduce target registers and delay the second base reload. No futility verdict.

## Accepted: func_84121130 permuter zero-score register tie (2026-09-02) (2026-09-02)

Accepted. Nine distinct probe candidates all compiled; seven exact-size variants remained normalized 1.0000/raw 0.6410 register_allocation_only with stable first-diff fingerprint at offset 22: expected mtc1 $at,4096, actual mtc1 $at,24576; two variants drifted scheduling/size. Repaired permuter on the strongest exact-size body: base score 95, best score 0. Zero-score body inlined both threshold comparisons while retaining the initial d local and call. Runner replay was link_verified=true and combined full-ROM gate passed (build/pokestadiumgs-us.z64: OK), installed as accepted. Futility then reported register-tie: 7 prior attempts at >=0.99; no further work needed.

## 2026-09-07

func_8412142C: plateau at 0.9189 (raw 0.5946), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-07

func_84122DD8: matched (call_sequence:clamp:direct-offset-match), 1 iterations, agent codex

## 2026-09-07

func_84123858: time cap at 0.9787 (raw 0.8936) after 2409s, mismatch operand_or_scheduling_drift; tried families: call-sequence; tie-pool no

## 2026-09-07

func_8412060C: matched (constant_map:oldstyle:counter-mask-ptr-do), 7 iterations, agent codex

## 2026-09-07

TYPE CONFLICT: func_8410B104 is extern void func_8410B104(void), not extern void func_8410B104()

## 2026-09-07

func_84123E74: plateau at 0.9333 (raw 0.2667), mismatch operand_or_scheduling_drift; tried families: state_field_access; tie-pool yes

## 2026-09-07

func_84122A78: time cap at 0.9375 (raw 0.9375) after 2416s, mismatch instruction_drift; tried families: state_field_access; tie-pool yes
