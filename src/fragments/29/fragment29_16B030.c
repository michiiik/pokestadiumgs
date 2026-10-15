#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D0510;
extern Gfx D_88006030[];
extern u8 D_8800EF30[];
extern s16 D_8800EF32;
extern s32 func_88000080(void *);
extern s32 func_8004C8C0();
extern s32 func_8004C990(s32, s32);
extern s32 D_8800EF3C;
void func_88004FF0(s32 archive) {
    s32 entry;
    func_8004C8C0(archive);
    switch (archive) {
    case 0x3A:
        entry = 0;
        break;
    case 0x3B:
        entry = 0;
        break;
    }
    D_8800EF3C = func_8004C990(archive, entry);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_16B030/func_88005048.s")

void func_8800528C(s32 mode) {
    gSPDisplayList(D_800D0510++, D_88006030);
    if (mode) {
        gDPSetRenderMode(D_800D0510++, 0x00504340, 0);
        gDPSetEnvColor(D_800D0510++, 150, D_8800EF32, 255, 128);
    } else {
        gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
        gDPSetEnvColor(D_800D0510++, 150, func_88000080(D_8800EF30), 255, 255);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_16B030/func_88005390.s")

extern void func_88005390(s32, s16, s16, void *);

void func_88005714(void *arg0) {
    func_88005390(0, (*(s16 *)((u8 *)(arg0) + (4))), (*(s16 *)((u8 *)(arg0) + (6))), arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_16B030/func_88005740.s")
#endif
