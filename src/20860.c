#include "global.h"


#ifdef VERSION_US
#pragma REWRITE_FUNCTION_HEX(func_8001FC60, aab43ff0da9d697b320dce6ed1082521758b661a304535e98733e51ff60e9e35, 20af00208ca800008ca900048caa00088cab000c20a50010ac880000ac890004ac8a0008ac8b000c14affff62084001003e00008000000000000000000000000)
void func_8001FC60(u32 *dst, const u32 *src) {
    s32 i;
    for (i = 0; i < 8; i += 4) {
        dst[i + 0] = src[i + 0];
        dst[i + 1] = src[i + 1];
        dst[i + 2] = src[i + 2];
        dst[i + 3] = src[i + 3];
    }
}
#endif
