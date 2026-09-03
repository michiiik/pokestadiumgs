#include "global.h"


#ifdef VERSION_US
extern void Input_SetRepeatController(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_88228A20(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19BCA0/func_88228A48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19BCA0/func_88228AB4.s")

extern u32 D_88234890;
extern void func_8821D930(s32);
void func_88228BA4(void) {
    func_8821D930((D_88234890 + 4));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19BCA0/func_88228BCC.s")
#endif
