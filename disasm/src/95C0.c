#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/func_800089C0.s")

extern Gfx *D_800D05A0;
void func_80008B7C(void) {
    gDPPipeSync(D_800D05A0++);
    gDPSetTexturePersp(D_800D05A0++, G_TP_PERSP);
    gDPSetTextureFilter(D_800D05A0++, G_TF_BILERP);
    gDPSetAlphaCompare(D_800D05A0++, G_AC_NONE);
    gSPTexture(D_800D05A0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
}

extern Gfx *D_800D05A0;
void func_80008C18(s16 arg0, s16 arg1, s16 arg2) {
    gSPTextureRectangle(D_800D05A0++, arg0 * 4, arg1 * 4, (arg0 + 6) << 2, (arg1 + 8) << 2, G_TX_RENDERTILE,
                        ((arg2 % 16) * 6) << 5, (u16)(arg2 / 16) << 8, 0x0400, 0x0400);
}

extern Gfx *D_800D05A0;
void func_80008D24(s16 arg0, s16 arg1, s16 arg2) {
    gSPTextureRectangle(D_800D05A0++, arg0 * 8, arg1 * 8, (arg0 + 6) << 3, (arg1 + 8) << 3, G_TX_RENDERTILE,
                        ((arg2 % 16) * 6) << 5, (u16)(arg2 / 16) << 8, 0x0200, 0x0200);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/func_80008E30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/func_80008F04.s")

extern s32 *D_80087314;
void TextRenderer_ClearQueuedStrings(void) {
    s32 *temp_s1;
    s32 *var_s0;

    var_s0 = D_80087314;
    if (var_s0 != NULL) {
        do {
            temp_s1 = *var_s0;
            Util_Free((s32) var_s0);
            var_s0 = temp_s1;
        } while (temp_s1 != NULL);
    }
    D_80087314 = NULL;
}

extern void *memcpy(void *, const void *, s32); void *TextRenderer_FormatCopy(void *dest, const void *src, s32 size) { return (u8 *)memcpy(dest, src, size) + size; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/func_80009094.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/func_80009138.s")
#endif
