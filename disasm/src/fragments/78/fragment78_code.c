#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F900020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F9000D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F900200.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F900284.s")

extern u8 D_8F901630;
extern s32 D_8F91163C;
extern s32 D_8F911664;

void func_8F900574(void) {
    D_8F911664 = (s32) *(&D_8F901630 + D_8F91163C);
}


void func_8F900594(void) {
    *(&D_8F901630 + D_8F91163C) = (s8) D_8F911664;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F9005B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F900690.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F90083C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F9008D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F900968.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F9009E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F900A6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F900F14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F901078.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F90132C.s")

extern void func_80049ED8(s32);
extern void func_8F9008D0(s32);
extern s32 D_80087200;
extern s32 D_8F911630;
extern s32 D_8F911634;
extern s32 D_8F911638;
extern s32 D_8F911644;
extern s32 D_8F911648;
extern s32 D_8F911668;
void func_8F9013E4(s32 arg0) {
    D_8F911668 = arg0;
    D_8F911648 = 0;
    D_8F911644 = 1;
    D_8F911638 = 0;
    D_8F911630 = 0;
    D_8F911634 = 0;
    func_80049ED8(D_80087200);
    func_8F9008D0(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/78/fragment78_code/func_8F901448.s")
#endif
