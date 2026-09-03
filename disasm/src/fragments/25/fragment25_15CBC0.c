#include "global.h"


#ifdef VERSION_US
void func_82102B80(u8 *arg0, f32 arg1, f32 arg2) {
    *(f32 *)arg0 = arg1;
    *(f32 *)(arg0 + 4) = arg2;
}

void func_82102B94(u8 *arg0, f32 arg1, f32 arg2) {
    *(f32 *)(arg0 + 0) = sinf(arg2) * arg1;
    *(f32 *)(arg0 + 4) = cosf(arg2) * arg1;
}

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

extern f32 D_82104160;
extern f32 D_82104164;
extern f32 D_82104168;
extern f32 D_8210416C;
void func_82102D34(f32 *arg0) {
    f32 value;
    f32 limit;
    f32 step;

    value = *arg0;
    limit = D_82104160;
    if (limit < *arg0) {
        step = D_82104164;
        do {
            *arg0 -= step;
        } while (limit < *arg0);
    }
    limit = D_82104168;
    step = D_8210416C;
    if (*arg0 < limit) {
        do {
            *arg0 += step;
        } while (*arg0 < limit);
    }
}

typedef struct { f32 x; f32 y; } V82102;
void func_82102DB8(V82102 *arg0, V82102 *arg1, f32 arg2) {
    f32 t = 1.0f - arg2;
    arg0->x = arg0->x * arg2 + t * arg1->x;
    arg0->y = arg0->y * arg2 + t * arg1->y;
}
#endif
