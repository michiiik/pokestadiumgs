#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88306D00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88306D6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88306DAC.s")

extern void func_88004B60(s32, u8, s32 *);
extern u8 D_88601896;
extern s32 D_88601898;
extern u8 func_88306D00;
extern u8 func_88306D6C;
extern u8 func_88306DAC;
void func_88306E18(s32 arg0) {
    s32 *sp1C;

    switch (arg0) {                                 /* irregular */
    case 0:
        sp1C = &func_88306D00;
        break;
    case 1:
        sp1C = &func_88306D6C;
        break;
    case 2:
        sp1C = &func_88306DAC;
        break;
    }
    func_88004B60(D_88601898, D_88601896, sp1C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88306E90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88306F18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88306F90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_8830700C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88307294.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88307468.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_883074E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_8830765C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_8830780C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B8010/func_88307938.s")
#endif
