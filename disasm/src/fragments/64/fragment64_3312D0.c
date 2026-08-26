#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0E660.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0E6B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0E790.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0E84C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0E978.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0E9D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0EA40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0EDDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0EE0C.s")

extern u32 D_87F15BB0;
extern void func_81A00020(void *);
extern void func_81A005F0(void *);
void func_87F0EECC(void) { func_81A00020(&D_87F15BB0); func_81A005F0(&D_87F15BB0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0EEFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0EFA0.s")

extern void func_8005777C();

void func_87F0F118(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_8005777C();
        var_s0 += 1;
    } while (var_s0 != 0x10);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0F158.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0F1C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0F234.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0F2B8.s")

s8 func_80057764(s32);
extern void func_80057944(s32);
void func_87F0F390(void *arg0) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_80057944(var_s0 & 0xFF);
        var_s0 += 1;
    } while (var_s0 != 4);
    (*(s8 *)((u8 *)(arg0) + (0x2178))) = func_80057764(0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0F3E4.s")

extern void func_81A0022C(void *);
void func_87F0F444(void) { func_81A0022C(&D_87F15BB0); }

extern u32 D_87F15BB8;
u32 func_87F0F468(void) {
    return D_87F15BB8;
}
#pragma C_FUNCTION_PADDING(12)
#endif
