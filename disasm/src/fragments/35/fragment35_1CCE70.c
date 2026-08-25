#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_88600270.s")

extern u8 D_88601510[];
s32 func_8860043C(s32 arg0) { u8 *table = D_88601510; s32 i = 0; do { if (table[i] == arg0) return i; i++; i &= 0xFF; } while (i < 0x12); }

void func_8860047C(void) { extern u8 D_88601914[]; extern f32 D_886018D0[]; extern f32 D_886018E0[]; extern u8 D_88601918[]; D_886018D0[0] = D_88601914[0]; D_886018D0[1] = D_88601914[1]; D_886018D0[2] = D_88601914[2]; D_886018E0[0] = D_88601918[0]; D_886018E0[1] = D_88601918[1]; D_886018E0[2] = D_88601918[2]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_88600578.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_886006B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_88600860.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_88600C38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_88600CC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_88600D64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_886013BC.s")

extern void func_886013BC(s32, s32);
void func_886014D8(s32 arg0) { func_886013BC(arg0, 0); }
#endif
