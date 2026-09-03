#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_8290FDB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_8290FE04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_8290FF14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910258.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910510.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910740.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910B30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910FC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82911418.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_829115E0.s")

extern void func_800088DC(void);
extern void func_829115E0(void);
extern void func_80008648(void);
void func_82911850(void) {
    func_800088DC();
    func_829115E0();
    func_80008648();
}

extern void StageFade_StartFromOpaque(s32);
extern s32 D_8291BE70;
void func_82911880(void) {
    s32 var_s0;

    StageFade_StartFromOpaque(0xC);
    var_s0 = 0;
    do {
        func_82911850();
        var_s0 += 1;
    } while (var_s0 != 0xC);
    D_8291BE70 = 1;
}

extern void func_80064D28();
extern void func_82910258();
void func_829118D4(void) {
    if (D_8291BE70 != 0) {
        do {
            func_80064D28();
            func_82910258();
            func_82911850();
        } while (D_8291BE70 != 0);
    }
}

extern void StageFade_StartFromTransparent(s32);
void func_8291192C(void) {
    s32 var_s0;

    StageFade_StartFromTransparent(0x10);
    var_s0 = 0;
    do {
        func_82911850();
        var_s0 += 1;
    } while (var_s0 != 0x10);
}

extern void func_8290FE04(s16);

void func_82911974(s16 arg0) {
    func_8290FE04(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_8291199C.s")
#endif
