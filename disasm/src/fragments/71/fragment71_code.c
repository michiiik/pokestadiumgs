#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F300020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F3000E8.s")

extern void GfxImage_FillCurrent(s32 *, s32);
extern void func_80008648();
extern void func_800088DC();
extern void func_8F3000E8();
extern u8 D_800D0510;

void func_8F300770(void) {
    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 1);
    func_8F3000E8();
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F3007B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F300AD0.s")

extern void func_80007AEC(s32);
extern void func_800086A4(s32);
extern void func_80064D28();
s32 func_8F300AD0(s32);
void func_8F300CAC(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    func_80007AEC(5);
    do {
        func_80064D28();
        func_8F300770();
        temp_v0 = func_8F300AD0(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F300D08.s")
#endif
