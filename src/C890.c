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
extern s32 Jpeg_DecodeBlock(JpegHuffmanTable *, JpegHuffmanTable *, s16 *, s16 *);
extern s32 Jpeg_DecodeHuffmanSymbol(JpegHuffmanTable *, s16 *, s8 *);
extern u16 Jpeg_ReadBits(u8);
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
            if (Jpeg_DecodeBlock(dcLuma, acLuma, output, &lumaDcPred) != 0) {
                return 2;
            }
            output += 0x40;
        }

        if (Jpeg_DecodeBlock(dcChroma, acChroma, output, &cbDcPred) != 0) {
            return 2;
        }

        output += 0x40;

        if (Jpeg_DecodeBlock(dcChroma, acChroma, output, &crDcPred) != 0) {
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

s32 Jpeg_DecodeBlock(JpegHuffmanTable* dcTable, JpegHuffmanTable* acTable, s16* coefficients, s16* dcPredictor) {
    s8 i = 0;
    s8 zeroCount;
    s16 coefficient;

    if (Jpeg_DecodeHuffmanSymbol(dcTable, &coefficient, &zeroCount)) {
        return 1;
    }

    *dcPredictor += coefficient;
    coefficients[i++] = *dcPredictor;
    while (i < 8 * 8) {
        if (Jpeg_DecodeHuffmanSymbol(acTable, &coefficient, &zeroCount) != 0) {
            return 1;
        }

        if (coefficient == 0) {
            if (zeroCount == 0xF) {
                while (zeroCount-- >= 0) {
                    coefficients[i++] = 0;
                }
            } else {
                while (i < 8 * 8) {
                    coefficients[i++] = 0;
                }
                break;
            }
        } else {
            while (0 < zeroCount--) {
                coefficients[i++] = 0;
            }
            coefficients[i++] = coefficient;
        }
    }

    return 0;
}

s32 Jpeg_DecodeHuffmanSymbol(JpegHuffmanTable* hTable, s16* outCoeff, s8* outZeroCount) {
    u8 codeIdx;
    u8 sym;
    u16 codeOff = 0;
    u16 buff = Jpeg_ReadBits(16);

    for (codeIdx = 0; codeIdx < 16; codeIdx++) {
        if (hTable->codesB[codeIdx] == 0xFFFF) {
            continue;
        }

        codeOff = buff >> (15 - codeIdx);
        if (codeOff <= hTable->codesB[codeIdx]) {
            break;
        }
    }

    if (codeIdx >= 16) {
        return 1;
    }

    sym = hTable->symbols[hTable->codeOffs[codeIdx] + codeOff - hTable->codesA[codeIdx]];
    *outZeroCount = sym >> 4;
    sym &= 0xF;

    D_800D1218 += codeIdx - 15;
    *outCoeff = 0;
    if (sym) {
        *outCoeff = Jpeg_ReadBits(sym);
        if (*outCoeff < (1 << (sym - 1))) {
            *outCoeff += (-1U << sym) + 1;
        }
    }

    return 0;
}

u16 Jpeg_ReadBits(u8 len) {
    u8 byteCount;
    u8 data;
    s32 ret;

    ret = D_800D1218;
    byteCount = ret >> 3;
    ret = 0;
    for (; byteCount > 0; byteCount--) {
        data = D_800D1210[D_800D1214++];
        if (Jpeg_LastByteWasFF) {
            if (data == 0) {
                data = D_800D1210[D_800D1214++];
            }
        }

        Jpeg_LastByteWasFF = (data == 0xFF) ? 1 : 0;

        D_800D121C <<= 8;
        D_800D121C |= data;
        D_800D1218 -= 8;
    }

    ret |= D_800D121C << D_800D1218;
    ret = (u32)ret >> -len;
    D_800D1218 += len;
    return ret;
}
#endif
