#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB000D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB001C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB002BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB005E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB009C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00C1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00E40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00F78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00FE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB011DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01634.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01A74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01C14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01CF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01EC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01FCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02108.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB021F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02418.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02454.s")

struct MsgState { u8 pad[0x40]; u32 flags; };
extern struct MsgState *func_8FB02418(void);
s32 func_8FB02494(void) {
    return (func_8FB02418()->flags >> 31) == 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB024BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02560.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02608.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02698.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02878.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB029B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02A10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB03164.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB031E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB032C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB03328.s")

extern void func_80006D3C();
extern void func_80008574();
extern void func_80047610();
extern void func_8004C398();

void func_8FB033F0(s32 arg0, s32 arg1) {
    func_80008574();
    func_80047610();
    func_8004C398();
    func_80006D3C();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB0342C.s")
#endif
