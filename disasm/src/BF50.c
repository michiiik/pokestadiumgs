#include "global.h"


#ifdef VERSION_US
extern s16 D_8008CE50[0x401];
u16 func_8000B350(f32 y, f32 x) {
    u16 ret;

    if (x == 0) {
        ret = D_8008CE50[0];
    } else {
        ret = D_8008CE50[(s32)(y / x * 1024 + 0.5f)];
    }
    return ret;
}

s16 func_8000B3B0(f32 y, f32 x) {
    u16 ret;

    if (x >= 0) {
        if (y >= 0) {
            if (y >= x) {
                ret = func_8000B350(x, y);
            } else {
                ret = 0x4000 - func_8000B350(y, x);
            }
        } else {
            y = -y;
            if (y < x) {
                ret = 0x4000 + func_8000B350(y, x);
            } else {
                ret = 0x8000 - func_8000B350(x, y);
            }
        }
    } else {
        x = -x;
        if (y < 0) {
            y = -y;
            if (y >= x) {
                ret = 0x8000 + func_8000B350(x, y);
            } else {
                ret = 0xC000 - func_8000B350(y, x);
            }
        } else {
            if (y < x) {
                ret = 0xC000 + func_8000B350(y, x);
            } else {
                ret = -func_8000B350(x, y);
            }
        }
    }
    return ret;
}

s32 func_8000B524(void) { return guRandom() & 0xFFFF; }

f32 func_8000B548(void) { return (f32)func_8000B524() / 65536.0f; }
#endif
