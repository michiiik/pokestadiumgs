#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern void func_8004D19C(s32, s32, s32, s32, s32);
extern s16 D_82802890[][4][2];

void func_82800620(s32 arg0, s32 arg1, f32 arg2) {
    gDPPipeSync(D_800D0510++);
    if (arg1 != 0) {
        gDPSetPrimColor(D_800D0510++, 0xFF, 0xFF, 0xFF, 0x64, 0x64, (u32)(255.0f * arg2));
        gDPSetEnvColor(D_800D0510++, 0x40, 0x0A, 0x0A, 0);
    } else {
        gDPSetPrimColor(D_800D0510++, 0xFF, 0xFF, 0x64, 0xFF, 0x64, (u32)(255.0f * arg2));
        gDPSetEnvColor(D_800D0510++, 0x0A, 0x40, 0x0A, 0);
    }
    func_8004D19C(D_82802890[arg1][arg0][0], D_82802890[arg1][arg0][1], func_8004C990(0x36, 0), 0, 0);
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82800864.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82800984.s")

extern void func_82800864(f32, s16 *);
extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern void func_8004D19C(s32, s32, s32, s32, s32);
void func_82800AE0(u8 *arg0) {
    s16 coords[2];

    func_82800864(*(f32 *)(arg0 + 0x94), coords);
    gDPPipeSync(D_800D0510++);
    gDPSetPrimColor(D_800D0510++, 0xFF, 0xFF, 0xFF, 0x64, 0x64, 0xFF);
    gDPSetEnvColor(D_800D0510++, 0x40, 0x0A, 0x0A, 0);
    func_8004D19C(coords[0] - 4, coords[1] - 4, func_8004C990(0x36, 0), 0, 0);
}

s32 func_82800B94(u8 *arg0) {
    return *(u32 *)(arg0 + 0x88) == 0 || *(u32 *)(arg0 + 0x8C) == 0;
}

s32 func_82800BB4(u8 *arg0) {
    return (*(u32 *)(arg0 + 0) & 0x100000) != 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82800BC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82800E94.s")

extern f32 (*D_8160BD08)(f32);
extern s16 D_828028F4[][4][2];

void func_8280105C(u8 *arg0, s16 *arg1, s32 arg2) {
    f32 ratio;

    ratio = D_8160BD08(*(f32 *)(arg0 + 4) / 12.0f);
    if (func_82800BB4(arg0) != 0) {
        ratio = 1.0f;
    }
    arg1[0] = (s16)((((f32)(D_828028F4[0][arg2][0] - D_828028F4[1][arg2][0])) * ratio) + ((f32)D_828028F4[1][arg2][0]));
    arg1[1] = (s16)((((f32)(D_828028F4[0][arg2][1] - D_828028F4[1][arg2][1])) * ratio) + ((f32)D_828028F4[1][arg2][1]));
}
// Unreferenced static empty function: the trailing jr ra; nop at 0x8280113C
// that IDO keeps because statics are never dead-stripped.
static void func_8280113C(void) {}
extern s32 func_8004C874(s32, s32);
extern void Fragment11_DrawBorderedPanelFill(s32, s32, s32, s32, s32, void *);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004989C(s32);
extern void func_800495BC(s32, s32, s32 *);
extern void func_800495F8(s32, s32, s32, s32);
extern void func_800499EC(void);
extern u8 D_82802838;
void func_82801144(void) {
    s32 result1;
    s32 result2;

    result1 = func_8004C874(0x19, 0xE);
    result2 = func_8004C874(0x19, 0x12);
    Fragment11_DrawBorderedPanelFill(0x63, 0xDC, 0x1BC, 0x92, 1, &D_82802838);
    func_800498C4();
    func_800496A4(0x10, 1);
    func_8004989C(0x20);
    func_800495BC(0x70, 0xE7, result1);
    func_800496A4(8, 1);
    func_800495F8(0x20E, 0x14B, 2, result2);
    func_800499EC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_828011F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801278.s")

extern s32 func_800606E8(s32);

u8 func_828014AC(void) {
    u8 result = 0;
    s32 index = 0;

loop:
    if (func_800606E8(index) != 0) result |= 1 << index;
    index++;
    if (index != 4) goto loop;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801510.s")

s32 func_828016AC(u8 *arg0) {
    *(f32 *)(arg0 + 4) = 0.0f;
    return 0;
}

extern f32 func_816092FC(void);
s32 func_828016BC(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 4) += step;
    if (*(f32 *)(arg0 + 4) >= 12.0f) {
        *(f32 *)(arg0 + 4) = 12.0f;
        *(u8 *)(arg0 + 0xC) = 2;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801718.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801774.s")

s32 func_828019B4(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 4) -= step;
    if (*(f32 *)(arg0 + 4) <= 0.0f) {
        *(f32 *)(arg0 + 4) = 0.0f;
        *(u8 *)(arg0 + 0xC) = 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801A08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801BE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801D7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82801F88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_828020C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D5250/func_82802224.s")

s32 func_8280276C(u8 *arg0) {
    if (arg0[0xC]) return -2;
    if (*(u32 *)(arg0 + 0x8C)) {
        if ((*(s32 *)(arg0 + 0) << 2) < 0 && *(s32 *)(arg0 + 0x10) != -1) return 7;
    }
    return *(s32 *)(arg0 + 0x10);
}

extern void func_80054248(void *);
extern void func_80051D64(s32, s32);
extern void func_80054E48(s32);
void func_828027C0(u8 *arg0) {
    if ((*(s32 *)arg0 << 14) >= 0) {
        return;
    }
    if (*(u32 *)(arg0 + 0x84) != 0) {
        arg0[0x4E] |= 1;
    } else {
        arg0[0x4E] &= 0xFFFE;
    }
    func_80054248(arg0 + 0x4C);
    func_80051D64(0x14, 0);
    func_80054E48(3);
}
#endif
