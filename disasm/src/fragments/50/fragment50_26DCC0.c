#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26DCC0/func_86207280.s")

extern u8 *D_8620E198;
extern void func_87F02684(void *);
void func_8620736C(void) {
    func_87F02684(D_8620E198 + 0x728C8);
}

extern void func_87F0277C(void *);
void func_8620739C(void) {
    func_87F0277C(D_8620E198 + 0x728C8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26DCC0/func_862073CC.s")

extern u8 D_87F15B70[];
extern s32 func_8004DDF4(s32);
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern s32 WidgetTree_RunMessagePanelSilent(s32, s32);
extern void MainPool_FinalizeAllocation(s32);
extern void func_87F0252C(void *, void *, void *, s32);
void func_862075BC(void) {
    s32 handle;
    func_8004DDF4(0xB7);
    handle = MainPool_AllocState(main_pool_get_available(), 0);
    *(s32 *)(D_8620E198 + 0x16C) = WidgetTree_RunMessagePanelSilent(handle, 0xB7);
    MainPool_FinalizeAllocation(handle);
    func_87F0252C(D_87F15B70, D_8620E198 + 0x728C8, D_8620E198 + 0x728DC, 8);
}
#endif
