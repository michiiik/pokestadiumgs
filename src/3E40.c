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
struct MemPool3A00;
extern void *mem_pool_alloc(struct MemPool3A00 *, s32);
void *Util_Malloc(s32 arg0) {
    return mem_pool_alloc(D_800CCDF0, arg0);
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

typedef struct PoolBlock3280 PoolBlock3280;
typedef struct PoolState3280 PoolState3280;
typedef struct Pool3280 {
    OSMesg msgs[1];
    OSMesgQueue queue;
    s32 available;
    PoolBlock3280 *start;
    PoolBlock3280 *end;
    PoolBlock3280 *listHeadL;
    PoolBlock3280 *listHeadR;
    PoolState3280 *mainState;
} Pool3280;

extern Pool3280 *func_80002DF0(void);
extern s32 main_pool_get_available(void);
extern s32 HAL_Printf(s16, s16, const char *, ...);
extern char D_800A1800[];
extern char D_800A1818[];
extern char D_800A1830[];
extern char D_800A1848[];

void func_800034E4(Gfx **dlist) {
    Pool3280 *pool;
    s32 sp58;
    s32 sp54;

    pool = func_80002DF0();
    sp58 = main_pool_get_available() - D_800871F0;
    sp54 = main_pool_get_available();

    if (sp58 >= 0) {
        s32 pad;
        s32 start;
        s32 listHeadL;
        s32 listHeadR;
        s32 end;

        start = (((u32)pool->start & 0x1FFFFFFF) >> 15) + 30;
        listHeadL = (((u32)pool->listHeadL & 0x1FFFFFFF) >> 15) + 30;
        listHeadR = ((((u32)pool->listHeadR & 0x1FFFFFFF) - D_800871F0) >> 15) + 30;
        end = ((((u32)pool->end & 0x1FFFFFFF) - D_800871F0) >> 15) + 30;

        Util_DrawRect(dlist, 30, start, 0xFBCB);
        Util_DrawRect(dlist, start, listHeadL, 0xFFCB);
        Util_DrawRect(dlist, listHeadL, listHeadR, 0x2ABF);
        Util_DrawRect(dlist, listHeadR, end, 0xFFCB);
        HAL_Printf(30, 20, D_800A1800, sp58, sp58 / 1024);
    } else {
        s32 pad;
        s32 start;
        s32 listHeadL;
        s32 listHeadR;
        s32 end;

        start = (((u32)pool->start & 0x1FFFFFFF) >> 15) + 30;
        listHeadL = (((u32)pool->listHeadL & 0x1FFFFFFF) >> 15) + 30;
        listHeadR = ((((u32)pool->listHeadR & 0x1FFFFFFF) - D_800871F0) >> 15) + 30;
        end = ((((u32)pool->end & 0x1FFFFFFF) - D_800871F0) >> 15) + 30;

        Util_DrawRect(dlist, 30, start, 0xFBCB);
        Util_DrawRect(dlist, start, listHeadR, 0xFFCB);
        Util_DrawRect(dlist, listHeadR, listHeadL, 0xF94B);
        Util_DrawRect(dlist, listHeadL, end, 0xFFCB);
        HAL_Printf(30, 20, D_800A1818, -sp58, -sp58 / 1024);
    }

    if (D_800871F0 != 0) {
        if (sp54 >= 0) {
            HAL_Printf(30, 30, D_800A1830, sp54, sp54 / 1024);
        } else {
            HAL_Printf(30, 30, D_800A1848, -sp54, -sp54 / 1024);
        }
    }
}

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
