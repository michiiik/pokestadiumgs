#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0B700.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0B73C.s")

extern void func_8004C8C0(s32);

void func_87E0B7F4(void) {
    func_8004C8C0(0x15E);
    func_8004C8C0(0x15F);
    func_8004C8C0(0x160);
    func_8004C8C0(0x162);
    func_8004C8C0(0x163);
}

extern u8 D_87E1A2C0[];
extern s32 func_80002B24(void);
extern s32 func_800030D0(s32, s32);
extern s32 func_80040E80(s32, void *);
extern void func_80003120(s32);
void func_87E0B834(void *arg0) {
    s32 temp = func_800030D0(func_80002B24(), 0);
    *(s32 *)((u8 *)arg0 + 8) = func_80040E80(temp, D_87E1A2C0);
    func_80003120(temp);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0B884.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0B9F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0BB5C.s")

extern void func_87F02684(s32);
void func_87E0BE28(s32 arg0) { func_87F02684(arg0 + 12); }

void func_87E0BE48(void *arg0) {
    void *var_v0;

    var_v0 = (*(void **)((u8 *)(arg0) + (0x18)));
    if (var_v0 != NULL) {
        do {
            (*(u8 *)((u8 *)(var_v0) + (0x25))) = (u8) ((*(u8 *)((u8 *)(var_v0) + (0x25))) & ~1);
            var_v0 = (*(void **)((u8 *)(var_v0) + (4)));
        } while (var_v0 != NULL);
    }
}

s32 func_87E0BE78(void *arg0)
{
  s32 var_v1;
  void *new_var;
  void *var_v0;
  var_v0 = *((void **) (((u8 *) arg0) + 0x18));
  var_v1 = 1;
  if (var_v0 != 0)
  {
    do
    {
      new_var = *((void **) (((u8 *) (*((void **) (((u8 *) var_v0) + 0x38)))) + 0xC));
      if ((*((s32 *) (((u8 *) new_var) + 0x98))) != 0)
      {
        var_v1 = 0;
      }
      var_v0 = *((void **) (((u8 *) var_v0) + 4));
    }
    while (var_v0 != 0);
  }
  return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0BEB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0BFFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0C290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0C390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0C3F8.s")

extern void func_87E0BFFC(s32, s32, s32);
void func_87E0C454(void *arg0, s32 arg1) {
    void *var_v0;

    var_v0 = (*(void **)((u8 *)(arg0) + (0x18)));
    if (var_v0 != NULL) {
        do {
            (*(f32 *)((u8 *)(var_v0) + (0x48))) = 0.0f;
            (*(f32 *)((u8 *)(var_v0) + (0x4C))) = 240.0f;
            (*(f32 *)((u8 *)(var_v0) + (0x50))) = 200.0f;
            (*(s16 *)((u8 *)(var_v0) + (0x46))) = -1;
            var_v0 = (*(void **)((u8 *)(var_v0) + (4)));
        } while (var_v0 != NULL);
    }
    func_87E0BFFC((s32) arg0, arg1, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0C4B4.s")

extern void func_87E0BB5C(); extern void func_87E0BFFC(s32, s32, s32);
void func_87E0C590(s32 arg0, s32 arg1) { func_87E0BB5C(); func_87E0BFFC(arg0, arg1, 1); }

extern void func_87E0BFFC(s32, s32, s32);
void func_87E0C5C4(s32 arg0, s32 arg1) { func_87E0BFFC(arg0, arg1, 0); }

void func_87E0C5E4(s32 arg0) { func_87E0BFFC(arg0, -1, 0); }

extern void func_87E0C290(void);
void func_87E0C608(void) {
    func_87E0C290();
}

extern void func_87E0B7F4();
extern void func_87E0B834(void *);
extern void func_87E0B884(void *);

void func_87E0C628(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)(arg0) + (4))) = arg1;
    (*(s32 *)((u8 *)(arg0) + (0))) = 1;
    func_87E0B7F4();
    func_87E0B834(arg0);
    func_87E0B884(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0C664.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0C6CC.s")

extern void func_87F0AF4C(s32);
void func_87E0C8DC(s32 arg0) { func_87F0AF4C(arg0 + 12); }
#endif
