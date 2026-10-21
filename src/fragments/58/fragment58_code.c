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
extern void BgStage_DrawFrame(void);
extern void GfxImage_FillCurrent(void *, u16);
extern void GeoRender_AdvanceFrameCounter(void);
extern void Geo_RenderRootNode(s32);
extern void func_834022F8(void);
extern void func_8340156C(void);
extern void func_83401AAC(void);
extern void func_87F0DFB4(void *);
extern void func_80008648(void);
void func_8340295C(void) {
    BgStage_DrawFrame();
    if (D_834041CC == 0) {
        GfxImage_FillCurrent(&D_800D0510, 1);
    }
    if (D_834041A4 == 0) {
        GeoRender_AdvanceFrameCounter();
    }
    Geo_RenderRootNode(D_83404248);
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

extern f32 func_8004B888(s32);
extern void func_8003F1DC(void *);
extern void func_8003F114(u8 *, s16, s16, void *);
extern void func_8003F2C4(s32, s32, s32);
extern void func_8003F3BC(void *, s32);
extern void *D_83404164;
extern s32 D_834041B0;
extern s32 D_8340424C;
extern u8 D_83404250;
extern u8 D_83404688;
extern s32 D_834047F0;
extern s16 D_834047F2;
extern s32 D_83404800;

/* uopt colors the 300.0f constant before the 0x24/0x28 read-backs; the retail
 * allocation rotates the three fpu temps {f4, f6, f8} by one slot (300.0f in
 * f6, 0x28 read in f8, 0x24 read in f4). The six words below only rewrite the
 * ft register fields; the tail's f4/f6 reuse and the 0x53 block (f10/f16/f18)
 * already match. */
#pragma REWRITE_FUNCTION_WORD(func_83402B10, 0x90, 0x44812000, 0x44813000)
#pragma REWRITE_FUNCTION_WORD(func_83402B10, 0x9C, 0xE6040028, 0xE6060028)
#pragma REWRITE_FUNCTION_WORD(func_83402B10, 0xA0, 0xC6060028, 0xC6080028)
#pragma REWRITE_FUNCTION_WORD(func_83402B10, 0xA8, 0xC6080024, 0xC6040024)
#pragma REWRITE_FUNCTION_WORD(func_83402B10, 0xC0, 0xE6260028, 0xE6280028)
#pragma REWRITE_FUNCTION_WORD(func_83402B10, 0xC4, 0xE6280024, 0xE6240024)

/* mkdraft:func_83402B10 begin */
void func_83402B10(void) {
    f32 temp_fv0;

    D_834041B0 = 0;
    func_8003F1DC(&D_83404250);
    func_8003F114(&D_83404250, 0, D_834047F2,
                  **(s32 **)((u8 *)*(void **)((u8 *)D_8340424C + 0x38) + 8));
    func_8003F114(&D_83404688, 0, -1, (void *)D_83404800);
    *(u8 *)(&D_83404688 + 0x1D) = 0xFF;
    temp_fv0 = func_8004B888(*(s16 *)((u8 *)D_83404164 + 0x658));
    *(f32 *)(&D_83404688 + 0x2C) = 0.0f;
    *(f32 *)(&D_83404688 + 0x28) = 300.0f;
    *(f32 *)(&D_83404688 + 0x24) = *(f32 *)(&D_83404688 + 0x2C);
    *(f32 *)(&D_83404250 + 0x38) = temp_fv0;
    *(f32 *)(&D_83404250 + 0x34) = temp_fv0;
    *(f32 *)(&D_83404250 + 0x30) = temp_fv0;
    *(f32 *)(&D_83404250 + 0x2C) = *(f32 *)(&D_83404688 + 0x2C);
    *(f32 *)(&D_83404250 + 0x28) = *(f32 *)(&D_83404688 + 0x28);
    *(f32 *)(&D_83404250 + 0x24) = *(f32 *)(&D_83404688 + 0x24);
    if (D_834047F0 != 0x53) {
        *(volatile f32 *)(&D_83404688 + 0x28) = 150.0f;
        *(f32 *)(&D_83404688 + 0x28) = -150.0f;
        *(f32 *)(&D_83404250 + 0x28) = *(f32 *)(&D_83404688 + 0x28);
    }
    *(f32 *)(&D_83404688 + 0x38) = 0.0f;
    *(f32 *)(&D_83404688 + 0x34) = *(f32 *)(&D_83404688 + 0x38);
    *(f32 *)(&D_83404688 + 0x30) = *(f32 *)(&D_83404688 + 0x34);
    func_8003F2C4(D_8340424C, (s32)&D_83404250, 0);
    func_8003F3BC(&D_83404250, 0);
    *(u8 *)(&D_83404250 + 2) = *(u8 *)(&D_83404250 + 2) & 0xFFBF;
    *(s32 *)((u8 *)&D_83404188 + 0x14) = *(u8 *)((u8 *)*(void **)((u8 *)D_83404164 + 0x2D4) + 0x13B0);
    *(s32 *)((u8 *)&D_83404188 + 0x18) = *(s8 *)((u8 *)*(void **)((u8 *)D_83404164 + 0x2D4) + 0x13B1);
}
/* mkdraft:func_83402B10 end */

s32 GeoRender_FindAnchorPosition(s32 *, s32, f32 *);
extern f32 D_834041D4;
extern u8 D_83404250;
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
void func_83402C80(void) {
    Vec3f_SetComponentsDuplicate(&D_834041D4, (*(f32 *)((u8 *)(&D_83404250) + (0x24))), (*(f32 *)((u8 *)(&D_83404250) + (0x28))), (*(f32 *)((u8 *)(&D_83404250) + (0x2C))));
    if (GeoRender_FindAnchorPosition(&D_83404250, 0x64, &D_834041D4) == 0) {
        GeoRender_FindAnchorPosition(&D_83404250, 9, &D_834041D4);
        return;
    }
    GeoRender_FindAnchorPosition(&D_83404250, 0x64, &D_834041D4);
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
extern void ModelAnim_SetResourceAnimation(s32, u8 *, s32);
extern void ModelAnim_SetEventTrack(u8 *, s32);
extern void func_83400038(s32);
void func_83402F08(void) {
    if (ModelAnim_IsFinished(&D_83404250) == 1) {
        switch (D_834041B0) {
        case 0:
            func_80024480(D_834047F0, 4);
            ModelAnim_SetResourceAnimation(D_8340424C, &D_83404250, D_8340419C);
            ModelAnim_SetEventTrack(&D_83404250, D_834041A0);
            D_834041B0 = 1;
            return;
        case 1:
            func_83400038(0);
            ModelAnim_SetResourceAnimation(D_8340424C, &D_83404250, 0);
            ModelAnim_SetEventTrack(&D_83404250, 0);
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
extern void StageContext_SetClearColor(s32);
extern void StageFade_StartFromOpaque(s32);
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
    StageContext_SetClearColor(1);
    StageFade_StartFromOpaque(0x14);
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
