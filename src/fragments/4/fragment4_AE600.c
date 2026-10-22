#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_81800020.s")
#endif

#ifdef VERSION_US
s32 func_80001FF0();
s32 func_80008970();

f32 func_818006B4(void) {
    s32 sp1C;

    sp1C = func_80008970();
    return ((f32) sp1C * 60.0f) / (f32) func_80001FF0();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_818006FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_818008E4.s")
#endif

#ifdef VERSION_US
/* mkdraft:Gfx_SetupOrthoProjection begin */
extern s32 func_8000731C(void);
extern void *Gfx_AllocDisplayList(s32);
extern void Gfx_SetViewportDimensions(void *, s16, s16);
extern Mtx D_80094890;
extern u32 D_800D0510;

void Gfx_SetupOrthoProjection(void) {
    s16 *dims;
    Mtx *matrix;
    Vp *viewport;
    dims = (s16 *)func_8000731C();
    matrix = Gfx_AllocDisplayList(0x40);
    viewport = Gfx_AllocDisplayList(0x10);
    Gfx_SetViewportDimensions(viewport, dims[2], dims[3]);
    gSPViewport((*(Gfx **)&D_800D0510)++, (u32)viewport & 0x1FFFFFFF);
    guOrtho(matrix, 0.5f, (f32)(u16)dims[2] - 0.5f, (f32)(u16)dims[3] - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);
    gSPPerspNormalize((*(Gfx **)&D_800D0510)++, 0xFFFF);
    gSPMatrix((*(Gfx **)&D_800D0510)++, (u32)matrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix((*(Gfx **)&D_800D0510)++, (u32)&D_80094890 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}
/* mkdraft:Gfx_SetupOrthoProjection end */
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_81800C18.s")
#endif

#ifdef VERSION_US
s32 func_8004C990(s32, s32);
extern void func_8004D1FC(s32);
extern void func_81800020(f32, f32, s32, s32, s32, s32, f32, f32);
void func_81800D70(s32 arg0, s32 arg1) {
    func_8004D1FC(func_8004C990(0xEF, 0));
    func_81800020((f32) arg0, (f32) arg1, 0x41000000, 0x41600000, 0x50, 0, 1.0f, 1.0f);
}
#endif

#ifdef VERSION_US
extern f32 D_81805CD4;
s32 func_81800DE4(f32 arg0) {
    s32 temp_v1;

    temp_v1 = (s32) arg0 & 0x1F;
    return ((temp_v1 << 0xA) + (s32) (((arg0 - (f32) temp_v1) + D_81805CD4) * 1024.0f)) & 0xFFFF;
}
#endif

void func_81800E30(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_81800E38.s")
#endif

#ifdef VERSION_US
/* mkdraft:func_818011EC begin */
extern s32 func_8004CA10(u16 *);
extern s32 func_8004CA24(u16 *);
extern u8 *func_8004CA60(u8 *);
extern s32 func_8004CA38(u8 *);
extern s32 func_8004CA4C(u8 *);
extern void func_81800E38(s16, s16, u16, u16, s32, s32, u8 *, s32, s32, s32);

void func_818011EC(s16 arg0, s16 arg1, u16 arg2, u16 arg3, void *arg4) {
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp24 = 1;
    u8 *sp34;

    sp44 = func_8004CA10((u16 *)arg4);
    sp40 = func_8004CA24((u16 *)arg4);
    sp34 = func_8004CA60((u8 *)arg4);
    sp3C = func_8004CA38((u8 *)arg4);
    func_81800E38(arg0, arg1, arg2, arg3, sp44, sp40, sp34, sp3C, func_8004CA4C((u8 *)arg4), sp24);
}
/* mkdraft:func_818011EC end */
#endif

#ifdef VERSION_US
extern s32 func_8004CA4C(u8 *);
extern s32 func_8004CA10(u16 *);
extern s32 func_8004CA24(u16 *);
s32 func_8180128C(u8 *arg0) {
    s32 scale;
    s32 value;

    scale = 8;
    switch (func_8004CA4C(arg0)) {
    case 0:
        scale = 4;
        break;
    case 1:
        break;
    case 2:
        scale = 0x10;
        break;
    case 3:
        scale = 0x20;
        break;
    }
    value = func_8004CA10((u16 *)arg0);
    return func_8004CA24((u16 *)arg0) * scale * value;
}
#endif

#ifdef VERSION_US
extern s32 StageContext_GetFadeMode(void);
extern void StageFade_StartFromOpaque(s32);
s32 func_8180132C(s32 arg0) {
    switch (StageContext_GetFadeMode()) {
    case 1:
        StageFade_StartFromOpaque(arg0);
    case 2:
    case 3:
        return 0;
    case 0:
        return 1;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_81801388.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_AE600/func_81801420.s")
#endif

#ifdef VERSION_US
extern f32 D_81805920;
f32 func_818014A8(void) {
    return D_81805920;
}
#pragma C_FUNCTION_PADDING(12)
#endif
