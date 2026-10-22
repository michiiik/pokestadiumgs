#include "global.h"


#ifdef VERSION_US
extern u8 **D_87F11768;
void fragment64_main(u8 *arg0) {
    *D_87F11768 = arg0;
}

extern u8 D_87F11770[];
extern u8 D_87F0F5B8[];
extern u8 D_87F11750[];
extern s32 main_pool_get_available(void);
extern u8 *MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(void *);
extern void *process_geo_layout(void *, void *);
extern s32 func_8004C8C0(u16);
extern s32 func_8004C990(s32, s32);
extern s32 func_87F08E3C(void *, s32);
extern void *func_80037E9C(void *, void *);
extern void func_87F0252C(void *, void *, u8 *, s32);

void func_87F00030(void) {
    u8 *var_v0;

    D_87F11768 = (u8 **)D_87F11770;
    *(s32 *)D_87F11768 = 20;
    *(s32 *)((u8 *)D_87F11768 + 4) = *(s32 *)D_87F11768 * 5;
    *(s32 *)((u8 *)D_87F11768 + 8) = 0;
    *(s32 *)((u8 *)D_87F11768 + 12) = 0;
    var_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    *(void **)((u8 *)D_87F11768 + 448) = process_geo_layout(var_v0, D_87F0F5B8);
    MainPool_FinalizeAllocation(var_v0);
    func_8004C8C0(360);
    *(s32 *)((u8 *)D_87F11768 + 24) = func_87F08E3C((void *)func_8004C990(360, 0), 0x0F000000);
    *(s32 *)((u8 *)D_87F11768 + 28) = func_87F08E3C((void *)func_8004C990(360, 3), 0x0F000000);
    func_80037E9C(NULL, D_87F11750);
    func_87F0252C(D_87F11750, (u8 *)D_87F11768 + 32, (u8 *)D_87F11768 + 52, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_322C90/func_87F00138.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_322C90/func_87F003F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_322C90/func_87F00534.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_322C90/func_87F005F0.s")

extern void func_87F005F0(f32, f32);
void func_87F00688(void) {
    func_87F005F0(0.0f, 0.0f);
}

u32 func_87F006AC(void) {
    return *(u32 *)((u8 *)D_87F11768 + 0xC);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_322C90/func_87F006BC.s")

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

M2C_UNK func_800495BC(M2C_UNK, M2C_UNK, M2C_UNK *, s32); /* extern */
M2C_UNK func_800496A4(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8004972C(M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_800498C4();                            /* extern */
extern M2C_UNK D_87F11430;
extern M2C_UNK D_87F11434;

void func_87F0085C(void) {
    s32 temp_a3;

    if (!(M2C_FIELD(D_87F11768, s32 *, 8) & 1) && (M2C_FIELD(D_87F11768, s32 *, 0x10) < 4)) {
        func_800498C4();
        func_800496A4(8, 0);
        func_8004972C(0xFF, 0xFF, 0, (s32) (M2C_FIELD(D_87F11768, f32 *, 0x14) * 255.0f));
        temp_a3 = M2C_FIELD(D_87F11768, s32 *, 0x10);
        if (temp_a3 == 0) {
            func_800495BC(0x80, 0x6E, &D_87F11430, temp_a3);
            return;
        }
        func_800495BC(0x90, 0x6E, &D_87F11434, temp_a3);
    }
}
#endif
