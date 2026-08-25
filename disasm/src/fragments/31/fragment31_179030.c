#include "global.h"


#ifdef VERSION_US
extern void func_800033DC(void *);
extern void *D_882346F8;

void func_88205DB0(void) {
    (*(s32 (**)())((u8 *)(D_882346F8) + (0x9C)))();
    func_800033DC(D_882346F8);
}

extern void func_88200134();
void func_88205DE8(void) { func_88200134(0, 1); func_88200134(1, 1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88205E18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88205EB0.s")

void func_88206430(void) { func_88200134(2, 2); func_88200134(3, 2); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206460.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_882064B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206508.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_8820659C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206668.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206714.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206C2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206CC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88207D14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88207D80.s")
#endif
