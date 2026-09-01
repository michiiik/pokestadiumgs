# Region notes -- disasm/src/fragments/67/fragment67_33FAE0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Fleet box 2026-08-31: call-sequence helper requeued (2026-08-31)

No accepted owner. func_82904E9C received 15 variants across 4 serial CC_CHECK-enabled batches; best callseq:m2c-shape:no-spill was 0.9091 normalized / 0.8727 raw with operand_or_scheduling_drift at offset 33: expected lbu $v0,$a1,4210 but actual lbu $v1,$a1,4210. Requeue targeting v0/v1 allocation and the expected a1 alias plus stack spill. Preserve the assigned tied/drift/stuck and jump-table skip list.

## Fleet box 2026-09-01: GBI display-list constructor accepted (2026-09-01)

Accepted func_82903BA4 with the compiler-faithful GBI macro spelling: gSPDisplayList(D_800D0510++, D_80094DB8), gDPSetCombine(..., 0xFFFFFF, 0xFFFE793C), gDPSetRenderMode(..., 0x00504240, 0), two Gfx_FillRectRgba calls, gSPDisplayList(..., D_80094D90), then two Gfx_FillRectRgb calls. Probe was link-verified and the sequential full ROM gate passed (MD5 1561c75d11cedf356a8ddb1a4a5f9d5d). Candidate batch had 5 variants; direct macros accepted. This confirms the display-list append macro family in a fragment.
