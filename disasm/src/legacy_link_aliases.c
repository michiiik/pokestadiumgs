#include "global.h"

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/226C0/LinkAlias_func_80021B00.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/226C0/LinkAlias_func_80021B74.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/LinkAlias_func_80035174.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/LinkAlias_func_800353BC.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/LinkAlias_func_80035494.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/LinkAlias_func_800355D4.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/LinkAlias_func_800355E4.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/LinkAlias_func_800561E4.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/LinkAlias_func_8007214C.s")

extern u32 MainPool_GetAllocationSize(void *fragment);
extern void Audio_DispatchCommand(s32 eventId);
extern void GbTower_StartPortSession(s32 port);
extern void GbTower_UpdatePortState(s32 port);

#define LEGACY_DECL(addr) extern void func_##addr(void);
LEGACY_DECL(80002DE4)
LEGACY_DECL(80021ED8)
LEGACY_DECL(8005ADD8)
LEGACY_DECL(8005A364)
#define LEGACY_CALL(addr) func_##addr
u32 MainPool_GetAllocationSize(void *fragment) { return ((u32 (*)(void *))LEGACY_CALL(80002DE4))(fragment); }
void Audio_DispatchCommand(s32 eventId) { ((void (*)(s32))LEGACY_CALL(80021ED8))(eventId); }
void GbTower_StartPortSession(s32 port) { ((void (*)(s32))LEGACY_CALL(8005ADD8))(port); }
void GbTower_UpdatePortState(s32 port) { ((void (*)(s32))LEGACY_CALL(8005A364))(port); }
#undef LEGACY_CALL

extern void Memmap_SegmentCleanupCallback(void *arg0, u32 vaddr);
extern void Memmap_FragmentCleanupCallback(void *arg0, u32 vaddr);
extern void Fragment_RelocateAndReset(void *pool, void *source, void *fragment);
extern unsigned char D_800D045C[];
#define LEGACY_FUNC(prefix, a, b, c, d, e, f, g, h) \
    prefix##a##b##c##d##e##f##g##h
void LEGACY_FUNC(func_, 8, 0, 0, 0, 4, 5, E, 0)(void *arg0, u32 vaddr) {
    Memmap_SegmentCleanupCallback(arg0, vaddr);
}
void LEGACY_FUNC(func_, 8, 0, 0, 0, 4, 6, C, 0)(void *arg0, u32 vaddr) {
    Memmap_FragmentCleanupCallback(arg0, vaddr);
}
void LEGACY_FUNC(func_, 8, 0, 0, 0, 4, 7, B, 0)(void *pool, void *source,
                                                   void *fragment) {
    Fragment_RelocateAndReset(pool, source, fragment);
}
void LEGACY_FUNC(func_, 8, 0, 0, 0, 6, A, 7, 8)(void *request, s32 mode) {
    if (mode == 1) {
        osJamMesg((OSMesgQueue *)D_800D045C, (OSMesg)request, 1);
    } else {
        osSendMesg((OSMesgQueue *)D_800D045C, (OSMesg)request, 1);
    }
}
#undef LEGACY_FUNC
 #endif
