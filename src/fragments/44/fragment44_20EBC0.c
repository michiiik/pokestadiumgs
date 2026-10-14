#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20EBC0/func_8AF20950.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20EBC0/func_8AF20DB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20EBC0/func_8AF20E4C.s")
#endif
