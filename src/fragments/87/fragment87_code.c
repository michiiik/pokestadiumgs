#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B00020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B000B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B0019C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B00230.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B002EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B003EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B004EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B005EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B006EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B00728.s")

s32 func_81B00764(u8 arg0) {
    switch (arg0) {
    case 0x1B:
        return 3;
    default:
        return 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B00788.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B00CA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B00E58.s")

s32 func_80059AE0(u8);
extern void func_81B00788(u8);

void func_81B00F78(u8 arg0) {
    if (func_80059AE0(arg0) != 0) {
        func_81B00788(arg0);
    }
}
#endif
