#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_84155820.s")
#endif

#ifdef VERSION_US
extern void func_84155820(s32);
void func_84155A1C(void) {
    func_84155820(0);
    func_84155820(1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_84155A44.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_84155AC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_84155BD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_84155CB8.s")
#endif

#ifdef VERSION_US
extern u8 D_8419EE17[];
u8 func_84155D5C(u8 arg0, u8 arg1, u8 arg2) {
    return D_8419EE17[arg0 * 0x132 + arg1 * 0x18 + arg2];
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_84155DB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_84155F28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_8415623C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_841562BC.s")
#endif

#ifdef VERSION_US
extern u8 D_8419EE01[];
extern u8 *D_841951F8[];
extern void func_84155F28(u8, u8);
extern void func_8415623C(u8);
void func_84156464(u8 arg0) {
    s32 i;
    D_8419EE01[arg0 * 0x132] = 1;
    i = 0;
    while (i < D_841951F8[arg0][7]) {
        func_84155F28(arg0, i);
        i++;
    }
    func_8415623C(arg0);
}
#endif

#ifdef VERSION_US
extern void func_84156464(u8);
void func_84156510(void) {
    s32 i;
    i = 0;
    while (i != 2) {
        func_84156464(i);
        i += 1;
    }
}
#endif

#ifdef VERSION_US
extern u8 D_8419EE00[];
u8 *func_84156550(void) {
    return D_8419EE00;
}
#endif

#ifdef VERSION_US
u8 *func_8415655C(u8 arg0) {
    return D_8419EE00 + arg0 * 0x132;
}
#endif

#ifdef VERSION_US
u8 *func_84156590(u8 arg0, u8 arg1) {
    return D_8419EE00 + arg0 * 0x132 + arg1 * 0x18 + 0x12;
}
#endif

#ifdef VERSION_US
u8 *func_841565E0(u8 arg0) {
    return D_8419EE00 + arg0 * 0x132 + 2;
}
#endif

#ifdef VERSION_US
extern u8 D_8419EE12[];
s32 func_84156618(u8 arg0, u8 arg1, u8 arg2) {
    return (D_8419EE12[arg0 * 0x132 + arg1 * 0x18] & arg2) != 0;
}
#endif

#ifdef VERSION_US
void func_84156674(u8 arg0, u8 arg1, u8 arg2) {
    D_8419EE00[arg0 * 0x132 + arg1 * 0x18 + 0x12] |= arg2;
}
#endif

#ifdef VERSION_US
void func_841566D0(u8 arg0, u8 arg1, u8 arg2) {
    D_8419EE00[arg0 * 0x132 + arg1 * 0x18 + 0x12] &= ~arg2;
}
#endif

#ifdef VERSION_US
void func_84156730(u8 arg0, u8 arg1) {
    D_8419EE00[arg0 * 0x132] |= arg1;
}
#endif

#ifdef VERSION_US
s32 func_84156774(u8 arg0, u8 arg1) {
    return (D_8419EE00[arg0 * 0x132] & arg1) != 0;
}
#endif

#ifdef VERSION_US
void func_841567B8(u8 arg0, u8 arg1) {
    D_8419EE00[arg0 * 0x132] &= ~arg1;
}
#endif

#ifdef VERSION_US
s32 func_84156800(s32 arg0, s32 arg1) {
    return arg0;
}
#endif

void func_8415680C(void) {
}

#ifdef VERSION_US
void func_84156814(void) {}
#endif
