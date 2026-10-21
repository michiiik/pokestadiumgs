#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1900C0/func_8821CE40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1900C0/func_8821D308.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1900C0/func_8821D3FC.s")

/* mkdraft:func_8821D550 begin */
extern s32 func_80001FF0(void);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern void func_8821D3FC(void);
extern f32 D_8823416C;

void func_8821D550(void) {
    u16 count;
    s32 i;
    count = (u16)((f32)func_80001FF0() * D_8823416C / 2);
    StageFade_StartFromOpaque(count);
    if (count != 0) {
        i = 0;
        do {
            func_80064D28();
            func_8821D3FC();
            i++;
        } while (i != count);
    }
}
/* mkdraft:func_8821D550 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1900C0/func_8821D64C.s")

/* mkdraft:func_8821D74C begin */
extern s32 func_80001FF0(void);
extern void StageFade_StartFromTransparent(s32);
extern void func_80064D28(void);
extern void func_8821D3FC(void);
extern f32 D_88234188;

void func_8821D74C(void) {
    u16 count;
    s32 i;
    count = (u16)((f32)func_80001FF0() * D_88234188 / 2);
    StageFade_StartFromTransparent(count);
    if (count != 0) {
        i = 0;
        do {
            func_80064D28();
            func_8821D3FC();
            i++;
        } while (i != count);
    }
}
/* mkdraft:func_8821D74C end */

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

M2C_UNK Font_EnableLineBreak();                     /* extern */
M2C_UNK Gfx_FreeDisplayListBuffers();               /* extern */
M2C_UNK Gfx_InitDisplayListBuffers(M2C_UNK, M2C_UNK); /* extern */
s32 func_800082E0(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_80008514(s32);                         /* extern */
M2C_UNK func_80008574();                            /* extern */
s32 func_80047588(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_80047610();                            /* extern */
M2C_UNK func_8004C09C(M2C_UNK);                     /* extern */
M2C_UNK func_8004C398();                            /* extern */
M2C_UNK func_8821CE40(M2C_UNK);                     /* extern */
M2C_UNK func_8821D64C();                            /* extern */
M2C_UNK main_pool_pop_state(M2C_UNK);               /* extern */
M2C_UNK main_pool_push_state(M2C_UNK);              /* extern */
extern s32 D_8800687C;

s32 func_8821D848(s32 arg0, M2C_UNK arg1) {
    s32 sp24;

    main_pool_push_state(0x50435445);
    Gfx_InitDisplayListBuffers(0x1A000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(0xB);
    D_8800687C = func_80047588(0x1C, 0);
    Font_EnableLineBreak();
    func_8821CE40(6);
    func_80008514(sp24);
    func_8821D550();
    func_8821D64C();
    func_8821D74C();
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x50435445);
    return 7;
}
#endif
