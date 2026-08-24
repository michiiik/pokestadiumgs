#include "global.h"


#ifdef VERSION_US
extern void func_8414FC30(u8 *, u8);
extern void func_84150268(u8 *, u8);
extern void func_8414D198(u8 *, u8);
extern void func_84153E28(u8 *, u8);
extern void func_8414D348(u8 *, u8);
void func_8414EE20(u8 *arg0, u8 arg1) {
    func_8414FC30(arg0, (u8)arg1);
    func_84150268(arg0, (u8)arg1);
    func_8414D198(arg0, (u8)arg1);
    func_84153E28(arg0, (u8)arg1);
    func_8414D348(arg0, (u8)arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BE6B0/func_8414EE88.s")

extern void func_8414EE88(u8 *);
void func_8414EFD0(u8 *arg0) {
    arg0[1] = 0;
    func_8414EE88(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BE6B0/func_8414EFF0.s")
#endif
