#include "global.h"


#ifdef VERSION_US
u16 func_84148520(u16 arg0, u16 arg1, u8 arg2) {
    s32 result;
    arg1 >>= arg2;
    result = (arg0 < arg1) ? arg0 : arg1;
    return result;
}

u16 func_84148560(u16 arg0, u16 arg1, u8 arg2) {
    s32 result;
    arg0 = arg1 - arg0;
    arg1 >>= arg2;
    result = (arg0 < arg1) ? arg0 : arg1;
    return result;
}

void func_841485A4(u8 *arg0, u16 arg1, u16 arg2) {
    s32 result = 255;

    if (arg2) {
        result = (arg1 * 255) / (u16)arg2;
    }
    if (result > 255) {
        result = 255;
    }
    *arg0 = result;
}
#endif
