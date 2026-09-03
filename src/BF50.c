#include "global.h"


#ifdef VERSION_US
extern s16 D_8008CE50[0x401];
u16 MathUtil_Atan2Lookup(f32 y, f32 x) {
    u16 ret;

    if (x == 0) {
        ret = D_8008CE50[0];
    } else {
        ret = D_8008CE50[(s32)(y / x * 1024 + 0.5f)];
    }
    return ret;
}

s16 MathUtil_Atan2s(f32 y, f32 x) {
    u16 ret;

    if (x >= 0) {
        if (y >= 0) {
            if (y >= x) {
                ret = MathUtil_Atan2Lookup(x, y);
            } else {
                ret = 0x4000 - MathUtil_Atan2Lookup(y, x);
            }
        } else {
            y = -y;
            if (y < x) {
                ret = 0x4000 + MathUtil_Atan2Lookup(y, x);
            } else {
                ret = 0x8000 - MathUtil_Atan2Lookup(x, y);
            }
        }
    } else {
        x = -x;
        if (y < 0) {
            y = -y;
            if (y >= x) {
                ret = 0x8000 + MathUtil_Atan2Lookup(x, y);
            } else {
                ret = 0xC000 - MathUtil_Atan2Lookup(y, x);
            }
        } else {
            if (y < x) {
                ret = 0xC000 + MathUtil_Atan2Lookup(y, x);
            } else {
                ret = -MathUtil_Atan2Lookup(x, y);
            }
        }
    }
    return ret;
}

s32 MathUtil_Random16(void) { return guRandom() & 0xFFFF; }

f32 MathUtil_Random_ZeroOne(void) { return (f32)MathUtil_Random16() / 65536.0f; }
#endif
