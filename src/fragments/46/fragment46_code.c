#include "global.h"


#ifdef VERSION_US
extern void func_800226C0();

void func_8AE00020(void) {
    func_800226C0();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE00040.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE000C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE0014C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE001D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE00230.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE002AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE00314.s")
#endif

#ifdef VERSION_US
extern void *D_8AE084BC;
extern void *D_80094908;
extern void func_80038E14(void *, s32, s32, s32, f32, f32, f32, s32);
extern void GeoCamera_SetPerspective(void *, f32, f32, f32);
void func_8AE00380(void) {
    u8 *temp_v0;
    u8 *temp_v1;
    temp_v0 = (u8 *)D_8AE084BC + 0xB4;
    temp_v1 = (u8 *)D_8AE084BC + 0xA8;
    func_80038E14(D_8AE084BC,
        *(s32 *)(temp_v1 + 0), *(s32 *)(temp_v1 + 4), *(s32 *)(temp_v1 + 8),
        *(f32 *)(temp_v0 + 0), *(f32 *)(temp_v0 + 4), *(f32 *)(temp_v0 + 8), 0);
    GeoCamera_SetPerspective(D_8AE084BC, 30.0f, 100.0f, 12800.0f);
    D_80094908 = D_8AE084BC;
}
#endif

#ifdef VERSION_US
extern s32 main_pool_alloc(s32, s32);
extern s16 D_8AE0A15E;
extern s32 D_8AE0A164;
extern void func_8004D878(void *, s16, s32);
void func_8AE003F8(void) {
    D_8AE0A164 = main_pool_alloc(0xC80, 0);
    func_8004D878((void *)D_8AE0A164, D_8AE0A15E, 0);
}
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_80094E00[];
extern u8 D_80094EF8[];
extern u8 D_80094F50[];
void func_8AE0043C(void) {
    gSPDisplayList(D_800D0510++, D_80094E00);
    gDPSetEnvColor(D_800D0510++, 0xC8, 0xFF, 0xFF, 0xB4);
    gSPDisplayList(D_800D0510++, D_80094EF8);
    gSPDisplayList(D_800D0510++, D_80094F50);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE004C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE00AF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE00C1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE00C94.s")
#endif

#ifdef VERSION_US
extern f32 D_80128C54[];
void func_8AE00CBC(f32 arg0) {
    D_80128C54[1] = arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE00CC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE00E54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE00F24.s")
#endif

#ifdef VERSION_US
u8 *func_8AE00F84(u8 *arg0, u8 arg1) {
    do {
        if (arg0[1] == 0xFF) {
            return NULL;
        }
        if (arg0[1] == arg1) {
            return arg0;
        }
        arg0 += 5;
    } while (1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE00FC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE01164.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE011E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE01248.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE012B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE01334.s")
#endif

#ifdef VERSION_US
extern s32 D_8AE09B5C;
extern s32 D_8AE09E60;
extern s32 D_8AE09E64;

void func_8AE01394(void) {
    D_8AE09B5C = 0x1E;
    D_8AE09E60 = 0x1E;
    D_8AE09E64 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE013B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE01564.s")
#endif

#ifdef VERSION_US
extern void func_8AE013B4(); extern void _bzero(void *, s32);
void func_8AE015C4(s16 arg0, s16 arg1) { s32 pad; u8 sp1C[0x50]; _bzero(sp1C, 0x50); func_8AE013B4(sp1C, arg0, arg1); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE01600.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE01738.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE017A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE018C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE019A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE01A90.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE01B88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE01CCC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE01DC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE01EA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE01F74.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE020FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE02398.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE02470.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE02568.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE026C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE027B0.s")
#endif

#ifdef VERSION_US
extern void func_8AE027B0(s32, void *, u16 *, void *, s32);
extern u16 D_8AE0994C;
extern u8 D_8AE099B4[];
s32 func_8AE02868(s32 arg0, void *arg1) {
    u16 *p = &D_8AE0994C;
    func_8AE027B0(arg0, arg1, p, D_8AE099B4, 1);
    *p = *p + 0x800;
    return 0;
}
#endif

#ifdef VERSION_US
extern void func_8AE027B0(s32, void *, u16 *, void *, s32);
extern u16 D_8AE09AC0;
extern u8 D_8AE09AC8[];
s32 func_8AE028B0(s32 arg0, void *arg1) {
    u16 *p = &D_8AE09AC0;
    func_8AE027B0(arg0, arg1, p, D_8AE09AC8, -1);
    *p = *p + 0x800;
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE028F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE029D0.s")
#endif

#ifdef VERSION_US
extern s32 func_8004C874(s32, s32);
s32 func_8AE03214(s16 arg0) {
    s32 value;
    if (arg0 < 2) {
        value = 0x15;
    } else if (arg0 < 6) {
        value = 0x16;
    } else if (arg0 < 0xB) {
        value = 0x17;
    } else if (arg0 < 0x15) {
        value = 0x18;
    } else if (arg0 < 0x29) {
        value = 0x19;
    } else if (arg0 < 0x51) {
        value = 0x1A;
    } else if (arg0 < 0x64) {
        value = 0x1B;
    } else {
        value = 0x1C;
    }
    return func_8004C874(0x2B, value);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE032C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE03324.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE035BC.s")
#endif

#ifdef VERSION_US
extern void _bzero(void *, s32);
extern s32 func_8AE032C8(u8, s32);
extern void func_8004C54C(s32, s32);
extern void func_8004C8A0(void *, s32, s32, s32);
extern void func_800495BC(s32, s32, s32, s32, void *);
extern u8 D_8AE083EC[];
extern s32 D_8AE09E64;
extern s32 D_8AE09AE4;
void func_8AE038DC(s32 arg0, s32 arg1, void *arg2) {
    u8 sp28[0x100];
    _bzero(sp28, 0x100);
    func_8004C54C(0x33, func_8AE032C8(*(u8 *)((u8 *)arg2 + 2), 0));
    func_8004C8A0(sp28, 0x100, 0x2B, 9);
    if (D_8AE09E64 >= 4) {
        func_800495BC(arg0, arg1, D_8AE083EC, D_8AE09AE4, sp28);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE03970.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE03BDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE03D94.s")
#endif

#ifdef VERSION_US
extern s32 D_8AE09920;
extern s32 D_8AE09938;
extern s16 D_8AE09B04;
extern s16 D_8AE09B40;
extern s16 D_8AE09B48;
extern s16 D_8AE09B52;
extern u8 D_8AE09E78;
extern u8 D_8AE09EA8;
extern u8 D_8AE09ED8;
extern u8 D_8AE09F08;
extern u8 D_8AE09F38;
extern u8 D_8AE09F68;
extern u8 D_8AE09F98;
extern u8 D_8AE09FC8;
void func_8AE04478(void) {
    func_8AC0695C(&D_8AE09EA8, (s32) &D_8AE09E78, (s16) (D_8AE09B40 + 0x1E), 0, 0x10, 0, 0, 0x14, -0x37370538, 0xC8, D_8AE09938);
    func_8AC069C4(&D_8AE09FC8, (s32) &D_8AE09F98, (s16) (D_8AE09B48 + 0x1E), 0, 8, 0, 0, 0x14, -0x37370538, 0xC8, D_8AE09938);
    func_8AC069C4(&D_8AE09F68, (s32) &D_8AE09F38, D_8AE09B52, 0, 0x16, 1, 0, 0x18, -0x37370538, 0xC8, D_8AE09920);
    func_8AC069C4(&D_8AE09F08, (s32) &D_8AE09ED8, (s16) (D_8AE09B04 + 0x14), 0, 8, 0, 0, 0x14, -0x37370538, 0xC8, D_8AE09938);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE04618.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE04BFC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE04EB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE04FA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE050AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE05118.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE0559C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE0566C.s")
#endif

#ifdef VERSION_US
extern u8 D_8AE084D0;
void func_8AE0575C(void *arg0) {
    (*(f32 *)((u8 *)(&D_8AE084D0) + (0))) = (f32) (*(s16 *)((u8 *)(arg0) + (0)));
    (*(f32 *)((u8 *)(&D_8AE084D0) + (4))) = (f32) (*(s16 *)((u8 *)(arg0) + (4)));
    (*(f32 *)((u8 *)(&D_8AE084D0) + (8))) = (f32) -(*(s16 *)((u8 *)(arg0) + (2)));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE057A8.s")
#endif

#ifdef VERSION_US
extern void func_8AE057A8(s16);
extern s16 D_8AE084EE;
extern s16 D_8AE084F4;
extern s16 D_8AE084F6;
extern f32 D_8AE084F0;
void func_8AE05910(s16 arg0) {
    D_8AE084F4 = arg0;
    D_8AE084F6 = 0xA;
    D_8AE084EE = arg0;
    D_8AE084F0 = 12.0f;
    func_8AE057A8(arg0);
}
#endif

#ifdef VERSION_US
void func_8AE05964(void) {
    D_8AE084F0 -= 0.25f;
    if (D_8AE084F0 < 1.0f) {
        D_8AE084F0 = 1.0f;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE059A8.s")
#endif

void func_8AE05B1C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE05B24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE05BF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE05CB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE0605C.s")
#endif

#ifdef VERSION_US
extern void func_80007AEC(s32);
extern void func_800086A4(s32);
extern void func_80064D28();
extern void func_8AE00380();
extern void func_8AE05118();
extern void func_8AE05CB4();
s32 func_8AE0605C(s32);

void func_8AE06118(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    func_80007AEC(5);
    do {
        func_80064D28();
        if (var_s0 == 1) {
            func_8AE05CB4();
        }
        func_8AE00380();
        func_8AE05118();
        temp_v0 = func_8AE0605C(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 3);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE06198.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/46/fragment46_code/func_8AE0626C.s")
#endif
