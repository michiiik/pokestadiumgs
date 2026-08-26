#include "global.h"


#ifdef VERSION_US
typedef struct { f32 x; f32 y; f32 z; } Vec3f84105880;
extern Vec3f84105880 *func_80035A10(Vec3f84105880 *);
Vec3f84105880 *func_84105880(Vec3f84105880 *arg0, Vec3f84105880 arg1, Vec3f84105880 arg2) {
    arg0->x = arg2.x - arg1.x;
    arg0->y = arg2.y - arg1.y;
    arg0->z = arg2.z - arg1.z;
    if (arg2.x == arg1.x && arg0->y == 0.0f && arg0->z == 0.0f) {
        arg0->x = 0.0f;
        arg0->y = 0.0f;
        arg0->z = 1.0f;
    } else {
        func_80035A10(arg0);
    }
    return arg0;
}

extern u8 *D_84190114;
void BattleAnim_GetPointAlongCameraRay(u8 *arg0, f32 arg1) {
    *(f32 *)(arg0 + 0) = arg1 * *(f32 *)(D_84190114 + 0x58) + *(f32 *)(D_84190114 + 0x40);
    *(f32 *)(arg0 + 4) = arg1 * *(f32 *)(D_84190114 + 0x5C) + *(f32 *)(D_84190114 + 0x44);
    *(f32 *)(arg0 + 8) = arg1 * *(f32 *)(D_84190114 + 0x60) + *(f32 *)(D_84190114 + 0x48);
}

extern u8 *D_84190090;
extern s32 MathUtil_Atan2s(f32, f32);
void func_84105988(u8 *arg0, u8 *arg1) {
    f32 x = *(f32 *)(D_84190090 + 0xA8) - *(f32 *)(D_84190090 + 0xB4);
    f32 y = *(f32 *)(D_84190090 + 0xAC) - *(f32 *)(D_84190090 + 0xB8);
    f32 z = *(f32 *)(D_84190090 + 0xB0) - *(f32 *)(D_84190090 + 0xBC);
    *(s16 *)arg0 = MathUtil_Atan2s(sqrtf(x * x + z * z), y);
    *(s16 *)arg1 = MathUtil_Atan2s(z, x);
}

void func_84105A0C(u8 *arg0) {
    f32 x = *(f32 *)(D_84190090 + 0xA8) - *(f32 *)(D_84190090 + 0xB4);
    f32 z = *(f32 *)(D_84190090 + 0xB0) - *(f32 *)(D_84190090 + 0xBC);
    *(s16 *)arg0 = MathUtil_Atan2s(z, x);
}

void func_84105A54(u8 *arg0, u8 *arg1) {
    f32 x = *(f32 *)(D_84190090 + 0xB4) - *(f32 *)(D_84190090 + 0xA8);
    f32 y = *(f32 *)(D_84190090 + 0xB8) - *(f32 *)(D_84190090 + 0xAC);
    f32 z = *(f32 *)(D_84190090 + 0xBC) - *(f32 *)(D_84190090 + 0xB0);
    *(s16 *)arg0 = MathUtil_Atan2s(sqrtf(x * x + z * z), y);
    *(s16 *)arg1 = MathUtil_Atan2s(z, x);
}

void func_84105AD8(u8 *arg0) {
    f32 x = *(f32 *)(D_84190090 + 0xB4) - *(f32 *)(D_84190090 + 0xA8);
    f32 z = *(f32 *)(D_84190090 + 0xBC) - *(f32 *)(D_84190090 + 0xB0);
    *(s16 *)arg0 = MathUtil_Atan2s(z, x);
}

void func_84105B20(u8 *arg0, u8 *arg1) {
    *(s16 *)arg0 = *(s16 *)(D_84190114 + 0x76);
    *(s16 *)arg1 = *(s16 *)(D_84190114 + 0x78);
}

void func_84105B44(u8 *arg0) {
    *(s16 *)arg0 = *(s16 *)(D_84190114 + 0x78);
}

void func_84105B58(u8 *arg0, u8 *arg1) {
    *(s16 *)arg0 = *(s16 *)(*(u8 **)&D_84190114 + 0x70);
    *(s16 *)arg1 = *(s16 *)(*(u8 **)&D_84190114 + 0x72);
}

void func_84105B7C(u8 *arg0) {
    *(s16 *)arg0 = *(s16 *)(D_84190114 + 0x72);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375110/func_84105B90.s")
#endif
