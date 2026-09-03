#include "global.h"


#ifdef VERSION_US
extern void func_88001900();
extern s32 D_880068B4;
extern s32 D_889041B4;

void func_8822AA20(void) {
    func_88001900();
    D_889041B4 = 1;
    D_880068B4 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DCA0/func_8822AA50.s")

extern void func_800226C0(s32);
extern void func_88004990(u8, s32);
extern s32 D_8800EF54;
extern void *D_882348E0;
void func_8822AA9C(s32 arg0) {
    func_88004990(*(*(u8 **)((u8 *)(D_882348E0) + (0))), 0);
    if (arg0 != 0) {
        D_8800EF54 = arg0;
        func_800226C0(0x5D);
        func_800226C0(0x63);
        func_88232B50();
        D_889041B4 = 0;
        D_880068B4 = 0;
    } else {
        D_889041B4 = 2;
    }
    (*(s32 *)((u8 *)(D_882348E0) + (0x204))) = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DCA0/func_8822AB28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DCA0/func_8822ABE8.s")
#endif
