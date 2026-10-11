#include "global.h"


#ifdef VERSION_US
extern void func_800226C0(s32);
extern s32 func_8821C0B0(void);
extern void func_8822AF00(void *);
extern void func_88001900(void);
extern u8 *D_882345F4;
extern s32 D_880068B4;
void func_88232E70(void) {
    func_800226C0(0x60);
    if (func_8821C0B0() == 0) {
        func_8822AF00(D_882345F4 + 0x3C);
    } else {
        func_88001900();
        D_880068B4 = 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A60F0/func_88232EC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A60F0/func_88232F88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A60F0/func_88233040.s")
#endif
