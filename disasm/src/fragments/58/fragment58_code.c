#include "global.h"


#ifdef VERSION_US
s32 func_83400020(s32 arg0, s32 arg1) {
    return arg0 + arg1 / 2;
}

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
} Fragment58State;
extern Fragment58State D_83404888;
extern Fragment58State D_83403DCC;
extern s32 D_83403D68[];
extern s32 D_83403E08[];
extern s32 D_83404190;
void func_83400038(s32 arg0) {
    s32 temp_v0;
    if (arg0 == 3) {
        D_83404888.unk24 = 0xA;
        D_83404888.unk28 = 1;
    } else {
        D_83404190 = arg0;
        D_83404888.unk34 = -1;
    }
    D_83404888.unk20 = 0;
    temp_v0 = D_83404190 * 4;
    if (D_83403D68[D_83404190] == 4) {
        D_83404888 = D_83403DCC;
        D_83404888.unk18 = 1;
    }
    D_83404888.unk0C = D_83403E08[D_83404190];
    D_83404888.unk04 = func_83400020(D_83404888.unk0C, D_83404888.unk14);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_8340010C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_834006A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83400A64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83400AFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83400B98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83400EA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_8340135C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83401454.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_8340156C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83401904.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83401AAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83401E64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_834022F8.s")

extern void *D_800D0510;
extern s32 D_83404188;
extern s32 D_834041A4;
extern s32 D_834041CC;
extern s32 D_83404248;
extern u8 D_83404170;
extern void func_800088DC(void);
extern void GfxImage_FillCurrent(void *, u16);
extern void GeoRender_AdvanceFrameCounter(void);
extern void func_8003C6B8(s32);
extern void func_834022F8(void);
extern void func_8340156C(void);
extern void func_83401AAC(void);
extern void func_87F0DFB4(void *);
extern void func_80008648(void);
void func_8340295C(void) {
    func_800088DC();
    if (D_834041CC == 0) {
        GfxImage_FillCurrent(&D_800D0510, 1);
    }
    if (D_834041A4 == 0) {
        GeoRender_AdvanceFrameCounter();
    }
    func_8003C6B8(D_83404248);
    switch (D_83404188) {
    case 2:
        func_834022F8();
        break;
    case 6:
    default:
        break;
    }
    func_8340156C();
    if (D_834041A4 == 1) {
        func_83401AAC();
    }
    func_87F0DFB4(&D_83404170);
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83402A24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83402B10.s")

s32 func_8003C9B8(s32 *, s32, f32 *);
extern f32 D_834041D4;
extern u8 D_83404250;
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
void func_83402C80(void) {
    Vec3f_SetComponentsDuplicate(&D_834041D4, (*(f32 *)((u8 *)(&D_83404250) + (0x24))), (*(f32 *)((u8 *)(&D_83404250) + (0x28))), (*(f32 *)((u8 *)(&D_83404250) + (0x2C))));
    if (func_8003C9B8(&D_83404250, 0x64, &D_834041D4) == 0) {
        func_8003C9B8(&D_83404250, 9, &D_834041D4);
        return;
    }
    func_8003C9B8(&D_83404250, 0x64, &D_834041D4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83402D00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83402DA8.s")

extern u8 D_83404250;
extern s32 D_8340419C;
extern s32 D_834041A0;
extern s32 D_834041B0;
extern s32 D_8340424C;
extern s32 D_834047F0;
extern s32 ModelAnim_IsFinished(u8 *);
extern void func_80024480(s32, s32);
extern void func_8003F2C4(s32, u8 *, s32);
extern void func_8003F3BC(u8 *, s32);
extern void func_83400038(s32);
void func_83402F08(void) {
    if (ModelAnim_IsFinished(&D_83404250) == 1) {
        switch (D_834041B0) {
        case 0:
            func_80024480(D_834047F0, 4);
            func_8003F2C4(D_8340424C, &D_83404250, D_8340419C);
            func_8003F3BC(&D_83404250, D_834041A0);
            D_834041B0 = 1;
            return;
        case 1:
            func_83400038(0);
            func_8003F2C4(D_8340424C, &D_83404250, 0);
            func_8003F3BC(&D_83404250, 0);
            D_834041B0 = 2;
            break;
        case 2:
        default:
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83402FE8.s")

extern void func_80055948(s32);
extern void func_80054A24(s32, s32);
extern void func_800086A4(s32);
extern void func_800088A4(s32);
extern void func_80007AEC(s32);
extern void func_80064D28(void);
extern void func_8340295C(void);
extern s32 func_83402FE8(s32);
extern s32 D_834047F0;
void func_834034CC(void) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    var_s0 = 1;
    var_s1 = 1;
    func_80055948(3);
    if (D_834047F0 == 0x53) {
        var_s1 = 0;
    }
    func_80054A24(var_s1, 1);
    func_800086A4(2);
    func_800088A4(1);
    func_80007AEC(0x14);
    var_s1 = 8;
    do {
        func_80064D28();
        func_8340295C();
        temp_v0 = func_83402FE8(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != var_s1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83403560.s")
#endif
