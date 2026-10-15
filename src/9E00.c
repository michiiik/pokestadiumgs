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

typedef struct {
    u8 threadAndStack[0x9CC];
    u16 *frameBuf;
    u16 width;
    u16 height;
} CrashScreenView;
extern u8 D_800D05B0[];
#define CRASH_SCREEN (*(CrashScreenView *)D_800D05B0)
extern u32 D_80087CA0[];
extern char *D_80087DA0[];
extern f32 func_80002090(void);
extern char D_800A1B44[];
extern char D_800A1B54[];
extern char D_800A1B74[];
extern char D_800A1B94[];
extern char D_800A1BB4[];
extern char D_800A1BD4[];
extern char D_800A1BF4[];
extern char D_800A1C14[];
extern char D_800A1C34[];
extern char D_800A1C54[];
extern char D_800A1C74[];
extern char D_800A1C94[];
extern char D_800A1CA8[];
extern char D_800A1CB4[];
extern char D_800A1CC0[];
void crash_screen_draw_rect(s32 x, s32 y, s32 width, s32 height) {
    u16* ptr;
    s32 i;
    s32 j;

    if (CRASH_SCREEN.width == (0x140 * 2)) {
        x <<= 1;
        y <<= 1;
        width <<= 1;
        height <<= 1;
    }

    ptr = CRASH_SCREEN.frameBuf + CRASH_SCREEN.width * y + x;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            *ptr = ((*ptr & 0xE738) >> 2) | 1;
            ptr++;
        }

        ptr += CRASH_SCREEN.width - width;
    }
}

void crash_screen_draw_glyph(s32 x, s32 y, s32 glyph) {
    s32 shift = ((glyph % 5) * 6);
    u32* data = &D_80087CA0[glyph / 5 * 7];
    s32 i;
    s32 j;

    if (CRASH_SCREEN.width == 320) {
        u16* ptr = CRASH_SCREEN.frameBuf + (CRASH_SCREEN.width) * y + x;

        for (i = 0; i < 7; i++) {
            u32 bit = 0x80000000U >> shift;
            u32 rowMask = *data++;

            for (j = 0; j < 6; j++) {
                *ptr++ = (bit & rowMask) ? 0xFFFF : 1;
                bit >>= 1;
            }

            ptr += CRASH_SCREEN.width - 6;
        }
    } else if (CRASH_SCREEN.width == (320 * 2)) {
        u16* ptr = (y * 0x500) + ((CrashScreenView *)D_800D05B0)->frameBuf + (x * 2);

        for (i = 0; i < 7; i++) {
            u32 bit = 0x80000000U >> shift;
            u32 rowMask = *data++;

            for (j = 0; j < 6; j++) {
                u16 temp = (bit & rowMask) ? 0xFFFF : 1;

                ptr[0] = temp;
                ptr[1] = temp;
                ptr[(320 * 2)] = temp;
                ptr[(320 * 2) + 1] = temp;
                ptr += 2;
                bit >>= 1;
            }

            ptr += (0x9E8 / 2);
        }
    }
}

extern void *memcpy(void *, const void *, s32); void *crash_screen_copy_to_buf(void *dest, const void *src, s32 size) { return (u8 *)memcpy(dest, src, size) + size; }

#include <stdarg.h>
extern u8 D_80087C20[];
extern s32 _Printf();
extern void crash_screen_draw_glyph(s32, s32, s32);
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
                crash_screen_draw_glyph(x, y, glyph);
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

void crash_screen_draw(OSThread* faultedThread) {
    s16 causeIndex;
    __OSThreadContext* ctx;
    u32 ret;

    ctx = &faultedThread->context;
    causeIndex = ((faultedThread->context.cause >> 2) & 0x1F);

    if (causeIndex == 23) {
        causeIndex = 16;
    }

    if (causeIndex == 31) {
        causeIndex = 17;
    }

    osWritebackDCacheAll();

    crash_screen_draw_rect(25, 20, 270, 25);
    crash_screen_printf(30, 25, D_800A1B44, faultedThread->id, D_80087DA0[causeIndex]);
    crash_screen_printf(30, 35, D_800A1B54, ctx->pc, ctx->sr, ctx->badvaddr);

    crash_screen_sleep(2000);

    osViBlack(0);
    osViSetYScale(func_80002090());
    osViRepeatLine(0);
    osViSwapBuffer(CRASH_SCREEN.frameBuf);

    crash_screen_draw_rect(25, 45, 270, 185);

    crash_screen_printf(30, 50, D_800A1B74, (u32)ctx->at, (u32)ctx->v0, (u32)ctx->v1);
    crash_screen_printf(30, 60, D_800A1B94, (u32)ctx->a0, (u32)ctx->a1, (u32)ctx->a2);
    crash_screen_printf(30, 70, D_800A1BB4, (u32)ctx->a3, (u32)ctx->t0, (u32)ctx->t1);
    crash_screen_printf(30, 80, D_800A1BD4, (u32)ctx->t2, (u32)ctx->t3, (u32)ctx->t4);
    crash_screen_printf(30, 90, D_800A1BF4, (u32)ctx->t5, (u32)ctx->t6, (u32)ctx->t7);
    crash_screen_printf(30, 100, D_800A1C14, (u32)ctx->s0, (u32)ctx->s1, (u32)ctx->s2);
    crash_screen_printf(30, 110, D_800A1C34, (u32)ctx->s3, (u32)ctx->s4, (u32)ctx->s5);
    crash_screen_printf(30, 120, D_800A1C54, (u32)ctx->s6, (u32)ctx->s7, (u32)ctx->t8);
    crash_screen_printf(30, 130, D_800A1C74, (u32)ctx->t9, (u32)ctx->gp, (u32)ctx->sp);
    crash_screen_printf(30, 140, D_800A1C94, (u32)ctx->s8, (u32)ctx->ra);

    crash_screen_print_fpcsr(ctx->fpcsr);

    crash_screen_print_fpr(30, 170, 0, &ctx->fp0.f.f_even);
    crash_screen_print_fpr(120, 170, 2, &ctx->fp2.f.f_even);
    crash_screen_print_fpr(210, 170, 4, &ctx->fp4.f.f_even);
    crash_screen_print_fpr(30, 180, 6, &ctx->fp6.f.f_even);
    crash_screen_print_fpr(120, 180, 8, &ctx->fp8.f.f_even);
    crash_screen_print_fpr(210, 180, 10, &ctx->fp10.f.f_even);
    crash_screen_print_fpr(30, 190, 12, &ctx->fp12.f.f_even);
    crash_screen_print_fpr(120, 190, 14, &ctx->fp14.f.f_even);
    crash_screen_print_fpr(210, 190, 16, &ctx->fp16.f.f_even);
    crash_screen_print_fpr(30, 200, 18, &ctx->fp18.f.f_even);
    crash_screen_print_fpr(120, 200, 20, &ctx->fp20.f.f_even);
    crash_screen_print_fpr(210, 200, 22, &ctx->fp22.f.f_even);
    crash_screen_print_fpr(30, 210, 24, &ctx->fp24.f.f_even);
    crash_screen_print_fpr(120, 210, 26, &ctx->fp26.f.f_even);
    crash_screen_print_fpr(210, 210, 28, &ctx->fp28.f.f_even);
    crash_screen_print_fpr(30, 220, 30, &ctx->fp30.f.f_even);

    ret = Memmap_GetLoadedFragmentVaddr(ctx->pc);
    if (ret != 0) {
        crash_screen_printf(120, 220, D_800A1CA8, ret - 0x20);
    }

    ret = Memmap_GetLoadedFragmentVaddr((u32)ctx->ra);
    if (ret != 0) {
        crash_screen_printf(210, 220, D_800A1CB4, ret - 0x20);
    }

    crash_screen_sleep(500);

    crash_screen_printf(210, 140, D_800A1CC0, *(u32*)(u32)ctx->pc);
}

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
extern void crash_screen_draw(OSThread *);
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
    crash_screen_draw(thread);
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

void crash_screen_printf_with_bg(s16 x, s16 y, const char* fmt, ...) {
    signed char* ptr;
    u32 glyph;
    s32 size;
    signed char buf[0x100];
    va_list args;

    va_start(args, fmt);

    size = _Printf(crash_screen_copy_to_buf, (char*)buf, fmt, args);

    if (size > 0) {
        crash_screen_draw_rect(x - 6, y - 6, (size + 2) * 6, 19);
        ptr = buf;

        while (size > 0) {
            glyph = D_80087C20[*ptr & 0x7F];

            if (glyph != 0xFF) {
                crash_screen_draw_glyph(x, y, glyph);
            }

            ptr++;
            size--;
            x += 6;
        }
    }

    va_end(args);
}
#endif
