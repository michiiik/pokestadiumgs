#include "global.h"

#ifdef VERSION_US
typedef struct LabPCCrossListMove {
    void *list;
    s8 rows[2];
    u8 column;
} LabPCCrossListMove;

extern void *D_8800EF54;
extern s16 D_8800EF58;
extern Gfx *D_800D0510;
extern void func_88230E38(void);
extern void func_88230D80(s16 *, s16 *);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_8820AAD0(s16, s16, void *);

void LabPC_DrawCrossColumnListMoveHighlights(void) {
    s32 i;
    s16 x;
    s16 y;
    LabPCCrossListMove *motion = D_8800EF54;

    func_88230E38();
    for (i = 0; i != 2; i++) {
        x = i * 297 + 71;
        y = motion->rows[i] * 27 + 125;
        gDPFillRectangle(D_800D0510++, x, y, x + 197, y + 26);
    }
}

void LabPC_DrawCrossColumnListMoveEntry(void) {
    s16 x;
    s16 y;
    s16 half;
    s16 alpha;
    LabPCCrossListMove *motion = D_8800EF54;

    func_88230D80(&half, &alpha);
    if (half >= D_8800EF58) {
        alpha = -alpha;
        if (half == D_8800EF58) {
            motion->column ^= 1;
        }
    }
    func_8004972C(255, 255, 255, alpha);
    x = motion->column * 297 + 77, y = motion->rows[motion->column] * 27 + 128;
    func_8820AAD0(x, y, (u8 *)motion->list + 8);
}

extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
extern void func_8820908C(void);
void func_882320F0(void) {
    func_88005B60(8, LabPC_DrawCrossColumnListMoveHighlights, LabPC_DrawCrossColumnListMoveEntry, func_8820908C);
}
#endif
