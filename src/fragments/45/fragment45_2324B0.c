#include "global.h"


#ifdef VERSION_US
typedef struct TextMode8AnswerRow {
    u8 unk_00[144];
    s16 delay_frames;
    s16 correct_chance;
} TextMode8AnswerRow;
extern u8 *D_8AB11D0C;
extern u8 D_8AB12CB0[];
extern s16 D_8AB17238;
extern s32 D_8AB12CA8;
extern u16 func_8AB023EC(u32);
extern s32 func_80001FF0(void);
void TextMode8_InitCpuAnswerSettings(void) {
    s16 lower_delay;
    s32 upper_delay;
    s32 lower_chance;
    s32 upper_chance;
    u16 delay_draw;
    s32 difficulty;
    s32 i;
    TextMode8AnswerRow *row;

    difficulty = D_8AB11D0C[2];
    if (D_8AB12CA8 != 0) {
        difficulty = 4;
    }
    switch (difficulty) {
    case 1:
        lower_delay = 7;
        upper_delay = 10;
        lower_chance = 15;
        upper_chance = 65;
        break;
    case 2:
        lower_delay = 6;
        upper_delay = 9;
        lower_chance = 25;
        upper_chance = 75;
        break;
    case 3:
        lower_delay = 5;
        upper_delay = 8;
        lower_chance = 35;
        upper_chance = 85;
        break;
    case 4:
        lower_delay = 4;
        upper_delay = 7;
        lower_chance = 45;
        upper_chance = 95;
        break;
    default:
        lower_delay = 5;
        upper_delay = 5;
        lower_chance = 50;
        upper_chance = 50;
        break;
    }
    row = (TextMode8AnswerRow *)D_8AB12CB0;
    for (i = 0; i < 4; i++) {
        delay_draw = func_8AB023EC(upper_delay - lower_delay + 1);
        row->delay_frames = (func_80001FF0() / 2) * (lower_delay + delay_draw);
        row->correct_chance = func_8AB023EC(upper_chance - lower_chance + 1) + lower_chance;
        row++;
    }
    D_8AB17238 = 0;
}

extern s16 D_8AB17238; void func_8AB0D4A4(void) { D_8AB17238 += 1; }

extern s16 D_8AB1269A;
extern u16 func_8AB023EC(u32);
extern s16 D_8AB17238;
s32 TextMode8_ChooseCpuAnswerMask(TextMode8AnswerRow *row) {
    s16 choice;

    if (D_8AB17238 < row->delay_frames) {
        return 0;
    }
    if ((s16)func_8AB023EC(100) < row->correct_chance) {
        switch (D_8AB1269A) {
        case 0:
            choice = 8;
            break;
        case 1:
            choice = 1;
            break;
        case 2:
            choice = 4;
            break;
        case 3:
            choice = 2;
            break;
        default:
            choice = 0;
            break;
        }
    } else {
        choice = (func_8AB023EC(3) + D_8AB1269A + 1) % 4;
        switch (choice) {
        case 0:
            choice = 8;
            break;
        case 1:
            choice = 1;
            break;
        case 2:
            choice = 4;
            break;
        case 3:
            choice = 2;
            break;
        default:
            choice = 0;
            break;
        }
    }
    return choice;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0D5F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0DFC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E0F4.s")

extern s32 func_8AB0E21C(s32);
s32 func_8AB0E1FC(void) {
    return func_8AB0E21C(0);
}

extern void func_8AB04AE4(void);
extern s32 StageContext_GetFadeMode(void);
extern s32 func_8AB0E4BC(s32);
s32 func_8AB0E21C(s32 arg0) {
    s32 result = 34;

    switch (arg0) {
    case 0:
        func_8AB04AE4();
        break;
    case 1:
        if (StageContext_GetFadeMode() == 0) {
            result = func_8AB0E4BC(0);
        }
        break;
    }
    return result;
}

extern s16 D_8AB1723A;
extern s32 func_8AB0E2EC(s32);
s32 func_8AB0E280(s32 arg0) {
    s16 *counter = &D_8AB1723A;

    switch (arg0) {
    case 0:
        *counter = 0;
        break;
    case 1:
        if (*counter >= 10) {
            func_8AB0E2EC(0);
        }
        *counter += 1;
        break;
    }
    return 36;
}

extern void StageFade_StartFromTransparent(s32 arg0);
extern s32 StageContext_GetFadeMode(void);
s32 func_8AB0E2EC(s32 arg0) {
    s32 result = 0x23;
    switch (arg0) {
    case 0:
        StageFade_StartFromTransparent(5);
        break;
    case 1:
        if (StageContext_GetFadeMode() == 1) {
            result = 0;
        }
        break;
    }
    return result;
}

extern s16 D_8AB1723C;
extern u8 *D_8AB11D0C;
extern void *D_8AB11D00;
extern u8 D_8AB126A8[], D_8AB127A8[], D_8AB12668[], D_8AB17110[];
extern u8 *D_8AB12688;
extern u16 D_8AB1268E;
extern s32 D_8AB12CBC, D_8AB12D50, D_8AB12DE4, D_8AB12E78;
extern s32 func_8004C54C(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void *func_8004C8A0(void *, s32, s32, s32);
extern void func_8AB00B98(u8 *, u32);
extern void func_8AB004E0(void);
extern void func_8AC063AC(void *, u16);
extern s32 func_8AB0E4BC(s32);
s32 TextMode8_HandlePromptState(s32 phase) {
    s16 *counter = &D_8AB1723C;
    s32 result = 0x25;

    switch (phase) {
    case 0:
        *counter = 0;
        func_8004C54C(15, func_8004C874(0x39, (s8)D_8AB11D0C[0x14] + 0x269));
        func_8004C8A0(D_8AB126A8, 0x100, 0x39, 0x172);
        ((u16 *)D_8AB11D00)[1] |= 1;
        func_8004C8A0(D_8AB127A8, 0x100, 0x39, 5);
        ((u16 *)((void **)D_8AB12668)[0])[1] |= 1;
        func_8AB00B98(((u8 **)D_8AB12668)[0], -1);
        D_8AB12CBC = 0;
        D_8AB12D50 = 0;
        D_8AB12DE4 = 0;
        D_8AB12E78 = 0;
        func_8AB004E0();
        break;
    case 1:
        func_8AC063AC(D_8AB17110, D_8AB1268E);
        if (*counter >= 31) {
            ((u16 *)((void **)D_8AB12668)[0])[1] &= ~1;
            result = func_8AB0E4BC(0);
            ((u16 *)D_8AB12688)[1] &= ~1;
        }
        *counter += 1;
        break;
    }
    return result;
}

extern void *func_8004C8A0(void *, s32, s32, s32);
extern void func_80021ED8(s32);
extern void func_8003C6B8(s32);
extern s32 func_8004C54C(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_800225C4(s32);
extern void func_87F005F0(f32, f32);
extern void func_87F006BC(void);
extern u32 func_87F006AC(void);
extern void func_8AB00BA4();
extern s32 func_8AB0E684(s32);
extern void *D_8AB11D00;
extern u8 *D_8AB11D0C;
extern u8 D_8AB126A8[];
extern s16 D_8AB17188;
extern void *D_8AB17220;
extern s32 D_8AB17234;

s32 func_8AB0E4BC(s32 arg0) {
    s32 sp1C;

    sp1C = 0x26;
    switch (arg0) {
    case 0:
        func_87F005F0((f32) (*(s16 *)((u8 *)D_8AB17220 + 8) - 0x140), (f32) (0xF0 - *(s16 *)((u8 *)D_8AB17220 + 0xA)));
        func_8004C8A0(D_8AB126A8, 0x100, 0x3A, 0x183);
        D_8AB17188 = 3;
        func_800225C4(0x5A);
        func_8004C54C(0xF, func_8004C874(0x39, *(s8 *)(D_8AB11D0C + 0x14) + 0x269));
        func_8004C8A0(D_8AB126A8, 0x100, 0x39, 0x172);
        *(u16 *)((u8 *)D_8AB11D00 + 2) = (u16)(*(u16 *)((u8 *)D_8AB11D00 + 2) | 1);
        break;
    case 1:
        func_87F006BC();
        switch ((s16) func_87F006AC()) {
        case 1:
            func_8AB00BA4(0x64, D_8AB17188, 0);
            D_8AB17188 -= 1;
            break;
        case 2:
            func_80021ED8(0x4C);
            func_8AB00BA4(0x64, D_8AB17188, 0);
            D_8AB17188 -= 1;
            break;
        case 3:
            *(u16 *)((u8 *)D_8AB11D00 + 2) = (u16)(*(u16 *)((u8 *)D_8AB11D00 + 2) & 0xFFFE);
            sp1C = func_8AB0E684(0);
            break;
        }
        break;
    case 2:
        func_8003C6B8(D_8AB17234);
        break;
    }
    return sp1C;
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E684.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E8B4.s")

void func_8AB0E9D8(u8 *arg0) {
    *(s32 *)(arg0 + 0xC) = 1;
    *(s16 *)(arg0 + 0x10) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E9E8.s")

extern u8 D_8AB12CB0[];
extern u8 *D_8AB11D0C;
extern s16 D_8AB1721C;
extern s32 func_8AB0F518(s32 arg0);
s32 func_8AB0EED8(s32 arg0) {
    s32 result = arg0;
    s32 i = 0;
    u8 *ptr = D_8AB12CB0;
    for (i = 0; i < 4; i++, ptr += 0x94) {
        if (*(s16 *)(ptr + 2) == 1) {
            D_8AB1721C = i;
            D_8AB11D0C[0xF] = i;
            result = func_8AB0F518(0);
            break;
        }
    }
    return result;
}

extern s16 D_8AB1722C;
extern s16 D_8AB1722E;
extern s16 D_8AB17230;
extern s16 D_8AB12694;
extern s32 D_8AB112C0;
extern s32 D_8AB17224;
extern u8 D_8AB16FD0[];
extern void *D_8AB16FC8;
extern void func_8AB03394(void);
extern void TextChoice_ShuffleAndRefresh(void);
extern void TextMode8_InitCpuAnswerSettings(void);
extern void _bzero(void *, s32);
extern void TextPanels_UpdateVisibility(void);
extern s32 func_8004C594(s32, s32);
extern void func_8AB0E9E8(void);
extern s32 func_8AB0E8B4(void);
extern s32 func_8AB0F0A8(s32);
extern s32 TextMode8_HandleRowCleanupState(s32);
s32 func_8AB0EF44(s32 arg0) {
    s32 result = 40;

    switch (arg0) {
    case 0:
        func_8AB03394();
        TextChoice_ShuffleAndRefresh();
        TextMode8_InitCpuAnswerSettings();
        D_8AB1722C = 1;
        D_8AB1722E = 0;
        _bzero(D_8AB16FD0, 256);
        *(u16 *)((u8 *)D_8AB16FC8 + 2) |= 1;
        *(u16 *)((u8 *)D_8AB11D00 + 2) &= ~1;
        TextPanels_UpdateVisibility();
        func_8004C594(2, D_8AB12694 + 1);
        D_8AB112C0 = 0;
        D_8AB17224 = 0;
        func_8AB004E0();
        break;
    case 1:
        func_8AB0E9E8();
        func_8AB0E8B4();
        if (D_8AB1722E == 1) {
            result = func_8AB0F0A8(0);
        }
        if (D_8AB17230 == 1) {
            result = TextMode8_HandleRowCleanupState(0);
            if (D_8AB1722E == 0) {
                func_8004C8A0(D_8AB16FD0, 256,
                              *(u16 *)((u8 *)D_8AB11D00 + 48),
                              *(u16 *)((u8 *)D_8AB11D00 + 50));
            }
        }
        result = func_8AB0EED8(result);
        break;
    case 2:
        break;
    }
    return result;
}

/* mkdraft:func_8AB0F0A8 begin */
extern s16 D_8AB1269C;
extern s16 D_8AB17230;
extern s16 D_8AB17232;
extern s32 D_8AB17240;
extern void func_8AB01728(void);
extern void func_8AB0E9E8(void);
extern s32 func_80001FF0(void);
extern void func_8AB00BA4();
extern s32 TextMode8_HandleRowCleanupState(s32);

s32 func_8AB0F0A8(s32 arg0) {
    s16 n;
    s32 result;
    result = 0x29;
    switch (arg0) {
    case 0:
        D_8AB1269C = 0x14;
        D_8AB17240 = 0;
        break;
    case 1:
        func_8AB01728();
        func_8AB0E9E8();
        if (D_8AB17240 % (func_80001FF0() / 4) == 0) {
            D_8AB1269C--;
            if (D_8AB1269C < 0) {
                D_8AB1269C = 0;
                if (D_8AB17230 == 0) {
                    func_8AB00BA4(0x65, 0, 0);
                }
                D_8AB17230 = 1;
            }
        }
        if (D_8AB17240 % ((func_80001FF0() / 4) * 2) == 0) {
            n = D_8AB1269C / 2 + 1;
            if (D_8AB17230 == 0) {
                func_8AB00BA4(0x65, n, 0);
            }
        }
        if (D_8AB17232 == 0 || D_8AB17230 == 1) {
            result = TextMode8_HandleRowCleanupState(0);
        }
        result = func_8AB0EED8(result);
        D_8AB17240++;
        break;
    case 2:
        break;
    }
    return result;
}
/* mkdraft:func_8AB0F0A8 end */

extern u8 *D_8AB17190[];
void func_8AB0F29C(u8 *arg0, s32 arg1) {
    if (*(s32 *)(arg0 + 0xC) == 1) {
        *(s16 *)(arg0 + 0x10) -= 1;
        if (*(s16 *)(arg0 + 0x10) > 0) {
            return;
        }
        *(s16 *)(arg0 + 0x10) = 0;
        *(s32 *)(arg0 + 0xC) = 0;
        *(u16 *)(D_8AB17190[arg1] + 2) &= 0xFFFD;
    }
}

extern s16 D_8AB17244;
extern u8 D_8AB12CB0[];
extern s32 D_8AB17224;
extern void func_8AB0F29C(u8 *, s32);
extern void TextHighlight_AnimateScales(void);
extern s32 func_80001FF0(void);
extern void func_8AB00BA4(s32, s32, s32);
extern s32 func_8AB0F484(s32);
s32 TextMode8_HandleRowCleanupState(s32 phase) {
    s32 result = 42;
    s16 *counter = &D_8AB17244;
    s32 i;
    s32 all_wrong;
    u8 *row;

    switch (phase) {
    case 0:
        *counter = 0;
        all_wrong = 1;
        for (i = 0; i < 4; i++) {
            row = D_8AB12CB0 + i * 148;
            if (*(s16 *)row != 0 && *(s16 *)(row + 4) != 2) {
                all_wrong = 0;
            }
        }
        if (all_wrong) {
            for (i = 0; i < 4; i++) {
                row = D_8AB12CB0 + i * 148;
                func_8AB0F29C(row, i);
            }
            D_8AB17224 = 1;
        } else {
            for (i = 0; i < 4; i++) {
                row = D_8AB12CB0 + i * 148;
                if (*(s16 *)row != 0 && *(s16 *)(row + 4) == 0) {
                    func_8AB0F29C(row, i);
                }
            }
        }
        break;
    case 1:
        *counter += 1;
        TextHighlight_AnimateScales();
        if (*counter == func_80001FF0() / 4) {
            func_8AB00BA4(102, 0, 0);
        }
        if (*counter >= 31) {
            result = func_8AB0F484(0);
        }
        break;
    case 2:
        break;
    }
    return result;
}

extern void func_8AB01FBC(void);
extern void func_8AB03ED4(void);
extern void func_8AB012A4(void);
extern s32 func_8AB0E684(s32);
extern s16 D_8AB17246;
s32 func_8AB0F484(s32 arg0) {
    s32 result = 0x2B;
    s16 *counter = &D_8AB17246;
    switch (arg0) {
    case 0:
        *counter = 0;
        func_8AB01FBC();
        break;
    case 1:
        *counter += 1;
        func_8AB03ED4();
        if (*counter >= 0xB) {
            func_8AB012A4();
            result = func_8AB0E684(0);
        }
        break;
    }
    return result;
}

extern s16 D_8AB17248;
extern void *D_8AB16FC8;
extern void func_8AB00BA4(s32, s32, s32);
extern void Audio_PlayDefaultSound(u16);
extern void TextHighlight_AnimateScales(void);
extern s32 func_8AB0F5F8(s32);
s32 func_8AB0F518(s32 arg0) {
    s16 *counter = &D_8AB17248;
    s32 result = 44;

    switch (arg0) {
    case 0:
        *counter = 0;
        *(u16 *)((u8 *)D_8AB11D00 + 2) |= 1;
        func_8004C8A0(D_8AB126A8, 256, 57, 389);
        *(u16 *)((u8 *)D_8AB16FC8 + 2) &= ~1;
        func_8AB00BA4(102, 0, 0);
        func_800225C4(40);
        Audio_PlayDefaultSound(52998);
        break;
    case 1:
        *counter += 1;
        TextHighlight_AnimateScales();
        if (*counter >= 61) {
            result = func_8AB0F5F8(0);
        }
        break;
    }
    return result;
}

extern s16 D_8AB126A0;
extern void *D_8AB16FC8;
extern s16 D_8AB1724A;
extern void func_800226C0(s32);
extern void func_80027774(u16, u8);
extern void func_8AB00618(void);
extern void func_8AB007E0(void);

s32 func_8AB0F5F8(s32 arg0) {
    s32 sp1C;
    s16 *counter = &D_8AB1724A;

    sp1C = 0x2D;
    switch (arg0) {
    case 0:
        *counter = 0;
        *(u16 *)((u8 *)D_8AB16FC8 + 2) = (u16) (*(u16 *)((u8 *)D_8AB16FC8 + 2) & 0xFFFE);
        func_8004C54C(0xF, func_8004C874(0x39, *(s8 *)(D_8AB11D0C + 0x14) + 0x269));
        if (*(s16 *)(D_8AB12CB0 + D_8AB1721C * 0x94) == 2) {
            func_8004C8A0(D_8AB126A8, 0x100, 0x39, D_8AB1721C + 0x228);
        } else {
            func_8004C8A0(D_8AB126A8, 0x100, 0x39, D_8AB1721C + 0x224);
        }
        *(u16 *)((u8 *)D_8AB11D00 + 2) = (u16) (*(u16 *)((u8 *)D_8AB11D00 + 2) | 1);
        func_80021ED8(0x37);
        func_80027774(0xCA0F, 0x24);
        func_8AB007E0();
        D_8AB126A0 = 0;
        break;
    case 1:
        *counter += 1;
        func_8AB03ED4();
        func_8AB00618();
        if (*counter >= 0x79) {
            func_800226C0(3);
            sp1C = func_8AB0E2EC(0);
        }
        break;
    }
    return sp1C;
}
#endif
