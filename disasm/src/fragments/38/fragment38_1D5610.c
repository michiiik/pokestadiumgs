#include "global.h"


#ifdef VERSION_US
extern u8 *D_88904190;
u8 *fragment38_main(void) {
    return D_88904190 + 0x6C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900030.s")

extern void Util_Free(void *arg0);
extern void main_pool_pop_state(s32 arg0);
void func_88900494(void) {
    Util_Free(D_88904190);
    main_pool_pop_state(0x45564F56);
}

extern s32 func_880007B0(s32);
s32 func_889004C4(void) {
    s32 result;
    s32 zero;

    result = 0;
    if (*(s32 *)(D_88904190 + 0x11C) != 0) {
        zero = 0;
        result = zero;
        if (func_880007B0(*(s32 *)(D_88904190 + 0x68)) != 0) {
            if (*(u8 *)(D_88904190 + 0x13C) >= 0xA6) {
                result = 1;
            }
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900528.s")

extern s32 func_80001FF0(void);
void func_8890055C(void) {
    *(s32 *)(D_88904190 + 0x120) = 0;
    *(s32 *)(D_88904190 + 0x124) = 1;
    *(s16 *)(D_88904190 + 0x13E) = (s16)(u32)((f32)func_80001FF0() / 2);
}

extern s32 func_88902B70(s32);
extern s32 func_889004C4(void);
extern s32 func_80001FF0(void);
void func_88900638(void) {
    *(s32 *)(D_88904190 + 0x120) = 0;
    if ((func_88902B70(*(s32 *)(D_88904190 + 0x68)) != 4) &&
        (func_889004C4() == 0)) {
        *(s32 *)(D_88904190 + 0x124) = 6;
    } else {
        *(s32 *)(D_88904190 + 0x124) = 7;
    }
    *(s16 *)(D_88904190 + 0x13E) =
        (s16)(u32)((f32)func_80001FF0() / 2);
}

void func_88900754(void) {
    u8 *ptr = D_88904190;
    if (*(u32 *)(ptr + 0x44) != 0) {
        *(s32 *)(*(u8 **)(ptr + 0x48) + 0x2C) = 1;
    }
}

extern void Input_SetRepeatController(void *arg0);
extern void *D_80087200;
void func_8890077C(void) {
    Input_SetRepeatController(D_80087200);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_889007A0.s")

extern void func_889033FC(void *arg0, void *arg1);
void func_88900ADC(void) {
    func_889033FC(*(void **)(D_88904190 + 4), D_88904190 + 8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900B08.s")

void func_88900C54(void) {
    Input_SetRepeatController(D_80087200);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900C78.s")

extern void func_889035FC(void *arg0);
void func_88900D8C(void) {
    func_889035FC(D_88904190 + 0x48);
}

extern void func_889035A0(void *, u8 *, s16, s16);
extern s32 func_88004804(s32, s32, s16, s16, s32, s32, s32, s32, s32,
                          void (*)(void), void (*)(void), void (*)(void),
                          void *, s32, s32);
extern void func_88900C78(void);
extern void func_88900D8C(void);
extern void func_88900C54(void);
extern u8 D_88000E4C;
extern u8 D_8800ED50[];
void func_88900DB4(void) {
    s32 result;

    func_889035A0(D_88904190 + 0x48, *(u8 **)(D_88904190 + 0x68),
                  *(s8 *)(D_88904190 + 0x12D), *(s8 *)(D_88904190 + 0x12E));
    result = func_88004804(
        0, 3,
        (s16)(*(s8 *)(D_88904190 + 0x12D) + 0x153),
        (s16)(*(s8 *)(D_88904190 + 0x12E) + 0x98),
        0, 1,
        *(u8 *)(D_88904190 + 0x129),
        *(u8 *)(D_88904190 + 0x12A),
        *(u8 *)(D_88904190 + 0x12B),
        func_88900C78, func_88900D8C, func_88900C54, &D_88000E4C, 1, 1);
    *(u8 **)(D_88904190 + 0x48) = D_8800ED50 + result * 0x4C;
    *(s16 *)(*(u8 **)(D_88904190 + 0x48) + 0x10) = 0xBE;
    *(s16 *)(*(u8 **)(D_88904190 + 0x48) + 0x12) = 0xC5;
    *(u8 *)(D_88904190 + 0x12C) = 3;
}

extern void func_800226C0(s32);
extern void func_8002602C(void);
extern void func_88004990(u8, s32);
void func_88900EE4(void) {
    func_800226C0(*(s32 *)(D_88904190 + 0x148));
    func_8002602C();
    func_88004990(*(u8 *)(*(u8 **)(D_88904190 + 0x0)), 0);
    *(s32 *)(*(u8 **)(D_88904190 + 0x0) + 0x34) = 1;
    ((void (*)(void))(u32)*(u32 *)(D_88904190 + 0x130))();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900F54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88901A24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88902624.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_889027A4.s")
#endif
