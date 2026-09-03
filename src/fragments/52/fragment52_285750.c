#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_285750/func_86407290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_285750/func_86407330.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_285750/func_864073B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_285750/func_86407610.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_285750/func_864079AC.s")

extern void func_87F05204(s32 *);
extern void func_87F09040();
extern u8 D_800D0510;
extern void *D_86416C00;
void func_86407A54(void) {
    if (((u32) (*(u32 *)((u8 *)(D_86416C00) + (0xC))) >> 0x1F) != 0) {
        func_87F05204(&D_800D0510);
        func_87F09040();
    }
}
#endif
