#include "global.h"


#ifdef VERSION_US
extern void func_8004C8C0(s32);
s32 func_8004C4B0(s32 value);
void fragment3_main(void *arg0) {
    (*(s32 *)((u8 *)(arg0) + (0))) = 0;
    (*(s32 *)((u8 *)(arg0) + (4))) = 0;
    (*(s32 *)((u8 *)(arg0) + (8))) = -1;
    (*(s32 *)((u8 *)(arg0) + (0xC))) = 4;
    (*(s32 *)((u8 *)(arg0) + (0x10))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x14))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x18))) = 0;
    func_8004C8C0(0x1C0);
    func_8004C8C0(0x15D);
    func_8004C4B0(0x27);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/3/fragment3_code/func_81A00074.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/3/fragment3_code/func_81A0022C.s")

void func_81A005F0(u8 *arg0) {
    *(s32 *)(arg0 + 0x18) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/3/fragment3_code/func_81A005FC.s")
#endif
