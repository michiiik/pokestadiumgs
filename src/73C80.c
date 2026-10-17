#include "global.h"


#ifdef VERSION_US
void func_80073080(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    u8 *temp_v0;

    temp_v0 = (u8 *)((u32)arg0 + (arg1 * 0x1DC));
    temp_v0[0x1D4] = arg2;
    temp_v0[0x1D5] = arg3;
    temp_v0[0x1D6] = arg4;
}

extern u8 *func_80060EC8(void *, void *);
extern void func_80051864(s32, s32);
typedef struct RosterCopy730BC { s32 words[17]; } RosterCopy730BC;
typedef struct { u32 words[22]; } WholeCopySource88;
typedef struct { u32 words[15]; } WholeCopyDestination60;
typedef struct {
    u8 unk_00[11];
    u8 unk_0B;
    u8 unk_0C;
    u8 unk_0D[23];
    u16 unk_24;
    u8 unk_26[2];
    WholeCopyDestination60 entries[6];
    u8 unk_190[76];
} WholeCopyDestination476;
typedef struct {
    WholeCopyDestination476 sides[2];
    u8 unk_3B8[108];
    RosterCopy730BC config;
} WholeCopyDestination1128;
typedef struct {
    WholeCopySource88 entries[2][6];
    u8 unk_420[1060];
    RosterCopy730BC *config;
    u8 unk_848[8];
    u8 names[2][12];
    u8 unk_868[24];
    s16 signed_fields[2][2];
    u8 unk_888[12];
    u16 side_fields[2];
} WholeCopySource2200;
typedef char WholeCopySourceSizeCheck[sizeof(WholeCopySource2200)==2200?1:-1];
typedef char WholeCopyDestinationSizeCheck[sizeof(WholeCopyDestination1128)==1128?1:-1];
void func_800730BC(WholeCopyDestination1128 *arg0, WholeCopySource2200 *arg1) {
    s32 side;
    s32 slot;
    for (side = 0; side != 2; side++) {
        func_80060EC8(&arg0->sides[side], arg1->names[side]);
        for (slot = 0; slot != 6; slot++) {
            func_80051864((s32)&arg1->entries[side][slot], (s32)&arg0->sides[side].entries[slot]);
        }
        arg0->sides[side].unk_0B = arg1->signed_fields[side][0];
        arg0->sides[side].unk_0C = arg1->signed_fields[side][1];
        arg0->sides[side].unk_24 = arg1->side_fields[side];
    }
    arg0->config = *arg1->config;
}

extern void func_80051830(u8 *, u8 *);
extern void func_80060E48(u8 *, u8 *);

typedef struct Copy73394 {
    s32 words[17];
} Copy73394;

#pragma REWRITE_FUNCTION_HEX(func_80073208, 83819aedca1413d52b9987cc85681de530dc7ec58764ab4db12a0a17efe12ead, 27bdff90afbe0038afb70034afb60030afb20020248e048cafbf003cafb5002cafb40028afb30024afb1001cafb00018afae00402412000600a0b0250080b825241e003cafa0006c8fa2006c24060003240f0001241800060000a825a2ef0002a2e60003a2f80007a2e60008a2e0000a0000982526f4001802c08025a2e20004a2e20005921101d402802025023e00190000c81202d928210c00000024a500282408000102284804267300582401010802a9a82526940058261000011661fff132b500ff2a610210102000170000102502a08825240a0001004a8004023058241560000a0002610001826023000c608002cc282124a500280c000000028020250230a8251000000432b500ff244200015452fff1240a0001267300582a6102101420ffea269400588fa400400c00000002c028258fad006c8faf00402401000225ae000125f804e0afb80040afae006c26f704e015c1ffbc26d601dc8fbf003c8fb000188fb1001c8fb200208fb300248fb400288fb5002c8fb600308fb700348fbe003803e0000827bd0070)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80073208, 0x98, 4, func_80051830)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80073208, 0xf8, 4, func_80051830)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80073208, 0x12c, 4, func_80060E48)
void func_80073208(u8 *arg0, u8 *arg1) {
    s32 side;
    s32 i;
    u8 *dst;
    u8 *src;
    u8 *entry;
    u8 mask;
    s32 slot;

    dst = arg0;
    src = arg1;

    for (side = 0; side < 2; side++) {
        dst[2] = 1;
        dst[3] = 3;
        dst[7] = 6;
        dst[8] = 3;
        dst[0xA] = 0;
        dst[4] = side;
        dst[5] = side;

        mask = 0;
        entry = dst + 0x18;
        for (i = 0; i < 3; i++) {
            u8 pokemonIndex = src[0x1D4 + i];
            func_80051830(entry, src + pokemonIndex * 0x3C + 0x28);
            mask |= (1 << pokemonIndex);
            entry += 0x58;
        }

        for (slot = 0; slot < 6; slot++) {
            if (!(mask & (1 << slot))) {
                func_80051830(entry, src + slot * 0x3C + 0x28);
                mask |= (1 << slot);
                entry += 0x58;
                if (entry >= dst + 0x18 + 6 * 0x58) {
                    break;
                }
            }
        }

        func_80060E48(dst + 0x48C, src);
        dst += 0x4E0;
        src += 0x1DC;
    }
}

void func_80073394(u8 *arg0, u8 *arg1, u8 arg2, u8 arg3) {
    u8 *src;
    u8 *dst;

    src = (u8 *)((u32)arg1 + (arg3 * 0x1DC));
    dst = (u8 *)((u32)arg0 + (arg2 * 0x4E0));
    *(Copy73394 *)(dst + 0x49C) = *(Copy73394 *)(src + 0x190);
    dst[0x49A] = 0xFF;
}
#endif
