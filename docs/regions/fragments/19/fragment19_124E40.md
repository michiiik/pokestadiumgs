# Region notes -- disasm/src/fragments/19/fragment19_124E40.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Accepted owner: func_8230583C (register tie closed) (2026-09-06)

Closed a register_allocation_only tie. tools/permute_candidate.py found a score-0 variant: adding an unreachable, unused label (dummy_label:) as the last statement inside the if-block, which is enough to shift IDO's register allocation for the surrounding do-while loop. Verified with tools/fleet_probe.py --gate: accepted, link-verified, full-ROM COMPARE=1 gate MD5 1561c75d11cedf356a8ddb1a4a5f9d5d.
