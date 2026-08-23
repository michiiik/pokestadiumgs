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

extern void *main_pool_alloc(u32 size, u32 tag);
extern void *MainPool_AllocAligned(void *pool, u32 size, u32 align);
extern void Yay0_DecompressAndRelocate(void *source, void *destination);
extern void main_pool_try_free(void *ptr);

void *func_800041E4(void *pool, void *old, void *header, u32 tag) {
    void *destination;

    if (pool == NULL) {
        destination = main_pool_alloc(*(u32 *)((u8 *)header + 0x10), tag);
    } else {
        destination = MainPool_AllocAligned(
            pool, *(u32 *)((u8 *)header + 0x10), 0x10);
    }

    if (destination != NULL) {
        Yay0_DecompressAndRelocate(header, destination);
    }
    main_pool_try_free(old);
    return destination;
}

void *func_80004254(void *pool, void *arg1, void *arg2, void *arg3,
                    u32 size, u32 tag) {
    void *destination;

    if (pool == NULL) {
        destination = main_pool_alloc(size, tag);
    } else {
        destination = MainPool_AllocAligned(pool, size, 0x10);
    }
    if (destination != NULL) {
        func_80003F74((u32)destination, (u32)arg1, (u32)arg2, (u32)arg3);
    }
    return destination;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800042C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004458.s")

extern u32 Memmap_GetSegmentBaseVaddr(u32 segment);
extern void Memmap_ClearSegmentMemmap(u32 segment);
extern u32 Memmap_GetFragmentBaseVaddr(u32 fragment);
extern void Memmap_ClearFragmentMemmap(u32 fragment);
extern void *func_800042C0(u32 source, u32 end, u32 decompress,
                           u32 relocate);
extern u32 MainPool_GetAllocationSize(void *fragment);
extern void main_pool_set_func(void *fragment, u32 vaddr, void *callback);
extern void Memmap_SetSegmentMap(u32 segment, void *asset, u32 size);

void Memmap_SegmentCleanupCallback(void *arg0, u32 vaddr) {
    u32 segment;

    if ((vaddr & 0xFF000000) != 0x82000000) {
        return;
    }

    segment = vaddr & 0x00FFFFFF;
    if (Memmap_GetSegmentBaseVaddr(segment) == (u32)arg0) {
        Memmap_ClearSegmentMemmap(segment);
    }
}

void *Asset_LoadToSegment(u32 segment, u32 source, u32 end, u32 decompress) {
    void *asset = func_800042C0(source, end, decompress, 0);

    if (asset != NULL && segment > 0) {
        u32 size = MainPool_GetAllocationSize(asset);

        Memmap_SetSegmentMap(segment, asset, size);
        main_pool_set_func(asset, segment + 0x82000000,
                           Memmap_SegmentCleanupCallback);
    }
    return asset;
}

void Memmap_FragmentCleanupCallback(void *arg0, u32 vaddr) {
    u32 fragment;

    if ((vaddr & 0xFF000000) != 0x81000000) {
        return;
    }

    fragment = vaddr & 0x00FFFFFF;
    if (Memmap_GetFragmentBaseVaddr(fragment) == (u32)arg0) {
        Memmap_ClearFragmentMemmap(fragment);
    }
}

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

void func_800049B8(void *ptr) {
    main_pool_try_free(ptr);
}

extern void *func_80004458(s32 pool, u32 source, u32 end, s32 flags);

void *func_800049D8(s32 pool, const u32 *header, const u32 *range) {
    u32 source = header[1] + range[0];
    u32 end = source + range[1];

    if (pool == 0) {
        return func_800042C0(source, end, 0, 0);
    }
    return func_80004458(pool, source, end, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004A40.s")

extern void *func_80004A40(s32 pool, void *archive, s32 index);

void *func_80004B4C(void *archive, s32 index) {
    return func_80004A40(0, archive, index);
}

void *func_80004B78(s32 pool, void *archive, s32 index) {
    return func_80004A40(pool, archive, index);
}

void *BinArchive_GetCachedFile(void *archive, s32 index) {
    u8 *base = archive;

    if ((u32)index >= *(u32 *)(base + 0xC)) {
        return NULL;
    }
    return *(void **)(base + (index * 0x10) + 0x18);
}
#endif
