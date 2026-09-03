#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_800564BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_8005655C.s")

extern u8 D_801283B0;
extern s32 GbPak_ReadCommand();
extern s32 GbPak_WriteCommand();
extern s32 _bcmp(const void *, const void *, s32);
s32 GbPak_VerifyPattern(s32 arg0, u8 *arg1) {
    struct {
        u8 leading[8];
        s32 result;
        u8 data[0x20];
        u8 pad[3];
        u8 status;
    } local;
    local.result = 0;
    if ((GbPak_WriteCommand(arg0, arg1, 0, 0x20) == 0) &&
        (GbPak_ReadCommand(arg0, local.data, 0, 0x20) == 0) &&
        (_bcmp(local.data, arg1, 0x20) == 0) &&
        (osGbpakGetStatus((arg0 * 0x68) + &D_801283B0, &local.status) == 0)) {
        local.result = ((local.status & 4) != 0) == 0;
    }
    return local.result;
}

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
s32 GbPak_DetectRam(s32 arg0, u8* arg1) {
    s32 var_s0 = 0;
    u8 sp34[0x20];

    if (arg1 == NULL) {
        arg1 = sp34;
    }
    HAL_Memset((char*)arg1, 0x55, 0x20);
    if (GbPak_VerifyPattern(arg0, arg1) != 0) {
        HAL_Memset((char*)arg1, 0xAA, 0x20);
        if (GbPak_VerifyPattern(arg0, arg1) != 0) {
            s32 i;
            for (i = 0; i < ARRAY_COUNT(sp34); i++) {
                arg1[i] = osGetCount();
            }
            var_s0 = GbPak_VerifyPattern(arg0, arg1);
        }
    }
    return var_s0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056870.s")

extern u8 D_80128550[];
extern s32 func_80056F7C(s32);
extern s32 func_8005D92C(s32);
extern s32 func_8005805C(s32);
extern s32 GbTower_VerifyPakStillInserted(s32, u8 *);
extern void func_80064D58(s32, s32);
s32 GbPak_ValidateAndRefresh(s32 arg0, u8 *arg1, u8 *arg2) {
    u8 *state;
    struct {
        s32 previous;
        s32 result;
        u8 trailing[0x50];
    } local;
    local.result = 0;
    if (arg1 != NULL) *arg1 = D_80128550[arg0];
    state = &D_80128550[arg0];
    if (*state == 1) return 1;
    if (func_80056F7C(arg0) != 0) {
        if (arg2 != NULL) {
            local.previous = func_8005D92C(arg0);
            if ((func_8005805C(arg0) == local.previous) && (GbTower_VerifyPakStillInserted(arg0, arg2) != 0)) {
                local.result = GbPak_DetectRam(arg0, arg2);
            }
            if (local.result == 0) func_80064D58(arg0, 1);
        }
    } else {
        func_80064D58(arg0, 1);
    }
    *state = 1;
    return local.result;
}

extern s32 HAL_Strcmp(const s8 *, const s8 *);
extern s8 D_800A49B0[];
extern s8 D_800A49BC[];
extern s8 D_800A49C8[];
extern s8 D_800A49D4[];
extern s8 D_800A49E0[];
extern s8 D_800A49EC[];
extern s8 D_800A49F8[];
s32 GbTower_CheckPakRemoved(s32 arg0, u8 arg1) {
    u8 status;
    s32 sp20;
    OSPfs *pfs;
    pfs = (arg0 * 0x68) + &D_801283B0;
    if (osGbpakGetStatus(pfs, &status) != 0) {
        func_80064D58(arg0, 1);
    }
    sp20 = ((status & 4) != 0) == 0;
    if (arg1 == 0) {
        osGbpakPower(pfs, 0);
        D_80128550[arg0] = 0;
    }
    return sp20;
}

extern u8 D_80128554;
void GbTower_PowerOffAllPaks(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (D_80128554 & (1 << i)) {
            osGbpakPower((OSPfs *)((u8 *)&D_801283B0 + (i * 0x68)), 0);
            D_80128550[i] = 0;
        }
    }
}

s32 func_80056BA4(u8 *arg0) {
    s8 *name;
    arg0[0x3D] = 0;
    name = (s8 *)(arg0 + 0x34);
    if (HAL_Strcmp(name, D_800A49B0) == 0) {
        return 1;
    }
    if (HAL_Strcmp(name, D_800A49BC) == 0) {
        return 1;
    }
    if (HAL_Strcmp(name, D_800A49C8) == 0) {
        return 1;
    }
    if (HAL_Strcmp(name, D_800A49D4) == 0) {
        return 1;
    }
    if (HAL_Strcmp(name, D_800A49E0) == 0) {
        return 1;
    }
    if (HAL_Strcmp(name, D_800A49EC) == 0) {
        return 1;
    }
    if (HAL_Strcmp(name, D_800A49F8) == 0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056C98.s")

s32 GbPak_IsCartOff(s32 arg0) {
    u8 local[12];
    s32 result;
    result = osGbpakGetStatus((arg0 * 0x68) + &D_801283B0, &local[11]);
    if ((result == 1) || (result == 0xB) || (result == 4)) {
        func_80064D58(arg0, 1);
    }
    return ((local[11] & 0x80) != 0) == 0;
}

s32 GbPak_IsCartOn(s32 arg0) {
    u8 sp1F;
    s32 temp_v0;

    temp_v0 = osGbpakGetStatus((arg0 * 0x68) + &D_801283B0, &sp1F);
    if ((temp_v0 == 1) || (temp_v0 == 0xB) || (temp_v0 == 4)) {
        func_80064D58(arg0, 1);
    }
    return (sp1F & 0x80) != 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056F7C.s")

s32 GbTower_VerifyPakStillInserted(s32 arg0, u8 *arg1) {
    u8 status;
    u8 data[0x20];
    s32 result;
    result = 0;
    if ((GbPak_ReadCommand(arg0, data, 0, 0x20) == 0) &&
        (_bcmp(data, arg1, 0x20) == 0) &&
        (osGbpakGetStatus((arg0 * 0x68) + &D_801283B0, &status) == 0) &&
        !(status & 4)) {
        result = 1;
    }
    return result;
}

extern u8 D_80128555;
extern s32 func_8005655C(u8, s32, s32, u8 *, s32);
s32 GbPak_ReadCommand(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
    s32 result;
    result = 1;
    if (D_80128555 & (1 << arg0)) {
        result = func_8005655C(arg0, 0, arg2, arg1, arg3);
    }
    return result;
}

s32 GbPak_WriteCommand(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
    s32 result;
    result = 1;
    if (D_80128555 & (1 << arg0)) {
        result = func_8005655C(arg0, 1, arg2, arg1, arg3);
    }
    return result;
}

extern u8 D_80128557;
extern u8 D_80128558;
s32 func_8005718C(s32 arg0, u8 *arg1, u16 arg2, u16 arg3) {
    s32 result;
    result = 1;
    if (D_80128555 & (1 << arg0)) {
        result = osGbpakReadWrite((arg0 * 0x68) + &D_801283B0, 0, arg2, arg1, arg3);
    }
    return result;
}

s32 func_80057210(s32 arg0, u8 *arg1, u16 arg2, u16 arg3) {
    s32 result;
    result = 1;
    if (D_80128555 & (1 << arg0)) {
        result = osGbpakReadWrite((arg0 * 0x68) + &D_801283B0, 1, arg2, arg1, arg3);
    }
    return result;
}

void func_80057294(u8 arg0, OSGbpakId *arg1, u8 *arg2) {
    osGbpakReadId((arg0 * 0x68) + &D_801283B0, arg1, arg2);
}

void func_800572D8(u8 arg0) {
    u8 data[0x28];
    HAL_Memset((char *)&data[8], 0xA, 0x20);
    func_80057210(arg0, &data[8], 0, 0x20);
}

s32 func_80057318(u8 arg0) {
    u8 data[0x20];
    s32 result;
    result = func_8005718C(arg0, data, 0x2000, 0x20);
    if (result != 0) {
        return result;
    }
    if (data[0] == 1) {
        _bzero(data, 0x20);
        result = func_80057210(arg0, data, 0x2000, 0x20);
        if (result != 0) {
            return result;
        }
    }
    HAL_Memset((char *)data, 1, 0x20);
    result = func_80057210(arg0, data, 0x2000, 0x20);
    if (result != 0) {
        return result;
    }
}

s32 func_800573C4(u8 arg0, u8 *arg1, u8 arg2) {
    u8 data[0x20];
    s32 result;
    HAL_Memset((char *)data, arg2, 0x20);
    result = func_80057210(arg0, data, 0x4000, 0x20);
    if (result != 0) {
        return result;
    }
    result = func_8005718C(arg0, data, 0xA000, 0x20);
    if (result != 0) {
        return result;
    }
    *arg1 = data[0];
    return result;
}

s32 func_80057450(u8 arg0, u8 arg1, u8 arg2) {
    u8 data[0x20];
    s32 result;
    HAL_Memset((char *)data, arg2, 0x20);
    result = func_80057210(arg0, data, 0x4000, 0x20);
    if (result != 0) {
        return result;
    }
    HAL_Memset((char *)data, arg1, 0x20);
    result = func_80057210(arg0, data, 0xA000, 0x20);
    if (result != 0) {
        return result;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_800574E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80057640.s")

u8 GbTower_SetPollMask(u8 arg0) {
    u8 old = D_80128557;
    D_80128557 = arg0;
    return old;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_8005777C.s")

void func_80057908(u8 arg0) {
    if (D_80128555 & (1 << arg0)) {
        D_80128558 |= 1 << arg0;
    }
}

void func_80057944(u8 arg0) { D_80128558 &= ~(1 << arg0); }

void func_80057970(u8 arg0) {
    s32 mask;
    mask = ~(1 << arg0);
    D_80128555 &= mask;
    D_80128557 &= mask;
    D_80128558 &= mask;
}
#endif
