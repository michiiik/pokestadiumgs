#include "global.h"


#ifdef VERSION_US
extern s32 D_882346F0;
extern void func_800226C0();
extern void func_88001900();
void func_88231430(void) { func_800226C0(94); func_88001900(); D_882346F0 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A46B0/func_8823145C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A46B0/func_88231540.s")

extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
extern void func_8823145C(void);
extern void func_88231540(void);
extern void func_88231430(void);
void func_88231698(void) {
    func_88005B60(3, func_8823145C, func_88231540, func_88231430);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A46B0/func_882316D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A46B0/func_88231784.s")

extern void func_882316D0(void);
extern void func_88231784(void);
extern void func_8820CE2C(void);
void func_882318B0(void) {
    func_88005B60(4, func_882316D0, func_88231784, func_8820CE2C);
}
#endif
