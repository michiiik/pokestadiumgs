#include "global.h"


#ifdef VERSION_US
s32 BinArchive_Open(s32, s32, s32, s32);
extern void func_800049B8(s32);
s32 func_80004B4C(s32, s32);
s32 func_800356CC(s32);
extern s32 D_80097124;
extern s32 D_80097128;
void func_8004C020(void) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = BinArchive_Open(func_800356CC(2), 0, 2, 1);
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

s32 func_8004C3B0(s32 arg0, s32 arg1) {
    s32 result;
    u8 *entry;
    result = 0;
    if (arg0 != 0 && arg1 >= 0) {
        entry = (u8 *)((u8 *)(u32)arg0 + arg1 * 0x10 + 0x10);
        if ((u32)arg1 < (u32)*(s32 *)((u8 *)(u32)arg0 + 0xC) && entry != NULL) {
            result = *(s32 *)(entry + 8);
        }
    }
    return result;
}

extern void main_pool_set_func(s32, s32, void (*)(s32, u8 *));
s32 func_8004C3EC(s32 arg0, s32 arg1, s32 arg2) {
    s32 result;
    result = func_8004C3B0(arg0, arg1);
    if (result == 0 || arg2 == 0) {
        result = func_80004B4C(arg0, arg1);
        if (result != 0) {
            main_pool_set_func(result, arg0 + 0x18 + arg1 * 0x10, func_8004C3A4);
        }
    }
    return result;
}

extern s32 func_8004C3B0(s32, s32);
extern void main_pool_try_free(s32);
s32 func_8004C468(s32 arg0, s32 arg1) {
    s32 result;
    s32 value;
    result = 0;
    value = func_8004C3B0(arg0, arg1);
    if (value != 0) {
        main_pool_try_free(value);
        result = 1;
    }
    return result;
}

extern s32 D_80097120; s32 func_8004C4A4(void) { return D_80097120; }

extern s32 D_80097120; extern s32 func_8004C3EC(s32,s32,s32); s32 func_8004C4B0(s32 value){s32 result=0; s32 ptr=D_80097120; if(ptr!=0&&*(s32*)((u8*)(u32)ptr+8)!=0&&func_8004C3EC(*(s32*)((u8*)(u32)ptr+8),value,1)!=0)result=1; return result;}

extern s32 D_80097120; extern s32 func_8004C468(s32,s32); s32 func_8004C504(s32 value){s32 result=0; s32 ptr=D_80097120; if(ptr!=0&&*(s32*)((u8*)(u32)ptr+8)!=0)result=func_8004C468(*(s32*)((u8*)(u32)ptr+8),value); return result;}

extern s32 D_80097120; s32 func_8004C54C(s32 index,s32 value){s32 result=0; s32 ptr=D_80097120; if(ptr!=0&&*(s32*)((u8*)(u32)ptr+8)!=0&&index>=0xA&&index<0x80){*(s32*)((u8*)(u32)ptr+index*4+0x2C)=value; result=1;} return result;}

extern s32 D_80097120; s32 func_8004C594(s32 index,s32 value){s32 result=0; s32 ptr=D_80097120; if(ptr!=0&&*(s32*)((u8*)(u32)ptr+8)!=0&&index>0&&index<10&&value>=0){*(s32*)((u8*)(u32)ptr+index*4+0x2C)=value; result=1;} return result;}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C5E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C7A0.s")

extern void func_8004C7A0();
void func_8004C874(s32 arg0, s32 arg1) {
    func_8004C7A0(0, 0, arg0, arg1);
}

void func_8004C8A0(void) {
    func_8004C7A0();
}

extern s32 func_8004C3EC(s32 arg0, s32 arg1, s32 arg2);
#ifdef CC_CHECK
s32 func_8004C8C0(u16 arg0) {
#else
s32 func_8004C8C0(arg0)
s32 arg0;
{
#endif
    s32 sp18;
    s32 result;
    s32 i;
    s32 value;
    result = 0;
    if (D_80097120 != 0) {
        sp18 = 0;
        value = func_8004C3EC(*(s32 *)((u8 *)(u32)D_80097120 + 4), arg0, 1);
        result = sp18;
        if (value != 0) {
            i = 0;
            if (*(s32 *)(u32)value != 0) {
                do {
                    i++;
                    *(s32 *)((u8 *)(u32)value + i * 4) &= 0xFFFFF;
                } while ((u32)i < (u32)*(s32 *)(u32)value);
            }
            result = 1;
        }
    }
    return result;
}

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

extern s32 func_8004C3B0(s32, s32);
s32 func_8004C990(s32 arg0, s32 arg1) {
    s32 var_v1;
    s32 temp_v0;
    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_v0 = func_8004C3B0(*(s32 *)((u8 *)(u32)D_80097120 + 4), arg0);
        if (temp_v0 != 0 && arg1 >= 0 && (u32)arg1 < (u32)*(s32 *)(u32)temp_v0) {
            var_v1 = *(s32 *)((u8 *)(u32)temp_v0 + arg1 * 4 + 4) + temp_v0 - 8;
        }
    }
    return var_v1;
}

u16 func_8004CA10(u16 *arg0) { u16 value = 0; if (arg0 != NULL) { value = *arg0; } return value; }

u16 func_8004CA24(u16 *arg0) { u16 value = 0; if (arg0 != NULL) { value = arg0[1]; } return value; }

s32 func_8004CA38(u8 *arg0) { s32 value = -1; if (arg0 != NULL) { value = arg0[4]; } return value; }

s32 func_8004CA4C(u8 *arg0) { s32 value = -1; if (arg0 != NULL) { value = arg0[5]; } return value; }

u8 *func_8004CA60(u8 *arg0) { u8 *value = NULL; if (arg0 != NULL) { value = arg0 + 8; } return value; }

s32 func_8004CA74(u8 *arg0) {
    s32 result = 0;
    if (arg0 != NULL) {
        switch (arg0[5]) {
        case 0: result = (*(u16 *)(arg0 + 2) * *(u16 *)(arg0 + 0)) / 2; break;
        case 1: result = *(u16 *)(arg0 + 2) * *(u16 *)(arg0 + 0); break;
        case 2: result = (*(u16 *)(arg0 + 2) * *(u16 *)(arg0 + 0)) * 2; break;
        case 3: result = (*(u16 *)(arg0 + 2) * *(u16 *)(arg0 + 0)) * 4; break;
        default: break;
        }
    }
    return result;
  }

extern s32 func_8004CA74(u8 *);
u8 *func_8004CB28(u8 *arg0) {
    u8 *result;
    u8 *base;
    s32 offset;
    result = NULL;
    if (arg0 != NULL && arg0[4] == 2) {
        base = func_8004CA60(arg0);
        offset = func_8004CA74(arg0);
        result = base + offset + 8;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CB7C.s")

extern void func_8004CB7C(s32, s32, s32, s32, s32, s32, s32, s32);
void func_8004D150(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_8004CB7C(arg0, arg1, 0, 0, arg2, arg3, (s32) (u16) arg4, arg5);
}

extern void func_8004D150(s32, s32, s32, s32, s32, s32);
void func_8004D19C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    func_8004D150(a0, a1, a2, a3, 0, a4);
}

void func_8004D1C4(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    func_8004CB7C(a0, a1, a2, a3, a4, a5, 0, a6);
}

s32 func_8004D1FC(u8 *arg0) {
    s32 sp4C;

    sp4C = 0;
    if (arg0 != NULL) {
        sp4C = 1;
        func_800459AC(func_8004CA60(arg0), (*(u8 *)((u8 *)(arg0) + (4))), (*(u8 *)((u8 *)(arg0) + (5))), (*(u16 *)((u8 *)(arg0) + (0))), (s32) (*(u16 *)((u8 *)(arg0) + (2))), 1, 0, 2, 2, 0, 0, 0, 0);
    }
    return sp4C;
}

extern void func_80045DB4(u8 *, s32, s32, u8, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_8004D27C(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp54;
    sp54 = 0;
    if (arg0 != NULL) {
        sp54 = 1;
        func_80045DB4(func_8004CA60(arg0), arg1, arg2,
                      *(u8 *)(arg0 + 4), (s32)*(u8 *)(arg0 + 5),
                      (s32)*(u16 *)(arg0 + 0), (s32)*(u16 *)(arg0 + 2),
                      1, 0, 2, 2, 0, 0, 0, 0);
    }
    return sp54;
}

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

typedef struct Struct_80128080_4 {
    s16 unk0;
    s16 unk2;
} Struct_80128080_4;

typedef struct Struct_80128080 {
    s16 unk0;
    s16 unk2;
    Struct_80128080_4 *unk4;
} Struct_80128080;
extern Struct_80128080 D_80128080;

extern s32 func_8004D43C(s32, s32);
extern void func_80044270(s16, s16, s16, s16, s32, s32, s32, s32, s32);
extern s16 D_8009712C[];

void func_8004D488(s32 x, s32 y, u8 *str) {
    s32 width = D_8009712C[D_80128080.unk0];
    u8 *s2 = str + 1;
    s32 c = *str;
    s32 temp;

    if (c != 0) {
        do {
            s32 index = func_8004D43C(D_80128080.unk0, c);
            if (index >= 0) {
                func_80044270((s16)x, (s16)y, (s16)width, D_80128080.unk4->unk2, (width * index) << 5, 0, 0x400, 0x400, 0);
            }
            temp = *s2;
            x += width;
            c = temp;
            if (temp != 0) {
                x += D_80128080.unk2;
            }
            s2++;
        } while (temp != 0);
    }
}

extern s16 D_8009712C[];
s32 func_8004D570(s32 arg0, s32 arg1, u8 *arg2) {
    s32 total = 0;
    s32 width = D_8009712C[arg0];
    u8 *ptr = arg2;

    while (*ptr++) {
        total += width + arg1;
    }
    if (total != 0) {
        total -= arg1;
    }
    return total;
}

#include <stdarg.h>

extern void *func_8004D418(void *, const void *, s32);
extern s32 _Printf();
extern s32 func_8004D570(s32, s32, u8 *);
extern void func_8004D488(s32, s32, u8 *);

void func_8004D5B8(s32 x, s32 y, s32 align, const char *fmt, ...) {
    u8 buf[256];
    s32 len;
    va_list args;

    if (D_80128080.unk0 >= 0) {
        va_start(args, fmt);
        len = _Printf(func_8004D418, buf, fmt, args);
        va_end(args);
        if (len > 0) {
            buf[len] = 0;
            switch (align) {
                case 1:
                    x -= func_8004D570(D_80128080.unk0, D_80128080.unk2, buf) / 2;
                    break;
                case 2:
                    x -= func_8004D570(D_80128080.unk0, D_80128080.unk2, buf);
                    break;
            }
            func_8004D488(x, y, buf);
        }
    }
}

extern s32 D_80097120;
extern s32 func_8004C3EC(s32, s32, s32);
s32 func_8004D690(s32 value) { s32 result = 0; s32 ptr = D_80097120; if (ptr != 0 && *(s32 *)((u8 *)(u32)ptr + 0xC) != 0) result = func_8004C3EC(*(s32 *)((u8 *)(u32)ptr + 0xC), value, 1); return result; }

extern s32 func_8004C468(s32, s32);
s32 func_8004D6D8(s32 value) { s32 result = 0; s32 ptr = D_80097120; if (ptr != 0 && *(s32 *)((u8 *)(u32)ptr + 0xC) != 0) result = func_8004C468(*(s32 *)((u8 *)(u32)ptr + 0xC), value); return result; }

extern s32 D_80097120;
extern void func_80003F74(u8 *, u8 *, u8 *, s32);

s32 func_8004D720(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 ptr = D_80097120;
    u8 *v1 = *(u8 **)(ptr + 0x10);
    u8 *t0 = *(u8 **)(ptr + 0x14);
    u8 *t1 = *(u8 **)(ptr + 0x18);
    s32 ret = 0;
    s32 a1_val;
    s32 a2_val;

    if (v1 != NULL) {
        if (t0 != NULL && t1 != NULL) {
            if (arg1 > 0 && arg1 < 0x118) {
                if (arg1 == 0xEB) {
                    a1_val = *(s32 *)(t1 + 4) + *(s32 *)((s32)t1 + (arg3 << 4) + 0x10);
                    a2_val = *(s32 *)((s32)t1 + (arg3 << 4) + 0x14) + a1_val;
                } else if (arg2 != 0) {
                    a1_val = *(s32 *)(t0 + 4) + *(s32 *)((s32)t0 + (arg1 << 4) + 0);
                    a2_val = *(s32 *)((s32)t0 + (arg1 << 4) + 4) + a1_val;
                } else {
                    a1_val = *(s32 *)(v1 + 4) + *(s32 *)((s32)v1 + (arg1 << 4) + 0);
                    a2_val = *(s32 *)((s32)v1 + (arg1 << 4) + 4) + a1_val;
                }
                func_80003F74(arg0, (u8 *)a1_val, (u8 *)a2_val, 0);
                ret = (s32)arg0;
            }
        }
    }
    return ret;
}

typedef union S1_arg1_func_80010CA8 {
    struct {
        /* 0x00 */ s16 unk_00;
        /* 0x02 */ s8 unk_02;
        /* 0x03 */ s8 unk_03;
    };
    u32 raw;
} S1_arg1_func_80010CA8;
void PokeIcon_AdjustImageColors(u16* arg0, s32 a1, S1_arg1_func_80010CA8 arg2) {
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

extern void Gfx_DrawTextureRgba16(s16, s16, s16, s16, u8 *, s16, s32);
void func_8004D998(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4) {
    s32 var_v0;

    var_v0 = arg0;
    if (arg2 != NULL) {
        switch (arg3) {
        case 1:
            var_v0 = arg0 - 0x14;
            break;
        case 2:
            var_v0 = arg0 - 0x28;
            break;
        }
        Gfx_DrawTextureRgba16((s16)var_v0, (s16)arg1, 0x28, 0x28, arg2, 0x28, arg4);
    }
}

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

extern s32 func_8004C8C0(u16); extern s32 func_8004DD1C(s32);
s32 func_8004DA8C(u8 *arg0) {
    s32 result = 1;
    if (arg0[0x15] == 0) {
        if (func_8004C8C0(*(u16 *)(arg0 + 0x10)) == 0) result = 0;
    } else if (func_8004DD1C(*(u16 *)(arg0 + 0x12)) == 0) {
        result = 0;
    }
    return result;
}

extern s32 func_8004C4B0(s32 value);
extern s32 func_8004EB1C(s32);
s32 func_8004DAF0(u8 *arg0, s32 *arg1) {
    s32 ret;
    s32 pad;
    s32 temp;

    ret = 1;
    temp = func_8004EB1C(*(s32 *)(arg0 + 0x10));
    if (!func_8004C4B0(*(u16 *)(arg0 + 0x20))) {
        ret = 0;
    }
    if (arg1 != NULL) {
        *arg1 |= temp;
    }
    return ret;
}

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

void func_8004DCFC(void) {
    func_8004DB5C();
}

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

extern s32 func_80004B78(s32, s32, s32);
s32 func_8004DE3C(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 var_v1;
    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a1 = *(s32 *)((u8 *)(D_80097120) + 0x24);
        if (temp_a1 != 0) {
            var_v1 = func_80004B78(arg0, temp_a1, arg1);
        }
    }
    return var_v1;
}

extern s32 D_80097120;
extern s32 func_8004C3B0(s32, s32);
typedef struct HandlerResult_DE84D { u8 pad[8]; s32 *table; } HandlerResult_DE84D;
s32 func_8004DE84(s32 arg0, s32 arg1) {
    s32 var_v1;
    s32 temp_a0;
    s32 temp_v0;
    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = *(s32 *)((u8 *)(u32)D_80097120 + 0x24);
        if (temp_a0 != 0) {
            temp_v0 = func_8004C3B0(temp_a0, arg0);
            if (temp_v0 != 0) {
                var_v1 = ((HandlerResult_DE84D *(*)(s32, s32))(u32)temp_v0)(0, 0)->table[arg1];
            }
        }
    }
    return var_v1;
}

void func_8004DEF8(s32 arg0) {
    func_8004DE84(arg0, 0);
}

typedef struct Struct_8004E018_Obj {
    u8 pad0[3];
    u8 unk3;
    u8 pad4[4];
    void *unk8;
} Struct_8004E018_Obj;

typedef struct Struct_8004E018_S0 {
    u8 pad0[0x2C];
    void *unk2C;
} Struct_8004E018_S0;

extern s32 func_8004DE84(s32, s32);
extern Struct_8004E018_S0 *func_80040E80(s32, s32);
extern s32 D_80097120;
extern s32 func_8004DF38(s32, s32, s32);

void WidgetTree_RunMessagePanelSilent(s32 arg0, s32 arg1) {
    func_8004DF38(arg0, arg1, 0);
}

s32 func_8004DF38(s32 arg0, s32 arg1, s32 arg2) {
    Struct_8004E018_S0 *res = NULL;
    s32 temp;

    temp = func_8004DE84(arg1, arg2);
    if (temp != 0) {
        s32 t7 = *(s32 *)(D_80097120 + 0x24);
        res = func_80040E80(arg0, temp);
        if (res != NULL) {
            void *(*fp)(s32, s32) = (void *(*)(s32, s32))func_8004C3B0(t7, arg1);
            Struct_8004E018_Obj *obj = (Struct_8004E018_Obj *)fp(0, 0);
            res->unk2C = (void *)fp;
            if (arg2 < obj->unk3) {
                ((Struct_8004E018_S0 **)obj->unk8)[arg2] = res;
            }
        }
    }
    return (s32)res;
}

typedef struct Struct_8004DFEC {
    s32 unk0;
} Struct_8004DFEC;
extern s32 func_8004E018(s32, s32, s32, Struct_8004DFEC);
void func_8004DFEC(s32 arg0, s32 arg1, Struct_8004DFEC arg2) {
    func_8004E018(arg0, arg1, 0, arg2);
}

extern void func_80040F60(Struct_8004E018_S0 *, Struct_8004DFEC);

s32 func_8004E018(s32 arg0, s32 arg1, s32 arg2, Struct_8004DFEC arg3) {
    Struct_8004E018_S0 *s0 = NULL;
    s32 temp;

    temp = func_8004DE84(arg1, arg2);
    if (temp != 0) {
        s32 t7 = *(s32 *)(D_80097120 + 0x24);
        s0 = func_80040E80(arg0, temp);
        if (s0 != NULL) {
            void *(*fp)(s32, s32) = (void *(*)(s32, s32))func_8004C3B0(t7, arg1);
            Struct_8004E018_Obj *obj = (Struct_8004E018_Obj *)fp(0, 0);
            s0->unk2C = (void *)fp;
            if (arg3.unk0 != 0) {
                func_80040F60(s0, arg3);
            }
            if (arg2 < obj->unk3) {
                ((Struct_8004E018_S0 **)obj->unk8)[arg2] = s0;
            }
        }
    }
    return (s32)s0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004E0F0.s")
#endif
