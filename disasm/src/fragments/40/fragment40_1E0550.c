#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B04380.s")

extern u8 D_88B05BE3[];
extern s32 *func_800635E0(u8);
void func_88B043B8(u8 arg0) {
    func_800635E0(D_88B05BE3[arg0 * 4]);
}

extern u8 D_88B05CF8[];
extern void func_8004C874(s32, s32);
void func_88B043EC(u8 arg0) {
    func_8004C874(0x3C, D_88B05CF8[arg0]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B04420.s")

extern u8 D_88B05BE0[];
s32 func_88B04468(void) {
    u8 *ptr = D_88B05BE0;
    s32 i = 0;
    s32 limit = 0x22;
    do {
        if (*ptr < 3) break;
        i++;
        ptr += 4;
    } while (i != limit);
    return i & 0xFF;
}

extern u8 D_88B05C68[];
s32 func_88B0449C(void) {
    u8 *ptr = D_88B05C68;
    s32 i = 0;
    s32 limit = 0x24;
    do {
        if (*ptr < 3) break;
        i++;
        ptr += 4;
    } while (i != limit);
    return i & 0xFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B044D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B04698.s")

extern s32 func_88B04698(void);
s32 func_88B046F0(void) {
    s32 result;
    if (func_88B04698() < 3) result = 1;
    else result = 0;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B04724.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B048C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B04950.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B04A08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B04ADC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B04BB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B04C38.s")

extern s8 *HAL_Strcpy(s8 *, s8 *);
extern u16 D_8800686A;
extern s8 D_8800686D[];
extern u8 D_88B05BE0[];
extern u8 D_88B05868[];
extern u16 D_88B05F6E;
extern s32 func_88B04380(u8);
void func_88B04F70(s8 *arg0, s16 arg1) {
    *(s16 *)(arg0 + 0) = arg1;
    *(s16 *)(arg0 + 2) = D_8800686A;
    HAL_Strcpy(arg0 + 4, D_8800686D);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B04FB0.s")

void func_88B05250(s8 *arg0, s16 arg1) {
    *(s16 *)(arg0 + 0) = arg1;
    *(s16 *)(arg0 + 4) = D_8800686A;
    HAL_Strcpy(arg0 + 8, D_8800686D);
    {
        u16 value = *(u16 *)(arg0 + 2);
        if (value != 0xFFFF) {
            *(u16 *)(arg0 + 2) = value + 1;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B052B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B05494.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B0552C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B05650.s")
#endif
