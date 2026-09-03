#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0A950.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0B24C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0B3F4.s")

extern s32 func_8AB0B67C(s32);
void func_8AB0B52C(void) {
    func_8AB0B67C(0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0B54C.s")

extern s32 func_8AB0B54C(s32);
extern s32 func_80001FF0(void);
extern s16 D_8AB16F6C;
extern u32 D_8AB1268C;
s32 func_8AB0B5E0(s32 arg0) {
    if ((D_8AB16F6C >= 0) && (((u32) D_8AB1268C % (u32) (func_80001FF0() / 2)) == 0)) {
        D_8AB16F6C -= 1;
        if (D_8AB16F6C < 0) {
            D_8AB16F6C = 0;
        }
        arg0 = func_8AB0B54C(arg0);
    }
    return arg0;
}

extern void func_8AB04AE4(void);
extern s32 func_8AB0B7CC(s32);
extern s32 StageContext_GetFadeMode(void);
s32 func_8AB0B67C(s32 arg0) {
    s32 result = 0x2E;

    switch (arg0) {
    case 0:
        func_8AB04AE4();
        break;
    case 1:
        if (StageContext_GetFadeMode() == 0) {
            result = func_8AB0B7CC(0);
        }
        break;
    }
    return result;
}

extern s32 func_8AB0B74C(s32);
extern s16 D_8AB16F7E;
s32 func_8AB0B6E0(s32 arg0) {
    s32 result = 0x30;
    s16 *p;

    p = &D_8AB16F7E;
    switch (arg0) {
    case 0:
        *p = 0;
        break;
    case 1:
        if (*p >= 0xA) {
            func_8AB0B74C(0);
        }
        *p += 1;
        break;
    }
    return result;
}

extern void StageFade_StartFromTransparent(s32);
s32 StageContext_GetFadeMode();
extern void func_800225C4(s32);
s32 func_8002806C();

s32 func_8AB0B74C(s32 arg0) {
    s32 sp1C;

    sp1C = 0x2F;
    switch (arg0) {                                 /* irregular */
    case 0:
        StageFade_StartFromTransparent(5);
        if (func_8002806C() != 0x48) {
            func_800225C4(5);
        }
        break;
    case 1:
        if (StageContext_GetFadeMode() == 1) {
            sp1C = 0;
        }
        break;
    }
    return sp1C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0B7CC.s")

typedef struct {
    u8 pad[8];
    s16 x;
    s16 y;
} Fragment45B96CState;
extern s16 D_8AB16EC8;
extern void *D_8AB16F64;
extern s32 D_8AB16F78;
extern u8 D_8AB126A8[];
extern void func_87F005F0(f32, f32);
extern void func_87F006BC(void);
extern u32 func_87F006AC(void);
extern void func_8004C8A0(void *, s32, s32, s32);
extern void func_800225C4(s32);
extern void func_8AB00BA4();
extern void func_80021ED8(s32);
extern s32 func_8AB0BACC(s32);
extern void func_8003C6B8(s32);
s32 func_8AB0B96C(s32 arg0) {
    s32 result = 0x32;
    s16 temp_v0;

    switch (arg0) {
    case 0:
        func_87F005F0((f32)(*(s16 *)((u8 *)D_8AB16F64 + 8) - 0x140),
                      (f32)(0xF0 - *(s16 *)((u8 *)D_8AB16F64 + 0xA)));
        func_8004C8A0(D_8AB126A8, 0x100, 0x3A, 0x183);
        D_8AB16EC8 = 3;
        func_800225C4(0x5A);
        break;
    case 1:
        func_87F006BC();
        temp_v0 = func_87F006AC();
        switch (temp_v0) {
        case 1:
            func_8AB00BA4(0x64, D_8AB16EC8, 0);
            D_8AB16EC8 -= 1;
            break;
        case 2:
            func_8AB00BA4(0x64, D_8AB16EC8, 0);
            func_80021ED8(0x4C);
            D_8AB16EC8 -= 1;
            break;
        case 3:
            result = func_8AB0BACC(0);
            break;
        }
        break;
    case 2:
        func_8003C6B8(D_8AB16F78);
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0BACC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0BE4C.s")

void func_8AB0BF70(u8 *arg0) {
    *(s32 *)(arg0 + 0xC) = 1;
    *(s16 *)(arg0 + 0x10) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0BF80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0C414.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0C5CC.s")

void func_8AB0C7C0(void *arg0, s32 arg1) {
    if ((*(s32 *)((u8 *)(arg0) + (0xC))) == 1) {
        (*(s16 *)((u8 *)(arg0) + (0x10))) = (s16) ((*(s16 *)((u8 *)(arg0) + (0x10))) - 1);
        if ((*(s16 *)((u8 *)(arg0) + (0x10))) <= 0) {
            (*(s16 *)((u8 *)(arg0) + (0x10))) = 0;
            (*(s32 *)((u8 *)(arg0) + (0xC))) = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0C7FC.s")

s32 func_8AB0C9B0(void) {
    return 0x37;
}

extern void func_8AB01FBC(void);
extern void func_8AB03ED4(void);
extern void func_8AB012A4(void);
extern s32 func_8AB0BACC(s32);
extern s32 func_8AB0B5E0(s32);
extern s16 D_8AB16F92;
s32 func_8AB0C9B8(s32 arg0) {
    s32 result = 0x38;
    s16 *p;

    p = &D_8AB16F92;
    switch (arg0) {
    case 0:
        *p = 0;
        func_8AB01FBC();
        break;
    case 1:
        *p += 1;
        func_8AB03ED4();
        if (*p >= 0xB) {
            func_8AB012A4();
            result = func_8AB0BACC(0);
        }
        result = func_8AB0B5E0(result);
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0CA58.s")

extern void *D_8AB16E30;
extern void *D_8AB16E34;
extern void *D_8AB16E38;
extern u8 *D_8AB16E40;
extern u8 *D_8AB16E44;
extern u8 *D_8AB16E48;
extern s16 D_8AB16F96;
void func_8AB0CBCC(void) {
    (*(u16 *)((u8 *)(D_8AB16E30) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16E30) + (2))) & 0xFFFE);
    (*(u16 *)((u8 *)(D_8AB16E34) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16E34) + (2))) & 0xFFFE);
    (*(u16 *)((u8 *)(D_8AB16E38) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16E38) + (2))) & 0xFFFE);
    func_8AB00B98(D_8AB16E40, -1U);
    func_8AB00B98(D_8AB16E44, -1U);
    func_8AB00B98(D_8AB16E48, -1U);
    switch (D_8AB16F96) {                           /* irregular */
    case 0:
        (*(u16 *)((u8 *)(D_8AB16E30) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16E30) + (2))) | 1);
        func_8AB00B98(D_8AB16E40, 0xFFFF00FFU);
        return;
    case 1:
        (*(u16 *)((u8 *)(D_8AB16E34) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16E34) + (2))) | 1);
        func_8AB00B98(D_8AB16E44, 0xFFFF00FFU);
        return;
    case 2:
        (*(u16 *)((u8 *)(D_8AB16E38) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16E38) + (2))) | 1);
        func_8AB00B98(D_8AB16E48, 0xFFFF00FFU);
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0CD00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0D08C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0D20C.s")
#endif
