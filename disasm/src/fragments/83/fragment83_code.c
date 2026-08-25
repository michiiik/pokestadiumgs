#include "global.h"


#ifdef VERSION_US
extern Gfx* D_800D0510;
void func_82C00020(u8 r, u8 g, u8 b, u8 a) {
    gDPSetPrimColor(D_800D0510++, 0, 0, r, g, b, a);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00078.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C000B0.s")
#endif

#ifdef VERSION_US
extern void func_82C000B0(s32, s32, s32, s32);
void func_82C0012C(s32 arg0) {
    if (arg0 != 0) {
        u8 *value = (u8 *)(u32)arg0;
        func_82C000B0(value[0], value[1], value[2], 1);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00164.s")
#endif

#ifdef VERSION_US
extern void func_82C00164(s32, s32, s32, s32);
void func_82C002B8(u8 *arg0) {
    func_82C00164(*(s16 *)(arg0 + 0), *(s16 *)(arg0 + 2), *(u16 *)(arg0 + 4), *(u16 *)(arg0 + 6));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C002EC.s")
#endif

void func_82C003B4(void) {
}

#ifdef VERSION_US
extern void *func_8004C990(s32, s32);
extern void func_8004D1FC(void *);
void func_82C003BC(u16 arg0, u16 arg1) {
    void *value = func_8004C990(arg0, arg1);
    func_8004D1FC(value);
}
#endif

#ifdef VERSION_US
extern void func_8004D19C(s32, s32, void *, s32, s32);
void func_82C003F8(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    void *value = func_8004C990(arg2, arg3);
    func_8004D19C(arg0, arg1, value, 0, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00444.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00624.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00804.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C008BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C009F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00A70.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00AE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00C78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00F20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C019B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C01C38.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C01E24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C01E98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C01FE4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02078.s")
#endif

#ifdef VERSION_US
extern void func_80008648();
extern void func_800088DC();
extern void func_82C00C78();
extern void func_82C00F20();
extern void func_82C019B4();
extern void func_82C01C38();
extern void func_82C01E24();
extern void func_82C01E98();
extern void func_82C01FE4();
extern void func_82C02078();
void func_82C02328(void) {
    func_800088DC();
    func_82C00C78();
    func_82C00F20();
    func_82C019B4();
    func_82C01E24();
    func_82C01E98();
    func_82C01FE4();
    func_82C02078();
    func_82C01C38();
    func_80008648();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02390.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02440.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02664.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C026D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0273C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02834.s")
#endif

#ifdef VERSION_US
extern void func_82C02834(s32);
extern u8 D_82C04C38;

void func_82C02950(void) {
    (*(s8 *)((u8 *)(&D_82C04C38) + (0x124A))) = 0;
    (*(s8 *)((u8 *)(&D_82C04C38) + (0x124B))) = 0;
    (*(s16 *)((u8 *)(&D_82C04C38) + (0x1250))) = 0;
    (*(s8 *)((u8 *)(&D_82C04C38) + (0x1249))) = 1;
    func_82C02834(1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0298C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02A44.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02B30.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02B84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03134.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0329C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C033E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03450.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C034C8.s")
#endif

#ifdef VERSION_US
extern void func_8004C8C0(s32);
void func_82C03524(void) { func_8004C8C0(0x101); func_8004C8C0(0x102); func_8004C8C0(0x33); func_8004C8C0(0x79); func_8004C8C0(0x1B); func_8004C8C0(0x1C); func_8004C8C0(0x123); }
#endif

#ifdef VERSION_US
extern void func_8004C4B0();
void func_82C03574(void) { func_8004C4B0(21); func_8004C4B0(19); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0359C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03674.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C036E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0383C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03904.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03974.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03CA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03D50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03DC0.s")
#endif

#ifdef VERSION_US
extern s8 *func_8004C874(s32, s32);
extern s8 *func_8000B580(s8 *, s8 *);
s32 func_82C03EE0(s8 *arg0, s32 arg1, s32 arg2) {
    func_8000B580(arg0 + 4, func_8004C874(0x15, 7));
    func_8000B580(arg0 + 0x54, func_8004C874(0x15, 0x20));
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03F40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03FB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0405C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0412C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C041CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0423C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C04350.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0458C.s")
#endif

#ifdef VERSION_US
extern void func_8004C594(s32, s32);
extern void func_8004C8A0(s32 *, s32, s32, s32);
s32 func_82C026D4(s32);
extern s32 D_82C04C50;
extern u8 D_82C05E90;
void func_82C04778(void) {
    func_8004C594(3, func_82C026D4(D_82C04C50 + 0x14));
    func_8004C8A0(&D_82C05E90, 0x3C, 0x15, 4);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C047C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C04880.s")
#endif
