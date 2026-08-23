#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Jpeg_ReadBigEndianU16.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Jpeg_ParseStreamMarkers.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Jpeg_InitializeDspTask.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Jpeg_BuildDspInput.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Jpeg_BuildDspOutput.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Jpeg_DecodeImage.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Dma_InitializeCompletionQueue.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Yay0_DecompressAndRelocate.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Dma_ReadChunks.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Dma_CopyChunks.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800040C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800040D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800041E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004254.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800042C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004458.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Memmap_SegmentCleanupCallback.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Asset_LoadToSegment.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Memmap_FragmentCleanupCallback.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Fragment_Register.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Fragment_RelocateAndReset.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/Fragment_Load.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/BinArchive_Open.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800049B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800049D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004B4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004B78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/BinArchive_GetCachedFile.s")
#endif
