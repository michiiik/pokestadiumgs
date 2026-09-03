#include "global.h"


#ifdef VERSION_US
extern u8 D_87E1A240[];
extern void func_87E10EA8(s32);
extern void func_87E10E64(s32);
extern void func_87E10F2C(s32);
void func_87E0AA00(void *arg0) {
    s32 *entry;
    s32 state;

    state = *(s32 *)((u8 *)arg0 + 0);
    entry = (s32 *)((u8 *)D_87E1A240 +
        (*(s32 *)*(void **)((u8 *)arg0 + 8) * 0xC));
    if ((state == 2) || (state == 3)) {
        func_87E10EA8(-1);
        func_87E10F2C(-1);
        return;
    }
    func_87E10E64(entry[0]);
    func_87E10EA8(entry[1]);
    func_87E10F2C(entry[2]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0AA8C.s")

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern void func_8003CD84(void);
void func_87E0AAE4(s32 arg0, s32 arg1) {
    void *context;

    if (arg0 == 5) {
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238);
        context = *(void **)((u8 *)D_8009491C + 0x14);
        gSPSegment(D_800D0510++, 0xF,
                   *(void **)((u8 *)*(void **)((u8 *)context + 4) + 8));
        gSPDisplayList(D_800D0510++, *(void **)context);
        func_8003CD84();
    }
}

extern void func_8004C8C0(s32);
void func_87E0AB9C(void) {
    func_8004C8C0(425);
}

extern u8 D_87E1A200[];
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern s32 func_80040E80(s32, void *);
extern void MainPool_FinalizeAllocation(s32);
void func_87E0ABBC(u8 *arg0) {
    s32 temp = MainPool_AllocState(main_pool_get_available(), 0);
    *(s32 *)(arg0 + 0x18) = func_80040E80(temp, D_87E1A200);
    MainPool_FinalizeAllocation(temp);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0AC0C.s")

extern void func_87F02684(s32);
void func_87E0AC6C(s32 arg0) {
    func_87F02684((arg0 + 28));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30E370/func_87E0AC8C.s")

extern void func_87E0AC0C(u8 *);
extern void func_87E11C38(s32);
void func_87F061D0(void);
extern void func_87E0AB9C(void);
extern void func_87E0ABBC(u8 *arg0);
void func_87E0ADA8(u8 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4) {
    (*(s32 *)((u8 *)(arg0) + (0))) = 0;
    (*(s32 *)((u8 *)(arg0) + (4))) = arg1;
    (*(s32 **)((u8 *)(arg0) + (8))) = arg2;
    (*(s32 *)((u8 *)(arg0) + (0x10))) = arg3;
    (*(s32 *)((u8 *)(arg0) + (0xC))) = arg4;
    (*(s32 *)((u8 *)(arg0) + (0x38))) = 0;
    (*(f32 *)((u8 *)(arg0) + (0x14))) = (f32) (*arg2 << 5);
    func_87E0AB9C();
    func_87E0ABBC(arg0);
    func_87E0AC0C(arg0);
    func_87F061D0();
    func_87E11C38(*(*(s32 **)((u8 *)(arg0) + (8))));
}

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
void func_87E0B6D4(s32 arg0) {
    func_87F0AF4C((arg0 + 28));
}
#endif
