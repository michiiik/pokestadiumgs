#include "global.h"


#ifdef VERSION_US
extern void *D_81331970;
extern void func_81600A34(void *, void *, s32, s32, s32, s32, s32);
void func_81302390(void *arg0) {
    func_81600A34(arg0, D_81331970, 0, 0, 0, 0x280, 0x1E0);
    func_81600A34(arg0, (u8 *)D_81331970 + 2, 0, 0, 0xF0, 0x280, 0xF0);
    func_81600A34(arg0, (u8 *)D_81331970 + 1, 1, 0, 0, 0x280, 0x46);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FA520/func_81302438.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FA520/func_8130251C.s")

extern void *D_81331974;
extern u8 D_81317800[];
extern void BgStage_DrawFrame(void);
extern void func_81302438(void *);
extern void Fragment14_DrawSelectionState(void *, void *);
extern void func_80008648(void);
void func_81302634(void) {
    BgStage_DrawFrame();
    func_81302438(D_81331974);
    Fragment14_DrawSelectionState(D_81317800, D_81331974);
    func_80008648();
}

extern s32 func_8006CBB8(s32);
extern void StageContext_SetClearColor(s32);
void func_8130267C(u8 *arg0) {
    if (*(s16 *)(*(u8 **)(arg0 + 0x940) + 0x34) == 6) {
        s32 result = func_8006CBB8(*(u16 *)(arg0 + 0x952));
        if (result == 0 || result == 1 || result == 2)
            StageContext_SetClearColor(1);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FA520/func_813026D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FA520/func_81302854.s")

extern s32 func_8004D690(s32);
void Fragment14_PreloadSelectionResource(u8 *arg0) {
    u16 message;
    u8 *metadata = *(u8 **)(arg0 + 0x940);
    message = *(u16 *)(metadata + 0x3A);
    switch (*(s16 *)(metadata + 0x34)) {
    case 6:
        switch (func_8006CBB8(*(u16 *)(arg0 + 0x952))) {
        case 0:
            message = 0x1A;
            break;
        case 1:
            message = 0x1B;
            break;
        case 2:
            message = 0xD;
            break;
        }
        break;
    case 0xE:
        message = 0x17;
        break;
    }
    switch (*(u16 *)(arg0 + 0x950) & 0xFF00) {
    case 0x400:
        message = 0xE;
        break;
    case 0x500:
        message = 0x2E;
        break;
    }
    func_8004D690(message);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FA520/func_813029F0.s")
#endif
