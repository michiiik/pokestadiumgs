#include "global.h"


#ifdef VERSION_US
extern void func_88001900();
extern s32 D_880068B4;
extern s32 D_889041B4;

void func_8822AA20(void) {
    func_88001900();
    D_889041B4 = 1;
    D_880068B4 = 1;
}

extern s32 D_882348E0;
extern void Util_Free(s32);
void func_8822AA50(void) {
    if (*(s32 *)((u8 *)(u32)D_882348E0 + 0x204) == 0) {
        func_88001900();
        D_889041B4 = 0;
    }
    Util_Free(D_882348E0);
}

extern void func_800226C0(s32);
extern void func_88004990(u8, s32);
extern s32 D_8800EF54;
extern void func_88232B50(void);
void func_8822AA9C(s32 arg0) {
    func_88004990(*(*(u8 **)((u8 *)(u32)D_882348E0 + (0))), 0);
    if (arg0 != 0) {
        D_8800EF54 = arg0;
        func_800226C0(0x5D);
        func_800226C0(0x63);
        func_88232B50();
        D_889041B4 = 0;
        D_880068B4 = 0;
    } else {
        D_889041B4 = 2;
    }
    (*(s32 *)((u8 *)(u32)D_882348E0 + (0x204))) = arg0;
}

extern Gfx *D_800D0510;
extern Gfx D_80094DE0[];
extern u8 *D_8800687C;
extern void func_880008B0(s16, s16, s16);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void *func_8004C874(s32, s32);
extern s32 func_80048E30(u8 *, s32, s32, const char *, s32);
extern void func_800499EC(void);

void func_8822AB28(void) {
    gSPDisplayList(D_800D0510++, D_80094DE0);
    func_880008B0(178, 179, 204);
    func_800498C4();
    func_800496A4(4, 1);
    func_80048E30(D_8800687C, 178, 157, func_8004C874(37, 72), 1);
    func_80048E30(D_8800687C, 182, 189, (const char *)(u32)D_882348E0 + 4, 1);
    func_800499EC();
}
extern void *Util_Malloc(s32);
extern void D_88000E4C(void);
extern s32 func_88004804(s32, s32, s16, s16, s32, s32, s32, s32, s32,
                         void (*)(void), void (*)(void), void (*)(void),
                         void (*)(void), s32, s32);
extern u8 D_8800ED50[];
extern void func_8004C54C(s32, void *);
extern void *func_800635E0(u8);
extern void func_8004C8A0(void *, s32, s32, s32);
extern u8 D_88234746;

void func_8822ABE8(u8 *arg0) {
    s32 result;

    D_882348E0 = (s32)Util_Malloc(0x208);
    result = func_88004804(0, 3, 0xA7, 0x92, 0, 1, 0xDC, 0xDC, 0xB4,
                           D_88000E4C, func_8822AB28, func_8822AA20, func_8822AA50, 2, 0);
    *(void **)D_882348E0 = D_8800ED50 + (result * 0x4C);
    *(s16 *)(*(s32 *)D_882348E0 + 0x10) = 0xE5;
    *(s16 *)(*(s32 *)D_882348E0 + 0x12) = 0x81;
    *(s32 *)(*(s32 *)D_882348E0 + 0x2C) = 0;
    func_8004C54C(0x1A, arg0 + 0x34);
    func_8004C54C(0x1B, func_800635E0(arg0[1]));
    func_8004C8A0((u8 *)D_882348E0 + 4, 0x200, 0x25, 0x49);
    D_880068B4 = 0;
    D_88234746 = 3;
}
#endif
