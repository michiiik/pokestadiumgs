#include "global.h"


#ifdef VERSION_US
extern s32 D_80094CF0; s32 func_80043700(s32 arg0, s32 arg1) { if (!arg0) { D_80094CF0 = arg1; } return 0; }

extern u8 D_80094CF8;
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern s32 func_80040E80(s32, void *);
extern void MainPool_FinalizeAllocation(s32);
extern void GeoCamera_SetViewport(void *, s16, s16, s16, s32);
extern void GeoCamera_SetPerspective(void *, f32, f32, f32);
void func_80043714(void *arg0, s16 arg1, s32 arg2) {
    s32 camera;
    s32 state;
    state = MainPool_AllocState(main_pool_get_available(), 0);
    *((s32 *)(((u8 *)arg0) + 0x14)) = func_80040E80(state, &D_80094CF8);
    *((s32 *)(((u8 *)arg0) + 0x18)) = D_80094CF0;
    MainPool_FinalizeAllocation(state);
    camera = *((s32 *)((u8 *)(u32)(*((u32 *)(((u8 *)arg0) + 0x14))) + 0xC));
    GeoCamera_SetViewport((void *)(u32)camera, 0, 0, arg1, arg2);
    GeoCamera_SetPerspective((void *)(u32)camera, 30.0f, 100.0f, 12800.0f);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_800437B4.s")

extern s32 func_80064728();
extern s32 func_8004BA34(s32);
extern void func_8004B7E0(s32, void *);
extern f32 func_8004B888(s32);
s32 func_80043950(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 pad_frame[2];
    s32 sp24;
    s32 temp_v0;
    s32 var_a0;
    u8 *temp_s0;
    s32 offset;
    s32 var_v1 = 0;
    if ((arg0 != 0) && (arg1 < *((s16 *)((u8 *)arg0 + 2)))) {
        temp_v0 = *((s32 *)((u8 *)arg0 + 0xC));
        if (temp_v0 != 0) {
            offset = arg1 * 0x24;
            temp_s0 = (u8 *)(temp_v0 + offset);
            *((u16 *)temp_s0) = 0;
            if (arg2 != 0) {
                var_a0 = func_80064728(arg3);
                *((u16 *)temp_s0) |= 2;
            } else {
                var_a0 = arg3;
            }
            *((u16 *)(temp_s0 + 2)) = 0;
            *((u16 *)temp_s0) |= 1;
            sp24 = var_a0;
            *((s8 *)(temp_s0 + 6)) = func_8004BA34(var_a0);
            func_8004B7E0(sp24, temp_s0 + 8);
            *((f32 *)(temp_s0 + 0x14)) = func_8004B888(sp24);
            var_v1 = 1;
            *((s32 *)(temp_s0 + 0x1C)) = arg3;
        }
    }
    return var_v1;
}

void func_80043A0C(void* arg0, void* arg1, s32 arg2) {
    func_80043950(arg0, arg1, 0, arg2);
}

void func_80043A30(void* arg0, void* arg1, s32 arg2) {
    func_80043950(arg0, arg1, 1, arg2);
}

s32 func_80043A54(void *arg0, s32 arg1, s16 arg2)
{
  s32 temp_v0;
  u8 *new_var;
  s32 var_v1;
  var_v1 = 0;
  if ((arg0 != 0) && (arg1 < (*((s16 *) (((u8 *) arg0) + 2)))))
  {
    ;
    if ((*((s32 *) (((u8 *) arg0) + 0xC))) != 0)
    {
      new_var = (u8 *) ((*((s32 *) (((u8 *) arg0) + 0xC))) + (arg1 * (0x24 & 0xFFu)));
      *((s16 *) (new_var + 2)) = arg2;
      var_v1 = 1;
    }
  }
  return var_v1;
}

s32 func_80043AA0(void *arg0, s32 arg1, s16 arg2) {
    s32 temp_v0;
    u8 *new_var;
    s32 var_v1;
    var_v1 = 0;
    if ((arg0 != 0) && (arg1 < (*((s16 *)(((u8 *)arg0) + 2))))) {
        if ((*((s32 *)(((u8 *)arg0) + 0xC))) != 0) {
            new_var = (u8 *)((*((s32 *)(((u8 *)arg0) + 0xC))) + (arg1 * (0x24 & 0xFFu)));
            *((s8 *)(new_var + 6)) = arg2;
            var_v1 = 1;
        }
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043AEC.s")

s32 func_80043B48(void *arg0, s32 arg1, f32 arg2) {
    s32 temp_v0;
    u8 *new_var;
    s32 var_v1;
    var_v1 = 0;
    if ((arg0 != 0) && (arg1 < (*((s16 *)(((u8 *)arg0) + 2))))) {
        if ((*((s32 *)(((u8 *)arg0) + 0xC))) != 0) {
            new_var = (u8 *)((*((s32 *)(((u8 *)arg0) + 0xC))) + (arg1 * (0x24 & 0xFFu)));
            *((f32 *)(new_var + 0x14)) = arg2;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 func_80043B8C(void *arg0, s32 arg1, u16 arg2) {
    s32 temp_v0;
    u8 *new_var;
    s32 var_v1;
    var_v1 = 0;
    if ((arg0 != 0) && (arg1 < (*((s16 *)(((u8 *)arg0) + 2))))) {
        if ((*((s32 *)(((u8 *)arg0) + 0xC))) != 0) {
            new_var = (u8 *)((*((s32 *)(((u8 *)arg0) + 0xC))) + (arg1 * (0x24 & 0xFFu)));
            *((u16 *)(new_var + 4)) = arg2;
            var_v1 = 1;
        }
    }
    return var_v1;
}

typedef struct { u8 pad0[2]; s16 count; u8 pad4[8]; u8 *base; } Func80043BD4State;
s32 func_80043BD4(Func80043BD4State *arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;
    if ((arg0 != NULL) && (arg1 < arg0->count)) {
        if (arg0->base != 0) {
            arg0 = (Func80043BD4State *)((u8 *)arg0->base + (arg1 * 0x24));
            (*(s32 *)((u8 *)arg0 + 0x20)) = arg2;
            var_v1 = 1;
        }
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043C14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80043E70.s")

typedef struct B4410Value B4410Value; typedef struct B4410Entry B4410Entry; typedef struct B4410State B4410State; struct B4410Value { u8 pad[8]; s32 value; }; struct B4410Entry { u8 pad[0x18]; B4410Value *value; u8 tail[8]; }; struct B4410State { u8 pad0[2]; s16 count; u8 pad4[8]; B4410Entry *entries; };
s32 func_8004410C(B4410State *arg0, s32 arg1) { s32 result = 0; if (arg1 < arg0->count) { result = arg0->entries[arg1].value->value; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/44300/func_80044144.s")

extern s32 func_8004BB58(s32, s32);
extern s32 func_8004BC6C(s32, s32);
extern f32 func_8004BAE8(s32, s32);
extern void func_8004BBA8(s32, s32, void *);
extern s32 func_80043AEC(void *, s32, void *);
s32 func_8004418C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_v1;
    u8 sp28[0xC];
    var_v1 = 0;
    if ((arg0 != 0) && (arg2 != 0)) {
        func_80043A54(arg0, arg1, (s16)func_8004BB58(arg2, arg3));
        func_80043AA0(arg0, arg1, (s16)func_8004BC6C(arg2, arg3));
        func_80043B48(arg0, arg1, func_8004BAE8(arg2, arg3));
        func_8004BBA8(arg2, arg3, sp28);
        func_80043AEC(arg0, arg1, sp28);
        var_v1 = 1;
    }
    return var_v1;
}

extern s8 D_80094CF4; void func_80044250(s8 value) { D_80094CF4 = value; }
#endif
