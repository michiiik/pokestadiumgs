#include "global.h"

#ifdef VERSION_US
typedef struct LabPCListFadeMotion {
    void *list;
    s8 row;
    u8 column;
} LabPCListFadeMotion;

typedef struct LabPCListExchangeMotion {
    void *lists[2];
    s8 rows[2];
    u8 columns[2];
} LabPCListExchangeMotion;

extern void *D_8800EF54;
extern Gfx *D_800D0510;
extern s16 D_8800EF58;
extern void func_88230E38(void);
extern void func_88230D80(s16 *, s16 *);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_8820AAD0(s16, s16, void *);

void LabPC_DrawListFadeHighlights(void) {
    s16 x;
    s16 y;
    LabPCListFadeMotion *motion = D_8800EF54;

    func_88230E38();
    x = motion->column * 297 + 71;
    y = motion->row * 27 + 125;
    gDPFillRectangle(D_800D0510++, x, y, x + 197, y + 26);
}

void LabPC_DrawListFadeEntry(void) {
    s16 half;
    s16 alpha;
    LabPCListFadeMotion *motion = D_8800EF54;

    func_88230D80(&half, &alpha);
    if (half < D_8800EF58) {
        func_8004972C(255, 255, 255, alpha);
        func_8820AAD0((s16)(motion->column * 297 + 77), (s16)(motion->row * 27 + 128), (u8 *)motion->list + 8);
    }
}

extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
extern void func_8820908C(void);
void func_882322B8(void) {
    func_88005B60(9, LabPC_DrawListFadeHighlights, LabPC_DrawListFadeEntry, func_8820908C);
}

void LabPC_MarkUnflaggedListEntries(u8 *state) {
    u8 **entry = *(u8 ***)(state + 16);
    u32 i;

    for (i = 0; i < state[21]; i++, entry++) {
        if ((((*entry)[38] & 1) != 0) == 0) {
            (*entry)[36] = 70;
        }
    }
}

void LabPC_DrawListExchangeHighlights(void) {
    s32 i;
    s16 x;
    s16 y;
    LabPCListExchangeMotion *motion = D_8800EF54;

    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, 0x2AFF2AFF);
    for (i = 0; i != 2; i++) {
        if (motion->rows[i] != -1) {
            x = motion->columns[i] * 311 + 52;
            y = motion->rows[i] * 27 + 125;
            gDPFillRectangle(D_800D0510++, x, y, x + 222, y + 25);
        }
    }
}

void LabPC_SetListExchangeAlphaCompare(u8 alpha) {
    gDPPipeSync(D_800D0510++);
    if (alpha == 255) {
        gDPSetAlphaCompare(D_800D0510++, G_AC_NONE);
    } else {
        gDPSetAlphaCompare(D_800D0510++, G_AC_DITHER);
    }
    func_8004972C(255, 255, 255, alpha);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A53B0/func_882324D4.s")

extern void func_882324D4(void);
extern void func_882114EC(void);
void func_88232820(s32 arg0) {
    func_88005B60(arg0, LabPC_DrawListExchangeHighlights, func_882324D4, func_882114EC);
}
#endif
