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

void Gfx_SetScissorRect(Gfx **displayList, s16 x, s16 y, s16 width, s16 height) {
    Gfx *list;
    if (D_80087220 != 0) {
        list = *displayList;
        gDPPipeSync(list++);
        gDPSetScissor(list++, G_SC_NON_INTERLACE, x, y, x + width, y + height);
        *displayList = list;
        GfxRect_SetBounds(&D_800D0530, x, y, (x + width) - 1, (y + height) - 1);
    }
}

extern s32 D_80087220;
void Gfx_ApplyScissorRect(void **arg0) { Gfx *cmd; if (D_80087220 != 0) { cmd = *(Gfx **)arg0; gDPPipeSync(cmd++); gDPSetScissor(cmd++, G_SC_NON_INTERLACE, D_800D0530.x1, D_800D0530.y2, D_800D0530.y1 + 1, D_800D0530.x2 + 1); *arg0 = cmd; } }

typedef struct { u16 fmt; u16 size; u16 width; u16 height; u8 *img_p; void *depth_p; } GfxImage;
void GfxImage_Initialize(GfxImage *arg0, s32 fmt, s32 size, s32 width, s32 height, u32 img_p) { arg0->fmt = fmt; arg0->size = size; arg0->width = width; arg0->height = height; arg0->img_p = (u8 *)((img_p + 0x3F) & ~0x3F); arg0->depth_p = NULL; }

extern void *main_pool_alloc(s32, s32);
void *func_800071A4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) { void *result; s32 bytes; u32 doubled; doubled = (arg2 * arg3) * 2; switch (arg1) { case 0: bytes = (arg2 * arg3 + 1) / 2; break; case 1: bytes = arg2 * arg3; break; case 2: bytes = doubled; break; case 3: bytes = arg2 * arg3 * 4; break; } result = main_pool_alloc(bytes + 0x50, arg4); if (result != NULL) GfxImage_Initialize(result, arg0, arg1, arg2, arg3, (u32)((u8 *)result + 0x10)); return result; }

void GfxImage_AttachDepthBuffer(u8 *arg0, u8 *arg1) { if (*(u16 *)(arg1 + 2) == 2) { if (*(u16 *)(arg1 + 4) == *(u16 *)(arg0 + 4)) { if (*(u16 *)(arg1 + 6) == *(u16 *)(arg0 + 6)) *(u32 *)(arg0 + 0xC) = (u32)arg1; } } }

void GfxImage_ResetCurrent(void) {
    D_80087220 = 0;
    GfxRect_SetBounds(&D_800D0530, 0, 0, 0, 0);
}

s32 func_8000731C(void) {
    return D_80087220;
}

void GfxImage_SetRenderTarget(Gfx **displayList, GfxImage *image) {
    Gfx *list;
    list = *displayList;
    gDPPipeSync(list++);
    if (image->depth_p != 0) {
        gDPSetDepthSource(list++, G_ZS_PIXEL);
        gDPSetDepthImage(list++, (u32)(((GfxImage *)image->depth_p))->img_p & 0x1FFFFFFF);
    }
    gDPSetColorImage(list++, image->fmt, image->size, image->width, (u32)image->img_p & 0x1FFFFFFF);
    D_80087220 = (s32)image;
    Gfx_SetScissorRect(&list, 0, 0, image->width, image->height);
    *displayList = list;
}

void GfxImage_FillRectangle(Gfx **displayList, s32 x, s32 y, s32 width, s32 height, u16 color) {
    if (D_80087220 != 0) {
        Gfx *list = *displayList;
        gDPPipeSync(list++);
        gDPSetCycleType(list++, G_CYC_FILL);
        gDPSetRenderMode(list++, G_RM_NOOP, G_RM_NOOP2);
        if (((S1_unk_D_80068BB0 *)(u32)D_80087220)->depth_p != 0) {
            S1_unk_D_80068BB0 *depth = (S1_unk_D_80068BB0 *)((S1_unk_D_80068BB0 *)(u32)D_80087220)->depth_p;
            gDPSetColorImage(list++, depth->fmt, depth->size, depth->width, (u32)depth->img_p & 0x1FFFFFFF);
            gDPSetFillColor(list++, 0xFFFCFFFC);
            gDPFillRectangle(list++, x, y, x + width - 1, y + height - 1);
            gDPPipeSync(list++);
            gDPSetColorImage(list++, ((S1_unk_D_80068BB0 *)(u32)D_80087220)->fmt, ((S1_unk_D_80068BB0 *)(u32)D_80087220)->size, ((S1_unk_D_80068BB0 *)(u32)D_80087220)->width, (u32)((S1_unk_D_80068BB0 *)(u32)D_80087220)->img_p & 0x1FFFFFFF);
        }
        gDPPipeSync(list++);
        gDPSetFillColor(list++, (color << 16) | color);
        gDPFillRectangle(list++, x, y, x + width - 1, y + height - 1);
        *displayList = list;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_8000766C.s")

void GfxImage_FillCurrent(void *arg0, u16 arg1) {
    GfxImage_FillRectangle(arg0, 0, 0, (s32) (*(u16 *)((u8 *)(D_80087220) + (4))), (s32) (*(u16 *)((u8 *)(D_80087220) + (6))), (arg1 << 0x10) | arg1);
}
#endif
