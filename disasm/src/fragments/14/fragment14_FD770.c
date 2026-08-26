#include "global.h"


#ifdef VERSION_US
s32 func_813055E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 result = (((arg3 + arg1) * 2) + arg2) - 1;
    return result >= 0 ? result : 0;
}

s32 func_8130560C(void *arg0, s32 arg1) {
    u8 *base = (u8 *)arg0;
    if (arg1 >= *(u16 *)(base + 0x50)) {
        return -1;
    }
    return *(u8 *)(base + arg1 + 0x10);
}

s32 func_81305634(void *arg0) {
    s32 temp_a1;

    temp_a1 = func_813055E0((s32) arg0, (s32) (*(s16 *)((u8 *)(arg0) + (0x7C))), (s32) (*(s16 *)((u8 *)(arg0) + (8))), (s32) (*(s16 *)((u8 *)(arg0) + (0xA))));
    if (((*(s16 *)((u8 *)(arg0) + (0x7C))) == 0) && ((*(s16 *)((u8 *)(arg0) + (8))) == 1) && ((*(s16 *)((u8 *)(arg0) + (0xA))) == 0)) {
        return -1;
    }
    return func_8130560C(arg0, temp_a1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_813056A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_8130571C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81305780.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81305A10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81305AD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81305BA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81305C54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81305FB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_813060C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306178.s")

void func_813061E8(u8 *arg0) {
    arg0[0x87] = 5;
    *(s16 *)(arg0 + 0x7E) = -2;
    *(f32 *)(arg0 + 0x78) = 4.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306208.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306264.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_813062C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_813063CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_813064E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_8130662C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306780.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_8130687C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_813068C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_813068FC.s")

f32 func_816092FC(void);
void func_81306954(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (0x78))) = (f32) ((*(f32 *)((u8 *)(arg0) + (0x78))) - func_816092FC());
    if ((*(f32 *)((u8 *)(arg0) + (0x78))) <= 0.0f) {
        (*(f32 *)((u8 *)(arg0) + (0x78))) = 0.0f;
        if ((*(s32 *)((u8 *)(arg0) + (0))) == 0) {
            (*(s8 *)((u8 *)(arg0) + (0x87))) = 0;
        }
    }
}

void func_813069B0(u8 *arg0) {
    *(f32 *)(arg0 + 0x78) = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_813069BC.s")

s16 func_81306B0C(void *arg0) {
    u8 temp_v0;

    temp_v0 = (*(u8 *)((u8 *)(arg0) + (0x87)));
    if ((temp_v0 == 0) || (temp_v0 == 5)) {
        (*(s16 *)((u8 *)(arg0) + (0x80))) = func_813055E0((s32) arg0, (s32) (*(s16 *)((u8 *)(arg0) + (0x7C))), (s32) (*(s16 *)((u8 *)(arg0) + (8))), (s32) (*(s16 *)((u8 *)(arg0) + (0xA))));
        return (*(s16 *)((u8 *)(arg0) + (0x7E)));
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306B64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306C18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306E90.s")
#endif
