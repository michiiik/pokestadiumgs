#include "global.h"


#ifdef VERSION_US
void PointerList_SwapRange(void** arg0, void** arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < arg2; i++) {
        void* tmp = *arg0;
        *arg0++ = *arg1;
        *arg1++ = tmp;
    }
}

s32* Sort_SelectMedianPointer(s32* arg0, s32* arg1, s32* arg2, s32 (*arg3)(s32, s32)) {
    return (arg3(*arg0, *arg1) < 0)   ? (arg3(*arg1, *arg2) < 0)   ? arg1
                                        : (arg3(*arg0, *arg2) < 0) ? arg2
                                                                   : arg0
           : (arg3(*arg1, *arg2) > 0) ? arg1
           : (arg3(*arg0, *arg2) > 0) ? arg2
                                      : arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_16AA30/func_88004B60.s")
#endif
