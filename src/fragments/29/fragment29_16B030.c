#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D0510;
extern Gfx D_88006030[];
extern u8 D_8800EF30[];
extern s16 D_8800EF32;
extern s32 Envelope_Advance(void *);
extern s32 func_8004C8C0();
extern s32 func_8004C990(s32, s32);
extern s32 D_8800EF3C;
void func_88004FF0(s32 archive) {
    s32 entry;
    func_8004C8C0(archive);
    switch (archive) {
    case 0x3A:
        entry = 0;
        break;
    case 0x3B:
        entry = 0;
        break;
    }
    D_8800EF3C = func_8004C990(archive, entry);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_16B030/func_88005048.s")

void func_8800528C(s32 mode) {
    gSPDisplayList(D_800D0510++, D_88006030);
    if (mode) {
        gDPSetRenderMode(D_800D0510++, 0x00504340, 0);
        gDPSetEnvColor(D_800D0510++, 150, D_8800EF32, 255, 128);
    } else {
        gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
        gDPSetEnvColor(D_800D0510++, 150, Envelope_Advance(D_8800EF30), 255, 255);
    }
}

extern Gfx D_80094DE0[];
extern s32 func_8004D1FC(u8 *);
extern void func_80044270(s16, s16, s16, s16, s16, s16, s16, s16, s32);
/* The legacy wrapper forwards an opaque fourth argument that retail ignores. */
#ifdef CC_CHECK
void func_88005390(s32 mode, s16 width, s16 height, void *unused) {
#else
void func_88005390(mode, width, height)
s32 mode;
s16 width;
s16 height;
{
#endif
    s16 textureWidth = *(s16 *)(u32)D_8800EF3C;
    s16 textureHeight = *(s16 *)((u8 *)(u32)D_8800EF3C + 2);
    s16 halfWidth = width >> 1;
    s16 halfHeight = height >> 1;
    s32 stepX = (s32)((((f32)textureWidth * 1024.0f / (f32)halfWidth > 0.0f) ? 0.5f : -0.5f) +
                     ((f32)textureWidth * 1024.0f / (f32)halfWidth));
    s32 stepY;
    stepY = (s32)((((f32)textureHeight * 1024.0f / (f32)halfHeight > 0.0f) ? 0.5f : -0.5f) +
                 ((f32)textureHeight * 1024.0f / (f32)halfHeight));
    func_8800528C(mode);
    func_8004D1FC((u8 *)(u32)D_8800EF3C);
    func_80044270(0, 0, halfWidth, halfHeight, -16, -16, stepX, stepY, 0);
    func_80044270(halfWidth, 0, halfWidth, halfHeight, ((textureWidth - 1) << 5) + 16, -16, -stepX, stepY, 0);
    func_80044270(0, halfHeight, halfWidth, halfHeight, -16, ((textureHeight - 1) << 5) + 16, stepX, -stepY, 0);
    func_80044270(halfWidth, halfHeight, halfWidth, halfHeight, ((textureWidth - 1) << 5) + 16,
                  ((textureHeight - 1) << 5) + 16, -stepX, -stepY, 0);
    if ((width & 1) || (height & 1)) {
        gSPDisplayList(D_800D0510++, D_80094DE0);
        gDPSetFillColor(D_800D0510++, 0x00010001);
        if (width & 1) gDPFillRectangle(D_800D0510++, width - 1, 0, width - 1, height - 1);
        if (height & 1) gDPFillRectangle(D_800D0510++, 0, height - 1, width - 1, height - 1);
    }
}

void func_88005714(void *arg0) {
    func_88005390(0, (*(s16 *)((u8 *)(arg0) + (4))), (*(s16 *)((u8 *)(arg0) + (6))), arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_16B030/func_88005740.s")
#endif
