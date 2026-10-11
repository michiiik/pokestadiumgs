#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D7D0/func_87F0AB60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D7D0/func_87F0ABA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D7D0/func_87F0ACDC.s")

s32 func_87F0AB60(s32, s32, s32);
extern void func_87F0ABA4(s32, s32, s32);

void func_87F0AD50(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_87F0ABA4(arg0, func_87F0AB60(arg1, arg2, arg3), arg3);
}

extern s32 func_8006456C(s32);
typedef struct {
    u8 *entries[0x1B0];
} func_87F0AD98Row;
s32 func_87F0AD98(func_87F0AD98Row *arg0, s32 arg1, s32 arg2) {
    u8 *entry = arg0[arg2].entries[arg1];
    entry += 4;
    return func_8006456C(*(u16 *)(entry + 0x16));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D7D0/func_87F0ADE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D7D0/func_87F0AEC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D7D0/func_87F0AF4C.s")
#endif
