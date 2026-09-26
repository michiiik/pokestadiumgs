#include "global.h"


#ifdef VERSION_US
s32 func_8004D690(s32);
extern s32 *D_825087F0;

void func_82504810(void) {
    *D_825087F0 = func_8004D690(0xD);
}

extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_800495BC(s32, s32, s32);
extern void func_800499EC(void);
extern s32 * D_825087F0;
void func_8250483C(void) {
    s32 *temp_s4;
    s32 var_s0;

    temp_s4 = D_825087F0;
    func_800498C4();
    func_800496A4(8, 0);
    func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
    var_s0 = 0;
    do {
        if (var_s0 != *(s16 *)((u8 *)temp_s4 + 0xC)) {
            func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
        } else {
            func_8004972C(0xFF, 0xFF, 0, 0xFF);
        }
        func_800495BC(((var_s0 / 11) * 0xA0) + 0x64, ((var_s0 % 11) * 0x14) + 0x64, func_8004C874(0x31, var_s0 + 0x10));
        var_s0++;
    } while (var_s0 != 0x14);
    func_800499EC();
}

extern void func_80008648();
extern void func_800088DC();
extern void func_800468A0(s32);
extern void func_800503A4(s32);
extern void func_8250483C();
void func_8250498C(void) {
    s32 *sp1C;

    sp1C = D_825087F0;
    func_800088DC();
    func_800468A0((*(s32 *)((u8 *)(sp1C) + (0))));
    func_800503A4((*(s32 *)((u8 *)(sp1C) + (4))));
    func_8250483C();
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825049DC.s")

extern void StageFade_StartFromTransparent(s32);
s32 func_825049DC();
s32 func_82504B04(s32 arg0) {
    s32 var_s0;

    var_s0 = arg0;
    switch (arg0) {                                 /* irregular */
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            var_s0 = 1;
        }
        break;
    case 1:
        if (func_825049DC() != 0) {
            var_s0 = 3;
            StageFade_StartFromTransparent(5);
            func_80035424(0xF);
        }
        break;
    case 3:
        if (StageContext_GetFadeMode() == 1) {
            var_s0 = 4;
        }
        break;
    }
    return var_s0;
}

s32 func_82504B04(s32);
s32 func_82504BA0(s32 *arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_s1;

    D_825087F0 = arg0;
    var_s1 = 0;
    func_8004C09C(0x107);
    func_8004C4B0(0x31);
    func_82504810();
    func_80008624();
    if (StageContext_GetFadeMode() != 0) {
        func_800086A4(2);
        StageFade_StartFromOpaque(5);
    }
    do {
        func_80064D28();
        func_8250498C();
        temp_v0 = func_82504B04(var_s1);
        var_s1 = temp_v0;
    } while (temp_v0 != 4);
    StageLoader_WaitForRetrace();
    func_8004C398();
    return 5;
}

extern u16 D_82508FF6;
#pragma pack(1)
struct Fragment21PackedWord { s32 value; };
#pragma pack(0)
void func_82504C50(void *arg0, s32 arg1) {
    if ((arg0 != NULL) && (*(s16 *)((u8 *)arg0 + 8) == 0)) {
        *(s16 *)((u8 *)arg0 + 8) = 1;
        *(s16 *)((u8 *)arg0 + 0xC) = 0;
        if (arg1 == 1) {
            *(s16 *)((u8 *)arg0 + 0x10) = 0;
            *(s16 *)((u8 *)arg0 + 0x12) = 0x1E0;
        } else {
            if (D_82508FF6 & 2) {
                *(s16 *)((u8 *)arg0 + 0x10) = -0x280;
            } else {
                *(s16 *)((u8 *)arg0 + 0x10) = 0x280;
            }
            *(s16 *)((u8 *)arg0 + 0x12) = 0;
        }
        *(struct Fragment21PackedWord *)((u8 *)arg0 + 0x14) = *(struct Fragment21PackedWord *)((u8 *)arg0 + 0x10);
    }
}

extern void func_800226C0(s32);
void func_82504CC8(void *arg0, s32 arg1) {
    if ((arg0 != NULL) && (*(s16 *)((u8 *)arg0 + 8) == 2)) {
        *(s16 *)((u8 *)arg0 + 8) = 3;
        *(s16 *)((u8 *)arg0 + 0x4E) = arg1;
        *(s16 *)((u8 *)arg0 + 0x4C) = *(s16 *)((u8 *)arg0 + 0x24);
        *(s16 *)((u8 *)arg0 + 0xC) = 0;
        if (*(s16 *)((u8 *)arg0 + 0x4C) < *(s16 *)((u8 *)arg0 + 0x4E)) {
            func_800226C0(4);
            return;
        }
        if (*(s16 *)((u8 *)arg0 + 0x4E) < *(s16 *)((u8 *)arg0 + 0x4C)) {
            func_800226C0(6);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82504D40.s")

extern u16 D_82508FF6;
void func_82504D94(void *arg0, s32 arg1) {
    if ((arg0 != NULL) && ((*(s16 *)((u8 *)(arg0) + (8))) == 2)) {
        (*(s16 *)((u8 *)(arg0) + (8))) = 5;
        (*(s16 *)((u8 *)(arg0) + (0xC))) = 0;
        switch (arg1) {                             /* irregular */
        case 1:
            (*(s16 *)((u8 *)(arg0) + (0x14))) = 0;
            (*(s16 *)((u8 *)(arg0) + (0x16))) = 0x1E0;
            return;
        case 2:
            if (D_82508FF6 & 2) {
                (*(s16 *)((u8 *)(arg0) + (0x14))) = -0x280;
            } else {
                (*(s16 *)((u8 *)(arg0) + (0x14))) = 0x280;
            }
            (*(s16 *)((u8 *)(arg0) + (0x16))) = 0;
            return;
        default:
            if (D_82508FF6 & 2) {
                (*(s16 *)((u8 *)(arg0) + (0x14))) = 0x280;
            } else {
                (*(s16 *)((u8 *)(arg0) + (0x14))) = -0x280;
            }
            (*(s16 *)((u8 *)(arg0) + (0x16))) = 0;
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82504E38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82504FB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825050EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825052A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82505420.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82505758.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82505A64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_8250610C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825064A4.s")

extern void _bzero(s16 *, s32);
extern void func_8004C8C0(s32);
extern s16 D_82508FF0;
void func_8250684C(void) {
    func_8004C8C0(0x4B);
    func_8004C8C0(0x85);
    _bzero(&D_82508FF0, 0x68C);
    D_82508FF0 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82506888.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825068C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82506910.s")

extern s32 D_82509024;
extern s32 D_82509028;
extern s32 D_8250902C;
extern s32 D_82509030;
extern s32 D_82509034;
extern s32 D_82509038;
extern s16 D_82508FF0;
void func_825069F0(void *arg0, s32 arg1, s32 arg2, void *arg3, void *arg4, void *arg5, void *arg6, void *arg7) {
    *(struct Fragment21PackedWord *)&D_82509024 = *(struct Fragment21PackedWord *)arg0;
    *(s16 *)((u8 *)&D_82508FF0 + 0x30) = arg1;
    *(s16 *)((u8 *)&D_82508FF0 + 0x32) = arg2;
    *(struct Fragment21PackedWord *)&D_82509028 = *(struct Fragment21PackedWord *)arg3;
    *(struct Fragment21PackedWord *)&D_8250902C = *(struct Fragment21PackedWord *)arg4;
    *(struct Fragment21PackedWord *)&D_82509030 = *(struct Fragment21PackedWord *)arg5;
    *(struct Fragment21PackedWord *)&D_82509034 = *(struct Fragment21PackedWord *)arg6;
    *(struct Fragment21PackedWord *)&D_82509038 = *(struct Fragment21PackedWord *)arg7;
}

extern s16 D_82508FF0;
void func_82506AA4(s16 *arg0, s32 arg1, s32 arg2) {
    *(s16 *)((u8 *)&D_82508FF0 + 0x28) = arg0[0];
    *(s16 *)((u8 *)&D_82508FF0 + 0x2A) = arg0[1];
    *(s16 *)((u8 *)&D_82508FF0 + 0x2C) = arg1;
    *(s16 *)((u8 *)&D_82508FF0 + 0x2E) = arg2;
    *(u16 *)((u8 *)&D_82508FF0 + 6) |= 4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82506AD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82506BEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82506E98.s")

extern s16 D_82508FFC;
extern void _bzero(s16 *, s32);
extern void * func_825068C4(s32, s32);
void func_82506FB8(s32 arg0)
{
  void *temp_v0;
  unsigned short new_var;
  temp_v0 = func_825068C4(2, arg0);
  if (temp_v0 != 0)
  {
    new_var = 1;
    _bzero(temp_v0, 0x64);
    D_82508FFC -= new_var;
  }
}

extern void func_82504C50(void *, s32);
void *func_825068C4(s32, s32);

void func_82507000(s16 *arg0) {
    s16 temp_v1;
    void *temp_v0;

    temp_v0 = func_825068C4(1, 0);
    temp_v1 = (*(s16 *)((u8 *)(temp_v0) + (8)));
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_82504C50(temp_v0, 0);
        func_82504C50(func_825068C4(1, 1), 0);
        return;
    case 2:
        *arg0 = 2;
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507078.s")

extern void func_82507D04(s32, void *, s32, s32, s32, s32, s32);
extern void func_82504D40(void *, void *);
extern void func_82504CC8(void *, s32);
extern void func_800226C0(s32);
extern void * func_825068C4(s32, s32);
extern void func_82506FB8(s32 arg0);
extern void func_82507B18(void);
void func_82507250(void *arg0) {
    s16 temp_a2;
    s32 temp_a1;
    s32 temp_s1;
    s16 temp_v1;
    s32 var_s0;
    s32 var_s0_2;
    void *temp_s0;
    void *temp_s2;

    temp_s0 = func_825068C4(1, 0);
    temp_v1 = *(s16 *)((u8 *)arg0 + 2);
    temp_a1 = *(s16 *)((u8 *)arg0 + 0xE);
    temp_s1 = *(s16 *)((u8 *)arg0 + 0xC);
    switch (temp_v1) {
    case 0:
        temp_a2 = *(s16 *)((u8 *)temp_s0 + 0x30);
        func_82507D04(0, (u8 *)temp_s0 + 0x48, temp_a2, 0x31, temp_a2,
                     *(s16 *)((u8 *)temp_s0 + 0x2E), *(s32 *)((u8 *)temp_s0 + 0x34));
        temp_s2 = (u8 *)arg0 + 0x18;
        func_82504D40(temp_s0, temp_s2);
        func_82507B18();
        var_s0 = 0;
        if (temp_s1 > 0) {
            do {
                func_82504D40(func_825068C4(2, var_s0), temp_s2);
                var_s0++;
            } while (var_s0 != temp_s1);
        }
        *(s16 *)((u8 *)arg0 + 2) = 1;
        break;
    case 1:
        if (*(s16 *)((u8 *)temp_s0 + 8) == 2) {
            func_82504CC8(temp_s0, temp_a1);
            var_s0_2 = 0;
            if (temp_s1 > 0) {
                do {
                    func_82506FB8(var_s0_2);
                    var_s0_2++;
                } while (var_s0_2 != temp_s1);
            }
            *(s16 *)((u8 *)arg0 + 2) = 2;
            if (*(s16 *)((u8 *)arg0 + 0xC) > 0) {
                func_800226C0(0x112);
            }
        }
        break;
    case 2:
        if (*(s16 *)((u8 *)temp_s0 + 8) == 2) {
            *(s16 *)((u8 *)arg0 + 0) = 2;
            *(s16 *)((u8 *)arg0 + 4) = 0;
            *(u16 *)((u8 *)arg0 + 6) &= 0xFFF7;
        }
        break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825073B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825075B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_8250771C.s")

void func_82507AF4(void)
{
  int new_var;
  new_var = 1;
  if (D_82508FF0 == 0)
  {
    D_82508FF0 = new_var;
  }
}

extern void func_82504C50(void *arg0, s32 arg1);
extern void * func_825068C4(s32, s32);
extern u16 D_82508FF6;
void func_82507B18(void) {
    u16 *flag;
    void *temp_v0;

    flag = &D_82508FF6;
    temp_v0 = func_825068C4(1, 1);
    func_82504C50(temp_v0, 1);
    *flag = *flag | 8;
}


s32 func_82507B58(void) {
    return D_82508FF0 == 2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507B6C.s")


s32 func_82507BBC(void) {
    return D_82508FF0 == 4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507BD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507BFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507C48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507C98.s")


s32 func_82507CF4(void) {
    return D_82508FF0 == 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507D04.s")
#endif
