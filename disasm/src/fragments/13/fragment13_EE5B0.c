#include "global.h"


#ifdef VERSION_US
extern u32 D_800D0510;
extern void func_80006F70(void *, s32, s32, s32, s32);
s32 func_82400530(s32 arg0, s32 arg1) {
    if (arg0 == 2) {
        func_80006F70(&D_800D0510, 0xD, 0x27, 0x126, 0xA1);
    }
    return 1;
}

void func_82400578(u8 *arg0, s32 arg1) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE5B0/func_82400584.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE5B0/func_824005D8.s")

extern u8 D_824090F3;
extern u8 D_82408A60[];
extern u8 D_82408A6C[];
void func_824006C8(s32 arg0, s32 arg1) {
    if (arg0 == 2) {
        u8 value = D_824090F3;
        D_82408A60[3] = value;
        D_82408A60[8] = value;
        D_82408A6C[3] = value;
        D_82408A6C[7] = value;
    }
}

extern s32 func_8005A134(s32);
extern s32 func_80040E80(s32, void *);
extern void *func_81600E28(s32, s32, s32);
extern s32 func_82400020(void *);
extern void func_82400108(void *);
extern void func_82405D38(u8 *, s32, s32, s32);
extern void func_82407228(u8 *, void *, void *);
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(s32);
extern void ModelRenderer_InitDisplayRoots(void);
extern s32 func_80071AA0(s32, s32);
extern void func_80071A40(s32, s16 *);
extern void func_80071940(s32, s32);
extern s32 D_82407550;
extern s32 D_82407554;
extern s32 D_82407558;
extern s32 D_8240755C;
extern s32 D_82407560;
extern s32 D_82407564;
extern s32 D_82407568;
extern u8 D_82407570[];
extern s16 D_82408BE0[];
extern u8 D_82409308;
extern s32 D_82409FB8;
extern s32 D_82409FBC;
extern u8 D_82409FC0[];
extern u8 D_824090A0[];
extern void *D_8240AA68;
void func_82400704(s32 arg0) {
    s32 temp_v0;
    s32 sp20;
    s32 s0;
    func_8005A134(arg0);
    s0 = (s32)&D_82409FC0;
    func_80071940(0, s0);
    func_80071A40(s0, &D_82408BE0);
    func_82400020(&D_82409308);
    D_82407550 = func_80071AA0(s0, 0x36);
    D_82407554 = func_80071AA0(s0, 0x1A);
    D_82407558 = func_80071AA0(s0, 0xD);
    D_8240755C = func_80071AA0(s0, 0x68);
    D_82407564 = func_80071AA0(s0, 0x33);
    D_82407568 = func_80071AA0(s0, 3);
    D_82407560 = func_80071AA0(s0, 0);
    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    sp20 = temp_v0;
    D_82409FBC = func_80040E80(sp20, &D_82407570);
    D_8240AA68 = func_81600E28(sp20, 0, 0x10);
    MainPool_FinalizeAllocation(sp20);
    ModelRenderer_InitDisplayRoots();
    func_82400108(&D_82409308);
    func_82405D38(D_824090A0, arg0, D_82409FBC, D_82409FB8);
    func_82407228(D_824090A0, &D_82409308, s0);
}

extern u8 D_824090A0[];
extern void *D_8240AA68;
extern void func_800088DC(void);
extern void GeoRender_AdvanceFrameCounter(void);
extern void func_82406E14(void *, void *);
extern void func_80008648(void);
void func_82400880(void) {
    func_800088DC();
    GeoRender_AdvanceFrameCounter();
    func_82406E14(D_824090A0, D_8240AA68);
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE5B0/func_824008C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE5B0/func_824009AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE5B0/func_82400A9C.s")
#endif
