# Region notes -- disasm/src/fragments/44/fragment44_1F7DD0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 14 handoff (2026-08-31)

No accepted owner. func_8AF09C34 received 7 probes; the best constant-map:m2c:word-pointers form reached normalized/raw 0.6744/0.2326 and had instruction drift. The final argument must remain s32 and be cast to a 32-bit source address; pointer formals caused frame drift. Next action is two loop-carried locals src and dst with the end condition directly expressed as (u8 *)(u32)arg13 + 0x504, without result or end locals. No link_verified candidate or ROM gate.
