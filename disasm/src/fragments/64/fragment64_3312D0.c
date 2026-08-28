#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0E660.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0E6B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0E790.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0E84C.s")

extern u8 D_87F113D0[];
extern s32 func_800625E0(s32, s32);
void func_87F0E978(u8 *arg0, s32 arg1) {
    arg0[0] = 0;
    arg0[4] = D_87F113D0[arg1];
    func_800625E0((s32)(arg0 + 0x38), arg0[4]);
    if (arg0[4] == 0x19) {
        arg0[0x22] |= 2;
    }
}

extern s32 func_87F0E790(void *, void *, u8);
extern s32 func_87F0E84C(void *, void *, u8);
extern void func_87F0E978(u8 *, s32);
void func_87F0E9D8(void *arg0, void *arg1, s32 arg2) {
    u8 value;
    value = D_87F113D0[arg2];
    if ((func_87F0E790(arg1, arg0, value) == 0) && (func_87F0E84C(arg1, arg0, value) == 0)) {
        func_87F0E978(arg0, arg2);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0EA40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0EDDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0EE0C.s")

extern u32 D_87F15BB0;
extern void fragment3_main(void *);
extern void func_81A005F0(void *);
void func_87F0EECC(void) { fragment3_main(&D_87F15BB0); func_81A005F0(&D_87F15BB0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0EEFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0EFA0.s")

extern void func_8005777C();

void func_87F0F118(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_8005777C();
        var_s0 += 1;
    } while (var_s0 != 0x10);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0F158.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0F1C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0F234.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3312D0/func_87F0F2B8.s")

s8 GbTower_SetPollMask(s32);
extern void func_80057944(s32);
void func_87F0F390(void *arg0) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_80057944(var_s0 & 0xFF);
        var_s0 += 1;
    } while (var_s0 != 4);
    (*(s8 *)((u8 *)(arg0) + (0x2178))) = GbTower_SetPollMask(0);
}

extern void func_87F0F118(void);
extern void func_87F0F158(void *, s32);
void func_87F0F3E4(void *arg0) {
    s32 i;
    GbTower_SetPollMask(*(u8 *)((u8 *)arg0 + 0x2178));
    func_87F0F118();
    i = 0;
    do {
        func_87F0F158(arg0, i);
        i += 1;
    } while (i != 4);
}

extern void func_81A0022C(void *);
void StageLoader_UpdateSegments(void) { func_81A0022C(&D_87F15BB0); }

extern u32 D_87F15BB8;
u32 func_87F0F468(void) {
    return D_87F15BB8;
}
#pragma C_FUNCTION_PADDING(12)
#endif
