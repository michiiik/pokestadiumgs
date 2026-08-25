#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80044270.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80044424.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_800445E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_8004468C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80044734.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_8004494C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80044B64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80044D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80044F98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_800451B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_800453D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_800455E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_800459AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80045DB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80046204.s")

s32 func_800464F8(s32 arg0, s32 arg1) {
    s32 temp_lo;
    s32 var_v1;

    temp_lo = arg0 / arg1;
    var_v1 = temp_lo;
    if ((arg0 % arg1) > 0) {
        var_v1 = temp_lo + 1;
    }
    return var_v1;
}

s32 func_80046540(s32 arg0, s32 arg1) {
    return (arg1 / arg0) & ~1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_8004657C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80046634.s")

extern void func_8004657C(void);
extern void func_80046634(s32);
void func_800468A0(s32 arg0) { func_8004657C(); func_80046634(arg0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_800468C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80046930.s")
#endif
