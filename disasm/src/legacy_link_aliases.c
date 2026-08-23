#include "global.h"

#ifdef VERSION_US

extern void Memmap_SegmentCleanupCallback(void *arg0, u32 vaddr);
extern void Memmap_FragmentCleanupCallback(void *arg0, u32 vaddr);
extern void Fragment_RelocateAndReset(void *pool, void *source, void *fragment);
 #endif
