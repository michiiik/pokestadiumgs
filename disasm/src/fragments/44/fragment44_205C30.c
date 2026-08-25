#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF179C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF17A5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF17AF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF17BA8.s")

void func_8AF17F0C(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x28) = arg1;
    *(s32 *)(arg0 + 0x2C) = arg2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF17F18.s")

extern s16 D_8AF34FAC;
extern s16 D_8AF34FAE;
extern s16 D_8AF34FFC;
extern s16 D_8AF35008;
extern s16 D_8AF3500A;
extern s16 D_8AF3500C;

void func_8AF180F4(void) {
    D_8AF3500C = 0;
    D_8AF34FAC = 2;
    D_8AF34FAE = 0;
    D_8AF34FFC = 0;
    D_8AF35008 = 0;
    D_8AF3500A = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF1812C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF18190.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF181F4.s")

void func_8AF18808(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (arg1 < value) {
        value -= arg2;
        if (value < arg1) value = arg1;
        *arg0 = value;
    }
}

void func_8AF18848(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (value < arg1) {
        value += arg2;
        if (arg1 < value) value = arg1;
        *arg0 = value;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_205C30/func_8AF18888.s")

extern void func_800498C4(void);
extern void func_800499EC(void);
void func_8AF19850(void) {
    func_800498C4();
    func_800499EC();
}
#pragma C_FUNCTION_PADDING(8)
#endif
