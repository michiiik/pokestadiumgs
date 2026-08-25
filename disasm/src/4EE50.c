#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E250.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E298.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E308.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E368.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E3C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E438.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E52C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E610.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E748.s")

extern s32 D_80128098; void func_8004E7AC(void) { D_80128098 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E7B8.s")

extern s32 D_80128098;
extern s32 D_8012809C;
void func_8004E7FC(void) {
    D_8012809C -= 1;
    D_80128098 += 4;
}

s32 func_8004E368(s32, s32);
extern void func_8004E748(s32);
extern s32 D_80128090;

void func_8004E828(void) {
    func_8004E748(func_8004E368(D_80128090, 0));
    D_80128098 += 0x10;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E868.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E8D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E9C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004EA60.s")

s32 func_8004EB1C(s32 value) { s32 result = value; if (value > 0) result = 1 << (value + 31); return result; }

u16 func_8004EB38(u16 *arg0) { return *arg0; }

extern u8 D_80097154[];
s32 func_8004EB40(u16 *arg0) { u16 index = *arg0; return *(s32 *)(D_80097154 + (index * 8)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004EB58.s")
#endif
