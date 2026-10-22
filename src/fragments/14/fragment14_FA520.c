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

/* mkdraft:func_813029F0 begin */
s32 Asset_LoadToSegment(u32, s32 *, s32 *, s32);
s32 Gfx_FreeDisplayListBuffers();
s32 Gfx_InitDisplayListBuffers(s32, s32);
s32 StageLoader_WaitForRetrace();
s32 _bzero(s32 *, s32);
s32 func_800082E0(s32, s32, s32, s32, s32, s32);
s32 func_80008494();
s32 func_80008514(s32);
s32 func_80008574();
s32 func_80008624();
s32 func_80047588(s32, s32);
s32 func_8004C09C(s32);
s32 func_8004C398();
s32 func_8130251C();
s32 func_81302854();
s32 func_81302920(s32);
s32 func_816031F4();
s32 main_pool_pop_state(s32);
s32 main_pool_push_state(s32);
extern s32 D_1000000;
extern s32 D_446E30;
extern s32 D_447D00;
extern s32 D_81311D50;
extern s32 D_8133197C;
extern s32 D_81331984;

s32 func_813029F0(s32 arg0, s32 arg1) {
    s32 sp24;
    s32 temp_v0;

    _bzero(&D_81317800, 0x1A188);
    D_8133197C = arg1;
    main_pool_push_state(0x50504B50);
    temp_v0 = func_80008494();
    D_81311D50 = temp_v0 == 0;
    sp24 = temp_v0;
    if (D_81311D50 != 0) {
        Gfx_InitDisplayListBuffers(0x1D800, 0);
        sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    }
    func_8004C09C(0xF);
    D_81331970 = func_81302920(D_8133197C);
    func_80047588(0x1C, 0);
    func_816031F4();
    Asset_LoadToSegment((u32) ((s32) &D_1000000 & 0x0F000000) >> 0x18, &D_446E30, &D_447D00, 0);
    func_8130251C();
    if (D_81311D50 != 0) {
        func_80008514(sp24);
    } else {
        func_80008624();
    }
    func_81302854();
    if (D_81311D50 != 0) {
        func_80008574();
    } else {
        StageLoader_WaitForRetrace();
    }
    func_8004C398();
    if (D_81311D50 != 0) {
        Gfx_FreeDisplayListBuffers();
    }
    main_pool_pop_state(0x50504354);
    main_pool_pop_state(0x50504B50);
    return D_81331984 == 0 ? 1 : 0;
}
/* mkdraft:func_813029F0 end */
#endif
