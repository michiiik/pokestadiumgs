#include "global.h"


#ifdef VERSION_US
extern void func_800226C0(s32);
extern void func_88220AD0(s32, s32);
extern s32 D_88234660;
void func_8821C298(void);
void func_88001900(void);
extern s32 D_880068B4;
void func_88232860(void) {
    func_800226C0(0x5E);
    func_8821C298();
    if (D_88234660 != 0) {
        func_88220AD0(0x17C, 0x11F);
        return;
    }
    func_88001900();
    D_880068B4 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A5AE0/func_882328C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A5AE0/func_882329A4.s")

extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
extern void func_882328C0(void);
extern void func_882329A4(void);
extern void func_88232860(void);
void func_88232B50(void) {
    func_88005B60(0xE, func_882328C0, func_882329A4, func_88232860);
}
#endif
