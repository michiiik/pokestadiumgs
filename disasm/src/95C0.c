#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_SetupGlyphState.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_RestoreState.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_DrawGlyphSmall.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_DrawGlyphLarge.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_DrawString.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_FlushQueuedStrings.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_ClearQueuedStrings.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_FormatCopy.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/HAL_Printf.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/TextRenderer_QueuePersistentString.s")
#endif
