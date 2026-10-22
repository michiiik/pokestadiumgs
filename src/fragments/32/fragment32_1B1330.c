#include "global.h"


#ifdef VERSION_US
extern void func_8004300C();
extern void func_88600020();
extern void func_88600074();
extern void func_88004FF0();
extern u16 D_88308934;
extern u8 D_88308E06[];
extern u8 D_88308E09[];
extern s8 D_88308E04;
void func_88300020(s32 arg0, s32 arg1) { func_8004300C(arg0); func_88600020(arg1); func_88600074(arg0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88300054.s")

extern void *D_88308DF0;
extern u16 D_88308DFA;
extern s32 func_886000F0(u16);
extern s32 func_80042FBC(void *, s32);

extern u16 D_88308DF8[];
void func_88300230(u16 species) {
    if (func_886000F0(species) != 0) {
        if (species != D_88308DF8[0]) {
            if (func_80042FBC(D_88308DF0, species) != 0) {
                D_88308DF8[0] = species;
            }
        }
    } else {
        D_88308DFA = D_88308DF8[0] = species;
    }
}

s32 func_8004C4B0(s32 value);
extern void func_8004C8C0();
void func_883002B8(void) {
    func_8004C4B0(1);
    func_8004C4B0(2);
    func_8004C4B0(3);
    func_8004C4B0((s32) D_88308934);
    func_8004C8C0(0x14C);
    func_88004FF0(0x3B);
}

void func_88300304(void) { func_8004C8C0(155); func_8004C8C0(265); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_8830032C.s")

extern void func_88306404(s32);
void func_883004E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 != 0) {
        func_88306404(0);
    }
    if (arg1 != 0) {
        func_88306404(1);
    }
    if (arg2 != 0) {
        func_88306404(2);
    }
    if (arg3 != 0) {
        func_88306404(3);
    }
}

s32 func_88300550(void) {
    s32 index;

    index = 0;
    do {
        if (D_88308E06[index] != 0) {
            return 1;
        }
        index++;
    } while (D_88308E09 != &D_88308E06[index]);
    return 0;
}

void func_8830058C(u8 value) {
    s32 index;

    index = 0;
    do {
        D_88308E06[index] = value;
        index++;
    } while (D_88308E09 != &D_88308E06[index]);
}

s32 func_8004C990(s32, s32);
extern void func_8004D1FC(s32);
extern void func_80044270(s32,s32,s32,s32,s32,s32,s32,s32,s32);
void func_883005B8(s32 arg0) {
    func_8004D1FC(func_8004C990(0x108, arg0 + 1));
    func_80044270((s32) (s16) ((arg0 * 0x3C) + 0x43), 0xD5, 0x3C, 0x3E, -0x10, -0x10, 0x400, 0x400, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88300640.s")

extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern void func_8004D19C(s32, s32, s32, s32, s32);
extern s8 D_88308DFF;
extern u8 D_88308E00;
void func_8830088C(void) {
    gDPPipeSync(D_800D0510++);
    gDPSetCombine(D_800D0510++, 0x309661, 0x552EFF7F);
    gDPSetPrimColor(D_800D0510++, 0, 0, 0xA0, 0xA0, 0x96, 0xFF);
    gDPSetEnvColor(D_800D0510++, 0x0A, 0x0A, 0x0A, 0xFF);
    func_8004D19C(0x1FA, 0x16E, func_8004C990(0x9B, D_88308DFF), 0, 0);
    if (D_88308E00 > 0) {
        D_88308DFF += 2;
    } else {
        D_88308DFF += 1;
    }
    if (D_88308DFF >= 0xF) {
        D_88308DFF -= 0xF;
    }
}

extern u8 *func_8004CA60(u8 *);
extern void func_800459AC(u8 *, u8, u8, u16, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 func_8004C990(s32, s32);
extern void func_8004D19C(s32, s32, s32, s32, s32);
extern s32 func_8830602C(void);
extern void func_8830639C(void);
extern void func_8830610C(s16, s16, u16, u16);
extern u8 *D_88308938;
extern u8 D_88308E0F;
extern s16 D_88308F10;
void func_8830099C(void) {
    func_800459AC(
        func_8004CA60(D_88308938),
        D_88308938[4],
        D_88308938[5],
        *(u16 *)D_88308938,
        *(u16 *)(D_88308938 + 2),
        1, 0, 1, 1, 3, 3, 0, 0
    );
    if (func_8830602C() != 0) {
        func_8830639C();
    }
    if (D_88308E0F != 0) {
        func_8830610C(0x11E, 0x3A, 0x13, 0xDE);
        func_8004D19C(0x123, D_88308F10, func_8004C990(0x10B, 0), 0, 0);
    }
}

s32 func_88300A78(void) { s32 value = D_88308E04; s32 result; if (value < 5) { result = value & 0xFF; } else { result = (8 - value) & 0xFF; } D_88308E04 = value + 1; if (D_88308E04 >= 8) { D_88308E04 = 0; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88300AC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88300B48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88301C00.s")

/* mkdraft:func_88304E60 begin */
extern s32 func_80001FF0(void);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern void func_88301C00(s32);
extern f32 D_88308920;

void func_88304E60(void) {
    u16 count;
    s32 i;
    count = (u16)((f32)func_80001FF0() * D_88308920 / 2);
    StageFade_StartFromOpaque(count);
    if (count != 0) {
        i = 0;
        do {
            func_80064D28();
            func_88301C00(0);
            i++;
        } while (i != count);
    }
}
/* mkdraft:func_88304E60 end */

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

M2C_UNK func_88300B48();                            /* extern */
extern s32 D_88006860;
extern u8 *D_88308DE8;
extern s32 D_886017AC;

void func_88304F5C(void) {
    D_886017AC = 1;
    M2C_FIELD(D_88308DF0, u16 *, 0) = (u16) (M2C_FIELD(D_88308DF0, u16 *, 0) | 4);
    M2C_FIELD(D_88308DE8, u16 *, 0) = (u16) (M2C_FIELD(D_88308DE8, u16 *, 0) | 4);
    M2C_FIELD(D_88308DE8, u16 *, 0) = (u16) (M2C_FIELD(D_88308DE8, u16 *, 0) | 2);
    M2C_FIELD(M2C_FIELD(D_88308DF0, u8 **, 0x1C), s32 *, 0x4C) = 0x10000;
    M2C_FIELD(M2C_FIELD(D_88308DE8, u8 **, 0x1C), s32 *, 0x4C) = 0x10000;
    if (D_88006860 == 1) {
        do {
            func_80064D28();
            func_88300B48();
            func_88301C00(1);
        } while (D_88006860 == 1);
    }
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_88305020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B1330/func_883051E4.s")

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
M2C_UNK Util_Free(s32);                             /* extern */
s32 func_800082E0(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_80008514(s32);                         /* extern */
M2C_UNK func_80008574();                            /* extern */
M2C_UNK func_8002602C();                            /* extern */
s32 func_80047588(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_80047610();                            /* extern */
M2C_UNK func_8004C09C(M2C_UNK);                     /* extern */
M2C_UNK func_8004C398();                            /* extern */
void func_88304F5C(void);
M2C_UNK func_88305020();                            /* extern */
M2C_UNK func_883051E4(s32, s32);                    /* extern */
M2C_UNK main_pool_pop_state(M2C_UNK);               /* extern */
M2C_UNK main_pool_push_state(M2C_UNK);              /* extern */
extern s32 D_80128C60;
extern s32 D_88006860;
extern s32 D_8800687C;
extern s32 D_88601890;
extern s32 D_88601898;

s32 func_883059F0(s32 arg0, s32 arg1) {
    s32 sp24;
    s32 sp20;

    main_pool_push_state(0x424F4F4B);
    Gfx_InitDisplayListBuffers(0x14000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(7);
    D_8800687C = func_80047588(0x1C, 0);
    Font_EnableLineBreak();
    func_883051E4(arg0, arg1);
    func_80008514(sp24);
    func_88304E60();
    func_88304F5C();
    func_88305020();
    func_80008574();
    main_pool_pop_state(0x70617274);
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    if (D_88006860 == 7) {
        Util_Free(D_88601898);
        func_8002602C();
        Util_Free(D_88601890);
    }
    sp20 = (s32) *D_88308DF8;
    main_pool_pop_state(0x424F4F4B);
    D_80128C60 = D_88006860;
    return sp20;
}
#endif
