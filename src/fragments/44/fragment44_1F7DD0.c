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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F7DD0/func_8AF09C34.s")

extern u8 D_8AF2D258[]; extern s32 D_8AF26938; void func_8AF09CC8(void) { _bzero(D_8AF2D258, 0xE); D_8AF26938 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F7DD0/func_8AF09CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F7DD0/func_8AF0A0B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F7DD0/func_8AF0A244.s")
#endif
