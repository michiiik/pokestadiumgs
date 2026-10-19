#include "global.h"

#ifdef VERSION_US
typedef struct LabPCTransferItem {
    u8 type;
    u8 count;
} LabPCTransferItem;

// The midpoint transfers count between columns and updates the source item.
typedef struct LabPCQuantityMotion {
    LabPCTransferItem *item;
    s8 rows[2];
    u8 source_column;
    u8 counts[2];
} LabPCQuantityMotion;

// Lists are exchanged at the midpoint; row -1 suppresses a column highlight.
typedef struct LabPCListSwapMotion {
    void *lists[2];
    s8 rows[2];
    u8 column;
} LabPCListSwapMotion;

extern void *D_8800EF54;
extern u8 D_8800EF50[];
extern u8 D_88234934;
extern void func_88230E38(void);
extern void func_88230D80(s16 *, s16 *);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_8820F74C(s16, s16, u8 *, u8);
extern void func_8820AAD0(s16, s16, void *);
extern void func_88201CF4(void *, void *);
extern u32 func_8820030C(u32 *, u32 *);
extern Gfx *D_800D0510;

void LabPC_DrawQuantityTransferHighlights(void) {
    s32 i;
    s16 x;
    s16 y;
    LabPCQuantityMotion *motion = D_8800EF54;

    func_88230E38();
    for (i = 0; i != 2; i++) {
        x = i * 311 + 52;
        y = motion->rows[i] * 27 + 125;
        gDPFillRectangle(D_800D0510++, x, y, x + 223, y + 26);
    }
}

void LabPC_DrawQuantityTransferEntries(void) {
    LabPCQuantityMotion *motion = *(LabPCQuantityMotion **)(D_8800EF50 + 4);
    s32 i;
    s16 half;
    s16 alpha;
    s16 x;
    s16 y;

    func_88230D80(&half, &alpha);
    if (half >= *(s16 *)(D_8800EF50 + 8)) {
        alpha = -alpha;
        if (half == *(s16 *)(D_8800EF50 + 8)) {
            motion->counts[motion->source_column] -= D_88234934;
            motion->counts[1 - motion->source_column] += D_88234934;
            motion->item->count = motion->counts[motion->source_column];
        }
    }
    func_8004972C(255, 255, 255, alpha);
    for (i = 0; i != 2; i++) {
        if (motion->counts[i] != 0) {
            x = i * 311 + 58;
            y = motion->rows[i] * 27 + 128;
            func_8820F74C(x, y, (u8 *)motion->item, motion->counts[i]);
        }
    }
}

extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
extern void func_8820CE2C(void);
void func_88231AE8(void) {
    func_88005B60(5, LabPC_DrawQuantityTransferHighlights, LabPC_DrawQuantityTransferEntries, func_8820CE2C);
}

void LabPC_DrawListSwapHighlights(void) {
    s32 i;
    s16 x;
    s16 y;
    LabPCListSwapMotion *motion = D_8800EF54;

    func_88230E38();
    for (i = 0; i != 2; i++) {
        if (motion->rows[i] != -1) {
            x = motion->column * 297 + 71;
            y = motion->rows[i] * 27 + 125;
            gDPFillRectangle(D_800D0510++, x, y, x + 197, y + 26);
        }
    }
}

void LabPC_DrawListSwapEntries(void) {
    s32 i;
    s16 half;
    s16 alpha;
    s16 x;
    s16 y;
    LabPCListSwapMotion *motion = *(LabPCListSwapMotion **)(D_8800EF50 + 4);

    func_88230D80(&half, &alpha);
    if (half >= *(s16 *)(D_8800EF50 + 8)) {
        alpha *= -1;
        if (half == *(s16 *)(D_8800EF50 + 8)) {
            func_88201CF4(motion->lists[0], motion->lists[1]);
            func_8820030C((u32 *)&motion->lists[0], (u32 *)&motion->lists[1]);
        }
    }
    func_8004972C(255, 255, 255, alpha);
    for (i = 0; i != 2; i++) {
        if (motion->rows[i] != -1) {
            x = motion->column * 297 + 77;
            y = motion->rows[i] * 27 + 128;
            func_8820AAD0(x, y, (u8 *)motion->lists[i] + 8);
        }
    }
}

extern void func_8820908C(void);
void func_88231D30(void) {
    func_88005B60(6, LabPC_DrawListSwapHighlights, LabPC_DrawListSwapEntries, func_8820908C);
}
#endif
