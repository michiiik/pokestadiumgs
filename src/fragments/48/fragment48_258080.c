#include "global.h"


#ifdef VERSION_US
extern void func_87C00144(s32);
void func_87C02080(u8 *arg0, f64 arg3, u8 *arg4) {
    f64 *out = (f64 *)arg0;
    f64 *in = (f64 *)arg4;

    out[0] = arg3;
    func_87C00144((s32)(arg0 + 0x20));
    out[1] = (((in[1] * in[1]) + (in[2] * in[2])) * out[0]) / 12.0;
    out[2] = (((in[2] * in[2]) + (in[0] * in[0])) * out[0]) / 12.0;
    out[3] = (((in[0] * in[0]) + (in[1] * in[1])) * out[0]) / 12.0;
}

extern f64 D_87C03DF0;
void func_87C02138(u8 *arg0, f64 arg3, f64 arg4) {
    f64 temp_fv0;

    *(f64 *)arg0 = arg3;
    func_87C00144((s32)(arg0 + 0x20));
    temp_fv0 = (*(f64 *)arg0) * arg4 * arg4 * D_87C03DF0;
    *(f64 *)(arg0 + 8) = temp_fv0;
    *(f64 *)(arg0 + 0x10) = temp_fv0;
    *(f64 *)(arg0 + 0x18) = temp_fv0;
}

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

extern f64 func_87C007DC(const f64 *, const f64 *);
extern f64 func_87C022A0(void *, void *, void *, f64, f64, f64, f64);
extern void * func_87C004C4(void *, void *, void *);
f64 func_87C021FC(u8 *arg0, u8 *arg1, u8 *arg2, f64 arg4, f64 arg6, f64 arg8) {
    f64 temp[7];
    f64 temp_fv0;

    func_87C004C4(temp + 3, arg1, arg0 + 0x38);
    func_87C00198(temp + 3, temp + 3, arg0 + 0xA0);
    temp_fv0 = func_87C007DC((f64 *)arg2, temp + 3);
    if (temp_fv0 < 0.0) {
        return func_87C022A0(arg0, temp + 3, arg2, arg4, arg6, -temp_fv0, arg8);
    }
    return 0.0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C022A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_258080/func_87C02488.s")


void func_87C02508(s32 arg0) {
    func_87C00144(arg0 + 0x70);
    func_87C00144(arg0 + 0x88);
}

extern void func_87C00AE4(void *, void *);
extern void *func_87C004C4(void *, void *, void *);
void func_87C02538(u8 *arg0) {
    f64 temp[3];

    func_87C00AE4(arg0 + 0x38, arg0 + 0x38);
    func_87C00198(arg0 + 0xA0, arg0 + 8,
                  func_87C004C4(temp, *(u8 **)arg0 + 0x20, arg0 + 0x38));
}

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
