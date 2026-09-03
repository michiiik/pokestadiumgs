#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88700020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88700080.s")

extern s32 func_88700080(void *);
void func_88700288(void *arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    *(s16 *)((u8 *)arg0 + 0) = arg1;
    *(s16 *)((u8 *)arg0 + 4) = arg2;
    *(s16 *)((u8 *)arg0 + 6) = arg3;
    *(u8 *)((u8 *)arg0 + 8) = arg4;
    *(u8 *)((u8 *)arg0 + 9) = arg5;
    *(u8 *)((u8 *)arg0 + 10) = arg6;
    *(u8 *)((u8 *)arg0 + 11) = arg7;
    func_88700080(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_887002F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_8870032C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88700364.s")

extern void main_pool_pop_state(s32);
void Util_Free(s32 arg0);
extern u8 *D_88701E00;
s32 func_8000204C(void);
void func_887009A0(void) {
    Util_Free((s32) D_88701E00);
    if (func_8000204C() == 0) {
        do {

        } while (func_8000204C() == 0);
    }
    main_pool_pop_state(0x4E414D45);
}

void func_887009F0(void) {
    *(s16 *)(D_88701E00 + 0x58) = 0;
    *(s16 *)(D_88701E00 + 0x5A) = D_88701E00[0x5E];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88700A10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88700B58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88700C34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88700CE4.s")

s16 func_8870118C(s16 arg0) {
    return (s16) ((*(s16 *)((u8 *)(D_88701E00) + (0xC))) + (arg0 * 0x16) + ((arg0 / 13) * 0xC) + 0x17);
}

s16 func_887011E8(s16 arg0)
{
  return (s16) ((((*((s16 *) (((u8 *) D_88701E00) + 0xE))) + (*((s16 *) (((u8 *) D_88701E00) + 0x5C)))) + (arg0 * 0x16)) + ((arg0 / 5) * 4));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88701240.s")
#endif
