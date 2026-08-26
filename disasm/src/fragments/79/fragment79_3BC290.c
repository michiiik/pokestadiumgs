#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414CA00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414CA80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414CB10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414CB74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414CD18.s")

extern u8 *func_84154B64(u8);
extern u16 func_84148560(u16, u16, u8);
void func_8414CDB8(u8 *arg0, u8 arg1, u8 arg2) {
    u8 *value;
    value = func_84154B64(arg1);
    *(u16 *)(arg0 + arg1 * 2 + 0x16) =
        func_84148560(*(u16 *)(value + 0x28), *(u16 *)(value + 0x2A), arg2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414CE08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414CEE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414CF74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D008.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D198.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D348.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D51C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D610.s")

s32 func_84156618(u8 arg0, u8 arg1, u8 arg2);
u8 *func_84154B30(u8 arg0);
u8 func_80062D20(u8 arg0);
u8 func_84154B18(void);
s32 func_84156618(u8 arg0, u8 arg1, u8 arg2);
u8 *func_84154B30(u8 arg0);
u8 func_80062D20(u8 arg0);
u8 func_84154B18(void);
s32 func_8414D680(u8 arg0, u8 arg1) {
    s32 sp1C;
    u8 temp_v0;

    sp1C = 0;
    if (func_84156618(arg0, (*(u8 *)((u8 *)(func_84154B30(arg0)) + (1))), 0x10U) != 0) {
        temp_v0 = func_80062D20(arg1);
        switch (temp_v0) {                          /* irregular */
        case 0x27:
        case 0x4B:
        case 0x91:
            sp1C = 1;
            break;
        case 0x97:
            if (func_84154B18() != 2) {
                sp1C = 1;
            }
            break;
        }
    }
    return sp1C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D720.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D910.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D9B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414DA70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414DB14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414DC58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414DD94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414E224.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414E2A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414E508.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414E5B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414E658.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414E760.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414E7D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414E880.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414EA4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414EB90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414EC18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414ECE0.s")

extern void func_8414D720(s32, u8);
extern void func_8414E880(s32);
extern void func_8414EC18(s32);
u8 func_84154B24();
void func_8414ED5C(s32 arg0) {
    u8 sp1F;
    u8 sp1E;
    u8 temp_v0;

    temp_v0 = func_84154B24();
    sp1F = temp_v0;
    sp1E = 1 - temp_v0;
    func_8414E880(arg0);
    func_8414EC18(arg0);
    func_8414D720(arg0, sp1F);
    func_8414D720(arg0, sp1E);
}

void func_8414EDB4(s32 arg0) {
    u8 sp27;
    u8 sp26;
    u8 temp_v0;

    temp_v0 = func_84154B24();
    sp27 = temp_v0;
    sp26 = 1 - temp_v0;
    func_8414E880(arg0);
    func_8414EC18(arg0);
    func_8414ECE0(arg0);
    func_8414D720(arg0, sp27);
    func_8414D720(arg0, sp26);
}
#endif
