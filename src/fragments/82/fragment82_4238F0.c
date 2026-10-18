#include "global.h"


#ifdef VERSION_US
typedef struct Fragment82MenuLabels { u8 kind, selection, first_text, second_text; } Fragment82MenuLabels;

typedef struct Fragment82Rectangle { s16 x, y, width, height; } Fragment82Rectangle;

/* Shared clipping rectangle, loaded as four halfwords by the draw traversal. */
typedef struct Fragment82GlobalState {
    s16 x, y;
    u16 width, height;
} Fragment82GlobalState;
extern Fragment82GlobalState D_82D07198;

typedef struct Fragment82MenuColor { u8 r, g, b, a; } Fragment82MenuColor;
typedef struct Fragment82MenuRow {
    u8 kind, index;
    s16 start_x, start_y, delta_x, delta_y;
    u8 flags, phase, timer, unk_0D[3];
    void *data;
    s16 x, y;
    u16 width, height;
    u8 unk_1C[4];
    Fragment82MenuColor primary, secondary;
} Fragment82MenuRow;
extern void func_82D00020(u8);
extern void func_82D067A0(u8 *);
extern void func_82D05BD8(u8 *);
extern void func_82D02B44(s16, s16, u16, u16);
extern Fragment82MenuRow D_82D06FB4[11];
extern Fragment82Rectangle D_82D0716C, D_82D07174, D_82D0717C;
extern u8 D_82D07190;
extern u8 D_82D07184, D_82D07188, D_82D0718C, D_82D07194;
extern Fragment82MenuColor D_82D06F90, D_82D06F94, D_82D06F98, D_82D06F9C;

extern Gfx* D_800D0510;
void ParticleGfx_SetPrimColor_fragment82(u8 r, u8 g, u8 b, u8 a) {
    gDPSetPrimColor(D_800D0510++, 0, 0, r, g, b, a);
}

void func_82D02AC8(u16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, (((((arg0 << 8) & 0xF800) | ((arg1 << 3) & 0x7C0) | ((arg2 >> 2) & 0x3E) | (arg3 & 1)) << 16) |
        (((arg0 << 8) & 0xF800) | ((arg1 << 3) & 0x7C0) | ((arg2 >> 2) & 0x3E) | (arg3 & 1))));
}

void func_82D02B44(s16 x, s16 y, u16 width, u16 height) {
    s16 right;
    s16 bottom;
    if ((right = x + width - 1) >= 640) right = 639;
    if (right < 0) right = 0;
    if ((bottom = y + height - 1) >= 480) bottom = 479;
    if (bottom < 0) bottom = 0;
    if (x < 0) x = 0;
    if (x >= 640) x = 639;
    if (y < 0) y = 0;
    if (y >= 480) y = 479;
    gDPSetScissor(D_800D0510++, G_SC_NON_INTERLACE, x, y, right, bottom);
}

extern void func_8004C8C0(s32);
void func_82D02C98(void) {
    func_8004C8C0(0x153);
    func_8004C8C0(0xF7);
    func_8004C8C0(0x7C);
    func_8004C8C0(0x101);
    func_8004C8C0(0x102);
    func_8004C8C0(0x33);
    func_8004C8C0(0x79);
    func_8004C8C0(0x1B);
    func_8004C8C0(0x1C);
    func_8004C8C0(0xAF);
}

void func_82D02D00(void) {
    func_8004C4B0(0x43);
}

void func_82D02D20(s32 arg0, s32 arg1)
{
  s32 temp_a2;
  s32 temp_a3;
  unsigned long long new_var;
  new_var = 0xFFFF;
  temp_a2 = arg0 & new_var;
  temp_a3 = arg1 & new_var;
  func_8004D1FC(func_8004C990(temp_a2, temp_a3, temp_a2, temp_a3));
}

void func_82D02D5C(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    s32 value = func_8004C990((s32)arg2, (s32)arg3);
    func_8004D19C((s32)arg0, (s32)arg1, value, 0, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D02DA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D02F78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D03144.s")

void func_82D03324(s16 arg0, s16 arg1, s32 arg2) {
    func_80044270((s32)arg0, (s32)arg1, (s16)arg2, 0x28, 0, 0, 0x400, 0x400, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D03380.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D03598.s")

extern int func_80044270(s32, s32, int, int, int, int, int, int, int);
void func_82D03778(s16 x, s16 y, u16 width, u16 height) {
    s32 w = width;
    if (w > 0 && height > 0) {
        func_82D02D20(0x102, 0);
        func_80044270(x, y, (s16)w, (s16)height, 0, 0, (0x10000 / w) & 0xFFFF, 0, 0);
    }
}

extern void func_82D02D20(s32 arg0, s32 arg1);
void func_82D03830(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    s32 w = arg2;
    if (w > 0 && arg3 > 0) {
        func_82D02D20(0x102, 0);
        gSPTextureRectangleFlip(D_800D0510++, arg0 * 4, arg1 * 4, (arg0 + w - 1) << 2, (arg1 + arg3 - 1) << 2, G_TX_RENDERTILE, 0, 0, (0x10000 / arg3) & 0xFFFF, 0);
    }
}

extern void func_82D03598(s16, s16, u16, u16);
void func_82D0396C(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    func_82D03778((s16) (arg0 + 3), (s16) (arg1 + 3), (arg2 - 6) & 0xFFFF, (arg3 - 6) & 0xFFFF);
    func_82D03598(arg0, arg1, arg2, arg3);
}

extern void func_82D03830(s16, s16, u16, u16);
void func_82D039E4(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    func_82D03830((s16) (arg0 + 3), (s16) (arg1 + 3), (arg2 - 5) & 0xFFFF, (arg3 - 6) & 0xFFFF);
    func_82D03598(arg0, arg1, arg2, arg3);
}

extern u8 D_82D07248[];
extern void ParticleGfx_SetPrimColor_fragment82(u8 r, u8 g, u8 b, u8 a);
extern void func_82D02D5C(s16 arg0, s16 arg1, u16 arg2, u16 arg3);
extern void func_82D039E4(s16 arg0, s16 arg1, u16 arg2, u16 arg3);
void func_82D03A5C(s16 arg0, s16 arg1, u16 arg2, f32 arg3) {
    s32 x;
    if (arg2 < 0x14) {
        return;
    }
    func_82D039E4(arg0, arg1, 0x13, arg2);
    gSPDisplayList(D_800D0510++, D_82D07248);
    ParticleGfx_SetPrimColor_fragment82(0xFF, 0xFF, 0, 0xFF);
    x = (s16)(arg0 + 3);
    func_82D02D5C(x, arg1 + (u16)((f32)(u16)(arg2 - 0x14) * arg3), 0x101, 1);
    func_82D02D5C(x, (s16)(arg1 + (u16)((f32)(u16)(arg2 - 0x14) * arg3) + 0xA), 0x101, 2);
}

extern f32 D_80087E50[];
extern u16 D_82D07280;
extern void func_82D02D5C(s16, s16, u16, u16);
void func_82D03BEC(s16 arg0, s16 arg1, u16 arg2) {
    s32 sp34;
    sp34 = (s32)(D_80087E50[(s32)D_82D07280 >> 4] * 2);
    D_82D07280 += 0x2000;
    func_82D02D5C(arg0, (s16)(arg1 - sp34), 0x1C, 0);
    func_80044270(arg0, (s16)(arg1 + arg2 + sp34), 0x20, 0xA, 0, 0x120, 0x400, -0x400, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D03CC0.s")

extern u16 D_82D23D98[2], D_82D23D9A;
extern u8 D_82D071D8[];
extern void func_82D03380(s16, s16, u16);
extern void func_8004989C(s32);
extern void Ui_DrawAnimatedTextureMarker(s32, s32);
extern void func_80049064(s32, s32, s32, s32);
extern void func_800496A4(s32, s32);
extern void func_800498C4(void);
extern s32 func_8004C874(s32, s32);
void func_82D049A0(void *arg0) {
    Fragment82MenuRow *row = arg0;
    Fragment82MenuLabels *labels = row->data;
    gSPDisplayList(D_800D0510++, D_82D071D8);
    ParticleGfx_SetPrimColor_fragment82(row->primary.r, row->primary.g, row->primary.b, row->primary.a);
    func_82D03380(row->x, row->y, row->width);
    if (row->phase == 0) {
        func_800498C4();
        func_800496A4(8, 1);
        func_8004989C(26);
        switch (labels->kind) {
        case 0:
            func_80049064(row->x + 76, row->y + 8, 0, func_8004C874(0x43, labels->first_text));
            break;
        case 1:
            func_80049064(row->x + 76, row->y + 8, 0, func_8004C874(0x43, labels->first_text));
            func_80049064(row->x + 76, row->y + 34, 0, func_8004C874(0x43, labels->second_text));
            func_80049064(D_82D23D98[0] + row->x, row->y + 60, 0, func_8004C874(0x43, 0x20));
            func_80049064(D_82D23D9A + row->x, row->y + 60, 0, func_8004C874(0x43, 0x21));
            break;
        }
        if (labels->kind == 1) {
            Ui_DrawAnimatedTextureMarker((s16)(D_82D23D98[labels->selection] + row->x - 40), (s16)(row->y + 60));
        }
    }
}

extern void func_800499EC(void);
void func_82D04B84(void *arg0) {
    gSPDisplayList(D_800D0510++, D_82D071D8);
    ParticleGfx_SetPrimColor_fragment82(
        *(u8 *)((u8 *)arg0 + 0x20),
        *(u8 *)((u8 *)arg0 + 0x21),
        *(u8 *)((u8 *)arg0 + 0x22),
        *(u8 *)((u8 *)arg0 + 0x23));
    func_82D02D20(0xF7, 0);
    func_82D03324(
        *(s16 *)((u8 *)arg0 + 0x14),
        *(s16 *)((u8 *)arg0 + 0x16),
        *(u16 *)((u8 *)arg0 + 0x18));
    func_800498C4();
    func_800496A4(0x10, 0);
    func_80049064(
        *(s16 *)((u8 *)arg0 + 0x14) + 0x40,
        *(s16 *)((u8 *)arg0 + 0x16) + 4,
        0,
        func_8004C874(0x43, 0));
    func_800499EC();
}

extern void func_8004972C(s32, s32, s32, s32);
void func_82D04C44(void *arg0) {
    u8 *sp24;

    sp24 = *(u8 **)((u8 *)arg0 + 0x10);
    gSPDisplayList(D_800D0510++, D_82D071D8);
    ParticleGfx_SetPrimColor_fragment82(
        *(u8 *)((u8 *)arg0 + 0x20),
        *(u8 *)((u8 *)arg0 + 0x21),
        *(u8 *)((u8 *)arg0 + 0x22),
        *(u8 *)((u8 *)arg0 + 0x23));
    func_82D02D20(0xF7, 0);
    func_82D03324(
        *(s16 *)((u8 *)arg0 + 0x14),
        *(s16 *)((u8 *)arg0 + 0x16),
        *(u16 *)((u8 *)arg0 + 0x18));
    func_800498C4();
    func_800496A4(0x10, 0);
    if (sp24[0] == 0) {
        if (*(s8 *)(sp24 + 1) == *(u8 *)((u8 *)arg0 + 1)) {
            func_8004972C(0xFF, 0xFF, 0, *(u8 *)((u8 *)arg0 + 0x27));
        } else {
            func_8004972C(0xFF, 0xFF, 0xFF, *(u8 *)((u8 *)arg0 + 0x27));
        }
    } else {
        func_8004972C(0xFF, 0xFF, 0xFF, *(u8 *)((u8 *)arg0 + 0x27));
    }
    func_80049064(
        *(s16 *)((u8 *)arg0 + 0x14) + 0x40,
        *(s16 *)((u8 *)arg0 + 0x16) + 4,
        0,
        func_8004C874(0x43, *(u8 *)((u8 *)arg0 + 1) + 1));
    func_800499EC();
    if (*(u8 *)((u8 *)arg0 + 0xB) == 0 &&
        *(s8 *)(sp24 + 1) == *(u8 *)((u8 *)arg0 + 1) &&
        sp24[0] == 0) {
        Ui_DrawAnimatedTextureMarker(
            (s16)(*(s16 *)((u8 *)arg0 + 0x14) + 0x18),
            (s16)(*(s16 *)((u8 *)arg0 + 0x16) + 4));
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D04DC8.s")

extern Fragment82MenuColor D_82D06FA4;
extern Gfx D_80094DE0[];
extern void func_82D03144(s16, s16, u16, u16);
extern void func_82D02AC8(u16 arg0, u16 arg1, u16 arg2, u16 arg3);
extern void func_82D02B44(s16 x, s16 y, u16 width, u16 height);
void func_82D0599C(void *arg0) {
    Fragment82MenuRow *row = arg0;
    func_82D02B44(row->x, row->y, row->width, row->height);
    gSPDisplayList(D_800D0510++, D_80094DE0);
    func_82D02AC8(D_82D06FA4.r, D_82D06FA4.g, D_82D06FA4.b, 1);
    gDPScisFillRectangle(D_800D0510++, row->x + 4, row->y + 4, row->x + (s16)row->width - 5, row->y + (s16)row->height - 5);
    gSPDisplayList(D_800D0510++, D_82D071D8);
    ParticleGfx_SetPrimColor_fragment82(255, 255, 255, 255);
    func_82D03144(row->x, row->y, row->width, row->height);
    if (row->phase == 0) {
        ParticleGfx_SetPrimColor_fragment82(255, 255, 100, 255);
        func_82D02D5C(304, (s16)(row->y + 16), 0xAF, 0);
        func_800498C4();
        func_800496A4(8, 1);
        func_8004989C(26);
        func_8004972C(255, 255, 255, 255);
        func_80049064(row->x + 16, row->y + 56, 0, func_8004C874(0x43, 0x23));
        func_800499EC();
    }
    func_82D02B44(D_82D07198.x, D_82D07198.y, D_82D07198.width, D_82D07198.height);
}

extern void func_82D02DA8(void *);
extern void func_82D03CC0(void *);
extern void func_82D049A0(void *);
extern void func_82D04DC8(void *);
extern void func_82D0599C(void *);
void func_82D05BD8(u8 *row) {
    if (row != 0 && (row[0xA] & 1)) {
        switch (row[0]) {
        case 0: func_82D02DA8(row); break;
        case 4: func_82D03CC0(row); break;
        case 3: func_82D049A0(row); break;
        case 1: func_82D04B84(row); break;
        case 2: func_82D04C44(row); break;
        case 5: func_82D04DC8(row); break;
        case 6: func_82D0599C(row); break;
        }
    }
}

void func_82D05C90(void) {
    u8 *row;
    u8 *end;
    Fragment82GlobalState *viewport = &D_82D07198;
    func_82D02B44(viewport->x, viewport->y, viewport->width, viewport->height);
    row = ((u8 *)D_82D06FB4); end = (u8 *)&D_82D0716C;
    do {
        func_82D05BD8(row);
        row += sizeof(Fragment82MenuRow);
    } while (row != end);
}

extern u8 D_82D07184;
typedef struct { u8 pad0[2]; s16 value2; u8 pad4[2]; s16 value6; u8 pad8[2]; u8 flagsA; u8 valueB; u8 countC; u8 padD[7]; s16 output14; } Fragment82BaseRateState;
void func_82D05CF4(Fragment82BaseRateState *arg0) {
    if (D_82D07184 >= arg0->countC) {
        arg0->flagsA |= 1;
        arg0->output14 = arg0->value2 + (arg0->value6 * arg0->countC) / D_82D07184;
    }
}

extern u8 D_82D06F9B;
void func_82D05D74(u8 *arg0) {
    typedef struct { u8 pad0[6]; s16 value6; u8 pad8[2]; u8 flagsA; u8 valueB; u8 countC; u8 padD[0x16]; u8 output23; u8 pad24[3]; u8 output27; } LocalRateState;
    LocalRateState *s = (LocalRateState *)arg0;

    if (D_82D07184 >= s->countC) {
        if (s->countC == 0) {
            s->output23 = D_82D06F9B;
            s->output27 = 0xFF;
            return;
        }
        s->output23 = (s->countC * D_82D06F9B) / D_82D07184;
        s->output27 = (s->countC * 0xFF) / D_82D07184;
    }
}

extern u8 D_82D07188;
typedef struct { u8 pad0[6]; s16 value6; u8 pad8[2]; u8 flagsA; u8 valueB; u8 countC; u8 padD[7]; s16 output14; } Fragment82State;
void func_82D05E38(Fragment82State *arg0) {
    if (D_82D07188 >= arg0->countC) {
        arg0->flagsA |= 1;
        arg0->output14 = (-arg0->value6 * arg0->countC) / D_82D07184;
    }
}

extern u8 D_82D06F97;
typedef struct { u8 pad0[6]; s16 value6; u8 pad8[2]; u8 flagsA; u8 valueB; u8 countC; u8 padD[0x16]; u8 output23; } Fragment82RateState;
void func_82D05EB4(Fragment82RateState *arg0) {
    if (D_82D07188 >= arg0->countC) {
        if (arg0->countC == 0) {
            arg0->output23 = D_82D06F97;
            return;
        }
        arg0->output23 = (arg0->countC * D_82D06F97) / D_82D07188;
    }
}

void func_82D05F30(u8 *arg0) {
    Fragment82MenuRow *row = (Fragment82MenuRow *)arg0;
    f32 progress;
    const f32 quarter_divisor = 4.0f;
    const f32 size_scale = 2.0f;
    if (D_82D0718C >= row->timer) {
        row->flags |= 1;
        progress = ((f32)(u32)row->timer / (f32)(u32)D_82D0718C) / quarter_divisor;
        row->x = (s16)(row->start_x + row->delta_x * progress);
        row->y = (s16)(row->start_y + row->delta_y * progress);
        row->width = (s16)(row->delta_x * (1.0f - progress * size_scale));
        row->height = (s16)(row->delta_y * (1.0f - progress * size_scale));
    }
}

void func_82D06040(u8 *arg0) {
    Fragment82MenuRow *row = (Fragment82MenuRow *)arg0;
    f32 progress;
    const f32 quarter_divisor = 4.0f;
    const f32 size_scale = 2.0f;
    if (D_82D0718C >= row->timer) {
        row->flags |= 1;
        progress = (1.0f - ((f32)(u32)row->timer / (f32)(u32)D_82D0718C)) / quarter_divisor;
        row->x = (s16)(row->start_x + row->delta_x * progress);
        row->y = (s16)(row->start_y + row->delta_y * progress);
        row->width = (s16)(row->delta_x * (1.0f - progress * size_scale));
        row->height = (s16)(row->delta_y * (1.0f - progress * size_scale));
    }
}

void func_82D06150(u8 *arg0, Fragment82Rectangle *from, Fragment82Rectangle *to, u8 duration) {
    Fragment82MenuRow *row = (Fragment82MenuRow *)arg0;
    s32 span = duration;
    s32 timer = row->timer;
    if (span >= timer && span != 0) {
        row->x = to->x - ((to->x - from->x) * timer) / span;
        row->y = to->y - ((to->y - from->y) * timer) / span;
        row->width = to->width - ((to->width - from->width) * timer) / span;
        row->height = to->height - ((to->height - from->height) * timer) / span;
    }
}

void func_82D062CC(u8 *arg0) {
    func_82D06150(arg0, &D_82D0716C, &D_82D07174, D_82D07190);
}

void func_82D06300(u8 *arg0) {
    func_82D06150(arg0, &D_82D07174, &D_82D0716C, D_82D07190);
}

void func_82D06334(u8 *arg0) {
    func_82D06150(arg0, &D_82D07174, &D_82D0717C, D_82D07190);
}

void func_82D06368(u8 *arg0) {
    func_82D06150(arg0, &D_82D0717C, &D_82D07174, D_82D07190);
}

extern void func_82D06B34(u8, u8, s32);
void func_82D0639C(u8 *arg0) {
    Fragment82MenuRow *row = (Fragment82MenuRow *)arg0;
    if (D_82D07194 >= row->timer) {
        row->flags |= 1;
        row->x = row->start_x - row->timer * 45;
        if (row->timer < D_82D07194 - 1) {
            if (row->x > 0) {
                D_82D07198.width = row->x;
            } else {
                D_82D07198.width = 0;
            }
        }
        switch (row->timer) {
        case 0:
            D_82D06FB4[8].flags &= ~1;
            break;
        case 1:
            func_82D06B34(0, 7, 2);
            func_82D06B34(1, 7, 2);
            break;
        }
    }
}

extern u8 D_82D07194;
typedef struct { u8 pad0[2]; s16 value2; u8 pad4[2]; s16 value6; u8 pad8[2]; u8 flagsA; u8 valueB; u8 countC; u8 padD[7]; s16 output14; u8 pad16[2]; s16 value18; } Fragment82OffsetState;
void func_82D06488(Fragment82OffsetState *arg0) {
    if (D_82D07194 >= arg0->countC) {
        arg0->flagsA |= 1;
        arg0->output14 = arg0->value2 - ((D_82D07194 - arg0->countC) * 0x2D);
        D_82D07198.x = arg0->output14 + arg0->value18;
        if (arg0->countC == 0) {
            D_82D07198.x = 0;
            D_82D07198.width = 0x280;
        }
    }
}

extern void func_82D05F30(u8 *arg0);
extern void func_82D0639C(u8 *arg0);
void func_82D06514(u8 *arg0) {
    s32 count;

    switch (arg0[0]) {
    case 2:
        func_82D05CF4((Fragment82BaseRateState *)arg0);
        break;
    case 3:
        func_82D05E38((Fragment82State *)arg0);
        break;
    case 4:
        func_82D05F30(arg0);
        break;
    case 5:
        func_82D0639C(arg0);
        break;
    case 6:
        func_82D05F30(arg0);
        break;
    }
    count = arg0[0xC];
    if (count == 0) {
        arg0[0xB] = 0;
        return;
    }
    arg0[0xC] = count - 1;
}
extern void func_82D05D74(u8 *);
extern void func_82D06040(u8 *);
extern void func_82D05EB4(Fragment82RateState *arg0);
extern void func_82D06488(Fragment82OffsetState *arg0);
void func_82D065C0(u8 *arg0) {
    s32 count;

    switch (arg0[0]) {
    case 2:
        func_82D05D74(arg0);
        break;
    case 3:
        func_82D05EB4((Fragment82RateState *)arg0);
        break;
    case 5:
        func_82D06488((Fragment82OffsetState *)arg0);
        break;
    case 4:
        func_82D06040(arg0);
        break;
    }
    count = arg0[0xC];
    if (count == 0) {
        arg0[0xB] = 0;
        arg0[0xA] &= 0xFFFE;
        return;
    }
    arg0[0xC] = count - 1;
}

void func_82D06670(u8 *arg0)
{
  u8 temp_v0;
  if ((*((u8 *) (((u8 *) arg0) + 0))) == 4)
  {
    func_82D062CC(arg0);
  }
  ;
  if ((*((u8 *) (((u8 *) arg0) + 0xC))) == 0)
  {
    *((s8 *) (((u8 *) arg0) + 0xB)) = 0;
    return;
  }
  *((u8 *) (((u8 *) arg0) + 0xC)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0xC))) - 1);
}

void func_82D066BC(u8 *arg0)
{
  u8 temp_v0;
 do { if ((*((u8 *) (((u8 *) arg0) + 0))) == 4) { func_82D06300(arg0); } temp_v0 = *((u8 *) (((u8 *) arg0) + 0xC)); } while (0);
  if (temp_v0 == 0)
  {
    *((s8 *) (((u8 *) arg0) + 0xB)) = 0;
    return;
  }
  *((u8 *) (((u8 *) arg0) + 0xC)) = (u8) (temp_v0 - 1);
}

void func_82D06708(u8 *arg0)
{
  u8 *new_var;
  u8 temp_v0;
  new_var = arg0;
  if (4 == (*((u8 *) (((u8 *) new_var) + 0))))
  {
    func_82D06334(new_var);
  }
  temp_v0 = *((u8 *) (((u8 *) new_var) + 0xC));
  if (!temp_v0)
  {
    *((s8 *) (((u8 *) arg0) + 0xB)) = 0;
    return;
  }
  *((u8 *) (((u8 *) new_var) + 0xC)) = (u8) (temp_v0 + -1);
}

void func_82D06754(u8 *arg0)
{
  u8 temp_v0;
  if ((*((u8 *) (((u8 *) arg0) + 0))) == 4)
  {
    func_82D06368(arg0);
  }
  ;
  if ((*((u8 *) (((u8 *) arg0) + 0xC))) == 0)
  {
    *((s8 *) (((u8 *) arg0) + 0xB)) = 0;
    return;
  }
  *((u8 *) (((u8 *) arg0) + 0xC)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0xC))) - 1);
}

void func_82D067A0(u8 *row) {
    s32 timer;
    switch (row[0xB]) {
    case 1: func_82D06514(row); break;
    case 2: func_82D065C0(row); break;
    case 3: func_82D06670(row); break;
    case 4: func_82D066BC(row); break;
    case 5: func_82D06708(row); break;
    case 6: func_82D06754(row); break;
    case 7:
        timer = row[0xC];
        if (timer == 0) {
            row[0xB] = 0;
            row[0xA] &= ~1;
        } else {
            row[0xC] = timer - 1;
        }
        break;
    }
    if (row[0xA] & 2) {
        func_82D00020(0);
        if (row[0xC] == 0) {
            row[0xA] &= ~2;
        }
    }
}

void func_82D068A0(void) {
    u8 *row;
    u8 *end;
    func_82D00020(1);
    row = ((u8 *)D_82D06FB4); end = (u8 *)&D_82D0716C;
    do {
        func_82D067A0(row);
        row += sizeof(Fragment82MenuRow);
    } while (row != end);
}

void func_82D068F0(Fragment82MenuRow *row, s32 delay) {
    switch (row->kind) {
    case 2: row->timer = D_82D07184 + delay; break;
    case 3: row->timer = D_82D07188 + delay; break;
    case 4:
    case 6: row->timer = D_82D0718C + delay; break;
    case 5: row->timer = D_82D07194 + delay; break;
    }
    row->flags |= 2;
    row->phase = 1;
}

void func_82D0697C(Fragment82MenuRow *row, s32 delay) {
    switch (row->kind) {
    case 2: row->timer = D_82D07184 + delay; break;
    case 3: row->timer = D_82D07188 + delay; break;
    case 4:
    case 6: row->timer = D_82D0718C + delay; break;
    case 5:
        D_82D07198.y = *(s16 *)(((u8 *)D_82D06FB4) + 0x16C);
        D_82D07198.width = 92;
        D_82D07198.height = *(s16 *)(((u8 *)D_82D06FB4) + 0x170);
        ((u8 *)D_82D06FB4)[0x14A] |= 1;
        ((u8 *)D_82D06FB4)[0xA] |= 1;
        ((u8 *)D_82D06FB4)[0x32] |= 1;
        row->timer = D_82D07194 + delay;
        break;
    }
    row->flags |= 2;
    row->phase = 2;
}

void func_82D06A54(void *arg0, s32 arg1)
{
  if ((*((u8 *) (((u8 *) arg0) + 0))) == 4)
  {
    *((s8 *) (((u8 *) arg0) + 0xC)) = (s8) (D_82D07190 + arg1);
  }
  *((u8 *) (((u8 *) arg0) + 0xA)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0xA))) | 2);
  *((s8 *) (((u8 *) arg0) + 0xB)) = 3;
}

void func_82D06A8C(void *arg0, s32 arg1)
{
  if (((unsigned long) (*((u8 *) (((u8 *) arg0) + 0)))) == 4)
  {
    *((s8 *) (((u8 *) arg0) + 0xC)) = (s8) (D_82D07190 + arg1);
  }
  *((u8 *) (((u8 *) arg0) + 0xA)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0xA))) | 2);
  *((s8 *) (((u8 *) arg0) + 0xB)) = 4;
}

void func_82D06AC4(void *arg0, s32 arg1)
{
  if ((*((u8 *) (((u8 *) arg0) + 0))) == 4)
  {
    *((s8 *) (((u8 *) arg0) + 0xC)) = (s8) (D_82D07190 + arg1);
  }
  *((u8 *) (((u8 *) arg0) + 0xA)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0xA))) | 2);
  *((s8 *) (((u8 *) arg0) + 0xB)) = 5;
}

void func_82D06AFC(void *arg0, s32 arg1)
{
  if ((*((u8 *) (((u8 *) arg0) + 0))) == 4)
  {
    *((s8 *) (((u8 *) arg0) + 0xC)) = (s8) (D_82D07190 + arg1);
  }
  *((u8 *) (((u8 *) arg0) + 0xA)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0xA))) | 2);
  *((s8 *) (((u8 *) arg0) + 0xB)) = 6;
}

void func_82D06B34(u8 index, u8 phase, s32 delay) {
    switch (phase) {
    case 1: func_82D068F0(&D_82D06FB4[index], delay); break;
    case 2: func_82D0697C(&D_82D06FB4[index], delay); break;
    case 3: func_82D06A54(&D_82D06FB4[index], delay); break;
    case 4: func_82D06A8C(&D_82D06FB4[index], delay); break;
    case 5: func_82D06AC4(&D_82D06FB4[index], delay); break;
    case 6: func_82D06AFC(&D_82D06FB4[index], delay); break;
    case 7: {
        Fragment82MenuRow *row = &D_82D06FB4[index];
        row->phase = phase;
        row->timer = delay;
        row->flags |= 2;
        break;
    }
    }
}

extern u8 D_82D06FC4[];
void func_82D06C9C(u8 arg0, s32 arg1) { *(s32 *)(D_82D06FC4 + (arg0 * 0x28)) = arg1; }

void func_82D06CC0(Fragment82MenuRow *row) {
    switch (row->kind) {
    case 0: row->primary = D_82D06F90; break;
    case 4: row->primary = D_82D06F9C; break;
    case 1:
    case 3: row->primary = D_82D06F94; break;
    case 2:
        row->primary = D_82D06F98;
        row->secondary.a = 255;
        break;
    }
}

extern u16 D_82D23D90, D_82D23D92, D_82D23D94;
extern char D_82D0732C[];
extern s32 func_80049148(s32, s32, void *);
extern s32 func_800472E0(void *);
extern void func_8004C09C(s32);
extern void func_82D02C98(void);
extern void func_82D02D00(void);
void func_82D06D50(void) {
    s32 width, height;
    Fragment82MenuRow *rows;
    s32 index;
    func_8004C09C(11);
    func_82D02C98();
    func_82D02D00();
    D_82D23D94 = 474 - func_80049148(4, 1, (void *)func_8004C874(0x43, 0x10));
    D_82D23D90 = D_82D23D94 - func_80049148(8, 3, D_82D0732C) - 4;
    if (D_82D23D94 == 474) D_82D23D90 += 4;
    D_82D23D92 = D_82D23D90 - func_80049148(4, 1, (void *)func_8004C874(0x43, 0xF)) - 4;
    width = func_80049148(8, 1, (void *)func_8004C874(0x43, 0x23)) + 32;
    height = func_800472E0((void *)func_8004C874(0x43, 0x23)) * 26;
    rows = D_82D06FB4;
    rows[10].start_x = (640 - width) / 2;
    rows[10].start_y = (408 - height) / 2;
    rows[10].delta_x = width;
    rows[10].delta_y = height + 72;
    D_82D23D98[0] = 116;
    D_82D23D9A = func_80049148(8, 1, (void *)func_8004C874(0x43, 0x20)) + 176;
    index = 0;
    do {
        func_82D06CC0(&D_82D06FB4[index]);
        *(Fragment82Rectangle *)&D_82D06FB4[index].x = *(Fragment82Rectangle *)&D_82D06FB4[index].start_x;
        index++;
    } while (index != 11);
    D_82D06FB4[0].flags |= 1;
    D_82D06FB4[1].flags |= 1;
}
#endif
