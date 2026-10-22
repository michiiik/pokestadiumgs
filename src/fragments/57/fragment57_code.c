#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83300020.s")

s32 func_83300398(s32 arg0, s32 arg1) {
    return arg0 + arg1 / 2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833003B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833005F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_8330084C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83300CB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833015C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_8330173C.s")

extern u8 D_8330A2B0;

s32 func_833018B8(s32 arg0, void *arg1) {
    if (arg0 == 2) {
        (*(u8 *)((u8 *)(arg1) + (0x18))) = (u8) (*(u8 *)((u8 *)(&D_8330A2B0) + (0x10C)));
        (*(u8 *)((u8 *)(arg1) + (0x19))) = (u8) (*(u8 *)((u8 *)(&D_8330A2B0) + (0x10D)));
        (*(u8 *)((u8 *)(arg1) + (0x1A))) = (u8) (*(u8 *)((u8 *)(&D_8330A2B0) + (0x10E)));
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833018E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833019CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83301C60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83302088.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83302180.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83302290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83302AC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83302D8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_8330309C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83303220.s")

extern void *D_800D0510;
extern void *D_80087200;
extern s32 D_833090AC;
extern u8 D_8330A288[];
extern s32 D_8330A2C4;
extern s32 D_8330A2EC;
extern s32 D_8330A4C8;
extern void BgStage_DrawFrame(void);
extern void GfxImage_FillCurrent(void *, u16);
extern void GeoRender_AdvanceFrameCounter(void);
extern void Geo_RenderRootNode(s32);
extern void func_83302290(void);
extern void func_83302AC8(void);
extern void func_83302D8C(void);
extern void func_83303220(void);
extern void func_81A0022C(void *);
extern void func_80008648(void);
void func_83303564(void) {
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&D_800D0510, 1);
    if (D_8330A2EC == 1) {
        func_83303220();
    }
    if (D_8330A2C4 == 0) {
        GeoRender_AdvanceFrameCounter();
    }
    Geo_RenderRootNode(D_8330A4C8);
    func_83302D8C();
    if ((*(u16 *)((u8 *)D_80087200 + 6) & 0x2000) && (D_833090AC == 1)) {
        func_83302AC8();
    }
    if (D_8330A2C4 == 1) {
        func_83302290();
    }
    func_81A0022C(D_8330A288);
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83303640.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83303AB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83305C1C.s")

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

s32 ModelAnim_IsFinished(M2C_UNK *);                /* extern */
M2C_UNK func_80024480(s32, M2C_UNK);                /* extern */
M2C_UNK func_8003F2C4(s32, M2C_UNK *, s32);         /* extern */
M2C_UNK func_8003F3BC(M2C_UNK *, s32);              /* extern */
M2C_UNK func_83300020(M2C_UNK);                     /* extern */
M2C_UNK func_833003B0(M2C_UNK);                     /* extern */
M2C_UNK func_83303640(M2C_UNK);                     /* extern */
extern u8 *D_83308E34;
extern s32 D_8330A4CC;
extern M2C_UNK D_8330A4D0;
extern s32 D_8330ABD8;

void func_83306BF0(void) {
    func_83300020(1);
    func_83303640(1);
    if ((ModelAnim_IsFinished(&D_8330A4D0) == 1) && ((M2C_FIELD(&D_8330A2B0, s32 *, 0xC) >= 0x5B) || (M2C_FIELD(D_83308E34, s16 *, 2) == -1))) {
        if (M2C_FIELD(&D_8330A2B0, s32 *, 0x30) == 0) {
            if (M2C_FIELD(&D_8330A2B0, s32 *, 0x48) == 1) {
                M2C_FIELD(&D_8330A2B0, s32 *, 0) = 9;
                func_80024480(D_8330ABD8, 4);
                func_8003F2C4(D_8330A4CC, &D_8330A4D0, M2C_FIELD(&D_8330A2B0, s32 *, 0x34));
                func_8003F3BC(&D_8330A4D0, M2C_FIELD(&D_8330A2B0, s32 *, 0x38));
                M2C_FIELD(&D_8330A2B0, s32 *, 0x30) = 1;
            }
        } else {
            func_8003F2C4(D_8330A4CC, &D_8330A4D0, 0);
            func_8003F3BC(&D_8330A4D0, 0);
            M2C_FIELD(&D_8330A2B0, s32 *, 0) = 9;
        }
        if (M2C_FIELD(&D_8330A2B0, s32 *, 0) == 9) {
            func_833003B0(4);
            M2C_FIELD(&D_8330A2B0, s32 *, 0xC) = 0;
        }
    }
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83306D0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83307088.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833078C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83307AAC.s")

extern s32 D_83308E2C;
extern void func_80021ED8(s32);
s32 func_83307C2C(s32 arg0) {
    if (arg0 > 0) {
        arg0 += 1;
    }
    if ((D_83308E2C * 5 + 5) < arg0) {
        func_80021ED8(0x57);
        arg0 = 0;
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_83307C7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/57/fragment57_code/func_833084B0.s")

s32 Asset_LoadToSegment(u32, s32 *, s32 *, s32); /* extern */
s32 Gfx_FreeDisplayListBuffers();               /* extern */
s32 Gfx_InitDisplayListBuffers(s32, s32); /* extern */
s32 fragment3_main(s32 *);                  /* extern */
s32 func_80001FF0();                                /* extern */
s32 func_800082E0(s32, s32, s32, s32, s32, s32); /* extern */
s32 func_80008514(s32);                         /* extern */
s32 func_80008574();                            /* extern */
s32 func_800086A4(s32);                     /* extern */
s32 func_80047588(s32, s32);            /* extern */
s32 func_80047610();                            /* extern */
s32 func_8004C09C(s32);                     /* extern */
s32 func_8004C398();                            /* extern */
s32 func_8004C4B0(s32);                     /* extern */
s32 func_8004D690(s32);                         /* extern */
s32 func_80057908(s32);                         /* extern */
s32 func_80057944(s32);                         /* extern */
s32 func_8005A134(s32);                         /* extern */
s32 func_83301C60();                            /* extern */
s32 func_833084B0();                            /* extern */
extern s32 D_1000000;
extern s32 D_446E30;
extern s32 D_447D00;
extern f32 D_83308E30;
extern f32 D_8330A23C;
extern s32 D_8330A4C4;
extern s32 D_8330AC68;

s32 func_8330853C(s32 arg0, u8 *arg1) {
    s32 sp24;
    u8 value;

    if (func_80001FF0() == 0x3C) {
        D_83308E2C = 0x1E;
        D_83308E30 = 1.0f;
    } else {
        D_83308E2C = 0x19;
        D_83308E30 = D_8330A23C;
    }
    D_83308E34 = arg1;
    D_833090AC = 0;
    if (D_83308E34 == NULL) {
        value = 1;
        D_833090AC = value;
        *(s16 *)&D_8330AC68 = 0;
        *(s16 *)((u8 *)&D_8330AC68 + 2) = -1;
        *(u8 *)((u8 *)&D_8330AC68 + 4) = 1;
        D_83308E34 = &D_8330AC68;
    } else {
        func_80057908((*(s8 *)(D_83308E34 + 0x5C) - 1) & 0xFF);
    }
    main_pool_push_state(0x4D525357);
    Gfx_InitDisplayListBuffers(0x20000, 0);
    sp24 = func_800082E0(0, 1, 2, 1, 2, 1);
    func_8004C09C(0x127);
    D_8330A4C4 = func_8004D690(0x18);
    func_8004C4B0(0x49);
    func_8004C4B0(6);
    func_8004C4B0(0);
    func_8004C8C0(0x4E);
    func_8004C8C0(0x164);
    func_8004C8C0(0x137);
    func_80047588(0x13, 0);
    Asset_LoadToSegment((u32) ((s32) &D_1000000 & 0x0F000000) >> 0x18, &D_446E30, &D_447D00, 0);
    func_8005A134(*(s8 *)(D_83308E34 + 0x5C) - 1);
    func_83301C60();
    fragment3_main(&D_8330A288);
    func_80008514(sp24);
    func_833084B0();
    func_800086A4(2);
    func_80008574();
    if (D_833090AC == 0) {
        func_80057944((*(s8 *)(D_83308E34 + 0x5C) - 1) & 0xFF);
    }
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x4D525357);
    return 0;
}
#endif
