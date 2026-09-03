#include "global.h"


#ifdef VERSION_US
extern u8 D_8800686C;
extern s32 fragment29_main(u8);
s32 fragment29_main(u8 arg0) {
    s32 result = 0;
    switch (arg0) {
    case 1:
    case 2:
    case 3:
    case 4:
        result = 1;
        break;
    }
    return result;
}

void func_8800005C(void) {
    fragment29_main(D_8800686C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000080.s")

extern void func_88000080(void *, s16, s16, s16);
void func_88000288(void *arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    *(s16 *)((u8 *)arg0 + 0) = arg1;
    *(s16 *)((u8 *)arg0 + 4) = arg2;
    *(s16 *)((u8 *)arg0 + 6) = arg3;
    *(u8 *)((u8 *)arg0 + 8) = arg4;
    *(u8 *)((u8 *)arg0 + 9) = arg5;
    *(u8 *)((u8 *)arg0 + 10) = arg6;
    *(u8 *)((u8 *)arg0 + 11) = arg7;
    func_88000080(arg0, arg1, arg2, arg3);
}

void func_880002F4(u8 *arg0, s16 arg1) {
    *(s16 *)arg0 = arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000308.s")

extern Gfx *D_800D0510;
void func_88000488(s32 *arg0, s32 arg1) {
    if (*arg0 != arg1) {
        gDPPipeSync(D_800D0510++);
        if (arg1 != 0) {
            gDPSetCombine(D_800D0510++, 0x509AA1, 0x3335FEFF);
        } else {
            gDPSetCombine(D_800D0510++, 0x129A25, 0xFF37FFFF);
        }
        *arg0 = arg1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000510.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000578.s")

extern u8 D_8800ED28[];
void func_880006BC(u8 *arg0) { struct S { u8 a,b,c; }; *(struct S *)&D_8800ED28 = *(struct S *)arg0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_880006E0.s")

s32 func_88000770(u8 *arg0)
{
  s32 result = 0;
  s32 count = 0;
  u8 *ptr = arg0;
  while (count != 4)
  {
    u8 value = ptr[2];
    count++;
    if (!value)
    {
      break;
    }
    if (value >= 0xA6)
    {
      result = 1;
      break;
    }
    ptr++;
  }

  return result;
}

extern s32 func_88000770(u8 *);
s32 func_880007B0(u8 *arg0) {
    s32 result = 0;
    if ((arg0[0] > 0) && (arg0[0] < 0x98) && ((arg0[0x1E] & 1) == 0)) {
        s32 temp = 0;
        result = temp;
        if (func_88000770(arg0) == 0) {
            result = 1;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000808.s")

extern Gfx *D_800D0510;
void func_880008B0(s16 arg0, s16 arg1, s16 arg2) {
    s32 i;

    for (i = 0; i != 2; i++, arg1++) {
        gDPPipeSync(D_800D0510++);
        if (i == 0) {
            gDPSetFillColor(D_800D0510++, 0x10001);
        } else {
            gDPSetFillColor(D_800D0510++, 0xFFFFFFFF);
        }
        gDPFillRectangle(D_800D0510++, arg0, arg1, arg0 + arg2 - 1, arg1);
    }
}

extern void func_8004B2CC(s32, s32, s32, s32, s32, s32, s32, s32);
void func_880009A8(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6) {
    if (arg0 != 0) {
        func_8004B314(arg1 - arg5, arg2 - arg6, arg3 + (arg5 * 2), arg4 + (arg6 * 2));
        return;
    }
    func_8004B2CC(arg1 - arg5, arg2 - arg6, arg3 + (arg5 * 2), arg4 + (arg6 * 2), 0x96, 0x96, 0x5A, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000A5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000C2C.s")

u32 Credits_RandomRange(u32 arg0) {
    s32 sp1C;

    if (arg0 == 0) {
        return 0U;
    }
    sp1C = guRandom();
    return (u32) ((u32) (osGetCount() + sp1C) / 10U) % arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000EC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88000FC4.s")

typedef struct {
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
} S1_unk_D_800A7440;
extern S1_unk_D_800A7440 *GfxRect_SetBounds(S1_unk_D_800A7440 *, s16, s16, s16, s16);
extern s32 GfxRect_ClipToScissor(S1_unk_D_800A7440 *);
extern Gfx *D_800D0510;
void func_88001144(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    S1_unk_D_800A7440 rect;

    GfxRect_SetBounds(&rect, arg0, arg1, arg0 + arg2 - 1, arg1 + arg3 - 1);
    if (GfxRect_ClipToScissor(&rect) != 0) {
        if ((arg4 == 0) || (arg4 == 0x100000)) {
            rect.y1++;
            rect.x2++;
        }
        gDPFillRectangle(D_800D0510++, rect.x1, rect.y2, rect.y1, rect.x2);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_88001234.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_880014A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_166060/func_880015F4.s")
#endif
