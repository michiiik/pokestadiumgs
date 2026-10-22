#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/42/fragment42_code/func_88D00020.s")

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

M2C_UNK GfxImage_FillCurrent(M2C_UNK *, M2C_UNK);   /* extern */
M2C_UNK func_80007444(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_80008648();                            /* extern */
M2C_UNK func_800088DC();                            /* extern */
M2C_UNK func_800495F8(); /* extern */
M2C_UNK func_800496A4(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8004972C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_800498C4();                            /* extern */
M2C_UNK func_800499EC();                            /* extern */
extern M2C_UNK D_800D0510;
extern u8 *D_88A01C64;
extern M2C_UNK D_88D00940;
extern M2C_UNK D_88D0094C;
extern M2C_UNK D_88D00984;
extern M2C_UNK D_88D00990;
extern M2C_UNK D_88D009BC;
extern M2C_UNK D_88D009EC;
extern M2C_UNK D_88D00A20;
extern M2C_UNK D_88D00A44;
extern M2C_UNK D_88D00A50;
extern M2C_UNK D_88D00A5C;
extern M2C_UNK D_88D00A68;

void func_88D00178(void) {
    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 1);
    func_80007444(&D_800D0510, 0x32, 0x5A, 0x136, 0x67, 0x7C67);
    func_800498C4();
    func_800496A4(0x10, 2);
    func_8004972C(0x32, 0x80, 0xFF, 0xFF);
    func_800495F8(0x3C, 0x64, 0, &D_88D00940);
    func_8004972C(0xFF, 0xC8, 0xC8, 0xFF);
    func_800495F8(0x32, 0xD2, 0, &D_88D0094C);
    func_800495F8(0x32, 0xF0, 0, &D_88D00984);
    func_800495F8(0x32, 0x10E, 0, &D_88D00990);
    func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
    func_800495F8(0x32, 0x136, 0, &D_88D009BC);
    func_8004972C(0xFF, 0x64, 0x64, 0xFF);
    func_800495F8(0x32, 0x168, 0, &D_88D009EC);
    func_800495F8(0x32, 0x186, 0, &D_88D00A20);
    func_800496A4(8, 1);
    func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
    func_800495F8(0x3C, 0x8C, 0, &D_88D00A44);
    func_800495F8(0x3C, 0xA5, 0, &D_88D00A50);
    func_800495F8(0x15E, 0x8C, 2, &D_88D00A5C, (s32) M2C_FIELD(D_88A01C64, u8 *, 0xF4));
    func_800495F8(0x15E, 0xA5, 2, &D_88D00A68, (s32) M2C_FIELD(D_88A01C64, u8 *, 0xFC));
    func_800499EC();
    func_80008648();
}
/* mkdraft:func_88D0038C begin */
extern s32 func_80001FF0(void);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern void func_88D00178(void);
extern f32 D_88D00A74;

void func_88D0038C(void) {
    u16 count;
    s32 i;
    count = (u16)((f32)func_80001FF0() * D_88D00A74 / 2);
    StageFade_StartFromOpaque(count);
    if (count != 0) {
        i = 0;
        do {
            func_80064D28();
            func_88D00178();
            i++;
        } while (i != count);
    }
}
/* mkdraft:func_88D0038C end */

extern void func_80064D28(void);
extern s32 func_88D00020(void);
extern void func_88D00178(void);
void func_88D00488(void) {
    s32 result;
    do {
        func_80064D28();
        result = func_88D00020();
        func_88D00178();
    } while (result == 0);
}

/* mkdraft:func_88D004C8 begin */
extern s32 func_80001FF0(void);
extern void func_800225C4(s32);
extern void StageFade_StartFromTransparent(s32);
extern void func_80064D28(void);
extern void func_88D00178(void);
extern f32 D_88D00A78;

void func_88D004C8(void) {
    u16 count;
    s32 i;
    count = (u16)((f32)func_80001FF0() * D_88D00A78 / 2);
    func_800225C4(count * 2);
    StageFade_StartFromTransparent(count);
    if (count != 0) {
        i = 0;
        do {
            func_80064D28();
            func_88D00178();
            i++;
        } while (i != count);
    }
}
/* mkdraft:func_88D004C8 end */

extern s32 mem_pool_try_init(s32, s32);
extern void func_80057908(s32);
extern s32 func_8005DA1C(s32);
extern u8 func_8005D92C(s32);
extern void func_8005DC48(s32, u8 *);
extern void func_8005A014(s32);
extern void func_8005A034(s32);
extern s32 func_80055948(s32);
extern void func_88A00D0C(s32);
extern s8 D_88006868[];
extern u8 D_8800686D[];
void func_88D005CC(void) {
    s32 pool = mem_pool_try_init(0x14000, 0);
    func_80057908(0);
    D_88006868[0] = 0;
    *(s16 *)(D_88006868 + 2) = func_8005DA1C(D_88006868[0]);
    D_88006868[4] = func_8005D92C(D_88006868[0]);
    func_8005DC48(D_88006868[0], D_8800686D);
    func_8005A014(0);
    func_8005A034(0);
    func_80055948(3);
    func_88A00D0C(pool);
}

extern void main_pool_push_state(s32 arg0);
extern void main_pool_pop_state(s32 arg0);
extern void Gfx_InitDisplayListBuffers(s32 arg0, s32 arg1);
extern s32 StageContext_Allocate(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern void func_8004C09C(s32 arg0);
extern s32 func_80047588(s32 arg0, s32 arg1);
extern s32 D_8800687C;
extern void func_88D005CC(void);
extern void func_80008514(s32 arg0);
extern void func_88D0038C(void);
extern void func_88D00488(void);
extern void func_88D004C8(void);
extern void func_80008574(void);
extern void func_80047610(void);
extern void func_8004C398(void);
extern void Gfx_FreeDisplayListBuffers(void);
extern void func_80057944(s32 arg0);
s32 fragment42_main(s32 arg0, s32 arg1) {
    s32 stage;
    main_pool_push_state(0x4946554C);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    stage = StageContext_Allocate(1, 0, 2, 0, 2, 1);
    func_8004C09C(3);
    D_8800687C = func_80047588(0x18, 0);
    func_88D005CC();
    func_80008514(stage);
    func_88D0038C();
    func_88D00488();
    func_88D004C8();
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    func_80057944(0);
    main_pool_pop_state(0x4946554C);
    return 0;
}
#endif
