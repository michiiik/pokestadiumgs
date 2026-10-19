#include "global.h"


#ifdef VERSION_US
extern void func_800226C0(s32);
extern s32 func_8821C0B0(void);
extern void func_8822AF00(void *);
extern void func_88001900(void);
extern u8 *D_882345F4;
extern s32 D_880068B4;
void func_88232E70(void) {
    func_800226C0(0x60);
    if (func_8821C0B0() == 0) {
        func_8822AF00(D_882345F4 + 0x3C);
    } else {
        func_88001900();
        D_880068B4 = 1;
    }
}

typedef struct LabPCMoveFieldMotion {
    u8 *entry;
    // Move-slot index chosen by func_88902B70, or the replacement-slot cursor.
    //@src/fragments/38/fragment38_1D8160.c
    s8 field;
} LabPCMoveFieldMotion;
extern void *D_8800EF54;
extern Gfx *D_800D0510;
extern u8 D_88006880[];
extern s16 D_88006890;
extern s16 D_8800EF58;
extern s8 D_889041A0;
extern u8 D_88234746;
extern u8 *D_88234620;
extern s32 func_88216D98(s8, s8);
extern s32 func_88216E28(s8, s8);
extern void func_88230E38(void);
extern void func_88230D80(s16 *, s16 *);
extern void func_800496A4(s32, s32);
extern void func_882033B0(void *, void *);
extern void func_88217F70(s16, s16, u8, u8);
extern s32 func_88902B70(u8 *);
extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
extern void *Util_Malloc(s32);

extern void LabPC_DrawMoveFieldHighlight(void);
extern void LabPC_DrawMoveFieldValue(void);

// Coordinate prefix; func_8800225C updates y from the active row and row height.
//@src/fragments/29/fragment29_167940.c
typedef struct LabPCWindowCoordinates {
    u8 unk_00[16];
    s16 y;
} LabPCWindowCoordinates;
void LabPC_DrawMoveFieldHighlight(void) {
    LabPCMoveFieldMotion *motion = D_8800EF54;
    s8 field;
    s16 x;

    field = motion->field + 2;
    x = func_88216D98(2, field);
    func_88230E38();
    gDPFillRectangle(D_800D0510++, x, ((LabPCWindowCoordinates *)D_88006880)->y,
        x + func_88216E28(2, field), ((LabPCWindowCoordinates *)D_88006880)->y + 20);
}

void LabPC_DrawMoveFieldValue(void) {
    LabPCMoveFieldMotion *motion = D_8800EF54;
    s8 field;
    s16 half;
    s16 alpha;
    s16 x;

    field = motion->field + 2;
    func_88230D80(&half, &alpha);
    func_800496A4(4, 0);
    if (half >= D_8800EF58) {
        alpha = -alpha;
        if (half == D_8800EF58) {
            func_882033B0(D_882345F4, D_88234620);
        }
    }
    x = func_88216D98(2, field);
    func_88217F70(x, D_88006890,
        motion->entry[motion->field + 10], alpha);
}

extern void func_88232E70(void);
void LabPC_StartMoveFieldAnimation(void) {
    LabPCMoveFieldMotion *motion;
    u8 selected;

    selected = func_88902B70(D_882345F4 + 8);
    func_800226C0(99);
    func_88005B60(20, LabPC_DrawMoveFieldHighlight, LabPC_DrawMoveFieldValue, func_88232E70);
    motion = Util_Malloc(sizeof(*motion));
    motion->entry = D_882345F4;
    motion->field = selected < 4 ? selected : D_889041A0;
    D_8800EF54 = motion;
    D_88234746 = 2;
}
#endif
