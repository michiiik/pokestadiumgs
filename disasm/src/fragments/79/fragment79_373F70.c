#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_841046E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_8410474C.s")

s32 func_841047A4(u8 *arg0) {
    return *(s32 *)(arg0 + 0x14);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_841047AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_84104818.s")

extern void func_84104818(u8 *);
void func_8410488C(u8 *arg0) {
    u8 *ptr = *(u8 **)(arg0 + 0xC);
    if (ptr != NULL) func_84104818(ptr);
}

extern void func_8003EB84(u8 *, s16);
void func_841048B8(u8 *arg0, s16 arg1) {
    func_8003EB84(arg0, arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_841048E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_8410491C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_84104958.s")

void func_841049B4(u8 *arg0) { func_8003EB84(arg0, (s16)(*(u16 *)(*(u8 **)(arg0 + 0x44) + 0xA) - 1)); }

s32 func_841049E4(u8 *arg0) { s32 result = 0; if (*(s32 *)(arg0 + 0x48) == 0) { result = 1; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_84104A00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_84104D28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_373F70/func_84104F54.s")
#endif
