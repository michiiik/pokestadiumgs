#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_326820/func_87F03BB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_326820/func_87F03D9C.s")

extern f32 D_87F11480;
extern f32 D_87F11484;
void func_87F03EDC(u8 *arg0, u8 *arg1) {
    switch (arg1[0xC]) {
    case 0:
        *(f32 *)(arg1 + 0x18) = D_87F11480;
        *(s16 *)(arg1 + 0x14) = 0xF;
        break;
    case 1:
        *(f32 *)(arg0 + 0x14) = *(f32 *)arg1;
        *(f32 *)(arg1 + 0x18) = D_87F11484;
        *(s16 *)(arg1 + 0x14) = 0xFF;
        break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_326820/func_87F03F38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_326820/func_87F04018.s")
#endif
