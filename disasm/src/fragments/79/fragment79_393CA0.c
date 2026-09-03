#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84124410.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84124514.s")
#endif

#ifdef VERSION_US
extern u8 *D_84195200[];
extern void func_84134CBC(u8, u8);
void func_84124594(u8 arg0) {
    if (D_84195200[arg0][0x24] & 7) {
        func_84134CBC(arg0, 4);
    } else if (D_84195200[arg0][0x24] & 0x20) {
        func_84134CBC(arg0, 2);
    } else {
        func_84134CBC(arg0, 3);
    }
}
#endif

#ifdef VERSION_US
extern u8 D_841951E6;
extern void func_84134F78(u8, u8);
extern void func_84134CBC(u8 arg0, u8 arg1);
extern void func_84134DD8(u8 arg0);
void func_84124604(u8 arg0, u8 arg1) {
    func_84134DD8(arg1);
    if (D_84195200[arg0][0x24] & 7) {
        func_84134CBC(arg0, 0xB);
    } else if (D_84195200[arg0][0x24] & 0x20) {
        func_84134CBC(arg0, 0xD);
    } else {
        func_84134CBC(arg0, 0xA);
    }
    if (D_841951E6 != 0) {
        func_84134F78(arg0, 1);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841246AC.s")
#endif

#ifdef VERSION_US
extern void func_84134DD8(u8);
void func_84124768(u8 arg0) {
    func_84134DD8(0xC2);
    func_84134CBC(arg0, 0x55);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84124798.s")
#endif

#ifdef VERSION_US
extern u8 D_841951E4, D_841951E5;
extern void func_84136678(u8, s32);
extern void func_84135B00(u8);
void func_841248DC(u8 arg0) {
    if (D_841951E4 != 2) {
        if (D_841951E5 >= 0xB) {
            func_84136678(arg0, -1);
            func_84135B00(0x25);
        } else if (D_841951E5 < 0xA) {
            func_84136678(arg0, -1);
            func_84135B00(0x44);
        }
    }
}
#endif

#ifdef VERSION_US
extern u8 D_841951E7;
extern u8 D_841951C6;
extern s32 func_800635E0(u8);
extern void func_8004C54C(u8, s32);
void func_84124954(u8 arg0) {
    switch (D_841951E7) {
    case 1:
        func_84136678(arg0, -1);
        func_84135B00(0x62);
        break;
    case 2:
        func_84136678(arg0, -1);
        func_8004C54C(0x2A, func_800635E0(D_841951C6));
        func_84135B00(0x86);
        break;
    }
}
#endif

#ifdef VERSION_US
extern u8 D_841951E6;
void func_841249D8(u8 arg0) {
    if (D_841951E6 == 0) return;
    func_84136678(arg0, -1);
    func_84135B00(0x7D);
}
#endif

#ifdef VERSION_US
extern u8 D_841951E6, D_841951BF;
extern void func_84136D40(u8);
extern void func_84136CA8(void);
void func_84124A14(u8 arg0) {
    if (D_841951E6 == 2) {
        func_84136678(arg0, -1);
        func_84135B00(0x7B);
        func_84134DD8(D_841951BF);
        func_84134CBC(arg0, 0x27);
        func_84136D40(3);
        func_84136CA8();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84124A7C.s")
#endif

#ifdef VERSION_US
void func_84124BA0(u8 arg0) {
    if (D_84195200[arg0][0x24] & 7) {
        func_84134CBC(arg0, 8);
    } else if (D_84195200[arg0][0x24] & 0x20) {
        func_84134CBC(arg0, 9);
    } else {
        func_84134CBC(arg0, 7);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84124C10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84124CC4.s")
#endif

#ifdef VERSION_US
extern void func_84134E30(s32); extern void func_84134E00(u8);
extern void func_84124604(u8 arg0, u8 arg1);
extern void func_84134CBC(u8 arg0, u8 arg1);
extern u8 D_841951BC;
extern u8 D_841951BF;
void func_84124DEC(u8 arg0) {
    if (arg0 == D_841951BC) {
        func_84134CBC(arg0, 0x41);
    } else {
        func_84124604(arg0, D_841951BF);
        func_84134E00(8);
        func_84134E30(5);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84124E44.s")
#endif

#ifdef VERSION_US
s32 func_84124EFC(u8 arg0, u8 *arg1) {
    while (*arg1 != 0xFF) {
        if (*arg1 == arg0) {
            return 1;
        }
        arg1++;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84124F40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84125080.s")
#endif

#ifdef VERSION_US
extern u8 D_84195188[];
u8 func_84125158(u8 arg0) {
    return D_84195188[arg0];
}
#endif

#ifdef VERSION_US
extern u8 D_84195180;
u8 func_84125170(void) {
    return D_84195180;
}
#endif

#ifdef VERSION_US
extern s32 func_80063660(u8);
extern s32 func_84124EFC(u8, u8 *);
extern u8 D_8418549C[];
void func_8412517C(u8 arg0) {
    func_84124EFC((u8)func_80063660(arg0), D_8418549C);
}
#endif

#ifdef VERSION_US
u8 func_841251B0(u8 arg0) {
    return (arg0 << 4) | (arg0 >> 4);
}
#endif

#ifdef VERSION_US
extern u8 func_80062D98(u8);
s32 func_841251CC(u8 arg0) {
    if (func_80062D98(arg0) < 0x14) return 0;
    return 1;
}
#endif

#ifdef VERSION_US
extern u8 D_841951D1, D_841951BC, D_841951BD;
extern u8 *D_84195208[];
s32 func_84125200(u8 arg0) {
    if (D_841951D1 == 0) return 1;
    if (arg0 == 0) {
        if (D_84195208[D_841951BD][0x1F] < D_84195208[D_841951BC][0x1E]) return 1;
        return 0;
    }
    if (D_84195208[D_841951BD][0x22] < D_84195208[D_841951BC][0x21]) return 1;
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841252D0.s")
#endif

#ifdef VERSION_US
extern u8 D_841951BC;
extern s32 D_841951B8;
void func_841253F4(void) {
    D_84195208[D_841951BC][0x29] = 1;
    D_841951B8 = -1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84125424.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84125484.s")
#endif

#ifdef VERSION_US
extern u8 D_84195198[];
void func_841254E0(void) {
    D_84195198[D_841951B8 + 1] = 0xFF;
    D_84195198[D_841951B8 + 2] = 0xFF;
    D_84195198[D_841951B8 + 3] = 0xFF;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84125508.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841255AC.s")
#endif

#ifdef VERSION_US
extern void func_84125508(u8 *, u16, u8);
void func_84125650(u8 *arg0, u8 arg1) {
    u16 flags;
    s32 i;

    i = 0;
    do {
        func_84125508((u8 *)((u32)arg0 + (i << 1) + 0x3C), *(u16 *)((u32)arg0 + (i << 1) + 0x32), *(u8 *)((u32)arg0 + i + 0x1E));
        i = (i + 1) & 0xFF;
    } while (i < 5);
    flags = *(u16 *)((u8 *)&arg1 - 1);
    if (!arg0) {
    }
    if (flags & 0x40) {
        *(u16 *)((u32)arg0 + 0x40) >>= 2;
    }
    if (flags & 0x10) {
        *(u16 *)((u32)arg0 + 0x3C) >>= 1;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841256E0.s")
#endif

#ifdef VERSION_US
extern u8 *D_84195200[];
extern u8 *D_84195208[];
extern void *D_841951F8[];
extern void func_84125650(u8 *, u8);
extern void func_841334D8(u8);
extern void func_841339D0(u8);
void func_84125734(u8 arg0) {
    func_84125650(D_84195208[arg0], D_84195200[arg0][0x24]);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84125778.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841259D4.s")
#endif

#ifdef VERSION_US
extern u8 D_841951C3;
s32 func_84125AB8(u8 arg0) {
    if ((s32) D_841951C3 < 0x12) {
        return 0;
    }
    if ((s32) D_841951C3 < 0x19) {
        return ((*(u8 *)((u8 *)(D_84195208[arg0]) + (0x10))) & 2) != 0;
    }
    if ((s32) D_841951C3 < 0x3A) {
        return 0;
    }
    if ((s32) D_841951C3 < 0x41) {
        return ((*(u8 *)((u8 *)(D_84195208[arg0]) + (0x10))) & 2) != 0;
    }
    if ((s32) D_841951C3 < 0x44) {
        return 0;
    }
    if ((s32) D_841951C3 < 0x4B) {
        return ((*(u8 *)((u8 *)(D_84195208[arg0]) + (0x10))) & 2) != 0;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84125B88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84125C68.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84125CF8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84125EC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84126064.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841260D4.s")
#endif

#ifdef VERSION_US
extern void func_84126200(u8); extern s32 func_84126260(u8); extern s32 func_84126064(u8); extern void func_841260D4(u8, u8, u8); extern s32 func_84129C8C(u8);
extern void * D_841951F8[];
void func_84126200(u8 arg0) {
    u8 *ptr = D_841951F8[arg0];

    if (ptr[0xA] < ptr[3]) {
        func_841260D4(arg0, 0, ptr[3]);
    } else {
        func_841260D4(arg0, ptr[3], ptr[8]);
    }
}
#endif

#ifdef VERSION_US
extern void * D_841951F8[];
s32 func_84126260(u8 arg0) {
    u8 *ptr = D_841951F8[arg0];

    if (ptr[0xA] < ptr[3]) {
        func_841260D4(arg0, ptr[3], ptr[8]);
    } else {
        func_841260D4(arg0, 0, ptr[3]);
    }
}
#endif

#ifdef VERSION_US
extern void * D_841951F8[];
extern s32 func_84126260(u8);
extern s32 func_84126064(u8);
s32 func_841262C4(u8 arg0) {
    if (((u8 *) D_841951F8[arg0])[0x12] != 0) {
        return 0 < func_84126260(arg0);
    } else {
        return func_84126064(arg0) >= 2;
    }
}
#endif

#ifdef VERSION_US
extern void func_84134E30(s32); extern u8 D_84199D81; extern u8 D_8418548C[];
extern s32 func_84126064(u8);
extern void func_84126200(u8 arg0);
extern void * D_841951F8[];
s32 func_84126320(u8 arg0) {
    if (((u8 *) D_841951F8[arg0])[0x12] != 0) {
        func_84126200(arg0);
    } else {
        return func_84126064(arg0);
    }
}
#endif

#ifdef VERSION_US
extern u8 D_841951BE;
s32 func_84126374(void) {
    return D_841951BC == D_841951BE;
}
#endif

#ifdef VERSION_US
s32 func_84126390(u8 arg0, u8 arg1)
{
  s32 result = arg1 == D_84195208[arg0][1];
  u8 *ptr = D_84195208[arg0];
  if (result == 0)
  {
    result = arg1 == ptr[2];
  }
  return result;
}
#endif

#ifdef VERSION_US
extern u8 * D_84195208[];
s32 func_841263D8(u8 arg0, u8 arg1) {
    u8 *ptr;
    s32 i;
    u8 value;
    arg1 &= 0xFF;
    ptr = D_84195208[arg0];
    i = 0;
    while (1) {
        value = *(u8 *)((unsigned long)ptr + (unsigned long)i + 5);
        if (value != 0) {
            if (value == arg1) {
                return (i + 1) & 0xFF;
            }
            i = (i + 1) & 0xFF;
            if (i < 4) {
                continue;
            }
        }
        return 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84126440.s")
#endif

#ifdef VERSION_US
extern void func_84126440(u8);
void BattleAnim_StopOwnerCategoryParticles(u8 arg0) {
    func_84126440(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841264F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84126568.s")
#endif

#ifdef VERSION_US
extern u8 D_841951D6;
extern s32 D_841951C8;
void func_841265D4(void) {
    D_841951D6 = 1;
    D_841951C8 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841265EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841266C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412676C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841267B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84126804.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84126850.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841268A0.s")
#endif

#ifdef VERSION_US
void func_8412693C(u8 arg0) {
    D_84195208[arg0][0x1E] = 7;
    D_84195208[arg0][0x1F] = 7;
    D_84195208[arg0][0x20] = 7;
    D_84195208[arg0][0x21] = 7;
    D_84195208[arg0][0x22] = 7;
    D_84195208[arg0][0x23] = 7;
    D_84195208[arg0][0x24] = 7;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84126994.s")
#endif

#ifdef VERSION_US
void func_84126A64(void) {
    D_84195208[0][0xD] &= 0xFF7F;
    D_84195208[1][0xD] &= 0xFF7F;
}
#endif

#ifdef VERSION_US
extern void func_841246AC(s32, u8);
extern u8 D_841951BF;
extern u8 *D_84195208[];
extern void func_84136678(u8, s32);
extern void func_84135B00(u8);
extern void func_84136CA8(void);
void func_84126A90(u8 arg0, u8 arg1, u8 arg2) {
    func_84136678(arg0, -1);
    if ((arg2 != 0) && (D_84195208[arg1][0xD] & 4)) {
        func_84135B00(0xA5);
    } else {
        func_84135B00(0xA4);
    }
    func_841246AC(arg1, D_841951BF);
    func_84136CA8();
}
#endif

#ifdef VERSION_US
void func_84126B1C(u8 arg0, u8 arg1, u8 arg2) {
    func_84136678(arg0, -1);
    if ((arg2 != 0) && (D_84195208[arg1][0xD] & 4)) {
        func_84135B00(0x56);
    } else {
        func_84135B00(0x55);
    }
    func_841246AC(arg1, D_841951BF);
    func_84136CA8();
}
#endif

#ifdef VERSION_US
extern void func_841246AC(s32, u8);
void func_84126BA8(u8 arg0) {
    func_84136678(arg0, -1);
    func_84135B00(0xB5U);
    func_841246AC((1 - arg0) & 0xFF, D_841951BF);
    func_84136CA8();
}
#endif

#ifdef VERSION_US
void func_84126BFC(u8 arg0) {
    func_84136678(arg0, -1);
    func_84135B00(0xB5U);
    func_84124594(arg0);
    func_84136CA8();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84126C3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84126CD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84126E88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84126EDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84126F2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84126FA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841270D8.s")
#endif

#ifdef VERSION_US
extern void *D_841951F8[];
s32 func_84127140(u8 a) {
    u8 *p;
    u8 x;
    u8 *new_var;

    p = D_841951F8[a];
    x = p[0x49A];
    new_var = p;
    if (p[0x11] != 0) {
        return 0;
    }
    if ((x > 0) && (x < 0xFF)) {
        return 1;
    }
    return new_var[0x49A] * 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84127194.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841278E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84127B00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84127C88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84127DB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841280D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84128204.s")
#endif

#ifdef VERSION_US
extern u8 D_841951C3; extern u8 D_841951D2;
void func_84128298(void) { if (D_841951C3 != 0x2D) D_841951C8 = 0; D_841951D2 = 1; }
#endif

#ifdef VERSION_US
s32 func_841282C0(void)
{
  u8 *temp_v0;
  u8 temp_v1;
  temp_v0 = D_84195208[D_841951BD];
  ;
  if ((*((u8 *) (((u8 *) temp_v0) + 0x11))) & 0x20)
  {
    *((u8 *) (((u8 *) temp_v0) + 0x11)) = (u8) ((*((u8 *) (((u8 *) temp_v0) + 0x11))) & 0xFFDF);
    if (((*((u8 *) (((u8 *) D_84195208[D_841951BD]) + 0xF))) & 0x40) && (((D_841951BF == 0x59) || (D_841951BF == 0x5A)) || (D_841951BF == 0xDE)))
    {
      return 0;
    }
    return 1;
  }
  return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84128354.s")
#endif

#ifdef VERSION_US
extern void *D_841951F0;

s32 func_841283FC(void) {
    if ((D_841951BF == 0x57) && ((*(u8 *)((u8 *)(D_841951F0) + (0x9C4))) == 1)) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84128438.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841284A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84128664.s")
#endif

#ifdef VERSION_US
extern u8 D_841951BC;
extern u8 D_841951BD;
extern s32 D_841951C8;
extern u8 *D_84195208[];
extern void func_84125424(s32);
void func_841288DC(void) {
    u8 *temp_v0;

    temp_v0 = D_84195208[D_841951BD];
    if (!((*(u8 *)((u8 *)temp_v0 + 0x10)) & 0x10)) {
        *(s32 *)((u8 *)temp_v0 + 0x4C) += D_841951C8;
        temp_v0 = D_84195208[D_841951BD];
        if ((u32)(*(s32 *)((u8 *)temp_v0 + 0x4C)) >= 0x10000U) {
            *(s32 *)((u8 *)temp_v0 + 0x4C) = 0xFFFF;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84128954.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84128B04.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84128B30.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84128B4C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84128CB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84128D48.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84128EC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84129180.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841292C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84129374.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412955C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84129900.s")
#endif

#ifdef VERSION_US
extern u8 D_841951BC;
extern u8 *D_84195200[];
extern u8 *D_84195208[];
extern void func_84136A9C(u8, s16, s16, u8);
extern void func_84136B9C(u8, s16, u16);
void func_84129A80(void) {
    func_84136A9C(D_841951BC, -1, (s16)(-*(u16 *)((u8 *)(D_84195200[D_841951BC]) + 0x26)), 3);
    func_84136B9C(D_841951BC, -1, 0);
    *(u8 *)((u8 *)(D_84195200[D_841951BC]) + 0x24) = 0;
    *(u16 *)((u8 *)(D_84195200[D_841951BC]) + 0x26) = 0;
    D_84195208[D_841951BC][0x10] &= 0xFF7F;
    D_84195208[D_841951BC][0x11] &= 0xFFBF;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84129B60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84129C8C.s")
#endif

#ifdef VERSION_US
s32 func_84129D3C(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (func_84129C8C((u8) i) != 0) {
            return 1;
        }
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84129D8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84129E84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412A028.s")
#endif

#ifdef VERSION_US
extern s32 func_84125080();
extern void func_841254E0(void);
void BattleAnim_Table_84185F10_003(void) {
    u8 *temp_v0;

    *(u8 *)((u8 *)D_84195208[D_841951BC] + 0xF) |= 1;
    *(s32 *)((u8 *)D_84195208[D_841951BC] + 0x4C) = 0;
    *(u8 *)((u8 *)D_84195208[D_841951BC] + 0x12) = (func_84125080() & 1) + 2;
    func_841254E0();
}
#endif

#ifdef VERSION_US
s32 func_841262C4(u8);

s32 func_8412A200(u8 arg0) {
    s32 var_a0;

    var_a0 = func_84126374() == 0;
    if (var_a0 != 0) {
        var_a0 = func_841262C4(arg0) != 0;
    }
    return var_a0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412A23C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412A300.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412A454.s")
#endif

#ifdef VERSION_US
extern u8 D_841951D3;
extern s32 func_84126374(void);
void BattleAnim_Table_84185F10_006(void) {
    if (!(((u8 *)D_84195208[D_841951BD])[0x10] & 0x10) &&
        !(((u8 *)D_84195200[D_841951BD])[0x24] & 0x27) &&
        (func_84126374() != 0) &&
        (D_841951D3 == 0)) {
        ((u8 *)D_84195208[D_841951BD])[0xF] |= 8;
        ((u8 *)D_84195208[D_841951BD])[0x10] &= 0xFFDF;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412A804.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412A934.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412A9F4.s")
#endif

#ifdef VERSION_US
extern void func_84124594(u8 arg0);
extern void func_84135B00(u8);
extern void func_84136678(u8, s32);
extern void func_84136CA8(void);
void BattleAnim_Table_84185F10_010(void) {
    u8 *ptr = D_84195208[D_841951BC];
    if (ptr[0x10] & 4) {
        func_84126BFC(D_841951BC);
        return;
    }
    ptr[0x10] |= 4;
    func_84136678(D_841951BC, -1);
    func_84135B00(0x58);
    func_84124594(D_841951BC);
    func_84136CA8();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412AAE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412ADF8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412AFE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412B1D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412B51C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412B65C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412B958.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412BB9C.s")
#endif

#ifdef VERSION_US
extern u8 D_841951BC; extern u8 *D_84195208[]; void BattleAnim_Table_84185F10_019(void) { D_84195208[D_841951BC][0x10] |= 0x20; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412BD3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412BDF0.s")
#endif

#ifdef VERSION_US
extern u8 D_8418548C[]; extern s32 func_84124EFC(u8, u8 *);
extern u8 D_841951BC;
extern u8 * D_84195208[];
s32 func_8412BF4C(u8 arg0) {
    u8 i;

    if (arg0 == 0 || arg0 >= 0xFC) {
        return 1;
    }
    if (func_84124EFC(arg0, D_8418548C) != 0) {
        return 1;
    }
    for (i = 0; i < 4; i++) {
        if (D_84195208[D_841951BC][((unsigned long) i) + 5] == arg0) {
            return 1;
        }
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412BFEC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412C0AC.s")
#endif

#ifdef VERSION_US
void BattleAnim_Table_84185F10_023(void) {
    func_84136678(D_841951BC, -1);
    func_84135B00(0x87U);
    func_84134CBC(D_841951BC, 0U);
    func_84134DD8(D_841951BF);
    func_84136CA8();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412C294.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412C47C.s")
#endif

#ifdef VERSION_US
extern u8 D_841951BC;
extern u8 *D_84195208[];
extern void func_84125424(s32);
void BattleAnim_Table_84185F10_026(void) {
    u8 *rec = D_84195208[D_841951BC];
    if (rec[0xF] & 0x10) {
        rec[0xF] &= 0xFF8F;
        func_84125424(0x31);
    }
}
#endif

#ifdef VERSION_US
extern s32 func_84125080();
void BattleAnim_Table_84185F10_027(void) {
    u8 *temp_v0;
    temp_v0 = D_84195208[D_841951BD];
    if ((temp_v0[0x1B] <= 0) && !(temp_v0[0x10] & 0x10)) {
        *(u8 *)((u8 *)D_84195208[D_841951BD] + 0x1B) =
            (func_84125080() & 3) + 3;
        *(u8 *)((u8 *)D_84195208[D_841951BD] + 0x1C) = D_841951BF;
    }
}
#endif

#ifdef VERSION_US
s32 func_84125080();
void BattleAnim_Table_84185F10_028(void) {
    u8 *temp_v0;

    if (!((*(u8 *)((u8 *)(D_84195200[D_841951BC]) + (0x24))) & 7)) {
        temp_v0 = D_84195208[D_841951BC];
        (*(u8 *)((u8 *)(temp_v0) + (0xF))) = (u8) ((*(u8 *)((u8 *)(temp_v0) + (0xF))) | 2);
        (*(s8 *)((u8 *)(D_84195208[D_841951BC]) + (0x12))) = (s8) ((func_84125080() & 1) + 1);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412C870.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412C95C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412CB00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412CBE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412CDA4.s")
#endif

#ifdef VERSION_US
extern void func_84126C3C(u8);
void BattleAnim_Table_84185F10_034(void) {
    if (!((*(u8 *)((u8 *)(D_84195200[D_841951BC]) + (0x24))) & 7)) {
        D_841951C8 = 0;
        D_841951D2 = 1;
        func_84126C3C(D_841951BC);
        func_841254E0();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412CFE4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412D06C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412D20C.s")
#endif

#ifdef VERSION_US
void BattleAnim_Table_84185F10_037(void) {
    (*(s8 *)((u8 *)(D_84195208[D_841951BC]) + (0x26))) = 0;
    (*(s8 *)((u8 *)(D_84195208[D_841951BC]) + (0x27))) = 0;
    func_84136678(D_841951BC, -1);
    func_84135B00(0x87U);
    func_84134CBC(D_841951BC, 0U);
    func_84134DD8(D_841951BF);
    func_84136CA8();
}
#endif

#ifdef VERSION_US
void BattleAnim_Table_84185F10_038(void) {
    u8 *temp_v0;

    temp_v0 = D_84195200[D_841951BD];
    if ((*(u8 *)((u8 *)(temp_v0) + (0x24))) & 0x20) {
        (*(u8 *)((u8 *)(temp_v0) + (0x24))) = 0U;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412D390.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412D4A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412D53C.s")
#endif

#ifdef VERSION_US
s32 func_84126320(u8);
extern void func_84135B40(s32);
extern void func_841366C4(u8, s32);
void BattleAnim_Table_84185F10_040(void) {
    u8 *temp_v0;

    if (func_84126320(D_841951BC) >= 2) {
        temp_v0 = D_84195208[D_841951BC];
        (*(u8 *)((u8 *)(temp_v0) + (0x11))) = (u8) ((*(u8 *)((u8 *)(temp_v0) + (0x11))) | 0x40);
        func_841366C4(D_841951BC, -1);
        func_84135B40(0x82);
        return;
    }
    func_84126BA8(D_841951BC);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412D6C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412D8C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412D950.s")
#endif

#ifdef VERSION_US
extern u8 D_841951C5;
extern u8 func_80063690(u8);
extern s32 func_80063660(u8);
extern s32 func_84125080();
void BattleAnim_Table_84185F10_044(void) {
    u8 limit;
    if ((D_841951D2 == 0) &&
        (func_80063660(D_841951C5) == 0x4B) &&
        !(((u8 *)D_84195208[D_841951BD])[0x10] & 0x10)) {
        limit = func_80063690(D_841951C5);
        if (func_84125080() < limit) {
            ((u8 *)D_84195208[D_841951BD])[0x10] &= 0xFFDF;
            ((u8 *)D_84195208[D_841951BD])[0xF] |= 8;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412DBC0.s")
#endif

#ifdef VERSION_US
extern u8 D_841951D7;
void BattleAnim_Table_84185F10_046(void) {
    D_841951D7 += 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412DC20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412DD0C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412DDC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412DE98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412E220.s")
#endif

#ifdef VERSION_US
void BattleAnim_Table_84185FDC_001(void) {
    u8 *temp_v0;

    if (func_8412E220() != 0) {
        temp_v0 = D_84195208[D_841951BC];
        (*(u8 *)((u8 *)(temp_v0) + (0xD))) = (u8) ((*(u8 *)((u8 *)(temp_v0) + (0xD))) | 4);
        func_84136678(D_841951BC, -1);
        func_84135B00(0x74U);
        func_84134CBC(D_841951BC, 0U);
        func_84134DD8(D_841951BF);
        func_84136CA8();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412E38C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412E420.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412E510.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412E680.s")
#endif

#ifdef VERSION_US
void BattleAnim_Table_84185FDC_006(void) {
    u8 *temp_v0;

    if (func_8412E220() != 0) {
        temp_v0 = D_84195208[D_841951BC];
        (*(u8 *)((u8 *)(temp_v0) + (0xD))) = (u8) ((*(u8 *)((u8 *)(temp_v0) + (0xD))) | 0x20);
        func_84136678(D_841951BC, -1);
        func_84135B00(0x61U);
        func_84134DD8(D_841951BF);
        func_84134CBC(D_841951BC, 0U);
        func_84136CA8();
    }
}
#endif

#ifdef VERSION_US
extern void func_84125424(s32);
void BattleAnim_Table_84185FDC_007(void) {
    u8 *temp_v0;

    temp_v0 = D_84195208[D_841951BC];
    if ((*(u8 *)((u8 *)(temp_v0) + (0xD))) & 0x40) {
        func_84125424(2);
        return;
    }
    (*(s8 *)((u8 *)(temp_v0) + (0x12))) = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412E82C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412E94C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412EA28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412EB10.s")
#endif

#ifdef VERSION_US
extern s8 D_841951C2;

void BattleAnim_Table_84186004_002(void) {
    D_841951C2 = (s8) ((s32) ((*(u8 *)((u8 *)(D_84195200[D_841951BC]) + (0x1C))) * 0xA) / 25);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412EC70.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412EE5C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412EFFC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412F044.s")
#endif

#ifdef VERSION_US
extern void func_841254E0(void);
extern void func_84135B00(u8);
extern void func_84136678(u8, s32);
extern void func_84136CA8(void);
void BattleAnim_Table_84186004_007(void) {
    if (((u8 *)D_841951F8[D_841951BD])[0xB] & 4) {
        D_841951D2 = 1;
        func_84136678(D_841951BD, -1);
        func_84135B00(0x73);
        func_841246AC(D_841951BD, D_841951BF);
        func_84136CA8();
        func_841254E0();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412F170.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412F208.s")
#endif

#ifdef VERSION_US
extern u8 D_841951BD;
extern void *D_841951F8[];
extern u8 *D_84195208[];
extern s32 D_841951C8;
void BattleAnim_Table_84186004_010(void) {
    void *rec = D_841951F8[D_841951BD];
    u8 *flag = (u8 *) rec + 0x10;
    if (*flag != 0) {
        D_841951C8 = D_841951C8 << 1;
        if (D_841951C8 >= 0x10000) {
            D_841951C8 = 0xFFFF;
        }
    }
    *flag = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412F39C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412F49C.s")
#endif

#ifdef VERSION_US
void BattleAnim_Table_84186004_012(void) {
    func_8412F49C();
}
#endif

#ifdef VERSION_US
void BattleAnim_Table_84186004_013(void) {
    func_8412F49C();
}
#endif

#ifdef VERSION_US
void BattleAnim_Table_84186004_014(void) {
    func_8412F49C();
}
#endif

#ifdef VERSION_US
extern u8 D_841951BC; extern u8 *D_84195208[]; extern s8 D_841951C1; extern s8 D_841951C2; extern s32 func_84126EDC(u16); extern s32 func_84126E88(u16); extern void func_84127DB8(void);
void BattleAnim_Table_84186004_015(void) {
    u16 val = *(u16 *)(D_84195208[D_841951BC] + 0x2E);
    D_841951C1 = func_84126EDC(val);
    D_841951C2 = func_84126E88(val);
    func_84127DB8();
}
#endif

#ifdef VERSION_US
extern void *D_841951F0;
extern u8 D_841951BC;
extern void func_84136218(u8, u8);
extern void func_841366C4(u8, s32);
extern void func_84135B40(s32);
extern void func_84136124(u8, s16, u16, u8, u8);
void BattleAnim_Table_84186004_016(void) {
    (*(u8 *)((u8 *)D_841951F0 + 0x9C4)) = 1;
    (*(u8 *)((u8 *)D_841951F0 + 0x9C5)) = 5;
    func_84136218(D_841951BC, 6);
    func_841366C4(D_841951BC, -1);
    func_84135B40(0x23);
    func_84136124(D_841951BC, -1, 0x3C, 6, 0xF);
}
#endif

#ifdef VERSION_US
void BattleAnim_Table_84186004_017(void) {
    (*(u8 *)((u8 *)D_841951F0 + 0x9C4)) = 2;
    (*(u8 *)((u8 *)D_841951F0 + 0x9C5)) = 5;
    func_84136218(D_841951BC, 6);
    func_841366C4(D_841951BC, -1);
    func_84135B40(0x8A);
    func_84136124(D_841951BC, -1, 0x3C, 6, 0xE);
}
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_018(void) { func_84125CF8(D_841951BC, 0, 1, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_019(void) { func_84125CF8(D_841951BC, 1, 1, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_020(void) { func_84125CF8(D_841951BC, 2, 1, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_021(void) { func_84125CF8(D_841951BC, 3, 1, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_022(void) { func_84125CF8(D_841951BC, 4, 1, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_023(void) { func_84125CF8(D_841951BC, 5, 1, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_024(void) { func_84125CF8(D_841951BC, 6, 1, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_025(void) { func_84125CF8(D_841951BC, 0, 2, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_026(void) { func_84125CF8(D_841951BC, 1, 2, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_027(void) { func_84125CF8(D_841951BC, 2, 2, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_028(void) { func_84125CF8(D_841951BC, 3, 2, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_029(void) { func_84125CF8(D_841951BC, 4, 2, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_030(void) { func_84125CF8(D_841951BC, 5, 2, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BC; void BattleAnim_Table_84186004_031(void) { func_84125CF8(D_841951BC, 6, 2, 0); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_032(void) { func_84125CF8(D_841951BD, 0, 1, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_033(void) { func_84125CF8(D_841951BD, 1, 1, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_034(void) { func_84125CF8(D_841951BD, 2, 1, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_035(void) { func_84125CF8(D_841951BD, 3, 1, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_036(void) { func_84125CF8(D_841951BD, 4, 1, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_037(void) { func_84125CF8(D_841951BD, 5, 1, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_038(void) { func_84125CF8(D_841951BD, 6, 1, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_039(void) { func_84125CF8(D_841951BD, 0, 2, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_040(void) { func_84125CF8(D_841951BD, 1, 2, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_041(void) { func_84125CF8(D_841951BD, 2, 2, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_042(void) { func_84125CF8(D_841951BD, 3, 2, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_043(void) { func_84125CF8(D_841951BD, 4, 2, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_044(void) { func_84125CF8(D_841951BD, 5, 2, 1); }
#endif

#ifdef VERSION_US
extern u8 D_841951BD; void BattleAnim_Table_84186004_045(void) { func_84125CF8(D_841951BD, 6, 2, 1); }
#endif

#ifdef VERSION_US
extern void func_84124DEC(u8);
extern u8 D_841951D8;
extern void func_84126FA0(s32);
extern u8 D_841951D9;
void BattleAnim_Table_84186004_046(void) {
    if (D_841951D8 == 0) {
        func_84136678(D_841951BC, -1);
        func_84126FA0(D_841951D9 & 0xF & 0xFF);
        if (D_841951D9 & 0xF0) {
            func_84135B00(0x90U);
        } else {
            func_84135B00(0x8FU);
        }
        func_84124DEC(D_841951BC);
        func_84136CA8();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412FD24.s")
#endif

#ifdef VERSION_US
void BattleAnim_Table_84186004_048(void) {
    switch (D_841951D8) {                           /* irregular */
    case 1:
        func_84126BA8(D_841951BC);
        return;
    case 2:
        func_841366C4(D_841951BC, -1);
        func_84126FA0(D_841951D9 & 0xF & 0xFF);
        func_84135B40(0x63);
        /* fallthrough */
    case 0:
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8412FF80.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413005C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841300D0.s")
#endif

#ifdef VERSION_US
extern s32 func_84126374(void);
void BattleAnim_Table_84186004_052(void) {
    if (D_841951D2 == 0) {
        if ((((u8 *)D_84195208[D_841951BD])[0x10] & 0x10) ||
            (*(u8 *)((u8 *)D_84195200[D_841951BD] + 0x24) & 0x27) ||
            (func_84126374() == 0)) {
            D_841951D2 = 1;
            return;
        }
        ((u8 *)D_84195208[D_841951BD])[0xF] |= 8;
        ((u8 *)D_84195208[D_841951BD])[0x10] &= 0xFFDF;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84130284.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84130380.s")
#endif

#ifdef VERSION_US
extern u8 D_841951BC; extern u8 *D_84195208[]; void BattleAnim_Table_84186004_055(void) { D_84195208[D_841951BC][0x10] |= 0x40; }
#endif

#ifdef VERSION_US
void BattleAnim_Table_84186004_056(void) {
    if (D_84195208[D_841951BD][0xF] & 0x40) {
        D_841951C8 = D_841951C8 << 1;
        if (D_841951C8 >= 0x10000) {
            D_841951C8 = 0xFFFF;
        }
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Table_84186004_057(void) {
    if (D_84195208[D_841951BD][0xF] & 0x20) {
        D_841951C8 = D_841951C8 << 1;
        if (D_841951C8 >= 0x10000) {
            D_841951C8 = 0xFFFF;
        }
    }
}
#endif

#ifdef VERSION_US
extern u8 D_841951BD;
extern u8 *D_84195208[];
extern u8 D_841951D2;
extern u8 D_841951D5;
extern u8 D_841951E5;
extern s32 D_841951C8;
extern u8 func_80063454(u8, u8, u8, s32);
extern u8 func_80062D5C(u8);
extern s32 func_84126374(void);
extern s32 func_841251CC(u8);
void BattleAnim_Table_84186004_058(void) {
    u8 field;
    u8 *rec;

    rec = D_84195208[D_841951BD];
    field = rec[0x26];
    D_841951D2 = 1;
    if (field == 0 || field == 0xF3) {
        return;
    }
    if (func_80063454(0x18, rec[1], rec[2], (rec[0xD] & 8) != 0) == 0) {
        D_841951D5 = 0;
        D_841951E5 = 0;
        return;
    }
    if (func_84126374() != 0) {
        return;
    }
    if (func_80062D5C(field) == 0) {
        return;
    }
    if (func_841251CC(field) != 0) {
        if (D_841951C8 != 0) {
            D_841951C8 = D_841951C8 << 1;
            if (D_841951C8 >= 0x10000) {
                D_841951C8 = 0xFFFF;
            }
            D_841951D2 = 0;
        }
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Table_84186004_059(void) {
    u8 *temp_v0;

    temp_v0 = D_84195208[D_841951BC];
    if (*(u8 *)((u8 *)temp_v0 + 0x1A) == 1) {
        *(u8 *)((u8 *)temp_v0 + 0x1A) = 0;
        D_841951C8 = *(u16 *)((u8 *)D_84195208[D_841951BC] + 0x30);
        func_84125424(0x91);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841306AC.s")
#endif

#ifdef VERSION_US
void BattleAnim_Table_84186004_061(void) {
    if (D_84195208[D_841951BD][0x2A] != 0) {
        D_841951C8 = D_841951C8 << 1;
        if (D_841951C8 >= 0x10000) {
            D_841951C8 = 0xFFFF;
        }
    }
}
#endif

#ifdef VERSION_US

void BattleAnim_Table_84186004_062(void) {
    if ((*(u8 *)((u8 *)(D_841951F0) + (0x9C4))) == 2) {
        func_84125424(0x31);
    }
}
#endif

#ifdef VERSION_US
extern u8 D_841951C4;
void BattleAnim_Table_84186004_063(void) {
    u8 value = *(u8 *)((u8 *)D_841951F0 + 0x9C4);
    if (value != 1) {
        if (value == 2) {
            D_841951C4 = 0x80;
        }
    } else {
        D_841951C4 = 0xFF;
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Table_84186004_064(void) {
    func_84136678(D_841951BC, -1);
    func_84135B00(0xB5U);
    func_84124594(D_841951BC);
    func_84136CA8();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841308A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84130A74.s")
#endif

#ifdef VERSION_US
extern u8 D_841951D5;
extern u8 func_80063454(u8, u8, u8, s32);
void BattleAnim_Table_84186004_067(void) {
    u8 *temp_v0;

    temp_v0 = D_84195208[D_841951BD];
    if (func_80063454(D_841951C1,
                      *(u8 *)((u8 *)temp_v0 + 1),
                      *(u8 *)((u8 *)temp_v0 + 2),
                      ((*(u8 *)((u8 *)temp_v0 + 0xD) & 8) != 0)) == 0) {
        D_841951C8 = 0;
        D_841951D5 = 0;
        D_841951E5 = 0;
        D_841951D2 = 1;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84130B40.s")
#endif

#ifdef VERSION_US
extern void func_84130EA8();
extern u8 D_841951D5;
extern u8 D_841951D2;
extern void func_84126BA8(u8);
void BattleAnim_Table_84186004_069(void) {
    if (D_841951D2 != 0) {
        if (D_841951D5 & 0x7F) {
            func_84126BA8(D_841951BC);
            return;
        }
        func_84136678(D_841951BC, -1);
        func_84135B00(0x66U);
        func_841246AC((s32) D_841951BD, D_841951BF);
        func_84136CA8();
        return;
    }
    func_84130EA8();
}
#endif

#ifdef VERSION_US
extern s32 D_841951E0;

void BattleAnim_Table_84186004_070(void) {
    if (D_841951E0 == 0) {
        func_84126BA8(D_841951BC);
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Table_84186004_071(void) {
    if (D_841951D2 != 0) D_841951C8 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84130CE8.s")
#endif

#ifdef VERSION_US
extern void func_84128B30();
void BattleAnim_Table_84186004_073(void) {
    if (!((*(u8 *)((u8 *)(D_84195208[D_841951BC]) + (0xF))) & 4)) {
        func_84128B30();
    }
}
#endif

#ifdef VERSION_US
extern u8 D_841951BC; extern u8 *D_84195208[]; void BattleAnim_Table_84186004_074(void) { D_84195208[D_841951BC][0x12] = 0; }
#endif

#ifdef VERSION_US
void BattleAnim_Table_84186004_075(void) { D_84195208[D_841951BC][0xE] |= 1; }
#endif

#ifdef VERSION_US
extern void func_84134E30(s32);
void func_84134DD8(u8 arg0);
void func_84136D40(u8 arg0);
void BattleAnim_Table_84186004_076(void) {
    if (D_841951D2 != 0) {
        func_84134E30(1);
    }
    if ((D_841951BF == 0xAD) && !((*(u8 *)((u8 *)(D_84195200[D_841951BC]) + (0x24))) & 7)) {
        func_84124594(D_841951BC);
    } else {
        func_84134CBC(D_841951BC, 0U);
    }
    func_84134DD8(D_841951BF);
    func_84136D40(0U);
    func_84136CA8();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84130EA8.s")
#endif

#ifdef VERSION_US
void func_84134DD8(u8 arg0);
void func_84135034(u8 arg0, u8 arg1);
void BattleAnim_Table_84186004_078(void) {
    s32 temp_v1;
    u8 *temp_v0;

    if ((*(u8 *)((u8 *)(D_84195208[D_841951BC]) + (0xF))) & 4) {
        func_84134CBC(D_841951BC, 0U);
        func_84134DD8(D_841951BF);
        temp_v0 = D_84195208[D_841951BC];
        temp_v1 = (*(s32 *)((u8 *)(temp_v0) + (0x4C)));
        func_84135034((temp_v1 - (*(u8 *)((u8 *)(temp_v0) + (0x12)))) & 0xFF, (temp_v1 - 1) & 0xFF);
        func_84136CA8();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84131174.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841312E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413146C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84131538.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841315C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84131664.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84131760.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841318C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84131AB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84131AF8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84131EAC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84131F80.s")
#endif

#ifdef VERSION_US
extern u8 func_84131F80(s32);
s32 func_8413202C(void) {
    u8 first;
    s32 second;

    first = func_84131F80(0);
    second = func_84131F80(1);
    if (second == first) {
        return 0;
    }
    if (second < (s32)first) {
        return 1;
    }
    return 2;
}
#endif

#ifdef VERSION_US
extern u8 *D_84195208[];
s32 func_8413207C(void) {
    u16 y = *(u16 *)(D_84195208[0] + 0x40);
    u16 x = *(u16 *)(D_84195208[1] + 0x40);
    if (y == x) {
        if (func_84125080() < 0x80) {
            return 1;
        }
        return 2;
    }
    if (x < y) {
        return 1;
    }
    return 2;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841320E8.s")
#endif

#ifdef VERSION_US
extern void func_84133C10(s32);
extern void *D_84195204;
void func_84132300(void) {
    if ((*(u16 *)((u8 *)(*D_84195200) + (0x26))) == 0) {
        func_84133C10(1);
    }
    if ((*(u16 *)((u8 *)(D_84195204) + (0x26))) == 0) {
        func_84133C10(0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84132350.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841324EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84132778.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413293C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84132A94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84132B9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84132D44.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84132E40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84132F34.s")
#endif

void func_841330B4(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841330BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841331F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84133304.s")
#endif

#ifdef VERSION_US
extern void func_84132300(void);
extern void func_84132350(void);
extern void func_841324EC(void);
extern void func_84132778(void);
extern void func_8413293C(void);
extern void func_84132A94(void);
extern void func_84132B9C(void);
extern void func_84132D44(void);
extern void func_84132E40(void);
extern void func_84132F34(void);
extern void func_841330BC(void);
extern void func_841331F8(void);
void func_84133440(void) {
    func_84132300();
    func_84132350();
    func_84132300();
    func_841324EC();
    func_84132300();
    func_84132778();
    func_84132300();
    func_8413293C();
    func_84132300();
    func_84132A94();
    func_84132B9C();
    func_84132D44();
    func_84132E40();
    func_84132F34();
    func_841330BC();
    func_841331F8();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841334D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84133714.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84133924.s")
#endif

#ifdef VERSION_US
extern void func_8412693C(u8);
extern void func_84126994(u8);
extern void func_841318C0(u8, u8);
extern void func_84133924(u8);
void func_84133984(u8 arg0, u8 arg1) {
    func_84133924(arg0);
    func_841318C0(arg0, arg1);
    func_84126994(arg0);
    func_8412693C(arg0);
    func_84126A64();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841339D0.s")
#endif

#ifdef VERSION_US
void func_84133ACC(u8 arg0) {
    ((u8 *) D_841951F8[arg0])[0x10] = 1;
    func_841334D8(arg0);
    func_841339D0(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84133B14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84133C10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84133F10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84134018.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84134098.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84134170.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841341D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413425C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841343FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841347A0.s")
#endif

#ifdef VERSION_US
extern void func_841347A0(void *);
extern OSThread D_84193FB0;
extern OSMesgQueue D_84195164;
extern OSMesg D_84195160;
void func_841348C0(void) {
    osCreateMesgQueue(&D_84195164, &D_84195160, 1);
    osCreateThread(&D_84193FB0, 0xC, func_841347A0, NULL, &D_84195160, 0x19);
}
#endif

#ifdef VERSION_US
void func_84134920(void) { extern OSThread D_84193FB0; osStartThread(&D_84193FB0); }
#endif

#ifdef VERSION_US
void func_84134944(void) { extern OSThread D_84193FB0; osDestroyThread(&D_84193FB0); }
#endif

#ifdef VERSION_US
s32 func_84134968(void) { extern OSMesgQueue D_84195164; return osRecvMesg(&D_84195164, NULL, 1); }
#endif

#ifdef VERSION_US
void Display_QueueFramebufferRequest_fragment79(OSMesg arg0) {
    osSendMesg(&D_84195164, arg0, 0);
}
#endif

#ifdef VERSION_US
s32 func_841349C0(f32 arg0) { s32 value = (s32)arg0; f64 fraction = (f64)(arg0 - (f32)value); return fraction >= 0.5 ? value + 1 : value; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84134A10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84134A6C.s")
#endif

#ifdef VERSION_US
extern void func_84134A6C(u8 *, u8, u8);
extern void func_841350F4(u8 *, u8, u8);
extern u8 D_84195280[];
void func_84134CBC(u8 arg0, u8 arg1) {
    func_84134A6C(&D_84195280[D_84195280[0x4D81] * 0x280], arg0, arg1);
}
#endif

#ifdef VERSION_US
extern u8 D_84195280[];
s32 func_84134D04(void) {
    return *(u16 *)(&D_84195280[D_84195280[0x4D81] * 0x280 + 4]);
}
#endif

#ifdef VERSION_US
extern u8 D_84195280[];
void func_84134D28(u8 arg0, u8 arg1) {
    s32 idx = D_84195280[0x4D81] - 1;
    if (idx < 0) {
        idx = 0x1D;
    }
    func_84134A6C(D_84195280 + idx * 0x280, arg0, arg1);
}
#endif

#ifdef VERSION_US
extern u8 *D_84186160[];
extern void func_84134A6C(u8 *, u8, u8);
void func_84134D80(u8 arg0, u8 arg1, u8 arg2) {
    if (arg0 < 4) {
        u8 *ptr = D_84186160[arg0];
        if (ptr != NULL) {
            func_84134A6C(ptr, arg1, arg2);
        }
    }
}
#endif

#ifdef VERSION_US
void func_84134DD8(u8 arg0) {
    D_84195280[D_84195280[0x4D81] * 0x280 + 8] = arg0;
}
#endif

#ifdef VERSION_US
void func_84134E00(u8 arg0) {
    D_84195280[D_84195280[0x4D81] * 0x280 + 9] |= arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84134E30.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84134E7C.s")
#endif

#ifdef VERSION_US
void func_84134EC8(u8 arg0) {
    s32 index;
    u8 *record;
    index = D_84195280[0x4D81] - 1;
    if (index < 0) {
        index = 0x1D;
    }
    record = D_84195280 + index * 0x280;
    record[9] |= arg0;
}
#endif

#ifdef VERSION_US
extern u8 *D_84186160[];
void func_84134F0C(u8 arg0, u8 arg1) {
    if (arg0 < 4) {
        u8 *ptr = D_84186160[arg0];
        u8 *base = ptr + 8;
        if (ptr != NULL) base[1] |= arg1;
    }
}
#endif

#ifdef VERSION_US
void func_84134F50(u8 *arg0, u8 arg1, u8 arg2) {
    *(u16 *)((u8 *)arg0 + ((u32)arg1 << 4) + 0x12) |= (u16)(u8)arg2;
}
#endif

#ifdef VERSION_US
void func_84134F78(u8 arg0, u8 arg1) {
    func_84134F50(&D_84195280[D_84195280[0x4D81] * 0x280], arg0, arg1);
}
#endif

#ifdef VERSION_US
void func_84134FC0(u8 *arg0, u8 arg1, u8 arg2) {
    *(u16 *)((u8 *)arg0 + (arg1 << 4) + 0x12) = *(u16 *)((u8 *)arg0 + (arg1 << 4) + 0x12) & ~(u16)(u8)arg2;
}
#endif

#ifdef VERSION_US
void func_84134FEC(u8 arg0, u8 arg1) {
    func_84134FC0(&D_84195280[D_84195280[0x4D81] * 0x280], arg0, arg1);
}
#endif

#ifdef VERSION_US
void func_84135034(u8 arg0, u8 arg1) {
    u8 *ptr = &D_84195280[D_84195280[0x4D81] * 0x280];
    ptr += 8;
    ptr[2] = arg0;
    ptr[3] = arg1;
}
#endif

#ifdef VERSION_US
extern u8 D_84195280[];
void func_84135068(u8 arg0, u8 arg1) {
    s32 idx = D_84195280[0x4D81] - 1;
    if (idx < 0) {
        idx = 0x1D;
    }
    D_84195280[idx * 0x280 + 0xA] = arg0;
    D_84195280[idx * 0x280 + 0xB] = arg1;
}
#endif

#ifdef VERSION_US
void func_841350AC(u8 arg0, u8 arg1, u8 arg2) {
    if (arg0 < 4) {
        u8 *ptr = D_84186160[arg0];
        u8 *base = ptr + 8;
        if (ptr != NULL) {
            base[2] = arg1;
            base[3] = arg2;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841350F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841351EC.s")
#endif

#ifdef VERSION_US
void func_8413523C(u8 arg0, u8 arg1) {
    func_841350F4(&D_84195280[D_84195280[0x4D81] * 0x280], arg0, arg1);
}
#endif

#ifdef VERSION_US
extern void func_841350F4(u8 *, u8, u8);
extern u8 D_84195280[];
void func_84135284(u8 arg0, u8 arg1) {
    s32 idx = D_84195280[0x4D81] - 1;
    if (idx < 0) {
        idx = 0x1D;
    }
    func_841350F4(D_84195280 + idx * 0x280, arg0, arg1);
}
#endif

#ifdef VERSION_US
extern u8 D_84195280[];
extern void func_841351EC(void *, u8);
void func_841352DC(u8 arg0) {
    s32 idx = D_84195280[0x4D81] - 1;
    if (idx < 0) {
        idx = 0x1D;
    }
    func_841351EC(D_84195280 + idx * 0x280, arg0);
}
void func_841352DC_padding1(void) {}
void func_841352DC_padding2(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84135338.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413543C.s")
#endif

#ifdef VERSION_US
s32 func_84135700(void) {
    if (*(u16 *)(D_84195280 + 0x4B36) != 0) {
        return 0;
    }
    if (*(u16 *)(D_84195280 + 0x4B4E) != 0) {
        return 0;
    }
    return 1;
}
#endif

#ifdef VERSION_US
extern u8 D_8419A004;
extern u16 D_84199FFC;
s32 func_8413573C(void) {
    if (D_8419A004 != 0) {
        if (D_84199FFC != 0) return 0;
        D_8419A004 = 0;
    }
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84135778.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84135808.s")
#endif

#ifdef VERSION_US
extern void StageFade_StartFromTransparent(u8);
extern void func_84147228(s32, u8, s32, s32, s32);
extern u8 D_84195278;
void func_8413584C(u8 arg0) {
    StageFade_StartFromTransparent(arg0);
    func_84147228(0x1D, 0U, 0, 0xA, (s32) arg0);
    func_84147228(0x1D, 0U, 0, 4, 4);
    D_84195278 = 7;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841358B0.s")
#endif

#ifdef VERSION_US
s32 func_84135778();
extern void func_841358B0();
extern s8 D_8419A005;

void func_84135998(void) {
    if (func_84135778() != 0) {
        func_841358B0();
        D_8419A005 = 0;
    }
}
#endif

#ifdef VERSION_US
extern void func_8413543C();
void func_841359D0(void) {
    switch (D_84195278) {                           /* irregular */
    case 1:
        func_8413543C();
        return;
    case 2:
    case 6:
        func_84135998();
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84135A2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84135B00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84135B40.s")
#endif

#ifdef VERSION_US
extern u8 *D_84186160[];
extern void func_84135A2C(u8 *, u16);
void func_84135B8C(u8 arg0, u16 arg1) {
    if (arg0 < 4) {
        u8 *ptr = D_84186160[arg0];
        if (ptr != NULL) {
            func_84135A2C(ptr, arg1);
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84135BDC.s")
#endif

#ifdef VERSION_US
extern u8 D_84195280[];
extern void func_84135BDC(void *, u8, s16, u16, s32);
void func_84135C78(u8 arg0, s16 arg1, u16 arg2, u16 arg3) {
    func_84135BDC(&D_84195280[D_84195280[0x4D81] * 0x280], arg0, arg1, arg2, arg3);
}
#endif

#ifdef VERSION_US
extern void func_84135BDC(void *, u8, s16, u16, s32);
void func_84135CD4(u8 arg0, s16 arg1, u16 arg2, u16 arg3) {
    s32 var_v0;

    var_v0 = (*(u8 *)((u8 *)(D_84195280) + (0x4D81))) - 1;
    if (var_v0 < 0) {
        var_v0 = 0x1D;
    }
    func_84135BDC(D_84195280 + (var_v0 * 0x280), arg0, arg1, arg2, (s32) arg3);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84135D3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84135DD8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84135E4C.s")
#endif

#ifdef VERSION_US
extern u32 func_8003570C(void);
s32 func_84135F94(u8 *arg0) {
    s32 result;

    result = 0;
    switch (arg0[1]) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 1;
        arg0[1] = 0;
        break;
    case 4:
        result = func_8003570C() & 1;
        break;
    case 3:
        result = 1;
        arg0[1] = 4;
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84136014.s")
#endif

#ifdef VERSION_US
extern u8 D_84195280[];
extern void func_84136014(void *, u8, s16, u16, s32, s32);
void func_841360C0(u8 arg0, s16 arg1, u16 arg2, u8 arg3, u8 arg4) {
    func_84136014(&D_84195280[D_84195280[0x4D81] * 0x280], arg0, arg1, arg2, arg3, arg4);
}
#endif

#ifdef VERSION_US
extern void func_84136014(void *, u8, s16, u16, s32, s32);
void func_84136124(u8 arg0, s16 arg1, u16 arg2, u8 arg3, u8 arg4) {
    s32 var_v0;

    var_v0 = (*(u8 *)((u8 *)(D_84195280) + (0x4D81))) - 1;
    if (var_v0 < 0) {
        var_v0 = 0x1D;
    }
    func_84136014(D_84195280 + (var_v0 * 0x280), arg0, arg1, arg2, (s32) arg3, (s32) arg4);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84136194.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84136218.s")
#endif

#ifdef VERSION_US
extern u32 D_8419A020[];
s32 func_84136294(u8 arg0, u8 arg1) {
    u8 *p = (u8 *)(u32)D_8419A020 + (arg0 << 6);
    return (*(u32 *)p & (1 << arg1)) != 0;
}
#endif

#ifdef VERSION_US
extern u8 D_8419A024[];
void func_841362C8(u8 arg0) {
    *(u32 *)(D_8419A024 + ((u32)arg0 << 6)) = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841362E4.s")
#endif

#ifdef VERSION_US
extern void func_841362E4(u8, u8, u8, u8, s32);
void func_84136354(u8 arg0) {
    func_841362E4(arg0, 1, 1, 0, 0xC);
    func_841362E4(arg0, 2, 1, 0, 0xD);
    func_841362E4(arg0, 3, 3, 0, 0xE);
    func_841362E4(arg0, 4, 3, 0, 0xF);
    func_841362E4(arg0, 5, 4, 0, 0x10);
    func_841362E4(arg0, 6, 4, 0, 0x11);
    func_841362E4(arg0, 7, 3, 0, 0x12);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84136440.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84136564.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841365F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84136678.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841366C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84136720.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413677C.s")
#endif

#ifdef VERSION_US
extern u8 D_84195280[];
extern void func_8413677C(void *, u8, s16, s16, s32);
void func_84136A9C(u8 arg0, s16 arg1, s16 arg2, u8 arg3) {
    func_8413677C(&D_84195280[D_84195280[0x4D81] * 0x280], arg0, arg1, arg2, arg3);
}
#endif

#ifdef VERSION_US
extern void func_8413677C(void *, u8, s16, s16, s32);
void func_84136AF8(u8 arg0, s16 arg1, s16 arg2, u8 arg3) {
    s32 var_v0;

    var_v0 = (*(u8 *)((u8 *)(D_84195280) + (0x4D81))) - 1;
    if (var_v0 < 0) {
        var_v0 = 0x1D;
    }
    func_8413677C(D_84195280 + (var_v0 * 0x280), arg0, arg1, arg2, (s32) arg3);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84136B60.s")
#endif

#ifdef VERSION_US
extern u8 D_84195280[];
extern void func_84136B60(void *, u8, s16, u16);
void func_84136B9C(u8 arg0, s16 arg1, u16 arg2) {
    func_84136B60(&D_84195280[D_84195280[0x4D81] * 0x280], arg0, arg1, arg2);
}
#endif

#ifdef VERSION_US
extern u8 D_84195280[];
extern void func_84136B60(void *, u8, s16, u16);
void func_84136BEC(u8 arg0, s16 arg1, u16 arg2) {
    s32 idx = D_84195280[0x4D81] - 1;
    if (idx < 0) {
        idx = 0x1D;
    }
    func_84136B60(D_84195280 + idx * 0x280, arg0, arg1, arg2);
}
#endif

#ifdef VERSION_US
extern void func_84136B60(void *, u8, s16, u16);
extern u8 * D_84186160[];
void func_84136C48(u8 arg0, u8 arg1, s32 arg2, u16 arg3) {
    u8 *ptr;

    if (arg0 >= 4) {
        return;
    }
    ptr = D_84186160[arg0];
    if (ptr != NULL) {
        func_84136B60(ptr, arg1, arg2, arg3);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84136CA8.s")
#endif

#ifdef VERSION_US
extern u8 D_84195280[]; u8 *func_84136D00(void) { return &D_84195280[D_84195280[0x4D80] * 0x280]; }
#endif

#ifdef VERSION_US
extern u8 D_84195280[]; u8 *func_84136D20(void) { return &D_84195280[D_84195280[0x4D81] * 0x280]; }
#endif

#ifdef VERSION_US
void func_84136D40(u8 arg0) {
    extern u8 *D_84186160[];
    if (arg0 < 4) {
        D_84186160[arg0] = &D_84195280[D_84195280[0x4D81] * 0x280];
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84136D84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84136D9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84137404.s")
#endif

#ifdef VERSION_US
extern void func_84137404(u8, u16); extern void func_8002C2E0(u8);
void func_841374D0(void *arg0) {
    s32 i;

    for (i = 0; i < *(u8 *)((u8 *)arg0 + 0x182); i++) {
        func_84137404(*(u8 *)((u8 *)arg0 + 0x180), *(u16 *)((u8 *)arg0 + 0x184 + i * 2));
    }
    func_8002C2E0(*(u8 *)((u8 *)arg0 + 0x180));
}
#endif

#ifdef VERSION_US
void func_8413753C(void *arg0) {
    func_84147228(0x11, 0U, 0, 6, (s32) (*(u8 *)((u8 *)(arg0) + (0x80))));
    func_84147228(0x11, 0U, 0, 8, (s32) (*(u8 *)((u8 *)(arg0) + (0x81))));
    func_84147228(0x11, 0U, 0, 3, 0);
    func_84147228(0x11, 0U, 0, 0xA, 0);
    func_84147228(0x12, 0U, 0, 6, (s32) (*(u8 *)((u8 *)(arg0) + (0x80))));
    func_84147228(0x12, 0U, 0, 3, 0);
    func_84147228(0x12, 0U, 0, 1, 0);
    func_84147228(0x12, 0U, 0, 0xF, 0);
    func_84147228(0x12, 0U, 0, 0xA, 0);
}
#endif

#ifdef VERSION_US
void func_84137648(void) {
    if (func_841484CC(0x11, 0, 0, 1) == 0) {
        func_84147228(0x11, 0U, 0, 4, 3);
        func_84147228(0x12, 0U, 0, 4, 3);
    }
}
#endif

#ifdef VERSION_US
void func_841376B0(void *arg0) {
    func_84147228(0x10, 0U, 0, 8, (s32) (*(u8 *)((u8 *)(arg0) + (0x181))));
    func_84147228(0x10, 0U, 0, 3, 0);
    func_84147228(0x10, 0U, 0, 0xA, 0);
}
#endif

#ifdef VERSION_US
extern void func_84147228(s32, u8, s32, s32, s32);
s32 func_8413771C(void) {
    s32 result = 0;
    if (func_841484CC(0x10, 0, 0, 1) == 0) {
        func_84147228(0x10, 0U, 0, 4, 3);
        result = 1;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84137778.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413794C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84137BD4.s")
#endif

#ifdef VERSION_US
extern void func_84134E30(s32); extern u8 D_84199D81; extern u8 D_8418548C[];
void func_84137CA4(void) {
    u8 *addr = &D_84199D81;
    u8 flags;

    flags = *addr;
    if (flags & 1) {
        flags = *addr;
        flags &= 0xFFFE;
        *addr = flags;
    }
    flags = *addr;
    if (flags & 2) {
        flags &= 0xFFFD;
    }
    *addr = flags;
    if (flags & 4) {
        flags &= 0xFFFB;
        *addr = flags;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84137D04.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84137DB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84137ED4.s")
#endif

#ifdef VERSION_US
void func_84138364(u8 arg0) {
    func_84147228(1, arg0, 0, 0xB, 0);
    func_84147228(1, arg0, 0, 4, 4);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841383B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84138530.s")
#endif

#ifdef VERSION_US
extern s32 D_8419527C;
extern void * D_841951F0;
void func_841385A8(u8 arg0, u8 arg1) {
    struct State { u8 pad[0x9D8]; u8 *items; };
    if (D_8419527C < 0x67) {
        u8 field = (((struct State *)D_841951F0)->items + D_8419527C)[4];
        u8 high = arg1 << 4;
        (((struct State *)D_841951F0)->items + D_8419527C)[4] = arg0 ? ((field & 0xF0) | (arg1 & 0xF)) : ((field & 0xF) | high);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413860C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84138658.s")
#endif

#ifdef VERSION_US
extern void * D_841951F8[];
s32 func_8413882C(u8 arg0, u8 arg1) {
    u8 *ptr = D_841951F8[arg0];

    if (ptr[0x12] != 0) {
        if (ptr[0xA] < ptr[3]) {
            return arg1 >= ptr[3];
        }
        return arg1 < ptr[3];
    }
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413888C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84138960.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84138A0C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84138D74.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84138EA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84139244.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841392E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84139364.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84139528.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84139618.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84139770.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_841397FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84139958.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84139C54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84139D94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84139EB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_84139F44.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413A12C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413A340.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413A53C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413A6CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413A8C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413AB2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413AD98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413B08C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413B254.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413B468.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413B5D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413B870.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413BBEC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413BC64.s")
#endif

#ifdef VERSION_US
extern u8 D_84195248[];
extern void *D_841951F8[];
extern void func_84139364(u8);
void func_8413BD94(u8 arg0) {
    u8 **entry = (u8 **)((u8 *)D_84195248 + arg0 * 24);
    if (((*(u16 *)(entry[0] + 8) & 0x20) != 0) || (((u8 *)D_841951F8[arg0])[2] == 2 && ((*(u16 *)(entry[1] + 8) & 0x20) != 0))) {
        func_84139364(arg0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413BE1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413BE84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413BF58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413C0A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413C18C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413C2C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413C3A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413C500.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413C6AC.s")
#endif

#ifdef VERSION_US
extern void GfxImage_FillCurrent(s32 *, s32);
extern u8 D_800D0510;
void func_8413C7C0(void) {
    GfxImage_FillCurrent(&D_800D0510, 1);
    if ((*(u8 *)((u8 *)(D_84195280) + (0x4B02))) != 0) {
        (*(u16 *)((u8 *)(D_84195280) + (0x4B06))) = 0x2DU;
        (*(u8 *)((u8 *)(D_84195280) + (0x4B02))) = 0U;
        (*(s8 *)((u8 *)(D_84195280) + (0x4B01))) = 5;
    }
    if ((s32) (*(u16 *)((u8 *)(D_84195280) + (0x4B06))) > 0) {
        (*(u16 *)((u8 *)(D_84195280) + (0x4B06))) = (u16) ((*(u16 *)((u8 *)(D_84195280) + (0x4B06))) - 1);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413C820.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413CE84.s")
#endif

#ifdef VERSION_US
extern u8 D_84199DE8[];
u8 *func_8413D254(void) {
    return D_84199DE8;
}
#endif

#ifdef VERSION_US
extern u8 D_84199F74[];
u8 *func_8413D260(void) {
    return &D_84199F74[2];
}
#endif

#ifdef VERSION_US
extern u8 D_84195252[];
u8 func_8413D26C(u8 arg0, u8 arg1) {
    return D_84195252[arg0 * 24 + arg1];
}
#endif

#ifdef VERSION_US
extern u8 D_84195218[];
u8 *func_8413D29C(u8 arg0) {
    return D_84195218 + arg0 * 24;
}
#endif

#ifdef VERSION_US
extern u8 D_84195254[];
void func_8413D2C0(u8 arg0, s32 arg1) {
    D_84195254[arg0 * 24] = arg1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413D2E4.s")
#endif

#ifdef VERSION_US
extern u8 D_8419521C[];
f32 func_8413D358(u8 arg0) {
    return *(f32 *)(D_8419521C + arg0 * 24);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413D37C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413D6D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413D7AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413DA18.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413DB28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413DD94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413DE28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_393CA0/func_8413E2EC.s")
#endif
