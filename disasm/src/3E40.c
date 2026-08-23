#include "global.h"

#define D_800871F0 (*(u32 *)0x800871F0)
#define D_800871F4 (*(u32 *)0x800871F4)
#define D_800CCDF0 (*(void **)0x800CCDF0)


#ifdef VERSION_US
extern u32 Memmap_GetSegmentVaddr(u32 vaddr);
extern u32 Memmap_GetFragmentVaddr(u32 vaddr);
extern u32 func_8000339C(void);

void *func_80003240(void *ptr) {
    u32 address = (u32)ptr;
    u32 result = 0;

    if (address < func_8000339C()) {
        result = address | 0x80000000;
    } else if (address < 0x10000000) {
        result = Memmap_GetSegmentVaddr(address);
    } else if (address >= 0x81000000 && address < 0x90000000) {
        result = Memmap_GetFragmentVaddr(address);
    } else if (address >= 0x80000000 && address < (func_8000339C() | 0x80000000)) {
        result = address;
    }
    return (void *)result;
}

void Util_Memcpy(u32 *dst, const u32 *src, s32 wordCount) {
    while (wordCount-- > 0) {
        *dst++ = *src++;
    }
}

extern u32 osGetMemSize(void);
extern void main_pool_init(void *start, u32 end);
#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/Util_InitMainPools.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/Util_Memclear.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/Util_CheckStubMemArea.s")
#endif
