#include "global.h"


#ifdef VERSION_US
extern void func_800033DC(s32);
extern void func_888002DC(void);
extern void main_pool_pop_state(s32);
extern void func_8821CE40(s32);
extern s32 D_88234560;
extern s32 D_88234564;
void func_88207ED0(void) {
    func_800033DC(D_88234564);
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820B020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820B09C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820B124.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17B150/func_8820B6C8.s")
#endif
