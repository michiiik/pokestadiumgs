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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC00138.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC00218.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC003F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC00558.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC0069C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC00774.s")
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
extern void func_800088DC(void);
extern void func_80008648(void);
extern void GfxImage_FillCurrent(Gfx **, s32);
extern void func_8FC003F8(s32, s32, s32, s32, s32, s32, s32);
extern void func_8FC00558(void);
extern void func_8FC0069C(void);
extern void func_8FC00774(void);
extern void func_8FC00AC4(void);
extern void func_8FC00B68(void);
void func_8FC00E90(void) {
    func_800088DC();
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
void func_8FC00FD0(void) { func_80060358(0, &D_8FC0C2D8); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC00FF8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC01068.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC0117C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC01288.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC0135C.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC01E28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC01E9C.s")
#endif

void func_8FC01FBC(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC01FC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC02074.s")
#endif

#ifdef VERSION_US
extern void func_8FC01E28();
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC02368.s")
#endif
