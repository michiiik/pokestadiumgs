#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300A9E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300AA58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300AAD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300AB58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300ABCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300AC8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300ADA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300AE40.s")

s32 func_8300AED8(void *arg0) {
    return (s32) (*(u8 *)((u8 *)(arg0) + (1))) >= (s32) (*(u8 *)((u8 *)(arg0) + (0)));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300AEEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300AF68.s")

typedef struct Func8300AFD8Copy { s32 words[292]; } Func8300AFD8Copy;
void func_8300AFD8(void *arg0, void *arg1, s32 arg2) {
    u8 *dst;
    if (arg2 < *(u8 *)((u8 *)arg0 + 1)) {
        dst = (u8 *)((u32)arg0 + (arg2 * 0x490));
        *(Func8300AFD8Copy *)(dst + 4) = *(Func8300AFD8Copy *)arg1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B038.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B0DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B1CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B260.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B284.s")

s32 func_8300B31C(void *arg0) {
    return (s32) (*(u8 *)((u8 *)(arg0) + (1))) >= (s32) (*(u8 *)((u8 *)(arg0) + (0)));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B330.s")

typedef struct Func8300B3A8Copy { s32 words[136]; } Func8300B3A8Copy;
void func_8300B3A8(void *arg0, void *arg1) {
    u8 index;
    u8 *dst;
    index = *(u8 *)((u8 *)arg0 + 1);
    if (index < *(u8 *)((u8 *)arg0 + 0)) {
        dst = (u8 *)((u32)arg0 + (index * 0x220));
        *(Func8300B3A8Copy *)(dst + 4) = *(Func8300B3A8Copy *)arg1;
        *(u8 *)((u8 *)arg0 + 1) = *(u8 *)((u8 *)arg0 + 1) + 1;
    }
}

typedef struct Func8300B410Copy { s32 words[136]; } Func8300B410Copy;
void func_8300B410(void *arg0, void *arg1, s32 arg2) {
    u8 *dst;
    if (arg2 < *(u8 *)((u8 *)arg0 + 1)) {
        dst = (u8 *)((u32)arg0 + (arg2 * 0x220));
        *(Func8300B410Copy *)(dst + 4) = *(Func8300B410Copy *)arg1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B468.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B504.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B54C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B728.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B818.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B8AC.s")

s32 func_8300B988(void *arg0) {
    return (s32) (*(u8 *)((u8 *)(arg0) + (1))) >= (s32) (*(u8 *)((u8 *)(arg0) + (0)));
}
#endif
