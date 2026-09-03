#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C01730.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C0177C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C017D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C0182C.s")

void func_87C01888(void *arg0, s32 arg1, s32 arg2) {
    (*(s32 *)((u8 *)(arg0) + (0))) = arg1;
    (*(s32 *)((u8 *)(arg0) + (4))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x14))) = -1;
    (*(s16 *)((u8 *)(arg0) + (0x16))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x18))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x1C))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x20))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x24))) = arg2;
    (*(f32 *)((u8 *)(arg0) + (8))) = 0.0f;
    (*(f32 *)((u8 *)(arg0) + (0x10))) = 0.0f;
    (*(f32 *)((u8 *)(arg0) + (0xC))) = 1.0f;
}

s32 func_80001FF0();
s32 func_80008970();

f32 func_87C018C8(void) {
    s32 sp1C;

    sp1C = func_80008970();
    return ((f32) sp1C * 60.0f) / (f32) func_80001FF0();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C01910.s")

extern void func_87C01910(void *);
void func_87C019B0(u8 *arg0, s16 arg1) {
    *(s16 *)(arg0 + 0x14) = arg1;
    func_87C01910(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C019DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C01A90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C01CBC.s")

extern void func_87C019B0(u8 *arg0, s16 arg1);
void func_87C01DB8(u8 *arg0, s32 arg1, s32 arg2) {
    s32 original;

    original = arg1;
    if ((arg2 != 0) || (arg1 != *(s16 *)(arg0 + 0x14))) {
        *(f32 *)(arg0 + 8) = 0.0f;
    }
    func_87C019B0(arg0, (s16)arg1);
    *(s32 *)(arg0 + 4) = 0;
    if (original < 0) {
        *(s32 *)(arg0 + 0x1C) = 1;
    } else {
        *(s32 *)(arg0 + 0x1C) = 0;
    }
    *(s32 *)(arg0 + 0x18) = 0;
}

s16 func_87C01E28(u8 *arg0) {
    return *(s16 *)(arg0 + 0x14);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C01E30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C01E98.s")

void func_87C01F6C(u8 *arg0, f32 arg1) {
    *(f32 *)(arg0 + 0xC) = arg1;
}

f32 func_87C01F78(u8 *arg0) {
    return *(f32 *)(arg0 + 0xC);
}

extern u8 *func_87C01730(void);
s32 func_87C01F80(void) {
    u8 *state = func_87C01730();
    s32 result;
    if (state != NULL) {
        result = state[4];
    } else {
        result = 0;
    }
    return result;
}

s32 func_87C01FB0(void) {
    u8 *state = func_87C01730();
    s32 result;
    if (state != NULL) {
        result = state[5];
    } else {
        result = 0;
    }
    return result;
}

extern u8 *func_87C017D0(void);
s32 func_87C01FE0(void) {
    u8 *state = func_87C017D0();
    s32 result;
    if (state != NULL) {
        result = *(u16 *)(state + 0xA);
    } else {
        result = 0;
    }
    return result;
}

extern u8 *func_87C0182C(void);
s32 func_87C02010(void) {
    u8 *state = func_87C0182C();
    s32 result;
    if (state != NULL) {
        result = *(u16 *)(state + 0xA);
    } else {
        result = 0;
    }
    return result;
}

s32 func_87C02040(void) {
    u8 *state = func_87C017D0();
    return state ? ((*(s16 *)state) & 1) : 0;
}
#endif
