#include "global.h"


#ifdef VERSION_US
void crash_screen_sleep(s32 ms) {
    u64 cycles = OS_USEC_TO_CYCLES(ms * 1000LL); // why not just do OS_NSEC_TO_CYCLES and not multiply by 1000LL?

    osSetTime(0);
    while (osGetTime() < cycles) {}
}

extern void *D_80087200;
extern u16 D_80087E00[];
extern void Cont_StartReadInputs(void);
extern void func_80005F0C(void);
void crash_screen_wait_for_button_combo(void) {
    s32 result = 0;
    s32 index = 0;
    u16 input;
    u16 expected;
    s32 match;
    do {
        Cont_StartReadInputs();
        func_80005F0C();
        input = *(u16 *)((u8 *)D_80087200 + 8);
        if (input != 0) {
            expected = (match = D_80087E00[index]);
            index++;
            match = expected == input;
            if (match != 0) {
                if (index == 10) {
                    result = 1;
                }
            } else {
                index = 0;
            }
        }
        crash_screen_sleep(10);
    } while (result == 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009384.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_8000948C.s")

extern void *memcpy(void *, const void *, s32); void *crash_screen_copy_to_buf(void *dest, const void *src, s32 size) { return (u8 *)memcpy(dest, src, size) + size; }

#include <stdarg.h>
extern u8 D_80087C20[];
extern s32 _Printf();
extern void func_8000948C(s32, s32, s32);
void crash_screen_printf(s32 x, s32 y, const char *fmt, ...) {
    signed char *ptr;
    s32 glyph;
    s32 size;
    signed char buf[0x100];
    va_list args;
    va_start(args, fmt);
    size = _Printf(crash_screen_copy_to_buf, (char *)buf, fmt, args);
    if (size > 0) {
        ptr = buf;
        while (size > 0) {
            glyph = D_80087C20[*ptr & 0x7F];
            if (glyph != 0xFF) {
                func_8000948C(x, y, glyph);
            }
            size--;
            ptr++;
            x += 6;
        }
    }
    va_end(args);
}

extern char D_800A1B14[];
extern char D_800A1B20[];
void crash_screen_print_fpr(s32 x, s32 y, s32 regNum, void* addr) {
    u32 bits;
    s32 exponent;

    bits = *(u32*)addr;
    exponent = ((bits & 0x7f800000U) >> 0x17) - 0x7f;
    if ((exponent >= -0x7e && exponent <= 0x7f) || bits == 0) {
        crash_screen_printf(x, y, D_800A1B14, regNum, *(f32*)addr);
    } else {
        crash_screen_printf(x, y, D_800A1B20, regNum);
    }
}

extern char D_800A1B30[];
extern char D_800A1B3C[];
extern s32 D_80087DE8[];
void crash_screen_print_fpcsr(u32 fpcsr) {
    s32 i;
    u32 bit = 1 << 17;
    crash_screen_printf(30, 155, D_800A1B30, fpcsr);
    for (i = 0; i < 6; i++) {
        if (fpcsr & bit) {
            crash_screen_printf(132, 155, D_800A1B3C, D_80087DE8[i]);
            break;
        }
        bit >>= 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009940.s")

OSThread* crash_screen_get_faulted_thread(void) {
    OSThread* thread = __osGetActiveQueue();

    while (thread->priority != -1) {
        if (thread->priority > 0 && thread->priority < 0x7F && (thread->flags & 3)) {
            return thread;
        }

        thread = thread->tlnext;
    }

    return NULL;
}

extern OSMesgQueue D_800D0F60;
extern OSThread *crash_screen_get_faulted_thread(void);
extern void crash_screen_wait_for_button_combo(void);
extern void func_80009940(OSThread *);
void crash_screen_thread_entry(void *arg0) {
    void *msg;
    OSThread *thread;
    osSetEventMesg(0xA, &D_800D0F60, 1);
    osSetEventMesg(0xC, &D_800D0F60, 2);
    for (;;) {
        osRecvMesg(&D_800D0F60, &msg, 1);
        thread = crash_screen_get_faulted_thread();
        if (thread != NULL) {
            break;
        }
    }
    osStopThread(thread);
    crash_screen_wait_for_button_combo();
    func_80009940(thread);
forever:
    goto forever;
}

extern u8 D_800D05B0[];
void func_80009EB4(s32 arg0, s32 arg1, s32 arg2) {
    s32 *arg1p = &arg1;
    s32 *arg2p = &arg2;
    *(s32 *)(D_800D05B0 + 0x9CC) = arg0 | 0xA0000000;
    *(s16 *)(D_800D05B0 + 0x9D0) = *arg1p;
    *(s16 *)(D_800D05B0 + 0x9D2) = *arg2p;
}

extern void *D_800D0F78;
extern s32 func_8000339C(void);
extern void crash_screen_thread_entry(void *);
void crash_screen_init(void) {
    s32 result;
    result = (func_8000339C() | 0xA0000000) + 0xFFFDA800;
    *(s32 *)(D_800D05B0 + 0x9CC) = result;
    *(s16 *)(D_800D05B0 + 0x9D0) = 0x140;
    *(s16 *)(D_800D05B0 + 0x9D2) = 0x10;
    osCreateMesgQueue(&D_800D0F60, &D_800D0F78, 1);
    osCreateThread((OSThread *)D_800D05B0, 2, crash_screen_thread_entry, NULL, &D_800D0F60, 0x80);
    osStartThread((OSThread *)D_800D05B0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009F80.s")
#endif
