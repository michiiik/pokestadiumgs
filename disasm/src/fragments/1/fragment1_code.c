#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500124.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500198.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500200.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_8350026C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500300.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500708.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500C14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_835012C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_8350182C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83501D3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83501DC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83502BFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83502EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503048.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503324.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_835034A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503548.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_835035F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503678.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503720.s")

extern void func_83502EF0();
s32 func_83503720(s32);
extern void func_800086A4(s32);
extern void func_80007AEC(s32);
void func_80064D28(void);
void func_835038BC(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    func_80007AEC(0x1E);
    do {
        func_80064D28();
        func_83502EF0();
        temp_v0 = func_83503720(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 5);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83503918.s")
#endif
