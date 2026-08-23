#include "global.h"

/* Character-code conversion tables used by the text/UI renderer.  These
 * labels are not present in the generated linker symbol lists, so retain the
 * original absolute addresses rather than introducing unresolved externals. */
#define D_8009F87F ((u8 *)0x8009F87F)
#define D_8009F880 ((u8 *)0x8009F880)
#define D_8009F97F ((u8 *)0x8009F97F)
#define D_8009FA7F ((u8 *)0x8009FA7F)
#define D_8009FB7B ((u8 *)0x8009FB7B)
#define D_8009FC77 ((u8 *)0x8009FC77)
#define D_8009FD73 ((u8 *)0x8009FD73)
#define D_8009FE6F ((u8 *)0x8009FE6F)
#define D_8009FF6B ((u8 *)0x8009FF6B)

#define D_8012B410 ((u8 *)0x8012B410)

#ifdef VERSION_US
u8 func_80073420(s32 code) {
    u8 index = (u8)code;
    if (index == 0 || index >= 0xFE) {
        return 0;
    }
    return D_8009F87F[index];
}

u8 func_80073450(s32 code) {
    u8 index = (u8)code;
    if (index == 0 || index >= 0xFE) {
        return 0;
    }
    return D_8009F97F[index];
}

u8 func_80073480(s32 code) {
    u8 index = (u8)code;
    if (index == 0) {
        return 0;
    }
    if (index < 0x32) {
        return D_8009F87F[index];
    }
    if (index >= 0xFC) {
        return 0;
    }
    return D_8009F880[index];
}

u8 func_800734CC(s32 code) {
    u8 index = (u8)code;
    u8 result;

    if (index == 0 || index >= 0xFC) {
        return 0;
    }
    result = D_8009F97F[index];
    if (result >= 0x33) {
        result = (u8)(result - 1);
    }
    return result;
}

u8 func_80073510(s32 code) {
    u8 index = (u8)code;
    if (index == 0 || index >= 0xFC) {
        return 0;
    }
    return D_8009FA7F[index];
}

u8 func_80073540(s32 code) {
    u8 index = (u8)code;
    if (index == 0 || index >= 0xFC) {
        return 0;
    }
    return D_8009FB7B[index];
}

u8 func_80073570(s32 code) {
    u8 index = (u8)code;
    if (index == 0 || index >= 0xFB) {
        return 0;
    }
    return D_8009FC77[index];
}

u8 func_800735A0(s32 code) {
    u8 index = (u8)code;
    if (index == 0 || index >= 0xFB) {
        return 0;
    }
    return D_8009FD73[index];
}

u8 func_800735D0(s32 code) {
    u8 index = (u8)code;
    if (index == 0 || index >= 0xFB) {
        return 0;
    }
    return D_8009FE6F[index];
}

u8 func_80073600(s32 code) {
    u8 index = (u8)code;
    if (index == 0 || index >= 0xFB) {
        return 0;
    }
    return D_8009FF6B[index];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/74020/func_80073638.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/74020/func_80073828.s")

/* Expand the game's packed text stream into the two-byte-per-glyph format
 * consumed by the renderer.  Bytes below 0x80 are literal glyphs; high-bit
 * bytes introduce a pair whose low seven bits select one of the compact
 * character ranges. */
u8 *func_800739EC(u8 *input, u8 *output) {
    u8 *dst = output != NULL ? output : D_8012B410;
    u8 code;

    for (;;) {
        code = *input++;
        if (code == 0) {
            *dst = 0;
            return output != NULL ? output : D_8012B410;
        }

        if (code < 0x80) {
            *dst++ = code;
            continue;
        }

        {
            u8 next = *input++;
            u8 index = code & 0x7F;
            u8 glyph;
            u8 base;

            if (next == 0) {
                *dst = 0;
                return output != NULL ? output : D_8012B410;
            }

            next &= 0x7F;
            if (index & 1) {
                glyph = next < 0x60 ? 0x1F : 0x20;
            } else {
                glyph = 0x7E;
            }
            base = index < 0x5F ? 0x71 : 0xB1;
            *dst++ = (u8)(base + (index == 0 ? -1 : (index - 1) / 2));
            *dst++ = (u8)(glyph + next);
        }
    }
}
#endif
