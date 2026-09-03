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
void func_84156880(void) { func_841098C0(); }
#endif

#ifdef VERSION_US
void BattleAnim_EffectSecondaryOwnerAnchorPosition() { func_84109780(); }
#endif

#ifdef VERSION_US
void BattleAnim_EffectTertiaryOwnerBonePosition(void) { func_841098C0(); }
#endif

#ifdef VERSION_US
void BattleAnim_EffectSecondaryOwnerBonePosition(void) { func_84109884(); }
#endif

#ifdef VERSION_US
void BattleAnim_EffectTertiaryOwnerModelScale(void) { func_84109590(); }
#endif

#ifdef VERSION_US
void BattleAnim_EffectSecondaryOwnerModelScale(void) { func_84109544(); }
#endif

#ifdef VERSION_US
void func_84156940(void) { func_841094F8(); }
#endif

#ifdef VERSION_US
void func_84156960(void) { func_8410971C(); }
#endif

#ifdef VERSION_US
void func_84156980(void) { func_84109848(); }
#endif

#ifdef VERSION_US
void func_841569A0(void) { func_841095DC(); }
#endif

#ifdef VERSION_US
void func_841569C0(void) { func_84109B1C(); }
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84156BD4.s")
#endif

#ifdef VERSION_US
extern void func_8415AD58(void);
void func_84156C40(void) {
    func_8415AD58();
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84156CCC.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D4A;
extern void BattleAnim_ResetSharedEffectMatrix(void);
extern void func_8415C530(void);
extern void func_84156CCC(void);
void func_84156E58(void) {
    D_841A4D4A = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_8415C530();
    func_84156CCC();
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D4A;
extern u16 D_841A4D4C;
extern u16 D_841A4D4E;
extern u16 D_841A4D52;
extern void func_84156CCC(void);
extern void func_84157128(void);
extern void func_84157398(void);
extern void func_8415782C(void);
extern s32 func_8415DAE4(void);
s32 func_84156E8C(void) {
    (*(s16 *)&D_841A4D4A) = (*(s16 *)&D_841A4D4A) + 1;
    if (*(s16 *)&D_841A4D4A >= 0xB5) {
        return -1;
    }
    if (*(s16 *)&D_841A4D4A < 0x78 && (*(s16 *)&D_841A4D4A % 7) == 0) {
        func_84156CCC();
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84156F50.s")
#endif

#ifdef VERSION_US
extern void func_8415BD48(s32);
void func_84156FC8(void) { func_8415BD48(0); }
#endif

#ifdef VERSION_US
extern s32 func_8415C2E0();
void func_84156FE8(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415C2E0(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415703C.s")
#endif

#ifdef VERSION_US
void func_841570B4(void) { func_8415BD48(1); }
#endif

#ifdef VERSION_US
void func_841570D4(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415C2E0(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157128.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D4C;
extern void func_84162660(void);
extern void func_84157128(void);
void BattleAnim_StartEffect7TexturedRibbonSheet_Init(void) {
    D_841A4D4C = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_84162660();
    func_84157128();
}
#endif

#ifdef VERSION_US
s32 BattleAnim_StartEffect7TexturedRibbonSheet_Update(void) {
    (*(s16 *)&D_841A4D4C) = (*(s16 *)&D_841A4D4C) + 1;
    if (*(s16 *)&D_841A4D4C >= 0x709) {
        return -1;
    }
    if (*(s16 *)&D_841A4D4C < 0x6EA && (*(s16 *)&D_841A4D4C % 3) == 0) {
        func_84157128();
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157650.s")
#endif

#ifdef VERSION_US
void func_841576CC(void) { func_8415BD48(0); }
#endif

#ifdef VERSION_US
void BattleAnim_EndEffect32Radial20_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415C2E0(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157740.s")
#endif

#ifdef VERSION_US
void func_841577B8(void) { func_8415BD48(0); }
#endif

#ifdef VERSION_US
void BattleAnim_EndEffect33Radial20_Draw(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415C2E0(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415782C.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D52;
extern void func_8415782C(void);
void BattleAnim_StartEffect98Radial20_Init(void) {
    D_841A4D52 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    func_8415C530();
    func_8415782C();
}
#endif

#ifdef VERSION_US
s32 BattleAnim_StartEffect98Radial20_Update(void) {
    (*(s16 *)&D_841A4D52) = (*(s16 *)&D_841A4D52) + 1;
    if (*(s16 *)&D_841A4D52 >= 0xB5) {
        return -1;
    }
    if (*(s16 *)&D_841A4D52 < 0x78 && (*(s16 *)&D_841A4D52 % 7) == 0) {
        func_8415782C();
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157ADC.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157CDC.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415839C.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84158588.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84159D30.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84159FA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415A364.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415A9E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415AC64.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415AD58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415ADE0.s")
#endif
