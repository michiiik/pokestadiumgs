#include "global.h"


#ifdef VERSION_US
typedef struct { s16 unk0,unk2,unk4,unk6,unk8,unkA,unkC,unkE; } AnimBlock;
typedef struct { char pad[0x168]; AnimBlock blocks[2]; s16 index; } AnimState;
extern void func_80021834(void *, s32, s32);
void func_80020050(AnimState *arg0, AnimBlock *arg1, s32 arg2, s32 arg3) {
    AnimBlock *dst = &arg0->blocks[arg0->index];
    dst->unk0 = (s16)(((((arg1->unk0 - 0x20) << 10) * 0x3333 + 0x4000) >> 15) * 2);
    dst->unk2 = (s16)(((((arg1->unk2 - 0x20) << 10) * 0x3333 + 0x4000) >> 15) * 2);
    dst->unk4 = (s16)(((((arg1->unk4 - 0x10) << 10) * 0x3333 - 0x0332F000) >> 15) * 2);
    dst->unk6 = (s16)(((((arg1->unk6 - 0x10) << 10) * 0x3333 + 0x04003C00) >> 15) * 2);
    dst->unk8 = (s16)(((((arg1->unk8 - 8) << 10) * 0x4B17 - 0x0036E4E4) >> 15) * 2);
    dst->unkA = (s16)(((((arg1->unkA - 8) << 10) * 0x4444 + 0x03BBF800) >> 15) * 2);
    dst->unkC = (s16)(((((arg1->unkC - 4) << 10) * 0x7ADE + 0x0147936C) >> 15) * 2);
    dst->unkE = (s16)(((((arg1->unkE - 4) << 10) * 0x740C + 0x040D6B40) >> 15) * 2);
    func_80021834(arg0, arg2, arg3);
    arg0->index ^= 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/20C50/func_80020248.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/20C50/func_80020330.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/20C50/func_800205C0.s")
#endif
