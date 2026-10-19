#include "global.h"

#ifdef VERSION_US
typedef struct LabPCCrossListSwap {
    void *lists[2];
    s8 rows[2];
} LabPCCrossListSwap;

extern void *D_8800EF54;
extern u8 D_8800EF50[];
extern Gfx *D_800D0510;
extern void func_88230E38(void);
extern void func_88230D80(s16 *, s16 *);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_8820AAD0(s16, s16, void *);
extern void func_88201CF4(void *, void *);
extern u32 func_8820030C(u32 *, u32 *);

void LabPC_DrawCrossColumnListSwapHighlights(void) {
    s32 i;
    s16 x;
    s16 y;
    LabPCCrossListSwap *motion = D_8800EF54;

    func_88230E38();
    for (i = 0; i != 2; i++) {
        x = i * 297 + 71;
        y = motion->rows[i] * 27 + 125;
        gDPFillRectangle(D_800D0510++, x, y, x + 197, y + 26);
    }
}

void LabPC_DrawCrossColumnListSwapEntries(void) {
    s32 i;
    s16 half;
    s16 alpha;
    s16 x;
    s16 y;
    LabPCCrossListSwap *motion = *(LabPCCrossListSwap **)(D_8800EF50 + 4);

    func_88230D80(&half, &alpha);
    if (half >= *(s16 *)(D_8800EF50 + 8)) {
        alpha = -alpha;
        if (half == *(s16 *)(D_8800EF50 + 8)) {
            func_88201CF4(motion->lists[0], motion->lists[1]);
            func_8820030C((u32 *)&motion->lists[0], (u32 *)&motion->lists[1]);
        }
    }
    func_8004972C(255, 255, 255, alpha);
    for (i = 0; i != 2; i++) {
        x = i * 297 + 77;
        y = motion->rows[i] * 27 + 128;
        func_8820AAD0(x, y, (u8 *)motion->lists[i] + 8);
    }
}

extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
extern void func_8820908C(void);
void func_88231F24(void) {
    func_88005B60(7, LabPC_DrawCrossColumnListSwapHighlights, LabPC_DrawCrossColumnListSwapEntries, func_8820908C);
}
#endif
