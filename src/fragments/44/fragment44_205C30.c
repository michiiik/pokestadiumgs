#include "global.h"


#ifdef VERSION_US
/* mkdraft:func_8AF179C0 begin */
extern void func_800504BC(s16 *);
extern void func_8AC015B0(s16, s16, s32, s32, s16);
extern u8 *D_8AF35000;
extern s16 D_8AF27430;
extern s16 D_8AF35008;

s32 func_8AF179C0(s32 mode, void *record) {
    s16 x;
    s16 y;
    void *preserved;
    s16 values[2];

    preserved = record;
    switch (mode) {
    case 0:
        *(u16 *)((u8 *)preserved + 2) &= 0xFFFD;
        break;
    case 1:
        func_800504BC(values);
        x = *(s16 *)((u8 *)preserved + 8) + values[0];
        y = *(s16 *)((u8 *)preserved + 0xA) + values[1];
        func_8AC015B0(x, y, (s32)D_8AF35000, D_8AF27430, D_8AF35008);
        break;
    }
    return 0;
}
/* mkdraft:func_8AF179C0 end */

/* mkdraft:func_8AF17A5C begin */
extern void func_800504BC(s16 *);
extern void func_8AC015B0(s16, s16, s32, s32, s16);
extern u8 *D_8AF35004;
extern s16 D_8AF27434;
extern s16 D_8AF3500A;

s32 func_8AF17A5C(s32 mode, void *record) {
    s16 x;
    s16 y;
    void *preserved;
    s16 values[2];

    preserved = record;
    switch (mode) {
    case 0:
        *(u16 *)((u8 *)preserved + 2) &= 0xFFFD;
        break;
    case 1:
        func_800504BC(values);
        x = *(s16 *)((u8 *)preserved + 8) + values[0];
        y = *(s16 *)((u8 *)preserved + 0xA) + values[1];
        func_8AC015B0(x, y, (s32)D_8AF35004, D_8AF27434, D_8AF3500A);
        break;
    }
    return 0;
}
/* mkdraft:func_8AF17A5C end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF17AF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF17BA8.s")

void func_8AF17F0C(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x28) = arg1;
    *(s32 *)(arg0 + 0x2C) = arg2;
}

extern s16 D_8AF3500C;
extern s16 D_8AF34FAC;
extern s16 D_8AF34FAE;
#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

extern u8 *D_8AF34FB0;
extern u8 *D_8AF34FB4;
extern u8 *D_8AF34FE0;
extern u8 *D_8AF34FE4;
extern u8 *D_8AF34FE8;
extern u8 *D_8AF34FEC;

void func_8AF17F18(void) {
    M2C_FIELD(D_8AF34FB0, u16 *, 2) = (u16) (M2C_FIELD(D_8AF34FB0, u16 *, 2) & 0xFFFE);
    M2C_FIELD(D_8AF34FB4, u16 *, 2) = (u16) (M2C_FIELD(D_8AF34FB4, u16 *, 2) & 0xFFFE);
    func_8AF17F0C(D_8AF34FE0, -0x3C5FA501, -0x1E3C7301);
    func_8AF17F0C(D_8AF34FE4, -0x3C5FA501, -0x1E3C7301);
    func_8AF17F0C(D_8AF34FE8, -0x3C5FA501, -0x1E3C7301);
    func_8AF17F0C(D_8AF34FEC, -0x3C5FA501, -0x1E3C7301);
    switch (D_8AF3500C) {                           /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        switch (D_8AF34FAC) {                       /* switch 2; irregular */
        case 2:                                     /* switch 2 */
            M2C_FIELD(D_8AF34FB0, u16 *, 2) = (u16) (M2C_FIELD(D_8AF34FB0, u16 *, 2) | 1);
            func_8AF17F0C(D_8AF34FE8, -0xFF01, -0xFF01);
            return;
        case 3:                                     /* switch 2 */
            M2C_FIELD(D_8AF34FB4, u16 *, 2) = (u16) (M2C_FIELD(D_8AF34FB4, u16 *, 2) | 1);
            func_8AF17F0C(D_8AF34FEC, -0xFF01, -0xFF01);
            return;
        }
        break;
    case 7:                                         /* switch 1 */
        switch (D_8AF34FAE) {                       /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            M2C_FIELD(D_8AF34FB0, u16 *, 2) = (u16) (M2C_FIELD(D_8AF34FB0, u16 *, 2) | 1);
            func_8AF17F0C(D_8AF34FE0, -0xFF01, -0xFF01);
            return;
        case 1:                                     /* switch 3 */
            M2C_FIELD(D_8AF34FB4, u16 *, 2) = (u16) (M2C_FIELD(D_8AF34FB4, u16 *, 2) | 1);
            func_8AF17F0C(D_8AF34FE4, -0xFF01, -0xFF01);
            return;
        }
        break;
    }
}
extern s16 D_8AF34FAC;
extern s16 D_8AF34FAE;
extern s16 D_8AF34FFC;
extern s16 D_8AF35008;
extern s16 D_8AF3500A;
extern s16 D_8AF3500C;

void func_8AF180F4(void) {
    D_8AF3500C = 0;
    D_8AF34FAC = 2;
    D_8AF34FAE = 0;
    D_8AF34FFC = 0;
    D_8AF35008 = 0;
    D_8AF3500A = 0;
}

extern u8 *D_8AF34F70;
extern u8 *D_8AF34F74;
extern f32 D_8AF29B24;
extern f32 D_8AF29B28;

void func_8AF1812C(void) {
    f32 first = D_8AF29B24;
    f32 second = D_8AF29B28;
    *(f32 *)(D_8AF34F70 + 0x40) = first;
    *(f32 *)(D_8AF34F70 + 0x44) = first;
    *(f32 *)(D_8AF34F74 + 0x40) = second;
    *(f32 *)(D_8AF34F74 + 0x44) = second;
    *(f32 *)(D_8AF34F70 + 0x48) = 120.0f;
    *(f32 *)(D_8AF34F70 + 0x4C) = 180.0f;
}

extern u8 *D_8AF34F78;
extern u8 *D_8AF34F7C;
extern f32 D_8AF29B2C;
extern f32 D_8AF29B30;

void func_8AF18190(void) {
    f32 first = D_8AF29B2C;
    f32 second = D_8AF29B30;
    *(f32 *)(D_8AF34F78 + 0x40) = first;
    *(f32 *)(D_8AF34F78 + 0x44) = first;
    *(f32 *)(D_8AF34F7C + 0x40) = second;
    *(f32 *)(D_8AF34F7C + 0x44) = second;
    *(f32 *)(D_8AF34F78 + 0x48) = 120.0f;
    *(f32 *)(D_8AF34F78 + 0x4C) = 260.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF181F4.s")

void func_8AF18808(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (arg1 < value) {
        value -= arg2;
        if (value < arg1) value = arg1;
        *arg0 = value;
    }
}

void func_8AF18848(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (value < arg1) {
        value += arg2;
        if (arg1 < value) value = arg1;
        *arg0 = value;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF18888.s")

extern void func_800498C4(void);
extern void func_800499EC(void);
void func_8AF19850(void) {
    func_800498C4();
    func_800499EC();
}
#pragma C_FUNCTION_PADDING(8)
#endif
