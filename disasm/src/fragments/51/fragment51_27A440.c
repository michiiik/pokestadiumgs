#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27A440/func_86304620.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27A440/func_8630470C.s")

extern u8 *D_863075D8;
extern void func_87F02684(void *);
extern void func_87F0277C(void *);
void func_8630487C(void) { func_87F02684(D_863075D8 + 0x88DC); }

void func_863048A8(void) { func_87F0277C(D_863075D8 + 0x88DC); }

extern u8 D_87F15B70[];
extern void func_87F0252C(void *, void *, void *, s32);
void func_863048D4(void) {
    func_87F0252C(D_87F15B70, D_863075D8 + 0x88DC, D_863075D8 + 0x88F0, 4);
}
#endif
