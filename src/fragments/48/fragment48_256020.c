#include "global.h"


#ifdef VERSION_US
extern f64 D_87C03D90;
extern f64 D_87C03D98;
extern f64 D_87C03DA0;
extern f64 D_87C03DA8;
f64 func_87C00020(f64 arg0) {
    f64 upper;
    f64 step;
    while (D_87C03D90 <= arg0) {
        arg0 -= D_87C03D98;
    }
    upper = D_87C03DA0;
    step = D_87C03DA8;
    if (arg0 <= upper) {
        do {
            arg0 += step;
        } while (arg0 <= upper);
    }
    return arg0;
}

f64 func_87C00090(f64 arg0, f64 arg1, f64 arg4) {
    if (arg0 < (arg1 - arg4)) {
        return arg0 + arg4;
    }
    if ((arg1 + arg4) < arg0) {
        return arg0 - arg4;
    }
    return arg1;
}

extern f64 func_87C00020(f64);
void func_87C000E4(f64 arg0, f64 arg1) {
    func_87C00020(func_87C00020(arg1) - func_87C00020(arg0));
}

void *func_87C00120(void *arg0, f64 arg1, f64 arg2, f64 arg3) {
    *(f64 *)((u8 *)arg0 + 0) = arg1;
    *(f64 *)((u8 *)arg0 + 8) = arg2;
    *(f64 *)((u8 *)arg0 + 0x10) = arg3;
    return arg0;
}

void *func_87C00144(void *arg0) {
    (*(f64 *)((u8 *)arg0 + 0x10)) = 0.0;
    (*(f64 *)((u8 *)arg0 + 8)) = 0.0;
    (*(f64 *)((u8 *)arg0 + 0)) = 0.0;
    return arg0;
}

void *func_87C00160(void *arg0, void *arg1, void *arg2) {
    (*(f64 *)((u8 *)(arg0) + (0))) = (f64) ((*(f64 *)((u8 *)(arg1) + (0))) - (*(f64 *)((u8 *)(arg2) + (0))));
    (*(f64 *)((u8 *)(arg0) + (8))) = (f64) ((*(f64 *)((u8 *)(arg1) + (8))) - (*(f64 *)((u8 *)(arg2) + (8))));
    (*(f64 *)((u8 *)(arg0) + (0x10))) = (f64) ((*(f64 *)((u8 *)(arg1) + (0x10))) - (*(f64 *)((u8 *)(arg2) + (0x10))));
    return arg0;
}

void *func_87C00198(void *arg0, void *arg1, void *arg2) {
    typedef struct { f64 x; f64 y; f64 z; } V;
    V *dst = arg0;
    V *a = arg1;
    V *b = arg2;
    dst->x = a->x + b->x;
    dst->y = a->y + b->y;
    dst->z = a->z + b->z;
    return arg0;
}

void *func_87C001D0(void *arg0, void *arg1, void *arg2) {
    typedef struct { f64 x; f64 y; f64 z; } V;
    V *dst = arg0;
    V *a = arg1;
    V *b = arg2;
    dst->x = a->x * b->x;
    dst->y = a->y * b->y;
    dst->z = a->z * b->z;
    return arg0;
}

f64 func_87C00208(void *a, void *b) {
    typedef struct {
        f64 x;
        f64 y;
        f64 z;
    } V;

    V *x = a;
    V *y = b;
    return x->x * y->x + x->y * y->y + x->z * y->z;
}

void *func_87C00238(void *arg0, void *arg1, void *arg2) {
    typedef struct { f64 x; f64 y; f64 z; } V;
    V *dst = arg0;
    V *a = arg1;
    V *b = arg2;
    dst->x = (a->y * b->z) - (b->y * a->z);
    dst->y = (a->z * b->x) - (b->z * a->x);
    dst->z = (a->x * b->y) - (b->x * a->y);
    return arg0;
}

void *func_87C002A8(void *arg0, void *arg1, f64 arg2) {
    *(f64 *)((u8 *)arg0 + 0x00) = *(f64 *)((u8 *)arg1 + 0x00) * arg2;
    *(f64 *)((u8 *)arg0 + 0x08) = *(f64 *)((u8 *)arg1 + 0x08) * arg2;
    *(f64 *)((u8 *)arg0 + 0x10) = *(f64 *)((u8 *)arg1 + 0x10) * arg2;
    return arg0;
}

void *func_87C002DC(void *arg0, void *arg1) {
    *(f64 *)((u8 *)arg0 + 0x00) = -*(f64 *)((u8 *)arg1 + 0x00);
    *(f64 *)((u8 *)arg0 + 0x08) = -*(f64 *)((u8 *)arg1 + 0x08);
    *(f64 *)((u8 *)arg0 + 0x10) = -*(f64 *)((u8 *)arg1 + 0x10);
    return arg0;
}

void *func_87C00308(void *arg0, void *arg1, void *arg2, f64 arg3) {
    typedef struct { f64 x; f64 y; f64 z; } V;
    V *dst = arg0;
    V *a = arg1;
    V *b = arg2;
    dst->x = ((b->x - a->x) * arg3) + a->x;
    dst->y = ((b->y - a->y) * arg3) + a->y;
    dst->z = ((b->z - a->z) * arg3) + a->z;
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_256020/func_87C0035C.s")

void func_87C003BC(void *arg0, void *arg1, void *arg2) {
    typedef struct { f64 x; f64 y; f64 z; } V;
    V *out = arg0;
    V *a = arg1;
    V *b = arg2;
    f64 scale = func_87C00208(arg1, arg2);
    out->x = a->x - (b->x * scale);
    out->y = a->y - (b->y * scale);
    out->z = a->z - (b->z * scale);
}

void func_87C00438(void *arg0, void *arg1, void *arg2, void *arg3) {
    typedef struct { f64 x; f64 y; f64 z; } V;
    V *a = arg0;
    V *b = arg1;
    V *mid = arg2;
    V *out = arg3;
    f64 scale = func_87C00208(a, b);
    mid->x = b->x * scale;
    mid->y = b->y * scale;
    mid->z = b->z * scale;
    out->x = a->x - mid->x;
    out->y = a->y - mid->y;
    out->z = a->z - mid->z;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_256020/func_87C004C4.s")

extern void func_87C00BC8();
extern void func_87C004C4();
void func_87C00628(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp18[8];
    func_87C00BC8(sp18, arg2);
    func_87C004C4(arg0, arg1, sp18);
}

f64 func_87C00664(void *arg0) {
    typedef struct { f64 x; f64 y; f64 z; } V;
    V *v = arg0;
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

extern f64 func_87C00664(void *);
f64 func_87C0068C(void *arg0) {
    return sqrtf((f32)func_87C00664(arg0));
}

f64 func_87C006B4(void *arg0, void *arg1) {
    typedef struct { f64 x; f64 y; f64 z; } V;
    V *a = arg0;
    V *b = arg1;
    f64 dx = a->x - b->x;
    f64 dy = a->y - b->y;
    f64 dz = a->z - b->z;
    return dx * dx + dy * dy + dz * dz;
}

extern f64 func_87C006B4(void *, void *);
f64 func_87C006F0(void *arg0, void *arg1) {
    return sqrtf((f32)func_87C006B4(arg0, arg1));
}

extern f64 D_87C03DB0;
extern f64 func_87C00664(void *);
extern void * func_87C00120(void *arg0, f64 arg1, f64 arg2, f64 arg3);
extern void * func_87C002A8(void *arg0, void *arg1, f64 arg2);
void *func_87C00718(void *arg0, void *arg1, f64 arg2) {
    f64 length = func_87C00664(arg1);
    if (D_87C03DB0 < length) {
        return func_87C002A8(arg0, arg1, arg2 / (f64)sqrtf((f32)length));
    }
    return func_87C00120(arg0, 0.0, 0.0, 0.0);
}

f32 *func_87C007B0(f32 *arg0, f64 *arg1) {
    arg0[0] = (f32)arg1[0];
    arg0[1] = (f32)arg1[1];
    arg0[2] = (f32)arg1[2];
    return arg0;
}

f64 func_87C007DC(const f64 *arg0, const f64 *arg1) {
    return arg0[0] * arg1[0] + arg0[1] * arg1[1] + arg0[2] * arg1[2] - arg0[3];
}

extern f64 func_87C007DC(const f64 *, const f64 *);
void func_87C00814(void *arg0, void *arg1, void *arg2) {
    typedef struct { f64 x; f64 y; f64 z; } V;
    V *a = arg0;
    V *b = arg1;
    V *out = arg2;
    f64 scale = func_87C007DC(arg0, arg1);
    out->x = b->x - (scale * a->x);
    out->y = b->y - (scale * a->y);
    out->z = b->z - (scale * a->z);
}

void func_87C00884(f64 *arg0, f64 arg1, f64 arg2, f64 arg3, f64 arg4) {
    arg0[0] = arg1;
    arg0[1] = arg2;
    arg0[2] = arg3;
    arg0[3] = arg4;
}

void *func_87C008B0(void *arg0) {
    *(f64 *)((u8 *)arg0 + 0x08) = 0.0;
    *(f64 *)((u8 *)arg0 + 0x10) = 0.0;
    *(f64 *)((u8 *)arg0 + 0x18) = 0.0;
    *(f64 *)((u8 *)arg0 + 0x00) = 1.0;
    return arg0;
}

void *func_87C008DC(void *arg0, f64 arg1, f64 arg2, f64 arg3, f64 arg4) {
    *(f64 *)((u8 *)arg0 + 0x00) = arg1;
    *(f64 *)((u8 *)arg0 + 0x08) = arg2;
    *(f64 *)((u8 *)arg0 + 0x10) = arg3;
    *(f64 *)((u8 *)arg0 + 0x18) = arg4;
    return arg0;
}

extern void func_87C01278(void *, void *);
void func_87C00908(void *arg0, f64 arg1, f64 arg2, f64 arg3) {
    f64 local[3];
    local[0] = arg1;
    local[1] = arg2;
    local[2] = arg3;
    func_87C01278(arg0, local);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_256020/func_87C00944.s")

extern void * func_87C008DC(void *arg0, f64 arg1, f64 arg2, f64 arg3, f64 arg4);
void func_87C00A14(void *arg0, void *arg1, void *arg2) {
    typedef struct { f64 x; f64 y; f64 z; f64 w; } V;
    V *a = arg1;
    V *b = arg2;
    func_87C008DC(arg0, a->x + b->x, a->y + a->y, a->z + b->z, a->w + b->w);
  }

void *func_87C00A78(void *arg0, void *arg1, void *arg2) {
    typedef struct { f64 x; f64 y; f64 z; f64 w; } V;
    V *a = arg1;
    V *b = arg2;
    f64 zero = 0.0;
    func_87C008DC(arg0, a->x - b->x, zero, a->z - b->z, a->w - b->w);
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_256020/func_87C00AE4.s")

f64 func_87C00B58(u8 *arg0) {
    f64 temp_fv1 = *(f64 *)(arg0 + 0);
    f64 temp_fa0 = *(f64 *)(arg0 + 8);
    f64 temp_fa1 = *(f64 *)(arg0 + 0x10);
    f64 temp_ft4 = *(f64 *)(arg0 + 0x18);
    return (f64) sqrtf((f32) ((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1) + (temp_ft4 * temp_ft4)));
}

void *func_87C00B94(void *arg0, void *arg1) {
    *(f64 *)((u8 *)arg0 + 0x00) = *(f64 *)((u8 *)arg1 + 0x00);
    *(f64 *)((u8 *)arg0 + 0x08) = -*(f64 *)((u8 *)arg1 + 0x08);
    *(f64 *)((u8 *)arg0 + 0x10) = -*(f64 *)((u8 *)arg1 + 0x10);
    *(f64 *)((u8 *)arg0 + 0x18) = -*(f64 *)((u8 *)arg1 + 0x18);
    return arg0;
}

extern void func_87C00AE4(s32, s32); extern void *func_87C00B94(void *, void *);
void func_87C00BC8(void *arg0, void *arg1) {
    func_87C00AE4((s32)(u32)arg0, (s32)(u32)func_87C00B94(arg0, arg1));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_256020/func_87C00BF4.s")

extern f64 func_87C00664(void *);
extern void *func_87C00718(void *, void *, f64);
extern void func_87C00BF4(void *, void *, f64);
extern void func_87C00944(void *, void *, void *);
void *func_87C00C80(void *arg0, void *arg1) {
    typedef struct { f64 x; f64 y; f64 z; } V3;
    typedef struct { f64 x; f64 y; f64 z; f64 w; } V4;
    V4 result;
    f64 length;
    V3 normalized;
    length = func_87C00664(arg1);
    if (length > 0.0) {
        func_87C00BF4(&result,
            func_87C00718(&normalized, arg1, 1.0),
            (f64)sqrtf((f32)length));
        func_87C00944(arg0, arg0, &result);
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_256020/func_87C00D14.s")

extern f64 D_87C03DE8;
extern f64 func_87C00D14(f64, f64);
f64 func_87C00F9C(f64 arg0) {
    f64 root;
    f64 abs_value;
    if (arg0 > 0.0) {
        abs_value = arg0;
    } else {
        abs_value = -arg0;
    }
    if (abs_value > 1.0) {
        return 0.0;
    }
    root = (f64)sqrtf((f32)(1.0 - (arg0 * arg0)));
    if (root != 0.0) {
        return -func_87C00D14(arg0, root);
    }
    if (arg0 > 0.0) {
        return 0.0;
    }
    return D_87C03DE8;
}

extern f64 func_87C00F9C(f64);
extern void func_87C00BF4(void *, void *, f64);
extern f64 func_87C00208(void *a, void *b);
extern void * func_87C00238(void *arg0, void *arg1, void *arg2);
void func_87C01048(void *arg0, void *arg1, void *arg2, f64 arg3) {
    typedef struct { f64 x; f64 y; f64 z; } V;
    V cross;
    f64 angle;
    func_87C00238(&cross, arg1, arg2);
    angle = func_87C00F9C(func_87C00208(arg1, arg2));
    func_87C00BF4(arg0, &cross, (-angle) * arg3);
  }

extern void func_87C01048(void *, void *, void *, f64);
void func_87C010AC(void *arg0, void *arg1, void *arg2) {
    func_87C01048(arg0, arg1, arg2, 1.0);
}

void *func_87C010D8(void *arg0, void *arg1) {
    (*(f64 *)((u8 *)(arg0) + (0))) = (f64) (*(f64 *)((u8 *)(arg1) + (0)));
    (*(f64 *)((u8 *)(arg0) + (8))) = (f64) (*(f64 *)((u8 *)(arg1) + (8)));
    (*(f64 *)((u8 *)(arg0) + (0x10))) = (f64) (*(f64 *)((u8 *)(arg1) + (0x10)));
    (*(f64 *)((u8 *)(arg0) + (0x18))) = (f64) (*(f64 *)((u8 *)(arg1) + (0x18)));
    return arg0;
}

f64 func_87C01100(void *arg0, void *arg1) {
    typedef struct { f64 x; f64 y; f64 z; f64 w; } V;
    V *a = arg0;
    V *b = arg1;
    return (a->y * b->y) + (a->z * b->z) + (a->w * b->w) + (a->x * b->x);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_256020/func_87C01140.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_256020/func_87C01278.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_256020/func_87C013CC.s")

void func_87C01540(void *arg0, void *arg1) {
    typedef struct { f64 x; f64 y; f64 z; f64 w; } V;
    V *a = arg0;
    V *out = arg1;
    out->x = (1.0 - (2.0 * (a->z * a->z))) - (2.0 * (a->w * a->w));
    out->y = (2.0 * (a->y * a->z)) + (2.0 * (a->x * a->w));
    out->z = (2.0 * (a->y * a->w)) - (2.0 * (a->x * a->z));
}

void func_87C015E4(void *arg0, void *arg1) {
    typedef struct { f64 x; f64 y; f64 z; f64 w; } V;
    V *a = arg0;
    V *out = arg1;
    out->x = (2.0 * (a->y * a->z)) - (2.0 * (a->x * a->w));
    out->y = (1.0 - (2.0 * (a->y * a->y))) - (2.0 * (a->w * a->w));
    out->z = (2.0 * (a->z * a->w)) + (2.0 * (a->x * a->y));
}

void func_87C01684(void *arg0, void *arg1) {
    typedef struct { f64 x; f64 y; f64 z; f64 w; } V;
    V *a = arg0;
    V *out = arg1;
    out->x = (2.0 * (a->y * a->w)) + (2.0 * (a->x * a->z));
    out->y = (2.0 * (a->z * a->w)) - (2.0 * (a->x * a->y));
    out->z = (1.0 - (2.0 * (a->y * a->y))) - (2.0 * (a->z * a->z));
}
#endif
