#include "global.h"


#ifdef VERSION_US
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
extern void func_80057908(u8);
extern s32 func_8005A0B4(s32);
void func_81300020(s32 arg0) {
    main_pool_pop_state(0x50504354);
    main_pool_push_state(0x50504354);
    func_80057908((u8)arg0);
    func_8005A0B4(arg0);
}

s32 func_81300064(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 4) && (func_8005D92C(arg0) == 7) && (func_800606F4(arg0) > 0)) {
        return 1;
    }
    return 0;
}

void func_813000BC(void *arg0, s32 arg1) {
    typedef struct {
        u8 pad_0[0x1A141];
        s8 flag;
        u8 pad_1[0x2A];
        s32 value;
    } State;
    State *state = (State *)arg0;
    state->flag = arg1;
    state->value = 1;
}

void func_813000DC(u8 *arg0) {}

s32 func_813000E4(void *arg0) {
    s32 var_v1;
    s8 temp_a0;
    s8 temp_a0_2;
    s8 temp_a0_3;
    s8 temp_a1;
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0x1A148)));
    var_v1 = 0;
    temp_a1 = (*(s8 *)((u8 *)(temp_v0) + (0x900)));
    if ((temp_a1 >= 0) && (temp_a1 < 4)) {
        var_v1 = 1;
    }
    temp_a0 = (*(s8 *)((u8 *)(temp_v0) + (0x901)));
    if ((temp_a0 >= 0) && (temp_a0 < 4)) {
        var_v1 += 1;
    }
    temp_a0_2 = (*(s8 *)((u8 *)(temp_v0) + (0x902)));
    if ((temp_a0_2 >= 0) && (temp_a0_2 < 4)) {
        var_v1 += 1;
    }
    temp_a0_3 = (*(s8 *)((u8 *)(temp_v0) + (0x903)));
    if ((temp_a0_3 >= 0) && (temp_a0_3 < 4)) {
        var_v1 += 1;
    }
    return var_v1 < 2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_8130015C.s")

extern void func_81306B64(s32, s32, s32, s32, s32 *);
extern void func_81601A38(s32 *, s32);
extern void func_81601A78(s32 *, s32);
extern void func_81601B00(s32 *, s32, s32);
extern u8 D_81312A40;
void func_81300244(s32 arg0, s32 arg1, s32 arg2) {
    func_81601A38(&D_81312A40, 0);
    func_81601A78(&D_81312A40, 1);
    if ((arg1 < 4) && (arg1 >= 0)) {
        func_81601B00(&D_81312A40, arg1, 1);
    }
    func_81306B64(arg0 + 0xD18, 0x9B, 0xE1, arg2, &D_81312A40);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_813002D0.s")

s32 func_81300314(void *arg0, s32 arg1, s32 arg2) { u8 *base = (u8 *)arg0 + 0x18000; do { arg1 += arg2; if (arg1 < 0 || arg1 >= 4) break; if (*(s8 *)(*(u8 **)(base + 0x2148) + arg1 + 0x900) >= -1) break; } while (1); return arg1; }

extern void func_80057944(s32);

void func_81300350(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_80057944(var_s0 & 0xFF);
        var_s0 += 1;
    } while (var_s0 != 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81300390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81300570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81300730.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81300830.s")

void func_81300B48(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81300B50.s")

extern void func_8130A570(s32, s32);
extern void func_81304208(s32);
extern void func_81311C18(s32);
void func_81300BA0(s32 arg0) { func_8130A570(arg0 + 0xDA8, 0); func_81304208(arg0 + 0x15370); func_81311C18(arg0 + 0x74); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81300BE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81300E34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81300F7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81301030.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_813010B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_813011B8.s")

extern s32 func_813000E4(void *arg0);
extern s32 func_81302290(void *);
s8 func_8130125C(void *arg0, s32 arg1) {
    s32 sp1C;
    s8 temp_v1;
    sp1C = func_81302290(arg0);
    if (func_813000E4(arg0) != 0) {
        temp_v1 = *(s8 *)((u8 *)(*(void **)((u8 *)arg0 + 0x1A148)) + 0x954);
        if ((temp_v1 >= 0) && (temp_v1 < sp1C)) {
            return temp_v1;
        }
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_813012C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_813013C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81301448.s")

extern void func_8130015C(void *, s32);
void func_813014D0(void *arg0) {
    s32 temp_a0;
    temp_a0 = (s32)arg0;
    func_8130015C(arg0, 0);
    func_81300350();
    *(s32 *)((u8 *)temp_a0 + 0x1A168) = 0;
}

extern void func_81300350(void);
void func_8130150C(void *arg0) {
    s32 temp_a0;
    temp_a0 = (s32)arg0;
    func_8130015C(arg0, 0);
    func_81300350();
    *(s32 *)((u8 *)temp_a0 + 0x1A168) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81301548.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81301648.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_8130176C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_8130183C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_813018FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_813019C8.s")

void func_8130C334(void *);
void func_81311AAC(void *, s32);
void func_8130F2C4(void *, s32);
void func_8130B3B8(void *, void *);
s32 func_8130CDD4(void *);
void func_813000BC(void *, s32);
void func_81301BDC(s32 arg0, s32 arg1) {
    s32 sub = arg0 + 0xD18;
    func_8130C334((void *)sub);
    func_81311AAC((void *)(arg0 + 0x74), arg1);
    func_8130F2C4((void *)arg0, arg1);
    func_8130B3B8((void *)sub, (void *)(arg0 + 0x1A154));
    if (func_8130CDD4((void *)sub)) {
        func_813000BC((void *)arg0, 2);
    }
}

void func_81301C54(s32 arg0, s32 arg1) {
    s32 sub = arg0 + 0xD18;
    func_8130C334((void *)sub);
    func_81311AAC((void *)(arg0 + 0x74), arg1);
    func_8130F2C4((void *)arg0, arg1);
    func_8130B3B8((void *)sub, (void *)(arg0 + 0x1A154));
    if (func_8130CDD4((void *)sub)) {
        func_813000BC((void *)arg0, 2);
    }
}

void func_81301CCC(u8 *arg0, s32 arg1) {}

void func_81301CD8(u8 *arg0, s32 arg1) {}

extern void func_81311030(s32);
extern void func_8130F7B8(s32, s32);
void func_81301CE4(s32 arg0) {
    s32 temp_a0 = arg0 + 0xF64C;
    func_81311030(temp_a0);
    func_8130F7B8(temp_a0, arg0 + 0x1A154);
}

extern void func_8130881C(s32);
extern void func_8130302C(s32, s32);
extern void func_8130DEB8(s32, s32);
extern void func_813060C8(s32, s32);
extern void func_81311650(s32, s32);
void func_81301D28(s32 arg0, s32 arg1)
{
  func_8130881C(arg0 + 0xDA8);
  func_8130302C(arg0 + 0x15370, arg1);
  func_8130DEB8(arg0, arg1);
  func_813060C8(arg0 + 0xD18, arg1);
  func_81311650(arg0 + 0x74, arg1);
  if (!arg1)
  {
  }
}

void func_81301D94(s32 arg0) {
    s32 temp_a0 = arg0 + 0xF64C;
    func_81311030(temp_a0);
    func_8130F7B8(temp_a0, arg0 + 0x1A154);
}

extern void func_813054F4(s32);

void func_81301DD8(s32 arg0, s32 arg1) {
    func_813054F4(arg0 + 0xF630);
    func_81311650(arg0 + 0x74, arg1);
}

void func_81301E14(s32 arg0, s32 arg1)
{
  func_8130881C(arg0 + 0xDA8);
  func_8130302C(arg0 + 0x15370, arg1);
  if (arg1)
  {
  }
  func_8130DEB8(arg0, arg1);
  func_813060C8(arg0 + 0xD18, arg1);
  func_81311650(arg0 + 0x74, arg1);
 dummy_label_321312: ;
}

extern void func_8130CB5C(s32);
void func_81301E80(s32 arg0, s32 arg1) {
    func_8130CB5C(arg0 + 0xD18);
    func_81311650(arg0 + 0x74, arg1);
    func_8130DEB8(arg0, arg1);
}

void func_81301EC4(s32 arg0, s32 arg1) {
    func_8130CB5C(arg0 + 0xD18);
    func_81311650(arg0 + 0x74, arg1);
    func_8130DEB8(arg0, arg1);
}

void func_81301F08(s32 arg0, s32 arg1) {
    func_8130CB5C(arg0 + 0xD18);
    func_81311650(arg0 + 0x74, arg1);
    func_8130DEB8(arg0, arg1);
}

void func_81301F4C(u8 *arg0, s32 arg1) {}

void func_81301F58(u8 *arg0, s32 arg1) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81301F64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_8130209C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_813021B4.s")

extern s32 func_80055A74(s32);
extern s32 func_80055BA8(void);
s32 func_81302290(void *arg0) {
    s8 value = *(s8 *)((u8 *)(*(void **)((u8 *)arg0 + 0x1A148)) + 0x944);
    if (value < 0) {
        return 0;
    }
    func_80055A74(value);
    return func_80055BA8();
}

s32 func_813022D8(void *arg0) {
    s8 value = *(s8 *)((u8 *)(*(void **)((u8 *)arg0 + 0x1A148)) + 0x944);
    return value >= 0;
}

extern s32 func_813022D8(void *);
extern s32 func_81302290(void *);
extern void func_8160A270(void *);
extern void func_8160A384(void *, s32, s32, s32);
extern void func_80055028(void);
s32 func_813022F4(void *arg0, void *arg1) {
    typedef struct {
        u8 pad_0[0x1A13C];
        s32 status;
    } State;
    s32 sp1C;
    s8 value;
    if (func_813022D8(arg0) != 0) {
        sp1C = func_81302290(arg0);
        if (sp1C < 0xA) {
            func_8160A270(arg1);
            value = *(s8 *)((u8 *)(*(void **)((u8 *)arg0 + 0x1A148)) + 0x944);
            func_8160A384(arg1, value, sp1C, *(s32 *)((u8 *)arg0 + 0x1A168));
            ((State *)arg0)->status = 1;
            func_80055028();
            return 1;
        }
    }
    return 0;
}
#endif
