#include "global.h"


#ifdef VERSION_US
typedef struct S1_unk_D_800FCED8_0000 S1_unk_D_800FCED8_0000;
typedef struct S1_unk_D_800FCED8 S1_unk_D_800FCED8;
typedef struct S1_unk_D_800FCED8_01598 S1_unk_D_800FCED8_01598;
typedef struct S1_unk_D_800FCED8_0198 S1_unk_D_800FCED8_0198;
struct S1_unk_D_800FCED8_0000 {
    /* 0x000 */ char unk000[0x166];
    /* 0x166 */ s16 unk_166;
    /* 0x168 */ char unk168[0x22];
    /* 0x18A */ s16 unk_18A;
    /* 0x18C */ s16 unk_18C;
    /* 0x18E */ s16 unk18E;
};
struct S1_unk_D_800FCED8_01598 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ u32 unk_04;
};
struct S1_unk_D_800FCED8_0198 {
    /* 0x000 */ char unk_0000[0x1400];
};
typedef void (*S1_unk_D_800FCED8_190)(s32, S1_unk_D_800FCED8_01598*, s32, OSMesgQueue*);
struct S1_unk_D_800FCED8 {
    /* 0x0000 */ S1_unk_D_800FCED8_0000 unk_0000; // AudioStream_OpenChannel: _bzero'd each open, unk_166 set to 0x28
    /* 0x0190 */ S1_unk_D_800FCED8_190 dmaReadFunc; // AudioStream_OpenChannel's arg2 (e.g. AudioStream_DmaReadChunk)
    /* 0x0194 */ s32 dmaBaseAddr; // AudioStream_OpenChannel's arg1; base ROM offset for DMA reads
    /* 0x0198 */ S1_unk_D_800FCED8_0198 pcmBuffer; // decoded PCM ring buffer; func_80045FF0's decode destination, aliased via D_800FCEE0[i] = this+0x198
    /* 0x1598 */ S1_unk_D_800FCED8_01598 unk_1598[1]; // compressed source-data ring, DMA'd via dmaReadFunc; declared size undersells - indexed by (dmaBytesRequested & 0xFFF) >> 3
    /* 0x15A0 */ u32 unk_15A0;
    /* 0x15A4 */ char unk_15A4[0xFF4];
    /* 0x2598 */ u16 chunksRemaining; // AudioStream_RefillAndDecode: decremented per decoded frame
    /* 0x259A */ u16 unk_259A; // set from unk_1598[0]'s header once per chunk; never read afterward
    /* 0x259C */ u32 chunkDwordsRemaining; // AudioStream_RefillAndDecode: decremented by 0x100 as compressed data is DMA'd
    /* 0x25A0 */ OSMesgQueue dmaMsgQueue;
    /* 0x25B8 */ OSMesg dmaMsgBuf;
    /* 0x25BC */ u32 lastChunkOffset; // set to 0x60 on first chunk; feeds dmaBytesConsumed's (>>3 & ~3) calc
    /* 0x25C0 */ u32 dmaBytesConsumed; // derived from lastChunkOffset after each decode iteration
    /* 0x25C4 */ u32 dmaBytesRequested; // AudioStream_RefillAndDecode: incremented by 0x400 per DMA read
    /* 0x25C8 */ s32 samplesConsumed; // AudioStream_ConsumeSamples's playback cursor
    /* 0x25CC */ u32 samplesDecoded; // AudioStream_RefillAndDecode's decode-produced cursor
    /* 0x25D0 */ s8 dmaPending; // AudioStream_RefillAndDecode: 0/1, a DMA read is currently in flight
    /* 0x25D1 */ s8 state; // 0=idle,1=loading,2=readyToMark,3=playing,4=aborted/done (AudioStream_MarkLoaded/Abort)
    /* 0x25D2 */ s8 decodeBudget; // AudioStream_RefillAndDecode: caps decode iterations per call
    /* 0x25D3 */ char unk25D3[0x5];
};
void AudioStream_OpenChannel(S1_unk_D_800FCED8* arg0, s32 arg1, S1_unk_D_800FCED8_190 arg2) {
    _bzero(&arg0->unk_0000, sizeof(S1_unk_D_800FCED8_0000));

    arg0->unk_0000.unk_166 = 0x28;
    arg0->dmaReadFunc = arg2;
    arg0->dmaBaseAddr = arg1;

    osCreateMesgQueue(&arg0->dmaMsgQueue, &arg0->dmaMsgBuf, 1);

    if ((arg1 == 0) || (arg2 == 0)) {
        arg0->state = 0;
    } else {
        arg0->state = 1;
    }

    arg0->dmaPending = 0;
    arg0->chunksRemaining = arg0->chunkDwordsRemaining = arg0->unk_259A = 0;
    arg0->lastChunkOffset = 0;
    arg0->dmaBytesRequested = 0;
    arg0->dmaBytesConsumed = 0;
    arg0->samplesDecoded = 0;
    arg0->samplesConsumed = 0;
    arg0->decodeBudget = 2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/208A0/func_8001FD50.s")

u32 func_8001FFB0(u8 *arg0, u32 arg1) {
    u32 temp_v0;
    u32 var_a2;
    if (*(s8 *)(arg0 + 0x25D1) == 3) {
        temp_v0 = *(u32 *)(arg0 + 0x25CC) - *(s32 *)(arg0 + 0x25C8);
        if (arg1 < temp_v0) var_a2 = arg1;
        else {
            var_a2 = temp_v0;
            if (*(u16 *)(arg0 + 0x2598) <= 0) *(s8 *)(arg0 + 0x25D1) = 4;
        }
        *(s32 *)(arg0 + 0x25C8) += var_a2;
        return var_a2;
    }
    return 0;
}

void func_80020018(u8 *arg0) { if (*(s8 *)(arg0 + 0x25D1) == 2) { arg0[0x25D1] = 3; } }

void func_80020038(u8 *arg0) {
    arg0[0x25D1] = 4;
}
#endif
