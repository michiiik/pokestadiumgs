#include "global.h"


#ifdef VERSION_US
extern void func_88004990(u8, s32);
extern s32 D_880068B8;
extern u8 **D_88234990;

void func_882302C0(void) {
    func_88004990(**D_88234990, 0);
    D_880068B8 = 1;
}

extern void func_8000612C();

void func_882302F8(void) {
    func_8000612C();
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3540/func_8823031C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3540/func_88230384.s")
#endif
