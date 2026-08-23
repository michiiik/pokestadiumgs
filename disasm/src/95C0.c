#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D05A0;
extern u8 D_80087320[];
extern void TextRenderer_DrawGlyphSmall(s16 x, s16 y, s16 glyph);
extern void TextRenderer_DrawGlyphLarge(s16 x, s16 y, s16 glyph);

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_SetupGlyphState.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_RestoreState.s")

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
