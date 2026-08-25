#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F001CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00460.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00580.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F005F8.s")

extern void func_800226C0(s32);

void func_82F00644(void *arg0, s32 arg1) {
    if (arg1 != 0) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 1;
        func_800226C0(3);
    }
}

extern void func_800226C0(s32);

void func_82F00670(void *arg0, s32 arg1) {
    if (arg1 != 0) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 1;
        func_800226C0(3);
    }
}

extern void func_800226C0(s32);

void func_82F0069C(void *arg0, s32 arg1) {
    if (arg1 != 0) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 1;
        func_800226C0(3);
    }
}

extern void func_800226C0(s32);

void func_82F006C8(void *arg0, s32 arg1) {
    if (arg1 != 0) {
        (*(s8 *)((u8 *)(arg0) + (0x1E))) = 6;
        func_800226C0(3);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F006F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00730.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00788.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F007C0.s")

extern u8 D_800D0510[];
extern void func_80007444(void *, s32, s32, s32, s32, s32);
void func_82F00818(s32 arg0, s32 arg1, s32 arg2) {
    func_80007444(D_800D0510, 0, 0, 0x280, 0x1E0, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00860.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00A3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00B28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00C2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F00CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F01220.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F012AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F01658.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F01958.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F019CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F01A5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F01BAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F01C34.s")

extern void func_80008648();
extern void func_800088DC();
extern void func_818017A8();
extern void func_81805308(s32 *);
extern u8 D_82F032C0;

void func_82F01D38(s32 arg0) {
    func_800088DC();
    func_818017A8();
    func_81805308(&D_82F032C0);
    func_80008648();
}

s32 func_82F01C34(s32);
void func_82F01D74(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    do {
        temp_v0 = func_82F01C34(var_s0);
        var_s0 = temp_v0;
        func_82F01D38(temp_v0);
    } while (var_s0 != 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F01DC4.s")

extern void func_80006D3C();
extern void func_80008574();
extern void func_80047610();
extern void func_8004C398();

void func_82F01EC8(s32 arg0, s32 arg1) {
    func_80008574();
    func_80047610();
    func_8004C398();
    func_80006D3C();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/8/fragment8_code/func_82F01F04.s")
#endif
