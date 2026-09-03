#include "global.h"


#ifdef VERSION_US
extern void Input_SetRepeatController(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_88229110(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19C390/func_88229138.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19C390/func_882291A4.s")

extern u32 D_882348B0;
extern void func_8821D930(s32);
void func_882295BC(void) { func_8821D930((D_882348B0 + 4)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19C390/func_882295E4.s")
#endif
