#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0C900.s")

extern void *D_87F119DC;
extern void func_87F0B4AC(void *, f32 *, f32 *, s16 *);
void func_87E0C93C(void) {
    void *state = D_87F119DC;
    func_87F0B4AC(
        *(void **)((u8 *)*(void **)((u8 *)state + 0x38) + 0x0C),
        (f32 *)((u8 *)state + 0x48),
        (f32 *)((u8 *)state + 0x54),
        (s16 *)((u8 *)state + 0x42));
}

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern void func_8003CD84();
void func_87E0C974(s32 arg0, s32 arg1) {
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0CA2C.s")

extern void func_8004C8C0(s32);

void func_87E0CB88(void) {
    func_8004C8C0(0x1B2);
    func_8004C8C0(0x160);
    func_8004C8C0(0x1B4);
    func_8004C8C0(0x161);
    func_8004C8C0(0x19F);
}

extern u8 D_87E1A400[];
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern s32 func_80040E80(s32, void *);
extern void MainPool_FinalizeAllocation(s32);
void func_87E0CBC8(void *arg0) {
    s32 temp = MainPool_AllocState(main_pool_get_available(), 0);
    *(s32 *)((u8 *)arg0 + 8) = func_80040E80(temp, D_87E1A400);
    MainPool_FinalizeAllocation(temp);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0CC18.s")

extern void func_87F02684(s32);
extern void func_87E134C0(void);
void func_87E0CD84(s32 arg0) {
    func_87F02684(arg0 + 0x10);
    func_87E134C0();
}

void func_87E0CDAC(void *arg0) {
    void *var_v0;

    var_v0 = (*(void **)((u8 *)(arg0) + (0x1C)));
    if (var_v0 != NULL) {
        do {
            (*(u8 *)((u8 *)(var_v0) + (0x25))) = (u8) ((*(u8 *)((u8 *)(var_v0) + (0x25))) & ~1);
            var_v0 = (*(void **)((u8 *)(var_v0) + (4)));
        } while (var_v0 != NULL);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0CDDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0CE60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0CEE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D0A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D18C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D278.s")

extern void func_87E0D18C(void);
void func_87E0D3A0(void) {
    func_87E0D18C();
}

void func_87E0D3C0(u8 *arg0) {
    *(s32 *)(arg0 + 0x3F4) = 3;
    *(s32 *)(arg0 + 0x3FC) = 0;
    *(s32 *)(arg0 + 0x3F8) = *(s8 *)(*(u8 **)(arg0 + 4) + 0x218D);
    func_87E0D18C();
}

void func_87E0D3F4(u8 *arg0) {
    *(s32 *)(arg0 + 0x3F4) = 4;
    *(s32 *)(arg0 + 0x3FC) = 0;
    func_87E0D18C();
}

void func_87E0D41C(void) {
    func_87E0D18C();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D43C.s")

extern void func_87E0D278(void);
void func_87E0D500(void) {
    func_87E0D278();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D520.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D6BC.s")

void func_87E0D73C(void) {
    func_87E0D278();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D75C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D7D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0D8EC.s")

extern void func_87E0CEE4(void *, s32);
extern void func_87E134C0(void);
extern void func_87E13490(void);
extern void func_87E13480(void *);
extern void func_87E1366C(void);
void func_87E0DA4C(void *arg0) {
    s32 i;
    u8 *node;

    node = *(u8 **)((u8 *)arg0 + 0x1C);
    *(s32 *)((u8 *)arg0 + 0x3F4) = 4;
    if (node != NULL) {
        do {
            *(u8 *)(node + 0x25) |= 1;
            node = *(u8 **)(node + 4);
        } while (node != NULL);
    }
    i = 0;
    do {
        func_87E0CEE4(arg0, i);
        i += 1;
    } while (i != 4);
    func_87E134C0();
    func_87E13490();
    func_87E13480(NULL);
    func_87E1366C();
}

extern void func_87E0CC18(void *);
extern void func_87F0BD10();
void func_87E0DAE0(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)(arg0) + (0))) = 1;
    (*(s32 *)((u8 *)(arg0) + (4))) = arg1;
    (*(s32 *)((u8 *)(arg0) + (0x3F4))) = 4;
    (*(s32 *)((u8 *)(arg0) + (0x3FC))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x408))) = -1;
    func_87F0BD10();
    func_87E0CB88();
    func_87E0CBC8(arg0);
    func_87E0CC18(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0DB40.s")

s32 func_87E0DC78(u8 *arg0) {
    s32 result = 0;
    if (*(s32 *)(arg0 + 0x3FC) >= 0x29) {
        result = 1;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0DC98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0DE34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E110.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E2C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E32C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E3EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E714.s")

s32 func_87E0E850(void *arg0)
{
  s32 var_v1;
  void *var_v0;
  u8 *new_var;
  var_v0 = *((void **) (((u8 *) arg0) + 0x1C));
  var_v1 = 1;
  if (var_v0 != 0)
  {
    do
    {
      new_var = (u8 *) (*((void **) (((u8 *) (*((void **) (((u8 *) var_v0) + 0x38)))) + 0xC)));
      if ((*((s32 *) (new_var + 0x84))) != 0)
      {
        var_v1 = 0;
      }
      var_v0 = *((void **) (((u8 *) var_v0) + 4));
    }
    while (var_v0 != 0);
  }
  return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E88C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_310270/func_87E0E9B0.s")

extern void func_87F0AF4C(s32);
void func_87E0F124(s32 arg0) { func_87F0AF4C(arg0 + 16); }

s32 func_87E0F144(void *arg0, s32 arg1) {
    s32 new_var;
    new_var = *((s32 *) (((u8 *) arg0) + 0x18));
    return (arg1 * 0x18C) + new_var;
}
#endif
