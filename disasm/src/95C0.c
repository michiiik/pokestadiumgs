#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D05A0;
extern u8 D_80087320[];
extern void TextRenderer_DrawGlyphSmall(s16 x, s16 y, s16 glyph);
extern void TextRenderer_DrawGlyphLarge(s16 x, s16 y, s16 glyph);

static Gfx *TextRenderer_Emit(Gfx *gfx, u32 w0, u32 w1) {
    gfx->words.w0 = w0;
    gfx->words.w1 = w1;
    return gfx + 1;
}

void TextRenderer_SetupGlyphState(void) {
    Gfx *gfx = D_800D05A0;

    gfx = TextRenderer_Emit(gfx, 0xE7000000, 0);
    gfx = TextRenderer_Emit(gfx, 0xE3000A01, 0);
    gfx = TextRenderer_Emit(gfx, 0xE3000C00, 0);
    gfx = TextRenderer_Emit(gfx, 0xE3001201, 0);
    gfx = TextRenderer_Emit(gfx, 0xFA000000, 0);
    gfx = TextRenderer_Emit(gfx, 0xE200001C, 0x0F0A7008);
    gfx = TextRenderer_Emit(gfx, 0xFC119623, 0xFF2FFFFF);
    gfx = TextRenderer_Emit(gfx, 0xFD700000,
                            (u32)D_80087320 & 0x1FFFFFFF);
    gfx = TextRenderer_Emit(gfx, 0xF5700000, 0x07018070);
    gfx = TextRenderer_Emit(gfx, 0xE6000000, 0);
    gfx = TextRenderer_Emit(gfx, 0xF3000000, 0x0747F156);
    gfx = TextRenderer_Emit(gfx, 0xE7000000, 0);
    gfx = TextRenderer_Emit(gfx, 0xF5600C00, 0x00018070);
    gfx = TextRenderer_Emit(gfx, 0xF2000000, 0x0017C0BC);
    D_800D05A0 = gfx;
}

void TextRenderer_RestoreState(void) {
    Gfx *gfx = D_800D05A0;

    gfx = TextRenderer_Emit(gfx, 0xE7000000, 0);
    gfx = TextRenderer_Emit(gfx, 0xE3000C00, 0x00080000);
    gfx = TextRenderer_Emit(gfx, 0xE3001201, 0x00002000);
    gfx = TextRenderer_Emit(gfx, 0xE2001E01, 0);
    gfx = TextRenderer_Emit(gfx, 0xD7000000, 0xFFFFFFFF);
    D_800D05A0 = gfx;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_DrawGlyphSmall.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_DrawGlyphLarge.s")

void TextRenderer_DrawString(s16 x, s16 y, const char *text, s32 mode) {
    while (*text != '\0') {
        s16 glyph = (u8)*text++ & 0x7F;
        glyph -= 0x20;
        if (glyph != 0 && mode == 0) {
            TextRenderer_DrawGlyphSmall(x, y, glyph);
        }
        if (glyph != 0 && mode == 1) {
            TextRenderer_DrawGlyphLarge(x, y, glyph);
        }
        x += 6;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_FlushQueuedStrings.s")

extern void *D_80087314;
extern void Util_Free(void *ptr);

void TextRenderer_ClearQueuedStrings(void) {
    void *entry = D_80087314;

    while (entry != NULL) {
        void *next = *(void **)entry;
        Util_Free(entry);
        entry = next;
    }

    D_80087314 = NULL;
}

void *TextRenderer_FormatCopy(void *dst, const void *src, s32 size) {
    memcpy(dst, src, size);
    return (u8 *)dst + size;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/HAL_Printf.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_QueuePersistentString.s")
#endif
