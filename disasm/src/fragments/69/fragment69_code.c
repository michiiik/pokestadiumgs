#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F10008C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1000F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100160.s")
#endif

#ifdef VERSION_US
extern u8 D_8F1DF270[];
s32 func_8F10018C(s32 arg0)
{
  s16 *entry = (s16 *) (D_8F1DF270 + (arg0 * 6));
  s16 value;
  s32 result = 0;
  if (((*entry) == 0) || ((*entry) == 6))
  {
    *entry = 1;
    result = 1;
  }
  return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1001D0.s")
#endif

void func_8F100218(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100220.s")
#endif

#ifdef VERSION_US
extern u8 D_8F1DF274[];
void func_8F100274(s32 arg0) { struct Rec { s16 value[3]; }; ((struct Rec *)D_8F1DF274)[arg0].value[0] = 0; }
#endif

#ifdef VERSION_US
void func_8F100290(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (2))) = (s16) ((*(s16 *)((u8 *)(arg0) + (2))) + 1);
    if ((*(s16 *)((u8 *)(arg0) + (2))) >= 8) {
        (*(s16 *)((u8 *)(arg0) + (0))) = 2;
        (*(s16 *)((u8 *)(arg0) + (2))) = 8;
    }
}
#endif

#ifdef VERSION_US
void func_8F1002C4(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (2))) = (s16) ((*(s16 *)((u8 *)(arg0) + (2))) - 1);
    if ((*(s16 *)((u8 *)(arg0) + (2))) <= 0) {
        (*(s16 *)((u8 *)(arg0) + (0))) = 6;
        (*(s16 *)((u8 *)(arg0) + (2))) = 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1002F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1003EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F10049C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100594.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100740.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1008EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100B54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100C64.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100D58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100DCC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100E78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F10128C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F101318.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F101CDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F101DA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F101FF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1020A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102394.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102488.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102618.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102708.s")
#endif

#ifdef VERSION_US
extern void func_80004024(s32 *, s32, s32);
s32 func_800356CC(s32);
extern u8 D_8F1DEE68;

void func_8F1027F8(void) {
    s32 temp_v0;

    temp_v0 = func_800356CC(9);
    func_80004024(&D_8F1DEE68, temp_v0, temp_v0 + 0x408);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F10282C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1029CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102A20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102A98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102B48.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102BC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102D98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102F58.s")
#endif

#ifdef VERSION_US
extern void func_8F100220(s32 arg0);
void func_8F102F94(void) {
    func_8F100220(2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102FB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F103194.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F103478.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1036F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1037C4.s")
#endif
