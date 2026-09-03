#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83300020.s")

s32 func_83300398(s32 arg0, s32 arg1) {
    return arg0 + arg1 / 2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833003B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833005F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_8330084C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83300CB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833015C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_8330173C.s")

extern u8 D_8330A2B0;

s32 func_833018B8(s32 arg0, void *arg1) {
    if (arg0 == 2) {
        (*(u8 *)((u8 *)(arg1) + (0x18))) = (u8) (*(u8 *)((u8 *)(&D_8330A2B0) + (0x10C)));
        (*(u8 *)((u8 *)(arg1) + (0x19))) = (u8) (*(u8 *)((u8 *)(&D_8330A2B0) + (0x10D)));
        (*(u8 *)((u8 *)(arg1) + (0x1A))) = (u8) (*(u8 *)((u8 *)(&D_8330A2B0) + (0x10E)));
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833018E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833019CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83301C60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83302088.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83302180.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83302290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83302AC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83302D8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_8330309C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83303220.s")

extern void *D_800D0510;
extern void *D_80087200;
extern s32 D_833090AC;
extern u8 D_8330A288[];
extern s32 D_8330A2C4;
extern s32 D_8330A2EC;
extern s32 D_8330A4C8;
extern void func_800088DC(void);
extern void GfxImage_FillCurrent(void *, u16);
extern void GeoRender_AdvanceFrameCounter(void);
extern void func_8003C6B8(s32);
extern void func_83302290(void);
extern void func_83302AC8(void);
extern void func_83302D8C(void);
extern void func_83303220(void);
extern void func_81A0022C(void *);
extern void func_80008648(void);
void func_83303564(void) {
    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 1);
    if (D_8330A2EC == 1) {
        func_83303220();
    }
    if (D_8330A2C4 == 0) {
        GeoRender_AdvanceFrameCounter();
    }
    func_8003C6B8(D_8330A4C8);
    func_83302D8C();
    if ((*(u16 *)((u8 *)D_80087200 + 6) & 0x2000) && (D_833090AC == 1)) {
        func_83302AC8();
    }
    if (D_8330A2C4 == 1) {
        func_83302290();
    }
    func_81A0022C(D_8330A288);
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83303640.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83303AB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83305C1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83306BF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83306D0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83307088.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833078C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83307AAC.s")

extern s32 D_83308E2C;
extern void func_80021ED8(s32);
s32 func_83307C2C(s32 arg0) {
    if (arg0 > 0) {
        arg0 += 1;
    }
    if ((D_83308E2C * 5 + 5) < arg0) {
        func_80021ED8(0x57);
        arg0 = 0;
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83307C7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833084B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_8330853C.s")
#endif
