#include "global.h"


#ifdef VERSION_US
s32 func_84104FB0(u8 *arg0) {
    return *(s32 *)(arg0 + 0x14);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_374840/func_84104FB8.s")

extern s32 D_800D0510;
extern s32 func_84104FB8(s32, s32);
void func_841050E4(s32 arg0, u8 *arg1) {
    if (arg0 == 5) {
        D_800D0510 = func_84104FB8(D_800D0510, *(s32 *)(arg1 + 0x14));
    }
}
#endif
