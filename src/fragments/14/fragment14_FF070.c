#include "global.h"


#ifdef VERSION_US
extern u8 D_8009F860;

s32 func_81306EE0(u8 *arg0, s32 arg1) {
    u8 v1 = D_8009F860;
    if (arg1 == arg0[0x137FB]) {
        if (v1 == 1) {
            return 4;
        }
        return v1;
    }
    return v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81306F20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81306F74.s")

extern void func_81306F74(void *, void *);
extern void func_81609A90(u8 *, u8 *);
void func_8130707C(void *arg0, s32 arg1) {
    struct S { u8 pad[0x137D0]; f32 value; };
    u8 sp30[8];
    u8 sp28[8];
    f32 sp24;

    sp24 = ((struct S *)arg0)->value;
    ((struct S *)arg0)->value = 0.0f;
    func_81306F74(arg0, sp30);
    ((struct S *)arg0)->value = 16.0f;
    func_81306F74(arg0, sp28);
    if (arg1 != 0) {
        func_81609A90(sp30, sp28);
    } else {
        func_81609A90(sp28, sp30);
    }
    ((struct S *)arg0)->value = sp24;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81307128.s")

void *func_81307204(void *arg0, s32 arg1) {
    while (arg1-- > 0) {
        arg0 = *(void **)((u8 *)arg0 + 0x33A0);
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81307228.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130728C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_813074E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81307570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81307600.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130785C.s")

extern void func_8130785C(void *, void *, s32);
void func_81307C94(void *arg0) {
    s32 var_s0;
    void *var_s1;

    var_s1 = (*(void **)((u8 *)(arg0) + (0x137A8)));
    var_s0 = 0;
    do {
        func_8130785C(arg0, var_s1, (*(u8 *)((u8 *)(arg0) + (0x137F9))) + var_s0);
        var_s0 += 1;
        var_s1 = (*(void **)((u8 *)(var_s1) + (0x33A0)));
    } while (var_s0 != 3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81307D08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81307DC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81308014.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81308078.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130881C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81308E3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81308F54.s")

extern s32 func_8130437C(s32 arg0);
extern void func_800226C0(s32);
void func_8130911C(void *arg0) {
    struct S { u8 pad0[0x137AC]; s32 value; u8 gap0[0x20]; f32 fvalue; u8 gap1[0x10]; s32 flag; u8 gap2[0x8]; s32 flag2; u8 gap3[1]; u8 state; };
    struct S *s = arg0;
    s32 result = func_8130437C(s->value + 0x15370);
    if (result == -1) {
        goto neg1;
    }
    if (result != 1) {
        goto end;
    }
    s->flag = 1;
    s->state = 4;
    func_800226C0(3);
    goto end;
neg1:
    s->flag2 = 0;
    s->flag = 1;
    s->fvalue = 16.0f;
    s->state = 6;
    func_800226C0(3);
end:
    ;
}

extern s32 func_813042E4(s32, void *);
extern void func_800226C0(s32);
void func_813091E0(void *arg0) {
    struct S { u8 pad0[0x137AC]; s32 value; u8 gap[0x34]; s32 flag; u8 gap1[0xD]; u8 state; };
    struct S *s = arg0;
    if (func_813042E4(s->value + 0x15370, s) != 0) {
        s->flag = 1;
        s->state = 4;
        func_800226C0(2);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130924C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81309394.s")

extern f32 func_816092FC(void);
extern void func_800226C0(s32);
void func_813094E0(void *arg0) {
    struct S { u8 pad0[0x137B4]; s16 count; u8 gap0[0x1E]; s16 x; s16 y; u8 gap1[0x1D]; u8 state; };
    struct S *s = arg0;
    s16 temp_v0;

    temp_v0 = s->count;
    if (temp_v0 > 0) {
        s->count = temp_v0 - 1;
        s->x = -1;
        s->y = -7;
        s->state = 9;
        func_800226C0(1);
    }
}

extern void func_800226C0(s32);
void func_81309550(void *arg0) {
    struct S { u8 pad0[0x137B4]; s16 count; u8 gap0[0x1E]; s16 x; s16 y; u8 gap1[0x1D]; u8 state; };
    struct S *s = arg0;
    s16 temp_v0;

    temp_v0 = s->count;
    if (temp_v0 < 3) {
        s->count = temp_v0 + 1;
        s->x = 1;
        s->y = 7;
        s->state = 9;
        func_800226C0(1);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_813095C4.s")

extern void func_813095C4(void *, s32, s32);
extern void func_800226C0(s32);
void func_813096B4(void *arg0) {
    struct S { u8 pad0[0x137B6]; s16 count; u8 gap0[0x1C]; s16 x; s16 y; u8 gap1[0x1D]; u8 state; };
    struct S *s = arg0;
    s16 temp_v0;

    temp_v0 = s->count;
    if (temp_v0 != 0) {
        s->count = temp_v0 - 1;
        s->x = -1;
        s->y = -2;
        s->state = 10;
        func_800226C0(1);
    } else {
        func_813095C4(arg0, 8, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81309740.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81309820.s")

extern void func_800226C0(s32);
extern void func_81307C94(void *arg0);
void func_813098B0(void *arg0) {
    struct S { u8 pad0[0x137B4]; s16 count; s16 count2; u8 gap[0x41]; u8 value; };
    struct S *s = arg0;

    D_8009F860 += 1;
    s->count = 0;
    s->count2 = 0;
    s->value = 0;
    if (D_8009F860 >= 4) {
        D_8009F860 = 1;
    }
    func_81307C94(arg0);
    func_800226C0(0x12);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81309928.s")

void func_81309ACC(u8 *arg0) {
    *(f32 *)(arg0 + 0x137D0) = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81309AE0.s")

void func_81309D00(u32 arg0)
{
    int new_var;
    u8 *p = (u8 *)((u32)arg0);
    u8 v = p[0x137FA];

    if (v)
    {
        p[0x137F5] = v;
        new_var = 0x137FA;
        if (0) { }
        p[new_var] = 0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81309D34.s")

extern f32 func_816092FC(void);
void func_81309DD8(void *arg0) {
    struct S { u8 pad0[0x137D0]; f32 value; u8 gap0[0x10]; s32 status; u8 gap1[0xD]; u8 state; };
    struct S *s = arg0;
    f32 temp_fv1;

    s->value = (f32)(s->value - func_816092FC());
    temp_fv1 = s->value;
    if (temp_fv1 <= 0.0f) {
        s->state = 2;
        s->value = 0.0f;
    } else if (temp_fv1 >= 16.0f) {
        s->value = 16.0f;
    }
    s->status = 1;
}

f32 func_81309E80(f32 arg0) {
    f32 result;
    if (arg0 > 0.0f) {
        result = arg0;
    } else {
        result = -arg0;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_81309EB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130A044.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130A460.s")

extern void func_8130707C(void *arg0, s32 arg1);
s32 func_8130A570(void *arg0, s32 arg1) {
    struct S { u8 pad0[0x137F0]; s32 value; u8 gap0; u8 state; u8 gap1[4]; u8 mode; };
    struct S *s = arg0;

    if (s->state != 4) {
        return 0;
    }
    s->value = arg1;
    s->mode = 6;
    func_8130707C(arg0, 0);
    return 1;
}

void func_8130A5D0(u8 *arg0) {
    *(s32 *)(arg0 + 0x137E4) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130A5E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130A708.s")

s32 func_8130A760(const u8 *arg0) {
    return ((arg0[0x137F5] ^ 2) == 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130A778.s")

u8 func_8130A880(u8 arg0) {
    return arg0;
}

extern void func_8130A778(u8 *, s32, u8 (*)(u8));
extern u8 func_800637C0(u8);
extern u8 func_80073450(u8);
extern u8 func_8130A880(u8);
void func_8130A88C(u8 *arg0) {
    func_8130A778(arg0, 2, func_8130A880);
    func_8130A778(arg0, 3, func_800637C0);
    func_8130A778(arg0, 4, func_80073450);
}

extern void func_8130B3B8(void *, void *);
extern void func_81609A90(u8 *, u8 *);
void func_8130A8E0(void *arg0, s32 arg1) {
    struct S { u8 pad[0xE8F0]; f32 value; };
    u8 sp30[8];
    u8 sp28[8];
    f32 sp24;

    sp24 = ((struct S *)arg0)->value;
    ((struct S *)arg0)->value = 0.0f;
    func_8130B3B8(arg0, sp30);
    ((struct S *)arg0)->value = 16.0f;
    func_8130B3B8(arg0, sp28);
    if (arg1 != 0) {
        func_81609A90(sp30, sp28);
    } else {
        func_81609A90(sp28, sp30);
    }
    ((struct S *)arg0)->value = sp24;
}


extern void (*D_8160BD1C)(f32);
void func_8130A98C(void *arg0) {
    D_8160BD1C(*(f32 *)((u8 *)arg0 + 0xE8FC) / 16);
}

s32 func_8130A9C8(u8 *arg0) {
    return arg0[0xE912] == 7;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130A9DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130AA18.s")


s32 func_8130AA54(u8 *arg0, s32 arg1) {
    u8 *base = arg0 + 0x8000;
    return (arg1 != base[0x6914] + base[0x6915])
        || (base[0x6913] != 0)
        || (*(s32 *)(base + 0x690C) != 0)
        || (base[0x6912] < 0xC);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130AAA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130AC40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130AEF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130AF94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130B06C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130B0E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130B12C.s")

extern s32 func_8160A33C(s32 arg0, u8 arg1);
s32 func_8130B1F4(u8 *arg0) {
    u8 *base = arg0 + 0x8000;
    return func_8160A33C(*(s32 *)(base + 0x68E8), base[0x6914]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130B220.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130B320.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130B3B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130B4E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130B620.s")

s32 func_8130B74C(void *arg0) {
    struct S { u8 pad[0xE8F0]; f32 x; u8 gap[8]; f32 y; };
    struct S *s = arg0;
    s->x = 0.0f;
    s->y = 0.0f;
    return 1;
}

extern f32 func_816092FC(void);
s32 func_8130B770(void *arg0) {
    struct S { u8 pad0[0xE8F0]; f32 value; u8 gap0[8]; f32 zero; u8 gap1[0x12]; u8 state; };
    struct S *s = arg0;
    s->value += func_816092FC();
    s->zero = 0.0f;
    if (s->value >= 16.0f) {
        s->value = 16.0f;
        s->state = 2;
    }
    return 1;
}

extern f32 func_816092FC(void);
extern void func_8130B620(void *, s32);
/* function: func_8130B7F8 */
s32 func_8130B7F8(void *arg0) {
    struct S { u8 pad[0xE8F0]; f32 first; u8 gap[8]; f32 second; u8 gap2[0x12]; u8 mode; };

    ((struct S *)arg0)->first = 16.0f;
    ((struct S *)arg0)->second += func_816092FC();
    if (((struct S *)arg0)->second >= 16.0f) {
        ((struct S *)arg0)->second = 16.0f;
        ((struct S *)arg0)->mode = 7;
        func_8130B620((void *)arg0, (s32)0);
    }
    return 1;
}

extern f32 func_816092FC(void);
extern void func_8130F5AC(s32);
s32 func_8130B88C(void *arg0) {
    struct S { u8 pad[0xE8F0]; f32 x; u8 gap[8]; f32 y; u8 gap2[0x12]; u8 flag; };

    ((struct S *)arg0)->x = 16.0f;
    ((struct S *)arg0)->y = ((struct S *)arg0)->y - func_816092FC();
    if (((struct S *)arg0)->y <= 0.0f) {
        ((struct S *)arg0)->y = 0.0f;
        ((struct S *)arg0)->flag = 2;
    }
    func_8130F5AC(*(s32 *)((u8 *)arg0 + 0xE8EC));
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130B91C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130B95C.s")

extern void func_800226C0(s32);
extern void func_8130B91C(void *);
void func_8130B9A0(void *arg0) {
    struct S { u8 pad[0xE912]; u8 state; u8 gap; u8 value; };

    u8 temp_v0 = ((struct S *)arg0)->value;
    if ((s32)temp_v0 > 0) {
        ((struct S *)arg0)->value = temp_v0 - 1;
        ((struct S *)arg0)->state = 3;
        func_800226C0(1);
        return;
    }
    func_8130B91C(arg0);
}

extern void func_800226C0(s32);
extern void func_8130B95C(void *);
void func_8130B9F4(void *arg0) {
    struct S { u8 pad[0xE912]; u8 state; u8 gap; u8 value; };

    u8 temp_v0 = ((struct S *)arg0)->value;
    if ((s32)temp_v0 <= 0) {
        ((struct S *)arg0)->value = temp_v0 + 1;
        ((struct S *)arg0)->state = 3;
        func_800226C0(1);
        return;
    }
    func_8130B95C(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130BA48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130BADC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130BC44.s")

extern f32 func_816092FC(void);
extern void func_8130F5AC(s32);
s32 func_8130BD2C(void *arg0) {
    struct S { u8 pad0[0xE8F0]; f32 value; u8 gap0[8]; f32 zero; u8 gap1[0x12]; u8 state; };
    struct S *s = arg0;
    s->zero = 0.0f;
    s->value -= func_816092FC();
    if (s->value <= 0.0f) {
        s->value = 0.0f;
        s->state = 0xD;
    }
    func_8130F5AC(*(s32 *)((u8 *)arg0 + 0xE8EC));
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130BDB8.s")

extern f32 func_816092FC(void);
extern void func_8130AF94(void *arg0);
extern s32 func_81302290(void *arg0);
extern void func_800226C0(s32 arg0);
struct S8130BF1C { u8 pad0[0xE904]; f32 value; u8 gap[0xA]; u8 state; };
s32 func_8130BF1C(struct S8130BF1C *arg0) {
    arg0->value += func_816092FC();
    if (arg0->value >= 16.0f) {
        arg0->value = 16.0f;
        func_8130AF94(arg0);
        if (func_81302290(*(void **)((u8 *)arg0 + 0xE8EC)) > 0) {
            arg0->state = 0xB;
            func_800226C0(0x11);
        } else {
            arg0->state = 2;
        }
    }
    return 1;
}

s32 func_8130BFCC(void *arg0) {
    struct S { u8 pad[0xE8F0]; f32 x; u8 gap[8]; f32 y; };
    struct S *s = arg0;
    s->y = 0.0f;
    s->x = 0.0f;
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130BFF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130C0BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130C14C.s")

extern f32 func_816092FC(void);
extern void func_8130B12C(void *arg0);
s32 func_8130C270(void *arg0) {
    struct S { u8 pad0[0xE8F8]; f32 value; u8 gap0[0x16]; u8 state; u8 gap1[2]; u8 count; };
    struct S *s = arg0;
    f32 delta = func_816092FC();
    f32 step = delta / 8;
    if (s->value + step < (f32)s->count) {
        s->value = s->value + step;
    } else {
        if ((f32)s->count < s->value - step) {
            s->value = s->value - step;
        } else {
            s->value = (f32)s->count;
            s->state = 2;
        }
    }
    func_8130B12C(arg0);
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130C334.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130C570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130CB5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FF070/func_8130CDD4.s")
#endif
