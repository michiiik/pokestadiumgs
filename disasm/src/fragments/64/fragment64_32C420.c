#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32C420/func_87F097B0.s")

extern void _bzero(void *, s32);
void func_87F09870(s32 *arg0) { _bzero(arg0, 0x1C); *arg0 = 0; }

extern void func_800279C4(s32);
void func_87F0989C(void *arg0) {
    (*(s32 *)((u8 *)(arg0) + (0))) = 1;
    (*(s32 *)((u8 *)(arg0) + (0x18))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x14))) = -0x100;
    (*(f32 *)((u8 *)(arg0) + (4))) = 160.0f;
    (*(f32 *)((u8 *)(arg0) + (0xC))) = 0.0f;
    (*(f32 *)((u8 *)(arg0) + (0x10))) = 0.0f;
    (*(f32 *)((u8 *)(arg0) + (8))) = 240.0f;
    func_800279C4(0xCF11);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32C420/func_87F098F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32C420/func_87F09B7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32C420/func_87F09EBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32C420/func_87F0A098.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32C420/func_87F0A3E8.s")

extern void func_800503A4(s32);
extern void func_87F09B7C(void *);
void func_87F0A5BC(void *arg0) {
    func_800503A4(*(s32 *)((u8 *)arg0 + 0x24));
    func_87F09B7C((u8 *)arg0 + 0x3C);
}
#endif
