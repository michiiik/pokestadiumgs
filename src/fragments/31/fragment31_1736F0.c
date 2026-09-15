#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1736F0/func_88200470.s")

extern s32 func_8005370C(s32, s32);
extern s32 func_8005CF20(s32, s32, s32);

s32 func_88200598(s32 arg0, s32 arg1, s32 arg2) {
    s32 result = 0;

    switch (arg0) {
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
            result = func_8005CF20(arg0, arg1, arg2);
            break;
        case 16:
        case 17:
        case 18:
        case 22:
        case 23:
            result = func_8005370C(arg0, arg2);
            break;
    }

    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1736F0/func_882005F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1736F0/func_882007B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1736F0/func_882009D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1736F0/func_88200BC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1736F0/func_88200D04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1736F0/func_88200DCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1736F0/func_88200EDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1736F0/func_88201048.s")
#endif
