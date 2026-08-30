# Region notes -- disasm/src/1CDC0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Coordinator near-miss terminal: func_8001F9B0 (2026-08-31)

Coordinator follow-up on 2026-08-31: func_8001F9B0 remains unresolved after 10 new CC_CHECK=1 candidates following 61 prior attempts. The one-cursor/global-base and typed-pointer/integer-address ABI models all produced the exact 208-byte body but the same operand_or_scheduling_drift fingerprint at instruction 2: expected or $v1,$a0,$zero, actual or $v0,$a0,$zero. No link-verified candidate or full-ROM gate was reached. Classify as register-allocation/repeated-drift terminal for hand decompilation; route the exact-size body to the permuter and do not repeat pointer declaration or formal-width variants without a new compiler rule.
