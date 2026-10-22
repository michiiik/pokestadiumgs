#include "global.h"


#ifdef VERSION_US
extern u8 D_86C00350[];
extern void fragment3_main(void *);
extern void func_81A005F0(void *);
extern void func_8005A0B4(s32);
void func_86C00020(void) {
    fragment3_main(D_86C00350);
    func_81A005F0(D_86C00350);
    func_8005A0B4(0);
    func_8005A0B4(1);
    func_8005A0B4(2);
    func_8005A0B4(3);
}

extern u8 D_800D0510[];
extern void BgStage_DrawFrame(void);
extern void GfxImage_FillCurrent(void *, s32);
extern void func_81A0022C(void *);
extern void func_80008648(void);
void func_86C00070(void) {
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&D_800D0510, 0x8421);
    func_81A0022C(&D_86C00350);
    func_80008648();
}

extern u8 StageContext_GetFadeMode(void);
extern s32 StageFade_StartFromTransparent(s32 arg0);
s32 func_86C002C4(void);

s32 func_86C000B4(s32 arg0) {
    s32 var_s0 = arg0;

    switch (arg0) {
        case 0:
            if (StageContext_GetFadeMode() == 0) {
                var_s0 = 1;
            }
            break;
        case 1:
            if (func_86C002C4() != 0) {
                var_s0 = 2;
                StageFade_StartFromTransparent(5);
            }
            break;
        case 2:
            if (StageContext_GetFadeMode() == 1) {
                var_s0 = 3;
            }
            break;
    }
    return var_s0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/62/fragment62_code/func_86C00148.s")

#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

M2C_UNK Asset_LoadToSegment(u32, M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK Gfx_FreeDisplayListBuffers();               /* extern */
M2C_UNK Gfx_InitDisplayListBuffers(M2C_UNK, M2C_UNK); /* extern */
s32 func_800082E0(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_80008514(s32);                         /* extern */
M2C_UNK func_80008574();                            /* extern */
s32 func_80047588(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_80047610();                            /* extern */
M2C_UNK func_8004C09C(M2C_UNK);                     /* extern */
M2C_UNK func_8004C398();                            /* extern */
M2C_UNK func_8004C4B0(M2C_UNK);                     /* extern */
M2C_UNK func_86C00148();                            /* extern */
M2C_UNK main_pool_pop_state(M2C_UNK);               /* extern */
M2C_UNK main_pool_push_state(M2C_UNK);              /* extern */
extern M2C_UNK D_1000000;
extern M2C_UNK D_446E30;
extern M2C_UNK D_447D00;
extern s32 D_86C0036C;

s32 func_86C001CC(s32 arg0, M2C_UNK arg1) {
    s32 sp24;

    main_pool_push_state(0x47424552);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = func_800082E0(0, 1, 2, 0, 2, 1);
    func_8004C09C(0x107);
    func_8004C4B0(0x35);
    D_86C0036C = func_80047588(0x3F, 0);
    Asset_LoadToSegment((u32) ((s32) &D_1000000 & 0x0F000000) >> 0x18, &D_446E30, &D_447D00, 0);
    func_86C00020();
    func_80008514(sp24);
    func_86C00148();
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x47424552);
    return 0;
}
s32 func_81A00074(u8 *, s32);
extern s8 D_86C00320;
extern s8 D_86C00330;
extern s8 D_86C00340;
s32 func_86C002C4(void) {
    s32 sp18;
    s32 temp_v0;

    osSyncPrintf(&D_86C00320);
    temp_v0 = func_81A00074(D_86C00350, 0);
    sp18 = temp_v0;
    osSyncPrintf(&D_86C00330, temp_v0);
    osSyncPrintf(&D_86C00340);
    return temp_v0;
}
#endif
