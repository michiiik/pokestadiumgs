#include "global.h"


#ifdef VERSION_US
f32 MathUtil_Random_ZeroOne();

s32 func_814028F0(void) {
    return (s32) ((MathUtil_Random_ZeroOne() * 15.0f) + 6.0f);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81402930.s")

void func_81402978(void *arg0, f32 arg1, s32 arg2) {
    *(s16 *)((u8 *)arg0 + 8) = arg2;
    *(f32 *)arg0 = arg1;

    if (arg2 >= 0) {
        *(f32 *)((u8 *)arg0 + 4) = 400.0f;
    } else {
        *(f32 *)((u8 *)arg0 + 4) = 0.0f;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814029AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81402A64.s")

void func_81402CD8(void *arg0, f32 arg1) {
    arg1 *= 100.0f;
    if (*(f32 *)((u8 *)arg0 + 0xCA8) < arg1)
        *(f32 *)((u8 *)arg0 + 0xCA8) = arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81402D08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403244.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403304.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403400.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403710.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403758.s")

s16 func_81403758();
void func_81403828(void *arg0, void *arg1) {
    s16 temp_v0;

    temp_v0 = func_81403758();
    (*(s16 *)((u8 *)(arg1) + (4))) = 0x20;
    if ((*(s32 *)((u8 *)(arg0) + (0xCC4))) != 0) {
        (*(s16 *)((u8 *)(arg1) + (0))) = 0x233;
        (*(s16 *)((u8 *)(arg1) + (2))) = temp_v0;
        (*(s16 *)((u8 *)(arg1) + (6))) = (s16) (0x1E0 - temp_v0);
        return;
    }
    (*(s16 *)((u8 *)(arg1) + (0))) = 0x2F;
    (*(s16 *)((u8 *)(arg1) + (2))) = 0;
    (*(s16 *)((u8 *)(arg1) + (6))) = temp_v0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403894.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814038D4.s")

extern void func_81403244(s32);
void func_81403918(s32 arg0) { func_81403244((arg0 + 8)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403938.s")

void func_81403A18(void *arg0) {
    u8 temp_v0;

    temp_v0 = (*(u8 *)((u8 *)(arg0) + (0xCC0)));
    switch (temp_v0) {                              /* irregular */
    case 0:
        (*(f32 *)((u8 *)(arg0) + (0xCBC))) = 0.0f;
        /* fallthrough */
    case 1:
    case 3:
        (*(u8 *)((u8 *)(arg0) + (0xCC0))) = 1U;
        /* fallthrough */
    case 2:
        return;
    }
}

s32 func_81403A64(u8 *arg0) {
    *(f32 *)(arg0 + 0xCBC) = 0.0f;
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403A74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403AE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403B18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403B7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403CD0.s")

void func_81403E2C(void *arg0) {
    u8 temp_v0;

    temp_v0 = (*(u8 *)((u8 *)(arg0) + (0xCC0)));
    switch (temp_v0) {                              /* irregular */
    case 2:
        (*(f32 *)((u8 *)(arg0) + (0xCBC))) = 16.0f;
        /* fallthrough */
    case 1:
    case 3:
        (*(u8 *)((u8 *)(arg0) + (0xCC0))) = 3U;
        /* fallthrough */
    case 0:
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403E7C.s")

extern u8 D_800CE060;

void *func_81403FAC(void *arg0) {
    s8 temp_v1;

    temp_v1 = (*(s8 *)((u8 *)(arg0) + (0xF)));
    if (temp_v1 >= 0) {
        return (temp_v1 * 0x28) + &D_800CE060;
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81403FDC.s")

s32 func_81404030(u8 *arg0) {
    *(f32 *)(arg0 + 4) = 0.0f;
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81404040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814040D8.s")

f32 func_816092FC(void);
s32 func_81404334(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (4))) = (f32) ((*(f32 *)((u8 *)(arg0) + (4))) - func_816092FC());
    if ((*(f32 *)((u8 *)(arg0) + (4))) <= 0.0f) {
        (*(f32 *)((u8 *)(arg0) + (4))) = 0.0f;
        (*(s8 *)((u8 *)(arg0) + (0xC))) = 4;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_8140438C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81404470.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_8140463C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814046C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81404700.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81404724.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814047C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_8140487C.s")


void *func_814049CC(void *arg0) {
    s8 temp_v1;

    temp_v1 = (*(s8 *)((u8 *)(arg0) + (8)));
    if ((temp_v1 >= 0) && ((*(s32 *)((u8 *)(arg0) + (0x4D60))) == 0)) {
        return (temp_v1 * 0x28) + &D_800CE060;
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81404A08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81404BEC.s")

s32 func_81404C2C(u8 *arg0) {
    *(f32 *)(arg0 + 0) = 0.0f;
    return 0;
}

s32 func_81404C3C(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (0))) = (f32) ((*(f32 *)((u8 *)(arg0) + (0))) - func_816092FC());
    if ((*(f32 *)((u8 *)(arg0) + (0))) < 0.0f) {
        (*(f32 *)((u8 *)(arg0) + (0))) = 0.0f;
        (*(s8 *)((u8 *)(arg0) + (6))) = 7;
    }
    return 0;
}

s32 func_81404C94(u8 *arg0) {
    *(f32 *)(arg0 + 0) = 0.0f;
    return 0;
}

s32 func_81404CA4(void *arg0)
{
  f32 new_var;
  new_var = func_816092FC();
  *((f32 *) (((u8 *) arg0) + 0)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0))) + new_var);
  if ((*((f32 *) (((u8 *) arg0) + 0))) >= 16.0f)
  {
    *((s8 *) (((u8 *) arg0) + 6)) = 2;
    *((f32 *) (((u8 *) arg0) + 0)) = 16.0f;
  }
  return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81404D00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81404D44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81404DA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81404DE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81404E68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814050EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81405208.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814052F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814053E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814054CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81405514.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814057CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81405CC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814063A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81406700.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81406A30.s")

s32 func_81406A74(u8 *arg0) {
    return arg0[6] == 5 && arg0[0x30] == 2;
}

s32 func_81406A9C(u8 *arg0) {
    return arg0[6] == 7;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81406AAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81406EA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81406F44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81407118.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814071C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81407258.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81407310.s")
#endif
