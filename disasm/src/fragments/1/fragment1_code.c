#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500124.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500198.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/1/fragment1_code/func_83500200.s")

s32 func_80040E80(s32, s32 *);
extern void func_80041E2C();
extern u8 D_83503BEC;
extern u8 D_83503C24;
extern u8 D_83503F30;
extern s32 D_83503F54;
extern s32 D_83503F6C;
extern u8 D_83503F70;
extern s32 func_800030D0(s32, s32);
s32 func_80002B24(void);
extern void func_80003120(s32);
void func_8003EFE0(void);
void func_87F02CB0(s32 arg0, s32 arg1);
void func_8003F018(s32 arg0);
void func_8350026C(void) {
    s32 sp1C[3];
    s32 temp_v0;
    temp_v0 = func_800030D0(func_80002B24(), 0);
    sp1C[0] = temp_v0;
    D_83503F54 = func_80040E80(temp_v0, &D_83503C24);
    D_83503F6C = func_80040E80(sp1C[0], &D_83503BEC);
    func_80003120(sp1C[0]);
    func_8003EFE0();
    func_80041E2C();
    func_87F02CB0((s32) &D_83503F30, 0x64);
    func_8003F018((s32) &D_83503F70);
}

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
