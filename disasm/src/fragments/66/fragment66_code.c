#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E00020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0048C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E00700.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E007F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E00868.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E00E5C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E017E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E01898.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E019B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E01A00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E01CE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E02378.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0248C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E02508.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E02658.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E02828.s")
#endif

#ifdef VERSION_US
extern void func_80007AEC(s32);
extern void func_800086A4(s32);
extern void func_80064D28();
extern void func_82E02658();
s32 func_82E02828(s32);
void func_82E028D0(void) {
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    func_80007AEC(5);
    do {
        func_80064D28();
        var_s0 = func_82E02828(var_s0);
        func_82E02658();
    } while (var_s0 != 3);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0292C.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_82E05450[];
void func_82E02A70(void) { Gfx *temp_v1 = D_800D0510++; temp_v1->words.w0 = 0xDE000000; temp_v1->words.w1 = (u32)D_82E05450; }
#endif

void func_82E02A9C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E02AA4.s")
#endif

#ifdef VERSION_US
extern void func_82E02A70();
extern void func_82E02AA4(s32);

void func_82E02CA4(s32 arg0) {
    func_82E02A70();
    func_82E02AA4(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E02CCC.s")
#endif

#ifdef VERSION_US
extern void func_82E02A70(void);
extern void func_82E02CCC(s32, s32, s32);
void func_82E02EB0(s32 arg0, s32 arg1, s32 arg2) {
    func_82E02A70();
    func_82E02CCC(arg0, arg1, arg2);
}
void func_82E02EB0_padding(void) {}
void func_82E02EB0_padding2(void) {}
void func_82E02EB0_padding3(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E02F00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E030B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0393C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E04040.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0424C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E04734.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E047C4.s")
#endif

#ifdef VERSION_US
extern void func_8003CD84();
extern void func_82E047C4(s32);
extern void *D_82E07600;
s32 func_82E04AE4(s32 arg0, s32 arg1) {
    if ((arg0 != 0) && (arg0 == 5)) {
        func_82E047C4((*(s32 *)((u8 *)(D_82E07600) + (8))));
        func_8003CD84();
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E04B28.s")
#endif

#ifdef VERSION_US
extern void func_82E04B28(s32);
s32 func_82E04E60(s32 arg0, s32 arg1) {
    if ((arg0 != 0) && (arg0 == 5)) {
        func_82E04B28((*(s32 *)((u8 *)(D_82E07600) + (8))));
        func_8003CD84();
    }
    return 0;
}
#endif
