#include "global.h"


#ifdef VERSION_US
void func_80021AC0(s32 arg0, s32 arg1) {
    if (arg0 || arg1) {
        /* intentionally empty */
    }
    func_80015AB8();
    func_80018704(0x41010000, 0x3F2147AE);
    func_80018704(0x41000000, 0x3F4F5C29);
}

extern void func_80021AC0(s32, s32);
extern void func_80028140(void);
extern void func_80035020(s32);
extern void func_800248A0(void);
extern void func_80018728(u32, ...);
extern void func_80025EB0(s32, s32, s32, s32);

void Audio_InitializeTaskState(void) {
    func_80021AC0(0, 0);
    func_80028140();
    func_80035020(2);
    func_800248A0();
    func_80018728(0xE40000FF, func_80025EB0);
}

void func_80021B50(void) {
    func_80018728(0x82010000, 0);
}

extern s32 D_80090090;
extern s32 func_80017AC0(void);
extern void func_80034FE0(void);
s32 Audio_BuildSchedulerTask(void) {
    s32 *address;
    address = &D_80090090;
    *address = func_80017AC0();
    func_80034FE0();
    if (*address == 0) {
        return 0;
    }
    return *address;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/226C0/func_80021BBC.s")
#endif
