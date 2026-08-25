#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_831000FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_831001A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100584.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_831005F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_8310065C.s")

extern void func_81600F0C(void *, s32, s32, s32, s32);
extern void func_818057D0(void *, void *, void *);
void func_83100A98(void *arg0, u8 *arg1, void *arg2) {
    func_81600F0C(*(void **)(arg1 + 0x5C), 0, 0, 0x280, 0x1E0);
    func_818057D0(arg0, arg1, arg2);
}

extern void func_81700D44(s32);
extern void func_8170024C(void);
s32 func_83100AE8(void *arg0, u8 *arg1) {
    if (arg1[0x1D] == 0) {
        func_81700D44(0);
        func_81700D44(1);
    }
    func_8170024C();
    return 1;
}

extern s32 func_81600DA8(void *, void *);
extern void func_81700908(void);
extern u8 D_83102290[];
void func_83100B2C(void *arg0, u8 *arg1, void *arg2) {
    if (func_81600DA8(*(void **)(arg1 + 4), D_83102290) == 0) {
        func_81600F0C(*(void **)(arg1 + 0x5C), 0, 0, 0x280, 0x46);
    }
    func_81700908();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100B8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100BF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100CA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100D10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100DBC.s")

void func_83100E98(u8 *arg0, s32 arg1)
{
  s32 result = arg1 - 4;
  s32 limit = arg0[0xCB] - 9;
  if (limit < result)
  {
    result = limit;
  }
  if (limit = result < 0)
  {
    result = 0;
  }
  arg0[0x43] = result;
  arg0[0x40] = ((arg1 - result) & 0xFFu) + 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100ED4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100FA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_8310103C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101090.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101104.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_831011A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101244.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101400.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101714.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101764.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101804.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101B04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101B60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101BD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101C24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101C80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101D74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101EB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101F5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101FFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83102080.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_831020D0.s")

extern void func_80006D3C();
extern void func_80008574();
extern void func_80047610();
extern void func_8004C398();

void func_831021E8(s32 arg0, s32 arg1) {
    func_80008574();
    func_8004C398();
    func_80047610();
    func_80006D3C();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83102224.s")
#endif
