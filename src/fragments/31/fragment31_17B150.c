#include "global.h"


#ifdef VERSION_US
extern void Util_Free(s32);
extern void func_888002DC(void);
extern void main_pool_pop_state(s32);
extern void func_8821CE40(s32);
extern s32 D_88234560;
extern s32 D_88234564;
void func_88207ED0(void) {
    Util_Free(D_88234564);
    func_888002DC();
    main_pool_pop_state(0x4152524D);
    func_8821CE40(1);
    D_88234560 = 5;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_88207F18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_88208010.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_88208174.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_882089E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_88208B38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_88208FF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820908C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_88209278.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820A56C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820A638.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820AAD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820ACD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820AF54.s")

extern void func_80049064(s32, s32, s32, s32);
extern void func_800496A4(s32, s32);
s32 func_8004C874(s32, s32);
extern void *D_88234700;

void func_8820B020(void) {
    func_800496A4(4, 2);
    func_80049064(0x140, 0x198, 1, func_8004C874(0x20, 7));
    func_800496A4(0x10, 2);
    func_80049064(0x140, 0x15F, 1, func_8004C874(0x20, (*(s16 *)((u8 *)(D_88234700) + (8))) + 1));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820B09C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820B124.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820B6C8.s")
#endif
