#include "global.h"


#ifdef VERSION_US
u16 Jpeg_ReadBigEndianU16(const u8 *arg0) {
    return (u16)((arg0[0] << 8) | arg0[1]);
}

typedef struct S1_JpegMarkerState4420 {
    u8 chromaSubsamplingMode;
    u8 hasRestartMarkers;
    u8 pad02[2];
    s16 width;
    s16 height;
    u8 *quantization_table;
    u8 *huffman_table;
    u8 *start_of_frame;
    u8 *start_of_scan;
} S1_JpegMarkerState4420;
void func_80003838(S1_JpegMarkerState4420 *arg0, u8 *arg1) {
    s32 temp_v0_2;
    s32 var_s2;
    s32 var_v0;
    u8 temp_t6;
    s32 temp_v0;

    var_s2 = 1;
    arg0->hasRestartMarkers = 0;
    while (var_s2 != 0) {
        if (*arg1++ == 0xFF) {
            temp_v0 = *arg1++;
            switch (temp_v0) {
                case 0:
                    break;
                case 0xD9:
                    var_s2 = 0;
                    break;
                case 0xDB:
                    arg0->quantization_table = arg1 + 2;
                    arg1 += Jpeg_ReadBigEndianU16(arg1);
                    break;
                case 0xC4:
                    arg0->huffman_table = arg1 + 2;
                    arg1 += Jpeg_ReadBigEndianU16(arg1);
                    break;
                case 0xC0:
                    arg0->start_of_frame = arg1 + 2;
                    arg1 += Jpeg_ReadBigEndianU16(arg1);
                    break;
                case 0xDA:
                    arg1 += Jpeg_ReadBigEndianU16(arg1);
                    arg0->start_of_scan = arg1;
                    break;
                case 0xD8:
                    break;
                default:
                    if ((temp_v0 >= 0xD0) && (temp_v0 <= 0xD7)) {
                        arg0->hasRestartMarkers = 1;
                    } else {
                        arg1 += Jpeg_ReadBigEndianU16(arg1);
                    }
                    break;
            }
        }
    }
    if (arg0->start_of_frame[7] == 0x21) {
        arg0->chromaSubsamplingMode = 0;
    } else {
        arg0->chromaSubsamplingMode = 2;
    }
    arg0->width = (arg0->start_of_frame[3] << 8) | arg0->start_of_frame[4];
    arg0->height = (arg0->start_of_frame[1] << 8) | arg0->start_of_frame[2];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800039C8.s")

void func_80003A78(u8 *arg0, u8 *arg1, u8 *arg2) {
    *(u32 *)(arg0 + 0x00) = *(u32 *)(arg2 + 0x14);
    *(u8 *)(arg0 + 0x04) = *(u8 *)(arg2 + 0x00);
    *(u8 *)(arg0 + 0x05) = 2;
    *(u32 *)(arg0 + 0x08) = (u32)arg1;
    *(u32 *)(arg0 + 0x0C) = (u32)(arg1 + 0xA8);
    *(u32 *)(arg0 + 0x10) = (u32)(arg1 + 0x54);
    *(u32 *)(arg0 + 0x14) = (u32)(arg1 + 0xFC);
    *(u8 *)(arg0 + 0x18) = *(u8 *)(arg2 + 0x01);
}

typedef struct S1_unk_func_80003680_sp90 S1_unk_func_80003680_sp90;
typedef struct S1_unk_func_80003680_sp300 S1_unk_func_80003680_sp300;
struct S1_unk_func_80003680_sp300 {
    /* 0x00 */ u8 chromaSubsamplingMode; // Jpeg_ParseStreamMarkers: 0/2 from the 2nd component's id byte; feeds Jpeg_BuildDspInput/Output
    /* 0x01 */ u8 hasRestartMarkers; // Jpeg_ParseStreamMarkers: set when a JPEG_MARKER_RESTARTn is seen
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ s16 width;
    /* 0x06 */ s16 height;
    /* 0x08 */ u8* quantization_table;
    /* 0x0C */ u8* huffman_table;
    /* 0x10 */ u8* start_of_frame;
    /* 0x14 */ u8* start_of_scan;
};
struct S1_unk_func_80003680_sp90 {
    /* 0x00 */ s32 unk_00; // Jpeg_BuildDspOutput: always 0
    /* 0x04 */ s32 unk_04; // Jpeg_BuildDspOutput: always 1
    /* 0x08 */ s32 chromaSubsamplingMode; // mirrors S1_unk_func_80003680_sp300's chromaSubsamplingMode
    /* 0x0C */ s32 outputBufferA; // (u32)&arg1[0], segment-masked
    /* 0x10 */ s32 outputBufferB; // (u32)&arg1[1], segment-masked
    /* 0x14 */ s32 outputBufferC; // Jpeg_BuildDspOutput: also (u32)&arg1[1] - same value as outputBufferB
};
void Jpeg_BuildDspOutput(S1_unk_func_80003680_sp90* arg0, u8(arg1)[2][0x80], S1_unk_func_80003680_sp300* arg2) {
    arg0->unk_00 = 0;
    arg0->chromaSubsamplingMode = arg2->chromaSubsamplingMode;
    arg0->unk_04 = 1;
    arg0->outputBufferA = (u32)&arg1[0] & 0x1FFFFFFF;
    arg0->outputBufferB = (u32)&arg1[1] & 0x1FFFFFFF;
    arg0->outputBufferC = (u32)&arg1[1] & 0x1FFFFFFF;
}

typedef struct S1_UnkStruct80001380 S1_UnkStruct80001380;
typedef struct S1_unk_func_80003680_sp60 S1_unk_func_80003680_sp60;
typedef struct S1_unk_func_80003680_sp27 S1_unk_func_80003680_sp27;
typedef struct S1_JpegHuffmanTable S1_JpegHuffmanTable;
struct S1_UnkStruct80001380 {
      OSMesg mesg;
      OSMesgQueue queue;
      u16 state;
      u16 notifyFlag;
      OSTask task;
      char unk60[0x8];
};
struct S1_unk_func_80003680_sp60 {
      s32 readOffset;
      u8 bitCount;
      u8 lastByteWasFF;
      s32 bitAccumulator;
      s16 lumaDcPred;
      s16 chromaDcPred1;
      s16 chromaDcPred2;
};
struct S1_unk_func_80003680_sp27 {
      s32 unk_00;
      u8 chromaSubsamplingMode;
      u8 subsamplingVariant;
      S1_JpegHuffmanTable* dcLumaTable;
      S1_JpegHuffmanTable* acLumaTable;
      S1_JpegHuffmanTable* dcChromaTable;
      S1_JpegHuffmanTable* acChromaTable;
      s8 unk_18;
};
struct S1_JpegHuffmanTable {
      u8 codeOffs[16];
      u16 codesA[16];
      u16 codesB[16];
      u8* symbols;
};
s32 Jpeg_DecodeImage(u32 addr, s32 arg1, u8 *arg2)
{
  S1_UnkStruct80001380 sp318;
  S1_unk_func_80003680_sp300 sp300;
  u8 sp200[2][0x80];
  S1_JpegHuffmanTable spB0[4];
  u16 *temp_s0;
  u8 *temp_s3;
  S1_unk_func_80003680_sp90 sp90;
  S1_unk_func_80003680_sp27 sp74;
  S1_unk_func_80003680_sp60 sp60;
  u32 var_s1;
  s32 i;
  s32 j;
  u8 var_s4 = 0;
  s32 var_s2 = 0;
  temp_s3 = Util_Malloc(0x110);
  temp_s0 = Util_Malloc(0x210);
  func_80003838(&sp300, arg2);
  func_8000B780(sp300.quantization_table, sp200, 2);
  func_8000BA3C(sp300.huffman_table, spB0, temp_s3, temp_s0, 4);
  Util_Free(temp_s0);
  Util_Free(temp_s3);
  func_80003A78(&sp74, &spB0, &sp300);
  Jpeg_BuildDspOutput(&sp90, &sp200, &sp300);
  func_800039C8(&sp318, &sp90);
  while (func_8000204C() == 0)
  {
  }

  for (i = 0; i < sp300.height; i += 16)
  {
    for (j = 0; j < sp300.width; j += 16)
    {
      if (arg1 < ((var_s2 ^ 0) + 0x300))
      {
        return 0;
      }
      if (func_8000BC90(&sp74, addr, 1, var_s4 & 0xFF, &sp60) != 0)
      {
        return 0;
      }
      sp90.unk_00 = addr & 0x1FFFFFFF;
      Sched_SubmitTask(&sp318, 1);
      var_s4 = 1;
      func_80004BEC(&sp318);
      addr += 0x200;
      if (1)
      {
      }
      var_s2 += 0x200;
    }

  }

  return var_s2;
}

void Dma_InitializeCompletionQueue(void) { extern OSMesgQueue D_800CD000; extern OSMesg D_800CD018[]; osCreateMesgQueue(&D_800CD000, D_800CD018, 1); }

typedef struct S1_PERSSZP S1_PERSSZP;
struct S1_PERSSZP {
    /* 0x00 */ char magic[0x8]; // PERS-SZP
    /* 0x08 */ u32 header_size;
    /* 0x0C */ u32 decompressed_size1; // How do these differ?
    /* 0x10 */ u32 decompressed_size2;
    /* 0x14 */ u32 relocationCount; // Yay0_DecompressAndRelocate: (value, offset) pair count following the header
};
void Yay0_DecompressAndRelocate(u8* in_header, u8* memory) {
    UNUSED s32 pad2;
    S1_PERSSZP* header = in_header;
    u32* sp2C = (u32*)header + 6;
    UNUSED s32 pad;
    s32 sp24 = header->decompressed_size2 - header->decompressed_size1;
    u32 var_v0;

    osInvalICache(memory, header->decompressed_size2);
    osInvalDCache(memory, header->decompressed_size2);

    func_8000B6C0(in_header + header->header_size, memory);

    for (var_v0 = 0; var_v0 < header->relocationCount; var_v0++) {
        *(u32*)(memory + sp2C[1]) = sp2C[0];
        sp2C += 2;
    }

    if (sp24 != 0) {
        _bzero(memory + header->decompressed_size1, sp24);
    }

    osWritebackDCache(memory, header->decompressed_size2);
}

extern OSMesgQueue D_800CD000;
extern void Storage_QueueSramTransfer(s32, u8 *, s32, s32, OSMesgQueue *, s32);
void Dma_ReadChunks(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_s0;
    for (; arg2 > 0; arg2 -= var_s0) {
        if (arg2 >= 0x1000) var_s0 = 0x1000; else var_s0 = arg2;
        Storage_QueueSramTransfer(arg3, arg0, arg1, var_s0, &D_800CD000, 0);
        osRecvMesg(&D_800CD000, NULL, 1);
        arg0 += var_s0;
        arg1 += var_s0;
    }
}

extern void Storage_QueueFlashTransfer(s32, s32, s16, OSMesgQueue *, s32);
s32 func_80003E84(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    OSMesg message;
    while (arg2 > 0) {
        Storage_QueueFlashTransfer(arg3, arg0, (s16)arg1, &D_800CD000, 0);
        osRecvMesg(&D_800CD000, &message, 1);
        if (arg3 == 1 && osFlashWriteArray(arg1) != 0) {
            return -1;
        }
        arg2--;
        arg0 += 0x80;
        arg1++;
    }
    return 0;
}

s32 func_80003F54(s32 arg0) { return osFlashSectorErase(arg0 << 7); }

extern void Dma_QueueRomRead(s32, u8 *, u8 *, s32, OSMesgQueue *, s32);
void func_80003F74(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    s32 remaining = arg2 - arg1;
    s32 chunk;
    while (remaining > 0) {
        chunk = remaining >= 0x1000 ? 0x1000 : remaining;
        Dma_QueueRomRead(arg3, arg0, arg1, chunk, &D_800CD000, 0);
        osRecvMesg(&D_800CD000, NULL, 1);
        remaining -= chunk;
        arg0 += chunk;
        arg1 += chunk;
    }
}

extern void Storage_QueueRomWrite(u8 *, u8 *, s32, OSMesgQueue *, s32);
void Dma_CopyChunks(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 remaining = arg2 - arg1;
    s32 chunk;
    while (remaining > 0) {
        chunk = remaining >= 0x1000 ? 0x1000 : remaining;
        Storage_QueueRomWrite(arg0, arg1, chunk, &D_800CD000, 0);
        osRecvMesg(&D_800CD000, NULL, 1);
        remaining -= chunk;
        arg0 += chunk;
        arg1 += chunk;
    }
}

s32 func_800040C4(u8 *arg0) {
    return *(s32 *)(arg0 + 0xC) + 0x100;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800040D0.s")

u8 *func_800041E4(s32 arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    u8 *result;
    if (arg0 == 0) {
        result = main_pool_alloc(*(s32 *)(arg2 + 0x10), arg3);
    } else {
        result = MainPool_AllocAligned(arg0, *(s32 *)(arg2 + 0x10), 0x10);
    }
    if (result != NULL) {
        Yay0_DecompressAndRelocate(arg2, result);
    }
    main_pool_try_free(arg1);
    return result;
}

u8 *func_80004254(s32 arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *result;
    if (arg0 == 0) {
        result = main_pool_alloc(arg4, arg5);
    } else {
        result = MainPool_AllocAligned(arg0, arg4, 0x10);
    }
    if (result != NULL) {
        func_80003F74(result, arg1, arg2, arg3);
    }
    return result;
}

u8 *func_800042C0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u8 *header;
    u8 *data;
    u8 *result;
    s32 mode;
    if (arg2 == 0) {
        mode = 1;
    } else {
        mode = 0;
    }
    header = main_pool_alloc(0x18, mode);
    if (header != NULL) {
        func_80003F74(header, arg0, arg0 + 0x18, arg3);
        if (*(u32 *)header == 0x50455253 && *(u32 *)(header + 4) == 0x2D535A50) {
            data = main_pool_alloc(((arg1 - arg0) + 0xF) & ~0xF, mode);
            if (data != NULL) {
                func_80003F74(data, arg0, arg1, arg3);
                result = func_800041E4(0, data, data, arg2);
            }
        } else if (*(u32 *)header == 0x50524553 && *(u32 *)(header + 4) == 0x4A504547) {
            data = main_pool_alloc(((arg1 - arg0) + 0xF) & ~0xF, mode);
            if (data != NULL) {
                func_80003F74(data, arg0, arg1, arg3);
                result = func_800040D0(0, data, data, arg2);
            }
        } else {
            result = func_80004254(0, arg0, arg1, arg3, ((arg1 - arg0) + 0xF) & ~0xF, arg2);
        }
        main_pool_try_free(header);
    }
    return result;
}

u8 *func_80004458(s32 arg0, u8 *arg1, u8 *arg2) {
    u8 *header;
    u8 *data;
    u8 *result;
    result = NULL;
    header = main_pool_alloc(0x18, 1);
    if (header != NULL) {
        func_80003F74(header, arg1, arg1 + 0x18, 0);
        if (*(u32 *)header == 0x50455253 && *(u32 *)(header + 4) == 0x2D535A50) {
            data = main_pool_alloc(((arg2 - arg1) + 0xF) & ~0xF, 1);
            if (data != NULL) {
                func_80003F74(data, arg1, arg2, 0);
                result = func_800041E4(arg0, data, data, -1);
            }
        } else if (*(u32 *)header == 0x50524553 && *(u32 *)(header + 4) == 0x4A504547) {
            data = main_pool_alloc(((arg2 - arg1) + 0xF) & ~0xF, 1);
            if (data != NULL) {
                func_80003F74(data, arg1, arg2, 0);
                result = func_800040D0(arg0, data, data, -1);
            }
        } else {
            result = func_80004254(arg0, arg1, arg2, 0, ((arg2 - arg1) + 0xF) & ~0xF, -1);
        }
        main_pool_try_free(header);
    }
    return result;
}

extern u32 Memmap_GetSegmentBaseVaddr(u32);
extern void Memmap_ClearSegmentMemmap(u32);
void func_800045E0(void *base_addr, u32 addr) {
    u32 sp1C;
    s32 temp_a0;
    if ((addr & 0xFF000000) == 0x82000000) {
        sp1C = addr & 0xFFFFFF;
        temp_a0 = Memmap_GetSegmentBaseVaddr(sp1C);
        if (temp_a0 == (u32)base_addr) {
            Memmap_ClearSegmentMemmap(sp1C);
        }
    }
}

extern u8 *func_800042C0(u8 *, u8 *, s32, s32);
extern s32 MainPool_GetAllocationSize(u8 *);
extern void Memmap_SetSegmentMap(s32, u8 *, s32);
extern void main_pool_set_func(u8 *, s32, void *);
extern void func_800045E0(void *, u32);
u8 *Asset_LoadToSegment(s32 id, u8 *rom_start, u8 *rom_end, s32 arg3) {
    u8 *vaddr = func_800042C0(rom_start, rom_end, arg3, 0);
    if (vaddr != NULL && id > 0) {
        Memmap_SetSegmentMap(id, vaddr, MainPool_GetAllocationSize(vaddr));
        main_pool_set_func(vaddr, id + 0x82000000, (void *)func_800045E0);
    }
    return vaddr;
}

void func_800046C0(u32 base_addr, u32 addr) {
    u32 sp1C;
    u32 temp_a0;

    if ((addr & 0xFF000000) == 0x81000000) {
        sp1C = addr & 0xFFFFFF;
        if (Memmap_GetFragmentBaseVaddr(sp1C) == base_addr) {
            Memmap_ClearFragmentMemmap(sp1C);
        }
    }
}

void func_80004718(s32 arg0, u8 *arg1) {
    UNUSED s32 pad;
    s32 allocationSize;
    u32 sizeInRam;
    allocationSize = MainPool_GetAllocationSize(arg1);
    main_pool_set_func(arg1, arg0 + 0x81000000, (void *)func_800046C0);
    sizeInRam = *(u32 *)(arg1 + 0x1C);
    if ((u32)allocationSize < sizeInRam) {
        main_pool_realloc(arg1, sizeInRam);
        Memmap_RelocateFragment(arg0, arg1);
        return;
    }
    Memmap_RelocateFragment(arg0, arg1);
    main_pool_realloc(arg1, *(u32 *)(arg1 + 0x1C));
}

#define RELOCATIONS_SIZE 1
typedef struct S1_Fragment S1_Fragment;
typedef struct S1_MainPoolState S1_MainPoolState;
typedef struct S1_MainPoolBlock S1_MainPoolBlock;
struct S1_Fragment {
      u32 inst[2];
      char magic[8];
      u32 headerSize;
      u32 relocOffset;
      u32 sizeInRom;
      u32 sizeInRam;
      char data[RELOCATIONS_SIZE];
};
struct S1_MainPoolState {
      s32 freeSpace;
      S1_MainPoolBlock *listHeadL;
      S1_MainPoolBlock *listHeadR;
      struct S1_MainPoolState *prev;
};
typedef void (*S1_AllocateFunc)(struct S1_MainPoolBlock*, u32);
struct S1_MainPoolBlock {
      struct S1_MainPoolBlock *prev;
      struct S1_MainPoolBlock *next;
      S1_AllocateFunc func;
      s32 arg;
};
void func_800047B0(S1_MainPoolState* arg0, u32 arg1, S1_Fragment* arg2) {
    Memmap_RelocateFragment(arg1, arg2);
    MainPool_ResetStateToOffset(arg0, ((u32)arg2 + arg2->sizeInRam) - (u32)arg0->listHeadR);
}

#define RELOCATIONS_SIZE 1
typedef void (*S1_ret_func_80004454)(void);
S1_ret_func_80004454 Fragment_Load(s32 arg0, u8* romStart, u8* romEnd) {
    void* addr = func_800042C0(romStart, romEnd, 0, 0);

    if (addr != NULL) {
        func_80004718(arg0, (S1_Fragment*)addr);
    }
    return addr;
}

typedef struct S1_BinArchive S1_BinArchive;
struct S1_BinArchive {
    union {
        struct {
            /* 0x00 */ u16 flags; // bit0=preloaded-flat, bit1=lazy/two-pass load, bit2=arg3 variant, bit7=buffered load
            /* 0x02 */ u16 fragmentModuleId; // BinArchive_Open's arg3; Fragment_Register's arg0 for FRAGMENT-tagged files
        };
        s32 raw;
    };
    /* 0x04 */ u32 romStart; // BinArchive_Open's romStart, kept for on-demand file loads
    /* 0x08 */ u32 total_size;
    /* 0x0C */ u32 num_files;
};
S1_BinArchive* BinArchive_Open(u8* romStart, u8* romEnd, s32 arg2, s32 arg3) {
    S1_BinArchive* ret = NULL;
    u32 sp28;
    u32 sp28_2;
    u16* newaddr;

    switch (arg2) {
        case 0:
            newaddr = func_800042C0(romStart, romEnd, 0, 0);
            ret = newaddr;
            if (newaddr != NULL) {
                newaddr[0] |= 1;
            }
            break;

        case 1:
            newaddr = func_800042C0(romStart, romStart + 0x20, 0, 0);
            ret = newaddr;
            if (newaddr != NULL) {
                sp28 = (ret->num_files * 0x10) + 0x10;
                main_pool_try_free(ret);
                newaddr = func_800042C0(romStart, romStart + sp28, 0, 0);
                ret = newaddr;
                if (newaddr != NULL) {
                    *newaddr |= 2;
                    if (arg3 == 1) {
                        *newaddr |= 4;
                    }
                }
            }
            break;

        case 2:
            newaddr = func_800042C0(romStart, romStart + 0x20, 1, 0);
            ret = newaddr;
            if (newaddr != NULL) {
                sp28_2 = (ret->num_files * 0x10) + 0x10;
                main_pool_try_free(ret);
                newaddr = func_800042C0(romStart, romStart + sp28_2, 1, 0);
                ret = newaddr;
                if ((newaddr != NULL) && (arg3 == 1)) {
                    *newaddr |= 4;
                }
            }
            break;
    }

    if (ret != NULL) {
        ret->romStart = romStart;
    }

    return ret;
}

void func_800049B8(void) {
    main_pool_try_free();
}

struct S1_BinArchive;
struct S1_BinArchiveFile4420;
extern u8 * func_800042C0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
extern u8 * func_80004458(s32 arg0, u8 *arg1, u8 *arg2);
u8 *func_800049D8(S1_MainPoolState *arg0, struct S1_BinArchive *arg1, struct S1_BinArchiveFile4420 *arg2) {
    UNUSED s32 pad;
    u8 *start;
    u8 *end;
    u8 *result;
    start = (u8 *)(*(u32 *)arg2 + *(u32 *)((u8 *)arg1 + 4));
    end = start + *(u32 *)((u8 *)arg2 + 4);
    if (arg0 == NULL) {
        result = func_800042C0(start, end, 0, 0);
    } else {
        result = func_80004458((s32)arg0, start, end);
    }
    return result;
}

typedef struct S1_BinArchiveFile4420 {
    u32 offset;
    u32 size;
    u32 cachedPtr;
    u32 pad;
} S1_BinArchiveFile4420;
extern u8 *func_800049D8(S1_MainPoolState *, S1_BinArchive *, S1_BinArchiveFile4420 *);
u8 *func_80004A40(poolState, archive, file_number)
S1_MainPoolState *poolState;
S1_BinArchive *archive;
s32 file_number;
{
    u8 *result;
    UNUSED s32 pad;
    S1_BinArchiveFile4420 *file;
    result = NULL;
    file = (S1_BinArchiveFile4420 *)((u8 *)archive + 0x10 + (file_number * 0x10));
    if ((u32)file_number < archive->num_files) {
        if (archive->flags & 1) {
            result = (u8 *)archive + file->offset;
        } else if (!(archive->flags & 4) && file->cachedPtr != 0) {
            result = (u8 *)file->cachedPtr;
        } else {
            result = func_800049D8(poolState, archive, file);
            if (result != NULL) {
                if (*(u32 *)(result + 8) == 0x46524147 && *(u32 *)(result + 0xC) == 0x4D454E54) {
                    if (poolState == NULL) {
                        func_80004718(archive->fragmentModuleId, result);
                    } else {
                        func_800047B0(poolState, archive->fragmentModuleId, (S1_Fragment *)result);
                    }
                }
                file->cachedPtr = (u32)result;
            }
        }
    }
    return result;
}

void func_80004B4C(s32 arg0, s32 arg1) {
    func_80004A40(0, arg0, arg1);
}

void func_80004B78(void) {
    func_80004A40();
}

typedef struct { u32 offset; u32 size; s32 cachedPtr; u32 pad; } BinFile;
typedef struct { u32 raw0; u32 romStart; u32 total_size; u32 num_files; BinFile files[1]; } BinArchive;
s32 BinArchive_GetCachedFile(BinArchive *archive, s32 file_number) {
    s32 result = 0;
    if ((u32)file_number < archive->num_files) result = archive->files[file_number].cachedPtr;
    return result;
}
#endif
