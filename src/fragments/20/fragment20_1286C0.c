#include "global.h"


#ifdef VERSION_US
extern s32 D_82615330;
void func_826005F0(s32 arg0) {
    D_82615330 = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_1286C0/func_826005FC.s")

extern void func_80008648();
extern void func_800088DC();
extern void func_826005FC();
extern void func_82602710(s32);
extern void func_826042A0();
extern s32 D_8261533C;
void func_826007E4(void) {
    func_800088DC();
    func_82602710(D_82615330);
    func_826042A0();
    if (D_8261533C != 0) {
        func_826005FC();
    }
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_1286C0/func_82600838.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_1286C0/func_826009A0.s")
#endif
