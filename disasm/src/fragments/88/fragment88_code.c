#include "global.h"


#ifdef VERSION_US
u16 func_81C00020(u8 arg0) {
    u16 result;
    if (arg0 < 0x29) {
        result = arg0 + 0x2A4;
    } else {
        result = arg0 + 0x2A7;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C00050.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C00174.s")

s8 func_81C00050(u8, u8);
s8 func_81C00174(u8, u8, u8);
u32 func_8003570C(void);
void func_81C002E4(void *arg0, void *arg1, u8 arg2) {
    (*(s8 *)((u8 *)(arg1) + (0))) = (s8) (func_8003570C() & 1);
    (*(s8 *)((u8 *)(arg1) + (1))) = func_81C00050((*(u8 *)((u8 *)(arg0) + (0))), (*(u8 *)((u8 *)(arg0) + (1))));
    (*(s8 *)((u8 *)(arg1) + (2))) = func_81C00174((*(u8 *)((u8 *)(arg0) + (1))), (*(u8 *)((u8 *)(arg0) + (0))), arg2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C0034C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C00408.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C004E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C00584.s")

s32 func_81C0034C(u8, u8);
s16 func_81C00408(u8);
s16 func_81C004E4(s32);
extern void func_81C00584(u8);
void func_81C00740(u8 arg0, s16 *arg1, s16 *arg2, s32 arg3, u8 arg4) {
    if (func_81C0034C(arg0, arg4) != 0) {
        func_81C00584(arg0);
        *arg1 = func_81C00408(arg0);
        *arg2 = func_81C004E4(arg3);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C007A4.s")
#endif
