#include "global.h"


#ifdef VERSION_US
extern Gfx* D_800D0510;
void func_8FC00020(u8 r, u8 g, u8 b, u8 a) {
    gDPSetPrimColor(D_800D0510++, 0, 0, r, g, b, a);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC00078.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC000F4.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC00E90.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC00F48.s")
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
extern u32 D_8FC0C2D8;
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/84/fragment84_code/func_8FC01480.s")
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
extern u8 D_8FC02830;
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
extern u8 D_8FC02830;
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
