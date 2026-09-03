#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_209BD0/func_8AF1B960.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_209BD0/func_8AF1B9C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_209BD0/func_8AF1BA18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_209BD0/func_8AF1BAE8.s")

extern s16 D_8AF27490;
void func_8AF1BB84(s16 arg0) {
    D_8AF27490 = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_209BD0/func_8AF1BB9C.s")

extern void *D_8AF37244;

s32 func_8AF1BED8(void) {
    if ((*(s16 *)((u8 *)(D_8AF37244) + (0xA))) < 0) {
        return 1;
    }
    return 0;
}

extern s32 D_8AF27494;

s32 func_8AF1BF00(void) {
    if (-D_8AF27494 < (*(s16 *)((u8 *)(D_8AF37244) + (0xA)))) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_209BD0/func_8AF1BF38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_209BD0/func_8AF1C31C.s")
#endif
