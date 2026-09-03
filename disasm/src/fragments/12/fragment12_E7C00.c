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

extern void func_814029AC();
void func_81403894(void *arg0, s32 arg1) {
    void *temp_a0;
    *(s32 *)((u8 *)arg0 + 0xCC4) = arg1;
    *(u8 *)((u8 *)arg0 + 0xCC0) = 0;
    *(s32 *)((u8 *)arg0 + 0) = 0;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    *(u8 *)((u8 *)arg0 + 0xCC2) = 0;
    temp_a0 = (u8 *)arg0 + 8;
    *(f32 *)((u8 *)temp_a0 + 0xCB4) = 0.0f;
    func_814029AC(temp_a0, 0x41B00000);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814038D4.s")

extern void func_81403244(s32);
void func_81403918(s32 arg0) {
    func_81403244((arg0 + 8));
}

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

extern void func_81402D08(void *arg0);
f32 func_816092FC(void);
s32 func_81403A74(void *arg0) {
    void *p = arg0;
    f32 delta;
    func_81402D08((u8 *)p + 8);
    delta = func_816092FC();
    *(f32 *)((u8 *)p + 0xCBC) += delta;
    if (*(f32 *)((u8 *)p + 0xCBC) >= 16.0f) {
        *(f32 *)((u8 *)p + 0xCBC) = 16.0f;
        *(u8 *)((u8 *)p + 0xCC0) = 2;
    }
    return 1;
}

extern void func_81402D08(void *);
s32 func_81403AE0(void *arg0) {
    func_81402D08((u8 *)arg0 + 8);
    *(f32 *)((u8 *)arg0 + 0xCBC) = 16.0f;
    return 1;
}

s32 func_81403B18(void *arg0) {
    u8 *p = (u8 *)arg0;
    func_81402D08(p + 8);
    *(f32 *)(p + 0xCBC) = *(f32 *)(p + 0xCBC) - func_816092FC();
    if (*(f32 *)(p + 0xCBC) <= 0.0f) {
        *(f32 *)(p + 0xCBC) = 0.0f;
        *(u8 *)(p + 0xCC0) = 0;
    }
    return 1;
}

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

void func_81403FDC(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    *(u8 *)((u8 *)arg0 + 0xF) = arg1;
    *(s8 *)((u8 *)arg0 + 0xE) = -1;
    *(s32 *)((u8 *)arg0 + 0x14) = arg3;
    *(u8 *)((u8 *)arg0 + 0xD) = arg2;
    *(u8 *)((u8 *)arg0 + 0xC) = 0;
    *(f32 *)((u8 *)arg0 + 4) = 0.0f;
    *(u8 *)((u8 *)arg0 + 0x11) = func_814028F0();
    *(s32 *)((u8 *)arg0 + 0) = 0;
    *(f32 *)((u8 *)arg0 + 8) = 0.0f;
}

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

extern s32 func_81403938(s32 arg0);
extern s32 func_8140463C(void *arg0, s32 arg1, s32 arg2);
extern void func_814046C4(void *arg0);
extern s32 func_81404D00(void);
s32 func_814050EC(void *arg0) {
    typedef struct {
        u8 pad0[4];
        u16 unk4;
        u8 unk6;
        u8 unk7;
        u8 pad8[8];
        s8 unk10;
        s8 unk11;
        s8 unk12;
        s8 unk13;
        s32 unk14;
        s32 unk18;
        u8 pad1c[8];
        u8 unk24[0x18];
        s32 unk3c;
    } State;
    State *state;
    s32 sp28;
    s32 sp24;
    void *temp_v0;
    s32 result;
    s32 mode;

    state = arg0;
    sp28 = func_81404D00();
    sp24 = state->unk18;
    temp_v0 = func_814049CC(state);
    if (sp28 < state->unk12) {
        state->unk6 = 2;
        func_814046C4(state->unk24);
        return 0;
    }
    if (state->unk14 != 0) {
        mode = 1;
    } else {
        mode = 0;
    }
    result = func_8140463C(state->unk24, mode, 0);
    state->unk10 = -1;
    if ((temp_v0 != NULL) && ((*(u16 *)((u8 *)temp_v0 + 6) & 0x10) != 0)) {
        state->unk18 = 1;
    } else {
        state->unk18 = 0;
    }
    if (result < 0 || result == 2) {
        func_81403938(state->unk3c);
        state->unk6 = 2;
    } else if (result == 1) {
        state->unk6 = 5;
    }
    mode = (state->unk14 == 0);
    if (mode == 0) {
        mode = (sp24 != state->unk18);
    }
    return mode;
}

extern s32 func_81403938(s32 arg0);
extern s32 func_8140463C(void *arg0, s32 arg1, s32 arg2);
extern void func_814046C4(void *arg0);
extern s32 func_81404D00(void);

s32 func_81405208(void *arg0) {
    typedef struct {
        u8 pad0[4]; u16 unk4; u8 unk6; u8 unk7; u8 pad8[8];
        s8 unk10; s8 unk11; s8 unk12; s8 unk13;
        s32 unk14; s32 unk18; u8 pad1c[8]; u8 unk24[0x18]; s32 unk3c;
    } State;
    State *state;
    s32 sp28;
    s32 sp24;
    void *temp_v0;
    s32 temp_v0_2;
    s32 var_v1;

    state = arg0;
    sp28 = func_81404D00();
    sp24 = state->unk18;
    temp_v0 = func_814049CC(state);
    if (sp28 < state->unk12) {
        state->unk6 = 2;
        func_814046C4(state->unk24);
        return 0;
    }
    if ((temp_v0 != NULL) && ((*(u16 *)((u8 *)temp_v0 + 0x6) & 0x10) != 0))
        state->unk18 = 1;
    else
        state->unk18 = 0;
    temp_v0_2 = func_8140463C(state->unk24, 2, 0);
    state->unk10 = -1;
    if (temp_v0_2 < 0) {
        func_81403938(state->unk3c);
        state->unk6 = 2;
    } else if (temp_v0_2 > 0) {
        state->unk6 = 6;
    }
    var_v1 = (state->unk14 == 0);
    if (var_v1 == 0)
        var_v1 = (sp24 != state->unk18);
    return var_v1;
}

extern s32 func_81403938(s32 arg0);
extern void func_814046C4(void *arg0);
extern s32 func_81404D00(void);
extern s32 func_8140463C(void *arg0, s32 arg1, s32 arg2);
s32 func_814052F4(void *arg0) {
    typedef struct {
        u8 pad0[4];
        u16 unk4;
        u8 unk6;
        u8 unk7;
        u8 pad8[8];
        s8 unk10;
        s8 unk11;
        s8 unk12;
        s8 unk13;
        s32 unk14;
        s32 unk18;
        u8 pad1c[8];
        u8 unk24[0x18];
        s32 unk3c;
    } State;
    State *state;
    s32 sp28;
    s32 sp24;
    void *temp_v0;
    s32 temp_v0_2;
    s32 mode;

    state = arg0;
    sp28 = func_81404D00();
    sp24 = state->unk18;
    temp_v0 = func_814049CC(state);
    if (sp28 < state->unk12) {
        state->unk6 = 2;
        func_814046C4(state->unk24);
        return 0;
    }
    if ((temp_v0 != NULL) && ((*(u16 *)((u8 *)temp_v0 + 6) & 0x10) != 0)) {
        state->unk18 = 1;
    } else {
        state->unk18 = 0;
    }
    if (state->unk14 != 0) {
        mode = 4;
    } else {
        mode = 3;
    }
    temp_v0_2 = func_8140463C(state->unk24, mode, state->unk4);
    state->unk10 = -1;
    if (temp_v0_2 != 0) {
        func_81403938(state->unk3c);
        state->unk6 = 2;
    }
    mode = (state->unk14 == 0);
    if (mode == 0) {
        mode = (sp24 != state->unk18);
    }
    return mode;
}

extern void func_81404724(void *arg0, void *arg1);
extern void func_814047C0(void *arg0, void *arg1);
extern void func_81600A34(void *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_814053E4(void *arg0, void *arg1, void *arg2) {
    s16 first[4];
    s16 second[4];

    if (*(s32 *)((u8 *)arg0 + 0x14) == 0)
        return;
    func_81404724(arg0, first);
    func_814047C0(arg0, second);
    if (*(s8 *)((u8 *)arg0 + 9) < 2)
        func_81600A34(arg1, (u8 *)arg0 + 1, arg2, first[0], first[1], first[2], first[3]);
    func_81600A34(arg1, (u8 *)arg0 + 2, arg2, second[0], second[1], second[2], second[3]);
    if (*(s8 *)((u8 *)arg0 + 9) >= 2)
        func_81600A34(arg1, (u8 *)arg0 + 1, arg2, first[0], first[1], first[2], first[3]);
}

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

extern void func_81404BEC(void *arg0);
extern void func_800226C0(s32 arg0);
void func_81406EA8(void *arg0) {
    s32 i;

    for (i = 0; i != 4; i++) {
        if (*(s32 *)((u8 *)arg0 + 0x18F48 + i * 4) != 0)
            func_81404BEC((u8 *)arg0 + i * 0x4D68 + 0x1990);
    }
    func_800226C0(0xA5);
    func_81403A18(arg0);
    func_81403A18((u8 *)arg0 + 0xCC8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81406F44.s")

extern void func_81406700(void *arg0, void *arg1);
extern void func_81403CD0(void *arg0, void *arg1);
void func_81407118(void *arg0, void *arg1) {
    s32 i;

    for (i = 0; i != 4; i++) {
        if (*(s32 *)((u8 *)arg0 + 0x18F48 + i * 4) != 0)
            func_81406700((u8 *)arg0 + i * 0x4D68 + 0x1990, arg1);
    }
    func_81403CD0(arg0, arg1);
    func_81403CD0((u8 *)arg0 + 0xCC8, arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_814071C4.s")

extern s32 func_81406A9C(u8 *arg0);
s32 func_81407258(void *arg0) {
    s32 i;
    s32 result;

    for (i = 0; i != 4; i++) {
        if (*(s32 *)((u8 *)arg0 + 0x18F48 + i * 4) != 0) {
            if (func_81406A9C((u8 *)arg0 + i * 0x4D68 + 0x1990) == 0)
                return 0;
        }
    }
    if (*(s32 *)((u8 *)arg0 + 0x18F5C) != 0)
        result = -1;
    else
        result = 1;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E7C00/func_81407310.s")
#endif
