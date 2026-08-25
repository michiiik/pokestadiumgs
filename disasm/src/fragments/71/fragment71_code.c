#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F300020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F3000E8.s")

extern void func_80007820(s32 *, s32);
extern void func_80008648();
extern void func_800088DC();
extern void func_8F3000E8();
extern u8 D_800D0510;

void func_8F300770(void) {
    func_800088DC();
    func_80007820(&D_800D0510, 1);
    func_8F3000E8();
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F3007B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F300AD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F300CAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F300D08.s")
#endif
