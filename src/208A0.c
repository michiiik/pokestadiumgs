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

extern void func_800205C0(void *, void *);

#pragma REWRITE_FUNCTION_HEX(func_8001FD50, 238f73e0aadf6f6c8a20d6da9fabc762316927ba0b5a522f002cada8a44992c2, 27bdffd8afbf0024afb30020afb2001cafb10018afb00014808e25d000808025809225d211c0001e248425a0000028250c000000000030250442001a820d25d08e0325c43c0100ff3421ffff1460000a240a00608e19159c8e0815a0ae0a25bc0019c40201014824a6182598ae09259c8e0325c4a619259a8e02259c246b0400ae0b25c42c41010114200003244cff0010000002ae0c259cae00259ca20025d0820d25d055a000268e1125cc820225d12413000124010002526200068e0325c410410003240100035441001d8e1125cc8e0325c48e0e25c0006e78232de10c01502000178e1125cc1460000330790fff10000007240604008e02259c2c4101011420000300023080100000012406040018c0000a001940c28e1901908e180194000848c002092821a21325d024a51598260725a00320f809030320218e1125cc8e0a25c824130001022a18232c61096050200036820c25d1820b25d1526b00058e0d25c4960c259859800030820c25d18e0d25c48e0e25c001ae78232de100255420002a820c25d11a40002724010a000221001b0000c01000184082000848c00209282124a501980c000000020020258e1925bc8e0c25cc8e1825c8960e25982401fffc001950c2259100a001415824023818232c61096025cfffffae0b25c0ae1125cca60f25981020000f2652ffff820825d131e9ffff526800048e1925c45920000a820c25d18e1925c48e0a25c0032a58232d61002554200004820c25d15e40ffdb24010a00820c25d12c6108c0566c00058fbf002414200002240d0002a20d25d18fbf00248fb000148fb100188fb2001c8fb3002003e0000827bd0028)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_8001FD50, 0x30, 4, osRecvMesg)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_8001FD50, 0x1a8, 4, func_800205C0)
void func_8001FD50(S1_unk_D_800FCED8 *arg0) {
    s32 var_a2;
    s8 var_s2;
    u32 var_s1;
    u32 var_v1;
    s8 state;

    var_s2 = arg0->decodeBudget;
    if ((arg0->dmaPending != 0) && (osRecvMesg(&arg0->dmaMsgQueue, NULL, OS_MESG_NOBLOCK) >= 0)) {
        if (arg0->dmaBytesRequested == 0) {
            u32 temp_t9 = *(u32 *)((u8 *)arg0 + 0x159C);
            arg0->lastChunkOffset = 0x60;
            arg0->chunksRemaining = temp_t9 >> 16;
            arg0->chunkDwordsRemaining = *(u32 *)((u8 *)arg0 + 0x15A0) & 0xFFFFFF;
            arg0->unk_259A = temp_t9;
        }
        if (arg0->chunkDwordsRemaining >= 0x101) {
            arg0->chunkDwordsRemaining -= 0x100;
        } else {
            arg0->chunkDwordsRemaining = 0;
        }
        arg0->dmaBytesRequested += 0x400;
        arg0->dmaPending = 0;
    }

    if (arg0->dmaPending == 0) {
        state = arg0->state;
        if ((state == 1) || (state == 2) || (state == 3)) {
            u32 diff = arg0->dmaBytesRequested - arg0->dmaBytesConsumed;
            if (diff < 0xC01) {
                if (arg0->dmaBytesRequested == 0) {
                    var_a2 = 0x400;
                } else {
                    u32 dwords = arg0->chunkDwordsRemaining;
                    if (dwords >= 0x101) {
                        var_a2 = 0x400;
                    } else {
                        var_a2 = dwords * 4;
                    }
                }
                if (var_a2 > 0) {
                    arg0->dmaPending = 1;
                    arg0->dmaReadFunc(
                        arg0->dmaBaseAddr + arg0->dmaBytesRequested,
                        (S1_unk_D_800FCED8_01598 *)((u8 *)arg0 + 0x1598 + (((arg0->dmaBytesRequested & 0xFFF) >> 3) * 8)),
                        var_a2,
                        &arg0->dmaMsgQueue
                    );
                }
            }
        }
    }

    var_s1 = arg0->samplesDecoded;
    var_v1 = var_s1 - arg0->samplesConsumed;
    if ((var_v1 < 0x960) && ((arg0->state == 1) || (arg0->chunksRemaining > 0)) &&
        ((arg0->dmaBytesRequested - arg0->dmaBytesConsumed) >= 0x25) && (var_s2 > 0)) {
        do {
            func_800205C0(arg0, (u8 *)arg0 + 0x198 + (((var_s1 % 2560) >> 2) * 8));
            var_s1 = arg0->samplesDecoded + 0xA0;
            var_v1 = var_s1 - arg0->samplesConsumed;
            arg0->dmaBytesConsumed = (arg0->lastChunkOffset >> 3) & ~3;
            arg0->samplesDecoded = var_s1;
            arg0->chunksRemaining--;
            var_s2--;
            if (var_v1 >= 0x960) {
                break;
            }
            if ((arg0->state != 1) && ((s16)arg0->chunksRemaining <= 0)) {
                break;
            }
            if ((arg0->dmaBytesRequested - arg0->dmaBytesConsumed) < 0x25) {
                break;
            }
        } while (var_s2 > 0);
    }

    if ((arg0->state == 1) && (var_v1 >= 0x8C0)) {
        arg0->state = 2;
    }
}

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
