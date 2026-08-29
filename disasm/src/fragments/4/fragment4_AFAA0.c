#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818014C0.s")

f64 func_818014C0(f64, f64);

f32 func_81801748(void *arg0) {
    return (f32) func_818014C0((f64) (*(s16 *)((u8 *)(arg0) + (2))), (f64) (*(s16 *)((u8 *)(arg0) + (0))));
}

extern u8 *D_81805930;
extern u8 D_81805CE8[];
void func_81801780(void) {
    D_81805930 = D_81805CE8;
}

extern u8 D_81805CE0[];
void func_81801794(void) {
    D_81805930 = D_81805CE0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818017A8.s")

void func_81801810(u8 *arg0, s32 arg1, s32 arg2) {
    *(u16 *)arg0 = (u16)arg1;
    *(u16 *)(arg0 + 2) = (u16)arg2;
}

f32 func_8180181C(void *arg0) {
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = (*(s16 *)((u8 *)(arg0) + (0)));
    temp_v1 = (*(s16 *)((u8 *)(arg0) + (2)));
    return sqrtf((f32) ((temp_v0 * temp_v0) + (temp_v1 * temp_v1)));
}

void func_81801854(u8 *arg0, u8 *arg1, u8 *arg2) {
    *(s16 *)(arg0 + 0) = *(s16 *)(arg2 + 0) + *(s16 *)(arg1 + 0);
    *(s16 *)(arg0 + 2) = *(s16 *)(arg2 + 2) + *(s16 *)(arg1 + 2);
}

void func_81801878(u8 *arg0, u8 *arg1, u8 *arg2) { *(s16 *)(arg0 + 0) = *(s16 *)(arg1 + 0) - *(s16 *)(arg2 + 0); *(s16 *)(arg0 + 2) = *(s16 *)(arg1 + 2) - *(s16 *)(arg2 + 2); }

extern f32 __cosf(f32);
extern f32 __sinf(f32);
extern void func_81801810(u8 *, s32, s32);
void func_8180189C(u8 *arg0, void *arg1, f32 arg2) {
    struct { s16 x; s16 y; } *point;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    point = arg1;
    sp18 = __cosf(arg2);
    sp1C = __sinf(arg2);
    sp20 = __sinf(arg2);
    func_81801810(arg0, (s32)(((f32)point->x * sp18) - (sp1C * (f32)point->y)), (s32)((__cosf(arg2) * (f32)point->y) + ((f32)point->x * sp20)));
}

extern void func_8180194C(u8 *, u8 *, u8 *, f32);
void func_8180194C(u8 *arg0, u8 *arg1, u8 *arg2, f32 arg3) {
    *(s16 *)(arg0 + 0) = (s16)(*(s16 *)(arg1 + 0) +
        (*(s16 *)(arg2 + 0) - *(s16 *)(arg1 + 0)) * arg3);
    *(s16 *)(arg0 + 2) = (s16)(*(s16 *)(arg1 + 2) +
        (*(s16 *)(arg2 + 2) - *(s16 *)(arg1 + 2)) * arg3);
}

s32 func_818019B8(u8 *arg0, u8 *arg1) {
    s32 result = *(s16 *)(arg1 + 0) == *(s16 *)(arg0 + 0);
    if (result) {
        result = *(s16 *)(arg1 + 2) == *(s16 *)(arg0 + 2);
    }
    return result;
}

void func_818019E8(u8 *arg0) {
    if (*(s16 *)(arg0 + 4) < 0) *(s16 *)(arg0 + 4) = 0;
    if (*(s16 *)(arg0 + 6) < 0) *(s16 *)(arg0 + 6) = 0;
}

void func_81801A10(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 value = arg4;
    *(u16 *)(arg0 + 4) = (u16)arg3;
    *(u16 *)(arg0 + 6) = (u16)value;
    *(u16 *)(arg0 + 0) = (u16)arg1;
    *(u16 *)(arg0 + 2) = (u16)arg2;
}

void func_81801A28(u8 *arg0, u8 *arg1, u8 *arg2) {
    *(s16 *)(arg0 + 0) = *(s16 *)(arg2 + 0) + *(s16 *)(arg1 + 0);
    *(s16 *)(arg0 + 2) = *(s16 *)(arg2 + 2) + *(s16 *)(arg1 + 2);
    *(s16 *)(arg0 + 4) = *(s16 *)(arg1 + 4) - *(s16 *)(arg2 + 0) - *(s16 *)(arg2 + 4);
    *(s16 *)(arg0 + 6) = *(s16 *)(arg1 + 6) - *(s16 *)(arg2 + 2) - *(s16 *)(arg2 + 6);
    func_818019E8(arg0);
}

s32 func_81801A94(s32 arg0, s32 arg1) {
    return arg1 < arg0 ? arg1 : arg0;
}

s32 func_81801AB0(s32 arg0, s32 arg1) {
    return arg0 < arg1 ? arg1 : arg0;
}

void func_81801ACC(u8 *arg0, u8 *arg1, u8 *arg2) {
    *(s16 *)(arg0 + 0) = func_81801AB0(*(s16 *)(arg1 + 0), *(s16 *)(arg2 + 0));
    *(s16 *)(arg0 + 2) = func_81801AB0(*(s16 *)(arg1 + 2), *(s16 *)(arg2 + 2));
    *(s16 *)(arg0 + 4) = func_81801A94(*(s16 *)(arg1 + 4) + *(s16 *)(arg1 + 0),
                                         *(s16 *)(arg2 + 4) + *(s16 *)(arg2 + 0))
                         - *(s16 *)(arg0 + 0);
    *(s16 *)(arg0 + 6) = func_81801A94(*(s16 *)(arg1 + 6) + *(s16 *)(arg1 + 2),
                                         *(s16 *)(arg2 + 6) + *(s16 *)(arg2 + 2))
                         - *(s16 *)(arg0 + 2);
    func_818019E8(arg0);
}

void func_81801B7C(u8 *arg0, u8 *arg1, u8 *arg2) {
    func_81801854(arg0, arg1, arg2);
    func_81801854(arg0 + 4, arg1 + 4, arg2 + 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801BC0.s")

s32 func_81801C30(u8 *arg0, u8 *arg1) {
    return (*(s16 *)(arg0 + 0) + *(s16 *)(arg0 + 4) < *(s16 *)(arg1 + 0))
        || (*(s16 *)(arg1 + 0) + *(s16 *)(arg1 + 4) < *(s16 *)(arg0 + 0))
        || (*(s16 *)(arg0 + 2) + *(s16 *)(arg0 + 6) < *(s16 *)(arg1 + 2))
        || (*(s16 *)(arg1 + 2) + *(s16 *)(arg1 + 6) < *(s16 *)(arg0 + 2));
}

s32 func_81801C90(u8 *arg0) {
    return !func_81801C30(arg0, D_81805930);
}

extern void func_8180194C(u8 *, u8 *, u8 *, f32);
void func_81801CB8(u8 *arg0, u8 *arg1, u8 *arg2, f32 arg3) {
    func_8180194C(arg0, arg1, arg2, arg3);
    func_8180194C(arg0 + 4, arg1 + 4, arg2 + 4, arg3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801D04.s")

extern void func_81801D04(u8 *);
void func_81801E3C(u8 *arg0, u8 *arg1) { u8 sp18[8]; func_81801A28(sp18, arg0, arg1); func_81801D04(sp18); }

s32 func_81801E70(u8 *arg0, u8 *arg1) {
    return func_818019B8(arg0, arg1) && func_818019B8(arg0 + 4, arg1 + 4);
}

void func_81801EB8(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801EC0.s")

void func_81801F04(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) { *(u16 *)(arg0 + 0) = arg1; *(u16 *)(arg0 + 2) = arg2; *(u16 *)(arg0 + 4) = arg3; *(u16 *)(arg0 + 6) = arg4; }

void func_81801F1C(u8 *arg0, u8 *arg1, u8 *arg2) {
    *(s16 *)(arg0 + 0) = *(s16 *)(arg2 + 0) + *(s16 *)(arg1 + 0);
    *(s16 *)(arg0 + 2) = *(s16 *)(arg2 + 2) + *(s16 *)(arg1 + 2);
    *(s16 *)(arg0 + 4) = *(s16 *)(arg2 + 4) + *(s16 *)(arg1 + 4);
    *(s16 *)(arg0 + 6) = *(s16 *)(arg2 + 6) + *(s16 *)(arg1 + 6);
}

extern void func_8004C8C0(s32);
void func_81801F60(u8 *arg0) {
    func_8004C8C0(*(s16 *)arg0);
}

extern void func_8004C4B0(s32);
void func_81801F80(u8 *arg0) {
    func_8004C4B0(*(s16 *)arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801FA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81801FE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802168.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818021B4.s")

extern Gfx *D_800D0510;
void func_81802208(s32 arg0, f32 arg1) {
    if (arg1 < 1.0f) {
        gDPSetRenderMode(D_800D0510++, 0x00504240, 0);
        return;
    }
    switch (*(s8 *)((u8 *)(u32)arg0 + 8)) {
    case 0:
        gDPSetRenderMode(D_800D0510++, 0x00504240, 0);
        break;
    case 1:
        gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
        break;
    case 2:
        gDPSetRenderMode(D_800D0510++, 0x0F0A7008, 0);
        break;
    }
}

void func_81802308(s32 arg0) {
    if (*(s8 *)((u8 *)(u32)arg0 + 0xA) >= 0) {
        gDPSetCombine(D_800D0510++,
            GCCc0w0(*(s8 *)((u8 *)(u32)arg0 + 0xA), *(s8 *)((u8 *)(u32)arg0 + 0xC), *(s8 *)((u8 *)(u32)arg0 + 0xE), *(s8 *)((u8 *)(u32)arg0 + 0x10)) | GCCc1w0(*(s8 *)((u8 *)(u32)arg0 + 0x12), *(s8 *)((u8 *)(u32)arg0 + 0x14)),
            GCCc0w1(*(s8 *)((u8 *)(u32)arg0 + 0xB), *(s8 *)((u8 *)(u32)arg0 + 0xD), *(s8 *)((u8 *)(u32)arg0 + 0xF), *(s8 *)((u8 *)(u32)arg0 + 0x11)) | GCCc1w1(*(s8 *)((u8 *)(u32)arg0 + 0x13), *(s8 *)((u8 *)(u32)arg0 + 0x16), *(s8 *)((u8 *)(u32)arg0 + 0x18), *(s8 *)((u8 *)(u32)arg0 + 0x15), *(s8 *)((u8 *)(u32)arg0 + 0x17), *(s8 *)((u8 *)(u32)arg0 + 0x19)));
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802438.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818024B0.s")

extern void func_80049770(s32, s32, s32, s32, s32);
extern void func_80049828(s32, s32, s32, s32, s32);
extern void func_81802208(s32, f32);
extern void func_81802308(s32);
void func_81802690(u8 *arg0, f32 arg1) {
    func_81802208((s32)arg0, arg1);
    func_81802308((s32)arg0);
    func_80049770(0, arg0[0], arg0[1], arg0[2], (s32)((f32)arg0[3] * arg1));
    func_80049828(0, arg0[4], arg0[5], arg0[6], (s32)((f32)arg0[7] * arg1));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802754.s")

extern void func_81802438();
extern void func_81802208(s32, f32);
extern void func_81802308(s32);
extern void func_818024B0(s32, s32);
void func_81802BAC(s32 arg0, s32 arg1) { func_81802438(arg0, arg1); func_81802208(arg0, *(f32 *)&arg1); func_81802308(arg0); func_818024B0(arg0, arg1); }

s32 func_81802BF0(s32 arg0) {
    s32 count = 0;
    while (arg0 >= 2) {
        arg0 >>= 1;
        count++;
    }
    return count;
}

extern u8 *func_8004CA60(u8 *);
extern void func_800459AC(u8 *, u8, u8, u16, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 func_81802BF0(s32);
s32 func_81802C14(u8 *arg0) {
    s32 result;
    s32 pad;
    s32 first;
    u8 *value;
    result = 0;
    if (arg0 != NULL) {
        result = 1;
        value = func_8004CA60(arg0);
        first = func_81802BF0((s32)*(u16 *)(arg0 + 0));
        func_800459AC(value, *(u8 *)(arg0 + 4), *(u8 *)(arg0 + 5), *(u16 *)(arg0 + 0), (s32)*(u16 *)(arg0 + 2), 1, 0, 0, 0, first, func_81802BF0((s32)*(u16 *)(arg0 + 2)), 0, 0);
    }
    return result;
}

extern u8 *func_81801FA0(void);
extern s32 func_81802C14(u8 *);
extern s32 func_8004D1FC(u8 *);
extern u8 D_80094D90[];
extern u8 D_80094DB8[];
u8 *func_81802CA8(void *arg0, s32 arg1) {
    u8 *value;
    value = func_81801FA0();
    if (value != NULL) {
        func_81802438(*(s32 *)((u8 *)(u32)arg0 + 0xC));
        if (arg1 != 0) {
            func_81802C14(value);
        } else {
            func_8004D1FC(value);
        }
    } else if (*(u8 *)(*(u8 **)((u8 *)(u32)arg0 + 0xC) + 3) >= 0xFF) {
        gSPDisplayList(D_800D0510++, D_80094D90);
    } else {
        gSPDisplayList(D_800D0510++, D_80094DB8);
    }
    func_81802208(*(s32 *)((u8 *)(u32)arg0 + 0xC), 1.0f);
    func_81802308(*(s32 *)((u8 *)(u32)arg0 + 0xC));
    func_818024B0(*(s32 *)((u8 *)(u32)arg0 + 0xC), 0x3F800000);
    return value;
}

void func_81802D98(void *arg0) {
    func_8004C8C0((s32) (*(s16 *)((u8 *)(arg0) + (0x30))));
    func_8004C8C0((s32) (*(s16 *)((u8 *)(arg0) + (0))));
}

void func_81802DC8(u8 *arg0) {
    func_8004C8C0(*(s16 *)arg0);
}

extern void func_8004C8C0(s32);
void func_81802DE8(u8 *arg0) {
    u8 *ptr = arg0;
    s16 v0 = *(s16 *)ptr;
    while (v0 >= 0) {
        func_8004C8C0(v0);
        ptr += 0x20;
        v0 = *(s16 *)ptr;
    }
}

void func_81802E34(u8 *arg0) {
    func_8004C4B0(*(s16 *)arg0);
}

extern void func_8004C4B0(s32);
void func_81802E54(u8 *arg0) {
    u8 *ptr = arg0;
    s16 v0 = *(s16 *)ptr;
    while (v0 >= 0) {
        func_8004C4B0(v0);
        ptr += 0x20;
        v0 = *(s16 *)ptr;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81802EA0.s")

void func_8004989C(s32 arg0);
void func_800496A4(s32 a0, s32 a1);
void func_8180351C(void *arg0) {
    func_8004989C((s32) (*(s8 *)((u8 *)(arg0) + (6))));
    func_800496A4((s32) (*(s8 *)((u8 *)(arg0) + (4))), (*(s8 *)((u8 *)(arg0) + (5))) + 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803558.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803668.s")

extern void func_800498C4();
extern void func_81803558(s32, s32, s32, s32);
extern void func_800499EC();
void func_818036D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { func_800498C4(); func_81803558(arg0, arg1, arg2, arg3); func_800499EC(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803720.s")

void func_818037A0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    if (*(s16 *)(arg0 + 4) <= 0) *(s16 *)(arg0 + 4) = (s16)arg2;
    if (*(s16 *)(arg0 + 6) <= 0) *(s16 *)(arg0 + 6) = (s16)arg3;
    if (*(s16 *)(arg1 + 0) < 0) *(s16 *)(arg1 + 0) = *(s16 *)(arg0 + 0) % arg2;
    if (*(s16 *)(arg1 + 2) < 0) *(s16 *)(arg1 + 2) = *(s16 *)(arg0 + 2) % arg3;
    if (*(s16 *)(arg1 + 4) < 0) *(s16 *)(arg1 + 4) = (s16)arg2;
    if (*(s16 *)(arg1 + 6) < 0) *(s16 *)(arg1 + 6) = (s16)arg3;
}

extern void func_81800020(f32, f32, f32, f32, s32, s32, f32, f32);
extern s32 func_8004D1FC(u8 *);
void func_81803868(u8 *arg0, void *arg1, void *arg2) {
    func_8004D1FC(arg0);
    func_81800020((f32)*(s16 *)((u8 *)arg1 + 0), (f32)*(s16 *)((u8 *)arg1 + 2), (f32)*(s16 *)((u8 *)arg1 + 4), (f32)*(s16 *)((u8 *)arg1 + 6), (s32)*(s16 *)((u8 *)arg2 + 0), (s32)*(s16 *)((u8 *)arg2 + 2), (f32)(*(s16 *)((u8 *)arg2 + 4) / *(s16 *)((u8 *)arg1 + 4)), (f32)(*(s16 *)((u8 *)arg2 + 6) / *(s16 *)((u8 *)arg1 + 6)));
}
void func_81803868_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803964.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803A74.s")

s32 func_81803AE4(u16 arg0) {
    if (arg0 & 0x8000)
        return 1;
    if (arg0 & 0x4000)
        return -1;
    return 0;
}

extern void func_81802E54(u8 *);
extern void func_81802DE8(u8 *);
void func_81803B18(void *arg0) {
    s32 i;
    s32 offset;
    u8 *entry;
    u8 *list0;
    u8 *list1;
    if (*(s32 *)((u8 *)arg0 + 0) != 0) {
        i = 0;
        offset = 0;
        if (*(u8 *)((u8 *)arg0 + 4) > 0) {
            do {
                entry = *(u8 **)((u8 *)arg0 + 0) + offset;
                list0 = *(u8 **)(entry + 0x10);
                if (list0 != NULL) {
                    func_81802E54(list0);
                }
                list1 = *(u8 **)(entry + 0x14);
                if (list1 != NULL) {
                    func_81802DE8(list1);
                }
                i += 1;
                offset += 0x18;
            } while (i < *(u8 *)((u8 *)arg0 + 4));
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803BB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803BE8.s")

extern u8 *func_81803BB8();
extern s32 func_81803BE8();
s32 func_81803C14(s32 arg0, s32 arg1) {
    s32 mask;
    u8 *value;

    mask = func_81803BE8(arg0, arg1);
    value = func_81803BB8(arg0, arg1);
    if (value == 0) return 0;
    if (mask == 0) return 0;
    if (*value >= 0x21) return 0;
    return ((1 << (*value + 0x1F)) & mask) != 0;
}

void func_81803C9C(void *arg0)
{
  u8 *temp_v0;
  temp_v0 = func_81803BB8();
  if ((*((s32 *) (((u8 *) arg0) + 0))) != 0)
  {
    *temp_v0 = *((u8 *) (((u8 *) arg0) + 5));
    if (arg0)
    {
    }
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803CD4.s")

extern f32 func_81803CD4(f32);

void func_81803D44(f32 arg0, f32 arg1) {
    func_81803CD4(func_81803CD4(arg1) - func_81803CD4(arg0));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81803D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81804088.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_818042E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AFAA0/func_81804534.s")
#endif
