# Region notes -- disasm/src/fragments/83/fragment83_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Unsolved shape: incoming-argument stack-home spill (AGENTS.md §5) (2026-08-28)

An incoming-argument stack-home spill (`sw a0, N(sp)` with no intervening call) that no C spelling reproduces -- one of the common dead ends in fragment work (`func_82C02664`). Drop an owner as soon as its first diff is this.

## Accepted and deferred owners (2026-08-29) (2026-08-29)

Accepted in the 2026-08-29 box:

- `func_82C03FB4`: label `call-chain:hal-strcpy:raw-s32-or`; direct `HAL_Strcpy` calls with raw s32 offsets and the 0x200/type-5 conditional.
- `func_82C02390`: label `state-field:scale:tie:reverse-add`; s8 factor, raw s16 offsets, and reverse add operand order. Exact linked/probe match.
- `func_82C02A44`: label `state-field:flags:raw-offsets:direct-decrement`; raw byte offsets, direct decrement/increment, and early return. Exact linked/probe match.

Deferred:

- `func_82C0359C`: final best .963 normalized/.8704 raw `operand_or_scheduling` drift; all 12 attempts omitted the expected result-mask scheduling.
- `func_82C0298C`: two batches ended in normalized 1.0/raw .9783 register-allocation tie; stop per `FLEET_AGENT.md`.
- `func_82C00804`: best .9348 normalized/.8261 raw instruction drift from missing incoming argument stack-home spills; companion edit was rejected because the owner is still `GLOBAL_ASM`.
- `func_82C02664`: existing incoming-argument stack-home spill dead end; skip.
- `func_82C03F40`: existing register-allocation tie; skip.
- `func_82C04880`: known runner `probe_unavailable`/list-index diagnostics defect; skip.
- `func_82C047C4` and larger/dispatcher owners: deferred for a later box.

## 2026-09-08

func_82C02664: matched (constant-map:bit-test:base-temp:post-index), 3 iterations, agent codex

## 2026-09-08

func_82C03F40: plateau at 0.9655 (raw 0.8966), mismatch instruction_drift; tried families: call-chain; tie-pool yes

## 2026-09-08

func_82C04880: matched (call-chain:guard-return:void-pointer-s32), 1 iterations, agent codex

## 2026-09-08

func_82C0359C: plateau at 0.0 (raw None), mismatch unknown; tried families: call-chain; tie-pool no

## 2026-09-08

func_82C03DC0: plateau at 0.9861 (raw 0.8056), mismatch instruction_drift; tried families: call-chain; tie-pool no
