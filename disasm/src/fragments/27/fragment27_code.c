#include "global.h"


#ifdef VERSION_US
void fragment27_main(u32 *arg0, u32 arg1) {
    *arg0 |= arg1;
}

void func_81100030(u32 *arg0, u32 arg1) {
    *arg0 &= ~arg1;
}

void func_81100044(u32 *arg0, u32 arg1) {
    *arg0 ^= arg1;
}

s32 ParticleMath_HasBits(s32 *arg0, s32 arg1) { s32 result = 0; if (*arg0 & arg1) { result = 1; } return result; }

s32 ParticleMath_LacksBits(u32 *arg0, u32 arg1) { s32 result = 0; if (!(*arg0 & arg1)) { result = 1; } return result; }

extern u32 D_80128C00;
s32 ParticleMath_RandomRange(s32 arg0) {
    u32 temp_a0 = guRandom() + D_80128C00;
    s32 var_v1;
    if (arg0 == 0) {
        var_v1 = 0;
    } else {
        var_v1 = (temp_a0 / 10) % arg0;
    }
    return var_v1;
}

extern s32 ParticleMath_RandomRange(s32 arg0);
s32 ParticleMath_RandomSigned(s32 arg0) {
    return ParticleMath_RandomRange(arg0 * 2) - arg0;
}

s32 func_81100120(s32 arg0, s32 arg1) {
    return ParticleMath_RandomRange(arg0) + arg1;
}


extern s32 ParticleMath_RandomSigned(s32 arg0);
s32 func_81100144(s32 arg0, s32 arg1) {
    return ParticleMath_RandomSigned(arg0) + arg1;
}

s32 ParticleMath_RandomSignedOffsetBySign(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_v1;
    temp_v0 = ParticleMath_RandomSigned(arg0);
    if (temp_v0 >= 0) {
        var_v1 = temp_v0 + arg1;
    } else {
        var_v1 = temp_v0 - arg1;
    }
    return var_v1;
}

extern f32 D_80087E50[];
extern f32 D_80088E50[];
typedef union { u32 bits; f32 value; } Frag27FloatBits;
f32 *ParticleMath_RotateVec3fY(f32 *arg0, Frag27FloatBits arg1, Frag27FloatBits arg2, Frag27FloatBits arg3, u16 arg4) {
    s32 index = arg4 >> 4;
    f32 temp_fv0 = D_80087E50[index];
    f32 fa0 = arg1.value;
    f32 temp_fv1 = D_80088E50[index];
    f32 fa1 = arg3.value;
    arg0[0] = fa0 * temp_fv1 + fa1 * temp_fv0;
    arg0[1] = arg2.value;
    arg0[2] = -fa0 * temp_fv0 + fa1 * temp_fv1;
    return arg0;
}

void ParticleMath_CopyVec3f(f32 *arg0, f32 *arg1) { arg0[0] = arg1[0]; arg0[1] = arg1[1]; arg0[2] = arg1[2]; }

void func_81100228(s16 *arg0, const s16 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    arg0[2] = arg1[2];
}
#pragma C_FUNCTION_PADDING(12)
#endif
