#include "global.h"


#ifdef VERSION_US
extern void func_80049064(s16, s16, s32, s32);
extern void func_800496A4(s32, s32);
extern void func_8004989C(s32);
extern void func_800498C4(void);
extern void func_800499EC(void);
extern s32 func_88902B70(u8 *);
void func_889033A0(void *arg0) {
    func_800498C4();
    func_800496A4((*(s32 *)((u8 *)(arg0) + (0x10))), (*(s16 *)((u8 *)(arg0) + (0x14))));
    func_8004989C(0x1A);
    func_80049064((*(s16 *)((u8 *)(arg0) + (0))), (*(s16 *)((u8 *)(arg0) + (2))), (*(s32 *)((u8 *)(arg0) + (4))), *(*(s32 **)((u8 *)(arg0) + (8))));
    func_800499EC();
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
typedef struct LabPCChoiceDialog {
    u8 *window;
    LabPCTextList layout;
    u8 *strings[2];
    s32 result;
} LabPCChoiceDialog;
typedef struct LabPCMessageDialog {
    u8 *window;
    LabPCTextList layout;
    u8 *text;
    s8 title[512];
    s32 *done;
    s32 *cancel;
    void (*callback)(void);
} LabPCMessageDialog;
extern s32 func_800472B8(s32);
extern void func_88002820(s16,s16,s8,u8 **,u16,s16,LabPCTextMask *);
extern void func_880009A8(s32,s16,s16,s16,s16,s16,s16);
extern void *func_8004C874(s32,s32);
extern u8 *func_88002AA8(u8 *,s32,u8 **,u16,s32,s16,s16,s16,s16,s16,s16,s32,s16,void *);
extern u8 func_88004804(s32,s32,s16,s16,s32,s32,u8,u8,u8,s32 *,s32 *,s32 *,s32 *,u8,u8);
extern s8 *HAL_Strcpy(s8 *,s8 *);
extern void *Util_Malloc(s32);
extern void Util_Free(s32);
extern void Input_SetRepeatController(s32);
extern void func_88001900(void);
extern u8 D_88006020[];
extern u8 D_8800ED50[];
extern u8 *D_889041B0;
extern u8 D_889041B8;
extern s32 D_889041B4;
extern void *D_80087200;
extern void func_88903BB4(void);
extern void func_88903C28(void);
extern void LabPC_CloseMessageDialog(void);
void LabPC_DrawSelectableTextList(void *parent, LabPCTextList *list) {
    u8 height = func_800472B8(list->font);

    func_800498C4();
    func_800496A4(list->font, list->spacing_x);
    func_88002820(list->x,list->y,list->align,list->strings,list->count,list->spacing_y,&list->mask);
    func_800499EC();
    func_880009A8(*(s32 *)((u8 *)parent + 44),
        *(s16 *)((u8 *)parent + 12) + list->left,
        *(s16 *)((u8 *)parent + 14) + list->top + list->selected * (height + list->spacing_y), list->width, height, 8, 6);
}

void LabPC_InitTwoChoiceDialog(LabPCChoiceDialog *dialog) {
    s32 i;

    for (i = 0; i < 2; i++) {
        dialog->strings[i] = func_8004C874(69, i);
    }
    func_88002AA8((u8 *)&dialog->layout,0,dialog->strings,2,8,1,6,15,16,13,16,0,0,D_88006020);
    dialog->result = 0;
}

void func_889035A0(void *arg0, u8 *arg1, s16 arg2, s16 arg3) {
    (*(s16 *)((u8 *)(arg0) + (4))) = arg2;
    (*(s16 *)((u8 *)(arg0) + (6))) = arg3;
    (*(u8 **)((u8 *)(arg0) + (8))) = arg1;
    (*(s16 *)((u8 *)(arg0) + (0xC))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0xE))) = func_88902B70(arg1);
    (*(s32 *)((u8 *)(arg0) + (0x10))) = 0;
}

typedef struct LabPCMoveDetails {
    u8 *window;
    s16 x, y;
    u8 *pokemon;
    s16 selected;
    u8 count;
    u8 unk_0F;
    s32 state;
} LabPCMoveDetails;
typedef struct LabPCMoveDetailsColor {
    u8 red, green, blue;
} LabPCMoveDetailsColor;
extern Gfx *D_800D0510;
extern Gfx D_80094DE0[];
extern u8 D_88005FA0[];
extern u8 *D_8800687C;
extern const char D_88904170[];
extern const char D_88904178[];
extern const char D_88904180[];
extern const char D_88904188[];
extern void func_880008B0(s16,s16,s16);
extern void func_880006BC(u8 *);
extern void func_880006E0(void *);
extern LabPCMoveDetailsColor *func_88000510(LabPCMoveDetailsColor *,s8);
extern u8 func_80062D98(u8);
extern u8 func_80062D5C(u8);
extern u8 func_80062DD4(u8);
extern s32 *func_80062CE0(u8);
extern s32 func_80063270(u8);
extern u8 func_80062EB0(u8,u8);
extern s32 func_80048E30(u8 *,s32,s32,const char *,s32);
extern void func_800495F8(s32,s32,s32,const char *,...);
extern s32 func_80049290(s32,s32,const char *);
extern void func_88002BA0(u8,u8,u8);
extern s32 func_8004D334(s32,s32);
extern void func_8004D40C(s32);
extern void func_8004D5B8(s32,s32,s32,const char *,...);
void LabPC_DrawMoveDetails(LabPCMoveDetails *pane) {
    u32 i;
    const char *header;
    const char *names[4];
    LabPCMoveDetailsColor color;
    s8 type;
    s16 x;
    s16 y;
    u8 value;
    u8 move;

    header = func_8004C874(69, 2);
    gSPDisplayList(D_800D0510++, D_80094DE0);
    func_880008B0(pane->x + 354, pane->y + 269, 157);
    func_800498C4();
    func_880006BC(D_88005FA0);
    func_800496A4(8, 1);
    y = pane->y + 165;
    for (i = 0; i < pane->count; i++, y += 26) {
        move = pane->pokemon[i + 2];
        func_880006E0(func_88000510(&color, move == 252 ? 0 : func_80062D98(move)));
        names[i] = move == 252 ? func_8004C874(69, 19) : (const char *)func_80062CE0(move);
        func_80048E30(D_8800687C, pane->x + 354, y, names[i], 1);
    }
    func_880006E0(D_88005FA0);
    func_800496A4(4, 0);
    x = pane->x + 354;
    y = pane->y + 277;
    func_80048E30(D_8800687C, x, y, header, 1);
    move = pane->pokemon[pane->selected + 2];
    if (move != 252) {
        value = func_80062D5C(move);
        y += 20;
        if (value == 0 || value == 1) {
            func_800495F8(x, y, 0, D_88904170, func_8004C874(69, 3), func_8004C874(69, 5));
        } else {
            func_800495F8(x, y, 0, D_88904178, func_8004C874(69, 3), value);
        }
        y += 20;
        func_800495F8(x, y, 0, D_88904180, func_8004C874(69, 4),
            (s32)((func_80062DD4(move) * 100) / 255.0f +
                (0.0f < (func_80062DD4(move) * 100) / 255.0f ? 0.5f : -0.5f)));
        type = func_80062D98(move);
        func_880006E0(func_88000510(&color, type));
    }
    func_80048E30(D_8800687C, x + *(s8 *)(D_8800687C + 120) + func_80049290(0, *(s8 *)(D_8800687C + 120), header), pane->y + 277,
        (const char *)func_80063270(move == 252 ? 19 : type), 1);
    func_88002BA0(255,255,255);
    func_8004D334(239,0);
    func_8004D40C(1);
    y = pane->y + 171;
    for (i = 0; i < pane->count; i++, y += 26) {
        if (pane->pokemon[i + 2] != 252) {
            func_8004D5B8(pane->x + 494, y, 0, D_88904188,
                func_80062EB0(pane->pokemon[i + 2], pane->pokemon[i + 24]) & 63);
        }
    }
    func_880009A8(*(s32 *)(pane->window + 44), pane->x + 354,
        pane->y + pane->selected * 26 + 165, 157, 20, 6, 6);
}

extern s32 D_880068B8;
void func_88903B00(void) {
    s32 *temp_v0;

    temp_v0 = (*(s32 **)((u8 *)(D_889041B0) + (0x240)));
    if (temp_v0 == NULL) {
        D_880068B8 = 0;
        return;
    }
    *temp_v0 = 0;
}

void LabPC_CloseMessageDialog(void) {
    void (*callback)(void);
    LabPCMessageDialog *dialog;

    Input_SetRepeatController((s32)D_80087200);
    func_88001900();
    dialog = (LabPCMessageDialog *)D_889041B0;
    {
        s32 *done = dialog->done;
        if (done != NULL) {
            *done = 1;
        }
        dialog = (LabPCMessageDialog *)D_889041B0;
    }
    if (dialog->cancel == NULL) {
        D_889041B8 = 2;
        D_889041B4 = 0;
    }
    callback = dialog->callback;
    Util_Free((s32)dialog);
    callback();
}

extern void func_88004990(u8, s32);
void func_88903BB4(void) {
    s32 *temp_v0;

    if ((*(u16 *)((u8 *)(D_80087200) + (8))) & 0xC000) {
        func_88004990(*(*(u8 **)((u8 *)(D_889041B0) + (0))), 0);
        temp_v0 = (*(s32 **)((u8 *)(D_889041B0) + (0x240)));
        if (temp_v0 != NULL) {
            *temp_v0 = 1;
            return;
        }
        D_880068B8 = 1;
    }
}

extern void func_889033A0(void *arg0);
void func_88903C28(void) {
    func_889033A0(D_889041B0 + 4);
}

void LabPC_OpenMessageDialog(s8 *title,s16 x,s16 y,s32 style,u8 red,u8 green,u8 blue,u8 delay,u8 kind,s32 *done,s32 *cancel,s32 *extra,void (*callback)(void)) {

    D_889041B0 = Util_Malloc(sizeof(LabPCMessageDialog));
    ((LabPCMessageDialog *)D_889041B0)->done = done;
    ((LabPCMessageDialog *)D_889041B0)->cancel = cancel;
    HAL_Strcpy(((LabPCMessageDialog *)D_889041B0)->title,title);
    ((LabPCMessageDialog *)D_889041B0)->text = (u8 *)((LabPCMessageDialog *)D_889041B0)->title;
    func_88002AA8((u8 *)&((LabPCMessageDialog *)D_889041B0)->layout,0,&((LabPCMessageDialog *)D_889041B0)->text,1,8,1,6,15,18,13,16,0,0,D_88006020);
    ((LabPCMessageDialog *)D_889041B0)->window = D_8800ED50 + func_88004804((s32)&((LabPCMessageDialog *)D_889041B0)->layout,0,x,y,style,1,red,green,blue,(s32 *)func_88903BB4,(s32 *)func_88903C28,extra,(s32 *)LabPC_CloseMessageDialog,delay,kind) * 76;
    ((LabPCMessageDialog *)D_889041B0)->callback = callback;
    if (done != NULL) {
        *done = 0;
    }
    if (((LabPCMessageDialog *)D_889041B0)->cancel == NULL) {
        D_880068B8 = 1;
        D_889041B4 = 4;
    }
}
#endif
