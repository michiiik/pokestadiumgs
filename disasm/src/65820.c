#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064C20.s")
#endif

#ifdef VERSION_US
extern s32 D_80128BE0;

s32 func_80064C88(void) {
    return D_80128BE0;
}
#endif

#ifdef VERSION_US
s32 func_80064C94(s32 value) { s32 result = 0; if (value >= 0 && value < 4) { D_80128BE0 = value; result = 1; } return result; }
#endif

#ifdef VERSION_US
extern s16 D_80128BE8;

void func_80064CB8(s32 arg0) {
    D_80128BE8 = arg0;
}
#endif

#ifdef VERSION_US

s16 func_80064CC4(void) {
    return D_80128BE8;
}
#endif

#ifdef VERSION_US
extern s16 D_80128BEA;

void func_80064CD0(s32 arg0) {
    D_80128BEA = arg0;
}
#endif

#ifdef VERSION_US

s16 func_80064CDC(void) {
    return D_80128BEA;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064CE8.s")
#endif

#ifdef VERSION_US
extern void func_80005EE0();
extern void func_80005F0C();
extern void func_80049ED0();
void func_80064D28(void) { func_80005EE0(); func_80005F0C(); func_80049ED0(); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064D58.s")
#endif

void func_80064DF4(void) {
}

#ifdef VERSION_US
extern s32 D_8009DE94;
extern s32 D_80128BE4;
s32 func_80064DFC(s32 value) { s32 result = 0; if (value != D_8009DE94) { D_80128BE4 = D_8009DE94; D_8009DE94 = value; result = 1; } return result; }
#endif

#ifdef VERSION_US

s32 func_80064E2C(void) {
    return D_8009DE94;
}
#endif

#ifdef VERSION_US

s32 func_80064E38(void) {
    return D_80128BE4;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064E44.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064ED0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064F54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/Game_Thread.s")
#endif

#ifdef VERSION_US
void func_80065210(s32 arg0) { }
#endif
