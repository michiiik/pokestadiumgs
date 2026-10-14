#include "global.h"


#ifdef VERSION_US
typedef struct {
    u32 words[0x52C / 4];
} Snapshot_8AF09B60;

extern Snapshot_8AF09B60 D_8AF2CC38;
extern Snapshot_8AF09B60 *D_8AF26930;
extern s16 D_8AF2CC34;
extern s16 D_8AF2CC36;
extern s16 D_8AF2C9E0;
extern s16 D_8AF2C9E2;

void func_8AF09B60(void) {
    *D_8AF26930 = D_8AF2CC38;
    D_8AF2C9E0 = D_8AF2CC34;
    D_8AF2C9E2 = D_8AF2CC36;
}

extern s16 D_8AF26934;

void func_8AF09BC4(void) {
    D_8AF2CC38 = *D_8AF26930;
    D_8AF2CC34 = D_8AF2C9E0;
    D_8AF2CC36 = D_8AF2C9E2;
    D_8AF26934 = 1;
}

typedef struct Payload_8AF09C34 {
    u32 words[0x504 / 4];
} Payload_8AF09C34;
void func_8AF09C34(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                    u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10,
                    s32 arg11, s32 arg12, const Payload_8AF09C34 *arg13) {
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
    *(Payload_8AF09C34 *)(arg0 + 0x28) = *arg13;
}

extern u8 D_8AF2D258[]; extern s32 D_8AF26938; void func_8AF09CC8(void) { _bzero(D_8AF2D258, 0xE); D_8AF26938 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F7DD0/func_8AF09CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F7DD0/func_8AF0A0B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F7DD0/func_8AF0A244.s")
#endif
