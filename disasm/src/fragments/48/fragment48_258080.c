#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C02080.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C02138.s")

extern s32 func_87C00160(u8 *, s32, u8 *);
extern s32 func_87C00238(u8 *, u8 *, s32);
extern void func_87C00198();
void func_87C021A4(u8 *arg0, s32 arg1, u8 *arg2) {
    s32 temp[7];
    s32 value;
    value = func_87C00160((u8 *)(temp + 1), arg1, arg0 + 0xA0);
    value = func_87C00238(arg2, arg0 + 0x58, value);
    func_87C00198(arg2, arg2, arg0 + 0x20);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C021FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C022A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C02488.s")

extern void func_87C00144(s32);

void func_87C02508(s32 arg0) {
    func_87C00144(arg0 + 0x70);
    func_87C00144(arg0 + 0x88);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C02538.s")

extern void func_87C00198();
extern s32 func_87C00160(u8 *, s32, u8 *);
extern s32 func_87C00238(u8 *, u8 *, s32);
void func_87C02594(u8 *arg0, s32 arg1, s32 arg2) {
    u8 temp0[0x18];
    u8 temp1[0x18];
    s32 value;
    func_87C00198(arg0 + 0x70, arg0 + 0x70);
    func_87C00160(temp0, arg1, arg0 + 0xA0);
    value = func_87C00238(temp1, temp0, arg2);
    func_87C00198(arg0 + 0x88, arg0 + 0x88, value);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C025FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C02690.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C02764.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C0288C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C02924.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C02ADC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C02C30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C02D1C.s")
#endif
