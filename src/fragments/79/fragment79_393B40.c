#include "global.h"


#ifdef VERSION_US
void func_841242B0(u8 *arg0, s32 arg1, s32 arg2) {}
#endif

void func_841242C0(void) {
}

#ifdef VERSION_US
void func_841242C8(u8 *arg0) {}
#endif

#ifdef VERSION_US
void func_841242D0(u8 *arg0) {}
#endif

#ifdef VERSION_US
extern u8 *D_84191208;
extern u8 *D_8419120C;
extern u8 *D_84193FA0;
void func_841242D8(void) {
    s16 mode;
    *(u16 *)(D_84191208 + 0x7EC) |= 1;
    *(u16 *)(D_8419120C + 0x7EC) |= 1;
    mode = *(s16 *)(D_84193FA0 + 0x80);
    if (mode == 0)
        goto call_d0;
    if (mode != 1)
        goto finish;
    goto call_c8;
call_d0:
    func_841242D0(D_84191208);
    goto finish;
call_c8:
    func_841242C8(D_84191208);
finish:
    ;
}
#endif
