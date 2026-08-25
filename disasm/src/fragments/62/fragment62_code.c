#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/62/fragment62_code/func_86C00020.s")

extern u8 D_800D0510[];
extern u8 D_86C00350[];
extern void func_800088DC(void);
extern void func_80007820(void *, s32);
extern void func_81A0022C(void *);
extern void func_80008648(void);
void func_86C00070(void) {
    func_800088DC();
    func_80007820(&D_800D0510, 0x8421);
    func_81A0022C(&D_86C00350);
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/62/fragment62_code/func_86C000B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/62/fragment62_code/func_86C00148.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/62/fragment62_code/func_86C001CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/62/fragment62_code/func_86C002C4.s")
#endif
