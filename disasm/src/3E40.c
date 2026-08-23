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

extern s32 StageContext_IsHighResolution(void);

/* Emit the RDP fill-rectangle sequence used by the UI. */
void Util_DrawRect(u32 **displayList, u32 ulx, u32 uly, u32 lrx, u32 lry,
                   u16 color) {
    u32 *gfx = *displayList;
    u32 edgeA = uly;
    u32 edgeB = lrx;
    u32 lowA;
    u32 lowB;

    (void)ulx;
    (void)lry;

    if (StageContext_IsHighResolution()) {
        edgeA <<= 1;
        edgeB <<= 1;
        lowA = 0x22;
        lowB = 0x1E;
    } else {
        lowA = 0x11;
        lowB = 0x0F;
    }

    gfx[0] = 0xE7000000;
    gfx[1] = 0;
    gfx[2] = 0xF7000000;
    gfx[3] = ((u32)color << 16) | color;
    gfx[4] = 0xF6000000 | ((edgeA & 0x3FF) << 14) | ((lowA & 0x3FF) << 2);
    gfx[5] = ((edgeB & 0x3FF) << 14) | ((lowB & 0x3FF) << 2);
    *displayList = gfx + 6;

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
