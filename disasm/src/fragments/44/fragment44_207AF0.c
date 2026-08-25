#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19880.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF198C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19908.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19970.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF199D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19A1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19AC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19B40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19BA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19BDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19CB0.s")

extern void func_8AF19CB0(s16, s32);

void func_8AF19E24(s16 arg0) {
    func_8AF19CB0(arg0, 6);
}

extern void func_8AF19CB0(s16, s32);

void func_8AF19E50(s16 arg0) {
    func_8AF19CB0(arg0, 0xC);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19E7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19FAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1A0DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1A1B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1A2B8.s")

extern void _bzero(s32 *, s32);
extern s16 D_8AF357AC;
extern s16 D_8AF357AE;
extern u8 D_8AF357C0;

void func_8AF1A72C(void) {
    D_8AF357AC = 0;
    D_8AF357AE = 0;
    _bzero(&D_8AF357C0, 0xE);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1A764.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1AE30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1B23C.s")

void func_8AF1B4D0(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x28) = arg1;
    *(s32 *)(arg0 + 0x2C) = arg2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1B4DC.s")

extern s16 D_8AF3720C;
void func_8AF1B5D4(void) {
    D_8AF3720C = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1B5E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1B770.s")

extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800499EC(void);
void func_8AF1B910(void) {
    func_800498C4();
    func_800496A4(0x10, 0);
    func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
    func_800499EC();
}
#endif
