#include "global.h"


#ifdef VERSION_US
extern void osWritebackDCacheAll(void);

void func_80004BC0(u8 *arg0) {
    osWritebackDCacheAll();
    *(u16 *)(arg0 + 0x1C) = 0;
    *(u16 *)(arg0 + 0x1E) = 0;
}
#endif

#ifdef VERSION_US
s32 func_80004BEC(u8 *arg0) {
    OSMesg msg;
    return osRecvMesg((OSMesgQueue *)(arg0 + 4), &msg, 1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004C14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004CF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004D4C.s")
#endif

#ifdef VERSION_US
extern s32 func_8000A1E8(s32);

void func_80004EA8(u8 *arg0) {
    func_8000A1E8(2);
    if (*(u16 *)(arg0 + 0x1C) == 3) {
        osSendMesg((OSMesgQueue *)(arg0 + 4), (OSMesg)0x444F4E45, 0);
    }
    *(u16 *)(arg0 + 0x1E) = 2;
}
#endif

#ifdef VERSION_US
typedef struct S1_UnkStruct80083CA0_2 S1_UnkStruct80083CA0_2;
typedef struct S1_unk_D_800AA660 S1_unk_D_800AA660;
typedef struct S1_UnkArray4 S1_UnkArray4;
typedef struct S1_GbTowerLaunchData S1_GbTowerLaunchData;
struct S1_UnkArray4 {
    /* 0x00 */ u8 bufferMode; // Display_SetBufferConfig's arg3
    /* 0x01 */ u8 videoModeA; // arg1; feeds Video_SetMode's arg0 once committed
    /* 0x02 */ u8 videoModeB; // arg2; feeds Video_SetMode's arg1 once committed
    /* 0x03 */ u8 bufferIndex; // arg4; compared against the committed index to detect a new frame
    /* 0x04 */ u32 displayListPtr; // arg5; DisplayTask_Submit's task data_ptr
    /* 0x08 */ u32 displayListSize; // arg6; DisplayTask_Submit's task data_size
    /* 0x0C */ u32 frameId; // arg7; compared against the committed frameId to detect a new frame
};
struct S1_GbTowerLaunchData {
    /* 0x00 */ u16 buttonBindingsPacked;
    /* 0x02 */ u8 presentationMode;
    /* 0x03 */ u8 partyCount;
    /* 0x04 */ u16 (*partyIconFrames)[6][0x640];
};
struct S1_unk_D_800AA660 {
    /* 0x0000 */ OSThread thread;
    /* 0x01B0 */ char unk01B0[0x10];
    /* 0x01C0 */ OSMesgQueue queue1;
    /* 0x01D8 */ struct S1_unk_D_800AA660* nextClient; // Sched_AddClient/NotifyClients linked-list traversal
    /* 0x01DC */ s32 eventFilter; // func_80004F00's arg1; gates which broadcast events this client receives
    /* 0x01E0 */ char unk01E0[0x2000];
    /* 0x21E0 */ OSMesg mesg;
    /* 0x21E4 */ OSMesgQueue queue2;
    /* 0x21FC */ u8* font1;
    /* 0x2200 */ u8* font2;
    /* 0x2204 */ S1_GbTowerLaunchData launchData;
    /* 0x220C */ char unk220C[4];
};
struct S1_UnkStruct80083CA0_2 {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ OSMesg unk_1B0;
    /* 0x1B4 */ char unk1B4[0xC];
    /* 0x1C0 */ OSMesgQueue unk_1C0;
    /* 0x1D8 */ s32 nextClient; // same layout as S1_unk_D_800AA660's nextClient
    /* 0x1DC */ s32 eventFilter; // func_80004F00's arg1
    /* 0x1E0 */ u8 unk1E0[0x800];
    /* 0x9E0 */ S1_UnkArray4* normalFramebuffer; // DisplayWorker_ProcessFrame's default osViSwapBuffer source
    /* 0x9E4 */ char unk9E4[0x48];
    /* 0xA2C */ s32 readyFrameCount; // Display_IsFrameReady: >0 gates readiness when taskSubmitted
    /* 0xA30 */ char unkA30[0x58];
    /* 0xA88 */ u16 unk_A88;
    /* 0xA8A */ u8 workerBusy; // set 1 before waiting on the frame-request mesg, 0 after receiving it
    /* 0xA8B */ u8 unk_A8B;
    /* 0xA8C */ u8 bufferMode; // committed copy of S1_UnkArray4.bufferMode
    /* 0xA8D */ u8 videoModeA; // committed copy of S1_UnkArray4.videoModeA
    /* 0xA8E */ u8 videoModeB; // committed copy of S1_UnkArray4.videoModeB
    /* 0xA8F */ u8 bufferIndex; // committed copy of S1_UnkArray4.bufferIndex
    /* 0xA90 */ s32 displayListPtr; // committed copy of S1_UnkArray4.displayListPtr; !=0 gates gfx task submission
    /* 0xA94 */ s32 displayListSize;
    /* 0xA98 */ s32 frameId;
    /* 0xA9C */ u8 pendingBufferMode; // restored into bufferMode/videoModeA/B when DisplayWorker_SetBufferConfig's arg is NULL
    /* 0xA9D */ u8 pendingVideoModeA; // Video_SetMode's arg0 once applied
    /* 0xA9E */ u8 pendingVideoModeB; // Video_SetMode's arg1 once applied
    /* 0xA9F */ u8 unk_A9F;
    /* 0xAA0 */ s32 taskSubmitted; // gates Sched_WaitForTaskMessage/Display_IsFrameReady
    /* 0xAA4 */ char unkAA4[0x4];
    /* 0xAA8 */ S1_UnkArray4* crashScreenFramebuffer; // overrides normalFramebuffer for osViSwapBuffer/crash_screen_set_draw_info when non-NULL
    /* 0xAAC */ u8 clientCount; // DisplayWorker_ProcessFrame's Sched_WaitClientQueue loop bound
    /* 0xAAD */ u8 appliedVideoModeA; // compared against pendingVideoModeA/B to detect a video-mode change
    /* 0xAAE */ u8 appliedVideoModeB;
    /* 0xAAF */ u8 appliedBufferIndex; // compared against bufferIndex to detect a new frame
    /* 0xAB0 */ char unkAB0[0x8];
    /* 0xAB8 */ s32 appliedFrameId; // compared against frameId to detect a new frame
};
void func_80004F00(S1_UnkStruct80083CA0_2* arg0, s32 arg1, s32 arg2) {
    arg0->eventFilter = arg1;
    arg0->nextClient = 0;
    osCreateMesgQueue(&arg0->unk_1C0, &arg0->unk_1B0, arg2);
}
#endif

#ifdef VERSION_US
OSMesg func_80004F34(u8 *arg0) {
    OSMesg msg;
    osRecvMesg((OSMesgQueue *)(arg0 + 0x1C0), &msg, 1);
    return msg;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004F60.s")
#endif

#ifdef VERSION_US
extern u32 D_800CD020[];

void func_80004FA4(void) {
    if (D_800CD020[0xA18 / 4] == 0 && D_800CD020[0xA20 / 4] != 0) {
        D_800CD020[0xA18 / 4] = D_800CD020[0xA20 / 4];
        D_800CD020[0xA20 / 4] = 0;
    }
    if (D_800CD020[0xA1C / 4] == 0 && D_800CD020[0xA24 / 4] != 0) {
        D_800CD020[0xA1C / 4] = D_800CD020[0xA24 / 4];
        D_800CD020[0xA24 / 4] = 0;
    }
}
#endif

void func_80004FF4(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004FFC.s")
#endif

#ifdef VERSION_US
void *func_800050A0(void *arg0) {
    if (arg0 && !func_80004C14(arg0)) {
        arg0 = 0;
    }
    return arg0;
}
#endif

#ifdef VERSION_US
extern u32 D_800CDA34;

void func_800050D4(void) {
    if (D_800CD020[0xA14 / 4] == 0) {
        D_800CDA34 = (u32)func_800050A0((void *)D_800CD020[0xA1C / 4]);
    }
}
#endif

#ifdef VERSION_US
s32 func_80004CF4(u32);

s32 func_80005110(void) {
    s32 var_v1;

    var_v1 = 0;
    if (D_800CDA34 != 0) {
        var_v1 = func_80004CF4(D_800CDA34);
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80005148.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_800051B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_800052C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80005388.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_800053D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/Thread3_CreateThread.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80005568.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_800055B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_800055F4.s")
#endif
