#include "global.h"


#ifdef VERSION_US
/* mkdraft:func_8000B780 begin */
typedef struct { u16 table[8 * 8]; } JpegQuantizationTable;

void func_8000B780(u8* dqt, JpegQuantizationTable* qt, u8 num_tables) {
    u8 i;

    for (i = 0; i < num_tables; i++) {
        u8 j;

        dqt++;
        for (j = 0; j < 64; j++) {
            qt[i].table[j] = *dqt++;
        }
    }
}
/* mkdraft:func_8000B780 end */

/* mkdraft:func_8000B7E8 begin */
s32 func_8000B7E8(u8* ptr, u8* codesLengths) {
    u8 off = 1;
    s16 count = 0;
    s16 idx = 1;

    while (off < 0x11) {
        while (idx <= ptr[off - 1]) {
            codesLengths[count++] = off;
            idx++;
        }
        idx = 1;
        off++;
    }

    codesLengths[count] = 0;
    return count;
}
/* mkdraft:func_8000B7E8 end */

/* mkdraft:func_8000B86C begin */
s16 func_8000B86C(u8* codesLengths, u16* codes) {
    s16 idx = 0;
    u16 code = 0;
    u8 lastLen = codesLengths[0];

    while (true) {
        while (true) {
            codes[idx++] = code++;

            if (codesLengths[idx] != lastLen) {
                break;
            }
        }

        if (codesLengths[idx] == 0) {
            break;
        }

        while (true) {
            if (code <<= 1, codesLengths[idx] == ++lastLen) {
                break;
            }
        }
    }

    return idx;
}
/* mkdraft:func_8000B86C end */

/* mkdraft:func_8000B8D8 begin */
typedef struct { u8 codeOffs[16]; u16 codesA[16]; u16 codesB[16]; u8* symbols; } JpegHuffmanTable;

u16 func_8000B8D8(u8* data, JpegHuffmanTable* ht, u16* codes) {
    u8 idx;
    u16 codeOff = 0;

    for (idx = 0; idx < 0x10; idx++) {
        if (data[idx]) {
            ht->codeOffs[idx] = codeOff;
            ht->codesA[idx] = codes[codeOff];
            codeOff += data[idx] - 1;
            ht->codesB[idx] = codes[codeOff];
            codeOff++;
        } else {
            ht->codesB[idx] = 0xFFFF;
        }
    }

    return codeOff;
}
/* mkdraft:func_8000B8D8 end */

/* mkdraft:func_8000B980 begin */
extern s32 func_8000B7E8(u8* ptr, u8* codesLengths);
extern s16 func_8000B86C(u8* codesLengths, u16* codes);
extern u16 func_8000B8D8(u8* data, JpegHuffmanTable* ht, u16* codes);

u32 func_8000B980(u8* data, JpegHuffmanTable* ht, u8* codesLengths, u16* codes, u8 isAc) {
    s16 ret;
    s32 count = func_8000B7E8(data, codesLengths);
    s32 temp;

    ret = count;
    if (count == 0 || (isAc && count > 0x100) || (!isAc && count > 0x10)) {
        return 0;
    }
    if (ret != func_8000B86C(codesLengths, codes)) {
        return 0;
    }
    if (temp = func_8000B8D8(data, ht, codes), temp != ret) {
        return 0;
    }

    return ret;
}
/* mkdraft:func_8000B980 end */

/* mkdraft:func_8000BA3C begin */
extern u32 func_8000B980(u8* data, JpegHuffmanTable* ht, u8* codesLengths, u16* codes, u8 isAc);

s32 func_8000BA3C(u8* dht, JpegHuffmanTable* ht, u8* codesLengths, u16* codes, u8 count) {
    u8 idx;
    u32 codeCount;

    for (idx = 0; idx < count; idx++) {
        u32 ac = (*dht++ >> 4);

        codeCount = func_8000B980(dht, &ht[idx], codesLengths, codes, ac);
        if (codeCount == 0) {
            return 1;
        }

        dht += 0x10;
        ht[idx].symbols = dht;
        dht += codeCount;
    }
    return 0;
}
/* mkdraft:func_8000BA3C end */

/* mkdraft:func_8000BB14 begin */
typedef struct JpegHuffmanTableOld { u8 codeOffs[16]; u16 dcCodes[120]; u16 acCodes[256]; } JpegHuffmanTableOld;

void func_8000BB14(u8* data, JpegHuffmanTableOld* ht, u8* codesLengths, u16* codes, s16 count, u8 isAc) {
    s16 idx;
    u8 a;

    for (idx = 0; idx < count; idx++) {
        a = data[idx];
        if (isAc) {
            ht->acCodes[a] = codes[idx];
            ht->codeOffs[a] = codesLengths[idx];
        } else {
            ht->dcCodes[a] = codes[idx];
            ht->codeOffs[a] = codesLengths[idx];
        }
    }
}
/* mkdraft:func_8000BB14 end */

/* mkdraft:func_8000BBBC begin */
extern s32 func_8000B7E8(u8* ptr, u8* codesLengths);
extern s16 func_8000B86C(u8* codesLengths, u16* codes);
extern void func_8000BB14(u8* data, JpegHuffmanTableOld* ht, u8* codesLengths, u16* codes, s16 count, u8 isAc);

u32 func_8000BBBC(u8* dht, JpegHuffmanTableOld* ht, u8* codesLengths, u16* codes) {
    u8 isAc = *dht++ >> 4;
    s16 count2;
    s32 count;

    count2 = count = func_8000B7E8(dht, codesLengths);

    if (count == 0 || (isAc && count > 0x100) || (!isAc && count > 0x10)) {
        return 1;
    }

    if (func_8000B86C(codesLengths, codes) != count2) {
        return 1;
    }

    func_8000BB14(dht + 0x10, ht, codesLengths, codes, count2, isAc);

    return 0;
}
/* mkdraft:func_8000BBBC end */
#endif
