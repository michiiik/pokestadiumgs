#include "global.h"


#ifdef VERSION_US
void func_8AF07CB0(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x28) = arg1;
    *(s32 *)(arg0 + 0x2C) = arg2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5F20/func_8AF07CBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5F20/func_8AF07EBC.s")

extern s16 D_8AF2C960;
void func_8AF07FF0(void) {
    D_8AF2C960 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5F20/func_8AF08000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5F20/func_8AF08390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5F20/func_8AF084BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5F20/func_8AF08538.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5F20/func_8AF085C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5F20/func_8AF08644.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5F20/func_8AF086C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5F20/func_8AF08758.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5F20/func_8AF087D4.s")

extern void func_800498C4(void);
extern void func_800499EC(void);
void func_8AF0894C(void) {
    func_800498C4();
    func_800499EC();
}
#pragma C_FUNCTION_PADDING(12)
#endif
