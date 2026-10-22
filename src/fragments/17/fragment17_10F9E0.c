#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10F9E0/func_82200020.s")

/* mkdraft:func_822000F0 begin */
extern s32 func_800506A4(void *);
extern void func_80050578(void *, s32);
extern s32 D_8220D758[];

s32 func_822000F0(s32 arg0, void *arg1) {
    s32 index = *(s32 *)((u8 *)arg1 + 0x20);

    switch (arg0) {
    case 0:
        *(s8 *)((u8 *)arg1 + 0x28) = 0x21;
        if (index == 1) {
            *(u16 *)((u8 *)arg1 + 2) &= 0xFFFD;
        }
        break;
    case 1:
        if (func_800506A4(arg1) != 0) {
            s32 idx = guRandom() & 3;
            func_80050578(arg1, D_8220D758[idx]);
        }
        break;
    }
    return 0;
}
/* mkdraft:func_822000F0 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10F9E0/func_82200184.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10F9E0/func_82200374.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10F9E0/func_822003EC.s")
#endif
