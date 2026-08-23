#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/226C0/func_80021AC0.s")

extern void func_80021AC0(s32, s32);
extern void func_80028140(void);
extern void func_80035020(s32);
extern void func_800248A0(void);
extern void func_80018728(u32, ...);
extern void func_80025EB0(s32, s32, s32, s32);

void func_80021B00(void) {
    func_80021AC0(0, 0);
    func_80028140();
    func_80035020(2);
    func_800248A0();
    func_80018728(0xE40000FF, func_80025EB0);
}

void func_80021B50(void) {
    func_80018728(0x82010000, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/226C0/func_80021B74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/226C0/func_80021BBC.s")
#endif
