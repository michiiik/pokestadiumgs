#include "global.h"


#ifdef VERSION_US
extern void Input_SetRepeatController(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_88228A20(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

typedef struct {
    u8 unused[0x5C];
    u8 selected;
    u8 padding[3];
    void (*callback)(void);
} Cleanup_88228A48;
extern u32 D_88234890;
extern s32 D_880068B4;
extern void func_88001900(void);
extern void Util_Free(s32);
void func_88228A48(void) {
    Cleanup_88228A48 *state = (Cleanup_88228A48 *)D_88234890;

    if (state->selected != 0) {
        state->callback();
    } else {
        Input_SetRepeatController(D_80087200);
        func_88001900();
        D_880068B4 = 1;
    }
    Util_Free((s32)D_88234890);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19BCA0/func_88228AB4.s")

extern u32 D_88234890;
extern void func_8821D930(s32);
void func_88228BA4(void) {
    func_8821D930((D_88234890 + 4));
}

void func_88228A20(void);
void func_88228A48(void);
void func_88228BA4(void);
s32 func_8004C874(s32, s32);
s32 func_88002AA8(void *, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32 *);
s32 func_88004804(void *, s32, s16, s16, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *, s32, s32);
extern s32 D_88006020;
extern unsigned char D_8800ED50;
void func_88228A20(void);
void func_88228A48(void);
void func_88228AB4(void);
void func_88228BA4(void);

void func_88228BCC(s16 arg0, s16 arg1, s32 arg2)
{
  D_88234890 = Util_Malloc(0x64);
  *((s32 *) (((u8 *) D_88234890) + 0x54)) = func_8004C874(0x27, 7);
  *((s32 *) (((u8 *) D_88234890) + 0x58)) = func_8004C874(0x27, 8);
  func_88002AA8(D_88234890 + 0x20, 0, D_88234890 + 0x54, 2, 8, 1, 6, 0, 0, 0, 0, 0, 0, &D_88006020);
  *((s32 *) (((u8 *) D_88234890) + 0xC)) = func_8004C874(0x27, 0);
  *((s32 *) (((u8 *) D_88234890) + 8)) = 0;
  *((s32 *) (((u8 *) D_88234890) + 0x10)) = 4;
  *((s16 *) (((u8 *) D_88234890) + 0x14)) = 1;
  *((s16 *) (((u8 *) D_88234890) + 0x16)) = 4;
  *((void **) (((u8 *) D_88234890) + 0)) = (void *) ((func_88004804(D_88234890 + 4, 2, arg0, arg1, 4, 1, 0xDC, 0xDC, 0xB4, &func_88228AB4, &func_88228BA4, &func_88228A20, &func_88228A48, 0, 0) * 0x4C) + (&D_8800ED50));
  D_880068B4 = 0;
  *((s32 *) (((u8 *) D_88234890) + 0x60)) = arg2;
}
#endif
