#include "global.h"


#ifdef VERSION_US
s32 fragment80_main(const u8 *arg0) {
    return *(u16 *)(*(u8 **)(arg0 + 0x1C) + 0x2E) < *(u16 *)(*(u8 **)(arg0 + 0x18) + 0x2E);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_4194A0/func_84200038.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_4194A0/func_84200094.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_4194A0/func_842000EC.s")

extern u8 func_84203464(void);
void func_84200150(u8 *arg0, u8 arg1) {
    u32 value = func_84203464();
    *(u8 **)(arg0 + 0x10) += (s32)((*(u8 **)(arg0 + 0x14))[0x0C] * value * arg1) / 0xFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_4194A0/func_842001BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_4194A0/func_84200258.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_4194A0/func_842002F4.s")

extern u8 func_84200094(u8 *, u8);
void func_84200390(u8 *arg0, u8 arg1) {
    if (func_84200094(*(u8 **)(arg0 + 0x1C), arg0[3])) {
        u32 value = func_84203464();
        *(u8 **)(arg0 + 0x10) += (s32)((*(u8 **)(arg0 + 0x14))[0x10] * value * arg1) / 0xFF;
    }
}

extern u8 func_84203470(void);
void func_84200418(u8 *arg0, u8 arg1, u8 arg2, u8 arg3) {
    u32 value = func_84203470();
    *(u8 **)(arg0 + 0x10) += (s32)((*(u8 **)(arg0 + 0x14))[arg2 + 0x17] * arg1 * arg3 * value) / 0xFF;
}

void func_842004A8(u8 *arg0, u8 arg1, u8 arg2, u8 arg3) {
    u32 value = func_84203470();
    *(u8 **)(arg0 + 0x10) += (s32)((*(u8 **)(arg0 + 0x14))[arg1 + 0x1E] * arg2 * arg3 * value) / 0xFF;
}

void func_84200538(u8 *arg0) {}

void func_84200540(u8 *arg0) {}

void func_84200548(u8 *arg0) {}

void func_84200550(u8 *arg0) {}

extern u8 func_84203494(void);
void func_84200558(u8 *arg0, u8 arg1) {
    if (fragment80_main(arg0)) {
        u32 value = func_84203494();
        *(u8 **)(arg0 + 0x10) += (s32)((*(u8 **)(arg0 + 0x14))[0x11] * arg1 * value) / 0xFF;
    }
}

void func_842005D4(u8 *arg0) { u32 value = func_842034A0(); *(u8 **)(arg0 + 0x10) += (*(u8 **)(arg0 + 0x14))[0x25] * value; }

void func_84200614(u8 *arg0) {}

void func_8420061C(u8 *arg0) {}

void func_84200624(u8 *arg0) { u32 value = func_842034A0(); *(u8 **)(arg0 + 0x10) += (*(u8 **)(arg0 + 0x14))[0x26] * value; }

void func_84200664(u8 *arg0) { u32 value = func_842034A0(); *(u8 **)(arg0 + 0x10) += (*(u8 **)(arg0 + 0x14))[0x27] * value; }

void func_842006A4(u8 *arg0, u8 arg1) {
    u32 value = func_84203494();
    *(u8 **)(arg0 + 0x10) += (s32)((*(u8 **)(arg0 + 0x14))[0x12] * arg1 * value) / 0xFF;
}

void func_84200710(u8 *arg0) {}

void func_84200718(u8 *arg0) { u32 value = func_842034A0(); *(u8 **)(arg0 + 0x10) += (*(u8 **)(arg0 + 0x14))[0x28] * value; }

void func_84200758(u8 *arg0) {}

void func_84200760(u8 *arg0) {}

extern s32 func_84200038(u8 *arg0, s32 arg1);
s32 func_84200768(u8 *arg0) {
    return func_84200038(*(u8 **)(arg0 + 0x1C), 0x16);
}

void func_8420078C(u8 *arg0) { u32 value = func_842034A0(); *(u8 **)(arg0 + 0x10) += (*(u8 **)(arg0 + 0x14))[0x29] * value; }

void func_842007CC(u8 *arg0) {}

void func_842007D4(u8 *arg0) {}

void func_842007DC(u8 *arg0) {}

void func_842007E4(u8 *arg0) {}

void func_842007EC(u8 *arg0) {}

void func_842007F4(u8 *arg0) {}

void func_842007FC(u8 *arg0) {}

void func_84200804(u8 *arg0) {}

void func_8420080C(u8 *arg0) {}

s32 func_84200814(u8 *arg0) {
    return func_84200038(*(u8 **)(arg0 + 0x18), 8);
}

void func_84200838(u8 *arg0) {}

void func_84200840(u8 *arg0) {}

void func_84200848(u8 *arg0) {}

void func_84200850(u8 *arg0) {}

void func_84200858(u8 *arg0) {}

void func_84200860(u8 *arg0) {}

void func_84200868(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_4194A0/func_84200870.s")

void func_842008F8(u8 *arg0) {}

void func_84200900(u8 *arg0) { u32 value = func_842034A0(); *(u8 **)(arg0 + 0x10) += (*(u8 **)(arg0 + 0x14))[0x2E] * value; }

void func_84200940(u8 *arg0) {}

void func_84200948(u8 *arg0) {}

void func_84200950(u8 *arg0) {}

void func_84200958(u8 *arg0) {}

void func_84200960(u8 *arg0) {}

void func_84200968(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_4194A0/func_84200970.s")
#endif
