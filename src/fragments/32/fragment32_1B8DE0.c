#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8DE0/func_88307AD0.s")

extern s32 func_88307AD0(s32, s8);
extern void *func_8004C874(s32, s32);
extern s32 func_80063270(u8);
s32 func_88307BCC(s32 arg0, u8 arg1) {
    s32 value = func_88307AD0(arg0, arg1);
    s8 narrowed = value;
    s32 result;

    if (value == -1) {
        result = (s32)func_8004C874(0x28, 0x24);
    } else {
        result = func_80063270(narrowed);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8DE0/func_88307C2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8DE0/func_88307DA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8DE0/func_88307DE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8DE0/func_88307F28.s")
#endif
