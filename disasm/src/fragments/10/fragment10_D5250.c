#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82800620.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82800864.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82800984.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82800AE0.s")

s32 func_82800B94(u8 *arg0) {
    return *(u32 *)(arg0 + 0x88) == 0 || *(u32 *)(arg0 + 0x8C) == 0;
}

s32 func_82800BB4(u8 *arg0) {
    return (*(u32 *)(arg0 + 0) & 0x100000) != 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82800BC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82800E94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_8280105C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801144.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_828011F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801278.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_828014AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801510.s")

s32 func_828016AC(u8 *arg0) {
    *(f32 *)(arg0 + 4) = 0.0f;
    return 0;
}

extern f32 func_816092FC(void);
s32 func_828016BC(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 4) += step;
    if (*(f32 *)(arg0 + 4) >= 12.0f) {
        *(f32 *)(arg0 + 4) = 12.0f;
        *(u8 *)(arg0 + 0xC) = 2;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801718.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801774.s")

s32 func_828019B4(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 4) -= step;
    if (*(f32 *)(arg0 + 4) <= 0.0f) {
        *(f32 *)(arg0 + 4) = 0.0f;
        *(u8 *)(arg0 + 0xC) = 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801A08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801BE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801D7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801F88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_828020C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82802224.s")

s32 func_8280276C(u8 *arg0) {
    if (arg0[0xC]) return -2;
    if (*(u32 *)(arg0 + 0x8C)) {
        if ((*(s32 *)(arg0 + 0) << 2) < 0 && *(s32 *)(arg0 + 0x10) != -1) return 7;
    }
    return *(s32 *)(arg0 + 0x10);
}

extern void func_80054248(void *);
extern void func_80051D64(s32, s32);
extern void func_80054E48(s32);
void func_828027C0(u8 *arg0) {
    if ((*(s32 *)arg0 << 14) >= 0) {
        return;
    }
    if (*(u32 *)(arg0 + 0x84) != 0) {
        arg0[0x4E] |= 1;
    } else {
        arg0[0x4E] &= 0xFFFE;
    }
    func_80054248(arg0 + 0x4C);
    func_80051D64(0x14, 0);
    func_80054E48(3);
}
#endif
