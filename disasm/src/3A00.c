#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/mem_pool_try_init.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/mem_pool_init.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/mem_pool_alloc.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/mem_pool_free.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/MainPool_AllocState.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/MainPool_FinalizeAllocation.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/MainPool_InitState.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/MainPool_AllocAligned.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/MainPool_ResetStateToOffset.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/MainPool_ResetState.s")
#endif
