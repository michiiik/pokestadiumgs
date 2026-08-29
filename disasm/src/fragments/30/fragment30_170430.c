#include "global.h"


#ifdef VERSION_US
extern void *D_88104E90;
extern s8 D_88006868;
extern void func_88A017B4(u8, s16);
extern void func_88A01990(void);
extern void func_8005DFD4(s32, s32);
extern s32 func_8005B120(s32);
extern void GbSave_RequirePakPresent(s32);
extern void func_8005ADD8(s8);
extern void func_80052ECC(s32);
extern void func_80054E48(s32);
extern void func_881000B8(void);

s32 func_88102F60(void) {
    s32 result;

    if (*(s32 *)((u8 *)D_88104E90 + 0xCC) != 0) {
        func_88A017B4(*(u8 *)((u8 *)D_88104E90 + 0xC7), *(s16 *)((u8 *)D_88104E90 + 0x2C));
        func_88A01990();
        func_8005DFD4(D_88006868, 0);
    }
    result = func_8005B120(D_88006868);
    if (*(s32 *)((u8 *)D_88104E90 + 0xCC) == 0) {
        GbSave_RequirePakPresent(D_88006868);
    }
    if (result != 0) {
        func_8005ADD8(D_88006868);
    }
    if ((*(s32 *)((u8 *)D_88104E90 + 0xCC) != 0) &&
        (*(s16 *)((u8 *)D_88104E90 + 0x2C) == 2)) {
        func_80052ECC(3);
        func_80054E48(3);
    }
    if (result != 0) {
        func_881000B8();
    } else {
        *(s32 *)((u8 *)D_88104E90 + 0xCC) = 0;
    }
    return result;
}

extern void *D_80087200;
extern void Input_SetRepeatController(void *);
extern s32 D_880068B8;
void func_88103058(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void *D_88104E90;
extern void Util_Free(void *);
extern s32 D_880068B4;
void func_88103080(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B4 = 1;
    Util_Free(D_88104E90);
}

extern void func_88004990(s32, s32);
void func_881030BC(void) {
    func_88004990(**(u8 **)(D_88104E90), 0);
    D_880068B8 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170430/func_881030F4.s")

extern void *D_88104E90;
extern s32 D_8800687C;
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_80049064(s32, s32, s32, s32);
extern void func_800499EC(void);
extern s32 func_800472E0(s32);
extern void func_8004989C(s32);
extern s32 func_800635E0(u8);
extern void func_8004C54C(s32, s32);
extern s32 func_8004C8A0(void *, s32, s32, s32);
extern s32 func_80048E30(s32, s32, s32, void *, s32);
extern void func_88002820(s32, s32, s32, s32, s32, s32, void *);
extern void Ui_DrawAnimatedTextureMarker(s32, s16);

void func_881033FC(void) {
    typedef struct {
        u8 padC8[0xC8];
        s32 c8;
        u8 padCC[4];
        u8 d0;
    } State;
    typedef struct {
        u8 padB8[0xB8];
        s32 entries[0x10];
    } TableState;
    struct { u8 pad[8]; u8 data[0x100]; } sp38;
    s32 sp34;

    func_800498C4();
    func_800496A4(8, 1);
    if (((State *)D_88104E90)->d0 != 0) {
        func_80049064(0x13F, 0xCB, 1, func_8004C874(0x1E, 0x1B));
        func_800499EC();
        return;
    }
    if (((State *)D_88104E90)->c8 != 0) {
        sp34 = (func_800472E0(func_8004C874(0x1E, 0x14)) * 0x1A) - 6;
        func_8004989C(0x1A);
        func_8004C54C(0x2A, func_800635E0(*(u8 *)((u8 *)D_88104E90 + 0xC7)));
        func_8004C54C(0x4A, ((TableState *)D_88104E90)->entries[*(s16 *)((u8 *)D_88104E90 + 0x2C)]);
        func_80049064(0x13F, 0xD5 - (sp34 >> 1), 1,
                       func_8004C8A0(sp38.data, 0x100, 0x1E, 0x14));
        func_800499EC();
        return;
    }
    func_80048E30(D_8800687C, 0x65, 0x9D, (u8 *)D_88104E90 + 0x38, 1);
    func_88002820(0x8B, 0xC5, 0,
                   *(s32 *)((u8 *)D_88104E90 + 0xC),
                   *(u16 *)((u8 *)D_88104E90 + 0x10),
                   *(s16 *)((u8 *)D_88104E90 + 0x1A),
                   (u8 *)D_88104E90 + 0x30);
    func_800499EC();
    Ui_DrawAnimatedTextureMarker(0x65,
                   (s16)(*(s16 *)((u8 *)D_88104E90 + 0x2C) * 0x1A + 0xC5));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170430/func_881035C0.s")
#endif
