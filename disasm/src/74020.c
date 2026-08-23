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
#define D_800A0068 ((u8 *)0x800A0068)
#define D_800A006C ((u8 *)0x800A006C)
#define D_800A0070 ((u8 *)0x800A0070)
#define D_800A0074 ((u8 *)0x800A0074)
#define D_800A0078 ((u8 *)0x800A0078)

#ifdef VERSION_US
extern void _bzero(void *dst, s32 size);

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

/* Expand the renderer's compact control codes into glyph/attribute pairs.
 * The input byte is deliberately sign-extended: the original routine uses
 * `lb`, and its unsigned jump-table bounds check is consequently preserved
 * here rather than silently changing the handling of high-bit bytes. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/74020/func_80073638.s")

#if 0
s32 func_80073638(const u8 *input, u8 *output, s32 maxGlyphs) {
    u8 *dst = output;
    s32 count = 0;
    s32 code;

    if ((code = (s32)(s8)*input) == 0 || maxGlyphs <= 0) {
        return 0;
    }

    while (code != 0 && count < maxGlyphs) {
        u8 attr;

        if ((u32)(code - 0xBC) < 0x41) {
            switch (code - 0xBC) {
            case 0:
                dst[0] = D_800A0068[0];
                dst[1] = D_800A0068[1];
                dst[2] = D_800A006C[0];
                dst[3] = D_800A006C[1];
                dst += 4;
                count += 2;
                goto next;
            case 1:
                dst[0] = D_800A0070[0];
                dst[1] = D_800A0070[1];
                dst[2] = D_800A0074[0];
                dst[3] = D_800A0074[1];
                dst += 4;
                count += 2;
                goto next;
            case 8:
                dst[0] = 0x41;
                attr = dst[1];
                dst[1] = (u8)((attr & 1) | 0xA);
                dst += 2;
                count++;
                goto next;
            case 0x1A:
                dst[0] = 0x4F;
                attr = dst[1];
                dst[1] = (u8)((attr & 1) | 0xA);
                dst += 2;
                count++;
                goto next;
            case 0x20:
                dst[0] = 0x55;
                attr = dst[1];
                dst[1] = (u8)((attr & 1) | 0xA);
                dst += 2;
                count++;
                goto next;
            case 0x23:
                dst[0] = D_800A0078[0];
                dst[1] = D_800A0078[1];
                dst[2] = D_800A0078[2];
                dst[3] = D_800A0078[3];
                dst += 4;
                count += 2;
                goto next;
            case 0x28:
                dst[0] = 0x41;
                dst[1] = 0xB;
                dst += 2;
                count++;
                goto next;
            case 0x3A:
                dst[0] = 0x4F;
                dst[1] = 0xB;
                dst += 2;
                count++;
                goto next;
            case 0x40:
                dst[0] = 0x55;
                dst[1] = 0xB;
                dst += 2;
                count++;
                goto next;
            default:
                break;
            }
        }

        if (code >= 0x61 && code < 0x7B) {
            dst[0] = (u8)(code - 0x20);
        } else {
            dst[0] = (u8)code;
        }
        attr = dst[1];
        dst[1] = (u8)((attr & 1) | 1);
        dst += 2;
        count++;

    next:
        code = (s32)(s8)*++input;
    }
    return count;
}
#endif

/* Compare two packed text strings after expanding their glyph pairs. */
s32 func_80073828(const u8 *left, const u8 *right) {
    u8 leftExpanded[0x100];
    u8 rightExpanded[0x100];
    s32 count = 0;
    s32 i;

    _bzero(leftExpanded, sizeof(leftExpanded));
    func_80073638(left, leftExpanded, 0x80);
    _bzero(rightExpanded, sizeof(rightExpanded));
    func_80073638(right, rightExpanded, 0x80);

    while (count < 0x80 && leftExpanded[count * 2] != 0) {
        u8 leftGlyph = leftExpanded[count * 2];
        u8 rightGlyph = rightExpanded[count * 2];

        if (rightGlyph < leftGlyph) {
            return 1;
        }
        if (leftGlyph < rightGlyph) {
            return -1;
        }
        count++;
    }

    if (count < 0x80 && rightExpanded[count * 2] != 0) {
        return 1;
    }

    for (i = 0; i < count; i++) {
        u8 leftAttr = leftExpanded[i * 2 + 1];
        u8 rightAttr = rightExpanded[i * 2 + 1];
        u8 leftWidth = leftAttr >> 1;
        u8 rightWidth = rightAttr >> 1;

        if (rightWidth < leftWidth) {
            return 1;
        }
        if (leftWidth < rightWidth) {
            return -1;
        }
    }
    for (i = 0; i < count; i++) {
        u8 leftFlag = leftExpanded[i * 2 + 1] & 1;
        u8 rightFlag = rightExpanded[i * 2 + 1] & 1;

        if (rightFlag < leftFlag) {
            return 1;
        }
        if (leftFlag < rightFlag) {
            return -1;
        }
    }
    return 0;
}

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
            /* The MIPS sequence performs an arithmetic shift of index - 1;
             * keep the signed conversion so the index-zero case yields 0. */
            *dst++ = (u8)(base + (((s32)index - 1) / 2));
            *dst++ = (u8)(glyph + next);
        }
    }
}
#endif
