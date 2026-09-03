#include "global.h"


#ifdef VERSION_US
f32 fragment11_main(f32 arg0) {
    if (arg0 <= 0.0f) {
        return 0.0f;
    }
    if (arg0 >= 1.0f) {
        return 1.0f;
    }
    return arg0;
}

f32 __sinf(f32, f32);
extern f32 D_8160BF40;
f32 func_8160006C(f32 arg0) {
    if (arg0 <= 0.0f) {
        return 0.0f;
    }
    if (arg0 >= 1.0f) {
        return 1.0f;
    }
    return __sinf(arg0 * D_8160BF40, arg0);
}

f32 __cosf(f32, f32);
extern f32 D_8160BF44;
f32 func_816000D4(f32 arg0) {
    if (arg0 <= 0.0f) {
        return 0.0f;
    }
    if (arg0 >= 1.0f) {
        return 1.0f;
    }
    return 1.0f - __cosf(arg0 * D_8160BF44, arg0);
}

f32 __sinf(f32, f32);
extern f32 D_8160BF48;
extern f32 D_8160BF4C;
f32 func_8160014C(f32 arg0) {
    if (arg0 <= 0.0f) {
        return 0.0f;
    }
    if (arg0 >= 1.0f) {
        return 1.0f;
    }
    return (__sinf((arg0 * D_8160BF48) - D_8160BF4C, arg0) * 0.5f) + 0.5f;
}

f32 __cosf(f32, f32);
extern f32 D_8160BF50;
f32 func_816001D0(f32 arg0) {
    if (arg0 <= 0.0f) {
        return 0.0f;
    }
    if (arg0 >= 1.0f) {
        return 1.0f;
    }
    return 0.5f - (__cosf(arg0 * D_8160BF50, arg0) * 0.5f);
}

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

f32 func_816002E8(f32 arg0) {
    if (arg0 <= 0.0f) {
        return 0.0f;
    }
    if (arg0 >= 1.0f) {
        return 1.0f;
    }
    return arg0 * arg0 * arg0;
}

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

s32 func_816004C0(u8 *arg0, u8 *arg1) {
    return (*(s16 *)(arg0 + 0) + *(s16 *)(arg0 + 4) < *(s16 *)(arg1 + 0))
        || (*(s16 *)(arg1 + 0) + *(s16 *)(arg1 + 4) < *(s16 *)(arg0 + 0))
        || (*(s16 *)(arg0 + 2) + *(s16 *)(arg0 + 6) < *(s16 *)(arg1 + 2))
        || (*(s16 *)(arg1 + 2) + *(s16 *)(arg1 + 6) < *(s16 *)(arg0 + 2));
}

s32 func_81600520(void *arg0, s32 arg1) {
    typedef struct {
        s16 x;
        s16 y;
        s16 width;
        s16 height;
    } Rect;
    Rect *rect = (Rect *)arg0;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s32 var_v1;
    s32 var_v1_2;

    if (arg1 != 0) {
        temp_v0 = rect->x;
        var_v1_2 = temp_v0 < 1;
        if (var_v1_2 != 0) {
            var_v1_2 = temp_v0 + rect->width >= 0x280;
            if (var_v1_2 != 0) {
                temp_v0_2 = rect->y;
                var_v1_2 = temp_v0_2 < 1;
                if (var_v1_2 != 0) {
                    var_v1_2 = temp_v0_2 + rect->height >= 0x1E0;
                }
            }
        }
        return var_v1_2;
    }
    temp_v0_3 = rect->x;
    var_v1 = temp_v0_3 < 1;
    if (var_v1 != 0) {
        var_v1 = temp_v0_3 + rect->width >= 0x140;
        if (var_v1 != 0) {
            temp_v0_4 = rect->y;
            var_v1 = temp_v0_4 < 1;
            if (var_v1 != 0) {
                var_v1 = temp_v0_4 + rect->height >= 0xF0;
            }
        }
    }
    return var_v1;
}

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

s32 func_816004C0(u8 *, u8 *);
void func_81600648(u8 *arg0) {
    u8 *var_s0;

    if (func_816005CC(arg0) == 0) {
        (*(s32 *)((u8 *)(arg0) + (0x18))) = 0;
        return;
    }
    var_s0 = (*(u8 **)((u8 *)(arg0) + (0x14)));
    (*(s32 *)((u8 *)(arg0) + (0x18))) = 1;
    if (var_s0 != NULL) {
        do {
            if (func_816004C0(var_s0, arg0) == 0) {
                func_81600648(var_s0);
            }
            var_s0 = (*(u8 **)((u8 *)(var_s0) + (0x14)));
        } while (var_s0 != NULL);
    }
}

s32 func_81600450(u8 *, void *);
void func_816006BC(u8 *arg0) {
    void *var_s0;

    if (((*(s32 *)((u8 *)(arg0) + (0x18))) != 0) && (func_816005CC(arg0) != 0)) {
        var_s0 = (*(void **)((u8 *)(arg0) + (0x10)));
        if (var_s0 != NULL) {
            do {
                if (func_81600450(arg0, var_s0) != 0) {
                    (*(s32 *)((u8 *)(var_s0) + (0x18))) = 0;
                }
                var_s0 = (*(void **)((u8 *)(var_s0) + (0x10)));
            } while (var_s0 != NULL);
        }
    }
}

s32 func_8160072C(s16 *arg0) {
    return (u32)arg0[3] * (u32)arg0[2];
}

void *func_81600744(void *arg0, s32 arg1) {
    void *result = NULL;
    void *node;

    node = *(void **)(*(u8 **)((u8 *)arg0 + 0x28));
    while (node != NULL) {
        if (arg1 == *(s32 *)((u8 *)node + 8)) {
            return node;
        }
        node = *(void **)((u8 *)node + 0x14);
    }
    return result;
}

void *func_81600780(void *arg0, s32 arg1) {
    void *result = NULL;
    void *node;

    node = *(void **)(*(u8 **)((u8 *)arg0 + 0x2C));
    while (node != NULL) {
        if (arg1 == *(s32 *)((u8 *)node + 8)) {
            return node;
        }
        node = *(void **)((u8 *)node + 0x14);
    }
    return result;
}

s32 func_816007BC(void *arg0) { u8 *base = *(u8 **)((u8 *)arg0 + 0x28); u8 *next = *(u8 **)(base + 8); s32 result; if (next != NULL) result = *(s32 *)(next + 0x14); else result = *(s32 *)base; return result; }

void func_816007E0(void) {}
void func_816007E0_padding(void) {}
void func_816007E0_padding2(void) {}

extern s32 func_816007BC(void *arg0);
s32 func_816007F8(void *arg0, s32 arg1) {
    s32 result;
    s32 node;

    result = func_816007BC(arg0);
    node = result;
    if (result != 0) {
        do {
            if (arg1 == *(s32 *)((u8 *)(u32)node + 8)) {
                return node;
            }
            node = *(s32 *)((u8 *)(u32)node + 0x14);
        } while (node != 0);
    }
    return 0;
}

typedef struct B1648Node B1648Node; typedef struct B1648Holder B1648Holder; typedef struct B1648Root B1648Root; struct B1648Node { u8 pad0[8]; s32 key; u8 pad0C[4]; B1648Node *next; }; struct B1648Holder { u8 pad0[8]; B1648Node *head; }; struct B1648Root { u8 pad0[0x28]; B1648Holder *holder; };
void *func_81600848(B1648Root *arg0, s32 arg1) { B1648Node *node = arg0->holder->head; while (node != NULL) { if (arg1 == node->key) return node; node = node->next; } return NULL; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600884.s")

extern void func_81600408(u8 *arg0);
void func_816008EC(void *arg0, u8 *arg1) {
    u8 *holder;
    u8 *node;

    holder = *(u8 **)((u8 *)arg0 + 0x28);
    node = *(u8 **)holder;
    if (arg1 == node) {
        *(u8 **)holder = *(u8 **)(node + 0x14);
    }
    holder = *(u8 **)((u8 *)arg0 + 0x28);
    node = *(u8 **)(holder + 8);
    if (arg1 == node) {
        *(u8 **)(holder + 8) = *(u8 **)(node + 0x10);
    }
    holder = *(u8 **)((u8 *)arg0 + 0x28);
    node = *(u8 **)(holder + 4);
    if (arg1 == node) {
        *(u8 **)(holder + 4) = *(u8 **)(node + 0x10);
    }
    func_81600408(arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600954.s")

extern void * func_81600780(void *arg0, s32 arg1);
extern s32 func_816007F8(void *arg0, s32 arg1);
void func_816009C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    func_816007F8((void *)(u32)arg0, arg2);
    *(s32 *)((u8 *)(u32)arg1 + 0x1C) = arg3;
    if (arg3 == 0) {
        temp_v0 = func_81600780((void *)(u32)arg0, arg2);
        if (temp_v0 == NULL || *(s32 *)((u8 *)temp_v0 + 0x1C) == 1) {
            arg3 = 1;
        }
    }
    *(s32 *)((u8 *)(u32)arg1 + 0x18) = arg3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600A34.s")

s32 func_816007F8();
extern void func_816009C0(s32, s32, s32, s32);

void func_81600AF0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = func_816007F8(arg0, arg1);
    if (temp_v0 != 0) {
        func_816009C0(arg0, temp_v0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_D7BC0/func_81600B30.s")

extern void * func_81600744(void *arg0, s32 arg1);
s32 func_81600DA8(void *arg0, void *arg1) {
    void *temp_v0;

    temp_v0 = func_81600744(arg0, (s32)(u32)arg1);
    if (temp_v0 == NULL) {
        return 1;
    }
    if (*(s16 *)((u8 *)temp_v0 + 4) <= 0) {
        return 0;
    }
    if (*(s16 *)((u8 *)temp_v0 + 6) <= 0) {
        return 0;
    }
    return *(s32 *)((u8 *)temp_v0 + 0x18);
}

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

extern u8 *D_8008720C;
extern void *osViGetCurrentFramebuffer(void);
extern s32 func_800356CC(s32);
extern void Dma_CopyChunks(s32, s32, s32);
extern void func_800226C0(s32);
void func_816018CC(s32 arg0) {
    s32 pad_frame[2];
    s32 sp1C;
    void *sp18;
    s32 temp_v1;
    s32 var_v0;

    if ((*(u16 *)(D_8008720C + 6) & 0x2000) && (*(u16 *)(D_8008720C + 8) & 0x8000)) {
        sp18 = osViGetCurrentFramebuffer();
        sp1C = func_800356CC(9);
        temp_v1 = func_800356CC(9);
        if (arg0 != 0) {
            var_v0 = 4;
        } else {
            var_v0 = 1;
        }
        Dma_CopyChunks((s32)(u32)sp18, sp1C, temp_v1 + (var_v0 * 0x25800));
        func_800226C0(2);
    }
}
#endif
