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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_882241B8.s")
#endif
