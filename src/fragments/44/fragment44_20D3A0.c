#include "global.h"


#ifdef VERSION_US
extern void func_800504BC(s16 *);
extern void func_8AC01160(s16, s16, s16, s16);
extern s16 D_8AF39228;
typedef struct {
    u8 pad0[4];
    s32 type;
    s16 x;
    s16 y;
    s16 z;
    s16 w;
} Func8AF1F130Arg;
s32 func_8AF1F130(s32 arg0, Func8AF1F130Arg *arg1) {
    struct { s32 pad[2]; s16 angles[2]; } scratch;
    s32 type;
    s32 var_v1;

    var_v1 = 0;
    if ((arg0 != 0) && (arg0 == 1)) {
        type = arg1->type;
        if ((type == 0x6B726F31) && (D_8AF39228 == 1)) {
            var_v1 = 1;
        }
        if ((type == 0x6B726F32) && (D_8AF39228 == 0)) {
            var_v1 = 1;
        }
        if (var_v1 != 0) {
            func_800504BC(scratch.angles);
            {
                s16 x;
                s16 y;
                x = scratch.angles[0] + arg1->x;
                y = scratch.angles[1] + arg1->y;
                func_8AC01160(x, y, arg1->z, arg1->w);
            }
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF1F1F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF1F294.s")

typedef struct {
    u32 unk_00[321];
} unk_func_8AF1F378;

void func_8AF1F378(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10,
                   s32 arg11, s32 arg12, const unk_func_8AF1F378 *arg13) {
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
    *(unk_func_8AF1F378 *)(arg0 + 0x28) = *arg13;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF1F40C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF1F490.s")

s32 func_8AF1F514(s16 arg0) {
    s32 var_v1 = 0;

    switch (arg0) {
        case 29:
        case 30:
        case 31:
        case 113:
        case 115:
        case 124:
        case 238:
        case 241:
        case 242:
            var_v1 = 1;
            break;
    }
    return var_v1;
}

s32 func_8AF1F590(s16 arg0) {
    s32 var_v1;

    var_v1 = 0;
    if ((arg0 == 0x20) || (arg0 == 0x21) || (arg0 == 0x22) || (arg0 == 0x6A) || (arg0 == 0x6B) || (arg0 == 0x80) || (arg0 == 0xEC) || (arg0 == 0xED)) {
        var_v1 = 1;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF1F5F0.s")

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

s16 *func_8AF01718(s16 *, s32);                      /* extern */
s32 func_80063804(u8);                               /* extern */
u8 func_8AF01654(u8);                                /* extern */
s32 func_8AC00FAC(u8);                               /* extern */
s32 func_8AF1E2F0(u8, u8);                           /* extern */
extern s16 *D_8AF2BA90[];
extern s16 D_8AF3779A;
extern s32 D_8AF2D302;
extern s16 D_8AF39230[];

void func_8AF1F7B8(void) {
    s16 *var_s4;
    s32 var_s0;
    s32 r;
    s16 temp_v0;
    u8 temp_s2;
    s32 temp_s3;

    func_8AF01718(D_8AF2BA90[0], D_8AF3779A);
    var_s4 = &D_8AF39230;
    for (var_s0 = 1; var_s0 != 0xFC; var_s0++) {
        r = func_80063804(var_s0);
        temp_v0 = r;
        temp_s2 = func_8AF01654(r & 0xFF);
        temp_s3 = func_8AC00FAC(M2C_FIELD(&D_8AF2D302, u8 *, 1)) & 0xFF;
        r = func_8AC00FAC(temp_v0);
        if (temp_s3 == r) {
            if (func_8AF1E2F0(temp_s2, 0xF) == 0) {
                *var_s4 = temp_v0;
                var_s4++;
            }
        }
    }
    *var_s4 = -1;
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

s16 *func_8AF01718(s16 *, s32);                      /* extern */
s32 func_80063804(u8);                               /* extern */
u8 func_8AF01654(u8);                                /* extern */
s32 func_8AC00FAC(u8);                               /* extern */
s32 func_8AF1E2F0(u8, u8);                           /* extern */
extern s16 *D_8AF2BA90[];
extern s16 D_8AF3779A;
extern s32 D_8AF2D302;
extern s16 D_8AF27974[];

void func_8AF1F898(void) {
    s16 *var_s4;
    s32 var_s0;
    s32 r;
    s16 temp_v0;
    u8 temp_s2;
    s32 temp_s3;

    func_8AF01718(D_8AF2BA90[0], D_8AF3779A);
    var_s4 = &D_8AF27974;
    for (var_s0 = 1; var_s0 != 0xFC; var_s0++) {
        r = func_80063804(var_s0);
        temp_v0 = r;
        temp_s2 = func_8AF01654(r & 0xFF);
        temp_s3 = func_8AC00FAC(M2C_FIELD(&D_8AF2D302, u8 *, 1)) & 0xFF;
        r = func_8AC00FAC(temp_v0);
        if (temp_s3 == r) {
            if (func_8AF1E2F0(temp_s2, 0xF) == 0) {
                *var_s4 = temp_v0;
                var_s4++;
            }
        }
    }
    *var_s4 = -1;
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF1F978.s")

extern void func_8AC01064(s32);
void func_8AF1FC80(void) {
    func_8AC01064(0x4649434E);
  }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF1FCA4.s")

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
M2C_UNK func_8AF1F978();                            /* extern */
extern u8 *D_8AF263C0;
extern u8 *D_8AF27970;
extern u16 D_8AF2BDC6;
extern s16 D_8AF39430;
extern M2C_UNK D_8AF39498;
extern M2C_UNK D_8AF39510;
extern M2C_UNK D_8AF39588;

s16 func_8AF2078C(void) {
    s16 sp1E;
    u8 *sp18;
    u16 temp_v1;

    sp1E = 0x1D;
    sp18 = D_8AF27970;
    if ((func_8AF0326C(D_8AF27970) == 0) && (M2C_FIELD(sp18, s16 *, 0x3A) == 0)) {
        temp_v1 = M2C_FIELD(D_8AF263C0, u16 *, 8);
        if (temp_v1 & 0x4000) {
            func_8AF00130(3);
            func_8AF1FC80();
            sp1E = 0x1C;
        } else if (D_8AF39430 == 0) {
            switch (D_8AF39228) {                   /* irregular */
            case 0:
                if (temp_v1 & 0x400) {
                    func_8AF00130(1);
                    D_8AF39228 = 1;
                    func_8AF1FC80();
                    func_8AF1F978();
                }
                break;
            case 1:
                if (temp_v1 & 0x800) {
                    func_8AF00130(1);
                    D_8AF39228 = 0;
                    func_8AF1FC80();
                    func_8AF1F978();
                }
                break;
            }
        }
    }
    func_8AC0686C(&D_8AF39588, M2C_FIELD(sp18, s16 *, 0x38));
    func_8AC0619C(&D_8AF39498, D_8AF2BDC6);
    func_8AC06220(&D_8AF39510, D_8AF2BDC6);
    return sp1E;
}
void func_8AC00738(void);                           /* extern */
void func_8AC05F00(M2C_UNK *);                       /* extern */
s32 func_8AC0665C(M2C_UNK *, s16);                  /* extern */
s32 func_8AC0672C(M2C_UNK *, s16);                  /* extern */
extern M2C_UNK D_8AF39498;
extern M2C_UNK D_8AF39510;
extern M2C_UNK D_8AF39588;

void func_8AF208D0(void) {
    u8 *sp24;
    void *sp1C;

    sp24 = D_8AF27970;
    sp1C = sp24 + 0x28;
    func_8AC00738();
    if (func_8AC0665C(&D_8AF39588, M2C_FIELD(sp1C, s16 *, 0x10)) != 0) {
        func_8AC05F00(&D_8AF39498);
    }
    if (func_8AC0672C(&D_8AF39588, M2C_FIELD(sp1C, s16 *, 0x10)) != 0) {
        func_8AC05F00(&D_8AF39510);
    }
}
#endif
