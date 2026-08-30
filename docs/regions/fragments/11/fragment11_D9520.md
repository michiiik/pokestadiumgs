# Region notes -- disasm/src/fragments/11/fragment11_D9520.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 8 handoff (2026-08-31)

Wave 8 handoff: func_8160324C remains unresolved after 12 serial CC_CHECK=1 candidates. Best normalized/raw similarity was 0.3971/0.2059 with operand_or_scheduling_drift. The literal 0xFB000000 requires gDPSetPrimColor rather than gDPSetFillColor, and direct macro forms load D_800D0510 too early. Next action is to preserve float conversion first while expressing the display-list pointer/global update in the established same-file ABI shape; investigate the D_800D0510 u32 declaration versus accepted Gfx * macro users.
