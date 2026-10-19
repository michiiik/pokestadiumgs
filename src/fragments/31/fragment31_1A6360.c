#include "global.h"


#ifdef VERSION_US
typedef struct LabPCStatFieldMotion {
    u8 *entry;
    s32 kind;
    s8 fields[2];
    u16 old_values[2];
    u16 new_values[2];
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

extern void func_800226C0(s32);
extern void func_800619E8(u8 *);
extern s32 func_88902E8C(u8 *, s32);
extern s32 func_88902E4C(u32 *, u8 *, s8);
extern s32 func_8821C0B0(void);
extern void func_8822AF00(void *);
extern void func_88001900(void);
extern u8 *D_882345F4;
extern u8 *D_88234620;
extern s8 D_88006868;
extern u8 D_8823474E;
extern u8 D_88234746;
extern s32 D_880068B4;
extern void *Util_Malloc(s32);
extern s32 func_88202158(u8 *, s32);
extern void func_882033B0(void *, void *);
extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
extern void LabPC_FinishStatChangeAnimation(void);
extern void LabPC_DrawStatChangeHighlights(void);
extern void LabPC_DrawStatChangeValues(void);
void LabPC_FinishStatChangeAnimation(void) {
    LabPCStatFieldMotion *motion = D_8800EF54;
    u8 *data;
    u16 old_hp;
    u32 move_cursor;

    func_800226C0(96);
    if (motion->kind == 8) {
        data = motion->entry + 8;
        old_hp = *(u16 *)(data + 40);
        func_800619E8(data);
        *(u16 *)(data + 38) += *(u16 *)(data + 40) - old_hp;
        if (func_88902E8C(data, 0) != 0 || func_88902E4C(&move_cursor, data, D_88006868) != 0) {
            D_8823474E = 3;
            return;
        }
    }
    if (func_8821C0B0() == 0 && motion->kind == 8) {
        func_8822AF00(D_882345F4 + 60);
    } else {
        func_88001900();
        D_880068B4 = 1;
    }
}

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

void LabPC_StartStatChangeAnimation(void) {
    LabPCStatFieldMotion *motion = Util_Malloc(sizeof(*motion));

    motion->entry = D_882345F4;
    motion->fields[1] = -1;
    if (func_88202158(D_88234620, 8)) {
        motion->kind = 8;
        motion->fields[0] = 0;
        motion->old_values[0] = motion->entry[37];
        motion->new_values[0] = motion->old_values[0] + 1;
    } else if (func_88202158(D_88234620, 16)) {
        motion->kind = 16;
        motion->fields[0] = 1;
        motion->old_values[0] = *(u16 *)(motion->entry + 48);
    } else if (func_88202158(D_88234620, 32)) {
        motion->kind = 32;
        motion->fields[0] = 2;
        motion->old_values[0] = *(u16 *)(motion->entry + 50);
    } else if (func_88202158(D_88234620, 64)) {
        motion->kind = 64;
        motion->fields[0] = 3;
        motion->old_values[0] = *(u16 *)(motion->entry + 52);
    } else if (func_88202158(D_88234620, 128)) {
        motion->kind = 128;
        motion->fields[0] = 6;
        motion->old_values[0] = *(u16 *)(motion->entry + 54);
    } else if (func_88202158(D_88234620, 256)) {
        motion->kind = 256;
        motion->fields[0] = 4;
        motion->fields[1] = 5;
        motion->old_values[0] = *(u16 *)(motion->entry + 56);
        motion->old_values[1] = *(u16 *)(motion->entry + 58);
    }
    func_882033B0(D_882345F4, D_88234620);
    if (motion->kind != 8) {
        func_800619E8(motion->entry + 8);
        switch (motion->kind) {
        case 16:
            motion->new_values[0] = *(u16 *)(motion->entry + 48);
            break;
        case 32:
            motion->new_values[0] = *(u16 *)(motion->entry + 50);
            break;
        case 64:
            motion->new_values[0] = *(u16 *)(motion->entry + 52);
            break;
        case 128:
            motion->new_values[0] = *(u16 *)(motion->entry + 54);
            break;
        case 256:
            motion->new_values[0] = *(u16 *)(motion->entry + 56);
            motion->new_values[1] = *(u16 *)(motion->entry + 58);
            break;
        }
    }
    func_800226C0(99);
    func_88005B60(21, LabPC_DrawStatChangeHighlights, LabPC_DrawStatChangeValues, LabPC_FinishStatChangeAnimation);
    D_8800EF54 = motion;
    D_88234746 = 1;
}
#endif
