#include "global.h"


#ifdef VERSION_US
extern void func_8004C8C0(s32);
s32 func_8004C990(s32, s32);
extern s32 D_829188F8;
extern s32 D_829188FC;
extern s32 D_82918900;
extern s32 D_82918904;
void func_82902920(void) {
    func_8004C8C0(2);
    D_829188F8 = func_8004C990(2, 0);
    D_829188FC = func_8004C990(2, 1);
    D_82918900 = func_8004C990(2, 5);
    D_82918904 = func_8004C990(2, 6);
}

void func_8290298C(void) {}
void func_8290298C_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33F420/func_8290299C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33F420/func_82902AC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33F420/func_82902EC0.s")
#endif
