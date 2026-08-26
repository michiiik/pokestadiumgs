#include "global.h"


#ifdef VERSION_US
extern void func_80049ED8(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_882306E0(void) {
    func_80049ED8(D_80087200);
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_88230708.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_88230770.s")

extern u32 D_882349A0;
extern void func_8821D930(s32);
void func_88230878(void) { func_8821D930(D_882349A0 + 4); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_882308A0.s")

extern void func_80049ED8(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_882309B0(void) {
    func_80049ED8(D_80087200);
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_882309D8.s")

extern void func_88004990(u8, s32);
extern u32 D_882349B0;
void func_88230A38(void) {
    func_88004990(*(*(u8 **)((u8 *)(D_882349B0) + (0))), 0);
    func_88004990(*(*(u8 **)((u8 *)(D_882349B0) + (4))), 0);
    D_880068B8 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_88230A88.s")

extern u32 D_882349B0;
extern void func_889033A0(s32);
void func_88230B2C(void) { func_889033A0((D_882349B0 + 236)); func_8821D930((D_882349B0 + 8)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_88230B64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_88230D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3960/func_88230E38.s")
#endif
