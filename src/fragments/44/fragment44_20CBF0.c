#include "global.h"


#ifdef VERSION_US
typedef struct {
    u32 words[0x52C / 4];
} Snapshot_8AF1E9D4;
extern Snapshot_8AF1E9D4 *D_8AF27960;
extern Snapshot_8AF1E9D4 D_8AF388C0;
extern s16 D_8AF3779A;
extern s16 D_8AF388BA;
extern s16 D_8AF27964;
void func_8AF1E980(void) {
    *D_8AF27960 = D_8AF388C0;
    D_8AF3779A = D_8AF388BA;
}
void func_8AF1E9D4(void) {
    D_8AF388C0 = *D_8AF27960;
    D_8AF388BA = D_8AF3779A;
    D_8AF27964 = 1;
}

typedef struct Payload_8AF1EA34 {
    u32 words[0x504 / 4];
} Payload_8AF1EA34;
void func_8AF1EA34(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                    u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10,
                    s32 arg11, s32 arg12, const Payload_8AF1EA34 *arg13) {
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
    *(Payload_8AF1EA34 *)(arg0 + 0x28) = *arg13;
}

extern u8 D_8AF39190[]; extern s32 D_8AF27968; void func_8AF1EAC8(void) { _bzero(D_8AF39190, 0xE); D_8AF27968 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20CBF0/func_8AF1EAF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20CBF0/func_8AF1EEA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20CBF0/func_8AF1F038.s")
#endif
