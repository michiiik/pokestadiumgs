#include "global.h"

/* Each entry stores the base virtual address and the loaded size for one
 * segment/fragment.  These data labels are not emitted into the generated
 * linker symbol list, so retain their original absolute addresses. */
#define D_800CC5B0 ((u32 *)0x800CC5B0)
#define D_800CC630 ((u32 *)0x800CC630)

void Memmap_SetSegmentMap(s32 segment, u32 base, u32 size) {
    u32 *entry = &D_800CC5B0[segment * 2];
    entry[0] = base;
    entry[1] = size;
}

u32 Memmap_GetSegmentBaseVaddr(s32 segment) {
    return D_800CC5B0[segment * 2];
}

u32 Memmap_GetSegmentVaddr(u32 vaddr) {
    u32 segment;
    u32 offset;
    u32 base;

    if ((vaddr >> 28) == 0) {
        segment = (vaddr >> 24) & 0xF;
        base = D_800CC5B0[segment * 2];
        offset = vaddr & 0x00FFFFFF;
        if (base != 0) {
            vaddr = base + offset;
        }
    }
    return vaddr;
}

u32 Memmap_GetSegmentVaddrMask(s32 segment, u32 vaddr) {
    u32 *entry = &D_800CC5B0[segment * 2];
    u32 offset = vaddr - entry[0];

    if (offset < entry[1]) {
        return ((u32)segment << 24) | offset;
    }
    return 0;
}

void Memmap_ClearSegmentMemmap(s32 segment) {
    u32 *entry = &D_800CC5B0[segment * 2];
    entry[0] = 0;
    entry[1] = 0;
}

void Memmap_SetFragmentMap(s32 fragment, u32 base, u32 size) {
    u32 *entry = &D_800CC630[fragment * 2];
    entry[0] = base;
    entry[1] = size;
}

u32 Memmap_GetFragmentBaseVaddr(s32 fragment) {
    return D_800CC630[fragment * 2];
}

u32 Memmap_GetFragmentVaddr(u32 vaddr) {
    u32 fragment;
    u32 offset;
    u32 base;

    if (vaddr >= 0x81000000 && vaddr < 0x90000000) {
        fragment = ((vaddr >> 20) & 0xFF) - 0x10;
        base = D_800CC630[fragment * 2];
        offset = vaddr & 0x000FFFFF;
        if (base != 0) {
            vaddr = base + offset;
        }
    }
    return vaddr;
}

u32 Memmap_GetFragmentVaddrMask(s32 fragment, u32 vaddr) {
    u32 *entry = &D_800CC630[fragment * 2];
    u32 offset = vaddr - entry[0];

    if (offset < entry[1]) {
        return ((u32)(fragment + 0x10) << 20) | 0x80000000 | offset;
    }
    return 0;
}

void Memmap_ClearFragmentMemmap(s32 fragment) {
    u32 *entry = &D_800CC630[fragment * 2];
    entry[0] = 0;
    entry[1] = 0;
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/Memmap_SetSegments.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/Memmap_RelocateFragment.s")

u32 Memmap_GetLoadedFragmentVaddr(u32 vaddr) {
    s32 fragment;

    for (fragment = 0; fragment < 0x3C; fragment++) {
        u32 *entry = &D_800CC630[fragment * 2];
        u32 offset;

        if (vaddr < entry[0]) {
            continue;
        }
        offset = vaddr - entry[0];
        if (offset < entry[1]) {
            return 0x80000000 | ((u32)(fragment + 0x10) << 20) | offset;
        }
    }
    return 0;
}
#endif
