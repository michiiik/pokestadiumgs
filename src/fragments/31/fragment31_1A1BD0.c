#include "global.h"


#ifdef VERSION_US
extern u8 **D_88234970;
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

s32 MainPool_AllocAligned(s32, s32, M2C_UNK);       /* extern */
s32 MainPool_AllocState(s32, M2C_UNK);              /* extern */
M2C_UNK MainPool_FinalizeAllocation(s32);           /* extern */
u8 **Util_Malloc(M2C_UNK);                          /* extern */
M2C_UNK func_8004C8C0(M2C_UNK);                     /* extern */
s32 func_8004C990(M2C_UNK, M2C_UNK);                /* extern */
s8 func_800532C4(M2C_UNK);                          /* extern */
s32 func_8005CAA4(M2C_UNK);                         /* extern */
s32 main_pool_get_available();                      /* extern */
M2C_UNK main_pool_push_state(M2C_UNK);              /* extern */

void func_8822E950(void) {
    s32 sp24;
    s32 sp20;
    s32 temp_v0;

    main_pool_push_state(0x50495550);
    D_88234970 = Util_Malloc(0x30);
    sp20 = func_8005CAA4(0x21);
    if (func_800532C4(0x11) < sp20) {
        M2C_FIELD(D_88234970, s8 *, 0x1C) = func_8005CAA4(0x21);
    } else {
        M2C_FIELD(D_88234970, s8 *, 0x1C) = func_800532C4(0x11);
    }
    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    sp24 = temp_v0;
    M2C_FIELD(D_88234970, s32 *, 0xC) = MainPool_AllocAligned(temp_v0, (u8) M2C_FIELD(D_88234970, s8 *, 0x1C) * 0xC80, 8);
    MainPool_FinalizeAllocation(sp24);
    func_8004C8C0(0x9A);
    M2C_FIELD(D_88234970, s32 *, 0x10) = func_8004C990(0x9A, 0);
    func_8004C8C0(0xF1);
    M2C_FIELD(D_88234970, s32 *, 0x14) = func_8004C990(0xF1, 0);
    func_8004C8C0(0xF3);
    M2C_FIELD(D_88234970, s32 *, 0x18) = func_8004C990(0xF3, 0);
}
extern void Util_Free(void *);
extern void main_pool_pop_state(s32);
extern u8 **D_88234970;
void func_8822EA80(void) {
    Util_Free(*(volatile void **)(&D_88234970));
    main_pool_pop_state(0x50495550);
}


void func_8822EAB0(void) {
    *(u32 *)(*D_88234970 + 0x30) = 0;
}


void func_8822EAC4(void) {
    *(u32 *)(*D_88234970 + 0x30) = 1;
}

extern void func_8000612C();

void func_8822EADC(void) {
    func_8000612C();
    (*(s32 *)((u8 *)(*D_88234970) + (0x2C))) = 1;
}

s32 func_88802DCC(s32, s32, void (*)(), void (*)(), void (*)(), s32 *, s32, s32);
extern u8 func_882313A4;

void func_8822EB10(s32 arg0) {
    func_88802DCC(0, arg0, func_8822EAB0, func_8822EADC, func_8822EAC4, &func_882313A4, 0, 1);
    (*(s32 *)((u8 *)(*D_88234970) + (0x2C))) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_8822EB78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_8822EDA8.s")

extern s32 D_880068B8;

void func_8822FA0C(void) {
    func_8000612C();
    D_880068B8 = 0;
}

extern void func_88001900();
extern s32 D_880068B4;

void func_8822FA30(void) {
    func_88001900();
    D_880068B4 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_8822FA58.s")

extern void Input_SetRepeatController(s32);
extern s32 D_80087200;

void func_8822FF80(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void func_88211168(s32, s32);
extern u32 D_88234980;
void func_8822FFA8(void) {
    if ((*(s32 *)((u8 *)(D_88234980) + (0x5C))) != 0) {
        func_88001900();
    } else {
        func_88211168(1 - (*(s16 *)((u8 *)(D_88234980) + (0x48))), 0);
    }
    D_880068B4 = 1;
    Util_Free((void *) D_88234980);
}

extern void func_88004990(u8 arg0, s32 arg1);
void func_88230010(void) {
    func_88004990(**(u8 **)D_88234980, 0);
    D_880068B8 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_88230048.s")

extern void func_8821D930(s32);
void func_882300E4(void) {
    func_8821D930(D_88234980 + 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_8823010C.s")
#endif
