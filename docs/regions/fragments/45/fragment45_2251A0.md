# Region notes -- disasm/src/fragments/45/fragment45_2251A0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-31 fleet box requeue (2026-08-31)

requeue func_8AB02240: eight candidates across macro, loop, frame, and ABI hypotheses; no link_verified hit or ROM gate. Best normalized/raw similarity was 0.8676/0.7353 with operand_or_scheduling_drift: expected 268 bytes/67 instructions versus actual 272/68, first diff expected sw $a3,68(sp) versus actual sw $a0,56(sp); expected sll/sra $a3 before gDPSetEnvColor while actual used andi directly. Next action is to resolve the caller/helper ABI and formal-width ordering, especially arg3 and func_8AB01FC8.
