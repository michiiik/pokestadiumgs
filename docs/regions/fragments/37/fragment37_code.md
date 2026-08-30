# Region notes -- disasm/src/fragments/37/fragment37_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 14 handoff (2026-08-31)

No accepted owner. func_88800A30 received CC_CHECK-enabled probes; the final best was init:locals:ascending at normalized/raw 0.9219/0.7344 with operand_or_scheduling_drift. The first mismatch was expected sw $ra, 0x44($sp) versus a local store at offset 21; a simpler form was 12 instructions short. Next action is exact stack-local declaration order and types, placing the saved return address before initialization stores while preserving initial global-address scheduling. No link_verified candidate or ROM gate.
