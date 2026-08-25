#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_81800020.s")
#endif

#ifdef VERSION_US
s32 func_80001FF0();
s32 func_80008970();

f32 func_818006B4(void) {
    s32 sp1C;

    sp1C = func_80008970();
    return ((f32) sp1C * 60.0f) / (f32) func_80001FF0();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_818006FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_818008E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_81800A90.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_81800C18.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_81800D70.s")
#endif

#ifdef VERSION_US
extern f32 D_81805CD4;
s32 func_81800DE4(f32 arg0) {
    s32 temp_v1;

    temp_v1 = (s32) arg0 & 0x1F;
    return ((temp_v1 << 0xA) + (s32) (((arg0 - (f32) temp_v1) + D_81805CD4) * 1024.0f)) & 0xFFFF;
}
#endif

void func_81800E30(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_81800E38.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_818011EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_8180128C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_8180132C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_81801388.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_81801420.s")
#endif

#ifdef VERSION_US
extern f32 D_81805920;
f32 func_818014A8(void) {
    return D_81805920;
}
#pragma C_FUNCTION_PADDING(12)
#endif
