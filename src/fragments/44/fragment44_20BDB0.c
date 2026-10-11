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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20BDB0/func_8AF1DC14.s")

extern u8 D_8AF37F38[]; extern s32 D_8AF27938; void func_8AF1DCA8(void) { _bzero(D_8AF37F38, 0xE); D_8AF27938 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20BDB0/func_8AF1DCD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20BDB0/func_8AF1E034.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20BDB0/func_8AF1E1F4.s")
#endif
