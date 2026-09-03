#include "global.h"


#ifdef VERSION_US
extern u8 D_84185400[];
void func_84124360(s32 *arg0, u8 arg1, u8 arg2) {
    u8 *entry = D_84185400;
    if (*arg0 == 0) return;
    while (entry[0] != 0xFF) {
        if (arg1 == entry[0] && arg2 == entry[1]) {
            *arg0 *= entry[2];
            *arg0 /= 10;
            if (*arg0 == 0) *arg0 += 1;
            return;
        }
        entry += 3;
    }
}
#endif
