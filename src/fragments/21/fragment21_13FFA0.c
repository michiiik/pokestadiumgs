#include "global.h"


#ifdef VERSION_US
extern s16 D_82508F6E;
s32 func_82500020(s32 arg0, void *arg1) {
    if (arg0 != 0 && arg0 == 1) {
        if (D_82508F6E != 0) {
            *(u16 *)((u8 *)arg1 + 2) |= 2;
        } else {
            *(u16 *)((u8 *)arg1 + 2) &= 0xFFFD;
        }
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 D_82508F80;
s32 func_82500064(s32 arg0, s32 arg1) { switch (arg0) { case 0: D_82508F80 = arg1; break; case 1: break; default: break; } return 0; }
#endif

#ifdef VERSION_US
extern u16 D_82508790;
extern f32 D_80088E50[];
s32 func_8250008C(s32 arg0, u8 *arg1) {
    u16 *state;
    u16 value;
    unsigned int new_var2;
    f32 sample;
    f32 square;
    f32 scaled;
    f32 bias;
    float new_var;
    s32 result;
    if ((arg0 != 0) && (arg0 == 1))
    {
        state = &D_82508790;
        value = *state;
        scaled = D_80088E50[value >> 4];
        sample = scaled;
        new_var = 255.0f;
        square = sample * sample;
        scaled = square * new_var;
        bias = (scaled > 0.0f) ? (0.5f) : (-0.5f);
        result = (s32) (bias + scaled);
        arg1[0x33] = result;
        arg1[0x2F] = result;
        new_var2 = value;
        *((0, state)) = new_var2 + 0x100;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern u16 D_82508794;
extern f32 D_80088E50[];
s32 func_82500120(s32 arg0, u8 *arg1) {
    u16 *state;
    u16 value;
    unsigned int next;
    f32 sample;
    f32 square;
    f32 scaled;
    f32 bias;
    float scale;
    s32 result;
    if ((arg0 != 0) && (arg0 == 1)) {
        state = &D_82508794;
        value = *state;
        scaled = D_80088E50[value >> 4];
        sample = scaled;
        scale = 255.0f;
        square = sample * sample;
        scaled = square * scale;
        bias = (scaled > 0.0f) ? 0.5f : -0.5f;
        result = (s32)(bias + scaled);
        arg1[0x2F] = result;
        arg1[0x2B] = result;
        next = value;
        *((0, state)) = next + 0x100;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s16 D_82508F6C;
s32 func_825001B4(s32 arg0, void *arg1) {
    if (arg0 != 0 && arg0 == 1) {
        if (D_82508F6C != 0) {
            *(u16 *)((u8 *)arg1 + 2) |= 2;
        } else {
            *(u16 *)((u8 *)arg1 + 2) &= 0xFFFD;
        }
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825001F8.s")
#endif

#ifdef VERSION_US
f32 func_825003DC(u32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 *arg5) {
    s32 end1;
    s32 end2;
    s32 phase;
    f32 result;

    end1 = arg1 + arg2;
    end2 = end1 + arg3;
    *arg5 = 0;
    phase = arg0 % (u32)(end2 + arg4);
    if (phase < arg1) {
        result = (f32)phase / (f32)arg1;
    } else if (phase < end1) {
        if (phase == arg1) {
            *arg5 = 1;
        }
        result = 1.0f;
    } else if (phase < end2) {
        result = 1.0f - (f32)(phase - arg1 - arg2) / (f32)arg3;
    } else {
        result = 0.0f;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825004A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82500780.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82500BC0.s")
#endif

#ifdef VERSION_US
extern void *D_82508FA4[];
s32 func_82500CF0(s32 arg0, void *arg1) { s32 index = *(s32 *)((u8 *)arg1 + 0x20); if (arg0 != 0) { if (arg0 != 1) { } } else { D_82508FA4[index] = arg1; } return 0; }
#endif

#ifdef VERSION_US
extern s16 D_82508F94;
extern void *D_82508FAC[];
s32 func_82500D24(s32 arg0, void *arg1) { s32 index = *(s32 *)((u8 *)arg1 + 0x20); switch (arg0) { case 0: D_82508FAC[index] = arg1; break; case 1: *(u8 *)((u8 *)arg1 + 0x2F) = D_82508F94; break; } return 0; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82500D68.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82500EF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82501034.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825010F8.s")
#endif

#ifdef VERSION_US
extern u16 D_82508F88;
extern s16 D_82508F96;
extern s16 D_82508F98;
s32 func_82501244(s32 arg0, void *arg1) { s32 index; u8 *entry; index = *(s32 *)((u8 *)arg1 + 0x20); if ((arg0 != 0) && (arg0 == 1)) { entry = (u8 *)&D_82508F88 + index * 2; if ((*(s16 *)(entry + 0x34) == D_82508F96) && (*(s16 *)(entry + 0x38) == D_82508F98)) { *(u16 *)((u8 *)arg1 + 2) |= 2; } else { *(u16 *)((u8 *)arg1 + 2) &= 0xFFFD; } } return 0; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825012B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82501490.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825015D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82501754.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82501814.s")
#endif

#ifdef VERSION_US
extern void *D_80087200;

void func_82501CDC(void *arg0) {
    if ((*(u16 *)((u8 *)(D_80087200) + (8))) & 0x8000) {
        (*(s16 *)((u8 *)(arg0) + (4))) = 3;
        (*(s16 *)((u8 *)(arg0) + (6))) = 0;
        (*(s16 *)((u8 *)(arg0) + (8))) = 0;
        (*(s16 *)((u8 *)(arg0) + (0xC))) = 0xFF;
        (*(s16 *)((u8 *)(arg0) + (0xA))) = 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82501D18.s")
#endif

#ifdef VERSION_US
extern void func_82501814(u16 *);
extern void func_82501D18(u16 *);
void func_82508268(void);
extern s16 D_82508F8C;
extern u16 D_82508F88;
void func_8250202C(void) {
    func_82508268();
    switch (D_82508F8C) {                           /* irregular */
    case 1:
        func_82501814(&D_82508F88);
        return;
    case 2:
        func_82501CDC(&D_82508F88);
        return;
    case 3:
        func_82501D18(&D_82508F88);
        return;
    }
}
#endif

#ifdef VERSION_US
extern s16 D_82508F8C;
extern u16 D_82508F88;
extern s32 D_82508F9C[];
extern void func_8250850C(void);
extern s32 func_8250865C(void);
extern void func_800503A4(s32);
void func_825020A8(void) { u32 index; if (D_82508F8C != 0) { func_8250850C(); if (func_8250865C() != 0) { index = D_82508F88 & 0xFF; func_800503A4(D_82508F9C[index]); } } }
#endif

#ifdef VERSION_US

s32 func_82502104(void) {
    return D_82508F8C == 0;
}
#endif

#ifdef VERSION_US
s32 func_82502114(void) {
    return D_82508F88;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502120.s")
#endif

#ifdef VERSION_US
extern void *D_82508680;
s32 func_82502404(s16 *arg0, s16 *arg1, s32 arg2, u16 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 result;
    s32 enabled;
    s32 i;
    s32 mask;
    s32 bit;

    result = 0;
    enabled = 0;
    switch (arg2) {
        case 2:
            if (arg5 == 0) {
                result = 1;
            } else if (*(s16 *)((u8 *)D_82508680 + 2) == 0xE) {
                result = 1;
            }
            if (arg6 == 0xE) {
                enabled = 1;
            } else {
                enabled = result;
            }
            break;
        case 3:
            if (arg6 == 0x18) {
                result = 1;
                mask = arg3;
                for (i = 0; i < 8; i++) {
                    bit = 1 << i;
                    if (!(mask & bit)) {
                        result = 0;
                        break;
                    }
                }
            } else {
                result = 1;
                mask = arg3;
            }
            bit = 1 << arg5;
            enabled = (mask & bit) != 0;
            break;
        case 1:
            if (arg5 == 0) {
                result = 1;
            } else {
                result = (arg3 & (1 << (arg5 - 1))) != 0;
            }
            enabled = result;
            break;
    }
    *arg0 = result;
    *arg1 = enabled;
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502528.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502634.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502854.s")
#endif

#ifdef VERSION_US
s16 func_825028E8(u8 *arg0)
{
  s16 var_v1;
  u8 new_var;
  int new_var2;
  var_v1 = -1;
  if (arg0 != (0 & 0xFFFFFFFFFFFFFFFF))
  {
    new_var = *arg0;
    new_var2 = new_var * 0x98;
    var_v1 = (*((u8 *) (((u8 *) (arg0 + new_var2)) + (-0x94)))) - 1;
  }
  return var_v1;
}
#endif

#ifdef VERSION_US
s16 func_82502924(u8 *arg0) {
    s16 result = -1;
    u8 index;
    u32 offset;

    if (arg0) {
        index = *arg0;
        offset = index * 0x98;
        result = *(u8 *)(arg0 + offset - 0x93) - 1;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502960.s")
#endif

#ifdef VERSION_US
s32 func_82502DDC(void *arg0, s32 arg1, u16 arg2)
{
  void *new_var;
  s32 result = 0;
  s32 i = 0;
  u8 *p;
  new_var = arg0;
  if (arg1 > 0)
  {
    p = new_var;
    scan:
    if (arg2 == (*((s16 *) (p + 0x26))))
    {
      result = i;
      goto done;
    }

    i++;
    p += 0x30;
    if (i != arg1)
    {
      goto scan;
    }
  }
  done:
  return result;
}
#endif

#ifdef VERSION_US
s32 func_82502E20(void *arg0, s32 arg1, s32 arg2)
{
  s32 result = 0;
  s16 *new_var;
  s32 i;
  for (i = 0; i < arg1; i++)
  {
    if (1)
    {
    }
    if (arg2 == ((*(new_var = &(*((s16 *) ((((u8 *) arg0) + (i * 0x30)) + 0x26))))) ^ 0))
    {
      result = i + 1;
      break;
    }
  }
  return result;
}
#endif

#ifdef VERSION_US
s32 func_82502E60(s32 arg0, s32 arg1, s32 arg2, void *arg3, u16 arg4) {
    s32 result = 0;
    if (arg0 == 1 && arg2 != -1) {
        if (arg1 < 9) {
            if (*(s16 *)((u8 *)(arg1 * 0x3C + 0x3C) + (u32)arg3) == 0) result = 1;
        } else if ((arg4 & 1) == 0) { result = 1; }
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502EBC.s")
#endif

void func_82503748(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82503750.s")
#endif

#ifdef VERSION_US
extern void func_80008648();
extern void func_800088DC();
extern void func_800503A4(s32);
extern void func_81700908();
extern void func_825020A8();
extern void func_82503750();
extern void func_8250771C();
s32 func_8250865C();
extern s32 D_82508D04;

void func_82503840(void) {
    func_800088DC();
    if (func_8250865C() == 0) {
        func_82503750();
        func_800503A4(D_82508D04);
        func_8250771C();
        func_81700908();
    }
    func_825020A8();
    func_80008648();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825038A4.s")
#endif

#ifdef VERSION_US
extern u8 D_82508D10[];
s32 func_82503954(s32 arg0) {
    s32 result = arg0;
    if ((arg0 >= 0) && (*(s16 *)(D_82508D10 + arg0 * 0x3C) == 0)) {
        result = -1;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82503988.s")
#endif

#ifdef VERSION_US
s32 func_82503DDC(void)
{
  s32 sp1C;
  u16 temp_v0;
  sp1C = 0;
  if (func_82507BBC() == 0)
  {
    return 0;
  }
  ;
  if ((*((u16 *) (((u8 *) D_80087200) + 8))) & 0x8000)
  {
    sp1C = 1;
  }
  else
    if ((*((u16 *) (((u8 *) D_80087200) + 8))) & 0x4000)
  {
    func_82507BD0();
    sp1C = -1;
    func_800226C0(3);
  }
  return sp1C;
}
#endif

#ifdef VERSION_US
extern s32 func_82502104(void);
extern s32 func_82502114(void);
s32 func_82503E50(void) { s32 result; result = 0; if (func_82502104() != 0) { if (func_82502114() == 0x201) { result = 2; } else { result = 1; } } return result; }
#endif

#ifdef VERSION_US
extern s32 func_82507CF4();
s32 func_82503E98(void) {
    s32 result = 0;
    if (func_82507CF4() != 0) {
        result = 1;
    }
    return result;
}
#endif

#ifdef VERSION_US
s32 func_82503EC8(void) {
    s32 result = 0;
    if (func_82507CF4() != 0) {
        result = 1;
    }
    return result;
}
#endif

#ifdef VERSION_US
s32 func_82503EF8(void) {
    s32 result = 0;
    if (func_82507CF4() != 0) {
        result = 1;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82503F28.s")
#endif

#ifdef VERSION_US
extern s16 D_82508F72;
extern void func_8004C09C();
extern void func_8004C4B0();
extern void func_8004C398();
extern void func_80008624();
extern void func_800086A4();
extern s32 StageContext_GetFadeMode(void);
extern void StageFade_StartFromOpaque();
extern void StageLoader_WaitForRetrace(void);
extern void func_80064D28();
extern void func_8170024C();
extern void func_825075B0();
extern void func_82502EBC();
extern s32 func_82503F28();
extern void func_8250202C(void);
extern void func_82503840(void);
s32 func_825043AC(s32 arg0, s32 arg1) {
    s32 state = 0;
    s32 result;

    func_8004C09C(0x147);
    func_8004C4B0(0x31);
    func_8004C4B0(0x29);
    func_8004C4B0(0x2A);
    func_82502EBC(arg0, arg1);
    func_80008624();
    if (StageContext_GetFadeMode() != 0) {
        func_800086A4(2);
        StageFade_StartFromOpaque(5);
    }
    do {
        func_80064D28();
        func_825075B0();
        func_8170024C();
        func_8250202C();
        func_82503840();
        state = func_82503F28(state, arg1);
    } while (state != 9);
    StageLoader_WaitForRetrace();
    switch (D_82508F72) {
        case 1:
        case 2:
        case 3:
        case 4:
            result = D_82508F72;
            break;
        default:
            result = 5;
            break;
    }
    func_8004C398();
    func_800226C0(0x122);
    return result;
}
#endif

#ifdef VERSION_US
extern void Fragment_LoadAndCall(s32, s32 *, s32 *, s32, s32);
s32 func_800718B8(s32);
extern u8 D_82C00000;
extern u8 fragment83_ROM_START;
extern u8 fragment84_ROM_START;

void func_825044D0(void) {
    Fragment_LoadAndCall(((u32) ((s32) &D_82C00000 & 0x0FF00000) >> 0x14) - 0x10, &fragment83_ROM_START, &fragment84_ROM_START, 0x300, func_800718B8(6));
}
#endif

#ifdef VERSION_US
extern void *D_82508680;
extern u8 D_82508F68[];
extern s16 D_82508F6A;
void func_82504524(void) {
    u8 *state;
    u8 *node;
    u8 *entry;
    state = D_82508F68;
    node = *(u8 **)(state + 0x1C);
    entry = *(s16 *)(state + 2) * 0x30 + *(u8 **)(node + 0x1C);
    *(s16 *)((u8 *)D_82508680 + 8) = *(s16 *)state;
    switch (*(s16 *)((u8 *)D_82508680 + 8)) {
        case 1:
            *(s16 *)((u8 *)D_82508680 + 0xA) = D_82508F6A;
            if (*(s16 *)(entry + 0x20) != -1) {
                *(s16 *)((u8 *)D_82508680 + 0xA) -= 1;
                if (*(s16 *)((u8 *)D_82508680 + 0xA) < 0) {
                    *(s16 *)((u8 *)D_82508680 + 0xA) = 0;
                }
            }
            break;
        case 3:
            *(s16 *)((u8 *)D_82508680 + 0xC) = D_82508F6A;
            break;
        case 2:
            *(s16 *)((u8 *)D_82508680 + 0xE) = D_82508F6A;
            break;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825045EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82504628.s")
#endif
