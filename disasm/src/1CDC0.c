#include "global.h"


#ifdef VERSION_US
extern u8 D_8008FB90[];
extern u8 func_8001CC3C(u8 **);
extern s16 func_8001CC50(u8 **);
s32 func_8001C1C0(u8 **arg0, u8 arg1) {
    u8 value;
    u8 bits;
    s32 result;

    value = D_8008FB90[arg1];
    result = 0;
    bits = value & 3;
    if (bits == 1) {
        if (!(value & 0x80)) {
            result = func_8001CC3C(arg0) & 0xFFFF;
        } else {
            result = func_8001CC50(arg0) & 0xFFFF;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001C228.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001C404.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001C570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001C6C8.s")

extern u8 D_80121EF4[];
extern void func_8001CB1C();
extern void func_8001C6C8();
void func_8001C744(void *arg0, s32 arg1) {
    s32 temp_a2;
    temp_a2 = *(s32 *)((u8 *)arg0 + (arg1 << 2) + 0x54);
    if (temp_a2 != 0) {
        func_8001CB1C(D_80121EF4, (void *)(u32)(temp_a2 + 0x80));
        func_8001C6C8(temp_a2);
        *(s32 *)((u8 *)arg0 + (arg1 << 2) + 0x54) = 0;
    }
}

void func_8001C744();
void func_8001AAD8();
void func_8001C794(s32 arg0)
{
  u32 new_var;
  s32 i;
  i = 0;
  *((u8 *) ((u32) arg0)) = (u8) (((*((u8 *) (new_var = (u32) arg0))) & 0xFFFFu) | 0x40);
  do
  {
    func_8001C744((void *) ((u32) arg0), i);
    i++;
  }
  while (i != 6);
  func_8001AAD8((void *) ((u32) (arg0 + 0x90)));
  *((u8 *) ((u32) ((arg0 & 0xFFFFFFFFFFFFFFFFu) & 0xFFFFFFFFFFFFFFFFu))) = (u8) ((*((u8 *) ((u32) arg0))) & 0xFF7F);
}

void func_8001C804(void *arg0, u16 arg1) {
    s32 i;
    u8 *dst;

    i = 0;
    do {
        if (arg1 & 1) {
            dst = *(u8 **)((u8 *)arg0 + (i * 4) + 0x38);
            dst[7] = *((u8 *)arg0 + 5);
            dst[3] = *((u8 *)arg0 + 3);
            dst[2] = *((u8 *)arg0 + 2);
        }
        arg1 = (arg1 >> 1) & 0xFFFF;
        if (arg1 & 1) {
            dst = *(u8 **)((u8 *)arg0 + (i * 4) + 0x3C);
            dst[7] = *((u8 *)arg0 + 5);
            dst[3] = *((u8 *)arg0 + 3);
            dst[2] = *((u8 *)arg0 + 2);
        }
        arg1 = (arg1 >> 1) & 0xFFFF;
        if (arg1 & 1) {
            dst = *(u8 **)((u8 *)arg0 + (i * 4) + 0x40);
            dst[7] = *((u8 *)arg0 + 5);
            dst[3] = *((u8 *)arg0 + 3);
            dst[2] = *((u8 *)arg0 + 2);
        }
        arg1 = (arg1 >> 1) & 0xFFFF;
        if (arg1 & 1) {
            dst = *(u8 **)((u8 *)arg0 + (i * 4) + 0x44);
            dst[7] = *((u8 *)arg0 + 5);
            dst[3] = *((u8 *)arg0 + 3);
            dst[2] = *((u8 *)arg0 + 2);
        }
        i += 4;
        arg1 = (arg1 >> 1) & 0xFFFF;
    } while (i != 0x10);
}

extern u8 D_80121DDC[];
extern void func_8001C794(s32);
void func_8001C8FC(void *arg0, s32 arg1)
{
  s32 i;
  u8 *entry;
  s32 value;
  s32 different;
  i = ((s32) ((u32) (&D_80121DDC))) * 0;
  entry = (u8 *) arg0;
  do
  {
    value = *((s32 *) (entry + 0x38));
    different = value != ((s32) ((u32) (&D_80121DDC)));
    if (different == 1)
    {
      func_8001C794(value);
    }
    i += 4;
    entry += 4;
  }
  while (i != 0x40);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001C97C.s")

extern void func_8001CA3C(void);
void func_8001CA14(u8 *arg0) {
    *arg0 = ((*arg0) & 0xFF) | 0x40;
    func_8001CA3C();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001CA3C.s")

void func_8001CB1C(void *arg0, void *arg1)
{
  if ((*((void **) (((u8 *) arg1) + 0))) == 0)
  {
    *((void **) (((u8 *) (*((void **) (((u8 *) arg0) + 0)))) + 4)) = arg1;
    *((void **) (((u8 *) arg1) + 0)) = *((void **) (((u8 *) arg0) + 0));
    *((void **) (((u8 *) arg1) + 4)) = arg0;
    *((void **) (((u8 *) arg0) + 0)) = arg1;
    *((s32 *) (((u8 *) arg0) + 8)) = (*((s32 *) (((u8 *) arg0) + 8))) + 1;
    *((s32 *) (((u8 *) arg1) + 0xC)) = *((s32 *) (((u8 *) arg0) + 0xC));
  }
}

s32 func_8001CB5C(void *arg0) {
    void *node = *(void **)arg0;
    if (node == arg0) return 0;
    *(void **)((u8 *)*(void **)node + 4) = arg0;
    *(void **)arg0 = *(void **)node;
    *(void **)node = NULL;
    *(s32 *)((u8 *)arg0 + 8) = *(s32 *)((u8 *)arg0 + 8) - 1;
    return *(s32 *)((u8 *)node + 8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001CB9C.s")

u8 func_8001CC3C(u8 **arg0) { u8 result = **arg0; (*arg0)++; return result; }

s16 func_8001CC50(u8 **arg0) {
    s16 value;
    value = (*(*arg0)) << 8;
    (*arg0)++;
    value = (0, (*(*arg0)) | value); (*arg0)++;
    return value;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001CC88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001CCC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001CDE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001CE70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001CF5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001D340.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001DA54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001DE58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001DEB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001DF24.s")

void func_8001DFD0(void *arg0, u8 arg1) {
    s32 value = arg1;
    *(f32 *)((u8 *)arg0 + 0x30) = (f32)value / 127.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001DFF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001ED64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001F6D4.s")

extern void func_8001ED64(void *);
extern void func_8001B8D0(void *);
void func_8001F7A0(void *arg0) {
    s32 temp_t8;

    if (*(s32 *)((u8 *)arg0 + 0xDC) > 0) {
        do {
            func_8001ED64(arg0);
            func_8001B8D0(arg0);
            temp_t8 = --(*(s32 *)((u8 *)arg0 + 0xDC));
        } while (temp_t8 > 0);
    }
}

extern void func_8001C404(s32);
extern u8 D_8008F194[];
extern u8 D_8008F1A4[];
void func_8001F7F0(void *arg0) {
    u8 *var_s1;
    s32 var_s0;

    func_8001CA3C();
    var_s1 = (u8 *)arg0;
    var_s0 = 0;
    var_s1 = var_s1;

    *(u8 *)(var_s1 + 0) = *(u8 *)(var_s1 + 0) & 0xFFFD;
    *(u16 *)(var_s1 + 0x10) = 0;
    *(u8 *)(var_s1 + 1) = 1;
    *(u16 *)(var_s1 + 0x12) = 0;
    *(u16 *)(var_s1 + 0x14) = 0;
    *(u16 *)(var_s1 + 0xA) = 0;
    *(u16 *)(var_s1 + 8) = 0x1680;
    *(u16 *)(var_s1 + 0xC) = 0;
    *(u16 *)(var_s1 + 0xE) = 0;
    *(u8 *)(var_s1 + 2) = 0;
    *(u32 *)(var_s1 + 0x94) = (u32)D_8008F194;
    *(u32 *)(var_s1 + 0x98) = (u32)D_8008F1A4;
    *(u32 *)(var_s1 + 0xE0) = 0;
    *(u16 *)(var_s1 + 0x16) = 0;
    *(f32 *)(var_s1 + 0x1C) = 1.0f;
    *(f32 *)(var_s1 + 0x20) = 0.0f;
    *(f32 *)(var_s1 + 0x24) = 0.0f;
    *(f32 *)(var_s1 + 0x28) = 0.5f;

    do {
        func_8001C404(*(s32 *)(var_s1 + 0x38));
        var_s0 += 4;
        var_s1 += 4;
    } while (var_s0 != 0x40);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001F8C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001F9B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001FA80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1CDC0/func_8001FBE0.s")
#endif
