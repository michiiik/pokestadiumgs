# Region notes -- disasm/src/fragments/18/fragment18_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Accepted owner: func_81700908 (register tie closed) (2026-09-06)

Closed a register_allocation_only tie. tools/permute_candidate.py found a score-0 variant: wrapping the whole function body in a do{...}while(0), which changes IDO's register allocation for the loop-carried temp without changing behavior. Verified with tools/fleet_probe.py --gate: accepted, link-verified, full-ROM COMPARE=1 gate MD5 1561c75d11cedf356a8ddb1a4a5f9d5d.
