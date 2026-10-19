#include "global.h"

#ifdef VERSION_US
typedef struct LabPCAnimationPair {
    u8 first;
    u8 second;
} LabPCAnimationPair;

typedef struct LabPCPairMotion {
    LabPCAnimationPair *entries[2];
    s8 rows[2];
    u8 column;
} LabPCPairMotion;

extern void *D_8800EF54;
extern u8 D_8800EF50[];
extern Gfx *D_800D0510;
extern void func_88230E38(void);
extern void func_88230D80(s16 *, s16 *);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_8820F74C(s16, s16, u8 *, u8);
extern s32 D_882346F0;
extern void func_800226C0(s32);
extern void func_88001900(void);
void func_88231430(void) { func_800226C0(94); func_88001900(); D_882346F0 = 0; }

void LabPC_DrawInColumnSwapHighlights(void) {
    s32 i;
    s16 x;
    s16 y;
    LabPCPairMotion *motion = D_8800EF54;

    func_88230E38();
    for (i = 0; i != 2; i++) {
        if (motion->rows[i] != -1) {
            x = motion->column * 311 + 52;
            y = motion->rows[i] * 27 + 125;
            gDPFillRectangle(D_800D0510++, x, y, x + 223, y + 26);
        }
    }
}

void LabPC_DrawInColumnSwapEntries(void) {
    LabPCPairMotion *motion = *(LabPCPairMotion **)(D_8800EF50 + 4);
    s32 i;
    s16 half;
    s16 alpha;
    s16 x;
    s16 y;
    LabPCAnimationPair saved;

    func_88230D80(&half, &alpha);
    if (half >= *(s16 *)(D_8800EF50 + 8)) {
        alpha *= -1;
        if (half == *(s16 *)(D_8800EF50 + 8)) {
            saved = *motion->entries[0];
            *motion->entries[0] = *motion->entries[1];
            *motion->entries[1] = saved;
        }
    }
    func_8004972C(255, 255, 255, alpha);
    for (i = 0; i != 2; i++) {
        if (motion->rows[i] != -1) {
            x = motion->column * 311 + 58;
            y = motion->rows[i] * 27 + 128;
            func_8820F74C(x, y, (u8 *)motion->entries[i], motion->entries[i]->second);
        }
    }
}

extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
void func_88231698(void) {
    func_88005B60(3, LabPC_DrawInColumnSwapHighlights, LabPC_DrawInColumnSwapEntries, func_88231430);
}

void LabPC_DrawCrossColumnSwapHighlights(void) {
    s32 i;
    s16 x;
    s16 y;
    LabPCPairMotion *motion = D_8800EF54;

    func_88230E38();
    for (i = 0; i != 2; i++) {
        x = i * 311 + 52;
        y = motion->rows[i] * 27 + 125;
        gDPFillRectangle(D_800D0510++, x, y, x + 223, y + 26);
    }
}

void LabPC_DrawCrossColumnSwapEntries(void) {
    LabPCPairMotion *motion = *(LabPCPairMotion **)(D_8800EF50 + 4);
    s32 i;
    s16 half;
    s16 alpha;
    s16 x;
    s16 y;
    LabPCAnimationPair saved;

    func_88230D80(&half, &alpha);
    if (half >= *(s16 *)(D_8800EF50 + 8)) {
        alpha = -alpha;
        if (half == *(s16 *)(D_8800EF50 + 8)) {
            saved = *motion->entries[0];
            *motion->entries[0] = *motion->entries[1];
            *motion->entries[1] = saved;
        }
    }
    func_8004972C(255, 255, 255, alpha);
    for (i = 0; i != 2; i++) {
        x = i * 311 + 58;
        y = motion->rows[i] * 27 + 128;
        func_8820F74C(x, y, (u8 *)motion->entries[i], motion->entries[i]->second);
    }
}

extern void func_8820CE2C(void);
void func_882318B0(void) {
    func_88005B60(4, LabPC_DrawCrossColumnSwapHighlights, LabPC_DrawCrossColumnSwapEntries, func_8820CE2C);
}
#endif
