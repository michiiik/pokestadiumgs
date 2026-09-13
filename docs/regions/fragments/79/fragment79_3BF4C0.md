# Region notes -- disasm/src/fragments/79/fragment79_3BF4C0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Verified spelling: wrapper called with four registers but only three read (AGENTS.md §4) (2026-08-28)

Declare only the parameters the body reads (`a3` was caller garbage); the fourth formal changes the frame. Evidence: 1 (`func_841518D0`).

## Unsolved shape: table pointer kept in $t7 (AGENTS.md §5) (2026-08-28)

`u8 *p = arg0 + 4; p[arg1 + 8] = 0xFF; p[0] |= 2;` -- IDO keeps the table pointer in `$t7`; no declaration-order/pointer-form variant reproduced it (`func_841523BC`, `func_84151CD8`, likely `func_84151DD4`). Needs a dedicated variant family.

## 2026-09-06

func_84151D3C: matched (call_sequence:guard:u8-value:callee-table-temp), 2 iterations, agent codex

## 2026-09-06

func_841526CC: plateau at 0.9231 (raw 0.8974), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-06

func_84152C34: plateau at 0.9286 (raw 0.4048), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-09

func_841502D0: plateau at 0.9583 (raw 0.9583), mismatch instruction_drift; tried families: call_sequence; tie-pool no

## 2026-09-09

func_84150268: time cap at 0.9615 (raw 0.8462) after 2407s, mismatch instruction_drift; tried families: call_sequence; tie-pool no

## 2026-09-09

func_84151420: matched (call_sequence:guard:integer-base), 2 iterations, agent codex

## 2026-09-09

func_84150330: plateau at 0.9688 (raw 0.8438), mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-13

func_84152088: time cap at 0.9362 (raw 0.4468) after 2400s, mismatch operand_or_scheduling_drift; tried families: call_sequence; tie-pool no

## 2026-09-13

func_84151838: matched (call_sequence:table-update:entry-table-amount-decl-order), 1 iterations, agent codex

## 2026-09-13

func_84151A5C: plateau at 0.925 (raw 0.6), mismatch instruction_drift; tried families: call_sequence; tie-pool no
