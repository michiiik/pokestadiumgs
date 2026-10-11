#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0C900.s")

extern void *D_87F119DC;
extern void func_87F0B4AC(void *, f32 *, f32 *, s16 *);
void func_87E0C93C(void) {
    void *state = D_87F119DC;
    func_87F0B4AC(
        *(void **)((u8 *)*(void **)((u8 *)state + 0x38) + 0x0C),
        (f32 *)((u8 *)state + 0x48),
        (f32 *)((u8 *)state + 0x54),
        (s16 *)((u8 *)state + 0x42));
}

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern void func_8003CD84();
void func_87E0C974(s32 arg0, s32 arg1) {
    void *context;

    if (arg0 == 5) {
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238);
        context = *(void **)((u8 *)D_8009491C + 0x14);
        gSPSegment(D_800D0510++, 0xF,
                   *(void **)((u8 *)*(void **)((u8 *)context + 4) + 8));
        gSPDisplayList(D_800D0510++, *(void **)context);
        func_8003CD84();
    }
}

extern void func_87F0BD30(void *, s32, s32, s32);
extern void func_87E0CEE4(void *, s32);
void func_87E0CA2C(void *arg0, s32 arg1) {
    u8 *entry;
    s32 color1;

    entry = (u8 *)arg0 + 0x28 + arg1 * 0xEC;
    entry[0xE8] = arg1;
    *(void **)(entry + 0x88) = (u8 *)*(void **)((u8 *)arg0 + 4) + 0x2190 + arg1 * 0x18;

    *(s32 *)(entry + 0xD4) = (*(u8 *)((u8 *)*(void **)((u8 *)arg0 + 4) + 0x2182) & (1 << arg1)) ? arg1 + 6 : arg1 + 2;

    *(s32 *)(entry + 0xD8) = 0;
    entry[0xE9] &= ~0x80;

    switch (arg1) {
        case 0:
            color1 = 0xC8D2FFFF;
            *(s32 *)(entry + 0xE4) = 0x32325AFF;
            break;
        case 1:
            color1 = 0xC3FFC3FF;
            *(s32 *)(entry + 0xE4) = 0x324632FF;
            break;
        case 2:
            color1 = 0xFFCDCDFF;
            *(s32 *)(entry + 0xE4) = 0x5A3232FF;
            break;
        case 3:
            color1 = 0xFFF5A5FF;
            *(s32 *)(entry + 0xE4) = 0x5A3C28FF;
            break;
    }

    func_87F0BD30(entry + 0xDC, 0x140, 0x24, color1);
    func_87E0CEE4(arg0, arg1);
}

extern void func_8004C8C0(s32);

void func_87E0CB88(void) {
    func_8004C8C0(0x1B2);
    func_8004C8C0(0x160);
    func_8004C8C0(0x1B4);
    func_8004C8C0(0x161);
    func_8004C8C0(0x19F);
}

extern u8 D_87E1A400[];
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern s32 func_80040E80(s32, void *);
extern void MainPool_FinalizeAllocation(s32);
void func_87E0CBC8(void *arg0) {
    s32 temp = MainPool_AllocState(main_pool_get_available(), 0);
    *(s32 *)((u8 *)arg0 + 8) = func_80040E80(temp, D_87E1A400);
    MainPool_FinalizeAllocation(temp);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0CC18.s")

extern void func_87F02684(s32);
extern void func_87E134C0(void);
void func_87E0CD84(s32 arg0) {
    func_87F02684(arg0 + 0x10);
    func_87E134C0();
}

void func_87E0CDAC(void *arg0) {
    void *var_v0;

    var_v0 = (*(void **)((u8 *)(arg0) + (0x1C)));
    if (var_v0 != NULL) {
        do {
            (*(u8 *)((u8 *)(var_v0) + (0x25))) = (u8) ((*(u8 *)((u8 *)(var_v0) + (0x25))) & ~1);
            var_v0 = (*(void **)((u8 *)(var_v0) + (4)));
        } while (var_v0 != NULL);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0CDDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0CE60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0CEE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D0A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D18C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D278.s")

extern void func_87E0D18C(void);
void func_87E0D3A0(void) {
    func_87E0D18C();
}

void func_87E0D3C0(u8 *arg0) {
    *(s32 *)(arg0 + 0x3F4) = 3;
    *(s32 *)(arg0 + 0x3FC) = 0;
    *(s32 *)(arg0 + 0x3F8) = *(s8 *)(*(u8 **)(arg0 + 4) + 0x218D);
    func_87E0D18C();
}

void func_87E0D3F4(u8 *arg0) {
    *(s32 *)(arg0 + 0x3F4) = 4;
    *(s32 *)(arg0 + 0x3FC) = 0;
    func_87E0D18C();
}

void func_87E0D41C(void) {
    func_87E0D18C();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D43C.s")

extern void func_87E0D278(void);
void func_87E0D500(void) {
    func_87E0D278();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D520.s")

extern void func_87F0B1A4(u8 *, u8 *, f32, f32, f32, s32, s32);
typedef struct D6BCNode {
    u8 pad0[4];
    struct D6BCNode *next;
    u8 pad1[0x30];
    u8 *child;
    u8 pad2[0xC];
    f32 values[3];
} D6BCNode;
void func_87E0D6BC(void *arg0) {
    D6BCNode *var_s0;
    var_s0 = *(D6BCNode **)((u8 *)arg0 + 0x1C);
    if (var_s0 != NULL) {
        do {
            func_87F0B1A4(*(u8 **)(var_s0->child + 0xC), (u8 *)var_s0 + 0x48,
                var_s0->values[0], var_s0->values[1] - -120.0f, var_s0->values[2], 30, 0x3000);
            var_s0 = var_s0->next;
        } while (var_s0 != NULL);
    }
}

void func_87E0D73C(void) {
    func_87E0D278();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D75C.s")

extern u32 func_8003570C(void);
extern void func_87E0D18C(void);
s32 func_87E0D7D8(u8 *arg0) {
    s32 i;
    s32 selected;
    s32 max;
    s32 count;
    s32 ret;
    u8 *entry;

    max = 0;
    count = 0;
    func_87E0D18C();
    entry = arg0 + 0x28;
    for (i = 0; i < 4; i++, entry += 0xEC) {
        if (i == 0 || max < *(s32 *)*(void **)(entry + 0x88)) {
            max = *(s32 *)*(void **)(entry + 0x88);
        }
    }
    selected = max;
    ((s8 *)arg0)[0x408] = -1;
    entry = arg0 + 0x28;
    for (i = 0; i != 4; i++, entry += 0xEC) {
        if (selected - *(s32 *)*(void **)(entry + 0x88) == 0) {
            entry[0xE9] |= 0x80;
            count++;
            if ((s8)((s8 *)arg0)[0x408] == -1) {
                ((s8 *)arg0)[0x408] = i;
            }
        }
    }
    if (count == 1) {
        *(s32 *)(arg0 + 0x3F4) = 1;
        ret = 0;
    } else {
        *(s32 *)(arg0 + 0x3F4) = 0;
        ret = 1;
    }
    *(s32 *)(arg0 + 0x400) = 0;
    *(s32 *)(arg0 + 0x3FC) = 0;
    *(s32 *)(arg0 + 0x404) = (func_8003570C() % 9) + 8;
    return ret;
}

extern void func_87E0D0A0(void);
extern void func_87E13558(void *, f32, f32, f32, s32);
extern u32 func_8003570C(void);
void func_87E0D8EC(u8 *arg0) {
    s32 selected;
    s32 i;
    s32 min;
    s32 count;
    u8 *entry;

    min = 0;
    count = 0;
    func_87E0D0A0();
    entry = arg0 + 0x28;
    for (i = 0; i < 4; i++, entry += 0xEC) {
        if (i == 0 || *(s32 *)*(void **)(entry + 0x88) < min) {
            min = *(s32 *)*(void **)(entry + 0x88);
        }
    }
    selected = min;
    ((s8 *)arg0)[0x408] = -1;
    entry = arg0 + 0x28;
    for (i = 0; i != 4; i++, entry += 0xEC) {
        if (selected - *(s32 *)*(void **)(entry + 0x88) == 0) {
            entry[0xE9] |= 0x80;
            count++;
            if ((s8)((s8 *)arg0)[0x408] == -1) {
                ((s8 *)arg0)[0x408] = i;
            }
        } else {
            entry[0xE9] &= 0xFF7F;
        }
    }
    if (count == 1) {
        *(s32 *)(arg0 + 0x3F4) = 0;
        *(s32 *)(arg0 + 0x3FC) = 0;
        *(s32 *)(arg0 + 0x400) = 0x3C;
        func_87E13558(((s8 *)arg0)[0x408] * 0x18C + *(u8 **)(arg0 + 0x18), -123.0f, -2.0f, 0.0f, 1);
    } else {
        *(s32 *)(arg0 + 0x3F4) = 0;
        *(s32 *)(arg0 + 0x400) = 0;
        *(s32 *)(arg0 + 0x3FC) = 0;
    }
    *(s32 *)(arg0 + 0x404) = (func_8003570C() % 9) + 4;
}

extern void func_87E0CEE4(void *, s32);
extern void func_87E134C0(void);
extern void func_87E13490(void);
extern void func_87E13480(void *);
extern void func_87E1366C(void);
void func_87E0DA4C(void *arg0) {
    s32 i;
    u8 *node;

    node = *(u8 **)((u8 *)arg0 + 0x1C);
    *(s32 *)((u8 *)arg0 + 0x3F4) = 4;
    if (node != NULL) {
        do {
            *(u8 *)(node + 0x25) |= 1;
            node = *(u8 **)(node + 4);
        } while (node != NULL);
    }
    i = 0;
    do {
        func_87E0CEE4(arg0, i);
        i += 1;
    } while (i != 4);
    func_87E134C0();
    func_87E13490();
    func_87E13480(NULL);
    func_87E1366C();
}

extern void func_87E0CC18(void *);
extern void func_87F0BD10();
void func_87E0DAE0(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)(arg0) + (0))) = 1;
    (*(s32 *)((u8 *)(arg0) + (4))) = arg1;
    (*(s32 *)((u8 *)(arg0) + (0x3F4))) = 4;
    (*(s32 *)((u8 *)(arg0) + (0x3FC))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x408))) = -1;
    func_87F0BD10();
    func_87E0CB88();
    func_87E0CBC8(arg0);
    func_87E0CC18(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0DB40.s")

s32 func_87E0DC78(u8 *arg0) {
    s32 result = 0;
    if (*(s32 *)(arg0 + 0x3FC) >= 0x29) {
        result = 1;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0DC98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0DE34.s")

extern s32 func_80001FF0(void);
extern void func_87E0DE34(void *);

typedef struct {
    u8 pad[0x88];
    s32 *val;
    u8 pad2[0x60];
} Fragment63_SubStruct;
extern void func_87E0CEE4(void *, s32);
s32 func_87E0E110(void *arg0) {
    s32 sp24 = 0;
    s32 *sp20;
    s32 temp;

    sp20 = ((Fragment63_SubStruct *)((u8 *)arg0 + 0x28))[(s8)((u8 *)arg0)[0x408]].val;
    if ((*(s8 *)(*(u8 **)((u8 *)arg0 + 4) + 0x218D) == *(s32 *)((u8 *)arg0 + 0x3F8)) && (*(s32 *)((u8 *)arg0 + 0x3DC) == 0)) {
        sp24 = 1;
    } else {
        if ((((f32)func_80001FF0() / 60.0f) * 20.0f) >= 0.0f) {
            temp = (s32)((((f32)func_80001FF0() / 60.0f) * 20.0f) + 0.5f);
        } else {
            temp = (s32)((((f32)func_80001FF0() / 60.0f) * 20.0f) - 0.5f);
        }

        if (temp + 1 < *(s32 *)((u8 *)arg0 + 0x3FC)) {
            if (*sp20 == 0) {
                *(s8 *)(*(u8 **)((u8 *)arg0 + 4) + 0x218D) = *(s32 *)((u8 *)arg0 + 0x3F8);
            } else if (*(s32 *)((u8 *)arg0 + 0x3F8) < *(s8 *)(*(u8 **)((u8 *)arg0 + 4) + 0x218D)) {
                func_87E0DE34(arg0);
                *(s32 *)((u8 *)arg0 + 0x3FC) = 0;
                (*sp20)--;
                func_87E0CEE4(arg0, ((s8 *)arg0)[0x408]);
                (*(s32 *)((u8 *)arg0 + 0x3F8))++;
            }
        }
    }

    return sp24;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E2C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E32C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E3EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E714.s")

s32 func_87E0E850(void *arg0)
{
  s32 var_v1;
  void *var_v0;
  u8 *new_var;
  var_v0 = *((void **) (((u8 *) arg0) + 0x1C));
  var_v1 = 1;
  if (var_v0 != 0)
  {
    do
    {
      new_var = (u8 *) (*((void **) (((u8 *) (*((void **) (((u8 *) var_v0) + 0x38)))) + 0xC)));
      if ((*((s32 *) (new_var + 0x84))) != 0)
      {
        var_v1 = 0;
      }
      var_v0 = *((void **) (((u8 *) var_v0) + 4));
    }
    while (var_v0 != 0);
  }
  return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E88C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E9B0.s")

extern void func_87F0AF4C(s32);
void func_87E0F124(s32 arg0) {
    func_87F0AF4C(arg0 + 16);
}

s32 func_87E0F144(void *arg0, s32 arg1) {
    s32 new_var;
    new_var = *((s32 *) (((u8 *) arg0) + 0x18));
    return (arg1 * 0x18C) + new_var;
}
#endif
