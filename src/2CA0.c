#include "global.h"


#ifdef VERSION_US
extern u8 D_800CC5B0[]; void Memmap_SetSegmentMap(s32 index, s32 value1, s32 value2) { *(s32 *)(D_800CC5B0 + index * 8) = value1; *(s32 *)(D_800CC5B0 + index * 8 + 4) = value2; }

extern u8 D_800CC5B0[]; s32 Memmap_GetSegmentBaseVaddr(s32 index) { return *(s32 *)(D_800CC5B0 + index * 8); }

extern u8 D_800CC5B0[];
u32 Memmap_GetSegmentVaddr(u32 mask) {
    if ((mask >> 0x1C) == 0) {
        u32 id = (mask & 0x0F000000) >> 0x18;
        u32 value = mask & 0x00FFFFFF;
        if (*(u32 *)(D_800CC5B0 + id * 8) != 0) {
            mask = *(u32 *)(D_800CC5B0 + id * 8) + value;
        }
    }
    return mask;
}

s32 Memmap_GetSegmentVaddrMask(s32 arg0, s32 arg1) {
    u8 *ptr = D_800CC5B0 + arg0 * 8;
    u32 offset = (u32)arg1 - *(u32 *)(ptr + 0);
    if (offset >= *(u32 *)(ptr + 4)) return 0;
    return (arg0 << 24) | offset;
}

extern u8 D_800CC5B0[]; void Memmap_ClearSegmentMemmap(s32 index) { *(s32 *)(D_800CC5B0 + index * 8) = 0; *(s32 *)(D_800CC5B0 + index * 8 + 4) = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/func_80002178.s")

extern u32 Memmap_GetFragmentVaddr(u32);
extern void Memmap_SetFragmentMap(s32, s32, s32);
extern void _bzero(void *, s32);
typedef struct MemmapFragment {
    u32 inst[2];
    char magic[8];
    u32 headerSize;
    u32 relocOffset;
    u32 sizeInRom;
    u32 sizeInRam;
    char data[1];
} MemmapFragment;

typedef struct MemmapRelocTable {
    u32 nRelocations;
    u32 relocations[1];
} MemmapRelocTable;

void Memmap_RelocateFragment(u32 id, MemmapFragment *fragment) {
    u32 isLoNeg;
    u32 *luiRefs[32];
    u32 luiVals[32];
    u32 *luiInstRef;
    u32 *relocDataP;
    u32 relocSize;
    MemmapRelocTable *relocInfo;
    UNUSED u32 relocOffset;
    u32 reloc;
    u32 temp_v0_5;
    u32 i;
    u32 *regValP;
    UNUSED s32 pad;

    relocOffset = fragment->relocOffset;
    relocSize = fragment->sizeInRam - fragment->relocOffset;
    relocInfo = (MemmapRelocTable *)((u32)fragment->relocOffset + (u32)fragment);

    osInvalICache(fragment, fragment->sizeInRam);
    osInvalDCache(fragment, fragment->sizeInRam);
    Memmap_SetFragmentMap(id, (u32)fragment, fragment->sizeInRam);

    for (i = 0; i < relocInfo->nRelocations; i++) {
        reloc = relocInfo->relocations[i];
        relocDataP = (u32 *)((reloc & 0xFFFFFF) + (u32)fragment);

        switch ((reloc & 0x7F000000) >> 24) {
            case 2:
                *relocDataP = Memmap_GetFragmentVaddr(*relocDataP);
                break;
            case 4:
                *relocDataP =
                    (((u32)(Memmap_GetFragmentVaddr(((*relocDataP * 4) & 0x0FFFFFFC) + 0x80000000) & 0x0FFFFFFF) >> 2) |
                     (*relocDataP & 0xFC000000));
                break;
            case 5:
                luiRefs[(*relocDataP >> 0x10) & 0x1F] = relocDataP;
                luiVals[(*relocDataP >> 0x10) & 0x1F] = *relocDataP;
                break;
            case 6:
                luiInstRef = luiRefs[(*relocDataP >> 0x15) & 0x1F];
                regValP = &luiVals[(*relocDataP >> 0x15) & 0x1F];

                temp_v0_5 = Memmap_GetFragmentVaddr((*regValP << 0x10) + (s16)*relocDataP);
                isLoNeg = (temp_v0_5 & 0x8000) ? 1 : 0;
                *luiInstRef = (*luiInstRef & 0xFFFF0000) | ((temp_v0_5 >> 16) + isLoNeg);
                *relocDataP = (*relocDataP & 0xFFFF0000) | (temp_v0_5 & 0xFFFF);
                break;
        }
    }
    if (relocSize != 0) {
        _bzero((void *)((u32)fragment->relocOffset + (u32)fragment), relocSize);
    }
    osWritebackDCache(fragment, fragment->sizeInRam);
}

extern u8 D_800CC630[]; void Memmap_SetFragmentMap(s32 index, s32 value1, s32 value2) { *(s32 *)(D_800CC630 + index * 8) = value1; *(s32 *)(D_800CC630 + index * 8 + 4) = value2; }

extern u8 D_800CC630[]; s32 Memmap_GetFragmentBaseVaddr(s32 index) { return *(s32 *)(D_800CC630 + index * 8); }

u32 Memmap_GetFragmentVaddr(u32 arg0) {
    u32 index;
    u32 value;

    if ((arg0 >= 0x81000000U) && (arg0 < 0x90000000U)) {
        index = ((arg0 & 0x0FF00000) >> 0x14) - 0x10;
        value = arg0 & 0xFFFFF;
        if (*(u32 *)(D_800CC630 + index * 8) != 0) {
            arg0 = *(u32 *)(D_800CC630 + index * 8) + value;
        }
    }
    return arg0;
}

extern u8 D_800CC630[];
s32 Memmap_GetFragmentVaddrMask(s32 arg0, s32 arg1) {
    u8 *ptr = D_800CC630 + arg0 * 8;
    u32 offset = (u32)arg1 - *(u32 *)(ptr + 0);
    if (offset >= *(u32 *)(ptr + 4)) return 0;
    return (((arg0 + 0x10) << 20) | 0x80000000) | offset;
}

extern u8 D_800CC630[]; void Memmap_ClearFragmentMemmap(s32 index) { *(s32 *)(D_800CC630 + index * 8) = 0; *(s32 *)(D_800CC630 + index * 8 + 4) = 0; }

u32 Memmap_GetLoadedFragmentVaddr(u32 addr) {
    typedef struct {
        u32 vaddr;
        u32 size;
    } MemmapEntry;
    MemmapEntry *fraglist;
    s32 i;
    s32 j;

    for (i = 0, fraglist = (MemmapEntry *)D_800CC630; i < 0xF0; i++, fraglist++) {
        if (addr >= fraglist->vaddr) {
            u32 diff = addr - fraglist->vaddr;
            if (diff < fraglist->size) {
                return ((i + 0x10) << 0x14) | 0x80000000 | diff;
            }
        }
    }
    return 0;
}
#endif
