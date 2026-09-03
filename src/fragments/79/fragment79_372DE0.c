#include "global.h"


#ifdef VERSION_US
typedef struct S1_arg1_func_80019420 {
    /* 0x00 */ s8 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ void* unk_04;
} S1_arg1_func_80019420;
extern u8* D_8418CA20[256];
typedef float S1_MtxF_t[4][4];
typedef union {
    S1_MtxF_t mf;
    struct {
        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
    };
} S1_MtxF;
extern Gfx* D_800D0510;
extern f32 D_80087E50[];
extern f32 D_80088E50[0x1000];
typedef struct S1_Vec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} S1_Vec3f;
typedef struct S1_Vec3s {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} S1_Vec3s;
void BattleAnim_RegisterAssetTable(S1_arg1_func_80019420* arg0) {
    if (arg0 != NULL) {
        do {
            if (arg0->unk_02 != 0) {
                D_8418CA20[arg0->unk_02] = arg0->unk_04;
                arg0++;
            }
        } while (arg0->unk_00 != 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_372DE0/func_8410358C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_372DE0/func_841035DC.s")

extern s16 D_8418D240[];
extern u8 D_8418D260[];
extern s32 func_841035DC(s16);
extern void func_8003F84C(s32, s16 *, u8 *);
extern void func_8003F874(s32);
void func_84103640(s32 arg0, s16 arg1) {
    func_841035DC(arg1);
    func_8003F84C(arg0, D_8418D240, D_8418D260);
    func_8003F874(arg0);
}

void func_84103694(s32 arg0, s16 arg1) {
    func_841035DC(arg1);
    func_8003F84C(arg0, D_8418D240, D_8418D260);
    func_8003F874(arg0);
}

void func_841036E8(s32 arg0, s16 arg1) {
    func_841035DC(arg1);
    func_8003F84C(arg0, D_8418D240, D_8418D260);
    func_8003F874(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_372DE0/func_8410373C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_372DE0/func_841037A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_372DE0/func_8410383C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_372DE0/func_841038F4.s")

extern void func_8410383C(S1_MtxF *, s16, s16, s16, f32);
extern void func_841037A0(S1_MtxF *);
void func_841039AC(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    S1_MtxF mat;

    func_8410383C(&mat, arg0, arg1, arg2, arg3);
    func_841037A0(&mat);
}

extern void func_841038F4(S1_MtxF *, s16, s16, s16, f32);
extern void func_841037A0(S1_MtxF *);
void func_841039F4(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    S1_MtxF mat;

    func_841038F4(&mat, arg0, arg1, arg2, arg3);
    func_841037A0(&mat);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_372DE0/func_84103A3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_372DE0/func_84103BCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_372DE0/func_84103D2C.s")

void ParticleGfx_BuildBillboardMatrix(S1_MtxF* arg0, S1_MtxF* arg1, S1_Vec3f arg2, f32 arg3) {
    arg0->mf[0][0] = arg1->mf[0][0] * arg3;
    arg0->mf[0][1] = arg1->mf[1][0] * arg3;
    arg0->mf[0][2] = arg1->mf[2][0] * arg3;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = arg1->mf[0][1] * arg3;
    arg0->mf[1][1] = arg1->mf[1][1] * arg3;
    arg0->mf[1][2] = arg1->mf[2][1] * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2] * arg3;
    arg0->mf[2][1] = arg1->mf[1][2] * arg3;
    arg0->mf[2][2] = arg1->mf[2][2] * arg3;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg2.x;
    arg0->mf[3][1] = arg2.y;
    arg0->mf[3][2] = arg2.z;
    arg0->mf[3][3] = 1.0f;
}

void ParticleGfx_BuildBillboardMatrixYScaled(S1_MtxF* arg0, S1_MtxF* arg1, S1_Vec3f arg2, f32 arg3) {
    arg0->mf[0][0] = arg1->mf[0][0];
    arg0->mf[0][1] = arg1->mf[1][0];
    arg0->mf[0][2] = arg1->mf[2][0];
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = arg1->mf[0][1] * arg3;
    arg0->mf[1][1] = arg1->mf[1][1] * arg3;
    arg0->mf[1][2] = arg1->mf[2][1] * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2];
    arg0->mf[2][1] = arg1->mf[1][2];
    arg0->mf[2][2] = arg1->mf[2][2];
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg2.x;
    arg0->mf[3][1] = arg2.y;
    arg0->mf[3][2] = arg2.z;
    arg0->mf[3][3] = 1.0f;
}

void ParticleGfx_BuildBillboardRotatedMatrix(S1_MtxF* arg0, S1_MtxF* arg1, S1_Vec3f arg2, f32 arg3, s16 arg4) {
    f32 temp_fv0 = D_80087E50[(u16) arg4 >> 4];
    f32 temp_fv1 = D_80088E50[(u16) arg4 >> 4];

    arg0->mf[0][0] = ((arg1->mf[0][0] * temp_fv1) + (arg1->mf[0][1] * temp_fv0)) * arg3;
    arg0->mf[0][1] = ((arg1->mf[1][0] * temp_fv1) + (arg1->mf[1][1] * temp_fv0)) * arg3;
    arg0->mf[0][2] = ((arg1->mf[2][0] * temp_fv1) + (arg1->mf[2][1] * temp_fv0)) * arg3;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((arg1->mf[0][0] * -temp_fv0) + (arg1->mf[0][1] * temp_fv1)) * arg3;
    arg0->mf[1][1] = ((arg1->mf[1][0] * -temp_fv0) + (arg1->mf[1][1] * temp_fv1)) * arg3;
    arg0->mf[1][2] = ((arg1->mf[2][0] * -temp_fv0) + (arg1->mf[2][1] * temp_fv1)) * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2] * arg3;
    arg0->mf[2][1] = arg1->mf[1][2] * arg3;
    arg0->mf[2][2] = arg1->mf[2][2] * arg3;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg2.x;
    arg0->mf[3][1] = arg2.y;
    arg0->mf[3][2] = arg2.z;
    arg0->mf[3][3] = 1.0f;
}

#define COSS(x) D_80088E50[(u16) (x) >> 4]
#define SINS(x) D_80087E50[(u16) (x) >> 4]
extern f32 D_80087E50[];
extern f32 D_80088E50[0x1000];
void ParticleGfx_BuildBillboardRotatedMatrixYScaled(S1_MtxF* arg0, S1_MtxF* arg1, S1_Vec3f arg2, f32 arg3, s16 arg4) {
    f32 temp_fv0 = SINS(arg4);
    f32 temp_fv1 = COSS(arg4);

    arg0->mf[0][0] = (arg1->mf[0][0] * temp_fv1) + (arg1->mf[0][1] * temp_fv0);
    arg0->mf[0][1] = (arg1->mf[1][0] * temp_fv1) + (arg1->mf[1][1] * temp_fv0);
    arg0->mf[0][2] = (arg1->mf[2][0] * temp_fv1) + (arg1->mf[2][1] * temp_fv0);
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((arg1->mf[0][0] * -temp_fv0) + (arg1->mf[0][1] * temp_fv1)) * arg3;
    arg0->mf[1][1] = ((arg1->mf[1][0] * -temp_fv0) + (arg1->mf[1][1] * temp_fv1)) * arg3;
    arg0->mf[1][2] = ((arg1->mf[2][0] * -temp_fv0) + (arg1->mf[2][1] * temp_fv1)) * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2];
    arg0->mf[2][1] = arg1->mf[1][2];
    arg0->mf[2][2] = arg1->mf[2][2];
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg2.x;
    arg0->mf[3][1] = arg2.y;
    arg0->mf[3][2] = arg2.z;
    arg0->mf[3][3] = 1.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_372DE0/func_84104270.s")

extern void func_84103A3C(S1_MtxF *, S1_Vec3f, S1_Vec3s, f32);
extern void func_841037A0(S1_MtxF *);
void func_841043AC(S1_Vec3f arg0, S1_Vec3s arg1, f32 arg2) {
    S1_MtxF sp28;

    func_84103A3C(&sp28, arg0, arg1, arg2);
    func_841037A0(&sp28);
}

extern void func_84103BCC(S1_MtxF *, S1_Vec3f, S1_Vec3s, f32);
extern void func_84103D2C(S1_MtxF *, S1_Vec3f, S1_Vec3s, f32, f32);
extern void func_841037A0(S1_MtxF *);
void func_84104428(S1_Vec3f arg0, S1_Vec3s arg1, f32 arg2) {
    S1_MtxF sp28;

    func_84103BCC(&sp28, arg0, arg1, arg2);
    func_841037A0(&sp28);
}

void ParticleGfx_PushTransformMatrixXYScaled(S1_Vec3f arg0, S1_Vec3s arg1, f32 arg2, f32 arg3) {
    S1_MtxF sp28;

    func_84103D2C(&sp28, arg0, arg1, arg2, arg3);
    func_841037A0(&sp28);
}

extern void ParticleGfx_BuildBillboardMatrix(S1_MtxF *, S1_MtxF *, S1_Vec3f, f32);
extern void func_841037A0(S1_MtxF *);
void func_84104528(S1_MtxF *arg0, S1_Vec3f arg1, f32 arg2) {
    S1_MtxF mat;

    ParticleGfx_BuildBillboardMatrix(&mat, (S1_MtxF *)((u8 *)arg0 + 0x64), arg1, arg2);
    func_841037A0(&mat);
}

extern void ParticleGfx_BuildBillboardRotatedMatrix(S1_MtxF *, S1_MtxF *, S1_Vec3f, f32, s16);
extern void func_841037A0(S1_MtxF *);
void func_84104590(S1_MtxF *arg0, S1_Vec3f arg1, f32 arg2, s16 arg3) {
    S1_MtxF mat;

    ParticleGfx_BuildBillboardRotatedMatrix(&mat, (S1_MtxF *)((u8 *)arg0 + 0x64), arg1, arg2, arg3);
    func_841037A0(&mat);
}

extern void ParticleGfx_BuildBillboardMatrixYScaled(S1_MtxF *, S1_MtxF *, S1_Vec3f, f32);
extern void func_841037A0(S1_MtxF *);
void func_84104600(S1_MtxF *arg0, S1_Vec3f arg1, f32 arg2) {
    S1_MtxF mat;

    ParticleGfx_BuildBillboardMatrixYScaled(&mat, (S1_MtxF *)((u8 *)arg0 + 0x64), arg1, arg2);
    func_841037A0(&mat);
}

extern void ParticleGfx_BuildBillboardRotatedMatrixYScaled(S1_MtxF *, S1_MtxF *, S1_Vec3f, f32, s16);
extern void func_841037A0(S1_MtxF *);
void func_84104668(S1_MtxF *arg0, S1_Vec3f arg1, f32 arg2, s16 arg3) {
    S1_MtxF mat;

    ParticleGfx_BuildBillboardRotatedMatrixYScaled(&mat, (S1_MtxF *)((u8 *)arg0 + 0x64), arg1, arg2, arg3);
    func_841037A0(&mat);
}
#endif
