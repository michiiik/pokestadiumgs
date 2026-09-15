#include "global.h"


#ifdef VERSION_US
extern void func_81304CE0(u8 *, u8 *);
extern void func_81609A90(u8 *, u8 *);
void func_81304BB0(u8 *arg0, s32 arg1) {
    u8 sp30[8];
    u8 sp28[8];
    f32 sp24;

    sp24 = *(f32 *)(arg0 + 0xC);
    *(f32 *)(arg0 + 0xC) = 0.0f;
    func_81304CE0(arg0, sp30);
    *(f32 *)(arg0 + 0xC) = 16.0f;
    func_81304CE0(arg0, sp28);
    if (arg1 != 0) {
        func_81609A90(sp30, sp28);
    } else {
        func_81609A90(sp28, sp30);
    }
    *(f32 *)(arg0 + 0xC) = sp24;
}

void func_81304C3C(u8 *arg0, s32 arg1, s32 arg2) {
    arg0[0x1A] = 0;
    *(s32 *)arg0 = arg1;
    arg0[0x19] = (u8)arg2;
    *(f32 *)(arg0 + 0x10) = 0.0f;
    *(f32 *)(arg0 + 0x0C) = 0.0f;
}

const u32 D_81312470[2] = {0x00220002, 0x00010000};

typedef struct {
    u8 unk[8];
} UnkStruct8_81304C58;

void func_81304C58(u8 *arg0, u8 *arg1) {
    if (arg1 == NULL) {
        *(s32 *)(arg0 + 0x14) = 0;
    } else {
        *(UnkStruct8_81304C58 *)(arg0 + 4) = *(UnkStruct8_81304C58 *)arg1;
    }
    switch (arg0[0x1A]) {
        case 0:
        case 5:
            *(f32 *)(arg0 + 0xC) = 0.0f;
        case 4:
            arg0[0x1A] = 1;
            arg0[0x18] = 0;
            break;
        case 1:
        case 2:
        case 3:
            break;
    }
    func_81304BB0(arg0, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FCD40/func_81304CE0.s")

s32 func_81304E14(u8 *arg0) {
    *(f32 *)(arg0 + 0xC) = 0.0f;
    return 0;
}

f32 func_816092FC(void);
s32 func_81304E24(u8 *arg0) {
    *(f32 *)(arg0 + 0xC) += func_816092FC();
    if (*(f32 *)(arg0 + 0xC) >= 16.0f) {
        *(f32 *)(arg0 + 0xC) = 16.0f;
        arg0[0x1A] = 2;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FCD40/func_81304E80.s")

extern s32 D_81311F40[];
extern s32 func_81311C70(s32, s32 *, u8, s32);
s32 func_8130500C(u8 *arg0) {
    s32 result;

    result = func_81311C70(*(s32 *)arg0 + 0x74, &D_81311F40, arg0[0x19], -1);
    *(f32 *)(arg0 + 0xC) = 16.0f;
    if (result == 0) {
        goto done;
    }
    arg0[0x1A] = 2;
done:
    return 1;
}

f32 func_816092FC(void);
s32 func_81305068(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (0xC))) = (f32) ((*(f32 *)((u8 *)(arg0) + (0xC))) - func_816092FC());
    if ((*(f32 *)((u8 *)(arg0) + (0xC))) <= 0.0f) {
        (*(f32 *)((u8 *)(arg0) + (0xC))) = 0.0f;
        (*(s8 *)((u8 *)(arg0) + (0x1A))) = 5;
    }
    return 1;
}

s32 func_813050C0(u8 *arg0) {
    *(f32 *)(arg0 + 0xC) = 0.0f;
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FCD40/func_813050D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FCD40/func_813051B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FCD40/func_813054F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FCD40/func_8130559C.s")
#endif
