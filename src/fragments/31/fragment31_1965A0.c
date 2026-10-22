#include "global.h"


#ifdef VERSION_US
extern void Input_SetRepeatController(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_88223320(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void Util_Free(s32);
extern s32 D_880068B4;
extern s32 D_88234850;
void func_88223348(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B4 = 1;
    Util_Free(D_88234850);
}

extern void func_88004990(u8, s32);
void func_88223384(void) {
    func_88004990(*(*(u8 **)((u8 *)(D_88234850) + 0)), 0);
    D_880068B8 = 1;
}

extern void func_880022B4(s32, s32, s32);
void func_882233BC(s32 arg0) {
    (*(s32 *)((u8 *)(D_88234850) + (0x30))) = arg0;
    if (arg0 != 0) {
        func_880022B4(D_88234850 + 4, 0xF00, 0);
        return;
    }
    func_880022B4(D_88234850 + 4, 0xF00, 1);
}

/* mkdraft:func_88223418 begin */
extern void func_800226C0(s32);
extern s8 D_882338E0[];
#pragma REWRITE_FUNCTION_WORD(func_88223418, 0x48, 0x0304C821, 0x0098C821)
#pragma REWRITE_FUNCTION_WORD(func_88223418, 0xC4, 0x504F0005, 0x51E20005)

void func_88223418(void) {
    s8 selected;
    UNUSED s8 pad;
    u8 sp25;
    s32 index;

    selected = D_882338E0[*(s16 *)((s8 *)(u32)D_88234850 + 0xC)];
    sp25 = 0;
    Input_SetRepeatController(D_80087200);
    func_882233BC(1);
    if (selected != *(s8 *)((s8 *)(u32)D_88234850 + *(s16 *)((s8 *)(u32)D_88234850 + 0x34) + 0x36)) {
        func_800226C0(0x47);
        ((s8 *)(u32)D_88234850)[*(s16 *)((s8 *)(u32)D_88234850 + 0x34) + 0x36] = selected;
    } else {
        func_800226C0(0x48);
        ((s8 *)(u32)D_88234850)[*(s16 *)((s8 *)(u32)D_88234850 + 0x34) + 0x36] = -1;
        sp25 = 1;
    }
    for (index = 0; index < 2; index = (index + 1) & 0xFF) {
        if (selected == ((s8 *)(u32)D_88234850)[index + 0x36] && *(s16 *)((s8 *)(u32)D_88234850 + 0x34) != index) {
            ((s8 *)(u32)D_88234850)[index + 0x36] = -1;
        }
    }
    if (((s8 *)(u32)D_88234850)[0x36] != -1 && ((s8 *)(u32)D_88234850)[0x37] != -1) {
        *(s16 *)((s8 *)(u32)D_88234850 + 0x34) = 2;
        return;
    }
    if (sp25 == 0) {
        *(s16 *)((s8 *)(u32)D_88234850 + 0x34) = (s16)(*(s16 *)((s8 *)(u32)D_88234850 + 0x34) + 1);
    }
}
/* mkdraft:func_88223418 end */

/* mkdraft:func_88223554 begin */
extern s8 D_88234758[];
extern s8 D_8823475F[];

s32 func_88223554(void) {
    s8 *output;
    s32 result;
    s32 index;
    s8 value;
    s16 sentinel;

    result = 0;
    output = D_8823475F;
    sentinel = -1;
    for (index = 0; index < 2; index = (index + 1) & 0xFF) {
        D_88234758[index + 7] = sentinel;
    }
    for (index = 0; index < 2; index = (index + 1) & 0xFF) {
        value = ((s8 *)(u32)D_88234850)[index + 0x36];
        if (sentinel != value) {
            result = 1;
            *output++ = value;
        }
    }
    return result;
}
/* mkdraft:func_88223554 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_882235CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_88223850.s")

extern void *Util_Malloc(s32);
extern s32 func_88004804(s32, s32, s16, s16, s32, s32, s32, s32, s32,
                         void (*)(void), void (*)(void), void (*)(void),
                         void (*)(void), s32, s32);
extern void func_88001C6C(void *, u16, u8, s16, u8, s16, s16, s16, s16, s16, s32);
extern s32 func_80001FF0(void);
extern u8 D_8800ED50[];
extern void func_882235CC(void);
extern void func_88223850(void);

void func_882241B8(void) {
    s32 result;
    s32 index;
    s32 first_refresh_rate;

    D_88234850 = (s32)Util_Malloc(0x38);
    result = func_88004804(0, 3, 167, 146, 0, 1, 220, 220, 180,
                           func_882235CC, func_88223850, func_88223320,
                           func_88223348, 0, 0);
    *(void **)D_88234850 = D_8800ED50 + result * 0x4C;
    *(s16 *)(*(s32 *)D_88234850 + 0x10) = 253;
    *(s16 *)(*(s32 *)D_88234850 + 0x12) = 303;
    D_880068B4 = 0;
    *(s32 *)((u8 *)D_88234850 + 0x30) = 1;
    *(s16 *)((u8 *)D_88234850 + 0x34) = 0;
    for (index = 0; index < 2; index = (index + 1) & 0xFF) {
        ((s8 *)(u32)D_88234850)[index + 0x36] = D_88234758[index + 7];
    }
    first_refresh_rate = func_80001FF0();
    func_88001C6C((u8 *)D_88234850 + 4, 17, 9, 209, 23, 12,
                 (s32)(540.0f / (f32)first_refresh_rate + (0.0f < (540.0f / func_80001FF0()) ? 0.5f : -0.5f)),
                 41, 41, 12, 70);
}
/* Retail carries three zero words after the epilogue (882243B4-882243BC);
 * fragment31_1965A0.o .text must stay 0x10A0 bytes so fragment31_197640.o
 * keeps starting at 0x882243C0 (same class as fragment31_1A43F0.c). */
#pragma C_FUNCTION_PADDING(12)
#endif
