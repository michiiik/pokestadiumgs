#include "global.h"

#ifdef VERSION_US
typedef struct LabPCRecordTransferMotion {
    s8 *entries[2];
    s8 rows[2];
    u8 columns[2];
} LabPCRecordTransferMotion;

// func_882009D4 uses these count/capacity/data/changed fields at a 12-byte stride.
//@src/fragments/31/fragment31_1736F0.c
typedef struct LabPCStorageList {
    u8 count;
    u8 capacity;
    void *entries;
    s32 changed;
} LabPCStorageList;

extern void *D_8800EF54;
extern u8 D_8800EF50[];
extern Gfx *D_800D0510;
extern u8 D_88234630[];
extern void *D_882345F4;
extern void func_88230E38(void);
extern void func_88230D80(s16 *, s16 *);
extern void func_8004972C(s32, s32, s32, s32);
extern u32 func_88200458(u32 *, u32 *);
extern void func_88200320(void *, void *);
extern void *func_8820137C(void *);
extern void func_882158E4(s16, s16, s8 *);

void LabPC_DrawRecordTransferHighlights(void) {
    s32 i;
    s16 x;
    s16 y;
    LabPCRecordTransferMotion *motion = D_8800EF54;

    func_88230E38();
    for (i = 0; i != 2; i++) {
        if (motion->rows[i] != -1) {
            x = motion->columns[i] * 311 + 52;
            y = motion->rows[i] * 27 + 125;
            gDPFillRectangle(D_800D0510++, x, y, x + 223, y + 26);
        }
    }
}

void LabPC_DrawRecordTransferEntries(void) {
    s32 i;
    s16 half;
    s16 alpha;
    s16 x;
    s16 y;
    LabPCRecordTransferMotion *motion = *(LabPCRecordTransferMotion **)(D_8800EF50 + 4);

    func_88230D80(&half, &alpha);
    if (half >= *(s16 *)(D_8800EF50 + 8)) {
        if (*(s32 *)D_8800EF50 == 18) {
            return;
        }
        alpha *= -1;
        if (half == *(s16 *)(D_8800EF50 + 8)) {
            switch (*(s32 *)D_8800EF50) {
            case 15:
                func_88200458((u32 *)&motion->entries[0], (u32 *)&motion->entries[1]);
                break;
            case 16:
            case 17:
                func_88200320(motion->entries[0], motion->entries[1]);
                for (i = 0; i != 2; i++) {
                    ((LabPCStorageList *)D_88234630)[motion->columns[i] * 2 + 1].changed = 1;
                }
                break;
            case 19:
                motion->entries[0] = func_8820137C(D_882345F4);
                break;
            }
        }
    }
    func_8004972C(255, 255, 255, alpha);
    for (i = 0; i != 2; i++) {
        if (motion->rows[i] != -1 && motion->entries[i] != NULL) {
            x = motion->columns[i] * 311 + 58;
            y = motion->rows[i] * 27 + 128;
            func_882158E4(x, y, motion->entries[i]);
        }
    }
}

extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
extern void func_88213E9C(void);
void func_88232E30(s32 arg0) {
    func_88005B60(arg0, LabPC_DrawRecordTransferHighlights, LabPC_DrawRecordTransferEntries, func_88213E9C);
}
#endif
