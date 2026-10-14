#include "global.h"


#ifdef VERSION_US
typedef union {
    u16 halfwords[18];
    s32 words[9];
    s8 bytes[36];
    struct {
        u16 geometry[4];
        s16 selected;
        u16 last;
        s8 digits[8];
        s32 value;
    } numeric;
    struct {
        u16 fields[6];
        s16 cursor;
        s8 buffer[18];
        u16 capacity;
    } text;
} F77EditorState;

/* Existing suffix of D_8F80397C, across the aligned rodata boundary. */
const u32 D_8F803990[1] = { 0x32640000 };

extern Gfx *D_800D0510;
extern u8 D_80094DE0[];
void func_8F800020(s32 arg0, s32 arg1, s32 arg2) {
    gSPDisplayList(D_800D0510++, D_80094DE0);
    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, 0xFFC7FFC1);
    gDPFillRectangle(D_800D0510++, arg0, arg1, arg0 + arg2, arg1 + 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F8000D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F8006B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F800924.s")

extern F77EditorState D_8F809FC0;
extern s32 D_8F803470, D_8F803474;
extern void Ui_DrawGradientPanel(s32, s32, s32, s32, s32, s32);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_80049628(s32, s32, s32);
extern void func_800499EC(void);
extern void func_8F800020(s32, s32, s32);
void func_8F800E50(void) {
    s32 index;
    F77EditorState* state = &D_8F809FC0;

    Ui_DrawGradientPanel(state->numeric.geometry[0] - 10, state->numeric.geometry[1] - 10,
                         state->numeric.geometry[2] + 20, state->numeric.geometry[3] + 20,
                         (s32)&D_8F803470, (s32)&D_8F803474);
    func_800498C4();
    func_800496A4(4, 0);
    for (index = state->numeric.last; index >= 0; index--) {
        func_80049628(state->numeric.geometry[0] + (state->numeric.last - index) * 20,
                      state->numeric.geometry[1], state->numeric.digits[index] + 0x30);
    }
    func_800499EC();
    func_8F800020(state->numeric.geometry[0] + (state->numeric.last - state->numeric.selected) * 20,
                  state->numeric.geometry[1] + 18, 20);
}

void func_8F800F7C(void) {
    s32 index;
    F77EditorState* state = &D_8F809FC0;

    Ui_DrawGradientPanel(state->numeric.geometry[0] - 10, state->numeric.geometry[1] - 10,
                         state->numeric.geometry[2] + 20, state->numeric.geometry[3] + 20,
                         (s32)&D_8F803470, (s32)&D_8F803474);
    func_800498C4();
    func_800496A4(4, 0);
    for (index = state->numeric.last; index >= 0; index--) {
        if (state->numeric.digits[index] < 10) {
            func_80049628(state->numeric.geometry[0] + (state->numeric.last - index) * 20,
                          state->numeric.geometry[1], state->numeric.digits[index] + 0x30);
        } else {
            func_80049628(state->numeric.geometry[0] + (state->numeric.last - index) * 20,
                          state->numeric.geometry[1], state->numeric.digits[index] + 0x37);
        }
    }
    func_800499EC();
    func_8F800020(state->numeric.geometry[0] + (state->numeric.last - state->numeric.selected) * 20,
                  state->numeric.geometry[1] + 18, 20);
}

extern s32 D_8F809F98, D_8F809F9C, D_8F809FA4, D_8F809FB4;
extern u8 D_8F803E08;
extern u16 D_8F8034CC[][17];
extern char D_8F803478[][12], D_8F803848[][12];
extern char D_8F803954[], D_8F803964[], D_8F80396C[], D_8F803974[], D_8F80397C[];
extern u16 D_8F809FE6;
extern u8 D_8F809FE4, D_8F809FE8, D_8F809FE9, D_8F809FEA;
extern void func_800088DC(void);
extern void GfxImage_FillCurrent(Gfx**, u32);
extern void func_800495F8(s32, s32, s32, const char*, ...);
extern void func_800495BC(s32, s32, const char*, ...);
extern s32 func_8005D92C(s32);
extern s32 func_80057A80(s32);
extern void func_8F8000D0(void*, s32);
void func_8F8010E4(void) {
    s32 index;

    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 0x89);
    func_800498C4();
    func_800496A4(16, 0);
    func_800495F8(320, 30, 1, D_8F803954);
    func_800496A4(8, 0);
    func_800495BC(100, 400, D_8F803964,
                  D_8F809F9C ? (char*)&D_8F803E08 + D_8F809F9C * 0x6F8 - 0x14 : D_8F80396C,
                  D_8F809FA4 + 1);
    func_800495BC(100, 375, D_8F803974, (char*)D_8F803478 + func_8005D92C(D_8F809F98) * 12 - 12);
    if (!func_80057A80(D_8F809F98)) {
        func_800495BC(100, 350, D_8F80397C, (char*)D_8F803848 + (D_8F809FE6 % 7) * 12,
                      D_8F809FE8, D_8F809FE9, D_8F809FEA, D_8F809FE4 * 2);
    }
    for (index = 0; index < 23; index++) {
        func_8F8000D0(D_8F8034CC[index], index == D_8F809FB4);
    }
    func_800499EC();
}

extern s32 D_8F809F98, D_8F809F9C, D_8F809FA0, D_8F809FA4;
extern u8 *D_8F809FA8, *D_8F809FB0;
extern u8 D_8F803BF0, D_8F803BF4, D_8F803E08;
extern u8 *func_8006218C(s32, s32, s32, s32);
extern s32 func_80062390(void*, s32, u8*);
extern s32 func_80062304(u8*);
void func_8F8012C0(u8 slot) {
    u8* data;

    if (slot == 0) {
        data = func_8006218C(0x20, D_8F809F98, 0, 0);
        D_8F803BF0 = func_80062390(&D_8F803BF4, 6, data);
        D_8F809FA0 = D_8F803BF0;
        D_8F809FA8 = &D_8F803BF4;
    } else {
        data = func_8006218C(0x21, D_8F809F98, slot - 1, 0);
        *((u8*)&D_8F803E08 + slot * 0x6F8 - 0x6F8) =
            func_80062390((u8*)&D_8F803E08 + slot * 0x6F8 - 0x6F4, 30, data);
        D_8F809FA0 = *((u8*)&D_8F803E08 + slot * 0x6F8 - 0x6F8);
        D_8F809FA8 = (u8*)&D_8F803E08 + slot * 0x6F8 - 0x6F4;
    }
    func_80062304(data);
    D_8F809F9C = slot;
    D_8F809FA4 = 0;
    D_8F809FB0 = D_8F809FA8 + D_8F809FA4 * 0x58;
}

extern s32 D_8F809F98;
extern u16 D_8F809FF0;
extern u8 D_8F803BF0;
extern u8 D_8F803BF4;
extern void func_8005DAC8(s32, u16);
extern void func_8006249C(void *, s32, u8 *);
extern void func_8005B058(s32);
extern void func_80059468(s32);
extern s32 func_80062304(u8 *);
void func_8F8013FC(u8 arg0) {
    u8 *sp1C;

    func_8005DAC8(D_8F809F98, D_8F809FF0);
    if (arg0 == 0) {
        sp1C = func_8006218C(0x20, D_8F809F98, 0, 1);
        func_8006249C(&D_8F803BF4, (s32)D_8F803BF0, sp1C);
        func_8005B058(D_8F809F98);
    } else {
        sp1C = func_8006218C(0x21, D_8F809F98, arg0 - 1, 1);
        func_8006249C((u8 *)&D_8F803E08 + (s32)arg0 * 0x6F8 - 0x6F4,
                      *(u8 *)((u8 *)&D_8F803E08 + (s32)arg0 * 0x6F8 - 0x6F8),
                      sp1C);
        func_80059468(D_8F809F98);
    }
    func_80062304(sp1C);
}

extern s32 D_8F809FB4, D_8F809FB8;
extern void func_8F8015A8(void);
extern s32 func_8F801FC4(void);
extern void func_8F800924(void);
extern void func_8F801988(void);
extern void func_800226C0(s32);
void func_8F8014E4(void) {
    D_8F809FE4++;
    if (D_8F809FE4 >= 30) {
        D_8F809FE4 -= 30;
        D_8F809FEA++;
        if (D_8F809FEA >= 60) {
            D_8F809FEA -= 60;
            D_8F809FE9++;
            if (D_8F809FE9 >= 60) {
                D_8F809FE9 -= 60;
                D_8F809FE8++;
                if (D_8F809FE8 >= 24) {
                    D_8F809FE8 -= 24;
                    D_8F809FE6++;
                    D_8F809FE6 &= 0xFF;
                }
            }
        }
    }
}

extern s32 D_8F809FB4, D_8F809F9C;
extern u8 *D_8F809FB0;
extern u8 func_80073450(u8);
extern u8 func_800735A0(u8);
extern u8 func_80073540(u8);
extern void _bcopy(const void*, void*, s32);
extern s8 D_8F809FCE;
void func_8F8015A8(void) {
    s32 kind = D_8F8034CC[D_8F809FB4][0];
    s32 step;

    switch (kind) {
    case 1:
        D_8F809FC0.halfwords[6] = 10;
        D_8F809FC0.halfwords[7] = 14;
        D_8F809FC0.halfwords[4] = D_8F809F9C;
        D_8F809FC0.halfwords[5] = 0;
        break;
    case 3:
        D_8F809FC0.halfwords[6] = 10;
        D_8F809FC0.halfwords[7] = 253;
        D_8F809FC0.halfwords[4] = func_80073450(D_8F809FB0[0]);
        step = D_8F809FC0.halfwords[6];
        D_8F809FC0.halfwords[5] = ((s16*)D_8F809FC0.halfwords)[4] - step / 2;
        if (((s16*)D_8F809FC0.halfwords)[5] < 0) {
            D_8F809FC0.halfwords[5] = 0;
        }
        if (((s16*)D_8F809FC0.halfwords)[5] > D_8F809FC0.halfwords[7] - step + 1) {
            D_8F809FC0.halfwords[5] = D_8F809FC0.halfwords[7] - step + 1;
        }
        break;
    case 4:
        D_8F809FC0.halfwords[6] = 10;
        D_8F809FC0.halfwords[7] = 255;
        D_8F809FC0.halfwords[4] = func_800735A0(D_8F809FB0[1]);
        step = D_8F809FC0.halfwords[6];
        D_8F809FC0.halfwords[5] = ((s16*)D_8F809FC0.halfwords)[4] - step / 2;
        if (((s16*)D_8F809FC0.halfwords)[5] < 0) {
            D_8F809FC0.halfwords[5] = 0;
        }
        if (((s16*)D_8F809FC0.halfwords)[5] > D_8F809FC0.halfwords[7] - step + 1) {
            D_8F809FC0.halfwords[5] = D_8F809FC0.halfwords[7] - step + 1;
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        D_8F809FC0.halfwords[6] = 10;
        D_8F809FC0.halfwords[7] = 251;
        D_8F809FC0.halfwords[4] = func_80073540(*(D_8F809FB0 + kind - 3));
        step = D_8F809FC0.halfwords[6];
        D_8F809FC0.halfwords[5] = ((s16*)D_8F809FC0.halfwords)[4] - step / 2;
        if (((s16*)D_8F809FC0.halfwords)[5] < 0) {
            D_8F809FC0.halfwords[5] = 0;
        }
        if (((s16*)D_8F809FC0.halfwords)[5] > D_8F809FC0.halfwords[7] - step + 1) {
            D_8F809FC0.halfwords[5] = D_8F809FC0.halfwords[7] - step + 1;
        }
        break;
    case 9:
        D_8F809FC0.words[5] = *(u16*)(D_8F809FB0 + 6);
        break;
    case 16:
        D_8F809FC0.words[5] = *(u16*)(D_8F809FB0 + 22);
        break;
    case 22:
        D_8F809FC0.words[5] = D_8F809FB0[29];
        break;
    case 23:
        D_8F809FC0.words[5] = D_8F809FB0[32];
        break;
    case 24:
        D_8F809FC0.words[5] = *(u16*)(D_8F809FB0 + 38);
        break;
    case 25:
        D_8F809FC0.words[5] = *(u16*)(D_8F809FB0 + 40);
        break;
    case 26:
        D_8F809FC0.words[5] = *(u16*)(D_8F809FB0 + 42);
        break;
    case 27:
        D_8F809FC0.words[5] = *(u16*)(D_8F809FB0 + 44);
        break;
    case 28:
        D_8F809FC0.words[5] = *(u16*)(D_8F809FB0 + 46);
        break;
    case 29:
        D_8F809FC0.words[5] = *(u16*)(D_8F809FB0 + 48);
        break;
    case 30:
        D_8F809FC0.words[5] = *(u16*)(D_8F809FB0 + 50);
        break;
    case 31:
        _bcopy(D_8F809FB0 + 52, &D_8F809FCE, 12);
        D_8F809FC0.text.cursor = 0;
        break;
    case 32:
        _bcopy(D_8F809FB0 + 64, &D_8F809FCE, 12);
        D_8F809FC0.text.cursor = 0;
        break;
    case 21:
        D_8F809FC0.words[5] = D_8F809FB0[0x1C];
        break;
    case 33:
        D_8F809FC0.words[5] = D_8F809FF0;
        break;
    }
}

extern s32 D_8F809FB4, D_8F809F98, D_8F809FD4;
extern u16 D_8F8034CC[][17], D_8F809FD6, D_8F809FF0;
extern u8 D_8F809FC9;
extern u8 func_80073420(u8);
extern u8 func_80073570(u8);
extern u8 func_80073510(u8);
extern u8 func_80062E10(u8);
extern s32 func_80061B88(s32, u16);
extern void func_800619E8(u8*);
extern s32 func_800647C8(u8);
extern s8* HAL_Strcpy(s8*, s8*);
extern u16 func_80061ADC(s32, s32, u16, u16, u16);
extern s16 func_8006183C(s32, s32, s32, s32, s32);
extern u8* func_80060DDC(u8*, s8*);
extern void func_8F8012C0(u8);
void func_8F801988(void) {
    s32 value;
    s32 hp;

    switch (D_8F8034CC[D_8F809FB4][0]) {
    case 1:
        func_8F8012C0(D_8F809FC9);
        break;
    case 3:
        value = func_80073420(D_8F809FC9);
        if (value < 252 && (!func_80057A80(D_8F809F98) || value < 152)) {
            D_8F809FB0[0] = value;
            *(s32*)(D_8F809FB0 + 8) = func_80061B88(D_8F809FB0[0], D_8F809FB0[0x1D]);
            func_800619E8(D_8F809FB0);
            *(u16*)(D_8F809FB0 + 38) = *(u16*)(D_8F809FB0 + 40);
            HAL_Strcpy((s8*)(D_8F809FB0 + 0x34), (s8*)func_800647C8(D_8F809FB0[0]));
        }
        break;
    case 4:
        D_8F809FB0[1] = func_80073570(D_8F809FC9);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        value = func_80073510(D_8F809FC9);
        if (!func_80057A80(D_8F809F98) || value < 166) {
            *(D_8F809FB0 + D_8F8034CC[D_8F809FB4][0] - 3) = value;
            *(D_8F809FB0 + D_8F8034CC[D_8F809FB4][0] + 0x13) = func_80062E10(func_80073510(D_8F809FC9));
        }
        break;
    case 9:
        *(u16*)(D_8F809FB0 + 6) = D_8F809FD4;
        break;
    case 22:
        D_8F809FB0[0x1D] = D_8F809FC0.words[5];
        *(s32*)(D_8F809FB0 + 8) = func_80061B88(D_8F809FB0[0], D_8F809FC0.halfwords[11]);
        func_800619E8(D_8F809FB0);
        *(u16*)(D_8F809FB0 + 38) = *(u16*)(D_8F809FB0 + 40);
        break;
    case 23:
        D_8F809FB0[0x20] = D_8F809FD4;
        break;
    case 16:
        *(u16*)(D_8F809FB0 + 22) = D_8F809FD4;
        func_800619E8(D_8F809FB0);
        *(u16*)(D_8F809FB0 + 38) = *(u16*)(D_8F809FB0 + 40);
        break;
    case 24:
        hp = *(u16*)(D_8F809FB0 + 40);
        if (D_8F809FD4 < hp) {
            *(u16*)(D_8F809FB0 + 38) = D_8F809FD4;
        } else {
            *(u16*)(D_8F809FB0 + 38) = hp;
        }
        break;
    case 25:
        *(u16*)(D_8F809FB0 + 12) = func_80061ADC(0, D_8F809FB0[0], D_8F809FD6, D_8F809FB0[0x1D],
                                               *(u16*)(D_8F809FB0 + 22));
        *(u16*)(D_8F809FB0 + 40) = func_8006183C(0, D_8F809FB0[0], *(u16*)(D_8F809FB0 + 12),
                                               D_8F809FB0[0x1D], *(u16*)(D_8F809FB0 + 22));
        break;
    case 26:
        *(u16*)(D_8F809FB0 + 14) = func_80061ADC(1, D_8F809FB0[0], D_8F809FD6, D_8F809FB0[0x1D],
                                               *(u16*)(D_8F809FB0 + 22));
        *(u16*)(D_8F809FB0 + 42) = func_8006183C(1, D_8F809FB0[0], *(u16*)(D_8F809FB0 + 14),
                                               D_8F809FB0[0x1D], *(u16*)(D_8F809FB0 + 22));
        break;
    case 27:
        *(u16*)(D_8F809FB0 + 16) = func_80061ADC(2, D_8F809FB0[0], D_8F809FD6, D_8F809FB0[0x1D],
                                               *(u16*)(D_8F809FB0 + 22));
        *(u16*)(D_8F809FB0 + 44) = func_8006183C(2, D_8F809FB0[0], *(u16*)(D_8F809FB0 + 16),
                                               D_8F809FB0[0x1D], *(u16*)(D_8F809FB0 + 22));
        break;
    case 28:
        *(u16*)(D_8F809FB0 + 18) = func_80061ADC(3, D_8F809FB0[0], D_8F809FD6, D_8F809FB0[0x1D],
                                               *(u16*)(D_8F809FB0 + 22));
        *(u16*)(D_8F809FB0 + 46) = func_8006183C(3, D_8F809FB0[0], *(u16*)(D_8F809FB0 + 18),
                                               D_8F809FB0[0x1D], *(u16*)(D_8F809FB0 + 22));
        break;
    case 29:
        *(u16*)(D_8F809FB0 + 20) = func_80061ADC(4, D_8F809FB0[0], D_8F809FD6, D_8F809FB0[0x1D],
                                               *(u16*)(D_8F809FB0 + 22));
        *(u16*)(D_8F809FB0 + 48) = func_8006183C(4, D_8F809FB0[0], *(u16*)(D_8F809FB0 + 20),
                                               D_8F809FB0[0x1D], *(u16*)(D_8F809FB0 + 22));
        break;
    case 30:
        *(u16*)(D_8F809FB0 + 20) = func_80061ADC(5, D_8F809FB0[0], D_8F809FD6, D_8F809FB0[0x1D],
                                               *(u16*)(D_8F809FB0 + 22));
        *(u16*)(D_8F809FB0 + 50) = func_8006183C(5, D_8F809FB0[0], *(u16*)(D_8F809FB0 + 20),
                                               D_8F809FB0[0x1D], *(u16*)(D_8F809FB0 + 22));
        break;
    case 31:
        if (D_8F809FCE != 0) {
            _bcopy(D_8F809FC0.text.buffer, D_8F809FB0 + 0x34, 12);
        } else {
            HAL_Strcpy((s8*)(D_8F809FB0 + 0x34), (s8*)func_800647C8(D_8F809FB0[0]));
        }
        break;
    case 32:
        _bcopy(&D_8F809FCE, D_8F809FB0 + 0x40, 12);
        func_80060DDC(D_8F809FB0 + 0x4C, (s8*)(D_8F809FB0 + 0x40));
        break;
    case 21:
        D_8F809FB0[0x1C] = D_8F809FD4;
        break;
    case 33:
        D_8F809FF0 = D_8F809FD4;
        break;
    }
}

extern s32 D_8F809FB4;
void func_8F801F44(void) {
    D_8F809FC0.halfwords[0] = D_8F8034CC[D_8F809FB4][1];
    D_8F809FC0.halfwords[1] = D_8F8034CC[D_8F809FB4][2];
    D_8F809FC0.halfwords[2] = D_8F8034CC[D_8F809FB4][5] * 20;
    func_8F8015A8();
    D_8F809FC0.halfwords[3] = D_8F809FC0.halfwords[6] * 20;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F801FC4.s")

s32 func_8F8021E8(void) {
    s32 event;

    event = func_8F801FC4();
    func_8F800924();
    if (event == 1) {
        func_800226C0(2);
        if (((s16*)D_8F809FC0.halfwords)[4] < D_8F8034CC[D_8F809FB4][3]) {
            ((s16*)D_8F809FC0.halfwords)[4] = D_8F8034CC[D_8F809FB4][3];
        }
        if (((s16*)D_8F809FC0.halfwords)[4] > D_8F8034CC[D_8F809FB4][4]) {
            ((s16*)D_8F809FC0.halfwords)[4] = D_8F8034CC[D_8F809FB4][4];
        }
        func_8F801988();
        D_8F809FB8 = 0;
    } else if (event == 2) {
        func_800226C0(3);
        D_8F809FB8 = 0;
    }
    return 1;
}

extern u16 D_8F8034D6[][17];
void func_8F8022B4(void) {
    D_8F809FC0.halfwords[0] = 230;
    D_8F809FC0.halfwords[1] = 150;
    D_8F809FC0.halfwords[2] = 180;
    D_8F809FC0.halfwords[3] = 170;
    D_8F809FC0.halfwords[16] = D_8F8034D6[D_8F809FB4][0];
    D_8F809FC0.halfwords[4] = 0;
    D_8F809FC0.halfwords[5] = 0;
    func_8F8015A8();
}

void func_8F802324(u8 character) {
    s32 index;
    F77EditorState* state = &D_8F809FC0;

    if (state->text.cursor < state->text.capacity - 1) {
        for (index = state->text.capacity - 2; index > state->text.cursor; index--) {
            state->text.buffer[index] = state->text.buffer[index - 1];
        }
        state->text.buffer[state->text.cursor] = character;
        state->text.cursor++;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/77/fragment77_code/func_8F8023B8.s")

extern s32 func_8F8023B8(void);
extern s32 func_8F8006B0(void);
extern s32 D_8F809FB8;
s32 func_8F802670(void) {
    s32 sp1C;

    sp1C = func_8F8023B8();
    func_8F8006B0();
    if (sp1C == 1) {
        func_8F801988();
        D_8F809FB8 = 0;
    } else if (sp1C == 2) {
        func_800226C0(3);
        D_8F809FB8 = 0;
    }
    return 1;
}

void func_8F8026DC(void) {
    s32 value;
    s32 index;

    D_8F809FC0.halfwords[0] = D_8F8034CC[D_8F809FB4][1];
    D_8F809FC0.halfwords[1] = D_8F8034CC[D_8F809FB4][2];
    D_8F809FC0.halfwords[2] = D_8F8034CC[D_8F809FB4][5] * 20;
    D_8F809FC0.halfwords[3] = 20;
    D_8F809FC0.halfwords[4] = 0;
    D_8F809FC0.halfwords[5] = D_8F8034CC[D_8F809FB4][5] - 1;
    func_8F8015A8();
    value = ((s32*)D_8F809FC0.halfwords)[5];
    index = 0;
    if (index <= D_8F809FC0.halfwords[5]) {
        do {
            D_8F809FC0.bytes[index + 12] = value % 10;
            value /= 10;
            index++;
        } while (index <= D_8F809FC0.halfwords[5]);
    }
}

extern s32 D_80087200;
extern s32 Input_GetRepeatedDPad(void);
s32 func_8F8027C4(void) {
    s32 raw;
    s32 result = 0;
    s16 input;
    s32 buttons;
    u32 value;
    s32 index;
    F77EditorState* state = &D_8F809FC0;

    /* IDO schedules this conversion with the input call on the same source line. */
    raw = Input_GetRepeatedDPad(); input = raw;
    if (raw) {
        func_800226C0(1);
        switch (input) {
        case 0x200:
            state->numeric.selected++;
            if (state->numeric.selected > state->numeric.last) {
                state->numeric.selected = state->numeric.last;
            }
            break;
        case 0x100:
            state->numeric.selected--;
            if (state->numeric.selected < 0) {
                state->numeric.selected = 0;
            }
            break;
        case 0x800:
            state->numeric.digits[state->numeric.selected]++;
            if (state->numeric.digits[state->numeric.selected] >= 10) {
                state->numeric.digits[state->numeric.selected] = 0;
            }
            break;
        case 0x400:
            state->numeric.digits[state->numeric.selected]--;
            if (state->numeric.digits[state->numeric.selected] < 0) {
                state->numeric.digits[state->numeric.selected] = 9;
            }
            break;
        }
    }
    buttons = *(u16*)((u8*)(u32)D_80087200 + 8);
    if (buttons & 0x8000) {
        value = 0;
        for (index = state->numeric.last; index >= 0; index--) {
            value = value * 10 + state->numeric.digits[index];
        }
        state->numeric.value = value;
        result = 1;
    } else if (buttons & 0x4000) {
        result = 2;
    }
    return result;
}

extern s32 func_8F8027C4(void);
extern s32 func_8F802B40(void);
extern void func_8F800E50(void);
extern void func_8F800F7C(void);
s32 func_8F80299C(void) {
    s32 event;

    event = func_8F8027C4();
    func_8F800E50();
    if (event == 1) {
        func_800226C0(2);
        if (((s32*)D_8F809FC0.halfwords)[5] < D_8F8034CC[D_8F809FB4][3]) {
            ((s32*)D_8F809FC0.halfwords)[5] = D_8F8034CC[D_8F809FB4][3];
        }
        if (((s32*)D_8F809FC0.halfwords)[5] > D_8F8034CC[D_8F809FB4][4]) {
            ((s32*)D_8F809FC0.halfwords)[5] = D_8F8034CC[D_8F809FB4][4];
        }
        func_8F801988();
        D_8F809FB8 = 0;
    } else if (event == 2) {
        func_800226C0(3);
        D_8F809FB8 = 0;
    }
    return 1;
}

void func_8F802A68(void) {
    s32 value;
    s32 index;

    D_8F809FC0.halfwords[0] = D_8F8034CC[D_8F809FB4][1];
    D_8F809FC0.halfwords[1] = D_8F8034CC[D_8F809FB4][2];
    D_8F809FC0.halfwords[2] = D_8F8034CC[D_8F809FB4][5] * 20;
    D_8F809FC0.halfwords[3] = 20;
    D_8F809FC0.halfwords[4] = 0;
    D_8F809FC0.halfwords[5] = D_8F8034CC[D_8F809FB4][5] - 1;
    func_8F8015A8();
    value = ((s32*)D_8F809FC0.halfwords)[5];
    index = 0;
    if (index <= D_8F809FC0.halfwords[5]) {
        do {
            D_8F809FC0.bytes[index + 12] = value % 16;
            value /= 16;
            index++;
        } while (index <= D_8F809FC0.halfwords[5]);
    }
}

s32 func_8F802B40(void) {
    s32 raw;
    s32 result = 0;
    s16 input;
    s32 buttons;
    u32 value;
    s32 index;
    F77EditorState* state = &D_8F809FC0;

    /* IDO schedules this conversion with the input call on the same source line. */
    raw = Input_GetRepeatedDPad(); input = raw;
    if (raw) {
        func_800226C0(1);
        switch (input) {
        case 0x200:
            state->numeric.selected++;
            if (state->numeric.selected > state->numeric.last) {
                state->numeric.selected = state->numeric.last;
            }
            break;
        case 0x100:
            state->numeric.selected--;
            if (state->numeric.selected < 0) {
                state->numeric.selected = 0;
            }
            break;
        case 0x800:
            state->numeric.digits[state->numeric.selected]++;
            if (state->numeric.digits[state->numeric.selected] >= 16) {
                state->numeric.digits[state->numeric.selected] = 0;
            }
            break;
        case 0x400:
            state->numeric.digits[state->numeric.selected]--;
            if (state->numeric.digits[state->numeric.selected] < 0) {
                state->numeric.digits[state->numeric.selected] = 15;
            }
            break;
        }
    }
    buttons = *(u16*)((u8*)(u32)D_80087200 + 8);
    if (buttons & 0x8000) {
        value = 0;
        for (index = state->numeric.last; index >= 0; index--) {
            value = value * 16 + state->numeric.digits[index];
        }
        state->numeric.value = value;
        result = 1;
    } else if (buttons & 0x4000) {
        result = 2;
    }
    return result;
}

s32 func_8F802D0C(void) {
    s32 event;

    event = func_8F802B40();
    func_8F800F7C();
    if (event == 1) {
        func_800226C0(2);
        if (((s32*)D_8F809FC0.halfwords)[5] < D_8F8034CC[D_8F809FB4][3]) {
            ((s32*)D_8F809FC0.halfwords)[5] = D_8F8034CC[D_8F809FB4][3];
        }
        if (((s32*)D_8F809FC0.halfwords)[5] > D_8F8034CC[D_8F809FB4][4]) {
            ((s32*)D_8F809FC0.halfwords)[5] = D_8F8034CC[D_8F809FB4][4];
        }
        func_8F801988();
        D_8F809FB8 = 0;
    } else if (event == 2) {
        func_800226C0(3);
        D_8F809FB8 = 0;
    }
    return 1;
}

extern s32 D_8F809FB8, D_8F809FB4, D_8F809F9C;
extern void func_80064D28(void);
extern void func_80008648(void);
extern void func_8F8014E4(void);
extern void func_8F8010E4(void);
extern s32 func_8F802ECC(void);
extern s32 func_8F8021E8(void);
extern s32 func_8F80299C(void);
extern s32 func_8F802D0C(void);
extern s32 func_8F802670(void);
extern void func_8F801F44(void);
extern void func_8F8013FC(u8);
extern void func_8F802A68(void);
extern void func_8F8026DC(void);
extern void func_8F8022B4(void);
extern u8 D_8F809F9F;
s32 func_8F802DD8(void) {
    s32 result = 1;

    switch (D_8F8034CC[D_8F809FB4][0]) {
    case 0:
        result = 0;
        break;
    case 1:
        func_8F801F44();
        D_8F809FB8 = 4;
        break;
    case 2:
        func_8F8013FC(D_8F809F9F);
        break;
    case 3: case 4: case 5: case 6: case 7: case 8:
        func_8F801F44();
        D_8F809FB8 = 4;
        break;
    case 16:
        func_8F802A68();
        D_8F809FB8 = 2;
        break;
    case 9: case 21: case 22: case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 33:
        func_8F8026DC();
        D_8F809FB8 = 1;
        break;
    case 31: case 32:
        func_8F8022B4();
        D_8F809FB8 = 3;
        break;
    }
    return result;
}

extern s32 D_8F809FB4, D_8F809FA0, D_8F809FA4;
extern s32 func_8F802DD8(void);
s32 func_8F802ECC(void) {
    s32 result = 1;
    s32 input;
    s32 buttons;

    input = Input_GetRepeatedDPad();
    buttons = *(u16*)((u8*)(u32)D_80087200 + 8);
    if (buttons & 0x8000) {
        func_800226C0(2);
        result = func_8F802DD8();
    } else if (buttons & 0x4000) {
        func_800226C0(3);
        D_8F809FB4 = 0;
    } else if (input == 0x800) {
        func_800226C0(1);
        D_8F809FB4 = ((u8*)D_8F8034CC[D_8F809FB4])[12];
    } else if (input == 0x400) {
        func_800226C0(1);
        D_8F809FB4 = ((u8*)D_8F8034CC[D_8F809FB4])[13];
    } else if (input == 0x200) {
        func_800226C0(1);
        D_8F809FB4 = ((u8*)D_8F8034CC[D_8F809FB4])[14];
    } else if (input == 0x100) {
        func_800226C0(1);
        D_8F809FB4 = ((u8*)D_8F8034CC[D_8F809FB4])[15];
    } else {
        if (buttons & 8) {
            func_800226C0(1);
            D_8F809FA4--;
            if (D_8F809FA4 < 0) {
                if (D_8F809FA0 - 1 > 0) {
                    D_8F809FA4 = D_8F809FA0 - 1;
                } else {
                    D_8F809FA4 = 0;
                }
            }
            D_8F809FB0 = D_8F809FA8 + D_8F809FA4 * 0x58;
        } else if (buttons & 4) {
            func_800226C0(1);
            D_8F809FA4++;
            if (D_8F809FA4 >= D_8F809FA0) {
                D_8F809FA4 = 0;
            }
            D_8F809FB0 = D_8F809FA8 + D_8F809FA4 * 0x58;
        }
    }
    return result;
}

void func_8F803130(void) {
    s32 running = 0;

    do {
        func_80064D28();
        func_8F8014E4();
        func_8F8010E4();
        switch (D_8F809FB8) {
        case 0: running = func_8F802ECC(); break;
        case 4: running = func_8F8021E8(); break;
        case 1: running = func_8F80299C(); break;
        case 2: running = func_8F802D0C(); break;
        case 3: running = func_8F802670(); break;
        }
        func_80008648();
    } while (running);
}

extern u8 D_8F8044EC[];
extern u16 D_8F809FE6, D_8F809FF0;
extern void Input_SetRepeatController(s32);
extern s32 func_8005A134(s32);
extern void func_8005F37C(s32, s32, s32, s32, s32);
extern void *func_8005EE88(s32, s32, void*);
extern s32 func_8005DA1C(s32);
void func_8F8031F8(s32 id) {
    s32 index;

    D_8F809F98 = id;
    D_8F809FB4 = 1;
    D_8F809F9C = 0;
    D_8F809FA4 = 0;
    D_8F809FA0 = 0;
    D_8F809FA8 = &D_8F803BF4;
    D_8F809FB0 = D_8F809FA8 + D_8F809FA4 * 0x58;
    D_8F809FB8 = 0;
    Input_SetRepeatController(D_80087200);
    func_8005A134(D_8F809F98);
    func_8005F37C((u8)D_8F809F98, (s32)&D_8F809FE6, (s32)&D_8F809FE8, (s32)&D_8F809FE9, (s32)&D_8F809FEA);
    D_8F809FE4 = 0;
    func_8F8012C0((u8)D_8F809F9C);
    for (index = 0; index < 14; index++) {
        func_8005EE88(D_8F809F98, index, D_8F8044EC + index * 0x6F8);
    }
    D_8F809FF0 = func_8005DA1C(D_8F809F98);
}

extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern s32 func_8005D8C0(void);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern s32 func_80047588(s32, s32);
extern void func_8004C09C(s32);
extern void func_8004C4B0(s32);
extern void Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern void func_8F8031F8(s32);
extern void func_80057908(s32);
extern void func_80008514(s32);
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_8F803130(void);
extern void func_80008574(void);
extern void func_80047610(void);
extern void func_80057944(s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 D_8F809FEC;
extern s32 D_1000000;
extern u8 D_446E30[];
extern u8 D_447D00[];
s32 fragment77_main(s32 arg0, s32 arg1) {
    s32 sp24;

    main_pool_push_state(0x504D4544);
    if (!(func_8005D8C0() & 1)) {
        return 0;
    }
    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    D_8F809FEC = func_80047588(0x1E, 0);
    func_8004C09C(3);
    func_8004C4B0(6);
    func_8004C4B0(8);
    func_8004C4B0(0x41);
    Asset_LoadToSegment((((u32)&D_1000000) & 0x0F000000) >> 24,
                        &D_446E30, &D_447D00, 0);
    func_8F8031F8(0);
    func_80057908(0);
    func_80008514(sp24);
    func_800086A4(2);
    StageFade_StartFromOpaque(0x10);
    func_8F803130();
    func_80008574();
    func_80047610();
    func_80057944(0);
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x504D4544);
    return 0;
}
#endif
