#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A6360/func_882330E0.s")

typedef struct LabPCStatFieldMotion {
    u8 *entry;
    s32 kind;
    s8 fields[2];
    s16 old_values[2];
    s16 new_values[2];
} LabPCStatFieldMotion;
// Coordinate prefix; func_8800225C updates y from the active row and row height.
//@src/fragments/29/fragment29_167940.c
typedef struct LabPCWindowCoordinates {
    u8 unk_00[16];
    s16 y;
} LabPCWindowCoordinates;
extern void *D_8800EF54;
extern u8 D_8800EF50[];
extern u8 D_88006880[];
extern Gfx *D_800D0510;
extern s32 func_88216D98(s8, s8);
extern s32 func_88216E28(s8, s8);
extern void func_800496A4(s32, s32);
extern void func_80006F70(Gfx **, s16, s16, s16, s16);
extern void func_88217C90(s8, s16, s16);
void LabPC_DrawStatChangeHighlights(void) {
    s32 i;
    s8 field;
    s16 x;
    LabPCStatFieldMotion *motion = D_8800EF54;

    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, 0x00010001);
    for (i = 0; i != 2; i++) {
        if (motion->fields[i] != -1) {
            field = motion->fields[i] + 2;
            x = func_88216D98(1, field);
            gDPFillRectangle(D_800D0510++, x, ((LabPCWindowCoordinates *)D_88006880)->y,
                x + func_88216E28(1, field) - 1, ((LabPCWindowCoordinates *)D_88006880)->y + 19);
        }
    }
}

void LabPC_DrawStatChangeValues(void) {
    s32 i;
    s8 delta;
    s8 field;
    s16 y;
    LabPCStatFieldMotion *motion;

    delta = *(s16 *)(D_8800EF50 + 10) - *(s16 *)(D_8800EF50 + 8);
    motion = *(LabPCStatFieldMotion **)(D_8800EF50 + 4);
    y = ((LabPCWindowCoordinates *)D_88006880)->y - delta;
    func_800496A4(4, 1);
    func_80006F70(&D_800D0510, 0, ((LabPCWindowCoordinates *)D_88006880)->y, 640, 20);
    for (i = 0; i != 2; i++) {
        if (motion->fields[i] != -1) {
            field = motion->fields[i] + 2;
            func_88217C90(field, y, motion->old_values[i]);
            func_88217C90(field, y + 20, motion->new_values[i]);
        }
    }
    func_80006F70(&D_800D0510, 48, 147, 544, 280);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A6360/func_88233484.s")
#endif
