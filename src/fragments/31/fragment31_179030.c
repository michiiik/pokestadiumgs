#include "global.h"


#ifdef VERSION_US
extern void Util_Free(void *);
extern void *D_882346F8;

void func_88205DB0(void) {
    (*(s32 (**)())((u8 *)(D_882346F8) + (0x9C)))();
    Util_Free(D_882346F8);
}

extern void func_88200134();
void func_88205DE8(void) { func_88200134(0, 1); func_88200134(1, 1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88205E18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88205EB0.s")

void func_88206430(void) { func_88200134(2, 2); func_88200134(3, 2); }

extern void func_88003A00(s32);
extern s32 D_88234564;
void func_88206460(void) {
    func_88003A00(D_88234564 + 0x88);
    func_88003A00(D_88234564 + 0xCC);
    func_88003A00(D_88234564 + 0x44);
    func_88003A00(D_88234564);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_882064B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206508.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_8820659C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206668.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206714.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206C2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206CC0.s")

extern void func_80006F70(s32 *, s32, s32, s32, s32);
s32 func_880032C4();
extern void func_882001E8();
extern u8 D_800D0510;

void func_88207D14(u8 *arg0) {
    if (*arg0 != 0) {
        func_80006F70(&D_800D0510, 0x2C, 0x48, 0x229, 0x17F);
        func_882001E8();
        if (func_880032C4() == 0) {
            *arg0 -= 1;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88207D80.s")
#endif
