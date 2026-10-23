#include "global.h"

extern u8 *D_841911E0;
extern u8 *D_841911E8;
extern u8 D_8418393C;
extern u8 *func_8410B330(u8 *);
extern s32 func_8411DC80(u16, s32 *, s32);
extern void func_841203B4(u8 *, f32, f32);
extern void func_84120BB4(u8 *, s32);
extern void func_8410DFC4(u8 *, void *);
extern u8 *D_84193DD0;
extern s32 D_841911EC;
extern s32 D_84184148;
extern void func_8410C934(u8 *arg0, s32 arg1, s16 arg2);
extern void func_8410E688(u8 *arg0, void *arg1);
extern void func_84110B2C(u8 *, s32);
extern void func_8410AFD4(void);
extern void BattleAnim_UpdateCameraHeightTarget(u8 *arg0, u8 *arg1);
extern void func_8410E7D0(u8 *arg0, void *arg1);

#ifdef VERSION_US
extern u8 * func_8410B330(u8 *);
extern void func_8410DFC4(u8 *, void *);
extern void func_8410E688(u8 *arg0, void *arg1);
extern s32 func_8411DC80(u16, s32 *, s32);
void BattleAnim_ModelDispatch_093(u8 *arg0, void *arg1) {
    extern u8 *D_841911E8;
    extern s32 func_8411DC80(u16, s32 *, s32);
    extern void func_8410DFC4(u8 *, void *);
    extern void func_8410E688(u8 *, void *);
    extern u8 D_8418393C;

    D_841911E8 = func_8410B330(arg0);
    func_841203B4(arg0 + 0x2C, *(f32 *)(D_841911E8 + 0x88), 0.05f);
    if (func_8411DC80(*(u8 *)((u8 *)arg1 + 0x61F),
            (s32 *)&D_8418393C, 8) == 0) {
        func_8410DFC4(arg0, arg1);
        func_8410E688(arg0, arg1);
    }
}
#endif

#ifdef VERSION_US
extern void func_8411EF20(u8 *);
extern void func_8410AFD4(void);
extern u8 * func_8410B330(u8 *);
extern void func_8410C934(u8 *arg0, s32 arg1, s16 arg2);
extern void func_8411EF08(u8 *arg0);
extern s32 D_84184148;
extern u8 * D_841911E0;
extern u8 * D_841911E8;
extern s32 D_841911EC;
void BattleAnim_ModelDispatch_113(u8 *arg0, u8 *arg1) {
 D_841911E8=func_8410B330(arg0);
 if(D_841911E8==D_841911E0){func_8410AFD4();func_8411EF08(arg1);}else{func_8411EF20(arg1);}
 func_8410C934(arg0,arg1,*(s16 *)(D_841911E8+0x98));
 *(s32 *)(D_841911E8+D_841911EC*8+8)=D_84184148;
}
#endif

#ifdef VERSION_US
extern u8 * func_8410B330(u8 *);
extern void func_8410C934(u8 *arg0, s32 arg1, s16 arg2);
extern void func_8411EF08(u8 *arg0);
extern void func_8411EF20(u8 *arg0);
extern s32 D_84184148;
extern u8 * D_841911E0;
extern u8 * D_841911E8;
extern s32 D_841911EC;
void BattleAnim_ModelDispatch_141(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    if (D_841911E8 == D_841911E0) {
        func_8411EF08((u8 *)arg1);
    } else {
        func_8411EF20((u8 *)arg1);
    }
    func_8410C934(arg0, arg1, *(s16 *)(D_841911E8 + 0x98));
    *(s32 *)(D_841911E8 + (D_841911EC * 8) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_380210/func_84110B2C.s")
#endif

#ifdef VERSION_US
extern u8 *D_80087200;
extern u8 *D_841911E8;
extern u8 *D_84193DD0;
extern u8 *D_84193FA0;
extern s32 D_8419120C;
extern void func_800371B4(u8 *, u8 *, f32, s16, s16);
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern u8 * func_8410B330(u8 *);
void BattleAnim_UpdateCameraFromInput(u8 *arg0, u8 *arg1) {
    D_841911E8 = func_8410B330(arg0);
    *(f32 *)(arg0 + 44) = 45.0f;
    switch (*(u16 *)(D_84193DD0 + 4)) {
    case 48: case 49: case 50: case 51: case 52: case 53:
        Vec3f_SetComponentsDuplicate((f32 *)(*(u8 **)D_841911E8 + 180), 0.0f, 40.0f, 0.0f);
        if (*(u16 *)(D_80087200 + 6) & 0x400) *(f32 *)(D_841911E8 + 116) -= 8;
        if (*(u16 *)(D_80087200 + 6) & 0x800) *(f32 *)(D_841911E8 + 116) += 8;
        ((u8 *)D_8419120C)[1] |= 1;
        break;
    default:
        if (*(s16 *)(D_84193FA0 + 144) != 0) {
            if (*(u16 *)(D_80087200 + 6) & 4) *(f32 *)(*(u8 **)D_841911E8 + 184) -= 4;
            if (*(u16 *)(D_80087200 + 6) & 8) *(f32 *)(*(u8 **)D_841911E8 + 184) += 4;
            if (*(u16 *)(D_80087200 + 6) & 1) *(f32 *)(*(u8 **)D_841911E8 + 180) -= 4;
            if (*(u16 *)(D_80087200 + 6) & 2) *(f32 *)(*(u8 **)D_841911E8 + 180) += 4;
            if (*(u16 *)(D_80087200 + 6) & 0x400) *(f32 *)(D_841911E8 + 116) -= 8;
            if (*(u16 *)(D_80087200 + 6) & 0x800) *(f32 *)(D_841911E8 + 116) += 8;
            break;
        }
    }
    if (*(f32 *)(D_80087200 + 24) != 0.0f) {
        *(s16 *)(D_841911E8 + 146) += (s16)(*(f32 *)(D_80087200 + 24) * 8.0f);
    }
    if (*(f32 *)(D_80087200 + 28) != 0.0f) {
        *(s16 *)(D_841911E8 + 144) += (s16)(*(f32 *)(D_80087200 + 28) * 8.0f);
    }
    func_800371B4(*(u8 **)D_841911E8 + 180, *(u8 **)D_841911E8 + 168,
        *(f32 *)(D_841911E8 + 116), *(s16 *)(D_841911E8 + 144), *(s16 *)(D_841911E8 + 146));
}
#endif

#ifdef VERSION_US
extern u8 D_84183960[];
extern void func_84110B2C(u8 *, s32);
extern void func_8410DFC4(u8 *, void *);
extern void func_8410E688(u8 *arg0, void *arg1);
extern void func_8410E7D0(u8 *arg0, void *arg1);
extern s32 func_8411DC80(u16, s32 *, s32);
void BattleAnim_ModelDispatch_009(u8 *arg0, s32 arg1) {
    s32 index;

    index = func_8411E1F8(arg1);
    if (((*(u16 *)((u8 *)(D_84193DD0) + (index << 4) + 0x12)) & 2) == 0) {
        func_8410DFC4(arg0, (void *)arg1);
    }
    if (func_8411DC80(*(u16 *)((u8 *)(D_841911E8) + 0x98),
            (s32 *)&D_84183960, 0x10) != 0) {
        func_8410E688(arg0, (void *)arg1);
    } else {
        func_8410E7D0(arg0, (void *)arg1);
    }
    func_84110B2C(arg0, arg1);
}
#endif

#ifdef VERSION_US
extern void func_84108940(u8 *, s32);
void BattleAnim_ModelDispatch_176(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84108940(arg0 + 0xB4, 0);
}
#endif

#ifdef VERSION_US
extern void func_8411EFE4(s32);
void BattleAnim_ModelDispatch_022(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84120BB4(arg0, arg1);
    func_8411EFE4(arg1);
    func_8410C934(arg0, arg1, (*(s16 *)((u8 *)(D_841911E8) + (0x98))));
    (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
}
#endif

#ifdef VERSION_US
extern void BattleAnim_UpdateCameraHeightTarget(u8 *, u8 *);
void BattleAnim_ModelDispatch_023(u8 *arg0, u8 *arg1) {
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    BattleAnim_UpdateCameraHeightTarget(arg0, arg1);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_015(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84120BB4(arg0, arg1);
    func_8410C934(arg0, arg1, (*(s16 *)((u8 *)(D_841911E8) + (0x98))));
    func_8411EFE4(arg1);
    func_8411EF08((u8 *) arg1);
    (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
}
#endif
