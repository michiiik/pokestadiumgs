#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F6BF0/func_8AF08980.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F6BF0/func_8AF08A1C.s")

extern void *D_8AF2CB38;
extern void *D_8AF2CB3C;
extern void *D_8AF2CB40;
extern void *D_8AF2CB44;
void func_8AF08AC0(void) {
    (*(u16 *)((u8 *)(D_8AF2CB38) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF2CB38) + (2))) & 0xFFFD);
    (*(u16 *)((u8 *)(D_8AF2CB40) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF2CB40) + (2))) & 0xFFFD);
    (*(u16 *)((u8 *)(D_8AF2CB3C) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF2CB3C) + (2))) & 0xFFFD);
    (*(u16 *)((u8 *)(D_8AF2CB44) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF2CB44) + (2))) & 0xFFFD);
}

void func_8AF08B14(void) {
    (*(u16 *)((u8 *)(D_8AF2CB38) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF2CB38) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF2CB40) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF2CB40) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF2CB3C) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF2CB3C) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF2CB44) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF2CB44) + (2))) | 2);
}

void func_8AF08B68(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x28) = arg1;
    *(s32 *)(arg0 + 0x2C) = arg2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F6BF0/func_8AF08B74.s")

extern s16 D_8AF2C9E0;
extern s16 D_8AF2C9E2;
extern s16 D_8AF2CB1C;
extern s16 D_8AF2CB74;

void func_8AF08C90(void) {
    D_8AF2CB74 = 0;
    D_8AF2C9E0 = 0;
    D_8AF2C9E2 = 0;
    D_8AF2CB1C = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F6BF0/func_8AF08CB4.s")

void func_8AF090B0(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (arg1 < value) {
        value -= arg2;
        if (value < arg1) value = arg1;
        *arg0 = value;
    }
}

void func_8AF090F0(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (value < arg1) {
        value += arg2;
        if (arg1 < value) value = arg1;
        *arg0 = value;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F6BF0/func_8AF09130.s")

extern void func_800498C4(void);
extern void func_800499EC(void);
void func_8AF09B2C(void) {
    func_800498C4();
    func_800499EC();
}
#pragma C_FUNCTION_PADDING(12)
#endif
