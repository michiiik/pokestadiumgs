#include "global.h"

extern u8 *D_841911E8;
extern u8 *D_841911E0;
extern f32 D_80088E50[];
extern f32 D_80087E50[];

extern u8 *func_8410B330(void *arg0, void *arg1);
extern void func_8411E0A4(void *arg0, void *arg1, void *arg2);
extern void func_80037120(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4);
extern s32 func_841203B4(void *arg0, void *arg1, f32 arg2);
extern s32 func_8411E1D4(void *arg0);
extern void Vec3f_SetComponentsDuplicate(void *arg0, f32 arg1, f32 arg2, f32 arg3);
extern void Camera_ComputeEyeFromAngles(void *arg0, void *arg1, f32 arg2, s16 arg3, s32 arg4);
extern f32 func_8410EB50(void);
extern void func_8411FEE8(s32 arg0);
extern u32 D_84193DD0[];
extern s32 func_8411E1F8(void *arg0);
extern void func_8410B8FC(void *arg0, void *arg1, s16 arg2);
extern void BattleAnim_StepToS16(s16 *value, s16 target, s16 step);
extern s32 func_80001FF0(void);
extern void func_84120960(void *arg0, ...);
extern void func_84120A50(void *arg0, ...);
extern void func_84120BB4(void *arg0, ...);
extern void func_84120C20(void *arg0, ...);
extern void func_84120CA4(void *arg0, ...);
extern void func_84120D34(void *arg0, ...);
extern void func_84120E14(void *arg0, ...);
extern void func_8410AF1C(void);
extern void func_8410B884(void *arg0, ...);
extern void func_8410B420(void *arg0, ...);
extern void func_8410C934(void *arg0, ...);
extern void func_8410CAE4(void *arg0, ...);
extern void func_8410CC90(void *arg0, ...);
extern void func_8410CD3C(void *arg0, ...);
extern void func_8410E73C(void *arg0, ...);
extern void func_8410ED98(void *arg0, ...);
extern u32 D_841911EC;
extern u32 D_84184148;
extern void func_8410D174(void *arg0, void *arg1);
extern void func_8410B60C(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_8410C840(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_8411EF08(void *arg0);
extern void func_8411EF20(void *arg0);
extern void func_8410E7D0(void *arg0, void *arg1);
extern void func_8410CF80(void *arg0);
extern void func_8410E878(void *arg0, void *arg1);
extern void func_8411EFE4(void *arg0);
extern void func_8410EA58(void *arg0, void *arg1, s16 arg2);
extern void func_84108940(void *arg0, s32 arg1);
extern s32 func_8411DC80(s32 arg0, void *arg1, s32 arg2);
extern void func_8410DFC4(void *arg0, void *arg1);
extern void func_8410AFD4(void);
extern void func_8410D088(void *arg0, ...);
extern void func_8410E688(void *arg0, void *arg1);
extern void func_84110B2C(void *arg0, void *arg1);
extern u8 D_8418393C[];
extern u8 D_84183944[];
extern u8 D_84183960[];
extern u8 *D_8419120C;
extern u8 *D_84193FA0;

static void BattleAnim_ModelDispatchFinish(void) {
    if (D_841911E8 != NULL) {
        *(u32 *)(D_841911E8 + (D_841911EC * 8) + 8) = D_84184148;
    }
}

static void BattleAnim_ModelDispatchCamera(u8 *model, u8 *state,
                                            f32 x, f32 y, f32 z,
                                            s16 pitch, s32 angle) {
    Vec3f_SetComponentsDuplicate(model + 0xB4, x, y, z);
    Camera_ComputeEyeFromAngles(model + 0xB4, model + 0xA8,
                                *(f32 *)(state + 0x74),
                                *(s16 *)(state + 0x92), pitch * angle);
}


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410AE50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410AE8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410AF1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410AFD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B08C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B104.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B1CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B224.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B27C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B2DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B330.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B35C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B420.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B578.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B594.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B60C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B704.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B884.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B8FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B974.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410BDA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410C304.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410C400.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410C544.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410C720.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410C840.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410C934.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410CAE4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410CC90.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410CD3C.s")
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_121(u8 *model, void *arg1) {
    u8 *state;
    u8 vector[0x10];
    f32 value;
    u16 outAngle;
    u8 *out;

    state = func_8410B330(model, arg1);
    D_841911E8 = state;
    func_8411E0A4(arg1, vector, state);
    func_80037120(vector, state + 0x50, &value, &outAngle, &out);
    if (*(f32 *)(state + 0x80) * 0.5 < value) {
        func_841203B4(state + 0x60, arg1, 0.3f);
    }
    *(f32 *)(model + 0xB8) = *(f32 *)(state + 0x60);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_024(u8 *model, void *arg1) {
    f32 current = *(f32 *)(model + 0xB8);
    f32 limit = *(f32 *)(model + 0xAC);

    (void)arg1;
    if (current > limit) {
        func_841203B4(model + 0xAC, (void *)*(u32 *)&current, 0.02f);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410D088.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410D174.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410D5CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410D9B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410DAC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410DEB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410DFC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410E688.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410E73C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410E7D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410E878.s")
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_050(u8 *model, u8 *entity) {
    u8 *transform;
    s32 angle;
    s32 index;
    f32 x;
    f32 y;
    f32 z;
    f32 tilt;

    func_84120BB4(entity);
    *(f32 *)(model + 0x2C) = 80.0f;
    transform = *(u8 **)(entity + 0x678);
    angle = func_8411E1D4(entity);
    index = (*(u16 *)(entity + 0x20) >> 4) & 0xFFF;
    x = *(f32 *)(entity + 0x24) +
        *(f32 *)(transform + 0x0) * (f32)angle * D_80088E50[index] -
        *(f32 *)(transform + 0x8) * D_80087E50[index];
    y = *(f32 *)(entity + 0x28) + *(f32 *)(transform + 0x4);
    angle = func_8411E1D4(entity);
    z = *(f32 *)(entity + 0x2C) +
        *(f32 *)(transform + 0x0) * (f32)angle * D_80087E50[index] +
        *(f32 *)(transform + 0x8) * D_80088E50[index];
    Vec3f_SetComponentsDuplicate(model + 0xB4, x, y, z);
    tilt = *(f32 *)(transform + 0xC);
    angle = func_8411E1D4(entity);
    Camera_ComputeEyeFromAngles(model + 0xB4, model + 0xA8, tilt,
                                *(s16 *)(transform + 0x10), angle * *(s16 *)(transform + 0x12));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410EA58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410EB50.s")
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_072(void *model, void *arg1) {
    if (func_8410EB50() >= 0.5f) {
        func_8411FEE8(0);
        BattleAnim_ModelDispatchFinish();
    }
    (void)model;
    (void)arg1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410ED98.s")
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_100(void *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    func_841203B4(state + 0x44, (void *)0x3BA3D70A, 0.3f);
    func_841203B4((u8 *)model + 0xB8, (void *)*(u32 *)(state + 0x54), *(f32 *)(state + 0x44));
    if (*(u16 *)((u8 *)D_84193DD0 + func_8411E1F8(arg1) * 0x10 + 6) < 0x29 &&
        *(f32 *)((u8 *)model + 0xB8) - *(f32 *)(state + 0x54) < 0.0f) {
        func_8411FEE8(0);
        BattleAnim_ModelDispatchFinish();
    }
}
#endif

#ifdef VERSION_US
/* 127/128 remain assembly-backed until their large state-machine bodies are reviewed. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410F1A8.s")
/*
void BattleAnim_ModelDispatch_127(void *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    u8 *entity = arg1;
    f32 position[3];
    f32 other[3];
    s16 angle, aux, flip = 1;
    s32 index;
    D_841911E8 = state;
    *(s16 *)(state + 0x94) = 0;
    *(s16 *)(state + 0xA2) = 0;
    index = func_8411E1F8(entity);
    *(s16 *)(state + 0x98) = ((u16 *)D_84193DD0)[index * 8 + 8] == 0x20 ? 0x26 : 0x24;
    *(f32 *)(state + 0x44) = 0.0f;
    *(f32 *)(state + 0x48) = 0.0f;
    *(f32 *)(state + 0x84) = *(f32 *)(entity + 0x644);
    *(f32 *)(state + 0x80) = *(f32 *)(entity + 0x640);
    *(f32 *)(state + 0x7C) = *(f32 *)(entity + 0x654);
    *(f32 *)(state + 0x74) = *(f32 *)(entity + 0x64C);
    *(f32 *)(state + 0x78) = 0.0f;
    func_8410B8FC(position, entity + 0x634, *(s16 *)(entity + 0x20));
    position[0] += *(f32 *)(entity + 0x24);
    position[1] += *(f32 *)(entity + 0x2C);
    Vec3f_SetComponentsDuplicate(state + 0x5C, position[0], *(f32 *)(state + 0x638), position[1]);
    Vec3f_SetComponentsDuplicate(state + 0x50, position[0], *(f32 *)(state + 0x638), position[1]);
    index = func_8411E1F8(entity);
    if (*(u16 *)((u8 *)D_84193DD0 + index * 0x10 + 0x12) & 2) {
        func_8411E0A4(entity, other, state);
        Vec3f_SetComponentsDuplicate(state + 0x5C, position[0], other[1], position[1]);
        Vec3f_SetComponentsDuplicate(state + 0x50, position[0], other[1], position[1]);
    }
    index = func_8411E1F8(entity);
    if ((*(u16 *)((u8 *)D_84193DD0 + index * 0x10 + 0x12) & 4) || (*(u16 *)(entity + 0x7F4) & 0x10)) {
        *(f32 *)(state + 0x60) = 30.0f;
        *(f32 *)(state + 0x54) = 30.0f;
    }
    Vec3f_SetComponentsDuplicate(state + 0x68, *(f32 *)((u8 *)model + 0xA8), *(f32 *)((u8 *)model + 0xAC), *(f32 *)((u8 *)model + 0xB0));
    BattleAnim_ModelDispatchFinish();
    *(f32 *)(state + 0x88) = 80.0f;
    (void)flip; (void)angle; (void)aux;
}
*/
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410F3E8.s")
/*
void BattleAnim_ModelDispatch_128(void *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    *(s16 *)(state + 0xA2) = 1;
    D_841911E8 = state;
    if (*(s16 *)(state + 0xA2) == 0) {
        return;
    }
    func_841203B4((u8 *)arg1 + 0x2C, (void *)*(u32 *)(state + 0x88), 0.02f);
    Vec3f_SetComponentsDuplicate(state + 0x40, *(f32 *)((u8 *)model + 0xB4), *(f32 *)((u8 *)model + 0xB8), *(f32 *)((u8 *)model + 0xBC));
    (void)func_8410B884(arg1, model, state, *(s16 *)(state + 0x36));
    if (func_80001FF0() == 0x32) *(f32 *)(state + 0x48) *= 0.5f;
    if (*(u16 *)((u8 *)D_84193DD0 + func_8411E1F8(arg1) * 0x10 + 0x12) & 2) *(f32 *)(state + 0x40) *= 0.5f;
    Camera_ComputeEyeFromAngles(state + 0x50, &state, *(f32 *)(state + 0x40), *(s16 *)(state + 0x3E), *(s32 *)(state + 0x3C));
}
*/
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_148(void *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1); D_841911E8 = state;
    func_80037120((u8 *)model + 0xA8, (u8 *)model + 0xB4, state + 0x74, state + 0x90, state + 0x92);
    BattleAnim_ModelDispatchFinish();
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_149(void *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1); D_841911E8 = state;
    BattleAnim_StepToS16((s16 *)(state + 0x92), -0x8000, 0x71C);
    Camera_ComputeEyeFromAngles((u8 *)model + 0xA8, (u8 *)model + 0xB4, *(f32 *)(state + 0x74), *(s16 *)(state + 0x90), *(s32 *)(state + 0x92));
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_155(void *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1); D_841911E8 = state;
    func_80037120((u8 *)model + 0xA8, (u8 *)model + 0xB4, state + 0x74, state + 0x90, state + 0x92);
    *(s16 *)(state + 0x92) += 0x5555;
    Camera_ComputeEyeFromAngles((u8 *)model + 0xA8, (u8 *)model + 0xB4, *(f32 *)(state + 0x74), *(s16 *)(state + 0x90), *(s32 *)(state + 0x92));
    BattleAnim_ModelDispatchFinish();
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_156(void *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1); D_841911E8 = state;
    BattleAnim_StepToS16((s16 *)(state + 0x92), 0x4000, 0x71C);
    Camera_ComputeEyeFromAngles((u8 *)model + 0xA8, (u8 *)model + 0xB4, *(f32 *)(state + 0x74), *(s16 *)(state + 0x90), *(s32 *)(state + 0x92));
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_134(void *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1); D_841911E8 = state; *(f32 *)((u8 *)model + 0x2C) = 30.0f;
    if (D_841911E0 == state) func_8410AF1C();
    BattleAnim_ModelDispatchFinish();
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_135(void *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1); D_841911E8 = state; *(f32 *)((u8 *)model + 0x2C) = 30.0f;
    Vec3f_SetComponentsDuplicate(*(u8 **)state, 0.0f, 30.0f, 0.0f);
    if (D_841911E0 == state) Vec3f_SetComponentsDuplicate(*(u8 **)state, 200.0f, 30.0f, 0.0f);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_162(void *model, void *arg1) { (void)func_8410B330(model, arg1); }
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_163(void *model, void *arg1) { (void)func_8410B330(model, arg1); }
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_169(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    if (*(s16 *)((u8 *)arg1 + 0x1A) == 0x5F || *(s16 *)((u8 *)arg1 + 0x1A) == 0xF9)
        state[0x98] = 0x23;
    else
        state[0x98] = 0x22;
    func_8410C934(model, arg1, *(s16 *)(state + 0x98));
    *(f32 *)(model + 0x2C) = 70.0f;
    BattleAnim_ModelDispatchFinish();
}

void BattleAnim_ModelDispatch_170(u8 *model, void *arg1) {
    u32 value = 0x42340000;
    D_841911E8 = func_8410B330(model, arg1);
    func_841203B4(model + 0x2C, (void *)value, 0.02f);
    func_8410E73C(model, arg1);
}

void BattleAnim_ModelDispatch_204(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    *(f32 *)(model + 0x2C) = 45.0f;
    func_84120960(model, arg1);
    *(s16 *)(state + 0x90) = 0x222;
    *(s16 *)(state + 0x92) = 0;
    *(f32 *)(state + 0x74) = 500.0f;
    BattleAnim_ModelDispatchCamera(model, state, 0.0f, 180.0f, 0.0f, -0x5E80, 1);
    BattleAnim_ModelDispatchFinish();
}

void BattleAnim_ModelDispatch_029(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    *(f32 *)(model + 0x2C) = 45.0f;
    func_84120960(model, arg1);
    *(s16 *)(state + 0x90) = 0x222; *(s16 *)(state + 0x92) = 0; *(f32 *)(state + 0x74) = 500.0f;
    BattleAnim_ModelDispatchCamera(model, state, 0.0f, 180.0f, 0.0f, -0x888, 1);
    BattleAnim_ModelDispatchFinish();
}

void BattleAnim_ModelDispatch_030(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    *(s16 *)(state + 0x92) += 0xE8;
    BattleAnim_ModelDispatchCamera(model, state, 0.0f, 0.0f, 0.0f, *(s16 *)(state + 0x92), 1);
    if (*(f32 *)(model + 0xAC) <= 0.0f) *(f32 *)(model + 0xAC) = 10.0f;
}

void BattleAnim_ModelDispatch_057(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1); D_841911E8 = state;
    *(s16 *)(state + 0x92) = 0; BattleAnim_ModelDispatchCamera(model, state, 0.0f, 180.0f, 0.0f, -0x5E80, 1);
}

void BattleAnim_ModelDispatch_058(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1); D_841911E8 = state;
    *(s16 *)(state + 0x92) += 0xE8; BattleAnim_ModelDispatchCamera(model, state, 0.0f, 0.0f, 0.0f, *(s16 *)(state + 0x92), 1);
}

void BattleAnim_ModelDispatch_064(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1); D_841911E8 = state; *(f32 *)(model + 0x2C) = 45.0f;
    func_84120960(model, arg1); *(s16 *)(state + 0x90) = 0x222; *(s16 *)(state + 0x92) = 0; *(f32 *)(state + 0x74) = 500.0f;
    BattleAnim_ModelDispatchCamera(model, state, 0.0f, 180.0f, 0.0f, -0x5E80, 1); BattleAnim_ModelDispatchFinish();
}

void BattleAnim_ModelDispatch_065(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1); D_841911E8 = state; *(s16 *)(state + 0x92) = 0;
    BattleAnim_ModelDispatchCamera(model, state, 0.0f, 0.0f, 0.0f, -0x5E80, 1); *(f32 *)(model + 0xB0) = *(f32 *)(model + 0xB0);
}

void BattleAnim_ModelDispatch_197(u8 *model, void *arg1) { D_841911E8 = func_8410B330(model, arg1); BattleAnim_ModelDispatchFinish(); }
void BattleAnim_ModelDispatch_183(u8 *model, void *arg1) { D_841911E8 = func_8410B330(model, arg1); func_8410C934(model, arg1, *(s16 *)(D_841911E8 + 0x98)); BattleAnim_ModelDispatchFinish(); }
void BattleAnim_ModelDispatch_190(u8 *model, void *arg1) { D_841911E8 = func_8410B330(model, arg1); func_8410CC90(model, arg1, *(s16 *)(D_841911E8 + 0x98)); BattleAnim_ModelDispatchFinish(); }
void BattleAnim_ModelDispatch_001(u8 *model, void *arg1) { D_841911E8 = func_8410B330(model, arg1); func_8410C934(model, arg1, *(s16 *)(D_841911E8 + 0x98)); BattleAnim_ModelDispatchFinish(); }
void BattleAnim_ModelDispatch_078(u8 *model, void *arg1) { D_841911E8 = func_8410B330(model, arg1); func_8410CAE4(model, arg1, *(s16 *)(D_841911E8 + 0x98)); BattleAnim_ModelDispatchFinish(); }
void BattleAnim_ModelDispatch_099(u8 *model, void *arg1) { D_841911E8 = func_8410B330(model, arg1); func_8410ED98(model, arg1, 0); BattleAnim_ModelDispatchFinish(); }
void BattleAnim_ModelDispatch_085(u8 *model, void *arg1) { D_841911E8 = func_8410B330(model, arg1); func_8410C934(model, arg1, *(s16 *)(D_841911E8 + 0x98)); BattleAnim_ModelDispatchFinish(); }
void BattleAnim_ModelDispatch_106(u8 *model, void *arg1) { D_841911E8 = func_8410B330(model, arg1); func_8410CD3C(model, arg1, *(s16 *)(D_841911E8 + 0x98)); BattleAnim_ModelDispatchFinish(); }
void BattleAnim_ModelDispatch_036(u8 *model, void *arg1) { D_841911E8 = func_8410B330(model, arg1); func_8410CC90(model, arg1, *(s16 *)(D_841911E8 + 0x98)); BattleAnim_ModelDispatchFinish(); }
void BattleAnim_ModelDispatch_043(u8 *model, void *arg1) { D_841911E8 = func_8410B330(model, arg1); func_8410CC90(model, arg1, *(s16 *)(D_841911E8 + 0x98)); BattleAnim_ModelDispatchFinish(); }
void BattleAnim_ModelDispatch_218(u8 *model, void *arg1) { D_841911E8 = func_8410B330(model, arg1); func_8410B420(model, arg1, *(s16 *)(D_841911E8 + 0x98)); BattleAnim_ModelDispatchFinish(); }
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_002(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    func_841203B4(model + 0x2C, (void *)*(u32 *)(state + 0x88), 0.3f);
    if (!func_8411DC80(*(u8 *)(arg1 + 0x61F), (void *)D_8418393C, 8))
        func_8410DFC4(model, arg1);
    if (func_8411DC80(*(s16 *)(state + 0x98), (void *)D_84183944, 0x1C))
        func_8410E688(model, arg1);
    else
        func_8410E73C(model, arg1);
    func_84110B2C(model, arg1);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_079(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    func_841203B4(model + 0x2C, (void *)*(u32 *)(state + 0x88), 0.3f);
    func_8410D174(model, arg1);
    func_8410B884(model, arg1, state, (void *)(s32)*(s16 *)(arg1 + 0x20));
    func_8410B60C(model, arg1, state, model + 0xB4);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_191(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    func_841203B4(model + 0x2C, (void *)*(u32 *)(state + 0x88), 0.3f);
    if (*(f32 *)(model + 0xB8) > 10.0f) {
        *(f32 *)(model + 0xB8) = 10.0f;
        func_8410DFC4(model, arg1);
    }
    func_8410B884(model, arg1, state, (void *)(s32)*(s16 *)(arg1 + 0x20));
    func_8410B60C(model, arg1, state, model + 0xB4);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_184(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    func_841203B4(model + 0x2C, (void *)*(u32 *)(state + 0x88), 0.3f);
    func_8410DFC4(model, arg1);
    func_8410C840(model, arg1, state, model + 0xB4);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_093(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    func_841203B4(model + 0x2C, (void *)*(u32 *)(state + 0x88), 0.3f);
    if (!func_8411DC80(*(u8 *)(arg1 + 0x61F), (void *)D_8418393C, 8)) {
        func_8410DFC4(model, arg1);
        func_8410E688(model, arg1);
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_113(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    if (D_841911E0 == state) {
        func_8410AFD4();
        func_8411EF08(arg1);
    } else {
        func_8411EF20(arg1);
    }
    func_8410C934(model, arg1, *(s16 *)(state + 0x98));
    BattleAnim_ModelDispatchFinish();
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_141(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    if (D_841911E0 == state) func_8411EF08(arg1);
    else func_8411EF20(arg1);
    func_8410C934(model, arg1, *(s16 *)(state + 0x98));
    BattleAnim_ModelDispatchFinish();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84110B2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_ModelDispatch_212.s")
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_009(u8 *model, void *arg1) {
    s32 index = func_8411E1F8(arg1);
    u8 *state;
    D_841911E8 = func_8410B330(model, arg1);
    state = D_841911E8;
    if (!(*(u16 *)(D_84193DD0 + index * 0x10 + 0x12) & 2))
        func_8410DFC4(model, arg1);
    if (func_8411DC80(*(u16 *)(state + 0x98), (void *)D_84183960, 0x10))
        func_8410E688(model, arg1);
    else
        func_8410E7D0(model, arg1);
    func_84110B2C(model, arg1);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_176(u8 *model, void *arg1) {
    D_841911E8 = func_8410B330(model, arg1);
    func_84108940(model + 0xB4, 0);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_022(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    func_84120BB4(model, arg1);
    func_8411EFE4(arg1);
    func_8410C934(model, arg1, *(s16 *)(state + 0x98));
    BattleAnim_ModelDispatchFinish();
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_023(u8 *model, void *arg1) {
    (void)arg1;
    *(f32 *)(model + 0x2C) = 45.0f;
    func_8410CF80(model);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_015(u8 *model, void *arg1) {
    *(f32 *)(model + 0x2C) = 45.0f;
    func_8410D088(model, arg1);
    func_8410E878(model, arg1);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_016(u8 *model, void *arg1) {
    *(f32 *)(model + 0x2C) = 45.0f;
    func_8410E73C(model, arg1);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_044(u8 *model, void *arg1) {
    *(f32 *)(model + 0x2C) = 45.0f;
    func_8410E73C(model, arg1);
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_071(u8 *model, void *arg1) {
    u8 *state = func_8410B330(model, arg1);
    D_841911E8 = state;
    func_8410EA58(model, arg1, *(s16 *)(state + 0x98));
    BattleAnim_ModelDispatchFinish();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411123C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111248.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841112C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111348.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841113F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841114A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111774.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111868.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841118E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841119CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111BEC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111C1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111C44.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111C6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111C8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111CF8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111D64.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111DB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111E50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111E80.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111EC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111FA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111FEC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411200C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841120A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841120AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112158.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841121CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112218.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112290.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841122D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112324.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112418.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112464.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112564.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112580.s")
#endif

void func_8411259C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841125A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841125F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112648.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841126C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112704.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411275C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411281C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411283C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411293C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841129E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112A40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112B44.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112B64.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112C98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112DB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112E40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112EAC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112EDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112FD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112FFC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113004.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411300C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113014.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841133EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113400.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113430.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411346C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841134A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841134D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113560.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113590.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113658.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841136E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841137F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841137F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411388C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113920.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841139D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_001.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_190.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_002.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113D38.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_218.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_219.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84114600.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84114678.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841146D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84114804.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_015.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_016.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84114BF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841153DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_017.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_043.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841155B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_044.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841156D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841157D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_045.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_050.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84115940.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84115988.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84115A24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_051.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_052.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_106.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84115D4C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84115D98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_107.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_108.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_057.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116010.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_058.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116248.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_059.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116410.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_155.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_156.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116604.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841166C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_157.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841168A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_113.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_114.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116A3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_115.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116B40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116BC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116EB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_029.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_030.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841175D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117648.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841176E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117744.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117880.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117948.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841179C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117A24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117AA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117C18.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117CAC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117CEC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117DC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117E94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84118138.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841182E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411845C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411854C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411862C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84118704.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84118754.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84118794.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_031.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_064.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_065.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_066.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_067.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_197.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_198.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_199.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_200.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_134.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_135.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_120.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_121.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_122.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_141.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_142.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_143.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411A310.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411A3D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_036.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_037.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_038.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_039.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_225.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_226.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_022.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_023.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_024.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_162.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_163.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_164.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_127.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_128.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_129.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_101.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_099.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_100.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411AF6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_092.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_093.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411B160.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_094.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_078.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_079.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_080.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_148.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_149.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_150.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411B710.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_176.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_177.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_178.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411BAB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_085.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_086.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_087.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411C1D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_169.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_170.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_171.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411C7B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_183.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_184.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_185.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_239.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_240.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_241.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_232.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_233.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_234.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_204.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_205.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_211.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_212.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_008.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_009.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_246.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/BattleAnim_Dispatch_247.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411D65C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411D7F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411D9B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411DA2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411DA4C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411DAE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411DBF4.s")
#endif
