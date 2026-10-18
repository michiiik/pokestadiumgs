#include "global.h"


#ifdef VERSION_US
/* Prefix of the 412-byte state allocated by func_88700364. */
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
    u8 unk_66[16];
    u8 error_flash, unk_77;
    s32 unk_78;
    s32 insert_sound, delete_sound, invalid_sound;
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88700080.s")

extern s32 func_88700080(void *);
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88700364.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/36/fragment36_code/func_88700C34.s")

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
