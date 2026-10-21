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

/* mkdraft:func_88200D04 begin */
extern s32 func_882005F8(void);
extern s32 func_882007B0(void);
extern s32 func_882009D4(void);
extern s32 func_88200BC4(void);
extern u8 D_882345E0;



s32 func_88200D04(u8 arg0) {
    s32 ret = 0;

    D_882345E0 = 0;
    if (arg0 & 1) {
        if (func_882005F8() != 0) {
            ret = 1;
        }
    }
    if (arg0 & 2) {
        if (func_882007B0() != 0) {
            ret = 1;
        }
    }
    if (arg0 & 4) {
        if (func_882009D4() != 0) {
            ret = 1;
        }
    }
    if (arg0 & 8) {
        if (func_88200BC4() != 0) {
            ret = 1;
        }
    }
    return ret;
}
/* mkdraft:func_88200D04 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1736F0/func_88200DCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1736F0/func_88200EDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1736F0/func_88201048.s")
#endif
