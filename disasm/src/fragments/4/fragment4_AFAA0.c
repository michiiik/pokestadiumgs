#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818014C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801748.s")

extern u8 *D_81805930;
extern u8 D_81805CE8[];
void func_81801780(void) {
    D_81805930 = D_81805CE8;
}

extern u8 *D_81805930;
extern u8 D_81805CE0[];
void func_81801794(void) {
    D_81805930 = D_81805CE0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818017A8.s")

void func_81801810(u8 *arg0, s32 arg1, s32 arg2) {
    *(u16 *)arg0 = (u16)arg1;
    *(u16 *)(arg0 + 2) = (u16)arg2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_8180181C.s")

void func_81801854(u8 *arg0, u8 *arg1, u8 *arg2) {
    *(s16 *)(arg0 + 0) = *(s16 *)(arg2 + 0) + *(s16 *)(arg1 + 0);
    *(s16 *)(arg0 + 2) = *(s16 *)(arg2 + 2) + *(s16 *)(arg1 + 2);
}

void func_81801878(u8 *arg0, u8 *arg1, u8 *arg2) { *(s16 *)(arg0 + 0) = *(s16 *)(arg1 + 0) - *(s16 *)(arg2 + 0); *(s16 *)(arg0 + 2) = *(s16 *)(arg1 + 2) - *(s16 *)(arg2 + 2); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_8180189C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_8180194C.s")

s32 func_818019B8(u8 *arg0, u8 *arg1) {
    s32 result = *(s16 *)(arg1 + 0) == *(s16 *)(arg0 + 0);
    if (result) {
        result = *(s16 *)(arg1 + 2) == *(s16 *)(arg0 + 2);
    }
    return result;
}

void func_818019E8(u8 *arg0) {
    if (*(s16 *)(arg0 + 4) < 0) *(s16 *)(arg0 + 4) = 0;
    if (*(s16 *)(arg0 + 6) < 0) *(s16 *)(arg0 + 6) = 0;
}

void func_81801A10(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 value = arg4;
    *(u16 *)(arg0 + 4) = (u16)arg3;
    *(u16 *)(arg0 + 6) = (u16)value;
    *(u16 *)(arg0 + 0) = (u16)arg1;
    *(u16 *)(arg0 + 2) = (u16)arg2;
}

void func_81801A28(u8 *arg0, u8 *arg1, u8 *arg2) {
    *(s16 *)(arg0 + 0) = *(s16 *)(arg2 + 0) + *(s16 *)(arg1 + 0);
    *(s16 *)(arg0 + 2) = *(s16 *)(arg2 + 2) + *(s16 *)(arg1 + 2);
    *(s16 *)(arg0 + 4) = *(s16 *)(arg1 + 4) - *(s16 *)(arg2 + 0) - *(s16 *)(arg2 + 4);
    *(s16 *)(arg0 + 6) = *(s16 *)(arg1 + 6) - *(s16 *)(arg2 + 2) - *(s16 *)(arg2 + 6);
    func_818019E8(arg0);
}

s32 func_81801A94(s32 arg0, s32 arg1) {
    return arg1 < arg0 ? arg1 : arg0;
}

s32 func_81801AB0(s32 arg0, s32 arg1) {
    return arg0 < arg1 ? arg1 : arg0;
}

void func_81801ACC(u8 *arg0, u8 *arg1, u8 *arg2) {
    *(s16 *)(arg0 + 0) = func_81801AB0(*(s16 *)(arg1 + 0), *(s16 *)(arg2 + 0));
    *(s16 *)(arg0 + 2) = func_81801AB0(*(s16 *)(arg1 + 2), *(s16 *)(arg2 + 2));
    *(s16 *)(arg0 + 4) = func_81801A94(*(s16 *)(arg1 + 4) + *(s16 *)(arg1 + 0),
                                         *(s16 *)(arg2 + 4) + *(s16 *)(arg2 + 0))
                         - *(s16 *)(arg0 + 0);
    *(s16 *)(arg0 + 6) = func_81801A94(*(s16 *)(arg1 + 6) + *(s16 *)(arg1 + 2),
                                         *(s16 *)(arg2 + 6) + *(s16 *)(arg2 + 2))
                         - *(s16 *)(arg0 + 2);
    func_818019E8(arg0);
}

void func_81801B7C(u8 *arg0, u8 *arg1, u8 *arg2) {
    func_81801854(arg0, arg1, arg2);
    func_81801854(arg0 + 4, arg1 + 4, arg2 + 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801BC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801C30.s")

extern u8 *D_81805930;
s32 func_81801C90(u8 *arg0) {
    return !func_81801C30(arg0, D_81805930);
}

extern void func_8180194C(u8 *, u8 *, u8 *, f32);
void func_81801CB8(u8 *arg0, u8 *arg1, u8 *arg2, f32 arg3) {
    func_8180194C(arg0, arg1, arg2, arg3);
    func_8180194C(arg0 + 4, arg1 + 4, arg2 + 4, arg3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801D04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801E3C.s")

s32 func_81801E70(u8 *arg0, u8 *arg1) {
    return func_818019B8(arg0, arg1) && func_818019B8(arg0 + 4, arg1 + 4);
}

void func_81801EB8(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801EC0.s")

void func_81801F04(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) { *(u16 *)(arg0 + 0) = arg1; *(u16 *)(arg0 + 2) = arg2; *(u16 *)(arg0 + 4) = arg3; *(u16 *)(arg0 + 6) = arg4; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801F1C.s")

extern void func_8004C8C0(s32);
void func_81801F60(u8 *arg0) {
    func_8004C8C0(*(s16 *)arg0);
}

extern void func_8004C4B0(s32);
void func_81801F80(u8 *arg0) {
    func_8004C4B0(*(s16 *)arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801FA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801FE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802168.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818021B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802208.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802308.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802438.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818024B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802690.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802754.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802BAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802BF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802C14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802CA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802D98.s")

extern void func_8004C8C0(s32);
void func_81802DC8(u8 *arg0) {
    func_8004C8C0(*(s16 *)arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802DE8.s")

extern void func_8004C4B0(s32);
void func_81802E34(u8 *arg0) {
    func_8004C4B0(*(s16 *)arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802E54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802EA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_8180351C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803558.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803668.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818036D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803720.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818037A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803868.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803964.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803A74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803AE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803B18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803BB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803BE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803C14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803C9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803CD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803D44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81804088.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818042E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81804534.s")
#endif
