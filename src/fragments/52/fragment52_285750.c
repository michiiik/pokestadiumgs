#include "global.h"


#ifdef VERSION_US
typedef struct unk_func_86407290_1 {
    f32 unk_00;
    f32 unk_04;
    f32 unk_08;
} unk_func_86407290_1;

typedef struct unk_func_86407290 {
    u8 unk_00[20];
    unk_func_86407290_1 unk_14;
    unk_func_86407290_1 unk_20;
    unk_func_86407290_1 unk_2C;
    unk_func_86407290_1 unk_38;
    f32 unk_44;
    f32 unk_48;
    f32 unk_4C;
    f32 unk_50;
    f32 unk_54;
    f32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} unk_func_86407290;

extern void *D_86416C00;

void func_86407290(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    ((unk_func_86407290 *)D_86416C00)->unk_2C = ((unk_func_86407290 *)D_86416C00)->unk_14;
    ((unk_func_86407290 *)D_86416C00)->unk_38 = ((unk_func_86407290 *)D_86416C00)->unk_20;
    ((unk_func_86407290 *)D_86416C00)->unk_44 = arg0;
    ((unk_func_86407290 *)D_86416C00)->unk_48 = arg1;
    ((unk_func_86407290 *)D_86416C00)->unk_4C = arg2;
    ((unk_func_86407290 *)D_86416C00)->unk_50 = arg3;
    ((unk_func_86407290 *)D_86416C00)->unk_54 = arg4;
    ((unk_func_86407290 *)D_86416C00)->unk_58 = arg5;
    ((unk_func_86407290 *)D_86416C00)->unk_60 = arg6;
    ((unk_func_86407290 *)D_86416C00)->unk_5C = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_285750/func_86407330.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_285750/func_864073B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_285750/func_86407610.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_285750/func_864079AC.s")

extern void func_87F05204(s32 *);
extern void func_87F09040();
extern u8 D_800D0510;
extern void *D_86416C00;
void func_86407A54(void) {
    if (((u32) (*(u32 *)((u8 *)(D_86416C00) + (0xC))) >> 0x1F) != 0) {
        func_87F05204(&D_800D0510);
        func_87F09040();
    }
}
#endif
