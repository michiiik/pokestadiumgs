#include "global.h"


#ifdef VERSION_US
extern void func_88004990(u8, s32);
extern s32 D_880068B8;
extern u8 **D_88234990;

void func_882302C0(void) {
    func_88004990(**D_88234990, 0);
    D_880068B8 = 1;
}

extern void func_8000612C();

void func_882302F8(void) {
    func_8000612C();
    D_880068B8 = 0;
}

extern void func_88001900(void);
extern void func_88211168(s32, s8 *);
extern void func_887009A0(void);
extern void Util_Free(s32);
extern s32 D_880068B4;
extern s32 D_882346F4;

void func_8823031C(void) {
    func_88001900();
    D_880068B4 = 1;
    D_882346F4 = 0;
    if (*(s8 *)((u8 *)D_88234990 + 4) != 0) {
        func_88211168(1, (s8 *)D_88234990 + 4);
    }
    func_887009A0();
    Util_Free((s32)D_88234990);
}
extern void *Util_Malloc(s32);
extern void func_88700364(s32, void *, void (*)(void));
extern s16 func_887002F4(void);
extern s16 func_8870032C(void);
extern void func_88700CE4(void);
extern void func_88701240(void);
extern s32 func_88004804(s32, s32, s16, s16, s32, s32, s32, s32, s32,
                         void (*)(void), void (*)(void), void (*)(void),
                         void (*)(void), s32, s32);
extern u8 D_8800ED50[];

void func_88230384(void) {
    s32 result;
    s16 sp4A;
    s16 val2;

    D_88234990 = Util_Malloc(0x44);
    func_88700364(2, (u8 *)D_88234990 + 4, func_882302C0);
    sp4A = func_887002F4();
    val2 = func_8870032C();
    result = func_88004804(0, 3, sp4A, val2, 0, 1, 0xDC, 0xDC, 0xB4,
                           func_88700CE4, func_88701240, func_882302F8, func_8823031C, 0, 0);
    *D_88234990 = D_8800ED50 + (result * 0x4C);
    *(s16 *)((*D_88234990) + 0x10) = 0x181;
    *(s16 *)((*D_88234990) + 0x12) = 0x15C;
    D_880068B4 = 0;
    D_882346F4 = 1;
}
#endif
