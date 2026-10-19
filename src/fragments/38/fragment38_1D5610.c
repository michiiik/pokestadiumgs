#include "global.h"

#ifdef VERSION_US
extern u8 *D_88904190;
u8 *fragment38_main(void) {
    return D_88904190 + 0x6C;
}

typedef struct ModelPreviewState ModelPreviewState;
extern s32 main_pool_push_state(s32);
extern void *Util_Malloc(s32);
extern s32 func_8004C4B0(s32);
extern s32 func_8004C8C0(s32);
extern void func_88004FF0(s32);
extern void *D_80128C64;
extern ModelPreviewState *ModelPreview_Create(void *,s32,s32);
extern s32 func_80042D74(u8 *,s32);
extern void func_88005714(void *);
extern s32 func_80001FF0(void);

void LabPC_InitEvolutionView(void) {
    main_pool_push_state(0x45564F56);
    D_88904190 = Util_Malloc(348);
    func_8004C4B0(69);
    func_8004C8C0(53);
    func_88004FF0(58);
    *(s16 *)(D_88904190 + 336) = (s16)(u32)(((f32)func_80001FF0() * 20.0f) / 2);
    *(s16 *)(D_88904190 + 338) = (s16)(u32)(((f32)func_80001FF0() * 2.0f) / 2);
    *(s16 *)(D_88904190 + 340) = (s16)(u32)(((f32)func_80001FF0() * 10.0f) / 2);
    *(s16 *)(D_88904190 + 342) = (s16)(u32)(((f32)func_80001FF0() * 2.0f) / 2);
    *(s16 *)(D_88904190 + 344) = (s16)(u32)(((f32)func_80001FF0() * 2.0f) / 2);
    *(s16 *)(D_88904190 + 346) = (s32)((245760.0f / (f32)func_80001FF0()) + (0.0f < 245760.0f / (f32)func_80001FF0() ? 0.5f : -0.5f));
    *(ModelPreviewState **)(D_88904190 + 96) = ModelPreview_Create(D_80128C64, 208, 141);
    *(u16 *)*(u8 **)(D_88904190 + 96) &= 0xFFFD;
    func_80042D74(*(u8 **)(D_88904190 + 96), (s32)func_88005714);
}

extern void Util_Free(void *arg0);
extern void main_pool_pop_state(s32 arg0);
void func_88900494(void) {
    Util_Free(D_88904190);
    main_pool_pop_state(0x45564F56);
}

extern s32 func_880007B0(s32);
s32 func_889004C4(void) {
    s32 result;
    s32 zero;

    result = 0;
    if (*(s32 *)(D_88904190 + 0x11C) != 0) {
        zero = 0;
        result = zero;
        if (func_880007B0(*(s32 *)(D_88904190 + 0x68)) != 0) {
            if (*(u8 *)(D_88904190 + 0x13C) >= 0xA6) {
                result = 1;
            }
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900528.s")

void func_8890055C(void) {
    *(s32 *)(D_88904190 + 0x120) = 0;
    *(s32 *)(D_88904190 + 0x124) = 1;
    *(s16 *)(D_88904190 + 0x13E) = (s16)(u32)((f32)func_80001FF0() / 2);
}

extern s32 func_88902B70(u8 *);
extern s32 func_889004C4(void);

void func_88900638(void) {
    *(s32 *)(D_88904190 + 0x120) = 0;
    if ((func_88902B70(*(u8 **)(D_88904190 + 0x68)) != 4) &&
        (func_889004C4() == 0)) {
        *(s32 *)(D_88904190 + 0x124) = 6;
    } else {
        *(s32 *)(D_88904190 + 0x124) = 7;
    }
    *(s16 *)(D_88904190 + 0x13E) =
        (s16)(u32)((f32)func_80001FF0() / 2);
}

void func_88900754(void) {
    u8 *ptr = D_88904190;
    if (*(u32 *)(ptr + 0x44) != 0) {
        *(s32 *)(*(u8 **)(ptr + 0x48) + 0x2C) = 1;
    }
}

extern void Input_SetRepeatController(void *arg0);
extern void *D_80087200;
void func_8890077C(void) {
    Input_SetRepeatController(D_80087200);
}

typedef struct LabPCTextMask {
    s32 enabled;
    u8 *flags;
} LabPCTextMask;
typedef struct LabPCTextList {
    s16 x, y;
    s32 align;
    u8 **strings;
    u16 count, width;
    s32 font;
    s16 spacing_x, spacing_y, left, right, top, bottom;
    s32 constrain;
    s32 active;
    s16 selected;
    LabPCTextMask mask;
} LabPCTextList;
extern void func_88900DB4(void);

extern void func_800226C0(s32);
extern void func_88002720(s16 *,u16,void *);
extern void func_88004990(u8, s32);

extern void LabPC_OpenChoiceWindow(s32 mode);

extern s8 D_8800EF18;

void LabPC_HandleChoiceInput(void) {
    LabPCTextList *list = (LabPCTextList *)(D_88904190 + 8);
    s32 special_sound;

    if (((*(u16 *)((u8 *)D_80087200 + 8)) & 0x8000) && list->selected == 0) {
        special_sound = 0;
        switch (*(s32 *)(D_88904190 + 288)) {
        case 9:
            if (func_889004C4() != 0) {
                *(s32 *)(D_88904190 + 292) = 12;
                *(s32 *)(*(u8 **)(D_88904190 + 4) + 32) = 0;
                LabPC_OpenChoiceWindow(0);
            } else {
                *(s32 *)(D_88904190 + 292) = 13;
                func_88004990((*(u8 **)(D_88904190 + 4))[0], 0);
                func_88900DB4();
            }
            break;
        case 11:
            special_sound = 1;
            *(s32 *)(D_88904190 + 292) = 10;
            func_88004990((*(u8 **)(D_88904190 + 4))[0], 0);
            break;
        case 12:
            if (func_88902B70(*(u8 **)(D_88904190 + 104)) == 4) {
                *(s32 *)(D_88904190 + 292) = 13;
                func_88004990((*(u8 **)(D_88904190 + 4))[0], 0);
                func_88900DB4();
            } else {
                *(s32 *)(D_88904190 + 292) = 6;
                func_88004990((*(u8 **)(D_88904190 + 4))[0], 0);
            }
            break;
        case 14:
            *(s32 *)(D_88904190 + 292) = 6;
            func_88004990((*(u8 **)(D_88904190 + 4))[0], 0);
            func_88004990((*(u8 **)(D_88904190 + 72))[0], 0);
            break;
        }
        *(s32 *)(D_88904190 + 288) = 0;
        *(s16 *)(D_88904190 + 318) = D_8800EF18;
        if (special_sound != 0) {
            func_800226C0(334);
        } else {
            func_800226C0(*(s32 *)(D_88904190 + 328));
        }
    } else if ((*(u16 *)((u8 *)D_80087200 + 8)) & 0xC000) {
        func_800226C0(*(s32 *)(D_88904190 + 332));
        switch (*(s32 *)(D_88904190 + 288)) {
        case 9:
            *(s32 *)(D_88904190 + 292) = 11;
            *(s32 *)(*(u8 **)(D_88904190 + 4) + 32) = 0;
            LabPC_OpenChoiceWindow(0);
            break;
        case 11:
            *(s32 *)(D_88904190 + 292) = 7;
            func_88004990((*(u8 **)(D_88904190 + 4))[0], 0);
            break;
        case 12:
            if (func_88902B70(*(u8 **)(D_88904190 + 104)) == 4) {
                *(s32 *)(D_88904190 + 292) = 11;
                *(s32 *)(*(u8 **)(D_88904190 + 4) + 32) = 0;
                LabPC_OpenChoiceWindow(0);
            } else {
                *(s32 *)(D_88904190 + 292) = 10;
                func_88004990((*(u8 **)(D_88904190 + 4))[0], 0);
            }
            break;
        case 14:
            *(s32 *)(D_88904190 + 292) = 13;
            func_88004990((*(u8 **)(D_88904190 + 4))[0], 0);
            *(s32 *)(D_88904190 + 68) = 1;
            break;
        }
        *(s32 *)(D_88904190 + 288) = 0;
        *(s16 *)(D_88904190 + 318) = D_8800EF18;
    } else {
        func_88002720(&list->selected, list->count, &list->mask);
    }
}

extern void func_889033FC(void *arg0, void *arg1);
void func_88900ADC(void) {
    func_889033FC(*(void **)(D_88904190 + 4), D_88904190 + 8);
}

typedef struct LabPCChoiceDialog LabPCChoiceDialog;
extern void func_889034DC(LabPCChoiceDialog *);
extern void LabPC_HandleChoiceInput(void);
extern u8 func_88004804(s32,s32,s16,s16,s32,s32,u8,u8,u8,
                         s32 *,s32 *,s32 *,s32 *,u8,u8);
extern void func_88900754(void);
extern void func_8890077C(void);
extern void func_88900ADC(void);
extern u8 D_8800ED50[];

void LabPC_OpenChoiceWindow(s32 mode) {
    u8 slot;
    s16 x;
    s16 y;
    s32 style;

    switch (mode) {
    case 0:
        x = *(s8 *)(D_88904190 + 301) + 528;
        y = *(s8 *)(D_88904190 + 302) + 442;
        style = 8;
        break;
    case 1:
        x = *(s8 *)(D_88904190 + 301) + 528;
        y = *(s8 *)(D_88904190 + 302) + 345;
        style = 2;
        break;
    }
    func_889034DC((LabPCChoiceDialog *)(D_88904190 + 4));
    slot = func_88004804(
        (s32)(D_88904190 + 8), 0, x, y, style, 1,
        *(u8 *)(D_88904190 + 297), *(u8 *)(D_88904190 + 298), *(u8 *)(D_88904190 + 299),
        (s32 *)LabPC_HandleChoiceInput, (s32 *)func_88900ADC, (s32 *)func_8890077C, (s32 *)func_88900754, 1, 2);
    *(u8 **)(D_88904190 + 4) = D_8800ED50 + slot * 76;
    *(u8 *)(D_88904190 + 300) = 3;
}

void func_88900C54(void) {
    Input_SetRepeatController(D_80087200);
}

typedef struct LabPCControllerMovePane {
    u8 *window;
    s16 x, y;
    u8 *pokemon;
    s16 selected;
    u8 count, unk_0F;
    s32 state;
} LabPCControllerMovePane;
extern u8 D_889041A0;

extern u8 D_88006020[];
extern void LabPC_OpenChoiceWindow(s32);

void LabPC_HandleMovePaneInput(void) {
    LabPCControllerMovePane *pane = (LabPCControllerMovePane *)(D_88904190 + 72);
    u32 pressed = *(u16 *)((u8 *)D_80087200 + 8);

    if (pressed & 0x8000) {
        func_800226C0(*(s32 *)(D_88904190 + 328));
        *(s32 *)(pane->window + 44) = 0;
        D_889041A0 = pane->selected;
        *(s32 *)(D_88904190 + 288) = 0;
        *(s32 *)(D_88904190 + 292) = 14;
        *(s16 *)(D_88904190 + 318) = D_8800EF18;
        LabPC_OpenChoiceWindow(1);
    } else if (pressed & 0x4000) {
        func_800226C0(*(s32 *)(D_88904190 + 332));
        func_88004990(pane->window[0], 0);
        *(s32 *)(D_88904190 + 288) = 0;
        *(s32 *)(D_88904190 + 292) = 11;
        *(s16 *)(D_88904190 + 318) = D_8800EF18;
        LabPC_OpenChoiceWindow(0);
    } else {
        func_88002720(&pane->selected, pane->count, D_88006020);
    }
}

extern void func_889035FC(void *arg0);
void func_88900D8C(void) {
    func_889035FC(D_88904190 + 0x48);
}

extern void func_889035A0(void *, u8 *, s16, s16);

extern void LabPC_HandleMovePaneInput(void);
extern void func_88900D8C(void);
extern void func_88900C54(void);
extern u8 D_88000E4C;

void func_88900DB4(void) {
    s32 result;

    func_889035A0(D_88904190 + 0x48, *(u8 **)(D_88904190 + 0x68),
                  *(s8 *)(D_88904190 + 0x12D), *(s8 *)(D_88904190 + 0x12E));
    result = func_88004804(
        0, 3,
        (s16)(*(s8 *)(D_88904190 + 0x12D) + 0x153),
        (s16)(*(s8 *)(D_88904190 + 0x12E) + 0x98),
        0, 1,
        *(u8 *)(D_88904190 + 0x129),
        *(u8 *)(D_88904190 + 0x12A),
        *(u8 *)(D_88904190 + 0x12B),
        (s32 *)LabPC_HandleMovePaneInput, (s32 *)func_88900D8C, (s32 *)func_88900C54, (s32 *)&D_88000E4C, 1, 1);
    *(u8 **)(D_88904190 + 0x48) = D_8800ED50 + result * 0x4C;
    *(s16 *)(*(u8 **)(D_88904190 + 0x48) + 0x10) = 0xBE;
    *(s16 *)(*(u8 **)(D_88904190 + 0x48) + 0x12) = 0xC5;
    *(u8 *)(D_88904190 + 0x12C) = 3;
}

extern void func_8002602C(void);

void func_88900EE4(void) {
    func_800226C0(*(s32 *)(D_88904190 + 0x148));
    func_8002602C();
    func_88004990(*(u8 *)(*(u8 **)(D_88904190 + 0x0)), 0);
    *(s32 *)(*(u8 **)(D_88904190 + 0x0) + 0x34) = 1;
    ((void (*)(void))(u32)*(u32 *)(D_88904190 + 0x130))();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900F54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88901A24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88902624.s")

typedef struct { u8 r, g, b, a; } LabPCControllerColor;
extern LabPCControllerColor *Color_SetRGB(LabPCControllerColor *, u8, u8, u8);
extern void func_80042F94(void *, void *);
extern void Audio_InitializeBufferMemory(void *);
extern u8 D_880068C0[];
extern s8 *HAL_Strcpy(s8 *, s8 *);
extern s32 func_8005DC48(s32, s32);
extern void func_88902624(s32, u8 *, s8);
extern void func_88900F54(void);
extern void func_88901A24(void);
extern s32 func_88902E4C(u32 *, u8 *, s8);
extern char *LabPC_FormatColoredMoveName(char *, u8);
extern void func_88005048(void);

u8 LabPC_OpenEvolutionView(s32 kind, u8 *pokemon, s8 slot, s32 context,
                         s32 *cb2, s32 *cb3, void (*done)(void), u8 delay) {
    func_80042F94(*(void **)(D_88904190 + 96), pokemon);
    Audio_InitializeBufferMemory(D_880068C0);
    if (kind == 0) {
        *(s8 *)(D_88904190 + 301) = -26;
        *(s8 *)(D_88904190 + 302) = -57;
        Color_SetRGB((LabPCControllerColor *)(D_88904190 + 297), 230, 255, 240);
        *(s32 *)(D_88904190 + 328) = 2;
        *(s32 *)(D_88904190 + 332) = 3;
    } else {
        *(s8 *)(D_88904190 + 301) = 8;
        *(s8 *)(D_88904190 + 302) = 0;
        Color_SetRGB((LabPCControllerColor *)(D_88904190 + 297), 220, 220, 180);
        *(s32 *)(D_88904190 + 328) = 71;
        *(s32 *)(D_88904190 + 332) = 72;
    }
    *(u8 **)(D_88904190 + 0) = D_8800ED50 + func_88004804(
        0, 3, (s16)(*(s8 *)(D_88904190 + 301) + 159),
        (s16)(*(s8 *)(D_88904190 + 302) + 146), 0, 2,
        *(u8 *)(D_88904190 + 297), *(u8 *)(D_88904190 + 298), *(u8 *)(D_88904190 + 299),
        (s32 *)func_88900F54, (s32 *)func_88901A24, cb2, cb3, delay, 0) * 76;
    *(s16 *)(*(u8 **)(D_88904190 + 0) + 16) = 376;
    *(s16 *)(*(u8 **)(D_88904190 + 0) + 18) = 303;
    *(s32 *)(D_88904190 + 92) = kind;
    *(u8 **)(D_88904190 + 104) = pokemon;
    *(s8 *)(D_88904190 + 282) = slot;
    *(s32 *)(D_88904190 + 284) = context;
    *(void (**)(void))(D_88904190 + 304) = done;
    HAL_Strcpy((s8 *)(D_88904190 + 108), (s8 *)(pokemon + 52));
    func_8005DC48(slot, (s32)(D_88904190 + 140));
    func_88902624(kind, pokemon, slot);
    *(u8 *)(D_88904190 + 300) = 3;
    *(u8 *)(D_88904190 + 296) = 0;
    if (kind == 1) {
        *(u8 *)(D_88904190 + 296) |= 1;
        *(u8 *)(D_88904190 + 316) = func_88902E4C((u32 *)(D_88904190 + 312), pokemon, slot);
    }
    if (kind == 1 && *(u8 *)(D_88904190 + 316) != 0) {
        LabPC_FormatColoredMoveName((char *)(D_88904190 + 154), *(u8 *)(D_88904190 + 316));
        func_88900638();
    } else if (kind == 0 && *(u8 *)(D_88904190 + 308) == 0) {
        *(s32 *)(D_88904190 + 288) = 0;
        *(s32 *)(D_88904190 + 292) = 5;
        *(s16 *)(D_88904190 + 318) = (s16)(u32)((f32)func_80001FF0() / 2);
    } else {
        func_8890055C();
    }
    *(u8 *)(D_88904190 + 317) = 0;
    *(u8 *)(D_88904190 + 320) = 1;
    *(s16 *)(D_88904190 + 322) = 0;
    *(s16 *)(D_88904190 + 324) = 0;
    *(s16 *)(D_88904190 + 326) = 0;
    func_88005048();
    return *(u8 *)(D_88904190 + 308);
}
#endif
