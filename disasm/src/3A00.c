#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80002E00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80002E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80002EB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80002F90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_800030D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80003120.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80003164.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_8000318C.s")

void func_800031FC(u8 *arg0, s32 arg1) { if (*(s32 *)(arg0 + 0) >= arg1) { *(s32 *)(arg0 + 4) = arg1; *(s32 *)(arg0 + 0xC) = *(s32 *)(arg0 + 8) + arg1; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80003224.s")
#endif
