#include "global.h"


#ifdef VERSION_US
extern void _bzero(void *, s32);
extern s32 func_8004C8C0(u16);
extern s32 func_8004D690(s32);
extern s32 main_pool_get_available(void);
extern u8 *MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(void *);
extern void *func_81600E28(void *, s32, s32);
extern void func_82801510(void *, s32, s32, s32, s32);

void func_82800020(u8 *arg0, s16 *arg1, s32 arg2) {
    u8 *var_v0;

    _bzero(arg0, 192);
    func_8004C8C0(341);
    func_8004C8C0(54);
    *(s32 *)(arg0 + 180) = func_8004D690(arg1[0]);
    var_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    *(void **)(arg0 + 8) = func_81600E28(var_v0, 1, 25);
    *(s16 **)(arg0 + 184) = arg1;
    MainPool_FinalizeAllocation(var_v0);
    func_82801510(arg0 + 12, arg1[1], arg2, *(s32 *)(arg1 + 2), *(s32 *)(arg0 + 180));
}

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
