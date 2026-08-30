# Region notes -- disasm/src/fragments/14/fragment14_FAD40.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 6 handoff (2026-08-31)

Wave 6 handoff: func_813035A0 unresolved after 18 serial CC_CHECK=1 probes. Best normalized/raw similarity was 0.9762/0.1190 with operand_or_scheduling_drift; repeated fingerprint was expected lui $t7, 0x0002 but actual lui $v0, 0x0002. Preserve the 0x20-byte frame and force the late global-base load into a dedicated temporary before retrying.
