#include "global.h"

#ifdef VERSION_US
extern void func_80021ED8(s32);
extern u8 D_800D2B58;
extern void GbAudio_UpdateSquare1Registers(u8);
/* Stadium 1 transfer helper: allocates a typed block from the supplied pool. */
extern void *MainPool_AllocAligned(void *, size_t, s32);
extern Vtx *func_800398F8();
#endif


#ifdef VERSION_US
extern unsigned char D_80090137[0x100];
extern unsigned char D_800917F8[0x100];
f32 func_80021DE0(s32 arg0) {
    u8 value = D_80090137[arg0];
    if (value >= 0x80) {
        value = D_800917F8[value & 0x7F];
        value = (u32)(f32)value;
    }
    return (f32)value / 127.0f;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80021ED8.s")
#endif

#ifdef VERSION_US
extern void func_800187AC();
extern s8 D_8009019C;
extern s8 D_800901A0;
extern s8 D_800901A4;
extern void func_80018728(u32, ...);

void func_800225C4(s32 arg0) {
    func_80018728(0x83000000U, arg0 * 3, arg0);
    func_800187AC();
    D_8009019C = 0;
    D_800901A0 = 0;
    D_800901A4 = 0;
}
#endif

#ifdef VERSION_US
void func_8002260C(s32 arg0, s32 arg1) {
    func_80018728(0x82000100, 0);
  }
#endif

#ifdef VERSION_US
s32 func_8002263C(void) {
    return 0x61;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80022644.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800226C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80023110.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800231A0.s")
#endif

#ifdef VERSION_US
extern s8 D_80090220;
extern s32 D_8009022C;
extern s8 D_80090B80;
void func_800238C4(void) {
    if (D_80090B80 == 2) {
        D_80090220 = 0;
        func_80018728(0x83010000U, 0xB4);
        D_8009022C = -1;
    }
}
#endif

#ifdef VERSION_US
void func_8002390C(s32 arg0) {
    if (D_80090B80 == 2) {
        D_80090220 = 0;
        func_80018728(0x83010000U, arg0);
        D_8009022C = -1;
    }
}
#endif

#ifdef VERSION_US
extern void func_8001874C(s32, s8);
void func_80023954(void) {
    func_8001874C(0x06010005, 1);
}
#endif

#ifdef VERSION_US
extern u8 D_80090200[];
/* Returns the selected mask bit, not a normalized boolean. */
u8 Audio_GetSpeciesMaskBit(u32 species) {
    u8 value;
    u8 bit;
    u8 mask;
    value = D_80090200[(u8)((species - 1) >> 3)];
    bit = (species - 1) & 7;
    mask = 1 << (7 - bit);
    value &= mask;
    return value;
}
#endif

#ifdef VERSION_US
extern s32 D_80090224, D_80090228;

void func_800239B4(s32 arg0, s32 arg1) {
    D_80090224 = arg0;
    D_80090228 = arg1;
}
#endif

#ifdef VERSION_US
void func_800239C8(void) {
    if (D_80090224 >= 0) {
        D_80090224--;
        if (D_80090224 < 0) {
            func_8002390C(D_80090228);
            D_80090228 = 0;
        }
    }
}
#endif

#ifdef VERSION_US
extern s32 D_8009061C[][4];
s32 func_80023A10(u8 arg0, u8 arg1) {
    return D_8009061C[arg0][arg1];
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80023A3C.s")
#endif

#ifdef VERSION_US
void func_80024180(u32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
    case 26:
    case 27:
    case 28:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
        func_8001874C(0x06020005, 1);
        return;
    case 30:
    case 35:
        func_8001874C(0x06020105, 1);
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002421C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024480.s")
#endif

#ifdef VERSION_US
s32 func_80024864(void) {
    extern s32 func_80019230(s32, s32, s32);
    if (func_80019230(4, 0, 0) != 0) {
        return 1;
    }
    return 0;
}
#pragma C_FUNCTION_PADDING(8)
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800248A0.s")
#endif

#ifdef VERSION_US
void func_800248EC(void *arg0) {
    u8 count = *(u8 *)arg0;
    u32 *ptr = (u32 *)((u8 *)arg0 + 4);
    u32 i = 0;
    while (i < count) {
        *ptr += (u32)arg0;
        i++;
        ptr++;
    }
    *((u8 *)arg0 + 1) = 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024974.s")
#endif

#ifdef VERSION_US
extern s8 D_80090A54;

void func_80024D10(s32 arg0) {
    D_80090A54 = 0;
    func_80018728(0x83030000U, arg0 * 3, arg0);
}
#endif

#ifdef VERSION_US
extern s32 D_80090A50;
extern u8 D_80090A74[2];
extern s8 D_80090A78;

void func_80024D44(void) {
    D_80090A50 = 0;
    (*(s8 *)((u8 *)(&D_80090A74) + (0))) = 0;
    (*(s8 *)((u8 *)(&D_80090A74) + (1))) = 0;
    D_80090A78 = -1;
}
#endif

#ifdef VERSION_US
extern s32 func_80024E30(u32);
extern u8 D_80090A7C;
typedef struct {
    u8 ids[2];
    u8 unknown02[2];
    s8 active;
    u8 unknown05[3];
    u8 lastSlot;
    u8 unknown09[3];
} AudioResourceCacheView;
s32 Audio_GetOrCacheResourceId(u32 id) {
    s32 found;
    s32 slot;
    u8 replacement;
    AudioResourceCacheView *cache;
    if ((id == 0 || id >= 0xFC) && id != 0x12C) { return -1; }
    found = func_80024E30(id);
    if (found == 0 || found == 1) { return found; }
    cache = (AudioResourceCacheView *)D_80090A74;
    for (slot = 0; slot < 2; slot++) {
        if (cache->ids[slot] == 0) {
            cache->ids[slot] = id;
            return slot;
        }
    }
    replacement = cache->lastSlot ^ 1;
    cache->ids[replacement] = id;
    cache->lastSlot = replacement;
    return replacement;
}

/* Original unreachable jr/nop tail at 0x80024E28. */
void func_80024D6C_padding(void) {}
#endif

#ifdef VERSION_US
s32 func_80024E30(u32 arg0) {
    s32 var_v1;
    u8 *var_v0;

    if (((arg0 == 0) || (arg0 >= 0xFCU)) && (arg0 != 0x12C)) {
        return -1;
    }
    var_v0 = D_80090A74;
    var_v1 = 0;
loop_5:
    if (arg0 == *var_v0) {
        return var_v1;
    }
    var_v1 += 1;
    var_v0 += 1;
    if (var_v1 == 2) {
        return -2;
    }
    goto loop_5;
}
#endif

#ifdef VERSION_US
extern s32 D_80090A80;
extern void func_80024480(s32, s32);

void func_80024E8C(s32 arg0) {
    D_80090A80 = arg0;
    switch (arg0) {
    case 0:
    case 1:
    case 11:
    case 12:
    default:
        return;
    case 2:
        arg0 = 0x100;
        break;
    case 3:
        arg0 = 0x107;
        break;
    case 4:
        arg0 = 0x106;
        break;
    case 5:
        arg0 = 0x102;
        break;
    case 6:
        arg0 = 0x103;
        break;
    case 7:
        arg0 = 0x108;
        break;
    case 8:
        arg0 = 0x105;
        break;
    case 9:
        arg0 = 0x109;
        break;
    case 10:
        arg0 = 0x104;
        break;
    }
    func_80024480(arg0, 0xA);
}
#pragma C_FUNCTION_PADDING(8)
#endif

#ifdef VERSION_US
/* func_80024F20 is still GLOBAL_ASM, but its .s is hand-maintained (not the
 * splat-generated asm/us/nonmatchings/229E0/func_80024F20.s) so that it can
 * also carry 3 extra .late_rodata padding words ahead of jtbl_800A32C0. See
 * the comment in hand_asm/229E0/func_80024F20_manual.s for why. */
#pragma GLOBAL_ASM("hand_asm/229E0/func_80024F20_manual.s")
#endif

#ifdef VERSION_US
extern void func_80018704(s32, s32);
void func_800251F8(s32 arg0) {
    switch (arg0) {
    case 0:
        func_80018728(0x82040700U, 0);
        func_80018704(0x41040000, 0x3F2147AE);
        return;
    case 1:
        func_80018728(0x83040000U, 0);
        return;
    case 2:
        func_80018728(0x83040000U, 0);
        func_80018728(0x82040700U, 0);
        func_80018704(0x41040000, 0x3F2147AE);
        return;
    default:
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025294.s")
#endif

#ifdef VERSION_US
void func_80025848(s32 arg0) {
    switch (arg0) {
    case 42:
        func_8001874C(0x06020005, 1);
        return;
    case 18:
    case 113:
    case 114:
    case 115:
        func_8001874C(0x06020205, 1);
        return;
    case 62:
        func_8001874C(0x06020305, 1);
        return;
    case 65:
        func_8001874C(0x06020405, 1);
        return;
    case 78:
    case 92:
        func_8001874C(0x06020505, 1);
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800258F4.s")
#endif

#ifdef VERSION_US
void Audio_ApplyCommandPreset(s32 preset) {
    s32 first;
    s32 second = 0;
    s32 third = 0;
    s32 fourth = 0;
    switch (preset) {
    case 10:
        first = 22;
        break;
    case 1:
        first = 1;
        second = 4;
        fourth = 3;
        func_8001874C(0x06020400, 21);
        break;
    case 2:
        first = 1;
        second = 6;
        third = 7;
        fourth = 5;
        break;
    case 3:
        first = 1;
        second = 9;
        fourth = 8;
        break;
    case 4:
        first = 1;
        second = 11;
        fourth = 10;
        break;
    case 5:
        first = 1;
        second = 13;
        third = 14;
        fourth = 12;
        break;
    case 6:
        first = 1;
        fourth = 15;
        break;
    case 7:
        first = 1;
        second = 17;
        third = 18;
        fourth = 16;
        break;
    case 8:
        first = 1;
        second = 20;
        fourth = 19;
        break;
    default:
        return;
    }
    func_8001874C(0x06020000, (s8)first);
    func_8001874C(0x06020100, (s8)second);
    func_8001874C(0x06020200, (s8)third);
    func_8001874C(0x06020300, (s8)fourth);
}
#endif

#ifdef VERSION_US
void func_80025ACC(s32 arg0) {
    switch (arg0) {
    case 7:
        func_8001874C(0x06020405, 1);
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 8:
        func_8001874C(0x06020000, 2);
        func_8001874C(0x06020105, 1);
        func_8001874C(0x06020205, 1);
        func_8001874C(0x06020305, 1);
        return;
    }
}
#endif

#ifdef VERSION_US
extern u8 D_80090BA4;
void Audio_SetPreset(s32 preset) {
    u32 bank;
    s32 sound;
    switch (preset) {
    case 1:
        D_80090BA4 = 1;
        bank = 0;
        sound = 1;
        break;
    case 2:
        bank = 1;
        sound = 2;
        break;
    case 3:
        bank = 1;
        sound = 3;
        break;
    case 4:
        bank = 2;
        sound = 4;
        break;
    case 5:
        bank = 2;
        sound = 5;
        break;
    case 6:
        bank = 0;
        sound = 6;
        break;
    case 7:
        bank = 1;
        sound = 7;
        break;
    case 8:
        bank = 1;
        sound = 8;
        break;
    case 9:
        bank = 2;
        sound = 9;
        break;
    case 10:
        bank = 2;
        sound = 10;
        break;
    case 11:
        bank = 2;
        sound = 11;
        break;
    case 12:
        bank = 1;
        sound = 12;
        break;
    default:
        return;
    }
    func_8001874C(0x06030000 | ((u8)bank << 8), (s8)sound);
}
#pragma C_FUNCTION_PADDING(12)
#endif

#ifdef VERSION_US
extern s8 D_80090B90;
void func_80025C50(u32 arg0) {
    if (arg0 < 5U) {
        if (arg0 == 4) {
            D_80090B90 = 1;
        } else {
            D_80090B90 = 0;
        }
        func_80018728(0xF0000000U, arg0);
    }
}
#endif

#ifdef VERSION_US
extern s32 func_80018C14(void);
s32 func_80025C9C(void) {
    return func_80018C14();
}
#endif

#ifdef VERSION_US
extern void func_800315E8();
extern u8 D_80090B9C;
void func_8002B1A0(void);
extern void func_80028140(void);

void func_80025CBC(s32 arg0) {
    s32 temp_s0;

    func_8002B1A0();
    func_800315E8();
    func_80028140();
    temp_s0 = arg0 * 3;
    func_80018728(0x83000000U, temp_s0);
    func_80018728(0x83010000U, temp_s0);
    func_80018728(0x83020000U, temp_s0);
    func_80018728(0x83030000U, temp_s0);
    func_80018728(0x83040000U, temp_s0);
    D_80090B9C = 0;
}
#endif

#ifdef VERSION_US
extern s32 func_80019378(void);

s32 func_80025D44(void) {
    return func_80019378();
}
#endif

#ifdef VERSION_US
void func_80025D64(u8 arg0) {
    if (arg0 != 0) {
        func_80018728(0xF1FF0000U, 0);
    } else {
        func_80018728(0xF2FF0000U, 0);
    }
}
#pragma C_FUNCTION_PADDING(8)
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025DB0.s")
#endif

#ifdef VERSION_US
extern void func_80025DB0();
extern u8 D_800D1910;

void func_80025E7C(void) {
    func_80025DB0();
    func_80018728(0xE2000700U, &D_800D1910);
}
#endif

#ifdef VERSION_US
extern u8 D_80090B8C;
extern u32 D_80090AC0;
extern s16 *D_800D1990[3];
extern void *D_800D198C;
extern void func_80031A6C(s32, void *);
extern s32 func_80031C84(s16 *, s32);
s32 Audio_RenderNextBuffer(s32 arg0, s32 samples, s32 initialize, s32 arg3) {
    s32 result;
    s16 *buffer;
    if ((s8)D_80090B8C == 0) { return 0; }
    buffer = D_800D1990[D_80090AC0];
    if (initialize == 1) {
        func_80031A6C(32000, D_800D198C);
    }
    result = func_80031C84(buffer, samples);
    D_80090AC0++;
    D_80090AC0 %= 3;
    if ((s8)D_80090B8C == 0) { return 0; }
    if (result == -1) { return result; }
    return (s32)buffer;
}
#endif

#ifdef VERSION_US
extern void func_80034DD0(void);
void Audio_InitializeBufferMemory(void *buffer) {
    u32 aligned = ((u32)buffer + 0xF) & ~0xF;
    u32 mask;
    D_800D198C = (void *)aligned;
    D_800D1990[0] = (s16 *)((u8 *)D_800D198C + 0x2380);
    D_800D1990[1] = (s16 *)((u8 *)D_800D1990[0] + 0x2000);
    D_800D1990[2] = (s16 *)((u8 *)D_800D1990[1] + 0x2000);
    func_80031A6C(32000, D_800D198C);
    func_80018728(0x82030300, 0);
    func_800187AC();
    func_80025E7C();
    func_8001874C(0x06030000, 0);
    func_80034DD0();
    mask = osSetIntMask(1);
    D_80090B8C = 1;
    osSetIntMask(mask);
}
#endif

#ifdef VERSION_US
extern void func_80018728(u32, ...); extern u8 D_80090B8C; void func_8002602C(void) { s32 mask; func_80018728(0x83030000, 0); mask = osSetIntMask(1); D_80090B8C = 0; osSetIntMask(mask); }
#endif

#ifdef VERSION_US
extern void func_80034E5C(s32, s32);

void func_80026068(u32 arg0) {
    s32 temp_a1;

    if (arg0 != 0) {
        temp_a1 = arg0 - 1;
        if (arg0 < 0xFCU) {
            func_80034E5C(temp_a1 & 0xFFFF, temp_a1);
        }
    }
}
#endif

#ifdef VERSION_US
extern u8 GbAudio_GetActiveChannelMask(void); void func_80026098(void) { GbAudio_GetActiveChannelMask(); }
#pragma C_FUNCTION_PADDING(8)
#endif

#ifdef VERSION_US
#pragma asmproc late_rodata_alignment("func_800260C0", 8)
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800260C0.s")
#endif

#ifdef VERSION_US
s32 func_80018ACC();
extern u8 D_80090B64;
s32 func_80026298(void) {
    func_80018810();
    if (D_80090B64 != 0) {
        if (func_80018ACC() == 0) {
            return 0;
        }
        D_80090B64 = 0;
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 1;
    }
    return 1;
}
#endif

#ifdef VERSION_US
extern s32 D_80090B60;
extern u8 D_80090B68;
extern s16 D_80090B6C;
extern s16 D_80090B70;
void Audio_ResetCategoryState(void) {
    D_80090B64 = 0;
    D_80090B6C = -1;
    D_80090B70 = -1;
    func_80018728(0x82010000U, 0);
    func_80018704(0x41010000, 0x3F2147AE);
    D_80090B80 = 1;
    switch (D_80090B60) {
    case 2:
    case 3:
    case 5:
    case 7:
    case 9:
    case 10:
        func_80018728(0x82040500U, 0);
        func_80018704(0x41040000, 0x3F2147AE);
    case 1:
    case 4:
        if (D_80090B9C == 0) {
            func_80018728(0x82020400U, 0);
            func_80018704(0x41020000, 0x3F2147AE);
            D_80090B9C = 1;
        }
        break;
    case 12:
        func_80018728(0x82030800U, 0);
        func_80018704(0x41030000, 0x3F3851EC);
        break;
    case 0:
        func_80018728(0x82020600U, 0);
        func_80018704(0x41020000, 0x3F25E354);
        break;
    }
    if (D_80090B60 == 3 || D_80090B60 == 4 || D_80090B60 == 6) {
        func_80018728(0x82030300U, 0);
        func_80018704(0x41030000, 0x3F43D70A);
        func_800187AC();
        func_80025E7C();
    }
    if (D_80090B68 != 0) {
        D_80090B68 = 0;
        switch (D_80090B60) {
        case 0:
            func_80018728(0x82020600U, 0);
            break;
        case 12:
            func_80018728(0x82040200U, 0);
            func_80018704(0x41020000, 0x3F800000);
            break;
        case 8:
            func_80018728(0x82040200U, 0);
            func_80018704(0x41020000, 0x3F800000);
            func_80018728(0x82020100U, 0);
            func_80018704(0x41020000, 0x3F2147AE);
            func_80018728(0x82010A00U, 0);
            func_80018728(0x82010000U, 0);
            func_80018704(0x41010000, 0x3F2147AE);
            D_80090B80 = 1;
            func_80024D44();
            func_80018728(0x82032300U, 0);
            D_80090A50 = 35;
            break;
        case 30:
            func_80024D44();
            func_80018728(0x82032300U, 0);
            D_80090A50 = 35;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
        case 10:
        case 11:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
            break;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800265B0.s")
#endif

#ifdef VERSION_US
s32 Audio_GetEventConfigIndex(s32 category, u32 request) {
    switch (request) {
    case 10: return 31;
    case 11: return 32;
    case 40: return 33;
    }
    switch (category) {
    case 0: return 0;
    case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 4: return 4;
    case 5: return 5;
    case 6: return 6;
    case 7: return 7;
    case 8: return 8;
    case 9: return 9;
    case 10:
        if (request < 2) return 10;
        if (request >= 2 && request < 5) return 11;
        if (request >= 5 && request < 8) return 12;
        if (request >= 8 && request < 11) return 13;
        if (request >= 11 && request < 13) return 14;
        if (request >= 13 && request < 14) return 15;
        if (request >= 14 && request < 18) return 16;
        if (request >= 18 && request < 21) return 17;
        if (request >= 21 && request < 24) return 18;
        return -1;
    case 11: return 19;
    case 12: return 20;
    case 13:
        switch (request) {
        case 0: return 21;
        case 1: return 22;
        case 2: return 23;
        case 3: return 24;
        case 4: return 25;
        case 5: return 26;
        case 6: return 27;
        case 7: return 28;
        default: return -1;
        }
    case 14: return 29;
    case 15: return 30;
    case 18: return 34;
    case 19: return 35;
    }
    return -1;
}
#endif

#ifdef VERSION_US
typedef struct Color_80026938 {
    u8 first;
    u8 second;
    u8 third;
} Color_80026938;
extern u8 D_80090B3C[];
extern Color_80026938 D_80090AD0[];
void func_80026938(u16 arg0) {
    s32 index;
    Color_80026938 *entry;

    if (arg0 >= 0x1E) {
        arg0 = 0xE;
    }
    index = D_80090B3C[arg0];
    entry = &D_80090AD0[index];
    D_80090B6C = entry->second;
    D_80090B70 = entry->first;
}
#pragma C_FUNCTION_PADDING(8)
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026990.s")
#endif

#ifdef VERSION_US
extern u16 D_800D19A0[];
extern char D_800A39A0[];
extern char D_800A39A4[];
extern f32 func_80026990(u8);
void Audio_DebugSampleHistogram(u8 mode) {
    s32 i;
    for (i = 0; i < 100; i++) D_800D19A0[i] = 0;
    for (i = 0; i < 1000; i++) {
        osSyncPrintf(D_800A39A0, (f64)func_80026990(mode));
    }
    for (i = 0; i < 100; i++) {
        osSyncPrintf(D_800A39A4, i, D_800D19A0[i]);
    }
}
#endif

#ifdef VERSION_US
#pragma pack(1)
typedef struct { s32 w0; s32 w4; } PackedRecord;
#pragma pack(0)
extern PackedRecord D_80090C84[];
extern PackedRecord D_80090CFC;
typedef struct AudioChannelEvent {
    u8 bank;
    u8 unknown01;
    u16 sound;
    u8 slot;
    u8 kind;
    u16 mask;
    u8 count;
    u8 unknown09[3];
    void *resource;
    f32 scale;
    u8 unknown14[4];
} AudioChannelEvent;
extern void func_80026ED8(u8);
extern u8 Audio_SetupEventVoice(AudioChannelEvent *, u8);
extern s32 func_8002738C(u8);
#endif

#ifdef VERSION_US
extern u8 D_800918E8;
extern s32 Audio_ConfigureEventChannel(AudioChannelEvent *, u8);
extern void Audio_UpdateEventVoiceParameters(void *, u8, u8);
void Audio_ProcessChannelEvent(AudioChannelEvent *event, s32 arg1) {
    PackedRecord *entry;
    if (event->slot == 15) {
        D_800918E8 = func_8002738C(Audio_SetupEventVoice(event, D_800918E8));
        return;
    }
    entry = &D_80090C84[event->slot];
    if (((u8 *)entry)[6] == 1) {
        switch (((u8 *)entry)[0]) {
        case 1:
            func_80026ED8(event->slot);
            break;
        case 3:
            ((u8 *)entry)[0] = 2;
            break;
        case 4:
            return;
        }
        entry = &D_80090C84[event->slot];
    }
    if (event->sound != *(u16 *)((u8 *)entry + 4)) {
        D_800918E8 = Audio_ConfigureEventChannel(event, D_800918E8);
        return;
    }
    switch (((u8 *)entry)[0]) {
    case 2:
        ((u8 *)entry)[0] = 3;
        Audio_UpdateEventVoiceParameters(event, ((u8 *)&D_80090C84[event->slot])[1], 0);
        ((u8 *)&D_80090C84[event->slot])[6] = 1;
        return;
    case 4:
        return;
    }
    *entry = D_80090CFC;
}
#endif

#ifdef VERSION_US
s32 Audio_ConfigureEventChannel(AudioChannelEvent *event, u8 request) {
    u8 channel;
    func_80026ED8(event->slot);
    channel = Audio_SetupEventVoice(event, request);
    ((u8 *)&D_80090C84[event->slot])[1] = channel;
    *(u16 *)((u8 *)&D_80090C84[event->slot] + 4) = event->sound;
    ((u8 *)&D_80090C84[event->slot])[3] = event->kind;
    if (event->kind == 0) {
        ((u8 *)&D_80090C84[event->slot])[0] = 1;
    } else {
        ((u8 *)&D_80090C84[event->slot])[0] = 4;
    }
    ((u8 *)&D_80090C84[event->slot])[6] = 1;
    return func_8002738C(channel);
}
#endif

#ifdef VERSION_US
void func_80026ED8(u8 arg0) {
    func_8001874C(0x06020000 | (((u8 *) &D_80090C84[arg0])[1] << 8), 0);
    D_80090C84[arg0] = D_80090CFC;
}
#endif

#ifdef VERSION_US
extern s32 Audio_SelectEventChannel(void *, u8);
extern void Audio_UpdateEventVoiceParameters(void *, u8, u8);
extern u8 D_80090BC1[];
extern u8 D_80090D28[][16];
u8 Audio_SetupEventVoice(AudioChannelEvent *arg0, u8 request) {
    request = (u8)Audio_SelectEventChannel(arg0, request);
    Audio_UpdateEventVoiceParameters(arg0, request, 1);
    D_80090BC1[request * 12] = ((u8 *)D_80090D28)[arg0->sound * 16 + 12];
    func_8001874C(((0x06020000 | (((u32)request & 0xFF) << 8)) | 1), (s8)((u8 *)D_80090D28)[arg0->sound * 16]);
    func_8001874C((0x06020000 | (((u32)request & 0xFF) << 8)), 1);
    func_8001874C(((0x06020000 | (((u32)request & 0xFF) << 8)) | 3), (s8)((((u8 *)D_80090D28)[arg0->sound * 16] & 0x80) >> 7));
    return request;
}
#endif

#ifdef VERSION_US
typedef struct { u8 unknown00[6]; u16 mask; } AudioChannelMask;
typedef struct { s32 w0; s32 w4; s32 w8; } Candidate27F7CRecord;
extern Candidate27F7CRecord D_80090BB8[];
extern Candidate27F7CRecord D_80090C78;
typedef struct { AudioChannelMask channels; u8 count; } AudioChannelGroup;
typedef struct AudioVoiceParameters {
    u8 unknown00[2];
    u16 sound;
    u8 unknown04[8];
    s8 *pan;
    f32 pitch;
    u8 balance;
} AudioVoiceParameters;
extern f64 D_800A39B0;
extern f32 D_800A39B8;
void Audio_UpdateEventVoiceParameters(void *arg0, u8 channel, u8 reset) {
    if (reset) {
        ((u8 *)(&D_80090BB8[channel]))[0] = ((u8 *)D_80090D28)[((AudioVoiceParameters *)arg0)->sound * 16 + 1];
        ((s8 *)(&D_80090BB8[channel]))[1] = ((s8 *)D_80090D28)[((AudioVoiceParameters *)arg0)->sound * 16 + 8];
    }
    *(f32 *)((u8 *)(&D_80090BB8[channel]) + 4) = *(f32 *)((u8 *)D_80090D28 + ((AudioVoiceParameters *)arg0)->sound * 16 + 4) * ((AudioVoiceParameters *)arg0)->pitch;
    if (*(f32 *)((u8 *)(&D_80090BB8[channel]) + 4) > 4.0) {
        *(f32 *)((u8 *)(&D_80090BB8[channel]) + 4) = 4.0f;
    } else if (*(f32 *)((u8 *)(&D_80090BB8[channel]) + 4) < D_800A39B0) {
        *(f32 *)((u8 *)(&D_80090BB8[channel]) + 4) = D_800A39B8;
    }
    if (((u8 *)D_80090D28)[((AudioVoiceParameters *)arg0)->sound * 16 + 13] & 0xF0) {
        *(f32 *)((u8 *)(&D_80090BB8[channel]) + 4) *= func_80026990(((u8 *)D_80090D28)[((AudioVoiceParameters *)arg0)->sound * 16 + 13] >> 4);
    }
    if (((u8 *)D_80090D28)[((AudioVoiceParameters *)arg0)->sound * 16 + 13] & 1) {
        if (*((AudioVoiceParameters *)arg0)->pan >= 64) {
            ((u8 *)(&D_80090BB8[channel]))[2] = 127;
        } else if (*((AudioVoiceParameters *)arg0)->pan < -64) {
            ((u8 *)(&D_80090BB8[channel]))[2] = 0;
        } else {
            ((u8 *)(&D_80090BB8[channel]))[2] = *((AudioVoiceParameters *)arg0)->pan + 64;
        }
    } else {
        ((u8 *)(&D_80090BB8[channel]))[2] = ((AudioVoiceParameters *)arg0)->balance;
    }
}
#endif

#ifdef VERSION_US
extern s8 func_80018C60(s32, s32, s32);
extern u8 Audio_FindEnabledChannel(AudioChannelMask *, u8, u8);
extern u8 Audio_FindLowestPriorityChannel(AudioChannelGroup *, u8);
s32 Audio_SelectEventChannel(void *arg0, u8 request) {
    u8 i;
    u8 scanned;
    u32 next;
    for (i = 0; i < 16; i++) {
        ((u8 *)&D_80090BB8[(u32)i])[8] = func_80018C60(2, i, 2);
    }
    next = Audio_FindEnabledChannel((AudioChannelMask *)arg0, request, 0);
    request = next;
    scanned = 0;
    while (((u8 *)&D_80090BB8[(u32)next])[8] == 1 && scanned < ((AudioChannelGroup *)arg0)->count) {
        next = Audio_FindEnabledChannel((AudioChannelMask *)arg0, request, 1);
        request = next;
        scanned++;
    }
    if (((u8 *)&D_80090BB8[(u32)next])[8] == 1) {
        request = Audio_FindLowestPriorityChannel((AudioChannelGroup *)arg0, request);
    }
    return request;
}
#endif

#ifdef VERSION_US
extern s32 func_8002738C(u8);
u8 Audio_FindEnabledChannel(AudioChannelMask *state, u8 channel, u8 advance) {
    if (advance) {
        channel = func_8002738C(channel);
    }
    if (!((state->mask >> channel) & 1)) {
        s32 next;
        do {
            next = func_8002738C(channel);
            channel = next;
        } while (!((state->mask >> next) & 1));
    }
    return channel;
}
#endif

#ifdef VERSION_US
s32 func_8002738C(u8 channel) {
    if (channel < 0xF) {
        channel++;
    } else {
        channel = 0;
    }
    return channel;
}
#endif

#ifdef VERSION_US
u8 Audio_FindLowestPriorityChannel(AudioChannelGroup *state, u8 channel) {
    u8 best = channel;
    u8 i;
    for (i = 1; i < state->count; i++) {
        Candidate27F7CRecord *bestRecord = &D_80090BB8[best];
        s32 next = Audio_FindEnabledChannel(&state->channels, channel, 1);
        channel = next;
        if (((u8 *)&D_80090BB8[next])[9] < ((u8 *)bestRecord)[9]) {
            best = next;
        }
    }
    return best;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027490.s")
#endif

#ifdef VERSION_US
extern f32 D_80090BBC[][3];
typedef struct Candidate275E8State {
    u8 unk0;
    u8 flags;
    u8 pad02[0x3A];
    f32 value;
} Candidate275E8State;
typedef struct Candidate275E8Bits {
    u8 unk0;
    unsigned char active : 1;
    unsigned char other : 7;
    u8 pad02[0x3A];
    f32 value;
} Candidate275E8Bits;
s32 func_800275E8(u8 arg0, Candidate275E8Bits *arg1) {
    arg1->value = D_80090BBC[arg0][0];
    arg1->active = 1;
    if (arg1->active == 1) {
        return arg0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027634.s")
#endif

#ifdef VERSION_US
typedef AudioChannelEvent ResourceContext_80027774;
extern void Audio_BuildAndDispatchSoundEvent(u16, s32, ResourceContext_80027774 *);
extern u8 D_80090D04[];
void func_80027774(u16 arg0, u8 arg1) {
    ResourceContext_80027774 context;

    context.resource = D_80090D04;
    context.kind = arg1;
    context.scale = 1.0f;
    Audio_BuildAndDispatchSoundEvent(arg0, 0, &context);
}
#endif

#ifdef VERSION_US

extern void func_8002781C(u16 resource_id, u8 mode, ...);
void func_800277C4(u16 resource_id, u8 mode) {
    func_8002781C(resource_id, mode);
}
#endif

#ifdef VERSION_US
void func_800277F0(u16 resource_id, void *context) {
    func_8002781C(resource_id, 0, context);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002781C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800278C0.s")
#endif

#ifdef VERSION_US
void Audio_PlayDefaultSound(u16 id) {
    ResourceContext_80027774 context;
    context.resource = D_80090D04;
    context.kind = 0;
    context.scale = 1.0f;
    if (id == 0x5F0A) {
        func_800225C4(5);
    }
    Audio_BuildAndDispatchSoundEvent(id, 0, &context);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027A28.s")
#endif

#ifdef VERSION_US
extern u8 D_800A3990[];
extern u8 D_80090D31[];
// Decode the request, adjust its channel mask, and dispatch nonempty events.
void Audio_BuildAndDispatchSoundEvent(u16 encoded, s32 offset, ResourceContext_80027774 *event) {
    u8 i;
    u8 j;
    u8 total = 0;

    event->slot = (encoded & 0xF00) >> 8;
    event->bank = (encoded & 0xF000) >> 12;
    event->sound = encoded & 0xFF;
    for (i = 0; i < event->bank; i++) event->sound += D_800A3990[i];
    event->unknown14[0] = D_80090D31[event->sound * 16];
    for (i = 0; i < 13; i++) total += D_800A3990[i];
    if (event->sound >= total) event->sound = total - 1;
    event->count = 0;
    for (i = 0; i < 16; i++) {
        if ((*(u16 *)(D_80090D28[event->sound] + 10) >> i) & 1) {
            event->count++;
        }
    }
    event->mask = *(u16 *)(D_80090D28[event->sound] + 10);
    if (event->bank != 6 && ((D_80090D28[event->sound][13] >> 1) & 1)) {
        if ((u8)offset * event->count >= 49) return;
        for (i = 0; i < (u8)offset * event->count; i++) {
            event->mask <<= 1;
            total = 0;
            for (j = 0; j < 16; j++) {
                if ((event->mask >> j) & 1) total++;
            }
            if (total == event->count - 1) {
                if (event->mask & 1) return;
                event->mask |= 1;
            } else if (total < event->count - 1) {
                return;
            }
        }
        if (event->slot != 15) {
            event->slot += offset;
            if (event->slot >= 15) event->slot -= 15;
        }
    }
    if (event->count) Audio_ProcessChannelEvent(event, offset);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027E30.s")
#endif

#ifdef VERSION_US
extern void func_80027E30(void);
extern void func_80027F4C(void);

// credit to https://decomp.me/scratch/eFWz0
void func_80027EE0(u16 arg0) {
    switch (arg0) {
        case 0xFFF:
            func_80027E30();
            return;
        case 0xFFE:
            func_80027F4C();
            return;
        case 0xFFD:
            func_80027F4C();
            func_80027E30();
            return;
        default:
            return;
    }
}
#endif

#ifdef VERSION_US
extern void func_80027F7C();
extern s8 D_80090BB0;

void func_80027F4C(void) {
    func_80018728(0x83020000U, 0x14);
    func_80027F7C();
    D_80090BB0 = 0;
}
#endif

#ifdef VERSION_US
void func_80027F7C(void) { u8 i; u8 j; for (i = 0; i < 15; i++) { D_80090C84[i] = D_80090CFC; } for (j = 0; j < 16; j++) { D_80090BB8[j] = D_80090C78; } }
#endif

#ifdef VERSION_US
extern u8 D_8011F300;
extern void func_80027EE0(u16);
extern void Audio_PlayDefaultSound(u16);

void func_80028014(void) {
    func_80027EE0(0xFFD);
    Audio_PlayDefaultSound(0xCF07);
    if (D_8011F300 == 0x5C) {
        func_80018728(0x83000000U, 0x1E);
        return;
    }
    func_80018728(0xF1000000U, 0);
}
#endif

#ifdef VERSION_US
extern u8 D_8011BE90;
extern u16 D_800D2B44;
extern s16 D_800D2BA8;
extern u8 D_800D2B78;
s32 func_8002806C(void) {
    u8 *base;
    s32 result;

    base = &D_8011BE90;
    result = *(u8 *)(base + 0x3470) - 0x27;
    if (((u32)*(s32 *)(base + 0x346C) >> 31) == 0) {
        return 0;
    }
    return result;
}
#endif

#ifdef VERSION_US
void func_8002809C(void) {
    func_80018728(0xF2000000, 0);
}
#endif

#ifdef VERSION_US

void func_800280C0(void) {
    func_80027EE0(0xFFE);
    func_80018728(0x4B000000U, 1);
}
#endif

#ifdef VERSION_US

void func_800280EC(void) {
    func_80027EE0(0xFFF);
    func_80018728(0x4C000000U, 1);
}
#endif

#ifdef VERSION_US
extern u8 D_80090BB4;
void func_80028118(u8 arg0) {
    D_80090BB4 = arg0 + 1;
}
#pragma C_FUNCTION_PADDING(20)
#endif

#ifdef VERSION_US
extern s32 D_800D1A70[2];
extern s32 D_800D1A78[2];
extern s8 D_800D1A80[2];
extern s8 D_800D1A82[2];
void func_80028140(void) {
    (*(s32 *)((u8 *)(&D_800D1A70) + (0))) = -1;
    (*(s32 *)((u8 *)(&D_800D1A70) + (4))) = -1;
    (*(s32 *)((u8 *)(&D_800D1A78) + (0))) = -1;
    (*(s32 *)((u8 *)(&D_800D1A78) + (4))) = -1;
    (*(s8 *)((u8 *)(&D_800D1A80) + (0))) = 0x7F;
    (*(s8 *)((u8 *)(&D_800D1A80) + (1))) = 0x7F;
    (*(s8 *)((u8 *)(&D_800D1A82) + (0))) = 0;
    (*(s8 *)((u8 *)(&D_800D1A82) + (1))) = 0;
}
#endif

#ifdef VERSION_US
// Select a request channel and leave its state for Audio_UpdateDeferredSounds.
void Audio_QueueDeferredSound(s32 sound, s32 delay, u8 parameter) {
    u16 channel;
    u8 mode = 0;

    channel = (sound >= 266) ? 1 : 0;
    if (channel == 1) {
        mode = ((sound & 0xF000) == 0x3000) ? 2 : 1;
        sound &= 0xFFF;
    }
    func_8001874C((0x06040000 | ((u8)channel << 8)) | 3, 1);
    //!bug Zero delay becomes two before the immediate-play branch tests for zero.
    if (delay == 0) {
        delay = 2;
    }
    if (delay == 0) {
        func_8001874C((0x06040000 | ((u8)channel << 8)), sound % 64);
        func_8001874C((0x06040000 | ((u8)channel << 8)) | 1, sound / 64);
        func_8001874C((0x06040000 | ((u8)channel << 8)) | 2, parameter);
        if (channel == 1) {
            func_8001874C((0x06040000 | ((u8)channel << 8)) | 4, mode);
        }
    } else {
        D_800D1A70[channel] = sound;
        D_800D1A78[channel] = delay;
        D_800D1A80[channel] = parameter;
        D_800D1A82[channel] = mode;
    }
}
#endif

#ifdef VERSION_US
void func_80028300(void) {
    func_8001874C(0x06040003, 1);
    func_8001874C(0x06040103, 1);
    func_80028140();
}
#endif

#ifdef VERSION_US
// Count down two pending requests and submit their channel commands when due.
void Audio_UpdateDeferredSounds(void) {
    u32 channel;
    s32 command;

    for (channel = 0; channel < 2; channel++) {
        if (D_800D1A70[channel] != -1) {
            if (D_800D1A78[channel] == 1) {
                func_8001874C((0x06040000 | ((u8)channel << 8)) | 3, 1);
            }
            if (D_800D1A78[channel] == 0) {
                command = 0x06040000 | ((u8)channel << 8);
                func_8001874C(command, D_800D1A70[channel] % 64);
                func_8001874C(command | 1, D_800D1A70[channel] / 64);
                func_8001874C(command | 2, D_800D1A80[channel]);
                if (channel == 1) {
                    func_8001874C(command | 4, D_800D1A82[channel]);
                }
                D_800D1A70[channel] = -1;
                D_800D1A78[channel] = -1;
                D_800D1A80[channel] = 127;
                D_800D1A82[channel] = 0;
            } else {
                D_800D1A78[channel]--;
            }
        }
    }
}
// Preserve the original two zero words of inter-function alignment.
#pragma C_FUNCTION_PADDING(8)
#endif

#ifdef VERSION_US
extern u8 D_8009210C[];
u8 Audio_LookupScaledRatio(u16 numerator, u16 denominator) {
    s32 scaled = (numerator * 48) / denominator;
    s32 index = 0;
    for (; index < 6; index++) {
        if (D_8009210C[index * 2] >= scaled) {
            break;
        }
    }
    return D_8009210C[index * 2 + 1];
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028540.s")
#endif

#ifdef VERSION_US
void Audio_SwapSoundCandidates(u8 *arg0, u8 *arg1) { if (*arg0 != *arg1) { u8 temp = *arg0; *arg0 = *arg1; *arg1 = temp; } }
#endif

#ifdef VERSION_US
extern u32 D_800D1AD8[24];
u16 Audio_FilterRecentSoundId(u16 arg0) {
    s32 i;
    for (i = 0; i < 24; i++) {
        if (arg0 == D_800D1AD8[i]) return 0;
    }
    return arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800289B0.s")
#endif

#ifdef VERSION_US
void Audio_RemoveRecentSoundAt(u16 arg0) {
    u32 i;
    for (i = arg0; i > 0; i--) D_800D1AD8[i] = D_800D1AD8[i - 1];
    D_800D1AD8[0] = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028ADC.s")
#endif

#ifdef VERSION_US
extern void func_800314D4(s32);
extern s32 func_80028ADC(void);
/* Existing callers pass an ignored address; preserve the no-argument body. */
void func_80028CA8() {
    s32 v0;
    s32 masked;

    v0 = func_80028ADC();
    masked = v0 & 0xFFFF;
    if (v0 != 0) {
        func_800314D4(masked);
    }
}
void func_80028CA8_padding(void) {}
void func_80028CA8_padding2(void) {}
#endif

#ifdef VERSION_US
s32 func_80028CE8(void *arg0, s32 arg1) {
    struct Node { u32 a; u32 b; struct Node *next; };
    struct Root { u32 a; struct Node *next; };
    struct Node *node = ((struct Root *)arg0)->next;
    s32 i = 0;
    while (i != arg1) {
        if (node->next == 0) return (s32)node;
        node = node->next;
        i++;
    }
    return (s32)node;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028D9C.s")
#endif

#ifdef VERSION_US
extern u8 D_800D2660[];
s32 func_80028E60(u32 arg0)
{
  u8 *ptr;
  int value;
  u32 mask;
  s32 result;
  arg0--;
  ptr = &D_800D2660[arg0 >> 3];
  value = *ptr;
  mask = 1U << (arg0 & 7);
  result = value & mask;
  value |= mask;
  if ((mask = result) != 0U)
  {
    return 1;
  }
  *ptr = value;
  return mask != (mask = 0);
}
#endif

#ifdef VERSION_US
void func_80028EA8(void) { extern u8 D_80091B90[]; func_80028D9C(D_80091B90); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028ECC.s")
#endif

#ifdef VERSION_US
extern s32 D_800D1A90[10];
extern u8 D_800D2660[32];
extern u32 D_80091A24;
extern u32 D_80091A28;
void Audio_ResetQueueAndBitmap(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        D_800D1A90[i] = 0;
    }
    D_80091A24 = 0;
    D_80091A28 = 0;
    for (i = 0; i < 32; i++) {
        D_800D2660[i] = 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A25C.s")
#endif

#ifdef VERSION_US
extern u16 D_80090BA0;
extern u8 D_800D2650[];
void func_8002A7A8(s32 arg0, s32 arg1) { D_800D2650[0] = arg0; D_800D2650[1] = arg1; D_800D2650[3] = D_80090BA0; if (D_80090BA0 == 1) D_800D2650[2] = 1; else D_800D2650[2] = 0; D_800D2650[4] = 0; *(u32 *)(D_800D2650 + 8) = 0; }
#endif

#ifdef VERSION_US
extern s8 D_80091A0C;

void func_8002A7E8(s32 arg0) {
    if (arg0 != 0) {
        D_80091A0C = 1;
        return;
    }
    D_80091A0C = 0;
}
#endif

#ifdef VERSION_US
extern s8 D_80091A10;

void func_8002A80C(s32 arg0) {
    if (arg0 != 0) {
        D_80091A10 = 1;
        return;
    }
    D_80091A10 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A830.s")
#endif

#ifdef VERSION_US
extern s32 D_800D2630;

void func_8002A9C0(s32 arg0) {
    D_800D2630 = arg0;
}
#endif

#ifdef VERSION_US
extern s32 D_800D2634;

void func_8002A9CC(s32 arg0) {
    D_800D2634 = arg0;
}
#endif

#ifdef VERSION_US
extern u8 *D_800D1B78[];
extern u8 *D_800D1B80[];
extern char D_800A3A60[];
extern char D_800A3A6C[];
extern char D_800A3A84[];
extern char D_800A3A94[];
extern char D_800A3AA4[];
void func_8002A9D8(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        osSyncPrintf(D_800A3A60, i);
        osSyncPrintf(D_800A3A6C, D_800D1B78[i][1]);
        osSyncPrintf(D_800A3A84, D_800D1B80[i][0]);
        osSyncPrintf(D_800A3A94, D_800D1B80[i][3]);
        osSyncPrintf(D_800A3AA4, D_800D1B80[i][4]);
    }
}
#endif

#ifdef VERSION_US
extern s8 D_80091A18;
void func_8002AAD0(u8 arg0) {
    if (arg0) {
        D_80091A18 = 1;
        return;
    }
    D_80091A18 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002AAFC.s")
#endif

#ifdef VERSION_US
extern void func_8002A25C();
extern void func_80024180();
void func_8002B1A0(void) { func_8002A25C(); func_80024180(0, 0); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B1CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B2FC.s")
#endif

#ifdef VERSION_US
extern void func_80023A3C(s32, s32, s32);
extern void func_8002AAFC(s32);
extern void func_800314D4(s32);

void func_8002B43C(void) {
    D_80091A18 = 0;
    func_8002AAFC(0);
    func_80023A3C(3, 0, 0);
    func_800314D4(0x2226);
}
#endif

#ifdef VERSION_US
extern s32 D_80091B08, D_80091B0C;
void func_8002B47C(s32 arg0, s32 arg1) {
    D_80091B08 = arg0;
    D_80091B0C = arg1;
}
#endif

#ifdef VERSION_US
extern u8 D_80091AC8;
extern u8 D_800D1B3B;
extern u32 D_800D2640[];
extern u8 D_800D269E[];
extern u8 D_80091F00[];
extern u8 D_80091EF8[];
extern u8 D_80091EEC[];
void Audio_RequestSlot(u8 slot) {
    if (D_80091AC8 != 0) {
        if (D_800D1B3B == 0)
        {
            func_800314D4(0x2028);
        }
        if (D_800D2640[slot] < 2U) {
            D_800D269E[slot] = 1;
        }
    } else {
        if (D_800D2640[slot] < 2U) {
            if (*(D_800D269E + slot) != 0) {
                if (D_800D1B3B == 0) {
                    func_80028CA8(D_80091F00);
                }
            } else if (D_800D1B3B == 0) {
                func_80028CA8(D_80091EF8);
            }
            *(D_800D269E + slot) = 1;
        } else if (D_800D1B3B == 0) {
            func_80028CA8(D_80091EEC);
        }
    }
    D_80091AC8 = 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B5B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002BE44.s")
#endif

#ifdef VERSION_US
extern u32 D_80091A2C;
extern s16 D_800D1AB8[];
void func_8002C2A0(unsigned short arg0)
{
  D_800D1AB8[D_80091A2C] = arg0;
  D_80091A2C = D_80091A2C + 1;
  if (((u32) D_80091A2C) >= 10U)
  {
    D_80091A2C = D_80091A2C - 1;
  }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002C2E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80030420.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80030AD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003121C.s")
#endif

#ifdef VERSION_US
extern u32 D_80091A24;
extern s32 D_800D1A90[];
extern s8 D_80091A0C;
extern s8 D_80091A10;
void func_800314D4(s32 arg0) {
    if ((u8)D_80091A0C != 0) {
        if ((u8)D_80091A10 != 0) {
            if (arg0 != 0) {
                D_800D1A90[D_80091A24 % 10] = arg0;
                D_80091A24++;
            }
        }
    }
}
#endif

#ifdef VERSION_US
void func_80031530(u16 a) {
    func_800314D4(a | 0x10000000);
}

void func_80031530_padding(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031564.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800315E8.s")
#endif

#ifdef VERSION_US
extern u8 D_80091A1C;
extern u32 D_80091A20;
extern u32 D_80091A30;
extern u8 D_80091A34;
extern u8 D_80091A44;
typedef struct { u8 unk00[38]; u16 unk26; } unk_D_800D1B88;
extern unk_D_800D1B88 *D_800D1B88[2];
extern s32 func_80019230(s32, s32, s32);
// Service queued sound/wait commands and the enabled timed command sequence.
void Audio_UpdateCommandQueue(void) {
    u32 command;

    if ((u8)D_80091A0C && (u8)D_80091A10 && D_80091A28 < D_80091A24) {
        if (D_80091A30 != 0) {
            D_80091A30--;
        } else if (func_80019230(4, 1, 0) == 0) {
            command = D_800D1A90[D_80091A28 % 10];
            if (command >= 0x10000) {
                switch (command & 0xFFFF0000) {
                    case 0x10000000:
                        D_80091A30 = command & 0xFFFF;
                        break;
                    case 0x20000000:
                        D_80091A34 = 1;
                        break;
                }
            } else if (command != 0) {
                Audio_QueueDeferredSound(command, 0, 127);
            }
            D_80091A28++;
        }
    }
    if (D_80091A1C && D_80091A34) {
        if (D_80091A20 == 0) {
            if (D_800D1B88[0]->unk26 == 0 || D_800D1B88[1]->unk26 == 0 || D_80091A44 != 0) {
                D_80091A20 = 598;
            }
        }
        if (D_80091A20 == 1) {
            func_800314D4(0x20E2);
        } else if (D_80091A20 == 600) {
            func_800314D4(0x20E3);
        } else if (D_80091A20 == 1200) {
            func_800314D4(0x20E4);
            D_80091A20 = 2;
        }
        D_80091A20++;
    }
}
#endif

#ifdef VERSION_US
extern u8 D_800D1B90[];
void func_80031844(s32 arg0, s32 arg1) { s32 *p0 = &arg0; *p0 = arg0; arg0 &= 0xFF; if (arg0 < 2) { if (arg1 <= 0) D_800D1B90[arg0] = 0; else D_800D1B90[arg0] = arg1; } }
#endif

#ifdef VERSION_US
void func_80031880(s32 arg0, s32 arg1) {
    switch (arg1) {
        case 1:
            arg0 |= 0x3000;
            break;
        case 2:
            arg0 |= 0x2000;
            break;
        case 0:
            break;
        default:
            return;
    }
    func_800314D4(arg0);
}
#endif

#ifdef VERSION_US
s32 func_80019230(s32, s32, s32);

s32 func_800318C8(void) {
    if (func_80019230(4, 1, 0) != 0) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800318FC.s")
#endif

#ifdef VERSION_US
typedef struct { u8 *ptr; u8 value; u8 pad; u16 limit; } Func31Entry;
extern Func31Entry D_800D27C0[];
// Registers 0xFF10 through 0xFF3F alternate value and write-flag bytes.
// GbAudio_QueueRegisterWrite marks the byte following each written value.
typedef struct {
    u8 unk00; u8 unk01; u8 unk02; u8 unk03;
    u8 unk04; u8 unk05; u8 unk06; u8 unk07;
    u8 unk08; u8 unk09; u8 unk0A; u8 unk0B;
    u8 unkC; u8 unkD; u8 unkE; u8 unkF;
    u8 unk10; u8 unk11; u8 unk12; u8 unk13;
    u8 unk14; u8 unk15; u8 unk16; u8 unk17;
    u8 unk18; u8 unk19; u8 unk1A; u8 unk1B;
    u8 unk1C; u8 unk1D; u8 unk1E; u8 unk1F;
    u8 unk20; u8 unk21; u8 unk22; u8 unk23;
    u8 unk24; u8 unk25; u8 unk26; u8 unk27;
    u8 unk28; u8 unk29; u8 unk2A; u8 unk2B;
    u8 unk2C; u8 unk2D;
    u8 unk2E[50];
} AudioConfig;
extern AudioConfig D_800D2760;
extern u32 D_800D2AE4;
extern u8 D_800D2AD8[];
void GbAudio_QueueRegisterWrite(u16 address, u8 value, u16 delay) {
    u8 index = address;
    D_800D27C0[D_800D2AE4].ptr = (u8 *)&D_800D2760 + index * 2 - 0x20;
    D_800D27C0[D_800D2AE4].value = value;
    D_800D27C0[D_800D2AE4].limit = delay + 1;
    D_800D2AD8[index] = value;
    D_800D2AE4++;
    D_800D2AE4 %= 100;
    D_800D27C0[D_800D2AE4].limit = 0;
}
#endif

#ifdef VERSION_US
u8 GbAudio_GetRegisterValue(u16 arg0)
{
  return D_800D2AD8[arg0 & 0xFF];
}
#endif

#ifdef VERSION_US
typedef struct {
    u32 unk0;
    s16 unk4;
    s16 unk6;
    u32 unk8;
    u32 unkC;
    u16 duty_ticks[2];
    s16 unk14;
    u8 unk16;
    u8 unk17;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u8 unk24;
} AudioState;
extern AudioState D_800D26E8;
extern u32 D_800D275C;
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031A6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031C84.s")
#endif

#ifdef VERSION_US
extern s32 D_800D2AE0;
void func_80031E6C(u16 arg0) {
    while (D_800D27C0[D_800D2AE0].limit >= arg0) {
        D_800D27C0[D_800D2AE0].ptr[0] = D_800D27C0[D_800D2AE0].value;
        D_800D27C0[D_800D2AE0].ptr[1] = 1;
        D_800D2AE0++;
        if ((u32)D_800D2AE0 >= 100U) D_800D2AE0 -= 100;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031F00.s")
#endif

#ifdef VERSION_US
// GB sound-register mirror: each register value is followed by a dirty byte.
#define GB_PULSE2_REG(n) (((u8 *)&D_800D2760)[(n) * 2])
#define GB_PULSE2_DIRTY(n) (((u8 *)&D_800D2760)[(n) * 2 + 1])
s16 GbAudio_RenderPulse2(void) {
    s32 i;
    s32 changed;
    s32 nr24;
    u8 phase;
    s16 out;

    changed = 0;
    for (i = 6; i < 10; i++) {
        if (GB_PULSE2_DIRTY(i) != 0) {
            changed = 1;
            GB_PULSE2_DIRTY(i) = 0;
        }
    }

    if (changed) {
        nr24 = GB_PULSE2_REG(9);
        D_800D26E8.unk1C = ((0x800 - (GB_PULSE2_REG(8) | (((u8)nr24 & 7) << 8))) * D_800D275C) >> 11;
        switch ((GB_PULSE2_REG(6) & 0xC0) >> 6) {
            case 0:
                D_800D26E8.duty_ticks[1] = D_800D26E8.unk1C >> 3;
                if (D_800D26E8.duty_ticks[1] < 64) {
                    D_800D26E8.duty_ticks[1] = 64;
                }
                phase = 1;
                D_800D26E8.duty_ticks[0] = D_800D26E8.unk1C - D_800D26E8.duty_ticks[1];
                goto duty_done;
            case 1:
                D_800D26E8.duty_ticks[1] = D_800D26E8.unk1C >> 2;
                if (D_800D26E8.duty_ticks[1] < 64) {
                    D_800D26E8.duty_ticks[1] = 64;
                }
                phase = 0;
                D_800D26E8.duty_ticks[0] = D_800D26E8.unk1C - D_800D26E8.duty_ticks[1];
                goto duty_done;
            case 2:
                D_800D26E8.duty_ticks[1] = D_800D26E8.unk1C >> 1;
                if (D_800D26E8.duty_ticks[1] < 64) {
                    D_800D26E8.duty_ticks[1] = 64;
                }
                phase = 0;
                D_800D26E8.duty_ticks[0] = D_800D26E8.unk1C - D_800D26E8.duty_ticks[1];
                goto duty_done;
            case 3:
                D_800D26E8.duty_ticks[0] = D_800D26E8.unk1C >> 2;
                if (D_800D26E8.duty_ticks[0] < 64) {
                    D_800D26E8.duty_ticks[0] = 64;
                }
                phase = 1;
                D_800D26E8.duty_ticks[1] = D_800D26E8.unk1C - D_800D26E8.duty_ticks[0];
                goto duty_done;
        }
        D_800D26E8.duty_ticks[1] = 0;
        phase = 1;
        D_800D26E8.duty_ticks[0] = D_800D26E8.unk1C;
    duty_done:

        if (!(GB_PULSE2_REG(7) & 8) && !(GB_PULSE2_REG(7) & 0xF0)) {
            D_800D26E8.unk24 = 0;
            D_800D2760.unk2C &= 0xFFFD;
            return 0;
        }
        if ((GB_PULSE2_REG(7) & 8) && !(GB_PULSE2_REG(7) & 0xF0) && !(GB_PULSE2_REG(7) & 7)) {
            D_800D26E8.unk24 = 0;
            D_800D2760.unk2C &= 0xFFFD;
            return 0;
        }

        if (nr24 & 0x80) {
            D_800D26E8.unk0 = 0;
            D_800D26E8.unk24 = 1;
            D_800D26E8.unk16 = phase;
            D_800D26E8.unk14 = 0;
            D_800D26E8.unk18 = 0;
            D_800D26E8.unk4 = ((GB_PULSE2_REG(7) & 0xF0) << 3) << 4;
            if (GB_PULSE2_REG(7) & 7) {
                if (GB_PULSE2_REG(7) & 8) {
                    D_800D26E8.unk6 = 0x800;
                } else {
                    D_800D26E8.unk6 = -0x800;
                }
                D_800D26E8.unkC = D_800D26E8.unk8 = (GB_PULSE2_REG(7) & 7) * D_800D275C;
            } else {
                D_800D26E8.unk6 = 0;
                D_800D26E8.unk8 = -1;
                D_800D26E8.unkC = -1;
            }
            if (nr24 & 0x40) {
                D_800D26E8.unk20 = ((64 - (GB_PULSE2_REG(6) & 0x3F)) * D_800D275C) >> 2;
            } else {
                D_800D26E8.unk20 = -1;
            }
            GB_PULSE2_REG(9) = nr24 & ~0x80;
        }
        if (D_800D26E8.unk24 == 0) {
            return 0;
        }
    } else if (D_800D26E8.unk24 == 0) {
        return 0;
    }

    if (D_800D26E8.unk20 < D_800D26E8.unk0) {
        D_800D26E8.unk24 = 0;
        D_800D2760.unk2C &= 0xFFFD;
        return 0;
    }

    if (D_800D26E8.unkC < D_800D26E8.unk0) {
        D_800D26E8.unk4 += D_800D26E8.unk6;
        D_800D26E8.unkC += D_800D26E8.unk8;
    }
    while (D_800D26E8.unk18 <= D_800D26E8.unk0) {
        D_800D26E8.unk16 ^= 1;
        D_800D26E8.unk18 += D_800D26E8.duty_ticks[D_800D26E8.unk16];
    }

    if (!(GB_PULSE2_REG(7) & 8) && (D_800D26E8.unk4 < 0)) {
        D_800D26E8.unk24 = 0;
        return 0;
    }
    if ((u16)D_800D26E8.unk4 > 30720) {
        D_800D26E8.unk4 = 30720;
        D_800D26E8.unk6 = 0;
        D_800D26E8.unkC = -1;
    }
    out = D_800D26E8.unk4;
    if (D_800D26E8.unk16 == 0) {
        out = -out;
    }
    D_800D26E8.unk0 += 64;
    return out;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80032A28.s")
#endif

#ifdef VERSION_US
extern u8 D_800D2B78;
void func_80032E40(u8 arg0) {
    u8 *p = &D_800D2B78 + (arg0 * 3 * 4 * 5);
    *(u16 *)(p + 0) = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0;
    *(s32 *)(p + 8) = 0; *(s32 *)(p + 12) = 0; *(s32 *)(p + 16) = 0;
    p[20] = 0; p[21] = 0; p[22] = 0; p[23] = 0; *(u16 *)(p + 24) = 0;
    p[26] = 0; p[27] = 0; p[28] = 0; p[29] = 0; p[30] = 0; p[31] = 0; p[32] = 0; *(u16 *)(p + 34) = 0;
    p[36] = 0; p[37] = 0; p[38] = 0; p[39] = 0; p[40] = 0; p[41] = 0; p[42] = 0; p[43] = 0; p[44] = 0; p[45] = 0; p[46] = 0; p[47] = 0;
    *(u16 *)(p + 48) = 0; p[50] = 0; p[51] = 0; p[52] = 0; p[53] = 0; p[54] = 0; p[55] = 0; p[56] = 0; p[57] = 0;
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B40;
extern u8 D_800D2B46;
extern u8 D_800D2B47;
extern u8 D_800D2B48;
extern u8 D_800D2B4A;
extern u8 D_800D2B4E;
extern u8 D_800D2B54;
extern u8 D_800D2B55;
extern u8 D_800D2B56;
extern u8 D_800D2B57;
extern u8 D_800D2B58;
extern u8 D_800D2B59;
extern u8 D_800D2B5A;
extern u8 D_800D2B5E;
extern u8 D_800D2B5F;
extern u8 D_800D2B62;
extern u8 D_800D2B68;
extern u8 D_800D2B69;
extern u8 D_800D2B6A;
extern u8 D_800D2B6B;
extern u8 D_800D2B6C;
extern u8 D_800D2B6D;
extern u8 D_800D2B6E;
extern u8 D_800D2B6F;
extern u8 D_800D2B73;
extern u16 D_800D2B44;
extern u16 D_800D2B4C;
extern u16 D_800D2B5C;
extern u16 D_800D2B60;
extern u16 D_800D2B64;
extern u16 D_800D2B66;
extern s8 D_800D2B42;
extern u8 D_800D2B43;
extern s8 D_800D2B4B;
extern u32 D_800D2B50;
extern u8 D_800D2B70[3];
extern u8 D_800D2B49;
extern void func_800331C8(void);
extern void func_800331B8(void);
extern void func_80032E40(u8);
// Reset hardware registers and software channels while frame updates are disabled.
void GbAudio_ResetState(void) {
    OSIntMask saved_mask;
    u32 index;

    saved_mask = osSetIntMask(OS_IM_NONE);
    func_800331C8();
    osSetIntMask(saved_mask);
    for (index = 0; index < 4; index++) {
        GbAudio_QueueRegisterWrite(index * 5 + 0xFF10, 0, 0);
        GbAudio_QueueRegisterWrite(index * 5 + 0xFF11, 0, 0);
        GbAudio_QueueRegisterWrite(index * 5 + 0xFF12, 8, 0);
        GbAudio_QueueRegisterWrite(index * 5 + 0xFF13, 0, 0);
        GbAudio_QueueRegisterWrite(index * 5 + 0xFF14, 0x80, 0);
    }
    GbAudio_QueueRegisterWrite(0xFF24, 0, 0);
    GbAudio_QueueRegisterWrite(0xFF25, 0, 0);
    GbAudio_QueueRegisterWrite(0xFF26, 0x80, 0);
    for (index = 0; index != 8; index++) {
        func_80032E40(index);
    }
    D_800D2B40 = 0;
    D_800D2B42 = 0;
    D_800D2B43 = 0;
    D_800D2B44 = 0;
    D_800D2B46 = 0;
    D_800D2B47 = 0;
    D_800D2B48 = 0;
    D_800D2B4A = 0;
    D_800D2B4B = 0;
    D_800D2B4C = 0;
    D_800D2B4E = 0;
    D_800D2B50 = 0;
    D_800D2B54 = 0;
    D_800D2B55 = 0;
    D_800D2B56 = 0;
    D_800D2B57 = 0;
    D_800D2B58 = 0;
    D_800D2B59 = 0;
    D_800D2B5A = 0;
    D_800D2B5C = 0;
    D_800D2B5E = 0;
    D_800D2B5F = 0;
    D_800D2B60 = 0;
    D_800D2B62 = 0;
    D_800D2B64 = 0;
    D_800D2B66 = 0;
    D_800D2B68 = 0;
    D_800D2B69 = 0;
    D_800D2B6A = 0;
    D_800D2B6B = 0;
    D_800D2B6C = 0;
    D_800D2B6D = 0;
    D_800D2B6E = 0;
    D_800D2B6F = 0;
    D_800D2B70[0] = 0;
    D_800D2B70[1] = 0;
    D_800D2B70[2] = 0;
    D_800D2B73 = 0;
    D_800D2B49 = 0x77;
    saved_mask = osSetIntMask(OS_IM_NONE);
    func_800331B8();
    osSetIntMask(saved_mask);
}
#endif

#ifdef VERSION_US
extern u16 D_800D2B5C;
extern void GbAudio_ResetState(void);
void func_80033188(void) {
    u16 sp1E;

    sp1E = D_800D2B5C;
    GbAudio_ResetState();
    D_800D2B5C = sp1E;
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B41; void func_800331B8(void) { D_800D2B41 = 1; }
#endif

#ifdef VERSION_US
extern u8 D_800D2B41; void func_800331C8(void) { D_800D2B41 = 0; }
#endif

#ifdef VERSION_US
typedef struct GbAudioStreamRecord {
    s16 unk_00;
    u8 unk_02;
    u8 flags_03;
    u8 flags_04;
    u8 unk_05[15];
    u8 flags_14;
    u8 unk_15;
    u8 unk_16;
    u8 unk_17;
    u16 unk_18;
    u8 unk_1A;
    u8 unk_1B;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E[6];
    u8 unk_24;
    u8 unk_25;
    u8 unk_26;
    u8 unk_27;
    u8 unk_28[20];
} GbAudioStreamRecord;
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800331D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800333CC.s")
#endif

#ifdef VERSION_US
void GbAudio_UpdateChannelIfEnabled(u8 channel) {
    if (!(D_800D2B58 & 0x80)) {
        GbAudio_UpdateSquare1Registers(channel);
    }
}
#endif

#ifdef VERSION_US
extern void GbAudio_QueueRegisterWrite(u16, u8, u16);
extern u8 GbAudio_GetRegisterValue(u16);
extern void GbAudio_QueueChannelReset(u16);
extern s8 D_800D2B42;
extern u8 D_800D2B43;
extern u16 D_800D2B44;
extern s8 D_800D2B4B;
extern u8 D_800D2B78;
void GbAudio_UpdateSquare1Registers(u8 channel) {
    if ((&D_800D2B78 + channel * 0x3C)[0x14] & 8) {
        GbAudio_QueueRegisterWrite(0xFF10, (u8)D_800D2B4B, 0);
    }
    if ((&D_800D2B78 + channel * 0x3C)[0x14] & 0x20) {
        u8 value;
        value = GbAudio_GetRegisterValue(0xFF26);
        value &= 0x8E;
        GbAudio_QueueRegisterWrite(0xFF26, value, 0);
        GbAudio_QueueChannelReset(0xFF10);
    } else if ((&D_800D2B78 + channel * 0x3C)[0x14] & 0x10) {
        GbAudio_QueueRegisterWrite(0xFF11, ((u8)D_800D2B42 | 0x3F) & 0xFF, 0);
        GbAudio_QueueRegisterWrite(0xFF12, D_800D2B43, 0);
        GbAudio_QueueRegisterWrite(0xFF13, D_800D2B44 & 0xFF, 0);
        GbAudio_QueueRegisterWrite(0xFF14, ((D_800D2B44 >> 8) | 0x80) & 0xFF, 0);
    } else {
        if ((&D_800D2B78 + channel * 0x3C)[0x14] & 2) {
            u8 lowByte = D_800D2B44 & 0xFF;
            GbAudio_QueueRegisterWrite(0xFF13, lowByte, 0);
            GbAudio_QueueRegisterWrite(0xFF14, (D_800D2B44 >> 8) & 0xFF, 0);
        }
        if ((&D_800D2B78 + channel * 0x3C)[0x14] & 1) {
            u8 value;
            value = GbAudio_GetRegisterValue(0xFF11);
            value &= 0x3F;
            value |= (u8)D_800D2B42;
            GbAudio_QueueRegisterWrite(0xFF11, value & 0xFF, 0);
        }
    }
}
#endif

#ifdef VERSION_US
extern void GbAudio_UpdateSquare2Registers(u8);
extern void func_80033864(s32);
extern void GbAudio_UpdateNoiseRegisters(u8);
void func_8003364C(s32 arg0) { s32 *p = &arg0; GbAudio_UpdateSquare2Registers(arg0 & 0xFF); }
#endif

#ifdef VERSION_US
extern void GbAudio_QueueRegisterWrite(u16, u8, u16);
extern u8 GbAudio_GetRegisterValue(u16);
extern void GbAudio_QueueChannelReset(u16);
extern s8 D_800D2B42;
extern u8 D_800D2B43;
extern u16 D_800D2B44;
extern u8 D_800D2B8C;
void GbAudio_UpdateSquare2Registers(u8 channel)
{
  s32 flags = (&D_800D2B8C)[channel * 0x3C];
  if (flags & 0x20)
  {
    s32 value;
    value = GbAudio_GetRegisterValue(0xFF26);
    value &= 0x8D;
    GbAudio_QueueRegisterWrite(0xFF26, value, 0);
    GbAudio_QueueChannelReset(0xFF15);
  }
  else
    if (flags & 0x10)
  {
    GbAudio_QueueRegisterWrite(0xFF16, (((u8) D_800D2B42) | 0x3F) & 0xFF, 0);
    GbAudio_QueueRegisterWrite(0xFF17, D_800D2B43, 0);
    GbAudio_QueueRegisterWrite(0xFF18, D_800D2B44 & 0xFF, 0);
    GbAudio_QueueRegisterWrite(0xFF19, ((D_800D2B44 >> 8) | 0x80) & 0xFF, 0);
  }
  else
    if (flags & 0x40)
  {
    u8 lowByte;
    u8 value;
    value = GbAudio_GetRegisterValue(0xFF16);
    value = value & 0x3F;
    value = value | ((u8) D_800D2B42);
    GbAudio_QueueRegisterWrite(0xFF16, value & 0xFF, 0);
    lowByte = D_800D2B44 & 0xFF;
    GbAudio_QueueRegisterWrite(0xFF18, lowByte, 0);
  }
  else
    if (flags & 1)
  {
    u8 value;
    value = GbAudio_GetRegisterValue(0xFF16);
    value &= 0x3F;
    value |= (u8)D_800D2B42;
    GbAudio_QueueRegisterWrite(0xFF16, value & 0xFF, 0);
  }
}
#endif

#ifdef VERSION_US
void func_800337D8(s32 arg0) { s32 *p = &arg0; func_80033864(arg0 & 0xFF); }
#endif

#ifdef VERSION_US
extern void GbAudio_QueueRegisterWrite(u16, u8, u16);
extern u8 D_800D2B43;
void func_800337FC(void) {
    s32 var_s0;

    var_s0 = 0x20;
    do {
        GbAudio_QueueRegisterWrite(var_s0, 0, 0);
        var_s0 += 1;
    } while (var_s0 != 0x30);
    GbAudio_QueueRegisterWrite(0xFF1C, ((D_800D2B43 & 0xF0) * 2) & 0xFF, 0);
}
#endif

#ifdef VERSION_US
void func_80033864(s32 arg0) {}
#endif

#ifdef VERSION_US
void func_8003386C(s32 arg0) { s32 *p = &arg0; GbAudio_UpdateNoiseRegisters(arg0 & 0xFF); }
#endif

#ifdef VERSION_US
extern u8 D_800D2B8C;
extern void GbAudio_QueueChannelReset(u16);
void GbAudio_UpdateNoiseRegisters(u8 channel) {
    s32 flags = (&D_800D2B8C)[channel * 0x3C];
    if (flags & 0x20) {
        s32 value;
        value = GbAudio_GetRegisterValue(0xFF26);
        value &= 0x87;
        GbAudio_QueueRegisterWrite(0xFF26, value, 0);
        GbAudio_QueueChannelReset(0xFF1F);
    } else if (flags & 0x10) {
        GbAudio_QueueRegisterWrite(0xFF20, 0x3F, 0);
        GbAudio_QueueRegisterWrite(0xFF21, D_800D2B43, 0);
        GbAudio_QueueRegisterWrite(0xFF22, D_800D2B44 & 0xFF, 0);
        GbAudio_QueueRegisterWrite(0xFF23, 0x80, 0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033950.s")
#endif

#ifdef VERSION_US
void func_800339DC(u8 arg0) {}
#endif

void func_800339E4(void) {
}

#ifdef VERSION_US
extern void func_80033B04(u8);
extern void func_80033A78(u8 arg0);
extern void func_80033ACC(u8 arg0);
extern u8 D_800D2B78;
void func_800339EC(u8 arg0) { if ((s32)(&D_800D2B78 + arg0 * 0x3C)[4] & 4) { func_80033A78(arg0); } if ((s32)(&D_800D2B78 + arg0 * 0x3C)[4] & 0x10) { func_80033ACC(arg0); } if ((s32)(&D_800D2B78 + arg0 * 0x3C)[4] & 1) { func_80033B04(arg0); } }
#endif

#ifdef VERSION_US
extern s8 D_800D2B42;
extern u8 D_800D2B78;
void func_80033A78(u8 arg0) {
    s32 value;
    s32 offset;
    s32 high;

    offset = arg0 * 0x3C;
    value = (&D_800D2B78)[offset + 0x25];
    high = (value & 0xC0) >> 6;
    value <<= 2;
    value |= high;
    (&D_800D2B78)[offset + 0x25] = value;
    value &= 0xC0;
    D_800D2B42 = value;
    (&D_800D2B78)[offset + 0x14] |= 1;
}
#endif

#ifdef VERSION_US
void func_80033ACC(u8 arg0) {
    D_800D2B44 += *(s16 *)((u8 *)&D_800D2BA8 + (arg0 * 0x3C));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033B04.s")
#endif

#ifdef VERSION_US
extern void func_80033C40(s32);
void func_80033BF4(u8 index) {
    if ((&D_800D2B78 + index * 0x3C)[4] & 2) {
        func_80033C40(index);
    }
}
#endif

#ifdef VERSION_US
void func_80033C40(s32 arg0) {}
#endif

#ifdef VERSION_US
void func_80033C48(s32 arg0) {}
#endif

#ifdef VERSION_US
void func_80033C50(s32 arg0) {}
#endif

#ifdef VERSION_US
extern u8 D_800D2B49;
extern u8 D_800D2B68;
extern u8 D_800D2B6A;
void func_80033C58(u8 arg0) {
    if (arg0 != 4) return;
    *(s16 *)((u8 *)&D_800D2B78 + 0x15C) = 0;
    *(s16 *)((u8 *)&D_800D2B78 + 0x1D4) = 0;
    D_800D2B49 = D_800D2B68;
    D_800D2B68 = 0;
    D_800D2B6A = 0;
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B78;
extern u8 D_800D2C6B;
extern u8 func_800347E8(u8);
extern void func_80033ED8(u8, u8);
extern void GbAudio_ReadChannelParameters(u8, u8);
extern void func_80033ED0(void);
extern void func_800348C4(u8, u8);
extern s32 func_80034838(u8, u8, u8);
extern void func_800339DC(u8);
void GbAudio_ProcessChannelStream(u8 channel) {
    GbAudioStreamRecord *record = (GbAudioStreamRecord *)&D_800D2B78 + channel;
    s32 value;
    u8 command;
    u8 high;
    while (1) {
        value = (command = func_800347E8(channel));
        if (value == 0xFF) {
            if (record->flags_03 & 2) {
                goto dispatch_command;
            }
            if (!(channel < 4 && (D_800D2C6B & 1))) {
                if (record->flags_03 & 0x20) {
                    func_80033C58(channel);
                }
                if (channel == 4) {
                    GbAudio_QueueRegisterWrite(0xFF10, 0, 0);
                }
            }
            record->flags_03 &= 0xFFFE;
            record->flags_14 |= 0x20;
            record->unk_00 = 0;
            record->unk_02 = 0;
            return;
        }
        if (value >= 208) {
        dispatch_command:
            func_80033ED8(channel, command);
            continue;
        }
        if ((record->flags_03 & 8) || (record->flags_03 & 0x20)) {
            GbAudio_ReadChannelParameters(channel, command);
        } else if (record->flags_03 & 0x10) {
            func_80033ED0();
        } else {
            func_800348C4(channel, command & 0xF);
            high = (command >> 4) & 0xF;
            if (high == 0) {
                record->flags_14 |= 0x20;
            } else {
                record->unk_1A = high;
                record->unk_18 = func_80034838(channel, high, record->unk_1B);
                record->flags_14 |= 0x10;
                func_800339DC(channel);
            }
        }
        return;
    }
}
#endif

#ifdef VERSION_US
extern void func_800348C4(u8, u8);
extern u8 func_800347E8(u8 arg0);
void GbAudio_ReadChannelParameters(u8 channel, u8 value) {
    u8 high;
    u8 *record = &D_800D2B78 + channel * 0x3C;
    record[0x14] |= 0x10;
    func_800348C4(channel, value);
    record[0x17] = func_800347E8(channel);
    *(u16 *)(record + 0x18) = func_800347E8(channel);
    if (((u32)channel & 3) != 3) {
        high = func_800347E8(channel);
        *(u16 *)(record + 0x18) = *(u16 *)(record + 0x18) + (high << 8);
    }
}
#endif

void func_80033ED0(void) {
}

#ifdef VERSION_US
extern void (*D_800921E4[])(u8, u8);
void func_80033ED8(u8 a, u8 b) {
    D_800921E4[b](a, b);
}
#endif

#ifdef VERSION_US
void func_80033F14(s32 arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
void func_80033F20(u8 arg0, u8 arg1) {
    u8 *entry;

    entry = &D_800D2B78 + (arg0 * 0x3C);
    entry[3] &= 0xFFFD;
    *(s32 *)(entry + 8) = *(s32 *)(entry + 0xC);
}
#endif

#ifdef VERSION_US
void func_80033F5C(s32 arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
void func_80033F68(s32 arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033F74.s")
#endif

#ifdef VERSION_US
u8 func_800347E8(u8);
extern u8 D_800D2B8D;

void func_80034058(u8 arg0, s32 arg1) {
    *(&D_800D2B8D + (arg0 * 0x3C)) = func_800347E8(arg0);
}
#endif

#ifdef VERSION_US
void func_80034098(s32 arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
void func_800340A4(s32 arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
extern u8 D_800D2B69;
void func_800340B0(s32 arg0, s32 arg1) {
    D_800D2B69 = 1;
}
#endif

#ifdef VERSION_US
extern u8 func_800347E8(u8);
extern u8 D_800D2B78;
void func_800340C8(u8 arg0, s32 arg1) {
    s32 result;
    u8 *record;

    result = func_800347E8(arg0);
    record = &D_800D2B78 + arg0 * 0x3C;
    record[0x35] = result;
    record[4] |= 8;
}
#endif

#ifdef VERSION_US
extern u8 func_800347E8(u8);
extern u8 D_800D2B78;
void GbAudio_ReadPackedChannelParameters(u8 channel, u8 high) {
    u8 value;
    (&D_800D2B78 + channel * 0x3C)[4] |= 1;
    (&D_800D2B78 + channel * 0x3C)[5] &= ~1;
    value = func_800347E8(channel);
    (&D_800D2B78 + channel * 0x3C)[0x27] = value;
    (&D_800D2B78 + channel * 0x3C)[0x26] = value;
    value = func_800347E8(channel);
    high = (u8)((value & 0xF0U) >> 4);
    value &= 0xF;
    {
        u8 shifted = (u32)high >> 1;
        u8 wrapped = high & 1;
        wrapped <<= 4;
        (&D_800D2B78 + channel * 0x3C)[0x28] = shifted | wrapped;
    }
    {
        u8 repeated;
        repeated = value << 4;
        (&D_800D2B78 + channel * 0x3C)[0x29] = value | repeated;
    }
}
#endif

#ifdef VERSION_US
void func_800341BC(s32 arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
typedef struct {
    u8 prefix[4];
    u8 flags;
    u8 unknown05[0x2B];
    u16 value;
    u8 unknown32[0xA];
} ChannelWordRecord;
void AudioSeq_ReadWordParameter(u8 channel, s32 unused) {
    u8 high;
    u8 low;
    ((ChannelWordRecord *)(&D_800D2B78 + channel * 0x3C))->flags |= 0x10;
    high = func_800347E8(channel);
    low = func_800347E8(channel);
    ((ChannelWordRecord *)(&D_800D2B78 + channel * 0x3C))->value = (high << 8) + low;
}
#endif

#ifdef VERSION_US
extern u8 func_800347E8(u8);
extern u8 D_800D2B78;
void func_80034238(unsigned char arg0, s32 arg1)
{
  arg0 &= 0xFF;
  ((u8 *)&D_800D2B78 + (arg0 * 0x3C))[4] |= 0x40;
  ((u8 *)&D_800D2B78 + (arg0 * 0x3C))[0x32] = func_800347E8(arg0);
}
#endif

#ifdef VERSION_US
void func_8003428C(u8 index, s32 unused) {
    u8 result;
    (&D_800D2B78 + index * 0x3C)[4] |= 4;
    result = func_800347E8(index);
    result = (u8)((u32)result >> 2) | (u8)((result << 1) << 5);
    (&D_800D2B78 + index * 0x3C)[0x25] = result;
    (&D_800D2B78 + index * 0x3C)[0x16] = result & 0xC0;
}
#endif

#ifdef VERSION_US
extern u8 func_800347E8(u8);
extern u8 D_800D2B78;
void func_800342F4(char arg0, s32 arg1)
{
  arg0 &= 0xFF;
  ((u8 *)&D_800D2B78 + (arg0 * 0x3C))[4] |= 0x20;
  ((u8 *)&D_800D2B78 + (arg0 * 0x3C))[0x33] = func_800347E8(arg0);
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B78;
void func_80034348(u8 arg0, s32 arg1) {
    u8 *ptr;
    s32 value;

    ptr = &D_800D2B78 + arg0 * 0x3C;
    value = ptr[3];
    if (value & 8) {
        ptr[3] = value & ~8;
        return;
    }
    ptr[3] = value | 8;
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B56;
extern u8 D_800D2B78;
void func_80034394(u8 arg0, s32 arg1) {
    u8 *entry;

    entry = &D_800D2B78 + (arg0 * 0x3C);
    if (entry[3] & 0x10) {
        entry[3] = entry[3] & 0xFFEF;
    } else {
        entry[3] = entry[3] & 0xFFEF;
        D_800D2B56 = func_800347E8(arg0);
    }
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B57;
extern u8 D_800D2B78;
void func_800343FC(u8 arg0, s32 arg1) {
    u8 *entry;

    entry = &D_800D2B78 + (arg0 * 0x3C);
    if (entry[3] & 0x10) {
        entry[3] = entry[3] & 0xFFEF;
    } else {
        entry[3] = entry[3] & 0xFFEF;
        D_800D2B57 = func_800347E8(arg0);
    }
}
#endif

#ifdef VERSION_US
extern void func_8003455C(u8, s32);
extern u8 D_800D2BAE[];
void func_80034464(u8 arg0, u8 arg1) {
    s8 result = func_800347E8(arg0);
    D_800D2BAE[arg0 * 0x3C] = result;
    if ((arg0 & 3) != 3) {
        func_8003455C(arg0, arg1);
    }
}
#endif

#ifdef VERSION_US
extern s8 D_800D2B4B;

void func_800344C4(u8 arg0, s32 arg1) {
    void *temp_v1;

    D_800D2B4B = func_800347E8(arg0);
    temp_v1 = (arg0 * 0x3C) + &D_800D2B78;
    (*(u8 *)((u8 *)(temp_v1) + (0x14))) = (u8) ((*(u8 *)((u8 *)(temp_v1) + (0x14))) | 8);
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B8E;
void func_80034518(u8 arg0, s32 arg1)
{
  unsigned char new_var;
  new_var = (s8)func_800347E8(arg0);
  (&D_800D2B8E)[0x3C * arg0] = (new_var << 1) << 5;
}
#endif

#ifdef VERSION_US
u8 func_800347E8(u8);
extern u8 D_800D2B8F;

void func_8003455C(u8 arg0, s32 arg1) {
    *(&D_800D2B8F + (arg0 * 0x3C)) = func_800347E8(arg0);
}
#endif

#ifdef VERSION_US
extern void func_8003492C(u8, u16);
void func_8003459C(u8 arg0, s32 arg1) {
    struct { u8 pad[7]; u8 hi; } temp;
    s32 low;
    temp.hi = func_800347E8(arg0);
    low = func_800347E8(arg0);
    func_8003492C(arg0, (u16)((temp.hi << 8) + low));
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B93[];
void func_800345E8(s32 arg0, s32 arg1) {
    s32 *p0 = &arg0;
    s32 *p1 = &arg1;
    arg0 = *p0 & 0xFF;
    *(u8 *)(D_800D2B93 + (arg0 * 0x3C)) = *p1 & 7;
}
#endif

#ifdef VERSION_US
u8 func_800347E8(u8);
extern u8 D_800D2B94;

void func_80034614(u8 arg0, s32 arg1) {
    *(&D_800D2B94 + (arg0 * 0x3C)) = func_800347E8(arg0);
}
#endif

#ifdef VERSION_US
extern u8 D_80092520;
extern void func_800346A4(u8, u8);
void func_80034654(u8 arg0, u8 arg1) {
    if (D_80092520 & 0x20) {
        func_800346A4(arg0, arg1);
    } else {
        func_800347E8(arg0);
    }
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B78;
void func_800346A4(u8 arg0, u8 arg1) {
    extern void func_80034A50(u8);
    func_80034A50(arg0);
    (&D_800D2B78 + arg0 * 0x3C)[0x24] &= func_800347E8(arg0);
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B59;
extern u8 D_800D2B49;
void func_800346F8(u8 arg0, s32 arg1) {
    s8 result = func_800347E8(arg0);
    if (D_800D2B59 == 0) D_800D2B49 = result;
}
#endif

#ifdef VERSION_US
extern u16 D_800D2B9A;
void func_8003492C(u8, u16);
extern u8 func_800347E8(u8 arg0);
void func_80034738(u8 arg0, s32 arg1) {
    s32 result = func_800347E8(arg0);
    u16 value = result;
    if (result >= 0x80) value = result + 0xFF00;
    value += *(u16 *)((u8 *)&D_800D2B9A + arg0 * 0x3C);
    func_8003492C(arg0, value);
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B6A;
void func_800347A4(s32 arg0, s32 arg1) {
    D_800D2B6A = 1;
}
#endif

#ifdef VERSION_US
void func_800347BC(s32 arg0, s32 arg1) {
    D_800D2B6A = 0;
}
#endif

#ifdef VERSION_US
void func_800347D0(s32 arg0, s32 arg1) { }
#endif

#ifdef VERSION_US
void func_800347DC(s32 arg0, s32 arg1) { }
#endif

#ifdef VERSION_US
extern u8 func_80034D98(const u8 *);
u8 func_800347E8(u8 arg0) {
    u8 *entry = &D_800D2B78 + arg0 * 0x3C;
    u8 result = func_80034D98(*(const u8 **)(entry + 8));
    *(u8 **)(entry + 8) += 1;
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034838.s")
#endif

#ifdef VERSION_US
extern u8 D_800D2B78;
void func_800348C4(u8 arg0, u8 arg1)
{
  u8 product;
  u32 value;
  u8 *entry;
  arg1++;
  product = (*(((&D_800D2B78) + (arg0 * 0x3C)) + 0x36)) * arg1;
  entry = (&D_800D2B78) + (arg0 * 0x3C);
  value = (product * (*((u16 *) (entry + 0x22)))) + entry[0x1E];
  entry[0x1E] = value;
  entry[0x1D] = (((unsigned short) value) & 0xFF00) >> 8;
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B78;
void func_8003492C(u8 arg0, u16 arg1) {
    u32 first;
    u32 last;
    u32 i;
    u8 *record;

    if (arg0 >= 4) {
        first = 4;
        last = 7;
    } else {
        first = 0;
        last = 3;
    }
    for (i = first; i <= last; i++) {
        record = (u8 *)&D_800D2B78 + i * 0x3C;
        *(u16 *)(record + 0x22) = arg1;
        record[0x1E] = 0;
    }
}
#endif

#ifdef VERSION_US
extern void func_80034A50(u8);
void func_80034A08(u8 arg0) {
    void *temp_v0;

    func_80034A50(arg0);
    temp_v0 = (arg0 * 0x3C) + &D_800D2B78;
    (*(u8 *)((u8 *)(temp_v0) + (3))) = (u8) ((*(u8 *)((u8 *)(temp_v0) + (3))) | 1);
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B9C[];
extern u8 * func_80034DA0(void);
void func_80034A50(u8 arg0) {
    u8 *table;
    u8 offset;

    table = func_80034DA0();
    offset = arg0 & 3;
    D_800D2B9C[arg0 * 0x3C] = *(offset + table);
}
#endif

#ifdef VERSION_US
extern u16 D_800D2B4C;

void func_80034A94(u16 arg0) {
    func_800331C8();
    D_800D2B4C = arg0;
}
#endif

#ifdef VERSION_US
extern const u8 *D_80094454[];
extern u8 GbAudio_StartSequenceChannel(const u8 *command);
extern u8 func_80034CF8(const u8 *arg0);
extern u8 D_800D2B49;
extern u8 D_800D2B68;
extern u8 D_800D2B6A;
extern u8 D_800D2B78;
void GbAudio_StartSequence(u16 sequence, u16 parameter, u16 volume)
{
  OSIntMask saved;
  const u8 *header;
  const u8 *entry;
  u8 count;
  u32 i;
  saved = osSetIntMask(0x00000001);
  func_800331C8();
  osSetIntMask(saved);
  GbAudio_QueueRegisterWrite(0xFF26, 0x8F, 0);
  header = D_80094454[sequence];
  count = ((func_80034CF8(header) >> 6) & 3) + 1;
  i = 0;
  if (count != 0)
  {
    entry = header;
    do
    {
      u8 channel = GbAudio_StartSequenceChannel(entry);
      u8 *record = (&D_800D2B78) + (channel * 0x3C);
      *((u16 *) (record + 0x30)) = parameter;
      saved = channel;
      record[3] |= 0x20;
      record[4] |= 0x10;
      if ((s32)(saved & 3) < 3)
      {
        *((u16 *) (((&D_800D2B78) + (channel * 0x3C)) + 0x22)) = volume;
      }
      func_80034A08(channel);
      entry += 8;
      i++;
    }
    while (i < count);
  }
  if (D_800D2B68 == 0)
  {
    D_800D2B68 = D_800D2B49;
    D_800D2B49 = 0x77;
  }
  D_800D2B6A = 1;
  saved = osSetIntMask(0x00000001);
  func_800331B8();
  osSetIntMask(saved);
}
#endif

#ifdef VERSION_US
void func_80034C48(s32 arg0) { }
#endif

#ifdef VERSION_US
void func_80034C50(s32 arg0) { }
#endif

#ifdef VERSION_US
extern u8 D_800D2B4E;
extern u8 func_80034CF8(const u8 *arg0);
u8 GbAudio_StartSequenceChannel(const u8 *command) {
    u8 value;
    u8 channel;
    u8 *record;
    value = func_80034CF8(command);
    channel = value & 7;
    record = &D_800D2B78 + channel * 0x3C;
    record[3] &= ~1;
    func_80032E40(channel);
    record = &D_800D2B78 + channel * 0x3C;
    *(u16 *)(record + 0x22) = 0x100;
    record[0x36] = 1;
    *(u32 *)(record + 8) = *(const u32 *)(command + 4);
    *(u16 *)record = D_800D2B4C;
    record[2] = D_800D2B4E;
    return channel;
}
#endif

#ifdef VERSION_US
u8 func_80034CF8(const u8 *arg0) { return arg0[0]; }
#endif

#ifdef VERSION_US
void GbAudio_QueueChannelReset(u16 address) {
    GbAudio_QueueRegisterWrite(address++, 0, 0);
    GbAudio_QueueRegisterWrite(address++, 0, 0);
    GbAudio_QueueRegisterWrite(address++, 8, 0);
    GbAudio_QueueRegisterWrite(address++, 0, 0);
    GbAudio_QueueRegisterWrite(address, 128, 0);
}
#endif

#ifdef VERSION_US
u8 func_80034D98(const u8 *arg0) { return arg0[0]; }
#endif

#ifdef VERSION_US
extern u8 D_80092520; extern u8 D_800925E4[]; extern u8 D_800925E8[]; u8 *func_80034DA0(void) { if (D_80092520 & 0x20) return D_800925E8; return D_800925E4; }
#endif

#ifdef VERSION_US
extern void GbAudio_ResetState(void); void func_80034DD0(void) { GbAudio_ResetState(); }
#endif

#ifdef VERSION_US
extern void func_800331D4(void); void func_80034DF0(void) { func_800331D4(); }
#endif

#ifdef VERSION_US
u8 func_80034E10(const u8 *arg0, s32 unused) { return arg0[0]; }
#endif

#ifdef VERSION_US
extern void GbAudio_ResetState(void);
extern void func_80034A94(u16 arg0);
void func_80034E1C(u16 arg0) {
    if (arg0 & 0xFF) {
        func_80034A94(arg0);
    } else {
        GbAudio_ResetState();
    }
}
#endif

#ifdef VERSION_US
typedef struct Func80034E5CRecord {
    u8 unk0;
    u8 pad1;
    u16 unk2;
    u16 unk4;
} Func80034E5CRecord;
extern Func80034E5CRecord D_80092620[];
extern void GbAudio_StartSequence(u16, u16, u16);
void func_80034E5C(s32 arg0, s32 arg1)
{
    s32 *input;
    Func80034E5CRecord *record;
    input = &arg0;
    arg1 = *input & 0xFFFF;
    record = &D_80092620[arg1];
    GbAudio_StartSequence(record->unk0, record->unk2, record->unk4);
}
#endif

#ifdef VERSION_US
void func_80034EA4(void) { D_800D2B49 = 0x77; }
#endif

#ifdef VERSION_US
void func_80034EB4(void) { D_800D2B49 = 0x33; }
#endif

#ifdef VERSION_US
extern u8 D_800D2B49; void func_80034EC4(void) { D_800D2B49 = 0; }
#endif

#ifdef VERSION_US
void func_80034ED0(void) { D_800D2B59 = 4; }
#endif

#ifdef VERSION_US
void func_80034EE0(void) { D_800D2B59 = 0x84; }
#endif

#ifdef VERSION_US
void func_80034EF0(s32 arg0)
{
  s32 var_s0;
  var_s0 = arg0 & 0xFF;
  if (var_s0 != 0)
  {
    do
    {
      var_s0 = ((unsigned long) (var_s0 - 1)) & 0xFF;
      func_80034DF0();
    }
    while (var_s0 != 0);
    if (arg0)
    {
    }
  }
}
#endif

#ifdef VERSION_US
u8 GbAudio_GetActiveChannelMask(void) {
    u8 mask = 0;
    s32 channel;
    for (channel = 0; channel < 8; channel++) {
        if ((&D_800D2B78 + channel * 0x3C)[3] & 1) {
            mask |= 1 << channel;
        }
    }
    return mask;
}
#pragma C_FUNCTION_PADDING(12)
#endif

#ifdef VERSION_US
extern s32 D_80094570;

void func_80034FE0(void) {
    if ((s8) D_80090B8C != 0) {
        func_80034DF0();
    }
    D_80094570 += 1;
}
#endif

#ifdef VERSION_US
extern OSMesgQueue D_800D2D60;
extern OSPiHandle *D_800D2D78;
extern void *D_800D2D7C;
void func_80035020(s32 arg0) {
    if (arg0 != 1) {
        D_800D2D78 = osCartRomInit();
    }
    osCreateMesgQueue(&D_800D2D60, &D_800D2D7C, 1);
}
#endif

#ifdef VERSION_US
extern OSMesgQueue D_800D2D60;
extern OSPiHandle *D_800D2D78;
void Audio_ReadRomBlocking(u32 rom, u8 *destination, u32 remaining) {
    OSIoMesg message;
    u32 currentRom = rom;
    u8 *currentDestination = destination;
    u32 chunk;
    while (remaining != 0) {
        if (remaining > 0x4000) chunk = 0x4000;
        else chunk = remaining;
        message.hdr.pri = OS_MESG_PRI_NORMAL;
        message.hdr.retQueue = &D_800D2D60;
        message.dramAddr = currentDestination;
        message.devAddr = currentRom;
        message.size = chunk;
        osInvalDCache(currentDestination, chunk);
        osEPiStartDma(D_800D2D78, &message, OS_READ);
        osRecvMesg(&D_800D2D60, NULL, OS_MESG_BLOCK);
        remaining -= chunk;
        currentRom += chunk;
        currentDestination += chunk;
    }
}
#pragma C_FUNCTION_PADDING(4)
#endif

#ifdef VERSION_US
extern s32 D_80094850; void func_80035140(s32 value) { D_80094850 = value; }
#endif

#ifdef VERSION_US
s32 func_8003514C(void) { return (s32)D_80094850; }
#pragma C_FUNCTION_PADDING(8)
#endif

#ifdef VERSION_US
extern s32 D_80094870[];
s32 func_80035160(s32 index) { return D_80094870[index]; }
#endif

#ifdef VERSION_US
typedef struct {
    OSMesg message;
    OSMesgQueue queue;
    u16 unknown1C;
    u16 unknown1E;
    OSTask task;
    u8 unknown60[8];
} AudioThreadTaskBuffer;
extern AudioThreadTaskBuffer D_80122A48[2];
extern OSThread D_80122B20;
extern s32 D_80122A40;
extern s32 D_80122B18;
extern u32 D_800CD020[];
extern s32 D_8009486C;
extern void __osSetFpcCsr(s32);
extern void Sched_InitClientQueue(void *, s32, s32);
extern void func_80005568(void *);
extern OSMesg func_80004F34(u8 *);
extern void profiler_log_thread4_time(void);
extern void Audio_InitializeTaskState(void);
extern s32 Audio_BuildSchedulerTask(void);
extern void Sched_SubmitTask(void *, s32);
extern OSMesgQueue D_80122A4C;
extern OSMesgQueue D_80122AB4;
extern OSMesg D_80122AB0;

void Audio_ThreadMain(void *unused) {
    OSTask *task;
    s32 tick;
    __osSetFpcCsr(0x01000C01);
    Sched_InitClientQueue(&D_80122B20, 1, 1);
    func_80005568(&D_80122B20);
    D_80122A40 = 1;
    D_80122B18 = 0;
    osCreateMesgQueue(&D_80122A4C, &D_80122A48[0].message, 1);
    osCreateMesgQueue(&D_80122AB4, &D_80122AB0, 1);
    osSendMesg(&D_80122A4C, (OSMesg)0x444F4E45, OS_MESG_NOBLOCK);
    osSendMesg(&D_80122AB4, (OSMesg)0x444F4E45, OS_MESG_NOBLOCK);
    Audio_InitializeTaskState();
    func_80025C50(2);
    while (1) {
        func_80004F34((u8 *)&D_80122B20);
        profiler_log_thread4_time();
        if (D_80122A40 != 0 && *(s16 *)((u8 *)D_800CD020 + 0xA38) < 21) {
            task = (OSTask *)Audio_BuildSchedulerTask();
            if (task != NULL) {
                D_80122A48[D_80122B18].task = *task;
                Sched_SubmitTask(&D_80122A48[D_80122B18], 0);
            }
        }
        D_80122B18 ^= 1;
        profiler_log_thread4_time();
        tick = D_8009486C;
        D_8009486C = tick + 1;
    }
}
#endif

#ifdef VERSION_US
extern void Audio_ThreadMain(void *);
extern OSThread D_80122B20;
extern u8 D_80124D00[];
void Thread4_CreateThread(void) {
    osCreateThread(&D_80122B20, 4, Audio_ThreadMain, NULL, D_80124D00, 0x50);
    osStartThread(&D_80122B20);
}
#endif

#ifdef VERSION_US
extern void func_80021BBC(void);
void func_8003539C(void) {
    func_80021BBC();
}
#endif

#ifdef VERSION_US
extern s32 func_80025C9C(void);
extern s32 D_80122A40;
s32 Audio_StopProcessing(void) {
    func_80025C9C();
    D_80122A40 = 0;
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 func_80025D44(void);
s32 Audio_WaitForPendingTasks(void) {
    s32 completed = 0;

    while (func_80025D44() != 0) {
        completed++;
    }
    return completed;
}
#endif

#ifdef VERSION_US
extern void *func_80008494();
void func_80035424(s32 arg0) {
    s32 value = arg0;
    void *entry = func_80008494();
    if (entry != 0) {
        value = arg0;
        value *= *(s8 *)((u8 *)entry + 0x10);
    }
    func_80025CBC(value);
}
#endif

#ifdef VERSION_US
void Audio_SetProcessingEnabled(s32 enabled) { D_80122A40 = enabled ? 0 : 1; }
#endif

#ifdef VERSION_US
extern s32 D_80094860;
void Audio_ResetModeSelector(void) {
    D_80094860 = -1;
}
#endif

#ifdef VERSION_US
extern s32 D_80094868;
void Audio_EnableModeFlag(void) {
    D_80094868 = 1;
}
#endif

#ifdef VERSION_US
extern void func_800260C0(s32, s32, s32);
extern void func_800262F0(void);
s32 Audio_SetModeBlocking(s32 mode, s32 arg1, s32 arg2) {
    s32 changed = 0;
    s32 tick;
    s32 readyTick;
    if (mode == 2) {
        if (D_80094868 != 0) {
            D_80094868 = 0;
            mode = 11;
        }
    }
    if (mode != D_80094860) {
        D_80094860 = mode;
        changed = 1;
        do {
            tick = *(volatile s32 *)&D_8009486C;
            func_8003539C();
            while (tick == *(volatile s32 *)&D_8009486C) {
            }
        } while (func_80025D44() != 0);
        func_800260C0(mode, arg1, arg2);
        while (func_80026298() == 0) {
            readyTick = *(volatile s32 *)&D_8009486C;
            while (readyTick == *(volatile s32 *)&D_8009486C) {
            }
        }
        func_800262F0();
        if (D_80094860 == 11) {
            D_80094860 = 2;
        }
    }
    return changed;
}
#endif

#ifdef VERSION_US
extern s32 D_80094864;
void Audio_ResetRequestId(void) {
    D_80094864 = -1;
}
#endif

#ifdef VERSION_US
s32 Audio_RequestIfChanged(s32 requestId) {
    if (requestId != D_80094864) {
        D_80094864 = requestId;
        func_80021ED8(requestId);
    }
    return 0;
}
#pragma C_FUNCTION_PADDING(4)
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035620.s")
#endif

#ifdef VERSION_US
s32 func_800356CC(s32 arg0) { s32 result = 0; if (arg0 >= 0 && arg0 < 19) result = *((s32 *)((u8 *)D_80124D00 + arg0 * 4)); return result; }
#pragma C_FUNCTION_PADDING(12)
#endif

#ifdef VERSION_US
extern u32 D_80124D50;
void func_80035700(u32 seed) {
    D_80124D50 = seed;
}
#endif

#ifdef VERSION_US
u32 func_8003570C(void) {
    D_80124D50 = D_80124D50 * 0x0019660D + 0x3C6EF35F;
    return D_80124D50;
}
#endif

#ifdef VERSION_US
typedef struct { u8 r, g, b, a; } Color3573C;
Color3573C *Color_SetRGB(Color3573C *arg0, u8 r, u8 g, u8 b) {
    arg0->r = r;
    arg0->g = g;
    arg0->b = b;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { u8 r, g, b, a; } Color3575C;
Color3575C *Color_SetRGBA(Color3575C *arg0, u8 r, u8 g, u8 b, u8 a) {
    arg0->r = r;
    arg0->g = g;
    arg0->b = b;
    arg0->a = a;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f35784;
Vec3f35784 *Vec3f_SetComponents(Vec3f35784 *arg0, f32 x, f32 y, f32 z) {
    arg0->x = x;
    arg0->y = y;
    arg0->z = z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef Vec3f35784 Vec3f357A8;
Vec3f357A8 *Vec3f_SetComponentsDuplicate(Vec3f357A8 *arg0, f32 x, f32 y, f32 z) {
    arg0->x = x;
    arg0->y = y;
    arg0->z = z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f357CC;
Vec3f357CC *Vec3f_AddInPlace(Vec3f357CC *arg0, Vec3f357CC *arg1) {
    arg0->x += arg1->x;
    arg0->y += arg1->y;
    arg0->z += arg1->z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f35804;
Vec3f35804 *Vec3f_Add(Vec3f35804 *arg0, Vec3f35804 *arg1, Vec3f35804 *arg2) {
    arg0->x = arg1->x + arg2->x;
    arg0->y = arg1->y + arg2->y;
    arg0->z = arg1->z + arg2->z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f3583C;
Vec3f3583C *Vec3f_SubtractInPlace(Vec3f3583C *arg0, Vec3f3583C *arg1) {
    arg0->x -= arg1->x;
    arg0->y -= arg1->y;
    arg0->z -= arg1->z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f35874;
Vec3f35874 *Vec3f_Subtract(Vec3f35874 *arg0, Vec3f35874 *arg1, Vec3f35874 *arg2) {
    arg0->x = arg1->x - arg2->x;
    arg0->y = arg1->y - arg2->y;
    arg0->z = arg1->z - arg2->z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f358AC;
typedef struct { s16 x, y, z; } Vec3s358AC;
Vec3f358AC *Vec3f_FromVec3s(Vec3f358AC *arg0, Vec3s358AC *arg1) {
    arg0->x = arg1->x;
    arg0->y = arg1->y;
    arg0->z = arg1->z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f358F0;
Vec3f358F0 *Vec3f_CrossProductFromPoints(Vec3f358F0 *arg0, Vec3f358F0 *arg1, Vec3f358F0 *arg2, Vec3f358F0 *arg3) {
    arg0->x = ((arg2->y - arg1->y) * (arg3->z - arg2->z)) - ((arg3->y - arg2->y) * (arg2->z - arg1->z));
    arg0->y = ((arg2->z - arg1->z) * (arg3->x - arg2->x)) - ((arg3->z - arg2->z) * (arg2->x - arg1->x));
    arg0->z = ((arg2->x - arg1->x) * (arg3->y - arg2->y)) - ((arg3->x - arg2->x) * (arg2->y - arg1->y));
    return arg0;
}
#endif

#ifdef VERSION_US
typedef Vec3f35784 Vec3f359A0;

Vec3f359A0 *Vec3f_CrossProduct(Vec3f359A0 *out, Vec3f359A0 *a, Vec3f359A0 *b) {
    out->x = (a->y * b->z) - (b->y * a->z);
    out->y = (a->z * b->x) - (b->z * a->x);
    out->z = (a->x * b->y) - (b->x * a->y);
    return out;
}
#endif

#ifdef VERSION_US
typedef Vec3f35784 Vec3f35A10;
Vec3f35A10 *func_80035A10(Vec3f35A10 *arg0) {
    f32 scale = 1.0f / sqrtf((arg0->x * arg0->x) + (arg0->y * arg0->y) + (arg0->z * arg0->z));
    arg0->x *= scale; arg0->y *= scale; arg0->z *= scale; return arg0;
}
#endif

#ifdef VERSION_US
void *Vec3s_SetComponents(void *arg0, s16 arg1, s16 arg2, s16 arg3) {
    (*(s16 *)((u8 *)(arg0) + (0))) = arg1;
    (*(s16 *)((u8 *)(arg0) + (2))) = arg2;
    (*(s16 *)((u8 *)(arg0) + (4))) = arg3;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { s16 x, y, z; } Vec3s35AA0;
Vec3s35AA0 *Vec3s_AddInPlace(Vec3s35AA0 *arg0, Vec3s35AA0 *arg1) {
    arg0->x += arg1->x; arg0->y += arg1->y; arg0->z += arg1->z; return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { s16 x, y, z; } Vec3s35AD8;
Vec3s35AD8 *Vec3s_Add(Vec3s35AD8 *arg0, Vec3s35AD8 *arg1, Vec3s35AD8 *arg2) {
    arg0->x = arg1->x + arg2->x; arg0->y = arg1->y + arg2->y; arg0->z = arg1->z + arg2->z; return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { s16 x, y, z; } Vec3s35B10;
Vec3s35B10 *Vec3s_SubtractInPlace(Vec3s35B10 *arg0, Vec3s35B10 *arg1) {
    arg0->x -= arg1->x; arg0->y -= arg1->y; arg0->z -= arg1->z; return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { s16 x, y, z; } Vec3s35B48;
Vec3s35B48 *Vec3s_Subtract(Vec3s35B48 *arg0, Vec3s35B48 *arg1, Vec3s35B48 *arg2) {
    arg0->x = arg1->x - arg2->x; arg0->y = arg1->y - arg2->y; arg0->z = arg1->z - arg2->z; return arg0;
}
#endif

#ifdef VERSION_US
#define ROUND_MAX(x) ((x) + ((x) > 0.0f ? 0.5f : -0.5f))
typedef struct { s16 x, y, z; } Vec3s35B80;
typedef struct { f32 x, y, z; } Vec3f35B80;
Vec3s35B80 *Vec3s_FromVec3f(Vec3s35B80 *arg0, Vec3f35B80 *arg1) {
    arg0->x = ROUND_MAX(arg1->x); arg0->y = ROUND_MAX(arg1->y); arg0->z = ROUND_MAX(arg1->z); return arg0;
}
#endif

#ifdef VERSION_US
void MtxF_Copy(u32 *dest, u32 *src) {
    if (dest != src) {
        s32 i; u32 *d = dest; u32 *s = src;
        for (i = 0; i < 16; i++) { *d++ = *s++; }
    }
}
#endif

#ifdef VERSION_US
void MtxF_Identity(f32 *arg0) {
    s32 i;
    f32 *dest;
    for (dest = arg0 + 1, i = 0; i < 14; dest++, i++) { *dest = 0.0f; }
    for (dest = arg0, i = 0; i < 4; dest += 5, i++) { *dest = 1.0f; }
}
#endif

#ifdef VERSION_US
extern void MtxF_Identity(f32 *arg0);
void MtxF_SetTranslation(f32 *dest, f32 *source) {
    MtxF_Identity(dest);
    dest[12] = source[0];
    dest[13] = source[1];
    dest[14] = source[2];
}
#endif

#ifdef VERSION_US
typedef struct S1_Vec3s S1_Vec3s;
struct S1_Vec3s {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
};
typedef float S1_MtxF_t[4][4];
typedef union {
    S1_MtxF_t mf;
    struct {
        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
    };
} S1_MtxF;
typedef struct S1_Vec3f S1_Vec3f;
struct S1_Vec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
};
#endif

#ifdef VERSION_US
extern f32 D_80087E50[];
extern f32 D_80088E50[0x1000];
void MtxF_SetLookAt(S1_MtxF *matrix, S1_Vec3f *from, S1_Vec3f *to, s16 view_angle) {
    f32 inverse_length;
    f32 dx;
    f32 dz;
    f32 x_col_y;
    f32 y_col_y;
    f32 z_col_y;
    f32 x_col_z;
    f32 y_col_z;
    f32 z_col_z;
    f32 x_col_x;
    f32 y_col_x;
    f32 z_col_x;

    dx = to->x - from->x;
    dz = to->z - from->z;

    inverse_length = -1.0 / sqrtf(dx * dx + dz * dz);
    dx *= inverse_length;
    dz *= inverse_length;

    y_col_y = D_80088E50[(u16)(view_angle) >> 4];
    x_col_y = D_80087E50[(u16)(view_angle) >> 4] * dz;
    z_col_y = -D_80087E50[(u16)(view_angle) >> 4] * dx;

    x_col_z = to->x - from->x;
    y_col_z = to->y - from->y;
    z_col_z = to->z - from->z;

    inverse_length = -1.0 / sqrtf(x_col_z * x_col_z + y_col_z * y_col_z + z_col_z * z_col_z);
    x_col_z *= inverse_length;
    y_col_z *= inverse_length;
    z_col_z *= inverse_length;

    x_col_x = y_col_y * z_col_z - z_col_y * y_col_z;
    y_col_x = z_col_y * x_col_z - x_col_y * z_col_z;
    z_col_x = x_col_y * y_col_z - y_col_y * x_col_z;

    inverse_length = 1.0 / sqrtf(x_col_x * x_col_x + y_col_x * y_col_x + z_col_x * z_col_x);

    x_col_x *= inverse_length;
    y_col_x *= inverse_length;
    z_col_x *= inverse_length;

    x_col_y = y_col_z * z_col_x - z_col_z * y_col_x;
    y_col_y = z_col_z * x_col_x - x_col_z * z_col_x;
    z_col_y = x_col_z * y_col_x - y_col_z * x_col_x;

    inverse_length = 1.0 / sqrtf(x_col_y * x_col_y + y_col_y * y_col_y + z_col_y * z_col_y);
    x_col_y *= inverse_length;
    y_col_y *= inverse_length;
    z_col_y *= inverse_length;

    matrix->mf[0][0] = x_col_x;
    matrix->mf[1][0] = y_col_x;
    matrix->mf[2][0] = z_col_x;
    matrix->mf[3][0] = -(from->x * x_col_x + from->y * y_col_x + from->z * z_col_x);

    matrix->mf[0][1] = x_col_y;
    matrix->mf[1][1] = y_col_y;
    matrix->mf[2][1] = z_col_y;
    matrix->mf[3][1] = -(from->x * x_col_y + from->y * y_col_y + from->z * z_col_y);

    matrix->mf[0][2] = x_col_z;
    matrix->mf[1][2] = y_col_z;
    matrix->mf[2][2] = z_col_z;
    matrix->mf[3][2] = -(from->x * x_col_z + from->y * y_col_z + from->z * z_col_z);

    matrix->mf[0][3] = 0.0f;
    matrix->mf[1][3] = 0.0f;
    matrix->mf[2][3] = 0.0f;
    matrix->mf[3][3] = 1.0f;
}
#endif

#ifdef VERSION_US
void MtxF_SetRotationTranslation(f32 matrix[4][4], Vec3s35AA0 *position, Vec3s35AA0 *rotation) {
    f32 sin_x;
    f32 cos_x;
    f32 sin_y;
    f32 cos_y;
    f32 sin_z;
    f32 cos_z;

    sin_x = D_80087E50[(u16)(rotation->x) >> 4];
    cos_x = D_80088E50[(u16)(rotation->x) >> 4];

    sin_y = D_80087E50[(u16)(rotation->y) >> 4];
    cos_y = D_80088E50[(u16)(rotation->y) >> 4];

    sin_z = D_80087E50[(u16)(rotation->z) >> 4];
    cos_z = D_80088E50[(u16)(rotation->z) >> 4];

    matrix[0][0] = cos_y * cos_z + (sin_x * sin_y) * sin_z;
    matrix[0][1] = -cos_y * sin_z + (sin_x * sin_y) * cos_z;
    matrix[0][2] = cos_x * sin_y;
    matrix[0][3] = position->x;

    matrix[1][0] = cos_x * sin_z;
    matrix[1][1] = cos_x * cos_z;
    matrix[1][2] = -sin_x;
    matrix[1][3] = position->y;

    matrix[2][0] = -sin_y * cos_z + (sin_x * cos_y) * sin_z;
    matrix[2][1] = sin_y * sin_z + (sin_x * cos_y) * cos_z;
    matrix[2][2] = cos_x * cos_y;
    matrix[2][3] = position->z;

    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
}
#endif

#ifdef VERSION_US
void MtxF_SetRotationTranslationF(f32 matrix[4][4], Vec3f35784 *position, Vec3s35AA0 *rotation) {
    f32 sin_y;
    f32 cos_y;
    f32 sin_z;
    f32 cos_z;
    f32 sin_x;
    f32 cos_x;
    f32 product;

    sin_x = D_80087E50[(u16)(rotation->x) >> 4];
    cos_x = D_80088E50[(u16)(rotation->x) >> 4];

    sin_y = D_80087E50[(u16)(rotation->y) >> 4];
    cos_y = D_80088E50[(u16)(rotation->y) >> 4];

    sin_z = D_80087E50[(u16)(rotation->z) >> 4];
    cos_z = D_80088E50[(u16)(rotation->z) >> 4];

    product = sin_x * sin_y;
    matrix[0][0] = (cos_y * cos_z) + (product * sin_z);
    matrix[1][0] = (-cos_y * sin_z) + (product * cos_z);
    matrix[2][0] = cos_x * sin_y;
    matrix[3][0] = position->x;

    matrix[0][1] = cos_x * sin_z;
    matrix[1][1] = cos_x * cos_z;
    matrix[2][1] = -sin_x;
    matrix[3][1] = position->y;

    product = sin_x * cos_y;
    matrix[0][2] = (-sin_y * cos_z) + (product * sin_z);
    matrix[1][2] = (sin_y * sin_z) + (product * cos_z);
    matrix[2][2] = cos_x * cos_y;
    matrix[3][2] = position->z;

    matrix[0][3] = 0.0f;
    matrix[1][3] = 0.0f;
    matrix[2][3] = 0.0f;
    matrix[3][3] = 1.0f;
}
#endif

#ifdef VERSION_US
void MtxF_SetRotationAndTransformTranslation(f32 matrix[4][4], Vec3f35784 *position, Vec3s35AA0 *rotation) {
    f32 sin_x;
    f32 cos_x;
    f32 sin_y;
    f32 cos_y;
    f32 sin_z;
    f32 cos_z;

    sin_x = D_80087E50[(u16)(rotation->x) >> 4];
    cos_x = D_80088E50[(u16)(rotation->x) >> 4];
    sin_y = D_80087E50[(u16)(rotation->y) >> 4];
    cos_y = D_80088E50[(u16)(rotation->y) >> 4];
    sin_z = D_80087E50[(u16)(rotation->z) >> 4];
    cos_z = D_80088E50[(u16)(rotation->z) >> 4];

    matrix[0][0] = (cos_y * cos_z) + ((sin_x * sin_y) * sin_z);
    matrix[0][1] = (-cos_y * sin_z) + ((sin_x * sin_y) * cos_z);
    matrix[0][2] = cos_x * sin_y;

    matrix[1][0] = cos_x * sin_z;
    matrix[1][1] = cos_x * cos_z;
    matrix[1][2] = -sin_x;

    matrix[2][0] = (-sin_y * cos_z) + ((sin_x * cos_y) * sin_z);
    matrix[2][1] = (sin_y * sin_z) + ((sin_x * cos_y) * cos_z);
    matrix[2][2] = cos_x * cos_y;

    matrix[3][0] = (matrix[0][0] * position->x) + (matrix[1][0] * position->y) + (matrix[2][0] * position->z);
    matrix[3][1] = (matrix[0][1] * position->x) + (matrix[1][1] * position->y) + (matrix[2][1] * position->z);
    matrix[3][2] = (matrix[0][2] * position->x) + (matrix[1][2] * position->y) + (matrix[2][2] * position->z);

    matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    matrix[3][3] = 1.0f;
}
#endif

#ifdef VERSION_US
void MtxF_SetRotationScaleTranslation(S1_MtxF *matrix, S1_Vec3f *position, S1_Vec3s *rotation, S1_Vec3f *scale) {
    f32 sin_x;
    f32 cos_x;
    f32 sin_y;
    f32 cos_y;
    f32 sin_z;
    f32 cos_z;

    sin_x = D_80087E50[(u16)(rotation->x) >> 4];
    cos_x = D_80088E50[(u16)(rotation->x) >> 4];

    sin_y = D_80087E50[(u16)(rotation->y) >> 4];
    cos_y = D_80088E50[(u16)(rotation->y) >> 4];

    sin_z = D_80087E50[(u16)(rotation->z) >> 4];
    cos_z = D_80088E50[(u16)(rotation->z) >> 4];

    matrix->mf[0][0] = (cos_y * cos_z) * scale->x;
    matrix->mf[0][1] = (cos_y * sin_z) * scale->x;
    matrix->mf[0][2] = (-sin_y) * scale->x;
    matrix->mf[0][3] = 0.0f;

    matrix->mf[1][0] = (sin_x * sin_y * cos_z - cos_x * sin_z) * scale->y;
    matrix->mf[1][1] = (sin_x * sin_y * sin_z + cos_x * cos_z) * scale->y;
    matrix->mf[1][2] = (sin_x * cos_y) * scale->y;
    matrix->mf[1][3] = 0.0f;

    matrix->mf[2][0] = (cos_x * sin_y * cos_z + sin_x * sin_z) * scale->z;
    matrix->mf[2][1] = (cos_x * sin_y * sin_z - sin_x * cos_z) * scale->z;
    matrix->mf[2][2] = (cos_x * cos_y) * scale->z;
    matrix->mf[2][3] = 0.0f;

    matrix->mf[3][0] = position->x;
    matrix->mf[3][1] = position->y;
    matrix->mf[3][2] = position->z;
    matrix->mf[3][3] = 1.0f;
}
#endif

#ifdef VERSION_US
void MtxF_SetRotationAndScaledTranslation(S1_MtxF *matrix, S1_Vec3f *position, S1_Vec3s *rotation, S1_Vec3f *scale) {
    f32 sin_x;
    f32 cos_x;
    f32 sin_y;
    f32 cos_y;
    f32 sin_z;
    f32 cos_z;

    sin_x = D_80087E50[(u16)(rotation->x) >> 4];
    cos_x = D_80088E50[(u16)(rotation->x) >> 4];

    sin_y = D_80087E50[(u16)(rotation->y) >> 4];
    cos_y = D_80088E50[(u16)(rotation->y) >> 4];

    sin_z = D_80087E50[(u16)(rotation->z) >> 4];
    cos_z = D_80088E50[(u16)(rotation->z) >> 4];

    matrix->mf[0][0] = cos_y * cos_z;
    matrix->mf[0][1] = cos_y * sin_z;
    matrix->mf[0][2] = -sin_y;
    matrix->mf[0][3] = 0.0f;

    matrix->mf[1][0] = sin_x * sin_y * cos_z - cos_x * sin_z;
    matrix->mf[1][1] = sin_x * sin_y * sin_z + cos_x * cos_z;
    matrix->mf[1][2] = sin_x * cos_y;
    matrix->mf[1][3] = 0.0f;

    matrix->mf[2][0] = cos_x * sin_y * cos_z + sin_x * sin_z;
    matrix->mf[2][1] = cos_x * sin_y * sin_z - sin_x * cos_z;
    matrix->mf[2][2] = cos_x * cos_y;
    matrix->mf[2][3] = 0.0f;

    matrix->mf[3][0] = position->x * scale->x;
    matrix->mf[3][1] = position->y * scale->y;
    matrix->mf[3][2] = position->z * scale->z;
    matrix->mf[3][3] = 1.0f;
}
#endif

#ifdef VERSION_US
void func_80036714(void *a0,s32 a1,s32 a2,s32 a3,f32 a4){f32 r0,r1,r2; r0=sqrtf(((f32*)a2)[0]*((f32*)a2)[0]+((f32*)a2)[1]*((f32*)a2)[1]+((f32*)a2)[2]*((f32*)a2)[2])*a4;r1=sqrtf(((f32*)a2)[4]*((f32*)a2)[4]+((f32*)a2)[5]*((f32*)a2)[5]+((f32*)a2)[6]*((f32*)a2)[6])*a4;r2=sqrtf(((f32*)a2)[8]*((f32*)a2)[8]+((f32*)a2)[9]*((f32*)a2)[9]+((f32*)a2)[10]*((f32*)a2)[10])*a4;((f32*)a0)[0]=((f32*)a1)[0]*r0;((f32*)a0)[1]=((f32*)a1)[4]*r0;((f32*)a0)[2]=((f32*)a1)[8]*r0;((f32*)a0)[3]=0;((f32*)a0)[4]=((f32*)a1)[1]*r1;((f32*)a0)[5]=((f32*)a1)[5]*r1;((f32*)a0)[6]=((f32*)a1)[9]*r1;((f32*)a0)[7]=0;((f32*)a0)[8]=((f32*)a1)[2]*r2;((f32*)a0)[9]=((f32*)a1)[6]*r2;((f32*)a0)[10]=((f32*)a1)[10]*r2;((f32*)a0)[11]=0;((f32*)a0)[12]=((f32*)a2)[0]*((f32*)a3)[0]+((f32*)a2)[4]*((f32*)a3)[1]+((f32*)a2)[8]*((f32*)a3)[2]+((f32*)a2)[12];((f32*)a0)[13]=((f32*)a2)[1]*((f32*)a3)[0]+((f32*)a2)[5]*((f32*)a3)[1]+((f32*)a2)[9]*((f32*)a3)[2]+((f32*)a2)[13];((f32*)a0)[14]=((f32*)a2)[2]*((f32*)a3)[0]+((f32*)a2)[6]*((f32*)a3)[1]+((f32*)a2)[10]*((f32*)a3)[2]+((f32*)a2)[14];((f32*)a0)[15]=1;}
#endif

#ifdef VERSION_US
void MtxF_SetOrthonormalBasis(f32 matrix[4][4], Vec3f35784 *up_direction, Vec3f35784 *position, s32 rotation_y) {
    Vec3f35784 reference;
    Vec3f35784 lateral;
    Vec3f35784 forward;
    Vec3f_SetComponentsDuplicate(&reference, D_80087E50[(u16)rotation_y >> 4], 0.0f, D_80088E50[(u16)rotation_y >> 4]);
    func_80035A10(up_direction);
    Vec3f_CrossProduct(&lateral, up_direction, &reference);
    func_80035A10(&lateral);
    Vec3f_CrossProduct(&forward, &lateral, up_direction);
    func_80035A10(&forward);
    matrix[0][0] = lateral.x;
    matrix[0][1] = lateral.y;
    matrix[0][2] = lateral.z;
    matrix[3][0] = position->x;
    matrix[1][0] = up_direction->x;
    matrix[1][1] = up_direction->y;
    matrix[1][2] = up_direction->z;
    matrix[3][1] = position->y;
    matrix[2][0] = forward.x;
    matrix[2][1] = forward.y;
    matrix[2][2] = forward.z;
    matrix[3][2] = position->z;
    matrix[0][3] = 0.0f;
    matrix[1][3] = 0.0f;
    matrix[2][3] = 0.0f;
    matrix[3][3] = 1.0f;
}
#endif

#ifdef VERSION_US
extern f32 D_80087E50[];
extern f32 D_80088E50[0x1000];
extern S1_Vec3f D_800948D0;
typedef union S1_Vec2s_s32 S1_Vec2s_s32;
union S1_Vec2s_s32 {
    struct {
        /* 0x0 */ s16 x;
        /* 0x2 */ s16 y;
    };
    s32 xy;
};
typedef union S1_Color_RGBA8_u32 S1_Color_RGBA8_u32;
union S1_Color_RGBA8_u32 {
    struct {
        u8 r, g, b, a;
    };
    u32 rgba;
};
typedef struct S1_GraphNode S1_GraphNode;
typedef struct S1_unk_D_86002F34_00C S1_unk_D_86002F34_00C;
typedef struct S1_unk_D_86002F34_00C_040 S1_unk_D_86002F34_00C_040;
typedef struct S1_unk_D_86002F34_00C_0CC S1_unk_D_86002F34_00C_0CC;
typedef struct S1_unk_D_86002F34_00C_060 S1_unk_D_86002F34_00C_060;
typedef struct S1_unk_D_86002F34_00C_024 S1_unk_D_86002F34_00C_024;
typedef struct S1_unk_D_86002F34_00C_018 S1_unk_D_86002F34_00C_018;
typedef s32 (*S1_func_D_86002F34_000_010)(s32, struct S1_GraphNode*);
extern void *func_80003240();
struct S1_GraphNode {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ struct S1_GraphNode* unk_04;
    /* 0x08 */ struct S1_GraphNode* unk_08;
    /* 0x0C */ struct S1_unk_D_86002F34_00C* unk_0C;
    /* 0x10 */ S1_func_D_86002F34_000_010 unk_10;
    /* 0x14 */ void* unk_14;
};
struct S1_unk_D_86002F34_00C_040 {
    /* 0x00 */ Mtx* mtx;
    /* 0x04 */ f32 l;
    /* 0x08 */ f32 r;
    /* 0x0C */ f32 b;
    /* 0x10 */ f32 t;
    /* 0x14 */ f32 n;
    /* 0x18 */ f32 f;
    /* 0x1C */ f32 scale;
};
struct S1_unk_D_86002F34_00C_0CC {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ S1_Color_RGBA8_u32 color;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ u8* texture;
};
struct S1_unk_D_86002F34_00C_024 {
    /* 0x00 */ Mtx* mtx;
    /* 0x04 */ u16 perspNorm;
    /* 0x08 */ f32 fovy;
    /* 0x0C */ f32 aspect;
    /* 0x10 */ f32 near;
    /* 0x14 */ f32 far;
    /* 0x18 */ f32 scale;
};
struct S1_unk_D_86002F34_00C_060 {
    /* 0x00 */ S1_MtxF* p_mtxf;
    /* 0x04 */ S1_MtxF mtxf;
    /* 0x44 */ LookAt* lookat;
    /* 0x48 */ S1_Vec3f eye;
    /* 0x54 */ S1_Vec3f at;
    /* 0x60 */ S1_Vec3f up;
};
struct S1_unk_D_86002F34_00C_018 {
    /* 0x00 */ Vp* vp;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 width;
    /* 0x0A */ s16 height;
};
struct S1_unk_D_86002F34_00C {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ S1_unk_D_86002F34_00C_018 unk_18;	//	viewPort
    /* 0x24 */ S1_unk_D_86002F34_00C_024 unk_24;	//	projection
    /* 0x40 */ S1_unk_D_86002F34_00C_040 unk_40;
    /* 0x60 */ S1_unk_D_86002F34_00C_060 unk_60;	//	camera
    /* 0xCC */ S1_unk_D_86002F34_00C_0CC unk_CC;
    /* 0xEC */ char unkEC[0x4];
};
extern Vtx *GeoOverlay_BuildFadeQuad(S1_unk_D_86002F34_00C_0CC *, S1_unk_D_86002F34_00C_040 *);
typedef struct S1_MainPoolState S1_MainPoolState;
typedef struct S1_MainPoolBlock S1_MainPoolBlock;
struct S1_MainPoolState {
    /* 0x00 */ s32 freeSpace;
    /* 0x04 */ S1_MainPoolBlock *listHeadL;
    /* 0x08 */ S1_MainPoolBlock *listHeadR;
    /* 0x0C */ struct S1_MainPoolState *prev;
};
typedef void (*S1_AllocateFunc)(struct S1_MainPoolBlock*, u32);
struct S1_MainPoolBlock {
    /* 0x00 */ struct S1_MainPoolBlock *prev;
    /* 0x04 */ struct S1_MainPoolBlock *next;
    /* 0x08 */ S1_AllocateFunc func;
    /* 0x0C */ s32 arg; // passed into func as the 2nd argument.
};
typedef struct S1_unk_D_86002F34_alt2 S1_unk_D_86002F34_alt2;
struct S1_unk_D_86002F34_alt2 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ S1_GraphNode* unk_18;
};
typedef struct S1_MemoryBlock S1_MemoryBlock;
struct S1_MemoryBlock {
    /* 0x00 */ struct S1_MemoryBlock *next;
    /* 0x04 */ u32 size;
};
typedef struct S1_unk_D_86002F34_alt13 S1_unk_D_86002F34_alt13;
struct S1_unk_D_86002F34_alt13 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
};
typedef struct S1_unk_D_86002F34_alt1 S1_unk_D_86002F34_alt1;
struct S1_unk_D_86002F34_alt1 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ s8 unk_1C;
    /* 0x1D */ s8 unk_1D;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ Lights7* lights;
};
typedef struct S1_unk_D_86002F34_alt14 S1_unk_D_86002F34_alt14;
struct S1_unk_D_86002F34_alt14 {
    /* 0x00 */ S1_GraphNode unk_00;
};
typedef struct S1_unk_D_86002F34_alt15 S1_unk_D_86002F34_alt15;
struct S1_unk_D_86002F34_alt15 {
    /* 0x00 */ S1_GraphNode unk_00;
};
typedef struct S1_unk_D_86002F34_alt16 S1_unk_D_86002F34_alt16;
struct S1_unk_D_86002F34_alt16 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ u32 unk_18;
};
typedef struct S1_unk_D_8690A610 S1_unk_D_8690A610;
typedef struct S1_unk_D_8690A610_018 S1_unk_D_8690A610_018;
typedef struct S1_unk_D_86002F58_004_000_000 S1_unk_D_86002F58_004_000_000;
typedef struct S1_unk_D_86002F58_004_000_00C S1_unk_D_86002F58_004_000_00C;
typedef struct S1_unk_D_86002F58_004_000_010 S1_unk_D_86002F58_004_000_010;
typedef struct S1_unk_D_86002F58_004_000_010_024 S1_unk_D_86002F58_004_000_010_024;
typedef union S1_arg1_func_80010CA8 S1_arg1_func_80010CA8;
typedef struct S1_unk_D_86002F58_004_000_004 S1_unk_D_86002F58_004_000_004;
typedef struct S1_unk_D_86002F58_004_000_00C_028 S1_unk_D_86002F58_004_000_00C_028;
struct S1_unk_D_8690A610_018 {
    /* 0x00 */ s16 fogNear; // GeoNode_CreateFog's arg2
    /* 0x02 */ s16 fogFar; // GeoNode_CreateFog's arg3
    /* 0x04 */ S1_Color_RGBA8_u32 fogColor;
};
struct S1_unk_D_86002F58_004_000_000 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ struct S1_unk_D_86002F58_004_000_000* unk_04;
    /* 0x08 */ struct S1_unk_D_86002F58_004_000_000* unk_08;
    /* 0x0C */ S1_unk_D_86002F58_004_000_00C* unk_0C;
    /* 0x10 */ S1_unk_D_86002F58_004_000_010* unk_10;
    /* 0x14 */ s32 unk_14;
};
struct S1_unk_D_8690A610 {
    /* 0x00 */ S1_unk_D_86002F58_004_000_000 unk_00;
    /* 0x18 */ S1_unk_D_8690A610_018 unk_18;
};
struct S1_unk_D_86002F58_004_000_004 {
    /* 0x00 */ struct S1_unk_D_86002F58_004_000_004* unk_00[4];
    /* 0x10 */ struct S1_unk_D_86002F58_004_000_00C* unk_10;
    /* 0x14 */ S1_unk_D_86002F58_004_000_010* unk_14;
};
typedef S1_unk_D_86002F58_004_000_00C_028* (*S1_unk_D_86002F58_004_000_00C_028_func)(s32, s32);
struct S1_unk_D_86002F58_004_000_00C {
    /* 0x00 */ S1_unk_D_86002F58_004_000_004 unk_00;
    /* 0x18 */ char unk_18[0x10];
    /* 0x28 */ S1_unk_D_86002F58_004_000_00C_028_func unk_28;
};
union S1_arg1_func_80010CA8 {
    struct {
        /* 0x00 */ s16 unk_00;
        /* 0x02 */ s8 unk_02;
        /* 0x03 */ s8 unk_03;
    };
    u32 raw;
};
struct S1_unk_D_86002F58_004_000_010 {
    /* 0x00 */ u8 configFlags; // PokeIcon_AllocFramebuffers's arg0: bit0=frame-load enabled, bit1=background-load enabled, bit2=double-buffered, bit3=quad-buffered
    /* 0x01 */ u8 pendingFlags; // bit0=frame load pending, bit1=background load pending (PokeIcon_RequestFrameLoad/RequestBackgroundLoad/ApplyLoadResult)
    /* 0x02 */ u8 activeVariant; // index into framebuffers[], flipped by configFlags bit2 in PokeIcon_RequestFrameLoad
    /* 0x04 */ s32 framebuffers[1]; // declared size undersells - up to 5 entries when configFlags bit3 is set (PokeIcon_AllocFramebuffers)
    /* 0x08 */ char pad8[0x10];
    /* 0x18 */ s32 backgroundBuffer; // PokeIcon_RequestBackgroundLoad's poolPtr
    /* 0x1C */ s32 frameResultSize; // PokeIcon_ApplyLoadResult's case 1: poolSize
    /* 0x20 */ s32 backgroundResultSize; // case 2: poolSize
    /* 0x24 */ S1_unk_D_86002F58_004_000_010_024* lastLoadedFragment; // case 1: result; PokeIcon_RequestFrameLoad reuses the load if this matches the requested species
    /* 0x28 */ s32 backgroundResult; // case 2: result
    /* 0x2C */ S1_arg1_func_80010CA8 colorAdjust; // cached alongside lastLoadedFragment for the reuse check
    /* 0x30 */ OSMesgQueue frameQueue;
    /* 0x48 */ OSMesg frameMsgBuf;
    /* 0x4C */ char pad4C[0x4];
    /* 0x50 */ OSMesgQueue backgroundQueue;
    /* 0x68 */ OSMesg backgroundMsgBuf;
    /* 0x6C */ char pad6C[0x4];
};
struct S1_unk_D_86002F58_004_000_010_024 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ char unk02[0x6];
    /* 0x08 */ struct S1_unk_D_86002F58_004_000_004* unk_08;
};
struct S1_unk_D_86002F58_004_000_00C_028 {
    /* 0x00 */ char pad0[4];
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char pad6[6];
    /* 0x0C */ s32* unk_0C;
    /* 0x10 */ s32* unk_10;
};
typedef struct S1_unk_D_86002F34_alt19 S1_unk_D_86002F34_alt19;
struct S1_unk_D_86002F34_alt19 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ u8 r;
    /* 0x19 */ u8 g;
    /* 0x1A */ u8 b;
};
typedef struct S1_unk_D_86002F34_alt12 S1_unk_D_86002F34_alt12;
struct S1_unk_D_86002F34_alt12 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
};
typedef struct S1_unk_D_86002F34_alt20 S1_unk_D_86002F34_alt20;
struct S1_unk_D_86002F34_alt20 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
};
typedef struct S1_unk_D_86002F34_alt21 S1_unk_D_86002F34_alt21;
struct S1_unk_D_86002F34_alt21 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
};
typedef struct S1_unk_D_86002F34_alt5 S1_unk_D_86002F34_alt5;
struct S1_unk_D_86002F34_alt5 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ S1_Vec3f unk_18;
    /* 0x24 */ S1_Vec3s unk_24;
};
typedef struct S1_unk_D_86002F34_alt22 S1_unk_D_86002F34_alt22;
struct S1_unk_D_86002F34_alt22 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ S1_Vec3f unk_18;
};
typedef struct S1_unk_D_86002F34_alt6 S1_unk_D_86002F34_alt6;
struct S1_unk_D_86002F34_alt6 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ S1_Vec3s unk_18;
    /* 0x1E */ S1_Vec3s unk_1E;
    /* 0x24 */ S1_Vec3f unk_24;
    /* 0x30 */ u8 unk_30;
    /* 0x31 */ u8 unk_31;
    /* 0x32 */ s16 unk_32;
};
typedef struct S1_unk_D_86002F34_alt7 S1_unk_D_86002F34_alt7;
struct S1_unk_D_86002F34_alt7 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ s16 unk_1C;
};
typedef struct S1_unk_D_86002F34_alt8 S1_unk_D_86002F34_alt8;
struct S1_unk_D_86002F34_alt8 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ S1_MtxF unk_1C;
};
typedef struct S1_unk_D_86002F34_alt9 S1_unk_D_86002F34_alt9;
struct S1_unk_D_86002F34_alt9 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ S1_Vec3f unk_1C;
    /* 0x28 */ f32 unk_28;
};
typedef struct S1_unk_func_80011B94 S1_unk_func_80011B94;
struct S1_unk_func_80011B94 {
    /* 0x00 */ S1_unk_D_86002F58_004_000_000 unk_00;
    /* 0x18 */ Gfx* displayList; // GeoNode_CreateDisplayList's arg3
};
typedef struct S1_unk_D_86002F34_alt10 S1_unk_D_86002F34_alt10;
struct S1_unk_D_86002F34_alt10 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ u8 unk_22;
    /* 0x24 */ S1_Color_RGBA8_u32 unk_24;
};
typedef struct S1_unk_D_86002F34_alt23 S1_unk_D_86002F34_alt23;
struct S1_unk_D_86002F34_alt23 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
};
typedef struct S1_unk_D_86002F34_alt24 S1_unk_D_86002F34_alt24;
struct S1_unk_D_86002F34_alt24 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ S1_Color_RGBA8_u32 unk_28;
};
extern Gfx* D_800D0510;
extern Mtx D_80094890;
typedef struct S1_unk_D_86002F34_alt3 S1_unk_D_86002F34_alt3;
struct S1_unk_D_86002F34_alt3 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s32 unk_1C;
};
typedef struct S1_unk_D_800ABCC0_008 S1_unk_D_800ABCC0_008;
typedef struct S1_unk_D_800ABCC0 S1_unk_D_800ABCC0;
typedef struct S1_unk_D_86002F58_004_000_040_004 S1_unk_D_86002F58_004_000_040_004;
struct S1_unk_D_800ABCC0_008 {
    /* 0x00 */ u8 translationKeyCount; // ModelAnim_EvaluateTranslationChannel: ==1 means a static (non-animated) value
    /* 0x01 */ u8 rotationKeyCount;
    /* 0x02 */ u8 scaleKeyCount;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u16 translationBaseIndex; // index into the context's translation value array
    /* 0x06 */ u16 rotationBaseIndex; // packed-bits index into the context's rotation value array
    /* 0x08 */ u16 scaleBaseIndex; // packed-bits index into the context's scale value array
};
struct S1_unk_D_800ABCC0 {
    /* 0x00 */ u8 isActive; // ModelAnim_BeginCurveContext: 1 when curveData != NULL, else 0
    /* 0x01 */ u8 flags; // mirrors curveData->unk_00; bit2 selects 16-bit vs 12-bit packed scale format
    /* 0x02 */ s16 currentFrame;
    /* 0x04 */ S1_unk_D_86002F58_004_000_040_004* curveData;
    /* 0x08 */ S1_unk_D_800ABCC0_008* channels; // per-joint-axis channel descriptors, indexed by ModelAnim_EvaluateJointTransform's arg3
    /* 0x0C */ s16* translationValues; // raw keyframe values, scaled by /1000.0f
    /* 0x10 */ s16* rotationValues; // PackedBits_ReadSigned source
    /* 0x14 */ s16* scaleValues; // PackedBits_ReadSigned source
};
struct S1_unk_D_86002F58_004_000_040_004 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ u32 unk_14;
    /* 0x18 */ u32 unk_18;
};
typedef struct S1_unk_func_80016B30_arg0 S1_unk_func_80016B30_arg0;
struct S1_unk_func_80016B30_arg0 {
    /* 0x00 */ S1_Vec3s vec;
    /* 0x06 */ s16 unk_06;
};
typedef struct S1_unk_D_86002F58_004_000_040_raw S1_unk_D_86002F58_004_000_040_raw;
typedef union S1_unk_D_86002F58_004_000_040_raw_08 S1_unk_D_86002F58_004_000_040_raw_08;
union S1_unk_D_86002F58_004_000_040_raw_08 {
    struct {
        s16 unk_00;
        s16 unk_02;
    };
    s32 raw;
};
struct S1_unk_D_86002F58_004_000_040_raw {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ S1_unk_D_86002F58_004_000_040_004* unk_04;
    /* 0x08 */ S1_unk_D_86002F58_004_000_040_raw_08 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char unk10[0x2];
    /* 0x12 */ u16 unk_12;
};
typedef struct S1_unk_D_86002F58_004_000_040 S1_unk_D_86002F58_004_000_040;
typedef struct S1_unk_D_86002F58_004_000 S1_unk_D_86002F58_004_000;
typedef struct S1_unk_D_86002F58_004_000_054 S1_unk_D_86002F58_004_000_054;
typedef struct S1_unk_D_86002F58_004_000_0A8 S1_unk_D_86002F58_004_000_0A8;
typedef struct S1_unk_D_86002F58_004_000_054_004 S1_unk_D_86002F58_004_000_054_004;
struct S1_unk_D_86002F58_004_000_040 {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ S1_unk_D_86002F58_004_000_040_004* unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ char unk10[0x2];
    /* 0x12 */ u16 unk_12;
};
struct S1_unk_D_86002F58_004_000_054 {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ S1_unk_D_86002F58_004_000_054_004* unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ u16 unk_0A;
};
struct S1_unk_D_86002F58_004_000_0A8 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ S1_Vec3f unk_04;
};
struct S1_unk_D_86002F58_004_000 {
    /* 0x000 */ S1_unk_D_86002F58_004_000_000 unk_000;
    /* 0x018 */ s16 animType; // Model_InitDisplayObject's arg1
    /* 0x01A */ s16 modelId; // Model_InitDisplayObject's arg2; a species id in most battle-scene consumers
    /* 0x01C */ u8 textureMode; // Model_SetMaterialTextureMode
    /* 0x01D */ u8 materialAlpha; // Model_SetMaterialAlpha
    /* 0x01E */ S1_Vec3s unk_01E;			//	total Rotation
    /* 0x024 */ S1_Vec3f unk_024;			//	global Position
    /* 0x030 */ S1_Vec3f unk_030;			//	scale
    /* 0x03C */ S1_Color_RGBA8_u32 unk_03C;
    /* 0x040 */ S1_unk_D_86002F58_004_000_040 unk_040;
    /* 0x054 */ S1_unk_D_86002F58_004_000_054 unk_054;
    /* 0x060 */ S1_MtxF unk_060;
    /* 0x0A0 */ S1_Color_RGBA8_u32 unk_0A0;    //  vertex color ?
    /* 0x0A4 */ char unk0A4[2];
    /* 0x0A6 */ u8 poolIndex; // stable index into the shared displayObjectPool; GeoRender_RecordAnchorPosition/etc.
    /* 0x0A7 */ u8 anchorCount; // GeoRender_RecordAnchorPosition/FindAnchorPosition; caps at 0xC (12)
    /* 0x0A8 */ S1_unk_D_86002F58_004_000_0A8 anchors[1]; // declared size undersells - indexed up to anchorCount (max 12)
    /* 0x0B8 */ char unk0B8[0x24];
    /* 0x0DC */ S1_Vec3f unk_0DC;
    /* 0x0E0 */ char unk0E0[0x4];
    /* 0x0EC */ S1_Vec3f unk_0EC;
    /* 0x0F8 */ char unk0F8[0x4];
    /* 0x0FC */ S1_Vec3f unk_0FC;
    /* 0x108 */ char unk108[0x60];
};
struct S1_unk_D_86002F58_004_000_054_004 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk_02[0x2];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ void* unk_0C;
    /* 0x10 */ void* unk_10;
};
typedef unsigned int S1_uintptr_t;
typedef struct S1_unk_D_800ABE00_cmd8 S1_unk_D_800ABE00_cmd8;
typedef struct S1_unk_D_86002F34_000_014 S1_unk_D_86002F34_000_014;
struct S1_unk_D_800ABE00_cmd8 {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ S1_func_D_86002F34_000_010 callback; // func_80037E3C's arg1
    /* 0x08 */ S1_unk_D_86002F34_000_014* callbackData; // func_80037E3C's arg2
};
struct S1_unk_D_86002F34_000_014 {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ u8* unk_04;
};
typedef struct S1_unk_D_800ABE00_cmd9 S1_unk_D_800ABE00_cmd9;
struct S1_unk_D_800ABE00_cmd9 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
};
typedef struct S1_unk_D_800ABE00_cmdA S1_unk_D_800ABE00_cmdA;
struct S1_unk_D_800ABE00_cmdA {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ S1_GraphNode* refNode; // GeoNode_CreateWithReference's arg1
};
typedef struct S1_unk_D_800ABE00_cmdB S1_unk_D_800ABE00_cmdB;
struct S1_unk_D_800ABE00_cmdB {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ u16 fovy;
    /* 0x04 */ u16 viewportX;
    /* 0x06 */ u16 viewportY;
    /* 0x08 */ s16 viewportWidth;
    /* 0x0A */ s16 viewportHeight;
    /* 0x0C */ S1_Vec3s lookAt;
    /* 0x12 */ s16 yaw;
    /* 0x14 */ s16 pitch;
    /* 0x16 */ s16 eyeDistance;
};
typedef struct S1_unk_D_800ABE00_cmdC S1_unk_D_800ABE00_cmdC;
struct S1_unk_D_800ABE00_cmdC {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 unk_02;
};
typedef struct S1_unk_D_800ABE00_cmdD S1_unk_D_800ABE00_cmdD;
struct S1_unk_D_800ABE00_cmdD {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 unk_02;
};
typedef struct S1_unk_D_800ABE00_cmdE S1_unk_D_800ABE00_cmdE;
struct S1_unk_D_800ABE00_cmdE {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 unk_02;
};
typedef struct S1_unk_D_800ABE00_cmdF S1_unk_D_800ABE00_cmdF;
struct S1_unk_D_800ABE00_cmdF {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 unk_02;
};
typedef struct S1_unk_D_800ABE00_cmd10 S1_unk_D_800ABE00_cmd10;
struct S1_unk_D_800ABE00_cmd10 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 r;
    /* 0x02 */ u8 g;
    /* 0x03 */ u8 b;
};
typedef struct S1_unk_D_800ABE00_cmd13 S1_unk_D_800ABE00_cmd13;
struct S1_unk_D_800ABE00_cmd13 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 r;
    /* 0x02 */ u8 g;
    /* 0x03 */ u8 b;
    /* 0x04 */ s16 fogNear;
    /* 0x06 */ s16 fogFar;
};
typedef struct S1_unk_D_800ABE00_cmd14 S1_unk_D_800ABE00_cmd14;
struct S1_unk_D_800ABE00_cmd14 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ s16 pitch; // GeoNode_CreateLight's arg2, scaled (val<<0xF)/180
    /* 0x06 */ s16 yaw; // GeoNode_CreateLight's arg3, scaled (val<<0xF)/180
    /* 0x08 */ u8 r;
    /* 0x09 */ u8 g;
    /* 0x0A */ u8 b;
    /* 0x0B */ u8 a;
};
typedef struct S1_unk_D_800ABE00_cmd18 S1_unk_D_800ABE00_cmd18;
struct S1_unk_D_800ABE00_cmd18 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
};
typedef struct S1_unk_D_800ABE00_cmd19 S1_unk_D_800ABE00_cmd19;
struct S1_unk_D_800ABE00_cmd19 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ s16 nearDistance; // Distance-cull node: children render only when nearDistance <= depth < farDistance
    /* 0x06 */ s16 farDistance;
};
typedef struct S1_unk_D_800ABE00_cmd1A S1_unk_D_800ABE00_cmd1A;
struct S1_unk_D_800ABE00_cmd1A {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 caseIndex; // Switch-case node: walks this many siblings from the first child before dispatching
};
typedef struct S1_unk_D_800ABE00_cmd1B S1_unk_D_800ABE00_cmd1B;
struct S1_unk_D_800ABE00_cmd1B {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ s16 rotX; // degrees, scaled (val<<0xF)/180
    /* 0x06 */ s16 rotY;
    /* 0x08 */ s16 rotZ;
    /* 0x0A */ S1_Vec3s translation;
};
typedef struct S1_unk_D_800ABE00_cmd1C S1_unk_D_800ABE00_cmd1C;
struct S1_unk_D_800ABE00_cmd1C {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ u32 translateX; // Q16 fixed point, /65536.0f
    /* 0x08 */ u32 translateY;
    /* 0x0C */ u32 translateZ;
};
typedef struct S1_unk_D_800ABE00_cmd1D S1_unk_D_800ABE00_cmd1D;
struct S1_unk_D_800ABE00_cmd1D {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 partIndex; // GeoNode_CreateAnimatedPart's arg2
    /* 0x02 */ u8 flags; // bit0/bit1 remapped into GeoNode_CreateAnimatedPart's arg3
    /* 0x03 */ u8 animIndex; // GeoNode_CreateAnimatedPart's arg4
    /* 0x04 */ S1_Vec3s rotationA; // GeoNode_CreateAnimatedPart's arg5
    /* 0x0A */ S1_Vec3s rotationB; // GeoNode_CreateAnimatedPart's arg6
    /* 0x10 */ u32 translateX; // Q16 fixed point, /65536.0f
    /* 0x14 */ u32 translateY;
    /* 0x18 */ u32 translateZ;
};
typedef struct S1_unk_D_800ABE00_cmd1E S1_unk_D_800ABE00_cmd1E;
struct S1_unk_D_800ABE00_cmd1E {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 partIndex; // GeoNode_CreateDisplayListPart's arg2
    /* 0x02 */ s16 unk_02; // GeoNode_CreateDisplayListPart's arg4
    /* 0x04 */ Gfx* displayList;
};
typedef struct S1_unk_D_800ABE00_cmd1F S1_unk_D_800ABE00_cmd1F;
struct S1_unk_D_800ABE00_cmd1F {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 modelIndex; // GeoNode_CreateModelPart's arg2
    /* 0x04 */ s16 rotX; // degrees, scaled (val<<0xF)/180
    /* 0x06 */ s16 rotY;
    /* 0x08 */ s16 rotZ;
    /* 0x0A */ S1_Vec3s position;
    /* 0x10 */ s16 scaleX; // /100.0f
    /* 0x12 */ s16 scaleY;
    /* 0x14 */ s16 scaleZ;
    /* 0x16 */ char pad[0x2];
};
typedef struct S1_unk_D_800ABE00_cmd20 S1_unk_D_800ABE00_cmd20;
struct S1_unk_D_800ABE00_cmd20 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 partIndex; // GeoNode_CreateDisplayListMatrixFromTransform's arg2
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 rotX; // degrees, scaled (val<<0xF)/180
    /* 0x06 */ s16 rotY;
    /* 0x08 */ s16 rotZ;
    /* 0x0A */ S1_Vec3s position;
    /* 0x10 */ Gfx* displayList;
};
typedef struct S1_unk_D_800ABE00_cmd21 S1_unk_D_800ABE00_cmd21;
struct S1_unk_D_800ABE00_cmd21 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 partIndex; // GeoNode_CreateScale's arg2
    /* 0x02 */ S1_Vec3s position;
    /* 0x08 */ u32 scale; // Q16 fixed point, /65536.0f
    /* 0x0C */ Gfx* displayList;
};
typedef struct S1_unk_D_800ABE00_cmd22 S1_unk_D_800ABE00_cmd22;
struct S1_unk_D_800ABE00_cmd22 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 partIndex; // GeoNode_CreateDisplayList's arg2
    /* 0x04 */ Gfx* displayList;
};
typedef struct S1_unk_D_800ABE00_cmd23 S1_unk_D_800ABE00_cmd23;
struct S1_unk_D_800ABE00_cmd23 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 colorOverrideFlag; // Geo_NodeShadowTexture: ==1 forces the shadow color to opaque white
    /* 0x02 */ s16 eventFrame; // ModelAnim_GetEventAtFrame's frame arg
    /* 0x04 */ Gfx* displayList;
    /* 0x07 */ s16 textureIndex1; // indexes D_8006F0A0's first texture array when >= 0
    /* 0x0A */ s16 textureIndex2; // indexes D_8006F0A0's second texture array when >= 0
    /* 0x0C */ u8 r;
    /* 0x0D */ u8 g;
    /* 0x0E */ u8 b;
    /* 0x0F */ u8 a;
};
typedef struct S1_unk_D_800ABE00_cmd24 S1_unk_D_800ABE00_cmd24;
struct S1_unk_D_800ABE00_cmd24 {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 anchorId; // GeoNode_CreateAnchor's arg2
};
typedef struct S1_unk_D_800ABE00_cmd26 S1_unk_D_800ABE00_cmd26;
struct S1_unk_D_800ABE00_cmd26 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 r;
    /* 0x11 */ u8 g;
    /* 0x12 */ u8 b;
    /* 0x13 */ u8 a;
};
typedef struct S1_arg1_func_80019420 S1_arg1_func_80019420;
struct S1_arg1_func_80019420 {
    /* 0x00 */ s8 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ void* unk_04;
};
void MtxF_Multiply(S1_MtxF* arg0, S1_MtxF* arg1, S1_MtxF* arg2) {
    f32 entry0;
    f32 entry1;
    f32 entry2;

    entry0 = arg1->mf[0][0];
    entry1 = arg1->mf[0][1];
    entry2 = arg1->mf[0][2];

    arg0->mf[0][0] = (entry0 * arg2->mf[0][0]) + (entry1 * arg2->mf[1][0]) + (entry2 * arg2->mf[2][0]);
    arg0->mf[0][1] = (entry0 * arg2->mf[0][1]) + (entry1 * arg2->mf[1][1]) + (entry2 * arg2->mf[2][1]);
    arg0->mf[0][2] = (entry0 * arg2->mf[0][2]) + (entry1 * arg2->mf[1][2]) + (entry2 * arg2->mf[2][2]);

    entry0 = arg1->mf[1][0];
    entry1 = arg1->mf[1][1];
    entry2 = arg1->mf[1][2];

    arg0->mf[1][0] = (entry0 * arg2->mf[0][0]) + (entry1 * arg2->mf[1][0]) + (entry2 * arg2->mf[2][0]);
    arg0->mf[1][1] = (entry0 * arg2->mf[0][1]) + (entry1 * arg2->mf[1][1]) + (entry2 * arg2->mf[2][1]);
    arg0->mf[1][2] = (entry0 * arg2->mf[0][2]) + (entry1 * arg2->mf[1][2]) + (entry2 * arg2->mf[2][2]);

    entry0 = arg1->mf[2][0];
    entry1 = arg1->mf[2][1];
    entry2 = arg1->mf[2][2];

    arg0->mf[2][0] = (entry0 * arg2->mf[0][0]) + (entry1 * arg2->mf[1][0]) + (entry2 * arg2->mf[2][0]);
    arg0->mf[2][1] = (entry0 * arg2->mf[0][1]) + (entry1 * arg2->mf[1][1]) + (entry2 * arg2->mf[2][1]);
    arg0->mf[2][2] = (entry0 * arg2->mf[0][2]) + (entry1 * arg2->mf[1][2]) + (entry2 * arg2->mf[2][2]);

    entry0 = arg1->mf[3][0];
    entry1 = arg1->mf[3][1];
    entry2 = arg1->mf[3][2];

    arg0->mf[3][0] = (entry0 * arg2->mf[0][0]) + (entry1 * arg2->mf[1][0]) + (entry2 * arg2->mf[2][0]) + arg2->mf[3][0];
    arg0->mf[3][1] = (entry0 * arg2->mf[0][1]) + (entry1 * arg2->mf[1][1]) + (entry2 * arg2->mf[2][1]) + arg2->mf[3][1];
    arg0->mf[3][2] = (entry0 * arg2->mf[0][2]) + (entry1 * arg2->mf[1][2]) + (entry2 * arg2->mf[2][2]) + arg2->mf[3][2];

    arg0->mf[0][3] = arg0->mf[1][3] = arg0->mf[2][3] = 0.0f;
    arg0->mf[3][3] = 1.0f;
}
#endif

#ifdef VERSION_US
void MtxF_ScaleRows(S1_MtxF* dest, S1_MtxF* mtx, S1_Vec3f* s) {
    s32 i;

    for (i = 0; i < 4; i++) {
        dest->mf[0][i] = mtx->mf[0][i] * s->x;
        dest->mf[1][i] = mtx->mf[1][i] * s->y;
        dest->mf[2][i] = mtx->mf[2][i] * s->z;
        dest->mf[3][i] = mtx->mf[3][i];
    }
}
#endif

#ifdef VERSION_US
void func_80036D8C(f32 *arg0, f32 *arg1) {
    arg1[0] = sqrtf(arg0[0] * arg0[0] + arg0[1] * arg0[1] + arg0[2] * arg0[2]);
    arg1[1] = sqrtf(arg0[4] * arg0[4] + arg0[5] * arg0[5] + arg0[6] * arg0[6]);
    arg1[2] = sqrtf(arg0[8] * arg0[8] + arg0[9] * arg0[9] + arg0[10] * arg0[10]);
}
#endif

#ifdef VERSION_US
void MtxF_TransformVec3s(S1_MtxF* arg0, S1_Vec3s* arg1) {
    f32 entry0 = arg1->x;
    f32 entry1 = arg1->y;
    f32 entry2 = arg1->z;

    arg1->x = ((entry0 * arg0->mf[0][0]) + (entry1 * arg0->mf[1][0]) + (entry2 * arg0->mf[2][0])) + arg0->mf[3][0];
    arg1->y = ((entry0 * arg0->mf[0][1]) + (entry1 * arg0->mf[1][1]) + (entry2 * arg0->mf[2][1])) + arg0->mf[3][1];
    arg1->z = ((entry0 * arg0->mf[0][2]) + (entry1 * arg0->mf[1][2]) + (entry2 * arg0->mf[2][2])) + arg0->mf[3][2];
}
#endif

#ifdef VERSION_US
void MtxF_ToFixed(void *destination, S1_MtxF *source) {
    s32 converted;
    s32 i;
    // N64 matrices store integer halves before fractional halves.
    s16 *integer = destination;
    s16 *fraction = (s16 *)destination + 16;
    f32 *input = (f32 *)source;
    for (i = 0; i < 16; i++) {
        converted = *input++ * 65536.0f;
        *integer++ = ((s16 *)&converted)[0];
        *fraction++ = ((s16 *)&converted)[1];
    }
}
#endif

#ifdef VERSION_US
extern void func_80036714(void *, s32, s32, s32, f32);
extern void MtxF_SetRotationTranslationF(f32 matrix[4][4], Vec3f35784 *position, Vec3s35AA0 *rotation);
void MtxF_BuildTransform(S1_MtxF *arg0, S1_Vec3f *arg1, S1_Vec3s *arg2, S1_Vec3f *arg3, S1_MtxF *arg4, S1_MtxF *arg5) {
    S1_MtxF sp60;
    S1_MtxF sp20;

    func_80036714(&sp60, (s32)arg4, (s32)arg5, (s32)arg1, 1.0f);
    MtxF_SetRotationTranslationF(sp20.mf, (void *)&D_800948D0, (void *)arg2);
    MtxF_Multiply(&sp20, &sp20, &sp60);
    MtxF_ScaleRows(arg0, &sp20, arg3);
}
#endif

#ifdef VERSION_US
extern s16 MathUtil_Atan2s(f32 y, f32 x);
void func_80037120(S1_Vec3f *arg0, S1_Vec3f *arg1, f32 *arg2, s16 *arg3, s16 *arg4) {
    f32 dx; f32 dy; f32 dz;
    dx = arg1->x - arg0->x; dy = arg1->y - arg0->y; dz = arg1->z - arg0->z;
    *arg2 = sqrtf(dx * dx + dy * dy + dz * dz);
    *arg3 = MathUtil_Atan2s(sqrtf(dx * dx + dz * dz), dy);
    *arg4 = MathUtil_Atan2s(dz, dx);
}
#endif

#ifdef VERSION_US
void Camera_ComputeEyeFromAngles(S1_Vec3f *from, S1_Vec3f *to, f32 dist, s16 pitch, s16 yaw) {
    to->x = from->x + (dist * D_80088E50[((u16)pitch >> 4)] * D_80087E50[((u16)yaw >> 4)]);
    to->y = from->y + (dist * D_80087E50[((u16)pitch >> 4)]);
    to->z = from->z + (dist * D_80088E50[((u16)pitch >> 4)] * D_80088E50[((u16)yaw >> 4)]);
}
#endif

#ifdef VERSION_US
s16 Math_StepToS(s16 current, s16 target, s16 inc) {
    s16 temp_v0 = target - current;

    if (temp_v0 < 0) {
        temp_v0 += inc;
        if (temp_v0 > 0) {
            temp_v0 = 0;
        }
    } else {
        temp_v0 -= inc;
        if (temp_v0 < 0) {
            temp_v0 = 0;
        }
    }

    return target - temp_v0;
}
#endif

#ifdef VERSION_US
s32 Math_StepToS32(s32 current, s32 target, s32 inc, s32 dec) {
    if (current < target) {
        current += inc;
        if (current > target) {
            current = target;
        }
    } else {
        current -= dec;
        if (current < target) {
            current = target;
        }
    }
    return current;
}
#endif

#ifdef VERSION_US
f32 Math_StepToF(f32 current, f32 target, f32 inc, f32 dec) {
    if (current < target) {
        current += inc;
        if (current > target) {
            current = target;
        }
    } else {
        current -= dec;
        if (current < target) {
            current = target;
        }
    }
    return current;
}
#endif

#ifdef VERSION_US
s16 func_80037360(s16* arg0, s32 arg1, s32 arg2) {
    S1_Vec2s_s32 spC;
    s16* temp_a3 = &arg0[(arg1 * arg2) / 16];
    s16* p_spC = &spC.x;

    p_spC[0] = temp_a3[0];
    p_spC[1] = temp_a3[1];

    spC.xy <<= ((arg1 * arg2) % 16);
    spC.xy >>= -arg2;
    return spC.y;
}
#endif

#ifdef VERSION_US
void Color_RGBToHSV(f32 arg0, f32 arg1, f32 arg2, S1_Vec3f* arg3) {
    f32 temp_ft4;
    f32 var_ft5;
    f32 var_fv0;
    f32 var_fv1;
    s32 var_v0;

    var_v0 = 0x47;
    if (arg1 <= arg0) {
        var_fv0 = arg0;
        var_v0 = 0x52;
    } else {
        var_fv0 = arg1;
    }

    if (var_fv0 < arg2) {
        var_fv0 = arg2;
        var_v0 = 0x42;
    }

    if (arg0 <= arg1) {
        var_fv1 = arg0;
    } else {
        var_fv1 = arg1;
    }

    if (arg2 < var_fv1) {
        var_fv1 = arg2;
    }

    temp_ft4 = var_fv0 + var_fv1;
    arg3->z = temp_ft4 - 1.0f;
    if (var_fv0 == var_fv1) {
        arg3->y = 0.0f;
        arg3->x = 0.0f;
        return;
    }

    if (arg3->z <= 0.0f) {
        var_ft5 = var_fv0 - var_fv1;
        arg3->y = var_ft5 / temp_ft4;
    } else {
        var_ft5 = var_fv0 - var_fv1;
        arg3->y = var_ft5 / (2.0 - temp_ft4);
    }

    if (var_v0 == 0x52) {
        arg3->x = (arg1 - arg2) / var_ft5;
    } else if (var_v0 == 0x47) {
        arg3->x = ((arg2 - arg0) / var_ft5) + 2.0;
    } else {
        arg3->x = ((arg0 - arg1) / var_ft5) + 4.0;
    }

    arg3->x *= 60.0f;
    if (arg3->x < 0.0f) {
        arg3->x += 360.0f;
    }
}
#endif

#ifdef VERSION_US
void Color_RGBA8ToHSV(S1_Color_RGBA8_u32 arg0, S1_Vec3f* arg1) {
    Color_RGBToHSV((s32)arg0.r / 255.0f, (s32)arg0.g / 255.0f, (s32)arg0.b / 255.0f, arg1);
}
#endif

#ifdef VERSION_US
void Color_RGB5551ToHSV(u16 arg0, S1_Vec3f* arg1) {
    Color_RGBToHSV(((arg0 & 0xF800) >> 0xB) / 31.0f, ((arg0 & 0x7C0) >> 6) / 31.0f, ((arg0 & 0x3E) >> 1) / 31.0f, arg1);
}
#endif

#ifdef VERSION_US
f32 Color_HSVInterpolate(f32 arg0, f32 arg1, f32 arg2) {
    f32 ret;

    if (arg0 < 0.0f) {
        arg0 += 360.0f;
    } else {
        while (arg0 >= 360.0f) {
            arg0 -= 360.0f;
        }
    }

    if (arg0 < 60.0f) {
        ret = (((arg2 - arg1) * arg0) / 60.0f) + arg1;
    } else if ((arg0 >= 60.0f) && (arg0 < 180.0f)) {
        ret = arg2;
    } else if ((arg0 >= 180.0f) && (arg0 < 240.0f)) {
        ret = arg1 + (((arg2 - arg1) * (240.0 - arg0)) / 60.0);
    } else {
        ret = arg1;
    }

    return ret;
}
#endif

#ifdef VERSION_US
void Color_HSVToRGB(f32* arg0, f32* arg1, f32* arg2, S1_Vec3f* arg3) {
    f32 sp24;
    f32 sp20;
    f32 temp_ft4;

    if (arg3->z < -1.0f) {
        arg3->z = -1.0f;
    } else if (arg3->z > 1.0f) {
        arg3->z = 1.0f;
    }

    if (arg3->y < 0.0f) {
        arg3->y = 0.0f;
    } else {
        sp24 = 1.0f;
        if (arg3->y > 1.0f) {
            arg3->y = 1.0f;
        }
    }

    if (arg3->x < 0.0f) {
        arg3->x += 360.0f;
    } else {
        while (arg3->x >= 360.0f) {
            arg3->x -= 360.0f;
        }
    }

    if (arg3->z <= 0.0f) {
        temp_ft4 = arg3->z + 1.0f;
        sp24 = temp_ft4 * 0.5f * (1.0f - arg3->y);
        sp20 = temp_ft4 - sp24;
    } else {
        temp_ft4 = arg3->z + 1.0f;
        sp20 = (temp_ft4 * 0.5 * (1.0f - arg3->y)) + arg3->y;
        sp24 = temp_ft4 - sp20;
    }

    *arg0 = Color_HSVInterpolate(arg3->x + 120.0f, sp24, sp20);
    *arg1 = Color_HSVInterpolate(arg3->x, sp24, sp20);
    *arg2 = Color_HSVInterpolate(arg3->x - 120.0f, sp24, sp20);
}
#endif

#ifdef VERSION_US
u16 Color_HSVToRGB5551(S1_Vec3f* arg0) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;

    Color_HSVToRGB(&sp2C, &sp28, &sp24, arg0);

    var_a1 = (sp2C * 31.0f) + 0.5f;
    if (var_a1 >= 0x20) {
        var_a1 = 0x1F;
    }

    var_v1 = (sp28 * 31.0f) + 0.5f;
    if (var_v1 >= 0x20) {
        var_v1 = 0x1F;
    }

    var_a0 = (sp24 * 31.0f) + 0.5f;
    if (var_a0 >= 0x20) {
        var_a0 = 0x1F;
    }

    return (var_a1 << 0xB) | (var_v1 << 6) | (var_a0 * 2) | 1;
}
#endif

#ifdef VERSION_US
S1_Color_RGBA8_u32* Color_HSVToRGBA8(S1_Color_RGBA8_u32* arg0, S1_Vec3f* arg1, s32 arg2) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;
    S1_Color_RGBA8_u32 sp1C;

    Color_HSVToRGB(&sp34, &sp30, &sp2C, arg1);

    var_a1 = (sp34 * 255.0f) + 0.5f;
    if (var_a1 >= 0x100) {
        var_a1 = 0xFF;
    }

    var_v1 = (sp30 * 255.0f) + 0.5f;
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }

    var_a0 = (sp2C * 255.0f) + 0.5f;
    if (var_a0 >= 0x100) {
        var_a0 = 0xFF;
    }

    sp1C.r = var_a1;
    sp1C.g = var_v1;
    sp1C.b = var_a0;
    sp1C.a = arg2;

    *arg0 = sp1C;

    return arg0;
}
#endif

#ifdef VERSION_US
extern u16 D_80095120[16][256];
extern const f32 D_800A42B0;
u16 Color_AdjustRGB5551(u16 color, S1_arg1_func_80010CA8 adjustment) {
    S1_Vec3f hsv;
    s32 column;
    s32 row;
    if (color & 1) {
        Color_RGB5551ToHSV(color, &hsv);
        if (adjustment.unk_00 != 0) {
            hsv.x += adjustment.unk_00 * 0.015625f;
        }
        if (adjustment.unk_02 != 0) {
            if (adjustment.unk_02 > 0) {
                hsv.y += (1.0f - hsv.y) * adjustment.unk_02 * 0.125f;
            } else {
                hsv.y += hsv.y * adjustment.unk_02 * 0.125f;
            }
        }
        if (adjustment.unk_03 != 0) {
            column = (hsv.z + 1.0f) * 0.5f * 255.0f;
            if (adjustment.unk_03 > 0) {
                row = adjustment.unk_03 + 7;
            } else {
                row = adjustment.unk_03 + 8;
            }
            hsv.z = (2.0f * (D_80095120[row][column] / D_800A42B0)) - 1.0f;
        }
        color = Color_HSVToRGB5551(&hsv);
    }
    return color;
}
#endif

#ifdef VERSION_US
extern const f32 D_800A42B4;
u32 Color_AdjustRGBA8(u32 word, S1_arg1_func_80010CA8 adjustment) {
    S1_Vec3f hsv;
    S1_Color_RGBA8_u32 color;
    s32 column;
    s32 row;
    u16 *brightness;
    color.rgba = word;
    if (color.a > 0) {
        Color_RGBA8ToHSV(color, &hsv);
        if (adjustment.unk_00 != 0) {
            hsv.x += adjustment.unk_00 * 0.015625f;
        }
        if (adjustment.unk_02 != 0) {
            if (adjustment.unk_02 > 0) {
                hsv.y += (1.0f - hsv.y) * adjustment.unk_02 * 0.125f;
            } else {
                hsv.y += hsv.y * adjustment.unk_02 * 0.125f;
            }
        }
        if (adjustment.unk_03 != 0) {
            column = (hsv.z + 1.0f) * 0.5f * 255.0f;
            if (adjustment.unk_03 > 0) {
                row = adjustment.unk_03 + 7;
            } else {
                row = adjustment.unk_03 + 8;
            }
            brightness = D_80095120[row];
            hsv.z = (2.0f * (brightness[column] / D_800A42B4)) - 1.0f;
        }
        Color_HSVToRGBA8(&color, &hsv, color.a);
    }
    return color.rgba;
}
#pragma C_FUNCTION_PADDING(4)
#endif

#ifdef VERSION_US
void GeoNode_Init(S1_GraphNode* arg0, u8 arg1) {
    if (arg0 != NULL) {
        arg0->unk_00 = arg1;
        arg0->unk_01 = 0x11;
        arg0->unk_02 = 0;
        arg0->unk_03 = 0;
        arg0->unk_04 = arg0;
        arg0->unk_08 = arg0;
        arg0->unk_0C = NULL;
        arg0->unk_10 = NULL;
        arg0->unk_14 = NULL;
    }
}
#endif

#ifdef VERSION_US
void func_80037E3C(S1_GraphNode* arg0, S1_func_D_86002F34_000_010 arg1, void* arg2) {
    if (arg1 != NULL) {
        arg1 = func_80003240(arg1);
    }

    if (arg0 != NULL) {
        arg0->unk_14 = arg2;
        arg0->unk_10 = arg1;
        if (arg1 != NULL) {
            arg1(0, arg0);
        }
    }
}
#endif

#ifdef VERSION_US
S1_GraphNode* GeoNode_CreateContainer(S1_MainPoolState* arg0, S1_GraphNode* arg1) { if (arg0 != NULL) { arg1 = MainPool_AllocAligned(arg0, sizeof(S1_GraphNode), 4); } if (arg1 != NULL) { GeoNode_Init(arg1, 0); } return arg1; }
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt2* GeoNode_CreateWithReference(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt2* arg1, S1_GraphNode* arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt2), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        GeoNode_Init(arg1, 1);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
extern void GeoCamera_SetViewport(S1_unk_D_86002F34_00C *, s16, s16, s16, s16);
extern void GeoCamera_SetPerspective(S1_unk_D_86002F34_00C *, f32, f32, f32);
extern void func_80038E14(void *, f32, f32, f32, f32, f32, f32, u16);
extern void GeoCamera_SetBackground(S1_unk_D_86002F34_00C *, s16, s16, u8, u8, u8);
S1_unk_D_86002F34_00C *GeoNode_CreateCamera(S1_MainPoolState *pool, S1_unk_D_86002F34_00C *node, s16 x, s16 y, s16 width, s16 height) {
    if (pool != NULL) {
        node = MainPool_AllocAligned(pool, sizeof(S1_unk_D_86002F34_00C), 4);
    }
    if (node != NULL) {
        GeoCamera_SetViewport(node, x, y, width, height);
        GeoCamera_SetPerspective(node, 30.0f, 100.0f, 12800.0f);
        func_80038E14(node, 0.0f, 512.0f, 4096.0f, 0.0f, 0.0f, 0.0f, 0);
        GeoCamera_SetBackground(node, 2, 0, 0, 0, 0);
        GeoNode_Init((void *)node, 2);
    }
    return node;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt13* GeoNode_CreateType3(S1_MemoryBlock* arg0, S1_unk_D_86002F34_alt13* arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt13), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        GeoNode_Init(arg1, 3);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt1* GeoNode_CreateType4(S1_MemoryBlock* arg0, S1_unk_D_86002F34_alt1* arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt1), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        arg1->unk_1A = 0;
        GeoNode_Init(arg1, 4);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
void *func_800380B8(S1_MainPoolState *arg0, s32 arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = (s32)(u32)MainPool_AllocAligned(arg0, 0x18, 4);
    }
    if (arg1 != 0) {
        GeoNode_Init((S1_GraphNode *)arg1, 5U);
        *(u8 *)(arg1 + 2) = *(u8 *)(arg1 + 2) | (arg2 & 7);
    }
    return (void *)arg1;
}
#endif

#ifdef VERSION_US
void *func_8003811C(S1_MainPoolState *arg0, s32 arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = (s32)(u32)MainPool_AllocAligned(arg0, 0x18, 4);
    }
    if (arg1 != 0) {
        GeoNode_Init((S1_GraphNode *)arg1, 6);
        *(u8 *)(arg1 + 2) = *(u8 *)(arg1 + 2) | (arg2 & 7);
    }
    return (void *)arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt16* GeoNode_CreateBackground(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt16* arg1, u8 arg2, u8 arg3, u8 arg4) {
    u32 temp_v0;

    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt16), 4);
    }

    if (arg1 != NULL) {
        temp_v0 = ((arg2 >> 3) << 0xB) | ((arg3 >> 3) << 6) | ((arg4 >> 3) << 1) | 1;
        arg1->unk_18 = (temp_v0 << 0x10) | temp_v0;
        GeoNode_Init(arg1, 7);
    }
    return arg1;
}
#endif

#ifdef VERSION_US
s32 func_8003820C(s32 arg0, s32 arg1) {
    s32 var_a2;

    var_a2 = arg1;
    if (arg0 != 0) {
        var_a2 = (s32)(u32)MainPool_AllocAligned((void *)(u32)arg0, 0x18, 4);
    }
    if (var_a2 != 0) {
        arg1 = var_a2;
        GeoNode_Init((S1_GraphNode *) var_a2, 8U);
        var_a2 = arg1;
    }
    return var_a2;
}
#endif

#ifdef VERSION_US
S1_unk_D_8690A610* GeoNode_CreateFog(s32 arg0, S1_unk_D_8690A610* arg1, s16 arg2, s16 arg3, u8 r, u8 g, u8 b, u8 a) {
    if (arg0 != 0) {
        arg1 = MainPool_AllocAligned((void *)(u32)arg0, sizeof(S1_unk_D_8690A610), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18.fogNear = arg2;
        arg1->unk_18.fogFar = arg3;
        arg1->unk_18.fogColor.rgba = (r << 0x18) | (g << 0x10) | (b << 8) | a;
        GeoNode_Init(arg1, 0xA);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
extern S1_Vec3s D_800948DC;
typedef struct {
    S1_GraphNode node;
    S1_Color_RGBA8_u32 color;
    s16 pitch;
    s16 yaw;
    S1_Vec3s direction;
    u16 pad26;
    u8 red;
    u8 green;
    u8 blue;
    u8 overrideDirection;
} SceneDirectionalLight;
void *GeoNode_CreateLight(S1_MainPoolState *pool, void *storage, s16 pitch, s16 yaw, u8 red, u8 green, u8 blue, u8 alpha) {
    SceneDirectionalLight *light;
    if (pool != NULL) {
        storage = MainPool_AllocAligned(pool, sizeof(SceneDirectionalLight), 4);
    }
    light = storage;
    if (light != NULL) {
        light->color.r = red;
        light->color.g = green;
        light->color.b = blue;
        light->color.a = alpha;
        light->pitch = pitch;
        light->yaw = yaw;
        light->direction = D_800948DC;
        light->red = 0;
        light->green = 0;
        light->blue = 0;
        light->overrideDirection = 0;
        GeoNode_Init((S1_GraphNode *)light, 0xB);
    }
    return light;
}
#endif

#ifdef VERSION_US
typedef struct Candidate38390Node {
    u8 pad00[0x20];
    S1_Vec3s vector;
    u8 pad26[2];
    u8 red;
    u8 green;
    u8 blue;
    u8 enabled;
} Candidate38390Node;
typedef struct Candidate38390UnsignedVector {
    u16 x;
    u16 y;
    u16 z;
} Candidate38390UnsignedVector;
void func_80038390(void *arg0, S1_Vec3s *arg1, u8 arg2, u8 arg3, u8 arg4) {
    if (arg0 != NULL) {
        *(S1_Vec3s *)((u8 *)arg0 + 0x20) = *arg1;
        ((u8 *)arg0)[0x28] = arg2;
        ((u8 *)arg0)[0x29] = arg3;
        ((u8 *)arg0)[0x2A] = arg4;
        ((u8 *)arg0)[0x2B] = 1;
    }
}
#endif

#ifdef VERSION_US
void func_800383DC(void *arg0, s16 arg1, s16 arg2) {
    if (arg0 != NULL) {
        (*(s16 *)((u8 *)(arg0) + (0x1C))) = arg1;
        (*(s16 *)((u8 *)(arg0) + (0x1E))) = arg2;
        (*(s8 *)((u8 *)(arg0) + (0x2B))) = 0;
    }
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt19* GeoNode_CreateAmbientLight(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt19* arg1, u8 r, u8 g, u8 b) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt19), 4);
    }

    if (arg1 != NULL) {
        arg1->r = r;
        arg1->g = g;
        arg1->b = b;
        GeoNode_Init(arg1, 0xD);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
s32 func_80038474(s32 arg0, s32 arg1) {
    s32 var_a2;

    var_a2 = arg1;
    if (arg0 != 0) {
        var_a2 = (s32)(u32)MainPool_AllocAligned((void *)(u32)arg0, 0x18, 4);
    }
    if (var_a2 != 0) {
        arg1 = var_a2;
        GeoNode_Init((S1_GraphNode *) var_a2, 0x1DU);
        var_a2 = arg1;
    }
    return var_a2;
}
#endif

#ifdef VERSION_US
S1_GraphNode *func_800384C0(void *arg0, S1_GraphNode *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u16 arg8) {
    S1_GraphNode *new_var;
    u8 *new_var2;
    if (arg0 != 0) {
        arg1 = MainPool_AllocAligned(arg0, 0x30, 4);
    }
    if (arg1 != 0) {
        ((s32 *)(((u8 *)arg1) + 0x18))[0] = arg3;
        ((s32 *)(((u8 *)arg1) + 0x1C))[0] = arg5;
        ((s32 *)(((u8 *)arg1) + 0x20))[0] = arg7;
        ((u8 *)arg1)[0x24] = (u8)arg2;
        ((u8 *)arg1)[0x25] = (u8)arg4;
        ((u16 *)(((u8 *)arg1) + 0x26))[0] = (u16)arg6;
        new_var2 = (u8 *)arg1;
        ((u16 *)(((u8 *)arg1) + 0x28))[0] = arg8;
        ((s32 *)(new_var2 + 0x2C))[0] = 0;
        GeoNode_Init(arg1, 0xE);
    }
    if (1) {
        new_var = arg1;
    }
    return new_var;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt12* GeoNode_CreateShadow(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt12* arg1, s16 arg2, s16 arg3, s16 arg4,
                                    s16 arg5) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt12), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        arg1->unk_1A = arg3;
        arg1->unk_1C = arg4;
        arg1->unk_1E = arg5;
        GeoNode_Init(arg1, 0xF);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt20* GeoNode_CreateCullDistance(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt20* arg1, s16 arg2, s16 arg3) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt20), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        arg1->unk_1A = arg3;
        GeoNode_Init(arg1, 0x10);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt21* GeoNode_CreateSwitchCase(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt21* arg1, s16 arg2, s16 arg3) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt21), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        arg1->unk_1A = arg3;
        GeoNode_Init(arg1, 0x11);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt5* GeoNode_CreateTranslateRotate(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt5* arg1, S1_Vec3f* arg2, S1_Vec3s* arg3) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt5), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = *arg2;
        arg1->unk_24 = *arg3;
        GeoNode_Init(arg1, 0x12);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt22* GeoNode_CreateTranslate(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt22* arg1, S1_Vec3f* arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt22), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = *arg2;
        GeoNode_Init(arg1, 0x13);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt6* GeoNode_CreateAnimatedPart(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt6* arg1, s16 arg2, s16 arg3, s16 arg4,
                                   S1_Vec3s* arg5, S1_Vec3s* arg6, S1_Vec3f* arg7) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt6), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = *arg5;
        arg1->unk_1E = *arg6;
        arg1->unk_24 = *arg7;
        arg1->unk_30 = arg2;
        arg1->unk_31 = arg3;
        arg1->unk_32 = arg4;
        GeoNode_Init(arg1, 0x14);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt7* GeoNode_CreateDisplayListPart(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt7* arg1, s32 arg2, Gfx* arg3, s16 arg4) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt7), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg3;
        arg1->unk_1C = arg4;
        GeoNode_Init(arg1, 0x15);
        arg1->unk_00.unk_03 = arg2;
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F58_004_000 *GeoNode_CreateModelPart(S1_MainPoolState *pool, void *storage, s16 model, S1_Vec3f *position, S1_Vec3s *rotation, S1_Vec3f *scale) {
    if (pool != NULL) storage = MainPool_AllocAligned(pool, 0x168, 4);
    if (storage != NULL) {
        S1_unk_D_86002F58_004_000 *node = storage;
        node->animType = 0;
        node->modelId = model;
        node->unk_024 = *position;
        node->unk_030 = *scale;
        node->unk_01E = *rotation;
        node->materialAlpha = 0xFF;
        node->textureMode = 0;
        node->unk_0A0.rgba = 0xFFFFFF00U;
        node->unk_03C.rgba = 0xFFFFFF00U;
        node->poolIndex = 0;
        node->unk_040.unk_00 = 0;
        node->unk_040.unk_04 = NULL;
        node->unk_040.unk_08 = 0;
        node->unk_040.unk_0C = 0x10000;
        node->unk_040.unk_12 = 0;
        node->unk_054.unk_00 = 0;
        *(s16 *)((u8 *)node + 0x56) = 0;
        node->unk_054.unk_04 = NULL;
        node->unk_054.unk_08 = 0;
        node->unk_054.unk_0A = 0;
        GeoNode_Init((S1_GraphNode *)node, 0x16);
        node->unk_000.unk_02 |= 0x60;
    }
    return storage;
}
#endif

#ifdef VERSION_US
extern void MtxF_Identity(f32 *arg0);
void *func_8003899C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    if (arg0 != 0) {
        arg1 = (s32) MainPool_AllocAligned((void *) arg0, sizeof(S1_unk_D_86002F34_alt8), 4);
    }
    if (arg1 != 0) {
        ((S1_unk_D_86002F34_alt8 *) arg1)->unk_18 = (Gfx *) arg3;
        if (arg4 == NULL) {
            MtxF_Identity((f32 *) &((S1_unk_D_86002F34_alt8 *) arg1)->unk_1C);
        } else {
            MtxF_Copy((u32 *) &((S1_unk_D_86002F34_alt8 *) arg1)->unk_1C, (u32 *) arg4);
        }
        GeoNode_Init((S1_GraphNode *) arg1, 0x17);
        ((S1_unk_D_86002F34_alt8 *) arg1)->unk_00.unk_03 = (u8) arg2;
    }
    return (void *) arg1;
}
#endif

#ifdef VERSION_US
extern void *func_8003899C(s32, s32, s32, s32, void *);
void *GeoNode_CreateDisplayListMatrixFromTransform(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    f32 temp[4][4];
    MtxF_SetRotationTranslationF(temp, (Vec3f35784 *)arg4, (Vec3s35AA0 *)arg5);
    func_8003899C(arg0, arg1, arg2, arg3, temp);
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt9* GeoNode_CreateScale(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt9* arg1, s32 arg2, Gfx* arg3, S1_Vec3f* arg4,
                                   f32 arg5) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt9), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_1C = *arg4;
        arg1->unk_28 = arg5;
        arg1->unk_18 = arg3;
        GeoNode_Init(arg1, 0x18);
        arg1->unk_00.unk_03 = arg2;
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_func_80011B94* GeoNode_CreateDisplayList(S1_MainPoolState* arg0, S1_unk_func_80011B94* arg1, s32 arg2, Gfx* arg3) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_func_80011B94), 4);
    }

    if (arg1 != NULL) {
        arg1->displayList = arg3;
        GeoNode_Init(arg1, 0x19);
        arg1->unk_00.unk_03 = arg2;
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt10* GeoNode_CreateShadowTexture(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt10* arg1, s16 arg2, s16 arg3, Gfx* arg4,
                                    s16 arg5, s16 arg6, u8 r, u8 g, u8 b, u8 a) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt10), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_22 = arg2;
        arg1->unk_20 = arg3;
        arg1->unk_18 = arg4;
        arg1->unk_1C = arg5;
        arg1->unk_1E = arg6;
        arg1->unk_24.rgba = (r << 0x18) | (g << 0x10) | (b << 8) | a;
        GeoNode_Init(arg1, 0x1A);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt23* GeoNode_CreateAnchor(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt23* arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt23), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        GeoNode_Init(arg1, 0x1B);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt24* GeoNode_CreateGroup(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt24* arg1, s32 arg2, s16 arg3, s16 arg4,
                                    s16 arg5, s16 arg6, s16 arg7, s16 arg8, s32 arg9, u8 r, u8 g, u8 b, u8 a) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt24), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_1C = arg3;
        arg1->unk_1E = arg4;
        arg1->unk_20 = arg5;
        arg1->unk_22 = arg6;
        arg1->unk_18 = arg7;
        arg1->unk_1A = arg8;
        arg1->unk_24 = arg9;
        arg1->unk_28.rgba = (r << 0x18) | (g << 0x10) | (b << 8) | a;
        GeoNode_Init(arg1, 0x1C);
        arg1->unk_00.unk_03 = arg2;
    }

    return arg1;
}
#endif

#ifdef VERSION_US
void GeoCamera_SetViewport(S1_unk_D_86002F34_00C* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    arg0->unk_18.x = arg1;
    arg0->unk_18.y = arg2;
    arg0->unk_18.width = arg3;
    arg0->unk_18.height = arg4;

    arg0->unk_40.l = -arg3 * 0.5f;
    arg0->unk_40.r = arg3 * 0.5f;
    arg0->unk_40.t = arg4 * 0.5f;
    arg0->unk_40.b = -arg4 * 0.5f;
    arg0->unk_40.n = -2.0f;
    arg0->unk_40.f = 2.0f;
    arg0->unk_40.scale = 1.0f;
}
#endif

#ifdef VERSION_US
void GeoCamera_SetPerspective(S1_unk_D_86002F34_00C* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_24.aspect = (f32)arg0->unk_18.width / arg0->unk_18.height;
    arg0->unk_24.fovy = arg1;
    arg0->unk_24.near = arg2;
    arg0->unk_24.far = arg3;
    arg0->unk_24.scale = 1.0f;
}
#endif

#ifdef VERSION_US
extern f32 D_80087E50[];
extern f32 D_80088E50[0x1000];
void func_80038E14(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u16 arg7) {
    f32 inv = (f32)(-1.0 / sqrtf((arg4 - arg1) * (arg4 - arg1) + (arg6 - arg3) * (arg6 - arg3)));
    f32 sx = (arg4 - arg1) * inv;
    f32 sz = (arg6 - arg3) * inv;
    u8 *ptr = (u8 *)arg0 + 0x60;
    Vec3f_SetComponentsDuplicate((void *)((u8 *)arg0 + 0xA8), arg1, arg2, arg3);
    Vec3f_SetComponentsDuplicate((void *)(ptr + 0x54), arg4, arg5, arg6);
    Vec3f_SetComponentsDuplicate((void *)(ptr + 0x60), D_80087E50[arg7 >> 4] * sz, D_80088E50[arg7 >> 4], -D_80087E50[arg7 >> 4] * sx);
}
#endif

#ifdef VERSION_US
void GeoCamera_SetBackground(S1_unk_D_86002F34_00C* arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    S1_unk_D_86002F34_00C_0CC* ptr = &arg0->unk_CC;

    if (arg2 < 2) {
        if ((arg1 == 2) || (arg1 == 4)) {
            ptr->unk_00 = 0;
        } else {
            ptr->unk_00 = 1;
        }
    } else {
        ptr->unk_00 = arg1;
        ptr->unk_08 = arg2;
        ptr->unk_0A = 1;
        ptr->color.r = arg3;
        ptr->color.g = arg4;
        ptr->color.b = arg5;
    }
}
#endif

#ifdef VERSION_US
void func_80038F8C(void *arg0, void *arg1) {
    void *temp_v0;
    void *temp_v1;

    if ((arg0 != NULL) && (arg1 != NULL)) {
        temp_v0 = (*(void **)((u8 *)(arg0) + (0xC)));
        if (temp_v0 == NULL) {
            (*(void **)((u8 *)(arg0) + (0xC))) = arg1;
            (*(void **)((u8 *)(arg1) + (4))) = arg1;
            (*(void **)((u8 *)(arg1) + (8))) = arg1;
            return;
        }
        temp_v1 = (*(void **)((u8 *)(temp_v0) + (4)));
        (*(void **)((u8 *)(arg1) + (8))) = temp_v0;
        (*(void **)((u8 *)(arg1) + (4))) = temp_v1;
        (*(void **)((u8 *)(temp_v0) + (4))) = arg1;
        (*(void **)((u8 *)(temp_v1) + (8))) = arg1;
    }
}
#endif

#ifdef VERSION_US
typedef struct GraphNodeLink {
    char pad0[4];
    struct GraphNodeLink *prev;
    struct GraphNodeLink *next;
} GraphNodeLink;
typedef struct {
    char pad[0xC];
    GraphNodeLink *child;
} GraphNode38FD4;

void GraphNode_RemoveChild(GraphNode38FD4 *root, GraphNodeLink *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    if (node == root->child) {
        if (node == node->next) {
            root->child = NULL;
        } else {
            root->child = node->next;
        }
    }
}
#endif

#ifdef VERSION_US
typedef struct unk_func_80039018 {
    u32 unk_00[2];
    struct unk_func_80039018 *unk_08;
    struct unk_func_80039018 *unk_0C;
} unk_func_80039018;

unk_func_80039018 *func_80039018(unk_func_80039018 *arg0, s32 arg1) {
    unk_func_80039018 *var_v1 = arg0->unk_0C;
    s32 var_v0;

    if (var_v1 != NULL) {
        for (var_v0 = 0; var_v0 < arg1; var_v0++) {
            var_v1 = var_v1->unk_08;
        }
    }
    return var_v1;
}
#pragma C_FUNCTION_PADDING(4)
#endif

#ifdef VERSION_US
extern Gfx *Gfx_AllocDisplayList(s32);
extern void MtxF_ToFixed(void *, S1_MtxF *);
extern u8 D_80124F68;
typedef struct {
    S1_MtxF matrices[64];
    Mtx *stack[32];
    s8 flags[32];
    s32 top;
} SceneTransformPool;
void func_80039070(s32 arg0) { *(s32 *)((u8 *)&D_80124F68 + 0x10A0) = 0; *((u8 *)&D_80124F68 + 0x1080) = 0; MtxF_Identity((f32 *)&D_80124F68); if (arg0 == 0) { *(s32 *)((u8 *)&D_80124F68 + 0x1000) = (s32)Gfx_AllocDisplayList(0x40); } else { *(s32 *)((u8 *)&D_80124F68 + 0x1000) = arg0; } MtxF_ToFixed((void *)*(s32 *)((u8 *)&D_80124F68 + 0x1000), (S1_MtxF *)&D_80124F68); }
#endif

#ifdef VERSION_US
void GeoRender_CommitMatrix(Mtx *fixed) {
    ((SceneTransformPool *)&D_80124F68)->flags[((SceneTransformPool *)&D_80124F68)->top] = 0;
    if (fixed == NULL) {
        ((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top] = (Mtx *)Gfx_AllocDisplayList(0x40);
    } else {
        ((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top] = fixed;
    }
    MtxF_ToFixed(((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top], &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top]);
}
#endif

#ifdef VERSION_US
Mtx *GeoRender_SetMatrix(S1_MtxF *matrix, Mtx *fixed) {
    MtxF_Copy((u32 *)(&((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top]), (u32 *)matrix);
    ((SceneTransformPool *)&D_80124F68)->flags[((SceneTransformPool *)&D_80124F68)->top] = 0;
    if (fixed == NULL) {
        ((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top] = (Mtx *)Gfx_AllocDisplayList(0x40);
    } else {
        ((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top] = fixed;
    }
    MtxF_ToFixed(((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top], &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top]);
    return ((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top];
}
#endif

#ifdef VERSION_US
void GeoRender_PushMultipliedMatrix(S1_MtxF *matrix, Mtx *fixed) {
    ((SceneTransformPool *)&D_80124F68)->top++;
    MtxF_Multiply(&((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top], matrix, &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top - 1]);
    ((SceneTransformPool *)&D_80124F68)->flags[((SceneTransformPool *)&D_80124F68)->top] = 0;
    if (fixed == NULL) {
        ((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top] = (Mtx *)Gfx_AllocDisplayList(0x40);
    } else {
        ((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top] = fixed;
    }
    MtxF_ToFixed(((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top], &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top]);
}
#endif

#ifdef VERSION_US
Mtx *GeoRender_PushScaledMatrix(S1_Vec3f *scale, Mtx *fixed) {
    ((SceneTransformPool *)&D_80124F68)->top++;
    MtxF_ScaleRows(&((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top], &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top - 1], scale);
    ((SceneTransformPool *)&D_80124F68)->flags[((SceneTransformPool *)&D_80124F68)->top] = 0;
    if (fixed == NULL) {
        ((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top] = (Mtx *)Gfx_AllocDisplayList(0x40);
    } else {
        ((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top] = fixed;
    }
    MtxF_ToFixed(((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top], &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top]);
    return ((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top];
}
#endif

#ifdef VERSION_US
extern u8 D_80124F68;
void *func_8003936C(s32 arg0) {
    void *var_v1;
    struct PoolBase {
        u8 pad[0x10A0];
        s32 count;
    };

    var_v1 = NULL;
    if (arg0 <= 0) {
        var_v1 = (void *)((u8 *)&D_80124F68 + (((struct PoolBase *)&D_80124F68)->count << 6) + (arg0 << 6));
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
extern u8 D_80124F68;

void *GeoRender_GetMatrix(s32 arg0) {
    void *var_v1;

    var_v1 = NULL;
    if ((arg0 >= 0) && (arg0 < 0x20)) {
        var_v1 = (arg0 << 6) + &D_80124F68;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
extern u8 D_80126010;
extern u8 D_800948E4[];
void GeoRender_ResetTransformStack(void) {
    struct Vec3Words {
        s32 x;
        s32 y;
        s32 z;
    };
    struct State {
        struct Vec3Words value;
        u8 pad[0x174];
        s32 flag;
    };

    ((struct State *)&D_80126010)->flag = 0;
    ((struct State *)&D_80126010)->value = *(struct Vec3Words *)D_800948E4;
}
#endif

#ifdef VERSION_US
extern u8 D_80126010;
void func_800393F0(S1_Vec3f *arg0) {
    S1_Vec3f *vec = (S1_Vec3f *)&D_80126010;
    s32 *counter = (s32 *)((u8 *)&D_80126010 + 0x180);
    vec[*counter + 1].x = vec[*counter].x * arg0->x;
    vec[*counter + 1].y = vec[*counter].y * arg0->y;
    vec[*counter + 1].z = vec[*counter].z * arg0->z;
    (*counter)++;
}
#endif

#ifdef VERSION_US
extern void Gfx_SetVertexAttributes(Vtx *, s16, s16, s16, s16, s16, u8, u8, u8, u8);
// Allocate the four projection-plane corners used by GeoOverlay_DrawFadeQuad.
Vtx *GeoOverlay_BuildFadeQuad(S1_unk_D_86002F34_00C_0CC *overlay, S1_unk_D_86002F34_00C_040 *projection) {
    u8 alpha;
    Vtx *vertices;

    vertices = Gfx_AllocDisplayList(4 * sizeof(Vtx));
    if (vertices != NULL) {
        switch (overlay->unk_00) {
        case 1:
            alpha = 255;
            break;
        case 2:
            alpha = 255 - (overlay->unk_0A * 255) / overlay->unk_08;
            break;
        case 3:
            alpha = (overlay->unk_0A * 255) / overlay->unk_08;
            break;
        }
        Gfx_SetVertexAttributes(&vertices[0], (s16)projection->l, (s16)projection->t, -1, 0, 0, overlay->color.r, overlay->color.g, overlay->color.b, alpha);
        Gfx_SetVertexAttributes(&vertices[1], (s16)projection->l, (s16)projection->b, -1, 0, 0, overlay->color.r, overlay->color.g, overlay->color.b, alpha);
        Gfx_SetVertexAttributes(&vertices[2], (s16)projection->r, (s16)projection->b, -1, 0, 0, overlay->color.r, overlay->color.g, overlay->color.b, alpha);
        Gfx_SetVertexAttributes(&vertices[3], (s16)projection->r, (s16)projection->t, -1, 0, 0, overlay->color.r, overlay->color.g, overlay->color.b, alpha);
    }
    return vertices;
}
#endif

#ifdef VERSION_US
void GeoOverlay_DrawFadeQuad(S1_unk_D_86002F34_00C_0CC* arg0, S1_unk_D_86002F34_00C_040* arg1) {
    Vtx* temp_v0 = GeoOverlay_BuildFadeQuad(arg0, arg1);

    if (temp_v0 != NULL) {
        gDPSetCombineMode(D_800D0510++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(D_800D0510++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);

        gSPVertex(D_800D0510++, (u32)temp_v0 & 0x1FFFFFFF, 4, 0);
        gSP2Triangles(D_800D0510++, 0, 1, 2, 0, 0, 2, 3, 0);
    }

    if (arg0->unk_00 != 1) {
        arg0->unk_0A++;
        if (arg0->unk_0A == arg0->unk_08) {
            if (arg0->unk_00 == 2) {
                arg0->unk_00 = 0;
            } else {
                arg0->unk_00 = 1;
            }
        }
    }
}
#endif

#ifdef VERSION_US
#pragma SWAP_FUNCTION_WORDS(func_80039808, 0xD0, 0xAFB80024, 0x00063403)
extern s32 D_80039808_alpha_hint_0;
#define COSS(x) D_80088E50[(u16)(x) >> 4]
#define SINS(x) D_80087E50[(u16)(x) >> 4]
extern void Gfx_SetVertexAttributes(Vtx *, s16, s16, s16, s16, s16, u8, u8, u8, u8);
void func_80039808(Vtx* arg0, S1_unk_D_86002F34_00C_0CC* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7) {
    f32 temp_fa0;
    f32 temp_fv1;
    u16 idx = arg1->unk_18;
    f32 a4;
    f32 a5;
    s16 tmp1;
    s16 tmp2;

    a4 = arg4;
    temp_fv1 = COSS(idx);
    temp_fa0 = SINS(idx);
    a5 = arg5;

    tmp1 = ((a4 * temp_fv1) - (temp_fa0 * a5));
    tmp2 = ((temp_fv1 * a5) + (a4 * temp_fa0));

    Gfx_SetVertexAttributes(arg0, tmp1 + arg2, tmp2 + arg3, -1, arg6 * 32, arg7 * 32, arg1->color.r, arg1->color.g, arg1->color.b, ((u8)(arg2 - arg2) + 0xFF));
}
#endif

#ifdef VERSION_US
Vtx *func_800398F8(S1_unk_D_86002F34_00C_0CC *arg0) {
    Vtx *out = (Vtx *)Gfx_AllocDisplayList(0x80); Vtx *p; s16 x,y,z,nz;
    if (out) {
        x=arg0->unk_10+((arg0->unk_14-arg0->unk_10)*arg0->unk_0A)/arg0->unk_08; y=arg0->unk_12+((arg0->unk_16-arg0->unk_12)*arg0->unk_0A)/arg0->unk_08; z=arg0->unk_0C+((arg0->unk_0E-arg0->unk_0C)*arg0->unk_0A)/arg0->unk_08; nz=-z; p=out;
        if(arg0->unk_00==2){func_80039808(p++,arg0,x,y,nz,nz,-31,63);func_80039808(p++,arg0,x,y,z,nz,31,63);func_80039808(p++,arg0,x,y,z,z,31,0);func_80039808(p++,arg0,x,y,nz,z,-31,0);}else{func_80039808(p++,arg0,x,y,nz,nz,0,63);func_80039808(p++,arg0,x,y,z,nz,63,63);func_80039808(p++,arg0,x,y,z,z,63,0);func_80039808(p++,arg0,x,y,nz,z,0,0);}
        func_80039808(p++,arg0,x,y,-2000,-2000,0,0);func_80039808(p++,arg0,x,y,2000,-2000,0,0);func_80039808(p++,arg0,x,y,2000,2000,0,0);func_80039808(p,arg0,x,y,-2000,2000,0,0);
    } arg0->unk_18+=arg0->unk_1A; return out;
}
#endif

#ifdef VERSION_US
void GeoOverlay_DrawRotatingQuad(S1_unk_D_86002F34_00C_0CC* arg0, UNUSED S1_unk_D_86002F34_00C_040* arg1) {
    Vtx* temp_v0 = func_800398F8(arg0);

    if (temp_v0 != 0) {
        gDPSetCombineMode(D_800D0510++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(D_800D0510++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);

        gSPVertex(D_800D0510++, (u32)temp_v0 & 0x1FFFFFFF, 8, 0);
        gSP2Triangles(D_800D0510++, 0, 4, 1, 0, 1, 4, 5, 0);
        gSP2Triangles(D_800D0510++, 1, 5, 2, 0, 2, 5, 6, 0);
        gSP2Triangles(D_800D0510++, 2, 6, 7, 0, 2, 7, 3, 0);
        gSP2Triangles(D_800D0510++, 3, 4, 0, 0, 3, 7, 4, 0);

        gDPPipeSync(D_800D0510++);

        gDPSetCombineMode(D_800D0510++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
        gDPSetRenderMode(D_800D0510++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        gDPSetTextureFilter(D_800D0510++, G_TF_BILERP);

        if (arg0->unk_02 == 0) {
            gDPLoadTextureBlock(D_800D0510++, arg0->texture, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureBlock(D_800D0510++, arg0->texture, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, 0,
                                G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
        }

        gSPTexture(D_800D0510++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

        gSPVertex(D_800D0510++, (u32)temp_v0 & 0x1FFFFFFF, 4, 0);
        gSP2Triangles(D_800D0510++, 0, 1, 2, 0, 0, 2, 3, 0);

        gSPTexture(D_800D0510++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetTextureFilter(D_800D0510++, G_TF_BILERP);
    }

    arg0->unk_0A++;
    if (arg0->unk_0A == arg0->unk_08) {
        if (arg0->unk_00 == 4) {
            arg0->unk_00 = 0;
        } else {
            arg0->unk_00 = 1;
        }
    }
}
#endif

#ifdef VERSION_US
void GeoOverlay_Draw(S1_unk_D_86002F34_00C_0CC* arg0, S1_unk_D_86002F34_00C_040* arg1) {
    if (arg0->unk_00 != 0) {
        gDPPipeSync(D_800D0510++);

        gDPSetCycleType(D_800D0510++, G_CYC_1CYCLE);
        gSPClearGeometryMode(D_800D0510++, G_ZBUFFER | G_LIGHTING);
        gSPPerspNormalize(D_800D0510++, 0xFFFF);
        gSPMatrix(D_800D0510++, (u32)arg1->mtx & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(D_800D0510++, (u32)&D_80094890 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if ((arg0->unk_00 == 1) || (arg0->unk_00 == 2) || (arg0->unk_00 == 3)) {
            GeoOverlay_DrawFadeQuad(arg0, arg1);
        } else {
            GeoOverlay_DrawRotatingQuad(arg0, arg1);
        }

        gDPPipeSync(D_800D0510++);
        gDPSetCycleType(D_800D0510++, G_CYC_2CYCLE);
    }
}
#endif

#ifdef VERSION_US
extern s32 D_80124D60;
extern void *D_80094924[];
void Geo_ProcessNodeChildren(void *root) {
    S1_GraphNode *first;
    S1_GraphNode *child;
    first = (S1_GraphNode *)((S1_GraphNode *)root)->unk_0C;
    child = first;
    if (first != NULL) {
        do {
            if (child->unk_01 & 1) {
                D_80124D60 = 0;
                if (child->unk_10 != NULL) {
                    D_80124D60 = child->unk_10(2, child);
                }
                ((void (*)(S1_GraphNode *))D_80094924[child->unk_00])(child);
            }
            child = child->unk_08;
        } while (child != first);
    }
}
#endif

#ifdef VERSION_US
extern s32 D_80124D60;
extern void func_8003B690(s32);
extern void Geo_PrepareAnimatedPart(s32);
void Geo_PrepareShadowChildren(s32 root) {
    S1_GraphNode *first = (S1_GraphNode *)((S1_GraphNode *)root)->unk_0C;
    S1_GraphNode *node = first;
    if (first != NULL) {
        do {
            if (node->unk_01 & 1) {
                D_80124D60 = 0;
                if (node->unk_10 != NULL) {
                    D_80124D60 = node->unk_10(6, node);
                }
                switch (node->unk_00) {
                default:
                    Geo_PrepareShadowChildren((s32)node);
                    break;
                case 0x13:
                    func_8003B690((s32)node);
                    break;
                case 0x14:
                    Geo_PrepareAnimatedPart((s32)node);
                    break;
                }
            }
            node = node->unk_08;
        } while (node != first);
    }
}
#endif

#ifdef VERSION_US
extern s32 D_80124D60;
extern void *D_80094924[];
extern void Geo_ProcessNodeChildren(void *);
void Geo_NodeReference(void *arg0) {
    s32 (*callback)(s32, void *);
    void *child;
    callback = 0;
    child = *(void **)((u8 *)arg0 + 0x18);
    if (child != 0 && (*(u8 *)((u8 *)child + 1) & 1) != 0) {
        D_80124D60 = 0;
        callback = *(s32 (**)(s32, void *))((u8 *)child + 0x10);
        if (callback != 0) {
            D_80124D60 = callback(2, child);
        }
        ((void (*)(void *))((void **)D_80094924)[*(u8 *)child])(child);
    }
    Geo_ProcessNodeChildren(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003A4CC.s")
#endif

#ifdef VERSION_US
extern s32 D_8009490C;
extern void Geo_ProcessNodeChildren(void *);
void Geo_NodeType3Pass(s32 arg0) {
    D_8009490C = arg0;
    Geo_ProcessNodeChildren((void *)arg0);
    D_8009490C = 0;
}
#endif

#ifdef VERSION_US
typedef struct {
    u8 pad[0x1A];
    u16 unk_1A;
    s8 lightCount;
    s8 unknown1D;
    s8 activeLights;
    s8 extraGeometryMode;
    u32 unknown20;
    Lights7 *lights;
} ModelFrame;
extern ModelFrame *D_80094910;
extern u16 D_80094904;
extern void ModelAnim_ResetCurveContext(void);
extern void ModelAnim_ResetEventContext(void);
extern void Geo_ProcessNodeChildren(void *);
extern Gfx* D_800D0510;
extern u8 D_80124F68;
void Geo_NodeModelRoot(void *root) {
    ModelFrame *node = (ModelFrame *)root;
    if (((S1_GraphNode *)root)->unk_0C != NULL) {
        node->unknown1D = 0;
        node->unknown20 = -1;
        node->lights = (Lights7 *)Gfx_AllocDisplayList(sizeof(Lights7));
        node->lightCount = 0;
        node->activeLights = 0;
        node->extraGeometryMode = 0;
        node->lights->a.l.col[0] = 0;
        node->lights->a.l.col[1] = 0;
        node->lights->a.l.col[2] = 0;
        // Geo_NodeAmbientLight conditionally enables the unnamed 0x00400000 bit.
        gSPClearGeometryMode(D_800D0510++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0x00400000);
        gSPSetGeometryMode(D_800D0510++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
        gSPTexture(D_800D0510++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetCycleType(D_800D0510++, G_CYC_2CYCLE);
        ModelAnim_ResetCurveContext();
        ModelAnim_ResetEventContext();
        func_80039070(0);
        GeoRender_ResetTransformStack();
        gSPMatrix(D_800D0510++, (u32)((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top] & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        D_80094910 = node;
        Geo_ProcessNodeChildren(root);
        D_80094910 = NULL;
    }
    node->unk_1A = D_80094904;
}
#endif

#ifdef VERSION_US
extern S1_unk_D_86002F34_00C *D_80094914;
extern s32 D_80094900;
extern void GeoRender_InitMaterialState(s32, s32);
extern void GeoRender_FlushMaterialSlots(void);
void Geo_NodeModelPartRoot(void *root) {
    void *node;
    node = root;
    if (D_80094914 == NULL && ((S1_GraphNode *)node)->unk_0C != NULL) {
        D_80094914 = (S1_unk_D_86002F34_00C *)node;
        GeoRender_InitMaterialState(((S1_GraphNode *)node)->unk_02 & 7, D_80094900);
        Geo_ProcessNodeChildren(root);
        GeoRender_FlushMaterialSlots();
        D_80094914 = NULL;
    }
}
#endif

#ifdef VERSION_US
extern S1_unk_D_86002F34_00C *D_80094914;
extern void Geo_NodeModelPartRoot(void *);
extern void * D_80094908;
extern Gfx* D_800D0510;
void Geo_NodeOrtho(void *root) {
    if (D_80094914 == NULL && ((S1_GraphNode *)root)->unk_0C != NULL) {
        gSPPerspNormalize(D_800D0510++, 0xFFFF);
        gSPMatrix(D_800D0510++, (u32)((S1_unk_D_86002F34_00C *)D_80094908)->unk_40.mtx & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        Geo_NodeModelPartRoot(root);
    }
}
#endif

#ifdef VERSION_US
void Geo_NodePerspective(void *root) {
    if (D_80094914 == NULL && ((S1_GraphNode *)root)->unk_0C != NULL) {
        gSPLookAt(D_800D0510++, (u32)(((S1_unk_D_86002F34_00C *)D_80094908)->unk_60.lookat) & 0x1FFFFFFF);
        gSPPerspNormalize(D_800D0510++, ((S1_unk_D_86002F34_00C *)D_80094908)->unk_24.perspNorm);
        gSPMatrix(D_800D0510++, (u32)((S1_unk_D_86002F34_00C *)D_80094908)->unk_24.mtx & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(D_800D0510++, (u32)((S1_unk_D_86002F34_00C *)D_80094908)->unk_60.p_mtxf & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        Geo_NodeModelPartRoot(root);
    }
}
#endif

#ifdef VERSION_US
extern void *D_80094908;
extern void GfxImage_FillRectangle(Gfx **, s16, s16, s16, s16, s32);
extern Gfx* D_800D0510;
void Geo_NodeBackground(u8 *arg0) { u8 *state = (u8 *)D_80094908 + 0x18; GfxImage_FillRectangle(&D_800D0510, *(s16 *)(state + 4), *(s16 *)(state + 6), *(s16 *)(state + 8), *(s16 *)(state + 10), *(s32 *)(arg0 + 0x18)); gDPPipeSync(D_800D0510++); gSPSetOtherMode(D_800D0510++, G_SETOTHERMODE_H, 20, 2, 0x100000); }
#endif

#ifdef VERSION_US
extern void *D_80094908;
extern void GfxImage_ClearDepthRectangle(void *, s32, s32, s32, s32);
extern Gfx* D_800D0510;
void Geo_NodeClearDepth(s32 arg0) {
    void *state = (u8 *)D_80094908 + 0x18;
    GfxImage_ClearDepthRectangle(&D_800D0510, *(s16 *)((u8 *)state + 4), *(s16 *)((u8 *)state + 6), *(s16 *)((u8 *)state + 8), *(s16 *)((u8 *)state + 10));
    gDPPipeSync(D_800D0510++);
    gDPSetCycleType(D_800D0510++, G_CYC_2CYCLE);
}
#endif

#ifdef VERSION_US
void func_8003AC84(s32 arg0) {}
#endif

#ifdef VERSION_US
extern ModelFrame *D_80094910;
extern Gfx* D_800D0510;
void Geo_NodeFog(S1_GraphNode *root) {
    S1_unk_D_86002F34_alt3 *node = (S1_unk_D_86002F34_alt3 *)root;
    D_80094910->unknown1D = 1;
    D_80094910->unknown20 = node->unk_1C;
    gSPFogPosition(D_800D0510++, node->unk_18, node->unk_1A);
    gSPSetGeometryMode(D_800D0510++, G_FOG);
    gDPSetColor(D_800D0510++, G_SETFOGCOLOR, node->unk_1C);
}
#endif

#ifdef VERSION_US
typedef union {
    Light directional;
    struct {
        u32 color;
        u32 colorCopy;
        S1_Vec3s position;
        u8 quadratic;
        u8 padF;
    } point;
} SceneLightRecord;
extern f32 D_80087E50[];
extern f32 D_80088E50[0x1000];
extern Gfx* D_800D0510;
void Geo_NodeLight(S1_GraphNode *root) {
    SceneDirectionalLight *node = (SceneDirectionalLight *)root;
    SceneLightRecord *light;
    s32 index;
    if (D_80094910->lightCount >= 7) {
        return;
    }
    light = (SceneLightRecord *)&D_80094910->lights->l[D_80094910->lightCount];
    if (node->overrideDirection == 0) {
        light->directional.l.pad1 = 0;
        *(u32 *)light->directional.l.col = node->color.rgba;
        *(u32 *)light->directional.l.colc = node->color.rgba;
        light->directional.l.dir[0] = (120.0f * D_80088E50[((u16)node->pitch >> 4)]) * D_80087E50[((u16)node->yaw >> 4)];
        light->directional.l.dir[1] = 120.0f * D_80087E50[((u16)node->pitch >> 4)];
        light->directional.l.dir[2] = (120.0f * D_80088E50[((u16)node->pitch >> 4)]) * D_80088E50[((u16)node->yaw >> 4)];
    } else {
        light->point.color = node->color.rgba;
        light->point.colorCopy = node->color.rgba;
        light->point.position.x = node->direction.x;
        light->point.position.y = node->direction.y;
        light->point.position.z = node->direction.z;
        light->directional.l.pad1 = node->red;
        light->directional.l.pad2 = node->green;
        light->point.quadratic = node->blue;
        D_80094910->extraGeometryMode++;
    }
    D_80094910->lightCount++;
    if (node->node.unk_02 & 1) {
        gMoveWd(D_800D0510++, G_MW_NUMLIGHT, 0, D_80094910->lightCount * 0x18);
        for (index = D_80094910->activeLights; index < D_80094910->lightCount; index++) {
            gSPLight(D_800D0510++, &D_80094910->lights->l[index], index + 1);
        }
        gSPLight(D_800D0510++, D_80094910->lights, index + 1);
    }
}
#endif

#ifdef VERSION_US
void func_8003B03C(s32 arg0) {}
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
typedef struct {
    S1_GraphNode node;
    S1_Color_RGBA8_u32 color;
} SceneAmbientLightNode;
void Geo_NodeAmbientLight(void *root) {
    SceneAmbientLightNode *node = root;
    s32 i;
    Lights7 *lights;
    lights = D_80094910->lights;
    if (node->color.r == 0xFF && node->color.g == 0xFF && node->color.b == 0xFF) {
        lights->a.l.colc[0] = lights->a.l.col[0];
        lights->a.l.colc[1] = lights->a.l.col[1];
        lights->a.l.colc[2] = lights->a.l.col[2];
    } else {
        lights->a.l.colc[0] = lights->a.l.col[0] = node->color.r;
        lights->a.l.colc[1] = lights->a.l.col[1] = node->color.g;
        lights->a.l.colc[2] = lights->a.l.col[2] = node->color.b;
    }
    D_80094910->activeLights = D_80094910->lightCount;
    gSPSetGeometryMode(D_800D0510++, G_LIGHTING);
    if (D_80094910->extraGeometryMode > 0) {
        gSPSetGeometryMode(D_800D0510++, 0x00400000);
    }
    gMoveWd(D_800D0510++, G_MW_NUMLIGHT, 0, D_80094910->lightCount * 0x18);
    for (i = 0; i < D_80094910->lightCount; i++) {
        gSPLight(D_800D0510++, &D_80094910->lights->l[i], i + 1);
    }
    gSPLight(D_800D0510++, D_80094910->lights, i + 1);
}
#endif

#ifdef VERSION_US
extern Gfx* D_800D0510;
void Geo_NodeUpdateLights(S1_GraphNode *root) {
    s32 index;
    if (D_80094910->activeLights != D_80094910->lightCount) {
        D_80094910->lightCount = D_80094910->activeLights;
        gMoveWd(D_800D0510++, G_MW_NUMLIGHT, 0, D_80094910->lightCount * 0x18);
        for (index = 0; index < D_80094910->lightCount; index++) {
            gSPLight(D_800D0510++, &D_80094910->lights->l[index], index + 1);
        }
        gSPLight(D_800D0510++, D_80094910->lights, index + 1);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B350.s")
#endif

#ifdef VERSION_US
extern void Geo_ProcessNodeChildren(void *root);
extern void * D_80094908;
extern u8 D_80124F68;
void Geo_NodeCullDistance(S1_GraphNode *root) {
    S1_unk_D_86002F34_alt3 *range = (S1_unk_D_86002F34_alt3 *)root;
    S1_MtxF *view = &((S1_unk_D_86002F34_00C *)D_80094908)->unk_60.mtxf;
    f32 x = ((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top].mf[3][0];
    f32 y = ((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top].mf[3][1];
    f32 z = ((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top].mf[3][2];
    s16 depth = ((x * view->mf[0][2]) + (y * view->mf[1][2]) + (z * view->mf[2][2])) + view->mf[3][2];
    if ((depth >= range->unk_18) && (depth < range->unk_1A)) {
        Geo_ProcessNodeChildren(root);
    }
}
#endif

#ifdef VERSION_US
extern void * D_80094924[];
void Geo_NodeSwitchCase(S1_GraphNode *root) {
    S1_unk_D_86002F34_alt3 *selection = (S1_unk_D_86002F34_alt3 *)root;
    s32 index;
    S1_GraphNode *child = (S1_GraphNode *)selection->unk_00.unk_0C;
    if (child != NULL) {
        for (index = 0; index < selection->unk_1A; index++) {
            child = child->unk_08;
        }
    }
    if (child->unk_01 & 1) {
        ((void (*)(S1_GraphNode *))D_80094924[child->unk_00])(child);
    }
}
#endif

#ifdef VERSION_US
extern void GeoRender_PushMultipliedMatrix(S1_MtxF *, Mtx *);
void func_8003B5AC(u8 *arg0) {
    struct {
        u8 unused[8];
        f32 matrix[4][4];
    } scratch;

    MtxF_SetRotationTranslationF(scratch.matrix, (Vec3f35784 *)(arg0 + 0x18), (Vec3s35AA0 *)(arg0 + 0x24));
    GeoRender_PushMultipliedMatrix((S1_MtxF *)scratch.matrix, NULL);
    Geo_ProcessNodeChildren(arg0);
    *(s32 *)((u8 *)&D_80124F68 + 0x10A0) -= 1;
}
#endif

#ifdef VERSION_US
extern u8 *D_80094920;
extern s32 D_8009499C;
extern Mtx *GeoRender_PushScaledMatrix(S1_Vec3f *, Mtx *);
void func_8003B600(u8 *arg0) {
    s32 status = 0;
    if (D_80094920 != NULL && (*(u16 *)(D_80094920 + 0x28) & 1) != 0) {
        status = 1;
    }
    if (status != 0) {
        GeoRender_PushScaledMatrix((S1_Vec3f *)(arg0 + 0x18), (Mtx *)D_8009499C);
    } else {
        D_8009499C = (s32)GeoRender_PushScaledMatrix((S1_Vec3f *)(arg0 + 0x18), NULL);
    }
    Geo_ProcessNodeChildren(arg0);
    (*(s32 *)((u8 *)&D_80124F68 + 0x10A0))--;
}
#endif

#ifdef VERSION_US
Mtx *GeoRender_PushScaledMatrix(S1_Vec3f *, Mtx *);
extern void Geo_PrepareShadowChildren(s32);
extern s32 D_8009499C;

void func_8003B690(s32 arg0) {
    D_8009499C = (s32)GeoRender_PushScaledMatrix((S1_Vec3f *)(arg0 + 0x18), NULL);
    Geo_PrepareShadowChildren(arg0);
    (*(s32 *)((u8 *)(&D_80124F68) + (0x10A0))) = (s32) ((*(s32 *)((u8 *)(&D_80124F68) + (0x10A0))) - 1);
}
#endif

#ifdef VERSION_US
extern void func_8003E8C8(S1_Vec3f *, S1_Vec3s *, S1_Vec3f *, s32);
extern void MtxF_SetRotationScaleTranslation(S1_MtxF *, S1_Vec3f *, S1_Vec3s *, S1_Vec3f *);
extern void MtxF_SetRotationAndScaledTranslation(S1_MtxF *, S1_Vec3f *, S1_Vec3s *, S1_Vec3f *);
extern void func_800393F0(S1_Vec3f *);
extern s32 D_80124D68[];
extern s32 D_80126190;
typedef struct {
    S1_Vec3f vectors[32];
    s32 top;
} SceneScaleStack;
extern void GeoRender_CommitMatrix(Mtx *fixed);
extern void * D_80094908;
extern u8 D_80124F68;
extern u8 D_80126010;
extern void Geo_ProcessNodeChildren(void *root);
extern u8 * D_80094920;
void Geo_NodeAnimatedPart(s32 root) {
    S1_Vec3s rotation;
    S1_Vec3f position;
    S1_Vec3f scaling;
    S1_MtxF matrix;
    S1_unk_D_86002F34_alt6 *node = (S1_unk_D_86002F34_alt6 *)root;
    s32 pushed;
    s32 reuse;
    pushed = 0;
    reuse = 0;
    if (D_80094920 != NULL && (*(u16 *)(D_80094920 + 0x28) & 1) != 0) {
        reuse = 1;
    }
    rotation = node->unk_1E;
    scaling = node->unk_24;
    Vec3f_FromVec3s((Vec3f358AC *)&position, (Vec3s358AC *)&node->unk_18);
    func_8003E8C8(&position, &rotation, &scaling, node->unk_32 * 3);
    if (node->unk_31 & 2) {
        MtxF_BuildTransform(&matrix, &position, &rotation, &scaling, &((S1_unk_D_86002F34_00C *)D_80094908)->unk_60.mtxf, &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top]);
        ((SceneTransformPool *)&D_80124F68)->top++;
        if (reuse != 0) {
            GeoRender_SetMatrix(&matrix, (Mtx *)D_80124D68[node->unk_30]);
        } else {
            GeoRender_SetMatrix(&matrix, NULL);
        }
    } else if (node->unk_31 & 1) {
        MtxF_SetRotationScaleTranslation(&matrix, &position, &rotation, &scaling);
        if (reuse != 0) {
            GeoRender_PushMultipliedMatrix(&matrix, (Mtx *)D_80124D68[node->unk_30]);
        } else {
            GeoRender_PushMultipliedMatrix(&matrix, NULL);
        }
    } else {
        MtxF_SetRotationAndScaledTranslation(&matrix, &position, &rotation, &((SceneScaleStack *)&D_80126010)->vectors[((SceneScaleStack *)&D_80126010)->top]);
        ((SceneTransformPool *)&D_80124F68)->top++;
        func_800393F0(&scaling);
        if (((SceneTransformPool *)&D_80124F68)->flags[((SceneTransformPool *)&D_80124F68)->top - 1] == 1) {
            MtxF_Multiply(&((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top + 32], &matrix, &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top + 31]);
        } else {
            MtxF_Multiply(&((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top + 32], &matrix, &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top - 1]);
        }
        MtxF_ScaleRows(&((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top], &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top + 32], &((SceneScaleStack *)&D_80126010)->vectors[((SceneScaleStack *)&D_80126010)->top]);
        if (reuse != 0) {
            GeoRender_CommitMatrix((Mtx *)D_80124D68[node->unk_30]);
        } else {
            GeoRender_CommitMatrix(NULL);
        }
        ((SceneTransformPool *)&D_80124F68)->flags[((SceneTransformPool *)&D_80124F68)->top] = 1;
        pushed = 1;
    }
    if (reuse == 0) {
        D_80124D68[node->unk_30] = (s32)((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top];
    }
    Geo_ProcessNodeChildren((void *)root);
    ((SceneTransformPool *)&D_80124F68)->top--;
    if (pushed != 0) {
        ((SceneScaleStack *)&D_80126010)->top--;
    }
}
#endif

#ifdef VERSION_US
void Geo_PrepareAnimatedPart(s32 root) {
    S1_Vec3s rotation;
    S1_Vec3f position;
    S1_Vec3f scaling;
    S1_MtxF matrix;
    S1_unk_D_86002F34_alt6 *node = (S1_unk_D_86002F34_alt6 *)root;
    s32 pushed;
    pushed = 0;
    rotation = node->unk_1E;
    scaling = node->unk_24;
    Vec3f_FromVec3s((Vec3f358AC *)&position, (Vec3s358AC *)&node->unk_18);
    func_8003E8C8(&position, &rotation, &scaling, node->unk_32 * 3);
    if (node->unk_31 & 2) {
        MtxF_BuildTransform(&matrix, &position, &rotation, &scaling, &((S1_unk_D_86002F34_00C *)D_80094908)->unk_60.mtxf, &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top]);
        ((SceneTransformPool *)&D_80124F68)->top++;
        GeoRender_SetMatrix(&matrix, NULL);
    } else if (node->unk_31 & 1) {
        MtxF_SetRotationScaleTranslation(&matrix, &position, &rotation, &scaling);
        GeoRender_PushMultipliedMatrix(&matrix, NULL);
    } else {
        MtxF_SetRotationAndScaledTranslation(&matrix, &position, &rotation, &((SceneScaleStack *)&D_80126010)->vectors[((SceneScaleStack *)&D_80126010)->top]);
        ((SceneTransformPool *)&D_80124F68)->top++;
        func_800393F0(&scaling);
        if (((SceneTransformPool *)&D_80124F68)->flags[((SceneTransformPool *)&D_80124F68)->top - 1] == 1) {
            MtxF_Multiply(&((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top + 32], &matrix, &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top + 31]);
        } else {
            MtxF_Multiply(&((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top + 32], &matrix, &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top - 1]);
        }
        MtxF_ScaleRows(&((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top], &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top + 32], &((SceneScaleStack *)&D_80126010)->vectors[((SceneScaleStack *)&D_80126010)->top]);
        GeoRender_CommitMatrix(NULL);
        ((SceneTransformPool *)&D_80124F68)->flags[((SceneTransformPool *)&D_80124F68)->top] = 1;
        pushed = 1;
    }
    D_80124D68[node->unk_30] = (s32)((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top];
    Geo_PrepareShadowChildren(root);
    ((SceneTransformPool *)&D_80124F68)->top--;
    if (pushed != 0) {
        ((SceneScaleStack *)&D_80126010)->top--;
    }
}
#endif

#ifdef VERSION_US
extern s32 D_80124D68[];
extern void GeoRender_SubmitMaterial(s16, Mtx *);
extern void func_8003DA20(s32, s32);
extern void Geo_ProcessNodeChildren(void *);
void func_8003BC48(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x18) != 0) {
        GeoRender_SubmitMaterial(*((u8 *)arg0 + 3), D_80124D68[*(s16 *)((u8 *)arg0 + 0x1C)]);
        func_8003DA20(*(s32 *)((u8 *)arg0 + 0x18), (*((u8 *)arg0 + 2) & 4) != 0);
    }
    Geo_ProcessNodeChildren(arg0);
}
#endif

#ifdef VERSION_US
extern ModelFrame *D_80094910;
extern void *D_8009491C;
extern void *D_80094908;
extern u16 D_80094904;
extern void func_8003E7B0(S1_unk_D_86002F58_004_000_040_raw *, u16, s32);
extern void ModelAnim_BeginEventContext(S1_unk_D_86002F58_004_000_054 *, u16, s32);
extern void ModelAnim_EndCurveContext(void);
extern void ModelAnim_EndEventContext(void);
extern void GeoRender_SetMaterialParams(S1_Color_RGBA8_u32, u8, u32);
extern void func_800707D0(void *);
extern void func_80070860(s32);
extern void Geo_ProcessNodeChildren(void *);
extern u8 D_80124F68;
void Geo_NodeModelPart(void *root) {
    S1_MtxF matrix;
    S1_Color_RGBA8_u32 reset_color;
    S1_unk_D_86002F58_004_000 *node = (S1_unk_D_86002F58_004_000 *)root;
    if (node->animType == *(s16 *)((u8 *)D_80094910 + 0x18) || node->animType == 10) {
        node->anchorCount = 0;
        func_8003E7B0((S1_unk_D_86002F58_004_000_040_raw *)&node->unk_040, D_80094904, (node->unk_000.unk_02 & 0x20) != 0);
        ModelAnim_BeginEventContext(&node->unk_054, D_80094904, (node->unk_000.unk_02 & 0x20) != 0);
        if (node->unk_000.unk_02 & 0x10) {
            MtxF_Multiply(&matrix, &node->unk_060, &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top]);
        } else if (node->unk_000.unk_02 & 8) {
            func_80036714(&matrix, (s32)&((S1_unk_D_86002F34_00C *)D_80094908)->unk_60.mtxf, (s32)&((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top], (s32)&node->unk_024, 1.0f);
        } else if (node->unk_000.unk_02 & 0x80) {
            MtxF_SetRotationAndTransformTranslation(matrix.mf, (Vec3f35784 *)&node->unk_024, (Vec3s35AA0 *)&node->unk_01E);
            MtxF_Multiply(&matrix, &matrix, &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top]);
        } else {
            MtxF_SetRotationTranslationF(matrix.mf, (Vec3f35784 *)&node->unk_024, (Vec3s35AA0 *)&node->unk_01E);
            MtxF_Multiply(&matrix, &matrix, &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top]);
        }
        MtxF_ScaleRows(&((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top + 1], &matrix, &node->unk_030);
        if (!(node->unk_000.unk_02 & 4)) {
            ((SceneTransformPool *)&D_80124F68)->top++;
            GeoRender_CommitMatrix(NULL);
            D_8009491C = node;
            GeoRender_SetMaterialParams(node->unk_0A0, node->materialAlpha, node->textureMode);
            if (node->modelId >= 0) {
                func_800707D0(node);
            }
            Geo_ProcessNodeChildren(root);
            if (node->modelId >= 0) {
                func_80070860((s32)node);
            }
            reset_color.rgba = 0xFFFFFF00;
            GeoRender_SetMaterialParams(reset_color, 0xFF, 0);
            D_8009491C = NULL;
        }
        ModelAnim_EndCurveContext();
        ModelAnim_EndEventContext();
        ((SceneTransformPool *)&D_80124F68)->top--;
    }
}
#endif

#ifdef VERSION_US
extern void GeoRender_PushMultipliedMatrix(S1_MtxF *, Mtx *);
extern void GeoRender_SubmitMaterial(s16, Mtx *);
extern void func_8003DA20(s32, s32);
extern s32 D_80126008;
extern void Geo_ProcessNodeChildren(void *);
extern u8 D_80124F68;
void func_8003BEF0(void *arg0) { s32 *counter = &D_80126008; GeoRender_PushMultipliedMatrix((u8 *)arg0 + 0x1C, 0); if (*(s32 *)((u8 *)arg0 + 0x18) != 0 || *(s32 *)((u8 *)arg0 + 0x10) != 0) { GeoRender_SubmitMaterial(*((u8 *)arg0 + 3), ((s32 *)&D_80124F68)[*(s32 *)((u8 *)&D_80124F68 + 0x10A0) + 0x400]); if (*(void **)((u8 *)arg0 + 0x10) != 0) ((void (*)(s32, void *))(*(void **)((u8 *)arg0 + 0x10)))(5, arg0); func_8003DA20(*(s32 *)((u8 *)arg0 + 0x18), (*((u8 *)arg0 + 2) & 4) != 0); } Geo_ProcessNodeChildren(arg0); *counter = *counter - 1; }
#endif

#ifdef VERSION_US
extern Mtx *GeoRender_SetMatrix(S1_MtxF *, Mtx *);
extern void Geo_ProcessNodeChildren(void *);
extern void * D_80094908;
extern u8 D_80124F68;
void func_8003BF9C(void *arg0) {
    S1_MtxF sp30;
    u8 (*pool)[0x40] = (u8 (*)[0x40])(void *)&D_80124F68;
    func_80036714(&sp30, (s32)((u8 *)D_80094908 + 0x64), (s32)pool[*(s32 *)((u8 *)&D_80124F68 + 0x10A0)], (s32)((u8 *)arg0 + 0x1C), *(f32 *)((u8 *)arg0 + 0x28));
    (*(s32 *)((u8 *)&D_80124F68 + 0x10A0))++;
    GeoRender_SetMatrix(&sp30, 0);
    if (*(s32 *)((u8 *)arg0 + 0x18) != 0 || *(s32 *)((u8 *)arg0 + 0x10) != 0) {
        GeoRender_SubmitMaterial(*((u8 *)arg0 + 3), ((s32 *)&D_80124F68)[*(s32 *)((u8 *)&D_80124F68 + 0x10A0) + 0x400]);
        if (*(void **)((u8 *)arg0 + 0x10) != 0) ((void (*)(s32, void *))(*(void **)((u8 *)arg0 + 0x10)))(5, arg0);
        func_8003DA20(*(s32 *)((u8 *)arg0 + 0x18), (*((u8 *)arg0 + 2) & 4) != 0);
    }
    Geo_ProcessNodeChildren(arg0);
    (*(s32 *)((u8 *)&D_80124F68 + 0x10A0))--;
}
#endif

#ifdef VERSION_US
extern void Geo_ProcessNodeChildren(void *);
extern u8 D_80124F68;
void Geo_NodeDisplayList(void *arg0) {
    void *root = arg0;
    s32 callback;
    if (*(s32 *)((u8 *)root + 0x18) != 0 || *(s32 *)((u8 *)root + 0x10) != 0) {
        GeoRender_SubmitMaterial(*(u8 *)((u8 *)root + 3), ((s32 *)((u8 *)&D_80124F68 + 0x1000))[*(s32 *)((u8 *)&D_80124F68 + 0x10A0)]);
        callback = *(s32 *)((u8 *)root + 0x10);
        if (callback != 0) ((void (*)(s32, void *))callback)(5, root);
        func_8003DA20(*(s32 *)((u8 *)root + 0x18), (*(u8 *)((u8 *)root + 2) & 4) != 0);
    }
    Geo_ProcessNodeChildren(root);
}
#endif

#ifdef VERSION_US
typedef union CandidateColor {
    struct { u8 r, g, b, a; };
    u32 rgba;
} CandidateColor;
extern u8 *D_80094920;
extern void *D_8009491C;
extern void func_8003EE20(s32 *, s32, s32);
extern void GeoRender_SetMaterialTexture(s32, CandidateColor, void *, void *, s32);
extern void Geo_ProcessNodeChildren(void *);
void Geo_NodeShadowTexture(void *root) {
    CandidateColor color;
    S1_unk_D_86002F34_alt10 *node = (S1_unk_D_86002F34_alt10 *)root;
    s32 texture;
    s32 material;
    s32 display_list;
    texture = 0;
    material = 0;
    display_list = (s32)node->unk_18;
    if (node->unk_22 == 1) {
        color.rgba = 0xFFFFFFFF;
    } else {
        color.rgba = node->unk_24.rgba;
    }
    if (node->unk_1C >= 0) {
        texture = *(s32 *)(D_80094920 + 0x18) + node->unk_1C * 12;
    }
    if (node->unk_1E >= 0) {
        material = *(s32 *)(D_80094920 + 0x1C) + node->unk_1E * 12;
    }
    if (D_8009491C != NULL) {
        color.r = (color.r * ((S1_unk_D_86002F58_004_000 *)D_8009491C)->unk_03C.r) / 255;
        color.g = (color.g * ((S1_unk_D_86002F58_004_000 *)D_8009491C)->unk_03C.g) / 255;
        color.b = (color.b * ((S1_unk_D_86002F58_004_000 *)D_8009491C)->unk_03C.b) / 255;
    }
    func_8003EE20(&texture, *(s32 *)(D_80094920 + 0x18), node->unk_20);
    GeoRender_SetMaterialTexture(node->unk_22, color, (void *)texture, (void *)material, display_list);
    Geo_ProcessNodeChildren(root);
}
#endif

#ifdef VERSION_US
extern void *D_8009491C;
extern u8 D_80124F68;
typedef struct {
    u16 id;
    u8 unknown02;
    S1_Vec3f position;
} SceneAnchorPosition;
typedef struct {
    S1_unk_D_86002F58_004_000_000 header;
    s16 animation;
    s16 model;
    u8 textureMode;
    u8 materialAlpha;
    S1_Vec3s rotation;
    S1_Vec3f position;
    S1_Vec3f scale;
    S1_Color_RGBA8_u32 tint;
    S1_unk_D_86002F58_004_000_040 transform;
    S1_unk_D_86002F58_004_000_054 events;
    S1_MtxF matrix;
    S1_Color_RGBA8_u32 color;
    u16 unknownA4;
    u8 poolIndex;
    u8 anchorCount;
    SceneAnchorPosition anchors[12];
} SceneDisplayObjectAnchors;
void func_8003C2D8(s32 id) {
    S1_MtxF *matrix;
    SceneAnchorPosition *anchor;
    if (((SceneDisplayObjectAnchors *)D_8009491C) != NULL) {
        if (((SceneDisplayObjectAnchors *)D_8009491C)->anchorCount < 12) {
            anchor = &((SceneDisplayObjectAnchors *)D_8009491C)->anchors[
                ((SceneDisplayObjectAnchors *)D_8009491C)->anchorCount++];
            matrix = &((SceneTransformPool *)&D_80124F68)->matrices[
                ((SceneTransformPool *)&D_80124F68)->top];
            anchor->id = id;
            anchor->position.x = matrix->mf[3][0];
            anchor->position.y = matrix->mf[3][1];
            anchor->position.z = matrix->mf[3][2];
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_8003C2D8(s32);
extern void Geo_ProcessNodeChildren(void *);
void Geo_NodeAnchor(void *arg0) {
    func_8003C2D8(*(s16 *)((u8 *)arg0 + 0x18));
    Geo_ProcessNodeChildren(arg0);
}
#endif

#ifdef VERSION_US
extern void Geo_ProcessNodeChildren(void *); void Geo_NodeGroup(void *arg0) { Geo_ProcessNodeChildren(arg0); }
#endif

#ifdef VERSION_US
extern S1_Vec3f *GeoRender_FindAnchorPosition(u8 *, s16, S1_Vec3f *);
extern u8 D_1000C80[];
extern u8 D_1000D08[];
extern Gfx* D_800D0510;
extern u8 D_80124F68;
// Project the model shadow onto y = 0 and fade it with height.
void Geo_NodeShadow(S1_unk_D_86002F34_alt12 *node) {
    Vec3f35784 position;
    Vec3f35784 up;
    S1_Vec3f scale;
    f32 height_scale;
    S1_MtxF basis;
    S1_MtxF *current;
    Gfx *commands;

    current = &((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top];
    commands = Gfx_AllocDisplayList(2 * sizeof(Gfx));
    if (GeoRender_FindAnchorPosition(D_8009491C, 100, NULL) == NULL) {
        func_8003C2D8(100);
    }
    Vec3f_SetComponentsDuplicate(&position, current->mf[3][0], current->mf[3][1] + node->unk_1E, current->mf[3][2]);
    position.y = 0.0f;
    if (((S1_unk_D_86002F58_004_000 *)D_8009491C)->unk_000.unk_02 & 0x40) {
        Vec3f_SetComponentsDuplicate(&up, 0.0f, 1.0f, 0.0f);
        func_80036D8C(&current->mf[0][0], &scale.x);
        height_scale = 1.0f - ((current->mf[3][1] - position.y) / 1000.0f);
        if (height_scale < 0.5f) {
            height_scale = 0.5f;
        }
        if (height_scale > 1.0f) {
            height_scale = 1.0f;
        }
        scale.x *= (node->unk_1A / 100.0f) * height_scale;
        scale.z *= (node->unk_1C / 100.0f) * height_scale;
        MtxF_SetOrthonormalBasis(basis.mf, &up, &position, ((S1_unk_D_86002F58_004_000 *)D_8009491C)->unk_01E.y);
        MtxF_ScaleRows(&((SceneTransformPool *)&D_80124F68)->matrices[((SceneTransformPool *)&D_80124F68)->top + 1], &basis, &scale);
        ((SceneTransformPool *)&D_80124F68)->top++;
        GeoRender_CommitMatrix(NULL);
        if (node->unk_18 == 0) {
            gSPBranchList(&commands[1], func_80003240(D_1000C80));
        } else {
            gSPBranchList(&commands[1], func_80003240(D_1000D08));
        }
        gDPSetEnvColor(&commands[0], 0, 0, 0, (s32)(120.0f * height_scale));
        if (((S1_unk_D_86002F58_004_000 *)D_8009491C)->unk_000.unk_02 & 2) {
            GeoRender_SubmitMaterial(7, ((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top]);
        } else {
            GeoRender_SubmitMaterial(6, ((SceneTransformPool *)&D_80124F68)->stack[((SceneTransformPool *)&D_80124F68)->top]);
        }
        gDPSetFogColor(D_800D0510++, 255, 255, 255, 0);
        gDPSetPrimColor(D_800D0510++, 0, ((S1_unk_D_86002F58_004_000 *)D_8009491C)->materialAlpha, 255, 255, 255, 255);
        func_8003DA20((u32)commands & 0x1FFFFFFF, 1);
        Geo_ProcessNodeChildren(node);
        ((SceneTransformPool *)&D_80124F68)->top--;
    }
}
#endif

#ifdef VERSION_US
extern s32 D_80094900;
extern void func_8006D2C0(void);
void Geo_RenderRootNode(u8 *node) {
    if (node[1] & 1) {
        gDPPipeSync(D_800D0510++);
        gDPSetTextureLOD(D_800D0510++, G_TL_TILE);
        gDPSetTextureLUT(D_800D0510++, G_TT_NONE);
        gDPSetTextureDetail(D_800D0510++, G_TD_CLAMP);
        gDPSetTexturePersp(D_800D0510++, G_TP_PERSP);
        gDPSetTextureFilter(D_800D0510++, G_TF_BILERP);
        gDPSetTextureConvert(D_800D0510++, G_TC_FILT);
        gDPSetCombineKey(D_800D0510++, G_CK_NONE);
        gDPSetAlphaCompare(D_800D0510++, G_AC_NONE);
        gDPSetColorDither(D_800D0510++, G_CD_MAGICSQ);
        gDPSetAlphaDither(D_800D0510++, G_AD_PATTERN);
        func_8006D2C0();
        D_8009490C = (s32)node;
        Geo_ProcessNodeChildren(node);
        D_8009490C = 0;
    }
    D_80094900 = 0;
}
#endif

#ifdef VERSION_US
extern void *D_80094918;
extern void * D_80094908;
extern void * D_8009491C;
void Geo_ProcessCallbacks(S1_GraphNode *root, s32 event) {
    S1_GraphNode *node = root;
    S1_GraphNode **slot;
    do {
        if (node->unk_10 != NULL) {
            node->unk_10(event, node);
        }
        if (node->unk_0C != NULL) {
            switch (node->unk_00) {
            default:
                slot = NULL;
                break;
            case 2:
                slot = (S1_GraphNode **)&D_80094908;
                break;
            case 4:
                slot = (S1_GraphNode **)&D_80094910;
                break;
            case 6:
                slot = (S1_GraphNode **)&D_80094918;
                break;
            case 22:
                slot = (S1_GraphNode **)&D_8009491C;
                break;
            }
            if (slot != NULL) {
                *slot = node;
            }
            Geo_ProcessCallbacks((S1_GraphNode *)node->unk_0C, event);
            if (slot != NULL) {
                *slot = NULL;
            }
        }
        node = node->unk_08;
    } while (node != root);
}
#endif

#ifdef VERSION_US
extern s32 D_80094900;
void func_8003C964(s32 value) { D_80094900 = value; }
#endif

#ifdef VERSION_US
extern u16 D_80094904;
void GeoRender_AdvanceFrameCounter(void) { D_80094904++; }
#endif

#ifdef VERSION_US
extern ModelFrame *D_80094910; extern u16 D_80094904;
s32 GeoRender_IsModelFrameCurrent(void) { s32 var_v1 = 1; if (D_80094910 != NULL) { var_v1 = D_80094910->unk_1A == D_80094904; } return var_v1; }
#endif

#ifdef VERSION_US
S1_Vec3f *GeoRender_FindAnchorPosition(u8 *object, s16 id, S1_Vec3f *out) {
    s32 i;
    for (i = 0; i < object[0xA7]; i++) {
        if (id == *(u16 *)(object + i * 0x10 + 0xA8)) {
            if (out != NULL) {
                *out = *(S1_Vec3f *)(object + i * 0x10 + 0xAC);
            }
            return (S1_Vec3f *)(object + i * 0x10 + 0xAC);
        }
    }
    return NULL;
}
/* Preserve the two zero words at the end of the original assembly owner. */
#pragma C_FUNCTION_PADDING(8)
#endif

#ifdef VERSION_US
typedef struct S1_arg1_func_81407874_014_000_010 S1_arg1_func_81407874_014_000_010;
struct S1_arg1_func_81407874_014_000_010 {
      u8 unk_00;
      u8 unk_01;
      u8 unk_02;
      u8 unk_03;
      u8 unk_04;
      u8 unk_05;
      u8 unk_06;
      u8 unk_07;
      u8 unk_08;
      u8 unk_09;
      u8 unk_0A;
      u8 unk_0B;
      u8 unk_0C;
      u8 unk_0D;
      u8 unk_0E;
      u8 unk_0F;
};
void func_8003CA30(Gfx* arg0, S1_arg1_func_81407874_014_000_010* arg1) {
    gDPSetCombine(arg0++,
                  GCCc0w0(arg1->unk_00, arg1->unk_02, arg1->unk_04, arg1->unk_06) | GCCc1w0(arg1->unk_08, arg1->unk_0A),

                  GCCc0w1(arg1->unk_01, arg1->unk_03, arg1->unk_05, arg1->unk_07) |
                      GCCc1w1(arg1->unk_09, arg1->unk_0C, arg1->unk_0E, arg1->unk_0B, arg1->unk_0D, arg1->unk_0F));
}
#endif

#ifdef VERSION_US
extern S1_arg1_func_81407874_014_000_010 D_80094AAC[];
void func_8003CB3C(Gfx *arg0, u8 arg1, u8 arg2) {
    S1_arg1_func_81407874_014_000_010 local;
    local = D_80094AAC[arg1];
    if (arg2 == 0xFF) {
        local.unk_0C = 7; local.unk_0D = 7; local.unk_0E = 7; local.unk_0F = 0;
    }
    func_8003CA30(arg0, &local);
}
#endif

#ifdef VERSION_US
extern s32 D_801261A8;
extern Gfx* D_800D0510;
void func_8003CBD4(void) {
    Gfx *command;
    if (D_801261A8 == 0) {
        D_801261A8 = 1;
        command = D_800D0510++;
        command->words.w1 = 0;
        command->words.w0 = 0xE7000000;
    }
}
#endif

#ifdef VERSION_US
typedef struct SceneMaterialState {
    s32 unknown00;
    void *unknown04;
    void *unknown08;
    void *unknown0C;
    S1_Color_RGBA8_u32 primitiveColor;
    S1_Color_RGBA8_u32 fogColor;
    void *unknown18;
    void *unknown1C;
    void *unknown20;
    u8 unknown24;
    u8 combineMode;
    u8 primitiveLevel;
    u8 unknown27;
} SceneMaterialState;
extern void *D_801263A8;
extern s32 D_801261A0;
extern s32 D_801261A4;
extern s32 D_801261A8;
extern s32 D_800949A4[][11];
extern Gfx* D_800D0510;
void GeoRender_SetRenderMode(void) {
    s32 mode = D_800949A4[D_801261A0][((SceneMaterialState *)D_801263A8)->unknown24];
    D_801261A8 = 1;
    gDPPipeSync(D_800D0510++);
    ((SceneMaterialState *)D_801263A8)->fogColor.rgba = 0;
    gDPSetColor(D_800D0510++, G_SETFOGCOLOR, D_80094910->unknown20);
    if ((D_801261A4 & 1) && D_801261A0 == 1 && (((SceneMaterialState *)D_801263A8)->unknown24 == 6 || ((SceneMaterialState *)D_801263A8)->unknown24 == 8)) {
        mode = 0x107A58;
    }
    if (D_80094910->unknown1D != 0) {
        gDPSetRenderMode(D_800D0510++, mode, 0xC8000000);
    } else {
        gDPSetRenderMode(D_800D0510++, mode, 0x0C080000);
    }
}
#endif

#ifdef VERSION_US
s32 func_8003CD58(s32 arg0) { s32 var_v1; if ((arg0 != 0) && (arg0 != 5) && (arg0 != 0xA)) { var_v1 = 0; } else { var_v1 = 1; } return var_v1; }
#endif

#ifdef VERSION_US
extern void func_8003CB3C(Gfx *arg0, u8 arg1, u8 arg2);
extern void * D_80094908;
extern Gfx* D_800D0510;
extern void * D_801263A8;
void GeoRender_ApplyMaterialState(void) {
    S1_Color_RGBA8_u32 color;
    color.rgba = ((SceneMaterialState *)D_801263A8)->primitiveColor.rgba;
    ((SceneMaterialState *)D_801263A8)->unknown18 = NULL;
    ((SceneMaterialState *)D_801263A8)->unknown1C = NULL;
    ((SceneMaterialState *)D_801263A8)->unknown0C = NULL;
    ((SceneMaterialState *)D_801263A8)->unknown27 = 0;
    D_801261A8 = 1;
    gDPPipeSync(D_800D0510++);
    gDPSetPrimColor(D_800D0510++, 0, ((SceneMaterialState *)D_801263A8)->primitiveLevel, color.r, color.g, color.b, color.a);
    gDPSetTextureLUT(D_800D0510++, G_TT_NONE);
    if (func_8003CD58(((SceneMaterialState *)D_801263A8)->combineMode) != 0) {
        gSPTexture(D_800D0510++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    } else {
        gSPTexture(D_800D0510++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    }
    func_8003CB3C(D_800D0510++, ((SceneMaterialState *)D_801263A8)->combineMode, ((SceneMaterialState *)D_801263A8)->primitiveLevel);
    gSPSetGeometryMode(D_800D0510++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gSPClearGeometryMode(D_800D0510++, G_FOG | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
    gSPLookAt(D_800D0510++, (u32)((S1_unk_D_86002F34_00C *)D_80094908)->unk_60.lookat & 0x1FFFFFFF);
    if (D_80094910->unknown1D != 0) {
        gSPSetGeometryMode(D_800D0510++, G_FOG);
    }
}
#endif

#ifdef VERSION_US
typedef struct {
    u8 mode;
    u8 level;
    u8 unknown02;
    u8 textureVariant;
    S1_Color_RGBA8_u32 primitiveColor;
    S1_Color_RGBA8_u32 fogColor;
    void *texture;
    void *material;
    Gfx *displayList;
} SceneMaterialParameters;
extern void func_8003CBD4(void);
extern Gfx* D_800D0510;
extern void * D_801263A8;
void GeoRender_SetFogColor(SceneMaterialParameters *node) {
    if (node->fogColor.rgba != ((SceneMaterialState *)D_801263A8)->fogColor.rgba) {
        func_8003CBD4();
        gDPSetColor(D_800D0510++, G_SETFOGCOLOR, node->fogColor.rgba);
        gDPSetRenderMode(D_800D0510++, D_800949A4[D_801261A0][((SceneMaterialState *)D_801263A8)->unknown24], 0xC4000000);
        ((SceneMaterialState *)D_801263A8)->fogColor.rgba = node->fogColor.rgba;
    }
}
#endif

#ifdef VERSION_US
extern void GeoRender_SetRenderMode();
extern void *D_801263A8;

void GeoRender_RestoreRenderMode(s32 arg0) {
    if ((*(s32 *)((u8 *)(D_801263A8) + (0x14))) & 0xFF) {
        GeoRender_SetRenderMode();
    }
}
#endif

#ifdef VERSION_US
typedef struct {
    u8 mode;
    u8 level;
    u8 unknown02;
    u8 unknown03;
    S1_Color_RGBA8_u32 color;
} ScenePrimitiveColor;
void GeoRender_SetPrimitiveColor(ScenePrimitiveColor *node) {
    if (node->color.rgba != ((SceneMaterialState *)D_801263A8)->primitiveColor.rgba ||
        node->level != ((SceneMaterialState *)D_801263A8)->primitiveLevel) {
        func_8003CBD4();
        gDPSetPrimColor(D_800D0510++, 0, node->level, node->color.r, node->color.g,
                       node->color.b, node->color.a);
        ((SceneMaterialState *)D_801263A8)->primitiveColor.rgba = node->color.rgba;
        ((SceneMaterialState *)D_801263A8)->primitiveLevel = node->level;
    }
}
#endif

#ifdef VERSION_US
extern void func_8003CBD4(void);
extern void func_8003D188_batch_decl_marker(void);
extern void func_8003CB3C(Gfx *arg0, u8 arg1, u8 arg2);
extern Gfx* D_800D0510;
extern void * D_801263A8;
void func_8003D188(u8 *arg0) {
    if (((u8 *)D_801263A8)[0x25] != arg0[0]) {
        func_8003CBD4();
        func_8003CB3C(D_800D0510++, arg0[0], arg0[1]);
        ((u8 *)D_801263A8)[0x25] = arg0[0];
    }
}
#endif

#ifdef VERSION_US
extern Gfx* D_800D0510;
extern void * D_801263A8;
void func_8003D1F8(s32 arg0) { if (func_8003CD58(((u8 *)D_801263A8)[0x25]) == 0) { Gfx *command = D_800D0510++; command->words.w0 = 0xD7000000; command->words.w1 = 0xFFFFFFFF; } *(s32 *)((u8 *)D_801263A8 + 0x18) = 0; *(s32 *)((u8 *)D_801263A8 + 0x1C) = 0; *(s32 *)((u8 *)D_801263A8 + 0x20) = 0; }
#endif

#ifdef VERSION_US
typedef struct {
    u8 format;
    u8 size;
    s16 width;
    s16 height;
    s16 numTexels;
    void *image;
} SceneBoundTexture;
typedef struct {
    u8 unknown00[8];
    Gfx *displayList;
} SceneBoundPalette;
extern s16 D_80094B9C[];
extern Gfx* D_800D0510;
extern void * D_801263A8;
void GeoRender_BindTexture(SceneMaterialParameters *node) {
    SceneBoundTexture *texture;
    s32 imageSize;
    if (func_8003CD58(((SceneMaterialState *)D_801263A8)->combineMode)) {
        gSPTexture(D_800D0510++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    }
    if (node->texture != NULL && node->displayList != NULL) {
        if (node->texture != ((SceneMaterialState *)D_801263A8)->unknown18 || node->displayList != ((SceneMaterialState *)D_801263A8)->unknown20) {
            texture = node->texture;
            if (node->material != NULL) {
                gSPDisplayList(D_800D0510++, ((SceneBoundPalette *)node->material)->displayList);
            } else {
                gDPSetTextureLUT(D_800D0510++, G_TT_NONE);
            }
            if (texture->size == 0) {
                if ((texture->width % D_80094B9C[0]) == 0) {
                    gDPSetTextureImage(D_800D0510++, texture->format, G_IM_SIZ_16b, 1, texture->image);
                } else {
                    gDPSetTextureImage(D_800D0510++, texture->format, G_IM_SIZ_8b, texture->width >> 1, texture->image);
                }
            } else if ((texture->width % D_80094B9C[texture->size]) == 0) {
                if (texture->size == 3) {
                    imageSize = 3;
                } else {
                    imageSize = 2;
                }
                gDPSetTextureImage(D_800D0510++, texture->format, imageSize, 1, texture->image);
            } else {
                gDPSetTextureImage(D_800D0510++, texture->format, texture->size, texture->width, texture->image);
            }
            gSPDisplayList(D_800D0510++, node->displayList);
        }
        ((SceneMaterialState *)D_801263A8)->unknown18 = node->texture;
        ((SceneMaterialState *)D_801263A8)->unknown1C = node->material;
        ((SceneMaterialState *)D_801263A8)->unknown20 = node->displayList;
    }
}
#endif

#ifdef VERSION_US
extern u8 D_1000000[];
extern u8 D_10019D0[];
void GeoRender_EnableTextureGeneration(SceneMaterialParameters *node) {
    void *texture;
    if (((SceneMaterialState *)D_801263A8)->unknown27 == 0) {
        texture = D_1000000;
        switch (node->textureVariant) {
        case 1:
            break;
        case 2:
            texture = D_10019D0;
            break;
        }
        gDPLoadTextureBlock(D_800D0510++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 1, 1);
        gSPTexture(D_800D0510++, 0x1194, 0x1194, 0, G_TX_RENDERTILE, G_ON);
        gSPSetGeometryMode(D_800D0510++, G_TEXTURE_GEN);
        gSPClearGeometryMode(D_800D0510++, G_TEXTURE_GEN_LINEAR);
        gDPSetCombineMode(D_800D0510++, G_CC_MODULATEIDECALA, G_CC_PASS2);
        ((SceneMaterialState *)D_801263A8)->unknown27 = 1;
    }
}
#endif

#ifdef VERSION_US
extern s32 D_801263AC;
extern SceneMaterialState D_801261C8[];
extern Gfx* D_800D0510;
extern void * D_801263A8;
void GeoRender_SelectMaterialSlot(s16 slot) {
    if (slot == D_801263AC) {
        return;
    }
    ((SceneMaterialState *)D_801263A8)->unknown08 = D_800D0510;
    gSPBranchList(D_800D0510++, NULL);
    D_801263AC = slot;
    D_801263A8 = &D_801261C8[D_801263AC];
    if (((SceneMaterialState *)D_801263A8)->unknown04 == NULL) {
        ((SceneMaterialState *)D_801263A8)->unknown04 = D_800D0510;
    } else if (((SceneMaterialState *)D_801263A8)->unknown08 != NULL) {
        gSPBranchList((Gfx *)((SceneMaterialState *)D_801263A8)->unknown08, D_800D0510);
    }
}
#endif

#ifdef VERSION_US
extern SceneMaterialParameters D_801261B0;
void func_8003D7B8(s16 arg0) {
    if (((arg0 > 0) && (arg0 < 4)) || (arg0 == 0x84) || (arg0 == 7)) {
        D_801261B0.textureVariant = D_801261B0.unknown02;
        return;
    }
    D_801261B0.textureVariant = 0;
}
#endif

#ifdef VERSION_US
extern u8 D_801261B1;
s16 func_8003D808(s16 arg0) {
    s16 value = arg0 & 0xF;
    s16 result = value;
    if (D_801261B1 < 0xFF) {
        switch (value) {
        case 1: result = 5; break;
        case 2: result = 7; break;
        case 3: result = 8; break;
        case 4: result = 6; break;
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
extern s32 D_800949A0;
extern s32 D_801261A4;
extern void GeoRender_SelectMaterialSlot(s16);
extern void GeoRender_SetFogColor(SceneMaterialParameters *);
extern void GeoRender_BindTexture(SceneMaterialParameters *);
extern void GeoRender_ApplyMaterialState(void);
void GeoRender_SubmitMaterial(s16 format, Mtx *matrix) {
    if (D_800949A0 != 0 && !(D_801261A4 & 2) && D_801261B0.level > 0) {
        func_8003D7B8(format);
        GeoRender_SelectMaterialSlot(func_8003D808(format));
        D_801261A8 = 0;
        if (((SceneMaterialState *)D_801263A8)->unknown00 == 0) {
            GeoRender_SetRenderMode();
            GeoRender_ApplyMaterialState();
            ((SceneMaterialState *)D_801263A8)->unknown00 = 1;
        }
        if (D_801261B0.fogColor.rgba & 0xFF) {
            GeoRender_SetFogColor((&D_801261B0));
        } else {
            GeoRender_RestoreRenderMode((s32)(&D_801261B0));
        }
        if (D_801261B0.textureVariant != 0) {
            GeoRender_EnableTextureGeneration((&D_801261B0));
        } else {
            if (((SceneMaterialState *)D_801263A8)->unknown27 == 1) {
                GeoRender_ApplyMaterialState();
            }
            if (func_8003CD58(D_801261B0.mode)) {
                func_8003D1F8((s32)(&D_801261B0));
            } else {
                GeoRender_BindTexture((&D_801261B0));
            }
            GeoRender_SetPrimitiveColor((ScenePrimitiveColor *)(&D_801261B0));
            func_8003D188((u8 *)(&D_801261B0));
        }
        if (matrix != ((SceneMaterialState *)D_801263A8)->unknown0C) {
            ((SceneMaterialState *)D_801263A8)->unknown0C = matrix;
            gSPMatrix(D_800D0510++, (u32)matrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        }
    }
}
#endif

#ifdef VERSION_US
extern u32 Memmap_GetFragmentVaddr(Gfx **);
extern void GeoRender_ApplyMaterialState(void);
extern s32 D_800949A0;
extern s32 D_801261A4;
extern Gfx* D_800D0510;
extern u8 D_801261B1;
void func_8003DA20(s32 arg0, s32 arg1) {
    if (D_800949A0 != 0 && !(D_801261A4 & 2) && D_801261B1 > 0) {
        if (arg0 != 0) {
            if ((u32)arg0 >= 0x81000000U && (u32)arg0 < 0x90000000U) {
                Gfx *command = D_800D0510++;
                command->words.w0 = 0xDE000000;
                command->words.w1 = Memmap_GetFragmentVaddr((Gfx **)arg0);
            } else {
                Gfx *command = D_800D0510++;
                command->words.w1 = arg0;
                command->words.w0 = 0xDE000000;
            }
        }
        if (arg1 != 0) GeoRender_ApplyMaterialState();
    }
}
#endif

#ifdef VERSION_US
void GeoRender_SetMaterialParams(S1_Color_RGBA8_u32 color, u8 level, u32 flags) {
    D_801261B0.fogColor.rgba = color.rgba;
    D_801261B0.level = level;
    D_801261B0.unknown02 = flags;
}
#endif

#ifdef VERSION_US
void GeoRender_SetMaterialTexture(s32 arg0, CandidateColor arg1, void *arg2, void *arg3, s32 arg4) {
    D_801261B0.mode = arg0;
    D_801261B0.primitiveColor.rgba = arg1.rgba;
    D_801261B0.texture = arg2;
    D_801261B0.material = arg3;
    D_801261B0.displayList = arg4;
}
#endif

#ifdef VERSION_US
extern Gfx* D_800D0510;
extern void * D_801263A8;
void GeoRender_InitMaterialState(s32 mode, s32 flags) {
    s32 index;
    SceneMaterialState *entry = D_801261C8;
    gDPPipeSync(D_800D0510++);
    gDPSetCycleType(D_800D0510++, G_CYC_2CYCLE);
    if (mode & 1) {
        gSPSetGeometryMode(D_800D0510++, G_ZBUFFER);
    } else {
        gSPClearGeometryMode(D_800D0510++, G_ZBUFFER);
    }
    for (index = 0; index < 12; index++, entry++) {
        entry->unknown04 = NULL;
        entry->unknown08 = NULL;
        entry->unknown00 = 0;
        entry->unknown0C = NULL;
        entry->primitiveColor.rgba = 0xFFFFFFFF;
        entry->fogColor.rgba = 0xFFFFFF00;
        entry->unknown18 = NULL;
        entry->unknown1C = NULL;
        entry->unknown20 = NULL;
        entry->unknown24 = index;
        entry->combineMode = 0;
        entry->unknown27 = 0;
        entry->primitiveLevel = 0xFF;
    }
    D_801261B0.mode = 0;
    D_801261B0.level = 0xFF;
    D_801261B0.unknown02 = 0;
    D_801261B0.textureVariant = 0;
    D_801261B0.primitiveColor.rgba = 0xFFFFFFFF;
    D_801261B0.fogColor.rgba = 0xFFFFFF00;
    D_801261B0.texture = NULL;
    D_801261B0.material = NULL;
    D_801261B0.displayList = NULL;
    D_801261A0 = mode;
    D_801261A4 = flags;
    D_801261C8[0].unknown04 = D_800D0510;
    D_801263AC = 0;
    D_801263A8 = D_801261C8;
    D_800949A0 = 1;
}
#endif

#ifdef VERSION_US
void GeoRender_FlushMaterialSlots(void) {
    s32 slot = 0;
    Gfx *branch;
    s32 next;
    GeoRender_SelectMaterialSlot(11);
    if (D_801261C8[0].unknown08 != NULL) {
        while (slot < 11) {
            next = slot + 1;
            branch = D_801261C8[slot].unknown08;
            slot++;
            while (D_801261C8[next].unknown04 == NULL) {
                next = slot + 1;
                slot++;
            }
            gSPBranchList(branch, D_801261C8[slot].unknown04);
        }
    }
    GeoRender_ApplyMaterialState();
    if (D_801261A0 & 1) {
        gSPClearGeometryMode(D_800D0510++, G_ZBUFFER);
    }
    D_800949A0 = 0;
}
#pragma C_FUNCTION_PADDING(4)
#endif

#ifdef VERSION_US
f32 ModelAnim_EvaluateTranslationChannel(S1_unk_D_800ABCC0* arg0, s32 arg1) {
    f32 ret;
    s32 var_a2;
    S1_unk_D_800ABCC0_008* temp_v0 = &arg0->channels[arg1];

    if (temp_v0->translationKeyCount == 1) {
        ret = temp_v0->translationBaseIndex / 1000.0f;
    } else {
        if (arg0->currentFrame < temp_v0->translationKeyCount) {
            var_a2 = temp_v0->translationBaseIndex + arg0->currentFrame;
        } else {
            var_a2 = (temp_v0->translationBaseIndex + temp_v0->translationKeyCount) - 1;
        }

        ret = arg0->translationValues[var_a2] / 1000.0f;
    }

    return ret;
}
#endif

#ifdef VERSION_US
s16 ModelAnim_EvaluateRotationChannel(S1_unk_D_800ABCC0* arg0, s32 arg1) {
    s32 var_a1;
    s16 var_v1;
    S1_unk_D_800ABCC0_008* temp_v0 = &arg0->channels[arg1];

    if (temp_v0->rotationKeyCount == 1) {
        var_v1 = temp_v0->rotationBaseIndex * 0x10;
    } else {
        if (arg0->currentFrame < temp_v0->rotationKeyCount) {
            var_a1 = temp_v0->rotationBaseIndex + arg0->currentFrame;
        } else {
            var_a1 = (temp_v0->rotationBaseIndex + temp_v0->rotationKeyCount) - 1;
        }
        var_v1 = func_80037360(arg0->rotationValues, var_a1, 0xC) * 0x10;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
f32 ModelAnim_EvaluateScaleChannel(S1_unk_D_800ABCC0* arg0, s32 arg1) {
    f32 var_fv1;
    s16 var_a2;
    s32 var_a1;
    S1_unk_D_800ABCC0_008* temp_v0 = &arg0->channels[arg1];

    if (temp_v0->scaleKeyCount == 1) {
        if (arg0->flags & 4) {
            var_fv1 = (s16)temp_v0->scaleBaseIndex;
        } else {
            var_a2 = temp_v0->scaleBaseIndex * 0x10;
            var_fv1 = var_a2 >> 4;
        }
    } else {
        if (arg0->currentFrame < temp_v0->scaleKeyCount) {
            var_a1 = temp_v0->scaleBaseIndex + arg0->currentFrame;
        } else {
            var_a1 = (temp_v0->scaleBaseIndex + temp_v0->scaleKeyCount) - 1;
        }

        if (arg0->flags & 4) {
            var_fv1 = func_80037360(arg0->scaleValues, var_a1, 0x10);
        } else {
            var_fv1 = func_80037360(arg0->scaleValues, var_a1, 0xC);
        }
    }

    return var_fv1;
}
#endif

#ifdef VERSION_US
f32 ModelAnim_InterpolateKeyframe(S1_Vec3s* arg0, s16 arg1, s16 arg2) {
    f32 y;
    s32 i;
    f32 x;
    f32 var_fv1;

    if (arg0->x >= arg2) {
        var_fv1 = arg0->y;
    } else {
        if (arg2 >= arg0[arg1 - 1].x) {
            var_fv1 = arg0[arg1 - 1].y;
        } else {
            for (i = 0; i < arg1 - 2; i++) {
                if (arg2 < arg0[i + 1].x) {
                    break;
                }
            }

            x = (arg2 - arg0[i].x) / 30.0f;
            y = 30.0f / (arg0[i + 1].x - arg0[i].x);

            var_fv1 = (arg0[i].y * (((2.0f * x * x * x * y * y * y) - 3.0f * x * x * y * y) + 1.0f))
                    + (arg0[i + 1].y * ((-2.0f * x * x * x * y * y * y) + 3.0f * x * x * y * y))
                    + (arg0[i].z * ((x * x * x * y * y - (2.0f * x * x * y)) + x))
                    + (arg0[i + 1].z * (x * x * x * y * y - (x * x * y)));
        }
    }
    return var_fv1;
}
#endif

#ifdef VERSION_US
f32 ModelAnim_InterpolateKeyframeTangent(S1_unk_func_80016B30_arg0* arg0, s16 arg1, s16 arg2) {
    f32 y;
    s32 i;
    f32 x;
    f32 var_fv1;

    if (arg0->vec.x >= arg2) {
        var_fv1 = arg0->vec.y;
    } else {
        if (arg2 >= arg0[arg1 - 1].vec.x) {
            var_fv1 = arg0[arg1 - 1].vec.y;
        } else {
            for (i = 0; i < arg1 - 2; i++) {
                if (arg2 < arg0[i + 1].vec.x) {
                    break;
                }
            }

            x = (arg2 - arg0[i].vec.x) / 30.0f;
            y = 30.0f / (arg0[i + 1].vec.x - arg0[i].vec.x);

            var_fv1 = (arg0[i].vec.y * (((2.0f * x * x * x * y * y * y) - 3.0f * x * x * y * y) + 1.0f))
                    + (arg0[i + 1].vec.y * ((-2.0f * x * x * x * y * y * y) + 3.0f * x * x * y * y))
                    + (arg0[i].unk_06 * ((x * x * x * y * y - (2.0f * x * x * y)) + x))
                    + (arg0[i + 1].vec.z * (x * x * x * y * y - (x * x * y)));
        }
    }
    return var_fv1;
}
#endif

#ifdef VERSION_US
f32 ModelAnim_EvaluateTranslationCurve(S1_unk_D_800ABCC0* arg0, s32 arg1) {
    f32 var_fv1;
    S1_unk_D_800ABCC0_008* temp_v0 = &arg0->channels[arg1];
    s16* tmp;

    if (temp_v0->translationKeyCount < 2) {
        var_fv1 = (s16)temp_v0->translationBaseIndex / 100.0f;
    } else {
        tmp = &arg0->translationValues[temp_v0->translationBaseIndex];
        if (temp_v0->unk_03 & 4) {
            var_fv1 = ModelAnim_InterpolateKeyframeTangent(tmp, temp_v0->translationKeyCount, arg0->currentFrame) / 100.0f;
        } else {
            var_fv1 = ModelAnim_InterpolateKeyframe(tmp, temp_v0->translationKeyCount, arg0->currentFrame) / 100.0f;
        }
    }
    return var_fv1;
}
#endif

#ifdef VERSION_US
s16 ModelAnim_EvaluateRotationCurve(S1_unk_D_800ABCC0* arg0, s32 arg1) {
    f32 var_fv1;
    s16* temp_a0;
    S1_unk_D_800ABCC0_008* temp_v0 = &arg0->channels[arg1];

    if (temp_v0->rotationKeyCount < 2) {
        var_fv1 = (s16)temp_v0->rotationBaseIndex / 10.0f;
    } else {
        temp_a0 = &arg0->rotationValues[temp_v0->rotationBaseIndex];
        if (temp_v0->unk_03 & 2) {
            var_fv1 = ModelAnim_InterpolateKeyframeTangent(temp_a0, temp_v0->rotationKeyCount, arg0->currentFrame) / 10.0f;
        } else {
            var_fv1 = ModelAnim_InterpolateKeyframe(temp_a0, temp_v0->rotationKeyCount, arg0->currentFrame) / 10.0f;
        }
    }

    while (var_fv1 < 0.0f) {
        var_fv1 += 360.0f;
    }

    while (var_fv1 >= 360.0f) {
        var_fv1 -= 360.0f;
    }

    return (var_fv1 / 360.0f) * 65536.0f;
}
#endif

#ifdef VERSION_US
f32 ModelAnim_EvaluateScaleCurve(S1_unk_D_800ABCC0* arg0, s32 arg1) {
    s16* temp_a0;
    f32 var_fv0;
    f32 var_fv1;
    S1_unk_D_800ABCC0_008* temp_v0 = &arg0->channels[arg1];

    if (temp_v0->scaleKeyCount < 2) {
        var_fv1 = (s16)temp_v0->scaleBaseIndex;
    } else {
        temp_a0 = &arg0->scaleValues[temp_v0->scaleBaseIndex];
        if (temp_v0->unk_03 & 1) {
            var_fv0 = ModelAnim_InterpolateKeyframeTangent(temp_a0, temp_v0->scaleKeyCount, arg0->currentFrame);
        } else {
            var_fv0 = ModelAnim_InterpolateKeyframe(temp_a0, temp_v0->scaleKeyCount, arg0->currentFrame);
        }
        var_fv1 = var_fv0;
    }
    return var_fv1;
}
#endif

#ifdef VERSION_US
s32 ModelAnim_AdvanceCurveFrame(S1_unk_D_86002F58_004_000_040_raw* arg0, u16 arg1) {
    S1_unk_D_86002F58_004_000_040_raw_08 spC;
    S1_unk_D_86002F58_004_000_040_raw_08* ptr;
    S1_unk_D_86002F58_004_000_040_004* temp_v0;

    ptr = &spC;
    temp_v0 = arg0->unk_04;
    spC.raw = arg0->unk_08.raw;
    if (arg0->unk_12 != arg1) {
        spC.raw += arg0->unk_0C;
        if (arg0->unk_0C >= 0) {
            if (ptr->unk_00 >= temp_v0->unk_0A) {
                if (temp_v0->unk_00 & 2) {
                    ptr->unk_00 = temp_v0->unk_0A - 1;
                } else {
                    ptr->unk_00 = temp_v0->unk_06;
                }
            }
        } else {
            if (ptr->unk_00 < temp_v0->unk_06) {
                if (temp_v0->unk_00 & 2) {
                    ptr->unk_00 = temp_v0->unk_06;
                } else {
                    ptr->unk_00 = temp_v0->unk_0A - 1;
                }
            }
        }
    }

    return spC.raw;
}
#endif

#ifdef VERSION_US
extern s32 D_801263E0; void ModelAnim_ResetCurveContext(void) { D_801263E0 = -1; }
#endif

#ifdef VERSION_US
extern void * func_80003240();
void func_8003E7B0(S1_unk_D_86002F58_004_000_040_raw *arg0, u16 arg1, s32 arg2) {
    extern S1_unk_D_800ABCC0 D_801263B0[2];
    S1_unk_D_800ABCC0 *ctx;
    S1_unk_D_86002F58_004_000_040_004 *data;
    data = arg0->unk_04;
    ++D_801263E0;
    if (D_801263E0 < 2) {
        ctx = &D_801263B0[D_801263E0];
        if (arg0->unk_04 != 0) {
            if (arg2 != 0) {
                arg0->unk_08.raw = ModelAnim_AdvanceCurveFrame(arg0, arg1);
            }
            arg0->unk_12 = arg1;
            ctx->isActive = 1;
            ctx->flags = arg0->unk_04->unk_00;
            ctx->currentFrame = arg0->unk_08.raw >> 16;
            ctx->curveData = data;
            ctx->channels = func_80003240(data->unk_0C);
            ctx->translationValues = func_80003240(data->unk_10);
            ctx->rotationValues = func_80003240(data->unk_14);
            ctx->scaleValues = func_80003240(data->unk_18);
            if (ctx->currentFrame < 0) {
                ctx->currentFrame = 0;
            }
        } else {
            ctx->isActive = 0;
        }
    }
}
#endif

#ifdef VERSION_US
extern s32 D_801263E0; void ModelAnim_EndCurveContext(void) { if (D_801263E0 >= 0) { D_801263E0--; } }
#endif

#ifdef VERSION_US
extern S1_unk_D_800ABCC0 D_801263B0[2];
void func_8003E8C8(S1_Vec3f *arg0, S1_Vec3s *arg1, S1_Vec3f *arg2, s32 arg3) {
    if (D_801263E0 >= 0 && D_801263E0 < 2) {
        S1_unk_D_800ABCC0 *ctx = &D_801263B0[D_801263E0];
        if (ctx->isActive == 1 && arg3 >= 0 && arg3 + 2 < ctx->curveData->unk_08) {
            if (ctx->flags & 8) {
                arg0->x = ModelAnim_EvaluateScaleCurve(ctx, arg3);
                arg0->y = ModelAnim_EvaluateScaleCurve(ctx, arg3 + 1);
                arg0->z = ModelAnim_EvaluateScaleCurve(ctx, arg3 + 2);
                arg1->x = ModelAnim_EvaluateRotationCurve(ctx, arg3);
                arg1->y = ModelAnim_EvaluateRotationCurve(ctx, arg3 + 1);
                arg1->z = ModelAnim_EvaluateRotationCurve(ctx, arg3 + 2);
                arg2->x = ModelAnim_EvaluateTranslationCurve(ctx, arg3);
                arg2->y = ModelAnim_EvaluateTranslationCurve(ctx, arg3 + 1);
                arg2->z = ModelAnim_EvaluateTranslationCurve(ctx, arg3 + 2);
            } else {
                arg0->x = ModelAnim_EvaluateScaleChannel(ctx, arg3);
                arg0->y = ModelAnim_EvaluateScaleChannel(ctx, arg3 + 1);
                arg0->z = ModelAnim_EvaluateScaleChannel(ctx, arg3 + 2);
                arg1->x = ModelAnim_EvaluateRotationChannel(ctx, arg3);
                arg1->y = ModelAnim_EvaluateRotationChannel(ctx, arg3 + 1);
                arg1->z = ModelAnim_EvaluateRotationChannel(ctx, arg3 + 2);
                arg2->x = ModelAnim_EvaluateTranslationChannel(ctx, arg3);
                arg2->y = ModelAnim_EvaluateTranslationChannel(ctx, arg3 + 1);
                arg2->z = ModelAnim_EvaluateTranslationChannel(ctx, arg3 + 2);
            }
        }
    }
}
#endif

#ifdef VERSION_US
void ModelAnim_ClearTransformChannel(u8 *arg0) { *(s16 *)(arg0 + 0x40) = -1; *(s32 *)(arg0 + 0x44) = 0; }
#endif

#ifdef VERSION_US
s32 ModelAnim_BindTransformCurve(S1_unk_D_86002F58_004_000* arg0, s16 arg1, void* arg2, s32 arg3) {
    S1_unk_D_86002F58_004_000_040_004* temp_v0 = func_80003240(arg2);
    S1_unk_D_86002F58_004_000_040* ptr = &arg0->unk_040;

    if ((temp_v0 != ptr->unk_04) || (arg1 != ptr->unk_00)) {
        ptr->unk_00 = arg1;
        ptr->unk_04 = temp_v0;
        ptr->unk_08 = (temp_v0->unk_04 << 0x10) - arg3;
    }

    ptr->unk_0C = arg3;
    return ptr->unk_08 >> 0x10;
}
#endif

#ifdef VERSION_US
s32 ModelAnim_SetSpeed(u8 *arg0, s32 arg1) { *(s32 *)(arg0 + 0x4C) = arg1; return *(s32 *)(arg0 + 0x48) >> 16; }
#endif

#ifdef VERSION_US
void ModelAnim_SetFrame(u8 *arg0, s16 value) { *(s32 *)(arg0 + 0x48) = ((s32)value << 16) - *(s32 *)(arg0 + 0x4C); }
#endif

#ifdef VERSION_US
typedef struct { char pad[0x40]; struct { s16 pad0; void *data; s32 frame; s32 speed; } curve; } ModelAnim;
s32 ModelAnim_HasCrossedFrame(ModelAnim *arg0, s16 arg1) { struct { s16 pad0; void *data; s32 frame; s32 speed; } *ptr = &arg0->curve; s32 temp_v0 = ptr->frame + ptr->speed; s32 arg = arg1 << 16; s32 var_a2; s32 v = ptr->speed; if (v >= 0) { var_a2 = ptr->frame < arg; if (var_a2 != 0) var_a2 = temp_v0 >= arg; } else { var_a2 = arg < ptr->frame; if (var_a2 != 0) var_a2 = arg >= temp_v0; } return var_a2; }
#endif

#ifdef VERSION_US
typedef struct { s16 flags; char pad2[4]; s16 fallback; char pad8[2]; u16 frameCount; } EventData;
s32 ModelAnim_IsAnimationDone(ModelAnim *arg0) { return ModelAnim_HasCrossedFrame(arg0, ((EventData *)arg0->curve.data)->frameCount - 1); }
#endif

#ifdef VERSION_US
typedef struct { u8 pad[0x44]; u8 *value44; s32 value48; } Func3EC34;
s32 ModelAnim_IsFinished(Func3EC34 *arg0) { return arg0->value48 >= ((*(u16 *)(arg0->value44 + 0xA) - 1) << 16); }
#endif

#ifdef VERSION_US
typedef struct { u8 pad[0x48]; s32 value48; s32 value4C; } Func3EC54;
s32 func_8003EC54(Func3EC54 *arg0) { s32 value = arg0->value48 + arg0->value4C; return (s16)(value >> 16); }
#endif

#ifdef VERSION_US
typedef struct { u16 keyCount; u16 baseIndex; } EventIndex;
s32 ModelAnim_ResolveEventIndex(s32 arg0, EventIndex* arg1, s32 arg2) { EventIndex* temp_v0 = &arg1[arg2]; s32 ret; if (arg0 < temp_v0->keyCount) { ret = arg0 + temp_v0->baseIndex; } else { ret = (temp_v0->baseIndex + temp_v0->keyCount) - 1; } return ret; }
#endif

#ifdef VERSION_US
s16 ModelAnim_AdvanceEventFrame(S1_unk_D_86002F58_004_000_054* arg0, u16 arg1) {
    s16 var_v1;
    S1_unk_D_86002F58_004_000_054_004* temp_v0;

    var_v1 = arg0->unk_08;
    temp_v0 = arg0->unk_04;

    if (arg0->unk_0A != arg1) {
        var_v1 += 1;
        if (var_v1 >= temp_v0->unk_0A) {
            if (temp_v0->unk_00 & 2) {
                var_v1 = temp_v0->unk_0A - 1;
            } else {
                var_v1 = temp_v0->unk_06;
            }
        }
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
extern s32 D_80126410; void ModelAnim_ResetEventContext(void) { D_80126410 = -1; }
#endif

#ifdef VERSION_US
extern u8 D_801263F0[];
typedef struct {
    u8 active;
    u8 unknown01;
    s16 frame;
    S1_unk_D_86002F58_004_000_054_004 *data;
    EventIndex *indices;
    u8 *values;
} SceneEventContext;
void ModelAnim_BeginEventContext(S1_unk_D_86002F58_004_000_054 *state, u16 renderFrame, s32 advance) {
    S1_unk_D_86002F58_004_000_054_004 *data;
    SceneEventContext *context;
    data = state->unk_04;
    D_80126410++;
    if (D_80126410 < 2) {
        context = &((SceneEventContext *)D_801263F0)[D_80126410];
        if (state->unk_04 != NULL) {
            if (advance != 0 && (*(u16 *)((u8 *)state + 2) & 1) == 0) {
                state->unk_08 = ModelAnim_AdvanceEventFrame(state, renderFrame);
            }
            state->unk_0A = renderFrame;
            context->active = 1;
            context->frame = state->unk_08;
            context->data = data;
            context->indices = func_80003240(data->unk_0C);
            context->values = func_80003240(data->unk_10);
            if (context->frame < 0) {
                context->frame = 0;
            }
        } else {
            context->active = 0;
        }
    }
}
#endif

#ifdef VERSION_US
extern s32 D_80126410; void ModelAnim_EndEventContext(void) { if (D_80126410 >= 0) { D_80126410--; } }
#endif

#ifdef VERSION_US
extern u8 D_801263F0[];
void func_8003EE20(s32 *arg0, s32 arg1, s32 arg2) {
    u8 *record;
    s32 index;
    if (D_80126410 < 0) { return; }
    if (D_80126410 >= 2) { return; }
    record = D_801263F0 + (D_80126410 * 0x10);
    if (record[0] != 1) { return; }
    if (arg2 < 0) { return; }
    if (arg2 >= (*((u16 *) ((*((u32 *) (record + 4))) + 8)))) { return; }
    ;
    *arg0 = ((*((u8 *) ((*((u32 *) (record + 0xC))) + ModelAnim_ResolveEventIndex(*((s16 *) (record + 2)), (void *) (*((u32 *) (record + 8))), arg2)))) * 12) + arg1;
}
#endif

#ifdef VERSION_US
void ModelAnim_ClearEventTrack(u8 *arg0) { *(s16 *)(arg0 + 0x54) = -1; *(s32 *)(arg0 + 0x58) = 0; }
#endif

#ifdef VERSION_US
s16 ModelAnim_BindEventTrack(S1_unk_D_86002F58_004_000* arg0, s16 arg1, s32 arg2) {
    S1_unk_D_86002F58_004_000_054_004* temp_v0 = func_80003240(arg2);
    S1_unk_D_86002F58_004_000_054* ptr = &arg0->unk_054;

    if ((temp_v0 != ptr->unk_04) || (arg1 != ptr->unk_00)) {
        ptr->unk_00 = arg1;
        ptr->unk_04 = temp_v0;
        ptr->unk_08 = temp_v0->unk_04 - 1;
    }

    return ptr->unk_08;
}
#endif

#ifdef VERSION_US
void ModelAnim_SetEventFrame(u8 *arg0, s16 value) { *(s16 *)(arg0 + 0x5C) = value - 1; }
#endif

#ifdef VERSION_US
void func_8003EF60(u8 *arg0) { *(u16 *)(arg0 + 0x56) |= 1; }
#endif

#ifdef VERSION_US
void func_8003EF70(u8 *arg0) { *(u16 *)(arg0 + 0x56) &= (u16)~1; }
#endif

#ifdef VERSION_US
s32 ModelAnim_IsEventFrame(u8 *arg0, s16 value) { return value == *(s16 *)(arg0 + 0x5C) + 1; }
#endif

#ifdef VERSION_US
s32 ModelAnim_IsEventTrackNearEnd(u8 *arg0) { return *(u16 *)(*(s32 *)(arg0 + 0x58) + 0xA) == *(s16 *)(arg0 + 0x5C) + 2; }
#endif

#ifdef VERSION_US
s32 ModelAnim_IsEventTrackDone(u8 *arg0) { return *(u16 *)(*(s32 *)(arg0 + 0x58) + 0xA) == *(s16 *)(arg0 + 0x5C) + 1; }
#pragma C_FUNCTION_PADDING(8)
#endif

#ifdef VERSION_US
extern S1_GraphNode* GeoNode_CreateContainer(S1_MainPoolState*, S1_GraphNode*);
extern u8 D_80126420[];
extern u8 D_80126438[];
void ModelRenderer_InitDisplayRoots(void) {
    GeoNode_CreateContainer(0, D_80126420);
    GeoNode_CreateContainer(0, D_80126438);
}
#endif

#ifdef VERSION_US
extern void func_8003F03C(s32, void *);
void func_8003F018(s32 arg0) {
    func_8003F03C(arg0, D_80126420);
}
#endif

#ifdef VERSION_US
extern S1_unk_D_86002F58_004_000 *GeoNode_CreateModelPart(S1_MainPoolState *, void *, s16, S1_Vec3f *, S1_Vec3s *, S1_Vec3f *);
extern S1_Vec3s D_800948DC;
void func_8003F03C(s32 arg0, void *arg1) {
    GeoNode_CreateModelPart(NULL, (void *) arg0, -1, &D_800948D0, &D_800948DC, (S1_Vec3f *) D_800948E4);
    func_80038F8C(arg1, (void *) arg0);
    (*(u8 *)((u8 *)(arg0) + (1))) = (u8) ((*(u8 *)((u8 *)(arg0) + (1))) & 0xFFFE);
}
#endif

#ifdef VERSION_US
void ModelRenderer_AttachSecondaryDisplayObject(void *arg0) {
    GeoNode_CreateModelPart(NULL, arg0, 0, &D_800948D0, &D_800948DC, (S1_Vec3f *) D_800948E4);
    func_80038F8C(D_80126438, arg0);
    (*(u8 *)((u8 *)(arg0) + (1))) = (u8) ((*(u8 *)((u8 *)(arg0) + (1))) & 0xFFFE);
}
#endif

#ifdef VERSION_US
extern void func_8007074C(void *);
extern void func_8006D430(s32);
void func_8003F114(u8 *node, s16 animation, s16 model, void *data) {
    func_80038F8C(node, data);
    MtxF_Identity((f32 *)(node + 0x60));
    *(s16 *)(node + 0x18) = animation;
    *(s16 *)(node + 0x1A) = model;
    node[0x1D] = 0xFF;
    node[0x1C] = 0;
    node[1] |= 1;
    node[2] &= ~4;
    node[2] |= 0x20;
    node[2] |= 0x40;
    node[2] &= ~2;
    *(u32 *)(node + 0xA0) = 0xFFFFFF00U;
    *(u32 *)(node + 0x3C) = 0xFFFFFF00U;
    node[0xA6] = 0;
    *(s16 *)(node + 0x40) = -1;
    *(void **)(node + 0x44) = NULL;
    *(s16 *)(node + 0x54) = -1;
    *(void **)(node + 0x58) = NULL;
    node[2] &= ~8;
    if (model >= 0) func_8007074C(node);
    func_8006D430((s32)node);
}
#endif

#ifdef VERSION_US
extern void func_8006D438();

void func_8003F1DC(void *arg0) {
    func_8006D438();
    (*(s32 *)((u8 *)(arg0) + (0xC))) = 0;
    (*(u8 *)((u8 *)(arg0) + (1))) = (u8) ((*(u8 *)((u8 *)(arg0) + (1))) & 0xFFFE);
}
#endif

#ifdef VERSION_US
typedef struct {
    u32 unknown00;
    u8 transformCount;
    u8 eventCount;
    u8 unknown06[6];
    void **transformTracks;
    void **eventTracks;
} SceneAnimationBank;
typedef SceneAnimationBank *(*SceneAnimationBankGetter)(s32, s32);
typedef struct {
    S1_GraphNode node;
    u8 unknown18[0x14];
    SceneAnimationBankGetter getAnimationBank;
} SceneAnimationAsset;
s32 ModelAnim_SetAnimation(S1_unk_D_86002F58_004_000 *object, s32 animation) {
    s32 result = 0;
    SceneAnimationBank *bank;
    if (object->unk_000.unk_0C != NULL) {
        if (((SceneAnimationAsset *)object->unk_000.unk_0C)->getAnimationBank != NULL) {
            bank = ((SceneAnimationAsset *)object->unk_000.unk_0C)->getAnimationBank(0, 0);
            if (bank != NULL) {
                if (animation == -1) {
                    ModelAnim_ClearTransformChannel((u8 *)object);
                } else if (animation < bank->transformCount) {
                    ModelAnim_BindTransformCurve(object, (s16)animation, bank->transformTracks[animation], 0x10000);
                    result = 1;
                }
            }
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
extern s32 func_80042ADC(u8 *);
extern s32 func_800422B4(u8 *, s32, u16, u16);
extern void func_80042968(s32);
typedef struct {
    u16 first;
    u16 second;
} SceneAnimationTransfer;

typedef struct { u8 unknown00[0x40]; void *loadedCurve; } SceneAnimationResource;
s32 ModelAnim_SetResourceAnimation(SceneAnimationResource *resource, u8 *object, s32 animation) {
    s32 result = 0;
    SceneAnimationAsset *asset;
    SceneAnimationBank *bank;
    S1_unk_D_86002F58_004_000_040 *channel;
    asset = (SceneAnimationAsset *)((S1_unk_D_86002F58_004_000 *)object)->unk_000.unk_0C;
    bank = asset->getAnimationBank(0, 0);
    channel = &((S1_unk_D_86002F58_004_000 *)object)->unk_040;
    if (animation == -1) {
        ModelAnim_ClearTransformChannel((u8 *)object);
    } else if (animation < bank->transformCount) {
        if (channel->unk_04 != resource->loadedCurve || animation != channel->unk_00) {
            s32 format;
            format = func_80042ADC((u8 *)bank);
            if (format >= 0) {
                func_800422B4((u8 *)resource, format, *(u16 *)bank, ((SceneAnimationTransfer *)bank->transformTracks)[animation].second);
                func_80042968((s32)resource);
            }
        }
        ModelAnim_BindTransformCurve(object, (s16)animation, resource->loadedCurve, 0x10000);
        result = 1;
    }
    return result;
}
#endif

#ifdef VERSION_US
s32 ModelAnim_SetEventTrack(void *arg0, s32 arg1) { struct CallbackData { char pad[0x2C]; void *(*callback)(s32, s32); } *data; void *result; data = *(struct CallbackData **)((u8 *)arg0 + 0x0C); result = data->callback(0, 0); if (arg1 == -1) { ModelAnim_ClearEventTrack(arg0); } else if (arg1 < *(u8 *)((u8 *)result + 5)) { ModelAnim_BindEventTrack(arg0, (s16)arg1, ((s32 *)*(void **)((u8 *)result + 0x10))[arg1]); return 1; } return 0; }
#endif

#ifdef VERSION_US
void func_8003F454(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    Color_SetRGBA((Color3575C *)(u32)(arg0 + 0xA0), arg1 & 0xFF, arg2 & 0xFF, arg3 & 0xFF, (u8) (s32) arg4);
}
#endif

#ifdef VERSION_US
void func_8003F498(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    Color_SetRGBA((Color3575C *)(u32)(arg0 + 0xA0), arg1 & 0xFF, arg2 & 0xFF, arg3 & 0xFF, (u8) (s32) arg4);
}
#endif

#ifdef VERSION_US
void func_8003F4DC(u8 *arg0, u8 value) { arg0[0x1D] = value; }
#endif

#ifdef VERSION_US
void func_8003F4E8(u8 *arg0, u8 value) { arg0[0x1C] = value; }
#endif

#ifdef VERSION_US
extern void *D_8009491C;
s32 func_8003F4F4(void *arg0, s32 arg1) {
    s32 result = 0;
    void *entry;
    if (arg0 == NULL) arg0 = D_8009491C;
    if (arg0 != NULL) {
        entry = *(void **)((u8 *)arg0 + 0xC);
        result = (*(s32 (**)())((u8 *)entry + 0x2C))(arg1, 0);
    }
    return result;
}
#endif

#ifdef VERSION_US
extern void *func_80003240();
void *func_8003F54C(void *arg0) {
    void *result = NULL;
    void *entry;
    void *value;

    entry = *(void **)((u8 *)arg0 + 0xC);
    if (entry != NULL) {
        value = (*(void *(**)(s32, s32))((u8 *)entry + 0x2C))(0, 0);
        if (*(void **)((u8 *)value + 0x18) != NULL) {
            result = func_80003240(*(void **)((u8 *)value + 0x18));
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F5AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F6E0.s")
#endif

#ifdef VERSION_US
extern void _bzero(void *arg0, s32 arg1);
void func_8003F818(s32 *arg0, s32 arg1) {
    _bzero(arg0, 0x10);
    *arg0 = arg1;
}
#endif

#ifdef VERSION_US
void func_8003F84C(u8 *arg0, u32 value1, u32 value2) { arg0[4] |= 0x80; *(u32 *)(arg0 + 8) = value1; *(u32 *)(arg0 + 0xC) = value2; }
#endif

#ifdef VERSION_US
void func_8003F864(u8 *arg0) { arg0[4] = (u8)(arg0[4] & ~0x10); }
#endif

#ifdef VERSION_US
extern s32 func_800421E0(u8 *, s32, s32);
extern void PokeIcon_WaitBackgroundLoad(s32);
typedef struct {
    u8 *context;
    u8 flags;
    u8 unknown05[3];
    s32 source;
    s32 background;
} SceneBackgroundRequest;
void PokeIcon_RequestBackgroundForObject(SceneBackgroundRequest *request) {
    if (!(request->flags & 0x40) && (request->flags & 0x80)) {
        func_800421E0(request->context, request->source, request->background);
        request->flags |= 0x40;
        request->flags &= ~0x10;
        if (request->flags & 0x20) {
            PokeIcon_WaitBackgroundLoad((s32)request->context);
            request->background = *(s32 *)(request->context + 0x3C);
            request->flags &= ~0xE0;
        }
    }
}
#endif

#ifdef VERSION_US
extern s32 func_80042808(s32);
void func_8003F904(u8 *arg0) {
    if (func_80042808(*(s32 *)arg0)) {
        *(s32 *)(arg0 + 0xC) = *(s32 *)(*(s32 *)arg0 + 0x3C), arg0[4] = (arg0[4] & ~0xE0), arg0[4] |= 0x10;
    }
}
#endif

#ifdef VERSION_US
s32 func_8003F954(u16 value) { return value % 9; }
#endif

#ifdef VERSION_US
s32 func_8003F970(s32 arg0, u16 arg1) {
    s32 result = 0;
    if (arg0 == 0xEB) {
        result = func_8003F954(arg1);
    }
    return result;
}
#endif

#ifdef VERSION_US
s32 SceneObject_SetModelVariant(u8 *object, s32 kind, u16 value) {
    s32 result = 0;
    if (object != NULL) {
        object[0xA6] = func_8003F970(kind, value);
        result = 1;
    }
    return result;
}
#pragma C_FUNCTION_PADDING(4)
#endif

#ifdef VERSION_US
extern void func_80027E30(void);
extern void func_80027F4C(void);
extern s16 D_8012651A;
extern s32 D_80126458[];
extern s16 D_8012651E;
extern s16 D_80126518;
extern s32 D_80126520;
extern void *func_80003240();
void geo_layout_cmd_branch_and_link(void)
{
  s32 p = D_80126520;
  s32 i = D_8012651A;
  if (D_8012651A)
  {
  }
  D_80126458[i] = p + 8;
  D_8012651A = i + 1;
  D_80126458[D_8012651A] = (D_80126518 << 16) + D_8012651E;
  D_8012651A = D_8012651A + 1;
  D_8012651E = D_8012651A;
  D_80126520 = (s32) func_80003240(*((s32 *) (((u8 *) p) + 4)));
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_2A(void) {
    s32 new_var;
    s32 p = D_80126520;
    s32 i = D_8012651A;
    if (D_8012651A)
    {
    }
    new_var = p;
    D_80126458[i] = p + 8;
    D_8012651A = i + 1;
    D_80126458[D_8012651A] = (D_80126518 << 16) + D_8012651E;
    D_8012651A = D_8012651A + 1;
    D_8012651E = D_8012651A;
    D_80126520 = (s32)func_80003240(*((s32 *) (*((s32 **) (new_var + 4)))));
}
#endif

#ifdef VERSION_US
extern s16 D_80126518;
extern s16 D_8012651A;
extern s16 D_8012651E;
void func_8003FB2C(void) {
    s16 temp_v0;
    D_8012651A = D_8012651E;
    temp_v0 = D_8012651A - 1;
    D_8012651A = temp_v0;
    D_8012651E = D_80126458[temp_v0] & 0xFFFF;
    D_80126518 = (u32)D_80126458[D_8012651A] >> 16;
    temp_v0 = D_8012651A - 1;
    D_8012651A = temp_v0;
    D_80126520 = D_80126458[temp_v0];
}
#endif

#ifdef VERSION_US
extern s32 D_80126520;
void geo_layout_cmd_jump(void) {
    void *p = (void *)(u32)D_80126520;
    D_80126520 = (s32)func_80003240(*(s32 *)((u8 *)p + 4));
}
#endif

#ifdef VERSION_US
extern void * func_80003240();
extern s16 D_8012651A;
void func_8003FBE0(void) {
    s32 (*command)[2] = (s32 (*)[2])D_80126520;
    D_80126458[D_8012651A] = D_80126520 + 8;
    D_8012651A++;
    D_80126520 = (s32)func_80003240((*command)[1]);
}
#endif

#ifdef VERSION_US
extern s16 D_8012651A;
extern s32 D_80126458[];
extern void * func_80003240();
void geo_layout_cmd_27(void)
{
    s32 new_var;
    s32 i = D_8012651A;
    s32 p = D_80126520;
    new_var = p;
    D_80126458[i] = p + 8;
    if (D_80126520)
    {
    }
    D_8012651A = i + 1;
    D_80126520 = (s32)func_80003240(*((s32 *) (*((s32 **) (new_var + 4)))));
}
#endif

#ifdef VERSION_US
extern s16 D_8012651A;
void geo_layout_cmd_return(void) { s16 temp_v0; temp_v0 = D_8012651A - 1; D_8012651A = temp_v0; D_80126520 = D_80126458[temp_v0]; }
#endif

#ifdef VERSION_US
extern s16 D_80126518;
extern s32 D_80126498[];
void geo_layout_cmd_open_node(void) {
    s32 i = D_80126518;
    s32 *table = D_80126498;
    table[i + 1] = table[i];
    D_80126518 = i + 1;
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_close_node(void) {
    D_80126518--;
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
extern void *D_80126454;
extern void func_80038F8C(void *arg0, void *arg1);
extern s16 D_80126518;
void func_8003FD34(void *arg0) {
    s32 *entry;
    s16 index;
    if (arg0 != NULL) {
        index = D_80126518;
        entry = &D_80126498[index];
        *entry = (s32)arg0;
        if (index == 0) {
            if (D_80126454 == NULL) {
                D_80126454 = arg0;
            }
        } else {
            func_80038F8C(entry[-1], arg0);
        }
    }
}
#endif

#ifdef VERSION_US
extern S1_MainPoolState *D_80126450;
extern void func_8003FD34(void *);
extern void *func_800380B8(S1_MainPoolState *, s32, s16);
extern void *func_8003811C(S1_MainPoolState *, s32, s16);
void geo_layout_cmd_attach_node(void) {
    struct Cmd {
        u8 pad[4];
        void *child;
    } *cmd;

    cmd = (struct Cmd *)(u32)D_80126520;
    func_8003FD34(cmd->child);
    D_80126520 += 8;
}
#endif

#ifdef VERSION_US
extern s16 D_80126518;
void func_8003FDD0(void) {
    S1_unk_D_800ABE00_cmd8 *cmd = (S1_unk_D_800ABE00_cmd8 *)(u32)D_80126520;
    S1_GraphNode *node = (S1_GraphNode *)D_80126498[D_80126518];
    if (node != NULL) {
        func_80037E3C(node, cmd->callback, cmd->callbackData);
    }
    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd8);
}
#endif

#ifdef VERSION_US
extern S1_GraphNode *func_80037E9C(S1_MainPoolState *, S1_GraphNode *);
extern void func_8003FD34(void *arg0);
void func_8003FE2C(void) {
    func_8003FD34(GeoNode_CreateContainer(D_80126450, NULL));
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_reference(void) {
    struct Cmd {
        u8 pad[4];
        S1_GraphNode *reference;
    } *cmd;

    cmd = (struct Cmd *)(u32)D_80126520;
    func_8003FD34(GeoNode_CreateWithReference(D_80126450, NULL, cmd->reference));
    D_80126520 += 8;
}
#endif

#ifdef VERSION_US
extern S1_unk_D_86002F34_00C *GeoNode_CreateCamera(S1_MainPoolState *, S1_unk_D_86002F34_00C *, s16, s16, s16, s16);
extern void Camera_ComputeEyeFromAngles(S1_Vec3f *, S1_Vec3f *, f32, s16, s16);
extern void func_8003FD34(void *);
void func_8003FEB8(void) {
    S1_unk_D_800ABE00_cmdB *cmd = (S1_unk_D_800ABE00_cmdB *)(u32)D_80126520;
    S1_unk_D_86002F34_00C *node = GeoNode_CreateCamera(D_80126450, NULL, (s16)cmd->viewportX, (s16)cmd->viewportY, cmd->viewportWidth, cmd->viewportHeight);
    if (node != NULL) {
        node->unk_24.fovy = (f32)cmd->fovy;
        Vec3f_FromVec3s(&node->unk_60.at, &cmd->lookAt);
        Camera_ComputeEyeFromAngles(&node->unk_60.at, &node->unk_60.eye, (f32)cmd->eyeDistance, (cmd->yaw << 15) / 180, (cmd->pitch << 15) / 180);
    }
    func_8003FD34(node);
    D_80126520 += 0x18;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_type3(void) {
    struct Cmd {
        u8 command;
        u8 pad;
        s16 value;
    } *cmd;

    cmd = (struct Cmd *)(u32)D_80126520;
    func_8003FD34(GeoNode_CreateType3((S1_MemoryBlock *)D_80126450, NULL, cmd->value));
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_type4(void) {
    struct Cmd {
        u8 command;
        u8 pad;
        s16 value;
    } *cmd;

    cmd = (struct Cmd *)(u32)D_80126520;
    func_8003FD34(GeoNode_CreateType4((S1_MemoryBlock *)D_80126450, NULL, cmd->value));
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_ortho(void) {
    struct Cmd {
        u8 command;
        u8 pad;
        s16 value;
    } *cmd;

    cmd = (struct Cmd *)(u32)D_80126520;
    func_8003FD34(func_800380B8(D_80126450, 0, cmd->value));
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_perspective(void) {
    struct Cmd {
        u8 command;
        u8 pad;
        s16 value;
    } *cmd;

    cmd = (struct Cmd *)(u32)D_80126520;
    func_8003FD34(func_8003811C(D_80126450, 0, cmd->value));
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_background(void) {
    struct TargetCmd16 { u8 cmd; u8 r; u8 g; u8 b; } *cmd;
    cmd = (struct TargetCmd16 *)(u32)D_80126520;
    func_8003FD34(GeoNode_CreateBackground(D_80126450, NULL, cmd->r, cmd->g, cmd->b));
    D_80126520 += sizeof(struct TargetCmd16);
}
#endif

#ifdef VERSION_US
extern s32 func_8003820C(s32, s32);
void geo_layout_cmd_create_clear_depth(void) {
    func_8003FD34((void *)(S1_uintptr_t)func_8003820C((s32)(S1_uintptr_t)D_80126450, 0));
    D_80126520 += 4;
}
#endif

void geo_layout_cmd_noop(void) {
}

#ifdef VERSION_US
void geo_layout_cmd_create_fog(void) {
    S1_unk_D_800ABE00_cmd13* cmd = (S1_unk_D_800ABE00_cmd13*)D_80126520;

    func_8003FD34(GeoNode_CreateFog((s32)(S1_uintptr_t)D_80126450, NULL, cmd->fogNear, cmd->fogFar, cmd->r, cmd->g, cmd->b, 0xFF));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd13);
}
#endif

#ifdef VERSION_US
extern void *GeoNode_CreateLight(S1_MainPoolState *, void *, s16, s16, u8, u8, u8, u8);
extern void func_8003FD34(void *);
void geo_layout_cmd_create_light(void) {
    S1_unk_D_800ABE00_cmd14 *cmd = (S1_unk_D_800ABE00_cmd14 *)(u32)D_80126520;
    func_8003FD34(GeoNode_CreateLight(D_80126450, NULL, (cmd->pitch << 15) / 180, (cmd->yaw << 15) / 180, cmd->r, cmd->g, cmd->b, cmd->a));
    D_80126520 += 12;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_28(void) {
    s32 *node = (s32 *)D_80126498[D_80126518];
    if (node != NULL) {
        *((u8 *)node + 2) |= 1;
    }
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
s32 func_80038474(s32, s32);

void geo_layout_cmd_29(void) {
    func_8003FD34((void *)(S1_uintptr_t)func_80038474((s32)(S1_uintptr_t)D_80126450, 0));
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
extern s32 D_80126520; void geo_layout_cmd_skip(void) { D_80126520 += 0xC; }
#endif

#ifdef VERSION_US
typedef struct S1_unk_D_800ABE00_cmd16 S1_unk_D_800ABE00_cmd16;
struct S1_unk_D_800ABE00_cmd16 {
      u8 cmd;
      u8 r;
      u8 g;
      u8 b;
};
void geo_layout_cmd_create_ambient_light(void) {
    S1_unk_D_800ABE00_cmd16* cmd = (S1_unk_D_800ABE00_cmd16*)D_80126520;

    func_8003FD34(GeoNode_CreateAmbientLight(D_80126450, NULL, cmd->r, cmd->g, cmd->b));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd16);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_17(void) {
    s32 var_v1;

    var_v1 = 0;
    if ((*(u8 *)((u8 *)(D_80126520) + (1))) & 1) {
        var_v1 = 1;
    }
    func_8003FD34(func_800384C0(D_80126450, 0, (*(s16 *)((u8 *)(D_80126520) + (2))), (*(s32 *)((u8 *)(D_80126520) + (8))), (s32) (*(s16 *)((u8 *)(D_80126520) + (4))), (*(s32 *)((u8 *)(D_80126520) + (0xC))), (s32) (*(s16 *)((u8 *)(D_80126520) + (6))), (*(s32 *)((u8 *)(D_80126520) + (0x10))), var_v1));
    D_80126520 += 0x14;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_shadow(void) {
    S1_unk_D_800ABE00_cmd18* cmd = (S1_unk_D_800ABE00_cmd18*)D_80126520;

    func_8003FD34(GeoNode_CreateShadow(D_80126450, NULL, cmd->unk_01, cmd->unk_04, cmd->unk_06, cmd->unk_02));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd18);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_cull_distance(void) {
    S1_unk_D_800ABE00_cmd19* cmd = (S1_unk_D_800ABE00_cmd19*)D_80126520;

    func_8003FD34(GeoNode_CreateCullDistance(D_80126450, NULL, cmd->nearDistance, cmd->farDistance));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd19);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_switch_case(void) {
    S1_unk_D_800ABE00_cmd1A* cmd = (S1_unk_D_800ABE00_cmd1A*)D_80126520;

    func_8003FD34(GeoNode_CreateSwitchCase(D_80126450, NULL, cmd->unk_01, cmd->caseIndex));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd1A);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_translate_rotate(void) {
    S1_Vec3s sp30;
    S1_Vec3f sp24;
    UNUSED s32 pad;
    S1_unk_D_800ABE00_cmd1B* cmd = (S1_unk_D_800ABE00_cmd1B*)D_80126520;

    Vec3f_FromVec3s(&sp24, &cmd->translation);
    Vec3s_SetComponents(&sp30, (cmd->rotX << 0xF) / 180, (cmd->rotY << 0xF) / 180, (cmd->rotZ << 0xF) / 180);
    func_8003FD34(GeoNode_CreateTranslateRotate(D_80126450, NULL, &sp24, &sp30));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd1B);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_translate(void) {
    S1_Vec3f sp24;
    S1_unk_D_800ABE00_cmd1C* cmd = (S1_unk_D_800ABE00_cmd1C*)D_80126520;

    sp24.x = cmd->translateX / 65536.0f;
    sp24.y = cmd->translateY / 65536.0f;
    sp24.z = cmd->translateZ / 65536.0f;
    func_8003FD34(GeoNode_CreateTranslate(D_80126450, NULL, &sp24));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd1C);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_animated_part(void) {
    S1_Vec3f sp3C;
    s16 var_a3 = 1;
    S1_unk_D_800ABE00_cmd1D* cmd = (S1_unk_D_800ABE00_cmd1D*)D_80126520;

    sp3C.x = cmd->translateX / 65536.0f;
    sp3C.y = cmd->translateY / 65536.0f;
    sp3C.z = cmd->translateZ / 65536.0f;

    if (cmd->flags & 1) {
        var_a3 = 0;
    }

    if (cmd->flags & 2) {
        var_a3 |= 2;
    }

    func_8003FD34(
        GeoNode_CreateAnimatedPart(D_80126450, NULL, cmd->partIndex, var_a3, cmd->animIndex, &cmd->rotationA, &cmd->rotationB, &sp3C));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd1D);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_display_list_part(void) {
    S1_unk_D_800ABE00_cmd1E* cmd = (S1_unk_D_800ABE00_cmd1E*)D_80126520;

    func_8003FD34(GeoNode_CreateDisplayListPart(D_80126450, NULL, cmd->partIndex, cmd->displayList, cmd->unk_02));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd1E);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_model_part(void) {
    S1_Vec3s sp40;
    S1_Vec3f sp34;
    S1_Vec3f sp28;
    S1_unk_D_86002F58_004_000* tmp;
    S1_unk_D_800ABE00_cmd1F* cmd = (S1_unk_D_800ABE00_cmd1F*)D_80126520;

    Vec3f_FromVec3s(&sp34, &cmd->position);

    sp28.x = cmd->scaleX / 100.0f;
    sp28.y = cmd->scaleY / 100.0f;
    sp28.z = cmd->scaleZ / 100.0f;

    Vec3s_SetComponents(&sp40, (cmd->rotX << 0xF) / 180, (cmd->rotY << 0xF) / 180, (cmd->rotZ << 0xF) / 180);
    tmp = GeoNode_CreateModelPart(D_80126450, NULL, cmd->modelIndex, &sp34, &sp40, &sp28);
    func_8003FD34(tmp);

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd1F);
}
#endif

#ifdef VERSION_US
extern void func_8003FD34(void *);
void geo_layout_cmd_create_display_list_matrix(void) {
    S1_Vec3f sp34;
    S1_Vec3s sp2C;
    void *node;
    S1_unk_D_800ABE00_cmd20 *cmd = (S1_unk_D_800ABE00_cmd20 *)D_80126520;
    Vec3f_FromVec3s(&sp34, &cmd->position);
    Vec3s_SetComponents(&sp2C, (cmd->rotX << 15) / 180, (cmd->rotY << 15) / 180, (cmd->rotZ << 15) / 180);
    node = GeoNode_CreateDisplayListMatrixFromTransform((s32)D_80126450, 0, cmd->partIndex, (s32)cmd->displayList, (s32)&sp34, (s32)&sp2C);
    func_8003FD34(node);
    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd20);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_scale(void) {
    S1_Vec3f sp2C;
    S1_unk_D_86002F34_alt9* tmp;
    S1_unk_D_800ABE00_cmd21* cmd = (S1_unk_D_800ABE00_cmd21*)D_80126520;

    Vec3f_FromVec3s(&sp2C, &cmd->position);
    tmp = GeoNode_CreateScale(D_80126450, NULL, cmd->partIndex, cmd->displayList, &sp2C, cmd->scale / 65536.0f);
    func_8003FD34(tmp);

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd21);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_display_list(void) {
    S1_unk_D_800ABE00_cmd22* cmd = (S1_unk_D_800ABE00_cmd22*)D_80126520;

    func_8003FD34(GeoNode_CreateDisplayList(D_80126450, NULL, cmd->partIndex, cmd->displayList));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd22);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_shadow_texture(void) {
    S1_unk_D_800ABE00_cmd23* cmd = (S1_unk_D_800ABE00_cmd23*)D_80126520;

    func_8003FD34(GeoNode_CreateShadowTexture(D_80126450, NULL, cmd->colorOverrideFlag, cmd->eventFrame, cmd->displayList, cmd->textureIndex1, cmd->textureIndex2,
                                cmd->r, cmd->g, cmd->b, cmd->a));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd23);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_anchor(void) {
    S1_unk_D_800ABE00_cmd24* cmd = (S1_unk_D_800ABE00_cmd24*)D_80126520;

    func_8003FD34(GeoNode_CreateAnchor(D_80126450, NULL, cmd->anchorId));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd24);
}
#endif

#ifdef VERSION_US
extern s16 D_80126518;
void geo_layout_cmd_set_node_flag4(void) {
    u8 *entry = (u8 *)D_80126498[D_80126518];
    if (entry != 0) { entry[2] |= 4; }
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_group(void) {
    S1_unk_D_800ABE00_cmd26* cmd = (S1_unk_D_800ABE00_cmd26*)D_80126520;

    func_8003FD34(GeoNode_CreateGroup(D_80126450, NULL, cmd->unk_01, cmd->unk_04, cmd->unk_06, cmd->unk_08, cmd->unk_0A,
                                cmd->unk_02, cmd->unk_03, cmd->unk_0C, cmd->r, cmd->g, cmd->b, cmd->a));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd26);
}
#endif

#ifdef VERSION_US
extern s32 D_80094BB0;
extern void (*D_80094BB4[])(void);
void *process_geo_layout(S1_MemoryBlock *pool, void *script) {
    D_80126454 = NULL;
    D_80126518 = 0;
    D_8012651A = 2;
    D_8012651E = 2;
    D_80126520 = (s32)func_80003240(script);
    D_80126450 = (S1_MainPoolState *)pool;
    D_80094BB0 = 0;
    D_80126498[0] = 0;
    D_80126458[0] = 0;
    D_80126458[1] = 0;
    while (D_80126520 != 0) {
        D_80094BB4[*((u8 *)(u32)D_80126520)]();
    }
    return D_80126454;
}
#pragma C_FUNCTION_PADDING(20)
#endif

#ifdef VERSION_US
typedef struct {
    u8 mode;
    u8 type;
    s16 width;
    s16 height;
    s16 numTexels;
    void *texture;
} SceneTextureData;
typedef struct {
    s32 count;
    u16 *colors;
    u32 unknown08;
} ScenePaletteData;
typedef struct {
    S1_GraphNode node;
    SceneTextureData *textures;
    ScenePaletteData *palettes;
    Vtx *vertices;
    u8 textureCount;
    u8 paletteCount;
    s16 unknown26;
    void *callback;
} SceneTextureModel;
extern u16 Color_AdjustRGB5551(u16, S1_arg1_func_80010CA8);
extern u32 Color_AdjustRGBA8(u32, S1_arg1_func_80010CA8);
void Model_AdjustTextureColors(SceneTextureModel *model, S1_arg1_func_80010CA8 adjustment) {
    s32 i;
    s32 j;
    SceneTextureData *texture = model->textures;
    ScenePaletteData *palette = model->palettes;
    for (i = 0; i < model->textureCount; i++, texture++) {
        if (texture != NULL && texture->texture != NULL && texture->mode == 0) {
            if (texture->type == 2) {
                u16 *pixel = texture->texture;
                for (j = 0; j < texture->numTexels; j++, pixel++) {
                    *pixel = Color_AdjustRGB5551(*pixel, adjustment);
                }
            } else if (texture->type == 3) {
                u32 *pixel = texture->texture;
                for (j = 0; j < texture->numTexels; j++, pixel++) {
                    *pixel = Color_AdjustRGBA8(*pixel, adjustment);
                }
            }
        }
    }
    for (i = 0; i < model->paletteCount; i++, palette++) {
        if (palette != NULL && palette->colors != NULL) {
            u16 *pixel = palette->colors;
            for (j = 0; j < palette->count; j++, pixel++) {
                *pixel = Color_AdjustRGB5551(*pixel, adjustment);
            }
        }
    }
}
#endif

#ifdef VERSION_US
typedef struct { s32 unused0; s32 unused1; s32 offset; s32 size; } CandidateJpegHeader;
extern s32 Jpeg_DecodeImage(u32, s32, u8 *);
extern void MainPool_ResetStateToOffset(void *, s32);
void *func_80041130(void *arg0, void *arg1, s32 arg2, CandidateJpegHeader *arg3) {
    void *sp1C;
    s32 sp18;
    s32 result;
    sp18 = 0;
    if (arg1 == NULL) {
        sp18 = ((s32 *)arg0)[1];
        sp1C = MainPool_AllocAligned(arg0, arg3->size + 0x100, 0x10);
    } else {
        sp1C = arg1;
    }
    if (sp1C != NULL) {
            result = Jpeg_DecodeImage((u32)sp1C, arg3->size + 0x100, (u8 *)arg3 + arg3->offset);
        if (arg1 == NULL) {
            if (result == 0) {
                MainPool_ResetStateToOffset(arg0, sp18);
                sp1C = NULL;
            } else {
                MainPool_ResetStateToOffset(arg0, sp18 + result);
            }
        }
    }
    return sp1C;
}
#endif

#ifdef VERSION_US
extern void Yay0_DecompressAndRelocate(u8 *, u8 *);
u8 *func_800411F0(void *arg0, u8 *arg1, s32 arg2, u8 *arg3) {
    u8 *var_a1;
    u8 *sp1C;

    if (arg1 == NULL) {
        var_a1 = MainPool_AllocAligned(arg0, *(u32 *)((u8 *)arg3 + 0x10), 0x10);
    } else {
        var_a1 = arg1;
    }
    if (var_a1 != NULL) {
        sp1C = var_a1;
        Yay0_DecompressAndRelocate(arg3, var_a1);
    }
    return var_a1;
}
#endif

#ifdef VERSION_US
extern void Util_Memcpy(u32 *, const u32 *, s32);
extern void *MainPool_AllocAligned(void *, size_t, s32);
void *func_8004124C(void *arg0, void *arg1, s32 arg2, s32 arg3, u32 arg4) {
    void *var_a0;
    void *sp1C;

    if (arg1 == NULL) {
        var_a0 = MainPool_AllocAligned(arg0, arg4, 0x10);
    } else {
        var_a0 = arg1;
    }
    if (var_a0 != NULL) {
        sp1C = var_a0;
        Util_Memcpy(var_a0, arg2 + arg3, arg4 >> 2);
    }
    return var_a0;
}
#endif

#ifdef VERSION_US
extern void func_80003F74(u8 *, u8 *, u8 *, s32);
s32 Fragment_LoadResourceFromRomRange(s32 pool, s32 destination, s32 start, s32 end, s32 buffer, s32 capacity) {
    u32 size = (end - start + 0xF) & ~0xF;
    s32 result = 0;
    u32 *header;
    if ((u32)capacity >= size) {
        header = (u32 *)buffer;
        func_80003F74((u8 *)buffer, (u8 *)start, (u8 *)end, 0);
        if (header[0] == 0x50455253 && header[1] == 0x2D535A50) {
            result = (s32)func_800411F0((void *)pool, (u8 *)destination, buffer, (u8 *)buffer);
        } else if (header[0] == 0x50524553 && header[1] == 0x4A504547) {
            result = (s32)func_80041130((void *)pool, (void *)destination, buffer, (CandidateJpegHeader *)buffer);
        } else {
            result = (s32)func_8004124C((void *)pool, (void *)destination, buffer, 0, size);
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
#define RELOCATIONS_SIZE 1
typedef struct S1_Fragment S1_Fragment;
struct S1_Fragment {
      u32 inst[2];
      char magic[8];
      u32 headerSize;
      u32 relocOffset;
      u32 sizeInRom;
      u32 sizeInRam;
      char data[RELOCATIONS_SIZE];
};
void func_800413A0(S1_MainPoolState* arg0, u32 arg1, S1_Fragment* arg2) {
    Memmap_RelocateFragment(arg1, arg2);
    MainPool_ResetStateToOffset(arg0, ((u32)arg2 + arg2->sizeInRam) - (u32)arg0->listHeadR);
}
#endif

#ifdef VERSION_US
extern s32 Fragment_LoadResourceFromRomRange(s32, s32, s32, s32, s32, s32);
s32 func_800413E8(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 arg4, s32 arg5) {
    s32 sum1 = arg3[0] + arg2[1];
    s32 sum2 = sum1 + arg3[1];
    return Fragment_LoadResourceFromRomRange(arg0, arg1, sum1, sum2, arg4, arg5);
}
#endif

#ifdef VERSION_US
s32 func_80041430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 base = arg2;
    s32 result = 0;
    s32 *entry;
    if ((u32)arg3 < *(u32 *)((u8 *)base + 0xC)) {
        if (*(u16 *)base & 1) {
            result = (arg2 += *(s32 *)((u8 *)base + arg3 * 0x10 + 0x10));
        } else {
            if (!(*(u16 *)base & 4)) {
                if (*(s32 *)((u8 *)base + arg3 * 0x10 + 0x18) != 0) {
                    result = *(s32 *)((u8 *)base + arg3 * 0x10 + 0x18);
                    goto done;
                }
            }
            entry = (s32 *)((u8 *)base + arg3 * 0x10 + 0x10);
            result = func_800413E8(arg0, arg1, (s32 *)base, entry, arg4, arg5);
            if (result != 0 && arg1 == 0) {
                if (*(s32 *)(result + 8) == 0x46524147 && *(s32 *)(result + 12) == 0x4D454E54) {
                    func_800413A0((S1_MainPoolState *)arg0, *(u16 *)((u8 *)base + 2), (S1_Fragment *)result);
                }
                entry[2] = result;
            }
        }
    }
done:
    return result;
}
#endif

#ifdef VERSION_US
typedef struct SceneProcessedModel SceneProcessedModel;
typedef SceneProcessedModel *(*SceneModelEntry)(s32, s32);
struct SceneProcessedModel {
    u16 species;
    u8 format;
    u8 geometryCount;
    u8 transformCount;
    u8 eventCount;
    u8 unknown06[2];
    void **geometry;
    void *transformTracks;
    void *eventTracks;
    SceneModelEntry entry;
};
typedef struct {
    S1_GraphNode node;
    u8 unknown18[0x14];
    SceneModelEntry entry;
} SceneGeometryNode;
extern void *process_geo_layout(S1_MemoryBlock *, void *);
SceneProcessedModel *Fragment_ProcessGeoLayout(S1_MemoryBlock *pool, SceneModelEntry entry, S1_arg1_func_80010CA8 adjustment, u8 format, s32 special) {
    SceneProcessedModel *model;
    s32 i;
    model = entry(0, 0);
    model->entry = entry;
    for (i = 0; i < model->geometryCount; i++) {
        SceneGeometryNode *node;
        node = process_geo_layout(pool, model->geometry[i]);
        if (node->node.unk_00 == 14) {
            node->entry = entry;
            if (adjustment.raw != 0) {
                Model_AdjustTextureColors((SceneTextureModel *)node, adjustment);
            }
        }
        model->geometry[i] = node;
    }
    model->format = format & 0xF;
    if (special != 0) {
        model->format |= 0x80;
    }
    return model;
}
#endif

#ifdef VERSION_US
extern void *process_geo_layout(S1_MemoryBlock *, void *);
void Fragment_ProcessGeoLayoutList(S1_MemoryBlock* arg0, S1_arg1_func_80019420* arg1) {
    while (arg1->unk_00) {
        if (arg1->unk_00 == 3) {
            arg1->unk_04 = process_geo_layout(arg0, arg1->unk_04);
        }

        arg1++;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800416C8.s")
#endif

#ifdef VERSION_US
typedef struct {
    s16 kind;
    s16 id;
    s16 buffer;
    s8 variant;
    u8 unknown07;
    OSMesgQueue *reply;
    void *data;
    s32 source;
    u8 *destination;
    s32 size;
    S1_arg1_func_80010CA8 adjustment;
} SceneWorkerMessage;
extern u8 *MainPool_InitState(u8 *, s32);
extern void MainPool_FinalizeAllocation(S1_MemoryBlock *);
extern OSThread D_80126530;
void PokeIcon_LoadResourceList(SceneWorkerMessage *message) {
    s32 fragment;
    S1_MemoryBlock *pool;
    s32 count = 0;
    S1_arg1_func_80019420 **output = message->data;
    s16 *ids;
    pool = (S1_MemoryBlock *)MainPool_InitState(message->destination, message->size);
    ids = (s16 *)message->source;
    while (*ids != -1) {
        fragment = func_80041430((s32)pool, 0, *(s32 *)((u8 *)&D_80126530 + 0x9F4), *ids,
                                 *(s32 *)((u8 *)&D_80126530 + 0x9FC), 0xF000);
        if (fragment == 0) {
            break;
        }
        output[count] = (S1_arg1_func_80019420 *)(fragment + 0x20);
        Fragment_ProcessGeoLayoutList(pool, (S1_arg1_func_80019420 *)(fragment + 0x20));
        ids++;
        count++;
    }
    output[count] = NULL;
    message->size = pool->size + 0x10;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8004186C.s")
#endif

#ifdef VERSION_US
s32 func_80041430(s32, s32, s32, s32, s32, s32);
extern OSThread D_80126530;
void func_8002B1A0(void);
s32 func_80041430(s32, s32, s32, s32, s32, s32);
void func_80041A18(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_80041430(0, (*(s32 *)((u8 *)(arg0) + (0x14))), (*(s32 *)((u8 *)(&D_80126530) + (0x9F8))), (*(s16 *)((u8 *)(arg0) + (2))), (*(s32 *)((u8 *)(&D_80126530) + (0x9FC))), 0xF000);
    if (temp_v0 != 0) {
        (*(s32 *)((u8 *)(arg0) + (0xC))) = temp_v0;
        return;
    }
    (*(s32 *)((u8 *)(arg0) + (0xC))) = 0;
}
#endif

#ifdef VERSION_US
extern void __osSetFpcCsr(s32);
extern void func_800416C8(void *);
extern void PokeIcon_LoadResourceList(SceneWorkerMessage *);
extern void func_8004186C(void *);
extern void func_80041A18(void *arg0);
extern OSMesgQueue D_80126F00;
void func_80041A78(void *arg0) {
    OSMesg msg;
    OSMesgQueue *queue;
    queue = &D_80126F00;
    __osSetFpcCsr(0x1000C01);
    for (;;) {
        osRecvMesg(queue, &msg, 1);
        switch (*(s16 *)msg) {
        case 1: func_800416C8(msg); break;
        case 2: PokeIcon_LoadResourceList(msg); break;
        case 4: func_8004186C(msg); break;
        case 8: func_80041A18(msg); break;
        }
        if (*(OSMesgQueue **)((u8 *)msg + 8) != NULL) {
            osSendMesg(*(OSMesgQueue **)((u8 *)msg + 8), msg, 1);
        }
    }
}
#endif

#ifdef VERSION_US
void func_80041A78(void *);
extern void *D_80126EE0;
extern OSMesgQueue D_80126F00;
void func_80041B84(void) {
    osCreateMesgQueue(&D_80126F00, &D_80126EE0, 8);
    osCreateThread(&D_80126530, 7, func_80041A78, NULL, &D_80126EE0, 0xA);
    osStartThread(&D_80126530);
}
#endif

#ifdef VERSION_US
typedef struct {
    OSMesgQueue queue;
    OSMesg messages[2];
} SceneLoadQueue;
typedef struct {
    u8 flags;
    u8 pending;
    u8 variant;
    u8 bufferCount;
    void *modelBuffers[2];
    void *backgroundBuffer;
    void *animationBuffers[2];
    void *imageBuffers[2];
    s32 modelBufferSize;
    s32 animationBufferSizes[2];
    s32 modelSize;
    s32 backgroundSize;
    s32 curveSize;
    SceneAnimationBank *loadedModel;
    void *loadedBackground;
    void *loadedCurve;
    u32 unknown44;
    S1_arg1_func_80010CA8 colorAdjust;
    u16 species;
    u16 unknown4E;
    SceneLoadQueue queues[4];
} SceneLoadContext;
void PokeIcon_InitLoadContext(SceneLoadContext *context, s32 flags, s32 modelBufferSize) {
    context->flags = flags;
    context->pending = 0;
    context->variant = 0;
    context->bufferCount = 0;
    context->loadedModel = NULL;
    context->modelBuffers[0] = NULL;
    context->modelBuffers[1] = NULL;
    context->backgroundBuffer = NULL;
    context->animationBuffers[0] = NULL;
    context->animationBuffers[1] = NULL;
    context->modelBufferSize = modelBufferSize;
    context->animationBufferSizes[0] = 0;
    context->animationBufferSizes[1] = 0;
    context->colorAdjust.raw = 0;
    context->species = 0;
    osCreateMesgQueue(&context->queues[0].queue, context->queues[0].messages, 2);
    osCreateMesgQueue(&context->queues[1].queue, context->queues[1].messages, 2);
    osCreateMesgQueue(&context->queues[2].queue, context->queues[2].messages, 2);
    osCreateMesgQueue(&context->queues[3].queue, context->queues[3].messages, 2);
}
#endif

#ifdef VERSION_US
extern s32 main_pool_alloc(s32, s32);
SceneLoadContext *PokeIcon_AllocLoadContext(u32 flags) {
    SceneLoadContext *context = (SceneLoadContext *)main_pool_alloc(sizeof(SceneLoadContext), 1);
    s32 doubleBuffered;
    if (context != NULL) {
        PokeIcon_InitLoadContext(context, flags, 0x26000);
        if (flags & 1) {
            context->modelBuffers[0] = (void *)main_pool_alloc(0x26000, 1);
            if (flags & 4) {
                context->modelBuffers[1] = (void *)main_pool_alloc(0x26000, 1);
            }
        }
        if (flags & 2) {
            context->backgroundBuffer = (void *)main_pool_alloc(0x18000, 1);
        }
        if (flags & 0x10) {
            doubleBuffered = flags & 4;
            context->imageBuffers[0] = (void *)main_pool_alloc(0x25C00, 1);
            if (doubleBuffered) {
                context->imageBuffers[1] = (void *)main_pool_alloc(0x25C00, 1);
            }
        }
    }
    return context;
}
#endif

#ifdef VERSION_US
SceneLoadContext *PokeIcon_AllocSpecialModelContext(u16 modelId) {
    SceneLoadContext *context = NULL;
    s32 capacity = 0;
    switch (modelId) {
    case 0xFC:
        capacity = 0xF000;
        break;
    case 0x118:
        capacity = 0x4C00;
        break;
    }
    if (capacity != 0) {
        context = (SceneLoadContext *)main_pool_alloc(sizeof(SceneLoadContext), 1);
    }
    if (context != NULL) {
        PokeIcon_InitLoadContext(context, 1, capacity);
        context->bufferCount = 1;
        context->modelBuffers[0] = (void *)main_pool_alloc(capacity, 1);
    }
    return context;
}
#endif

#ifdef VERSION_US
extern s32 BinArchive_Open(s32, s32, s32, s32);
typedef void (*SceneFragmentEntry)(void);
extern SceneFragmentEntry Fragment_Load(s32, u8 *, u8 *);
extern u8 D_81000000[];
extern u8 fragment26_ROM_START[];
extern u8 fragment27_ROM_START[];
extern OSThread D_80126530;
void PokeIcon_InitResourceArchives(void) {
    *(s32 *)((u8 *)&D_80126530 + 0x9e8) = BinArchive_Open(func_800356CC(6), 0, 1, 1);
    *(s32 *)((u8 *)&D_80126530 + 0x9f4) = BinArchive_Open(func_800356CC(5), 0, 1, 1);
    *(s32 *)((u8 *)&D_80126530 + 0x9ec) = BinArchive_Open(func_800356CC(7), 0, 1, 1);
    *(s32 *)((u8 *)&D_80126530 + 0x9f0) = BinArchive_Open(func_800356CC(14), 0, 1, 1);
    *(s32 *)((u8 *)&D_80126530 + 0x9F8) = 0;
    *(s32 *)((u8 *)&D_80126530 + 0x9FC) = main_pool_alloc(0xF000, 1);
    Fragment_Load(((((u32)D_81000000 & 0x0FF00000) >> 20) - 0x10), fragment26_ROM_START, fragment27_ROM_START);
}
#endif

#ifdef VERSION_US
s32 main_pool_alloc(s32, s32);
s32 BinArchive_Open(s32, s32, s32, s32);
extern s32 D_80126F28;
extern s32 D_80126F2C;
void func_80041F14(void) {
    D_80126F28 = BinArchive_Open(func_800356CC(8), 0, 1, 1);
    D_80126F2C = main_pool_alloc(0xF000, 1);
}
#endif

#ifdef VERSION_US
extern s16 D_8009F428[];
s32 func_80041F60(s16 *arg0) {
    s16 *ptr = D_8009F428;
    s32 result = 0;
    while (*ptr != -1) {
        if (ptr == arg0) {
            result = 1;
        }
        ptr++;
    }
    return result;
}
#endif

#ifdef VERSION_US
typedef union { s32 word; s8 bytes[4]; } Func80041FA0State;
typedef Func80041FA0State Func80041FA0Packed;
extern s32 func_80041FD0(s32, u16, Func80041FA0State, s32);
void func_80041FA0(s32 arg0, u16 arg1, Func80041FA0State arg2) {
    func_80041FD0(arg0, arg1, arg2, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041FD0.s")
#endif

#ifdef VERSION_US
extern void *Util_Malloc(s32);
extern OSMesgQueue D_80126F00;
s32 func_800421E0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 result = 0;
    u8 *msg;
    if ((arg0[0] & 2) != 0) {
        if ((arg0[1] & 2) == 0) {
            msg = Util_Malloc(0x20);
            if (msg != NULL) {
                *(s16 *)(msg + 0) = 2;
                *(s16 *)(msg + 2) = 0;
                *(s16 *)(msg + 4) = 0;
                msg[6] = 0;
                *(void **)(msg + 8) = arg0 + 0x70;
                *(s32 *)(msg + 0xC) = arg2;
                *(s32 *)(msg + 0x10) = arg1;
                *(s32 *)(msg + 0x14) = *(s32 *)(arg0 + 0xC);
                *(s32 *)(msg + 0x18) = 0x18000;
                osSendMesg(&D_80126F00, (OSMesg)msg, 1);
                arg0[1] |= 2;
                result = 1;
            }
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
extern OSMesgQueue D_80126F00;
s32 func_800422B4(u8 *arg0, s32 arg1, u16 arg2, u16 arg3) {
    s32 result = 0;
    u8 *msg;
    if ((arg0[0] & 1) && !(arg0[1] & 4) && arg1 < 2 && *(s32 *)(((u8 (*)[4])arg0)[arg1] + 0x10)) {
        msg = Util_Malloc(0x20);
        if (msg != NULL) {
            *(u16 *)(msg + 0) = 4;
            *(u16 *)(msg + 2) = arg2;
            *(u16 *)(msg + 4) = arg3;
            msg[6] = 0;
            *(void **)(msg + 8) = arg0 + 0x90;
            *(s32 *)(msg + 0xC) = 0;
            *(s32 *)(msg + 0x10) = 0;
            *(s32 *)(msg + 0x14) = *(s32 *)(((u8 (*)[4])arg0)[arg1] + 0x10);
            *(s32 *)(msg + 0x18) = *(s32 *)(((u8 (*)[4])arg0)[arg1] + 0x24);
            osSendMesg(&D_80126F00, msg, 1);
            arg0[1] |= 4;
            result = 1;
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
extern OSMesgQueue D_80126F00;
s32 func_8004239C(u8 *arg0, s32 arg1) {
    s32 result = 0;
    u8 *msg;
    s32 index;
    u32 base;
    if ((arg0[0] & 0x10) && !(arg0[1] & 8)) {
        msg = Util_Malloc(0x20);
        if (msg != NULL) {
            index = arg0[2];
            if (arg0[0] & 4) { index ^= 1; }
            *(u16 *)(msg + 0) = 8;
            *(u16 *)(msg + 2) = arg1;
            *(u16 *)(msg + 4) = index;
            msg[6] = 0;
            base = (u32)arg0 + 0xB0;
            *(void **)(msg + 8) = (void *)base;
            *(s32 *)(msg + 0xC) = 0;
            *(s32 *)(msg + 0x10) = 0;
            *(s32 *)(msg + 0x14) = *(s32 *)((u8 *)arg0 + (index << 2) + 0x18);
            *(s32 *)(msg + 0x18) = 0x25C00;
            osSendMesg(&D_80126F00, msg, 1);
            arg0[1] |= 8;
            result = 1;
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
u32 Model_FindLowestTextureAddress(SceneTextureModel *model) {
    u32 result = 0;
    s32 count;
    u32 minimum;
    s32 i;
    SceneTextureData *entry;
    if (model->node.unk_00 == 14) {
        count = model->textureCount;
        minimum = 0xFFFFFFFF;
        for (i = 0; i < count; i++) {
            entry = &model->textures[i];
            if (entry->texture != NULL) {
                if ((u32)entry->texture < minimum) {
                    minimum = (u32)entry->texture;
                }
            }
        }
        if (minimum != 0xFFFFFFFF) {
            result = minimum;
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
typedef struct {
    s16 kind;
    s16 id;
    s16 buffer;
    s8 variant;
    u8 unknown07;
    OSMesgQueue *reply;
    void *data;
    s32 source;
    void *destination;
    s32 size;
    S1_arg1_func_80010CA8 adjustment;
} SceneLoadResult;
extern void Util_Free(void *);
s32 PokeIcon_ApplyResourceLoadResult(SceneLoadContext *context, SceneLoadResult *message) {
    s32 result = 0;
    switch (message->kind) {
    case 1:
        context->pending &= ~1;
        if (message->data != NULL) {
            s32 buffer;
            buffer = message->buffer;
            if (context->flags & 4) {
                context->variant ^= 1;
            }
            context->loadedModel = message->data;
            context->modelSize = message->size;
            context->colorAdjust = message->adjustment;
            context->species = message->variant;
            if (message->variant == 1) {
                u32 address;
                address = Model_FindLowestTextureAddress(((SceneProcessedModel *)context->loadedModel)->geometry[0]);
                if (address != 0) {
                    func_80041430(0, address, *(s32 *)((u8 *)&D_80126530 + 0x9F0), message->id,
                                  *(s32 *)((u8 *)&D_80126530 + 0x9FC), 0xF000);
                }
            }
            context->animationBuffers[buffer] = (u8 *)context->modelBuffers[buffer] + context->modelSize;
            if ((u32)context->animationBuffers[buffer] < (u32)context->modelBuffers[buffer] + context->modelBufferSize) {
                context->animationBufferSizes[buffer] = context->modelBufferSize - context->modelSize;
                result = 1;
                break;
            } else {
                context->animationBuffers[buffer] = NULL;
                context->animationBufferSizes[buffer] = 0;
            }
        }
        result = 1;
        break;
    case 2:
        context->pending &= ~2;
        context->loadedBackground = message->data;
        context->backgroundSize = message->size;
        result = 1;
        break;
    case 4:
        context->pending &= ~4;
        if (message->data != NULL) {
            context->loadedCurve = message->data;
            context->curveSize = message->size;
        }
        result = 1;
        break;
    case 8:
        context->pending &= ~8;
        if (message->data != NULL) {
            if (context->flags & 4) {
                context->variant ^= 1;
            }
            context->unknown44 = (u32)message->data;
        }
        result = 1;
        break;
    }
    Util_Free(message);
    return result;
}
#endif

#ifdef VERSION_US
extern s32 PokeIcon_ApplyResourceLoadResult(SceneLoadContext *, SceneLoadResult *);

s32 func_800427B8(s32 arg0) {
    void *sp1C;
    s32 sp18 = 0;

    if (osRecvMesg((OSMesgQueue *)(u32)(arg0 + 0x50), &sp1C, 0) != -1) {
        sp18 = PokeIcon_ApplyResourceLoadResult(arg0, sp1C);
    }
    return sp18;
}
#endif

#ifdef VERSION_US
s32 func_80042808(s32 arg0) {
    void *sp1C;
    s32 sp18 = 0;

    if (osRecvMesg((OSMesgQueue *)(u32)(arg0 + 0x70), &sp1C, 0) != -1) {
        sp18 = PokeIcon_ApplyResourceLoadResult(arg0, sp1C);
    }
    return sp18;
}
#endif

#ifdef VERSION_US
s32 func_80042858(s32 arg0) {
    void *sp1C;
    s32 sp18 = 0;

    if (osRecvMesg((OSMesgQueue *)(u32)(arg0 + 0x90), &sp1C, 0) != -1) {
        sp18 = PokeIcon_ApplyResourceLoadResult(arg0, sp1C);
    }
    return sp18;
}
#endif

#ifdef VERSION_US
s32 func_800428A8(s32 arg0) {
    void *sp1C;
    s32 sp18 = 0;

    if (osRecvMesg((OSMesgQueue *)(u32)(arg0 + 0xB0), &sp1C, 0) != -1) {
        sp18 = PokeIcon_ApplyResourceLoadResult(arg0, sp1C);
    }
    return sp18;
}
#endif

#ifdef VERSION_US
extern s32 PokeIcon_ApplyResourceLoadResult(SceneLoadContext *, SceneLoadResult *);

void func_800428F8(s32 arg0) {
    void *sp1C;

    osRecvMesg((OSMesgQueue *)(u32)(arg0 + 0x50), &sp1C, 1);
    PokeIcon_ApplyResourceLoadResult(arg0, sp1C);
}
#endif

#ifdef VERSION_US

void PokeIcon_WaitBackgroundLoad(s32 arg0) {
    void *sp1C;

    osRecvMesg((OSMesgQueue *)(u32)(arg0 + 0x70), &sp1C, 1);
    PokeIcon_ApplyResourceLoadResult(arg0, sp1C);
}
#endif

#ifdef VERSION_US

void func_80042968(s32 arg0) {
    void *sp1C;

    osRecvMesg((OSMesgQueue *)(u32)(arg0 + 0x90), &sp1C, 1);
    PokeIcon_ApplyResourceLoadResult(arg0, sp1C);
}
#endif

#ifdef VERSION_US

void func_800429A0(s32 arg0) {
    void *sp1C;

    osRecvMesg((OSMesgQueue *)(u32)(arg0 + 0xB0), &sp1C, 1);
    PokeIcon_ApplyResourceLoadResult(arg0, sp1C);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800429D8.s")
#endif

#ifdef VERSION_US
s32 func_80042A64(s32 arg0) { return 0; }
#endif

#ifdef VERSION_US
extern void *func_80004B4C(s32 arg0, s32 arg1);
extern S1_MemoryBlock *MainPool_AllocState(s32 arg0, s32 arg1);
extern s32 main_pool_get_available(void);
extern void MainPool_FinalizeAllocation(S1_MemoryBlock *arg0);
extern s32 D_80126F24;
S1_arg1_func_80019420 *BattleAnim_LoadResourceTable(s32 arg0) {
    s32 sp24;
    S1_arg1_func_80019420 *sp20;
    S1_MemoryBlock *sp1C;
    sp20 = NULL;
    sp24 = (s32)func_80004B4C(D_80126F24, arg0);
    if (sp24 != 0) {
        sp1C = MainPool_AllocState(main_pool_get_available(), 0);
        sp20 = (S1_arg1_func_80019420 *)(sp24 + 0x20);
        Fragment_ProcessGeoLayoutList(sp1C, sp20);
        MainPool_FinalizeAllocation(sp1C);
    }
    return sp20;
}
#endif

#ifdef VERSION_US
s32 func_80042ADC(u8 *arg0) { s32 result = -1; if (arg0 != NULL) result = arg0[2] & 0xF; return result; }
#endif
