#include "global.h"


#ifdef VERSION_US
extern void func_800226C0(s32);
extern void Input_SetRepeatController(s32);
extern void func_88800B24();
extern s32 D_80087200;
extern void **D_882345F4;
void func_88231170(void) {
    func_800226C0(0x5E);
    Input_SetRepeatController(D_80087200);
    func_88800B24();
    (*(s32 *)((u8 *)(*D_882345F4) + (0xC))) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A43F0/func_882311B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A43F0/func_882313A4.s")
#endif
