#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000A080.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000A170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000A1E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000A28C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000A304.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000A3EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000A590.s")

extern void func_8000A304(s32, s32, s32, s32);
void func_8000A6C8(void) {
    func_8000A304(0x1E, 0x4F, 0xDC, 0x2ABF);
    func_8000A304(0x4F, 0x80, 0xDC, 0xFFCB);
    func_8000A304(0x80, 0xB1, 0xDC, 0xFBCB);
    func_8000A304(0xB1, 0xE2, 0xDC, 0xF94B);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000A730.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000AA2C.s")

extern Gfx* D_800D0510;
void func_8000AF80(s32 profiler_mode) {
    s32 ulx;
    s32 uly;
    s32 ulx_off;
    s32 uly_off;

    gDPPipeSync(D_800D0510++);
    gDPSetCycleType(D_800D0510++, G_CYC_FILL);
    gDPSetRenderMode(D_800D0510++, G_RM_NOOP, G_RM_NOOP2);

    ulx = 30;
    uly = 211;
    ulx_off = 196;
    uly_off = 9;

    if (func_80008990() != 0) {
        ulx <<= 1;
        uly <<= 1;
        ulx_off <<= 1;
        uly_off <<= 1;
    }

    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, 0x00010001);
    gDPFillRectangle(D_800D0510++, ulx, uly, ulx + ulx_off, uly + uly_off);

    if (profiler_mode == 0) {
        func_8000AA2C();
    } else {
        func_8000A730();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000B0F0.s")

extern void _bzero(s32 *, s32);
extern u8 D_800D0F90;

void func_8000B254(void) {
    _bzero(&D_800D0F90, 0xC8);
    (*(s16 *)((u8 *)(&D_800D0F90) + (0x25A))) = 1;
    (*(s16 *)((u8 *)(&D_800D0F90) + (0x25C))) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000B28C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000B2A4.s")
#endif
