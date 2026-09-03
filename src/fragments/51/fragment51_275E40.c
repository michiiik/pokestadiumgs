#include "global.h"


#ifdef VERSION_US
extern void StageFade_StartFromTransparent(s32);
extern void func_800088A4(s32);
extern void *D_863075D8;
void func_86300020(s32 arg0) {
    (*(s32 *)((u8 *)(D_863075D8) + (0x8F58))) = arg0;
    (*(s32 *)((u8 *)(D_863075D8) + (0))) = 7;
    (*(s32 *)((u8 *)(D_863075D8) + (4))) = 8;
    func_800088A4(0xFFFF);
    StageFade_StartFromTransparent(0xA);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86300074.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86300120.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863001BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863003DC.s")
#endif

#ifdef VERSION_US
extern void *D_863075D8;
extern void func_863003DC(void *);
void func_86300494(void) {
    s32 i;
    void *p;

    p = (u8 *)D_863075D8 + 0x149C;
    for (i = 0; i != 4; i += 1) {
        func_863003DC(p);
        p = (u8 *)p + 0x18C;
    }
}
#endif

void func_863004E8(void) {
}

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
extern u8 D_863070F0[];
void func_863004F0(s32 arg0, s32 arg1) {
    if (arg0 == 5) {
        gDPPipeSync(D_800D0510++);
        gSPSegment(D_800D0510++, 0xF, func_8004CA60((u8 *)func_8004C990(0x93, 0)));
        gDPSetEnvColor(D_800D0510++, 0x7F, 0x7F, 0x7F, 0xFF);
        gSPDisplayList(D_800D0510++, D_863070F0);
        func_8003CD84();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863005B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863006F8.s")
#endif

#ifdef VERSION_US
u32 func_8003570C();
void func_863007B8(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (0x38))) = (f32) ((((f32) func_8003570C() / 4294967296.0f) - 0.5f) * 0.5f);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86300818.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86300C74.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86300DD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86300EF8.s")
#endif

#ifdef VERSION_US
extern void *D_87F119DC;
extern void MtxF_Copy(u32 *dest, u32 *src);
void func_86300FB4(void) {
    void *state = D_87F119DC;
    void *source = *(void **)((u8 *)state + 0x20);
    MtxF_Copy((u32 *)((u8 *)state + 0x84), (u32 *)((u8 *)source + 0x84));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86300FE4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863010A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86301250.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863013C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863018C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86301B3C.s")
#endif

#ifdef VERSION_US
extern void func_86301B3C(s32);

void func_86301E14(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_86301B3C(var_s0);
        var_s0 += 1;
    } while (var_s0 != 4);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86301E54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86301F0C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86302404.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863024A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86302634.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_8630271C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86302F9C.s")
#endif

#ifdef VERSION_US
extern void *D_863075D8;
extern void func_863048A8(void);
extern s32 func_87F08208(void *);
extern void func_800088A4(s32);
extern void StageFade_StartFromTransparent(s32);
extern void func_800225C4(s32);
extern void func_800279C4(s32);
extern void func_86300020(s32);
extern void func_800226C0(s32);
void func_86303110(void) {
    s32 temp_v0;

    func_863048A8();
    temp_v0 = func_87F08208((u8 *)D_863075D8 + 0x44);
    switch (temp_v0) {
    case 1:
        func_800088A4(0xFFFF);
        StageFade_StartFromTransparent(0x14);
        *(s32 *)D_863075D8 = 2;
        func_800225C4(0x28);
        func_800279C4(0xCF0B);
        break;
    case 2:
        func_86300020(0);
        func_800226C0(3);
        break;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863031A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_8630328C.s")
#endif

#ifdef VERSION_US
extern void func_86302404();
extern void func_863031A4();
extern void func_8630328C();
extern s32 D_863072E8;
s32 func_80001FF0(void);
void func_80028118(u8 arg0);
void func_8630352C(void) {
    if ((*(s32 *)((u8 *)(D_863075D8) + (0x8F30))) < ((func_80001FF0() >> 1) * 0x1E)) {
        func_80028118(6U);
    }
    func_863031A4();
    func_86302404();
    func_8630328C();
    if (D_863072E8 != 4) {
loop_3:
        goto loop_3;
    }
}
#endif

#ifdef VERSION_US
extern void *D_863075D8;
extern void func_863048A8(void);
extern s32 StageContext_GetFadeMode(void);
extern void func_8630487C(void);
extern void func_86301E14(void);
extern void func_80007AEC(s32);
extern void func_87F00688(void);
void func_863035B0(void) {
    func_863048A8();
    if (StageContext_GetFadeMode() == 1) {
        func_8630487C();
        func_86301E14();
        func_80007AEC(0x14);
        *(s32 *)D_863075D8 = 3;
        func_87F00688();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86303610.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863036FC.s")
#endif

#ifdef VERSION_US
extern void *D_863075D8;
extern void func_800086A4(s32);
extern void func_80007AEC(s32);
extern void func_80064D28(void);
extern void func_863036FC(void);
extern void func_86302F9C(void);
void func_86303974(void) {
    func_800086A4(2);
    func_80007AEC(0xA);
    do {
        func_80064D28();
        func_863036FC();
        func_86302F9C();
    } while (*(s32 *)D_863075D8 != 8);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863039DC.s")
#endif
