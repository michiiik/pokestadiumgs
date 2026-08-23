#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046980.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046AC0.s")

void func_80046B14(u8 *arg0) {
    if (arg0[0x7B] > 0) {
        arg0[0x7B]--;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046B2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046BB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046C18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046CA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046D70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046DD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046E64.s")

void func_80046F2C(u8 *arg0, s32 arg1) {
    arg0[0x79] = (u8)arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046F34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047058.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800470B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047104.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047158.s")

extern void *memcpy(void *, const void *, s32); void *func_800471B4(void *dest, const void *src, s32 size) { return (u8 *)memcpy(dest, src, size) + size; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800471D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047244.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800472B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800472E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047318.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047348.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_8004735C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047398.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047444.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047524.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047558.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047588.s")

extern u8 *D_80126F50; void func_80047610(void) { func_800029E0(D_80126F50); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047634.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047650.s")

extern u8 *D_80126F50;

void func_80047670(void) {
    D_80126F50[0x7A] |= 4;
}

extern u8 *D_80126F50;
void func_80047688(void) { D_80126F50[0x7A] = (u8)(D_80126F50[0x7A] & ~4); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800476A0.s")

extern u8 *D_80126F50;
s32 func_800476FC(s32 arg0, s32 arg1) { s32 result = 0; if (arg1 > 0 && arg1 < 0x100 && D_80126F50 != NULL) { *(s32 *)(D_80126F50 + 0x50) = arg0; D_80126F50[0x7F] = arg1; result = 1; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047738.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047790.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800477C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047864.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047B4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047BD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047D24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047DC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047EC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_8004803C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800481C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800481FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048234.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800482C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048344.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048830.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048E30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049064.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049148.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800493B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800495BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800495F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049628.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049668.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800496A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800496D8.s")

extern u8 *D_80126F50; void func_80049708(void) { func_80046B14(D_80126F50); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_8004972C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049770.s")

extern u8 *D_80126F50; void func_800497C0(void) { func_80046C18(D_80126F50); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800497E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049828.s")

extern u8 *D_80126F50; void func_80049878(void) { func_80046DD4(D_80126F50); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_8004989C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800498C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800499EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049B48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049B9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049BDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049C44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049C70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049D9C.s")
#endif
