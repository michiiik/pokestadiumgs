#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_342DB0/func_829062B0.s")

/* mkdraft:func_829063EC begin */
extern s32 MathUtil_Random16(void);
extern f64 D_829174D0;

u16 func_829063EC(s32 arg0) {
    return ((f32)(u32)MathUtil_Random16() / D_829174D0) * arg0;
}
/* mkdraft:func_829063EC end */

/* mkdraft:func_829064D0 begin */
extern f32 MathUtil_Random_ZeroOne(void);
extern f32 D_829174D8;
extern f32 D_829174DC;
extern u8 D_82919DE0[];
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0xE4, 0x244802D8, 0x244A02D8)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0xE8, 0x2409C000, 0x240BC000)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0xEC, 0xA6080010, 0xA60A0010)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0xF4, 0xA6090014, 0xA60B0014)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0x128, 0x244A0063, 0x244C0063)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0x12C, 0xA20A0021, 0xA20C0021)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0x138, 0x00025880, 0x00026880)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0x13C, 0x01625823, 0x01A26823)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0x140, 0x000B58C0, 0x000D68C0)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0x144, 0x01625823, 0x01A26823)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0x148, 0x000B5880, 0x000D6880)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0x14C, 0x01625823, 0x01A26823)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0x150, 0x000B5840, 0x000D6840)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0x154, 0x256C02D8, 0x25AE02D8)
#pragma REWRITE_FUNCTION_WORD(func_829064D0, 0x158, 0xA60C0018, 0xA60E0018)

void func_829064D0(s32 arg0, void *arg1) {
    f32 sp24;
    u32 temp_ft1;
    u8 *temp_s0;

    sp24 = (f32)(u32)func_829063EC(200) - 100.0f;
    temp_ft1 = func_829063EC(120);
    temp_s0 = &D_82919DE0[arg0 * 36];
    *(f32 *)(temp_s0 + 8) = *(f32 *)((u8 *)arg1 + 8) + sp24;
    *(f32 *)(temp_s0 + 4) = (f32)temp_ft1 + 60.0f + *(f32 *)((u8 *)arg1 + 4);
    *(f32 *)(temp_s0 + 0) = *(f32 *)((u8 *)arg1 + 0) + (-MathUtil_Random_ZeroOne() * 50.0f - 50.0f);
    *(s16 *)(temp_s0 + 0x10) = func_829063EC(546) + 728;
    *(s16 *)(temp_s0 + 0x12) = 0;
    *(s16 *)(temp_s0 + 0x14) = -0x4000;
    *(f32 *)(temp_s0 + 0x1C) = (f32)(u32)func_829063EC(2);
    *(s8 *)(temp_s0 + 0x21) = func_829063EC(155) + 99;
    *(s16 *)(temp_s0 + 0x18) = func_829063EC(2) * 182 + 728;
    *(s16 *)(temp_s0 + 0x16) = 0;
    *(f32 *)(temp_s0 + 0xC) = D_829174DC + (f32)(u32)func_829063EC(6) * D_829174D8;
}
/* mkdraft:func_829064D0 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_342DB0/func_82906680.s")

/* mkdraft:func_82906748 begin */
extern u8 D_82919DE0[];
extern s32 Math_StepToS32(s32, s32, s32, s32);
extern void func_829064D0(s32, void *);

void func_82906748(void *arg0) {
    u8 *temp_s0;
    s32 i;

    temp_s0 = D_82919DE0;
    for (i = 0; i != 40; i++, temp_s0 += 0x24) {
        *(s16 *)(temp_s0 + 0x12) = Math_StepToS32(*(s16 *)(temp_s0 + 0x12), *(s16 *)(temp_s0 + 0x10), 0xB6, 0xB6);
        *(s16 *)(temp_s0 + 0x14) = Math_StepToS32(*(s16 *)(temp_s0 + 0x14), 0x4000, -*(s16 *)(temp_s0 + 0x12), *(s16 *)(temp_s0 + 0x12));
        *(u8 *)(temp_s0 + 0x20) = Math_StepToS32(*(u8 *)(temp_s0 + 0x20), 0xFF, 0xA, 0xA);
        if (*(s16 *)(temp_s0 + 0x14) == 0x4000) {
            func_829064D0(i, arg0);
        }
    }
}
/* mkdraft:func_82906748 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_342DB0/func_82906808.s")
#endif
