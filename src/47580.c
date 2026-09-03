#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046980.s")

s32 func_80046AC0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 result;
    u8 value;
    result = 1;
    if (arg1 != 0) {
        if (arg1 != 1) {
            result = 0;
        } else {
            value = arg0[0x7B];
            if (value < 3) {
                arg0[0x7B] = value + 1;
            } else {
                result = 0;
            }
        }
    }
    if (result) {
        (arg0 + arg0[0x7B])[0x74] = arg2;
    }
    return result;
}

void func_80046B14(u8 *arg0) {
    if (arg0[0x7B] > 0) {
        arg0[0x7B]--;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046B2C.s")

#pragma pack(1)
struct PackedWord { s32 value; };
#pragma pack(0)
s32 func_80046BB4(u8 *arg0, s32 arg1, u8 *arg2) {
    s32 result;
    u8 value;
    result = 1;
    if (arg1 != 0) {
        if (arg1 != 1) {
            result = 0;
        } else {
            value = arg0[0x7C];
            if (value < 3) {
                arg0[0x7C] = value + 1;
            } else {
                result = 0;
            }
        }
    }
    if (result) {
        *(struct PackedWord *)((u8 *)arg0 + (arg0[0x7C] << 2) + 0x54) = *(struct PackedWord *)arg2;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046C18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046CA8.s")

s32 func_80046D70(u8 *arg0, s32 arg1, u8 *arg2) {
    s32 result;
    u8 value;
    result = 1;
    if (arg1 != 0) {
        if (arg1 != 1) {
            result = 0;
        } else {
            value = arg0[0x7D];
            if (value < 3) {
                arg0[0x7D] = value + 1;
            } else {
                result = 0;
            }
        }
    }
    if (result) {
        *(struct PackedWord *)((u8 *)arg0 + (arg0[0x7D] << 2) + 0x64) = *(struct PackedWord *)arg2;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046DD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046E64.s")

void func_80046F2C(u8 *arg0, s32 arg1) {
    arg0[0x79] = (u8)arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80046F34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047058.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800470B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047104.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047158.s")

extern void *memcpy(void *, const void *, s32); void *func_800471B4(void *dest, const void *src, s32 size) { return (u8 *)memcpy(dest, src, size) + size; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800471D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047244.s")

extern u8 *D_80126F50;
extern void func_80047244(u8 *, s32);
void func_800472B8(s32 arg0) {
    func_80047244(D_80126F50, arg0);
}

s32 func_800472E0(u8 *arg0) {
    s32 count;
    s32 value;
    u8 *next;

    count = 1;
    value = *arg0;
    next = arg0;
    next++;
    if (value != 0) {
        do {
            if (value == 10) {
                count++;
            }
            value = *next;
            next++;
        } while (value != 0);
    }
    return count;
}

s32 func_80047318(u8 *arg0)
{
  s32 var_v1;
  u8 new_var;
  u8 *var_a1;
  u8 temp_v0;
  var_v1 = 1;
  new_var = *arg0;
  var_a1 = arg0 + 1;
  if (new_var != 0)
  {
    do
    {
      temp_v0 = *var_a1;
      var_v1 += 1;
      var_a1 += 1;
    }
    while (temp_v0 != 0);
    if (!arg0)
    {
    }
  }
  return var_v1;
}

void func_80047348(s32 arg0, s32 arg1) {
    D_80126F50 = 0;
}

void Font_FreeSetAsset(s32 arg0, s32 arg1)
{
  s32 temp_v1;
  ;
  if (D_80126F50 != 0)
  {
    *((s32 *) (((u8 *) (D_80126F50 + ((arg1 * 6) * 2))) + 4)) = 0;
    *((s32 *) (((u8 *) (D_80126F50 + ((arg1 * 6) * 2))) + 8)) = 0;
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047398.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047444.s")

extern u32 D_437750;
extern u32 D_446E30;
extern void BinArchive_Open(void *, void *, s32, s32);
void func_80047524(void) { BinArchive_Open(&D_437750, &D_446E30, 1, 1); }

extern void func_80004B4C(s32, s32);
s32 func_80047104(s32);

void func_80047558(s32 arg0, s32 arg1) {
    func_80004B4C(arg0, func_80047104(arg1));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047588.s")

extern u8 *D_80126F50; void func_80047610(void) { main_pool_try_free(D_80126F50); }

extern u16 D_80094FB4;
void func_80047634(u16 arg0) { D_80094FB4 |= arg0; }

extern u16 D_80094FB4; void func_80047650(u16 arg0) { D_80094FB4 &= ~arg0; }


void func_80047670(void) {
    D_80126F50[0x7A] |= 4;
}

void Font_EnableLineBreak(void) { D_80126F50[0x7A] = (u8)(D_80126F50[0x7A] & ~4); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800476A0.s")

s32 func_800476FC(s32 arg0, s32 arg1) { s32 result = 0; if (arg1 > 0 && arg1 < 0x100 && D_80126F50 != NULL) { *(s32 *)(D_80126F50 + 0x50) = arg0; D_80126F50[0x7F] = arg1; result = 1; } return result; }

s32 func_80047738(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
  s32 temp_a0;
  s32 var_v1;
  void *temp_v0;
  var_v1 = 0;
  if (D_80126F50 != 0)
  {
    temp_a0 = *((s32 *) (((u8 *) D_80126F50) + 0x50));
    if (temp_a0 != 0)
    {
      temp_v0 = temp_a0 + (arg0 * 0x10);
      if (arg0 < ((s32) (*((u8 *) (((u8 *) D_80126F50) + 0x7F)))))
      {
        *((s32 *) (((u8 *) (temp_a0 + (arg0 * 0x10))) + 4)) = arg1;
        *((s32 *) (((u8 *) temp_v0) + 8)) = arg2;
        *((s32 *) (((u8 *) (temp_a0 + (arg0 * 0x10))) + 0xC)) = arg3;
        var_v1 = 1;
      }
    }
  }
  return var_v1;
}

s32 func_80047790(s32 arg0) {
    s32 var_v1;

    var_v1 = 0;
    if ((arg0 == 9) || (arg0 == 0x20) || (arg0 == 0x2C) || (arg0 == 0x3E)) {
        var_v1 = 1;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800477C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047864.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047B4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047BD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047D24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047DC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047EC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_8004803C.s")

extern void func_800477C4(void *);
extern s32 func_80047BD4(void *);
extern void func_80046F2C(u8 *, s32);
void func_80048188(u8 *arg0) { u8 temp[0x20]; func_800477C4(temp); func_80046F2C(arg0, func_80047BD4(temp)); }

extern s32 func_8003514C(void);
s32 func_800481C0(u8 *arg0, s32 value) { if (func_8003514C() != 0) value = 0; arg0[0x78] = value; return 1; }

extern s32 func_800481C0(u8 *, s32);
s32 func_800481FC(u8 *arg0) { u8 temp[0x20]; func_800477C4(temp); return func_800481C0(arg0, func_80047BD4(temp)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048234.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800482C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048344.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048830.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048E30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049064.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049148.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800493B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800495BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800495F8.s")

extern void func_80048830(u8 *, s32, s32, s32, s32);

void func_80049628(s32 arg0, s32 arg1, s32 arg2) {
    func_80048830(D_80126F50, arg0, arg1, arg2, 1);
}

s32 func_80049668(s32 value) { s32 result=0; if (D_80126F50 != NULL) result=func_800481C0(D_80126F50,value); return result; }

extern void func_800496D8(s32, s32);
extern s32 func_80049668(s32);
void func_800496A4(s32 a0, s32 a1) { func_800496D8(0, a0); func_80049668(a1); }

extern void func_80046B2C(u8 *, s32, s32);

void func_800496D8(s32 arg0, s32 arg1) {
    func_80046B2C(D_80126F50, arg0, arg1);
}

extern u8 *D_80126F50; void func_80049708(void) { func_80046B14(D_80126F50); }

extern void func_80049770(s32,s32,s32,s32,s32); void func_8004972C(s32 a0,s32 a1,s32 a2,s32 a3){func_80049770(0,a0,a1,a2,a3);}

extern void func_80046CA8(u8 *, s32, s32, s32, s32, s32);
void func_80049770(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_80046CA8(D_80126F50, arg0, arg1, arg2, arg3, arg4);
}

extern u8 *D_80126F50; void func_800497C0(void) { func_80046C18(D_80126F50); }

extern void func_80049828(s32, s32, s32, s32, s32);
void func_800497E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { func_80049828(0, arg0, arg1, arg2, arg3); }

extern void func_80046E64(u8 *, s32, s32, s32, s32, s32);
void func_80049828(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_80046E64(D_80126F50, arg0, arg1, arg2, arg3, arg4);
}

extern u8 *D_80126F50; void func_80049878(void) { func_80046DD4(D_80126F50); }

void func_8004989C(s32 arg0) {
    func_80046F2C(D_80126F50, arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800498C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800499EC.s")

extern u8 *D_80126F50; extern Gfx *D_800D0510; extern u8 D_80095018[];
void func_80049B48(void) {
    D_80126F50[0x7A] |= 1;
    D_80126F50[0x7A] &= 0xFFFD;
    gSPDisplayList(D_800D0510++, D_80095018);
}

extern u8 D_80095040[]; extern Gfx *D_800D0510;
void func_80049B9C(void) { D_80126F50[0x7A] &= 0xFFFC; gSPDisplayList(D_800D0510++, D_80095040); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049BDC.s")

extern Gfx *D_800D0510;
extern u8 D_80095098[];
void Font_EndTexturedTextRendering(void) { Gfx *temp_v1 = D_800D0510++; temp_v1->words.w0 = 0xDE000000; temp_v1->words.w1 = (u32)D_80095098; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049C70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80049D9C.s")
#endif
