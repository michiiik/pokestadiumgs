#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D4C50/func_82800020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D4C50/func_828000CC.s")

extern void func_81600954(void *);
extern void func_81600A34(void *, s32, s32, s32, s32, s32, s32);
extern void func_82801BE8(void *, void *);
extern void func_81600B30(void *);
void func_8280018C(u8 *arg0, s32 arg1) {
    func_81600954(*(void **)(arg0 + 8));
    func_81600A34(*(void **)(arg0 + 8), *(s32 *)(arg0 + 0xB4), arg1 == 0, 0, 0, 640, 480);
    func_82801BE8(arg0 + 0xC, *(void **)(arg0 + 8));
    func_81600B30(*(void **)(arg0 + 8));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D4C50/func_828001FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D4C50/func_82800490.s")
#endif
