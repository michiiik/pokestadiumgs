#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80050BE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80050CAC.s")

extern s32 D_800972B0[]; s32 func_80050CF8(s32 arg0){s32 result=0;if(arg0>=0&&arg0<4)result=D_800972B0[arg0];return result;}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80050D20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80050DE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80050E88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80050F60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051028.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800510CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051138.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800511A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051208.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051274.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800512E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005134C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800513B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051424.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051490.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800514FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051568.s")

u16 func_800515D4(u8* arg0, s32 arg1) {
    u16 var_v1 = 0;

    while (arg1-- > 2) {
        var_v1 += *arg0++;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051610.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051680.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800516C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051724.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051780.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800517D8.s")

extern void func_80061248();
extern void func_800619E8(void *);

void func_80051830(void *arg0) {
    func_80061248();
    func_800619E8(arg0);
    (*(u16 *)((u8 *)(arg0) + (0x26))) = (u16) (*(u16 *)((u8 *)(arg0) + (0x28)));
}

extern void func_800615D0(s32,s32); void func_80051864(s32 a0,s32 a1){func_800615D0(a1,a0);}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051890.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800519AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051A8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051BF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051D64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80052150.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005253C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80052928.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80052ECC.s")

extern void func_80052ECC(s32);

void func_800530DC(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_80052ECC(var_s0);
        var_s0 += 1;
    } while (var_s0 != 4);
}

extern void func_80052928(s32,s32); extern void func_80051D64(s32,s32); void func_8005311C(s32 a0,s32 a1){func_80052928(a0,a1);func_80051D64(a0,a1);}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005314C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053230.s")

s32 func_800532C4(s32 arg0){s32 result=0;switch(arg0){case 0x10:result=1;break;case 0x11:result=0xE;break;}return result;}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800532F0.s")

void func_80053384(void *arg0, void *arg1) { func_80051A8C(arg0, arg1, 1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800533A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053440.s")

extern u8 D_801281F0[]; u8 *func_800534FC(s32 arg0){u8 *result=NULL;if(arg0>=0&&arg0<0xE)result=D_801281F0+arg0*0x20;return result;}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053524.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053584.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800535D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005370C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053808.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053908.s")

extern void func_80062614(void);
void func_80053A30(void) {
    func_80062614();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053A50.s")

extern void func_80060C08(u16 *,u16 *); void func_80053AC8(u16 *a0,u16 *a1){a0[0]=a1[0];a0[1]=a1[1];a0[2]=a1[2];func_80060C08(a0+4,a1+4);}

extern void func_80060C08(u16 *,u16 *); void func_80053B04(u16 *a0,u16 *a1){a0[0]=a1[0];a0[1]=a1[1];func_80060C08(a0+2,a1+2);}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053B38.s")

extern void func_8006276C(s32,s32); void func_80053DDC(s32 a0,s32 a1){func_8006276C(a1,a0);}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053E08.s")

extern void func_80060D70(u8 *, u8 *);
void func_80053E8C(u8 *arg0, u8 *arg1) {
    *(u16 *)(arg1 + 0) = *(u16 *)(arg0 + 0);
    *(u16 *)(arg1 + 2) = *(u16 *)(arg0 + 2);
    *(u16 *)(arg1 + 4) = *(u16 *)(arg0 + 4);
    func_80060D70(arg1 + 8, arg0 + 8);
}

void func_80053ECC(u8 *arg0, u8 *arg1) {
    *(u16 *)(arg1 + 0) = *(u16 *)(arg0 + 0);
    *(u16 *)(arg1 + 2) = *(u16 *)(arg0 + 2);
    func_80060D70(arg1 + 4, arg0 + 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053F04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054210.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054248.s")

extern void func_80053B38(s32, s32, s32, u8 *);

u8 func_800542B0(s32 arg0) {
    u8 sp1F;

    sp1F = 0;
    func_80053B38(0x13, 0, arg0, &sp1F);
    return sp1F;
}

extern void func_80053F04(s32, s32, s32, u8 *);

void func_800542E4(s32 arg0, u8 arg1) {
    u8 sp1F;

    sp1F = arg1;
    func_80053F04(0x13, 0, arg0, &sp1F);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005431C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005437C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054410.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054488.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005453C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800545B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054668.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800546E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054794.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800547F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005487C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800548C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005493C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054974.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800549DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054A24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054AA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054AF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054B7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054CC4.s")

s32 func_80054E10(u16 *arg0)
{
  int new_var;
  func_80050D20(0x15, -1);
  new_var = (*arg0) != 0xFFFF;
  return new_var;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055028.s")

extern u8 D_801281C0;
void func_80055088(s32 arg0, u32 arg1) {
    void *temp_v0;

    if ((arg1 >= 0x424E4B30U) && (arg1 < 0x424E4B34U)) {
        temp_v0 = ((arg1 - 0x424E4B30) * 0xC) + &D_801281C0;
        (*(s32 *)((u8 *)(temp_v0) + (4))) = 0;
        (*(s32 *)((u8 *)(temp_v0) + (0))) = (s32) ((*(s32 *)((u8 *)(temp_v0) + (0))) & ~3);
        (*(s32 *)((u8 *)(temp_v0) + (8))) = 0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800550E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800551EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055260.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800555B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005565C.s")

extern void func_80055260(s32, s32);
void func_8005577C(s32 arg0) {
    s32 var_s0;

    var_s0 = 1;
    do {
        if (arg0 == 0) {
            func_80055260(0x11, var_s0);
        } else {
            func_8005311C(0x11, var_s0);
        }
        var_s0 += 1;
    } while (var_s0 != 0xE);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800557E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055948.s")

extern void func_80055948(s32);

void func_80055A34(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_80055948(var_s0);
        var_s0 += 1;
    } while (var_s0 != 4);
}

s32 func_80055A74(s32 arg0) { extern s32 D_800972C0; s32 old = D_800972C0; if (arg0 >= 0 && arg0 < 6) D_800972C0 = arg0; return old; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055A9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055B14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055BA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055BF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055CCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055D44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055DC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055E54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055F6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80056024.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800560F0.s")

s32 func_80056184(void *arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (!((*(u8 *)((u8 *)(arg0) + (6))) & 1)) {
        var_v1 = 0;
    }
    if (!((*(u8 *)((u8 *)(arg0) + (9))) & 1)) {
        var_v1 = 0;
    }
    if (((*(u8 *)((u8 *)(arg0) + (7))) & 0xF) != 0xF) {
        var_v1 = 0;
    }
    if (((*(u8 *)((u8 *)(arg0) + (8))) & 0xF) != 0xF) {
        var_v1 = 0;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800561E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800562B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005633C.s")
#endif
