#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F400020.s")

extern void Dma_CopyChunks(s32, s32, s32);
s32 func_800356CC(s32);
extern s32 D_8F4020E4;

void func_8F400198(void) {
    s32 temp_v0;

    temp_v0 = func_800356CC(9);
    Dma_CopyChunks(D_8F4020E4, temp_v0, temp_v0 + 0xBDC);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F4001CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F4009A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F400A8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F400B88.s")

void func_8F400C08(s32 arg0, s32 arg1) {
    s32 temp_a1;

    temp_a1 = func_800356CC(4) + (arg0 * 0xC80);
    Dma_CopyChunks(arg1, temp_a1, temp_a1 + 0xC80);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F400C58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F400DE8.s")

void func_8F400E74(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == arg1) {
        func_8004972C(0xFF, 0xFF, 0, 0xFF);
        return;
    }
    if (arg2 == 0) {
        func_8004972C(0x80, 0x80, 0x80, 0xFF);
        return;
    }
    func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F400EE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F401464.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F4015FC.s")

extern void Dma_CopyChunks(s32, s32, s32);
extern s32 func_800356CC(s32);
extern s32 D_8F4020E4;
extern void func_800226C0(s32);
extern void func_8F4001CC(void);
extern void *D_80087200;
extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_8F4020C0;
extern void func_8F4015FC(s32, s32, s32, s16, s32, s32);
#define GFX_DL (*(Gfx **)&D_800D0510)
void func_8F401750(void) {
    s16 temp_a3;
    u8 *temp_t2;
    s32 temp_a2;
    s32 temp_t3;
    s32 temp_t7;

    temp_t2 = (u8 *)(u32)(*(u32 *)((u8 *)&D_8F4020C0 + 0xC));
    temp_a2 = *(s32 *)((u8 *)&D_8F4020C0 + 0x18);
    if ((temp_t2 != NULL) && (temp_a2 != 0)) {
        temp_a3 = *(s16 *)(temp_t2 + 4);
        temp_t3 = *(s16 *)(temp_t2 + 6);
        temp_t7 = (0x800 / temp_a3) & ~1;
        gSPDisplayList(GFX_DL++, D_80094E38);
        gDPSetRenderMode(GFX_DL++, 0x0F0A4000, 0);
        func_8F4015FC(0x64, 0x64, temp_a2, temp_a3, temp_t3, temp_t7);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F401828.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F401918.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F401A08.s")

extern void func_800226C0(s32);
extern void func_8F4001CC();
extern void *D_80087200;
s32 func_8F401B74(s32 arg0) {
    s32 sp1C;

    sp1C = 0;
    func_8F4001CC();
    if ((*(u16 *)((u8 *)(D_80087200) + (8))) & 0x4000) {
        sp1C = -1;
        func_800226C0(3);
    }
    return sp1C;
}

extern void Dma_CopyChunks(s32, s32, s32);
extern s32 func_800356CC(s32);
extern s32 D_8F4020E4;
extern void func_800226C0(s32);
extern void func_8F4001CC(void);
extern void *D_80087200;
extern void func_8F400C58(void);
extern s16 D_8F402102;
extern s16 D_8F402104;
s32 func_8F401BC4(s32 arg0) {
    s32 sp1C;
    s32 sp18;

    sp18 = 0;
    func_8F400C58();
    if (((*(u16 *)((u8 *)(D_80087200) + 8)) & 0x4000) &&
        (D_8F402102 >= (D_8F402104 - 1))) {
        sp18 = -1;
        func_800226C0(3);
    }
    return sp18;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F401C30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/72/fragment72_code/func_8F401D88.s")

extern void Dma_CopyChunks(s32, s32, s32);
extern s32 func_800356CC(s32);
extern s32 D_8F4020E4;
extern void func_800226C0(s32);
extern void func_8F4001CC(void);
extern void *D_80087200;
extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void func_80006CD0(s32, s32);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_8004C09C(s32);
extern void func_8004C4B0(s32);
extern void func_80047588(s32, s32);
extern void Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern void func_8F400DE8(void);
extern void func_80008514(s32);
extern void func_8F401D88(void);
extern void func_80008574(void);
extern void func_80047610(void);
extern void func_8004C398(void);
extern void Gfx_FreeDisplayListBuffers(void);
extern u8 D_1000000[];
extern u8 D_446E30[];
extern u8 D_447D00[];
s32 func_8F401F30(s32 arg0, s32 arg1) {
    s32 sp24;

    main_pool_push_state(0x49434D4B);
    func_80006CD0(0x18000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(3);
    func_8004C4B0(0x42);
    func_80047588(0x18, 0);
    Asset_LoadToSegment(((u32)&D_1000000 & 0x0F000000) >> 24, &D_446E30, &D_447D00, 0);
    func_8F400DE8();
    func_80008514(sp24);
    func_8F401D88();
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x49434D4B);
    return 0;
}
#endif
