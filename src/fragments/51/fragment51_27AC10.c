#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27AC10/func_86304DF0.s")

void func_8630500C(void *a) {
    func_86305C48(
        *(s32 *)((u8 *)a + 0xC),
        (u8 *)a + 0x80,
        *(s32 *)((u8 *)a + 0x74)
    );
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27AC10/func_86305038.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27AC10/func_86305144.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27AC10/func_86305448.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27AC10/func_8630557C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27AC10/func_86305694.s")

void func_86305790(void) {}
void func_86305790_padding(void) {}

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

M2C_UNK func_87D0059C(u8 *, u8 *);              /* extern */
M2C_UNK func_87D00648(u8 *, u8 *, u8 *);      /* extern */

void func_863057A0(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, f32 arg4, f32 arg5) {
    M2C_FIELD(arg0, f32 *, 0) = (f32) (M2C_FIELD(arg3, f32 *, 0) - M2C_FIELD(arg2, f32 *, 0));
    M2C_FIELD(arg0, f32 *, 4) = (f32) (M2C_FIELD(arg3, f32 *, 4) - M2C_FIELD(arg2, f32 *, 4));
    if ((M2C_FIELD(arg0, f32 *, 0) != 0.0f) || (M2C_FIELD(arg0, f32 *, 4) != 0.0f)) {
        func_87D00648(arg1, arg2, arg3);
        func_87D0059C(arg1, arg1 + 4);
        return;
    }
    M2C_FIELD(arg1, f32 *, 0) = arg4;
    M2C_FIELD(arg1, f32 *, 4) = arg5;
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27AC10/func_86305840.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27AC10/func_86305A04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27AC10/func_86305B44.s")
#endif
