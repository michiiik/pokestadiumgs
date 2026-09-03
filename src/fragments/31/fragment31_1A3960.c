#include "global.h"


#ifdef VERSION_US
extern void Input_SetRepeatController(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_882306E0(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void func_88213BE4(s32, s32);
extern s32 D_882346F4;
extern u32 D_882349A0;
void func_88001900(void);
extern s32 D_880068B4;
void Util_Free(s32 arg0);
void func_88230708(void) {
    if ((*(s32 *)((u8 *)(D_882349A0) + (0xE4))) != 0) {
        func_88001900();
    } else {
        func_88213BE4(0x12, 0);
    }
    D_880068B4 = 1;
    D_882346F4 = 0;
    Util_Free((s32) D_882349A0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_88230770.s")

extern void func_8821D930(s32);
void func_88230878(void) {
    func_8821D930(D_882349A0 + 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_882308A0.s")


void func_882309B0(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void func_88214330();
extern u32 D_882349B0;
void func_88001900(void);
void Util_Free(s32 arg0);
void func_882309D8(void) {
    if ((*(s32 *)((u8 *)(D_882349B0) + (0xE8))) != 0) {
        func_88001900();
        D_880068B4 = 1;
    } else {
        func_88214330();
    }
    D_882346F4 = 0;
    Util_Free((s32) D_882349B0);
}

extern void func_88004990(u8, s32);
void func_88230A38(void) {
    func_88004990(*(*(u8 **)((u8 *)(D_882349B0) + (0))), 0);
    func_88004990(*(*(u8 **)((u8 *)(D_882349B0) + (4))), 0);
    D_880068B8 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_88230A88.s")

extern void func_889033A0(s32);
void func_88230B2C(void) { func_889033A0((D_882349B0 + 236)); func_8821D930((D_882349B0 + 8)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_88230B64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_88230D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_88230E38.s")
#endif
