#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305BC0.s")

void func_86305C48(void *arg0, void *arg1, f32 arg2) {
    *(f32 *)((u8 *)arg0 + 0x48) += *(f32 *)((u8 *)arg1 + 0) * arg2;
    *(f32 *)((u8 *)arg0 + 0x4C) += *(f32 *)((u8 *)arg1 + 4) * arg2;
}

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


void func_8630665C(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (8))) = (f32) ((*(f32 *)((u8 *)(D_87F119DC) + (0x48))) - (*(f32 *)((u8 *)(arg0) + (0))));
    (*(f32 *)((u8 *)(arg0) + (0xC))) = (f32) ((*(f32 *)((u8 *)(D_87F119DC) + (0x4C))) - (*(f32 *)((u8 *)(arg0) + (4))));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86306690.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86306710.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86306AC0.s")

extern void func_863060FC(void **);
extern void func_86306710(void **);
extern void func_86306AC0(void **);
void func_86306CC4(void) {
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(D_87F119DC) + (0x20)));
    (*(s32 *)((u8 *)(temp_v0) + (0x1C))) = (s32) ((*(s32 *)((u8 *)(temp_v0) + (0x1C))) + 1);
    temp_v1 = (*(s32 *)((u8 *)(D_87F119DC) + (0xC)));
    if (temp_v1 & 0x10000000) {
        func_863060FC(&D_87F119DC);
        return;
    }
    if (temp_v1 & 0x20000000) {
        func_86306AC0(&D_87F119DC);
        return;
    }
    func_86306710(&D_87F119DC);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86306D3C.s")
#endif
