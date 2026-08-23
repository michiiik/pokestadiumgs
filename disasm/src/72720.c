#include "global.h"

extern void *func_80004B4C(void *archive, s32 index);

#ifdef VERSION_US
void *func_80071B20(void *archive, s32 index) {
    if (index < 0 || index >= 5) {
        return NULL;
    }
    return func_80004B4C(archive, index);
}

void *func_80071B58(void *archive, s32 index, s32 entry) {
    void *result;

    if (archive == NULL) {
        return NULL;
    }
    result = func_80004B4C(archive, index);
    if (result == NULL) {
        return NULL;
    }
    return (u8 *)result + (entry * 0x98) + 4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72720/func_80071BB8.s")

f32 func_80071CA0(f32 value, f32 *integerPart) {
    s32 truncated = (s32)value;

    *integerPart = (f32)truncated;
    return value - *integerPart;
}
#endif
