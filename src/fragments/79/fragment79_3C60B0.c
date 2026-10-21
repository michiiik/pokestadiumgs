#include "global.h"


#ifdef VERSION_US
extern void func_84169B80(void);
extern void _bzero(void *, s32);
extern u8 D_8419F070[];
void func_84156820(void) {
    func_84169B80();
    _bzero(D_8419F070, 0x5C90);
}
void func_84156820_padding(void) {}
void func_84156820_padding2(void) {}
#endif

#ifdef VERSION_US
s32 func_84156860(void) {
    return -1;
}
#endif

#ifdef VERSION_US
s32 func_84156868(void) {
    return -1;
}
#endif

#ifdef VERSION_US
void func_84156870(void) {}
void func_84156870_padding(void) {}
#endif

#ifdef VERSION_US
void func_84156880(void) {
    func_841098C0();
}
#endif

#ifdef VERSION_US
void BattleAnim_EffectSecondaryOwnerAnchorPosition(f32 *position) {
    extern void func_84109780(s32);
    func_84109780((s32)position);
}
#endif

#ifdef VERSION_US
void BattleAnim_EffectTertiaryOwnerBonePosition(void) {
    func_841098C0();
}
#endif

#ifdef VERSION_US
void BattleAnim_EffectSecondaryOwnerBonePosition(s32 arg0) {
    extern void func_84109884(s32);
    func_84109884(arg0);
  }
#endif

#ifdef VERSION_US
f32 BattleAnim_EffectTertiaryOwnerModelScale(void) {
    extern f32 func_84109590(void);
    return func_84109590();
  }
#endif

#ifdef VERSION_US
f32 BattleAnim_EffectSecondaryOwnerModelScale(void) {
    extern f32 func_84109544(void);
    return func_84109544();
}
#endif

#ifdef VERSION_US
f32 func_84156940(void) {
    extern f32 func_841094F8(void);
    return func_841094F8();
  }
#endif

#ifdef VERSION_US
  void func_84156960(void) {
      func_8410971C();
  }
#endif

#ifdef VERSION_US
void func_84156980(s32 arg0) {
    extern void func_84109848(s32);
    func_84109848(arg0);
  }
#endif

#ifdef VERSION_US
f32 func_841569A0(void) {
    extern f32 func_841095DC(void);
    return func_841095DC();
  }
#endif

#ifdef VERSION_US
void func_841569C0(s32 arg0) {
    extern void func_84109B1C(s32);
    func_84109B1C(arg0);
  }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_841569E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84156AB4.s")
#endif

#ifdef VERSION_US
extern u8 D_841A4D08[];
extern void func_8007D454(void *, f32, f32, f32);
void BattleAnim_ResetSharedEffectMatrix(void) {
    func_8007D454(D_841A4D08, 0.0f, 0.0f, 0.0f);
}
#endif

#ifdef VERSION_US
extern void BattleAnim_InitializeTerrainGrid(s32, s16, s32);
void BattleAnim_StartEffect34TerrainGrid_Init(void) {
    u8 pad[8];
    f32 sp1C;

    BattleAnim_EffectSecondaryOwnerAnchorPosition(&sp1C);
    BattleAnim_ResetSharedEffectMatrix();
    if ((f64)sp1C < 0.0) {
        BattleAnim_InitializeTerrainGrid(1, 0, 0x4650);
        return;
    }
    BattleAnim_InitializeTerrainGrid(-1, 0, 0x4650);
}
#endif

#ifdef VERSION_US
extern void BattleAnim_UpdateTerrainGrid(void);
void func_84156C40(void) {
    BattleAnim_UpdateTerrainGrid();
}
#endif

#ifdef VERSION_US
extern s32 D_800D0510;
extern s32 func_8415ADE0();
void func_84156C60(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415ADE0(D_800D0510);
}
#endif

void func_84156CB4(void) {
}

#ifdef VERSION_US
s32 func_84156CBC(void) {
    return -1;
}
#endif

void func_84156CC4(void) {
}

#ifdef VERSION_US
extern void func_841569E0(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
extern void func_8415CC74(f32, f32, f32, f32, f32, f32, s16, u8, u8, u8, u8, u8, u8, u8, f32, f32, f32, s16);
extern void TrailEffectPool_Start(f32, f32, f32, f32, f32, f32, u8, u8, u8, u8, f32, f32, f32, s16);
extern s32 TrailEffectPool_IsComplete(void);
extern f32 D_8418C530;
extern f32 D_8418C534;
extern f32 D_8418C538;
extern f32 D_8418C53C;
extern f32 D_8418C540;
extern f32 D_8418C558;
extern f32 D_8418C55C;
extern f32 D_8418C560;
extern f32 D_8418C564;
extern f32 D_8418C568;
extern f32 D_8418C56C;
extern f32 D_8418C570;

void BattleAnim_StartEffect19Radial20_EmitVariantD(void) {
    f32 x;
    f32 y;
    f32 z;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 scale;
    s32 randomZ;
    s32 randomY;

    func_841569E0(&x, &y, &z, &vx, &vy, &vz);
    vx *= 8.0f;
    vy *= 4.0f;
    vz = 0.0f;
    vy += 6.0f;
    scale = BattleAnim_EffectSecondaryOwnerModelScale();
    randomY = guRandom();
    func_8415CC74(x, y, z, vx, (((randomY % 4) * D_8418C530) + vy) - D_8418C534, (vz - (((randomZ = guRandom()) % 5) * D_8418C538)) + D_8418C53C, 2, 100, 200, 255, 200, 0, 100, 200, D_8418C540, scale, 4.0f * scale, 60);
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D4A;
extern void BattleAnim_ResetSharedEffectMatrix(void);
extern void func_8415C530(void);
extern void BattleAnim_StartEffect19Radial20_EmitVariantD(void);
void func_84156E58(void) {
    D_841A4D4A = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_8415C530();
    BattleAnim_StartEffect19Radial20_EmitVariantD();
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D4A;
extern u16 D_841A4D4C;
extern u16 D_841A4D4E;
extern u16 D_841A4D52;
extern void BattleAnim_StartEffect19Radial20_EmitVariantD(void);
extern void BattleAnim_StartEffect7TexturedRibbonSheet_Emit(void);
extern void func_84157398(void);
extern void BattleAnim_StartEffect98Radial20_EmitVariantD(void);
extern s32 func_8415DAE4(void);
s32 func_84156E8C(void) {
    (*(s16 *)&D_841A4D4A) = (*(s16 *)&D_841A4D4A) + 1;
    if (*(s16 *)&D_841A4D4A >= 0xB5) {
        return -1;
    }
    if (*(s16 *)&D_841A4D4A < 0x78 && (*(s16 *)&D_841A4D4A % 7) == 0) {
        BattleAnim_StartEffect19Radial20_EmitVariantD();
    }
    return func_8415DAE4();
}
#endif

#ifdef VERSION_US
extern s32 func_8415DBBC();
void func_84156EFC(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415DBBC(D_800D0510);
}
#endif

#ifdef VERSION_US
extern void func_8415BBA0(f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_84156F50(void) {
    s32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;

    BattleAnim_ResetSharedEffectMatrix();
    func_84156980((s32)(u32)&sp34);
    sp30 = func_84156940();
    BattleAnim_ResetSharedEffectMatrix();
    func_8415BBA0(sp34, sp38, sp3C, *(s32 *)&sp30, 0x64, 0xC8, 0xFF, 0, 0x64, 0xC8);
}
#endif

#ifdef VERSION_US
extern void func_8415BD48(s32);
void func_84156FC8(void) {
    func_8415BD48(0);
}
#endif

#ifdef VERSION_US
extern s32 func_8415C2E0();
void func_84156FE8(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415C2E0(D_800D0510);
}
#endif

#ifdef VERSION_US
extern void func_8415BBA0(f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_8415703C(void) {
    s32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;

    BattleAnim_ResetSharedEffectMatrix();
    func_841569C0((s32)(u32)&sp34);
    sp30 = func_841569A0();
    BattleAnim_ResetSharedEffectMatrix();
    func_8415BBA0(sp34, sp38, sp3C, *(s32 *)&sp30, 0x64, 0xC8, 0xFF, 0, 0x64, 0xC8);
}
#endif

#ifdef VERSION_US
void func_841570B4(void) {
    func_8415BD48(1);
}
#endif

#ifdef VERSION_US
void func_841570D4(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415C2E0(D_800D0510);
}
#endif

#ifdef VERSION_US
extern f32 BattleAnim_EffectSecondaryOwnerModelScale(void);
extern void func_84156AB4(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
extern void func_84162798(f32, f32, f32, f32, f32, f32, u8, u8, u8, u8, f32, s16);
extern f32 D_8418C544;
void BattleAnim_StartEffect7TexturedRibbonSheet_Emit(void) {
    f32 jitterX;
    f32 jitterY;
    f32 jitterZ;
    f32 x;
    f32 y;
    f32 z;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 scale;
    s32 random;
    scale = BattleAnim_EffectSecondaryOwnerModelScale();
    func_84156AB4(&x, &y, &z, &vx, &vy, &vz);
    vx *= 20.0f;
    vy *= 20.0f;
    vz *= 20.0f;
    random = guRandom();
    jitterX = 30.0f - (random % 60);
    x += scale * jitterX;
    random = guRandom();
    jitterY = 30.0f - (random % 60);
    y += scale * jitterY;
    random = guRandom();
    jitterZ = 30.0f - (random % 60);
    z += scale * jitterZ;
    func_84162798(x, y, z, vx, vy, vz, 255, 255, 0, 60, D_8418C544, 30);
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D4C;
extern void func_84162660(void);
extern void BattleAnim_StartEffect7TexturedRibbonSheet_Emit(void);
void BattleAnim_StartEffect7TexturedRibbonSheet_Init(void) {
    D_841A4D4C = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_84162660();
    BattleAnim_StartEffect7TexturedRibbonSheet_Emit();
}
#endif

#ifdef VERSION_US
s32 BattleAnim_StartEffect7TexturedRibbonSheet_Update(void) {
    (*(s16 *)&D_841A4D4C) = (*(s16 *)&D_841A4D4C) + 1;
    if (*(s16 *)&D_841A4D4C >= 0x709) {
        return -1;
    }
    if (*(s16 *)&D_841A4D4C < 0x6EA && (*(s16 *)&D_841A4D4C % 3) == 0) {
        BattleAnim_StartEffect7TexturedRibbonSheet_Emit();
    }
    return func_84162C88();
}
#endif

#ifdef VERSION_US
extern s32 func_84162DE8();
void BattleAnim_StartEffect7TexturedRibbonSheet_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84162DE8(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157398.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D4E;
extern void func_84157398(void);
void BattleAnim_StartEffect33Radial20_Init(void) {
    D_841A4D4E = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_8415C530();
    func_84157398();
}
#endif

#ifdef VERSION_US
s32 BattleAnim_StartEffect33Radial20_Update(void) {
    (*(s16 *)&D_841A4D4E) = (*(s16 *)&D_841A4D4E) + 1;
    if (*(s16 *)&D_841A4D4E >= 0xB5) {
        return -1;
    }
    if (*(s16 *)&D_841A4D4E < 0x78 && (*(s16 *)&D_841A4D4E % 7) == 0) {
        func_84157398();
    }
    return func_8415DAE4();
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect33Radial20_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415DBBC(D_800D0510);
}
#endif

#ifdef VERSION_US
extern void func_8415BBA0(f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);
void BattleAnim_EndEffect32Radial20_Init(void) {
    s32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerBonePosition((s32)(u32)&sp34);
    sp30 = BattleAnim_EffectTertiaryOwnerModelScale();
    BattleAnim_ResetSharedEffectMatrix();
    func_8415BBA0(sp34, sp38, sp3C, *(s32 *)&sp30, 0xFF, 0xFF, 0xFF, 0x64, 0x96, 0x96);
}
#endif

#ifdef VERSION_US
void func_841576CC(void) {
    func_8415BD48(0);
}
#endif

#ifdef VERSION_US
void BattleAnim_EndEffect32Radial20_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415C2E0(D_800D0510);
}
#endif

#ifdef VERSION_US
extern void func_8415BBA0(f32, f32, s32, s32, s32, s32, s32, s32, s32, s32);
void BattleAnim_EndEffect33Radial20_Init(void) {
    s32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerBonePosition((s32)(u32)&sp34);
    sp30 = BattleAnim_EffectTertiaryOwnerModelScale();
    BattleAnim_ResetSharedEffectMatrix();
    func_8415BBA0(sp34, sp38, sp3C, *(s32 *)&sp30, 0xFF, 0xFF, 0x64, 0x96, 0x96, 0);
}
#endif

#ifdef VERSION_US
void func_841577B8(void) {
    func_8415BD48(0);
}
#endif

#ifdef VERSION_US
void BattleAnim_EndEffect33Radial20_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415C2E0(D_800D0510);
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect98Radial20_EmitVariantD(void) {
    f32 x;
    f32 y;
    f32 z;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 scale;
    s32 randomZ;
    s32 randomY;

    func_841569E0(&x, &y, &z, &vx, &vy, &vz);
    vx *= 8.0f;
    vy *= 4.0f;
    vz = 0.0f;
    vy += 6.0f;
    scale = BattleAnim_EffectSecondaryOwnerModelScale();
    randomY = guRandom();
    func_8415CC74(x, y, z, vx, (((randomY % 4) * D_8418C558) + vy) - D_8418C55C, (vz - (((randomZ = guRandom()) % 5) * D_8418C560)) + D_8418C564, 2, 255, 255, 100, 255, 150, 150, 0, D_8418C568, scale, 4.0f * scale, 60);
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D52;
extern void BattleAnim_StartEffect98Radial20_EmitVariantD(void);
void BattleAnim_StartEffect98Radial20_Init(void) {
    D_841A4D52 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_8415C530();
    BattleAnim_StartEffect98Radial20_EmitVariantD();
}
#endif

#ifdef VERSION_US
s32 BattleAnim_StartEffect98Radial20_Update(void) {
    (*(s16 *)&D_841A4D52) = (*(s16 *)&D_841A4D52) + 1;
    if (*(s16 *)&D_841A4D52 >= 0xB5) {
        return -1;
    }
    if (*(s16 *)&D_841A4D52 < 0x78 && (*(s16 *)&D_841A4D52 % 7) == 0) {
        BattleAnim_StartEffect98Radial20_EmitVariantD();
    }
    return func_8415DAE4();
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect98Radial20_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415DBBC(D_800D0510);
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D54;
extern void func_84166130(void);
void BattleAnim_StartEffect11Trail50Alt_Init(void) {
    D_841A4D54 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_84166130();
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D54;
s32 BattleAnim_StartEffect11Trail50Alt_Update(void) {
    f32 jitterX;
    struct { f32 x; f32 y; f32 z; } anchor;
    f32 x;
    f32 y;
    f32 z;
    f32 jitterY;
    f32 jitterZ;
    f32 velocity;
    f32 scale;

    *(s16 *)&D_841A4D54 += 1;
    if ((*(s16 *)&D_841A4D54 & 1) == 0) {
        scale = BattleAnim_EffectSecondaryOwnerModelScale();
        BattleAnim_EffectSecondaryOwnerAnchorPosition((f32 *)&anchor);
        jitterX = ((guRandom() % 50) - 25) * scale;
        x = jitterX + anchor.x;
        jitterY = ((guRandom() % 60) - 30) * scale;
        y = jitterY + anchor.y;
        jitterZ = ((guRandom() % 50) - 25) * scale;
        z = jitterZ + anchor.z;
        velocity = 10.0f;
        if ((f64)x > 0.0) {
            velocity = -velocity;
        }
        TrailEffectPool_Start(x, y, z, velocity, 0.0f, 0.0f, 255, 255, 255, 100, D_8418C56C, 1.0f, 4.0f, 30);
    }
    return TrailEffectPool_IsComplete();
}
#endif

#ifdef VERSION_US
extern u8 D_841A4D08[];
extern s32 func_84166A64(s32, s32);
void func_84157C58(void) {
    s32 temp = D_800D0510;
    D_800D0510 += 8;
    gSPMatrix((Gfx *)(u32)temp, &D_841A4D08, G_MTX_MODELVIEW | G_MTX_LOAD);
    D_800D0510 = func_84166A64(D_800D0510, 0x22);
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D56;
void BattleAnim_StartEffect57Trail50_Init(void) {
    D_841A4D56 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_84166130();
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D56;
s32 BattleAnim_StartEffect57Trail50_Update(void) {
    f32 jitterX;
    struct { f32 x; f32 y; f32 z; } anchor;
    f32 x;
    f32 y;
    f32 z;
    f32 jitterY;
    f32 jitterZ;
    f32 velocity;
    f32 scale;

    *(s16 *)&D_841A4D56 += 1;
    if ((*(s16 *)&D_841A4D56 & 1) == 0) {
        scale = BattleAnim_EffectSecondaryOwnerModelScale();
        BattleAnim_EffectSecondaryOwnerAnchorPosition((f32 *)&anchor);
        jitterX = ((guRandom() % 50) - 25) * scale;
        x = jitterX + anchor.x;
        jitterY = ((guRandom() % 60) - 30) * scale;
        y = jitterY + anchor.y;
        jitterZ = ((guRandom() % 50) - 25) * scale;
        z = jitterZ + anchor.z;
        velocity = 10.0f;
        if ((f64)x > 0.0) {
            velocity = -velocity;
        }
        TrailEffectPool_Start(x, y, z, velocity, 0.0f, 0.0f, 255, 255, 255, 100, D_8418C570, 1.0f, 4.0f, 30);
    }
    return TrailEffectPool_IsComplete();
}
#endif

#ifdef VERSION_US
void func_84157E58(void) {
    s32 temp = D_800D0510;
    D_800D0510 += 8;
    gSPMatrix((Gfx *)(u32)temp, &D_841A4D08, G_MTX_MODELVIEW | G_MTX_LOAD);
    D_800D0510 = func_84166A64(D_800D0510, 0x23);
}
#endif

#ifdef VERSION_US
extern void func_8415F0D0(s32);
extern void func_841603A0(s32);
void BattleAnim_StartEffect42Trail40_Init(void) {
    s32 temp[3];
    extern void BattleAnim_EffectSecondaryOwnerAnchorPosition();
    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerAnchorPosition(temp);
    func_8415F0D0(0x708);
}
#endif

#ifdef VERSION_US
extern void func_8415F9A0(void);
void BattleAnim_StartEffect42Trail40_Update(void) {
    func_8415F9A0();
}
#endif

#ifdef VERSION_US
extern s32 func_8415FD8C();
void BattleAnim_StartEffect42Trail40_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415FD8C(D_800D0510);
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect43Trail40Variant_Init(void) {
    s32 temp[3];
    extern void BattleAnim_EffectSecondaryOwnerAnchorPosition();
    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerAnchorPosition(temp);
    func_841603A0(0x708);
}
#endif

#ifdef VERSION_US
extern void func_84160CD8(void);
void BattleAnim_StartEffect43Trail40Variant_Update(void) {
    func_84160CD8();
}
#endif

#ifdef VERSION_US
extern s32 func_84161018();
void BattleAnim_StartEffect43Trail40Variant_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84161018(D_800D0510);
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect44Trail40GridAlt_Init(void) {
    s32 temp[3];
    extern void BattleAnim_EffectSecondaryOwnerAnchorPosition();
    extern void func_841614E0(s32);
    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerAnchorPosition(temp);
    func_841614E0(0x708);
}
#endif

#ifdef VERSION_US
extern void func_84161DAC(void);
void BattleAnim_StartEffect44Trail40GridAlt_Update(void) {
    func_84161DAC();
}
#endif

#ifdef VERSION_US
extern s32 func_841621A4();
void BattleAnim_StartEffect44Trail40GridAlt_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_841621A4(D_800D0510);
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D00;
extern void func_841639D0(void);
void BattleAnim_StartEffect45FourStreamTrail_Init(void) {
    D_841A4D00 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_841639D0();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_841580C8.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D00;
extern u16 D_841A4D02;
extern u8 D_841A4D08[];
extern s32 func_84164280(s32);
extern s32 func_841650A8(s32);
void BattleAnim_StartEffect45FourStreamTrail_Draw(void) {
    if (*(s16 *)&D_841A4D00 >= 2) {
        s32 temp = D_800D0510;
        D_800D0510 += 8;
        gSPMatrix((Gfx *)(u32)temp, &D_841A4D08, G_MTX_MODELVIEW | G_MTX_LOAD);
        D_800D0510 = func_84164280(D_800D0510);
    }
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D02;
extern void func_841647D0(void);
void BattleAnim_StartEffect62OwnerLinkedFourStream_Init(void) {
    D_841A4D02 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_841647D0();
}
#endif

#ifdef VERSION_US
extern void func_841569E0(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
extern u16 D_841A4D02;
typedef struct { f32 x, y, z; } EmitterPosition;
extern void OwnerLinkedFourStream_Start(f32, f32, f32, f32, f32, f32, u8, u8, u8, u8, f32, f32, f32, s16);
extern s32 OwnerLinkedFourStream_IsComplete(void);
extern void OwnerAnchoredFourStream_Init(void);
extern void OwnerAnchoredFourStream_Start(f32, f32, f32, f32, f32, f32, u8, u8, u8, u8, f32, f32, f32, s16);
extern u8 *func_84109B88(EmitterPosition, u8);
extern f32 __sinf(f32);
extern f32 __cosf(f32);
extern f32 D_8418C588;
extern f32 D_8418C58C;
extern f32 D_8418C590;
extern f32 D_8418C594;
s32 BattleAnim_StartEffect62OwnerLinkedFourStream_Update(void) {
    s32 result;
    f32 x;
    f32 y;
    f32 z;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 angle;
    *(s16 *)&D_841A4D02 += 1;
    if ((*(s16 *)&D_841A4D02 >> 2) < 4 && (*(s16 *)&D_841A4D02 & 3) == 0) {
        func_841569E0(&x, &y, &z, &vx, &vy, &vz);
        angle = (2 - (((*(s16 *)&D_841A4D02 >> 2) + 2) % 3)) * D_8418C588 + D_8418C58C;
        vx *= 7.0f * __cosf(angle);
        vy = __sinf(angle) * 10.0f;
        vz = 0.0f;
        OwnerLinkedFourStream_Start(x, y, z, vx, vy, vz, 208, 255, 255, 128, D_8418C590, 2.0f, 4.0f, 40);
    }
    if (*(s16 *)&D_841A4D02 >= 2) {
        result = OwnerLinkedFourStream_IsComplete();
    } else {
        result = 0;
    }
    return result;
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect62OwnerLinkedFourStream_Draw(void) {
    if (*(s16 *)&D_841A4D02 >= 2) {
        s32 temp = D_800D0510;
        D_800D0510 += 8;
        gSPMatrix((Gfx *)(u32)temp, &D_841A4D08, G_MTX_MODELVIEW | G_MTX_LOAD);
        D_800D0510 = func_841650A8(D_800D0510);
    }
}
#endif

#ifdef VERSION_US
extern void BattleAnim_ResetSharedEffectMatrix(void);
extern void func_841569E0(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
extern u16 D_841A4D04;
void BattleAnim_StartEffect67OwnerAnchoredFourStream_Init(void) {
    EmitterPosition position;
    f32 x;
    f32 y;
    f32 z;
    f32 vx;
    f32 vy;
    f32 vz;
    D_841A4D04 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    OwnerAnchoredFourStream_Init();
    func_841569E0(&x, &y, &z, &vx, &vy, &vz);
    vx *= 5.0;
    vy *= 5.0;
    vz *= 5.0;
    OwnerAnchoredFourStream_Start(x, y, z, vx, vy, vz, 192, 255, 255, 160, D_8418C594, 2.0f, 4.0f, 40);
    position.x = x;
    position.y = y;
    position.z = z;
    func_84109B88(position, 1);
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D04;
extern s32 func_84165C2C(void);
s32 BattleAnim_StartEffect67OwnerAnchoredFourStream_Update(void) {
    (*(s16 *)&D_841A4D04) = (*(s16 *)&D_841A4D04) + 1;
    if (*(s16 *)&D_841A4D04 >= 0x32) {
        return -1;
    }
    return func_84165C2C();
}
#endif

#ifdef VERSION_US
extern s32 func_84165CC0();
void BattleAnim_StartEffect67OwnerAnchoredFourStream_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84165CC0(D_800D0510);
}
#endif

#ifdef VERSION_US
extern void func_841569E0(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
extern void func_8415C644(f32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, f32, f32, s32);
extern f32 D_8418C598;
void BattleAnim_StartEffect78Radial20_EmitVariantA(void) {
    f32 out[6];
    func_841569E0(&out[5], &out[4], &out[3], &out[2], &out[1], &out[0]);
    out[2] *= 6.0f;
    out[1] *= 6.0f;
    out[0] *= 6.0f;
    func_8415C644(out[5], out[4], out[3], out[2], out[1], out[0], 5, 0xFF, 0xFF, 0xFF, 0xB4, D_8418C598, 2.0f, 20.0f, 0x3C);
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D06;
extern void BattleAnim_StartEffect78Radial20_EmitVariantA(void);
void BattleAnim_StartEffect78Radial20_Init(void) {
    D_841A4D06 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_8415C530();
    BattleAnim_StartEffect78Radial20_EmitVariantA();
}
#endif

#ifdef VERSION_US
extern s32 func_8415DAE4(void);
s32 BattleAnim_StartEffect78Radial20_Update(void) {
    (*(s16 *)&D_841A4D06) = (*(s16 *)&D_841A4D06) + 1;
    if (*(s16 *)&D_841A4D06 >= 0xB5) {
        return -1;
    }
    return func_8415DAE4();
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect78Radial20_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415DBBC(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84158914.s")
#endif

#ifdef VERSION_US
extern void func_84166F60(void);
extern void func_84158914(void);
void BattleAnim_StartEffect26DoubleTextureTrail_Init(void) {
    BattleAnim_ResetSharedEffectMatrix();
    func_84166F60();
    func_84158914();
}
#endif

#ifdef VERSION_US
extern void func_841677C4(void);
void BattleAnim_StartEffect26DoubleTextureTrail_Update(void) {
    func_841677C4();
}
#endif

#ifdef VERSION_US
extern s32 func_84168000();
void BattleAnim_StartEffect26DoubleTextureTrail_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84168000(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84158C4C.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D48;
extern void func_84168540(void);
extern void func_84158C4C(void);
void BattleAnim_StartEffect47SixSlotTrail_Init(void) {
    D_841A4D48 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_84168540();
    func_84158C4C();
}
#endif

#ifdef VERSION_US
extern s32 func_84169040(void);
s32 BattleAnim_StartEffect47SixSlotTrail_Update(void) {
    (*(s16 *)&D_841A4D48) = (*(s16 *)&D_841A4D48) + 1;
    if ((*(s16 *)&D_841A4D48 % 10) == 0) {
        func_84158C4C();
    }
    return func_84169040();
}
#endif

#ifdef VERSION_US
extern s32 func_84169618();
void BattleAnim_StartEffect47SixSlotTrail_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84169618(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84158F00.s")
#endif

#ifdef VERSION_US
extern void func_84158F00(void);
void BattleAnim_StartEffect4DoubleTextureTrail_Init(void) {
    BattleAnim_ResetSharedEffectMatrix();
    func_84166F60();
    func_84158F00();
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect4DoubleTextureTrail_Update(void) {
    func_841677C4();
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect4DoubleTextureTrail_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84168000(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415923C.s")
#endif

#ifdef VERSION_US
extern void func_8415923C(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Init(void) {
    BattleAnim_ResetSharedEffectMatrix();
    func_84166F60();
    func_8415923C();
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect77DoubleTextureTrail_Update(void) {
    func_841677C4();
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect77DoubleTextureTrail_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84168000(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84159584.s")
#endif

#ifdef VERSION_US
extern void func_84159584(void);
void BattleAnim_StartEffect70DoubleTextureTrail_Init(void) {
    BattleAnim_ResetSharedEffectMatrix();
    func_84166F60();
    func_84159584();
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect70DoubleTextureTrail_Update(void) {
    func_841677C4();
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect70DoubleTextureTrail_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84168000(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_841597AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84159A50.s")
#endif

#ifdef VERSION_US
extern void func_841597AC(void);
extern void func_84159A50(void);
void BattleAnim_StartEffect39CombinedTrail_Init(void) {
    BattleAnim_ResetSharedEffectMatrix();
    func_84166F60();
    func_841597AC();
    func_84168540();
    func_84159A50();
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D50;
void BattleAnim_StartEffect39CombinedTrail_Update(void) {
    (*(s16 *)&D_841A4D50) = (*(s16 *)&D_841A4D50) + 1;
    if ((*(s16 *)&D_841A4D50 % 10) == 0) {
        func_84159A50();
    }
    func_84169040();
    func_841677C4();
}
#endif

#ifdef VERSION_US
void BattleAnim_StartEffect39CombinedTrail_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp)
    D_800D0510 = func_84168000(D_800D0510);
    D_800D0510 = func_84169618(D_800D0510);
}
#endif

#ifdef VERSION_US
extern u8 *D_80094908;
extern f32 D_8418C5F0;
extern f32 D_8418C5F4;
extern void func_80070C14(f32 *, f32 *, f32 *);
extern void Vec3f_CrossProductComponents(f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);
extern f32 Math_AbsF32(f32);
extern f32 __sinf(f32);
extern f32 __cosf(f32);

void BattleAnim_BuildTerrainCameraBounds(void *output) {
    u8 *camera = D_80094908;
    f32 eyeXOrHalfHeight;
    f32 eyeY;
    f32 eyeZ;
    f32 scaledSine;
    f32 atZ;
    f32 atY;
    f32 atX;
    f32 halfWidth;
    f32 sine;
    f32 nearPlane;
    f32 signedHalfHeight;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 upX;
    f32 upY;
    f32 upZ;
    f32 distance;
    f32 rightX;
    f32 rightY;
    f32 rightZ;
    f32 planeUpX;
    f32 planeUpY;
    f32 planeUpZ;
    f32 cosine;
    f32 fovy;
    f32 ratio;
    f32 aspect;
    f32 angle;

    eyeXOrHalfHeight = *(f32 *)(camera + 0xA8);
    eyeY = *(f32 *)(camera + 0xAC);
    eyeZ = *(f32 *)(camera + 0xB0);
    atX = *(f32 *)(camera + 0xB4);
    atY = *(f32 *)(camera + 0xB8);
    atZ = *(f32 *)(camera + 0xBC);
    upX = *(f32 *)(camera + 0xC0);
    upY = *(f32 *)(camera + 0xC4);
    upZ = *(f32 *)(camera + 0xC8);
    fovy = *(f32 *)(camera + 0x2C);
    ratio = fovy / 30.0f;
    nearPlane = *(f32 *)(camera + 0x34);
    aspect = *(f32 *)(camera + 0x30);
    dx = atX - eyeXOrHalfHeight;
    dy = atY - eyeY;
    dz = atZ - eyeZ;
    func_80070C14(&dx, &dy, &dz);
    distance = nearPlane + 20.0f;
    ((f32 *)output)[0] = (distance * dx) + eyeXOrHalfHeight;
    ((f32 *)output)[1] = (distance * dy) + eyeY;
    ((f32 *)output)[2] = (distance * dz) + eyeZ;
    /* The center no longer needs the eye-X carrier; reuse it for the radius. */
    angle = (D_8418C5F0 * fovy) / 720.0f;
    cosine = __cosf(angle);
    if (cosine != 0.0f) {
        sine = __sinf(angle);
        scaledSine = sine * distance;
        signedHalfHeight = scaledSine / cosine;
        eyeXOrHalfHeight = signedHalfHeight;
    } else {
        eyeXOrHalfHeight = 0.0f;
    }
    eyeXOrHalfHeight = Math_AbsF32(eyeXOrHalfHeight);
    halfWidth = aspect * eyeXOrHalfHeight * ratio * D_8418C5F4;
    Vec3f_CrossProductComponents(dx, dy, dz, upX, upY, upZ, &rightX, &rightY, &rightZ);
    Vec3f_CrossProductComponents(dx, dy, dz, rightX, rightY, rightZ, &planeUpX, &planeUpY, &planeUpZ);
    func_80070C14(&rightX, &rightY, &rightZ);
    func_80070C14(&planeUpX, &planeUpY, &planeUpZ);
    ((f32 *)output)[3] = rightX * halfWidth;
    ((f32 *)output)[4] = rightY * halfWidth;
    ((f32 *)output)[5] = rightZ * halfWidth;
    ((f32 *)output)[6] = planeUpX * eyeXOrHalfHeight;
    ((f32 *)output)[7] = planeUpY * eyeXOrHalfHeight;
    ((f32 *)output)[8] = planeUpZ * eyeXOrHalfHeight;
}
#endif

#ifdef VERSION_US
typedef struct {
    f32 field_00;
    f32 field_04;
    f32 field_08;
    f32 field_0C;
    s16 value;
    u8 unknown_12[2];
} Fragment79TerrainPointView;
extern u8 *D_84187330;
extern s16 MathUtil_Atan2s(f32, f32);

f32 BattleAnim_SampleTerrainHeightAndSlope(f32 x, f32 z, f32 *slope) {
    f32 cellX;
    f32 cellZ;
    f32 height;
    f32 ax;
    f32 ay;
    f32 az;
    f32 bx;
    f32 by;
    f32 bz;
    f32 cx;
    f32 cy;
    f32 cz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dxB;
    f32 dzB;
    f32 dxD;
    f32 dzD;
    f32 angle;
    f32 distanceB;
    f32 distanceD;
    f32 relativeX;
    f32 relativeZ;
    f32 e1x;
    f32 e1y;
    f32 e1z;
    f32 e2x;
    f32 e2y;
    f32 e2z;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 weightedX;
    f32 weightedZ;
    s32 i;
    s32 j;
    Fragment79TerrainPointView *point;

    cellX = ((x + 440.0f) / 150.0f) + 8.0f;
    cellZ = (z / 200.0f) + 8.0f;
    i = (s32)cellX;
    j = (s32)cellZ;
    if (i < 0) {
        i = 0;
    }
    if (i >= 15) {
        i = 14;
    }
    if (j < 0) {
        j = 0;
    }
    if (j >= 15) {
        j = 14;
    }
    point = &((Fragment79TerrainPointView (*)[16])(D_84187330 + 0x1010))[i][j];
    ax = point->field_00;
    ay = point->field_04;
    az = point->field_08;
    point = &((Fragment79TerrainPointView (*)[16])(D_84187330 + 0x1010))[i + 1][j];
    bx = point->field_00;
    by = point->field_04;
    bz = point->field_08;
    point = &((Fragment79TerrainPointView (*)[16])(D_84187330 + 0x1010))[i][j + 1];
    cx = point->field_00;
    cy = point->field_04;
    cz = point->field_08;
    point = &((Fragment79TerrainPointView (*)[16])(D_84187330 + 0x1010))[i + 1][j + 1];
    dx = point->field_00;
    dy = point->field_04;
    dz = point->field_08;
    dxB = bx - x;
    dzB = bz - z;
    dxD = dx - x;
    dzD = dz - z;
    distanceB = dxB * dxB + dzB * dzB;
    distanceD = dxD * dxD + dzD * dzD;
    if (distanceB <= distanceD) {
        e1x = bx - ax;
        e1y = by - ay;
        e1z = bz - az;
        e2x = cx - ax;
        e2y = cy - ay;
        e2z = cz - az;
        Vec3f_CrossProductComponents(e1x, e1y, e1z, e2x, e2y, e2z, &nx, &ny, &nz);
        if (ny != 0.0f) {
            relativeX = x - ax;
            relativeZ = z - az;
            weightedX = relativeX * nx;
            weightedZ = nz * relativeZ;
            height = ay - ((weightedX + weightedZ) / ny);
        } else {
            height = (ay + by + cy) / 3.0f;
        }
    } else {
        e1x = bx - dx;
        e1y = by - dy;
        e1z = bz - dz;
        e2x = cx - dx;
        e2y = cy - dy;
        e2z = cz - dz;
        Vec3f_CrossProductComponents(e1x, e1y, e1z, e2x, e2y, e2z, &nx, &ny, &nz);
        if (ny != 0.0f) {
            relativeX = x - dx;
            relativeZ = z - dz;
            weightedX = relativeX * nx;
            weightedZ = nz * relativeZ;
            height = dy - ((weightedX + weightedZ) / ny);
        } else {
            height = (dy + by + cy) / 3.0f;
        }
    }
    angle = (f32)MathUtil_Atan2s(ny, nx);
    angle = (angle * 360.0f) / 65536.0f;
    if (angle > 90.0f) {
        angle -= 180.0f;
    }
    if (angle < -90.0f) {
        angle += 180.0f;
    }
    *slope = angle;
    return height;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415A364.s")
#endif

#ifdef VERSION_US
extern void *D_84187334;
extern s16 D_841A4D60;
extern s16 D_841A4D62;
extern s16 D_841A4D64;
extern s32 func_8415A364(void);

void BattleAnim_InitializeTerrainGrid(s32 orientation, s16 warmup, s32 duration) {
    s32 i;
    s32 j;
    Fragment79TerrainPointView *point;

    D_841A4D60 = 0;
    *(s16 *)(D_84187330 + 4) = 0;
    *(f32 *)D_84187330 = 0.0f;
    *(s16 *)(D_84187330 + 6) = warmup;
    *(s16 *)(D_84187330 + 8) = 30000;
    point = (Fragment79TerrainPointView *)(D_84187330 + 0x1010);
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            point->field_00 = (f32)orientation * (((f32)i * 150.0f - 1200.0f) - 440.0f);
            point->field_04 = 1.0f;
            point->field_08 = (f32)j * 200.0f - 1600.0f;
            point->field_0C = 1.0f;
            point->value = 0;
            point++;
        }
    }
    D_841A4D62 = 0;
    D_841A4D64 = 8;
    if (warmup > 0) {
        for (i = 0; i < warmup; i++) {
            func_8415A364();
        }
        BattleAnim_BuildTerrainCameraBounds(D_84187334);
    }
}
#endif

#ifdef VERSION_US

void BattleAnim_SetTerrainGridPointValue(u8 value) {
    Fragment79TerrainPointView *point;
    s32 i;
    s32 j;

    for (i = 1; i < 15; i++) {
        for (j = 1; j < 15; j++) {
            point = &((Fragment79TerrainPointView (*)[16])(D_84187330 + 0x1010))[i][j];
            point->value = value;
        }
    }
}
#endif

#ifdef VERSION_US
extern u32 func_841094EC(void);

void BattleAnim_UpdateTerrainGrid(void) {
    s32 status;

    status = (s32)func_841094EC();
    if (status == 1 && D_841A4D60 == 0) {
        *(s16 *)(D_84187330 + 8) = *(s16 *)(D_84187330 + 4) + 0x463C;
        D_841A4D60 = 1;
    }
    func_8415A364();
    D_841A4D62 = (D_841A4D62 + 2) & 0x3FFF;
    D_841A4D64 = (D_841A4D64 - 1) & 0x3FFF;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415ADE0.s")
#endif
