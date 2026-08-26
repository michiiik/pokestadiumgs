#include "global.h"


#ifdef VERSION_US
extern void func_8004300C();
extern void func_88600020();
extern void func_88600074();
extern void func_88004FF0();
extern u16 D_88308934;
extern u8 D_88308E06[];
extern u8 D_88308E09[];
extern s8 D_88308E04;
void func_88300020(s32 arg0, s32 arg1) { func_8004300C(arg0); func_88600020(arg1); func_88600074(arg0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88300054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88300230.s")

s32 func_8004C4B0(s32 value);
extern void func_8004C8C0();
void func_883002B8(void) {
    func_8004C4B0(1);
    func_8004C4B0(2);
    func_8004C4B0(3);
    func_8004C4B0((s32) D_88308934);
    func_8004C8C0(0x14C);
    func_88004FF0(0x3B);
}

void func_88300304(void) { func_8004C8C0(155); func_8004C8C0(265); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_8830032C.s")

extern void func_88306404(s32);
void func_883004E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 != 0) {
        func_88306404(0);
    }
    if (arg1 != 0) {
        func_88306404(1);
    }
    if (arg2 != 0) {
        func_88306404(2);
    }
    if (arg3 != 0) {
        func_88306404(3);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88300550.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_8830058C.s")

s32 func_8004C990(s32, s32);
extern void func_8004D1FC(s32);
extern void func_80044270(s32,s32,s32,s32,s32,s32,s32,s32,s32);
void func_883005B8(s32 arg0) {
    func_8004D1FC(func_8004C990(0x108, arg0 + 1));
    func_80044270((s32) (s16) ((arg0 * 0x3C) + 0x43), 0xD5, 0x3C, 0x3E, -0x10, -0x10, 0x400, 0x400, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88300640.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_8830088C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_8830099C.s")

s32 func_88300A78(void) { s32 value = D_88308E04; s32 result; if (value < 5) { result = value & 0xFF; } else { result = (8 - value) & 0xFF; } D_88308E04 = value + 1; if (D_88308E04 >= 8) { D_88308E04 = 0; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88300AC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88300B48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88301C00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88304E60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88304F5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88305020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_883051E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_883059F0.s")
#endif
