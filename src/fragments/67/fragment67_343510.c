#include "global.h"


#ifdef VERSION_US
void func_82906A10(f32 *arg0, f32 *arg1) { arg0[0] = arg1[0]; arg0[1] = arg1[1]; arg0[2] = arg1[2]; }

void func_82906A2C(f32 *arg0, const f32 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    arg0[2] = arg1[2];
    arg0[3] = arg1[3];
}

/* mkdraft:func_82906A50 begin */
extern f32 Math_StepToF(f32, f32, f32, f32);

void func_82906A50(f32 *arg0, f32 *arg1, f32 *arg2, s16 arg3) {
    f32 stepX;
    f32 stepY;
    f32 stepZ;

    stepX = (arg1[0] - arg2[0]) / (f32)arg3;
    stepY = (arg1[1] - arg2[1]) / (f32)arg3;
    stepZ = (arg1[2] - arg2[2]) / (f32)arg3;
    if (stepX < 0.0f) stepX *= -1.0f;
    if (stepY < 0.0f) stepY *= -1.0f;
    if (stepZ < 0.0f) stepZ *= -1.0f;
    arg0[0] = Math_StepToF(arg0[0], arg1[0], stepX, stepX);
    arg0[1] = Math_StepToF(arg0[1], arg1[1], stepY, stepY);
    arg0[2] = Math_StepToF(arg0[2], arg1[2], stepZ, stepZ);
}
/* mkdraft:func_82906A50 end */

/* mkdraft:func_82906B6C begin */
extern f32 Math_StepToF(f32, f32, f32, f32);

void func_82906B6C(f32 *arg0, f32 *arg1, f32 *arg2, s16 arg3) {
    f32 stepX;
    f32 stepY;
    f32 stepZ;
    f32 stepW;

    stepX = (arg1[0] - arg2[0]) / (f32)arg3;
    stepY = (arg1[1] - arg2[1]) / (f32)arg3;
    stepZ = (arg1[2] - arg2[2]) / (f32)arg3;
    stepW = (arg1[3] - arg2[3]) / (f32)arg3;
    if (stepX < 0.0f) stepX *= -1.0f;
    if (stepY < 0.0f) stepY *= -1.0f;
    if (stepZ < 0.0f) stepZ *= -1.0f;
    if (stepW < 0.0f) stepW *= -1.0f;
    arg0[0] = Math_StepToF(arg0[0], arg1[0], stepX, stepX);
    arg0[1] = Math_StepToF(arg0[1], arg1[1], stepY, stepY);
    arg0[2] = Math_StepToF(arg0[2], arg1[2], stepZ, stepZ);
    arg0[3] = Math_StepToF(arg0[3], arg1[3], stepW, stepW);
}
/* mkdraft:func_82906B6C end */

extern f32 Math_StepToF(f32, f32, f32, f32);
extern void func_82906A50(f32 *, f32 *, f32 *, s16);
extern void func_82906B6C(f32 *, f32 *, f32 *, s16);
extern f32 D_82912370;
extern f32 D_8291237C;
extern f32 D_82912388;
extern f32 D_82912394;
extern f32 D_829123A4;
extern f32 D_829123B4;
extern f32 D_829123C0;
extern f32 D_829123CC;
extern f32 D_829123D8;
extern f32 D_829123E8;
extern f32 D_829123F8;
extern f32 D_82912408;
extern f32 D_82912418;
extern f32 D_82912424;
extern f32 D_82912430;
extern f32 D_8291243C;
extern f32 D_8291244C;
extern f32 D_8291245C;
extern f32 D_8291246C;
extern f32 D_82919D4C;
extern f32 D_82919D50;
extern f32 D_82919D54;
extern f32 D_82919D64;
extern f32 D_82919D70;
extern f32 D_82919D80;
extern f32 D_82919D8C;
extern f32 D_82919D9C;
void func_82906CC8(s32 arg0) {
    if (arg0 == 0) {
        func_82906A10(&D_82919D64, &D_82912370);
    }
    if ((arg0 >= 4) && (arg0 < 0xC)) {
        func_82906A50(&D_82919D64, &D_8291237C, &D_82912370, 7);
    }
    if ((arg0 >= 0xC) && (arg0 < 0x28)) {
        func_82906A50(&D_82919D64, &D_82912388, &D_8291237C, 0x1B);
    }
}

extern void func_82906A2C(f32 *arg0, const f32 *arg1);
void func_82906D64(s32 arg0) {
    if (arg0 == 0) {
        func_82906A2C(&D_82919D54, &D_82912394);
    }
    if ((arg0 > 0) && (arg0 < 4)) {
        func_82906B6C(&D_82919D54, &D_829123A4, &D_82912394, 2);
    }
    if ((arg0 >= 0x27) && (arg0 < 0x2D)) {
        func_82906B6C(&D_82919D54, &D_82912394, &D_829123A4, 5);
    }
}

void func_82906DFC(s32 arg0) {
    D_82919D4C = Math_StepToF(D_82919D4C, 18.0f, 0.5f, 0.5f);
    if (arg0 == 0) {
        func_82906A10(&D_82919D80, &D_829123B4);
    }
    if ((arg0 >= 4) && (arg0 < 0xC)) {
        func_82906A50(&D_82919D80, &D_829123C0, &D_829123B4, 7);
    }
    if ((arg0 >= 0xC) && (arg0 < 0x23)) {
        func_82906A50(&D_82919D80, &D_829123CC, &D_829123C0, 0x16);
    }
}

extern void func_82906A2C(f32 *arg0, const f32 *arg1);
void func_82906EC4(s32 arg0) {
    if (arg0 == 0) {
        func_82906A2C(&D_82919D70, &D_829123D8);
    }
    if ((arg0 > 0) && (arg0 < 4)) {
        func_82906B6C(&D_82919D70, &D_829123E8, &D_829123D8, 2);
    }
    if ((arg0 >= 4) && (arg0 < 0xC)) {
        func_82906B6C(&D_82919D70, &D_829123F8, &D_829123E8, 7);
    }
    if ((arg0 >= 0xC) && (arg0 < 0x23)) {
        func_82906B6C(&D_82919D70, &D_82912408, &D_829123F8, 0x16);
    }
}

void func_82906F8C(s32 arg0) {
    D_82919D50 = Math_StepToF(D_82919D50, 36.0f, 1.0f, 1.0f);
    if (arg0 == 0) {
        func_82906A10(&D_82919D9C, &D_82912418);
    }
    if ((arg0 >= 4) && (arg0 < 0xC)) {
        func_82906A50(&D_82919D9C, &D_82912424, &D_82912418, 7);
    }
    if ((arg0 >= 0xC) && (arg0 < 0x1E)) {
        func_82906A50(&D_82919D9C, &D_82912430, &D_82912424, 0x11);
    }
}

extern void func_82906A2C(f32 *arg0, const f32 *arg1);
void func_82907054(s32 arg0) {
    if (arg0 == 0) {
        func_82906A2C(&D_82919D8C, &D_8291243C);
    }
    if ((arg0 > 0) && (arg0 < 4)) {
        func_82906B6C(&D_82919D8C, &D_8291244C, &D_8291243C, 2);
    }
    if ((arg0 >= 4) && (arg0 < 0xC)) {
        func_82906B6C(&D_82919D8C, &D_8291245C, &D_8291244C, 7);
    }
    if ((arg0 >= 0xC) && (arg0 < 0x1E)) {
        func_82906B6C(&D_82919D8C, &D_8291246C, &D_8291245C, 0x11);
    }
}

extern void func_82906B6C(f32 *, f32 *, f32 *, s16);
extern f32 D_8291247C;
extern u8 D_8291248C;
extern f32 D_82919DA8;
void func_8290711C(s32 arg0) {
    if (arg0 == 0) {
        func_82906A2C(&D_82919DA8, &D_8291247C);
    }
    if ((arg0 >= 0xC) && (arg0 < 0x27)) {
        func_82906B6C(&D_82919DA8, &D_8291248C, &D_8291247C, 0x1A);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_343510/func_82907188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_343510/func_82907274.s")
#endif
