#include "global.h"


#ifdef VERSION_US
void func_82102B80(u8 *arg0, f32 arg1, f32 arg2) {
    *(f32 *)arg0 = arg1;
    *(f32 *)(arg0 + 4) = arg2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15CBC0/func_82102B94.s")

void func_82102BE8(u8 *arg0, u8 *arg1) {
    *(f32 *)(arg0 + 0) += *(f32 *)(arg1 + 0);
    *(f32 *)(arg0 + 4) += *(f32 *)(arg1 + 4);
}

void func_82102C0C(f32 *arg0, const f32 *arg1) {
    arg0[0] = arg0[0] - arg1[0];
    arg0[1] = arg0[1] - arg1[1];
}

void func_82102C30(u8 *arg0, u8 *arg1, u8 *arg2) {
    *(f32 *)(arg0 + 0) = *(f32 *)(arg2 + 0) + *(f32 *)(arg1 + 0);
    *(f32 *)(arg0 + 4) = *(f32 *)(arg2 + 4) + *(f32 *)(arg1 + 4);
}

void func_82102C54(f32 *arg0, const f32 *arg1, const f32 *arg2) {
    arg0[0] = arg1[0] - arg2[0];
    arg0[1] = arg1[1] - arg2[1];
}

f32 func_82102C78(u8 *arg0) {
    f32 x = *(f32 *)(arg0 + 0);
    f32 y = *(f32 *)(arg0 + 4);
    return sqrtf(x * x + y * y);
}

f32 func_82102C98(u8 *arg0) {
    f32 x = *(f32 *)(arg0 + 0);
    f32 y = *(f32 *)(arg0 + 4);
    return x * x + y * y;
}

f32 func_82102CB4(u8 *arg0, u8 *arg1) { f32 x = *(f32 *)(arg0 + 0) - *(f32 *)(arg1 + 0); f32 y = *(f32 *)(arg0 + 4) - *(f32 *)(arg1 + 4); return sqrtf(x * x + y * y); }

f32 func_82102CE4(u8 *arg0, u8 *arg1) { f32 x = *(f32 *)(arg0 + 0) - *(f32 *)(arg1 + 0); f32 y = *(f32 *)(arg0 + 4) - *(f32 *)(arg1 + 4); return x * x + y * y; }

extern void func_821028E0(f32, f32);
void func_82102D10(f32 *arg0) {
    func_821028E0(arg0[0], arg0[1]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15CBC0/func_82102D34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15CBC0/func_82102DB8.s")
#endif
