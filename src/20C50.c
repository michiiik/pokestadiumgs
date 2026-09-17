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

typedef struct { char pad[0x18A]; s16 unk_18A; s16 unk_18C; s16 unk_18E; } GS_DecodeInner;
typedef struct { GS_DecodeInner unk_0000; char pad_190[0x1408]; u32 unk_1598[0x400]; char pad_2598[0x24]; u32 unk_25BC; } GS_DecodeState;
typedef struct { s16 xRotA; s16 xRotB; s16 flag0; s16 yRotA; s16 yRotB; s16 flag1; s16 zRotA; s16 zRotB; s16 flag2; s16 unkA; s16 unkB; s16 unkC; s16 unkD; } GS_XMc;
extern void _bzero(void *, s32);
#define GSM_STREAM_WORD(state, pos) (((u32 *)(state)->unk_1598)[((pos) >> 5) & 0x3FF])
#define READ_BITS(dst, n) if (bitsLeft > (n)) { (dst) = window & ((1 << (n)) - 1); window >>= (n); bitsLeft -= (n); } else { (dst) = window & ((1 << bitsLeft) - 1); pos += 32; window = GSM_STREAM_WORD(state, pos); if (bitsLeft != (n)) { (dst) |= (window & ((1 << ((n) - bitsLeft)) - 1)) << bitsLeft; } window >>= (n) - bitsLeft; bitsLeft += 32 - (n); }
s32 func_800205C0(GS_DecodeState* state, void* arg1) {
    s16 LARc[8];
    s16 Nc[4];
    s16 Mc[4];
    s16 bc[4];
    s16 xmaxc[4];
    GS_XMc xM[4];
    s32 unused; // required for the stack layout to match
    s32 bitsLeft;
    s32 i;
    s32 pos;
    u32 window;
    s32 bitOffset;

    pos = state->unk_25BC;
    bitOffset = pos & 0x1F;
    window = GSM_STREAM_WORD(state, pos) >> bitOffset;
    bitsLeft = 32 - bitOffset;

    if ((state->unk_0000.unk_18A == 0) && (state->unk_0000.unk_18C == 0)) {
        READ_BITS(i, 1);
        if (i != 0) {
            READ_BITS(state->unk_0000.unk_18C, 4);
            state->unk_0000.unk_18C++;
        } else {
            READ_BITS(state->unk_0000.unk_18A, 7);
            state->unk_0000.unk_18A++;
        }
    }

    if (state->unk_0000.unk_18C != 0) {
        _bzero(arg1, 160 * sizeof(s16));
        state->unk_0000.unk_18C--;
    } else {
        READ_BITS(LARc[0], 6);
        READ_BITS(LARc[1], 6);
        READ_BITS(LARc[2], 5);
        READ_BITS(LARc[3], 5);
        READ_BITS(LARc[4], 4);
        READ_BITS(LARc[5], 4);
        READ_BITS(LARc[6], 3);
        READ_BITS(LARc[7], 3);

        for (i = 0; i < 4; i++) {
            READ_BITS(Nc[i], 7);
            READ_BITS(bc[i], 2);
            READ_BITS(Mc[i], 2);
            READ_BITS(xmaxc[i], 6);
            READ_BITS(xM[i].xRotA, 3);
            READ_BITS(xM[i].xRotB, 3);
            READ_BITS(xM[i].flag0, 3);
            READ_BITS(xM[i].yRotA, 3);
            READ_BITS(xM[i].yRotB, 3);
            READ_BITS(xM[i].flag1, 3);
            READ_BITS(xM[i].zRotA, 3);
            READ_BITS(xM[i].zRotB, 3);
            READ_BITS(xM[i].flag2, 3);
            READ_BITS(xM[i].unkA, 3);
            READ_BITS(xM[i].unkB, 3);
            READ_BITS(xM[i].unkC, 3);
            READ_BITS(xM[i].unkD, 3);
        }

        state->unk_0000.unk_18A--;
        Anim_BuildTransformCurves(state, LARc, Nc, bc, Mc, xmaxc, xM, (s32)arg1);
    }

    state->unk_25BC = (pos & ~0x1F) - bitsLeft + 32;
    return 0;
}
#endif
