#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220B850.s")

extern void _bzero(s32 *, s32);
extern void func_8004C8C0(s32);
extern u8 D_82210B60;

void func_8220B900(void) {
    func_8004C8C0(0x9F);
    _bzero(&D_82210B60, 0xC4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220B930.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220B984.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220BC40.s")

extern s32 func_8220BC40(void);
s32 func_8220BC7C(s32 arg0, s32 arg1) {
    s32 result;
    s32 temp_v0;
    u8 *temp_v1;
    result = 0;
    temp_v0 = func_8220BC40();
    if (temp_v0 != -1) {
        temp_v1 = (u8 *)(&D_82210B60) + (temp_v0 * 0x18);
        *(s16 *)(temp_v1 + 4) = 1;
        *(s16 *)(temp_v1 + 6) = 0;
        *(s16 *)(temp_v1 + 8) = 0;
        *(s32 *)(temp_v1 + 0xC) = 0;
        result = 1;
        *(s16 *)(temp_v1 + 0x10) = arg0;
        *(f32 *)(temp_v1 + 0x14) = 0.0f;
        *(f32 *)(temp_v1 + 0x18) = 0.0f;
        *(s16 *)(temp_v1 + 0x12) = arg1;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220BD00.s")

extern s16 D_82210C36;
void func_8220BD90(s16 *arg0) {
    arg0[1] = 1;
    arg0[2] = 0;
    D_82210C36 = arg0[0];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220BDAC.s")

void func_8220BE84(s16 *arg0) {
    arg0[1] = 3;
    arg0[2] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220BE94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220BF68.s")

extern void func_8220BD90(s16 *);
extern void func_800226C0(s32);
void func_8220C030(void *arg0) {
    s16 temp_v0;
    temp_v0 = *(s16 *)((u8 *)arg0 + 0x16);
    switch (temp_v0) {
    case 0:
        func_8220BD90((s16 *)((u8 *)arg0 + 0x14));
        func_800226C0(0xA9);
        break;
    case 2:
        *(s16 *)((u8 *)arg0 + 2) = 2;
        *(s16 *)((u8 *)arg0 + 4) = 0;
        break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220C08C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220C1C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220C340.s")

void func_8220C42C(u8 *arg0, u8 *arg1, s16 *arg2) {
    if (*arg2 == 1) {
        arg0[0] = 0xDC;
        arg0[1] = 0x96;
        arg0[2] = 0x96;
    } else {
        arg0[0] = 0xFF;
        arg0[1] = 0xFF;
        arg0[2] = 0xFF;
    }
    arg1[0] = 0;
    arg1[1] = 0;
    arg1[2] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220C470.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220C6C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220CB34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220CE10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220CF9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220D3C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220D560.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220D630.s")

extern s16 D_82210C38;
s32 func_8220D670(void) { s32 result = D_82210C38; return result; }

extern s16 D_82210C30;
extern s16 D_82210C32;
s32 func_8220D67C(void) {
    s32 result = 0;
    if (D_82210C30 != 0) {
        if (D_82210C32 != 0) result = 1;
    }
    return result;
}

s32 func_8220D6AC(void) {
    s32 result = 0;
    if ((D_82210C30 != 0) && ((D_82210C32 == 2) || (D_82210C32 == 3))) {
        result = 1;
    }
    return result;
}
#endif
