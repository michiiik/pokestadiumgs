#include "global.h"


#ifdef VERSION_US
s32 func_88902B70(u8 *arg0) {
    s32 var_v1;

    var_v1 = 0;
loop_1:
    if ((*(u8 *)((u8 *)(&arg0[var_v1]) + (2))) != 0) {
        var_v1 = (var_v1 + 1) & 0xFF;
        if (var_v1 < 4) {
            goto loop_1;
        }
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8160/func_88902BA0.s")

extern s32 func_88902B70(u8 *); extern u8 D_889041A0; extern u8 func_80062E10(u8); void func_88902BE0(u8 *arg0, u8 arg1) { s32 i = func_88902B70(arg0); if (i < 4) i &= 0xff; else i = D_889041A0; *(u8 *)(arg0 + i + 2) = arg1; *(u8 *)(arg0 + i + 0x18) = func_80062E10(arg1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8160/func_88902C3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8160/func_88902CF0.s")

extern s32 func_80064800(u8); extern void func_88902CF0(void *, void *, s8); void func_88902E4C(u32 *arg0, u8 *arg1, s8 arg2) { *arg0 = func_80064800(arg1[0]); func_88902CF0(arg0, arg1, arg2); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8160/func_88902E8C.s")

u8 func_88903084(u8 arg0) { u8 result = 0; switch (arg0) { case 0x1e: result=0x1f; break; case 0x21: result=0x22; break; case 0x23: result=0x24; break; case 0x27: result=0x28; break; default: break; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8160/func_889030D8.s")

u8 func_8890311C(u8 arg0) {
    u8 result = 0;
    if (arg0 != 0x19) {
        if (arg0 == 0x85) {
            result = 0x87;
        }
    } else {
        result = 0x1A;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8160/func_88903150.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8160/func_889031A4.s")

u8 func_889031EC(u8 arg0) { u8 result = 0; switch (arg0) { case 0x2c: result=0xb6; break; case 0xbf: result=0xc0; break; default: break; } return result; }

extern u8 func_8005D92C(s32 index);
extern s32 fragment29_main(u8);
s32 func_88903220(u8 *arg0, s8 arg1) {
    u8 result = 0;

    if ((arg0[0x1E] & 1) == 0) {
        if (arg0[1] != 0x70) {
            switch (arg0[0]) {
                case 0x40: result = 0x41; break;
                case 0x43: result = 0x44; break;
                case 0x4B: result = 0x4C; break;
                case 0x5D: result = 0x5E; break;
            }
            if (result == 0) {
                if (fragment29_main(func_8005D92C(arg1)) == 0) {
                    switch (arg0[0]) {
                        case 0x3D:
                            if (arg0[1] == 0x52) result = 0xBA;
                            break;
                        case 0x4F:
                            if (arg0[1] == 0x52) result = 0xC7;
                            break;
                        case 0x5F:
                            if (arg0[1] == 0x8F) result = 0xD0;
                            break;
                        case 0x7B:
                            if (arg0[1] == 0x8F) result = 0xD4;
                            break;
                        case 0x75:
                            if (arg0[1] == 0x97) result = 0xE6;
                            break;
                        case 0x89:
                            if (arg0[1] == 0xAC) result = 0xE9;
                            break;
                    }
                }
            }
        }
    }
    return result;
}
#endif
