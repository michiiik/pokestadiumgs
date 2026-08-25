#include "global.h"


#ifdef VERSION_US
extern void func_80049ED8(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_88223320(void) {
    func_80049ED8(D_80087200);
    D_880068B8 = 0;
}

extern void func_80049ED8(s32);
extern void func_800033DC(s32);
extern s32 D_80087200;
extern s32 D_880068B4;
extern s32 D_88234850;
void func_88223348(void) {
    func_80049ED8(D_80087200);
    D_880068B4 = 1;
    func_800033DC(D_88234850);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_88223384.s")

extern void func_880022B4(s32, s32, s32);
void func_882233BC(s32 arg0) {
    (*(s32 *)((u8 *)(D_88234850) + (0x30))) = arg0;
    if (arg0 != 0) {
        func_880022B4(D_88234850 + 4, 0xF00, 0);
        return;
    }
    func_880022B4(D_88234850 + 4, 0xF00, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_88223418.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_88223554.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_882235CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_88223850.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_882241B8.s")
#endif
