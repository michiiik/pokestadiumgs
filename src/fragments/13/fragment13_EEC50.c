#include "global.h"


#ifdef VERSION_US
/* Shared named constants precede this file's compiler-owned switch tables. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/D_82408F00.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/D_82408F04.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/D_82408F08.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/D_82408F0C.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/D_82408F10.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/D_82408F14.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/D_82408F20.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/D_82408F2C.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/D_82408F38.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/D_82408F40.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/D_82408F78.s")

struct Fragment13GroupItem {
    u8 opaque[6];
    s16 labelIndex;
    s16 id;
    s16 value;
};

struct Fragment13MotionVector {
    f32 x, y, z;
};

struct Fragment13GroupAnchor {
    f32 x, y, z;
    u8 opaque[16];
    struct Fragment13MotionVector eye;
    struct Fragment13MotionVector target;
    struct Fragment13GroupItem *items;
    s16 defaultValue;
    u16 count;
};
extern struct Fragment13GroupAnchor D_82407370[];

/* The item-pointer field repeats at the anchor record's 0x3C-byte stride. */
struct Fragment13GroupItemSpan {
    struct Fragment13GroupItem *items;
    u8 rest[56];
};
extern struct Fragment13GroupItemSpan D_824073A4[];

struct Fragment13GroupedList {
    s16 entries[128];
    s16 counts[8];
    s16 starts[8];
};

extern Gfx *D_800D0510;
void Fragment13_DrawClippedTextureRect(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, f32 arg6, f32 arg7) {
    f32 right;
    f32 bottom;
    if (arg2 < 0.0f || arg3 < 0.0f || arg0 > 320.0f || arg1 > 240.0f) {
        return;
    }
    right = arg0 + arg2;
    if (right < 0.0f) {
        return;
    }
    bottom = arg1 + arg3;
    if (bottom < 0.0f) {
        return;
    }
    if (arg0 < 0.0f) {
        arg2 += arg0;
        arg4 -= arg0 * arg6;
        arg0 = 0.0f;
    }
    if (arg1 < 0.0f) {
        arg3 += arg1;
        arg5 -= arg1 * arg7;
        arg1 = 0.0f;
    }
    right = arg0 + arg2;
    if (right > 320.0f) {
        arg2 -= 320.0f - arg0;
        right = arg0 + arg2;
    }
    bottom = arg1 + arg3;
    if (bottom > 240.0f) {
        arg3 -= 240.0f - arg1;
        bottom = arg1 + arg3;
    }
    gSPScisTextureRectangle(D_800D0510++, ((s32)arg0) * 4, ((s32)arg1) * 4,
                           ((s32)right) * 4, ((s32)bottom) * 4, G_TX_RENDERTILE,
                           arg4 * 32, arg5 * 32, (s16)(s32)(arg6 * 1024.0f),
                           (s16)(s32)(arg7 * 1024.0f));
}

extern void func_8004C8C0(s32);
s32 func_8004C990(s32, s32);
extern s32 D_82407830;
extern s32 D_82407834;
extern s32 D_82407838;
extern s32 D_8240783C;
extern s32 D_82407840;
extern s32 D_82407844;
extern s32 D_82407848;
extern s32 D_8240784C;
extern s32 D_82407850;
extern s32 D_82407854;
extern s32 D_82407858;
extern s32 D_8240785C;
extern s32 D_82407860;
extern s32 D_82407864;
extern s32 D_82407868;
void func_82401000(void) {
    func_8004C4B0(0x3C);
    func_8004C8C0(0x94);
    func_8004C8C0(0x1E);
    func_8004C8C0(0x21);
    func_8004C8C0(0x1F);
    func_8004C8C0(0xE7);
    func_8004C8C0(0xE9);
    func_8004C8C0(0xEA);
    func_8004C8C0(0xE8);
    func_8004C8C0(0xEB);
    func_8004C8C0(0x12);
    D_82407840 = func_8004C990(0xEA, 6);
    D_82407848 = func_8004C990(0xE8, 0);
    D_82407838 = func_8004C990(0x1E, 0);
    D_8240783C = func_8004C990(0x1E, 1);
    D_82407830 = func_8004C990(0x94, 0);
    D_82407844 = func_8004C990(0xEA, 5);
    D_82407834 = func_8004C990(0xEA, 4);
    D_8240784C = func_8004C990(0xEA, 1);
    D_82407850 = func_8004C990(0xEA, 2);
    D_82407854 = func_8004C990(0xEA, 3);
    D_82407858 = func_8004C990(0xEA, 0);
    D_82407868 = func_8004C990(0xEB, 0);
    D_82407864 = func_8004C990(0xEB, 1);
    D_8240785C = func_8004C990(0xEB, 2);
    D_82407860 = func_8004C990(0xEB, 3);
}

extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_80094F50[];
extern u8 D_80094DB8[];
extern void func_8004D1FC(u8 *);
extern void Gfx_FillRectRgba(s16, s16, s16, s16, u8, u8, u8, u8);
extern s32 D_82407840;
void func_82401198(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 < 4 || arg3 < 4) {
        return;
    }
    func_8004D1FC((void *)D_82407840);
    gSPDisplayList(D_800D0510++, D_80094E38);
    arg0 -= 2;
    arg1 -= 2;
    arg2 += 2;
    arg3 += 2;
    Fragment13_DrawClippedTextureRect(arg0, arg1, 4.0f, 4.0f, 0, 0, 1.0f, 1.0f);
    Fragment13_DrawClippedTextureRect((arg0 + arg2) - 4, arg1, 4.0f, 4.0f, 4, 0, 1.0f, 1.0f);
    Fragment13_DrawClippedTextureRect(arg0, (arg1 + arg3) - 4, 4.0f, 4.0f, 8, 0, 1.0f, 1.0f);
    Fragment13_DrawClippedTextureRect((arg0 + arg2) - 4, (arg1 + arg3) - 4, 4.0f, 4.0f, 0xC, 0, 1.0f, 1.0f);
    Fragment13_DrawClippedTextureRect(arg0, arg1 + 4, 4.0f, arg3 - 8, 0, 4, 1.0f, 0.0f);
    Fragment13_DrawClippedTextureRect(arg0 + 4, arg1, arg2 - 8, 4.0f, 4, 0, 0.0f, 1.0f);
    Fragment13_DrawClippedTextureRect((arg0 + arg2) - 4, arg1 + 4, 4.0f, arg3 - 8, 0xC, 0, 1.0f, 0.0f);
    Fragment13_DrawClippedTextureRect(arg0 + 4, (arg1 + arg3) - 4, arg2 - 8, 4.0f, 0xC, 0, 0.0f, 1.0f);
    gSPDisplayList(D_800D0510++, D_80094F50);
    gSPDisplayList(D_800D0510++, D_80094DB8);
    gDPSetRenderMode(D_800D0510++, 0x00504240, 0);
    Gfx_FillRectRgba(arg0 - 1, arg1 - 1, arg2 + 2, 6, 0, 0, 0, 0);
    Gfx_FillRectRgba(arg0 - 1, (arg1 + arg3) - 6, arg2 + 2, 6, 0, 0, 0, 0);
    Gfx_FillRectRgba(arg0 - 1, arg1 + 4, 6, arg3 - 8, 0, 0, 0, 0);
    Gfx_FillRectRgba((arg0 + arg2) - 5, arg1 + 4, 6, arg3 - 8, 0, 0, 0, 0);
}

void Fragment13_DrawTexturedPanelBorder(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 >= 4 && arg3 >= 4) {
        func_8004D1FC((void *)(u32)D_82407844);
        gSPDisplayList(D_800D0510++, D_80094E38);
        gDPSetRenderMode(D_800D0510++, 0, 0x0F0A7008);
        Fragment13_DrawClippedTextureRect(arg0, arg1, 4.0f, 4.0f, 0, 0, 1.0f, 1.0f);
        Fragment13_DrawClippedTextureRect((arg0 + arg2) - 4, arg1, 4.0f, 4.0f, 4, 0, 1.0f, 1.0f);
        Fragment13_DrawClippedTextureRect(arg0, (arg1 + arg3) - 4, 4.0f, 4.0f, 0, 4, 1.0f, 1.0f);
        Fragment13_DrawClippedTextureRect((arg0 + arg2) - 4, (arg1 + arg3) - 4, 4.0f, 4.0f, 4, 4, 1.0f, 1.0f);
        Fragment13_DrawClippedTextureRect(arg0, arg1 + 4, 4.0f, arg3 - 8, 0, 4, 1.0f, 0.0f);
        Fragment13_DrawClippedTextureRect(arg0 + 4, arg1, arg2 - 8, 4.0f, 4, 0, 0.0f, 1.0f);
        Fragment13_DrawClippedTextureRect((arg0 + arg2) - 4, arg1 + 4, 4.0f, arg3 - 8, 4, 4, 1.0f, 0.0f);
        Fragment13_DrawClippedTextureRect(arg0 + 4, (arg1 + arg3) - 4, arg2 - 8, 4.0f, 4, 4, 0.0f, 1.0f);
        gSPDisplayList(D_800D0510++, D_80094F50);
    }
}

void Fragment13_DrawPanelCorners(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 >= 4 && arg3 >= 4) {
        arg2++;
        arg3++;
        func_8004D1FC((void *)(u32)D_82407834);
        gSPDisplayList(D_800D0510++, D_80094E38);
        gDPSetRenderMode(D_800D0510++, 0, 0x0F0A7008);
        gDPSetEnvColor(D_800D0510++, 0xF8, 0xFF, 0x7C, 0xFF);
        gDPPipeSync(D_800D0510++);
        Fragment13_DrawClippedTextureRect((f32)arg0, (f32)arg1, 8.0f, 8.0f, 0, 0, 1.0f, 1.0f);
        Fragment13_DrawClippedTextureRect((f32)(arg0 + arg2 - 8), (f32)arg1, 8.0f, 8.0f, 8, 0, 1.0f, 1.0f);
        Fragment13_DrawClippedTextureRect((f32)arg0, (f32)(arg1 + arg3 - 8), 8.0f, 8.0f, 0, 8, 1.0f, 1.0f);
        Fragment13_DrawClippedTextureRect((f32)(arg0 + arg2 - 8), (f32)(arg1 + arg3 - 8), 8.0f, 8.0f, 8, 8, 1.0f, 1.0f);
        gSPDisplayList(D_800D0510++, D_80094F50);
    }
}

void Fragment13_DrawColoredPanelFill(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    func_8004D1FC((void *)(u32)D_82407848);
    gSPDisplayList(D_800D0510++, D_80094E38);
    /* Preserve RGB bit positions and the original color-pack evaluation tree. */
    gDPSetColor(D_800D0510++, G_SETENVCOLOR, (_SHIFTL(arg4[1], 16, 8) | _SHIFTL(arg4[2], 8, 8) | _SHIFTL(arg4[0], 24, 8) | _SHIFTL(0xFF, 0, 8)));
    gDPSetRenderMode(D_800D0510++, 0, 0x0F0A4000);
    gSPScisTextureRectangle(D_800D0510++, arg0 * 4, arg1 * 4, (arg0 + arg2) * 4, (arg1 + arg3) * 4, G_TX_RENDERTILE, 0, 0, (u32)(65536.0f / (f32)arg2), 0);
    gSPDisplayList(D_800D0510++, D_80094F50);
}

extern void func_800496A4(s32, s32);
extern void func_8004C54C(s32, s32);
extern s32 func_8004C8A0(void *, s32, s32, s32);
extern void func_800495F8(s32, s32, s32, s32);
void func_82401DD4(s32 arg0) {
    s32 temp[32];
    s32 value;
    func_800496A4(4, 1);
    func_8004C54C(0x14, arg0);
    value = func_8004C8A0(temp, 0x40, 0x3C, 0);
    func_800495F8(0xA0, 0x12, 1, value);
}

extern Gfx *D_800D0510;
extern void func_8004D1FC(u8 *);
void func_82401E30(s32 arg0, s32 arg1) {
    gDPSetEnvColor(D_800D0510++, 0xAA, 0xAA, 0xFF, 0xFF);
    func_8004D1FC((u8 *)(u32)D_82407838);
    Fragment13_DrawClippedTextureRect((f32)arg0, (f32)arg1, (f32)*(u16 *)(u8 *)(u32)D_82407838, (f32)*(u16 *)((u8 *)(u32)D_82407838 + 2), 0, 0, 1.0f, 1.0f);
}

void func_82401F08(s32 arg0, s32 arg1) {
    gDPSetEnvColor(D_800D0510++, 0xAA, 0xFF, 0xAA, 0xFF);
    func_8004D1FC((u8 *)(u32)D_8240783C);
    Fragment13_DrawClippedTextureRect((f32)arg0, (f32)arg1, (f32)*(u16 *)(u8 *)(u32)D_8240783C, (f32)*(u16 *)((u8 *)(u32)D_8240783C + 2), 0, 0, 1.0f, 1.0f);
}

extern Gfx *D_800D0510;
extern void func_8004D1FC(u8 *);
void func_82401FE0(s32 arg0, s32 arg1) {
    gDPSetEnvColor(D_800D0510++, 0xFF, 0xFF, 0xFF, 0xFF);
    func_8004D1FC((u8 *)(u32)D_82407830);
    Fragment13_DrawClippedTextureRect((f32)arg0, (f32)arg1, (f32)*(u16 *)(u8 *)(u32)D_82407830, (f32)*(u16 *)((u8 *)(u32)D_82407830 + 2), 0, 0, 1.0f, 1.0f);
}

extern void func_800498C4(void);
extern void func_800499EC(void);
extern s32 func_8004C874(s32, s32);
extern void func_800495BC(s32, s32, s32);
void Fragment13_DrawSelectionFooter(s32 arg0, s32 arg1) {
    Gfx *packet;

    if (arg0) {
        func_800498C4();
        func_82401DD4(arg1);
        func_800499EC();
        return;
    }
    packet = D_800D0510++;
    gSPDisplayList(packet, D_80094E38);
    func_82401E30(28, 207);
    func_82401F08(240, 207);
    packet = D_800D0510++;
    gSPDisplayList(packet, D_80094F50);
    func_800498C4();
    func_800496A4(2, 1);
    func_800495BC(44, 209, func_8004C874(60, 3));
    func_800495BC(256, 209, func_8004C874(60, 5));
    func_800499EC();
}

extern void func_800498C4(void);
extern void func_82401DD4(s32);
extern void func_82401F08(s32, s32);
extern void func_800499EC(void);
extern void func_800496A4(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_800495BC(s32, s32, s32);
extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_80094F50[];
void func_824021AC(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        func_800498C4();
        func_82401DD4(arg1);
        func_800499EC();
        return;
    }
    gSPDisplayList(D_800D0510++, D_80094E38);
    func_82401F08(0xF0, 0xCF);
    gSPDisplayList(D_800D0510++, D_80094F50);
    func_800498C4();
    func_800496A4(2, 1);
    func_800495BC(0x100, 0xD1, func_8004C874(0x3C, 5));
    func_800499EC();
}

extern void func_800498C4(void);
extern void func_82401DD4(s32);
extern void func_82401FE0(s32, s32);
extern void func_82401E30(s32, s32);
extern void func_82401F08(s32, s32);
extern void func_800499EC(void);
extern void func_800496A4(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_800495BC(s32, s32, s32);
extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_80094F50[];
void func_8240227C(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        func_800498C4();
        func_82401DD4(arg1);
        func_800499EC();
        return;
    }
    gSPDisplayList(D_800D0510++, D_80094E38);
    func_82401FE0(0x1F, 0xCD);
    func_82401E30(0x92, 0xCF);
    func_82401F08(0xF2, 0xCF);
    gSPDisplayList(D_800D0510++, D_80094F50);
    func_800498C4();
    func_800496A4(2, 1);
    func_800495BC(0x35, 0xD1, func_8004C874(0x3C, 1));
    func_800495BC(0xA2, 0xD1, func_8004C874(0x3C, 2));
    func_800495BC(0x102, 0xD1, func_8004C874(0x3C, 0x41));
    func_800499EC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_8240239C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_824027F4.s")

void Fragment13_DrawSelectionHeader(s32 arg0, s32 arg1) {
    Gfx *packet;

    if (!arg0) {
        return;
    }
    packet = D_800D0510++;
    gSPDisplayList(packet, D_80094E38);
    func_82401E30(31, 20);
    func_82401F08(241, 20);
    packet = D_800D0510++;
    gSPDisplayList(packet, D_80094F50);
    func_800498C4();
    func_82401DD4(arg1);
    func_800496A4(2, 1);
    func_800495BC(47, 22, func_8004C874(60, 4));
    func_800495BC(257, 22, func_8004C874(60, 5));
    func_800499EC();
}

s32 func_824029E4(s32 arg0, s16 arg1) {
    if (arg1 < 0) {
        return 8;
    }
    return *(s16 *)((u8 *)(u32)arg0 + ((s32)arg1 << 1) + 0x100) + 1;
}

extern u8 D_82408F00[];
s32 Fragment13_GetGroupedItemLabel(struct Fragment13GroupedList *arg0, s32 arg1, s16 arg2) {
    if (arg2 >= func_824029E4((s32)arg0, (s16)arg1)) {
        return (s32)D_82408F00;
    } else if (arg1 < 0) {
        return func_8004C874(0x3C, arg2 + 6);
    } else if (func_824029E4((s32)arg0, (s16)arg1) == arg2 + 1) {
        return func_8004C874(0x3C, 0x3D);
    } else {
        return func_8004C874(0x3C, D_824073A4[arg1].items[(arg0->entries + arg0->starts[arg1])[arg2]].labelIndex);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82402B1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82402E28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_8240330C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82403624.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82403C84.s")

s32 func_80001FF0();
s32 func_80008970();

f32 func_82403F10(void) {
    s32 sp1C;

    sp1C = func_80008970();
    return ((f32) sp1C * 60.0f) / (f32) func_80001FF0();
}

extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_80094F50[];
extern s32 func_8004D19C(s32, s32, s32, s32, s32);
void func_82403F58(void) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
    func_8004D19C(0, 0, D_8240785C, 0, 0);
    gSPDisplayList(D_800D0510++, D_80094F50);
}

extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_80094F50[];
extern s32 func_8004D19C(s32, s32, s32, s32, s32);
void func_82404000(void) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
    func_8004D19C(0, 0xCA, D_82407860, 0, 0);
    gSPDisplayList(D_800D0510++, D_80094F50);
}

void func_824040A8(void) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
    func_8004D19C(0, 0x26, D_82407868, 0, 0);
    gSPDisplayList(D_800D0510++, D_80094F50);
}

void func_82404150(void) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
    func_8004D19C(0x134, 0x26, D_82407864, 0, 0);
    gSPDisplayList(D_800D0510++, D_80094F50);
}

extern void func_82403F58(void);
extern void func_82404000(void);
extern void func_824040A8(void);
extern void func_82404150(void);
void func_824041F8(void) {
    func_82403F58();
    func_82404000();
    func_824040A8();
    func_82404150();
}

extern f32 (*D_8160BD08)(f32);
s32 func_82404230(void *arg0) {
    return (s32) (((f32) (-((s32) (*((s16 *) (6 + ((u8 *) arg0))))))) + (((f32) ((*((s16 *) (((u8 *) arg0) + 2))) - (-((s32) (*((s16 *) (((u8 *) arg0) + 6))))))) * D_8160BD08((*((f32 *) (((u8 *) arg0) + 0x1C))) / ((f32) 8))));
}

extern s32 func_8004C874(s32, s32);
extern s32 func_800472E0(s32);
extern s16 func_80049148(s32, s32, s32);
extern s32 func_8004C990(s32, s32);
void func_8240429C(u8 *arg0) {
    *(s32 *)(arg0 + 8) = func_8004C874(0x3C, 0x3E);
    *(s32 *)(arg0 + 0xC) = func_8004C874(0x3C, 0x3F);
    *(s32 *)(arg0 + 0x10) = func_8004C874(0x3C, 0x40);
    func_800472E0(*(s32 *)(arg0 + 8));
    *(s16 *)(arg0 + 4) = func_80049148(2, 1, *(s32 *)(arg0 + 8));
    *(s32 *)(arg0 + 0x14) = func_8004C990(0x12, 3);
    *(s32 *)(arg0 + 0x18) = func_8004C990(0x12, 2);
    *(s16 *)(arg0 + 4) = 0xAF;
    *(s16 *)(arg0 + 6) = 0x4C;
    *(s16 *)(arg0 + 0) = 0x48;
    *(s16 *)(arg0 + 2) = 0x40;
    *(u8 *)(arg0 + 0x21) = 0;
    *(s8 *)(arg0 + 0x20) = -1;
    *(f32 *)(arg0 + 0x1C) = 0.0f;
}

s32 func_82404360(u8 *arg0) {
    *(s8 *)(arg0 + 0x20) = -1;
    *(f32 *)(arg0 + 0x1C) = 0.0f;
    return 0;
}

s32 func_82404378(void *arg0)
{
  f32 new_var2;
  u8 *new_var;
  new_var2 = func_82403F10();
  *((f32 *) (((u8 *) arg0) + 0x1C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x1C))) + new_var2);
  if ((*((f32 *) (((u8 *) arg0) + 0x1C))) >= 8.0f)
  {
    new_var = (u8 *) arg0;
    *((f32 *) (new_var + 0x1C)) = 8.0f;
    *((s8 *) (new_var + 0x21)) = 2;
    *((s8 *) (((u8 *) arg0) + 0x20)) = 0;
  }
  return 0;
}

s32 func_824043D8(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (0x1C))) = (f32) ((*(f32 *)((u8 *)(arg0) + (0x1C))) - func_82403F10());
    if ((*(f32 *)((u8 *)(arg0) + (0x1C))) <= 0.0f) {
        (*(f32 *)((u8 *)(arg0) + (0x1C))) = 0.0f;
        (*(s8 *)((u8 *)(arg0) + (0x21))) = 4;
    }
    return 0;
}

s32 func_82404430(u8 *arg0) {
    *(f32 *)(arg0 + 0x1C) = 0.0f;
    return 0;
}

extern u8 *D_80087200;
/* Sound requests carry a sound word and, for contextual requests, a context. */
extern void func_800226C0(s32, ...);
s32 Fragment13_HandleConfirmationInput(u8 *arg0) {
    s32 buttons;

    *(f32 *)(arg0 + 0x1C) = 8.0f;
    buttons = *(u16 *)(D_80087200 + 8);
    if ((buttons & 0x100) && *(s8 *)(arg0 + 0x20) <= 0) {
        func_800226C0(1);
        *(s8 *)(arg0 + 0x20) = 1;
    } else if ((buttons & 0x200) && *(s8 *)(arg0 + 0x20) > 0) {
        func_800226C0(1);
        *(s8 *)(arg0 + 0x20) = 0;
    } else if (buttons & 0x8000) {
        *(u8 *)(arg0 + 0x21) = 3;
        switch (*(s8 *)(arg0 + 0x20)) {
        case 0:
            func_800226C0(0x14A);
            break;
        case 1:
            func_800226C0(0x14);
            break;
        }
        func_800226C0(0xAA);
        return 1;
    } else if (buttons & 0x4000) {
        *(s8 *)(arg0 + 0x20) = 2;
        func_800226C0(3);
        func_800226C0(0xAA);
        *(u8 *)(arg0 + 0x21) = 3;
    } else {
        return 0;
    }
    return 1;
}

s8 func_82404564(void *arg0) {
    u8 temp_v0;

    temp_v0 = (*(u8 *)((u8 *)(arg0) + (0x21)));
    if (temp_v0 != 0) {
        if (temp_v0 == 4) {
            (*(u8 *)((u8 *)(arg0) + (0x21))) = 0U;
            return (*(s8 *)((u8 *)(arg0) + (0x20)));
        }
        goto block_4;
    }
    (*(u8 *)((u8 *)(arg0) + (0x21))) = 1U;
    func_800226C0(0xA9, arg0);
block_4:
    return -1;
}

extern void func_81600A34(void *, void *, s32, s32, s32, s32, s32);
void Fragment13_UpdateConfirmationDialog(u8 *arg0, void *arg1) {
    s32 result = 0;

    switch (arg0[0x21]) {
    case 1:
        result = func_82404378(arg0);
        break;
    case 2:
        result = Fragment13_HandleConfirmationInput(arg0);
        break;
    case 3:
        result = func_824043D8(arg0);
        break;
    case 0:
        result = func_82404360(arg0);
        break;
    case 4:
        result = func_82404430(arg0);
        break;
    }
    if (arg0[0x21] != 0 && arg0[0x21] != 4) {
        func_81600A34(arg1, arg0, result, *(s16 *)arg0, func_82404230(arg0),
                      *(s16 *)(arg0 + 4), *(s16 *)(arg0 + 6));
    }
}

struct Fragment13DialogView {
    s16 x, y, width, height;
    s32 title, leftLabel, rightLabel;
    s32 leftImage, rightImage;
    f32 phase;
    s8 selected;
    u8 state;
};
extern u8 D_82408BB0[];
extern s32 func_81600DA8(void *, void *);
extern void func_80006F70(Gfx **, s16, s16, s16, s16);
extern void func_8004989C(s32);
void Fragment13_DrawConfirmationDialog(struct Fragment13DialogView *arg0, void *arg1) {
    s32 x;
    s32 y;
    s32 width;
    s32 height;

    x = arg0->x;
    y = func_82404230(arg0);
    width = arg0->width;
    height = arg0->height;
    if (arg0->state != 0 && arg0->state != 4) {
        if (func_81600DA8(arg1, arg0)) {
            func_82401198(x, y, width, height);
            Fragment13_DrawColoredPanelFill(x + 2, y + 2, width - 6, height - 6, D_82408BB0);
            func_80006F70(&D_800D0510, x + 2, y + 2, width - 6, height);
            gSPDisplayList(D_800D0510++, D_80094E38);
            func_8004D19C(x + 25, y + 54, arg0->selected == 0 ? arg0->leftImage : arg0->rightImage, 0, 0);
            func_8004D19C(x + 102, y + 54, arg0->selected == 0 ? arg0->rightImage : arg0->leftImage, 0, 0);
            gSPDisplayList(D_800D0510++, D_80094F50);
            func_800498C4();
            func_800496A4(2, 0);
            func_8004989C(14);
            func_800495BC(x + 10, y + 8, arg0->title);
            func_800495BC(x + 43, y + 56, arg0->leftLabel);
            func_800495BC(x + 120, y + 56, arg0->rightLabel);
            func_800499EC();
            func_80006F70(&D_800D0510, 0, 0, 320, 240);
        }
    }
}

s32 func_824048A0(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = (*(s32 *)((u8 *)(arg0) + (0x1DC)));
    if ((temp_v0 == 4) && (arg1 == (*(s32 *)((u8 *)(arg0) + (0x1A8))))) {
        return 1;
    }
    if ((temp_v0 == 5) && (arg1 == (*(s32 *)((u8 *)(arg0) + (0x1A4))))) {
        return 1;
    }
    return 0;
}

void Fragment13_InitGroupedList(struct Fragment13GroupedList *arg0) {
    s32 index;
    s32 group;
    s32 item;

    /* Keep the body on its own source line for the original IDO schedule. */
    for (index = 0; index < 128; index++) {
        arg0->entries[index] = -1;
    }
    index = 0;
    for (group = 0; group < 8; group++) {
        arg0->counts[group] = 0;
        arg0->starts[group] = index;
        for (item = 0; item < *(u16 *)((u8 *)&D_82407370[group] + 0x3A); item++) {
            arg0->entries[index] = item;
            index++;
            arg0->counts[group]++;
        }
        arg0->entries[index] = -1;
        index++;
    }
}

s32 Fragment13_GetGroupedListItem(struct Fragment13GroupedList *arg0, s32 group, s32 index) {
    if (arg0->counts[group] <= index) {
        return -1;
    }
    return (arg0->entries + arg0->starts[group])[index];
}

extern s32 func_8005F9A4(s32, s32);

void Fragment13_InitAvailableGroupedList(struct Fragment13GroupedList *arg0, s32 handle) {
    s32 cursor = 0;
    s32 group;
    s32 item;
    struct Fragment13GroupItem *entry;

    for (group = 0; group < 8; group++) {
        arg0->counts[group] = 0;
        arg0->starts[group] = cursor;
        for (item = 0; item < D_82407370[group].count; item++) {
            entry = &D_82407370[group].items[item];
            if (entry->id == 0x2A4 || entry->id == 0x2AF || func_8005F9A4(handle, (u16)entry->id)) {
                arg0->entries[cursor] = item;
                cursor++;
                arg0->counts[group]++;
            }
        }
        arg0->entries[cursor] = -1;
        cursor++;
    }
}

struct Fragment13GroupSelection {
    u8 prefix[0x54];
    struct Fragment13GroupedList list;
    u8 gap[0x1C];
    s32 handle;
    s32 current[8];
    s32 previous[8];
};

s32 Fragment13_HasSelectionChanges(struct Fragment13GroupSelection *arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (arg0->current[i] != arg0->previous[i]) {
            return 1;
        }
    }
    return 0;
}

extern u8 D_82408F38[];
extern u8 func_8005FFB4(s32, u8);

void Fragment13_LoadGroupSelections(struct Fragment13GroupSelection *arg0) {
    s32 group;
    s32 item;
    u8 value;

    for (group = 0; group < 8; group++) {
        value = func_8005FFB4(arg0->handle, D_82408F38[group]);
        arg0->current[group] = -1;
        for (item = 0; item < arg0->list.counts[group]; item++) {
            if (D_824073A4[group].items[arg0->list.entries[arg0->list.starts[group] + item]].value == value) {
                arg0->current[group] = item;
                break;
            }
        }
    }
}

extern void func_80057908(u8);
extern void func_80057944(u8);
extern void func_81B00E58(u8, u8, u8);
extern void func_81B00F78(u8);

void Fragment13_ApplyGroupSelections(struct Fragment13GroupSelection *arg0) {
    s32 group;
    s32 itemIndex;
    struct Fragment13GroupItem *entry;
    s32 key;
    s32 value;

    func_80057908(*((u8 *)arg0 + 0x193));
    for (group = 0; group < 8; group++) {
        value = D_82407370[group].defaultValue;
        key = D_82408F38[group];
        if (arg0->current[group] >= 0) {
            itemIndex = (arg0->list.entries + arg0->current[group])[arg0->list.starts[group]];
            entry = &D_82407370[group].items[itemIndex];
            if (func_8005F9A4(arg0->handle, (u16)entry->id)) {
                value = entry->value;
            } else if (key == 0 && entry->value == 2) {
                value = entry->value;
            } else if (key == 3 && entry->value == 16) {
                value = entry->value;
            }
        }
        func_81B00E58(*((u8 *)arg0 + 0x193), (u8)key, (u8)value);
    }
    func_81B00F78(*((u8 *)arg0 + 0x193));
    func_80057944(*((u8 *)arg0 + 0x193));
    *(s32 *)((u8 *)arg0 + 0x210) = 1;
}

extern void func_81A00074(s32, s32);
void func_82404DD8(s32 arg0) {
    func_81A00074(arg0 + 0x24C, *(s32 *)(arg0 + 0x190));
}

void func_82404E00(void *arg0, void *arg1, void *arg2, f32 arg3)
{
  f32 temp_fa1;
  f32 temp_fv0;
  f32 temp_fv1;
  f32 new_var;
 do { temp_fv0 = *((f32 *) (((u8 *) arg1) + 0)); *((f32 *) (((u8 *) arg0) + 0)) = (f32) ((((*((f32 *) (((u8 *) arg2) + 0))) - temp_fv0) * arg3) + temp_fv0); temp_fv1 = *((f32 *) (((u8 *) arg1) + 4)); new_var = arg3; *((f32 *) (((u8 *) arg0) + 4)) = (f32) ((((*((f32 *) (((u8 *) arg2) + 4))) - temp_fv1) * new_var) + temp_fv1); temp_fa1 = *((f32 *) (((u8 *) arg1) + 8)); *((f32 *) (((u8 *) arg0) + 8)) = (f32) ((((*((f32 *) (((u8 *) arg2) + 8))) - temp_fa1) * new_var) + temp_fa1); } while (0);
}

extern f32 (*D_8160BD1C)(f32);

void Fragment13_UpdateGroupTransition(void *arg0) {
    f32 factor;

    if ((*(s32 *)((u8 *)arg0 + 0x1DC)) != (*(s32 *)((u8 *)arg0 + 0x1E0))) {
        (*(f32 *)((u8 *)arg0 + 0x200)) += func_82403F10();
        if ((*(f32 *)((u8 *)arg0 + 0x200)) >= 20.0f) {
            (*(s32 *)((u8 *)arg0 + 0x1E0)) = (*(s32 *)((u8 *)arg0 + 0x1DC));
            (*(f32 *)((u8 *)arg0 + 0x200)) = 0.0f;
        }
    }
    factor = D_8160BD1C((*(f32 *)((u8 *)arg0 + 0x200)) / 20.0f);
    func_82404E00((u8 *)arg0 + 0x174, (u8 *)&D_82407370[(*(s32 *)((u8 *)arg0 + 0x1E0))] + 0x1C, (u8 *)&D_82407370[(*(s32 *)((u8 *)arg0 + 0x1DC))] + 0x1C, factor);
    func_82404E00((u8 *)arg0 + 0x180, (u8 *)&D_82407370[(*(s32 *)((u8 *)arg0 + 0x1E0))] + 0x28, (u8 *)&D_82407370[(*(s32 *)((u8 *)arg0 + 0x1DC))] + 0x28, factor);
}

extern u8 D_82407DE8;
extern u8 D_82407DF0;
extern u8 D_82408160;
extern u8 D_82408168;
void func_82404F64(void *arg0) {
    (*(u8 *)((u8 *)(&D_82408160) + (0))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x47)));
    (*(u8 *)((u8 *)(&D_82408160) + (1))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x48)));
    (*(u8 *)((u8 *)(&D_82408160) + (2))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x49)));
    (*(u8 *)((u8 *)(&D_82408168) + (0))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x4A)));
    (*(u8 *)((u8 *)(&D_82408168) + (1))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x4B)));
    (*(u8 *)((u8 *)(&D_82408168) + (2))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x4C)));
    (*(u8 *)((u8 *)(&D_82407DE8) + (0))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x4D)));
    (*(u8 *)((u8 *)(&D_82407DE8) + (1))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x4E)));
    (*(u8 *)((u8 *)(&D_82407DE8) + (2))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x4F)));
    (*(u8 *)((u8 *)(&D_82407DF0) + (0))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x50)));
    (*(u8 *)((u8 *)(&D_82407DF0) + (1))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x51)));
    (*(u8 *)((u8 *)(&D_82407DF0) + (2))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x52)));
}

s16 MathUtil_Atan2s(f32 y, f32 x);
void func_82404FE8(s16 *arg0, s16 *arg1, void *arg2) {
    f32 temp_ft4;
    f32 temp_fv1;

    temp_fv1 = (*(f32 *)((u8 *)(arg2) + (0)));
    temp_ft4 = (*(f32 *)((u8 *)(arg2) + (8)));
    *arg0 = MathUtil_Atan2s(sqrtf((temp_fv1 * temp_fv1) + (temp_ft4 * temp_ft4)), (*(f32 *)((u8 *)(arg2) + (4))));
    *arg1 = MathUtil_Atan2s((*(f32 *)((u8 *)(arg2) + (8))), (*(f32 *)((u8 *)(arg2) + (0))));
}

extern void func_8005F37C(u8, void *, void *, void *, void *);
void func_8240504C(void *arg0, s32 arg1) {
    *(f32 *)((u8 *)arg0 + 0) = 0.0f;
    if ((arg1 >= 0) && (arg1 < 4)) {
        func_8005F37C((u8)arg1, (u8 *)arg0 + 4, (u8 *)arg0 + 6, (u8 *)arg0 + 7, (u8 *)arg0 + 8);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_824050A8.s")

void Fragment13_LerpRgb(void *arg0, void *arg1, void *arg2, f32 arg3) {
    u8 *dst = arg0;
    u8 *a = arg1;
    u8 *b = arg2;
    dst[0] = (u32)((f32)(u32)a[0] + (f32)(b[0] - a[0]) * arg3);
    dst[1] = (u32)((f32)(u32)a[1] + (f32)(b[1] - a[1]) * arg3);
    dst[2] = (u32)((f32)(u32)a[2] + (f32)(b[2] - a[2]) * arg3);
}

void func_82405494(void *arg0, void *arg1, void *arg2, f32 arg3)
{
  f32 temp_fa1;
  f32 temp_fv0;
  f32 temp_fv1;
  f32 new_var;
 do { temp_fv0 = *((f32 *) (((u8 *) arg1) + 0)); *((f32 *) (((u8 *) arg0) + 0)) = (f32) ((((*((f32 *) (((u8 *) arg2) + 0))) - temp_fv0) * arg3) + temp_fv0); temp_fv1 = *((f32 *) (((u8 *) arg1) + 4)); new_var = arg3; *((f32 *) (((u8 *) arg0) + 4)) = (f32) ((((*((f32 *) (((u8 *) arg2) + 4))) - temp_fv1) * new_var) + temp_fv1); temp_fa1 = *((f32 *) (((u8 *) arg1) + 8)); *((f32 *) (((u8 *) arg0) + 8)) = (f32) ((((*((f32 *) (((u8 *) arg2) + 8))) - temp_fa1) * new_var) + temp_fa1); } while (0);
}

extern void func_82405494(void *arg0, void *arg1, void *arg2, f32 arg3);
void func_824054E4(u8 *arg0, u8 *arg1, u8 *arg2, f32 arg3) {
    s32 i;
    for (i = 0; i < 0x20; i += 0x10) {
        Fragment13_LerpRgb(arg0 + i, arg1 + i, arg2 + i, arg3);
        func_82405494(arg0 + i + 4, arg1 + i + 4, arg2 + i + 4, arg3);
    }
    Fragment13_LerpRgb(arg0 + 0x20, arg1 + 0x20, arg2 + 0x20, arg3);
    Fragment13_LerpRgb(arg0 + 0x23, arg1 + 0x23, arg2 + 0x23, arg3);
    Fragment13_LerpRgb(arg0 + 0x26, arg1 + 0x26, arg2 + 0x26, arg3);
    Fragment13_LerpRgb(arg0 + 0x29, arg1 + 0x29, arg2 + 0x29, arg3);
    Fragment13_LerpRgb(arg0 + 0x2C, arg1 + 0x2C, arg2 + 0x2C, arg3);
    arg0[0x2F] = (u32)((f32)(u32)arg1[0x2F] + (f32)((s32)arg2[0x2F] - (s32)arg1[0x2F]) * arg3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82405718.s")

extern void *Vec3s_FromVec3f(void *, void *);
extern void func_80038390(void *, void *, u8, u8, u8);
extern void func_800383DC(void *, s16, s16);
void Fragment13_UpdateSceneLightNode(s32 arg0, void *arg1) {
    u8 *data = *(u8 **)((u8 *)arg1 + 0x14);
    s32 kind;
    s16 vector[3];
    s16 pitch;
    s16 yaw;

    if (arg0 == 2) {
        *(u8 *)((u8 *)arg1 + 0x1B) = 0;
        *(u8 *)((u8 *)arg1 + 0x18) = data[0x24];
        *(u8 *)((u8 *)arg1 + 0x19) = data[0x25];
        *(u8 *)((u8 *)arg1 + 0x1A) = data[0x26];
        kind = data[6];
        if (kind >= 19 && kind < 22) {
            Vec3s_FromVec3f(vector, data + 0x28);
            func_80038390(arg1, vector, 18, 0, 0);
        } else {
            func_82404FE8(&pitch, &yaw, data + 0x28);
            func_800383DC(arg1, pitch, yaw);
        }
    }
}

void Fragment13_UpdateSceneDirectionalLightNode(s32 arg0, void *arg1) {
    u8 *node = (u8 *)arg1;
    u8 *data = *(u8 **)(node + 0x14);
    s16 pitch;
    s16 yaw;

    if (arg0 == 2) {
        func_82404FE8(&pitch, &yaw, data + 0x38);
        *(s16 *)(node + 0x1C) = pitch;
        *(s16 *)(node + 0x1E) = yaw;
        node[0x1B] = 0;
        node[0x18] = data[0x34];
        node[0x19] = data[0x35];
        node[0x1A] = data[0x36];
    }
}

void func_82405A58(s32 arg0, void *arg1) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg1) + (0x14)));
    if (arg0 == 2) {
        (*(u8 *)((u8 *)(arg1) + (0x18))) = (u8) (*(u8 *)((u8 *)(temp_v0) + (0x44)));
        (*(u8 *)((u8 *)(arg1) + (0x19))) = (u8) (*(u8 *)((u8 *)(temp_v0) + (0x45)));
        (*(u8 *)((u8 *)(arg1) + (0x1A))) = (u8) (*(u8 *)((u8 *)(temp_v0) + (0x46)));
    }
}

void Fragment13_UpdateClockHourHand(s32 arg0, void *arg1) {
    u8 *data = *(u8 **)((u8 *)arg1 + 0x14);
    s32 angle;

    if (arg0 == 2) {
        /* Preserve the integer angle and truncate before negating. */
        angle = (s32)((((f32)data[7] + *(f32 *)data / 60.0f) / 60.0f + (f32)data[6]) / 12.0f * 65535.0f);
        *(s16 *)((u8 *)arg1 + 0x22) = -angle;
    }
}

void Fragment13_UpdateClockMinuteHand(s32 arg0, void *arg1) {
    u8 *data = *(u8 **)((u8 *)arg1 + 0x14);
    f32 value;

    if (arg0 == 2) {
        /* The fractional term comes first in the original IDO expression. */
        value = (f32)data[8] / 60.0f + (f32)data[7];
        *(s16 *)((u8 *)arg1 + 0x22) = (s16)(-(value * 65535.0f / 60.0f));
    }
}

void func_82405BAC(s32 arg0, void *arg1) {
    u8 *ptr = *(u8 **)((u8 *)arg1 + 0x14);
    if (arg0 == 2) {
        f32 value = (f32)ptr[8];
        *(s16 *)((u8 *)arg1 + 0x22) = (s16)(-(value * 65535.0f / 60.0f));
    }
}

struct Fragment13CameraState {
    u8 prefix[0x174];
    struct Fragment13MotionVector eye;
    struct Fragment13MotionVector target;
    u8 gap[0x50];
    s32 group;
    u8 gap1[0x18];
    f32 offsetX;
    f32 offsetZ;
};
extern struct Fragment13MotionVector D_82408F20;
extern struct Fragment13MotionVector D_82408F2C;
extern f32 D_82408BAC;
extern f32 D_82408BA4;
extern f32 D_82408BA8;
extern f32 D_82408BA0;

void Fragment13_ResetGroupCamera(struct Fragment13CameraState *arg0) {
    arg0->target = D_82407370[arg0->group].target;
    arg0->target.y = D_82408F2C.y;
    arg0->offsetX = arg0->target.x - D_82408F2C.x;
    arg0->offsetZ = arg0->target.z - D_82408F2C.z;
    if (arg0->offsetZ < D_82408BAC) {
        arg0->offsetZ = D_82408BAC;
    }
    if (arg0->offsetX < D_82408BA4) {
        arg0->offsetX = D_82408BA4;
    }
    if (D_82408BA8 < arg0->offsetZ) {
        arg0->offsetZ = D_82408BA8;
    }
    if (D_82408BA0 < arg0->offsetX) {
        arg0->offsetX = D_82408BA0;
    }
    arg0->eye = D_82408F20;
    arg0->eye.x += arg0->offsetX;
    arg0->eye.z += arg0->offsetZ;
}

extern void func_8005D9E0(s32, s32 *);
extern s32 Fragment13_FindNearestGroup(struct Fragment13MotionVector *);
extern s8 *HAL_Strcpy(s8 *, s8 *);
extern void func_80006158(void);
extern void func_82405718(void *, void *);
struct Fragment13GroupState {
    u8 prefix[0x54];
    struct Fragment13GroupedList list;
    struct Fragment13MotionVector eye;
    struct Fragment13MotionVector target;
    s32 field18C;
    s32 handle;
    s32 current[8];
    s32 previous[8];
    s32 end;
    s32 start;
    s32 group;
    s32 previousGroup;
    s32 state;
    s32 targetState;
    s32 previousState;
    s32 selected;
    s32 field1F4;
    f32 offsetX;
    f32 offsetZ;
    f32 timer;
    f32 transition;
    f32 selectionTimer;
    s32 idle;
    s32 dirty;
    s32 field214;
    s8 name[16];
    u8 panel[0x24];
};
extern void func_8240429C(u8 *arg0);
extern void func_8240504C(void *arg0, s32 arg1);
extern f32 D_82408BAC;
void Fragment13_InitGroupState(struct Fragment13GroupState *arg0, s32 handle, s32 arg2, s32 arg3) {
    s32 i;
    struct Fragment13MotionVector *target;
    s32 info[4];
    struct Fragment13MotionVector position;
    arg0->handle = handle;
    Fragment13_InitGroupedList(&arg0->list);
    Fragment13_InitAvailableGroupedList(&arg0->list, handle);
    arg0->eye = D_82408F20;
    target = &arg0->target;
    *target = D_82408F2C;
    func_8005D9E0(handle, (s32 *)info);
    HAL_Strcpy(arg0->name, (s8 *)info + 2);
    position = *target;
    arg0->group = arg0->previousGroup = Fragment13_FindNearestGroup(&position);
    arg0->offsetX = 0.0f;
    arg0->offsetZ = D_82408BAC;
    arg0->idle = 1;
    arg0->dirty = 0;
    arg0->state = 0;
    arg0->previousState = 0;
    arg0->timer = 0.0f;
    arg0->transition = 0.0f;
    arg0->selectionTimer = 0.0f;
    arg0->field18C = arg3;
    arg0->targetState = arg0->idle;
    arg0->field214 = arg2;
    arg0->selected = -1;
    arg0->field1F4 = 0;
    /* The original counter-only loop is present at 0x82405E54-0x82405E60. */
    for (i = 0; i < 8; i++) {
    }
    Fragment13_LoadGroupSelections((struct Fragment13GroupSelection *)arg0);
    func_80006158();
    func_8240504C(arg0, handle);
    func_82405718((u8 *)arg0 + 0x24, arg0);
    func_8240429C(arg0->panel);
    for (i = 0; i < 8; i++) {
        arg0->previous[i] = arg0->current[i];
    }
}

extern Gfx *D_800D0510;
extern void func_80038E14(void *, s32, s32, s32, f32, f32, f32, s32);
extern void GeoCamera_SetPerspective(void *, f32, f32, f32);
extern void Gfx_SetScissorRect(Gfx **, s32, s32, s32, s32);
s32 func_82405EE0(s32 arg0, void *arg1) {
    void *record;

    record = *(void **)((u8 *)arg1 + 0x14);
    if (arg0 == 0) {
        return 1;
    }
    func_80038E14(arg1, *(s32 *)((u8 *)record + 0x174), *(s32 *)((u8 *)record + 0x178), *(s32 *)((u8 *)record + 0x17C), *(f32 *)((u8 *)record + 0x180), *(f32 *)((u8 *)record + 0x184), *(f32 *)((u8 *)record + 0x188), 0);
    GeoCamera_SetPerspective(arg1, 23.1f, 64.0f, 10000.0f);
    if (arg0 == 5) {
        Gfx_SetScissorRect(&D_800D0510, 0xD, 0x27, 0x126, 0xA1);
    }
    return 1;
}

s32 Fragment13_StepVectorToward(struct Fragment13MotionVector *arg0, struct Fragment13MotionVector *arg1, f32 step) {
    f32 dx, dy, dz;
    f32 distance;

    dx = arg1->x - arg0->x;
    dy = arg1->y - arg0->y;
    dz = arg1->z - arg0->z;
    distance = sqrtf(dx * dx + dy * dy + dz * dz);
    if (step < 0.0f || distance < step) {
        *arg0 = *arg1;
        return 0;
    }
    arg0->x = arg0->x + dx / distance * step;
    arg0->y = arg0->y + dy / distance * step;
    arg0->z = arg0->z + dz / distance * step;
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82406060.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_8240641C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82406560.s")

extern void func_82402B1C(void *, void *, f32, s16, f32, s32, s32, s32);
extern void func_8240330C(void *, s32, f32, s32, s32, f32);
extern f32 func_82407088(void *arg0);
extern f32 Fragment13_GetInterpolatedListPosition(void *);
void Fragment13_UpdateGroupListTransition(void *arg0, void *arg1) {
    f32 factor;

    factor = D_8160BD08(*(f32 *)((u8 *)arg0 + 0x204) / 10.0f);
    if (*(s32 *)((u8 *)arg0 + 0x1E4) == *(s32 *)((u8 *)arg0 + 0x1EC)) {
        *(f32 *)((u8 *)arg0 + 0x204) = func_82403F10() + *(f32 *)((u8 *)arg0 + 0x204);
        if (*(f32 *)((u8 *)arg0 + 0x204) >= 10.0f) {
            *(f32 *)((u8 *)arg0 + 0x204) = 10.0f;
        }
    } else {
        *(f32 *)((u8 *)arg0 + 0x204) = *(f32 *)((u8 *)arg0 + 0x204) - func_82403F10();
        if (*(f32 *)((u8 *)arg0 + 0x204) <= 0.0f) {
            *(f32 *)((u8 *)arg0 + 0x204) = 0.0f;
            if (*(s32 *)((u8 *)arg0 + 0x1EC) == 2 && *(s32 *)((u8 *)arg0 + 0x1E4) == 1) {
                func_800226C0(0xAA);
            } else if (*(s32 *)((u8 *)arg0 + 0x1E4) == 2) {
                func_800226C0(0xA9);
            }
            *(s32 *)((u8 *)arg0 + 0x1EC) = *(s32 *)((u8 *)arg0 + 0x1E4);
        }
    }
    switch (*(s32 *)((u8 *)arg0 + 0x1EC)) {
    case 0:
        return;
    case 1:
        func_82402B1C(arg1, (u8 *)arg0 + 0x54, func_82407088(arg0), -1, factor, 184, 1,
                      *(s32 *)((u8 *)arg0 + 0x1E0) < *(s32 *)((u8 *)arg0 + 0x1DC));
        return;
    case 2:
        func_8240330C(arg1, *(s32 *)((u8 *)arg0 + 0x1DC), factor, *(s32 *)((u8 *)arg0 + 0x1D4),
                      *(s32 *)((u8 *)arg0 + 0x1D8), *(f32 *)((u8 *)arg0 + 0x208) / 6.0f);
        func_82402B1C(arg1, (u8 *)arg0 + 0x54, Fragment13_GetInterpolatedListPosition(arg0), (s16)(*(s32 *)((u8 *)arg0 + 0x1DC)),
                      factor, 154, 0, *(s32 *)((u8 *)arg0 + 0x1E0) < *(s32 *)((u8 *)arg0 + 0x1DC));
        return;
    }
}

extern s32 D_82408BB8;
extern void func_824050A8(void *, f32);
extern void func_82406060(void *);
extern void func_8240641C(void *);
extern void func_82406560(void *);
void Fragment13_UpdateGroupScene(u8 *arg0, void *arg1) {
    s32 changed;
    u8 *dialog;

    changed = *(s32 *)(arg0 + 0x1E4) != *(s32 *)(arg0 + 0x1E8);
    func_824050A8(arg0, D_82408BB8 != 0 ? 1.0f : 3000.0f);
    func_82404F64(arg0);
    func_82405718(arg0 + 0x24, arg0);
    func_81600A34(arg1, (void *)1, 0, 0, 0, 320, 240);
    func_81600A34(arg1, (void *)4, changed, 0, 0, 320, 38);
    func_81600A34(arg1, (void *)5, changed, 0, 202, 320, 38);
    func_81600A34(arg1, (void *)7, changed, 0, 38, 12, 164);
    func_81600A34(arg1, (void *)6, changed, 308, 38, 12, 164);
    func_81600A34(arg1, (void *)(u32)*(s32 *)(arg0 + 0x214), 1, 11, 37, 300, 167);
    switch (*(u32 *)(arg0 + 0x1E8) = *(u32 *)(arg0 + 0x1E4)) {
    case 0:
        func_82406060(arg0);
        break;
    case 1:
        func_8240641C(arg0);
        break;
    case 2:
        func_82406560(arg0);
        break;
    case 3:
        switch (func_82404564(arg0 + 0x228)) {
        case 0:
            Fragment13_ApplyGroupSelections((struct Fragment13GroupSelection *)arg0);
            *(u32 *)(arg0 + 0x1E4) = 4;
            func_800226C0(0x14A);
            break;
        case 1:
            *(s32 *)(arg0 + 0x210) = 0;
            *(u32 *)(arg0 + 0x1E4) = 4;
            break;
        case 2:
            *(u32 *)(arg0 + 0x1E4) = 0;
            break;
        }
        break;
    case 4:
        return;
    }
    dialog = arg0 + 0x228;
    Fragment13_UpdateGroupListTransition(arg0, arg1);
    Fragment13_UpdateConfirmationDialog(dialog, arg1);
}

s32 func_82406CCC(u8 *arg0) {
    return *(s32 *)(arg0 + 0x1E4) == 4;
}

extern void func_82402E28(s32, void *, f32, s32, f32, s32, s32, s32);
extern void func_82403624(s32, void *, s32, f32, s32, s32, f32);
void func_82406CDC(void *arg0, s32 arg1) { f32 scale; s32 state; scale = D_8160BD08(*(f32 *)((u8 *)arg0 + 0x204) / 10.0f); state = *(s32 *)((u8 *)arg0 + 0x1EC); switch (state) { case 0: return; case 1: func_82402E28(arg1, (u8 *)arg0 + 0x54, func_82407088(arg0), -1, scale, 0xB8, 1, *(s32 *)((u8 *)arg0 + 0x1E0) < *(s32 *)((u8 *)arg0 + 0x1DC)); return; case 2: func_82403624(arg1, arg0, *(s32 *)((u8 *)arg0 + 0x1DC), scale, *(s32 *)((u8 *)arg0 + 0x1D4), *(s32 *)((u8 *)arg0 + 0x1D8), *(f32 *)((u8 *)arg0 + 0x208) / 6.0f); func_82402E28(arg1, (u8 *)arg0 + 0x54, Fragment13_GetInterpolatedListPosition(arg0), (s16)*(s32 *)((u8 *)arg0 + 0x1DC), scale, 0x9A, 0, *(s32 *)((u8 *)arg0 + 0x1E0) < *(s32 *)((u8 *)arg0 + 0x1DC)); return; } }

extern void func_8000766C(Gfx **, s32, s32, s32, s32);
extern void func_8003C6B8(s32);
extern void func_81A0022C(void *);
void Fragment13_DrawGroupScene(u8 *arg0, void *arg1) {
    s32 full;

    full = func_81600DA8(arg1, (void *)1);
    if (full || func_81600DA8(arg1, (void *)4)) {
        func_82403F58();
        switch (*(s32 *)(arg0 + 0x1E4)) {
        case 0:
            func_8240227C(1, (s32)(arg0 + 0x218));
            break;
        case 1:
            Fragment13_DrawSelectionFooter(1, (s32)(arg0 + 0x218));
            break;
        case 2:
            Fragment13_DrawSelectionHeader(1, (s32)(arg0 + 0x218));
            break;
        case 3:
            func_824021AC(1, (s32)(arg0 + 0x218));
            break;
        }
    }
    if (full || func_81600DA8(arg1, (void *)5)) {
        func_82404000();
        switch (*(s32 *)(arg0 + 0x1E4)) {
        case 0:
            func_8240227C(0, (s32)(arg0 + 0x218));
            break;
        case 1:
            Fragment13_DrawSelectionFooter(0, (s32)(arg0 + 0x218));
            break;
        case 2:
            Fragment13_DrawSelectionHeader(0, (s32)(arg0 + 0x218));
            break;
        case 3:
            func_824021AC(0, (s32)(arg0 + 0x218));
            break;
        }
    }
    if (full || func_81600DA8(arg1, (void *)7)) {
        func_824040A8();
    }
    if (full || func_81600DA8(arg1, (void *)6)) {
        func_82404150();
    }
    if (func_81600DA8(arg1, *(void **)(arg0 + 0x214))) {
        func_8000766C(&D_800D0510, 13, 39, 294, 161);
        func_80006F70(&D_800D0510, 13, 39, 294, 161);
        func_8003C6B8(*(s32 *)(arg0 + 0x214));
        func_80006F70(&D_800D0510, 0, 0, 320, 240);
        func_82401198(11, 37, 300, 167);
    }
    func_82406CDC(arg0, (s32)arg1);
    Fragment13_DrawConfirmationDialog((void *)(arg0 + 0x228), arg1);
    func_81A0022C(arg0 + 0x24C);
}

extern f32 (*D_8160BD1C)(f32);
f32 func_82407088(void *arg0) {
    f32 factor;
    f32 start;
    factor = D_8160BD1C(*(f32 *)((u8 *)arg0 + 0x200) / 20.0f);
    start = (f32)*(s32 *)((u8 *)arg0 + 0x1E0);
    return ((f32)*(s32 *)((u8 *)arg0 + 0x1DC) - start) * factor + start;
}

extern f32 (*D_8160BD00)(f32);
f32 Fragment13_GetInterpolatedListPosition(void *arg0) {
    f32 factor;
    f32 base;
    s32 start;
    s32 end;
    s32 limit;
    struct Fragment13GroupState *state;

    state = arg0;
    factor = D_8160BD00(state->selectionTimer / 6.0f);
    end = state->end;
    start = state->start;
    limit = state->list.counts[state->group];
    if (start >= limit) {
        start = limit;
    }
    base = (f32)start;
    if (end >= limit) {
        end = limit;
    }
    return ((f32)end - base) * factor + base;
}

s32 Fragment13_FindNearestGroup(struct Fragment13MotionVector *arg0) {
    s32 best = 100000000;
    s32 nearest = 0;
    s32 i;
    s32 distance;

    for (i = 0; i < 8; i++) {
        /* Inline terms retain the original two-at-a-time IDO loop. */
        distance = (s32)((arg0->x - D_82407370[i].x) * (arg0->x - D_82407370[i].x) + (arg0->z - D_82407370[i].z) * (arg0->z - D_82407370[i].z));
        if (distance < best) {
            best = distance;
            nearest = i;
        }
    }
    return nearest;
}

extern void func_824001C0(void *, s32 *, s32, s32, s32, void *);
void Fragment13_SyncSceneSelections(struct Fragment13GroupState *arg0, void *arg1, void *arg2) {
    s32 values[8];
    s32 i;

    for (i = 0; i < 8; i++) {
        values[i] = (arg0->list.entries + arg0->current[i])[arg0->list.starts[i]];
    }
    func_824001C0(arg1, values, arg0->group, (*(u8 *)((u8 *)arg0 + 6) >= 6 && *(u8 *)((u8 *)arg0 + 6) < 23), (arg0->state == 1 || arg0->state == 2), arg2);
}

/* Preserve the original trailing alignment NOPs at 0x82407344-0x8240734C. */
#pragma C_FUNCTION_PADDING(12)
#endif
