#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0D330.s")

extern s16 D_8AB17238; void func_8AB0D4A4(void) { D_8AB17238 += 1; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0D4BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0D5F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0DFC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E0F4.s")

extern void func_8AB0E21C(s32);
void func_8AB0E1FC(void) { func_8AB0E21C(0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E21C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E280.s")

extern void StageFade_StartFromTransparent(s32 arg0);
extern s32 StageContext_GetFadeMode(void);
s32 func_8AB0E2EC(s32 arg0) {
    s32 result = 0x23;
    switch (arg0) {
    case 0:
        StageFade_StartFromTransparent(5);
        break;
    case 1:
        if (StageContext_GetFadeMode() == 1) {
            result = 0;
        }
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E350.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E4BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E684.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E8B4.s")

void func_8AB0E9D8(u8 *arg0) {
    *(s32 *)(arg0 + 0xC) = 1;
    *(s16 *)(arg0 + 0x10) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E9E8.s")

extern u8 D_8AB12CB0[];
extern u8 *D_8AB11D0C;
extern s16 D_8AB1721C;
extern s32 func_8AB0F518(s32 arg0);
s32 func_8AB0EED8(s32 arg0) {
    s32 result = arg0;
    s32 i = 0;
    u8 *ptr = D_8AB12CB0;
    for (i = 0; i < 4; i++, ptr += 0x94) {
        if (*(s16 *)(ptr + 2) == 1) {
            D_8AB1721C = i;
            D_8AB11D0C[0xF] = i;
            result = func_8AB0F518(0);
            break;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0EF44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0F0A8.s")

extern u8 *D_8AB17190[];
void func_8AB0F29C(u8 *arg0, s32 arg1) {
    if (*(s32 *)(arg0 + 0xC) == 1) {
        *(s16 *)(arg0 + 0x10) -= 1;
        if (*(s16 *)(arg0 + 0x10) > 0) {
            return;
        }
        *(s16 *)(arg0 + 0x10) = 0;
        *(s32 *)(arg0 + 0xC) = 0;
        *(u16 *)(D_8AB17190[arg1] + 2) &= 0xFFFD;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0F2F0.s")

extern void func_8AB01FBC(void);
extern void func_8AB03ED4(void);
extern void func_8AB012A4(void);
extern s32 func_8AB0E684(s32);
extern s16 D_8AB17246;
s32 func_8AB0F484(s32 arg0) {
    s32 result = 0x2B;
    s16 *counter = &D_8AB17246;
    switch (arg0) {
    case 0:
        *counter = 0;
        func_8AB01FBC();
        break;
    case 1:
        *counter += 1;
        func_8AB03ED4();
        if (*counter >= 0xB) {
            func_8AB012A4();
            result = func_8AB0E684(0);
        }
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0F518.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0F5F8.s")
#endif
