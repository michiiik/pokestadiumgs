#include "global.h"


#ifdef VERSION_US
extern s32 func_8003514C(void);
extern u8 D_80097380[];
extern u8 D_80097480[];
extern u8 D_80097580[];
extern u8 *D_80097680;
void func_800609D0(void) {
    s32 mode;
    mode = func_8003514C();
    switch (mode) {
    case 1:
        D_80097680 = D_80097380;
        break;
    case 2:
    case 3:
        D_80097680 = D_80097480;
        break;
    case 4:
    case 5:
        D_80097680 = D_80097580;
        break;
    }
}

u16 func_80060A4C(const u8 *arg0) { return (u16)((arg0[0] << 8) | arg0[1]); }

u32 GbData_ReadU24BE(const u8 *arg0) { return ((u32)arg0[0] << 16) | ((u32)arg0[1] << 8) | arg0[2]; }

void func_80060A84(u8* arg0, s32 arg1) { arg0[0] = (arg1 >> 8) & 0xFF; arg0[1] = arg1 & 0xFF; }

void GbData_WriteU24BE(u8 *arg0, s32 arg1) {
    arg0[0] = (arg1 >> 16) & 0xFF;
    arg0[1] = (arg1 >> 8) & 0xFF;
    arg0[2] = arg1 & 0xFF;
}

u8 func_80060AAC(u8 arg0) { extern u8 *D_80097680; return D_80097680[arg0]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060AC8.s")

s32 func_80060B28(u8 arg0) {
    u8 i;
    for (i = 0; i < 0x100; i++) {
        if (arg0 == D_80097680[i]) {
            return i;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060B74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060C08.s")

s8 *func_80060C50(s8 *arg0, u8 *arg1) {
    s8 *result;
    result = arg0;
    while (*arg1 != 0x50) {
        *arg0 = D_80097680[*arg1];
        arg0++;
        arg1++;
    }
    *arg0 = 0;
    return result;
}

extern u8 func_80060AC8(u8, s32);
s8 *func_80060C98(s8 *arg0, u8 *arg1, s32 arg2) {
    s8 *result;
    result = arg0;
    while (*arg1 != 0x50) {
        *arg0++ = func_80060AC8(*arg1++, arg2);
    }
    *arg0 = 0;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060D1C.s")

u8 *func_80060D70(u8 *arg0, s8 *arg1) {
    u8 *result;
    result = arg0;
    while (*arg1 != 0) {
        *arg0++ = func_80060B28(*arg1++);
    }
    *arg0 = 0x50;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060DDC.s")

extern void _bcopy(const void *, void *, s32);
extern void func_80060C08(void *, void *);
extern void func_80060D1C(void *, void *);
extern void func_80060EC8(void *, void *);
extern s32 func_8004B7A4(s32);
extern void func_80062808(void *, s32);
extern void func_80062884(void *, s32);
extern void func_80062978(void *, s32);
void func_80060E48(void *arg0, void *arg1) {
    u8 sp1C[11];
    _bcopy(arg1, sp1C, 0xA);
    sp1C[0xA] = 0x50;
    func_80060C08(arg0, sp1C);
}

void func_80060E88(void *arg0, void *arg1) {
    u8 sp1C[11];
    _bcopy(arg1, sp1C, 0xA);
    sp1C[0xA] = 0x50;
    func_80060D1C(arg0, sp1C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060EC8.s")

void func_80060EF8(void *arg0, void *arg1) {
    u8 sp1C[9];
    _bcopy(arg1, sp1C, 8);
    sp1C[8] = 0x50;
    func_80060C08(arg0, sp1C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060F38.s")

extern void HAL_Strcpy(void); void func_80060F68() { HAL_Strcpy(); }

s32 func_80060F88(void) { return 0x46; }

s32 func_80060F90(void) { return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060F98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060FF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061124.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061248.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800612B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006136C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800613F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800614EC.s")

void func_800615D0(void *arg0, void *arg1) {
    _bcopy(arg1, arg0, 0x24);
    _bcopy((u8 *)arg1 + 0x4C, (u8 *)arg0 + 0x30, 0xB);
    func_80060EC8((u8 *)arg0 + 0x24, (u8 *)arg1 + 0x34);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006162C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800616BC.s")

u16 StatExpSqrt(u16 arg0) { u16 i; for (i = 1; i < 255; i++) { if ((i * i) >= arg0) break; } return i; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006179C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006183C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061940.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800619E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061ADC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061B88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061D8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061ED0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061F44.s")

extern s32 _bcmp(const void *, const void *, s32); s32 GbSave_PlayerIdentityMatches(const void *a, const void *b) { return _bcmp(a, b, 0xD) == 0; }

extern u8 D_800976A0[]; u8 func_80061FD0(s32 index) { return D_800976A0[index]; }

extern u8 D_800976D7[];
s32 Species_ToInternalIndex(s32 index) { if (index <= 0 || index >= 0x98) return 0; return D_800976D7[index]; }

extern u8 D_8009776F[];
s32 func_80062008(s32 index) { if (index <= 0 || index >= 0xBF) return 0xFC; return D_8009776F[index]; }

s32 func_80062030(s32 value) { if (value > 0 && value < 0xFC) return value; return 0xFC; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800620E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006218C.s")

typedef struct S1_DeckHandle {
    /* 0x00 */ u8 mode; // func_8006218C's arg3; ==1 selected by Deck_Initialize*Backend to reset the entry count
    /* 0x01 */ u8 deckType; // func_8006218C's arg0; high nibble dispatches Deck_InitializeSaveBackend(0x10)/InitializeBoxBackend(0x20)
    /* 0x02 */ u8 port; // func_8006218C's arg1
    /* 0x03 */ u8 slot; // func_8006218C's arg2 (box/save-record index)
    /* 0x04 */ u8 dirty; // bit 0 set when the deck was modified; checked by Deck_CloseAndFlush/CloseAndFlushBox to decide whether to commit
    /* 0x05 */ u8 recordSize; // Deck_GetSaveRecordSize/Deck_GetEntrySize
    /* 0x06 */ s16 capacity; // Deck_GetSaveRecordCapacity/Deck_GetCapacity
    /* 0x08 */ s16 count; // Deck_GetSaveEntryCount/Deck_GetCount
    /* 0x0A */ s16 cursor; // Deck_SetCursor
} S1_DeckHandle;
S1_DeckHandle* Deck_OpenAndSetName(s32 arg0, s32 arg1, s32 arg2, s32 arg3, char* arg4, u16 arg5) {
    S1_DeckHandle* sp24;
    S1_DeckHandle* temp_v0;
    S1_DeckHandle* var_v1;

    sp24 = func_8006218C(arg0, arg1, arg2, 1);
    if ((sp24 != NULL) && (arg0 & 0xF0)) {
        func_800535D4(arg0, arg2, arg3, arg4, arg5);
    }
    return sp24;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006229C.s")

extern s32 func_80051D64(s32, s32);
extern void Util_Free(void *);
s32 func_80062304(u8 *arg0) { s32 result = 0; if ((arg0[1] & 0x10) && (arg0[4] & 1)) { func_80051D64(arg0[1], arg0[3]); result = 1; } Util_Free(arg0); return result; }

s32 func_8006236C(u8 *arg0, s32 arg1) { s32 result = 0; if (arg0[5] >= arg1) { *(u16 *)(arg0 + 10) = arg1; result = 1; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006249C.s")

s32 func_800625E0(s32 arg0, s32 arg1) {
    extern void func_80060F68();
    func_80060F68(arg0, func_8004B7A4(arg1));
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062614.s")

void func_8006276C(s32 arg0, s32 arg1) {
    s32 pad_frame[2];
    s32 sp24;

    func_80060EC8(&sp24, arg1 + 0x66);
    _bcopy(arg1 + 0x44, (void *) arg0, 0x21);
    _bcopy(&sp24, arg0 + 0x21, 8);
    _bcopy(arg1 + 0x42, arg0 + 0x29, 2);
    func_80060A84(arg0 + 0x2B, (s32) (*(u16 *)((u8 *)(arg1) + (0x72))));
    (*(u8 *)((u8 *)(arg0) + (0x2D))) = (u8) (*(u8 *)((u8 *)(arg1) + (0x74)));
    (*(u8 *)((u8 *)(arg0) + (0x2E))) = (u8) (*(u8 *)((u8 *)(arg1) + (0x75)));
}

void func_800627F0(s32 arg0, s32 arg1) {}

void func_800627FC(s32 arg0, s32 arg1) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062808.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062884.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062978.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062BD4.s")

s32 func_80062C18(s32 arg0) { return 1; }

s32 func_80062C24(s32 arg0) { return 1; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062C30.s")
#endif
