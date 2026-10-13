#include "global.h"
#include <stdarg.h>


#ifdef VERSION_US
struct FontHeightRecord {
    s16 unk00;
    s16 height;
    u8 *data;
    s32 unk08;
};

extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern u8 *func_800042C0(u8 *, u8 *, s32, s32);
extern void _bcopy(const void *, void *, s32);
extern u32 D_437670;
extern u32 D_437750;
extern u8 *D_80126F50;
struct FontTableHeader {
    u8 mode;
    u8 extraCount;
    u16 bitmapOffset;
    u32 tables[3];
};
extern u8 D_80126F58[];
extern u8 D_80126F68[0x60];
extern u8 D_80126FC8[0x80];
extern u8 D_80127048[0x53];

/* Byte-array view of the variable-sized ROM image, including its header. */
struct FontTableBlob { u8 bytes[1]; };
u8 *func_80046980(void) {
    u8 *blob;
    s32 count;

    main_pool_push_state(0x414E4B50);
    D_80126F50 = NULL;
    D_80126F58[0] = 0xFF;
    blob = func_800042C0((u8 *)&D_437670, (u8 *)&D_437750, 0, 0);
    if (blob != NULL) {
        *(struct FontTableHeader *)D_80126F58 = *(struct FontTableHeader *)blob;
        if (((struct FontTableHeader *)blob)->tables[0] != 0) {
            _bcopy(&((struct FontTableBlob *)blob)->bytes[((struct FontTableHeader *)blob)->tables[0]], D_80126F68, 0x60);
            ((struct FontTableHeader *)D_80126F58)->tables[0] = (u32)D_80126F68;
        }
        if (((struct FontTableHeader *)blob)->tables[1] != 0) {
            u8 *copySource;
            count = 0x60;
            copySource = &((struct FontTableBlob *)blob)->bytes[((struct FontTableHeader *)blob)->tables[1]];
            if (D_80126F58[1] < 0x21) {
                count = D_80126F58[1] + 0x60;
            }
            _bcopy(copySource, D_80126FC8, count);
            ((struct FontTableHeader *)D_80126F58)->tables[1] = (u32)D_80126FC8;
        }
        if (((struct FontTableHeader *)blob)->tables[2] != 0) {
            _bcopy(&((struct FontTableBlob *)blob)->bytes[((struct FontTableHeader *)blob)->tables[2]], D_80127048, 0x53);
            ((struct FontTableHeader *)D_80126F58)->tables[2] = (u32)D_80127048;
        }
    }
    main_pool_pop_state(0x414E4B50);
    return D_80126F58;
}

s32 func_80046AC0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 result;
    u8 value;
    result = 1;
    if (arg1 != 0) {
        if (arg1 != 1) {
            result = 0;
        } else {
            value = arg0[0x7B];
            if (value < 3) {
                arg0[0x7B] = value + 1;
            } else {
                result = 0;
            }
        }
    }
    if (result) {
        (arg0 + arg0[0x7B])[0x74] = arg2;
    }
    return result;
}

void func_80046B14(u8 *arg0) {
    if (arg0[0x7B] > 0) {
        arg0[0x7B]--;
    }
}

extern s32 func_80047104(s32);
s32 func_80046B2C(u8 *state, s32 mode, s32 font) {
    s32 result;
    s32 index;
    result = 0;
    if (state != NULL) {
        index = func_80047104(font);
        if (((struct FontHeightRecord *)state)[index].data != 0) {
            result = func_80046AC0(state, mode, font);
            state[0x7A] &= ~2;
        }
    }
    return result;
}

#pragma pack(1)
struct PackedWord { s32 value; };
#pragma pack(0)
s32 func_80046BB4(u8 *arg0, s32 arg1, u8 *arg2) {
    s32 result;
    u8 value;
    result = 1;
    if (arg1 != 0) {
        if (arg1 != 1) {
            result = 0;
        } else {
            value = arg0[0x7C];
            if (value < 3) {
                arg0[0x7C] = value + 1;
            } else {
                result = 0;
            }
        }
    }
    if (result) {
        *(struct PackedWord *)((u8 *)arg0 + (arg0[0x7C] << 2) + 0x54) = *(struct PackedWord *)arg2;
    }
    return result;
}

extern Gfx * D_800D0510;
void func_80046C18(u8 *arg0) {
    struct { u8 r, g, b, a; } color;
    if (arg0[0x7C] > 0) {
        arg0[0x7C]--;
        *(u32 *)&color = ((u32 *)(arg0 + 0x54))[arg0[0x7C]];
        gDPPipeSync(D_800D0510++);
        gDPSetEnvColor(D_800D0510++, color.r, color.g, color.b, color.a);
    }
}

s32 func_80046CA8(u8 *state, s32 mode, s32 r, s32 g, s32 b, s32 a) {
    s32 result;
    struct { u8 r, g, b, a; } color;
    result = 0;
    if (state != NULL) {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
        if (*(u32 *)&color != ((u32 *)(state + 0x54))[state[0x7C]]) {
            result = func_80046BB4(state, mode, (u8 *)&color);
            if (result != 0) {
                gDPPipeSync(D_800D0510++);
                gDPSetEnvColor(D_800D0510++, color.r, color.g, color.b, color.a);
            }
        }
    }
    return result;
}

s32 func_80046D70(u8 *arg0, s32 arg1, u8 *arg2) {
    s32 result;
    u8 value;
    result = 1;
    if (arg1 != 0) {
        if (arg1 != 1) {
            result = 0;
        } else {
            value = arg0[0x7D];
            if (value < 3) {
                arg0[0x7D] = value + 1;
            } else {
                result = 0;
            }
        }
    }
    if (result) {
        *(struct PackedWord *)((u8 *)arg0 + (arg0[0x7D] << 2) + 0x64) = *(struct PackedWord *)arg2;
    }
    return result;
}

extern Gfx * D_800D0510;
void func_80046DD4(u8 *arg0) {
    struct { u8 r, g, b, a; } color;
    if (arg0[0x7D] > 0) {
        arg0[0x7D]--;
        *(u32 *)&color = ((u32 *)(arg0 + 0x64))[arg0[0x7D]];
        gDPPipeSync(D_800D0510++);
        gDPSetPrimColor(D_800D0510++, 0, 0, color.r, color.g, color.b, color.a);
    }
}

s32 func_80046E64(u8 *state, s32 mode, s32 r, s32 g, s32 b, s32 a) {
    s32 result;
    struct { u8 r, g, b, a; } color;
    result = 0;
    if (state != NULL) {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
        if (*(u32 *)&color != ((u32 *)(state + 0x64))[state[0x7D]]) {
            result = func_80046D70(state, mode, (u8 *)&color);
            if (result != 0) {
                gDPPipeSync(D_800D0510++);
                gDPSetPrimColor(D_800D0510++, 0, 0, color.r, color.g, color.b, color.a);
            }
        }
    }
    return result;
}

void func_80046F2C(u8 *arg0, s32 arg1) {
    arg0[0x79] = (u8)arg1;
}

extern u8 *D_80126F5C;
extern u8 *D_80126F60;
extern u8 *D_80126F64;
s32 func_80046F34(u16 arg0) {
    s32 result;
    s32 index;
    result = 0;
    arg0 &= 0x7F7F;
    arg0 &= 0xFFFF;
    if (arg0 >= 0x20 && arg0 < 0x80) { index = arg0 - 0x20; result = D_80126F5C[index]; }
    else if (arg0 >= 0x2120 && arg0 < 0x2180) { index = arg0 - 0x2120; result = D_80126F60[index]; }
    else if (arg0 >= 0x2330 && arg0 < 0x233A) result = arg0 - 0x2320;
    else if (arg0 >= 0x2341 && arg0 < 0x235B) result = arg0 - 0x2327;
    else if (arg0 >= 0x2361 && arg0 < 0x237B) result = arg0 - 0x22CC;
    else if (arg0 >= 0x2421 && arg0 < 0x2474) { index = arg0 - 0x2421; result = D_80126F64[index] + 0xAF; }
    else if (arg0 >= 0x2521 && arg0 < 0x2574) { index = arg0 - 0x2521; result = D_80126F64[index] + 0x45; }
    else if (arg0 == 0x2574) result = 0xFF;
    return result;
}

extern u8 * D_80126F5C;
extern u8 * D_80126F60;
s32 func_80047058(u16 arg0) {
    s32 result;
    s32 code;
    arg0 &= 0xFF;
    result = 0;
    code = arg0;
    if (arg0 >= 0x20 && arg0 < 0x80) {
        result = (D_80126F5C - 0x20)[arg0];
        goto done;
    }
    if (code >= 0x90 && code < 0x100) {
        result = (D_80126F60 - 0x90)[code];
    }
done:
    return result;
}

extern s32 func_80047058(u16);
extern s32 func_80046F34(u16 arg0);
s32 func_800470B8(u16 arg0) {
    s32 result;
    if (D_80126F58[0] == 0) {
        result = func_80046F34(arg0);
    } else {
        result = func_80047058(arg0);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047104.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80047158.s")

extern void *memcpy(void *, const void *, s32); void *func_800471B4(void *dest, const void *src, s32 size) { return (u8 *)memcpy(dest, src, size) + size; }

extern u16 D_80094FB4;
extern s32 func_8003514C(void);
s32 func_800471D8(u8 *font, s32 unused, u16 glyph) {
    s32 index;
    s32 width;

    index = func_800470B8(glyph);
    /* The font record stores its byte-width table pointer at +4. */
    width = *(u8 *)(index + *(s32 *)(font + 4));
    if (func_8003514C() == 0 && (D_80094FB4 & 1)) {
        width = *(s16 *)(font + 2);
    }
    return width;
}

struct FontHeightState {
    struct FontHeightRecord fonts[6];
    u8 unk48[0x2C];
    u8 fontStack[4];
    u8 attributes[8];
};
extern s32 func_80047104(s32);
s32 func_80047244(u8 *state, s32 font) {
    s32 index;
    struct FontHeightRecord *record;
    s32 result;
    result = 0;
    if (font == 0) {
        index = func_80047104(((struct FontHeightState *)state)->fontStack[state[0x7B]]);
    } else {
        index = func_80047104(font);
    }
    record = &((struct FontHeightState *)state)->fonts[index];
    if (record->data != 0) {
        result = record->height;
    }
    return result;
}

extern u8 *D_80126F50;
extern s32 func_80047244(u8 *, s32);
void func_800472B8(s32 arg0) {
    func_80047244(D_80126F50, arg0);
}

s32 func_800472E0(u8 *arg0) {
    s32 count;
    s32 value;
    u8 *next;

    count = 1;
    value = *arg0;
    next = arg0;
    next++;
    if (value != 0) {
        do {
            if (value == 10) {
                count++;
            }
            value = *next;
            next++;
        } while (value != 0);
    }
    return count;
}

s32 func_80047318(u8 *arg0)
{
  s32 var_v1;
  u8 new_var;
  u8 *var_a1;
  u8 temp_v0;
  var_v1 = 1;
  new_var = *arg0;
  var_a1 = arg0 + 1;
  if (new_var != 0)
  {
    do
    {
      temp_v0 = *var_a1;
      var_v1 += 1;
      var_a1 += 1;
    }
    while (temp_v0 != 0);
    if (!arg0)
    {
    }
  }
  return var_v1;
}

void func_80047348(s32 arg0, s32 arg1) {
    D_80126F50 = 0;
}

void Font_FreeSetAsset(s32 arg0, s32 arg1)
{
  s32 temp_v1;
  ;
  if (D_80126F50 != 0)
  {
    *((s32 *) (((u8 *) (D_80126F50 + ((arg1 * 6) * 2))) + 4)) = 0;
    *((s32 *) (((u8 *) (D_80126F50 + ((arg1 * 6) * 2))) + 8)) = 0;
  }
}

extern u8 *func_80047558(s32, s32);
extern u16 D_80126F5A;
extern u8 *main_pool_set_func(u8 *, s32, s32);
void func_80047398(s32 font, s32 width, s32 height) {
    s32 index;
    struct FontHeightRecord *record;
    u8 *data;

    index = func_80047104(font);
    record = &((struct FontHeightState *)D_80126F50)->fonts[index];
    if (record->data == NULL) {
        data = func_80047558(*(s32 *)(D_80126F50 + 0x48), font);
        record->unk00 = width;
        record->height = height;
        record->data = data;
        record->unk08 = D_80126F5A + (s32)data;
        main_pool_set_func(data, index, (s32)Font_FreeSetAsset);
        D_80126F50[0x7E] = font;
    }
}

extern void func_80047398(s32, s32, s32);
extern u8 * D_80126F50;
void func_80047444(s32 arg0) {
    if (D_80126F50 != NULL) {
        if (arg0 & 0x20) {
            func_80047398(0x20, 0x10, 0x10);
        }
        if (arg0 & 0x10) {
            func_80047398(0x10, 0x18, 0x18);
        }
        if (arg0 & 8) {
            func_80047398(8, 0x18, 0x14);
        }
        if (arg0 & 4) {
            func_80047398(4, 0x10, 0x10);
        }
        if (arg0 & 2) {
            func_80047398(2, 0x10, 0xC);
        }
        if (arg0 & 1) {
            func_80047398(1, 0x10, 0xA);
        }
    }
}

extern u32 D_446E30;
extern void *BinArchive_Open(void *, void *, s32, s32);
void *func_80047524(void) {
    return BinArchive_Open(&D_437750, &D_446E30, 1, 1);
}

extern void *func_80004B4C(s32, s32);
s32 func_80047104(s32);

u8 *func_80047558(s32 arg0, s32 arg1) {
    return func_80004B4C(arg0, func_80047104(arg1));
}

void func_80047670(void);
extern void _bzero(void *, s32);
extern s32 main_pool_alloc_with_func(s32, s32, s32, s32);
u8 *func_80047588(s32 flags, s32 side) {
    D_80126F50 = (u8 *)main_pool_alloc_with_func(0x80, side, 0x50524E54, (s32)func_80047348);
    if (D_80126F50 != NULL) {
        _bzero(D_80126F50, 0x80);
        func_80047670();
        *(void **)(D_80126F50 + 0x48) = func_80047524();
        func_80047444(flags);
        D_80094FB4 = 0;
    }
    return D_80126F50;
}

extern u8 *D_80126F50; void func_80047610(void) { main_pool_try_free(D_80126F50); }

extern u16 D_80094FB4;
void func_80047634(u16 arg0) { D_80094FB4 |= arg0; }

extern u16 D_80094FB4; void func_80047650(u16 arg0) { D_80094FB4 &= ~arg0; }


void func_80047670(void) {
    D_80126F50[0x7A] |= 4;
}

void Font_EnableLineBreak(void) { D_80126F50[0x7A] = (u8)(D_80126F50[0x7A] & ~4); }

extern void _bzero(void *, s32);
void func_800476A0(u8 *arg0, s32 arg1) {
    s32 index;

    for (index = 0; index < arg1; index++) {
        _bzero(arg0 + index * 0x10, 0x10);
    }
}

s32 func_800476FC(s32 arg0, s32 arg1) { s32 result = 0; if (arg1 > 0 && arg1 < 0x100 && D_80126F50 != NULL) { *(s32 *)(D_80126F50 + 0x50) = arg0; D_80126F50[0x7F] = arg1; result = 1; } return result; }

s32 func_80047738(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
  s32 temp_a0;
  s32 var_v1;
  void *temp_v0;
  var_v1 = 0;
  if (D_80126F50 != 0)
  {
    temp_a0 = *((s32 *) (((u8 *) D_80126F50) + 0x50));
    if (temp_a0 != 0)
    {
      temp_v0 = temp_a0 + (arg0 * 0x10);
      if (arg0 < ((s32) (*((u8 *) (((u8 *) D_80126F50) + 0x7F)))))
      {
        *((s32 *) (((u8 *) (temp_a0 + (arg0 * 0x10))) + 4)) = arg1;
        *((s32 *) (((u8 *) temp_v0) + 8)) = arg2;
        *((s32 *) (((u8 *) (temp_a0 + (arg0 * 0x10))) + 0xC)) = arg3;
        var_v1 = 1;
      }
    }
  }
  return var_v1;
}

s32 func_80047790(s32 arg0) {
    s32 var_v1;

    var_v1 = 0;
    if ((arg0 == 9) || (arg0 == 0x20) || (arg0 == 0x2C) || (arg0 == 0x3E)) {
        var_v1 = 1;
    }
    return var_v1;
}

u8 *func_800477C4(u8 *dest, u8 *input) {
    s32 character;
    u8 *output;
    u8 *cursor;
    s32 started;

    character = *input;
    output = dest;
    started = 0;
    cursor = input + 1;
    if (character != 0) {
        do {
            if (started == 0) {
                if (func_80047790(character) == 0) {
                    *output++ = character;
                    started = 1;
                }
            } else {
                if (func_80047790(character) != 0) {
                    break;
                }
                *output++ = character;
            }
        } while ((character = *cursor++) != 0);
    }
    *output = 0;
    return cursor;
}

extern s32 HAL_Strcmp(const s8 *, const s8 *);
s32 func_80047864(const s8 * arg0) {
    s32 result = 25;
    if (HAL_Strcmp(arg0, "FONT") == 0) {
        result = 0;
    }
    else if (HAL_Strcmp(arg0, "COL1") == 0) {
        result = 1;
    }
    else if (HAL_Strcmp(arg0, "COL2") == 0) {
        result = 2;
    }
    else if (HAL_Strcmp(arg0, "TEX") == 0) {
        result = 3;
    }
    else if (HAL_Strcmp(arg0, "LINE") == 0) {
        result = 4;
    }
    else if (HAL_Strcmp(arg0, "FACE") == 0) {
        result = 5;
    }
    else if (HAL_Strcmp(arg0, "DIST") == 0) {
        result = 6;
    }
    else if (HAL_Strcmp(arg0, "WAZA") == 0) {
        result = 7;
    }
    else if (HAL_Strcmp(arg0, "KOKA") == 0) {
        result = 8;
    }
    else if (HAL_Strcmp(arg0, "NEMURI") == 0) {
        result = 9;
    }
    else if (HAL_Strcmp(arg0, "DOKU") == 0) {
        result = 10;
    }
    else if (HAL_Strcmp(arg0, "DOKUDOKU") == 0) {
        result = 11;
    }
    else if (HAL_Strcmp(arg0, "YAKEDO") == 0) {
        result = 12;
    }
    else if (HAL_Strcmp(arg0, "KOHRI") == 0) {
        result = 13;
    }
    else if (HAL_Strcmp(arg0, "MAHI") == 0) {
        result = 14;
    }
    else if (HAL_Strcmp(arg0, "HIRUMI") == 0) {
        result = 15;
    }
    else if (HAL_Strcmp(arg0, "SHIBARI") == 0) {
        result = 16;
    }
    else if (HAL_Strcmp(arg0, "KONRAN") == 0) {
        result = 17;
    }
    else if (HAL_Strcmp(arg0, "MEROMERO") == 0) {
        result = 18;
    }
    else if (HAL_Strcmp(arg0, "NOROI") == 0) {
        result = 19;
    }
    else if (HAL_Strcmp(arg0, "AKUMU") == 0) {
        result = 20;
    }
    else if (HAL_Strcmp(arg0, "YADORIGI") == 0) {
        result = 21;
    }
    else if (HAL_Strcmp(arg0, "HARE") == 0) {
        result = 22;
    }
    else if (HAL_Strcmp(arg0, "AME") == 0) {
        result = 23;
    }
    else if (HAL_Strcmp(arg0, "SUNA") == 0) {
        result = 24;
    }
    return result;
}


extern s32 HAL_Strcmp(const s8 *, const s8 *);

s32 func_80047B4C(const s8 *arg0) {
    s32 result = -1;
    if (HAL_Strcmp(arg0, "LOAD") == 0) {
        result = 0;
    } else if (HAL_Strcmp(arg0, "PUSH") == 0) {
        result = 1;
    } else if (HAL_Strcmp(arg0, "POP") == 0) {
        result = 10;
    }
    return result;
}

s32 func_80047BD4(u8 *arg0) {
    u8 *p;
    u8 *start;
    s32 total;
    s32 place;

    total = 0;
    place = 1;
    p = arg0;
    start = arg0;
    while (*p != 0) {
        p++;
    }
    p--;
    while (start != p) {
        total += place * (*p - '0');
        place *= 10;
        p--;
    }
    if (*p == '-') {
        total = -total;
    } else {
        total += place * (*p - '0');
    }
    return total;
}

extern s32 func_80047158(s32);
extern void func_80046B14(u8 *arg0);
extern s32 func_80046B2C(u8 *, s32, s32);
extern u8 * func_800477C4(u8 *, u8 *);
extern s32 func_80047B4C(const s8 *arg0);
extern s32 func_80047BD4(u8 *arg0);
void func_80047D24(u8 *arg0, u8 *arg1) {
    u8 buffer[32];
    s32 mode;
    s32 value;

    arg1 = func_800477C4(buffer, arg1);
    if (arg0 != 0) {
        mode = func_80047B4C((const s8 *)buffer);
        switch (mode) {
        case 0:
        case 1:
            func_800477C4(buffer, arg1);
            value = func_80047158(func_80047BD4(buffer));
            if (value != 0) {
                func_80046B2C(arg0, mode, value);
            }
            break;
        case 10:
            func_80046B14(arg0);
            break;
        }
    }
}

extern u8 *func_800477C4(u8 *, u8 *);
extern s32 func_80046CA8(u8 *, s32, s32, s32, s32, s32);
extern void func_80046C18(u8 *);

void func_80047DC4(u8 *arg0, u8 *arg1) {
    u8 buffer[0x20];
    s32 type;
    u8 value3;
    u8 value2;
    u8 value1;

    arg1 = func_800477C4(buffer, arg1);
    type = func_80047B4C(buffer);

    switch (type) {
        case 0:
        case 1:
            arg1 = func_800477C4(buffer, arg1);
            value3 = func_80047BD4(buffer);

            arg1 = func_800477C4(buffer, arg1);
            value2 = func_80047BD4(buffer);

            arg1 = func_800477C4(buffer, arg1);
            value1 = func_80047BD4(buffer);

            arg1 = func_800477C4(buffer, arg1);
            func_80046CA8(arg0, type, value3, value2, value1, func_80047BD4(buffer) & 0xFF);
            break;

        case 10:
            func_80046C18(arg0);
            break;
    }
}

extern void Font_DisableTwoCycleTexturing(void);
extern void Font_EnableTwoCycleTexturing(void);
extern s32 func_80046E64(u8 *, s32, s32, s32, s32, s32);
extern u8 * func_800477C4(u8 *, u8 *);
extern s32 func_80047B4C(const s8 *arg0);
extern s32 func_80047BD4(u8 *arg0);
void func_80047EC4(u8 *arg0, u8 *arg1) {
    u8 buffer[0x20];
    s32 type;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u32 current;
    u8 color[4];

    arg1 = func_800477C4(buffer, arg1);
    type = func_80047B4C((s8 *)buffer);
    switch (type) {
        case 0:
        case 1:
            arg1 = func_800477C4(buffer, arg1);
            red = func_80047BD4(buffer);
            arg1 = func_800477C4(buffer, arg1);
            green = func_80047BD4(buffer);
            arg1 = func_800477C4(buffer, arg1);
            blue = func_80047BD4(buffer);
            arg1 = func_800477C4(buffer, arg1);
            alpha = func_80047BD4(buffer);
            if (func_80046E64(arg0, type, red, green, blue, alpha)) {
                current = ((u32 *)(arg0 + 0x54))[arg0[0x7C]];
                color[0] = red;
                color[1] = green;
                color[2] = blue;
                color[3] = alpha;
                if (arg0[0x7A] & 1) {
                    if (current == *(u32 *)color) {
                        Font_DisableTwoCycleTexturing();
                    }
                } else if (current != *(u32 *)color) {
                    Font_EnableTwoCycleTexturing();
                }
            }
            break;
        case 10:
            func_80046DD4(arg0);
            break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_8004803C.s")

extern s32 func_80047BD4(u8 *);
extern void func_80046F2C(u8 *, s32);
void func_80048188(u8 *arg0, u8 *arg1) { u8 temp[0x20]; func_800477C4(temp, arg1); func_80046F2C(arg0, func_80047BD4(temp)); }

extern s32 func_8003514C(void);
s32 func_800481C0(u8 *arg0, s32 value) { if (func_8003514C() != 0) value = 0; arg0[0x78] = value; return 1; }

extern s32 func_800481C0(u8 *, s32);
s32 func_800481FC(u8 *arg0, u8 *arg1) { u8 temp[0x20]; func_800477C4(temp, arg1); return func_800481C0(arg0, func_80047BD4(temp)); }

extern s16 D_80094FA0;
extern s16 D_80094FA4;
void func_80048234(u8 *text) {
    u8 buffer[0x20];

    text = func_800477C4(buffer, text);
    if (buffer[0] != 0) {
        D_80094FA0 = func_80047BD4(buffer);
    } else {
        D_80094FA0 = -1;
    }
    func_800477C4(buffer, text);
    if (buffer[0] != 0) {
        D_80094FA4 = func_80047BD4(buffer);
    } else {
        D_80094FA4 = -1;
    }
}

extern s16 D_80094FAC;
extern s16 D_80094FB0;
void func_800482C0(u8 *text) {
    u8 buffer[0x40];

    text = func_800477C4(buffer, text);
    if (buffer[0] != 0) {
        D_80094FB0 = func_80047BD4(buffer);
    } else {
        D_80094FB0 = 0;
    }
    func_800477C4(buffer, text);
    if (buffer[0] != 0) {
        D_80094FAC = func_80047BD4(buffer);
    } else {
        D_80094FAC = 0;
    }
}

extern s16 D_80094FAC;
extern u8 * func_800477C4(u8 *, u8 *);
extern s32 func_80047BD4(u8 *arg0);
void func_80048344(u8 *arg0) {
    u8 buffer[0x40];

    func_800477C4(buffer, arg0);
    if (buffer[0] != 0) {
        D_80094FAC = func_80047BD4(buffer);
    } else {
        D_80094FAC = 0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048830.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_80048E30.s")

extern s32 func_80049290(s32, s32, const char *);
extern s32 func_80048E30(u8 *, s32, s32, const char *, s32);
void func_80049064(s32 x, s32 y, s32 mode, const char *text) {
    u8 *state;
    state = D_80126F50;
    func_800472B8(((struct FontHeightState *)state)->fontStack[state[0x7B]]);
    switch (mode) {
    case 1:
    case 3:
        x -= func_80049290(((struct FontHeightState *)state)->fontStack[state[0x7B]], (s8)state[0x78], text) / 2;
        break;
    case 2:
    case 4:
        x -= func_80049290(((struct FontHeightState *)state)->fontStack[state[0x7B]], (s8)state[0x78], text);
        break;
    }
    func_80048E30(state, x, y, text, 1);
}

extern void *Util_Malloc(s32);
extern void Util_Free(void *);
extern s32 _Printf(void *(*)(void *, const void *, s32), void *, const char *, va_list);
extern s32 func_80048E30(u8 *, s32, s32, const char *, s32);
s32 func_80049148(s32 font, s32 flags, const char *format, ...) {
    const s32 renderFlag = 0;
    struct {
        char text[513];
        s32 width;
    } work;
    u8 *state;
    s32 length;
    s32 index;
    struct FontHeightRecord *record;
    char *text;
    va_list args;

    work.width = 0;
    if (D_80126F58[0] != 0) {
        flags = 0;
    }
    state = Util_Malloc(0x80);
    if (state == NULL) {
        return 0;
    }
    *(struct FontHeightState *)state = *(struct FontHeightState *)D_80126F50;
    if (font == 0) {
        font = ((struct FontHeightState *)state)->fontStack[state[0x7B]];
    } else {
        func_80046AC0(state, 0, font);
    }
    state[0x78] = flags;
    index = func_80047104(font);
    record = &((struct FontHeightState *)state)->fonts[index];
    if (record->data != NULL) {
        text = work.text;
        va_start(args, format);
        length = _Printf(func_800471B4, text, format, args);
        va_end(args);
        if (length > 0) {
            text[length] = 0;
            work.width = func_80048E30(state, 0, 0, text, renderFlag);
        }
    }
    Util_Free(state);
    return work.width;
}

extern void *Util_Malloc(s32);
extern void Util_Free(void *);
extern s32 func_80048E30(u8 *, s32, s32, const char *, s32);
s32 func_80049290(s32 font, s32 flags, const char *text) {
    u8 *state;
    s32 result;
    struct FontStateView {
        struct { s32 unk00, unk04, unk08; } fonts[6];
        u8 unk48[0x2C];
        u8 fontStack[4];
        u8 attributes[8];
    };

    result = 0;
    if (D_80126F58[0] != 0) {
        flags = 0;
    }
    state = Util_Malloc(0x80);
    if (state == 0) {
        return 0;
    }
    *(struct FontStateView *)state = *(struct FontStateView *)D_80126F50;
    if (font == 0) {
        font = ((struct FontStateView *)state)->fontStack[state[0x7B]];
    } else {
        func_80046AC0(state, 0, (s32)font);
    }
    state[0x78] = (u8)flags;
    if (((struct FontStateView *)state)->fonts[func_80047104((s32)font)].unk04 != 0) {
        result = func_80048E30(state, 0, 0, text, 0);
    }
    Util_Free(state);
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/47580/func_800493B0.s")

extern void func_800493B0(s32, s32, s32, const char *, va_list);
void func_800495BC(s32 arg0, s32 arg1, const char *arg2, ...) {
    void *args;
    if (arg2 != 0) {
        args = (void *)(&arg2 + 1);
        func_800493B0(arg0, arg1, 0, arg2, args);
    }
}

void func_800495F8(s32 x, s32 y, s32 mode, const char *format, ...) {
    va_list args;
    if (format != 0) {
        va_start(args, format);
        func_800493B0(x, y, mode, format, args);
        va_end(args);
    }
}

extern void func_80048830(u8 *, s32, s32, s32, s32);

void func_80049628(s32 arg0, s32 arg1, s32 arg2) {
    func_80048830(D_80126F50, arg0, arg1, arg2, 1);
}

s32 func_80049668(s32 value) { s32 result=0; if (D_80126F50 != NULL) result=func_800481C0(D_80126F50,value); return result; }

extern void func_800496D8(s32, s32);
extern s32 func_80049668(s32);
void func_800496A4(s32 a0, s32 a1) { func_800496D8(0, a0); func_80049668(a1); }

extern s32 func_80046B2C(u8 *, s32, s32);

void func_800496D8(s32 arg0, s32 arg1) {
    func_80046B2C(D_80126F50, arg0, arg1);
}

extern u8 *D_80126F50; void func_80049708(void) { func_80046B14(D_80126F50); }

extern void func_80049770(s32,s32,s32,s32,s32); void func_8004972C(s32 a0,s32 a1,s32 a2,s32 a3){func_80049770(0,a0,a1,a2,a3);}

void func_80049770(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_80046CA8(D_80126F50, arg0, arg1, arg2, arg3, arg4);
}

extern u8 *D_80126F50; void func_800497C0(void) { func_80046C18(D_80126F50); }

extern void func_80049828(s32, s32, s32, s32, s32);
void func_800497E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80049828(0, arg0, arg1, arg2, arg3);
}

extern s32 func_80046E64(u8 *, s32, s32, s32, s32, s32);
void func_80049828(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_80046E64(D_80126F50, arg0, arg1, arg2, arg3, arg4);
}

extern u8 *D_80126F50; void func_80049878(void) { func_80046DD4(D_80126F50); }

void func_8004989C(s32 arg0) {
    func_80046F2C(D_80126F50, arg0);
}

extern Gfx D_80094FB8[];
void func_800498C4(void) {
    s32 color;
    s32 i;
    s32 offset;
    u8 flags;

    flags = D_80126F50[0x7A];
    D_80126F50[0x7A] = 0;
    if (flags & 4) {
        func_80047670();
    }
    D_80126F50[0x79] = 0x28;
    *(s32 *)(D_80126F50 + 0x4C) = 0;
    D_80126F50[0x7B] = 0;
    func_80046AC0(D_80126F50, 0, D_80126F50[0x7E]);
    D_80126F50[0x7C] = 0;
    color = -1;
    func_80046BB4(D_80126F50, 0, (u8 *)&color);
    D_80126F50[0x7D] = 0;
    color = -1;
    func_80046D70(D_80126F50, 0, (u8 *)&color);
    if (*(u8 **)(D_80126F50 + 0x50) != NULL) {
        for (i = 0, offset = 0; i < D_80126F50[0x7F]; i++, offset += 0x10) {
            *(s32 *)(*(u8 **)(D_80126F50 + 0x50) + offset) = 0;
        }
    }
    gSPDisplayList(D_800D0510++, D_80094FB8);
}

extern u8 D_80094E38[];
extern u8 D_80095000[];
extern void Util_Free(void *);
extern void func_8004D19C(s32, s32, s32, s32, s32);
extern Gfx * D_800D0510;
extern u8 * D_80126F50;
void func_800499EC(void) {
    s32 i;
    s32 offset;
    u8 *group;
    u8 **link;
    u8 *node;
    void (*callback)(u8 *, u8 *);

    if (*(u8 **)(D_80126F50 + 0x50) != NULL) {
        gSPDisplayList(D_800D0510++, D_80094E38);
        for (i = 0, offset = 0; i < D_80126F50[0x7F]; i++, offset += 0x10) {
            group = *(u8 **)(D_80126F50 + 0x50) + offset;
            link = (u8 **)group;
            while (*link != NULL) {
                node = *link;
                if (*(u16 *)(node + 4) & 1) {
                    callback = *(void (**)(u8 *, u8 *))(group + 8);
                    if (callback != NULL) {
                        callback(group, node);
                    }
                    if (*(u16 *)(node + 4) & 2) {
                        func_8004D19C(*(s16 *)node, *(s16 *)(node + 2), *(s32 *)(group + 4), 0, 0);
                    }
                }
                link = (u8 **)(*link + 8);
                Util_Free(node);
            }
        }
    }
    gSPDisplayList(D_800D0510++, D_80095000);
}

extern u8 *D_80126F50; extern Gfx *D_800D0510; extern u8 D_80095018[];
void Font_EnableTwoCycleTexturing(void) {
    D_80126F50[0x7A] |= 1;
    D_80126F50[0x7A] &= 0xFFFD;
    gSPDisplayList(D_800D0510++, D_80095018);
}

extern u8 D_80095040[]; extern Gfx *D_800D0510;
void Font_DisableTwoCycleTexturing(void) { D_80126F50[0x7A] &= 0xFFFC; gSPDisplayList(D_800D0510++, D_80095040); }

extern u8 D_80095068[];
void func_80049BDC(void) {
    s32 color;

    D_80126F50[0x7D] = 0;
    color = -1;
    func_80046D70(D_80126F50, 0, (u8 *)&color);
    gSPDisplayList(D_800D0510++, D_80095068);
}

extern Gfx *D_800D0510;
extern u8 D_80095098[];
void Font_EndTexturedTextRendering(void) { Gfx *temp_v1 = D_800D0510++; temp_v1->words.w0 = 0xDE000000; temp_v1->words.w1 = (u32)D_80095098; }

extern u8 *func_80048390(u8 *, u8 *, s32 *, s32, s32);
void func_80049C70(s32 *first, s32 *second, u8 *text) {
    u8 *cursor;
    s32 character;

    if (first != NULL) {
        *first = 0;
    }
    if (second != NULL) {
        *second = 0;
    }
    character = *text;
    cursor = text + 1;
    if (character != 0) {
        do {
            switch (character) {
            case '<':
                cursor = func_80048390(NULL, cursor, NULL, 0, 0);
                if (first != NULL && D_80094FA0 != -1) {
                    *first = D_80094FA0;
                    D_80094FA0 = -1;
                }
                if (second != NULL && D_80094FA4 != -1) {
                    *second = D_80094FA4;
                    D_80094FA4 = -1;
                }
                break;
            default:
                if (D_80126F58[0] == 0 && character >= 0x80 && *cursor != 0) {
                    cursor += 1;
                }
                break;
            }
        } while ((character = *cursor++) != 0);
    }
}

extern s16 D_80094FA8;
void func_80049D9C(u8 *first, u8 *second, u8 *third, u8 *text) {
    u8 *cursor;
    s32 character;

    *first = 0;
    *second = 0;
    *third = 0;
    D_80094FA8 = 0;
    D_80094FAC = 0;
    D_80094FB0 = 0;
    character = *text;
    cursor = text + 1;
    if (character != 0) {
        do {
            switch (character) {
            case '<':
                cursor = func_80048390(NULL, cursor, NULL, 0, 0);
                *first = D_80094FA8;
                *second = D_80094FAC;
                *third = D_80094FB0;
                break;
            default:
                if (D_80126F58[0] == 0 && character >= 0x80 && *cursor != 0) {
                    cursor++;
                }
                break;
            }
        } while ((character = *cursor++) != 0);
    }
}
#endif
