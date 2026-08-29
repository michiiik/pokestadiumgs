# Region notes -- disasm/src/fragments/76/fragment76_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-29 fleet wave (2026-08-29)

- Accepted and installed only after linked probe plus full ROM gate (no DECOMP_PROVENANCE_SKIP):
  - func_8F7007B8: 7 runner attempts total (6 probe candidates, 1 gate); accepted label call-chain:inline-array:m2c; gate reported link_verified=true, combined make -C disasm COMPARE=1 passed, install_compiles=1. Final spelling uses direct (D_8F7023B4 * 0x30) + D_8F701358 base expression and the existing void/u8 callee signatures.
  - func_8F700858: 11 attempts total (10 probe candidates, 1 gate); accepted label predicate:direct-flag-expression:shared-return; gate reported link_verified=true, combined full-ROM gate passed, install_compiles=1. Final spelling uses repeated raw u16 flag expressions, s16 D_8F7023BC, the second flag chain inside <= 0, and one shared return 0.
  - func_8F70107C: 16 attempts total (15 probe candidates, 1 gate); accepted label dispatch:goto-labels:reverse-blocks; gate reported link_verified=true, combined full-ROM gate passed, install_compiles=1. Final spelling uses explicit goto labels in reverse call-block order to reproduce the direct branch chain.
- Deferred after probe-only work; no source changes installed:
  - func_8F700B78: 18 attempts, 17 operand_or_scheduling_drift and 1 instruction_drift; strongest normalized similarity 0.9221, raw 0.4026 (six-byte-local/subscript-base). Frame/stack/register scheduling remains wrong; do not repeat without a new declaration/source shape.
  - func_8F700DC8: 5 attempts, all operand_or_scheduling_drift; strongest normalized 0.8533, raw 0.2400 (var-before-guard/do-loop). Initial D_8F7023B4/pointer register allocation and frame scheduling remain wrong.
  - func_8F700420: 15 recorded attempts (14 hand probes plus one permuter run); 13 operand_or_scheduling_drift, 1 instruction_drift, 1 register_allocation_only. Strongest normalized 1.0000, raw 0.8714; permuter timed out without a zero, so stop as a register tie.
- Existing deferred owners not repeated: func_8F700538 (48 prior, best 0.8571 normalized/0.5714 raw, operand_or_scheduling_drift, stuck), func_8F700EF4 (15 prior, best 0.9048/0.3810, operand_or_scheduling_drift), func_8F700A54 (15 prior, best 0.9200/0.4933, operand_or_scheduling_drift), and func_8F700CA4 (2 prior, best 0.8219/0.2466, operand_or_scheduling_drift).
- Explicitly skipped jump-table/dispatcher owners because no rodata subsegment is prepared: func_8F7005D8, func_8F7006F0, func_8F700624, func_8F700028.
- Remaining owners are deferred for a later wave; no candidate source edits were made for them.
