#include "global.h"


#ifdef VERSION_US
extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void func_800355E4(s32);
extern void Fragment_Load(s32, void *, void *);
extern s32 Fragment_LoadAndCall(s32, void *, void *, u32, u32);
extern s32 Game_SetState(s32);
extern u8 D_88000000;
extern u8 D_88B00000;
extern u8 fragment29_ROM_START;
extern u8 fragment30_ROM_START;
extern u8 fragment40_ROM_START;
extern u8 fragment41_ROM_START;
void func_80069E80(void) {
    main_pool_push_state(0x70727374);
    func_800355E4(0x44);
    Fragment_Load(((u32) ((s32) &D_88000000 & 0x0FF00000) >> 20) - 0x10, &fragment29_ROM_START, &fragment30_ROM_START);
    Fragment_LoadAndCall(((u32) ((s32) &D_88B00000 & 0x0FF00000) >> 20) - 0x10, &fragment40_ROM_START, &fragment41_ROM_START, 0, 0);
    main_pool_pop_state(0x70727374);
    Game_SetState(2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_80069F20.s")

extern void func_80069F20();
void BattleScene_ResetParticipantModelFlags(s32 arg0) { func_80069F20(arg0, 0, 0); }

extern void func_80069F20(void); void func_8006A160(void) { func_80069F20(); }

extern s32 D_8009DF70;
extern void _bzero(void *, s32);
void func_8006A180(void) {
    u8 *ptr;
    if (D_8009DF70 != 0) {
        ptr = *(u8 **)((u8 *)(u32)D_8009DF70 + 0x24);
        if (ptr != NULL) {
            _bzero(ptr, 0x958);
            *(s8 *)(*(u8 **)((u8 *)(u32)D_8009DF70 + 0x24) + 0x93C) = -1;
            *(s8 *)(*(u8 **)((u8 *)(u32)D_8009DF70 + 0x24) + 0x93D) = -1;
            *(s8 *)(*(u8 **)((u8 *)(u32)D_8009DF70 + 0x24) + 0x93E) = -1;
            *(s8 *)(*(u8 **)((u8 *)(u32)D_8009DF70 + 0x24) + 0x93F) = -1;
        }
    }
}

extern void *main_pool_alloc(s32, s32);
typedef struct NodeA1FC { s32 pad0; s32 next; s32 value; } NodeA1FC;
NodeA1FC *func_8006A1FC(s32 arg0) {
    NodeA1FC *result = NULL;
    if (D_8009DF70 != 0) {
        result = main_pool_alloc(0xC, 0);
        if (result != NULL) {
            _bzero(result, 0xC);
            result->next = *(s32 *)((u8 *)(u32)D_8009DF70 + 0x1C);
            result->value = arg0;
            *(NodeA1FC **)((u8 *)(u32)D_8009DF70 + 0x30) = result;
        }
    }
    return result;
}

typedef struct InitA278 { u8 pad0[4]; s16 value4; s16 value6; s16 value8; } InitA278;
InitA278 *func_8006A278(void) {
    InitA278 *result = NULL;
    if (D_8009DF70 != 0) {
        result = main_pool_alloc(0x50, 0);
        if (result != NULL) {
            *(InitA278 **)((u8 *)(u32)D_8009DF70 + 0x34) = result;
            _bzero(result, 0x50);
            result->value4 = 1;
            result->value6 = 0xF;
            result->value8 = 0x1E;
        }
    }
    return result;
}

extern s32 D_8009DF70; void func_8006A2EC(void) { D_8009DF70 = 0; }

extern s32 D_8009DF70; s32 func_8006A2F8(u16 value){s32 result=0; s32 ptr=D_8009DF70; if(ptr!=0){*(u16 *)((u8 *)(u32)ptr+4)|=value; result=1;} return result;}

extern s32 D_8009DF70; s32 func_8006A328(u16 value){s32 result=0; s32 ptr=D_8009DF70; if(ptr!=0){*(u16 *)((u8 *)(u32)ptr+4)&=~value; result=1;} return result;}

s32 func_8006A35C(u16 value) { s32 result = 0; if (D_8009DF70 != 0) result = ((*(u16 *)((u8 *)(u32)D_8009DF70 + 4) & value) != 0); return result; }

s32 func_8006A388(void) { s32 result = 0; if (D_8009DF70 != 0 && (*(u16 *)((u8 *)(u32)D_8009DF70 + 4) & 1) != 0) result = 1; return result; }

s32 func_8006A3B8(u16 arg0) { s32 result = 0; if (D_8009DF70 != 0) { *(u16 *)((u8 *)(u32)D_8009DF70) = arg0; result = 1; } return result; }

s32 func_8006A3E0(void) { s32 result = 0xFFFF; if (D_8009DF70 != 0) result = *(u16 *)((u8 *)(u32)D_8009DF70); return result; }

s32 func_8006A400(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s16 *)((u8 *)(u32)D_8009DF70 + 2) = value; result = 1; } return result; }

s32 func_8006A424(void) { s32 result = 0; s32 ptr = D_8009DF70; if (ptr != 0) result = *(s16 *)((u8 *)(u32)ptr + 2); return result; }

s32 func_8006A444(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s16 *)((u8 *)(u32)D_8009DF70 + 6) = value; _bzero((u8 *)(u32)D_8009DF70 + 0x3C, 0x44); result = 1; } return result; }

s32 func_8006A48C(void) { s32 result = -1; s32 ptr = D_8009DF70; if (ptr != 0) result = *(s16 *)((u8 *)(u32)ptr + 6); return result; }

typedef struct CopyA4AC { s32 words[17]; } CopyA4AC;
s32 func_8006A4AC(void *arg0) {
    s32 result = 0;
    if ((D_8009DF70 != 0) && (arg0 != NULL)) {
        *(s16 *)((u8 *)(u32)D_8009DF70 + 6) = 0xE;
        *(CopyA4AC *)((u8 *)(u32)D_8009DF70 + 0x3C) = *(CopyA4AC *)arg0;
        result = 1;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A51C.s")

s32 func_8006A5AC(s32 arg0) {
    s32 result = -1;
    switch (arg0) {
    case 1: result = 0; break;
    case 2: result = 1; break;
    case 3: result = 2; break;
    case 4: result = 3; break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A600.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A73C.s")

extern void func_8006A73C(s32);
void func_8006AB68(s32 arg0) { s32 *p = &arg0; func_8006A73C(arg0 & 0xFFFF); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AB8C.s")

s32 func_8006ABD8(void *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (D_8009DF70 != 0) {
        var_v1 = 1;
        (*(s8 *)((u8 *)(D_8009DF70) + (8))) = (s8) (*(s32 *)((u8 *)(arg0) + (0)));
        (*(s8 *)((u8 *)(D_8009DF70) + (9))) = (s8) (*(s32 *)((u8 *)(arg0) + (4)));
        (*(s8 *)((u8 *)(D_8009DF70) + (0xA))) = (s8) (*(s32 *)((u8 *)(arg0) + (8)));
        (*(s8 *)((u8 *)(D_8009DF70) + (0xB))) = (s8) (*(s32 *)((u8 *)(arg0) + (0xC)));
    }
    return var_v1;
}

s32 func_8006AC28(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s32 *)((u8 *)(u32)D_8009DF70 + 0xC) = value; result = 1; } return result; }

s32 func_8006AC4C(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s16 *)((u8 *)(u32)D_8009DF70 + 0x12) = value; result = 1; } return result; }

s32 func_8006AC70(void) { s32 result = -1; s32 ptr = D_8009DF70; if (ptr != 0) result = *(s16 *)((u8 *)(u32)ptr + 0x12); return result; }

extern s32 func_8006CBA0(s32, s32);
s32 func_8006AC90(void) { s32 result = 0; s32 ptr = D_8009DF70; if (ptr != 0) result = func_8006CBA0(*(s16 *)((u8 *)(u32)ptr + 0x12), *(s16 *)((u8 *)(u32)ptr + 0x16)); return result; }

s32 func_8006ACCC(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s16 *)((u8 *)(u32)D_8009DF70 + 0x16) = value; result = 1; } return result; }

s32 func_8006ACF0(void) { s32 result = 0; s32 ptr = D_8009DF70; if (ptr != 0) result = *(s16 *)((u8 *)(u32)ptr + 0x16); return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AD10.s")

s32 func_8006AE90(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s16 *)((u8 *)(u32)D_8009DF70 + 0x14) = value; result = 1; } return result; }

s32 func_8006AEB4(void) { s32 result = -1; s32 ptr = D_8009DF70; if (ptr != 0) result = *(s16 *)((u8 *)(u32)ptr + 0x14); return result; }

typedef struct U4A { u8 bytes[4]; } U4A;
s32 func_8006AED4(s32 arg0, void *arg1) {
    s32 base;
    s32 result = 0;
    if (D_8009DF70 != 0) {
        base = (s32)*(s32 *)((u8 *)(u32)D_8009DF70 + 0x1C);
        if (base != 0) {
            *(U4A *)((u8 *)(u32)base + arg0 * 0x4E0 + 0x498) = *(U4A *)arg1;
            result = 1;
        }
    }
    return result;
}

typedef struct U4F { u8 bytes[4]; } U4F;
s32 func_8006AF28(s32 arg0, void *arg1) {
    s32 base;
    s32 result = 0;
    u8 *dst;
    if (D_8009DF70 != 0) {
        base = (s32)*(s32 *)((u8 *)(u32)D_8009DF70 + 0x1C);
        if (base != 0) {
            dst = (u8 *)(u32)base + arg0 * 0x4E0;
            *(U4F *)(dst + 0x498) = *(U4F *)arg1;
            dst[0x11] = 1;
            result = 1;
        }
    }
    return result;
}


s32 func_8006AF84(void) {
    return *(s32 *)((u8 *)(u32)D_8009DF70 + 0x1C);
}

s32 func_8006AF94(void) { s32 result = -1; s32 ptr = D_8009DF70; if (ptr != 0) result = *(s16 *)((u8 *)(u32)ptr + 0x10); return result; }

s32 func_8006AFB4(s32 arg0) {
    s32 result;
    s32 value = 1;
    if ((arg0 != 0x45) && (arg0 != 0x46) && (arg0 != 0x47)) {
        result = 0;
    } else {
        result = value;
    }
    return result;
}

void func_8006AFE4(s8 *arg0, s8 *arg1) {
    s32 found = 0;
    s32 i = 0;
    s8 *ptr = arg0;
    s8 value;
    do {
        i++;
        *ptr = -2;
        ptr++;
    } while (i < 4);
    i = 0;
    ptr = arg1;
    do {
        value = *ptr;
        i++;
        if (value >= 0) {
            arg0[value] = value;
        } else if (value == -1) {
            found = 1;
        }
        ptr++;
    } while (i < 4);
    i = 0;
    if (found != 0) {
        ptr = arg0;
loop:
        i++;
        if (*ptr == -2) {
            *ptr = -1;
            return;
        }
        ptr++;
        if (i != 4) goto loop;
    }
}

s32 func_8006B07C(s8 *arg0) {
    s32 result = -1;
    s32 sentinel = -1;
    s32 i = 0;
    for (i = 0; i < 4; i++) {
        if (*(s8 *)((u8 *)arg0 + i) == sentinel) {
            result = i;
            break;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B0B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B428.s")

s32 func_8006B790(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(u8 *)((u8 *)(u32)D_8009DF70 + 0x1A) = value; result = 1; } return result; }

s32 func_8006B7B4(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(u8 *)((u8 *)(u32)D_8009DF70 + 0x1B) = value; result = 1; } return result; }

s32 func_8006B7D8(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s16 *)((u8 *)(u32)D_8009DF70 + 0x18) = value; result = 1; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B7FC.s")

s32 func_8006B854(s32 arg0, s32 arg1) {
    s32 high;
    s32 low;
    s32 result;

    high = arg0 & 0xFF00;
    result = -1;
    switch (high) {
    case 0x200:
        low = arg0 & 0xFF;
        if (arg1 == 5) {
            result = 0;
        } else {
            switch (low) {
            case 0:
                result = 1;
                break;
            case 1:
                result = 2;
                break;
            case 3:
                result = 3;
                break;
            }
        }
        break;
    case 0:
    case 0x100:
        low = arg0 & 0xFF;
        switch (low) {
        case 0:
            result = 1;
            break;
        case 1:
            result = 2;
            break;
        case 3:
            result = 3;
            break;
        }
        break;
    case 0x300:
        result = 4;
        break;
    case 0x600:
        result = 5;
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B928.s")

void func_8006BA74(u8 *arg0) {
    s32 i;
    u8 *ptr;
    if (arg0 != NULL) {
        _bzero(arg0, 0x490);
        ptr = arg0;
        i = 0;
        do {
            i++;
            ptr += 0x1DC;
            ptr[-0x1DC] = 0x50;
            ptr[-0x1CF] = 0x50;
        } while (i != 2);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006BAC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006BF78.s")

extern void func_8006BF78(s32); void func_8006C58C(void) { func_8006BF78(0); }

extern void _bcopy(void *, void *, s32);
void func_8006C5AC(s32 arg0, void *arg1, s32 arg2, s32 arg3)
{
  void *base;
  void *temp;
  if (D_8009DF70 != 0)
  {
    base = *((void **) (((u8 *) ((u32) D_8009DF70)) + 0x2C));
    temp = ((u8 *) base) + arg0;
    if (((base != 0) && (arg0 >= 0)) && (arg0 < 4))
    {
      _bcopy(arg1, (((u8 *) (*((void **) (((u8 *) ((u32) D_8009DF70)) + 0x2C)))) + (arg0 * 0x16)) + 0x1C, 0x16);
      temp = ((u8 *) base) + arg0;
      if (1)
      {
        *((s8 *) (((u8 *) temp) + 0x74)) = arg2;
      }
      *((s8 *) (((u8 *) temp) + 0x78)) = arg3;
    }
  }
}

extern void func_8006BF78(s32); void func_8006C644(void) { func_8006BF78(1); }

extern s32 func_800718B8(s32);
extern void func_80073208(void *, s32);
void *func_8006C664(void) {
    u8 *result = NULL; volatile s32 *globalp = &D_8009DF70;
    s32 linked; s32 state;  s16 kind;
    state=*globalp;
    if(state!=0){
        result=*(u8 **)((u8 *)(u32)state+0x1C);
        result[0x9C2]=*(u8 *)((u8 *)(u32)state+0x1A);
        state=*globalp; linked=*(s32 *)((u8 *)(u32)state+0x20);
        if(linked!=0){*(s32 *)(result+0x9D8)=linked+0x3B8; state=*globalp;}
        kind=*(s16 *)((u8 *)(u32)state+6);
        if(kind!=0xE) *(s32 *)(result+0x9D4)=func_800718B8(kind);
        else *(s32 *)(result+0x9D4)=state+0x3C;
        if(result[0x9C2]==2){func_80073208(result, *(s32 *)((u8 *)(u32)*globalp + 0x20));}
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006C714.s")

extern void main_pool_try_free(void);
void func_8006C9C0(void) { main_pool_try_free(); if (D_8009DF70 != 0) *(s32 *)((u8 *)(u32)D_8009DF70 + 0x38) = 0; }

void *func_8006C9F4(void) { void *result = main_pool_alloc(0x440, 0); if (result != NULL) _bzero(result, 0x440); return result; }

extern void main_pool_try_free(void); void func_8006CA34(void) { main_pool_try_free(); }

typedef struct SmallCA54 { s16 flag; s8 value; u8 pad3; } SmallCA54;
SmallCA54 *func_8006CA54(s32 arg0) {
    SmallCA54 *result = main_pool_alloc(4, 0);
    if (result != NULL) {
        _bzero(result, 4);
        if (D_8009DF70 != 0) {
            result->flag = ((*(u16 *)((u8 *)(u32)D_8009DF70 + 4) & 1) != 0);
            result->value = arg0;
        }
    }
    return result;
}

extern void main_pool_try_free(void); void func_8006CAC0(void) { main_pool_try_free(); }

typedef struct InitCAE0 {
    s16 flag;
    s16 value4;
    u16 value5;
    u16 pad6;
    s16 value0;
    s16 value1;
    s16 value2;
    s16 value3;
} InitCAE0;
InitCAE0 *func_8006CAE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5) {
    InitCAE0 *result = main_pool_alloc(0x10, 0);
    if (result != NULL) {
        _bzero(result, 0x10);
        if (D_8009DF70 != 0) {
            result->flag = ((*(u16 *)((u8 *)(u32)D_8009DF70 + 4) & 1) != 0);
            result->value4 = (s16)arg4;
            result->value5 = (u16)arg5;
            result->value0 = (s16)arg0;
            result->value1 = (s16)arg1;
            result->value2 = (s16)arg2;
            result->value3 = (s16)arg3;
        }
    }
    return result;
}

extern void main_pool_try_free(void); void func_8006CB80(void) { main_pool_try_free(); }

s32 func_8006CBA0(s32 a,s32 b){s32 result=0; s32 next=a+1; if(b==next)result=1; return result;}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CBB8.s")

extern s16 D_8009DF74; void func_8006CBFC(void) { D_8009DF74 = 1; }

extern s16 D_8009DF74; void func_8006CC0C(void) { D_8009DF74 = 0; }

extern void *Util_Malloc(s32);
extern void Util_Free(void *);
extern void _bcopy(void *, void *, s32);
extern void func_80054B7C();
extern void func_80051D64(s32, s32);
typedef struct PacketCC18B {
    u16 value0;
    s16 value2;
    s8 flag4;
    s8 value5;
    s8 value6;
    s8 value7;
    u16 value8;
    u8 copyA[12];
    u8 tail16;
} PacketCC18B;
typedef struct CopyCC18Phase2B { s32 words[22]; } CopyCC18Phase2B;
s32 func_8006CC18(s32 arg0, s32 arg1) {
    s32 result;
    u8 pad[8];
    PacketCC18B packet;
    u8 *buffer;
    s32 count;
    s32 offset;
    u8 *src;
    result = 0;
    if (D_8009DF70 != 0) {
        buffer = Util_Malloc(0x210);
        result = 1;
        packet.value0 = *(u16 *)((u8 *)(u32)D_8009DF70);
        packet.value2 = *(s16 *)((u8 *)(u32)D_8009DF70 + 2);
        packet.flag4 = ((*(u16 *)((u8 *)(u32)D_8009DF70 + 4) & 1) != 0);
        if (arg0 != 0) packet.value5 = *(s16 *)((u8 *)(u32)D_8009DF70 + 0x12) + 1;
        else packet.value5 = *(s16 *)((u8 *)(u32)D_8009DF70 + 0x12);
        packet.value6 = arg1;
        packet.value7 = *(s16 *)((u8 *)(u32)D_8009DF70 + 0x16);
        packet.value8 = *(u16 *)(*(u8 **)((u8 *)(u32)D_8009DF70 + 0x24) + 0x934);
        _bcopy(*(u8 **)((u8 *)(u32)D_8009DF70 + 0x24) + 0x904, packet.copyA, 0xC);
        count = 0;
        offset = 0;
        packet.tail16 = *(u8 *)(*(u8 **)((u8 *)(u32)D_8009DF70 + 0x24) + 0x955);
        do {
            src = *(u8 **)((u8 *)(u32)D_8009DF70 + 0x24) + offset;
            offset += 0x60;
            if (*src != 0) {
                ((CopyCC18Phase2B *)buffer)[count] = *(CopyCC18Phase2B *)src;
                count++;
            }
        } while (offset != 0x240);
        func_80054B7C(&packet, buffer, count);
        func_80051D64(0x15, 0);
        Util_Free(buffer);
    }
    return result;
}

typedef struct CopyCDA0C { s32 words[22]; } CopyCDA0C;
s32 func_8006CDA0(u8 *arg0,u8 *arg1) {
 s32 result=0; s32 offset; u8 *src; u8 *dst;
 if(D_8009DF70!=0) {
  result=1; func_8006A3B8(*(u16 *)arg0); func_8006A400(*(s16 *)(arg0+2));
  if(arg0[4]!=0) func_8006A2F8(1); else func_8006A328(1);
  func_8006AC4C(arg0[5]); func_8006B7D8(arg0[6]);
  *(u16 *)(*(u8 **)((u8 *)(u32)D_8009DF70+0x24)+0x934)=*(u16 *)(arg0+8);
  _bcopy(arg0+0xA,*(u8 **)((u8 *)(u32)D_8009DF70+0x24)+0x904,0xC);
  *(u8 *)(*(u8 **)((u8 *)(u32)D_8009DF70+0x24)+0x955)=arg0[0x16];
  src=arg1;
  for(offset=0; offset!=0x240; offset+=0x60) {
            dst=*(u8 **)((u8 *)(u32)D_8009DF70+0x24)+offset;
            _bzero(dst,0x60);
            *(CopyCDA0C *)dst=*(CopyCDA0C *)src;
            src+=0x58;
        }
 }
 return result;
}

s32 func_8006CEE8(u16 arg0) {
 u16 high; s32 value; s32 low; s32 result; u16 *home=&arg0;
 high=arg0;
 value=high;
 result=-1;
 high&=0xFF00;
 switch(high){
 case 0:
  low=(u16)value; low&=0xFF;
  switch(low){case 0:result=0x55;break;case 1:result=0x53;break;case 2:result=0x54;break;case 3:result=0x56;break;}
  break;
 case 0x300:result=0x5E;break;
 }
 return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CF70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006D068.s")
#endif
