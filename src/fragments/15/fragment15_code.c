#include "global.h"


#ifdef VERSION_US
extern s32 D_83F003F0;
void func_83F00020(void) {
    D_83F003F0 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/15/fragment15_code/func_83F0002C.s")

extern OSTime D_83F00400;

s32 func_83F0012C(void) {
    s32 var_v0;

    var_v0 = 0;
    if ((u32)OS_CYCLES_TO_USEC(osGetTime() - D_83F00400) >= 1000000) {
        var_v0 = 1;
    }
    return var_v0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/15/fragment15_code/func_83F001A8.s")

extern void func_83F0002C();
s32 func_83F001A8(s32);
void func_83F00298(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(0xA);
    StageFade_StartFromOpaque(1);
    do {
        func_80064D28();
        func_83F0002C();
        temp_v0 = func_83F001A8(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 4);
}

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
M2C_UNK func_80047588(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_80047610();                            /* extern */
M2C_UNK func_8004C09C(M2C_UNK);                     /* extern */
M2C_UNK func_8004C398();                            /* extern */
M2C_UNK func_8004C8C0(M2C_UNK);                     /* extern */
M2C_UNK main_pool_pop_state(M2C_UNK);               /* extern */
M2C_UNK main_pool_push_state(M2C_UNK);              /* extern */
extern M2C_UNK D_1000000;
extern M2C_UNK D_446E30;
extern M2C_UNK D_447D00;

s32 func_83F002F4(s32 arg0, M2C_UNK arg1) {
    s32 sp24;

    main_pool_push_state(0x4C475657);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(3);
    func_8004C8C0(0xED);
    func_80047588(0x18, 0);
    Asset_LoadToSegment((u32) ((s32) &D_1000000 & 0x0F000000) >> 0x18, &D_446E30, &D_447D00, 0);
    func_83F00020();
    func_80008514(sp24);
    func_83F00298();
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x4C475657);
    return 0;
}
#endif
