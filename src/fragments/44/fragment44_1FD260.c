#include "global.h"


#ifdef VERSION_US
extern void Ui_DrawGradientQuad(s32, s32, u16, u16, s32 *, s32 *);
extern u8 D_8AF26450;
extern u8 D_8AF26454;
s32 func_8AF0EFF0(void *arg0) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0x18)));
    Ui_DrawGradientQuad(0, 0, (*(u16 *)((u8 *)(temp_v0) + (4))), (*(u16 *)((u8 *)(temp_v0) + (6))), &D_8AF26450, &D_8AF26454);
    return 0;
}

extern s32 func_8004C594(s32, s32);
extern u8 func_8006397C(u8);
extern u8 func_800639C0(u8);
extern void *func_8004C874(s32, s32);
extern s32 func_8004C54C(s32, s32);
extern s16 func_8AF01530(s16);
extern s16 D_8AF263C4[];
extern char *D_8AF26A30;
extern char D_8AF294E0[];

s32 func_8AF0F040(s32 mode, void *record) {
    s16 index;
    u8 first;
    u8 second;
    char *first_name;
    s32 lookup;

    index = *(s16 *)((u8 *)record + 0x22);
    if (mode != 0 && mode == 1) {
        func_8004C594(3, index);
        lookup = index - 1;
        func_8004C54C(0x2C, (s32)func_8004C874(2, lookup));
        func_8004C54C(0x2D, (s32)func_8004C874(3, lookup));
        func_8004C54C(0x2E, (s32)func_8004C874(1, lookup));
        first = func_8AF01530(func_8006397C(index));
        second = func_8AF01530(func_800639C0(index));
        if (first == second) {
            func_8004C54C(0x2F, (s32)func_8004C874(0xC, D_8AF263C4[first]));
        } else {
            first_name = func_8004C874(0xC, D_8AF263C4[first]);
            sprintf(D_8AF26A30, D_8AF294E0, first_name, func_8004C874(0xC, D_8AF263C4[second]));
            func_8004C54C(0x2F, (s32)D_8AF26A30);
        }
    }
    return 0;
}

extern void func_800504BC(s16 *);
extern s16 D_8AF2F9E0[][3];

void func_8AF0F1A0(s32 mode, void *record) {
    s16 index;
    s16 values[2];
    s16 *entry;

    index = *(s16 *)((u8 *)record + 0x22);
    if (mode != 0 && mode == 1) {
        func_800504BC(values);
        entry = D_8AF2F9E0[index];
        entry[0] = index + 1;
        entry[1] = *(s16 *)((u8 *)record + 8) + values[0];
        entry[2] = *(s16 *)((u8 *)record + 0xA) + values[1];
    }
}

extern s32 func_80063BB8(u8);
extern s16 D_8AF2F9DE;
extern s16 D_8AF2F9D0[];
extern u8 D_8AF2FA70[][3];
extern u8 D_8AF31D42;
extern u8 func_80062D98(u8);
extern u8 *func_8AF12410(u8 *, s16);

void func_8AF0F220(u8 code) {
    struct EvolutionEntry {
        u8 method;
        u8 requirement;
        u8 species;
    };
    u8 *entry;
    u8 *copy;
    s16 index;

    entry = (u8 *)func_80063BB8(code);
    if (entry != NULL) {
        for (;;) {
            if (entry[0] == 0) {
                break;
            }
            D_8AF2F9DE++;
            index = D_8AF2F9DE;
            D_8AF2F9D0[index] = entry[2];
            copy = D_8AF2FA70[index];
            *(struct EvolutionEntry *)copy = *(struct EvolutionEntry *)entry;
            func_8AF0F220(entry[2]);
            entry += 3;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF0F2EC.s")

extern void func_8AC007FC(void);
extern s32 func_80044144(s32);
extern void func_8AF00130(s32);
extern void func_8AC06D70(void *, u32, u32, s32);
extern void *D_8AF263C0;
extern void *D_8AF2FA8C;
extern void *D_8AF2FA90;
extern u8 D_8AF2FA98[];
extern u8 D_8AF2FAC8[];
extern u8 D_8AF2FAF8[];
extern u8 D_8AF2FB28[];
extern u8 D_8AF2FB88[];
extern u8 D_8AF2FB58[];
extern u8 D_8AF2FBB8[];
extern u8 D_8AF2FBE8[];
extern s16 D_8AF2F9CC;
extern u16 D_8AF2F9CE;
extern s32 D_8AF26A44;

s32 func_8AF1000C(void) {
    s16 result;

    func_8AC007FC();
    result = 12;
    if ((*(u16 *)((u8 *)D_8AF263C0 + 8) & 0x4000) && func_80044144(D_8AF26A44)) {
        func_8AF00130(3);
        result = 10;
        D_8AF26A44 = 0;
    }
    if (D_8AF2FA8C != NULL && *(s32 *)((u8 *)D_8AF2FA8C + 0x1C) != 0) {
        func_8AC06D70(D_8AF2FA98, (u32)0xB93732FF, (u32)0xC39B6EFF, 3);
    }
    if (D_8AF2FA90 != NULL && *(s32 *)((u8 *)D_8AF2FA90 + 0x1C) != 0) {
        func_8AC06D70(D_8AF2FAC8, (u32)0xB93732FF, (u32)0xC39B6EFF, 5);
    }
    switch ((s16)D_8AF2F9CE) {
    case 1:
        func_8AC06D70(D_8AF2FB28, (u32)0xB93732FF, (u32)0xC39B6EFF, 5);
        break;
    case 2: case 6:
        func_8AC06D70(D_8AF2FB28, (u32)0xB93732FF, (u32)0xC39B6EFF, 0);
        break;
    case 3: case 4:
        if (D_8AF2F9CC == 0xEC) {
            func_8AC06D70(D_8AF2FAF8, (u32)0xB93732FF, (u32)0xC39B6EFF, 3);
        } else {
            func_8AC06D70(D_8AF2FAF8, (u32)0xB93732FF, (u32)0xC39B6EFF, 0);
        }
        func_8AC06D70(D_8AF2FB58, (u32)0xB93732FF, (u32)0xC39B6EFF, 0);
        func_8AC06D70(D_8AF2FB88, (u32)0xB93732FF, (u32)0xC39B6EFF, 5);
        break;
    case 5:
        func_8AC06D70(D_8AF2FB28, (u32)0xB93732FF, (u32)0xC39B6EFF, 3);
        func_8AC06D70(D_8AF2FB58, (u32)0xB93732FF, (u32)0xC39B6EFF, 3);
        func_8AC06D70(D_8AF2FB88, (u32)0xB93732FF, (u32)0xC39B6EFF, 0);
        func_8AC06D70(D_8AF2FBB8, (u32)0xB93732FF, (u32)0xC39B6EFF, 5);
        func_8AC06D70(D_8AF2FBE8, (u32)0xB93732FF, (u32)0xC39B6EFF, 5);
        break;
    }
    return result;
}

s32 func_8AF1025C(s16 code) {
    s32 result;

    switch (code) {
    case 0: case 1:
        result = 0x80;
        break;
    case 2: case 6:
        result = 0x54;
        break;
    case 3: case 4: case 5:
        result = 0x40;
        break;
    default:
        result = -1;
        break;
    }
    return result;
}

extern void Gfx_DrawTextureRgba16(s16, s16, s16, s16, u8 *, s16, s32);

/* Preserve one logical source line for IDO's instruction scheduling. */
void func_8AF102AC(s16 x, s16 y, u8 *image) { \
    s32 row; \
    s32 i; \
    u8 *texture; \
    switch (D_8AF2F9CE) { \
    case 0: case 1: \
        row = y; \
        i = 0; \
        texture = image; \
        do { \
            Gfx_DrawTextureRgba16(x, row, 128, 16, texture, 128, 0); \
            i += 4096; \
            row += 16; \
            texture += 4096; \
        } while (i != 32768); \
        break; \
    case 2: case 6: \
        row = y; \
        i = 0; \
        texture = image; \
        do { \
            Gfx_DrawTextureRgba16(x, row, 84, 21, texture, 84, 0); \
            i += 3528; \
            row += 21; \
            texture += 3528; \
        } while (i != 14112); \
        break; \
    case 3: case 4: case 5: \
        Gfx_DrawTextureRgba16(x, y, 64, 32, image, 64, 0); \
        Gfx_DrawTextureRgba16(x, y + 32, 64, 32, image + 0x1000, 64, 0); \
        break; \
    } \
}

struct B4410State;
extern s32 func_8004410C(struct B4410State *, s32);
extern Gfx *D_800D0510;
extern Gfx D_80094E38[];

void func_8AF1043C(void) {
    s32 i;

    func_8AF1025C((s16)D_8AF2F9CE);
    if (D_8AF26A44 != 0) {
        gSPDisplayList(D_800D0510++, D_80094E38);
        gDPSetRenderMode(D_800D0510++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
        for (i = 0; i < 6UL; i++) {
            if (D_8AF2F9E0[i][0] != 0) {
                if (D_8AF2F9D0[i] == 0) {
                    continue;
                }

                func_8AF102AC(D_8AF2F9E0[i][1], D_8AF2F9E0[i][2], (u8 *)func_8004410C((struct B4410State *)D_8AF26A44, i));
            }
        }
    }
}

extern void func_80043E70(s32, s32);

void func_8AF10540(void) {
    if (D_8AF26A44 != 0) {
        func_80043E70(D_8AF26A44, 0);
    }
}

extern void func_8AC015B0(s16, s16, s32, s32, s16);
extern u8 D_8AF26A58[];
extern u8 D_8AF26B98[];
extern u8 D_8AF30158[];
extern s16 D_8AF26F1C;
extern s16 D_8AF26F24;
extern s16 D_8AF26F28;
extern s16 D_8AF30FF8;
extern s16 D_8AF30FFA;
extern s16 D_8AF30FFC;
extern s16 D_8AF30FFE;

s32 func_8AF10570(s32 mode, void *record) {
    s16 x;
    s16 y;
    void *preserved;
    s16 values[2];

    preserved = record;
    switch (mode) {
    case 0:
        *(u16 *)((u8 *)preserved + 2) &= 0xFFFD;
        break;
    case 1:
        func_800504BC(values);
        x = *(s16 *)((u8 *)preserved + 8) + values[0];
        y = *(s16 *)((u8 *)preserved + 0xA) + values[1];
        func_8AC015B0(x, y, (s32)(D_8AF26A58), D_8AF26F1C, D_8AF30FF8);
        break;
    }
    return 0;
}

s32 func_8AF1060C(s32 mode, void *record) {
    s16 x;
    s16 y;
    void *preserved;
    s16 values[2];

    preserved = record;
    switch (mode) {
    case 0:
        *(u16 *)((u8 *)preserved + 2) &= 0xFFFD;
        break;
    case 1:
        func_800504BC(values);
        x = *(s16 *)((u8 *)preserved + 8) + values[0];
        y = *(s16 *)((u8 *)preserved + 0xA) + values[1];
        func_8AC015B0(x, y, (s32)(D_8AF26B98), D_8AF26F24, D_8AF30FFC);
        break;
    }
    return 0;
}

extern void func_8AC01574(s16, s16, s32, s32, s16);
extern u8 D_8AF26DD8[];
extern s16 D_8AF26F20;
extern s16 D_8AF31000;

s32 func_8AF106A8(s32 mode, void *record) {
    void *preserved;
    s16 x;
    s16 y;
    s16 values[2];

    preserved = record;
    switch (mode) {
    case 0:
        *(u16 *)((u8 *)preserved + 2) &= 0xFFFD;
        break;
    case 1:
        func_800504BC(values);
        x = *(s16 *)((u8 *)preserved + 8) + values[0];
        y = *(s16 *)((u8 *)preserved + 0xA) + values[1];
        if (D_8AF31000 == 3) {
            func_8AC01574(x, y, (s32)D_8AF26DD8, D_8AF26F20, D_8AF30FFA);
        } else {
            func_8AC015B0(x, y, (s32)D_8AF26DD8, D_8AF26F20, D_8AF30FFA);
        }
        break;
    }
    return 0;
}

s32 func_8AF10784(s32 mode, void *record) {
    s16 x;
    s16 y;
    void *preserved;
    s16 values[2];

    preserved = record;
    switch (mode) {
    case 0:
        *(u16 *)((u8 *)preserved + 2) &= 0xFFFD;
        break;
    case 1:
        func_800504BC(values);
        x = *(s16 *)((u8 *)preserved + 8) + values[0];
        y = *(s16 *)((u8 *)preserved + 0xA) + values[1];
        func_8AC015B0(x, y, (s32)(D_8AF30158 + D_8AF30FFA * 0x1A0), D_8AF26F28, D_8AF30FFE);
        break;
    }
    return 0;
}

extern void *D_8AF3011C;
extern void *D_8AF30120;
extern void *D_8AF30124;
extern void *D_8AF30128;
extern void *D_8AF3012C;
extern void *D_8AF30130;

void func_8AF10840(void) {
    *(u16 *)((u8 *)D_8AF3011C + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF30128 + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF30120 + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF3012C + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF30124 + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF30130 + 2) &= ~2;
}

void func_8AF108BC(void) {
    (*(u16 *)((u8 *)(D_8AF3011C) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3011C) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30128) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30128) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30120) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30120) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF3012C) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3012C) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30124) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30124) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30130) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30130) + (2))) | 2);
}

void func_8AF10938(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x28) = arg1;
    *(s32 *)(arg0 + 0x2C) = arg2;
}

extern void *D_8AF300C8;
extern void *D_8AF300CC;
extern void *D_8AF300D0;
extern s16 D_8AF300C4;

void func_8AF10944(void) {
    *(u16 *)((u8 *)D_8AF300C8 + 2) &= ~1;
    *(u16 *)((u8 *)D_8AF300CC + 2) &= ~1;
    *(u16 *)((u8 *)D_8AF300D0 + 2) &= ~1;
    func_8AF10938(D_8AF30128, (s32)0xC3A05AFF, (s32)0xE1C38CFF);
    func_8AF10938(D_8AF3012C, (s32)0xC3A05AFF, (s32)0xE1C38CFF);
    func_8AF10938(D_8AF30130, (s32)0xC3A05AFF, (s32)0xE1C38CFF);
    if (D_8AF31000 == 0) {
        switch (D_8AF300C4) {
        case 0:
            *(u16 *)((u8 *)D_8AF300C8 + 2) |= 1;
            func_8AF10938(D_8AF30128, (s32)0xFFFF00FF, (s32)0xFFFF00FF);
            break;
        case 2:
            *(u16 *)((u8 *)D_8AF300CC + 2) |= 1;
            func_8AF10938(D_8AF3012C, (s32)0xFFFF00FF, (s32)0xFFFF00FF);
            break;
        case 1:
            *(u16 *)((u8 *)D_8AF300D0 + 2) |= 1;
            func_8AF10938(D_8AF30130, (s32)0xFFFF00FF, (s32)0xFFFF00FF);
            break;
        }
    }
}

extern void _bzero(s32 *, s32);
extern s16 D_8AF26EF8[][2];
struct MenuRGBA {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};
extern struct MenuRGBA D_8AF26A50;
extern struct MenuRGBA D_8AF26A54;

void func_8AF10AB8(void) {
    u8 *bank;
    u8 *record;
    s32 count;
    s32 first;
    s32 i;
    s16 *descriptor;
    s32 group;

    _bzero((s32 *)D_8AF30158, 0xEA0);
    descriptor = &D_8AF26EF8[0][0];
    for (group = 0; group < 9; group++) {
        count = descriptor[1];
        first = descriptor[0];
        bank = D_8AF30158 + group * 0x1A0;
        record = bank;
        for (i = 0; i < count; i++) {
            *(s16 *)(record + 0) = 1;
            *(s16 *)(record + 2) = 0;
            *(s16 *)(record + 4) = i * 0x18;
            *(s32 *)(record + 8) = 0x3B;
            *(s32 *)(record + 0xC) = first + i;
            *(struct MenuRGBA *)(record + 0x16) = D_8AF26A50;
            *(struct MenuRGBA *)(record + 0x1A) = D_8AF26A54;
            record += 0x20;
        }
        descriptor += 2;
    }
}

void func_8AF10CD4(void) {
    D_8AF31000 = 0;
    D_8AF30FF8 = 0;
    D_8AF30FFC = 0;
    D_8AF30FFA = 0;
    D_8AF30FFE = 0;
    D_8AF300C4 = 0;
}

extern void *func_8AF00504(s16);
extern s32 func_8AF003A8(s16);
extern void func_8AC06E98(void *);
extern void func_8AC05E40(s32, s32, s32);
extern s32 func_8AC06D8C(s32, s32);
extern void func_8004E308(s32, s32 *, s32 *);
extern void func_8AC02C80(s32, s32, s32, void *);
extern s16 func_8AC01354(void *, s32);
extern void func_8AC0080C(s16);
extern s32 func_8AF013D8(s32, void *);
extern s32 func_8AF10570(s32, void *);
extern s32 func_8AF1060C(s32, void *);
extern s32 func_8AF106A8(s32, void *);
extern s32 func_8AF10784(s32, void *);
extern u8 D_8AF2FF40[];
extern u8 D_8AF2FFB8[];
extern u8 D_8AF30030[];
extern u8 D_8AF300E8[];
extern void *D_8AF300A8;
extern void *D_8AF300AC;
extern void *D_8AF300B0;
extern void *D_8AF300B8;
extern void *D_8AF300BC;
extern void *D_8AF300C0;
extern void *D_8AF300D4;
extern void *D_8AF300D8;
extern void *D_8AF300DC;
extern void *D_8AF300E0;
extern void *D_8AF30114;
extern void *D_8AF30134;
extern void *D_8AF30138;
extern void *D_8AF3013C;
extern void *D_8AF30140;
extern void *D_8AF30144;
extern void *D_8AF30148;
extern void *D_8AF3014C;
extern void *D_8AF30150;

void func_8AF10D08(void) {
    s32 page;

    func_8AF00504(0x1B);
    func_8AF00504(0x35);
    page = func_8AF003A8(0x1B);
    func_8AC06E98((void *)page);
    func_8AC05E40(page, 0x6E616D65, (s32)D_8AF2FF40);
    func_8AC05E40(page, 0x74797065, (s32)D_8AF2FFB8);
    func_8AC05E40(page, 0x6B6F6B61, (s32)D_8AF30030);
    D_8AF300A8 = D_8AF2FF40;
    D_8AF300AC = D_8AF2FFB8;
    D_8AF300B0 = D_8AF30030;
    D_8AF300D8 = (void *)func_8AC06D8C(page, 0x6E616D65);
    D_8AF300DC = (void *)func_8AC06D8C(page, 0x74797065);
    D_8AF300E0 = (void *)func_8AC06D8C(page, 0x6B6F6B61);
    D_8AF300C8 = (void *)func_8AC06D8C(page, 0x74655F31);
    D_8AF300CC = (void *)func_8AC06D8C(page, 0x74655F32);
    D_8AF300D0 = (void *)func_8AC06D8C(page, 0x74655F33);
    func_8004E308((s32)D_8AF300C8, (s32 *)func_8AF013D8, NULL);
    func_8004E308((s32)D_8AF300CC, (s32 *)func_8AF013D8, NULL);
    func_8004E308((s32)D_8AF300D0, (s32 *)func_8AF013D8, NULL);
    D_8AF300D4 = (void *)func_8AC06D8C(page, 0x626F6F6B);
    D_8AF3011C = (void *)func_8AC06D8C(page, 0x6E5F7769);
    D_8AF30120 = (void *)func_8AC06D8C(page, 0x745F7769);
    D_8AF30124 = (void *)func_8AC06D8C(page, 0x6B5F7769);
    D_8AF30128 = (void *)func_8AC06D8C(page, 0x6E5F3230);
    D_8AF3012C = (void *)func_8AC06D8C(page, 0x745F3230);
    D_8AF30130 = (void *)func_8AC06D8C(page, 0x6B5F3230);
    D_8AF30134 = (void *)func_8AC06D8C(page, 0x6E6E6E6E);
    D_8AF30138 = (void *)func_8AC06D8C(page, 0x6E5F6E5F);
    *(u16 *)((u8 *)D_8AF30134 + 2) &= 0xFFFE;
    *(u16 *)((u8 *)D_8AF30134 + 2) &= 0xFFFD;
    D_8AF3013C = (void *)func_8AC06D8C(page, 0x74747474);
    D_8AF30140 = (void *)func_8AC06D8C(page, 0x745F745F);
    *(u16 *)((u8 *)D_8AF3013C + 2) &= 0xFFFE;
    *(u16 *)((u8 *)D_8AF3013C + 2) &= 0xFFFD;
    D_8AF30144 = (void *)func_8AC06D8C(page, 0x6B6B6B6B);
    D_8AF30148 = (void *)func_8AC06D8C(page, 0x6B5F6B5F);
    *(u16 *)((u8 *)D_8AF30144 + 2) &= 0xFFFE;
    *(u16 *)((u8 *)D_8AF30144 + 2) &= 0xFFFD;
    D_8AF3014C = (void *)func_8AC06D8C(page, 0x6B326B32);
    D_8AF30150 = (void *)func_8AC06D8C(page, 0x6B5F325F);
    *(u16 *)((u8 *)D_8AF3014C + 2) &= 0xFFFE;
    *(u16 *)((u8 *)D_8AF3014C + 2) &= 0xFFFD;
    func_8004E308((s32)D_8AF30138, (s32 *)func_8AF10570, NULL);
    func_8004E308((s32)D_8AF30140, (s32 *)func_8AF1060C, NULL);
    func_8004E308((s32)D_8AF30148, (s32 *)func_8AF106A8, NULL);
    func_8004E308((s32)D_8AF30150, (s32 *)func_8AF10784, NULL);
    page = func_8AF003A8(0x35);
    func_8AC02C80(page, 0x74697431, 0x74697432, D_8AF300E8);
    D_8AF30114 = (void *)func_8AC06D8C(page, 0x7469746C);
    *(s16 *)((u8 *)D_8AF30114 + 0x30) = 0x36;
    *(s16 *)((u8 *)D_8AF30114 + 0x32) = 0x10;
    D_8AF26F1C = func_8AC01354(D_8AF26A58, 10);
    D_8AF26F20 = func_8AC01354(D_8AF26DD8, 9);
    D_8AF26F24 = func_8AC01354(D_8AF26B98, 18);
    func_8AF10AB8();
    func_8AC01354(D_8AF30158 + D_8AF30FFA * 0x1A0, 13);
    func_8AF10944();
    switch (D_8AF31000) {
    case 1:
        D_8AF300B8 = D_8AF300A8;
        D_8AF300BC = D_8AF300AC;
        D_8AF300C0 = D_8AF300B0;
        func_8AF10840();
        goto scale;
    case 4:
        D_8AF300BC = D_8AF300A8;
        D_8AF300B8 = D_8AF300AC;
        D_8AF300C0 = D_8AF300B0;
        func_8AF10840();
        goto scale;
    case 2: case 3:
        D_8AF300BC = D_8AF300A8;
        D_8AF300C0 = D_8AF300AC;
        D_8AF300B8 = D_8AF300B0;
        func_8AF10840();
        goto scale;
    case 0:
    default:
        break;
    }
scale:
    if (D_8AF31000 != 0) {
        *(f32 *)((u8 *)D_8AF300B8 + 0x40) = 0.6f;
        *(f32 *)((u8 *)D_8AF300B8 + 0x44) = 0.6f;
        *(f32 *)((u8 *)D_8AF300BC + 0x40) = 0.01f;
        *(f32 *)((u8 *)D_8AF300BC + 0x44) = 0.01f;
        *(f32 *)((u8 *)D_8AF300C0 + 0x40) = 0.01f;
        *(f32 *)((u8 *)D_8AF300C0 + 0x44) = 0.01f;
        *(f32 *)((u8 *)D_8AF300B8 + 0x48) = 120.0f;
        *(f32 *)((u8 *)D_8AF300B8 + 0x4C) = 180.0f;
    }
    func_8AC0080C(4);
}

void func_8AF11358(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (arg1 < value) {
        value -= arg2;
        if (value < arg1) value = arg1;
        *arg0 = value;
    }
}

void func_8AF11398(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (value < arg1) {
        value += arg2;
        if (arg1 < value) value = arg1;
        *arg0 = value;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF113D8.s")

extern void func_800498C4(void);
extern void func_800499EC(void);
void func_8AF12398(void) {
    func_800498C4();
    func_800499EC();
}

extern s16 *D_8AF2BA94;
extern u8 D_8AF31C48[250];
void func_8AF123C0(void) {
    s16 *source;
    s16 index;
    s16 value;
    s16 sentinel;

    source = D_8AF2BA94;
    index = 0;
    sentinel = -1;
    for (;;) {
        value = *source;
        if (sentinel != value) {
            *((u8 *)&D_8AF31C48 + index) = value;
            index++;
            index = (s16) index;
            if (index >= 250) {
                break;
            }
        }
        source++;
    }
}

u8 *func_8AF12410(u8 *pixels, s16 count) {
    s32 remainder;
    s32 i;
    remainder = count % 4;
    if (remainder > 0) {
        for (i = 0; i < 4 - (count % 4); i++) {
            pixels[0] = 0xFF;
            pixels[1] = 0xFF;
            pixels += 4;
        }
    }
    return pixels;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF124A8.s")

extern s16 D_8AF31024;
extern char D_8AF315A0[];
extern char D_8AF296C8[];
struct MenuGridEntry {
    u8 kind;
    u8 palette;
    u8 unknown;
    u8 blink;
};
extern struct MenuGridEntry D_8AF316C8[];

u8 *func_8AF125D0(s16 category) {
    u8 *output;
    u8 *destination;
    s32 index;
    s16 count;
    s16 selected;
    s16 mapped;
    s16 id;
    u16 saved;

    count = 0;
    D_8AF31024 = 1;
    *(s16 *)&D_8AF31D42 = -1;
    selected = (s16)category;
    sprintf(D_8AF315A0, D_8AF296C8);
    func_8004C54C(0x2F, (s32)func_8004C874(0xC, D_8AF263C4[selected]));
    func_8AF123C0();
    output = (u8 *)D_8AF316C8;
    _bzero((s32 *)output, 1000);
    destination = output;
    for (index = 0; index != 250; index++) {
        id = D_8AF31C48[index];
        saved = id;
        mapped = func_8AF01530(func_80062D98(id));
        if (id == 0xA5) {
            continue;
        }
        if (mapped != selected) {
            continue;
        }
        destination[0] = saved;
        destination[1] = mapped;
        destination += 4;
        count++;
    }
    return func_8AF12410(destination, count);
}

/* Preserve this logical source line for IDO's instruction scheduling. */
u8 *func_8AF1271C(u8 *output, s16 *table, u16 mask) { \
    u8 *entry; \
    u8 *end; \
    u8 *destination; \
    s32 id; \
    s16 count; \
    destination = output;
    count = 0;
    entry = D_8AF31C48; end = &D_8AF31D42;
    do {
        id = *entry;
        if (table[id - 1] & mask) {
            destination[0] = id;
            destination[1] = func_8AF01530(func_80062D98(id));
            destination += 4;
            count++;
        }
        entry++;
    } while (entry != end);
    return func_8AF12410(destination, count);
}

extern char D_8AF314A0[];
extern char D_8AF296F0[];
extern char D_8AF29730[];
extern char D_8AF29734[];
extern char D_8AF29738[];
extern char D_8AF2973C[];
extern s16 *D_8AF2BA90[];
extern u16 D_8AF26F4C[][13][2];

void func_8AF127E8(s16 group, s16 selected) {
    char *heading;
    char *detail;
    u8 *output;
    u8 *destination;
    u16 *entry;
    s32 i;

    *(s16 *)&D_8AF31D42 = selected;
    D_8AF31024 = 2;
    heading = func_8004C874(0x3B, group + 0x68);
    if (selected >= 0) {
        detail = func_8004C874(0x3B, D_8AF26EF8[group][0] + selected);
    } else {
        detail = D_8AF296F0;
    }
    if (selected >= 0) {
        sprintf(D_8AF314A0, D_8AF29730, heading);
        sprintf(D_8AF315A0, D_8AF29734, detail);
    } else {
        sprintf(D_8AF314A0, D_8AF29738, heading);
        sprintf(D_8AF315A0, D_8AF2973C);
    }
    func_8AF123C0();
    output = (u8 *)D_8AF316C8;
    _bzero((s32 *)output, 1000);
    destination = output;
    switch (group) {
    case 0:
        for (i = 0; i != 9; i++) {
            destination = func_8AF1271C(destination, D_8AF2BA90[2], 0x8000 >> i);
        }
        break;
    case 1:
        for (i = 0; i != 7; i++) {
            destination = func_8AF1271C(destination, D_8AF2BA90[2], 0x40 >> i);
        }
        func_8AF1271C(destination, D_8AF2BA90[3], 0x8000);
        break;
    default:
        entry = D_8AF26F4C[group][selected];
        func_8AF1271C(output, D_8AF2BA90[entry[0] + 1], entry[1]);
        break;
    }
}

extern u8 D_8AF26F34[];
s32 func_8AF129F8(u8 arg0) {
    u8 *ptr;
    s32 index;
    ptr = &D_8AF26F34;
    index = 0;
    for (;;) {
        if (*ptr != 0xFF) {
            if (arg0 == *ptr) return index;
            ptr++;
            index++;
            index = (s16)index;
        } else {
            return -1;
        }
    }
}

extern u8 func_80062D5C(u8);
extern u8 func_80062E10(u8);
extern u8 func_80062DD4(u8);
extern void *D_8AF31178;
extern void *D_8AF3117C;
extern void *D_8AF31180;
extern void *D_8AF31188;
extern void *D_8AF3118C;
extern void *D_8AF31190;
extern u8 D_8AF316B2[2];
extern u8 D_8AF316B4;
extern s16 D_8AF316B0;
extern s16 D_8AF31D78;
extern s32 D_8AF316AC;
extern char D_8AF311A0[];
extern char D_8AF312A0[];
extern char D_8AF313A0[];
extern char D_8AF29740[];
extern char D_8AF29744[];
extern char D_8AF29778[];
extern char D_8AF2977C[];

void func_8AF12A4C(u8 *record) {
    u8 id;
    u8 category;
    s32 texture_index;
    u8 rate;

    id = record[0];
    category = record[1];
    texture_index = id - 1;
    *(s16 *)((u8 *)D_8AF31178 + 0x30) = 6;
    *(s16 *)((u8 *)D_8AF31178 + 0x32) = texture_index;
    *(s16 *)((u8 *)D_8AF3117C + 0x30) = 7;
    *(s16 *)((u8 *)D_8AF3117C + 0x32) = texture_index;
    D_8AF316B2[0] = func_80062D5C(id);
    D_8AF316B2[1] = func_80062E10(id);
    rate = func_80062DD4(id);
    D_8AF316B4 = (s32)((((func_80062DD4(id) * 100.0f / 255.0f) > 0.0f) ? 0.5f : -0.5f) +
                      (rate * 100.0f / 255.0f));
    sprintf(D_8AF312A0, D_8AF29740, D_8AF316B2[1]);
    sprintf(D_8AF313A0, D_8AF29744, D_8AF316B4);
    switch (D_8AF31024) {
    case 0:
        func_8004C54C(0x2F, (s32)func_8004C874(0xC, D_8AF263C4[category]));
        func_8004C54C(0x3D, (s32)D_8AF314A0);
        func_8004C54C(0x3F, (s32)D_8AF315A0);
        *(s16 *)((u8 *)D_8AF31188 + 0x30) = 0x3B;
        *(s16 *)((u8 *)D_8AF31188 + 0x32) = 0x9F;
        break;
    case 1:
        func_8004C54C(0x3F, (s32)D_8AF315A0);
        *(s16 *)((u8 *)D_8AF31188 + 0x30) = 0x3B;
        *(s16 *)((u8 *)D_8AF31188 + 0x32) = 0xA0;
        break;
    case 2:
        func_8004C54C(0x2F, (s32)func_8004C874(0xC, D_8AF263C4[category]));
        func_8004C54C(0x3E, (s32)D_8AF314A0);
        func_8004C54C(0x3F, (s32)D_8AF315A0);
        *(s16 *)((u8 *)D_8AF31188 + 0x30) = 0x3B;
        *(s16 *)((u8 *)D_8AF31188 + 0x32) = 0xA1;
        break;
    }
    func_8004C54C(0x31, (s32)D_8AF312A0);
    func_8004C54C(0x32, (s32)D_8AF313A0);
    func_8004C594(2, D_8AF316B0);
    D_8AF31D78 = func_8AF129F8(id);
    if (D_8AF31D78 >= 0) {
        *(s16 *)((u8 *)D_8AF3118C + 0x32) = D_8AF31D78 + 0xA8;
        *(u16 *)((u8 *)D_8AF3118C + 2) |= 1;
        *(u16 *)((u8 *)D_8AF31190 + 2) |= 1;
    } else {
        *(u16 *)((u8 *)D_8AF3118C + 2) &= ~1;
        *(u16 *)((u8 *)D_8AF31190 + 2) &= ~1;
    }
    if (record[2] != 0) {
        *(s16 *)((u8 *)D_8AF31180 + 0x32) = 0xA2;
    } else {
        *(s16 *)((u8 *)D_8AF31180 + 0x32) = 0x67;
    }
    if (D_8AF316B2[0] >= 2) {
        sprintf(D_8AF311A0, D_8AF29778, D_8AF316B2[0]);
    } else {
        sprintf(D_8AF311A0, D_8AF2977C, D_8AF316AC);
    }
    func_8004C54C(0x30, (s32)D_8AF311A0);
}

extern u16 *D_8AF2BA9C;

s32 func_8AF12E30(s16 arg0) {
    u16 *entry;
    s32 result;

    /* Byte-scaled base with an explicit shift; D_8AF2BA9C + arg0 would scale the
     * index first and swap the base-load/scale temp colors (t6/t7). Same idiom as
     * func_8AF16EB0's family of checks against D_8AF2BAA4.
     * //@src/fragments/44/fragment44_204950.c */
    entry = (u16 *)((u8 *)D_8AF2BA9C + (arg0 << 1));
    result = 0;
    if (*--entry & 1) {
        return 1;
    }
    return result;
}

/* Standalone empty function: the retail ROM has a lone jr ra; nop at 0x8AF12E74
 * between func_8AF12E30 and func_8AF12E7C with no symbol in the map file, so it
 * had static linkage and its body compiled out. Keeping it here preserves the
 * fragment's byte layout. */
static void func_8AF12E74(void) {
}
extern s32 D_8AF26F30;
extern s16 D_8AF316A4;
extern s16 D_8AF316A6;
struct MenuScrollState {
    s16 fields[7];
};
extern struct MenuScrollState D_8AF316B8;

void func_8AF12E7C(void) {
    D_8AF316A4 = 0;
    D_8AF316A6 = 0;
    _bzero((s32 *)&D_8AF316B8, 0xE);
    D_8AF26F30 = 0;
}

extern void func_8004C4B0(s32);
extern s32 func_8AF12E30(s16);
extern s32 func_8AC039A4(s32, void *);
extern void func_8AC06400(void *, void *);
extern void func_8AC0651C(void *, s16, s16, s16, s16);
extern void func_8AC05ED4(s32, s32, s32);
extern s16 D_8AF31198;
extern s16 D_8AF31C40;
extern void *D_8AF31184;
extern void *D_8AF31194;
extern void *D_8AF31D7C;
extern u8 D_8AF31D80[];
extern s16 D_8AF316A0;
extern s16 D_8AF316A2;
extern s32 D_8AF316A8;
extern u8 D_8AF31088[];
extern u8 D_8AF31100[];
extern u8 D_8AF31028[];
extern u8 D_8AF31058[];
extern struct MenuScrollState D_8AF31DF8;

void func_8AF12EB8(void) {
    s32 page;
    struct MenuGridEntry *entry;
    s32 i;
    void *node;
    s32 first;
    s32 second;
    s32 third;
    s32 fourth;
    s32 fifth;
    s32 sixth;
    s16 visible_rows;

    D_8AF31198 = 0;
    func_8004C4B0(6);
    func_8004C4B0(7);
    func_8004C4B0(0x3B);
    func_8AF00504(0x65);
    page = func_8AF003A8(0x65);
    func_8AC06E98((void *)page);
    D_8AF316B0 = 0;
    D_8AF31C40 = 0;
    entry = D_8AF316C8;
    for (i = 0; i != 250; i++, entry++) {
        if (entry->kind <= 0) {
            break;
        }
        D_8AF31C40++;
        if (entry->kind == 0xFF) {
            continue;
        }
        D_8AF316B0++;
        if (func_8AF12E30(entry->kind)) {
            entry->unknown = 1;
        }
        if (func_8AF129F8(entry->kind) >= 0) {
            entry->blink = 1;
        }
    }
    first = func_8AC06D8C(page, 0x65727331);
    second = func_8AC06D8C(page, 0x65727332);
    third = func_8AC06D8C(page, 0x65727333);
    fourth = func_8AC06D8C(page, 0x65727334);
    fifth = func_8AC06D8C(page, 0x65727335);
    sixth = func_8AC06D8C(page, 0x65727336);
    func_8004E308(first, (s32 *)func_8AC039A4, (s32 *)0xFFF1);
    func_8004E308(second, (s32 *)func_8AC039A4, (s32 *)0xFFF1);
    func_8004E308(third, (s32 *)func_8AC039A4, (s32 *)0xFFF1);
    func_8004E308(fourth, (s32 *)func_8AC039A4, (s32 *)0xFFF1);
    func_8004E308(fifth, (s32 *)func_8AC039A4, (s32 *)0xFFF1);
    func_8004E308(sixth, (s32 *)func_8AC039A4, (s32 *)0xFFF1);
    D_8AF31188 = (void *)func_8AC06D8C(page, 0x7469746C);
    *(s16 *)((u8 *)D_8AF31188 + 0x30) = 0x3B;
    *(s16 *)((u8 *)D_8AF31188 + 0x32) = 0x9F;
    D_8AF3118C = (void *)func_8AC06D8C(page, 0x62756E32);
    *(s16 *)((u8 *)D_8AF3118C + 0x30) = 0x3B;
    *(s16 *)((u8 *)D_8AF3118C + 0x32) = 0xA8;
    D_8AF31180 = (void *)func_8AC06D8C(page, 0x736C6966);
    *(s16 *)((u8 *)D_8AF31180 + 0x30) = 0x3B;
    *(s16 *)((u8 *)D_8AF31180 + 0x32) = 0xA2;
    D_8AF31178 = (void *)func_8AC06D8C(page, 0x77617A61);
    D_8AF3117C = (void *)func_8AC06D8C(page, 0x62756E5F);
    D_8AF31190 = (void *)func_8AC06D8C(page, 0x6D61726B);
    D_8AF31194 = (void *)func_8AC06D8C(page, 0x626F6F6B);
    D_8AF31D7C = (void *)func_8AC06D8C(page, 0x6162746E);
    func_8AC05E40(page, 0x6162746E, (s32)D_8AF31D80);
    func_8AC06400(D_8AF31D80, D_8AF31D7C);
    D_8AF31184 = (void *)func_8AC06D8C(page, 0x77615F31);
    D_8AF316A0 = *(s16 *)((u8 *)D_8AF31184 + 8);
    D_8AF316A2 = *(s16 *)((u8 *)D_8AF31184 + 0xA);
    visible_rows = *(s16 *)((u8 *)D_8AF31184 + 0xE) / 20 - 1;
    D_8AF316A8 = (s32)func_8004C874(0x3B, 0x3D);
    D_8AF316AC = (s32)func_8004C874(0x3B, 0x46);
    func_8AC05ED4(page, 0x79615F75, (s32)D_8AF31088);
    func_8AC05ED4(page, 0x79615F73, (s32)D_8AF31100);
    func_8AC02C80(page, 0x725F6C5F, 0x725F725F, D_8AF31028);
    if (*(s16 *)&D_8AF31D42 >= 0) {
        func_8AC02C80(page, 0x725F6C32, 0x725F7232, D_8AF31058);
    } else {
        node = (void *)func_8AC06D8C(page, 0x725F6C32);
        *(u16 *)((u8 *)node + 2) &= ~1;
        node = (void *)func_8AC06D8C(page, 0x725F7232);
        *(u16 *)((u8 *)node + 2) &= ~1;
    }
    func_8AF12A4C(&D_8AF316C8[D_8AF316A4 + D_8AF316A6 * 4].kind);
    func_8AC0651C(&D_8AF316B8, (D_8AF31C40 - 1) / 4, 20, visible_rows, 10);
    if (D_8AF26F30 != 0) {
        D_8AF316B8 = D_8AF31DF8;
        D_8AF26F30 = 0;
    }
}

extern void func_8AC0686C(void *, s16);
extern s32 func_8AC0660C(s16);
extern s32 func_8AC06630(s16, void *);
extern void func_8AC0619C(void *, u16);
extern void func_8AC06220(void *, u16);
extern void func_8AC063AC(void *, u16);
extern s16 D_8AF316BC;
extern u8 D_8AF31E40;
extern u16 D_8AF2BDC6;
struct MenuInputState {
    u8 header[6];
    u16 held;
    u16 pressed;
    u16 unknown;
    u16 repeat;
};

s32 func_8AF133C0(void) {
    s16 result;
    s32 pressed;
    s16 old_column;
    s16 old_row;
    s32 was_scrolling;
    s32 changed;
    u16 repeat;
    u16 buttons;

    was_scrolling = 0;
    old_column = D_8AF316A4;
    old_row = D_8AF316A6;
    func_8AC007FC();
    if (D_8AF31198 < 4) {
        *(u16 *)((u8 *)D_8AF31194 + 2) |= 2;
    } else {
        *(u16 *)((u8 *)D_8AF31194 + 2) &= 0xFFFD;
    }
    result = 14;
    if (D_8AF316BC != 0) {
        was_scrolling = 1;
    }
    func_8AC0686C(&D_8AF316B8, D_8AF316A6);
    pressed = ((struct MenuInputState *)D_8AF263C0)->pressed;
    if ((pressed & 0x8000) && D_8AF316C8[D_8AF316A4 + D_8AF316A6 * 4].kind != 0xFF) {
        func_8AF00130(0xC2);
        result = 15;
        D_8AF31E40 = D_8AF316C8[D_8AF316A4 + D_8AF316A6 * 4].kind;
        D_8AF31DF8 = D_8AF316B8;
        D_8AF26F30 = 1;
    } else if (pressed & 0x4000) {
        func_8AF00130(3);
        result = 13;
    } else {
        repeat = ((struct MenuInputState *)D_8AF263C0)->repeat;
        if ((repeat & 0x100) && D_8AF316A4 < 3) {
            func_8AF00130(1);
            D_8AF316A4++;
        } else if ((repeat & 0x200) && D_8AF316A4 > 0) {
            func_8AF00130(1);
            D_8AF316A4--;
        } else if (D_8AF316BC == 0) {
            changed = 0;
            buttons = repeat;
            if (was_scrolling != 0) {
                buttons = ((struct MenuInputState *)D_8AF263C0)->held;
            }
            if ((buttons & 0x800) && func_8AC0660C(D_8AF316A6)) {
                func_8AF00130(1);
                D_8AF316A6--;
                changed = 1;
            } else if ((buttons & 0x400) && func_8AC06630(D_8AF316A6, &D_8AF316B8)) {
                func_8AF00130(1);
                D_8AF316A6++;
                changed = 1;
            }
            if (changed != 0) {
                func_8AC0686C(&D_8AF316B8, D_8AF316A6);
            }
        }
    }
    if (old_column != D_8AF316A4 || old_row != D_8AF316A6) {
        func_8AF12A4C(&D_8AF316C8[D_8AF316A4 + D_8AF316A6 * 4].kind);
    }
    func_8AC0619C(D_8AF31088, D_8AF2BDC6);
    func_8AC06220(D_8AF31100, D_8AF2BDC6);
    func_8AC063AC(D_8AF31D80, D_8AF2BDC6);
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF13718.s")
#endif
