#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/func_800089C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/func_80008B7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/func_80008C18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/95C0/func_80008D24.s")

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
