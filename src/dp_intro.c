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

extern void func_800055F4(void *, s32);
void func_80001684(void *arg0, void *arg1, s32 arg2) {
    *(u32 *)((u8 *)arg0 + 0x50) = *(u32 *)((u8 *)arg1 + 4);
    *(u32 *)((u8 *)arg0 + 0x54) = *(u32 *)((u8 *)arg1 + 8);
    func_800055F4(arg0, arg2);
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_800017F8.s")
#endif

#ifdef VERSION_US

extern void func_80004F34(void *);
extern void Sched_TryReceiveClientQueue(void *);

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
