#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/Storage_GetSramHandle.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/Storage_ReadSram.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_80006664.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_800066EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_80006778.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/Storage_ReadFlashArray.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/Storage_StartFlashWriteBuffer.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_800068C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/rsp_init.s")

typedef struct {
    u8 type;
    u8 pad_01[0x1B];
    u32 field_1C;
    u32 field_20;
    u32 field_24;
    u32 field_28;
} DmaRequest;

extern u8 D_800D045C[];
extern void *Util_Malloc(s32 size);

void Dma_QueueRequestMessage(DmaRequest *request, s32 mode) {
    if (mode == 1) {
        osJamMesg((OSMesgQueue *)D_800D045C, (OSMesg)request, 1);
    } else {
        osSendMesg((OSMesgQueue *)D_800D045C, (OSMesg)request, 1);
    }
}

s32 Dma_QueueRomRead(u32 unused, u32 source, u32 destination, u32 length,
                 u32 staging, s32 mode) {
    DmaRequest *request = Util_Malloc(0x2C);

    if (request != NULL) {
        request->type = 0xF0;
        request->field_1C = destination;
        request->field_24 = length;
        request->field_20 = source;
        request->field_28 = staging;
        Dma_QueueRequestMessage(request, mode);
    }

    return request == NULL;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/Storage_QueueRomWrite.s")
#if 0
s32 Storage_QueueRomWrite(u32 destination, u32 source, u32 length,
                          OSMesgQueue *queue, s32 mode) {
    DmaRequest *request = Util_Malloc(0x2C);

    if (request != NULL) {
        request->type = 0xF4;
        request->field_1C = source;
        request->field_20 = destination;
        request->field_24 = length;
        request->field_28 = (u32)queue;
        Dma_QueueRequestMessage(request, mode);
    }

    return request == NULL;
}
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/Storage_QueueSramTransfer.s")
#if 0
s32 Storage_QueueSramTransfer(u32 staging, u32 destination, u32 source,
                               u32 length, OSMesgQueue *queue, s32 mode) {
    DmaRequest *request = Util_Malloc(0x2C);

    if (request != NULL) {
        request->type = staging == 0 ? 0xF2 : 0xF3;
        request->field_1C = source;
        request->field_20 = destination;
        request->field_24 = length;
        request->field_28 = (u32)queue;
        Dma_QueueRequestMessage(request, mode);
    }

    return request == NULL;
}
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/Storage_QueueFlashTransfer.s")
#if 0
s32 Storage_QueueFlashTransfer(u32 type, u32 destination, u32 page,
                                u32 unused, OSMesgQueue *queue, s32 mode) {
    DmaRequest *request = Util_Malloc(0x2C);

    if (request != NULL) {
        request->type = type == 0 ? 0xF5 : 0xF6;
        request->field_1C = (u16)page;
        request->field_20 = destination;
        request->field_24 = 1;
        request->field_28 = unused;
        Dma_QueueRequestMessage(request, mode);
    }

    return request == NULL;
}
#endif
#endif
