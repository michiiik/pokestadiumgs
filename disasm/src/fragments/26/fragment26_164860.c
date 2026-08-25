#include "global.h"


#ifdef VERSION_US
void func_81005FB0(u8 *arg0, s32 arg1) {}

void func_81005FBC(u8 *arg0, s32 arg1) {}

extern u32 D_81100254;
void func_81005FC8(u8 *arg0, s32 arg1) {
    D_81100254 = 0x7B;
}

void func_81005FE0(u8 *arg0, s32 arg1) {
    D_81100254 = 0x1C8;
}

void func_81005FF8(u8 *arg0, s32 arg1) {
    D_81100254 = 0;
}

void func_8100600C(u8 *arg0, s32 arg1) { arg0 = arg0; arg1 = arg1; }
#endif
