#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_881038A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_88103A64.s")

extern void *D_80087200;
extern void func_80049ED8(void *);
extern s32 D_880068B8;
void func_88103B90(void) {
    func_80049ED8(D_80087200);
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_88103BB8.s")

extern void func_88103BB8(void);
extern s32 D_880068B4;
void func_88103CAC(void) {
    func_80049ED8(D_80087200);
    D_880068B4 = 1;
    func_88103BB8();
}

extern void *D_88104EA0;
extern void func_88004990(s32, s32);
void func_88103CE0(void) {
    func_88004990(**(u8 **)((u8 *)D_88104EA0 + 0), 0);
    func_88004990(**(u8 **)((u8 *)D_88104EA0 + 4), 0);
    D_880068B8 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_88103D30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_88103DC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_88104214.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_88104730.s")
#endif
