#include "global.h"


#ifdef VERSION_US
typedef struct { s16 unk0,unk2,unk4,unk6,unk8,unkA,unkC,unkE; } AnimBlock;
typedef struct { char pad[0x168]; AnimBlock blocks[2]; s16 index; } AnimState;
extern void func_80021834(void *, s32, s32);
void Anim_UpdateDoubleBufferedTransform(AnimState *arg0, AnimBlock *arg1, s32 arg2, s32 arg3) {
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

typedef struct S1_AnimBlock19 {
    s16 xRotA;
    s16 xRotB;
    s16 flag0;
    s16 yRotA;
    s16 yRotB;
    s16 flag1;
    s16 zRotA;
    s16 zRotB;
    s16 flag2;
    s16 unkA;
    s16 unkB;
    s16 unkC;
    s16 unkD;
} S1_AnimBlock19;
typedef struct S1_unk_arg1_func_80045A80 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkE;
} S1_unk_arg1_func_80045A80;
typedef struct S1_unk_arg0_func_80045A80 {
    char pad0[0x168];
    S1_unk_arg1_func_80045A80 unk168[2];
    s16 unk188;       // 0x188
} S1_unk_arg0_func_80045A80;
typedef struct S1_unk_arg1_func_80045D60 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
} S1_unk_arg1_func_80045D60;
void Anim_BuildTransformCurves(S1_unk_arg0_func_80045A80* arg0, S1_unk_arg1_func_80045A80* arg1, s16* arg2, s16* arg3, s16* arg4, s16* arg5, S1_AnimBlock19* arg6, s32 arg7) {
    s32 i;
    s16 sp44[40];

    for (i = 0; i < 4; i++) {
        func_800214C0(*arg5, *arg4, arg6, sp44);
        func_800215B4(arg0, *arg2, *arg3, sp44);
        arg5++;
        arg3++;
        arg2++;
        arg4++;
        arg6++;
    }


#ifdef CC_CHECK
    Anim_UpdateDoubleBufferedTransform((AnimState *)arg0, (AnimBlock *)arg1, (s32)arg0, arg7);
#else
    Anim_UpdateDoubleBufferedTransform(arg0, arg1, arg0, arg7);
#endif
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/20C50/func_80020330.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/20C50/func_800205C0.s")
#endif
