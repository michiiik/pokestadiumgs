#include "global.h"


#ifdef VERSION_US
typedef struct S1_unk_D_800A7440 {
	/* 0x00 */ s16 x1;
	/* 0x02 */ s16 y1;
	/* 0x04 */ s16 x2;
	/* 0x06 */ s16 y2;
} S1_unk_D_800A7440;
typedef struct S1_unk_D_80068BB0 {
	/* 0x00 */ u16 fmt;
	/* 0x02 */ u16 size;
	/* 0x04 */ u16 width;
	/* 0x06 */ u16 height;
	/* 0x08 */ u8* img_p;
	/* 0x0C */ struct S1_unk_D_80068BB0* depth_p;
} S1_unk_D_80068BB0;
S1_unk_D_800A7440* GfxRect_SetBounds(S1_unk_D_800A7440* arg0, s16 x1, s16 y1, s16 x2, s16 y2) {
    if (x2 >= x1) {
        arg0->x1 = x1;
        arg0->y1 = x2;
    } else {
        arg0->x1 = x2;
        arg0->y1 = x1;
    }

    if (y2 >= y1) {
        arg0->x2 = y2;
        arg0->y2 = y1;
    } else {
        arg0->y2 = y2;
        arg0->x2 = y1;
    }

    return arg0;
}

extern s32 D_80087220;
extern S1_unk_D_800A7440 D_800D0530;
s32 GfxRect_ClipToScissor(S1_unk_D_800A7440 *arg0) {
    s32 ret = 0;
    if (D_80087220 != NULL) {
        if (arg0->x1 < D_800D0530.x1) arg0->x1 = D_800D0530.x1;
        if (D_800D0530.y1 < arg0->y1) arg0->y1 = D_800D0530.y1;
        if (arg0->y2 < D_800D0530.y2) arg0->y2 = D_800D0530.y2;
        if (D_800D0530.x2 < arg0->x2) arg0->x2 = D_800D0530.x2;
        ret = arg0->y1 >= arg0->x1 && arg0->x2 >= arg0->y2;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_80006F70.s")

extern s32 D_80087220;
void Gfx_ApplyScissorRect(void **arg0) { Gfx *cmd; if (D_80087220 != 0) { cmd = *(Gfx **)arg0; gDPPipeSync(cmd++); gDPSetScissor(cmd++, G_SC_NON_INTERLACE, D_800D0530.x1, D_800D0530.y2, D_800D0530.y1 + 1, D_800D0530.x2 + 1); *arg0 = cmd; } }

typedef struct { u16 fmt; u16 size; u16 width; u16 height; u8 *img_p; void *depth_p; } GfxImage;
void GfxImage_Initialize(GfxImage *arg0, s32 fmt, s32 size, s32 width, s32 height, u32 img_p) { arg0->fmt = fmt; arg0->size = size; arg0->width = width; arg0->height = height; arg0->img_p = (u8 *)((img_p + 0x3F) & ~0x3F); arg0->depth_p = NULL; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_800071A4.s")

void GfxImage_AttachDepthBuffer(u8 *arg0, u8 *arg1) { if (*(u16 *)(arg1 + 2) == 2) { if (*(u16 *)(arg1 + 4) == *(u16 *)(arg0 + 4)) { if (*(u16 *)(arg1 + 6) == *(u16 *)(arg0 + 6)) *(u32 *)(arg0 + 0xC) = (u32)arg1; } } }

void GfxImage_ResetCurrent(void) {
    D_80087220 = 0;
    GfxRect_SetBounds(&D_800D0530, 0, 0, 0, 0);
}

s32 func_8000731C(void) {
    return D_80087220;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_80007328.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_80007444.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_8000766C.s")

void GfxImage_FillCurrent(void *arg0, u16 arg1) {
    func_80007444(arg0, 0, 0, (s32) (*(u16 *)((u8 *)(D_80087220) + (4))), (s32) (*(u16 *)((u8 *)(D_80087220) + (6))), (arg1 << 0x10) | arg1);
}
#endif
