#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80044270.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80044424.s")

typedef struct S1_unk_D_800A7440 {
	/* 0x00 */ s16 x1;
	/* 0x02 */ s16 y1;
	/* 0x04 */ s16 x2;
	/* 0x06 */ s16 y2;
} S1_unk_D_800A7440;
extern Gfx* D_800D0510;
void Gfx_FillRectRgb(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6) {
    gDPSetPrimColor(D_800D0510++, 0, 0, arg4, arg5, arg6, 0xFF);

    func_80044270(arg0, arg1, arg2, arg3, 0, 0, 0, 0, 0);
}

void Gfx_FillRectRgba(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    gDPSetPrimColor(D_800D0510++, 0, 0, arg4, arg5, arg6, arg7);

    func_80044270(arg0, arg1, arg2, arg3, 0, 0, 0, 0, 0);
}

void Gfx_DrawTextureRgba16(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock(D_800D0510++, arg4, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg5, arg3, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    func_80044270(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawTextureRgba32(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock(D_800D0510++, arg4, G_IM_FMT_RGBA, G_IM_SIZ_32b, arg5, arg3, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    func_80044270(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawTextureIa8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock(D_800D0510++, arg4, G_IM_FMT_IA, G_IM_SIZ_8b, arg5, arg3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_80044270(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawTextureIa16(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock(D_800D0510++, arg4, G_IM_FMT_IA, G_IM_SIZ_16b, arg5, arg3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_80044270(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawTextureI4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock_4b(D_800D0510++, arg4, G_IM_FMT_I, arg5, arg3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    func_80044270(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawTextureI8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock(D_800D0510++, arg4, G_IM_FMT_I, G_IM_SIZ_8b, arg5, arg3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    func_80044270(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawTextureI16(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock(D_800D0510++, arg4, G_IM_FMT_I, G_IM_SIZ_16b, arg5, arg3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    func_80044270(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawTextureRgba16Ia8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, u8* arg5, s16 arg6, s32 arg7) {
    gDPLoadTextureBlock(D_800D0510++, arg4, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg6, arg3, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gDPLoadMultiBlock(D_800D0510++, arg5, 0x0100, 1, G_IM_FMT_I, G_IM_SIZ_8b, arg6, arg3, 0,
                      G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                      G_TX_NOLOD);

    func_80044270(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg7);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_800459AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80045DB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80046204.s")

s32 func_800464F8(s32 arg0, s32 arg1) {
    s32 temp_lo;
    s32 var_v1;

    temp_lo = arg0 / arg1;
    var_v1 = temp_lo;
    if ((arg0 % arg1) > 0) {
        var_v1 = temp_lo + 1;
    }
    return var_v1;
}

s32 func_80046540(s32 arg0, s32 arg1) {
    return (arg1 / arg0) & ~1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_8004657C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44E70/func_80046634.s")

extern void func_8004657C(void);
extern void func_80046634(s32);
void func_800468A0(s32 arg0) { func_8004657C(); func_80046634(arg0); }

void Gfx_SetVertexAttributes(Vtx* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9) {
    arg0->v.ob[0] = arg1;
    arg0->v.ob[1] = arg2;
    arg0->v.ob[2] = arg3;
    arg0->v.flag = 0;
    arg0->v.tc[0] = arg4;
    arg0->v.tc[1] = arg5;
    arg0->v.cn[0] = arg6;
    arg0->v.cn[1] = arg7;
    arg0->v.cn[2] = arg8;
    arg0->v.cn[3] = arg9;
}

void Gfx_SetViewportDimensions(void *arg0, s16 arg1, s16 arg2) {
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = arg1 * 2;
    temp_v1 = arg2 * 2;
    (*(s16 *)((u8 *)(arg0) + (8))) = temp_v0;
    (*(s16 *)((u8 *)(arg0) + (0xA))) = temp_v1;
    (*(s16 *)((u8 *)(arg0) + (0xC))) = 0x1FF;
    (*(s16 *)((u8 *)(arg0) + (0xE))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0))) = temp_v0;
    (*(s16 *)((u8 *)(arg0) + (2))) = temp_v1;
    (*(s16 *)((u8 *)(arg0) + (4))) = 0x1FF;
    (*(s16 *)((u8 *)(arg0) + (6))) = 0;
}
#endif
