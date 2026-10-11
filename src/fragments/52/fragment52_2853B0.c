#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2853B0/func_86406EF0.s")

extern u8 *D_86416C00;
extern void func_87F026E8(void *, void *);
void func_86407034(void) {
    u8 *entry = *(u8 **)(D_86416C00 + 0xEC);

    if (entry != NULL) {
        do {
            func_87F026E8(D_86416C00 + 0xE0, entry);
            entry = *(u8 **)(entry + 4);
        } while (entry != NULL);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2853B0/func_8640708C.s")
#endif
