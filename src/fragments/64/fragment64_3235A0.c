#include "global.h"


#ifdef VERSION_US
extern u8 *D_87F0F610;
u32 func_87F00930(void) {
    return ((u32)D_87F0F610[0x3D]) >> 7;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3235A0/func_87F00944.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3235A0/func_87F01110.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3235A0/func_87F012BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3235A0/func_87F014C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3235A0/func_87F01870.s")

extern u8 D_800CE060[];
extern void func_80006148(u8 *);
void func_87F01934(void) {
    u8 *entry = D_800CE060;
    s32 offset;

    for (offset = 0; offset < 8; offset += 2) {
        *(u16 *)(D_87F0F610 + offset + 0x34) = *(u16 *)(entry + 0x10);
        func_80006148(entry);
        entry += 0x28;
    }
}

/* mkdraft:func_87F019A4 begin */
void func_87F019A4(void) {
    u8 *entry = D_800CE060;
    s32 offset;

    for (offset = 0; offset < 8; offset += 2) {
        *(u16 *)(entry + 0x10) = *(u16 *)(D_87F0F610 + offset + 0x34);
        entry += 0x28;
    }
}
/* mkdraft:func_87F019A4 end */

extern void Audio_PlayDefaultSound(s32);
extern void func_8002809C();
void func_87F019F0(void) {
    func_8002809C();
    if ((*(s32 *)((u8 *)(D_87F0F610) + (0x30))) == 2) {
        Audio_PlayDefaultSound(0xCF08);
        return;
    }
    Audio_PlayDefaultSound(0xCF02);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3235A0/func_87F01A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3235A0/func_87F01D44.s")
#endif
