#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
extern u8 D_8670BA40[];
extern u8 D_8670B660[];
void func_86700020(s32 arg0, s32 arg1) {
    if (arg0 == 5) {
        gDPPipeSync(D_800D0510++);
        gSPSegment(D_800D0510++, 0xF, func_8004CA60((u8 *)func_8004C990(0x133, 1)));
        gSPDisplayList(D_800D0510++, D_8670BA40);
        func_8003CD84();
    }
}
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
extern u8 D_8670BA40[];
extern u8 D_8670B660[];
void func_867000C8(s32 arg0, s32 arg1) {
    if (arg0 == 5) {
        gDPPipeSync(D_800D0510++);
        gSPSegment(D_800D0510++, 0xF, func_8004CA60((u8 *)func_8004C990(0x3E, 1)));
        gDPSetEnvColor(D_800D0510++, 0, 0, 0xFF, 0xFF);
        gSPDisplayList(D_800D0510++, D_8670B660);
        func_8003CD84();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670018C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86700318.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86700418.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86700588.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern void *D_8009491C;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
extern s32 D_8670AB90[];
extern s32 D_8670C97C;
extern void *D_8670C978;
/* function: func_867006C4 */
void func_867006C4(s32 arg0, s32 arg1) {
    void *context;
    s32 index;

    if (arg0 == 5) {
        context = D_8009491C;
        index = *(s32 *)((u8 *)context + 0x14);
        D_8670C97C = func_8004C990(0x1B2, D_8670AB90[index]);
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238);
        gSPSegment(D_800D0510++, 0xF,
                   func_8004CA60((u8 *)D_8670C97C));
        gSPDisplayList(D_800D0510++, D_8670C978);
        func_8003CD84();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867007B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86700FD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670122C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867014C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86701874.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86701C6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670211C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86702434.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86702B28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86702E50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867035A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867036B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867037B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86703D98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86703DF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86703E9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86703F9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670408C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670427C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867043AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670675C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86706874.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867068EC.s")
#endif

#ifdef VERSION_US
typedef struct { u8 pad38[0x38]; s32 index; u8 pad3C[0x0C]; f32 out48; f32 out4C; f32 out50; f32 in54; f32 out58; } State86706A30;
typedef struct { u8 pad24[0x24]; f32 x; f32 y; f32 z; u8 tail[0x138]; } Row86706A30;
extern State86706A30 *D_87F119DC;
extern f32 D_8670C974;
extern Row86706A30 D_86710C20[];
void func_86706A30(void) { f32 temp_fv0; temp_fv0 = D_87F119DC->in54; D_87F119DC->out58 = temp_fv0; D_8670C974 = temp_fv0; D_87F119DC->out48 = D_86710C20[D_87F119DC->index].x; D_87F119DC->out4C = D_86710C20[D_87F119DC->index].y + 120.0f; D_87F119DC->out50 = D_86710C20[D_87F119DC->index].z - 50.0f; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86706AC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86706B88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86706D3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86706E34.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86707E2C.s")
#endif

void func_867086E4(void) {
}

#ifdef VERSION_US
s32 func_87F00930();
extern void func_87F01D44();

void func_867086EC(void) {
    if (func_87F00930() == 1) {
        func_87F01D44();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86708720.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86708944.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86708B18.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86708EDC.s")
#endif

#ifdef VERSION_US
extern s32 D_8670BB48;
extern void *D_8670FEB0;
void func_86709040(void) {
    if ((*(u8 *)((u8 *)(D_8670FEB0) + (0x2180))) == 4) {
        StageFade_StartFromOpaque(0x14);
        func_87F00688();
        D_8670BB48 = 0xD;
        return;
    }
    if (StageContext_GetFadeMode() == 0) {
        D_8670BB48 = 4;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867090A8.s")
#endif

void func_86709128(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86709130.s")
#endif

#ifdef VERSION_US
extern s32 StageFade_StartFromTransparent(s32);
s32 func_87F01A40();
extern s32 D_8670B394;
void func_8670972C(void) {
    s32 temp_v0;

    D_8670B394 = 1;
    temp_v0 = func_87F01A40();
    switch (temp_v0) {                              /* irregular */
    case 0:
    case 2:
        D_8670B394 = 0;
        return;
    case 3:
        (*(s32 *)((u8 *)(&D_8670BB48) + (0x48))) = 0;
        (*(s32 *)((u8 *)(&D_8670BB48) + (0))) = 2;
        (*(s32 *)((u8 *)(&D_8670BB48) + (0x30))) = 3;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        return;
    case 4:
        (*(s32 *)((u8 *)(&D_8670BB48) + (0x48))) = 1;
        (*(s32 *)((u8 *)(&D_8670BB48) + (0))) = 2;
        (*(s32 *)((u8 *)(&D_8670BB48) + (0x30))) = 3;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_867097D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86709934.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_86709AD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670A07C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670A404.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670A4D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670A790.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/55/fragment55_code/func_8670A96C.s")
#endif
