# Region notes -- disasm/src/fragments/79/fragment79_3B7DB0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 13 handoff (2026-08-31)

No accepted owner. func_841485A4 received 19 cumulative attempts. Best constant-map:u8-return:assign reached normalized/raw 0.7500/0.5000; the repeated first mismatch at instruction 16 expected beq $a2,$zero,14 but generated a pointer move. Next action is to preserve arg0 in $a0 through the divide and clamp path while resolving the pointer and return ABI. No link_verified candidate or ROM gate.
