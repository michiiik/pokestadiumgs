#include "global.h"


#ifdef VERSION_US
void func_8160BA20(s16 *arg0, s16 arg1, s16 arg2) {
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E35C0/func_8160BAE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E35C0/func_8160BB30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E35C0/func_8160BB60.s")

s32 func_8160BBCC(s16 *arg0, s16 *arg1) {
    s16 dx = arg0[0] - arg1[0];
    s16 dy = arg0[1] - arg1[1];
    return (s16)(dx * dx + dy * dy);
}

s32 func_8160BC1C(u8 *arg0) {
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E35C0/func_8160BC28.s")
#endif
