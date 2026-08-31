#include "global.h"


void fragment43_main(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC00028.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC0011C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC00270.s")
#endif

#ifdef VERSION_US
void func_8AC002D8(s16 arg0, s16 arg1, u8 arg2)
{
  s32 temp_a2;
  s32 temp_v1;
  temp_v1 = 1 << arg0;
  temp_a2 = ((func_800542B0(arg1) & 0xFFFF) & (~temp_v1)) & 0xFF;
  if (arg2 != 0)
  {
    func_800542E4(arg1, (temp_v1 | temp_a2) & 0xFF, temp_a2);
  }
}
#endif

#ifdef VERSION_US
s32 func_8AC00334(s16 arg0, s16 arg1) {
    return (func_800542B0((s32) arg1) >> arg0) & 1 & 0xFF;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC0036C.s")
#endif

#ifdef VERSION_US
extern u8 func_8005453C(s32);
s32 func_8AC004E0(s16 arg0) {
    s32 result = 0;
    switch (arg0) {
    case 0:
        if ((func_8005453C(0) == 1) && (func_8005453C(3) == 1) && (func_8005453C(6) == 1)) {
            result = 1;
        }
        break;
    case 1:
        if ((func_8005453C(1) == 1) && (func_8005453C(4) == 1) && (func_8005453C(7) == 1)) {
            result = 1;
        }
        break;
    case 2:
        if ((func_8005453C(2) == 1) && (func_8005453C(5) == 1) && (func_8005453C(8) == 1)) {
            result = 1;
        }
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern s16 D_8AC08514;
extern s16 D_8AC08516;
extern s16 D_8AC08518;
extern s16 D_8AC0851A;
void func_8AC005D8(void) { gDPPipeSync(D_800D0510++); gDPSetScissor(D_800D0510++, G_SC_NON_INTERLACE, D_8AC08514, D_8AC08516, D_8AC08518, D_8AC0851A); }
#endif

#ifdef VERSION_US
extern s16 D_8AC08514;
extern s16 D_8AC08516;
extern s16 D_8AC08518;
extern s16 D_8AC0851A;
extern void func_8AC005D8();
void func_8AC006B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_8AC08514 = (s16) arg0;
    D_8AC08516 = (s16) arg1;
    D_8AC08518 = (s16) arg2;
    D_8AC0851A = (s16) arg3;
    func_8AC005D8();
}
#endif

#ifdef VERSION_US
void func_8AC006F4(void) {
    D_8AC08514 = 0;
    D_8AC08516 = 0;
    D_8AC08518 = 0x280;
    D_8AC0851A = 0x1E0;
    func_8AC005D8();
}
#endif

#ifdef VERSION_US
void func_8AC00738(void) {
    D_8AC08514 = 0;
    D_8AC08516 = 0;
    D_8AC08518 = 0x280;
    D_8AC0851A = 0x1E0;
    func_8AC005D8();
}
#endif

#ifdef VERSION_US
extern s16 D_8AC08514;
extern s16 D_8AC08516;
extern s16 D_8AC08518;
extern s16 D_8AC0851A;
extern void func_8AC005D8();
void func_8AC0077C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_8AC08514 = (s16) arg0; D_8AC08516 = (s16) arg1; D_8AC08518 = (s16) arg2; D_8AC0851A = (s16) arg3; func_8AC005D8();
}
#endif

#ifdef VERSION_US
extern s16 D_8AC08514; extern s16 D_8AC08516; extern s16 D_8AC08518; extern s16 D_8AC0851A; extern void func_8AC005D8();
void func_8AC007B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
 D_8AC08514 = (s16) arg0; D_8AC08516 = (s16) arg1; D_8AC08518 = (s16) (arg0 + arg2); D_8AC0851A = (s16) (arg1 + arg3); func_8AC005D8();
}
#endif

#ifdef VERSION_US
extern s16 D_8AC0851E;
void func_8AC007FC(void) {
    D_8AC0851E = 1;
}
#endif

#ifdef VERSION_US
extern s16 D_8AC08522;
void func_8AC0080C(s16 arg0) {
    D_8AC08522 = arg0;
}
#endif

#ifdef VERSION_US
void func_8AC00824(void) {
    D_8AC0851E = 0;
}
#endif

#ifdef VERSION_US
extern s16 D_8AC0851C;
void func_8AC00830(void) {
    D_8AC0851C = 2;
}
#endif

#ifdef VERSION_US
extern s16 D_8AC08520;
extern s16 D_8AC0851E;
extern s16 D_8AC0851C;
extern s16 D_8AC08522;
extern void func_8AC00830(void);
s32 func_8AC00840(void) {
    D_8AC08520 = 0;
    if (D_8AC0851E == 1) {
        if (D_8AC0851C > 0) {
            D_8AC0851C -= 1;
        } else {
            D_8AC08520 = -1;
        }
    } else {
        func_8AC00830();
    }
    if (D_8AC08522 > 0) {
        D_8AC08522 -= 1;
        return 1;
    }
    if (D_8AC08520 == 0) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s16 D_8AC08520;

s32 func_8AC008E4(void) {
    if (D_8AC08520 == 0) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC00908.s")
#endif

#ifdef VERSION_US
extern s32 D_8AC08524;
void func_8AC00DE8(void) {
    D_8AC08524 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC00DF4.s")
#endif

#ifdef VERSION_US
extern void *D_8AC08528;
extern void func_8AC00908(s32, s16, s16, s16, s32);
void func_8AC00F04(s32 arg0) {
    s32 var_s0;
    void **var_s1;
    void *temp_v0;
    s32 var_v1;
    if ((D_8AC08524 >= 0) && (D_8AC08524 < 0x64)) {
        var_s0 = 0;
        if (D_8AC08524 > 0) {
            var_s1 = &D_8AC08528;
            do {
                temp_v0 = *var_s1;
                if ((temp_v0 != NULL) && ((*(u16 *)((u8 *)temp_v0 + 2) & 2) != 0)) {
                    var_v1 = *(s16 *)((u8 *)temp_v0 + 0xE);
                    func_8AC00908(arg0, *(s16 *)((u8 *)temp_v0 + 8), *(s16 *)((u8 *)temp_v0 + 0xA), *(s16 *)((u8 *)temp_v0 + 0xC), var_v1);
                }
                var_s0 += 1;
                var_s1++;
            } while (var_s0 < D_8AC08524);
        }
    }
}
#endif

#ifdef VERSION_US
extern u8 func_80063B7C(u8);
s32 func_8AC00FAC(u8 arg0) {
    s32 var_s0;
    u8 temp_v0;
    var_s0 = arg0;
loop_1:
    temp_v0 = func_80063B7C(var_s0);
    if (temp_v0 != 0) {
        var_s0 = temp_v0 & 0xFF;
        goto loop_1;
    }
    return var_s0;
}
#endif

#ifdef VERSION_US
extern s16 D_8AC086B8;
void func_8AC00FEC(void) {
    D_8AC086B8 = 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC00FFC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC01064.s")
#endif

#ifdef VERSION_US
extern u8 *func_8004CA60(u8 *);
extern void func_800459AC(u8 *, u8, u8, u16, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_8AC010D4(u8 *arg0, u16 arg1, u16 arg2) {
    if (arg0 == NULL) {
        return 0;
    }
    func_800459AC(func_8004CA60(arg0), (*(u8 *)((u8 *)(arg0) + (4))), (*(u8 *)((u8 *)(arg0) + (5))), (*(u16 *)((u8 *)(arg0) + (0))), (s32) (*(u16 *)((u8 *)(arg0) + (2))), 1, 0, 0, 0, (s32) arg1, (s32) arg2, 0, 0);
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC01160.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC01354.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC013FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC01574.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC015B0.s")
#endif

#ifdef VERSION_US
extern u8 D_8AC099BC;

void func_8AC01634(void *arg0) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0)));
    (*(s16 *)((u8 *)(temp_v0) + (8))) = (s16) ((*(s16 *)((u8 *)(arg0) + (0x14))) - (*(s16 *)((u8 *)(&D_8AC099BC) + (0))));
    (*(s16 *)((u8 *)(temp_v0) + (0xA))) = (s16) ((*(s16 *)((u8 *)(arg0) + (0x16))) - (*(s16 *)((u8 *)(&D_8AC099BC) + (2))));
}
#endif

#ifdef VERSION_US
void func_8AC01664(void *arg0)
{
  void *temp_v0;
  void *temp_v1;
  temp_v0 = *((void **) (((u8 *) arg0) + 0));
  temp_v1 = *((void **) (((u8 *) arg0) + 0x14));
  *((s16 *) (((u8 *) temp_v0) + 8)) = (s16) (((*((s16 *) (((u8 *) temp_v1) + 0xE))) + (*((s16 *) (((u8 *) arg0) + 0x18)))) - (*((s16 *) (((u8 *) (&D_8AC099BC)) + 0))));
  *((s16 *) (((u8 *) temp_v0) + 0xA)) = (s16) (((*((s16 *) (((u8 *) temp_v1) + 0x10))) + (*((s16 *) (((u8 *) arg0) + 0x1A)))) - (*((s16 *) (((u8 *) (&D_8AC099BC)) + 2))));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC016A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC017B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC0198C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC01B74.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC01D88.s")
#endif

#ifdef VERSION_US
extern void func_8AC0077C(s32, s32, s32, s32);
extern s16 D_8AC099C0;
extern s16 D_8AC099C2;
extern s16 D_8AC099C4;
extern s16 D_8AC099C6;
void func_8AC01F20(void *arg0) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0)));
    if ((*(s16 *)((u8 *)(arg0) + (4))) == 0) {
        (*(s16 *)((u8 *)(arg0) + (4))) = 1;
        (*(u16 *)((u8 *)(temp_v0) + (2))) = (u16) ((*(u16 *)((u8 *)(temp_v0) + (2))) & 0xFFFD);
        return;
    }
    (*(u16 *)((u8 *)(temp_v0) + (2))) = (u16) ((*(u16 *)((u8 *)(temp_v0) + (2))) | 2);
    func_8AC0077C(D_8AC099C0, D_8AC099C2, D_8AC099C4, D_8AC099C6);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC01F8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC0202C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC02564.s")
#endif

#ifdef VERSION_US
extern void _bzero(void *, s32);
extern s32 func_8AC06D8C(s32, s32);
extern void func_8004E308(s32, s32 *, s32 *);
extern u8 func_8AC02564;
void func_8AC02770(s32 arg0, s32 arg1, void *arg2, s16 arg3) {
    s32 v0;

    _bzero(arg2, 0x30);
    v0 = func_8AC06D8C(arg0, arg1);
    (*(s32 *)((u8 *)(arg2) + (0))) = v0;
    (*(s16 *)((u8 *)(arg2) + (0x12))) = arg3;
    func_8004E308(v0, (s32 *) &func_8AC02564, (s32 *) arg2);
}
#endif

#ifdef VERSION_US
extern void _bzero(void *, s32);
extern s32 func_8AC06D8C(s32, s32);
extern void func_8004E308(s32, s32 *, s32 *);
extern u8 func_8AC02564;
void func_8AC027D0(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 v0;

    v0 = func_8AC06D8C(arg0, arg1);
    _bzero(arg2, 0x30);
    (*(s32 *)((u8 *)(arg2) + (0))) = v0;
    func_8004E308(v0, (s32 *) &func_8AC02564, (s32 *) arg2);
    (*(s32 *)((u8 *)(v0) + (0x2C))) = arg3;
    (*(u8 *)((u8 *)(v0) + (0x28))) = 1;
}
#endif

#ifdef VERSION_US
void func_8AC02830(s32 arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4) {
    s32 v0;

    v0 = func_8AC06D8C(arg0, arg1);
    _bzero(arg2, 0x30);
    (*(s32 *)((u8 *)(arg2) + (0))) = v0;
    func_8004E308(v0, (s32 *) &func_8AC02564, (s32 *) arg2);
    (*(s32 *)((u8 *)(v0) + (0x2C))) = arg3;
    (*(s32 *)((u8 *)(v0) + (0x30))) = arg4;
    (*(u8 *)((u8 *)(v0) + (0x28))) = 2;
}
#endif

#ifdef VERSION_US
extern void func_800504BC(s16 *);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800497E4(s32, s32, s32, s32);
extern s32 func_80049668(s32);
extern void func_8004989C(s32);
extern void func_800495F8(s16, s16, u8, s32);
extern void func_800499EC(void);
#pragma pack(1)
struct Fragment43PackedWord { s32 value; };
#pragma pack(0)
struct Fragment43RenderState { u8 pad0[2]; u16 flags; u8 pad4[4]; s16 x; s16 y; u8 padC[0x14]; s32 callback; u16 mode; s8 shade; u8 alpha; struct Fragment43PackedWord color0; struct Fragment43PackedWord color1; };
s32 func_8AC02898(s32 arg0, struct Fragment43RenderState *arg1) {
    s16 sp3E; s16 sp3C; s16 sp3A; s16 sp38; s32 sp34; u8 padding[8]; struct Fragment43PackedWord sp28; struct Fragment43PackedWord sp24;
    sp34 = arg1->callback;
    switch (arg0) {
    case 0:
        arg1->flags &= 0xFFFD;
        break;
    case 1:
        func_800504BC(&sp38);
        sp3E = sp38 + arg1->x;
        sp3C = sp3A + arg1->y;
        sp28 = *(struct Fragment43PackedWord *)((u8 *)arg1 + 0x28);
        sp24 = *(struct Fragment43PackedWord *)((u8 *)arg1 + 0x2C);
        func_800498C4();
        func_800496A4(arg1->mode, 0);
        func_8004972C(((u8 *)&sp28)[0], ((u8 *)&sp28)[1], ((u8 *)&sp28)[2], ((u8 *)&sp28)[3]);
        func_800497E4(((u8 *)&sp24)[0], ((u8 *)&sp24)[1], ((u8 *)&sp24)[2], ((u8 *)&sp24)[3]);
        func_80049668(0);
        func_8004989C(arg1->shade);
        func_800495F8(sp3E, sp3C, arg1->alpha, sp34);
        func_800499EC();
        break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern u8 D_8AC099BC;
extern s32 func_8004C990(s32, s32);
extern void func_800504BC(s16 *);
s32 func_8AC02998(s32 arg0, void *arg1) {
    void *temp_v1;

    temp_v1 = (*(void **)((u8 *)(arg1) + (0x20)));
    switch (arg0) {
        case 0:
            (*(s32 *)((u8 *)(temp_v1) + (0x10))) = func_8004C990((*(u16 *)((u8 *)(arg1) + (0x24))), (*(u16 *)((u8 *)(arg1) + (0x26))));
            break;
        case 1:
            func_800504BC((s16 *)(&D_8AC099BC));
            (*(s16 *)((u8 *)(temp_v1) + (8))) = (*(s16 *)((u8 *)(arg1) + (8))) + (*(s16 *)((u8 *)(&D_8AC099BC) + (0)));
            (*(s16 *)((u8 *)(temp_v1) + (0xA))) = (*(s16 *)((u8 *)(arg1) + (0xA))) + (*(s16 *)((u8 *)(&D_8AC099BC) + (2)));
            break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC02A34.s")
#endif

#ifdef VERSION_US
extern void _bzero(void *, s32);
extern s32 func_8AC06D8C(s32, s32);
extern void func_8004E308(s32, s32 *, s32 *);
extern u8 func_8AC02A34;
extern u8 func_8AC02DA0;
extern u8 func_8AC030EC;
extern s32 func_8AC02998(s32, void *);
extern s32 func_8AC02D04(s32, void *);
extern s32 func_8AC03050(s32, void *);
extern u8 D_8AC099BC;
extern s32 func_8004C990(s32, s32);
extern void func_800504BC(s16 *);
void func_8AC02C80(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 v0;

    _bzero(arg3, 0x2C);
    v0 = func_8AC06D8C(arg0, arg1);
    (*(s32 *)((u8 *)(arg3) + (0))) = v0;
    v0 = func_8AC06D8C(arg0, arg2);
    (*(s32 *)((u8 *)(arg3) + (4))) = v0;
    func_8004E308((*(s32 *)((u8 *)(arg3) + (0))), (s32 *) func_8AC02998, (s32 *) arg3);
    func_8004E308((*(s32 *)((u8 *)(arg3) + (4))), (s32 *) &func_8AC02A34, (s32 *) arg3);
}
#endif

#ifdef VERSION_US
s32 func_8AC02D04(s32 arg0, void *arg1) {
    void *temp_v1;

    temp_v1 = (*(void **)((u8 *)(arg1) + (0x20)));
    switch (arg0) {
        case 0:
            (*(s32 *)((u8 *)(temp_v1) + (0x10))) = func_8004C990((*(u16 *)((u8 *)(arg1) + (0x24))), (*(u16 *)((u8 *)(arg1) + (0x26))));
            break;
        case 1:
            func_800504BC((s16 *)(&D_8AC099BC));
            (*(s16 *)((u8 *)(temp_v1) + (8))) = (*(s16 *)((u8 *)(arg1) + (8))) + (*(s16 *)((u8 *)(&D_8AC099BC) + (0)));
            (*(s16 *)((u8 *)(temp_v1) + (0xA))) = (*(s16 *)((u8 *)(arg1) + (0xA))) + (*(s16 *)((u8 *)(&D_8AC099BC) + (2)));
            break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC02DA0.s")
#endif

#ifdef VERSION_US
void func_8AC02FCC(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 v0;

    _bzero(arg3, 0x2C);
    v0 = func_8AC06D8C(arg0, arg1);
    (*(s32 *)((u8 *)(arg3) + (0))) = v0;
    v0 = func_8AC06D8C(arg0, arg2);
    (*(s32 *)((u8 *)(arg3) + (4))) = v0;
    func_8004E308((*(s32 *)((u8 *)(arg3) + (0))), (s32 *) func_8AC02D04, (s32 *) arg3);
    func_8004E308((*(s32 *)((u8 *)(arg3) + (4))), (s32 *) &func_8AC02DA0, (s32 *) arg3);
}
#endif

#ifdef VERSION_US
s32 func_8AC03050(s32 arg0, void *arg1) {
    void *temp_v1;

    temp_v1 = (*(void **)((u8 *)(arg1) + (0x20)));
    switch (arg0) {
        case 0:
            (*(s32 *)((u8 *)(temp_v1) + (0x10))) = func_8004C990((*(u16 *)((u8 *)(arg1) + (0x24))), (*(u16 *)((u8 *)(arg1) + (0x26))));
            break;
        case 1:
            func_800504BC((s16 *)(&D_8AC099BC));
            (*(s16 *)((u8 *)(temp_v1) + (8))) = (*(s16 *)((u8 *)(arg1) + (8))) + (*(s16 *)((u8 *)(&D_8AC099BC) + (0)));
            (*(s16 *)((u8 *)(temp_v1) + (0xA))) = (*(s16 *)((u8 *)(arg1) + (0xA))) + (*(s16 *)((u8 *)(&D_8AC099BC) + (2)));
            break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC030EC.s")
#endif

#ifdef VERSION_US
void func_8AC03334(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 v0;

    _bzero(arg3, 0x2C);
    v0 = func_8AC06D8C(arg0, arg1);
    (*(s32 *)((u8 *)(arg3) + (0))) = v0;
    v0 = func_8AC06D8C(arg0, arg2);
    (*(s32 *)((u8 *)(arg3) + (4))) = v0;
    func_8004E308((*(s32 *)((u8 *)(arg3) + (0))), (s32 *) func_8AC03050, (s32 *) arg3);
    func_8004E308((*(s32 *)((u8 *)(arg3) + (4))), (s32 *) &func_8AC030EC, (s32 *) arg3);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC033B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC039A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC03AFC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC03C28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC03C74.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC03D24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC03F64.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_8AC07D90[];
typedef struct { u8 r; u8 g; u8 b; u8 a; } Fragment43Color405C;
void func_8AC0405C(s32 arg0, s32 arg1, s32 arg2, Fragment43Color405C color) {
    gSPDisplayList(D_800D0510++, D_8AC07D90);
    gDPSetPrimColor(D_800D0510++, 0, 0, color.r, color.g, color.b, color.a);
    gSPTextureRectangleFlip(D_800D0510++, arg0 << 2, arg1 << 2, (arg0 + 2) << 2, (arg1 + arg2) << 2, 0, 0, 0, 0x400, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC04154.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC043A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC043E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC04418.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC0444C.s")
#endif

#ifdef VERSION_US
extern void func_800504BC(s16 *);
extern void func_8AC0405C(s32 arg0, s32 arg1, s32 arg2, Fragment43Color405C color);
s32 func_8AC044DC(s32 arg0, void *arg1) {
    struct { s32 pad[2]; s16 angles[2]; } scratch;
    if ((arg0 != 0) && (arg0 == 1)) {
        func_800504BC(scratch.angles);
        {
            s16 x;
            Fragment43Color405C color;
            s16 y;
            s16 z;
            x = *(s16 *)((u8 *)arg1 + 8) + scratch.angles[0];
            y = *(s16 *)((u8 *)arg1 + 0xA) + scratch.angles[1];
            z = *(s16 *)((u8 *)arg1 + 0xE);
            color = *(Fragment43Color405C *)((u8 *)arg1 + 0x28);
            func_8AC0405C(x, y, z, color);
        }
    }
    return 0;
}
#endif

#ifdef VERSION_US
typedef struct Fragment43Color { u8 bytes[4]; } Fragment43Color;
extern void func_800504BC(s16 *);
extern void func_8AC04154(s16, s16, s32, s32, Fragment43Color);
s32 func_8AC0456C(s32 arg0, void *arg1) {
    struct { s32 pad[2]; s16 angles[2]; } scratch;
    if ((arg0 != 0) && (arg0 == 1)) {
        func_800504BC(scratch.angles);
        {
            s16 x;
            s16 y;
            Fragment43Color color;
            s16 z;
            s16 w;
            x = *(s16 *)((u8 *)arg1 + 8) + scratch.angles[0];
            y = *(s16 *)((u8 *)arg1 + 0xA) + scratch.angles[1];
            z = *(s16 *)((u8 *)arg1 + 0xC);
            w = *(s16 *)((u8 *)arg1 + 0xE);
            color = *(Fragment43Color *)((u8 *)arg1 + 0x28);
            func_8AC04154(x, y, x + z, y + w, color);
        }
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC04604.s")
#endif

#ifdef VERSION_US
extern void func_8004E308(s32, s32 *, s32 *);
s32 func_8AC06D8C(s32, s32);
extern u8 func_8AC0479C;

void func_8AC04744(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp1C;

    sp1C = func_8AC06D8C(arg1, arg2);
    *arg0 = func_8AC06D8C(arg1, arg3);
    func_8004E308(sp1C, &func_8AC0479C, arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC0479C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC049A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC05E40.s")
#endif

#ifdef VERSION_US
extern void func_8AC05E40(s32, s32, s32);
void func_8AC05ED4(s32 arg0, s32 arg1, s32 arg2) {
    func_8AC05E40(arg0, arg1, arg2);
    *(s16 *)((u8 *)arg2 + 0x70) = 1;
}
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
void func_8AC05F00(void *arg0) {
    Gfx *temp_v1;
    if (*(s16 *)((u8 *)arg0 + 0x70) != 0) {
        temp_v1 = D_800D0510++;
        temp_v1->words.w0 = 0xDE000000;
        temp_v1->words.w1 = *(s32 *)((u8 *)arg0 + 0x3C);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC05F38.s")
#endif

#ifdef VERSION_US
typedef struct Fragment43Motion602C { u8 pad00[0x40]; f32 unk40; f32 unk44; f32 unk48; f32 unk4C; f32 unk50; f32 unk54; s16 unk58; s16 unk5A; } Fragment43Motion602C;
extern f32 D_80088E50[];
extern f32 D_8AC08178;
extern void func_8AC05F38(Fragment43Motion602C *);
void func_8AC0602C(Fragment43Motion602C *arg0, u16 arg1, s32 arg2) {
    f32 *temp_v0;
    f32 temp_fv0;

    if (arg2 != 0) {
        arg1 <<= 12;
        temp_v0 = &D_80088E50[arg1 >> 4];
        temp_fv0 = D_8AC08178;
        if (arg0) {
        }
        arg0->unk40 = 1.0f - (*temp_v0 * temp_fv0);
        arg0->unk44 = (*temp_v0 * temp_fv0) + 1.0f;
    } else {
        func_8AC05F38(arg0);
    }
    arg0->unk4C = arg0->unk54 + ((f32)arg0->unk5A * 0.5f * (1.0f - arg0->unk44));
}
#endif

#ifdef VERSION_US
extern f32 D_8AC0817C;
extern void func_8AC05F38(Fragment43Motion602C *);
void func_8AC060E4(Fragment43Motion602C *arg0, u16 arg1, s32 arg2) {
    f32 *temp_v0;
    f32 temp_fv0;

    if (arg2 != 0) {
        arg1 <<= 12;
        temp_v0 = &D_80088E50[arg1 >> 4];
        temp_fv0 = D_8AC0817C;
        if (arg0) {
        }
        arg0->unk40 = 1.0f - (*temp_v0 * temp_fv0);
        arg0->unk44 = (*temp_v0 * temp_fv0) + 1.0f;
    } else {
        func_8AC05F38(arg0);
    }
    arg0->unk4C = arg0->unk54 - ((f32)arg0->unk5A * 0.5f * (1.0f - arg0->unk44));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC0619C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC06220.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC062A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC06328.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC063AC.s")
#endif

#ifdef VERSION_US
void func_8AC06400(void *arg0, void *arg1) {
    (*(f32 *)((u8 *)(arg0) + (0x40))) = 1.0f;
    (*(f32 *)((u8 *)(arg0) + (0x44))) = 1.0f;
    (*(f32 *)((u8 *)(arg0) + (0x48))) = (f32)(*(s16 *)((u8 *)(arg1) + (0xC))) * 0.5f + (f32)(*(s16 *)((u8 *)(arg1) + (0x8)));
    (*(f32 *)((u8 *)(arg0) + (0x4C))) = (f32)(*(s16 *)((u8 *)(arg1) + (0xE))) * 0.5f + (f32)(*(s16 *)((u8 *)(arg1) + (0xA)));
}
#endif

#ifdef VERSION_US
s32 func_8AC06464(s16 arg0, void *arg1) {
    if (arg0 < (*(s16 *)((u8 *)(arg1) + (2)))) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_8AC06490(s16 arg0, void *arg1)
{
  if (((*((s16 *) (((u8 *) arg1) + 2))) + (*((s16 *) (((u8 *) arg1) + 0xA)))) < ((0, arg0)))
  {
    return 1;
  }
  return 0;
}
#endif

#ifdef VERSION_US
s32 func_8AC064C4(s16 arg0, s16 *arg1) {
    if (arg0 < *arg1) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_8AC064F0(s16 arg0, s16 *arg1) {
    if (*arg1 < arg0) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
void func_8AC0651C(void *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    _bzero(arg0, 0xE);
    (*(s16 *)((u8 *)(arg0) + (6))) = arg1;
    (*(s16 *)((u8 *)(arg0) + (8))) = arg2;
    (*(s16 *)((u8 *)(arg0) + (0xA))) = arg3;
    (*(s16 *)((u8 *)(arg0) + (0xC))) = arg4;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC06570.s")
#endif

#ifdef VERSION_US
s32 func_8AC0660C(s16 arg0) {
    if (arg0 > 0) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_8AC06630(s16 arg0, void *arg1) {
    if (arg0 < (*(s16 *)((u8 *)(arg1) + (6)))) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC0665C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC0672C.s")
#endif

#ifdef VERSION_US
s32 func_8AC06800(void *arg0, s16 arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (((*(s16 *)((u8 *)(arg0) + (0xA))) < (*(s16 *)((u8 *)(arg0) + (6)))) && (arg1 > 0)) {
        var_v1 = 1;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
s32 func_8AC06834(void *arg0, s16 arg1)
{
  s16 temp_v0;
  s32 var_v1;
 do { temp_v0 = *((s16 *) (((u8 *) arg0) + 6)); var_v1 = 0; if (((*((s16 *) (((u8 *) arg0) + 0xA))) < temp_v0) && (arg1 < temp_v0)) { var_v1 = 1; } } while (0);
  return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC0686C.s")
#endif

#ifdef VERSION_US
void func_8AC0695C(void *arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s32 arg8, s32 arg9, s32 arg10) {
    (*(s16 *)((u8 *)(arg0) + (0x12))) = 7;
    (*(s32 *)((u8 *)(arg0) + (0x14))) = arg1;
    (*(s16 *)((u8 *)(arg0) + (0x18))) = arg2;
    (*(s16 *)((u8 *)(arg0) + (0x1A))) = arg3;
    (*(s16 *)((u8 *)(arg0) + (0x1C))) = arg4;
    (*(s16 *)((u8 *)(arg0) + (0x1E))) = arg5;
    (*(s16 *)((u8 *)(arg0) + (0x20))) = arg6;
    (*(s16 *)((u8 *)(arg0) + (0x22))) = arg7;
    (*(s32 *)((u8 *)(arg0) + (0x24))) = arg8;
    (*(s32 *)((u8 *)(arg0) + (0x28))) = arg9;
    (*(s32 *)((u8 *)(arg0) + (0x2C))) = arg10;
}
#endif

#ifdef VERSION_US
void func_8AC069C4(void *arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s32 arg8, s32 arg9, s32 arg10) {
    (*(s16 *)((u8 *)(arg0) + (0x12))) = 4;
    (*(s32 *)((u8 *)(arg0) + (0x14))) = arg1;
    (*(s16 *)((u8 *)(arg0) + (0x18))) = arg2;
    (*(s16 *)((u8 *)(arg0) + (0x1A))) = arg3;
    (*(s16 *)((u8 *)(arg0) + (0x1C))) = arg4;
    (*(s16 *)((u8 *)(arg0) + (0x1E))) = arg5;
    (*(s16 *)((u8 *)(arg0) + (0x20))) = arg6;
    (*(s16 *)((u8 *)(arg0) + (0x22))) = arg7;
    (*(s32 *)((u8 *)(arg0) + (0x24))) = arg8;
    (*(s32 *)((u8 *)(arg0) + (0x28))) = arg9;
    (*(s32 *)((u8 *)(arg0) + (0x2C))) = arg10;
}
#endif

#ifdef VERSION_US
void func_8AC06A2C(void *arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s32 arg8, s32 arg9, s32 arg10) {
    (*(s16 *)((u8 *)(arg0) + (0x12))) = 8;
    (*(s32 *)((u8 *)(arg0) + (0x14))) = arg1;
    (*(s16 *)((u8 *)(arg0) + (0x18))) = arg2;
    (*(s16 *)((u8 *)(arg0) + (0x1A))) = arg3;
    (*(s16 *)((u8 *)(arg0) + (0x1C))) = arg4;
    (*(s16 *)((u8 *)(arg0) + (0x1E))) = arg5;
    (*(s16 *)((u8 *)(arg0) + (0x20))) = arg6;
    (*(s16 *)((u8 *)(arg0) + (0x22))) = arg7;
    (*(s32 *)((u8 *)(arg0) + (0x24))) = arg8;
    (*(s32 *)((u8 *)(arg0) + (0x28))) = arg9;
    (*(s32 *)((u8 *)(arg0) + (0x2C))) = arg10;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC06A94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC06C10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC06CC8.s")
#endif

#ifdef VERSION_US
void func_8AC06D70(void *arg0, s32 arg1, s32 arg2, u16 arg3) {
    u8 *ptr = (u8 *)arg0;
    *(s16 *)(ptr + 0x12) = 0xA;
    *(s32 *)(ptr + 0x14) = arg1;
    *(s32 *)(ptr + 0x18) = arg2;
    *(s16 *)(ptr + 0x20) = arg3;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC06D8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC06DC8.s")
#endif

#ifdef VERSION_US
extern void func_8AC06DC8(void *arg0, void *arg1);
extern s16 D_8AC08790;
void func_8AC06E98(void *arg0) {
    D_8AC08790 = 0;
    func_8AC06DC8(arg0, arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1E5A10/func_8AC06EC0.s")
#endif

#ifdef VERSION_US
extern void func_8AC06EC0(void);
void func_8AC06F28(void) {
    func_8AC06EC0();
}
#endif

#ifdef VERSION_US
void func_8AC06F48(s32 arg0, s32 arg1) {

}
#endif
