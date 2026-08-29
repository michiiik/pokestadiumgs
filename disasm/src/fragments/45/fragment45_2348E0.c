#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB0F760.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB0F87C.s")
#endif

void func_8AB0FE08(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB0FE10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB0FF40.s")
#endif

#ifdef VERSION_US
extern void func_8AB1007C(s32);
void func_8AB1005C(void) { func_8AB1007C(0); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB1007C.s")
#endif

#ifdef VERSION_US
extern s32 StageContext_GetFadeMode(void);
extern void StageFade_StartFromTransparent(s32);
s32 func_8AB100E0(s32 arg0) {
    s32 result = 0x3E;

    switch (arg0) {
    case 0:
        StageFade_StartFromTransparent(5);
        break;
    case 1:
        if (StageContext_GetFadeMode() == 1) {
            result = 0;
        }
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB10144.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB10248.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB103B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB104FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB1075C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB10AD0.s")
#endif

#ifdef VERSION_US
s32 func_8AB10D28(void) {
    return 0x45;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB10D30.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB10DE4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB10F14.s")
#endif
