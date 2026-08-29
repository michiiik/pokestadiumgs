# Region notes -- disasm/src/fragments/60/fragment60_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## func_86A0B66C (2026-08-29)

Accepted call_sequence owner. The exact compiler-faithful spelling keeps the raw D_87F119DC field accesses and declares f32 temp_fv0 before s32 var_v0; initialize var_v0 to 0, then write field 0x48 from field 0x10 + field 0x48 (increment-before-current operand order), reload field 0x48 for the -270.0f/270.0f range test, and conditionally call func_87F026E8(D_87F119D8, D_87F119DC). The first four source-shape batches were rejected as register/scheduling variants; a 60-second permuter found score 0 for the operand swap. Final probe was link_verified with normalized and raw exact match, and the full combined ROM gate accepted with one install compile. No evidence-backed semantic rename is known.
