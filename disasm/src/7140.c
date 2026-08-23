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

void func_80006A78(DmaRequest *request, s32 mode) {
    if (mode == 1) {
        osJamMesg((OSMesgQueue *)D_800D045C, (OSMesg)request, 1);
    } else {
        osSendMesg((OSMesgQueue *)D_800D045C, (OSMesg)request, 1);
    }
}

s32 func_80006ACC(u32 unused, u32 source, u32 destination, u32 length,
                 u32 staging, s32 mode) {
    DmaRequest *request = Util_Malloc(0x2C);

    if (request != NULL) {
        request->type = 0xF0;
        request->field_1C = destination;
        request->field_24 = length;
        request->field_20 = source;
        request->field_28 = staging;
        func_80006A78(request, mode);
    }

    return request == NULL;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/Storage_QueueRomWrite.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/Storage_QueueSramTransfer.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/Storage_QueueFlashTransfer.s")
#endif
