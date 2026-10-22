#include "global.h"


#ifdef VERSION_US
u8 *func_82101B80(u8 *arg0)
{
  return (arg0 + ((*((u32 *) (arg0 + 0x24))) * 8)) + ((0, 4));
}

/* mkdraft:func_82101B94 begin */
extern void *MainPool_AllocAligned(void *, size_t, s32);
extern void func_82102D34(f32 *);
extern f32 __sinf(f32);
extern f32 __cosf(f32);
extern f32 D_82104118;

f32 *func_82101B94(void *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 *var_s1;
    f32 temp_fs0;
    s32 var_s0;

    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, 0x2C, 4);
    }
    *(f32 *)((u8 *)arg1 + 0) = arg3 + D_82104118;
    func_82102D34(arg1);
    *(f32 *)((u8 *)arg1 + 0x28) = arg2;
    for (var_s0 = 0, var_s1 = arg1; var_s0 != 4; var_s0++, var_s1 += 2) {
        temp_fs0 = arg3 - ((f32) (3 - var_s0) * arg4);
        *(f32 *)((u8 *)var_s1 + 4) = (f32) ((__sinf(temp_fs0) * arg7) + arg5);
        *(f32 *)((u8 *)var_s1 + 8) = (__cosf(temp_fs0) * arg7) + arg6;
    }
    *(u32 *)((u8 *)arg1 + 0x24) = 3;
    return arg1;
}
/* mkdraft:func_82101B94 end */

extern f32 __sinf(f32);
extern f32 __cosf(f32);

void func_82101CB4(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 *var_s1;
    f32 temp_fs0;
    s32 var_s0;

    for (var_s0 = 0, var_s1 = arg0; var_s0 != 4; var_s0++, var_s1 += 2) {
        temp_fs0 = arg5 - ((f32) (3 - var_s0) * arg4);
        *(f32 *)((u8 *)var_s1 + 4) = (f32) ((__sinf(temp_fs0) * arg3) + arg1);
        *(f32 *)((u8 *)var_s1 + 8) = (__cosf(temp_fs0) * arg3) + arg2;
    }
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_82101D88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_82101E70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_82101FB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_821020B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_82102190.s")

extern void func_82102444(s32, s32);
void func_821023F4(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s1 = arg0;
    do {
        func_82102444(var_s1, var_s0);
        var_s0 += 1;
        var_s1 += 0x2C;
    } while (var_s0 != 3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_82102444.s")
#endif
