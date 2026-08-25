#include "global.h"


#ifdef VERSION_US
extern void func_87F05FB0(s32, s32, s32, s32, s32);
extern s32 D_80094908;
void func_86408D00(s32 arg0, s32 arg1) {
    if (arg0 == 2) {
        func_87F05FB0(arg1 + 0x60, D_80094908 + 0x64, arg1 + 0x24, arg1 + 0x1E, arg1 + 0x30);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2871C0/func_86408D4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2871C0/func_86408F84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2871C0/func_8640912C.s")

extern void func_87F02684(void);
void func_86409240(void) {
    func_87F02684();
}

extern void func_87F0277C(void);
void func_86409260(void) {
    func_87F0277C();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2871C0/func_86409280.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2871C0/func_86409378.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2871C0/func_864094BC.s")
#endif
