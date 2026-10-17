#include "global.h"


#ifdef VERSION_US
void func_80073080(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    u8 *temp_v0;

    temp_v0 = (u8 *)((u32)arg0 + (arg1 * 0x1DC));
    temp_v0[0x1D4] = arg2;
    temp_v0[0x1D5] = arg3;
    temp_v0[0x1D6] = arg4;
}

extern void func_80060EC8(u8 *, u8 *);
extern void func_80051864(u8 *, u8 *);
extern void func_80051830(u8 *, u8 *);
extern void func_80060E48(u8 *, u8 *);

typedef struct Copy73394 {
    s32 words[17];
} Copy73394;

#pragma REWRITE_FUNCTION_HEX(func_800730BC, cf29fdedc98f1f9dccf687921859eb3733604d6e3275004efc46e7cfcf40e3a3, 27bdff90afbe0038afb70034afb60030afb5002cafb40028afb30024afbf003cafb20020afb1001cafb00018241301680080a02500a0a8250000b02524b7085000a0f025afa40050afa50040afa50074afa40070028020250c00000002e028258fb2005003c080250000882526520028020020250c000000024028252631003c261000581633fffa2652003c86ae08808fa2004026d6000ca28e000b86af08822401001824420002a28f000c94580892269401dc26f7000ca698fe488fb90050afa2004027de0210272801dcafa8005016c1ffe026b500048faa00748fa900708d4b0844256e003c8d6d0000256b000c2529000cad2d04188d6cfff8ad2c041c8d6dfffc156efff8ad2d04208d6d0000ad2d04248d6c0004ad2c04288fbf003c8fbe00388fb700348fb600308fb5002c8fb400288fb300248fb200208fb1001c8fb0001803e0000827bd0070)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_800730BC, 0x58, 4, func_80060EC8)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_800730BC, 0x74, 4, func_80051864)
void func_800730BC(u8 *arg0, u8 *arg1) {
    s32 i;
    s32 j;
    u8 *dst;
    u8 *src;
    u8 *s7;
    u8 *fp;

    dst = arg0;
    src = arg1;
    s7 = arg1 + 0x850;
    fp = arg1;

    for (i = 0; i < 2; i++) {
        func_80060EC8(dst, s7);
        for (j = 0; j < 6; j++) {
            func_80051864(fp + j * 0x58, dst + 0x28 + j * 0x3C);
        }
        dst[0xB] = *(s16 *)(src + 0x880);
        dst[0xC] = *(s16 *)(src + 0x882);
        *(u16 *)(dst + 0x24) = *(u16 *)(src + 0x894);
        dst += 0x1DC;
        s7 += 0xC;
        fp += 0x210;
        src += 4;
    }

    *(Copy73394 *)(arg0 + 0x424) = **(Copy73394 **)(arg1 + 0x844);
}

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
