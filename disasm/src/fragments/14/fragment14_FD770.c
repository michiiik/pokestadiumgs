#include "global.h"


#ifdef VERSION_US
s32 func_813055E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 result = (((arg3 + arg1) * 2) + arg2) - 1;
    return result >= 0 ? result : 0;
}

s32 func_8130560C(void *arg0, s32 arg1) {
    u8 *base = (u8 *)arg0;
    if (arg1 >= *(u16 *)(base + 0x50)) {
        return -1;
    }
    return *(u8 *)(base + arg1 + 0x10);
}

s32 func_81305634(void *arg0) {
    s32 temp_a1;

    temp_a1 = func_813055E0((s32) arg0, (s32) (*(s16 *)((u8 *)(arg0) + (0x7C))), (s32) (*(s16 *)((u8 *)(arg0) + (8))), (s32) (*(s16 *)((u8 *)(arg0) + (0xA))));
    if (((*(s16 *)((u8 *)(arg0) + (0x7C))) == 0) && ((*(s16 *)((u8 *)(arg0) + (8))) == 1) && ((*(s16 *)((u8 *)(arg0) + (0xA))) == 0)) {
        return -1;
    }
    return func_8130560C(arg0, temp_a1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_813056A0.s")

f32 func_8130571C(void *arg0) { u8 *base = (u8 *)arg0; f32 result = 1.0f; if (base[0x87] == 3) { result = (f32)base[0x82] / (f32)base[0x86]; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81305780.s")

extern void func_816048E0(s32, s32, s32, s32, f32);
extern f32 D_813124E8;
extern void func_816073A0(void *);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_800495BC(s32, s32, s32);
extern void func_800499EC(void);
extern void func_81607408(void);
void func_81305A10(void *arg0, void *arg1, f32 arg2) {
    s16 temp_a3;
    s32 color;

    temp_a3 = *(s16 *)((u8 *)arg1 + 6);
    if (temp_a3 >= 0x10) {
        func_816048E0(
            *(s16 *)((u8 *)arg1 + 0),
            *(s16 *)((u8 *)arg1 + 2),
            *(s16 *)((u8 *)arg1 + 4),
            temp_a3,
            arg2);
        if (!(D_813124E8 < arg2)) {
            func_816073A0(arg1);
            func_800498C4();
            func_800496A4(4, 1);
            color = func_8004C874(0xF, 0);
            func_800495BC(
                *(s16 *)((u8 *)arg1 + 0) + 0xC,
                *(s16 *)((u8 *)arg1 + 2) + 0xC,
                color);
            func_800499EC();
            func_81607408();
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81305AD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81305BA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81305C54.s")

extern s32 func_81305634(void *);
extern Gfx *D_800D0510;
extern f32 D_813124F4;
extern void func_8004989C(s32);
extern s32 func_816020BC(u8);
void func_81305FB4(void *arg0, void *arg1, f32 arg2) {
    s32 result;

    result = func_81305634(arg0);
    if (*(s16 *)((u8 *)arg1 + 6) >= 0x10) {
        gDPPipeSync(D_800D0510++);
        func_816048E0(
            *(s16 *)((u8 *)arg1 + 0),
            *(s16 *)((u8 *)arg1 + 2),
            *(s16 *)((u8 *)arg1 + 4),
            *(s16 *)((u8 *)arg1 + 6),
            arg2);
        if (!(D_813124F4 < arg2) && (result > 0)) {
            gDPPipeSync(D_800D0510++);
            func_816073A0(arg1);
            func_800498C4();
            func_800496A4(4, 1);
            func_8004989C(0x14);
            func_800495BC(
                *(s16 *)((u8 *)arg1 + 0) + 0xE,
                *(s16 *)((u8 *)arg1 + 2) + 0xE,
                func_816020BC((u8)result));
            func_800499EC();
            func_81607408();
        }
    }
}

extern f32 func_81305780(void *, void *, void *, void *);
extern void func_81305A10(void *, void *, f32);
extern void func_81305C54(void *, void *, f32);
extern void func_81305FB4(void *, void *, f32);
extern s32 func_81600DA8(void *, void *);
void func_813060C8(void *arg0, void *arg1) {
    u8 sp38[8];
    u8 sp30[8];
    u8 sp28[8];
    f32 sp24;

    if (*(u8 *)((u8 *)arg0 + 0x87) != 0) {
        sp24 = 1.0f - func_81305780(arg0, sp38, sp30, sp28);
        if (func_81600DA8(arg1, (u8 *)arg0 + 1) != 0) {
            func_81305A10(arg0, sp38, sp24);
        }
        if (func_81600DA8(arg1, (u8 *)arg0 + 2) != 0) {
            func_81305C54(arg0, sp30, sp24);
        }
        if (func_81600DA8(arg1, (u8 *)arg0 + 3) != 0) {
            func_81305FB4(arg0, sp28, sp24);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306178.s")

void func_813061E8(u8 *arg0) {
    arg0[0x87] = 5;
    *(s16 *)(arg0 + 0x7E) = -2;
    *(f32 *)(arg0 + 0x78) = 4.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306208.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306264.s")

extern void func_800226C0(s32);
extern f32 D_81311F70;
void func_813062C0(void *arg0)
{
  s16 temp_v0;
  s32 temp_v1;
  s32 var_v0;
  temp_v0 = *((s16 *) (((u8 *) arg0) + 0x7C));
  if ((*((s16 *) (((u8 *) arg0) + 0x7C))) > 0)
  {
    *((u8 *) (((u8 *) arg0) + 0x8A)) = (u8) (*((s16 *) (((u8 *) arg0) + 0x7C)));
    *((s16 *) (((u8 *) arg0) + 0x7C)) = (*((s16 *) (((u8 *) arg0) + 0x7C))) - 4;
    if ((*((s16 *) (((u8 *) arg0) + 0x7C))) < 0)
    {
      *((s16 *) (((u8 *) arg0) + 0x7C)) = 0;
    }
    *((u8 *) (((u8 *) arg0) + 0x87)) = 3;
    temp_v1 = (*((s16 *) (((u8 *) arg0) + 0x7C))) - (*((u8 *) (((u8 *) arg0) + 0x8A)));
    *((u8 *) (((u8 *) arg0) + 0x82)) = 0;
    if (temp_v1 > 0)
    {
      var_v0 = temp_v1;
    }
    else
    {
      var_v0 = -temp_v1;
    }
    *((s8 *) (((u8 *) arg0) + 0x86)) = (s8) ((u32) (((f32) var_v0) * D_81311F70));
    func_800226C0(1);
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_813063CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_813064E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_8130662C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306780.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_8130687C.s")

void func_813068C0(void *arg0)
{
  unsigned int temp_v0;
  temp_v0 = *((u8 *) (((u8 *) arg0) + 0x82));
  if (((s32) temp_v0) >= ((s32) (*((u8 *) (((u8 *) arg0) + 0x86)))))
  {
    *((u8 *) (((u8 *) arg0) + 0x82)) = 0U;
    *((s8 *) (((u8 *) arg0) + 0x8A)) = (s8) (*((s16 *) (((u8 *) arg0) + 0x7C)));
    *((s8 *) (((u8 *) arg0) + 0x87)) = 1;
    return;
  }
  *((u8 *) (((u8 *) arg0) + 0x82)) = (u8) (temp_v0 + 1);
}

extern f32 func_816092FC(void);
void func_813068FC(void *arg0) { *(f32 *)((u8 *)arg0 + 0x78) += func_816092FC(); if (*(f32 *)((u8 *)arg0 + 0x78) >= 4.0f) { *(f32 *)((u8 *)arg0 + 0x78) = 4.0f; *(u8 *)((u8 *)arg0 + 0x87) = 1; } }

f32 func_816092FC(void);
void func_81306954(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (0x78))) = (f32) ((*(f32 *)((u8 *)(arg0) + (0x78))) - func_816092FC());
    if ((*(f32 *)((u8 *)(arg0) + (0x78))) <= 0.0f) {
        (*(f32 *)((u8 *)(arg0) + (0x78))) = 0.0f;
        if ((*(s32 *)((u8 *)(arg0) + (0))) == 0) {
            (*(s8 *)((u8 *)(arg0) + (0x87))) = 0;
        }
    }
}

void func_813069B0(u8 *arg0) {
    *(f32 *)(arg0 + 0x78) = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_813069BC.s")

s16 func_81306B0C(void *arg0) {
    u8 temp_v0;

    temp_v0 = (*(u8 *)((u8 *)(arg0) + (0x87)));
    if ((temp_v0 == 0) || (temp_v0 == 5)) {
        (*(s16 *)((u8 *)(arg0) + (0x80))) = func_813055E0((s32) arg0, (s32) (*(s16 *)((u8 *)(arg0) + (0x7C))), (s32) (*(s16 *)((u8 *)(arg0) + (8))), (s32) (*(s16 *)((u8 *)(arg0) + (0xA))));
        return (*(s16 *)((u8 *)(arg0) + (0x7E)));
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306B64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306C18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FD770/func_81306E90.s")
#endif
