#include "global.h"

#ifdef VERSION_US
extern void func_800226C0(s32);
extern void func_88220AD0(s32, s32);
extern s32 D_88234660;
void func_8821C298(void);
void func_88001900(void);
extern s32 D_880068B4;
void func_88232860(void) {
    func_800226C0(0x5E);
    func_8821C298();
    if (D_88234660 != 0) {
        func_88220AD0(0x17C, 0x11F);
        return;
    }
    func_88001900();
    D_880068B4 = 1;
}

typedef struct LabPCFieldSwapMotion {
    u8 *entries[2];
    s8 rows[2];
} LabPCFieldSwapMotion;

extern void *D_8800EF54;
extern u8 D_8800EF50[];
extern Gfx *D_800D0510;
extern u8 *D_8800687C;
extern s32 func_88216D98(s8, s8);
extern s32 func_88216E28(s8, s8);
extern void func_88230E38(void);
extern void func_88230D80(s16 *, s16 *);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_88201A74(void *, void *);
extern u8 func_882002F8(u8 *, u8 *);
extern s32 *func_800635E0(u8);
extern s32 func_80048E30(u8 *, s32, s32, const char *, s32);

void LabPC_DrawFieldSwapHighlights(void) {
    s32 i;
    s16 x;
    s16 y;
    s16 width;
    LabPCFieldSwapMotion *motion;

    x = func_88216D98(3, 5);
    width = func_88216E28(3, 5);
    motion = D_8800EF54;
    func_88230E38();
    for (i = 0; i != 2; i++) {
        if (motion->rows[i] != -1) {
            y = motion->rows[i] * 20 + 147;
            gDPFillRectangle(D_800D0510++, x, y, x + width, y + 20);
        }
    }
}

void LabPC_DrawFieldSwapLabels(void) {
    s32 i;
    s16 x;
    s16 half;
    s16 alpha;
    u8 field;
    LabPCFieldSwapMotion *motion;

    x = func_88216D98(3, 5);
    motion = *(LabPCFieldSwapMotion **)(D_8800EF50 + 4);
    func_88230D80(&half, &alpha);
    func_800496A4(4, 1);
    if (half >= *(s16 *)(D_8800EF50 + 8)) {
        alpha *= -1;
        if (half == *(s16 *)(D_8800EF50 + 8)) {
            func_88201A74(motion->entries[0], motion->entries[1]);
            func_882002F8(motion->entries[0] + 9, motion->entries[1] + 9);
            *(s32 *)(*(u8 **)motion->entries[1] + 12) = 1;
            *(s32 *)(*(u8 **)motion->entries[0] + 12) = *(s32 *)(*(u8 **)motion->entries[1] + 12);
        }
    }
    func_8004972C(255, 255, 255, alpha);
    for (i = 0; i != 2; i++) {
        if (motion->rows[i] != -1) {
            field = motion->entries[i][9];
            if ((motion->entries[i][38] & 1) == 0 && field != 0) {
                func_80048E30(D_8800687C, x + 5, motion->rows[i] * 20 + 149,
                    (const char *)func_800635E0(field), 1);
            }
        }
    }
}

extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
void func_88232B50(void) {
    func_88005B60(0xE, LabPC_DrawFieldSwapHighlights, LabPC_DrawFieldSwapLabels, func_88232860);
}
#endif
