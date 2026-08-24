#include "global.h"


#ifdef VERSION_US
s32 func_87E043F0(u8 *arg0) {
    return (*(u16 *)(arg0 + 0x274) & 4) != 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E04400.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E044B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E0469C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E04790.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E049A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E04A14.s")

extern void func_87F02684(s32);
void func_87E04AA4(s32 arg0) { func_87F02684(arg0 + 8); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E04AC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E04AFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E04D2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E04ED4.s")

extern void func_8004C8C0(s32);
void func_87E05128(void) { func_8004C8C0(426); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E05148.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E0520C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_307D60/func_87E05258.s")

extern void func_87E05258(void);
extern void func_800088DC(void);
void func_87E053D0(void) {
    func_87E05258();
    func_800088DC();
}
#pragma C_FUNCTION_PADDING(8)
#endif
