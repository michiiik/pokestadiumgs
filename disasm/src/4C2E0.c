#include "global.h"


#ifdef VERSION_US
extern void _bcopy(u8 *, u8 *, s32);
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
s32 func_800356CC(s32 arg0);
s32 func_8004C4A4(void);
extern u8 *func_800042C0(u8 *, u8 *, s32, s32);
extern u8 D_801270B0;
s32 func_8004B6E0(void) {
    s32 pad_frame[2];
    s32 sp1C;
    u8 *sp18;
    s32 temp_v0;

    temp_v0 = func_800356CC(0xA);
    sp1C = temp_v0;
    sp18 = temp_v0 + 0xFD0;
    func_8004C4A4();
    main_pool_push_state(0x504D4442);
    _bcopy(func_800042C0((u8 *) sp1C, sp18, 0, 0), &D_801270B0, 0xFD0);
    main_pool_pop_state(0x504D4442);
    return 0;
}

s32 func_8004B754(s32 a) {
    s32 r = -1;
    if (a > 0 && a <= 0xfd)
        r = a - 1;
    else if (a >= 0xfe && a <= 0x116)
        r = 0xc8;
    else if (a == 0x117)
        r = 0x18;
    return r;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B7A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B7E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B888.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B8E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B920.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B98C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B9E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BA34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BA70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BAE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BB58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BBA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BC6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BCBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BD28.s")

extern s32 func_8004B754(s32);
extern u8 D_801270B3[];
extern u8 D_801270B4[];
void func_8004BD78(s32 a, s16 b) {
    s32 i = func_8004B754(a);
    if (i >= 0)
        D_801270B3[i << 4] = (u8)b;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BDB0.s")

void func_8004BE18(s32 a, s32 b) {
    s32 i = func_8004B754(a);
    if (i >= 0)
        *(s32 *)(D_801270B4 + (i << 4)) = b;
}

extern void Dma_CopyChunks(s32 *, s32, s32);
s32 func_800356CC(s32);
extern u8 D_801270B0;

void func_8004BE50(void) {
    s32 temp_v0;

    temp_v0 = func_800356CC(0xA);
    Dma_CopyChunks(&D_801270B0, temp_v0, temp_v0 + 0xFD0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BE84.s")

s32 func_8004B754(s32);
void func_8004BEEC(s32 arg0, s32 arg1, s16 arg2) {
    s32 temp_v0;

    temp_v0 = func_8004B754(arg1);
    if ((arg0 != 0) && (temp_v0 >= 0)) {
        (*(s16 *)((u8 *)(((temp_v0 * 0xC) + arg0)) + (2))) = arg2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BF3C.s")

void func_8004BFC4(s32 arg0, s32 arg1, s16 arg2) {
    s32 temp_v0;

    temp_v0 = func_8004B754(arg1);
    if ((arg0 != 0) && (temp_v0 >= 0)) {
        (*(s8 *)((u8 *)(((temp_v0 * 0xC) + arg0)) + (8))) = (s8) arg2;
    }
}
#endif
