#include "global.h"


#ifdef VERSION_US
u32 Memmap_GetFragmentVaddr(u32);
u32 Memmap_GetSegmentVaddr(u32);
u32 func_8000339C(void);
u32 func_80003240(u32 arg0) {
    u32 sp18;
    u32 var_v1;

    sp18 = 0;
    var_v1 = sp18;
    if (arg0 < func_8000339C()) {
        var_v1 = arg0 | 0x80000000;
    } else if (arg0 < 0x10000000U) {
        var_v1 = Memmap_GetSegmentVaddr(arg0);
    } else if ((arg0 >= 0x81000000U) && (arg0 < 0x90000000U)) {
        var_v1 = Memmap_GetFragmentVaddr(arg0);
    } else if ((arg0 >= 0x80000000U) && (arg0 < (u32)(func_8000339C() + 0x80000000))) {
        var_v1 = arg0;
    }
    return var_v1;
}


void Util_Memcpy(u32 *dst, const u32 *src, s32 wordCount) {
    while (wordCount-- > 0) {
        *dst++ = *src++;
    }
}

extern void main_pool_init(void *, s32);
extern void Dma_InitializeCompletionQueue(void);
extern void *mem_pool_try_init(s32, s32);
extern u32 D_800871F0;
extern u32 D_800871F4;
extern u8 D_80134470[];
extern void *D_800CCDF0;
void Util_InitMainPools(void) {
    s32 size = osGetMemSize();
    D_800871F0 = size - 0x400000;
    D_800871F4 = size;
    main_pool_init(D_80134470, size | 0x80000000);
    Dma_InitializeCompletionQueue();
    D_800CCDF0 = mem_pool_try_init(0x10000, 0);
}

extern u32 D_800871F4; u32 func_8000339C(void) { return D_800871F4; }

extern u32 D_800871F0; u32 func_800033A8(void) { return D_800871F0; }


extern void * D_800CCDF0;
extern void mem_pool_alloc(void *, s32);
void Util_Malloc(s32 arg0) {
    mem_pool_alloc(D_800CCDF0, arg0);
}


extern void mem_pool_free(void *, s32);
void Util_Free(s32 arg0) {
    mem_pool_free(D_800CCDF0, arg0);
}

void Util_DrawRect(Gfx** dlist, s32 ulx, s32 lrx, u16 color) {
    s32 uly = 15;
    s32 lry = 17;
    Gfx* gfx = *dlist;

    if (StageContext_IsHighResolution() != 0) {
        ulx <<= 1;
        lrx <<= 1;
        uly <<= 1;
        lry <<= 1;
    }

    gDPPipeSync(gfx++);
    gDPSetFillColor(gfx++, color << 16 | color);
    gDPFillRectangle(gfx++, ulx, uly, lrx, lry);
    *dlist = gfx;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/func_800034E4.s")

void Util_Memclear(u64 *dest, u32 size) {
    while (size-- > 0) {
        *(dest++) = -1;
    }
}

s32 Util_CheckStubMemArea(u64 *ptr) {
    s32 ret = 0;
    while (*(ptr++) == 0x8040000080400000ULL) {
        ret++;
    }
    return ret * sizeof(*ptr);
}
#endif
