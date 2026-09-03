#include "global.h"


#ifdef VERSION_US
extern void func_81600A34(void *, void *, s32, s32, s32, s32, s32);
extern u8 *D_81407BB0;
void func_81400020(s32 arg0) {
    func_81600A34((void *)arg0, D_81407BB0, 0, 0, 0, 0x280, 0x1E0);
    func_81600A34((void *)arg0, D_81407BB0 + 1, 1, 0, 0x1A1, 0x230, 0x3F);
}

extern u8 *D_814077AC;
extern s32 func_81600DA8(void *, void *);
extern void func_81600F0C(void *, s32, s32, s32, s32);
extern void func_814025E8(s32, s32);
void func_81400098(s32 arg0) {
    if (func_81600DA8((void *)arg0, D_81407BB0) != 0) {
        func_81600F0C(D_81407BB0, 0, 0, 0x280, 0x1E0);
    } else {
        func_81600F0C(D_81407BB0, 0, 0x1A1, 0x230, 0x3F);
    }
    func_814025E8(
        ((u32)*(s32 *)(*(u8 **)((u8 *)(u32)D_814077AC + 0x844) + 0x40)) >> 31,
        *(s32 *)((u8 *)(u32)D_814077AC + 0x888)
    );
}

s32 main_pool_get_available();
s32 MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(s32);
extern void func_81406AAC(s32 *, s32);
extern void func_81406EA8(s32 *);
s32 func_81600E28(s32, s32, s32);
extern s32 D_814077A0;
extern u8 D_81407BB8;
void func_81400124(void) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    sp1C = temp_v0;
    D_814077A0 = func_81600E28(temp_v0, 1, 0x12);
    MainPool_FinalizeAllocation(sp1C);
    func_81406AAC(&D_81407BB8, D_814077AC);
    func_81406EA8(&D_81407BB8);
}

extern void func_80008648();
extern void func_800088DC();
extern void func_81400098(s32);
extern void func_81407118(u8 *, s32);
extern s32 D_814077B4;
extern s32 D_814077B8;
void func_81400194(void) {
    s32 temp_v0;

    func_800088DC();
    temp_v0 = func_8000731C();
    D_814077B4 = D_814077B8;
    if (temp_v0 != 0) {
        D_814077B8 = (*(s32 *)((u8 *)(temp_v0) + (8)));
    } else {
        D_814077B8 = D_814077B4;
    }
    func_81400098(D_814077A0);
    func_81407118(&D_81407BB8, D_814077A0);
    func_80008648();
}

extern s32 D_814077A8;
extern s32 StageContext_GetFadeMode(void);
extern void StageFade_StartFromTransparent(s32);
extern s32 func_81407258(u8 *);
extern void func_80025CBC(s32);
s32 func_81400218(s32 arg0) {
    s32 result = arg0;
    s32 temp_v0;
    s32 temp_v1;
    switch (arg0) {
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            result = 1;
        }
        break;
    case 1:
        temp_v0 = func_81407258(&D_81407BB8);
        if (temp_v0 != 0) {
            result = 2;
            StageFade_StartFromTransparent(5);
            temp_v1 = temp_v0;
            if (temp_v1 < 0) {
                func_80025CBC(5);
            }
            if (temp_v1 > 0) {
                D_814077A8 = 1;
            } else {
                D_814077A8 = 0;
            }
        }
        break;
    case 2:
        if (StageContext_GetFadeMode() == 1) {
            result = 3;
        }
        break;
    }
    return result;
}

extern void func_81400020(s32);
extern void func_81400194();
s32 func_81400218(s32);
extern void func_81406F44(u8 *, s32);
extern void func_81600954(s32);
extern void func_81600B30(s32);
extern void func_816018CC(s32);
void func_814002E8(void) {
    s32 temp_v0;
    s32 var_s1;

    var_s1 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(3);
    func_80021ED8(0x1C);
    do {
        func_80064D28();
        func_816018CC(1);
        func_81600954(D_814077A0);
        func_81400020(D_814077A0);
        func_81406F44(&D_81407BB8, D_814077A0);
        func_81600B30(D_814077A0);
        func_81400194();
        temp_v0 = func_81400218(var_s1);
        var_s1 = temp_v0;
    } while (temp_v0 != 3);
}

extern s32 func_8006CBB8(s16, u16, void *);
extern s32 func_8004D690(s32);
s32 func_81400398(void *arg0) {
    typedef struct { u8 pad_0034[0x34]; s16 kind; u8 pad_0036[4]; u16 value; } Header;
    typedef struct { u8 pad_0000[0x844]; Header *header; u8 pad_0848[0x54]; s16 value_89C; s16 value_89E; } State;
    u16 var_a1;
    s32 temp_v1;
    s32 temp_v0_2;
    Header *temp_v0;
    temp_v0 = ((State *)arg0)->header;
    temp_v1 = temp_v0->kind;
    var_a1 = temp_v0->value;
    switch (temp_v1) {
    case 6: {
        u16 sp1E;
        temp_v0_2 = func_8006CBB8(((State *)arg0)->value_89E, (sp1E = var_a1), arg0);
        switch (temp_v0_2) {
        case 0: var_a1 = 0x1A; break;
        case 1: var_a1 = 0x1B; break;
        case 2: var_a1 = 0xD; break;
        }
        break;
    }
    case 0xE:
        var_a1 = 0x17;
        break;
    }
    temp_v1 = ((State *)arg0)->value_89C & 0xFF00;
    switch (temp_v1) {
    case 0x400: var_a1 = 0xE; break;
    case 0x500: var_a1 = 0x2E; break;
    }
    return func_8004D690(var_a1);
}

extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_8004C09C(s32);
extern void func_80047588(s32, s32);
extern void func_8004C8C0(s32);
extern void func_8160317C(void);
extern void func_814005B0(void);
extern void Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern void func_81400124(void);
extern void func_80008514(s32);
extern void func_814002E8(void);
extern void func_81407310(u8 *);
extern void func_80008574(void);
extern void func_8004C398(void);
extern void Gfx_FreeDisplayListBuffers(void);
extern u8 D_1000000[];
extern u8 D_446E30[];
extern u8 D_447D00[];
extern s32 D_814077A4;
extern s32 func_81400398(void *);
s32 fragment12_main(s32 arg0, s32 arg1) {
    s32 sp24;

    D_814077AC = (u8 *)(u32)arg1;
    D_814077A4 = *(s32 *)(D_814077AC + 0x840);
    main_pool_push_state(0x4F474E5A);
    Gfx_InitDisplayListBuffers(0x50000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(0x4F);
    D_81407BB0 = (u8 *)(u32)func_81400398(D_814077AC);
    func_80047588(0x1C, 0);
    func_8004C8C0(0x79);
    func_8160317C();
    func_814005B0();
    Asset_LoadToSegment(((u32)&D_1000000 & 0x0F000000) >> 24, &D_446E30, D_447D00, 0);
    func_81400124();
    func_80008514(sp24);
    func_814002E8();
    func_800086A4(3);
    if (D_814077A8 == 1) {
        func_81407310(&D_81407BB8);
    }
    func_80008574();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x4F474E5A);
    return D_814077A8;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_814005B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400884.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400A50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400C24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400DE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400FA4.s")

extern u8 *D_814077D0[];
extern s32 func_8004D1FC(u8 *);
void func_81401178(s32 arg0) {
    s32 var_v0;
    if (arg0 >= 0) {
        var_v0 = arg0;
    } else {
        var_v0 = 0;
    }
    func_8004D1FC(D_814077D0[var_v0]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_814011B4.s")

extern Gfx *D_800D0510;
extern u8 *D_814077C0;
extern u8 D_80094E38[];
void func_81401394(void) {
    func_8004D1FC(D_814077C0);
    gSPDisplayList(D_800D0510++, D_80094E38);
    gDPSetCombine(D_800D0510++, 0xFFB3FF, 0xFF65FEFF);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81401404.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_814014C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_814018F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81401DB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_8140225C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_814024B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_814025E8.s")

s32 func_814028A0(s32 arg0) {
    return (s32) (((((f32) arg0 + 0.5f) * 22.0f) + 17.0f) - 6.0f);
}
#endif
