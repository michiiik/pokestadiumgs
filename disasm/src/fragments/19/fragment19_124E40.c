#include "global.h"


#ifdef VERSION_US
typedef struct { s16 x; s16 y; } Vec2s; void func_82303D60(Vec2s *arg0, Vec2s *arg1, Vec2s *arg2) { arg0->x = arg1->x + arg2->x; arg0->y = arg1->y + arg2->y; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82303D84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82303E14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82304260.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_823043D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82304520.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82304608.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_823049A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82304C88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82304F5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_823052FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_823053A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_823055DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_8230570C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_8230583C.s")

extern void func_823055DC(u8 *);
extern void func_8230570C(u8 *);
extern void func_8230583C(u8 *);
extern u8 D_82306AF8[];
void func_82305914(void) {
    switch ((*(s16 *)((u8 *)(D_82306AF8) + (2)))) {      /* irregular */
    case 1:
        func_823055DC(D_82306AF8);
        return;
    case 3:
        func_8230570C(D_82306AF8);
        return;
    case 4:
        func_8230583C(D_82306AF8);
        /* fallthrough */
    case 0:
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_124E40/func_82305988.s")

void func_823059D4(void) {
    *(s16 *)(D_82306AF8 + 2) = 1;
    *(s16 *)(D_82306AF8 + 6) = -1;
}

void func_823059F0(void) {
    *(s16 *)(D_82306AF8 + 2) = 3;
    *(s16 *)(D_82306AF8 + 6) = -1;
}

void func_82305A0C(void) {
    *(s16 *)(D_82306AF8 + 2) = 4;
    *(s16 *)(D_82306AF8 + 6) = -1;
}

extern s16 D_82306AFA;
s32 func_82305A28(void) {
    s32 result = 0;
    if (D_82306AFA == 2) result = 1;
    return result;
}

s32 func_82305A4C(void) {
    s32 result = 0;
    if (D_82306AFA == 0) result = 1;
    return result;
}
#endif
