#include "global.h"


#ifdef VERSION_US
typedef struct { u8 pad[0xCEB8]; s32 a,b,c,d; } BE0State;
extern BE0State *D_86416C00;
void func_86408BE0(void) {
    D_86416C00->a = 0;
    D_86416C00->b = 0;
    D_86416C00->c = 0;
    D_86416C00->d = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2870A0/func_86408C1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2870A0/func_86408CA0.s")
#endif
