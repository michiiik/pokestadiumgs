#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_829057F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_82905830.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_82905A88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_82905CE4.s")

s32 func_82905EE4(s32 arg0, u8 *arg1) {
    arg1[0x18] = 100;
    arg1[0x19] = 100;
    arg1[0x1A] = 100;
    return 0;
}

extern s16 D_829199F8;
s32 func_82905F00(s32 arg0, u8 *arg1) { if (arg0 == 0) *(s16 *)(arg1 + 0x1A) = 0; if (arg0 == 2) { if (D_829199F8 >= 7) *(s16 *)(arg1 + 0x1A) = 1; else *(s16 *)(arg1 + 0x1A) = 0; } return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_82905F40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_829060BC.s")

extern f32 D_80128C54[];

void func_82906164(f32 arg0) {
    D_80128C54[1] = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_82906170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_829061CC.s")

extern s32 D_82919DC0;
extern s32 D_82919DC8;
void func_82906264(s32 (*arg0)(s32, s32)) {
    D_82919DC0 = arg0(0, 0);
    D_82919DC8 = arg0(1, 0);
}
#endif
