#include "global.h"


#ifdef VERSION_US
u16 func_80003820(const u8 *arg0) {
    return (u16)((arg0[0] << 8) | arg0[1]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003838.s")

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
    /* 0x00 */ s32 unk_00; // func_80003AB8: always 0
    /* 0x04 */ s32 unk_04; // func_80003AB8: always 1
    /* 0x08 */ s32 chromaSubsamplingMode; // mirrors S1_unk_func_80003680_sp300's chromaSubsamplingMode
    /* 0x0C */ s32 outputBufferA; // (u32)&arg1[0], segment-masked
    /* 0x10 */ s32 outputBufferB; // (u32)&arg1[1], segment-masked
    /* 0x14 */ s32 outputBufferC; // func_80003AB8: also (u32)&arg1[1] - same value as outputBufferB
};
void func_80003AB8(S1_unk_func_80003680_sp90* arg0, u8(arg1)[2][0x80], S1_unk_func_80003680_sp300* arg2) {
    arg0->unk_00 = 0;
    arg0->chromaSubsamplingMode = arg2->chromaSubsamplingMode;
    arg0->unk_04 = 1;
    arg0->outputBufferA = (u32)&arg1[0] & 0x1FFFFFFF;
    arg0->outputBufferB = (u32)&arg1[1] & 0x1FFFFFFF;
    arg0->outputBufferC = (u32)&arg1[1] & 0x1FFFFFFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003AF0.s")

void func_80003CD0(void) { extern OSMesgQueue D_800CD000; extern OSMesg D_800CD018[]; osCreateMesgQueue(&D_800CD000, D_800CD018, 1); }

typedef struct S1_PERSSZP S1_PERSSZP;
struct S1_PERSSZP {
    /* 0x00 */ char magic[0x8]; // PERS-SZP
    /* 0x08 */ u32 header_size;
    /* 0x0C */ u32 decompressed_size1; // How do these differ?
    /* 0x10 */ u32 decompressed_size2;
    /* 0x14 */ u32 relocationCount; // func_80003D00: (value, offset) pair count following the header
};
void func_80003D00(u8* in_header, u8* memory) {
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
extern void func_80006BB4(s32, u8 *, s32, s32, OSMesgQueue *, s32);
void func_80003DD4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_s0;
    for (; arg2 > 0; arg2 -= var_s0) {
        if (arg2 >= 0x1000) var_s0 = 0x1000; else var_s0 = arg2;
        func_80006BB4(arg3, arg0, arg1, var_s0, &D_800CD000, 0);
        osRecvMesg(&D_800CD000, NULL, 1);
        arg0 += var_s0;
        arg1 += var_s0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003E84.s")

s32 func_80003F54(s32 arg0) { return osFlashSectorErase(arg0 << 7); }

extern void func_80006ACC(s32, u8 *, u8 *, s32, OSMesgQueue *, s32);
void func_80003F74(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    s32 remaining = arg2 - arg1;
    s32 chunk;
    while (remaining > 0) {
        chunk = remaining >= 0x1000 ? 0x1000 : remaining;
        func_80006ACC(arg3, arg0, arg1, chunk, &D_800CD000, 0);
        osRecvMesg(&D_800CD000, NULL, 1);
        remaining -= chunk;
        arg0 += chunk;
        arg1 += chunk;
    }
}

extern void func_80006B40(u8 *, u8 *, s32, OSMesgQueue *, s32);
void func_80004024(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 remaining = arg2 - arg1;
    s32 chunk;
    while (remaining > 0) {
        chunk = remaining >= 0x1000 ? 0x1000 : remaining;
        func_80006B40(arg0, arg1, chunk, &D_800CD000, 0);
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800041E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004254.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800042C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004458.s")

extern u32 func_800020BC(u32);
extern void func_8000215C(u32);
void func_800045E0(void *base_addr, u32 addr) {
    u32 sp1C;
    s32 temp_a0;
    if ((addr & 0xFF000000) == 0x82000000) {
        sp1C = addr & 0xFFFFFF;
        temp_a0 = func_800020BC(sp1C);
        if (temp_a0 == (u32)base_addr) {
            func_8000215C(sp1C);
        }
    }
}

extern u8 *func_800042C0(u8 *, u8 *, s32, s32);
extern s32 func_80002DE4(u8 *);
extern void func_800020A0(s32, u8 *, s32);
extern void func_80002DD4(u8 *, s32, void *);
extern void func_800045E0(void *, u32);
u8 *func_80004638(s32 id, u8 *rom_start, u8 *rom_end, s32 arg3) {
    u8 *vaddr = func_800042C0(rom_start, rom_end, arg3, 0);
    if (vaddr != NULL && id > 0) {
        func_800020A0(id, vaddr, func_80002DE4(vaddr));
        func_80002DD4(vaddr, id + 0x82000000, (void *)func_800045E0);
    }
    return vaddr;
}

void func_800046C0(u32 base_addr, u32 addr) {
    u32 sp1C;
    u32 temp_a0;

    if ((addr & 0xFF000000) == 0x81000000) {
        sp1C = addr & 0xFFFFFF;
        if (func_8000248C(sp1C) == base_addr) {
            func_8000254C(sp1C);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004718.s")

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
    func_80002210(arg1, arg2);
    func_800031FC(arg0, ((u32)arg2 + arg2->sizeInRam) - (u32)arg0->listHeadR);
}

#define RELOCATIONS_SIZE 1
typedef void (*S1_ret_func_80004454)(void);
S1_ret_func_80004454 func_800047F8(s32 arg0, u8* romStart, u8* romEnd) {
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
            /* 0x02 */ u16 fragmentModuleId; // func_8000484C's arg3; Fragment_Register's arg0 for FRAGMENT-tagged files
        };
        s32 raw;
    };
    /* 0x04 */ u32 romStart; // func_8000484C's romStart, kept for on-demand file loads
    /* 0x08 */ u32 total_size;
    /* 0x0C */ u32 num_files;
};
S1_BinArchive* func_8000484C(u8* romStart, u8* romEnd, s32 arg2, s32 arg3) {
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
                func_800029E0(ret);
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
                func_800029E0(ret);
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

void func_800049B8(void) { func_800029E0(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800049D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004A40.s")

void func_80004B4C(s32 arg0,s32 arg1){func_80004A40(0,arg0,arg1);}

void func_80004B78(void) { func_80004A40(); }

typedef struct { u32 offset; u32 size; s32 cachedPtr; u32 pad; } BinFile;
typedef struct { u32 raw0; u32 romStart; u32 total_size; u32 num_files; BinFile files[1]; } BinArchive;
s32 func_80004B98(BinArchive *archive, s32 file_number) {
    s32 result = 0;
    if ((u32)file_number < archive->num_files) result = archive->files[file_number].cachedPtr;
    return result;
}
#endif
