#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_80094DE0[];
void func_8FB00020(s32 arg0, s32 arg1, s32 arg2) {
    gSPDisplayList(D_800D0510++, D_80094DE0);
    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, 0xFFC7FFC1);
    gDPFillRectangle(D_800D0510++, arg0, arg1, arg0 + arg2, arg1 + 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB000D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB001C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB002BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB005E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB009C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00C1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00E40.s")

s32 func_8FB00C1C();
s32 func_8FB00F78(void *arg0, void *arg1) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg1) + (0x44)));
    (*(u16 *)((u8 *)(arg0) + (0))) = (u16) (*(u16 *)((u8 *)(temp_v0) + (4)));
    (*(u16 *)((u8 *)(arg0) + (2))) = (u16) (*(u16 *)((u8 *)(temp_v0) + (6)));
    (*(s16 *)((u8 *)(arg0) + (4))) = (s16) ((*(u16 *)((u8 *)(temp_v0) + (0xC))) * 0x14);
    if (func_8FB00C1C() != 0) {
        (*(s16 *)((u8 *)(arg0) + (6))) = (s16) ((*(u16 *)((u8 *)(arg0) + (0xC))) * 0x14);
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00FE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB011DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01634.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01A74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01C14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01CF8.s")

extern u8 D_8FB03490[];
extern u8 D_8FB03494[];
extern void Ui_DrawGradientPanel(s32, s32, s32, s32, s32, s32);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_80049628(s32, s32, s32);
extern void func_800499EC(void);
extern void func_8FB00020(s32, s32, s32);
void func_8FB01EC4(void *arg0) {
    s32 var_s0;
    u8 *var_s1;
    struct { u16 x; u16 y; u16 w; u16 h; s16 offset; u16 count; } *state = arg0;
    Ui_DrawGradientPanel(state->x - 0xA, state->y - 0xA, state->w + 0x14, state->h + 0x14, (s32)&D_8FB03490, (s32)&D_8FB03494);
    func_800498C4();
    func_800496A4(4, 0);
    var_s0 = state->count;
    var_s1 = (u8 *)arg0 + var_s0;
    if (var_s0 >= 0) {
        do {
            func_80049628(state->x + ((state->count - var_s0) * 0x14), state->y, *(s8 *)(var_s1 + 0xC) + 0x30);
            var_s0 -= 1;
            var_s1 -= 1;
        } while (var_s0 >= 0);
    }
    func_800499EC();
    func_8FB00020(state->x + ((state->count - state->offset) * 0x14), state->y + 0x12, 0x14);
}

void func_8FB01FCC(void *arg0) {
    s8 temp_v0;
    u16 temp_v1;
    s32 var_s0;
    u8 *var_s2;
    struct { u16 x; u16 y; u16 w; u16 h; s16 offset; u16 count; } *state = arg0;
    Ui_DrawGradientPanel(state->x - 0xA, state->y - 0xA, state->w + 0x14, state->h + 0x14, (s32)&D_8FB03490, (s32)&D_8FB03494);
    func_800498C4();
    func_800496A4(4, 0);
    var_s0 = state->count;
    var_s2 = (u8 *)arg0 + var_s0;
    if (var_s0 >= 0) {
        do {
            temp_v0 = *(s8 *)(var_s2 + 0xC);
            temp_v1 = state->count;
            if (temp_v0 < 0xA) {
                func_80049628(state->x + ((temp_v1 - var_s0) * 0x14), state->y, temp_v0 + 0x30);
            } else {
                func_80049628(state->x + ((temp_v1 - var_s0) * 0x14), state->y, temp_v0 + 0x37);
            }
            var_s0 -= 1;
            var_s2 -= 1;
        } while (var_s0 >= 0);
    }
    func_800499EC();
    func_8FB00020(state->x + ((state->count - state->offset) * 0x14), state->y + 0x12, 0x14);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02108.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB021F8.s")

struct MsgState *func_8FB02418(void)
{
  s32 temp_v0;
  temp_v0 = func_8006B7FC();
  return func_800718B8(func_8006A600(temp_v0 & 0xFFFF, (temp_v0 & 0xFF) & 0xFFu, 0));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02454.s")

struct MsgState { u8 pad[0x40]; u32 flags; };
extern struct MsgState *func_8FB02418(void);
s32 func_8FB02494(void) {
    return (func_8FB02418()->flags >> 31) == 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB024BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02560.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02608.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02698.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02878.s")

extern void func_8FB024BC(void *);
extern void func_8FB02698(void *);
extern void func_8FB02878(void *);
void func_8FB029B4(void *arg0) {
    s32 temp_v0;

    temp_v0 = (*(s32 *)((u8 *)(arg0) + (0x40)));
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8FB02698(arg0);
        break;
    case 1:
        func_8FB02878(arg0);
        break;
    }
    func_8FB024BC(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02A10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB03164.s")

extern u8 D_8FB03B2C[];
extern void func_800088DC(void);
extern void GfxImage_FillCurrent(Gfx **, s32);
extern void func_800495F8(s32, s32, s32, s32);
extern void func_80008648(void);
extern void func_8FB02A10(void *, s32);
extern void func_8FB03164(void *);
void func_8FB031E0(void *arg0) {
    s32 var_s0;
    s32 var_s1;
    struct { u8 pad[0x34]; s32 index; } *state = arg0;
    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 0x89);
    func_800498C4();
    func_800496A4(0x10, 0);
    func_800495F8(0x140, 0x1E, 1, (s32)&D_8FB03B2C);
    func_800496A4(8, 0);
    var_s0 = 0;
    var_s1 = 0x1E;
    do {
        func_8FB02A10(arg0, var_s0);
        var_s0 += 1;
    } while (var_s0 != var_s1);
    func_800495F8(0x64, 0x46, 1, *(s32 *)((u8 *)arg0 + (state->index << 2)));
    func_800499EC();
    if (*(s32 *)((u8 *)arg0 + 0x40) == 1) {
        func_8FB03164(arg0);
    }
    func_80008648();
}

extern u8 D_8FB03DF8;
void func_80064D28(void);

void func_8FB032C4(s32 arg0, s32 arg1) {
    if ((*(s32 *)((u8 *)(&D_8FB03DF8) + (0x40))) != 2) {
        do {
            func_80064D28();
            func_8FB029B4(&D_8FB03DF8);
            func_8FB031E0(&D_8FB03DF8);
        } while ((*(s32 *)((u8 *)(&D_8FB03DF8) + (0x40))) != 2);
    }
}

extern void func_800060F4(s32, s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_8004C09C(s32);
extern void func_8004C4B0(s32);
extern s32 func_80047588(s32, s32);
extern void func_8FB02560(void *);
extern void func_80008514(s32);
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern s32 D_8FB03DF0;
void func_8FB03328(s32 arg0, s32 arg1) {
    s32 sp24;
    func_800060F4(0xF, 2);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(0x107);
    func_8004C4B0(6);
    func_8004C4B0(8);
    func_8004C4B0(0x41);
    func_8004C4B0(0xF);
    func_8004C4B0(0x2A);
    D_8FB03DF0 = func_80047588(0x1E, 0);
    func_8FB02560(&D_8FB03DF8);
    func_80008514(sp24);
    func_800086A4(2);
    StageFade_StartFromOpaque(0x10);
}

extern void Gfx_FreeDisplayListBuffers();
extern void func_80008574();
extern void func_80047610();
extern void func_8004C398();

void func_8FB033F0(s32 arg0, s32 arg1) {
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
}

extern void func_8FB032C4(s32, s32);
extern void func_8FB03328(s32, s32);
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
s32 fragment9_main(s32 arg0, s32 arg1) {
    main_pool_push_state(0x52504D45);
    func_8FB03328(arg0, arg1);
    func_8FB032C4(arg0, arg1);
    func_8FB033F0(arg0, arg1);
    main_pool_pop_state(0x52504D45);
    return 0;
}
#endif
