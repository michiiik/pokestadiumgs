#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86600020.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern s32 D_86606714;
extern s32 D_86607218;
extern s32 D_8660731C;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
extern u8 D_86606600[];
extern u8 D_86606560[];
void func_86600160(s32 arg0, s32 arg1) {
    if (arg0 == 5) {
        gDPPipeSync(D_800D0510++);
        if (D_86606714 == 0) {
            D_8660731C = guRandom() % 7;
        }
        gDPSetEnvColor(D_800D0510++, 0xFF, 0xFF, 0xFF, 0xFF);
        gDPSetPrimColor(D_800D0510++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        gDPSetCombine(D_800D0510++, 0x509BFF, 0x3FFDFE38);
        gSPSegment(D_800D0510++, 0xF,
                   func_8004CA60((u8 *)func_8004C990(0xE0, D_8660731C)));
        gSPDisplayList(D_800D0510++, D_86606560);
        func_8003CD84();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86600298.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86600678.s")
#endif

#ifdef VERSION_US
extern u8 D_8660A990[];
extern s32 D_866066F4[];
void func_86600C70(s32 arg0) {
    u8 *record;

    record = (u8 *)D_8660A990 + arg0 * 0x58;
    *(s32 *)(record + 0x18) = 1;
    *(s32 *)(record + 0x10) = -1;
    if (D_866066F4[arg0] != 0) {
        *(s32 *)(record + 4) = 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86600CC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86600E00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86600EEC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86601188.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86601398.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86601408.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_866016D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_866017E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86601910.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86601A04.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86601C98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86601F70.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86602260.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_866023F4.s")
#endif

#ifdef VERSION_US
extern void func_80038E14(s32, s32, s32, s32, f32, f32, f32, s32);
extern u8 D_86606788;
s32 func_8660265C(s32 arg0, s32 arg1) {
    func_80038E14(arg1, (*(s32 *)((u8 *)(&D_86606788) + (0x1C))), (*(s32 *)((u8 *)(&D_86606788) + (0x20))), (*(s32 *)((u8 *)(&D_86606788) + (0x24))), (*(f32 *)((u8 *)(&D_86606788) + (0x28))), (*(f32 *)((u8 *)(&D_86606788) + (0x2C))), (*(f32 *)((u8 *)(&D_86606788) + (0x30))), 0);
    return 0;
}
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_866026B8(s32 arg0, void *arg1) {
    s16 pad;
    s32 x;
    s16 y;
    s16 z;

    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &x, &y, &z);
        *(s16 *)((u8 *)arg1 + 0x1C) = y + 0x2000;
        *(s16 *)((u8 *)arg1 + 0x1E) = z - 0x2000;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_86602720(s32 arg0, void *arg1) {
    s16 pad;
    s32 x;
    s16 y;
    s16 z;

    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &x, &y, &z);
        *(s16 *)((u8 *)arg1 + 0x1C) = -0x2000 - y;
        *(s16 *)((u8 *)arg1 + 0x1E) = z + 0x6000;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 D_8660670C;
extern s32 D_86606710;
extern s32 D_8660681C;
void func_8660278C(void) {
    switch (D_8660681C) {
    case 1:
        D_8660670C = 1;
        D_86606710 = 0x78;
        return;
    case 2:
        D_8660670C = 2;
        D_86606710 = 0x8C;
        return;
    case 3:
        D_8660670C = 4;
        D_86606710 = 0x78;
        return;
    case 4:
        D_8660670C = 6;
        D_86606710 = 0x8C;
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86602828.s")
#endif

void func_86603100(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86603108.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86603604.s")
#endif

#ifdef VERSION_US
s32 func_87F00930();
extern void func_87F01D44();

void func_86604084(void) {
    if (func_87F00930() == 1) {
        func_87F01D44();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_866040B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86604370.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_866044F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_8660484C.s")
#endif

#ifdef VERSION_US
extern s32 D_8660678C;
extern void *D_86607230;
extern void StageFade_StartFromOpaque(s32);
void func_87F00688(void);
u8 StageContext_GetFadeMode(void);
void func_866048EC(void) {
    if ((*(u8 *)((u8 *)(D_86607230) + (0x2180))) == 4) {
        StageFade_StartFromOpaque(0x14);
        func_87F00688();
        D_8660678C = 0xA;
        return;
    }
    if (StageContext_GetFadeMode() == 0) {
        D_8660678C = 4;
    }
}
#endif

#ifdef VERSION_US
extern s32 D_86606714;
extern s32 D_8660678C;
extern s32 func_87F006AC(void);
extern void func_800279C4(s32);
extern void func_80021ED8(s32);
extern void func_87F0CA30(void);
s32 func_86604954(void) {
    if (D_86606714 == 1) {
        return 0;
    }
    if (func_87F006AC() == 1) {
        func_800279C4(0x2F00);
    }
    if (func_87F006AC() == 2) {
        D_8660678C = 0xC;
        func_800279C4(0x2F01);
        func_80021ED8(0x15);
        func_87F0CA30();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_866049D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86605098.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_866055C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_866056B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86605ABC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86605D5C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86605DCC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_86605F04.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/54/fragment54_code/func_866061E0.s")
#endif

#ifdef VERSION_US
extern void Gfx_InitDisplayListBuffers(s32, s32);
s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_80008514(s32);
extern void func_80008574();
extern void func_8004C8C0(s32);
extern void func_86602828();
extern void func_866061E0();
extern void func_87F00030();
extern void func_87F01F34(void *);
extern void func_87F06EAC(s32, s32 *, void *);
extern void func_87F0F480(void *);
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
extern u8 D_446E30;
extern s32 D_86606814;
extern u8 D_86607320;
extern s32 D_86607328;
extern s32 D_86607378;
extern void func_80027EE0(s32);
extern void func_8004C09C(s32 arg0);
extern s32 func_80047588(s32 arg0, s32 arg1);
u8 *Asset_LoadToSegment(s32 id, u8 *rom_start, u8 *rom_end, s32 arg3);
extern u8 D_1000000[];
extern u8 D_447D00[];
void func_87F0C980(void);
void func_80047610(void);
void func_8004C398(void);
void Gfx_FreeDisplayListBuffers(void);
s32 func_800082E0(s32, s32, s32, s32, s32, s32);
u8 *Asset_LoadToSegment(s32 id, u8 *rom_start, u8 *rom_end, s32 arg3);
void func_87F0C980(void);
void func_80047610(void);
void func_8004C398(void);
void Gfx_FreeDisplayListBuffers(void);
s32 fragment54_main(s32 arg0, void *arg1) {
    s32 sp24;

    D_86607230 = arg1;
    if ((*(u8 *)((u8 *)(D_86607230) + (0x2180))) == 4) {
        func_80027EE0(0xFFF);
    }
    main_pool_push_state(0x4D523032);
    Gfx_InitDisplayListBuffers(0x20000, 0);
    sp24 = func_800082E0(0, 1, 3, 1, 2, 1);
    func_8004C09C(0x123);
    func_87F06EAC(0x6A, &D_86607320, D_86607230);
    func_8004C8C0(0xE0);
    func_8004C8C0(0xE1);
    func_8004C8C0(0x1B2);
    func_8004C8C0(0x19A);
    func_8004C8C0(0x199);
    func_80047588(D_86607328 | 5 | D_86607378, 0);
    Asset_LoadToSegment((s32) ((u32) ((s32) D_1000000 & 0x0F000000) >> 0x18), &D_446E30, D_447D00, 0);
    func_87F00030();
    func_87F0C980();
    func_87F01F34(D_86607230);
    func_86602828();
    func_80008514(sp24);
    func_866061E0();
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x4D523032);
    func_87F0F480(D_86607230);
    func_80027EE0(0xFFE);
    return D_86606814;
}
#endif
