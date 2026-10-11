#include "global.h"


#ifdef VERSION_US
extern void _bcopy(void *, void *, s32);
void func_87F0A5F0(s32 arg0) { s32 sp18[2]; _bcopy(&arg0, &sp18[0], 4); }

extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern s32 MainPool_AllocAligned(s32, s32, s32);
extern void MainPool_FinalizeAllocation(s32);
s32 func_87F0A61C(void) { s32 ptr = MainPool_AllocState(main_pool_get_available(), 0); s32 result = MainPool_AllocAligned(ptr, 0xC, 4); MainPool_FinalizeAllocation(ptr); return result; }

void func_87F0A66C(u8 *arg0, u32 *arg1, u32 *arg2) {
    arg0[0x28] = 2;
    *(u32 *)(arg0 + 0x2C) = *arg1;
    *(u32 *)(arg0 + 0x30) = *arg2;
}

typedef struct TreeNode_80050428 TreeNode_80050428;
extern void *func_8005049C(TreeNode_80050428 *, s32);
void func_87F0A688(TreeNode_80050428 *arg0, s32 arg1, s32 arg2) {
    u8 *entry = func_8005049C(arg0, arg1);
    if (entry == NULL) {
        func_87F0A5F0(arg1);
    } else {
        *(s16 *)(entry + 0x26) = arg2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D260/func_87F0A6C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D260/func_87F0A714.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D260/func_87F0A91C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D260/func_87F0A988.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D260/func_87F0AA80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D260/func_87F0AB08.s")
#endif
