#include "global.h"


#ifdef VERSION_US
/* mkdraft:func_8AF20950 begin */
extern void func_800504BC(s16 *);
extern void func_8AC007B8(s32, s32, s32, s32);
extern void func_8AF02F18(void *);
extern void func_8AC00738(void);

s32 func_8AF20950(s32 arg0, u8 *arg1) {
    struct { s32 pad[2]; s16 angles[2]; } scratch;
    s32 *ptr;
    s16 x;
    s16 y;
    s16 z;
    s16 w;

    ptr = *(s32 **)(arg1 + 0x20);
    if ((arg0 != 0) && (arg0 == 1)) {
        func_800504BC(scratch.angles);
        x = *(s16 *)(arg1 + 8) + scratch.angles[0];
        y = *(s16 *)(arg1 + 0xA) + scratch.angles[1];
        z = *(s16 *)(arg1 + 0xC);
        w = *(s16 *)(arg1 + 0xE);
        ptr[2] = x;
        ptr[3] = y;
        func_8AC007B8(x, y, z, w);
        func_8AF02F18(ptr);
        func_8AC00738();
    }
    return 0;
}
/* mkdraft:func_8AF20950 end */

typedef struct {
    u32 unk_00[321];
} unk_func_8AF209E4;

void func_8AF209E4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10,
                   s32 arg11, s32 arg12, const unk_func_8AF209E4 *arg13) {
    *(s32 *)(arg0 + 0x18) = arg1;
    *(s32 *)(arg0 + 8) = arg2;
    *(s32 *)(arg0 + 0xC) = arg3;
    *(s32 *)(arg0 + 0x10) = arg4;
    arg0[0x22] = arg5;
    arg0[0x23] = arg6;
    arg0[0x24] = arg7;
    arg0[0x25] = arg8;
    arg0[0x26] = arg9;
    arg0[0x27] = arg10;
    *(s32 *)arg0 = arg11;
    *(s32 *)(arg0 + 0x14) = -1;
    *(s32 *)(arg0 + 0x1C) = arg12;
    *(unk_func_8AF209E4 *)(arg0 + 0x28) = *arg13;
}


#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20EBC0/func_8AF20A78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20EBC0/func_8AF20B7C.s")

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

M2C_UNK func_8AC0619C(M2C_UNK *, u16);              /* extern */
M2C_UNK func_8AC06220(M2C_UNK *, u16);              /* extern */
M2C_UNK func_8AC0686C(M2C_UNK *, s16);              /* extern */
M2C_UNK func_8AF00130(M2C_UNK);                     /* extern */
s32 func_8AF0326C(u8 *);                          /* extern */
extern u8 *D_8AF263C0;
extern u8 *D_8AF279A0;
extern u16 D_8AF2BDC6;
extern M2C_UNK D_8AF39840;
extern M2C_UNK D_8AF398B8;
extern M2C_UNK D_8AF39930;

s16 func_8AF20DB0(void) {
    s16 sp1E;
    u8 *sp18;

    sp1E = 0x1A;
    sp18 = D_8AF279A0;
    if ((func_8AF0326C(D_8AF279A0) == 0) && (M2C_FIELD(D_8AF263C0, u16 *, 8) & 0x4000)) {
        func_8AF00130(3);
        sp1E = 0x18;
    }
    func_8AC0686C(&D_8AF39930, M2C_FIELD(sp18, s16 *, 0x38));
    func_8AC0619C(&D_8AF39840, D_8AF2BDC6);
    func_8AC06220(&D_8AF398B8, D_8AF2BDC6);
    return sp1E;
}
void func_8AC00738(void);                           /* extern */
void func_8AC05F00(M2C_UNK *);                       /* extern */
s32 func_8AC06800(M2C_UNK *, s16);                  /* extern */
s32 func_8AC06834(M2C_UNK *, s16);                  /* extern */
extern M2C_UNK D_8AF39840;
extern M2C_UNK D_8AF398B8;
extern M2C_UNK D_8AF39930;

void func_8AF20E4C(void) {
    u8 *sp24;
    void *sp18;
    void *temp_v0;

    sp24 = D_8AF279A0;
    sp18 = sp24 + 0x28;
    func_8AC00738();
    if (func_8AC06800(&D_8AF39930, M2C_FIELD(sp18, s16 *, 0x10)) != 0) {
        func_8AC05F00(&D_8AF39840);
    }
    if (func_8AC06834(&D_8AF39930, M2C_FIELD(sp18, s16 *, 0x10)) != 0) {
        func_8AC05F00(&D_8AF398B8);
    }
}
#endif
