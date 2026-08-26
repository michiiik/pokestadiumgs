#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0AA00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0AA8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0AAE4.s")

extern void func_8004C8C0(s32);
void func_87E0AB9C(void) { func_8004C8C0(425); }

extern u8 D_87E1A200[];
extern s32 main_pool_get_available(void);
extern s32 func_800030D0(s32, s32);
extern s32 func_80040E80(s32, void *);
extern void MainPool_FinalizeAllocation(s32);
void func_87E0ABBC(u8 *arg0) {
    s32 temp = func_800030D0(main_pool_get_available(), 0);
    *(s32 *)(arg0 + 0x18) = func_80040E80(temp, D_87E1A200);
    MainPool_FinalizeAllocation(temp);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0AC0C.s")

extern void func_87F02684(s32);
void func_87E0AC6C(s32 arg0) { func_87F02684((arg0 + 28)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0AC8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0ADA8.s")

s32 func_87E0AE28(void *arg0)
{
  void *new_var;
  void *node;
  void *container;
  void *state;
  s32 result;
  result = 1;
  node = *((void **) (((u8 *) arg0) + 0x28));
  if (node != 0)
  {
    do
    {
      ;
 if (1) { } if (1) { } if (1) { } if (1) { }
      ;
      new_var = *((void **) (((u8 *) (*((void **) (((u8 *) node) + 0x38)))) + 0xC));
      if ((*((s32 *) (((u8 *) new_var) + 0x84))) != 0)
      {
        result = 0;
      }
      node = *((void **) (((u8 *) node) + 4));
    }
    while (node != 0);
  }
  return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0AE64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0AF44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0B0EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0B2CC.s")

extern void func_87F0AF4C(s32);
void func_87E0B6D4(s32 arg0) { func_87F0AF4C((arg0 + 28)); }
#endif
