#include "global.h"


#ifdef VERSION_US
typedef struct Fragment36Envelope {
    s16 tick, value, start, end;
    u8 delay, rise, hold, fall;
} Fragment36Envelope;

/* The 412-byte name-entry state allocated by func_88700364. */
typedef struct Fragment36NameEntry {
    s32 mode;
    u8 *output;
    u32 unk_08;
    s16 panel_x, panel_y;
    s16 entry_x, entry_y;
    u8 capacity;
    u8 unk_15;
    s16 cursor;
    u16 characters[32];
    s16 keyboard_column, keyboard_row;
    s16 keyboard_y;
    u8 keyboard_rows, unk_5F;
    u16 *keyboard;
    s16 slide_offset;
    s16 label_x, indicator_x;
    Fragment36Envelope pulse;
    u8 error_flash, unk_77;
    s32 unk_78;
    s32 insert_sound, delete_sound, invalid_sound;
    s32 confirm_sound;
    u16 keyboard_copy[135];
} Fragment36NameEntry;

extern Fragment36NameEntry *D_88701E00;
extern s32 func_80049290(s32, s32, const char *);
extern void func_80049628(s32, s32, s32);
extern void func_800226C0(s32);
extern void func_887009F0(void);
/* Center one glyph within a 16-pixel keyboard cell. */
void func_88700020(s32 x, s32 y, s32 character) {
    char text[2];
    s32 width;
    text[0] = character;
    text[1] = 0;
    width = func_80049290(4, 0, text);
    x += (16 - width) >> 1;
    func_80049628(x, y, character);
}


/* Advance a delay/rise/hold/fall cycle and return its rounded value. */
s16 func_88700080(Fragment36Envelope *envelope) {
    f32 bias;
    f32 delta;
    if (envelope->tick <= envelope->delay) {
        envelope->value = envelope->start;
    } else if (envelope->delay < envelope->tick && envelope->tick < envelope->delay + envelope->rise) {
        if (((f32)((envelope->end - envelope->start) * (envelope->tick - envelope->delay)) / envelope->rise) > 0.0f) {
            bias = 0.5f;
        } else {
            bias = -0.5f;
        }
        delta = (f32)((envelope->end - envelope->start) * (envelope->tick - envelope->delay)) / envelope->rise;
        envelope->value = (s32)(bias + delta) + envelope->start;
    } else if (envelope->delay + envelope->rise <= envelope->tick && envelope->tick <= envelope->delay + envelope->rise + envelope->hold) {
        envelope->value = envelope->end;
    } else {
        if (((f32)((envelope->start - envelope->end) * (envelope->tick - envelope->delay - envelope->rise - envelope->hold)) / envelope->fall) > 0.0f) {
            bias = 0.5f;
        } else {
            bias = -0.5f;
        }
        delta = (f32)((envelope->start - envelope->end) * (envelope->tick - envelope->delay - envelope->rise - envelope->hold)) / envelope->fall;
        envelope->value = (s32)(bias + delta) + envelope->end;
    }
    envelope->tick++;
    if (envelope->tick == envelope->delay + envelope->rise + envelope->hold + envelope->fall) {
        envelope->tick = 0;
    }
    return envelope->value;
}

void func_88700288(void *arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    *(s16 *)((u8 *)arg0 + 0) = arg1;
    *(s16 *)((u8 *)arg0 + 4) = arg2;
    *(s16 *)((u8 *)arg0 + 6) = arg3;
    *(u8 *)((u8 *)arg0 + 8) = arg4;
    *(u8 *)((u8 *)arg0 + 9) = arg5;
    *(u8 *)((u8 *)arg0 + 10) = arg6;
    *(u8 *)((u8 *)arg0 + 11) = arg7;
    func_88700080(arg0);
}

s32 func_887002F4(void) {
    s32 result;
    switch (D_88701E00->mode) {
        case 0: result = 0xA7; break;
        case 3: result = 0x81; break;
        default: result = 0x81; break;
    }
    return result;
}

s32 func_8870032C(void) {
    s32 result;
    switch (D_88701E00->mode) {
        case 0: result = 0x6B; break;
        case 3: result = 0x60; break;
        default: result = 0x5A; break;
    }
    return result;
}

extern s32 main_pool_push_state(s32);
extern void *Util_Malloc(s32);
extern s32 func_8004C4B0(s32);
extern s32 func_8004C8C0(u16);
extern s32 func_8003514C(void);
extern void _bcopy(void *, void *, s32);
extern void _bzero(void *, s32);
extern void *func_8004C874(s32, s32);
extern void func_8000612C(void);
extern s32 func_80001FF0(void);
extern u16 D_88701B00[], D_88701BD4[], D_88701CC4[];
extern u16 D_88701DD4[5];
/* Allocate the name-entry state and select its keyboard, sounds and pulse. */
void func_88700364(u32 mode, u8 *output, u32 callback) {
    s32 i;
    u16 *cell;
    s32 excluded_index;

    main_pool_push_state(0x4E414D45);
    D_88701E00 = Util_Malloc(sizeof(*D_88701E00));
    func_8004C4B0(36);
    func_8004C8C0(27);
    func_8004C8C0(29);
    func_8004C8C0(47);
    D_88701E00->mode = mode;
    D_88701E00->output = output;
    D_88701E00->unk_08 = callback;
    D_88701E00->panel_x = func_887002F4();
    D_88701E00->panel_y = func_8870032C();
    D_88701E00->keyboard_row = 0;
    D_88701E00->keyboard_column = D_88701E00->keyboard_row;
    switch (mode) {
    default:
        D_88701E00->entry_x = D_88701E00->panel_x + 31;
        D_88701E00->entry_y = D_88701E00->panel_y + 47;
        D_88701E00->capacity = 32;
        break;
    case 2:
        D_88701E00->entry_x = D_88701E00->panel_x + 111;
        D_88701E00->entry_y = D_88701E00->panel_y + 60;
        D_88701E00->capacity = 8;
        break;
    case 3:
        D_88701E00->entry_x = D_88701E00->panel_x + 101;
        D_88701E00->entry_y = D_88701E00->panel_y + 60;
        D_88701E00->capacity = 9;
        break;
    }
    if (mode == 3) {
        D_88701E00->unk_78 = 1;
        D_88701E00->insert_sound = 2;
        D_88701E00->delete_sound = 3;
        D_88701E00->invalid_sound = 5;
        D_88701E00->confirm_sound = 146;
    } else {
        D_88701E00->unk_78 = 70;
        D_88701E00->insert_sound = 63;
        D_88701E00->delete_sound = 64;
        D_88701E00->invalid_sound = 73;
        D_88701E00->confirm_sound = 98;
    }
    switch (func_8003514C()) {
    case 1:
        D_88701E00->keyboard_y = 127;
        D_88701E00->keyboard_rows = 7;
        D_88701E00->keyboard = D_88701B00;
        break;
    case 2:
    case 3:
        D_88701E00->keyboard_y = 119;
        D_88701E00->keyboard_rows = 8;
        D_88701E00->keyboard = D_88701BD4;
        break;
    case 4:
    case 5:
        D_88701E00->keyboard_y = 105;
        D_88701E00->keyboard_rows = 9;
        D_88701E00->keyboard = D_88701CC4;
        break;
    }
    if (mode == 2) {
        _bcopy(D_88701E00->keyboard, D_88701E00->keyboard_copy, D_88701E00->keyboard_rows * 30);
        D_88701E00->keyboard = D_88701E00->keyboard_copy;
        cell = D_88701E00->keyboard;
        for (i = 0; i < D_88701E00->keyboard_rows * 15; i++, cell++) {
            for (excluded_index = 4; excluded_index >= 0; excluded_index--) {
                if (*cell == D_88701DD4[excluded_index]) {
                    *cell = 32;
                    break;
                }
            }
        }
    }
    D_88701E00->slide_offset = D_88701E00->keyboard_y + D_88701E00->keyboard_rows * 16 + D_88701E00->keyboard_rows * 6 + 11;
    D_88701E00->indicator_x = 340 - func_80049290(4, 0, func_8004C874(36, 5));
    D_88701E00->label_x = D_88701E00->indicator_x - 18;
    D_88701E00->cursor = 0;
    _bzero(D_88701E00->characters, D_88701E00->capacity * 2);
    func_8000612C();
    /* Scale 60 Hz pulse durations to the TV rate, rounding to nearest. */
    func_88700288(&D_88701E00->pulse, 0, 255, 0,
        (s32)(((13.0f * (f32)func_80001FF0()) / 60.0f) + ((((13.0f * (f32)func_80001FF0()) / 60.0f) > 0.0f) ? 0.5f : -0.5f)),
        (s32)(((10.0f * (f32)func_80001FF0()) / 60.0f) + ((((10.0f * (f32)func_80001FF0()) / 60.0f) > 0.0f) ? 0.5f : -0.5f)),
        (s32)(((5.0f * (f32)func_80001FF0()) / 60.0f) + ((((5.0f * (f32)func_80001FF0()) / 60.0f) > 0.0f) ? 0.5f : -0.5f)),
        (s32)(((7.0f * (f32)func_80001FF0()) / 60.0f) + ((((7.0f * (f32)func_80001FF0()) / 60.0f) > 0.0f) ? 0.5f : -0.5f)));
    D_88701E00->error_flash = 0;
}

extern void main_pool_pop_state(s32);
void Util_Free(s32 arg0);
s32 func_8000204C(void);
void func_887009A0(void) {
    Util_Free((s32) D_88701E00);
    if (func_8000204C() == 0) {
        do {

        } while (func_8000204C() == 0);
    }
    main_pool_pop_state(0x4E414D45);
}

void func_887009F0(void) {
    D_88701E00->keyboard_column = 0;
    D_88701E00->keyboard_row = D_88701E00->keyboard_rows;
}

/* Fill empty positions before the cursor with spaces, then insert. */
void func_88700A10(u16 character) {
    s8 i;
    if (D_88701E00->characters[D_88701E00->capacity - 1] != 0 || D_88701E00->cursor == D_88701E00->capacity) {
        func_800226C0(D_88701E00->invalid_sound);
        D_88701E00->error_flash = 2;
    } else {
        func_800226C0(D_88701E00->insert_sound);
        for (i = 0; i < D_88701E00->cursor; i++) {
            if (D_88701E00->characters[i] == 0) {
                D_88701E00->characters[i] = 32;
            }
        }
        for (i = D_88701E00->capacity - 1; i > D_88701E00->cursor; i--) {
            D_88701E00->characters[i] = D_88701E00->characters[i - 1];
        }
        D_88701E00->characters[D_88701E00->cursor] = character;
        D_88701E00->cursor++;
        if (D_88701E00->cursor == D_88701E00->capacity) {
            func_887009F0();
        }
    }
}

/* Delete the nonempty character immediately before the cursor. */
void func_88700B58(void) {
    u8 i;
    if (D_88701E00->cursor == 0 || D_88701E00->characters[D_88701E00->cursor - 1] == 0) {
        func_800226C0(D_88701E00->invalid_sound);
    } else {
        func_800226C0(D_88701E00->delete_sound);
        for (i = D_88701E00->cursor - 1; i < D_88701E00->capacity - 1; i++) {
            D_88701E00->characters[i] = D_88701E00->characters[i + 1];
        }
        D_88701E00->characters[D_88701E00->capacity - 1] = 0;
        D_88701E00->cursor--;
    }
}

/* Encode nonzero character codes high byte first; wrap modes 0 and 1 every 16 characters. */
void func_88700C34(void) {
    u8 i;
    u16 *character;
    u8 *output;
    output = D_88701E00->output;
    i = 0;
    character = D_88701E00->characters;
    for (; i < D_88701E00->capacity; i++, character++) {
        if (*character == 0) {
            break;
        }
        switch (D_88701E00->mode) {
        case 0:
        case 1:
            if (i != 0 && (i & 15) == 0) {
                *output = 10;
                output++;
            }
            break;
        }
        if ((s32)*character >= 256) {
            *output = ((s32)*character >> 8) & 0xFF;
            output++;
        }
        *output++ = *character & 0xFF;
    }
    *output = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88700CE4.s")

s16 func_8870118C(s16 arg0) {
    return (s16) ((*(s16 *)((u8 *)(D_88701E00) + (0xC))) + (arg0 * 0x16) + ((arg0 / 13) * 0xC) + 0x17);
}

s16 func_887011E8(s16 arg0)
{
  return (s16) ((((*((s16 *) (((u8 *) D_88701E00) + 0xE))) + (*((s16 *) (((u8 *) D_88701E00) + 0x5C)))) + (arg0 * 0x16)) + ((arg0 / 5) * 4));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88701240.s")
#endif
