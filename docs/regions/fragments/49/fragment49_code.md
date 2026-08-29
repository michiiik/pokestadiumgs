# Region notes -- disasm/src/fragments/49/fragment49_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Accepted float-random sibling family (2026-08-29)

2026-08-29: func_86104B2C and func_86104BEC accepted with the direct raw-address field spelling: u32 func_8003570C(void), divide the returned integer conversion by 4294967296.0f, multiply by the paired f32 constants, store at offsets 0x18 and 0x1C, then store 0.0f at 0x20. Both probe matches were link_verified=true and full runner gates exited 0. B2C also required the same-file caller transaction: add old-style extern void func_86104B2C(); before func_861048FC and spell its saved pointer as void *sp1C; sp1C = *p; this reproduced the caller 0x1C($sp) store and preserved the original no-argument call ABI. The direct typed forward prototype plus func_86104B2C(x) probe matched locally but full-ROM gate rejected. Prior B2C best was similarity 0.8776/raw 0.5714 with instruction_drift after 31 attempts; the accepted source-shape change was caller ABI/frame integration, not a new function-body arithmetic variant.
