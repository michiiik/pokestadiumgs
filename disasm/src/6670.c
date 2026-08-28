#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_80005A70.s")

typedef struct { u8 pad0[2]; s16 x; s16 y; u8 pad6[0xC]; s16 angle; f32 magnitude; f32 x_norm; f32 y_norm; } InputState_6670;
extern s16 MathUtil_Atan2s(f32, f32);
void func_80005B88(InputState_6670 *state) { s16 x; s16 y; f32 x_norm; f32 y_norm; f32 magnitude; f32 old_magnitude; f32 scale; x = state->x; state->x_norm = 0.0f; state->y_norm = 0.0f; if (x < -7) { state->x_norm = (f32)(x + 6); } if (x >= 8) { state->x_norm = (f32)(x - 6); } y = state->y; if (y < -7) { state->y_norm = (f32)(y + 6); } if (y >= 8) { state->y_norm = (f32)(y - 6); } x_norm = state->x_norm; y_norm = state->y_norm; magnitude = sqrtf((x_norm * x_norm) + (y_norm * y_norm)); state->magnitude = magnitude; if (magnitude > 64.0f) { scale = 64.0f / state->magnitude; state->magnitude = 64.0f; state->x_norm = x_norm * scale; state->y_norm = y_norm * scale; } if (state->magnitude > 0.0f) { state->angle = MathUtil_Atan2s(-state->y_norm, state->x_norm); } }

extern s16 D_80087210;
extern s16 D_80087214;
void func_80005CA4(void *arg0) {
    s32 result = 0;
    if (*(u16 *)((u8 *)arg0 + 8) & 0x800) { result = 0x800; *(s16 *)((u8 *)arg0 + 0xE) = D_80087210; }
    if (*(u16 *)((u8 *)arg0 + 8) & 0x400) { result = (result | 0x400) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087210; }
    if (*(u16 *)((u8 *)arg0 + 8) & 0x200) { result = (result | 0x200) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087210; }
    if (*(u16 *)((u8 *)arg0 + 8) & 0x100) { result = (result | 0x100) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087210; }
    if (*(u16 *)((u8 *)arg0 + 8) & 8) { result = (result | 8) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087210; }
    if (*(u16 *)((u8 *)arg0 + 8) & 4) { result = (result | 4) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087210; }
    if (*(u16 *)((u8 *)arg0 + 8) & 2) { result = (result | 2) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087210; }
    if (*(u16 *)((u8 *)arg0 + 8) & 1) { result = (result | 1) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087210; }
    *(s16 *)((u8 *)arg0 + 0xE) = *(s16 *)((u8 *)arg0 + 0xE) - 1;
    if (*(s16 *)((u8 *)arg0 + 0xE) <= 0) {
        *(s16 *)((u8 *)arg0 + 0xE) = 0;
        if (*(u16 *)((u8 *)arg0 + 6) & 0x800) { result = (result | 0x800) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087214; }
        if (*(u16 *)((u8 *)arg0 + 6) & 0x400) { result = (result | 0x400) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087214; }
        if (*(u16 *)((u8 *)arg0 + 6) & 0x200) { result = (result | 0x200) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087214; }
        if (*(u16 *)((u8 *)arg0 + 6) & 0x100) { result = (result | 0x100) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087214; }
        if (*(u16 *)((u8 *)arg0 + 6) & 8) { result = (result | 8) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087214; }
        if (*(u16 *)((u8 *)arg0 + 6) & 4) { result = (result | 4) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087214; }
        if (*(u16 *)((u8 *)arg0 + 6) & 2) { result = (result | 2) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087214; }
        if (*(u16 *)((u8 *)arg0 + 6) & 1) { result = (result | 1) & 0xFFFF; *(s16 *)((u8 *)arg0 + 0xE) = D_80087214; }
    }
    *(u16 *)((u8 *)arg0 + 0xC) = *(u16 *)((u8 *)arg0 + 8) | result;
}

extern void Cont_BlockEepromQueue(void); extern OSMesgQueue D_800CE100;
void Cont_StartReadInputs(void) { Cont_BlockEepromQueue(); osContStartReadData(&D_800CE100); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_80005F0C.s")

extern u8 D_800CE118; u8 func_800060E8(void) { return D_800CE118; }

void func_800060F4(s16 arg0, s16 arg1) { extern s16 D_80087210; extern s16 D_80087214; if (arg0 > 0) D_80087210 = arg0; if (arg1 > 0) D_80087214 = arg1; }

extern s16 D_80087210; extern s16 D_80087214; void func_8000612C(void) { D_80087210 = 10; D_80087214 = 2; }

void func_80006148(u8 *arg0) { *(u16 *)(arg0 + 0x10) |= 1; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_80006158.s")

s32 func_800061C4(void *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if ((*(*(u16 **)((u8 *)(arg0) + (0x20))) & 0x1F07) == 5) {
        var_v1 = 1;
    }
    return var_v1;
}

extern void *D_80087200;
s32 func_800061EC(void) {
    s32 var_a0;

    var_a0 = (func_800060E8() & 1) != 0;
    if (var_a0 != 0) {
        var_a0 = func_800061C4(D_80087200) != 0;
    }
    return var_a0;
}

extern u8 D_800CE119; s32 func_80006230(void) { return D_800CE119 != 0; }

extern void Cont_NoBlockEepromQueue(void);
s32 func_80006240(u8 *buffer, u32 size, s32 inaddr) {
    s32 result = 1;
    if (D_800CE119) {
        s32 i = 4;
        Cont_BlockEepromQueue();
        do {
            s32 count = size / 8;
            s32 address = (inaddr + 7) & ~7;
            i--;
            result = osEepromLongRead(&D_800CE100, count, buffer, address);
        } while (i > 0 && result);
        Cont_NoBlockEepromQueue();
    }
    return result;
}

s32 func_800062F8(u8 *buffer, u32 size, s32 inaddr) {
    s32 result = 1;
    if (D_800CE119) {
        s32 i = 4;
        Cont_BlockEepromQueue();
        do {
            s32 count = size / 8;
            s32 address = (inaddr + 7) & ~7;
            i--;
            result = osEepromLongWrite(&D_800CE100, count, buffer, address);
        } while (i > 0 && result);
        Cont_NoBlockEepromQueue();
    }
    return result;
}

void Cont_BlockEepromQueue(void) { extern OSMesgQueue D_800CE150; osRecvMesg(&D_800CE150, NULL, OS_MESG_BLOCK); }

void Cont_NoBlockEepromQueue(void) { extern OSMesgQueue D_800CE150; osSendMesg(&D_800CE150, NULL, OS_MESG_NOBLOCK); }

void Cont_InitEepromQueue(void) { extern OSMesgQueue D_800CE150; extern OSMesg D_800CE14C; osCreateMesgQueue(&D_800CE150, &D_800CE14C, 1); osSendMesg(&D_800CE150, NULL, OS_MESG_NOBLOCK); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_8000644C.s")
#endif
