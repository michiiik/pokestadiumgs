#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0BB40.s")

extern s32 D_8AF26A20;
extern s8 *D_8AF2E8E8;
extern s8 *D_8AF2E8F0;
extern s8 *D_8AF2E8F4;
void func_8AF0BBF0(void *arg0) {
    sprintf(D_8AF26A20 + 0x300, D_8AF2E8E8);
    sprintf(D_8AF26A20 + 0x400, D_8AF2E8E8);
    sprintf(D_8AF26A20 + 0x700, D_8AF2E8E8);
    sprintf(D_8AF26A20 + 0x800, D_8AF2E8E8);
    sprintf(D_8AF26A20 + 0x900, D_8AF2E8E8);
    if ((*(u8 *)((u8 *)(arg0) + (0x10))) == 0) {
        sprintf(D_8AF26A20 + 0x500, D_8AF2E8E8);
    } else {
        sprintf(D_8AF26A20 + 0x500, D_8AF2E8F0);
    }
    if ((*(u8 *)((u8 *)(arg0) + (0x11))) == 0) {
        sprintf(D_8AF26A20 + 0x600, D_8AF2E8E8);
    } else {
        sprintf(D_8AF26A20 + 0x600, D_8AF2E8F0);
    }
    if ((*(u8 *)((u8 *)(arg0) + (0x12))) == 0) {
        sprintf(D_8AF26A20 + 0xA00, D_8AF2E8E8);
        return;
    }
    sprintf(D_8AF26A20 + 0xA00, D_8AF2E8F4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0BD2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0C1D8.s")

s32 func_8AF0C5BC(s16 arg0, s16 arg1) {
    s32 var_v1;

    var_v1 = 1;
    if ((arg0 == 0x10) && (arg1 == 0xD3)) {
        var_v1 = 0;
    }
    if ((arg0 == 0x2E) && (arg1 == 0xE6)) {
        var_v1 = 0;
    }
    if ((arg0 == 0x2B) && (arg1 == 0xCC)) {
        var_v1 = 0;
    }
    if ((arg0 == 0x53) && (arg1 == 0xD3)) {
        var_v1 = 0;
    }
    if ((arg0 == 0x78) && (arg1 == 0x3E)) {
        var_v1 = 0;
    }
    if ((arg0 == 0x78) && (arg1 == 0x70)) {
        var_v1 = 0;
    }
    if ((arg0 == 0x78) && (arg1 == 0x30)) {
        var_v1 = 0;
    }
    if ((arg0 == 0x8E) && (arg1 == 0xD3)) {
        var_v1 = 0;
    }
    if ((arg0 == 0x8F) && (arg1 == 0xCC)) {
        var_v1 = 0;
    }
    if ((arg0 == 1) && (arg1 == 0xCC)) {
        var_v1 = 0;
    }
    if ((arg0 == 0xEE) && (arg1 == 0x8E)) {
        var_v1 = 0;
    }
    if ((arg0 == 0x30) && (arg1 == 0xCA)) {
        var_v1 = 0;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0C6F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0C758.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0C7C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0C96C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0CA00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0CE6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0D29C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0D398.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0D704.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0D7C8.s")

extern void func_8AF00130(s32);
extern s16 D_8AF2E894;
extern s16 D_8AF2E896;
extern s16 D_8AF2E89A;
extern void *D_8AF2E8A4;
extern s16 D_8AF2ECF8;
extern s16 D_8AF2ECFA;
void func_8AF0E084(void) {
    func_8AF00130(1);
    D_8AF2ECF8 = 0;
    D_8AF2E894 = (*(s16 *)((u8 *)(D_8AF2E8A4) + (8)));
    D_8AF2E896 = (*(s16 *)((u8 *)(D_8AF2E8A4) + (0xA)));
    D_8AF2E89A = D_8AF2ECFA;
}

extern void *D_8AF2E8A8;
extern s16 D_8AF2ECFC;
void func_8AF0E0D8(void) {
    func_8AF00130(1);
    D_8AF2ECF8 = 1;
    D_8AF2E894 = (*(s16 *)((u8 *)(D_8AF2E8A8) + (8)));
    D_8AF2E896 = (*(s16 *)((u8 *)(D_8AF2E8A8) + (0xA)));
    D_8AF2E89A = D_8AF2ECFC;
}

extern s16 D_8AF2E898;
extern void *D_8AF2E8AC;
extern s16 D_8AF2ECFE;
void func_8AF0E130(void) {
    func_8AF00130(1);
    D_8AF2ECF8 = 2;
    D_8AF2E894 = (*(s16 *)((u8 *)(D_8AF2E8AC) + (8)));
    D_8AF2E896 = (*(s16 *)((u8 *)(D_8AF2E8AC) + (0xA)));
    D_8AF2E898 = 0;
    D_8AF2E89A = D_8AF2ECFE;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0E190.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F9DB0/func_8AF0E838.s")
#endif
