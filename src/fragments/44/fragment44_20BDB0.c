#include "global.h"


#ifdef VERSION_US
typedef struct { u32 words[0x52C / 4]; } Snapshot_8AF1DB40;
extern Snapshot_8AF1DB40 *D_8AF27930;
extern Snapshot_8AF1DB40 D_8AF37868;
extern s16 D_8AF37860;
extern s16 D_8AF37862;
extern s16 D_8AF37798;
extern s16 D_8AF2C9E2;

void func_8AF1DB40(void) {
    *D_8AF27930 = D_8AF37868;
    D_8AF37798 = D_8AF37860;
    D_8AF2C9E2 = D_8AF37862;
}

extern s16 D_8AF27934;

void func_8AF1DBA4(void) {
    D_8AF37868 = *D_8AF27930;
    D_8AF37860 = D_8AF37798;
    D_8AF37862 = D_8AF2C9E2;
    D_8AF27934 = 1;
}

typedef struct {
    u32 unk_00[321];
} unk_func_8AF1DC14;

void func_8AF1DC14(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10,
                   s32 arg11, s32 arg12, const unk_func_8AF1DC14 *arg13) {
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
    *(unk_func_8AF1DC14 *)(arg0 + 0x28) = *arg13;
}


extern u8 D_8AF37F38[]; extern s32 D_8AF27938; void func_8AF1DCA8(void) { _bzero(D_8AF37F38, 0xE); D_8AF27938 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20BDB0/func_8AF1DCD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20BDB0/func_8AF1E034.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20BDB0/func_8AF1E1F4.s")
#endif
