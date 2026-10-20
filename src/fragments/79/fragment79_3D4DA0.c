#include "global.h"


#ifdef VERSION_US
typedef struct S1_unk_D_843C2C00_064 S1_unk_D_843C2C00_064;
typedef struct S1_DoubleTextureTrail S1_DoubleTextureTrail;
typedef struct S1_unk_D_843C2C00_024 S1_unk_D_843C2C00_024;
typedef struct S1_unk_D_84389CE0 S1_unk_D_84389CE0;
typedef struct S1_unk_D_843C2C00_0B0 S1_unk_D_843C2C00_0B0;
typedef struct S1_Vec3f S1_Vec3f;
struct S1_unk_D_843C2C00_064 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
};
typedef struct {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} S1_Color_RGBA8;
struct S1_unk_D_843C2C00_024 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
};
struct S1_unk_D_84389CE0 {
    /* 0x00 */ S1_Color_RGBA8 unk_00;
    /* 0x04 */ u8 unk_04;
};
struct S1_Vec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
};
struct S1_unk_D_843C2C00_0B0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ S1_Vec3f unk_10;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
};
struct S1_DoubleTextureTrail {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ f32 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ s32 unk_01C;
    /* 0x020 */ s32 unk_020;
    /* 0x024 */ S1_unk_D_843C2C00_024 unk_024;
    /* 0x044 */ S1_unk_D_843C2C00_024 unk_044;
    /* 0x064 */ S1_unk_D_843C2C00_064 unk_064;
    /* 0x070 */ S1_unk_D_843C2C00_064 unk_070;
    /* 0x07C */ S1_unk_D_84389CE0 unk_07C;
    /* 0x081 */ S1_unk_D_84389CE0 unk_081;
    /* 0x086 */ S1_Color_RGBA8 unk_086;
    /* 0x08C */ f32 unk_08C;
    /* 0x090 */ f32 unk_090;
    /* 0x094 */ s16 unk_094;
    /* 0x096 */ char unk096[0x1A];
    /* 0x0B0 */ S1_unk_D_843C2C00_0B0 unk_0B0[10];
};
// Four 0x41C-byte streams, each retaining fifteen current/previous samples.
typedef struct { f32 x, y, z; } AnchorTrailVec3f;
typedef struct {
    u8 alpha;
    f32 scale;
    f32 angle;
    AnchorTrailVec3f position;
    AnchorTrailVec3f velocity;
    f32 previous_scale;
    f32 previous_angle;
    AnchorTrailVec3f previous_position;
    AnchorTrailVec3f previous_velocity;
} AnchorTrailSample;
typedef struct {
    s16 active, age, lifetime, direction;
    u8 color[3];
    f32 scale_limit;
    f32 angle_step;
    Vtx *vertices;
    u8 *particle;
    AnchorTrailSample samples[15];
    f32 marker_scale;
} AnchorTrailStream;
// GS adds a live scalar at 0x0C before the pool node's position.
//@src/fragments/79/fragment79_3C60B0.c
typedef struct {
    u8 alpha;
    f32 scale;
    f32 angle;
    f32 unk0C;
    AnchorTrailVec3f position;
    AnchorTrailVec3f velocity;
    AnchorTrailVec3f acceleration;
    f32 previous_scale;
    AnchorTrailVec3f previous_position;
    AnchorTrailVec3f previous_velocity;
} TrailPoolSample;
typedef struct {
    s16 active, age, unk004, unk006, unk008;
    u8 color[3];
    f32 unk010, unk014, unk018;
    u8 unk01C[4];
    Vtx *vertices;
    AnchorTrailVec3f unk024;
    u8 unk030[16];
    TrailPoolSample samples[10];
} TrailPoolRecord;
extern u8 *D_84187BD0;
extern TrailPoolRecord D_8419F070[];
extern s16 D_841A4DB4, D_841A4DB2;
extern s32 BattleAnim_GetSecondaryOwnerSpecies(void);
extern u8 *func_84109B88(AnchorTrailVec3f, u8);
extern void func_84109BA4(u8 *, AnchorTrailVec3f);

void OwnerAnchoredFourStream_Init(void) {
    s32 i;
    s32 j;
    AnchorTrailStream* var_v0 = (AnchorTrailStream *)D_84187BD0;
    AnchorTrailSample* var_a0;

    for (i = 0; i < 4; i++, var_v0++) {
        var_v0->active = 0;
        var_v0->age = 0;
        var_v0->lifetime = 0;
        var_v0->marker_scale = 0.16f;

        var_a0 = &var_v0->samples[0];
        for (j = 0; j < 15; j++, var_a0++) {
            var_a0->alpha = 0;
            var_a0->scale = 1.0f;
            var_a0->angle = 0.0f;
            var_a0->position.x = 0.0f;
            var_a0->position.y = 0.0f;
            var_a0->position.z = 0.0f;
            var_a0->velocity.x = 0.0f;
            var_a0->velocity.y = 0.0f;
            var_a0->velocity.z = 0.0f;
        }
    }
}

void OwnerAnchoredFourStream_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9,
                   f32 argA, f32 argB, f32 argC, s16 argD) {
    s32 i;
    s32 j;
    AnchorTrailStream* var_v1;
    AnchorTrailSample* var_s0;
    AnchorTrailVec3f sp64;
    AnchorTrailVec3f sp58;

    sp64.x = arg0;
    sp64.y = arg1;
    sp64.z = arg2;
    sp58.x = arg3;
    sp58.y = arg4;
    sp58.z = arg5;

    var_v1 = (AnchorTrailStream *)D_84187BD0;
    for (i = 0; i < 4; i++, var_v1++) {
        if (var_v1->active == 0) {
            var_v1->active = 1;
            var_v1->age = 0;
            var_v1->lifetime = argD;
            var_v1->color[0] = arg6;
            var_v1->color[1] = arg7;
            var_v1->color[2] = arg8;
            var_v1->angle_step = argA;

            if (BattleAnim_GetSecondaryOwnerSpecies() == 0xD) {
                var_v1->marker_scale = 0.08f;
                var_v1->scale_limit = argC * 0.5f;
            } else {
                var_v1->marker_scale = 0.16f;
                var_v1->scale_limit = argC;
            }

            var_v1->particle = func_84109B88(sp64, 2);
            if (arg3 < 0.0) {
                var_v1->direction = -1;
            } else {
                var_v1->direction = 1;
            }

            var_s0 = &var_v1->samples[0];
            for (j = 0; j < 15; j++, var_s0++) {
                var_s0->alpha = (arg9 * (0xE - j)) / 15;
                var_s0->scale = argB;
                var_s0->angle = ((guRandom() % 120) * 6.2831855f) / 120.0;
                var_s0->position = sp64;
                var_s0->velocity = sp58;
            }
            break;
        }
    }
}

void OwnerAnchoredFourStream_Update(f32 arg0, f32 *arg1, f32 arg2) {
    UNUSED f32 pad[16]; // FAKE: inherited unused matrix-sized storage.
    f32 sp30[4][4];
    UNUSED s32 pad2[2]; // FAKE: inherited unused local; cleanup remains unresolved.
    guRotateF(sp30, (arg0 * 360.0) / 6.2831854820251465, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

void OwnerAnchoredFourStream_UpdateNodeChain(u8 *data) {
    AnchorTrailStream *arg0 = (AnchorTrailStream *)data;
    s32 i;
    AnchorTrailSample* var_s0 = &arg0->samples[0];

    for (i = 0; i < 15; i++, var_s0++) {
        if (i == 0) {
            var_s0->previous_scale = var_s0->scale;
            var_s0->previous_angle = var_s0->angle;

            var_s0->previous_position = var_s0->position;
            var_s0->previous_velocity = var_s0->velocity;

            var_s0->position.x += var_s0->velocity.x;
            var_s0->position.y += var_s0->velocity.y;
            var_s0->position.z += var_s0->velocity.z;

            var_s0->angle += arg0->angle_step;
            if (arg0->direction > 0) {
                var_s0->velocity.x += 0.4;
                if (var_s0->velocity.x > 20.0) {
                    var_s0->velocity.x = 20.0f;
                }
            } else {
                var_s0->velocity.x -= 0.4;
                if (var_s0->velocity.x < -20.0) {
                    var_s0->velocity.x = -20.0f;
                }
            }

            func_84109BA4(arg0->particle, var_s0->position);

            var_s0->scale += 2.0;
            if (arg0->scale_limit < var_s0->scale) {
                var_s0->scale = arg0->scale_limit;
            }
        } else {
            var_s0->previous_scale = var_s0->scale;
            var_s0->previous_angle = var_s0->angle;

            var_s0->previous_position = var_s0->position;
            var_s0->previous_velocity = var_s0->velocity;

            var_s0->position = var_s0[-1].previous_position;
            var_s0->angle = var_s0[-1].previous_angle;
            var_s0->velocity = var_s0[-1].previous_velocity;
            var_s0->scale = var_s0[-1].previous_scale;
        }
    }
}

s32 func_84165C2C(void) {
    u8 *ptr = D_84187BD0;
    s32 i = 0;
    do {
        if (*(s16 *)ptr == 1) {
            *(s16 *)(ptr + 2) = *(s16 *)(ptr + 2) + 1;
            if (*(s16 *)(ptr + 4) < *(s16 *)(ptr + 2)) {
                *(s16 *)ptr = 0;
            } else {
                OwnerAnchoredFourStream_UpdateNodeChain(ptr);
            }
        }
        i++;
        ptr += 0x41C;
    } while (i != 4);
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84165CC0.s")

// Unlike Stadium 1's fifty-record pool, GS initializes twenty-six records.
void TrailEffectPool_Init(void) {
    TrailPoolRecord* var_v0 = &D_8419F070[0];
    TrailPoolSample* var_a0;
    s32 i;
    s32 j;

    D_841A4DB4 = 0;
    D_841A4DB2 = 0;

    for (i = 0; i < 26; i++, var_v0++) {
        var_v0->active = 0;
        var_v0->unk004 = 0;
        var_v0->unk006 = 0;

        var_a0 = &var_v0->samples[0];

        for (j = 0; j < 10; j++, var_a0++) {
            var_a0->alpha = 0;
            var_a0->scale = 1.0f;
            var_a0->angle = 0.0f;

            var_a0->position.x = 0.0f;
            var_a0->position.y = 0.0f;
            var_a0->position.z = 0.0f;
            var_a0->velocity.x = 0.0f;
            var_a0->velocity.y = 0.0f;
            var_a0->velocity.z = 0.0f;
        }
    }
}

extern f32 func_84109544(void);
void TrailEffectPool_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9,
                   f32 argA, f32 argB, f32 argC, s16 argD) {
    TrailPoolRecord* var_v1;
    TrailPoolSample* var_s0;
    s32 i;
    s32 j;
    AnchorTrailVec3f sp7C;
    AnchorTrailVec3f sp70;
    AnchorTrailVec3f sp64;
    f32 temp_fv1;

    if (D_841A4DB4 == 2) {
        return;
    }

    temp_fv1 = func_84109544() * 0.5f;

    sp7C.x = arg0;
    sp7C.y = (80.0f * temp_fv1) + arg1;
    sp7C.z = arg2;

    sp70.x = arg3;
    sp70.y = arg4;
    sp70.z = arg5;

    sp64.x = 0.0f;
    sp64.y = temp_fv1 * -2.0;
    sp64.z = 0.0f;

    var_v1 = &D_8419F070[0];

    for (i = 0; i < 26; i++, var_v1++) {
        if (var_v1->active == 0) {
            var_v1->active = 1;
            var_v1->age = 0;
            var_v1->unk004 = 0;
            var_v1->unk006 = argD;
            var_v1->color[0] = arg6;
            var_v1->color[1] = arg7;
            var_v1->color[2] = arg8;
            var_v1->unk024 = sp7C;
            var_v1->unk018 = argC;
            var_v1->unk010 = argA;
            var_v1->unk014 = temp_fv1;

            if (arg0 > 0.0) {
                var_v1->unk008 = -1;
            } else {
                var_v1->unk008 = 1;
            }

            var_s0 = var_v1->samples;
            for (j = 0; j < 10; j++, var_s0++) {
                var_s0->alpha = (arg9 * (9 - j)) / 10;
                var_s0->scale = argB;
                var_s0->angle = ((guRandom() % 120) * 6.2831855f) / 120.0;
                var_s0->position = sp7C;
                var_s0->velocity = sp70;
                var_s0->acceleration = sp64;
            }
            break;
        }
    }
}

void func_8416654C(f32 arg0, f32 *arg1, f32 arg2) {
    f32 sp30[4][4];
    f32 angle = (arg0 * 360.0) / 6.2831854820251465;
    guRotateRPYF(sp30, 90.0f, angle, angle);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_841665D4.s")

extern u32 func_841094EC(void);
extern s16 D_841A4DB0;
extern void func_841665D4(TrailPoolRecord *);
s32 TrailEffectPool_IsComplete(void) {
    s32 i;
    TrailPoolRecord *stream;
    s32 state_flag;

    D_841A4DB2++;
    // Setup routines initialize this flag to 0 or 1; its getter returns u32.
    //@src/fragments/79/fragment79_377F80.c
    state_flag = func_841094EC();
    if (state_flag == 1 && D_841A4DB4 == 0) {
        D_841A4DB0 = D_841A4DB2 + 70;
        D_841A4DB4 = 1;
    } else if (D_841A4DB4 == 1) {
        if (D_841A4DB0 - 50 < D_841A4DB2) {
            D_841A4DB4 = 2;
        }
    } else if (D_841A4DB4 == 2) {
        if (D_841A4DB0 < D_841A4DB2) {
            return -1;
        }
    }
    stream = &D_8419F070[0];
    for (i = 0; i < 26; i++, stream++) {
        if (stream->active == 1) {
            stream->unk004++;
            if (stream->age == 1 && stream->unk006 < stream->unk004) {
                stream->active = 0;
            } else {
                func_841665D4(stream);
            }
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84166A64.s")

extern u8 *D_84187D40;
void DoubleTextureTrail_InitPool(void) {
    s32 i;
    s32 j;
    S1_DoubleTextureTrail* var_v0 = (S1_DoubleTextureTrail *)D_84187D40;
    S1_unk_D_843C2C00_0B0* var_a0;

    for (i = 0; i < 4; i++, var_v0++) {
        var_v0->unk_000 = 0;
        var_v0->unk_002 = 0;
        var_v0->unk_004 = 0;

        var_a0 = &var_v0->unk_0B0[0];
        for (j = 0; j < 10; j++, var_a0++) {
            var_a0->unk_00 = 0;
            var_a0->unk_04 = 0;
            var_a0->unk_08 = 1.0f;
            var_a0->unk_0C = 0.0f;
            var_a0->unk_10.x = 0.0f;
            var_a0->unk_10.y = 0.0f;
            var_a0->unk_10.z = 0.0f;
            var_a0->unk_1C = 0.0f;
            var_a0->unk_20 = 0.0f;
            var_a0->unk_24 = 0.0f;
        }
    }
}

void DoubleTextureTrail_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9,
                   f32 argA, s16 argB, s32 argC, s32 argD, s16 argE, s16 argF, s16 arg10, s16 arg11, s16 arg12,
                   s16 arg13, s16 arg14, s16 arg15, S1_unk_D_843C2C00_024* arg16, S1_unk_D_843C2C00_024* arg17, u8 arg18,
                   u8 arg19, u8 arg1A, u8 arg1B, u8 arg1C, u8 arg1D, u8 arg1E, u8 arg1F, u8 arg20, u8 arg21, u8 arg22,
                   u8 arg23, u8 arg24) {
    S1_DoubleTextureTrail* var_v0;
    S1_unk_D_843C2C00_0B0* var_a0;
    s32 i;
    s32 j;
    S1_Vec3f sp3C;
    S1_Vec3f sp30;

    sp3C.x = arg0;
    sp3C.y = arg1;
    sp3C.z = arg2;

    sp30.x = arg3;
    sp30.y = arg4;
    sp30.z = arg5;

    var_v0 = (S1_DoubleTextureTrail *)D_84187D40;
    for (i = 0; i < 4; i++, var_v0++) {
        if (var_v0->unk_000 == 0) {
            var_v0->unk_000 = 1;
            var_v0->unk_002 = 0;
            var_v0->unk_004 = argB;
            var_v0->unk_006 = 0;
            var_v0->unk_008 = argA;
            var_v0->unk_010 = arg7;
            var_v0->unk_014 = arg8;
            var_v0->unk_00C = arg6;
            var_v0->unk_01C = argC;
            var_v0->unk_020 = argD;

            var_v0->unk_064.unk_00 = 0;
            var_v0->unk_064.unk_02 = 0;
            var_v0->unk_070.unk_00 = 0;
            var_v0->unk_070.unk_02 = 0;

            var_v0->unk_064.unk_04 = argE;
            var_v0->unk_064.unk_06 = argF;
            var_v0->unk_070.unk_04 = arg12;
            var_v0->unk_070.unk_06 = arg13;

            var_v0->unk_064.unk_08 = arg10;
            var_v0->unk_064.unk_0A = arg11;
            var_v0->unk_070.unk_08 = arg14;
            var_v0->unk_070.unk_0A = arg15;

            var_v0->unk_024 = *arg16;
            var_v0->unk_044 = *arg17;

            var_v0->unk_07C.unk_00.r = arg18;
            var_v0->unk_07C.unk_00.g = arg19;
            var_v0->unk_07C.unk_00.b = arg1A;
            var_v0->unk_07C.unk_00.a = arg1B;

            var_v0->unk_07C.unk_04 = arg1C;

            var_v0->unk_081.unk_00.r = arg1D;
            var_v0->unk_081.unk_00.g = arg1E;
            var_v0->unk_081.unk_00.b = arg1F;
            var_v0->unk_081.unk_00.a = arg20;

            var_v0->unk_086.r = arg21;
            var_v0->unk_086.g = arg22;
            var_v0->unk_086.b = arg23;
            var_v0->unk_086.a = arg24;

            var_v0->unk_08C = 1.0f;
            var_v0->unk_090 = 1.0f;
            var_v0->unk_094 = 65;

            var_a0 = &var_v0->unk_0B0[0];
            for (j = 0; j < 10; j++, var_a0++) {
                var_a0->unk_00 = j;
                var_a0->unk_04 = 0xFF;
                var_a0->unk_08 = arg9;
                var_a0->unk_0C = 0.0f;
                var_a0->unk_10 = sp3C;
                var_a0->unk_1C = sp30.x * arg8;
                var_a0->unk_20 = sp30.y * arg8;
                var_a0->unk_24 = sp30.z * arg8;
            }
            break;
        }
    }
}

void DoubleTextureTrail_RotateVertexOffset(f32 arg0, f32 *arg1, f32 arg2) {
    UNUSED f32 pad[16]; // FAKE: inherited unused matrix-sized storage.
    f32 sp30[4][4];
    UNUSED s32 pad2[2]; // FAKE: inherited unused local; cleanup remains unresolved.
    guRotateF(sp30, (360.0f * arg0) / 6.2831855f, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_841674C0.s")

extern void func_841674C0(u8 *);
s32 func_841677C4(void) {
    u8 *ptr = D_84187D40;
    s32 i = 0;
    if (*(s16 *)(ptr + 6) == 2 && *(s16 *)(ptr + 0x94) < *(s16 *)(ptr + 2)) {
        return -1;
    }
    do {
        if (*(s16 *)ptr == 1) {
            *(s16 *)(ptr + 2) = *(s16 *)(ptr + 2) + 1;
            func_841674C0(ptr);
        }
        i++;
        ptr += 0x240;
    } while (i != 4);
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84167864.s")

extern u8* D_8418CA20[256];
Gfx* DoubleTextureTrail_LoadTextures(Gfx* arg0, S1_DoubleTextureTrail* arg1) {
    S1_unk_D_843C2C00_064* ptr;

    ptr = &arg1->unk_064;
    gDPLoadTextureTile_4b(arg0++, D_8418CA20[arg1->unk_01C], G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0,
                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, ptr->unk_08, ptr->unk_0A);
    gDPSetTileSize(arg0++, G_TX_RENDERTILE, ptr->unk_00, ptr->unk_02, (ptr->unk_00 + 31) << 2, (ptr->unk_02 + 31) << 2);

    ptr = &arg1->unk_070;
    gDPLoadMultiTile_4b(arg0++, D_8418CA20[arg1->unk_020], 0x0100, 1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, ptr->unk_08, ptr->unk_0A);
    gDPSetTileSize(arg0++, 1, ptr->unk_00, ptr->unk_02, (ptr->unk_00 + 31) << 2, (ptr->unk_02 + 31) << 2);

    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84168000.s")
#endif
