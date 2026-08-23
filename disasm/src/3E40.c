#include "global.h"

#define D_800871F0 (*(u32 *)0x800871F0)
#define D_800871F4 (*(u32 *)0x800871F4)
#define D_800CCDF0 (*(void **)0x800CCDF0)


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/func_80003240.s")

void Util_Memcpy(u32 *dst, const u32 *src, s32 wordCount) {
    while (wordCount-- > 0) {
        *dst++ = *src++;
    }
}

extern u32 osGetMemSize(void);
extern void main_pool_init(void *start, u32 end);
extern void Dma_InitializeCompletionQueue(void);
extern void *mem_pool_try_init(u32 size, s32 flags);

void Util_InitMainPools(void) {
    u32 memorySize = osGetMemSize();

    D_800871F0 = memorySize - 0x400000;
    D_800871F4 = memorySize;
    main_pool_init((void *)0x80134470, memorySize | 0x80000000);
    Dma_InitializeCompletionQueue();
    D_800CCDF0 = mem_pool_try_init(0x10000, 0);
}

u32 func_8000339C(void) {
    return *(u32 *)0x800871F4;
}

u32 func_800033A8(void) {
    return *(u32 *)0x800871F0;
}

extern void *mem_pool_alloc(void *pool, u32 size);

void *Util_Malloc(u32 size) {
    return mem_pool_alloc(D_800CCDF0, size);
}

extern void mem_pool_free(void *pool, void *ptr);

void Util_Free(void *ptr) {
    mem_pool_free(D_800CCDF0, ptr);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/Util_DrawRect.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/func_800034E4.s")

void Util_Memclear(u32 *dst, u32 count) {
    while (count-- != 0) {
        *dst++ = 0xFFFFFFFF;
        *dst++ = 0xFFFFFFFF;
    }
}

s32 Util_CheckStubMemArea(const u32 *pairs) {
    s32 count = 0;

    while (pairs[0] == 0x80400000 && pairs[1] == 0x80400000) {
        pairs += 2;
        count++;
    }
    return count * 8;
}
#endif
