#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290E5F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290E6D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290E76C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290E81C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290E8D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290EAC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290EFA0.s")
#endif

void func_8290F36C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290F374.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290F42C.s")
#endif

#ifdef VERSION_US
extern void func_800088DC(void);
extern void func_8290F42C(void);
extern void func_80008648(void);
void func_8290FA00(void) {
    func_800088DC();
    func_8290F42C();
    func_80008648();
}
#endif

#ifdef VERSION_US
extern s32 D_8291BC40;
extern s32 D_8291BC44;
extern void StageFade_StartFromOpaque(s32);
extern void func_8290FA00(void);
extern void func_80021ED8(s32);
void func_8290FA30(void) {
    s32 var_s0;

    D_8291BC40 = 1;
    D_8291BC44 = 1;
    StageFade_StartFromOpaque(0xC);
    var_s0 = 0;
    do {
        func_8290FA00();
        var_s0 += 1;
    } while (var_s0 != 0xE);
    func_80021ED8(0x3F);
    D_8291BC44 = 0;
}
#endif

#ifdef VERSION_US
extern void func_80064D28(void);
extern void func_8290E8D8(void);
void func_8290FA9C(void) {
    func_80064D28();
    func_8290E8D8();
    func_8290FA00();
}
#endif

#ifdef VERSION_US
extern void StageFade_StartFromTransparent(s32);
extern void func_800225C4(s32);
void func_8290FACC(void) {
    s32 var_s0;

    func_800225C4(0x10);
    StageFade_StartFromTransparent(0x10);
    var_s0 = 0;
    do {
        func_8290FA00();
        var_s0 += 1;
    } while (var_s0 != 0x10);
}
#endif

#ifdef VERSION_US
extern void func_8290E5F0(void);
void func_8290FB1C(void) {
    func_8290E5F0();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290FB3C.s")
#endif
