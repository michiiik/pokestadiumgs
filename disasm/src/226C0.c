#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/226C0/func_80021AC0.s")

extern void func_80028140(void);
extern void func_80035020(s32 mode);
extern void func_800248A0(void);
extern void func_80018728(u32 command, ...);
extern void func_80025EB0(s32, s32, s32, s32);

void Audio_InitializeTaskState(void) {
    func_80021AC0();
    func_80028140();
    func_80035020(2);
    func_800248A0();
    func_80018728(0xE40000FF, func_80025EB0);
}

void func_80021B50(void) {
    func_80018728(0x82010000, 0);
}

extern void *func_80017AC0(void);
extern void func_80034FE0(void);
extern void *D_80090090;

void *Audio_BuildSchedulerTask(void) {
    D_80090090 = func_80017AC0();
    func_80034FE0();
    return D_80090090;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/226C0/func_80021BBC.s")
#endif
