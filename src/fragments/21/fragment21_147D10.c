#include "global.h"


#ifdef VERSION_US
extern void _bzero(void *, s32);
extern s16 D_82509680;
extern s16 D_82509686;
void func_82507D90(void) {
    _bzero(&D_82509680, 0x12C8);
    D_82509686 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_147D10/func_82507DC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_147D10/func_82507EE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_147D10/func_82508014.s")

extern void func_82507DC0(s16 *);
extern void func_82508014(s16 *);
void func_82508268(void) {
    switch (D_82509680) {                           /* irregular */
    case 1:
        func_82507DC0(&D_82509680);
        return;
    case 2:
    case 4:
        func_82508014(&D_82509680);
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_147D10/func_825082C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_147D10/func_8250850C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_147D10/func_825085E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_147D10/func_82508620.s")


s32 func_8250865C(void) {
    return D_82509680 == 3;
}


s32 func_82508670(void) {
    return D_82509680 == 0;
}
#endif
