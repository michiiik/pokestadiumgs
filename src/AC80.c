#include "global.h"


#ifdef VERSION_US
/* mkdraft:profiler_log_worker_time begin */
void profiler_log_worker_time(s32 arg0) {
    typedef struct {
        s16 count;
        u8 pad[6];
        OSTime times[4];
        u8 tail[0xA0];
    } ProfilerRecordWorker;
    extern u8 D_800D0F90;
    extern OSTime D_800CDA28;
    extern OSTime osGetTime(void);
    if (arg0 == 0) {
        ((ProfilerRecordWorker *)&D_800D0F90)[*(s16 *)((u8 *)&D_800D0F90 + 0x25A)].times[arg0] = D_800CDA28;
    } else {
        ((ProfilerRecordWorker *)&D_800D0F90)[*(s16 *)((u8 *)&D_800D0F90 + 0x25A)].times[arg0] = osGetTime();
    }
    if (arg0 == 3) {
        if (*(s16 *)((u8 *)&D_800D0F90 + 0x25A) == 2) {
            *(s16 *)((u8 *)&D_800D0F90 + 0x25A) = 0;
        } else {
            *(s16 *)((u8 *)&D_800D0F90 + 0x25A) += 1;
        }
        ((ProfilerRecordWorker *)&D_800D0F90)[*(s16 *)((u8 *)&D_800D0F90 + 0x25A)].count = 0;
    }
}
/* mkdraft:profiler_log_worker_time end */

extern u8 D_800D0F90;
extern OSTime osGetTime(void);
typedef struct {
    s16 count;
    u8 pad[0x46];
    OSTime times[8];
    u8 tail[0x40];
} ProfilerRecordA170;
void profiler_log_thread4_time(void) {
    ProfilerRecordA170 *record = (ProfilerRecordA170 *)&D_800D0F90;
    record += *(s16 *)((u8 *)&D_800D0F90 + 0x25A);
    if (record->count < 8) {
        record->times[record->count] = osGetTime();
        record->count++;
    }
}

extern u8 D_800D0F90;
extern OSTime osGetTime(void);
typedef struct {
    s16 pad0;
    s16 count;
    u8 pad[0x2C];
    OSTime times[8];
    u8 tail[0x58];
} ProfilerRecordA1E8;
OSTime profiler_log_gfx_time(s32 arg0) {
    OSTime time;
    if (arg0 == 0) {
        if (*(s16 *)((u8 *)&D_800D0F90 + 0x25C) == 2) {
            *(s16 *)((u8 *)&D_800D0F90 + 0x25C) = 0;
        } else {
            *(s16 *)((u8 *)&D_800D0F90 + 0x25C) += 1;
        }
        ((ProfilerRecordA1E8 *)&D_800D0F90 + *(s16 *)((u8 *)&D_800D0F90 + 0x25C))->count = 0;
    }
    time = osGetTime();
    ((ProfilerRecordA1E8 *)&D_800D0F90 + *(s16 *)((u8 *)&D_800D0F90 + 0x25C))->times[arg0] = time;
    return time;
}

extern u8 D_800D0F90;
extern OSTime osGetTime(void);
typedef struct {
    s16 pad0;
    s16 count;
    u8 pad[0x84];
    OSTime times[8];
} ProfilerRecord;
void profiler_log_vblank_time(void) {
    ProfilerRecord *record = (ProfilerRecord *)&D_800D0F90;
    record += *(s16 *)((u8 *)&D_800D0F90 + 0x25C);
    if (record->count < 8) {
        record->times[record->count] = osGetTime();
        record->count++;
    }
}

extern Gfx *D_800D0510;
void draw_profiler_rect(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 y;
    s32 y2;
    y2 = arg2 + 2;
    y = arg2;
    if (StageContext_IsHighResolution() != 0) {
        arg0 *= 2;
        arg1 *= 2;
        y = arg2 * 2;
        y2 *= 2;
    }
    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, ((u16)arg3 << 16) | (u16)arg3);
    gDPFillRectangle(D_800D0510++, arg0, y, arg1, y2);
}

void draw_profiler_bar_cpu(u64 start, u64 endA, u64 endB, s16 y, u16 color) {
    u64 first;
    u64 second;
    s32 x0;
    s32 x1;
    first = endA - start;
    if ((s64)first < 0) first = 0;
    second = endB - start;
    if ((s64)second < 0) second = 0;
    x0 = (((first * 64) / 3000) * 3) / 1000 + 30;
    x1 = (((second * 64) / 3000) * 3) / 1000 + 30;
    if (x0 >= 226) x0 = 225;
    if (x1 >= 226) x1 = 225;
    if (x0 < x1) draw_profiler_rect(x0, x1, y, color);
}

void draw_profiler_bar_cpu_keep_max(OSTime start, OSTime end, s16 posY, s16 *last_max, s16 *reset_ctr) {
    u64 duration;
    s32 ulx;
    s32 lrx;
    duration = end - start;
    if ((s64)duration < 0) duration = 0;
    lrx = (((duration * 64) / 3000) * 3) / 1000 + 30;
    if (lrx > 225) lrx = 225;
    if (++*reset_ctr > 15 || *last_max < lrx) {
        *reset_ctr = 0;
        *last_max = lrx;
    }
    lrx = *last_max;
    ulx = lrx - 4;
    if (ulx < 30) ulx = 30;
    if (ulx < lrx) draw_profiler_rect(ulx, lrx, posY, 0xA67F);
}

extern void draw_profiler_rect(s32, s32, s32, s32);
void draw_reference_profiler_bars(void) {
    draw_profiler_rect(0x1E, 0x4F, 0xDC, 0x2ABF);
    draw_profiler_rect(0x4F, 0x80, 0xDC, 0xFFCB);
    draw_profiler_rect(0x80, 0xB1, 0xDC, 0xFBCB);
    draw_profiler_rect(0xB1, 0xE2, 0xDC, 0xF94B);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000A730.s")

typedef struct ProfilerFrameDataAC80 {
    s16 numSoundTimes;
    s16 numVblankTimes;
    OSTime gameTimes[5];
    OSTime gfxTimes[3];
    OSTime soundTimes[8];
    OSTime vblankTimes[8];
} ProfilerFrameDataAC80;
extern u8 D_800D0F90;

void func_8000AA2C(void) {
    s32 i;
    ProfilerFrameDataAC80 *profiler =
        &(*(ProfilerFrameDataAC80 (*)[3])&D_800D0F90)[(*(s16 *)((u8 *)&D_800D0F90 + 0x25A) == 0) ? 2 : *(s16 *)((u8 *)&D_800D0F90 + 0x25A) - 1];
    OSTime clockStart = profiler->gameTimes[0] <= profiler->soundTimes[0] ? profiler->gameTimes[0] : profiler->soundTimes[0];
    OSTime gameDuration = profiler->gameTimes[1] - clockStart;
    OSTime renderDuration = profiler->gameTimes[2] - profiler->gameTimes[1];
    OSTime taskStart = 0;
    ProfilerFrameDataAC80 *profiler_2 =
        &(*(ProfilerFrameDataAC80 (*)[3])&D_800D0F90)[(*(s16 *)((u8 *)&D_800D0F90 + 0x25C) == 0) ? 2 : *(s16 *)((u8 *)&D_800D0F90 + 0x25C) - 1];
    OSTime rspDuration = profiler_2->gfxTimes[1] - profiler_2->gfxTimes[0];
    OSTime rdpDuration = profiler_2->gfxTimes[2] - profiler_2->gfxTimes[0];
    OSTime vblank = 0;
    static s16 sRenderLastMax = 0;
    static s16 sRenderResetCtr = 0;
    static s16 sRDPLastMax = 0;
    static s16 sRDPResetCtr = 0;

    profiler->numSoundTimes &= 0xFFFE;

    for (i = 0; i < profiler->numSoundTimes; i += 2) {
        u64 soundDuration = profiler->soundTimes[i + 1] - profiler->soundTimes[i];
        taskStart += soundDuration;
        if (profiler->soundTimes[i] < profiler->gameTimes[1]) {
            gameDuration -= soundDuration;
        } else if (profiler->soundTimes[i] < profiler->gameTimes[2]) {
            renderDuration -= soundDuration;
        }
    }

    profiler_2->numVblankTimes &= 0xFFFE;

    for (i = 0; i < profiler_2->numVblankTimes; i += 2) {
        vblank += (profiler_2->vblankTimes[i + 1] - profiler_2->vblankTimes[i]);
    }

    clockStart = 0;
    draw_profiler_bar_cpu(0, clockStart, clockStart + taskStart, 212, 0xF94B);

    clockStart += taskStart;
    draw_profiler_bar_cpu(0, clockStart, clockStart + gameDuration, 212, 0xFFCB);

    clockStart += gameDuration;
    draw_profiler_bar_cpu(0, clockStart, clockStart + renderDuration, 212, 0xFBCB);

    draw_profiler_bar_cpu_keep_max(0, clockStart + renderDuration, 212, &sRenderLastMax, &sRenderResetCtr);

    draw_profiler_bar_cpu(0, 0, rdpDuration, 216, 0xFBCB);

    draw_profiler_bar_cpu(0, 0, rspDuration, 216, 0xFFCB);

    draw_profiler_bar_cpu(0, 0, vblank, 216, 0xF94B);

    draw_profiler_bar_cpu_keep_max(0, rdpDuration, 216, &sRDPLastMax, &sRDPResetCtr);

    draw_reference_profiler_bars();
}
extern Gfx* D_800D0510;
void draw_profiler(s32 profiler_mode) {
    s32 ulx;
    s32 uly;
    s32 ulx_off;
    s32 uly_off;

    gDPPipeSync(D_800D0510++);
    gDPSetCycleType(D_800D0510++, G_CYC_FILL);
    gDPSetRenderMode(D_800D0510++, G_RM_NOOP, G_RM_NOOP2);

    ulx = 30;
    uly = 211;
    ulx_off = 196;
    uly_off = 9;

    if (StageContext_IsHighResolution() != 0) {
        ulx <<= 1;
        uly <<= 1;
        ulx_off <<= 1;
        uly_off <<= 1;
    }

    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, 0x00010001);
    gDPFillRectangle(D_800D0510++, ulx, uly, ulx + ulx_off, uly + uly_off);

    if (profiler_mode == 0) {
        func_8000AA2C();
    } else {
        func_8000A730();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/AC80/func_8000B0F0.s")

extern void _bzero(s32 *, s32);
extern u8 D_800D0F90;

void clear_profiler_data(void) {
    _bzero(&D_800D0F90, 0xC8);
    (*(s16 *)((u8 *)(&D_800D0F90) + (0x25A))) = 1;
    (*(s16 *)((u8 *)(&D_800D0F90) + (0x25C))) = 1;
}

/* mkdraft:func_8000B28C begin */
extern s16 D_80087E30;

void func_8000B28C(void) {
    *(OSTime *)&D_80087E30 = 0;
}
/* mkdraft:func_8000B28C end */

s16 D_80087E30 = 0;
s16 D_80087E34 = 0;
u32 func_8000B2A4(s32 arg0) {
    u32 ret = 0;
    static OSTime sBackupTime = 0ULL;

    switch (arg0) {
        case 1:
            sBackupTime = osGetTime();
            ret = 0;
            break;
        case 2:
            ret = OS_CYCLES_TO_USEC(osGetTime() - sBackupTime);
            break;
    }
    return ret;
}
#endif
