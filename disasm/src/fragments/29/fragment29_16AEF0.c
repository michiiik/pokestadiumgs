#include "global.h"


#ifdef VERSION_US
extern u8 D_8800EF20;

void func_88004EB0(void) {
    D_8800EF20 = 10;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_16AEF0/func_88004EC0.s")
#endif
