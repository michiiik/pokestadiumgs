#include "global.h"


#ifdef VERSION_US
extern s16 D_829188A8;
extern s16 D_829188AA;

s32 func_82900BA0(s32 arg0, void *arg1) {
    if (arg0 == 2) {
        (*(s16 *)((u8 *)(arg1) + (0x1C))) = (s16) (D_829188A8 + 0x2000);
        (*(s16 *)((u8 *)(arg1) + (0x1E))) = (s16) (D_829188AA - 0x2000);
    }
    return 0;
}
#endif

#ifdef VERSION_US

s32 func_82900BD0(s32 arg0, void *arg1) {
    if (arg0 == 2) {
        (*(s16 *)((u8 *)(arg1) + (0x1C))) = (s16) (-0x2000 - D_829188A8);
        (*(s16 *)((u8 *)(arg1) + (0x1E))) = (s16) (D_829188AA + 0x6000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern void func_80041E2C(void);
extern void func_8003F018(s32);
extern s32 func_80041C98(s32);
void func_82900C04(s32 arg0) {
    func_80041E2C();
    func_8003F018((s32)((u8 *)(u32)arg0 + 4));
    *(s32 *)(u32)arg0 = func_80041C98(5);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82900C40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82900D78.s")
#endif

#ifdef VERSION_US
extern s16 D_82918858;
extern u8 D_82911D70[];
extern u8 D_829188C0[];
void func_82900E54(void) {
    *(s16 *)(D_829188C0 + 0) = *(s16 *)(D_82911D70 + D_82918858 * 8 + 0);
    *(s16 *)(D_829188C0 + 2) = *(s16 *)(D_82911D70 + D_82918858 * 8 + 2);
    *(s16 *)(D_829188C0 + 4) = *(s16 *)(D_82911D70 + D_82918858 * 8 + 4);
    *(s16 *)(D_829188C0 + 6) = *(s16 *)(D_82911D70 + D_82918858 * 8 + 6);
}
#endif

#ifdef VERSION_US
extern s16 D_82918858;
extern u8 D_82911D00[];
extern s16 D_829188B0[];
void func_82900E98(void) {
    D_829188B0[0] = ((s16 *)((u8 *)D_82911D00 + D_82918858 * 14))[0];
    D_829188B0[1] = ((s16 *)((u8 *)D_82911D00 + D_82918858 * 14))[1];
    D_829188B0[2] = ((s16 *)((u8 *)D_82911D00 + D_82918858 * 14))[2];
    D_829188B0[3] = ((s16 *)((u8 *)D_82911D00 + D_82918858 * 14))[3];
    D_829188B0[4] = ((s16 *)((u8 *)D_82911D00 + D_82918858 * 14))[4];
    D_829188B0[5] = ((s16 *)((u8 *)D_82911D00 + D_82918858 * 14))[5];
    D_829188B0[6] = ((s16 *)((u8 *)D_82911D00 + D_82918858 * 14))[6];
}
#endif

#ifdef VERSION_US
extern void *D_829188A0;
extern void GeoCamera_SetViewport(void *, s16, s16, s16, s16);
extern void GeoCamera_SetPerspective(void *, s32, f32, f32);
extern void func_80038E14(void *, s32, s32, s32, f32, f32, f32, s32);
void func_82900EFC(void) {
    GeoCamera_SetViewport(
        D_829188A0,
        *(s16 *)((u8 *)D_829188A0 + 0x1C),
        *(s16 *)((u8 *)D_829188A0 + 0x1E),
        *(s16 *)((u8 *)D_829188A0 + 0x20),
        *(s16 *)((u8 *)D_829188A0 + 0x22));
    GeoCamera_SetPerspective(
        D_829188A0,
        *(s32 *)((u8 *)D_829188A0 + 0x2C),
        20.0f,
        6400.0f);
    func_80038E14(
        D_829188A0,
        *(s32 *)((u8 *)D_829188A0 + 0xA8),
        *(s32 *)((u8 *)D_829188A0 + 0xAC),
        *(s32 *)((u8 *)D_829188A0 + 0xB0),
        *(f32 *)((u8 *)D_829188A0 + 0xB4),
        *(f32 *)((u8 *)D_829188A0 + 0xB8),
        *(f32 *)((u8 *)D_829188A0 + 0xBC),
        0);
}
#endif

#ifdef VERSION_US
extern void func_82900EFC();
extern void *D_829188A0;
void func_82900F80(void) {
    (*(s16 *)((u8 *)(D_829188A0) + (0x1C))) = (s16) (*(s16 *)((u8 *)(D_829188C0) + (0)));
    (*(s16 *)((u8 *)(D_829188A0) + (0x1E))) = (s16) (*(s16 *)((u8 *)(D_829188C0) + (2)));
    (*(s16 *)((u8 *)(D_829188A0) + (0x20))) = (s16) (*(s16 *)((u8 *)(D_829188C0) + (4)));
    (*(s16 *)((u8 *)(D_829188A0) + (0x22))) = (s16) (*(s16 *)((u8 *)(D_829188C0) + (6)));
    func_82900EFC();
}
#endif

#ifdef VERSION_US
extern void func_82900D78();
extern void func_82900E98();
extern void func_8290299C(u8);
extern u8 D_82918859;
extern void func_82900C40(s32);
extern s32 D_8291889C;
void func_82900FDC(void) {
    func_82900C40(D_8291889C);
    func_82900D78();
    func_82900E98();
    func_82900E54();
    func_82900F80();
    func_8290299C(D_82918859);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_8290102C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_829011D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_829012E4.s")
#endif

#ifdef VERSION_US
extern s16 D_829188AC;
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_800371B4(u8 *, u8 *, f32, s16, s32);
extern void func_82900E54(void);
extern void func_82900E98(void);
extern void func_82900F80(void);
void func_829013F8(void) {
    extern s32 D_829188A4;
    D_829188A0 = *(void **)((u8 *)(u32)D_829188A4 + 0xC);
    D_829188A8 = 0;
    D_829188AA = 0;
    D_829188AC = 0x96;
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)D_829188A0 + 0xB4), 0.0f, 50.0f, 0.0f);
    func_800371B4((u8 *)D_829188A0 + 0xB4, (u8 *)D_829188A0 + 0xA8, (f32)D_829188AC, D_829188A8, (s32)D_829188AA);
    *(f32 *)((u8 *)D_829188A0 + 0x34) = 40.0f;
    *(f32 *)((u8 *)D_829188A0 + 0x38) = 6400.0f;
    *(f32 *)((u8 *)D_829188A0 + 0x2C) = 45.0f;
    func_82900D78();
    func_82900E98();
    func_82900E54();
    func_82900F80();
}
#endif

#ifdef VERSION_US
extern u8 D_82918868[];
void func_829014F4(void) {
    D_82918868[0x32] = 0;
    D_82918868[0x30] = 0;
    D_82918868[0x31] = 3;
}
#endif

#ifdef VERSION_US
extern s32 D_829188EC;
extern void func_829014F4(void);
extern void func_82900C04(s32);
void func_82901510(s32 arg0) {
    D_829188EC = 1;
    func_829014F4();
    func_82900C04(D_8291889C);
    func_82900C40(D_8291889C);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82901554.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_80094D90[];
extern void Gfx_FillRectRgb(s16, s16, s16, s16, s32, s32, s32);
void func_82901628(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    gSPDisplayList(D_800D0510++, D_80094D90);
    Gfx_FillRectRgb(arg0, arg1, arg2, arg3, 0, 0, 0);
}
void func_82901628_padding(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_829016B0.s")
#endif

#ifdef VERSION_US
extern void func_8003C6B8(s32);
extern void func_82902EC0(u8, s16, s16, s16, s32);
extern u8 D_82918868[];
extern s16 D_829188B0[];
extern s32 D_829188A4;
extern u8 D_82918859;
void func_82901A6C(void) {
    if (D_82918868[0x31] != 3 && D_82918868[0x32] != 0 && D_82918868[0x32] != 6) {
        func_82902EC0(D_82918859, D_829188B0[3], D_829188B0[4], D_829188B0[1], D_829188B0[2]);
        func_8003C6B8(D_829188A4);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82901AE0.s")
#endif

#ifdef VERSION_US
extern void func_800088DC(void);
extern void GfxImage_FillCurrent(void *, u16);
extern void func_80007444(void *, s32, s32, s32, s32, s32);
extern s32 func_800061EC(void);
extern void GeoRender_AdvanceFrameCounter(void);
extern void func_82901A6C(void);
extern void func_829016B0(void);
extern void func_82901AE0(void);
extern void func_80008648(void);
extern Gfx *D_800D0510;
extern u8 D_82918868[];
extern s16 D_829188B0[];
void func_82901BA8(void) {
    func_800088DC();
    if (D_82918868[0x31] == 3 || D_82918868[0x32] == 0 || D_82918868[0x32] == 6) {
        GfxImage_FillCurrent(&D_800D0510, 1);
    } else {
        func_80007444(&D_800D0510, D_829188B0[3], D_829188B0[4], D_829188B0[1], D_829188B0[2], 1);
    }
    if ((func_800061EC() & 1) == 0) {
        func_80007444(&D_800D0510, 0, 0x190, 0x280, 0x1C, 1);
    }
    GeoRender_AdvanceFrameCounter();
    func_82901A6C();
    func_829016B0();
    func_82901AE0();
    func_80008648();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82901C98.s")
#endif

#ifdef VERSION_US
extern u8 D_82918868[];
extern s16 D_829188B0[];
extern f32 Math_StepToF(f32, f32, f32, f32);
void func_82901DD4(void) {
    f32 temp_fv0;
    f32 target;
    f32 step;

    switch (*(u8 *)(D_82918868 + 0x32)) {
    case 1:
        temp_fv0 = (f32)D_829188B0[0];
        *(f32 *)(D_82918868 + 4) = temp_fv0;
        *(u8 *)(D_82918868 + 0x32) = 2;
        *(f32 *)(D_82918868 + 0x10) = temp_fv0;
        return;
    case 2:
        target = (f32)D_829188B0[5];
        step = (f32)((s32)(D_829188B0[0] - D_829188B0[5]) / 4);
        *(f32 *)(D_82918868 + 4) = Math_StepToF(*(f32 *)(D_82918868 + 4), target, step, step);
        target = (f32)D_829188B0[6];
        step = (f32)((s32)(D_829188B0[0] - D_829188B0[5]) / 4);
        *(f32 *)(D_82918868 + 0x10) = Math_StepToF(*(f32 *)(D_82918868 + 0x10), target, step, step);
        if (*(f32 *)(D_82918868 + 4) == (f32)D_829188B0[5]) {
            *(u8 *)(D_82918868 + 0x32) = 3;
            do { } while (0);
            return;
        }
        return;
    case 4:
        *(f32 *)(D_82918868 + 4) = (f32)D_829188B0[5];
        *(f32 *)(D_82918868 + 0x10) = (f32)D_829188B0[6];
        *(u8 *)(D_82918868 + 0x32) = 5;
        return;
    case 5:
        target = (f32)(D_829188B0[0] + 5);
        step = (f32)((s32)(D_829188B0[0] - D_829188B0[5]) / 4);
        *(f32 *)(D_82918868 + 4) = Math_StepToF(*(f32 *)(D_82918868 + 4), target, step, step);
        target = (f32)(D_829188B0[0] - 5);
        step = (f32)((s32)(D_829188B0[0] - D_829188B0[5]) / 4);
        *(f32 *)(D_82918868 + 0x10) = Math_StepToF(*(f32 *)(D_82918868 + 0x10), target, step, step);
        if (*(f32 *)(D_82918868 + 4) == (f32)(D_829188B0[0] + 5)) {
            *(u8 *)(D_82918868 + 0x32) = 6;
        }
        break;
    }
}
#endif

#ifdef VERSION_US
void func_82902024(void) {
    f32 temp_fv0;
    f32 target;
    f32 step_first;
    f32 step;

    switch (*(u8 *)(D_82918868 + 0x32)) {
    case 1:
        temp_fv0 = (f32)D_829188B0[0];
        *(f32 *)(D_82918868 + 4) = temp_fv0;
        *(u8 *)(D_82918868 + 0x32) = 2;
        *(f32 *)(D_82918868 + 0x10) = temp_fv0;
        return;
    case 2:
        target = (f32)D_829188B0[5];
        step_first = (f32)((s32)(D_829188B0[0] - D_829188B0[5]) / 4);
        *(f32 *)(D_82918868 + 4) = Math_StepToF(*(f32 *)(D_82918868 + 4), target, step_first, step_first);
        target = (f32)D_829188B0[6];
        step = (f32)((s32)(D_829188B0[6] - D_829188B0[0]) / 4);
        *(f32 *)(D_82918868 + 0x10) = Math_StepToF(*(f32 *)(D_82918868 + 0x10), target, step, step);
        if (*(f32 *)(D_82918868 + 4) == (f32)D_829188B0[5]) {
            *(u8 *)(D_82918868 + 0x32) = 3;
            do { } while (0);
            return;
        }
        return;
    case 4:
        *(f32 *)(D_82918868 + 4) = (f32)D_829188B0[5];
        *(f32 *)(D_82918868 + 0x10) = (f32)D_829188B0[6];
        *(u8 *)(D_82918868 + 0x32) = 5;
        return;
    case 5:
        target = (f32)D_829188B0[0];
        step_first = (f32)((s32)(D_829188B0[0] - D_829188B0[5]) / 4);
        *(f32 *)(D_82918868 + 4) = Math_StepToF(*(f32 *)(D_82918868 + 4), target, step_first, step_first);
        target = (f32)D_829188B0[0];
        step = (f32)((s32)(D_829188B0[6] - D_829188B0[0]) / 4);
        *(f32 *)(D_82918868 + 0x10) = Math_StepToF(*(f32 *)(D_82918868 + 0x10), target, step, step);
        if (*(f32 *)(D_82918868 + 4) == (f32)D_829188B0[0]) {
            *(u8 *)(D_82918868 + 0x32) = 6;
        }
        break;
    }
}
#endif

void func_82902260(void) {
}

#ifdef VERSION_US
extern u8 D_82918899;
extern void func_82901C98(void);
extern void func_82901DD4(void);
extern void func_82902024(void);
void func_82902268(void) {
    switch (D_82918899) {
    case 0:
        func_82901C98();
        return;
    case 1:
        func_82901DD4();
        return;
    case 2:
        func_82902024();
        return;
    case 3:
        func_82902260();
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_829022E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82902554.s")
#endif

#ifdef VERSION_US
extern void func_82902554(void);
extern void func_82902268(void);
void func_8290260C(void) {
    func_82902554();
    func_82902268();
}
#endif

void func_82902634(void) {
}

#ifdef VERSION_US
extern void StageFade_StartFromOpaque(s32);
extern void StageContext_SetClearColor(s32);
extern void func_80064D28();
extern void func_82901BA8();
void func_8290263C(void) {
    s32 var_s0;

    StageContext_SetClearColor(1);
    StageFade_StartFromOpaque(0x10);
    var_s0 = 0;
    do {
        func_80064D28();
        func_82901BA8();
        var_s0 += 1;
    } while (var_s0 != 0x10);
}
#endif

#ifdef VERSION_US
extern void *D_80087200;
extern s32 D_829188EC;
extern void func_80064D28(void);
extern void func_8290260C(void);
extern void func_82902634(void);
extern void func_82901BA8(void);
void func_82902694(void) {
    if (D_829188EC != 0) {
        do {
            func_80064D28();
            func_8290260C();
            func_82902634();
            if ((*(u16 *)((u8 *)D_80087200 + 8) & 0xD000) != 0) {
                D_829188EC = 0;
            }
            func_82901BA8();
        } while (D_829188EC != 0);
    }
}
#endif

#ifdef VERSION_US
void func_82902714(void) {
    s32 var_s0;

    StageContext_SetClearColor(1);
    StageFade_StartFromTransparent(0xA);
    var_s0 = 0;
    do {
        func_8290260C();
        func_82902634();
        func_82901BA8();
        var_s0 += 1;
    } while (var_s0 != 0xA);
    func_80025CBC(1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_8290277C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82902808.s")
#endif
