#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20CBF0/func_8AF1E980.s")

typedef struct {
    u32 words[0x52C / 4];
} Snapshot_8AF1E9D4;
extern Snapshot_8AF1E9D4 *D_8AF27960;
extern Snapshot_8AF1E9D4 D_8AF388C0;
extern s16 D_8AF3779A;
extern s16 D_8AF388BA;
extern s16 D_8AF27964;
void func_8AF1E9D4(void) {
    D_8AF388C0 = *D_8AF27960;
    D_8AF388BA = D_8AF3779A;
    D_8AF27964 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20CBF0/func_8AF1EA34.s")

extern u8 D_8AF39190[]; extern s32 D_8AF27968; void func_8AF1EAC8(void) { _bzero(D_8AF39190, 0xE); D_8AF27968 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20CBF0/func_8AF1EAF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20CBF0/func_8AF1EEA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20CBF0/func_8AF1F038.s")
#endif
