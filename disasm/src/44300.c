#include "global.h"


#ifdef VERSION_US
extern s32 D_80094CF0; s32 func_80043700(s32 arg0, s32 arg1) { if (!arg0) { D_80094CF0 = arg1; } return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043714.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_800437B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043950.s")

void func_80043A0C(void *arg0, void *arg1, s32 arg2) { func_80043950(arg0, arg1, 0, arg2); }

void func_80043A30(void *arg0, void *arg1, s32 arg2) { func_80043950(arg0, arg1, 1, arg2); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043A54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043AA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043AEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043B48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043B8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043BD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043C14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043E70.s")

typedef struct B4410Value B4410Value; typedef struct B4410Entry B4410Entry; typedef struct B4410State B4410State; struct B4410Value { u8 pad[8]; s32 value; }; struct B4410Entry { u8 pad[0x18]; B4410Value *value; u8 tail[8]; }; struct B4410State { u8 pad0[2]; s16 count; u8 pad4[8]; B4410Entry *entries; };
s32 func_8004410C(B4410State *arg0, s32 arg1) { s32 result = 0; if (arg1 < arg0->count) { result = arg0->entries[arg1].value->value; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80044144.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_8004418C.s")

extern s8 D_80094CF4; void func_80044250(s8 value) { D_80094CF4 = value; }
#endif
