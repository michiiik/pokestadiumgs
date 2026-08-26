#include "global.h"


#ifdef VERSION_US
f32 func_81600020(f32 arg0) {
    if (arg0 <= 0.0f) {
        return 0.0f;
    }
    if (arg0 >= 1.0f) {
        return 1.0f;
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_8160006C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_816000D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_8160014C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_816001D0.s")

f32 func_8160024C(f32 arg0) {
    if (arg0 <= 0.0f) {
        return 0.0f;
    }
    if (arg0 >= 1.0f) {
        return 1.0f;
    }
    return arg0 * arg0;
}

f32 func_8160029C(f32 arg0) {
    if (arg0 <= 0.0f) {
        return 0.0f;
    }
    if (arg0 >= 1.0f) {
        return 1.0f;
    }
    return sqrtf(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_816002E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600340.s")

void func_816003B0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) { *(u16 *)(arg0 + 0) = arg1; *(u16 *)(arg0 + 2) = arg2; *(u16 *)(arg0 + 4) = arg3; *(u16 *)(arg0 + 6) = arg4; }

void func_816003C8(u8 *arg0) {
    (*(s32 *)((u8 *)(arg0) + (0x10))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x14))) = 0;
    (*(s32 *)((u8 *)(arg0) + (8))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x18))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0xC))) = 0;
    func_816003B0(arg0, 0, 0, 0, 0);
}

void func_81600408(u8 *arg0) {
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0x10)));
    if (temp_v0 != NULL) {
        (*(void **)((u8 *)(temp_v0) + (0x14))) = (void *) (*(void **)((u8 *)(arg0) + (0x14)));
    }
    temp_v0_2 = (*(void **)((u8 *)(arg0) + (0x14)));
    if (temp_v0_2 != NULL) {
        (*(void **)((u8 *)(temp_v0_2) + (0x10))) = (void *) (*(void **)((u8 *)(arg0) + (0x10)));
    }
    func_816003C8(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600450.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_816004C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600520.s")

s32 func_816005CC(u8 *arg0) {
    return ((u32)*(s16 *)(arg0 + 6) * (u32)*(s16 *)(arg0 + 4)) != 0;
}

s32 func_816005E8(void *arg0, void *arg1) {
    s32 var_v1;

    var_v1 = (*(s16 *)((u8 *)(arg1) + (0))) == (*(s16 *)((u8 *)(arg0) + (0)));
    if (var_v1 != 0) {
        var_v1 = (*(s16 *)((u8 *)(arg1) + (2))) == (*(s16 *)((u8 *)(arg0) + (2)));
        if (var_v1 != 0) {
            var_v1 = (*(s16 *)((u8 *)(arg1) + (4))) == (*(s16 *)((u8 *)(arg0) + (4)));
            if (var_v1 != 0) {
                var_v1 = (*(s16 *)((u8 *)(arg1) + (6))) == (*(s16 *)((u8 *)(arg0) + (6)));
            }
        }
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600648.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_816006BC.s")

s32 func_8160072C(s16 *arg0) {
    return (u32)arg0[3] * (u32)arg0[2];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600744.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600780.s")

s32 func_816007BC(void *arg0) { u8 *base = *(u8 **)((u8 *)arg0 + 0x28); u8 *next = *(u8 **)(base + 8); s32 result; if (next != NULL) result = *(s32 *)(next + 0x14); else result = *(s32 *)base; return result; }

void func_816007E0(void) {}
void func_816007E0_padding(void) {}
void func_816007E0_padding2(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_816007F8.s")

typedef struct B1648Node B1648Node; typedef struct B1648Holder B1648Holder; typedef struct B1648Root B1648Root; struct B1648Node { u8 pad0[8]; s32 key; u8 pad0C[4]; B1648Node *next; }; struct B1648Holder { u8 pad0[8]; B1648Node *head; }; struct B1648Root { u8 pad0[0x28]; B1648Holder *holder; };
void *func_81600848(B1648Root *arg0, s32 arg1) { B1648Node *node = arg0->holder->head; while (node != NULL) { if (arg1 == node->key) return node; node = node->next; } return NULL; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600884.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_816008EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600954.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_816009C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600A34.s")

s32 func_816007F8();
extern void func_816009C0(s32, s32, s32, s32);

void func_81600AF0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = func_816007F8();
    if (temp_v0 != 0) {
        func_816009C0(arg0, temp_v0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600B30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600DA8.s")

void func_81600E04(void *arg0)
{
  void *var_v0;
  void **new_var;
  var_v0 = *(*((void ***) (((u8 *) arg0) + 0x28)));
  new_var = *((void ***) (((u8 *) arg0) + 0x28));
  if (var_v0 != 0)
  {
    do
    {
      var_v0 = *((void **) (((u8 *) var_v0) + 0x14));
    }
    while (var_v0 != 0);
    var_v0 = *new_var;
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600E28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600F0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_816013EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_816018CC.s")
#endif
