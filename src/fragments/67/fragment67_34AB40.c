#include "global.h"


#ifdef VERSION_US
void func_8290E040(f32* arg0, f32 arg1) {
    static f32 D_8291BC14;
    static f32 D_8291BC18;
    static f32 D_8291BC1C;

    D_8291BC1C = 1.0f - arg1;
    D_8291BC18 = arg1 * arg1;
    D_8291BC14 = D_8291BC18 * arg1;

    arg0[0] = ((D_8291BC1C * D_8291BC1C) * D_8291BC1C) / 6.0f;
    arg0[1] = ((0.5f * D_8291BC14) - D_8291BC18) + 0.6666667f;
    arg0[2] = (-0.5f * D_8291BC14) + (0.5f * D_8291BC18) + (0.5f * arg1) + 0.16666667f;
    arg0[3] = D_8291BC14 / 6.0;
}
void func_8290E0FC(f32* arg0, f32 arg1) {
    static f32 D_8291BC20;
    static f32 D_8291BC24;
    static f32 D_8291BC28;

    D_8291BC28 = 1.0 - arg1;
    D_8291BC24 = arg1 * arg1;
    D_8291BC20 = D_8291BC24 * arg1;

    arg0[0] = (D_8291BC28 * D_8291BC28) * D_8291BC28;
    arg0[1] = (((21.0f * D_8291BC20) / 12.0f) - (9.0f * D_8291BC24 * 0.5f)) + (3.0f * arg1);
    arg0[2] = ((-11.0f * D_8291BC20) / 12.0f) + (3.0f * D_8291BC24 * 0.5f);
    arg0[3] = D_8291BC20 / 6.0f;
}
void func_8290E1D8(f32* arg0, f32 arg1) {
    static f32 D_8291BC2C;
    static f32 D_8291BC30;
    static f32 D_8291BC34;

    D_8291BC34 = 1.0f - arg1;
    D_8291BC30 = arg1 * arg1;
    D_8291BC2C = D_8291BC30 * arg1;

    arg0[0] = ((D_8291BC34 * D_8291BC34) * D_8291BC34) * 0.25f;
    arg0[1] = ((0.5833333f * D_8291BC2C) - (1.25f * D_8291BC30)) + (arg1 * 0.25f) + 0.5833333f;
    arg0[2] = (-0.5f * D_8291BC2C) + (0.5f * D_8291BC30) + (0.5f * arg1) + 0.16666667f;
    arg0[3] = D_8291BC2C / 6.0f;
}
extern s32 D_8291BC00;
extern s32 D_8291BC04;
extern s32 D_8291BC08;
extern s32 D_8291BC10;

void func_8290E2A8(void)
{
  *((s16 *) (((u8 *) (&D_8291BC00)) + 0)) = 0xA;
  *((s16 *) (((u8 *) (&D_8291BC04)) + 0)) = 1;
  *((f32 *) (((u8 *) (&D_8291BC08)) + 0)) = 0.0f;
  *((s16 *) (((u8 *) (&D_8291BC10)) + 0)) = 0xE;
  *((s16 *) (((u8 *) (&D_8291BC00)) + 2)) = 0xA;
  *((s16 *) (((u8 *) (&D_8291BC04)) + 2)) = 1;
  *((s16 *) (((u8 *) (&D_8291BC10)) + 2)) = 0xE;
  *((f32 *) (((u8 *) (&D_8291BC08)) + 4)) = 0.0f;
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34AB40/func_8290E2FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34AB40/func_8290E438.s")
#endif
