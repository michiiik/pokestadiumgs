#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D0510;
extern void func_80044270(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void Ui_DrawTexturedRect8x8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    s32 local0;
    s32 local1;
    local0 = (arg2 < 9) ? 0x400 : 0;
    local1 = (arg3 < 9) ? 0x400 : 0;
    gDPSetTextureImage(D_800D0510++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, arg4);
    gDPSetTile(D_800D0510++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPLoadSync(D_800D0510++);
    gDPLoadBlock(D_800D0510++, G_TX_LOADTILE, 0, 0, 0x3F, 0x400);
    gDPPipeSync(D_800D0510++);
    gDPSetTile(D_800D0510++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPSetTileSize(D_800D0510++, G_TX_RENDERTILE, 0, 0, 0x1C, 0x1C);
    func_80044270((s16)arg0, (s16)arg1, (s16)arg2, (s16)arg3, 0, 0, local0, local1, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004A174.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004A2E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004A44C.s")

extern Gfx *D_800D0510;
extern s32 StageContext_IsHighResolution(void);
extern u8 D_80094DE0[];
void func_8004A5B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(D_800D0510++, D_80094DE0);
    gDPSetFillColor(D_800D0510++, (arg4 << 16) | arg4);
    if (StageContext_IsHighResolution() != 0) {
        gDPFillRectangle(D_800D0510++, arg0 + 7, arg1 + 7, arg0 + arg2 - 8, arg1 + arg3 - 8);
    } else {
        gDPFillRectangle(D_800D0510++, arg0 + 3, arg1 + 3, arg0 + arg2 - 4, arg1 + arg3 - 4);
    }
}

extern Gfx *D_800D0510;
extern s32 StageContext_IsHighResolution(void);
extern u8 D_80094DE0[];
void func_8004A708(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(D_800D0510++, D_80094DE0);
    gDPSetFillColor(D_800D0510++, (arg4 << 16) | arg4);
    if (StageContext_IsHighResolution() != 0) {
        gDPFillRectangle(D_800D0510++, arg0 + 5, arg1 + 5, arg0 + arg2 - 6, arg1 + arg3 - 6);
    } else {
        gDPFillRectangle(D_800D0510++, arg0 + 3, arg1 + 3, arg0 + arg2 - 4, arg1 + arg3 - 4);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004A858.s")

extern Gfx *D_800D0510;
extern s32 StageContext_IsHighResolution(void);
extern void func_8004A174(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8004A44C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8004A5B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4);
extern u8 D_80094E38[];
extern u8 D_80094F50[];
void func_8004AC24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    if (StageContext_IsHighResolution() != 0) {
        func_8004A174(arg0, arg1, arg2, arg3);
    } else {
        func_8004A44C(arg0, arg1, arg2, arg3);
    }
    if (arg2 >= 15 && arg3 >= 15) {
        func_8004A5B8(arg0, arg1, arg2, arg3, arg4);
    }
    gSPDisplayList(D_800D0510++, D_80094F50);
}

extern Gfx *D_800D0510;
extern s32 StageContext_IsHighResolution(void);
extern void func_8004A858(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern void func_8004A174(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8004A44C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_80094E38[];
extern u8 D_80094F50[];
void func_8004AD00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg2 >= 15 && arg3 >= 15) {
        if (StageContext_IsHighResolution() != 0) {
            func_8004A858(arg0 + 6, arg1 + 6, arg2 - 12, arg3 - 12, arg4, arg5);
        } else {
            func_8004A858(arg0 + 2, arg1 + 2, arg2 - 4, arg3 - 4, arg4, arg5);
        }
    }
    gSPDisplayList(D_800D0510++, D_80094E38);
    if (StageContext_IsHighResolution() != 0) {
        func_8004A174(arg0, arg1, arg2, arg3);
    } else {
        func_8004A44C(arg0, arg1, arg2, arg3);
    }
    gSPDisplayList(D_800D0510++, D_80094F50);
}

extern Gfx *D_800D0510;
extern s32 StageContext_IsHighResolution(void);
extern void func_8004A2E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8004A44C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8004A708(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4);
extern u8 D_80094E38[];
extern u8 D_80094F50[];
void func_8004AE3C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    if (StageContext_IsHighResolution() != 0) {
        func_8004A2E0(arg0, arg1, arg2, arg3);
    } else {
        func_8004A44C(arg0, arg1, arg2, arg3);
    }
    if (arg2 >= 15 && arg3 >= 15) {
        func_8004A708(arg0, arg1, arg2, arg3, arg4);
    }
    gSPDisplayList(D_800D0510++, D_80094F50);
}

extern Gfx *D_800D0510;
extern s32 StageContext_IsHighResolution(void);
extern s32 func_8004C990(s32 arg0, s32 arg1);
extern void func_8004D19C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern u8 D_80094E38[];
extern u8 D_80094F50[];
void func_8004AF18(s32 arg0, s32 arg1) {
    s32 result;
    if (StageContext_IsHighResolution() != 0) {
        result = func_8004C990(0x79, 0);
        if (result != 0) {
            gSPDisplayList(D_800D0510++, D_80094E38);
            func_8004D19C(arg0, arg1, result, 0, 0);
        }
    } else {
        result = func_8004C990(0x7A, 0);
        if (result != 0) {
            gSPDisplayList(D_800D0510++, D_80094E38);
            func_8004D19C(arg0, arg1, result, 0, 0);
        }
    }
    gSPDisplayList(D_800D0510++, D_80094F50);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004B010.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004B09C.s")

extern u8 D_80095110[];
extern void func_8004B09C(s32, s32, s32, s32, void *, s32, s32, s32, s32);
void func_8004B2CC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7) {
    func_8004B09C(arg0, arg1, arg2, arg3, D_80095110, arg4, arg5, arg6, arg7);
}

extern u8 D_80095114[];
void func_8004B314(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8004B09C(arg0, arg1, arg2, arg3, D_80095114, 0xF0, 0xD4, 0x68, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4AC10/func_8004B35C.s")
#endif
