#include "global.h"


#ifdef VERSION_US
extern void func_800226C0(s32);
extern void Input_SetRepeatController(s32);
extern void func_88800B24();
extern s32 D_80087200;
extern void **D_882345F4;
void func_88231170(void) {
    func_800226C0(0x5E);
    Input_SetRepeatController(D_80087200);
    func_88800B24();
    (*(s32 *)((u8 *)(*D_882345F4) + (0xC))) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A43F0/func_882311B8.s")

typedef struct {
    s8 unk_00;
    s8 unk_01;
    u16 unk_02;
} unk_func_882313A4;
extern unk_func_882313A4 *D_882349D0;
extern void *D_8800EF54;
extern void D_88000E4C(void);
extern void func_882311B8(void);
extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
extern void *Util_Malloc(s32);

void func_882313A4(s8 arg0, s8 arg1, u16 arg2) {
    func_88005B60(2, D_88000E4C, func_882311B8, func_88231170);
    D_882349D0 = Util_Malloc(4);
    D_882349D0->unk_00 = arg0;
    D_882349D0->unk_01 = arg1;
    D_882349D0->unk_02 = arg2;
    D_8800EF54 = D_882349D0;
}
#pragma C_FUNCTION_PADDING(12)
#endif
