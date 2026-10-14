#include "global.h"


#ifdef VERSION_US
typedef struct F65Vec2 { f32 x; f32 y; } F65Vec2;
extern f32 D_87D007D0, D_87D007D4;
extern void MtxF_Identity(f32*);
extern void MtxF_Copy(void*, void*);
extern void MtxF_Multiply(void*, void*, void*);
extern void* Vec3f_CrossProduct(void*, void*, void*);
extern void* func_80035A10(void*);
extern f32 __sinf(f32);
extern f32 __cosf(f32);
extern f32 func_87D005E8(f32 *a, f32 *b, f32 *c);
void fragment65_main(f32* m, f32 angle, f32 x, f32 y, f32 z) {
    f32 sine;
    f32 cosine;
    f32 xy;
    f32 yz;
    f32 zx;
    f32 square;
    func_87D005E8(&x, &y, &z);
    angle = angle * D_87D007D0;
    sine = __sinf(angle);
    cosine = __cosf(angle);
    xy = (x * y) * (1.0f - cosine);
    yz = (y * z) * (1.0f - cosine);
    zx = (z * x) * (1.0f - cosine);
    MtxF_Identity(m);
    square = x * x;
    m[0] = ((1.0f - square) * cosine) + square;
    m[9] = yz - (x * sine);
    m[6] = (x * sine) + yz;
    square = y * y;
    m[5] = ((1.0f - square) * cosine) + square;
    m[8] = (y * sine) + zx;
    m[2] = zx - (y * sine);
    square = z * z;
    m[10] = ((1.0f - square) * cosine) + square;
    m[4] = xy - (z * sine);
    m[1] = (z * sine) + xy;
}

void func_87D001A4(f32* m, f32 angle, f32 x, f32 y, f32 z) {
    f32 sine;
    f32 cosine;
    f32 horizontal;
    f32 reciprocal;
    func_87D005E8(&x, &y, &z);
    angle = angle * D_87D007D4;
    sine = __sinf(angle);
    cosine = __cosf(angle);
    horizontal = sqrtf((x * x) + (z * z));
    MtxF_Identity(m);
    if (horizontal != 0.0f) {
        reciprocal = 1.0f / horizontal;
        m[0] = (((-z * cosine) - ((sine * y) * x)) * reciprocal);
        m[4] = (((z * sine) - ((cosine * y) * x)) * reciprocal);
        m[8] = -x;
        m[12] = 0.0f;
        m[1] = sine * horizontal;
        m[5] = cosine * horizontal;
        m[9] = -y;
        m[13] = 0.0f;
        m[2] = (((cosine * x) - ((sine * y) * z)) * reciprocal);
        m[6] = (((-sine * x) - ((cosine * y) * z)) * reciprocal);
        m[10] = -z;
        m[14] = 0.0f;
        m[3] = 0.0f;
        m[7] = 0.0f;
        m[11] = 0.0f;
        m[15] = 1.0f;
    }
}

void func_87D00354(f32* m, f32* vector) {
    f32 rotation[16];
    f32 copy[16];
    f32 angle;
    f32 up[3];
    f32 axis[3];
    f32 x;
    f32 z;
    x = vector[0];
    z = vector[2];
    angle = sqrtf((x * x) + (z * z));
    if (angle > 0.0f) {
        up[0] = 0.0f;
        up[2] = 0.0f;
        up[1] = 1.0f;
        Vec3f_CrossProduct(axis, up, vector);
        func_80035A10(axis);
        MtxF_Copy(copy, m);
        fragment65_main(rotation, angle, axis[0], axis[1], axis[2]);
        MtxF_Multiply(m, copy, rotation);
        func_87D005E8(&m[0], &m[1], &m[2]);
        func_87D005E8(&m[4], &m[5], &m[6]);
        func_87D005E8(&m[8], &m[9], &m[10]);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/65/fragment65_code/func_87D00438.s")

f32 func_87D0059C(f32 *arg0, f32 *arg1) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv1 = *arg1;
    temp_fa0 = *arg0;
    temp_fv0 = sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0));
    if (temp_fv0 != 0.0f) {
        *arg0 = temp_fa0 / temp_fv0;
        *arg1 /= temp_fv0;
    }
    return temp_fv0;
}

f32 func_87D005E8(f32 *a, f32 *b, f32 *c) {
    f32 r = sqrtf((*a) * (*a) + (*b) * (*b) + (*c) * (*c));
    if (r) {
        *a /= r;
        *b /= r;
        *c /= r;
    }
    return r;
}

void func_87D00648(void *arg0, void *arg1, void *arg2) {
    (*(f32 *)((u8 *)(arg0) + (0))) = (f32) -((*(f32 *)((u8 *)(arg2) + (4))) - (*(f32 *)((u8 *)(arg1) + (4))));
    (*(f32 *)((u8 *)(arg0) + (4))) = (f32) ((*(f32 *)((u8 *)(arg2) + (0))) - (*(f32 *)((u8 *)(arg1) + (0))));
}

s32 func_87D00670(f32 *a, f32 *b, f32 *second, f32 *c, F65Vec2 *d, f32 *first)
{
  f32 p;
  f32 q;
  s32 result;
  f32 *directionX;
  p = b[1] * d->x;
  directionX = &d->x;
  q = b[0] * d->y;
  result = 0;
  if (p != q)
  {
    result = 1;
    *first = ((b[0] * (c[1] - a[1])) + ((a[0] - c[0]) * b[1])) / (p - q);
    *second = ((d->y * (c[0] - a[0])) + ((a[1] - c[1]) * (*directionX))) / (q - p);
  }
  return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/65/fragment65_code/func_87D00720.s")
#endif
