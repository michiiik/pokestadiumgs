#include "global.h"


#ifdef VERSION_US
extern void *D_80095110;
extern void *D_80095114;
extern void func_8004B09C(s32 x, s32 y, s32 width, s32 height,
                          void *texture, s32 red, s32 green, s32 blue,
                          s32 advance);

extern s16 D_800950D0;
extern void func_8004AF18(s32 x, s32 y);

void Ui_DrawAnimatedTextureMarker(s32 x, s32 y) {
    s16 frame = D_800950D0;
    s16 markerX;

    if (frame < 6) {
        markerX = (s16)((s16)x + frame);
    } else {
        markerX = (s16)((s16)x - frame + 12);
    }

    func_8004AF18(markerX, (s16)y);
    D_800950D0 = (s16)((frame + 1) % 12);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/Ui_DrawTexturedRect8x8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/Ui_DrawBorderStyleA.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/Ui_DrawBorderStyleB.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/Ui_DrawBorderStyleC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/Ui_FillInsetRectangleA.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/Ui_FillInsetRectangleB.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004A858.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/Ui_DrawBorderedPanel.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/Ui_DrawGradientPanel.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004AE3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004AF18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004B09C.s")

void func_8004B2CC(s32 x, s32 y, s32 width, s32 height,
                   s32 red, s32 green, s32 blue, s32 advance) {
    func_8004B09C(x, y, width, height, D_80095110,
                  (red >> 24) & 0xFF, (green >> 24) & 0xFF,
                  (blue >> 24) & 0xFF, advance);
}

void func_8004B314(s32 x, s32 y, s32 width, s32 height) {
    func_8004B09C(x, y, width, height, D_80095114,
                  0xF0, 0xD4, 0x68, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004B35C.s")
#endif
