#include "global.h"


#ifdef VERSION_US
extern s32 D_880068B8;
void func_8822E870(void) {
    D_880068B8 = 0;
}

void func_8822E87C(void) {
    D_880068B8 = 1;
}

extern void func_88208FF0();
extern s32 D_880068B4;
extern s32 D_88234960;
extern s32 D_88804058;
void func_8822E88C(void) {
    D_880068B4 = 1;
    if ((D_88234960 == 4) && (D_88804058 != 0)) {
        func_88208FF0();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1AF0/func_8822E8D8.s")
#endif
