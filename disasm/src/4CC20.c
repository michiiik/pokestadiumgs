#include "global.h"


#ifdef VERSION_US
s32 func_8000484C(s32, s32, s32, s32);
extern void func_800049B8(s32);
s32 func_80004B4C(s32, s32);
s32 func_800356CC(s32);
extern s32 D_80097124;
extern s32 D_80097128;
void func_8004C020(void) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = func_8000484C(func_800356CC(2), 0, 2, 1);
    sp1C = temp_v0;
    D_80097124 = func_80004B4C(temp_v0, 0x41);
    D_80097128 = func_80004B4C(sp1C, 0);
    func_800049B8(sp1C);
}

void func_8004C088(s32 arg0, s32 arg1) {
    extern s32 D_80097120;
    D_80097120 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C09C.s")

extern s32 D_80097120; void func_8004C398(void) { D_80097120 = 0; }

void func_8004C3A4(s32 unused, u8 *arg1) { *(s32 *)arg1 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C3B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C3EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C468.s")

extern s32 D_80097120; s32 func_8004C4A4(void) { return D_80097120; }

extern s32 D_80097120; extern s32 func_8004C3EC(s32,s32,s32); s32 func_8004C4B0(s32 value){s32 result=0; s32 ptr=D_80097120; if(ptr!=0&&*(s32*)((u8*)(u32)ptr+8)!=0&&func_8004C3EC(*(s32*)((u8*)(u32)ptr+8),value,1)!=0)result=1; return result;}

extern s32 D_80097120; extern s32 func_8004C468(s32,s32); s32 func_8004C504(s32 value){s32 result=0; s32 ptr=D_80097120; if(ptr!=0&&*(s32*)((u8*)(u32)ptr+8)!=0)result=func_8004C468(*(s32*)((u8*)(u32)ptr+8),value); return result;}

extern s32 D_80097120; s32 func_8004C54C(s32 index,s32 value){s32 result=0; s32 ptr=D_80097120; if(ptr!=0&&*(s32*)((u8*)(u32)ptr+8)!=0&&index>=0xA&&index<0x80){*(s32*)((u8*)(u32)ptr+index*4+0x2C)=value; result=1;} return result;}

extern s32 D_80097120; s32 func_8004C594(s32 index,s32 value){s32 result=0; s32 ptr=D_80097120; if(ptr!=0&&*(s32*)((u8*)(u32)ptr+8)!=0&&index>0&&index<10&&value>=0){*(s32*)((u8*)(u32)ptr+index*4+0x2C)=value; result=1;} return result;}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C5E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C7A0.s")

extern void func_8004C7A0();
void func_8004C874(s32 arg0, s32 arg1) { func_8004C7A0(0, 0, arg0, arg1); }

void func_8004C8A0(void) { func_8004C7A0(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C8C0.s")

s32 func_8004C948(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (4)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C468(temp_a0, arg0);
        }
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C990.s")

u16 func_8004CA10(u16 *arg0) { u16 value = 0; if (arg0 != NULL) { value = *arg0; } return value; }

u16 func_8004CA24(u16 *arg0) { u16 value = 0; if (arg0 != NULL) { value = arg0[1]; } return value; }

s32 func_8004CA38(u8 *arg0) { s32 value = -1; if (arg0 != NULL) { value = arg0[4]; } return value; }

s32 func_8004CA4C(u8 *arg0) { s32 value = -1; if (arg0 != NULL) { value = arg0[5]; } return value; }

u8 *func_8004CA60(u8 *arg0) { u8 *value = NULL; if (arg0 != NULL) { value = arg0 + 8; } return value; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CA74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CB28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CB7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D150.s")

extern void func_8004D150(s32, s32, s32, s32, s32, s32);
void func_8004D19C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) { func_8004D150(a0, a1, a2, a3, 0, a4); }

extern void func_8004CB7C(s32, s32, s32, s32, s32, s32, s32, s32);
void func_8004D1C4(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) { func_8004CB7C(a0, a1, a2, a3, a4, a5, 0, a6); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D1FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D27C.s")

s32 func_8004D314(s32 arg0, s32 arg1) { s32 result = -1; if (arg0 == 0xEF && arg1 == 0) result = 0; return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D334.s")

extern s16 D_80128082;

void func_8004D40C(s32 arg0) {
    D_80128082 = (s16)arg0;
}

extern void *memcpy(void *, const void *, s32); void *func_8004D418(void *dest, const void *src, s32 size) { return (u8 *)memcpy(dest, src, size) + size; }

extern s8 *D_80097140[];
s32 func_8004D43C(s32 arg0, s32 arg1)
{
  s8 *base = D_80097140[arg0];
  s32 result = -1;
  s8 *p = base;
  if ((*p) != 0)
  {
    do
    {
      if (arg1 == (*p))
      {
        result = p - base;
      }
      p++;
    }
    while ((*p) != 0);
  }
  return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D488.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D5B8.s")

extern s32 D_80097120;
extern s32 func_8004C3EC(s32, s32, s32);
s32 func_8004D690(s32 value) { s32 result = 0; s32 ptr = D_80097120; if (ptr != 0 && *(s32 *)((u8 *)(u32)ptr + 0xC) != 0) result = func_8004C3EC(*(s32 *)((u8 *)(u32)ptr + 0xC), value, 1); return result; }

extern s32 func_8004C468(s32, s32);
s32 func_8004D6D8(s32 value) { s32 result = 0; s32 ptr = D_80097120; if (ptr != 0 && *(s32 *)((u8 *)(u32)ptr + 0xC) != 0) result = func_8004C468(*(s32 *)((u8 *)(u32)ptr + 0xC), value); return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D720.s")

typedef union S1_arg1_func_80010CA8 {
    struct {
        /* 0x00 */ s16 unk_00;
        /* 0x02 */ s8 unk_02;
        /* 0x03 */ s8 unk_03;
    };
    u32 raw;
} S1_arg1_func_80010CA8;
void func_8004D7F8(u16* arg0, s32 a1, S1_arg1_func_80010CA8 arg2) {
    s32 cond;
    s32 arg1 = a1;

    if (!arg0) {}

    arg1 *= 2;
    osInvalDCache(arg0, arg1);

    cond = arg1 >= 2;
    arg1 -= 2;
    // clang-format off
    while (cond != 0) {
        *arg0 = func_80037B08(*arg0, arg2);        cond = arg1 >= 2;        arg1 -= 2;
        arg0++;
    }
    // clang-format on
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D878.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D998.s")

s32 func_8004C8C0(u16);
s32 func_8004DA18(void *arg0) {
    s32 var_s0;

    var_s0 = 1;
    if (func_8004C8C0((*(u16 *)((u8 *)(arg0) + (0x18)))) == 0) {
        var_s0 = 0;
    }
    if (func_8004C8C0((*(u16 *)((u8 *)(arg0) + (0x1C)))) == 0) {
        var_s0 = 0;
    }
    if (func_8004C8C0((*(u16 *)((u8 *)(arg0) + (0x20)))) == 0) {
        var_s0 = 0;
    }
    if (func_8004C8C0((*(u16 *)((u8 *)(arg0) + (0x24)))) == 0) {
        var_s0 = 0;
    }
    return var_s0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DA8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DAF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DB5C.s")

s32 func_8004DC6C(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (0x1C)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C3EC(temp_a0, arg0, 1);
        }
    }
    return var_v1;
}

s32 func_8004DCB4(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (0x1C)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C468(temp_a0, arg0);
        }
    }
    return var_v1;
}

void func_8004DCFC(void) { func_8004DB5C(); }

s32 func_8004DD1C(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (0x20)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C3EC(temp_a0, arg0, 1);
        }
    }
    return var_v1;
}

s32 func_8004DD64(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (0x20)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C468(temp_a0, arg0);
        }
    }
    return var_v1;
}

s32 func_8004C3B0(s32, s32);

s32 func_8004DDAC(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (0x20)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C3B0(temp_a0, arg0);
        }
    }
    return var_v1;
}

s32 func_8004DDF4(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (0x24)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C3EC(temp_a0, arg0, 0);
        }
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DE3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DE84.s")

void func_8004DEF8(s32 arg0) { func_8004DE84(arg0, 0); }

void func_8004DF18(s32 arg0, s32 arg1) { func_8004DF38(arg0, arg1, 0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DF38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DFEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004E018.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004E0F0.s")
#endif
