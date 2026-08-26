#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804720.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_818047E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804858.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_818048A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804954.s")

extern void func_81804858(s32);
void WidgetTree_OpenMessagePanel_fragment4(u8 *arg0) {
    func_81804858(*(s32 *)arg0);
}

s32 func_81804A20(u8 *arg0) {
    return *(u16 *)(arg0 + 0x1A) == 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804A2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804AE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804B74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804BC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804FD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81805308.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81805428.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81805474.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_818054D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81805524.s")

s32 func_81805594(u8 *arg0, u8 *arg1) { return 1; }

s32 StageContext_GetFadeMode(s32);
s32 func_81805524();

s32 func_818055A4(void) {
    s32 var_a0;

    var_a0 = func_81805524() != 0;
    if (var_a0 == 0) {
        var_a0 = StageContext_GetFadeMode(var_a0) != 0;
    }
    return var_a0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_818055E0.s")

extern void func_8180567C(s32, s32, s32);
extern void func_818057D0();

void func_81805644(s32 arg0, s32 arg1, s32 arg2) {
    func_818057D0();
    func_8180567C(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_8180567C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_818057D0.s")
#endif
