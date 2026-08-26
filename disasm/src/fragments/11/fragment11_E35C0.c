#include "global.h"


#ifdef VERSION_US
void Particle_Field9A_SetXY_0A3A0(s16 *arg0, s16 arg1, s16 arg2) {
    arg0[0] = arg1;
    arg0[1] = arg2;
}

void func_8160BA44(s32 arg0, s32 arg1, s32 arg2) {}

void func_8160BA54(s16 *arg0, s16 *arg1) {
    arg0[0] += arg1[0];
    arg0[1] += arg1[1];
}

void func_8160BA78(s16 *arg0, s16 *arg1) {
    arg0[0] -= arg1[0];
    arg0[1] -= arg1[1];
}

typedef struct { s16 x; s16 y; } Vec2s_8160BA9C; void func_8160BA9C(Vec2s_8160BA9C *arg0, Vec2s_8160BA9C *arg1, Vec2s_8160BA9C *arg2) { arg0->x = arg1->x + arg2->x; arg0->y = arg1->y + arg2->y; }

void func_8160BAC0(u8 *arg0, u8 *arg1, u8 *arg2) { *(s16 *)(arg0 + 0) = *(s16 *)(arg1 + 0) - *(s16 *)(arg2 + 0); *(s16 *)(arg0 + 2) = *(s16 *)(arg1 + 2) - *(s16 *)(arg2 + 2); }

s32 func_8160BAE4(s16 *arg0) {
    s16 x;
    s16 y;
    s32 result;
    x = arg0[0];
    y = arg0[1];
    result = sqrtf((f32)(x * x + y * y));
    return (s16)result;
}

s32 func_8160BB30(s16 *arg0) {
    s16 x = arg0[0];
    s16 y = arg0[1];
    return (s16)(x * x + y * y);
}

s32 func_8160BB60(s16 *arg0, s16 *arg1) {
    s16 dx;
    s16 dy;
    s32 result;
    dx = arg0[0] - arg1[0];
    dy = arg0[1] - arg1[1];
    result = sqrtf((f32)(dx * dx + dy * dy));
    return (s16)result;
}

s32 func_8160BBCC(s16 *arg0, s16 *arg1) {
    s16 dx = arg0[0] - arg1[0];
    s16 dy = arg0[1] - arg1[1];
    return (s16)(dx * dx + dy * dy);
}

s32 func_8160BC1C(u8 *arg0) {
    return 0;
}

void func_8160BC28(Vec2s_8160BA9C *arg0, Vec2s_8160BA9C *arg1, f32 arg2) {
    f32 inv = 1.0f - arg2;
    arg0->x = (arg0->x * arg2) + (inv * arg1->x);
    arg0->y = (arg0->y * arg2) + (inv * arg1->y);
}
#endif
