#include "global.h"

#ifdef VERSION_US

extern void Memmap_SegmentCleanupCallback(void *arg0, u32 vaddr);
extern void Memmap_FragmentCleanupCallback(void *arg0, u32 vaddr);
extern void Fragment_RelocateAndReset(void *pool, void *source, void *fragment);
extern unsigned char D_800D045C[];
#define LEGACY_FUNC(prefix, a, b, c, d, e, f, g, h) \
    prefix##a##b##c##d##e##f##g##h
void LEGACY_FUNC(func_, 8, 0, 0, 0, 6, A, 7, 8)(void *request, s32 mode) {
    if (mode == 1) {
        osJamMesg((OSMesgQueue *)D_800D045C, (OSMesg)request, 1);
    } else {
        osSendMesg((OSMesgQueue *)D_800D045C, (OSMesg)request, 1);
    }
}
#undef LEGACY_FUNC
 #endif
