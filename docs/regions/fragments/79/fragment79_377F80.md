# Region notes -- disasm/src/fragments/79/fragment79_377F80.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 7 handoff (2026-08-31)

Wave 7 handoff: func_84108A10 remains unresolved after 6 serial CC_CHECK=1 probes. Best normalized/raw similarity was 0.9655/0.9655 over 56 of 58 instructions; no link_verified candidate or ROM gate. Remaining drift is constant-load scheduling plus signed lb versus lbu. Next action is declaration/order shaping that schedules 0x10080 initialization before loop-counter setup and forces the signed-byte load.
