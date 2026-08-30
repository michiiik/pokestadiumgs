# Region notes -- disasm/src/fragments/69/fragment69_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## 2026-08-30 wave 6 accepted sibling families (2026-08-30)

accepted: func_8F102618 and func_8F102708 match as signed-byte wrap/update helpers when D_8F1DEE48 is modeled as a 4-byte union and passed by value as func_80041FD0's third Fragment69PackedState argument; the aggregate ABI home copy emits the required sw a2, 8(sp). Exact sibling reuse changes only bytes[3] to bytes[2]. Both were link_verified and full-ROM COMPARE=1 gated.

accepted: func_8F100594 and func_8F100740 match as two-item rendering loops with a 6-byte Fragment69MenuState source record, 10-byte position records, and separate item/table-byte/Y induction variables. IDO requires the exact one-line spelling 'item = 0; tableOffset = 0; yOffset = 0; do {' to schedule both pointer-table base adjustments before counter zeroing; putting do on the next line is 105/107 exact, and putting only tableOffset/yOffset/do together is 106/107. Exact sibling reuse changes the initial color/text assets and Y base/stride (0x28/0xE versus 0x14/0xC). Both were link_verified and full-ROM COMPARE=1 gated.
