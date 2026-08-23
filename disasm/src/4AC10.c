#include "global.h"


#ifdef VERSION_US
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004B2CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004B314.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004B35C.s")
#endif
