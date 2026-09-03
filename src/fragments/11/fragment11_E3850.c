#include "global.h"


#ifdef VERSION_US
f32 func_8160BCB0(f32 arg0, f32 arg1) {
    if (arg1 == 0.0f) {
        return 0.0f;
    }
    return arg0 - ((f32) (s32) (arg0 / arg1) * arg1);
}
#endif
