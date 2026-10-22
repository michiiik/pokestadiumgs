#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BD630/func_88500020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BD630/func_885002A0.s")

extern void func_885002A0(s32);
extern void func_8850A0EC(s32);
extern s32 D_8850D6CC;

void func_88500460(s32 arg0) {
    D_8850D6CC = arg0;
    func_885002A0(3);
    func_8850A0EC(arg0);
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

M2C_UNK func_80008648();                            /* extern */
M2C_UNK func_800088DC();                            /* extern */
M2C_UNK func_80049064(M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_800496A4(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_800498C4();                            /* extern */
M2C_UNK func_800499EC();                            /* extern */
s32 func_8004C874(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_88004180();                            /* extern */
M2C_UNK func_8850C998();                            /* extern */
extern s32 D_880068B8;
extern s32 D_8850D670;

void func_88500494(void) {
    func_800088DC();
    if (D_880068B8 != 0) {
        func_8850C998();
        if (D_8850D670 == 1) {
            func_800498C4();
            func_800496A4(0x10, 2);
            func_80049064(0x140, 0x168, 1, func_8004C874(0x34, 0));
            func_800499EC();
        }
    }
    func_88004180();
    func_80008648();
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BD630/func_8850052C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BD630/func_8850089C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BD630/func_885009D0.s")

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
M2C_UNK func_800086A4(M2C_UNK);                     /* extern */
s32 func_80047588(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_80047610();                            /* extern */
M2C_UNK func_8004C09C(M2C_UNK);                     /* extern */
M2C_UNK func_8004C398();                            /* extern */
M2C_UNK func_8850089C();                            /* extern */
M2C_UNK func_885009D0();                            /* extern */
M2C_UNK main_pool_pop_state(M2C_UNK);               /* extern */
M2C_UNK main_pool_push_state(M2C_UNK);              /* extern */
extern s32 D_8800687C;

s32 func_88500C10(s32 arg0, M2C_UNK arg1) {
    s32 sp24;

    main_pool_push_state(0x504D4558);
    Gfx_InitDisplayListBuffers(0x14000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(0xB);
    D_8800687C = func_80047588(0x1C, 0);
    Font_EnableLineBreak();
    func_885009D0();
    func_80008514(sp24);
    func_8850089C();
    func_800086A4(2);
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x504D4558);
    return 7;
}
#endif
