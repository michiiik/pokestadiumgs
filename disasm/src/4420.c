#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Jpeg_ReadBigEndianU16.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Jpeg_ParseStreamMarkers.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Jpeg_InitializeDspTask.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Jpeg_BuildDspInput.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Jpeg_BuildDspOutput.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Jpeg_DecodeImage.s")

extern u8 D_800CD000[];
extern u8 D_800CD018[];

void Dma_InitializeCompletionQueue(void) {
    osCreateMesgQueue((OSMesgQueue *)D_800CD000, (OSMesg *)D_800CD018, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Yay0_DecompressAndRelocate.s")

extern s32 Storage_QueueSramTransfer(u32 staging, u32 destination,
                                     u32 source, u32 length,
                                     OSMesgQueue *queue, s32 mode);

void Dma_ReadChunks(u32 destination, u32 source, s32 length, u32 staging) {
    OSMesgQueue *queue = (OSMesgQueue *)D_800CD000;

    while (length > 0) {
        u32 chunk = length >= 0x1000 ? 0x1000 : (u32)length;

        Storage_QueueSramTransfer(staging, destination, source, chunk, queue,
                                  0);
        osRecvMesg(queue, NULL, 1);

        length -= chunk;
        destination += chunk;
        source += chunk;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003E84.s")

extern s32 Dma_QueueRomRead(u32 destination, u32 source, u32 end,
                         u32 length, u32 staging, s32 mode);
extern u8 D_800CD000[];

s32 func_80003F54(s32 size) {
    return osFlashSectorErase(size << 7);
}

void func_80003F74(u32 destination, u32 source, u32 end, u32 staging) {
    OSMesgQueue *queue = (OSMesgQueue *)D_800CD000;
    s32 remaining = end - source;
    u32 chunk;

    while (remaining > 0) {
        if (remaining >= 0x1000) {
            chunk = 0x1000;
        } else {
            chunk = remaining;
        }

        Dma_QueueRomRead(staging, destination, source, chunk, (u32)queue, 0);
        osRecvMesg(queue, NULL, 1);

        remaining -= chunk;
        destination += chunk;
        source += chunk;
    }
}

extern s32 Storage_QueueRomWrite(u32 destination, u32 source, u32 length,
                                  OSMesgQueue *queue, s32 mode);

void Dma_CopyChunks(u32 destination, u32 source, u32 end) {
    OSMesgQueue *queue = (OSMesgQueue *)D_800CD000;
    s32 remaining = end - source;

    while (remaining > 0) {
        u32 chunk = remaining >= 0x1000 ? 0x1000 : (u32)remaining;

        Storage_QueueRomWrite(destination, source, chunk, queue, 0);
        osRecvMesg(queue, NULL, 1);

        remaining -= chunk;
        destination += chunk;
        source += chunk;
    }
}

u32 func_800040C4(void *asset) {
    return *(u32 *)((u8 *)asset + 0xC) + 0x100;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800040D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800041E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004254.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800042C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004458.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Memmap_SegmentCleanupCallback.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Asset_LoadToSegment.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Memmap_FragmentCleanupCallback.s")

typedef struct {
    u8 pad_00[0x1C];
    u32 end_offset;
} FragmentHeader;

extern void *func_800042C0(u32 source, u32 end, u32 decompress,
                           u32 relocate);
extern u32 MainPool_GetAllocationSize(void *fragment);
extern void main_pool_set_func(void *fragment, u32 vaddr, void *callback);
extern void main_pool_realloc(void *fragment, ...);
extern void Memmap_RelocateFragment(void *source, void *fragment);
extern void MainPool_ResetStateToOffset(void *pool, u32 offset);
extern void Memmap_FragmentCleanupCallback(void *arg0, u32 vaddr);

void Fragment_Register(u32 pool, FragmentHeader *fragment) {
    u32 allocation_size = MainPool_GetAllocationSize(fragment);

    main_pool_set_func(fragment, (u32)pool + 0x81000000,
                       Memmap_FragmentCleanupCallback);
    if (allocation_size < fragment->end_offset) {
        main_pool_realloc(fragment);
        Memmap_RelocateFragment(pool, fragment);
    } else {
        Memmap_RelocateFragment(pool, fragment);
        main_pool_realloc(fragment, fragment->end_offset);
    }
}

void Fragment_RelocateAndReset(void *pool, void *source,
                               FragmentHeader *fragment) {
    Memmap_RelocateFragment(source, fragment);
    MainPool_ResetStateToOffset(
        pool, (u32)((u8 *)fragment + fragment->end_offset) -
                 *(u32 *)((u8 *)pool + 8));
}

void *Fragment_Load(u32 pool, u32 source, u32 end) {
    void *fragment = func_800042C0(source, end, 0, 0);

    if (fragment != NULL) {
        Fragment_Register(pool, fragment);
    }
    return fragment;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/BinArchive_Open.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800049B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800049D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004B4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004B78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/BinArchive_GetCachedFile.s")
#endif
