#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_8414FC30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84150268.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841502D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84150330.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841503B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84150538.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841506D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84150878.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841509E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84150B14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84150EA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151128.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151270.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_8415132C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151420.s")

extern s32 func_84151420(u8 *, u8);

s32 func_84151498(u8 *arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (func_84151420(arg0, i) != 0) {
            return 1;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841514F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841515AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_8415169C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_8415178C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151838.s")

extern void func_841506D0(void *, u8, u8, u8);
extern void func_84150878(void *, u8, u8, u8);
extern void func_841509E0(void *, u8, u8, u8);

void func_841518D0(void *arg0, u8 arg1, u8 arg2) {
    u8 local = arg2 / 3;

    func_841506D0(arg0, arg1, 0xA1, local);
    func_84150878(arg0, arg1, 0xA1, local);
    func_841509E0(arg0, arg1, 0xA1, local);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151940.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151A5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151AF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151B8C.s")

void *func_84154B64(s32);
void func_84151CD8(void *arg0, u8 arg1) { s32 base; base = (s32)(u32)arg0 + 4; if ((*(u8 *)((u8 *)func_84154B64((1 - arg1) & 0xFF) + 0x19) & 8) == 0) { *(u8 *)((u8 *)(u32)base + arg1 + 8) = 0xFF; *(u8 *)((u8 *)(u32)base) |= 2; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151D3C.s")

void *func_84154B64(s32);
void func_84151DD4(void *arg0, u8 arg1) { void *state; s32 base; state = func_84154B64(arg1); base = (s32)(u32)arg0 + 4; if (((*(u8 *)((u8 *)state + 0x18) & 0x10) == 0) && (((s32)*(u16 *)((u8 *)state + 0x2A) >> 2) < (s32)*(u16 *)((u8 *)state + 0x28))) { *(u8 *)((u8 *)(u32)base + arg1 + 8) = 0xFF; *(u8 *)((u8 *)(u32)base) |= 2; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151E44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151F20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151F9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152088.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152140.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_8415220C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152308.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841523BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152408.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841524B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_8415252C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152600.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841526CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152764.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841528C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152980.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152AC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152C34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152CD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152D6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152E10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152EE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153028.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841531D4.s")

extern void func_84151B8C(s32, u8, u8);
void *func_84154B64(s32);
void func_84153304(s32 arg0, u8 arg1, u8 arg2) {
    if ((s32) (*(u8 *)((u8 *)(func_84154B64((1 - arg1) & 0xFF)) + (0xD))) < 0xD) {
        func_84151B8C(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_8415335C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153454.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153554.s")

u8 *func_84154B30(u8);
u8 func_84153718(u8 arg0) { u8 *state; u8 result; state = func_84154B30(arg0); result = 0; if ((state[0x20] & 0x80) != 0) result = 1; if ((state[3] & 1) != 0) { result++; result &= 0xFF; } if (state[0x2B] > 0) result++; return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153780.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841537FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153930.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153A64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153B10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153CB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153D94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153E28.s")
#endif
