#include "global.h"


#ifdef VERSION_US
#define ALIGN16(val) (((val) + 0xFu) & ~0xFu)
typedef struct S1_UnkStruct80001380 S1_UnkStruct80001380;
struct S1_UnkStruct80001380 {
    OSMesg mesg;
    OSMesgQueue queue;
    u16 state;
    u16 notifyFlag;
    OSTask task;
    char unk60[0x8];
};
typedef unsigned int S1_uintptr_t;
extern u64 D_800AB4A0[0x100 / sizeof(u64)];
extern u64 D_800A63D0[];
extern u64 D_800A7A00[];
extern u64 D_800AB5A0[0x1];
extern u64 D_800AB9A8[0x1];
extern u64 D_800AC5B0[0x1];
extern u64 D_800CC5B0[];
void DisplayTask_Initialize(S1_UnkStruct80001380* arg0) {
    arg0->task.t.type = M_GFXTASK;
    arg0->task.t.flags = 0;
    arg0->task.t.ucode_boot = D_800AB4A0;
    arg0->task.t.ucode_boot_size = 0x100;
    arg0->task.t.ucode = D_800A63D0;
    arg0->task.t.ucode_data = D_800A7A00;
    arg0->task.t.ucode_size = 0x1000;
    arg0->task.t.ucode_data_size = 0x800;
    arg0->task.t.dram_stack = (void*)ALIGN16((S1_uintptr_t)D_800AB5A0);
    arg0->task.t.dram_stack_size = 0x400;
    arg0->task.t.yield_data_ptr = (void*)ALIGN16((S1_uintptr_t)D_800AB9A8);
    arg0->task.t.yield_data_size = 0xC00;
    arg0->task.t.output_buff = (D_800AC5B0);
    arg0->task.t.output_buff_size = D_800CC5B0;
    osCreateMesgQueue(&arg0->queue, &arg0->mesg, 1);
}
#endif

#ifdef VERSION_US

extern void Sched_SubmitTask(void *, s32);
void func_80001684(void *arg0, void *arg1, s32 arg2) {
    *(u32 *)((u8 *)arg0 + 0x50) = *(u32 *)((u8 *)arg1 + 4);
    *(u32 *)((u8 *)arg0 + 0x54) = *(u32 *)((u8 *)arg1 + 8);
    Sched_SubmitTask(arg0, arg2);
}
#endif

#ifdef VERSION_US

extern s32 osTvType;
extern u8 D_800871D4[];
extern OSViMode osViModeTable[];
extern f32 D_800A17F0;
extern u8 leoDiskID[];

void Vi_SelectMode(s8 arg0, s8 arg1) {
    s32 index;
    if (osTvType == 2) {
        index = (arg0 << 1) + arg1 + 8;
    } else {
        index = (arg0 << 1) + arg1 + 4;
    }
    osViSetMode(&osViModeTable[D_800871D4[index]]);
    osViSetSpecialFeatures(0x40);
    osViSetSpecialFeatures(2);
    osViSetSpecialFeatures(0x10);
    if (osTvType == 0) {
        *(f32 *)(leoDiskID + 0xA8C) = D_800A17F0;
        osViSetYScale(*(f32 *)(leoDiskID + 0xA8C));
    }
}
#endif

#ifdef VERSION_US

void func_8000177C(u8 *arg0) {
    if (arg0 == NULL) {
        *(s32 *)(leoDiskID + 0xA94) = 0;
        *(s32 *)(leoDiskID + 0xA98) = 0;
        *(s32 *)(leoDiskID + 0xA9C) = 0;
        leoDiskID[0xA91] = leoDiskID[0xAA1];
        leoDiskID[0xA92] = leoDiskID[0xAA2];
        leoDiskID[0xA90] = leoDiskID[0xAA0];
    } else {
        leoDiskID[0xA91] = arg0[1];
        leoDiskID[0xA92] = arg0[2];
        leoDiskID[0xA90] = arg0[0];
        *(s32 *)(leoDiskID + 0xA94) = *(s32 *)(arg0 + 4);
        *(s32 *)(leoDiskID + 0xA98) = *(s32 *)(arg0 + 8);
        *(s32 *)(leoDiskID + 0xA9C) = *(s32 *)(arg0 + 0xC);
        leoDiskID[0xA93] = arg0[3];
    }
}
#endif

#ifdef VERSION_US

typedef struct FramebufferInfo {
    u8 padding00[4];
    u16 unk4;
    u8 padding06[2];
    void *unk8;
} FramebufferInfo;

typedef struct ProvisionalContext {
    u8 padding000[0x1C8];
    s32 unk1C8;

    u8 padding1CC[0x814];
    FramebufferInfo *unk9E0;

    u8 padding9E4[0xA8];
    f32 unkA8C;

    u8 paddingA90[3];
    u8 unkA93;
    s32 unkA94;

    u8 paddingA98[4];
    s32 unkA9C;

    u8 unkAA0;
    u8 unkAA1;
    u8 unkAA2;
    u8 paddingAA3;
    s32 unkAA4;

    u8 paddingAA8[4];
    FramebufferInfo *unkAAC;

    u8 unkAB0;
    u8 unkAB1;
    u8 unkAB2;
    u8 unkAB3;

    u8 paddingAB4[8];
    s32 unkABC;
} ProvisionalContext;

typedef struct FourWords {
    u32 word0;
    u32 word4;
    u32 word8;
    u32 wordC;
} FourWords;

extern u8 D_800AB400;
extern FourWords D_800AB470;
extern FourWords D_800AB480;
extern FourWords D_800AB490;
extern s32 D_800871D0;
extern void func_80004BEC(void *);
extern s32 func_80004F34(void *);
extern s32 Sched_TryReceiveClientQueue(void *);
extern void func_80009EB4(void *, u16, s32);
extern void func_8000A080(s32);
extern s32 Display_GetFramebufferClearColor(void);

/* A local `ctx` variable holding this cast (computed once) makes IDO
 * spill/rematerialize the pointer across calls instead of keeping it live
 * in one register the way retail does. A macro that re-expands the same
 * cast expression at every use site gets IDO to treat it the same way
 * retail's compiler did. */
#define ctx ((ProvisionalContext *)(void *)leoDiskID)

s32 func_800017F8(void) {
    s32 index;
    s32 retraceCount;
    s32 pendingStateCopied;

    retraceCount = 0;
    pendingStateCopied = 0;

    if (ctx->unkAA4 != 0) {
        func_80004BEC(&D_800AB400);
    }

    if ((ctx->unkA94 != 0) &&
        (ctx->unkABC != ctx->unkA9C) &&
        (ctx->unkAB3 != ctx->unkA93)) {
        func_80001684(&D_800AB400, &D_800AB470, 1);
        pendingStateCopied = 1;
    }

    for (index = 1; index < (s32)ctx->unkAB0; index++) {
        if (func_80004F34(ctx) == 0x56545245) {
            retraceCount++;
        }
    }

    if (ctx->unk1C8 > 0) {
        do {
            if (Sched_TryReceiveClientQueue(ctx) == 0x56545245) {
                retraceCount++;
            }
        } while (ctx->unk1C8 > 0);
    }

    if (ctx->unkAAC != NULL) {
        osViSwapBuffer(ctx->unkAAC->unk8);
        osViRepeatLine(0);

        if ((ctx->unkAA1 != ctx->unkAB1) ||
            (ctx->unkAA2 != ctx->unkAB2)) {
            Vi_SelectMode((s8)ctx->unkAA1, (s8)ctx->unkAA2);
        }

        if (D_800871D0 != 0) {
            osViBlack(1);
            osViSetYScale(1.0f);
        } else {
            osViBlack(0);
            osViSetYScale(ctx->unkA8C);
        }

        func_80009EB4(ctx->unkAAC->unk8, ctx->unkAAC->unk4, 0x10);
    } else {
        if (((Display_GetFramebufferClearColor() | 1) & 0xFFFF) != 1) {
            osViRepeatLine(1);
        } else {
            osViBlack(1);
            osViSetYScale(1.0f);
        }

        osViSwapBuffer(ctx->unk9E0->unk8);

        if ((ctx->unkAA1 != ctx->unkAB1) ||
            (ctx->unkAA2 != ctx->unkAB2)) {
            Vi_SelectMode((s8)ctx->unkAA1, (s8)ctx->unkAA2);
        }
    }

    if ((pendingStateCopied == 0) && (ctx->unkA94 != 0)) {
        func_80001684(&D_800AB400, &D_800AB470, 0);
    }

    D_800AB490 = D_800AB480;
    D_800AB480 = D_800AB470;

    func_8000A080(3);

    if (func_80004F34(ctx) == 0x56545245) {
        retraceCount++;
    }

    return retraceCount;
}

#undef ctx
#endif

#ifdef VERSION_US

extern s32 func_80004F34(void *);
extern s32 Sched_TryReceiveClientQueue(void *);

void DisplayWorker_DrainEvents(void) {
    func_80004F34(leoDiskID);
    if (*(s32 *)(leoDiskID + 0x1C8) > 0) {
        do {
            Sched_TryReceiveClientQueue(leoDiskID);
        } while (*(s32 *)(leoDiskID + 0x1C8) > 0);
    }
    func_80004F34(leoDiskID);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001B20.s")
#endif

void func_80001CA8(void) {
}

#ifdef VERSION_US

s32 func_80001CB0(arg0)
s32 arg0;
{
    s32 result = 0;
    if (arg0 == 1) {
        goto set_result;
    }
    if (arg0 != 2) {
        goto done;
    }
set_result:
    result = 1;
done:
    return result;
}
#endif

void func_80001CD4(void) {
}

#ifdef VERSION_US
s32 func_80001CDC(s32 arg0) { return func_80001CB0(arg0); }
#endif

#ifdef VERSION_US
extern s32 func_80001CDC(s32);
extern void func_80001B20(void *);
extern s32 func_800071A4(s32, s32, s32, s32, s32);
extern void Display_ClearFramebufferLine(u16);
extern void func_80003F74(u8 *, u8 *, u8 *, s32);
extern u8 *D_800AB3C0;
extern u8 D_800AB3C4[];
extern u8 D_800AB3C8[];
extern OSMesgQueue D_800AB3CC;
extern OSMesgQueue D_800AB3E4;
void Thread5_CreateThread(void) {
    OSThread *thread = (OSThread *)leoDiskID;
    if (func_80001CDC(osTvType) == 0) {
        osViBlack(1);
        osViSetYScale(1.0f);
        while (1) {}
    }
    osCreateThread(thread, 5, func_80001B20, NULL, &D_800AB3C0, 0x28);
    osStartThread(thread);
    osCreateMesgQueue(&D_800AB3CC, (OSMesg *)D_800AB3C4, 1);
    osCreateMesgQueue(&D_800AB3E4, (OSMesg *)D_800AB3C8, 1);
    *(s16 *)(leoDiskID + 0xA88) = 0;
    leoDiskID[0xA8A] = 0;
    leoDiskID[0xA8B] = 0;
    *(f32 *)(leoDiskID + 0xA8C) = 1.0f;
    *(s32 *)(leoDiskID + 0x9E0) = func_800071A4(0, 2, 0x280, 1, 1);
    Display_ClearFramebufferLine(1);
    func_80003F74(D_800AB4A0, (u8 *)0xB0000B70, (u8 *)0xB0000C70, 0);
}
#endif

#ifdef VERSION_US
void Display_ClearFramebufferLine(u16 color) { s32 width = 640; u16 *buf = *(u16 **)(*(u8 **)(leoDiskID + 0x9E0) + 8); while (width-- > 0) { *buf++ = color; } osWritebackDCache(*(void **)(*(u8 **)(leoDiskID + 0x9E0) + 8), 0x500); }
#endif

#ifdef VERSION_US

extern u8 *D_800AB3C0;
s32 func_80001E70(void) {
    s32 result = 1;
    u16 *ptr = *(u16 **)(D_800AB3C0 + 8);
    u16 expected = *ptr;
    s32 count = 0x27F;

    do {
        if (expected != *ptr++) {
            result = 0;
        }
    } while (count-- > 0);
    return result;
}
#endif

#ifdef VERSION_US
s32 Display_GetFramebufferClearColor(void) { u8 *ptr = *(u8 **)(D_800AB3C0 + 8); return *(u16 *)ptr; }
#endif

#ifdef VERSION_US
extern u8 *D_800AB3C0; extern void *osViGetCurrentFramebuffer(void);
s32 Display_IsCurrentFramebuffer(void) { s32 result = 0; if (osViGetCurrentFramebuffer() == *(void **)(D_800AB3C0 + 8)) result = 1; return result; }
#endif

#ifdef VERSION_US
void Display_WaitForCompletion(void) { extern OSMesgQueue D_800AB3E4; osRecvMesg(&D_800AB3E4, NULL, OS_MESG_BLOCK); }
#endif

#ifdef VERSION_US

extern OSMesgQueue D_800AB3CC;
void Display_QueueFramebufferRequest(s32 arg0) {
    osSendMesg(&D_800AB3CC, (OSMesg)arg0, NULL);
}
#endif

#ifdef VERSION_US
void Display_WaitForFrames(s32 arg0) {
    while (arg0-- > 0) {
        Display_QueueFramebufferRequest(0);
        Display_WaitForCompletion();
    }
}
#endif

#ifdef VERSION_US
void func_80001FA8(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7) {
    arg0[1] = arg1;
    arg0[2] = arg2;
    arg0[0] = arg3;
    arg0[3] = arg4;
    *(s32 *)(arg0 + 4) = arg5;
    *(s32 *)(arg0 + 8) = arg6;
    *(s32 *)(arg0 + 0xC) = arg7;
}
#endif

#ifdef VERSION_US
extern s32 D_800AB49C;
s32 func_80001FE4(void) {
    return D_800AB49C;
}
#endif

#ifdef VERSION_US
s32 func_80001FF0(void) { extern s32 osTvType; return osTvType == 0 ? 0x32 : 0x3C; }
#endif

#ifdef VERSION_US
extern u8 D_800AB46B;
u8 func_80002014(void) {
    return D_800AB46B;
}
#endif

#ifdef VERSION_US
void Display_ApplyPendingVideoMode(void) { extern u8 leoDiskID[]; Vi_SelectMode(*(s8 *)(leoDiskID + 0xAB1), *(s8 *)(leoDiskID + 0xAB2)); }
#endif

#ifdef VERSION_US
s32 func_8000204C(void) { extern u8 leoDiskID[]; s32 ready = 1; if (*(s32 *)(leoDiskID + 0xAA4) != 0) ready = *(s32 *)(leoDiskID + 0xA2C) > 0; return ready; }
#endif

#ifdef VERSION_US
extern s32 D_800871D0;
void Display_EnableBlackout(void) {
    D_800871D0 = 1;
}
#endif

#ifdef VERSION_US
void func_80002084(void) {
    D_800871D0 = 0;
}
#endif

#ifdef VERSION_US
extern f32 D_800AB46C;
f32 func_80002090(void) {
    return D_800AB46C;
}
#endif
