#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_201DA0/func_8AF13B30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_201DA0/func_8AF141E8.s")

typedef struct {
    u32 unk_00[321];
} unk_func_8AF145B4;

void func_8AF145B4(u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, u8 arg7,
                   u8 arg8, u8 arg9, u8 arg10, s32 arg11, s32 arg12, const unk_func_8AF145B4* arg13) {
    *(s32*)(arg0 + 24) = arg1;
    *(s32*)(arg0 + 8) = arg2;
    *(s32*)(arg0 + 12) = arg3;
    *(s32*)(arg0 + 16) = arg4;
    arg0[34] = arg5;
    arg0[35] = arg6;
    arg0[36] = arg7;
    arg0[37] = arg8;
    arg0[38] = arg9;
    arg0[39] = arg10;
    *(s32*)arg0 = arg11;
    *(s32*)(arg0 + 20) = -1;
    *(s32*)(arg0 + 28) = arg12;
    *(unk_func_8AF145B4*)(arg0 + 40) = *arg13;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_201DA0/func_8AF14648.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_201DA0/func_8AF14BE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_201DA0/func_8AF14D3C.s")
#endif
