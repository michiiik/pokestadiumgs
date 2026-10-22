#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_279D70/func_86303F50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_279D70/func_863040C4.s")

s32 func_87F026E8(s32, void *);
extern s32 D_87F119D8;
extern void *D_87F119DC;

void func_8630421C(void)
{
  s32 temp_v0;
  float new_var;
  ;
  if ((*((s32 *) (0x1C + ((u8 *) D_87F119DC)))) >= 8)
  {
    func_87F026E8(D_87F119D8, D_87F119DC);
    return;
  }
 dummy_label_621702: ;
  new_var = 1.0f - (((f32) (*((s32 *) (0x1C + ((u8 *) D_87F119DC))))) / 7.0f);
  temp_v0 = (s8) ((u32) (200.0f * new_var));
  *((s8 *) (((u8 *) D_87F119DC) + 0x41)) = temp_v0;
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_279D70/func_86304318.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_279D70/func_863043E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_279D70/func_86304544.s")
#endif
