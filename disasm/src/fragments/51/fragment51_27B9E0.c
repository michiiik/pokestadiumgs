#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305BC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305C48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305C78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305D88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305E20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305E70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305FD8.s")

s32 func_86305E70();
extern void func_86305FD8(s32);

void func_863060CC(s32 arg0) {
    if (func_86305E70() != 0) {
        func_86305FD8(arg0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_863060FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_863063C0.s")

extern void *D_87F119DC;

void func_86306638(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (0))) = (f32) (*(f32 *)((u8 *)(D_87F119DC) + (0x48)));
    (*(f32 *)((u8 *)(arg0) + (4))) = (f32) (*(f32 *)((u8 *)(D_87F119DC) + (0x4C)));
}

extern void *D_87F119DC;

void func_8630665C(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (8))) = (f32) ((*(f32 *)((u8 *)(D_87F119DC) + (0x48))) - (*(f32 *)((u8 *)(arg0) + (0))));
    (*(f32 *)((u8 *)(arg0) + (0xC))) = (f32) ((*(f32 *)((u8 *)(D_87F119DC) + (0x4C))) - (*(f32 *)((u8 *)(arg0) + (4))));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86306690.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86306710.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86306AC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86306CC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86306D3C.s")
#endif
