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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF1F7B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF1F898.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF1F978.s")

extern void func_8AC01064(s32);
void func_8AF1FC80(void) {
    func_8AC01064(0x4649434E);
  }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF1FCA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF2078C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20D3A0/func_8AF208D0.s")
#endif
