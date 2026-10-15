#include "global.h"


#ifdef VERSION_US
typedef struct {
    u8 codeOffs[16];
    u16 codesA[16];
    u16 codesB[16];
    u8 *symbols;
} JpegHuffmanTable;
typedef struct {
    u8 *inputBuffer;
    u8 chromaSubsamplingMode;
    u8 subsamplingVariant;
    JpegHuffmanTable *dcLumaTable;
    JpegHuffmanTable *acLumaTable;
    JpegHuffmanTable *dcChromaTable;
    JpegHuffmanTable *acChromaTable;
    s8 unk_18;
} JpegMcuConfig;
typedef struct {
    s32 readOffset;
    u8 bitCount;
    u8 lastByteWasFF;
    u32 bitAccumulator;
    s16 lumaDcPred;
    s16 chromaDcPred1;
    s16 chromaDcPred2;
} JpegMcuState;
extern u8 *D_800D1210;
extern s32 D_800D1214;
extern u8 D_800D1218;
extern u8 Jpeg_LastByteWasFF;
extern u32 D_800D121C;
extern s32 func_8000BEB8(JpegHuffmanTable *, JpegHuffmanTable *, s16 *, s16 *);
extern s32 func_8000C054(JpegHuffmanTable *, s16 *, s8 *);
extern u16 func_8000C190(u8);
s32 Jpeg_DecodeMcus(JpegMcuConfig* config, s16* output, u32 mcuCount, u8 resume, JpegMcuState* state) {
    u16 lumaBlocks;
    s16 lumaDcPred;
    s16 cbDcPred;
    s16 crDcPred;
    u32 i;
    s32 chromaRowStride;
    JpegHuffmanTable* acChroma;
    JpegHuffmanTable* dcLuma;
    JpegHuffmanTable* acLuma;
    JpegHuffmanTable* dcChroma;

    chromaRowStride = 0;
    D_800D1210 = config->inputBuffer;

    if (config->chromaSubsamplingMode == 0) {
        lumaBlocks = 2;
    } else {
        lumaBlocks = 4;
        if (config->subsamplingVariant == 1) {
            chromaRowStride = 0x80;
        }
    }

    dcLuma = config->dcLumaTable;
    acLuma = config->acLumaTable;
    dcChroma = config->dcChromaTable;
    acChroma = config->acChromaTable;

    if (resume == 0) {
        D_800D1214 = 0;
        D_800D1218 = 0x20;
        D_800D121C = 0;
        Jpeg_LastByteWasFF = 0;
        lumaDcPred = 0;
        cbDcPred = 0;
        crDcPred = 0;
    } else {
        D_800D1214 = state->readOffset;
        D_800D1218 = state->bitCount;
        D_800D121C = state->bitAccumulator;
        Jpeg_LastByteWasFF = state->lastByteWasFF;
        lumaDcPred = state->lumaDcPred;
        cbDcPred = state->chromaDcPred1;
        crDcPred = state->chromaDcPred2;
    }

    while (mcuCount) {
        for (i = 0; i < lumaBlocks; i++) {
            if (func_8000BEB8(dcLuma, acLuma, output, &lumaDcPred) != 0) {
                return 2;
            }
            output += 0x40;
        }

        if (func_8000BEB8(dcChroma, acChroma, output, &cbDcPred) != 0) {
            return 2;
        }

        output += 0x40;

        if (func_8000BEB8(dcChroma, acChroma, output, &crDcPred) != 0) {
            return 2;
        }

        mcuCount--;
        output += 0x40;

        output += chromaRowStride;
    }

    state->readOffset = D_800D1214;
    state->bitCount = D_800D1218;
    state->bitAccumulator = D_800D121C;
    state->lastByteWasFF = Jpeg_LastByteWasFF;
    state->lumaDcPred = lumaDcPred;
    state->chromaDcPred1 = cbDcPred;
    state->chromaDcPred2 = crDcPred;

    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/C890/func_8000BEB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/C890/func_8000C054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/C890/func_8000C190.s")
#endif
