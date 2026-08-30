# Region notes -- disasm/src/fragments/44/fragment44_20F140.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-31 fleet box requeue (2026-08-31)

requeue func_8AF221C4: ten candidates across raw-pointer, pointer-variable, direct-offset, local, and struct-overlay forms; no link_verified hit or ROM gate. Best similarity was 0.8400, raw 0.3800, operand_or_scheduling_drift; first diff offset 13 expected lui $a3 versus actual lui $a2. Next action is to reproduce the compiler global-address register allocation with the m2c void-pointer record-field form, then vary declaration/order and branch spelling. This is not a field-width mismatch.

## 2026-08-31 successor box requeue (2026-08-31)

requeue func_8AF221C4: seven candidates across two batches; no link_verified candidate or ROM gate. Best was normalized/raw 0.74/0.34 with operand/scheduling drift at offset 13, expected lui $a3 versus actual lui $a2. The m2c void-pointer arithmetic forms failed IDO compilation. Next action is an IDO-valid typed byte-pointer field form that preserves the observed global-load ordering.

## 2026-08-31 third successor box requeue (2026-08-31)

requeue func_8AF221C4: five typed IDO-valid variants; no link_verified candidate or ROM gate. Best normalized/raw 0.66/0.34 with persistent $a3 versus $a2 scheduling drift. Next action is to preserve typed record fields while forcing the D_8AF3A160/D_8AF3A164/D_8AF3A168 global declaration/evaluation order that produces the observed $a1/$a3/$t0 address allocation.
