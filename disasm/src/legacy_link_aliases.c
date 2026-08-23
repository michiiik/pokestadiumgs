#include "global.h"

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/3280/LinkAlias_func_80002DE4.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/LinkAlias_func_80017B00.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/LinkAlias_func_80035174.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/LinkAlias_func_800353BC.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/LinkAlias_func_80035494.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/LinkAlias_func_800355D4.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/LinkAlias_func_800355E4.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/LinkAlias_func_800561E4.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/LinkAlias_func_8007214C.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/LinkAlias_func_8290D738.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/LinkAlias_func_8290D7C8.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/LinkAlias_func_8290D858.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/LinkAlias_func_8290D8EC.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/LinkAlias_func_8290D980.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/LinkAlias_func_8290DA10.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/LinkAlias_func_8290DAA4.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/LinkAlias_func_8290DB3C.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/LinkAlias_func_8290DBD0.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/LinkAlias_func_8290DC60.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/LinkAlias_func_8290DCF0.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/LinkAlias_func_8290DD80.s")

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
 #endif
