#include "global.h"


#ifdef VERSION_US
extern u8 D_8800686C;
extern s32 func_88000020(u8);
s32 func_88000020(u8 arg0) {
    s32 result = 0;
    switch (arg0) {
    case 1:
    case 2:
    case 3:
    case 4:
        result = 1;
        break;
    }
    return result;
}

void func_8800005C(void) {
    func_88000020(D_8800686C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000080.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000288.s")

void func_880002F4(u8 *arg0, s16 arg1) {
    *(s16 *)arg0 = arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000308.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000488.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000510.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000578.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_880006BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_880006E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000770.s")

extern s32 func_88000770(u8 *);
s32 func_880007B0(u8 *arg0) {
    s32 result = 0;
    if ((arg0[0] > 0) && (arg0[0] < 0x98) && ((arg0[0x1E] & 1) == 0)) {
        s32 temp = 0;
        result = temp;
        if (func_88000770(arg0) == 0) {
            result = 1;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000808.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_880008B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_880009A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000A5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000C2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000E54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000EC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000FC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88001144.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88001234.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_880014A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_880015F4.s")
#endif
