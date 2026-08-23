#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800609D0.s")

u16 func_80060A4C(const u8 *arg0) { return (u16)((arg0[0] << 8) | arg0[1]); }

u32 func_80060A64(const u8 *arg0) { return ((u32)arg0[0] << 16) | ((u32)arg0[1] << 8) | arg0[2]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060A84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060A94.s")

u8 func_80060AAC(u8 arg0) { extern u8 *D_80097680; return D_80097680[arg0]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060AC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060B28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060B74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060C08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060C50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060C98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060D1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060D70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060DDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060E88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060EC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060EF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060F38.s")

extern void func_8000B580(void); void func_80060F68(void) { func_8000B580(); }

s32 func_80060F88(void) { return 0x46; }

s32 func_80060F90(void) { return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060F98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060FF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061124.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061248.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800612B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006136C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800613F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800614EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800615D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006162C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800616BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006175C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006179C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006183C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061940.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800619E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061ADC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061B88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061D8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061ED0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061F44.s")

extern s32 _bcmp(const void *, const void *, s32); s32 func_80061FAC(const void *a, const void *b) { return _bcmp(a, b, 0xD) == 0; }

extern u8 D_800976A0[]; u8 func_80061FD0(s32 index) { return D_800976A0[index]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061FE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062008.s")

s32 func_80062030(s32 value) { if (value > 0 && value < 0xFC) return value; return 0xFC; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800620E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006218C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062238.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006229C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062304.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006236C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006249C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800625E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062614.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006276C.s")

void func_800627F0(s32 arg0, s32 arg1) {}

void func_800627FC(s32 arg0, s32 arg1) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062808.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062884.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062978.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062BD4.s")

s32 func_80062C18(s32 arg0) { return 1; }

s32 func_80062C24(s32 arg0) { return 1; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062C30.s")
#endif
