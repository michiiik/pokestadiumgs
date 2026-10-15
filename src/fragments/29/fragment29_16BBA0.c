#include "global.h"


#ifdef VERSION_US
typedef struct {
    s32 mode;
    void *data;
    s16 count, limit;
    void (*update)(void), (*tick)(void), (*done)(void);
} F29Callbacks;
extern F29Callbacks D_8800EF50;
extern void Util_Free(void *);

extern s32 func_80001FF0(void);
void func_88005B60(s32 mode, void (*update)(void), void (*tick)(void), void (*done)(void)) {
    D_8800EF50.mode = mode;
    D_8800EF50.update = update;
    D_8800EF50.tick = tick;
    D_8800EF50.done = done;
    if (mode == 0) {
        D_8800EF50.count = 0;
        D_8800EF50.limit = D_8800EF50.count;
        D_8800EF50.data = 0;
    } else if (mode == 21) {
        D_8800EF50.count = 20;
        D_8800EF50.limit = D_8800EF50.count;
    } else {
        D_8800EF50.count = (u32)((f32)func_80001FF0() / 2);
        D_8800EF50.limit = D_8800EF50.count;
    }
}

void func_88005C7C(void) {
    if (((*(s16 *)((u8 *)(&D_8800EF50) + (8))) != 0) && ((*(s32 *)((u8 *)(&D_8800EF50) + (0))) != 0)) {
        (*(s32 (**)())((u8 *)(&D_8800EF50) + (0xC)))();
    }
}

s32 func_88005CC0(s32 mode, void *value) {
    s32 found = 0;

    if (D_8800EF50.count != 0) {
        if (mode == D_8800EF50.mode) {
            switch (mode) {
                case 1:
                    if ((*(s16 *)((u8 *)D_8800EF50.data+2)==*(s16 *)((u8 *)value+2)) && (*(s16 *)((u8 *)D_8800EF50.data+4)==*(s16 *)((u8 *)value+4))) found = 1;
                    break;
                case 2:
                    if ((*(s8 *)(u8 *)value==*(s8 *)D_8800EF50.data) || (*(s8 *)(u8 *)value==*((s8 *)D_8800EF50.data+1))) found = 1;
                    break;
                case 3:
                    if ((s32)value==*(s32 *)D_8800EF50.data || (s32)value==*((s32 *)D_8800EF50.data+1)) found = 1;
                    break;
                case 4:
                    if ((s32)value==*(s32 *)D_8800EF50.data || (s32)value==*((s32 *)D_8800EF50.data+1)) found = 1;
                    break;
                case 5:
                    if ((s32)value==*(s32 *)D_8800EF50.data) found = 1;
                    break;
                case 6:
                    if ((s32)value==*(s32 *)D_8800EF50.data || (s32)value==*((s32 *)D_8800EF50.data+1)) found = 1;
                    break;
                case 7:
                    if ((s32)value==*(s32 *)D_8800EF50.data || (s32)value==*((s32 *)D_8800EF50.data+1)) found = 1;
                    break;
                case 8:
                    if ((s32)value==*(s32 *)D_8800EF50.data) found = 1;
                    break;
                case 9:
                    if ((s32)value==*(s32 *)D_8800EF50.data) found = 1;
                    break;
                case 10:
                case 11:
                case 12:
                case 13:
                    if ((s32)value==*(s32 *)D_8800EF50.data || (s32)value==*((s32 *)D_8800EF50.data+1)) found = 1;
                    break;
                case 14:
                    if ((s32)value==*(s32 *)D_8800EF50.data || (s32)value==*((s32 *)D_8800EF50.data+1)) found = 1;
                    break;
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                    if ((s32)value==*(s32 *)D_8800EF50.data || (s32)value==*((s32 *)D_8800EF50.data+1)) found = 1;
                    break;
                case 20:
                    if ((*(s32 *)D_8800EF50.data==*(s32 *)(u8 *)value) && (*(s8 *)((u8 *)D_8800EF50.data+4)==*(s8 *)((u8 *)value+4))) found = 1;
                    break;
                case 21:
                    if ((*(s32 *)D_8800EF50.data==*(s32 *)(u8 *)value) && ((*(s8 *)((u8 *)value+8)==*(s8 *)((u8 *)D_8800EF50.data+8)) || (*(s8 *)((u8 *)value+8)==*(s8 *)((u8 *)D_8800EF50.data+9)))) found = 1;
                    break;
            }
        }
    }
    return found;
}

void func_88005F08(void) {
    if (D_8800EF50.count != 0) {
        if (D_8800EF50.mode != 0) D_8800EF50.tick();
        D_8800EF50.count--;
        if (D_8800EF50.count == 0) {
            if (D_8800EF50.mode != 0) {
                D_8800EF50.done();
                D_8800EF50.mode = 0;
            }
            Util_Free(D_8800EF50.data);
        }
    }
}
#endif
