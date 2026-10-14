#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F500020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F500130.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F5002F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F500414.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F500544.s")

extern s32 StageContext_GetFadeMode(void);
extern void StageFade_StartFromTransparent(s32);
extern void func_80035424(s32);
extern s32 func_8F500544(void);
s32 func_8F500774(s32 incoming) {
    s32 state = incoming;
    switch (incoming) {
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            state = 1;
        }
        break;
    case 1:
        if (func_8F500544() != 0) {
            state = 2;
            StageFade_StartFromTransparent(5);
            func_80035424(10);
        }
        break;
    case 2:
        if (StageContext_GetFadeMode() == 1) {
            state = 3;
        }
        break;
    }
    return state;
}

extern void StageFade_StartFromOpaque(s32);
extern void func_800086A4(s32);
extern void func_80064D28();
extern void func_8F500414();
void func_8F500810(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    do {
        func_80064D28();
        func_8F500414();
        temp_v0 = func_8F500774(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 3);
}

extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern s32 func_8004C09C(s32);
extern s32 func_8004C8C0(u16);
extern s32 func_8004C4B0(s32);
extern s32 func_8004D690(s32);
extern u8* func_80047588(s32, s32);
extern u8* Asset_LoadToSegment(s32, u8*, u8*, s32);
extern u8 D_1000000[], D_446E30[], D_447D00[];
extern s32 D_8F5009A0;
extern void func_8F500020(void);
extern void func_80008514(s32);
extern void func_80008574(void);
extern void func_80047610(void);
extern void func_8004C398(void);
s32 fragment73_main(s32 arg0, s32 arg1) {
    s32 configuration;
    main_pool_push_state(0x42474D50);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    configuration = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(7);
    func_8004C8C0(0x79);
    func_8004C4B0(0x42);
    D_8F5009A0 = func_8004D690(0x16);
    func_80047588(0x18, 0);
    Asset_LoadToSegment(((u32)D_1000000 & 0x0F000000) >> 24, D_446E30, D_447D00, 0);
    func_8F500020();
    func_80008514(configuration);
    func_8F500810();
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x42474D50);
    return 0;
}
#endif
