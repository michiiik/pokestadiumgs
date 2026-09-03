#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/74/fragment74_code/func_8F600020.s")

extern s16 D_8F600BFE;
void func_8F60009C(s16 *arg0, s32 arg1, s32 arg2) {
    arg0[0] = arg1;
    arg0[1] = arg2;
    if (D_8F600BFE == 0) {
        arg0[0] = arg0[0] / 2;
        arg0[1] = arg0[1] / 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/74/fragment74_code/func_8F6000EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/74/fragment74_code/func_8F6001FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/74/fragment74_code/func_8F60028C.s")

extern void func_800088DC(void);
extern void GfxImage_FillCurrent(void *, s32);
extern void func_8F6001FC(void);
extern void func_8F60028C(void);
extern void func_80008648(void);
extern u8 D_800D0510[];
void func_8F6004D4(void) {
    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 0x5295);
    func_8F6001FC();
    func_8F60028C();
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/74/fragment74_code/func_8F60051C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/74/fragment74_code/func_8F600610.s")

extern s32 StageContext_GetFadeMode(void);
extern void StageFade_StartFromTransparent(s32);
extern s32 func_8F600610(void);
s32 func_8F600948(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    sp1C = arg0;
    switch (arg0) {
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            sp1C = 1;
        }
        break;
    case 1:
        temp_v0 = func_8F600610();
        if (temp_v0 != 0) {
            if (temp_v0 == 1) {
                sp1C = 2;
            } else {
                sp1C = 3;
            }
            StageFade_StartFromTransparent(5);
        }
        break;
    case 2:
        if (StageContext_GetFadeMode() == 1) {
            sp1C = 4;
        }
        break;
    }
    return sp1C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/74/fragment74_code/func_8F6009F0.s")

extern s32 main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern s32 func_8004C09C(s32);
extern void func_8004C4B0(s32);
extern void func_80047588(s32, s32);
extern void Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern void func_8F600020(s32);
extern void func_8F6009F0(void);
extern void func_80047610(void);
extern void func_8004C398(void);
extern void Gfx_FreeDisplayListBuffers(void);
extern u8 D_1000000[];
extern u8 D_446E30[];
extern u8 D_447D00[];
s32 fragment74_main(s32 arg0, s32 arg1) {
    s32 sp1C;
    main_pool_push_state(0x54524E56);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp1C = func_8004C09C(0x43);
    func_8004C4B0(0x42);
    func_80047588(0x3F, 0);
    Asset_LoadToSegment((((u32)&D_1000000) & 0x0F000000) >> 24, &D_446E30, &D_447D00, 0);
    func_8F600020(sp1C);
    func_8F6009F0();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x54524E56);
    return 0;
}
#endif
