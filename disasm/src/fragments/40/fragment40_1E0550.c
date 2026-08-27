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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B04F70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B04FB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B05250.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B052B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B05494.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B0552C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1E0550/func_88B05650.s")
#endif
