#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818014C0.s")

f64 func_818014C0(f64, f64);

f32 func_81801748(void *arg0) {
    return (f32) func_818014C0((f64) (*(s16 *)((u8 *)(arg0) + (2))), (f64) (*(s16 *)((u8 *)(arg0) + (0))));
}

extern u8 *D_81805930;
extern u8 D_81805CE8[];
void func_81801780(void) {
    D_81805930 = D_81805CE8;
}

extern u8 D_81805CE0[];
void func_81801794(void) {
    D_81805930 = D_81805CE0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818017A8.s")

void func_81801810(u8 *arg0, s32 arg1, s32 arg2) {
    *(u16 *)arg0 = (u16)arg1;
    *(u16 *)(arg0 + 2) = (u16)arg2;
}

f32 func_8180181C(void *arg0) {
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = (*(s16 *)((u8 *)(arg0) + (0)));
    temp_v1 = (*(s16 *)((u8 *)(arg0) + (2)));
    return sqrtf((f32) ((temp_v0 * temp_v0) + (temp_v1 * temp_v1)));
}

void func_81801854(u8 *arg0, u8 *arg1, u8 *arg2) {
    *(s16 *)(arg0 + 0) = *(s16 *)(arg2 + 0) + *(s16 *)(arg1 + 0);
    *(s16 *)(arg0 + 2) = *(s16 *)(arg2 + 2) + *(s16 *)(arg1 + 2);
}

void func_81801878(u8 *arg0, u8 *arg1, u8 *arg2) { *(s16 *)(arg0 + 0) = *(s16 *)(arg1 + 0) - *(s16 *)(arg2 + 0); *(s16 *)(arg0 + 2) = *(s16 *)(arg1 + 2) - *(s16 *)(arg2 + 2); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_8180189C.s")

extern void func_8180194C(u8 *, u8 *, u8 *, f32);
void func_8180194C(u8 *arg0, u8 *arg1, u8 *arg2, f32 arg3) {
    *(s16 *)(arg0 + 0) = (s16)(*(s16 *)(arg1 + 0) +
        (*(s16 *)(arg2 + 0) - *(s16 *)(arg1 + 0)) * arg3);
    *(s16 *)(arg0 + 2) = (s16)(*(s16 *)(arg1 + 2) +
        (*(s16 *)(arg2 + 2) - *(s16 *)(arg1 + 2)) * arg3);
}

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

s32 func_81801C30(u8 *arg0, u8 *arg1) {
    return (*(s16 *)(arg0 + 0) + *(s16 *)(arg0 + 4) < *(s16 *)(arg1 + 0))
        || (*(s16 *)(arg1 + 0) + *(s16 *)(arg1 + 4) < *(s16 *)(arg0 + 0))
        || (*(s16 *)(arg0 + 2) + *(s16 *)(arg0 + 6) < *(s16 *)(arg1 + 2))
        || (*(s16 *)(arg1 + 2) + *(s16 *)(arg1 + 6) < *(s16 *)(arg0 + 2));
}

s32 func_81801C90(u8 *arg0) {
    return !func_81801C30(arg0, D_81805930);
}

extern void func_8180194C(u8 *, u8 *, u8 *, f32);
void func_81801CB8(u8 *arg0, u8 *arg1, u8 *arg2, f32 arg3) {
    func_8180194C(arg0, arg1, arg2, arg3);
    func_8180194C(arg0 + 4, arg1 + 4, arg2 + 4, arg3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801D04.s")

extern void func_81801D04(u8 *);
void func_81801E3C(u8 *arg0, u8 *arg1) { u8 sp18[8]; func_81801A28(sp18, arg0, arg1); func_81801D04(sp18); }

s32 func_81801E70(u8 *arg0, u8 *arg1) {
    return func_818019B8(arg0, arg1) && func_818019B8(arg0 + 4, arg1 + 4);
}

void func_81801EB8(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801EC0.s")

void func_81801F04(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) { *(u16 *)(arg0 + 0) = arg1; *(u16 *)(arg0 + 2) = arg2; *(u16 *)(arg0 + 4) = arg3; *(u16 *)(arg0 + 6) = arg4; }

void func_81801F1C(u8 *arg0, u8 *arg1, u8 *arg2) {
    *(s16 *)(arg0 + 0) = *(s16 *)(arg2 + 0) + *(s16 *)(arg1 + 0);
    *(s16 *)(arg0 + 2) = *(s16 *)(arg2 + 2) + *(s16 *)(arg1 + 2);
    *(s16 *)(arg0 + 4) = *(s16 *)(arg2 + 4) + *(s16 *)(arg1 + 4);
    *(s16 *)(arg0 + 6) = *(s16 *)(arg2 + 6) + *(s16 *)(arg1 + 6);
}

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

extern void func_81802438(s32, s32);
extern void func_81802208(s32, s32);
extern void func_81802308(s32);
extern void func_818024B0(s32, s32);
void func_81802BAC(s32 arg0, s32 arg1) { func_81802438(arg0, arg1); func_81802208(arg0, arg1); func_81802308(arg0); func_818024B0(arg0, arg1); }

s32 func_81802BF0(s32 arg0) {
    s32 count = 0;
    while (arg0 >= 2) {
        arg0 >>= 1;
        count++;
    }
    return count;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802C14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802CA8.s")

void func_81802D98(void *arg0) {
    func_8004C8C0((s32) (*(s16 *)((u8 *)(arg0) + (0x30))));
    func_8004C8C0((s32) (*(s16 *)((u8 *)(arg0) + (0))));
}

void func_81802DC8(u8 *arg0) {
    func_8004C8C0(*(s16 *)arg0);
}

extern void func_8004C8C0(s32);
void func_81802DE8(u8 *arg0) {
    u8 *ptr = arg0;
    s16 v0 = *(s16 *)ptr;
    while (v0 >= 0) {
        func_8004C8C0(v0);
        ptr += 0x20;
        v0 = *(s16 *)ptr;
    }
}

void func_81802E34(u8 *arg0) {
    func_8004C4B0(*(s16 *)arg0);
}

extern void func_8004C4B0(s32);
void func_81802E54(u8 *arg0) {
    u8 *ptr = arg0;
    s16 v0 = *(s16 *)ptr;
    while (v0 >= 0) {
        func_8004C4B0(v0);
        ptr += 0x20;
        v0 = *(s16 *)ptr;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802EA0.s")

void func_8004989C(s32 arg0);
void func_800496A4(s32 a0, s32 a1);
void func_8180351C(void *arg0) {
    func_8004989C((s32) (*(s8 *)((u8 *)(arg0) + (6))));
    func_800496A4((s32) (*(s8 *)((u8 *)(arg0) + (4))), (*(s8 *)((u8 *)(arg0) + (5))) + 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803558.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803668.s")

extern void func_800498C4();
extern void func_81803558(s32, s32, s32, s32);
extern void func_800499EC();
void func_818036D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { func_800498C4(); func_81803558(arg0, arg1, arg2, arg3); func_800499EC(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803720.s")

void func_818037A0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    if (*(s16 *)(arg0 + 4) <= 0) *(s16 *)(arg0 + 4) = (s16)arg2;
    if (*(s16 *)(arg0 + 6) <= 0) *(s16 *)(arg0 + 6) = (s16)arg3;
    if (*(s16 *)(arg1 + 0) < 0) *(s16 *)(arg1 + 0) = *(s16 *)(arg0 + 0) % arg2;
    if (*(s16 *)(arg1 + 2) < 0) *(s16 *)(arg1 + 2) = *(s16 *)(arg0 + 2) % arg3;
    if (*(s16 *)(arg1 + 4) < 0) *(s16 *)(arg1 + 4) = (s16)arg2;
    if (*(s16 *)(arg1 + 6) < 0) *(s16 *)(arg1 + 6) = (s16)arg3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803868.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803964.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803A74.s")

s32 func_81803AE4(u16 arg0) {
    if (arg0 & 0x8000)
        return 1;
    if (arg0 & 0x4000)
        return -1;
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803B18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803BB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803BE8.s")

extern u8 *func_81803BB8();
extern s32 func_81803BE8();
s32 func_81803C14(s32 arg0, s32 arg1) {
    s32 mask;
    u8 *value;

    mask = func_81803BE8(arg0, arg1);
    value = func_81803BB8(arg0, arg1);
    if (value == 0) return 0;
    if (mask == 0) return 0;
    if (*value >= 0x21) return 0;
    return ((1 << (*value + 0x1F)) & mask) != 0;
}

void func_81803C9C(void *arg0)
{
  u8 *temp_v0;
  temp_v0 = func_81803BB8();
  if ((*((s32 *) (((u8 *) arg0) + 0))) != 0)
  {
    *temp_v0 = *((u8 *) (((u8 *) arg0) + 5));
    if (arg0)
    {
    }
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803CD4.s")

extern f32 func_81803CD4(f32);

void func_81803D44(f32 arg0, f32 arg1) {
    func_81803CD4(func_81803CD4(arg1) - func_81803CD4(arg0));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81804088.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818042E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81804534.s")
#endif
