#include "global.h"


#ifdef VERSION_US
extern void Input_SetRepeatController(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_88228D80(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19C000/func_88228DA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19C000/func_88228E14.s")

extern u32 D_882348A0;
extern void func_8821D930(s32);
void func_88228F08(void) { func_8821D930((D_882348A0 + 4)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19C000/func_88228F30.s")
#endif
