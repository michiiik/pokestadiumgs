#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_80006E50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_80006EC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_80006F70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_80007090.s")

typedef struct { u16 fmt; u16 size; u16 width; u16 height; u8 *img_p; void *depth_p; } GfxImage;
void func_80007174(GfxImage *arg0, s32 fmt, s32 size, s32 width, s32 height, u32 img_p) { arg0->fmt = fmt; arg0->size = size; arg0->width = width; arg0->height = height; arg0->img_p = (u8 *)((img_p + 0x3F) & ~0x3F); arg0->depth_p = NULL; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_800071A4.s")

void func_800072A4(u8 *arg0, u8 *arg1) { if (*(u16 *)(arg1 + 2) == 2) { if (*(u16 *)(arg1 + 4) == *(u16 *)(arg0 + 4)) { if (*(u16 *)(arg1 + 6) == *(u16 *)(arg0 + 6)) *(u32 *)(arg0 + 0xC) = (u32)arg1; } } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_800072E0.s")

extern s32 D_80087220;
s32 func_8000731C(void) {
    return D_80087220;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_80007328.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_80007444.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_8000766C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7A50/func_80007820.s")
#endif
