#include "global.h"


#ifdef VERSION_US
void func_87F0E390(u8 *arg0, s32 arg1) {
    *(s32 *)arg0 = 0;
    *(s32 *)(arg0 + 4) = arg1;
}

extern u8 D_800CE060[];
u16 func_87F0E39C(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;

    switch (arg2) {
        case 0:
            var_v1 = *(u16 *)(D_800CE060 + arg1 * 40 + 6);
            break;
        case 1:
            var_v1 = *(u16 *)(D_800CE060 + arg1 * 40 + 8);
            break;
        case 2:
            var_v1 = *(u16 *)(D_800CE060 + arg1 * 40 + 12);
            break;
    }
    if (var_v1 != 0) {
        arg0[8] = arg1;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_331000/func_87F0E420.s")

extern void func_87F0E420(u8 *, u8 *, s32);
void func_87F0E504(u8* arg0, u8* arg1) {
    func_87F0E420(arg0, arg1, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_331000/func_87F0E524.s")

s32 WidgetTree_RunMessagePanelSilent_fragment64(u8 *arg0, u8 *arg1) { extern s32 func_87F0E524(u8 *, u8 *, s32); return func_87F0E524(arg0, arg1, 0); }

s32 func_87F0E610(u8 *arg0, u8 *arg1) { extern s32 func_87F0E524(u8 *, u8 *, s32); return func_87F0E524(arg0, arg1, 1); }

s32 func_87F0E630(u8 *arg0, u8 *arg1) { extern s32 func_87F0E524(u8 *, u8 *, s32); return func_87F0E524(arg0, arg1, 2); }

s8 func_87F0E650(u8 *arg0) { return *(s8 *)(arg0 + 8); }
#endif
