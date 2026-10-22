#include "global.h"


#ifdef VERSION_US
extern void *D_87F119DC;
extern void func_87F0B4AC(void *, f32 *, f32 *, s16 *);
void func_87E0B700(void) {
    void *state = D_87F119DC;
    void *a0 = *(void **)((u8 *)*(void **)((u8 *)state + 0x38) + 0x0C);
    func_87F0B4AC(
        (u8 *)a0 + 0x14,
        (f32 *)((u8 *)state + 0x48),
        (f32 *)((u8 *)state + 0x54),
        (s16 *)((u8 *)state + 0x42));
}

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern void GeoRender_ApplyMaterialState();
void func_87E0B73C(s32 arg0, s32 arg1) {
    void *context;

    if (arg0 == 5) {
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238);
        context = *(void **)((u8 *)D_8009491C + 0x14);
        gSPSegment(D_800D0510++, 0xF,
                   *(void **)((u8 *)*(void **)((u8 *)context + 4) + 8));
        gSPDisplayList(D_800D0510++, *(void **)context);
        GeoRender_ApplyMaterialState();
    }
}

extern void func_8004C8C0(s32);

void func_87E0B7F4(void) {
    func_8004C8C0(0x15E);
    func_8004C8C0(0x15F);
    func_8004C8C0(0x160);
    func_8004C8C0(0x162);
    func_8004C8C0(0x163);
}

extern u8 D_87E1A2C0[];
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern s32 process_geo_layout(s32, void *);
extern void MainPool_FinalizeAllocation(s32);
void func_87E0B834(void *arg0) {
    s32 temp = MainPool_AllocState(main_pool_get_available(), 0);
    *(s32 *)((u8 *)arg0 + 8) = process_geo_layout(temp, D_87E1A2C0);
    MainPool_FinalizeAllocation(temp);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0B884.s")

extern s32 func_8004C990(s32, s32);

void func_87E0B9F0(void *arg0) {
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s8 temp_v1;
    void *temp_s0;

    var_s1 = 0;
    var_s2 = 0;
    var_s3 = 0;
    do {
        temp_s0 = *(void **)((u8 *)(*(s32 *)((u8 *)arg0 + 0x20) + var_s2) + 0xC);
        *(void **)temp_s0 = (void *)(*(s32 *)((u8 *)arg0 + 0x24) + var_s3);
        *(s32 *)((u8 *)temp_s0 + 8) = func_8004C990(0x162, var_s1);
        temp_v1 = *(s8 *)((u8 *)*(void **)temp_s0 + 1);
        switch (temp_v1) {
        case 0:
            *(s32 *)((u8 *)temp_s0 + 4) = func_8004C990(0x15E, 1);
            *(s32 *)((u8 *)temp_s0 + 0xC) = 0;
            break;
        case 1:
            *(s32 *)((u8 *)temp_s0 + 4) = func_8004C990(0x15E, 0);
            *(s32 *)((u8 *)temp_s0 + 0xC) = func_8004C990(0x15F, 0);
            break;
        case 2:
            *(s32 *)((u8 *)temp_s0 + 4) = func_8004C990(0x15E, 2);
            *(s32 *)((u8 *)temp_s0 + 0xC) = func_8004C990(0x15F, 1);
            break;
        }
        temp_v1 = *(s8 *)((u8 *)*(void **)temp_s0 + 2);
        switch (temp_v1) {
        case 0:
            *(s32 *)((u8 *)temp_s0 + 0x10) = func_8004C990(0x163, 0);
            break;
        case 1:
            *(s32 *)((u8 *)temp_s0 + 0x10) = func_8004C990(0x163, 1);
            break;
        }
        var_s1 += 1;
        var_s2 += 0x10;
        var_s3 += 3;
    } while (var_s1 != 6);
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0BB5C.s")

extern void func_87F02684(s32);
void func_87E0BE28(s32 arg0) {
    func_87F02684(arg0 + 12);
}

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

extern f32 D_87E1A3B4[];
extern void func_87E0BB5C();
void func_87E0C390(void *arg0) {
    f32 *var_v1;
    void *var_v0;

    var_v0 = *(void **)((u8 *)arg0 + 0x18);
    var_v1 = D_87E1A3B4;
    if (var_v0 != 0) {
        do {
            var_v1 += 3;
            *(u8 *)((u8 *)var_v0 + 0x25) |= 1;
            *(f32 *)((u8 *)var_v0 + 0x48) = var_v1[-3];
            *(f32 *)((u8 *)var_v0 + 0x4C) = var_v1[-2];
            *(f32 *)((u8 *)var_v0 + 0x50) = var_v1[-1];
            var_v0 = *(void **)((u8 *)var_v0 + 4);
        } while (var_v0 != 0);
    }
    func_87E0BB5C();
}

extern void func_87E0BEB4();
void func_87E0C3F8(void *arg0) {
    f32 *var_v1;
    void *var_v0;

    var_v0 = *(void **)((u8 *)arg0 + 0x18);
    var_v1 = D_87E1A3B4;
    if (var_v0 != 0) {
        do {
            var_v1 += 3;
            *(f32 *)((u8 *)var_v0 + 0x48) = var_v1[-3];
            *(f32 *)((u8 *)var_v0 + 0x4C) = var_v1[-2];
            *(f32 *)((u8 *)var_v0 + 0x50) = var_v1[-1];
            var_v0 = *(void **)((u8 *)var_v0 + 4);
        } while (var_v0 != 0);
    }
    func_87E0BEB4();
}

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

extern void func_87F0B1A4(u8 *, u8 *, f32, s32, f32, s32, s32);
extern void func_87F0B2F4(u8 *, s16 *, f32, f32, f32, s32, s32);
void func_87E0C4B4(void *arg0) {
    void *var_v0;
    void *var_v1;

    var_v0 = *(void **)((u8 *)arg0 + 0x18);
    if (var_v0 != 0) {
        do {
            var_v1 = *(void **)((u8 *)*(void **)((u8 *)var_v0 + 0x38) + 0x0C);
            func_87F0B1A4((u8 *)var_v1 + 0x14,
                          (u8 *)var_v0 + 0x48,
                          *(f32 *)((u8 *)var_v0 + 0x48) - 160.0f,
                          *(s32 *)((u8 *)var_v0 + 0x4C),
                          300.0f, 15, 0x2000);
            func_87F0B2F4((u8 *)var_v1 + 0x14,
                          (s16 *)((u8 *)var_v0 + 0x42),
                          0.0f, -90.0f, 0.0f, 15, 0);
            var_v0 = *(void **)((u8 *)var_v0 + 4);
        } while (var_v0 != 0);
    }
}

extern void func_87E0BB5C(); extern void func_87E0BFFC(s32, s32, s32);
void func_87E0C590(s32 arg0, s32 arg1) { func_87E0BB5C(); func_87E0BFFC(arg0, arg1, 1); }

void WidgetTree_RunMessagePanelSilent_fragment63(s32 arg0, s32 arg1) {
    func_87E0BFFC(arg0, arg1, 0);
}

void func_87E0C5E4(s32 arg0) {
    func_87E0BFFC(arg0, -1, 0);
}

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

extern void func_87F0277C(void *, s32 *);
extern s32 func_87E0BE78(void *arg0);
s32 func_87E0C664(s32 *arg0) {
    s32 temp_v0;
    s32 sp18;

    sp18 = 1;
    if (func_87E0BE78(arg0) != 0) {
        *arg0 = 1;
    } else {
        *arg0 = 0;
    }
    temp_v0 = *arg0;
    if ((temp_v0 != 0) && (temp_v0 == 1)) {
        sp18 = 0;
    }
    func_87F0277C((u8 *)arg0 + 0xC, arg0);
    return sp18;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_30F070/func_87E0C6CC.s")

extern void func_87F0AF4C(s32);
void func_87E0C8DC(s32 arg0) {
    func_87F0AF4C(arg0 + 12);
}
#endif
