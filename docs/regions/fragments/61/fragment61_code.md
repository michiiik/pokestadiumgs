# Region notes -- disasm/src/fragments/61/fragment61_code.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Accepted func_86B05484 (2026-08-30)

Accepted func_86B05484 in the 2026-08-30 box via call-chain:object-base. Winning spelling: f32 arg0/f32 arg1/f32 arg2/s32 arg3; u8 *object; u8 *base; f32 scale; assign object->0x1c = 0, compute scale as (f32)((f64)D_86B0D178 * D_86B0DDE8), store it at 0x5c/0x58/0x54, set base = object + 0x24, call func_8003F1DC(base), then store the three float args at 0x48/0x4c/0x50 and s32 arg3 at 0x20, call func_8003F114(base, 0, -1, D_86B0E1A4) and func_8003F210(base, 0). Probe candidate was link_verified=true and the full COMPARE=1 ROM gate passed with checksum 1561c75d11cedf356a8ddb1a4a5f9d5d. The prior m2c-style aliases (sp18/sp24/temp_v0) produced a 0x30 frame / immediate drift; keep the object/base local shape.
