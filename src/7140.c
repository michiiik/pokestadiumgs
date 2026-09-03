#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_80006540.s")

s32 Storage_ReadSram(void *arg0) {
    struct Func800065DCState { u8 pad[0x1C]; s32 unk1C; void *vaddr; s32 size; s32 unk28; };
    extern OSMesgQueue D_800D0474;
    extern OSMesg D_800D0440;
    OSIoMesg msg;
    OSPiHandle *handle;
    struct Func800065DCState *p = (struct Func800065DCState *)arg0;
    handle = (OSPiHandle *)(u32)func_80006540();
    msg.hdr.pri = 0;
    msg.hdr.retQueue = &D_800D0474;
    msg.dramAddr = p->vaddr;
    msg.devAddr = p->unk1C;
    msg.size = p->size;
    osInvalDCache(p->vaddr, p->size);
    osEPiStartDma(handle, &msg, 0);
    osRecvMesg(&D_800D0474, &D_800D0440, OS_MESG_BLOCK);
    return 0;
}

s32 func_80006664(void *arg0) {
    struct Func80006664State { u8 pad[0x1C]; s32 unk1C; void *vaddr; s32 size; s32 unk28; };
    extern OSMesgQueue D_800D0474;
    extern OSMesg D_800D0440;
    OSIoMesg msg;
    OSPiHandle *handle;
    struct Func80006664State *p = (struct Func80006664State *)arg0;
    handle = (OSPiHandle *)(u32)func_80006540();
    msg.hdr.pri = 0;
    msg.hdr.retQueue = &D_800D0474;
    msg.dramAddr = p->vaddr;
    msg.devAddr = p->unk1C;
    msg.size = p->size;
    osWritebackDCache(p->vaddr, p->size);
    osEPiStartDma(handle, &msg, 1);
    osRecvMesg(&D_800D0474, &D_800D0440, OS_MESG_BLOCK);
    return 0;
}

s32 func_800066EC(void *arg0, s32 arg1) {
    struct Func800066ECState { u8 pad[0x1C]; s32 unk1C; void *vaddr; s32 size; s32 unk28; };
    extern OSMesgQueue D_800D0474;
    extern OSMesg D_800D0440;
    OSIoMesg msg;
    OSPiHandle *handle;
    struct Func800066ECState *p = (struct Func800066ECState *)arg0;
    handle = (OSPiHandle *)(u32)osCartRomInit();
    msg.hdr.pri = 0;
    msg.hdr.retQueue = &D_800D0474;
    msg.dramAddr = p->vaddr;
    msg.devAddr = p->unk1C;
    msg.size = p->size;
    osInvalDCache(p->vaddr, p->size);
    osEPiStartDma(handle, &msg, 0);
    osRecvMesg(&D_800D0474, &D_800D0440, OS_MESG_BLOCK);
    return 0;
}

s32 func_80006778(void *arg0) {
    struct Func80006778State { u8 pad[0x1C]; s32 unk1C; void *vaddr; s32 size; s32 unk28; };
    extern OSMesgQueue D_800D0474;
    extern OSMesg D_800D0440;
    OSIoMesg msg;
    OSPiHandle *handle;
    struct Func80006778State *p = (struct Func80006778State *)arg0;
    handle = osCartRomInit();
    msg.hdr.pri = 0;
    msg.hdr.retQueue = &D_800D0474;
    msg.dramAddr = p->vaddr;
    msg.devAddr = p->unk1C;
    msg.size = p->size;
    osWritebackDCache(p->vaddr, p->size);
    osEPiStartDma(handle, &msg, 1);
    osRecvMesg(&D_800D0474, &D_800D0440, OS_MESG_BLOCK);
    return 0;
}

s32 Storage_ReadFlashArray(u8 *arg0) {
    extern OSMesgQueue D_800D0474;
    extern OSMesg D_800D0440;
    OSIoMesg msg;
    osInvalDCache(*(void **)(arg0 + 0x20), 0x80);
    osFlashReadArray(&msg, 0, *(s32 *)(arg0 + 0x1C), *(void **)(arg0 + 0x20), 1, &D_800D0474);
    osRecvMesg(&D_800D0474, &D_800D0440, 1);
    return 0;
}

s32 Storage_StartFlashWriteBuffer(void *arg0) {
    struct Func80006870State { u8 pad[0x1C]; s32 unk1C; void *vaddr; s32 size; s32 unk28; };
    extern OSMesgQueue D_800D0474;
    extern OSMesg D_800D0440;
    OSIoMesg msg;
    struct Func80006870State *p = (struct Func80006870State *)arg0;
    osFlashWriteBuffer(&msg, 0, p->vaddr, &D_800D0474);
    osRecvMesg(&D_800D0474, &D_800D0440, OS_MESG_BLOCK);
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_800068C4.s")

void func_800068C4(void *);
extern OSThread D_800CE170;
extern u8 D_800D0320;
extern void *D_800D033C;
extern void *D_800D03FC;
extern void *D_800D043C;
extern OSMesgQueue D_800D0444;
extern OSMesgQueue D_800D045C;
extern OSMesgQueue D_800D0474;
void rsp_init(void) {
    osCreateMesgQueue(&D_800D0474, &D_800D043C, 1);
    osCreateMesgQueue(&D_800D045C, &D_800D03FC, 0x10);
    osCreatePiManager(0x96, &D_800D0444, &D_800D033C, 0x20);
    osCreateThread(&D_800CE170, 0x14, func_800068C4, NULL, &D_800D0320, 0x5A);
    osStartThread(&D_800CE170);
}

void Dma_QueueRequestMessage(void *arg0, s32 arg1) {
    extern OSMesgQueue D_800D045C;
    if (arg1 == 1) {
        osJamMesg(&D_800D045C, arg0, OS_MESG_BLOCK);
        return;
    }
    osSendMesg(&D_800D045C, arg0, OS_MESG_BLOCK);
}

s32 Dma_QueueRomRead(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct Func80006ACCState { u8 unk0; u8 filler[0x18]; s32 unk1C; void *unk20; s32 unk24; s32 unk28; };
    struct Func80006ACCState *p;
    p = (struct Func80006ACCState *)(u32)Util_Malloc(0x2C);
    if (p != NULL) {
        p->unk0 = 0xF0;
        p->unk1C = arg2;
        p->unk24 = arg3;
        p->unk20 = arg1;
        p->unk28 = arg4;
        Dma_QueueRequestMessage(p, arg5);
    }
    return p == NULL;
}

struct S1_UnkStruct80000E80 {
    char unk0;
    char filler4[0x18];
    s32 unk1C;
    u8* unk20;
    s32 unk24;
    s32 unk28;
};
typedef unsigned int S1_uintptr_t;
s32 Storage_QueueRomWrite(s32 arg0, void* arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct S1_UnkStruct80000E80* temp_v0;

    temp_v0 = Util_Malloc(0x2C);
    if (temp_v0 != NULL) {
        temp_v0->unk0 = 0xF4;
        temp_v0->unk1C = (S1_uintptr_t)arg1;
        temp_v0->unk24 = arg2;
        temp_v0->unk20 = (void*)(S1_uintptr_t)arg0;
        temp_v0->unk28 = arg3;
        Dma_QueueRequestMessage(temp_v0, arg4);
    }
    return temp_v0 == NULL;
}

s32 Storage_QueueSramTransfer(s32 arg0, void* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct S1_UnkStruct80000E80* temp_v0;

    temp_v0 = Util_Malloc(0x2C);
    if (temp_v0 != NULL) {
        if (arg0 == 0) {
            temp_v0->unk0 = 0xF2;
        } else {
            temp_v0->unk0 = 0xF3;
        }
        temp_v0->unk1C = arg2;
        temp_v0->unk24 = arg3;
        temp_v0->unk20 = arg1;
        temp_v0->unk28 = arg4;
        Dma_QueueRequestMessage(temp_v0, arg5);
    }
    return temp_v0 == NULL;
}

extern void Dma_QueueRequestMessage(void *, s32);
typedef struct { u8 unk0; u8 filler[0x18]; s32 unk1C; s32 unk20; s32 unk24; s32 unk28; } Req;
s32 Storage_QueueFlashTransfer(s32 arg0, s32 arg1, s16 arg2, void *arg3, s32 arg4) {
    Req *p = Util_Malloc(0x2C);
    if (p != NULL) {
        if (arg0 == 0) {
            p->unk0 = 0xF5;
        } else {
            p->unk0 = 0xF6;
        }
        p->unk1C = arg2;
        p->unk24 = 1;
        p->unk20 = arg1;
        p->unk28 = (s32)arg3;
        Dma_QueueRequestMessage(p, arg4);
    }
    return p == NULL;
}
#endif
