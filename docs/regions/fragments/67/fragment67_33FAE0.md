# Region notes -- disasm/src/fragments/67/fragment67_33FAE0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Fleet box 2026-08-31: call-sequence helper requeued (2026-08-31)

No accepted owner. func_82904E9C received 15 variants across 4 serial CC_CHECK-enabled batches; best callseq:m2c-shape:no-spill was 0.9091 normalized / 0.8727 raw with operand_or_scheduling_drift at offset 33: expected lbu $v0,$a1,4210 but actual lbu $v1,$a1,4210. Requeue targeting v0/v1 allocation and the expected a1 alias plus stack spill. Preserve the assigned tied/drift/stuck and jump-table skip list.
