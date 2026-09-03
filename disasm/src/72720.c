#include "global.h"


#ifdef VERSION_US
s32 func_80004B4C(s32, s32);
s32 func_80071B20(s32 arg0, s32 arg1) {
    if ((arg1 < 0) || (arg1 >= 5)) {
        return 0;
    }
    return func_80004B4C(arg0, arg1);
}

s32 func_80071B58(s32 arg0, s32 arg1, s32 arg2) {
    s32 offset;
    s32 base;
    if (arg0 == 0) {
        return 0;
    }
    base = func_80004B4C(arg0, arg1);
    if (base == 0) {
        return 0;
    }
    offset = arg2 * 0x98;
    return base + offset + 4;
}

typedef struct {
    u8 bytes[0x58];
} CopyFillDstRecord;

typedef struct {
    u8 bytes[0x18];
} CopyFillSrcRecord;

typedef struct {
    u8 unk00[4];
    u8 count;
    u8 unk05[3];
    CopyFillSrcRecord records[1];
} CopyFillInput;

void func_80071E48(void *, void *);
void func_80071BB8(CopyFillDstRecord *arg0, CopyFillInput *arg1) {
    s32 i;
    if (arg1 != NULL) {
        for (i = 0; (i < (s32)arg1->count) && (i != 6); i++) {
            func_80071E48(&arg0[i], &arg1->records[i]);
        }
        for (; i < 6; i++) {
            arg0[i].bytes[0] = 0;
        }
    }
}

f32 func_80071CA0(f32 arg0, f32 *arg1) { s32 value = (s32)arg0; *arg1 = (f32)value; return arg0 - *arg1; }
#endif
