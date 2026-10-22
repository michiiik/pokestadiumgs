#include "global.h"


#ifdef VERSION_US
extern Gfx* D_800D0510;
void ParticleGfx_SetPrimColor_fragment84(u8 r, u8 g, u8 b, u8 a) {
    gDPSetPrimColor(D_800D0510++, 0, 0, r, g, b, a);
}
#endif

#ifdef VERSION_US
void func_8FC00078(u16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, (((((arg0 << 8) & 0xF800) | ((arg1 << 3) & 0x7C0) | ((arg2 >> 2) & 0x3E) | (arg3 & 1)) << 16) |
        (((arg0 << 8) & 0xF800) | ((arg1 << 3) & 0x7C0) | ((arg2 >> 2) & 0x3E) | (arg3 & 1))));
}
#endif

#ifdef VERSION_US
extern s32 func_8004C990(s32, s32, s32, s32);
extern void func_8004D1FC(s32);
void func_8FC000F4(s32 arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_a3;
    unsigned long long new_var;

    new_var = 0xFFFF;
    temp_a2 = arg0 & new_var;
    temp_a3 = arg1 & new_var;
    func_8004D1FC(func_8004C990(temp_a2, temp_a3, temp_a2, temp_a3));
}
void func_8FC000F4_padding(void) {}
#endif

#ifdef VERSION_US
extern u8 D_80094DE0[];
void func_8FC00138(s32 arg0, s32 arg1, s32 arg2) {
    gSPDisplayList(D_800D0510++, D_80094DE0);
    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, 0xFFC7FFC1);
    gDPFillRectangle(D_800D0510++, arg0, arg1, arg0 + arg2, arg1 + 2);
}
#endif

#ifdef VERSION_US
void func_8FC001E8(void) {}
void func_8FC001E8_padding(void) {}
void func_8FC001E8_padding2(void) {}
void func_8FC001E8_padding3(void) {}
void func_8FC001E8_padding4(void) {}
void func_8FC001E8_padding5(void) {}
#endif

#ifdef VERSION_US
/* mkdraft:Gfx_DrawTexturedFrame16 begin */
extern void GfxRect_DrawTextured(s16, s16, s16, s16, s16, s16, s16, s16, s32);

void Gfx_DrawTexturedFrame16(s16 x, s16 y, u16 width, u16 height) {
    if (width >= 32 && height >= 32) {
        func_8FC000F4(0x101, 4);
        GfxRect_DrawTextured(x, y, (s16)(width - 16), 16, 0, 0, 0x400, 0x400, 0);
        GfxRect_DrawTextured(x, (s16)(y + 16), (s16)(width - 16), (s16)(height - 32), 0, 0x1E0, 0x400, 0, 0);
        GfxRect_DrawTextured((s16)(x + width - 16), y, 16, 16, 0, 0x200, 0x400, 0x400, 0);
        GfxRect_DrawTextured((s16)(x + width - 16), (s16)(y + 16), 16, (s16)(height - 32), 0, 0x3E0, 0x400, 0, 0);
        GfxRect_DrawTextured(x, (s16)(y + height - 16), (s16)(width - 16), 16, 0, 0x400, 0x400, 0x400, 0);
        GfxRect_DrawTextured((s16)(x + width - 16), (s16)(y + height - 16), 16, 16, 0, 0x600, 0x400, 0x400, 0);
    }
}
/* mkdraft:Gfx_DrawTexturedFrame16 end */
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC003F8.s")
#endif

#ifdef VERSION_US
extern void func_8FC003F8(s32, s32, s32, s32, s32, s32, s32);
void func_8FC00558(void) {
    func_8FC003F8(0x3C, 0x4B, 0x91, 0x7D, 0x50, 0x50, 0xFF);
    func_8FC003F8(0xC8, 0x4B, 0x190, 0x7D, 0x50, 0x50, 0xFF);
    func_8FC003F8(0x8C, 0xC3, 0x168, 0x32, 0x50, 0x50, 0xFF);
    func_8FC003F8(0x3C, 0xF0, 0x109, 0xC8, 0x5A, 0x96, 0xFF);
    func_8FC003F8(0x140, 0xF0, 0x109, 0xC8, 0, 0xFF, 0x64);
    func_8FC003F8(0x82, 0xFF, 0x6E, 0x3C, 0xA, 0x78, 0xEB);
    func_8FC003F8(0x186, 0xFF, 0x6E, 0x3C, 0, 0xE1, 0x50);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC0069C.s")
#endif

#ifdef VERSION_US
extern u8 D_8FC02832;
extern u8 D_8FC0244C;
extern void Ui_DrawAnimatedTextureMarker(s16, s16);
void func_8FC00774(void) {
    u8 *record = (u8 *)((D_8FC02832 * 0x10) + &D_8FC0244C);

    switch (record[0]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        Ui_DrawAnimatedTextureMarker(*(u16 *)(record + 4) - 0x28, *(s16 *)(record + 6));
        break;
    }
}
#endif

#ifdef VERSION_US
extern void func_80049064(s32, s32, s32, s32);
s32 func_8004C874(s32, u8);
extern u8 D_8FC0242F;
extern u8 D_8FC02831;
void func_8FC007E0(void) {
    if (D_8FC02831 != 0) {
        func_80049064(0xDC, 0x64, 0, func_8004C874(0x4B, *(&D_8FC0242F + D_8FC02831)));
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC0082C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC009C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC00AC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC00B68.s")
#endif

#ifdef VERSION_US
extern u8 D_8FC02830;
extern Gfx *D_800D0510;
extern void BgStage_DrawFrame(void);
extern void func_80008648(void);
extern void GfxImage_FillCurrent(Gfx **, s32);
extern void func_8FC003F8(s32, s32, s32, s32, s32, s32, s32);
extern void func_8FC00558(void);
extern void func_8FC0069C(void);
extern void func_8FC00774(void);
extern void func_8FC00AC4(void);
extern void func_8FC00B68(void);
void func_8FC00E90(void) {
    BgStage_DrawFrame();
    if (D_8FC02830 == 2) {
        func_8FC003F8(0x96, 0x64, 0x154, 0x14A, 0x50, 0x50, 0xFF);
        func_8FC00B68();
    } else {
        GfxImage_FillCurrent(&D_800D0510, 0x89);
        func_8FC00558();
        func_8FC0069C();
        func_8FC00774();
        func_8FC00AC4();
    }
    func_80008648();
}
#endif

#ifdef VERSION_US
void func_8FC00F34(u8 *arg0, s32 arg1) {
    s32 *ptr = &arg1;
    s32 high = arg1 >> 8;
    arg0[0] = (u8)arg1;
    arg0[1] = (u8)((high & 0xFFFF) & 0xFFFF);
}
#endif

#ifdef VERSION_US
s32 func_8FC00F48(u32 *arg0, s32 arg1) {
    s32 result = 0;
    while ((u32)arg1-- > 0) {
        result += *(u8 *)arg0;
        result &= 0xFFFF;
        arg0 = (u32 *)((u8 *)arg0 + 1);
    }
    result += 0x83;
    return result & 0xFFFF;
}
#endif

#ifdef VERSION_US
s32 func_8FC00F48(u32 *, s32);
extern u8 D_8FC0C766;
extern u32 D_8FC0C2D8;
void func_8FC00F88(void) {
    (*(s8 *)((u8 *)(&D_8FC0C2D8) + (0x48C))) = 0x50;
    (*(s8 *)((u8 *)(&D_8FC0C2D8) + (0x48D))) = 0x33;
    func_8FC00F34(&D_8FC0C766, func_8FC00F48(&D_8FC0C2D8, 0x48C) & 0xFFFF);
}
#endif

#ifdef VERSION_US
extern void func_80060358(s32, void *);
void func_8FC00FD0(void) {
    func_80060358(0, &D_8FC0C2D8);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC00FF8.s")
#endif

#ifdef VERSION_US
void _bcopy(s32 *, s32, s32);
void func_800226C0(s32);
#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

M2C_UNK Deck_WriteEntries(u32 *, M2C_UNK, s32);     /* extern */
M2C_UNK Dma_CopyChunks(u32 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_80054E48(M2C_UNK);                     /* extern */
M2C_UNK func_80055948(M2C_UNK);                     /* extern */
s32 func_8006218C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_80062304(s32);                         /* extern */
M2C_UNK func_8FC00FF8(M2C_UNK *, u8);               /* extern */
extern s32 D_8FC02833;
extern u8 D_8FC02858;
extern s32 D_8FC02865;
extern u8 D_8FC07598;
extern s32 D_8FC075A5;
extern M2C_UNK D_8FC0C2E5;
extern M2C_UNK D_8FC0C468;
extern M2C_UNK D_8FC0C4C1;
extern M2C_UNK D_8FC0C644;
extern M2C_UNK D_8FC0C740;

void func_8FC01068(void) {
    s32 sp1C;
    s32 temp_v0;

    if (D_8FC02831 == 0) {
        _bcopy(&D_8FC02865, (s32) &D_8FC0C2E5, 0x16);
        _bcopy(&D_8FC075A5, (s32) &D_8FC0C4C1, 0x16);
        _bcopy(&D_8FC02833, (s32) &D_8FC0C740, 0x20);
        func_8FC00FF8(&D_8FC0C468, D_8FC02858);
        func_8FC00FF8(&D_8FC0C644, D_8FC07598);
        func_8FC00F88();
        Dma_CopyChunks(&D_8FC0C2D8, 0x03FEF000, 0x03FEF490);
        func_80055948(3);
        temp_v0 = func_8006218C(0x19, 0, 0, 1);
        sp1C = temp_v0;
        Deck_WriteEntries(&D_8FC0C2D8, 1, temp_v0);
        func_80062304(sp1C);
        func_80054E48(3);
        func_800226C0(2);
        return;
    }
    func_800226C0(5);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC0117C.s")
#endif

#ifdef VERSION_US
extern s32 func_8005D92C(s32);
extern u8 D_8FC02830;
extern s8 D_8FC0243C;
extern u8 D_8FC0C6FB;
void func_8FC01288(void) {
    if ((func_8005D92C(0) != 0xD) &&
        (*(u8 *)((u8 *)&D_8FC0243C + 0) != 0)) {
        *(u8 *)((u8 *)&D_8FC02830 + 1) = 2;
        return;
    }
    if (D_8FC0C6FB == 0) {
        *(u8 *)((u8 *)&D_8FC02830 + 1) = 3;
        return;
    }
    if (*(s8 *)((u8 *)&D_8FC02830 + 3) == 0) {
        *(u8 *)((u8 *)&D_8FC02830 + 1) = 5;
        return;
    }
    if ((*(s8 *)((u8 *)&D_8FC02830 + 0x35) == 0) ||
        (*(s8 *)((u8 *)&D_8FC02830 + 0x4D75) == 0)) {
        *(u8 *)((u8 *)&D_8FC02830 + 1) = 6;
        return;
    }
    if ((*(u8 *)((u8 *)&D_8FC02830 + 0x28) == 0) ||
        (*(u8 *)((u8 *)&D_8FC02830 + 0x4D68) == 0)) {
        *(u8 *)((u8 *)&D_8FC02830 + 1) = 7;
        return;
    }
    *(u8 *)((u8 *)&D_8FC02830 + 1) = 0;
}
#endif

#ifdef VERSION_US
extern u8 D_8FC02831; extern u8 D_8FC0C6FB; extern u8 func_8005D8CC(s32); extern s32 func_8005D92C(s32); extern void func_8FC00FD0(void); extern void func_80057908(u8); extern void func_8FC0117C(void); extern void func_8FC01288(void);
void func_8FC0135C(void) {
    s32 result;
    D_8FC02831 = 4;
    result = func_8005D8CC(0);
    if (result != 0) {
        if (result == 2) D_8FC02831 = 1;
    } else if (func_8005D92C(0) == 0xD) {
        func_8FC00FD0();
        func_80057908(0);
        if ((s32)D_8FC0C6FB > 0) { func_8FC0117C(); func_8FC01288(); } else D_8FC02831 = 3;
    } else D_8FC02831 = 2;
}
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
extern void func_8FC0117C();
extern void func_8FC01288();
extern s8 D_8FC0243C;
extern u8 D_8FC0C6FB;
void func_8FC01408(void) {
    func_80003F74((u8 *) &D_8FC0C2D8, (u8 *)0x03FEF000, (u8 *)0x03FEF490, 0);
    D_8FC0243C = 0;
    if ((s32) D_8FC0C6FB > 0) {
        func_8FC0117C();
        func_8FC01288();
    } else {
        D_8FC02831 = 3;
    }
    func_800226C0(2);
}
#endif

#ifdef VERSION_US
extern u8 D_8FC02832;
extern u8 D_8FC0244C;
extern u8 D_8FC0C776;
extern u8 D_8FC0C768;
extern void _bcopy(s32 *, s32, s32);
void func_8FC01480(void) {
    u8 *record = (u8 *)((D_8FC02832 * 0x10) + &D_8FC0244C);
    switch (record[0]) {
    case 4:
        _bcopy(*(s32 *)(record + 0xC), (s32)&D_8FC0C776, 0x20);
        *(u16 *)((u8 *)&D_8FC0C768 + 0x2E) = 0x1F;
        *(u16 *)((u8 *)&D_8FC0C768 + 0xC) = 0;
        *(s32 *)((u8 *)&D_8FC0C768 + 0x30) = 0;
        break;
    case 5:
        _bcopy(*(s32 *)(record + 0xC), (s32)&D_8FC0C776, 0x16);
        *(u16 *)((u8 *)&D_8FC0C768 + 0x2E) = 0x15;
        *(u16 *)((u8 *)&D_8FC0C768 + 0xC) = 0;
        *(s32 *)((u8 *)&D_8FC0C768 + 0x30) = 1;
        break;
    }
}
#endif

#ifdef VERSION_US
extern void _bcopy(s32 *, s32, s32);
extern u8 D_8FC0244C;
extern u8 D_8FC02832;
extern u8 D_8FC0C776;
void func_8FC01530(void) {
    u8 temp_v1;
    void *temp_v0;

    temp_v0 = (D_8FC02832 * 0x10) + &D_8FC0244C;
    temp_v1 = (*(u8 *)((u8 *)(temp_v0) + (0)));
    switch (temp_v1) {                              /* irregular */
    case 4:
        _bcopy(&D_8FC0C776, (*(s32 *)((u8 *)(temp_v0) + (0xC))), 0x20);
        return;
    case 5:
        _bcopy(&D_8FC0C776, (*(s32 *)((u8 *)(temp_v0) + (0xC))), 0x16);
        return;
    }
}
#endif

#ifdef VERSION_US
extern void func_8FC01480();
extern u8 D_8FC0C768;
void func_8FC015AC(void) {
    (*(s16 *)((u8 *)(&D_8FC0C768) + (0))) = 0xB4;
    (*(s16 *)((u8 *)(&D_8FC0C768) + (2))) = 0x6E;
    (*(s16 *)((u8 *)(&D_8FC0C768) + (4))) = 0x12C;
    (*(s16 *)((u8 *)(&D_8FC0C768) + (6))) = 0xD2;
    (*(s16 *)((u8 *)(&D_8FC0C768) + (8))) = 0;
    (*(s16 *)((u8 *)(&D_8FC0C768) + (0xA))) = 0;
    func_8FC01480();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC015F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC019B8.s")
#endif

#ifdef VERSION_US
extern s32 func_8FC019B8(void);
extern void func_8FC00B68(void);
extern void func_8FC01530(void);
extern void func_8FC01288(void);
extern void func_800226C0(s32);
extern u8 D_8FC02830;
s32 func_8FC01E28(void) {
    s32 sp1C;

    sp1C = func_8FC019B8();
    func_8FC00B68();
    if (sp1C == 1) {
        func_8FC01530();
        func_8FC01288();
        *(u8 *)&D_8FC02830 = 0;
    } else if (sp1C == 2) {
        func_800226C0(3);
        *(u8 *)&D_8FC02830 = 0;
    }
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC01E9C.s")
#endif

void func_8FC01FBC(void) {
}

#ifdef VERSION_US
extern void func_8FC01068(void);
extern void func_8FC01408(void);
extern void func_80060250(s32);
extern void func_8FC01288(void);
extern void func_800226C0(s32);
extern void func_8FC015AC(void);
extern u8 D_8FC02830;
void func_8FC01FC4(u8 *arg0) {
    switch (arg0[0]) {
    case 1:
        func_8FC01068();
        return;
    case 2:
        func_8FC01408();
        return;
    case 0:
        func_80060250(0);
        func_8FC01288();
        func_800226C0(2);
        return;
    case 4:
    case 5:
        func_8FC015AC();
        D_8FC02830 = 2;
        break;
    case 6:
        D_8FC02830 = 1;
        break;
    case 3:
        D_8FC02830 = 3;
        break;
    }
}
#endif

#ifdef VERSION_US
extern u16 D_8FC0C7A0;
extern u16 D_8FC0C79E;
#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

void func_8FC02074(void) {
    u8 *temp_s0;

    temp_s0 = (M2C_FIELD(&D_8FC02830, u8 *, 2) * 0x10) + &D_8FC0244C;
    if (D_8FC0C7A0 & 0x800) {
        M2C_FIELD(&D_8FC02830, u8 *, 2) = (u8) M2C_FIELD(temp_s0, u8 *, 8);
        func_800226C0(1);
    } else if (D_8FC0C7A0 & 0x400) {
        M2C_FIELD(&D_8FC02830, u8 *, 2) = (u8) M2C_FIELD(temp_s0, u8 *, 9);
        func_800226C0(1);
    } else if (D_8FC0C7A0 & 0x200) {
        M2C_FIELD(&D_8FC02830, u8 *, 2) = (u8) M2C_FIELD(temp_s0, u8 *, 0xA);
        func_800226C0(1);
    } else if (D_8FC0C7A0 & 0x100) {
        M2C_FIELD(&D_8FC02830, u8 *, 2) = (u8) M2C_FIELD(temp_s0, u8 *, 0xB);
        func_800226C0(1);
    }
    if (D_8FC0C79E & 0x8000) {
        func_8FC01FC4(temp_s0);
        return;
    }
    if (D_8FC0C79E & 0x4000) {
        func_8FC01FBC();
    }
}
#endif

#ifdef VERSION_US
extern s32 func_8FC01E28(void);
extern void func_8FC01E9C();
extern void func_8FC02074();
extern u8 D_8FC02830;
void func_8FC02168(void) {
    switch (D_8FC02830) {                           /* irregular */
    case 0:
        func_8FC02074();
        return;
    case 2:
        func_8FC01E28();
        return;
    case 1:
        func_8FC01E9C();
        return;
    }
}
#endif

#ifdef VERSION_US
extern void *D_80087200;
extern u8 D_8FC02438;
extern u16 D_8FC0C79C;
extern u16 D_8FC0C79E;
extern u16 D_8FC0C7A0;
void func_8FC021D0(void) {
    func_80064D28();
    if (D_8FC02438 != 0) {
        D_8FC0C79C = (*(u16 *)((u8 *)(D_80087200) + (6)));
        D_8FC0C79E = (*(u16 *)((u8 *)(D_80087200) + (8)));
        D_8FC0C7A0 = (*(u16 *)((u8 *)(D_80087200) + (0xC)));
        return;
    }
    D_8FC0C79C = 0;
    D_8FC0C79E = 0;
    D_8FC0C7A0 = 0;
}
#endif

#ifdef VERSION_US
extern void func_8FC00E90();
extern void func_8FC02168();
extern void func_8FC021D0();
void func_8FC02248(void) {
    do {
        func_8FC021D0();
        func_8FC02168();
        func_8FC00E90();
    } while (D_8FC02830 != 3);
}
#endif

#ifdef VERSION_US
extern void func_8004C8C0(s32);
void func_8FC0229C(void) {
    func_8004C8C0(0x154);
    func_8004C8C0(0xC1);
    func_8004C8C0(0x101);
    func_8004C8C0(0x102);
    func_8004C8C0(0x79);
    func_8004C8C0(0x1B);
    func_8004C8C0(0x1C);
    func_8004C8C0(0xAF);
}
#endif

#ifdef VERSION_US
extern void func_8004C4B0();
void func_8FC022F4(void) { func_8004C4B0(6); func_8004C4B0(75); }
#endif

#ifdef VERSION_US
extern void _bzero(s32 *, s32);
extern void func_8FC0135C();
void func_8FC0231C(s32 arg0) {
    func_8FC0229C();
    func_8FC022F4();
    _bzero(&D_8FC02830, 0x9AA8);
    (*(s8 *)((u8 *)(&D_8FC02830) + (0))) = 0;
    (*(s8 *)((u8 *)(&D_8FC02830) + (2))) = 0;
    func_8FC0135C();
}
#endif

#ifdef VERSION_US
extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern s32 StageContext_Allocate(s32, s32, s32, s32, s32, s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern void func_80047588(s32, s32);
extern void func_8004C09C(s32);
extern void func_80008514(s32);
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_80008574(void);
extern void func_80047610(void);
extern void Gfx_FreeDisplayListBuffers(void);
extern void func_8FC02248(void);
extern void func_8FC0231C(s32 arg0);
s32 fragment84_main(s32 arg0, s32 arg1) {
    s32 sp24;

    main_pool_push_state(0x52434544);
    sp24 = StageContext_Allocate(1, 0, 2, 0, 2, 1);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    func_80047588(0x1C, 0);
    func_8004C09C(0xB);
    func_8FC0231C(0);
    func_80008514(sp24);
    func_800086A4(2);
    StageFade_StartFromOpaque(0xA);
    func_8FC02248();
    func_80008574();
    func_80047610();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x52434544);
    return 0;
}
#endif
