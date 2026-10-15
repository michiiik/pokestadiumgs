#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000098.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000100.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_820001F0.s")
#endif

#ifdef VERSION_US
extern s16 D_82001D58;
extern void func_800468A0(s32);
extern void func_820001F0(s16 *);
void func_820006B8(void) {
    s16 *base = &D_82001D58;
    s32 *table = (s32 *)((u8 *)base + 8);
    func_800468A0(table[*(s16 *)((u8 *)base + 4)]);
    if (*base == 1) {
        func_820001F0(base);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_8200070C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000794.s")
#endif

#ifdef VERSION_US
typedef struct {
    s16 counter;
    s16 alpha;
} Fragment16Fade;
extern s16 D_82001EA0;
extern Fragment16Fade D_82001EA4;
extern s16 D_82001EA6;
extern s16 D_82001EA8;
extern s16 D_82001EAA;
extern s32 func_8004C990(s32, s32);
extern s32 func_8004D19C(s32, s32, s32, s32, s32);
extern u8 D_80094E38[];
extern Gfx *D_800D0510;
void Fragment16_DrawFadingOverlay(void) {
    s32 texture;
    if (D_82001EA0 != 0 && D_82001EA4.alpha > 0) {
        gSPDisplayList(D_800D0510++, D_80094E38);
        gDPSetEnvColor(D_800D0510++, 255, 255, 255, D_82001EA6);
        texture = func_8004C990(0x13D, 0);
        func_8004D19C(D_82001EA8, D_82001EAA, texture, 1, 0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000CB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000CE0.s")
#endif

#ifdef VERSION_US
s32 func_82000D10(s32 arg0, u8 *arg1) {
    if (arg0 == 0) {
        arg1[0x28] = 0x21;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern u8 D_82001EB8;
extern s16 D_82001EBC;
extern s16 D_82001EBE;

s32 func_82000D24(s32 arg0, void *arg1) {
    if (arg0 == 0) {
        (*(s16 *)((u8 *)(&D_82001EB8) + (0))) = (s16) (*(s16 *)((u8 *)(arg1) + (8)));
        (*(s16 *)((u8 *)(&D_82001EB8) + (2))) = (s16) (*(s16 *)((u8 *)(arg1) + (0xA)));
        D_82001EBC = (*(s16 *)((u8 *)(arg1) + (0xC)));
        D_82001EBE = (*(s16 *)((u8 *)(arg1) + (0xE)));
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s16 D_82001EC0;

s32 func_82000D64(s32 arg0, void *arg1) {
    if (arg0 == 0) {
        D_82001EC0 = (*(s16 *)((u8 *)(arg1) + (0xA)));
    }
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_82000D80(s32 arg0, void *arg1) {
    switch (arg0) {                                 /* irregular */
    case 1:
        break;
    case 0:
        if (func_800033A8() != 0) {
            (*(u16 *)((u8 *)(arg1) + (2))) = (u16) ((*(u16 *)((u8 *)(arg1) + (2))) | 2);
        } else {
            (*(u16 *)((u8 *)(arg1) + (2))) = (u16) ((*(u16 *)((u8 *)(arg1) + (2))) & 0xFFFD);
        }
        break;
    }
    return 0;
}
#endif

void func_82000DE0(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000DE8.s")
#endif

#ifdef VERSION_US
typedef struct {
    u8 r;
    u8 g;
    u8 b;
} Fragment16Color;
extern Gfx *D_800D0510;
extern s32 D_82001EB0, D_82001EB4;
extern s32 D_82001EAC;
extern s32 D_82001CD4;
extern s16 D_82001C10[];
extern Fragment16Color D_82001CF0, D_82001CF4, D_82001CF8, D_82001CFC;
extern char D_82001D10[], D_82001D24[], D_82001D2C[];
extern void *D_80087200;
extern void *func_8004C874(s32, s32);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800495F8(s32, s32, s32, const char *, ...);
extern void func_800495BC(s32, s32, const char *, ...);
extern s32 func_80049148(s32, s32, const char *, ...);
extern void Ui_DrawGradientPanel(s32, s32, s32, s32, s32, s32);
extern void func_800498C4(void);
extern void func_800499EC(void);
extern void func_800226C0(s32);
extern void _bcopy(const void *, void *, s32);
void Fragment16_DrawVersionStamp(void) {
    s8 month[4];
    s8 day[4];
    s8 hour[4];
    s8 minute[4];

    _bcopy((u8 *)(u32)D_82001CD4, month, 2);
    if (month[0] == '0') {
        month[0] = month[1];
        month[1] = 0;
    }
    month[2] = 0;
    _bcopy((u8 *)(u32)D_82001CD4 + 2, day, 2);
    if (day[0] == '0') {
        day[0] = day[1];
        day[1] = 0;
    }
    day[2] = 0;
    _bcopy((u8 *)(u32)D_82001CD4 + 4, hour, 2);
    hour[2] = 0;
    _bcopy((u8 *)(u32)D_82001CD4 + 6, minute, 2);
    minute[2] = 0;
    func_800496A4(0x10, 0);
    func_8004972C(255, 255, 255, 255);
    func_800495F8(600, 50, 2, D_82001D10, month, day, hour, minute);
}
#endif

#ifdef VERSION_US
void Fragment16_DrawSelectionList(void) {
    s32 i;
    Fragment16Color top = D_82001CF0;
    Fragment16Color bottom = D_82001CF4;
    s16 *entry;
    s32 y;

    Ui_DrawGradientPanel(100, 30, 300, 420, (s32)&top, (s32)&bottom);
    func_800498C4();
    func_800496A4(8, 0);
    for (i = 0, entry = D_82001C10, y = 50; i < 19; i++, entry++, y += 20) {
        if (i == D_82001EAC) {
            func_8004972C(255, 255, 0, 255);
        } else {
            func_8004972C(255, 255, 255, 255);
        }
        func_800495BC(120, y, func_8004C874(0x42, *entry));
    }
    func_800499EC();
}
#endif

#ifdef VERSION_US
void Fragment16_DrawSelectionPopup(void) {
    char *name;
    char buffer[0x80];
    s32 width;

    name = func_8004C874(0x16, D_82001EB0 + 1);
    {
        Fragment16Color top = D_82001CF8;
        Fragment16Color bottom = D_82001CFC;
        if (name != NULL) {
            sprintf(buffer, D_82001D24, D_82001EB0, name);
        } else {
            sprintf(buffer, D_82001D2C, D_82001EB0);
        }
        width = func_80049148(8, 0, buffer);
        Ui_DrawGradientPanel(140, 140, width + 40, 60, (s32)&top, (s32)&bottom);
        func_800498C4();
        func_800496A4(8, 0);
        func_8004972C(255, 255, 255, 255);
        if (name != NULL) {
            func_800495BC(160, 160, buffer);
        } else {
            func_800495BC(160, 160, buffer);
        }
        func_800499EC();
    }
}
#endif

#ifdef VERSION_US
void func_82001304(void) {
    func_800498C4();
    if (D_82001CD4 != 0) {
        Fragment16_DrawVersionStamp();
    }
    func_800499EC();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82001344.s")
#endif

#ifdef VERSION_US
extern void *D_82001CD0;
extern s32 D_82001EC4;
extern s32 D_82001EC8;
extern s32 func_8006D268(s32);
extern void BgStage_DrawFrame(void);
extern void func_800503A4(void *);
extern void Fragment16_DrawFadingOverlay(void);
extern void func_82001344(void);
extern void Fragment16_DrawSelectionList(void);
extern void Fragment16_DrawSelectionPopup(void);
extern void func_82001304(void);
extern void func_80008648(void);
extern void func_820006B8(void);
void func_820014C4(void) {
    BgStage_DrawFrame();
    if (func_8006D268(0x202) != 0 && ((*(u16 *)((u8 *)(u32)D_80087200 + 8)) & 4) != 0) {
        (*(s16 *)((u8 *)&D_82001D58 + 4)) =
            (s16)((*(s16 *)((u8 *)&D_82001D58 + 4) + 1) % 3);
    }
    func_820006B8();
    func_800503A4(D_82001CD0);
    Fragment16_DrawFadingOverlay();
    func_82001344();
    if (D_82001EC4 != 0) {
        Fragment16_DrawSelectionList();
    }
    if (D_82001EC8 != 0) {
        Fragment16_DrawSelectionPopup();
    }
    func_82001304();
    func_80008648();
}
#endif

#ifdef VERSION_US
s32 Fragment16_HandleSelectionInput(void) {
    s32 result = 0;
    s32 previousSelection = D_82001EB0;
    if ((*(u16 *)((u8 *)D_80087200 + 0xC)) & 0x200) {
        D_82001EB0--;
        if (D_82001EB0 < 0) {
            D_82001EB0 = D_82001EB4 - 1;
        }
    }
    if ((*(u16 *)((u8 *)D_80087200 + 0xC)) & 0x100) {
        D_82001EB0++;
        if (D_82001EB0 >= D_82001EB4) {
            D_82001EB0 = 0;
        }
    }
    if (previousSelection != D_82001EB0) {
        func_800226C0(1);
    }
    if ((*(u16 *)((u8 *)D_80087200 + 8)) & 0x8000) {
        result = 1;
        func_800226C0(2);
    }
    if ((*(u16 *)((u8 *)D_80087200 + 8)) & 0x4000) {
        result = -1;
        func_800226C0(3);
    }
    return result;
}
#endif

#ifdef VERSION_US
extern s32 func_80025D44(void);
s32 func_82001688(void) {
    s32 result = 0;
    if (func_80025D44() == 0) {
        result = 1;
    } else if (func_8006D268(0x201) != 0 && ((*(u16 *)((u8 *)(u32)D_80087200 + 8)) & 2) != 0) {
        result = 1;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_820016EC.s")
#endif

#ifdef VERSION_US
s32 func_8200180C(void) {
    s32 result = 0;
    if (D_82001D58 == 0) result = 1;
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_8200182C.s")
#endif

#ifdef VERSION_US
extern void func_82000100();
extern void func_82000794();
extern void func_820014C4();
s32 func_8200182C(s32);
extern s32 D_82001D50;
void func_820019EC(void) {
    s32 temp_v0;
    s32 var_s1;

    var_s1 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(0xA);
    do {
        func_80064D28();
        func_82000100();
        func_82000794();
        func_820014C4();
        if (D_82001D50 != 0) {
            D_82001D50 -= 1;
        }
        temp_v0 = func_8200182C(var_s1);
        var_s1 = temp_v0;
    } while (temp_v0 != 6);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82001A78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82001ADC.s")
#endif
