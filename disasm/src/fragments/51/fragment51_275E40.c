#include "global.h"


#ifdef VERSION_US
extern void func_80007B34(s32);
extern void func_800088A4(s32);
extern void *D_863075D8;
void func_86300020(s32 arg0) {
    (*(s32 *)((u8 *)(D_863075D8) + (0x8F58))) = arg0;
    (*(s32 *)((u8 *)(D_863075D8) + (0))) = 7;
    (*(s32 *)((u8 *)(D_863075D8) + (4))) = 8;
    func_800088A4(0xFFFF);
    func_80007B34(0xA);
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86300494.s")
#endif

void func_863004E8(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863004F0.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86300FB4.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86303110.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863035B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86303610.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863036FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_86303974.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_275E40/func_863039DC.s")
#endif
