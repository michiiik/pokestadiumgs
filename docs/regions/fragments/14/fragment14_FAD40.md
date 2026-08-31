# Region notes -- disasm/src/fragments/14/fragment14_FAD40.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 6 handoff (2026-08-31)

Wave 6 handoff: func_813035A0 unresolved after 18 serial CC_CHECK=1 probes. Best normalized/raw similarity was 0.9762/0.1190 with operand_or_scheduling_drift; repeated fingerprint was expected lui $t7, 0x0002 but actual lui $v0, 0x0002. Preserve the 0x20-byte frame and force the late global-base load into a dedicated temporary before retrying.

## Wave 16 handoff (2026-08-31) (2026-08-31)

requeue: func_81302CB4 (fresh, prior_attempts=0; 105 instructions, expected frame 0x28). Best normalized/raw similarity was 0.7429/0.5048 with operand_or_scheduling_drift; first diff expected stack adjustment -40 but actual -48. Tried raw-offset and m2c coordinate-helper shapes; one K&R struct-selector form compile-failed. Next reduce float temporaries/spills, retain sp18 plus saved a1, preserve the one-argument D_8160BD08 call, and reorder declarations.
