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

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_DrawString.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_FormatCopy.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/HAL_Printf.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_QueuePersistentString.s")
#endif
