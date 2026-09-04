#include "global.h"


#ifdef VERSION_US
u16 func_800579D0(const u8* arg0) {
    return (u16)((arg0[1] << 8) | arg0[0]);
}
#endif

#ifdef VERSION_US
void func_800579E8(u8 *arg0, u16 arg1)
{
  u16 new_var;
  arg0[0] = arg1 & 0xFFFF;
  arg0[1] = (new_var = arg1 >> 8);
}
#endif

#ifdef VERSION_US
void func_800579FC(void) {}
void func_800579FC_padding(void) {}
void func_800579FC_padding2(void) {}
void func_800579FC_padding3(void) {}
#endif

#ifdef VERSION_US
extern u8 D_80128574[];
s32 func_80057A1C(s32 arg0) {
    u8 value = D_80128574[arg0 * 0x70];
    if ((value == 5) || (value == 6)) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern u8 D_80128574[]; s32 func_80057A5C(s32 index) { return D_80128574[index * 112] == 7; }
#endif

#ifdef VERSION_US
u8 func_8005D92C(s32);
s32 func_80057A80(s32 arg0) {
    s32 v0 = func_8005D92C(arg0);
    if (v0 == 1 || v0 == 2 || v0 == 3 || v0 == 4) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057ACC.s")
#endif

#ifdef VERSION_US
s32 GbPak_WriteCommand(s32, s32, s32, s32);
s32 func_80057ACC(s32, s32, s32, s32);
s32 func_80057BCC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if ((GbPak_WriteCommand(arg0, arg1, arg2, arg3) == 0) && (func_80057ACC(arg0, arg1, arg2, arg3) != 0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 == 4) {
        return 0;
    }
    goto loop_1;
}
#endif

#ifdef VERSION_US
s32 func_80057C74(s8 *arg0) {
    s32 i = 0;
    if (*arg0++ == 0x50) return 1;
    i += 1;
    if (*arg0++ == 0x50) return 1;
    i += 1;
    if (*arg0++ == 0x50) return 1;
    i = 3;
    while (i != 0xB) {
        i += 4;
        if (*arg0++ == 0x50) return 1;
        if (*arg0++ == 0x50) return 1;
        if (*arg0++ == 0x50) return 1;
        if (*arg0++ == 0x50) return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057D74.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057E08.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057EB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80057F58.s")
#endif

#ifdef VERSION_US
void GbSave_ComputeChecksum(u8 *start, u8 *end) {
    s32 sum = 0;

    while (start < end) {
        sum += *start++;
    }
    *end = 0xFF - (sum & 0xFF);
}
#endif

#ifdef VERSION_US
void GbSave_ComputeChecksumRange(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 sum;
    sum = 0;
    if (arg0 <= arg1) {
        do {
            sum += *arg0++;
        } while (arg0 <= arg1);
    }
    func_800579E8(arg2, sum);
}
#endif

#ifdef VERSION_US
extern s32 func_80057294(u8, OSGbpakId *, u8 *);
extern s32 HAL_Strcmp(const s8 *, const s8 *);
s32 GbSave_IdentifyFormat(s32 arg0) {
    OSGbpakId id;
    u8 status;
    s32 result = 0;
    if (func_80057294(arg0 & 0xFF, &id, &status) == 0 && id.company_code == 0x3031 && id.country_code != 0) {
        id.game_title[7] = 0;
        if (HAL_Strcmp(id.game_title, (const s8 *)"POKEMON") == 0) {
            if (HAL_Strcmp(id.game_title + 8, (const s8 *)"RED") == 0) result = 1;
            else if (HAL_Strcmp(id.game_title + 8, (const s8 *)"GREEN") == 0) result = 2;
            else if (HAL_Strcmp(id.game_title + 8, (const s8 *)"BLUE") == 0) result = 3;
            else {
                id.game_title[9] = 0;
                if (HAL_Strcmp(id.game_title + 8, (const s8 *)"Y") == 0) result = 4;
                else if (HAL_Strcmp(id.game_title + 8, (const s8 *)"G") == 0) result = 5;
                else if (HAL_Strcmp(id.game_title + 8, (const s8 *)"S") == 0) result = 6;
            }
        } else if (HAL_Strcmp(id.game_title, (const s8 *)"PM_CRYS") == 0) result = 7;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005818C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058288.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058614.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_800587BC.s")
#endif

#ifdef VERSION_US
s32 func_80058850(u8 arg0) {
    return (arg0 < 0x29) ? ((arg0 + 0x2A4) & 0xFFFF) : ((arg0 + 0x2A7) & 0xFFFF);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058880.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005892C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_800589A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058C6C.s")
#endif

#ifdef VERSION_US
s32 func_80058D18(s32 arg0)
{
    s32 result = 0;
    switch (func_8005D92C(arg0)) {
    case 1:
    case 2:
    case 3:
    case 4:
        result = func_8005892C(arg0);
        break;
    case 5:
    case 6:
        result = func_800589A4(arg0);
        break;
    case 7:
        result = func_80058C6C(arg0);
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
extern u8 D_801285D8[];
void func_80058D98(s32 arg0) {
    func_80057BCC(arg0, *(s32 *)(D_801285D8 + arg0 * 112), 0x600, 0x640);
}
void func_80058D98_padding(void) {}
void func_80058D98_padding2(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058DE4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058E60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80058F18.s")
#endif

#ifdef VERSION_US
s32 func_80058FD0(s32 arg0) {
    s32 result = 0;
    switch (func_8005D92C(arg0)) {
    case 1:
    case 2:
    case 3:
    case 4:
        result = func_80058DE4(arg0);
        break;
    case 5:
    case 6:
        result = func_80058E60(arg0);
        break;
    case 7:
        result = func_80058F18(arg0);
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
extern u8 D_801285D4[];
extern s32 GbPak_ReadCommand(s32, s32, s32, s32);
extern s32 func_800591BC(s32, s32);
s32 func_80059050(s32 arg0, s32 arg1) {
    s32 base = *(s32 *)(D_801285D4 + arg0 * 112);
    s32 size = (arg1 == 0) ? 0x4000 : 0x6000;
    return GbPak_ReadCommand(arg0, base + arg1 * 0x1A60, size, 0x1A60) == 0;
}
#endif

#ifdef VERSION_US
s32 func_800590CC(s32 arg0) {
    if (func_80059050(arg0, 0) != 0) {
        return func_80059050(arg0, 1);
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern void func_8005F190();
extern s32 GbPak_ReadCommand();
extern u8 D_80128570[];
extern u8 D_801285D4[];
s32 func_8005910C(s32 arg0) {
    return GbPak_ReadCommand(arg0, *(s32 *)(D_801285D4 + arg0 * 112), 0x4000, 0x3E40) == 0;
}
#endif

#ifdef VERSION_US
s32 func_8005914C(s32 arg0) {
    s32 result;
    result = 0x0;
    switch ((u16)func_8005D92C(arg0)) {
    case 1:
    case 2:
    case 3:
    case 4:
        result = func_800590CC(arg0);
        break;
    case 5:
    case 6:
    case 7:
        result = func_8005910C(arg0);
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
extern s32 func_80057BCC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_800591BC(s32 arg0, s32 arg1) {
    s32 base = *(s32 *)(D_801285D4 + arg0 * 112);
    s32 size = (arg1 == 0) ? 0x4000 : 0x6000;
    return func_80057BCC(arg0, base + arg1 * 0x1A60, size, 0x1A60);
}
#endif

#ifdef VERSION_US
s32 func_80059234(s32 arg0) {
    if (func_800591BC(arg0, 0) != 0) {
        return func_800591BC(arg0, 1);
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern u8 D_801285D4[];
void func_80059274(s32 arg0) {
    func_80057BCC(arg0, *(s32 *)(D_801285D4 + arg0 * 112), 0x4000, 0x3E40);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_800592B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059320.s")
#endif

#ifdef VERSION_US
void func_80059468(s32 arg0) {
    func_80059320(arg0, 4);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059488.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059578.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059670.s")
#endif

#ifdef VERSION_US
extern u8 D_80128570[];
extern s32 D_80128730[];
void func_800596D0(s32 arg0, u32 arg1) {
    u8 *record;
    s32 index;
    if (arg1 >= 0x44415430U && arg1 < 0x44415434U) {
        index = arg1 - 0x44415430U;
        record = D_80128570 + index * 0x70;
        *(u32 *)record &= 0xDFFFFFFE;
        *(u32 *)(record + 0x60) = 0;
        return;
    }
    if (arg1 >= 0x424F5830U && arg1 < 0x424F5834U) {
        index = arg1 - 0x424F5830U;
        record = D_80128570 + index * 0x70;
        *(u32 *)record &= 0xBFFFFFFB;
        *(u32 *)(record + 0x64) = 0;
        return;
    }
    if (arg1 >= 0x44543230U && arg1 < 0x44543234U) {
        index = arg1 - 0x44543230U;
        record = D_80128570 + index * 0x70;
        *(u32 *)record &= 0xDFFFFFFD;
        *(u32 *)(record + 0x68) = 0;
        return;
    }
    if (arg1 >= 0x50545030U && arg1 < 0x50545034U) {
        index = arg1 - 0x50545030U;
        record = D_80128570 + index * 0x70;
        *(u32 *)record &= 0xDFFFFFF7;
        *(u32 *)(record + 0x6C) = 0;
        return;
    }
    if (arg1 >= 0x444C4430U && arg1 < 0x444C4434U) {
        index = arg1 - 0x444C4430U;
        record = D_80128570 + index * 0x70;
        *(u32 *)record &= 0xDFFFFFEF;
        D_80128730[index] = 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005989C.s")
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_80059AE0(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x10000) != 0; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059B08.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059D00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059DD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80059EF8.s")
#endif

#ifdef VERSION_US
void func_8005A014(s32 arg0) {
    func_80059EF8(arg0, 1);
}
#endif

#ifdef VERSION_US
void func_8005A034(s32 arg0) {
    func_80059EF8(arg0, 2);
}
#endif

#ifdef VERSION_US
void func_8005A054(s32 arg0) {
    func_80059EF8(arg0, 5);
}
#endif

#ifdef VERSION_US
void func_8005A074(s32 arg0) {
    func_80059EF8(arg0, 8);
}
#endif

#ifdef VERSION_US
void func_8005A094(s32 arg0) {
    func_80059EF8(arg0, 16);
}
#endif

#ifdef VERSION_US
s32 func_8005A0B4(s32 arg0) {
    s32 result = func_80059EF8(arg0, 5);
    if (result != 0) {
        func_8005E6B8(arg0);
    }
    return result;
}
#endif

#ifdef VERSION_US
s32 func_8005A0F4(s32 arg0) {
    s32 result = func_80059EF8(arg0, 7);
    if (result != 0) {
        func_8005E6B8(arg0);
    }
    return result;
}
#endif

#ifdef VERSION_US
s32 func_8005A134(s32 arg0) {
    s32 result = func_80059EF8(arg0, 0xFF);
    if (result != 0) {
        func_8005E6B8(arg0);
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A174.s")
#endif

#ifdef VERSION_US
extern u8 D_80097374[];
extern s32 GbPak_IsCartOff(s32);
extern s32 GbPak_IsCartOn(s32);
extern s32 func_80056F7C(s32);
extern s32 GbTower_VerifyPakStillInserted(s32, u8 *);
extern s32 GbSave_IdentifyFormat(s32 arg0);
extern u8 D_80128570[];
s32 GbTower_PollPortState(s32 arg0) {
    s32 result = 0;
    u8 *status = D_80097374 + arg0;
    switch (*status) {
    case 0:
        GbTower_CheckPakRemoved(arg0, 0);
        *status += 1;
    case 1:
        if (GbPak_IsCartOff(arg0) != 0) {
            *status += 1;
        }
        break;
    case 2:
        if (GbPak_IsCartOn(arg0) != 0) {
            *status += 1;
        }
        result = 1;
        break;
    case 3:
        if (func_80056F7C(arg0) != 0) {
            result = 3;
            if (GbSave_IdentifyFormat(arg0) == *(u8 *)(D_80128570 + arg0 * 0x70 + 4)) {
                if (GbTower_VerifyPakStillInserted(arg0, D_80128570 + arg0 * 0x70 + 0x28) != 0) {
                    result = 2;
                }
            }
        }
        *status = 0;
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A364.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A468.s")
#endif

#ifdef VERSION_US
u8 func_8005A5C4(u8 arg0, u8 *arg1) {
    arg0 = arg0 & 0xFF;
    switch (arg0) {
    case 0xBB:
        *arg1 |= 1;
        break;
    case 0xBD:
        *arg1 |= 2;
        break;
    }
    return *arg1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A60C.s")
#endif

void func_8005A8E4(void) {
}

#ifdef VERSION_US
u8 func_8005A8EC(u8 arg0, u8 *arg1) {
    arg0 = arg0 & 0xFF;
    if (arg0 != 0x46) {
        if (arg0 == 0x74) {
            *arg1 |= 4;
        }
    } else {
        *arg1 |= 8;
    }
    return *arg1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A92C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005A98C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005ACE8.s")
#endif

#ifdef VERSION_US
extern s8 func_80059B08(s32);
extern void func_8005D964(s32);
extern s32 func_8005989C(s32);
extern void func_8005ACE8(s32);
extern u8 D_80128570[];
void func_8005AD58(s32 arg0) {
    u8 *record = D_80128570 + arg0 * 112;
    s8 result;
    *(s32 *)record &= 0xFF0000FF;
    result = func_80059B08(arg0);
    record[5] = result;
    if ((result & 0xFF) == 0) {
        func_8005D964(arg0);
        func_8005989C(arg0);
        func_8005ACE8(arg0);
    }
}
#endif

#ifdef VERSION_US
extern void func_80055948(s32);
extern s32 func_80056870(s32, u8 *, void *);
extern void func_80054E48(s32);
extern void func_8005AD58(s32 arg0);
extern u8 D_80128570[];
extern s32 D_80128748;
void GbTower_StartPortSession(s32 arg0) {
    u8 flag;
    if (D_80128748 & (1 << arg0)) {
        func_80055948(3);
        if (func_80056870(arg0, &flag, (s32 *)(D_80128570 + arg0 * 112) + 10) == 0) {
            Game_ShutdownAndLoadFragment(arg0, 2);
        }
        *(s32 *)(D_80128570 + arg0 * 112) |= 0x80000000;
        func_8005AD58(arg0);
        if (GbTower_CheckPakRemoved(arg0, flag) == 0) {
            Game_ShutdownAndLoadFragment(arg0, 2);
        }
        func_80054E48(3);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005AEA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005AFF4.s")
#endif

#ifdef VERSION_US
void func_8005B058(s32 arg0) {
    func_80059320(arg0, 1);
}
#endif

#ifdef VERSION_US
s32 func_80057A80(s32);
s32 func_8005B078(s32 arg0) {
    if (func_80057A80(arg0) != 0) {
        return 1;
    }
    return func_80059320(arg0, 2);
}
#endif

#ifdef VERSION_US
s32 func_80057A80(s32);
s32 func_8005B0B0(s32 arg0) {
    if (func_80057A80(arg0) != 0) {
        return 1;
    }
    return func_80059320(arg0, 8);
}
#endif

#ifdef VERSION_US
s32 func_80057A80(s32);
s32 func_8005B0E8(s32 arg0) {
    if (func_80057A80(arg0) != 0) {
        return 1;
    }
    return func_80059320(arg0, 16);
}
#endif

#ifdef VERSION_US
void func_8005B120(s32 arg0) {
    func_80059320(arg0, 0xFF);
}
#endif

#ifdef VERSION_US
extern u8 D_80128570[];
extern s32 GbPak_ValidateAndRefresh(s32, s32, u8 *);
void func_8005B140(s32 arg0) {
    if (GbPak_ValidateAndRefresh(arg0, 0, D_80128570 + arg0 * 112 + 0x28) == 0) {
        Game_ShutdownAndLoadFragment(arg0, 2);
    }
}
#endif

#ifdef VERSION_US
void GbSave_RequirePakPresent(s32 arg0) {
    if (GbTower_CheckPakRemoved(arg0, 0) == 0)
        Game_ShutdownAndLoadFragment(arg0, 2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B1C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B280.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B314.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B378.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B4B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B5D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B6F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B778.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B848.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005B924.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BA00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BA88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BBD4.s")
#endif

#ifdef VERSION_US
s32 func_80057A80(s32);
extern void func_8005BA88(s32, s32, s32, s32);
extern void func_8005BBD4(s32, s32, s32, s32);
void func_8005BCF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_80057A80(arg1) != 0) {
        func_8005BA88(arg0, arg1, arg2, arg3);
        return;
    }
    func_8005BBD4(arg0, arg1, arg2, arg3);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BD4C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BE08.s")
#endif

#ifdef VERSION_US
s32 func_80057A80(s32);
extern void func_8005BD4C(s32, s32, s32, s32);
extern void func_8005BE08(s32, s32, s32, s32);
void func_8005BECC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_80057A80(arg1) != 0) {
        func_8005BD4C(arg0, arg1, arg2, arg3);
        return;
    }
    func_8005BE08(arg0, arg1, arg2, arg3);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BF28.s")
#endif

#ifdef VERSION_US
u8 *func_8005B280();

u8 func_8005BF78(void) {
    u8 *temp_v0;
    u8 var_v1;

    temp_v0 = func_8005B280();
    if (temp_v0 != NULL) {
        var_v1 = *temp_v0;
    } else {
        var_v1 = 0;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005BFA8.s")
#endif

#ifdef VERSION_US
typedef struct S1_GbSaveBoxEntry S1_GbSaveBoxEntry;
struct S1_GbSaveBoxEntry {
      u8 count;
      u8 speciesIndices[1];
      char unk002[0x12];
};
void func_8005BFF0(s32 arg0, s32 arg1, s32 arg2) {
    S1_GbSaveBoxEntry* temp_v0 = func_8005B1C4(arg0, arg1);

    if (temp_v0 != NULL) {
        temp_v0->count = arg2;
        temp_v0->speciesIndices[arg2] = 0xFF;
    }
}
#endif

#ifdef VERSION_US
void func_8005C028(s32 arg0, s32 arg1, s32 arg2) {
    S1_GbSaveBoxEntry* temp_v0 = func_8005B280(arg0, arg1);

    if (temp_v0 != NULL) {
        temp_v0->count = arg2;
        temp_v0->speciesIndices[arg2] = 0xFF;
    }
}
#endif

#ifdef VERSION_US
void func_8005C060(s32 arg0, s32 arg1, s32 arg2) {
    if (func_80057A80(arg0) != 0) {
        func_8005BFF0(arg0, arg1, arg2);
        return;
    }
    func_8005C028(arg0, arg1, arg2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C0B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C12C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C1AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C22C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C2B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C2FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C348.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C394.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C41C.s")
#endif

#ifdef VERSION_US
extern u8 D_801285D0[];
extern u8 D_801285D8[];
extern void _bcopy(s32, s32, s32);
extern void _bzero(s32, s32);
void func_8005C52C(s32 arg0, s32 arg1) {
    s32 v0 = *(s32 *)(D_801285D0 + arg1 * 112);
    _bzero(arg0, 0x98);
    _bcopy(v0 + 0x49, arg0 + 0x39, 0x2A);
}
#endif

#ifdef VERSION_US
void func_8005C584(s32 arg0, s32 arg1) {
    s32 v0 = *(s32 *)(D_801285D0 + arg1 * 112);
    _bcopy(v0 + 0x3E6, arg0, 0x98);
}
#endif

#ifdef VERSION_US
void func_8005C5CC(s32 arg0, s32 arg1) {
    s32 v0 = *(s32 *)(D_801285D0 + arg1 * 112);
    _bcopy(v0 + 0x3E7, arg0, 0x98);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C614.s")
#endif

#ifdef VERSION_US
void func_8005C694(s32 arg0, s32 arg1) {
    s32 v0 = *(s32 *)(D_801285D0 + arg1 * 112);
    _bcopy(arg0 + 0x39, v0 + 0x49, 0x2A);
}
#endif

#ifdef VERSION_US
void func_8005C6D8(s32 arg0, s32 arg1) {
    s32 v0 = *(s32 *)(D_801285D0 + arg1 * 112);
    _bcopy(arg0, v0 + 0x3E6, 0x98);
}
#endif

#ifdef VERSION_US
void func_8005C714(s32 arg0, s32 arg1) {
    s32 v0 = *(s32 *)(D_801285D0 + arg1 * 112);
    _bcopy(arg0, v0 + 0x3E7, 0x98);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C750.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C7D0.s")
#endif

#ifdef VERSION_US
extern void func_8006276C(s32, s32);
void func_8005C880(s32 arg0, s32 arg1, s32 arg2) {
    s32 offset = arg2 * 47;
    s32 v0 = *(s32 *)(D_801285D8 + arg1 * 112);
    func_8006276C(v0 + offset + 0x40C, arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C8D8.s")
#endif

#ifdef VERSION_US
void func_8005C988(s32 arg0, s32 arg1, s32 arg2) {
    s32 offset = arg2 * 47;
    s32 v0 = *(s32 *)(D_801285D8 + arg1 * 112);
    func_8006276C(v0 + offset + 0x11A, arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005C9E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CAA4.s")
#endif

#ifdef VERSION_US
s32 func_8005CB38(s32 arg0, s32 arg1) {
    s32 result = 0;
    switch ((s32)arg1) {
    case 0x21:
        if (func_80057A80(arg0) != 0) {
            result = 0xC;
        } else {
            result = 0xE;
        }
        break;
    case 0x20:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
        result = 1;
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CBA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CC14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CCD8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CDDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005CF20.s")
#endif

#ifdef VERSION_US
extern s32 func_8005CF20(s32, s32, s32);
extern u8 D_801285D0[];
void func_8005CFE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 record = *(s32 *)(D_801285D0 + arg1 * 112);
    if (arg3 < func_8005CF20(arg0, arg1, arg2)) {
        switch (arg0) {
        case 0x20:
            *(u8 *)(record + 0x9AC) = arg3;
            *(u8 *)(record + arg3 + 0x9AD) = 0xFF;
            break;
        case 0x21:
            func_8005C060(arg1, arg2, arg3);
            break;
        case 0x22:
            *(u8 *)(record + 0x266) = arg3;
            *(u8 *)(record + arg3 * 2 + 0x267) = 0xFF;
            break;
        case 0x23:
            break;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D0B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D194.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D2BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D348.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D418.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D4FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D610.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D698.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D778.s")
#endif

#ifdef VERSION_US
extern s32 D_80128748;

s32 func_8005D8C0(void) {
    return D_80128748;
}
#endif

#ifdef VERSION_US
extern u8 D_80128575[]; u8 func_8005D8CC(s32 index) { return D_80128575[index * 112]; }
#endif

#ifdef VERSION_US
extern u8 D_8012874C;
extern u8 D_8012874D;
s32 GbSave_GetPortAvailability(s32 arg0) {
    s32 mask = 1 << arg0;
    if (!(D_8012874C & mask)) {
        return 1;
    }
    if (!(D_8012874D & mask)) {
        return 2;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern u8 D_80128574[]; u8 func_8005D92C(s32 index) { return D_80128574[index * 112]; }
#endif

#ifdef VERSION_US
extern u8 D_801285B8[]; u8 func_8005D948(s32 index) { return D_801285B8[index * 112]; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D964.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005D9E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005DA1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005DAC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005DB84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005DC48.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005DD14.s")
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DDD4(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x100) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DDF8(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x200) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DE1C(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x200000) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DE44(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x400) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DE68(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x1000) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DE8C(s32 index) { return !((*(u32 *)(D_80128570 + index * 112) & 0x2000) != 0); }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DEB4(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x800) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DED8(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x4000) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DEFC(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x8000) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DF20(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x40000) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DF48(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x80000) != 0; }
#endif

#ifdef VERSION_US
extern u8 D_80128570[]; s32 func_8005DF70(s32 index) { return (*(u32 *)(D_80128570 + index * 112) & 0x100000) != 0; }
#endif

#ifdef VERSION_US
u8 func_8005DF98(s32 i) {
    u8 *p = (u8 *)D_80128570 + i * 0x70;
    u8 r = 0;
    if (*(s32 *)p & 2)
        r = *(u8 *)(*(s32 *)(p + 0x68) + 0x5e4);
    return r;
}
#endif

#ifdef VERSION_US
extern u8 D_80128570[];
extern void func_8005F9CC(s32, s32);
extern void func_8005F9F4(s32, s32);
void func_8005DFD4(s32 arg0, u8 arg1)
{
  u8 *rec = D_80128570 + (arg0 * 112);
  if ((*((u32 *) rec)) & 2)
  {
    s32 t0 = *((s32 *) (rec + 0x68));
    *((u8 *) ((*((s32 *) (rec + 0x68))) + 0x5E4)) = arg1;
    if (arg1 == 0)
    {
      func_8005F9CC(arg0, 0x711);
    }
    else
    {
      func_8005F9F4(arg0, 0x711);
    }
  }
}
#endif

#ifdef VERSION_US
extern u8 D_80128570[];
u8 func_8005E03C(s32 arg0) {
    u8 *entry = D_80128570 + (arg0 * 0x70);
    if (*(u32 *)entry & 2) {
        return *(u8 *)(*(u8 **)(entry + 0x68) + 0x5E5);
    }
    return 0;
}
#endif

#ifdef VERSION_US
void func_8005E07C(s32 arg0, u8 arg1) { u8 *entry = D_80128570 + arg0 * 0x70; if ((*(u32 *)entry & 2) != 0) *(u8 *)(*(u8 **)(entry + 0x68) + 0x5E5) = arg1; }
#endif

#ifdef VERSION_US
extern void func_80060A84(u8* arg0, s32 arg1);
extern u8 D_80128570[];
void func_8005E0BC(s32 arg0, u8 arg1, u16 arg2) {
    u8 *entry = D_80128570 + arg0 * 112;
    u8 index = arg1;
    u16 value = arg2;
    if ((*(u32 *)entry & 2) != 0 && index < 5) {
        func_80060A84(*(u8 **)(entry + 0x68) + index * 2 + 0x5E6, value);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E12C.s")
#endif

#ifdef VERSION_US
extern u8 D_80128570[];
void func_8005E1F0(u8 arg0, void *arg1) {
    typedef struct { u8 bytes[0x32]; } Copy32;
    u8 *entry;

    entry = D_80128570 + arg0 * 0x70;
    (*(u8 **)(entry + 0x68))[0x5FD] = 1;
    *(Copy32 *)((*(u8 **)(entry + 0x68)) + 0x5FE) = *(Copy32 *)arg1;
}
#endif

#ifdef VERSION_US
void func_8005E278(u8 arg0, s32 arg1) {
    s32 idx = arg0;
    _bcopy(*(s32 *)(D_801285D8 + idx * 112) + 0x5FA, arg1, 3);
}
#endif

#ifdef VERSION_US
void func_8005E2BC(u8 arg0, s32 arg1) {
    _bcopy(arg1, *(s32 *)(D_801285D8 + arg0 * 112) + 0x5FA, 3);
}
#endif

#ifdef VERSION_US
s32 func_8005E304(s32 arg0, void *arg1) {
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = (arg0 * 0x70) + D_80128570;
    temp_v1 = ((*(s32 *)((u8 *)(temp_v0) + (0))) & 1) != 0;
    if (temp_v1 != 0) {
        (*(u8 *)((u8 *)(arg1) + (0))) = (u8) (*(u8 *)((u8 *)(temp_v0) + (4)));
        (*(s8 *)((u8 *)(arg1) + (1))) = (s8) (*(u16 *)((u8 *)(temp_v0) + (6)));
        (*(u16 *)((u8 *)(arg1) + (2))) = (u16) (*(u16 *)((u8 *)(temp_v0) + (0x50)));
    }
    return temp_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E350.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E420.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E524.s")
#endif

#ifdef VERSION_US
extern u8 D_80128570[];
extern void _bzero(s32, s32);
extern void func_8005E350(s32, u8, s32, s32);
extern void func_8005E524(s32, s32);
void func_8005E5D8(s32 arg0) {
    s32 sp1C;
    s32 sp20;

    sp20 = *(s32 *)(D_80128570 + arg0 * 112 + 0x60);
    sp1C = (s32)(D_80128570 + arg0 * 112 + 8);
    _bzero(sp1C, 0x20);
    func_8005E350(sp1C, *(u8 *)(sp20 + 0x88A), sp20 + 0x88B, 1);
    func_8005E524((u8)arg0, sp1C);
}
#endif

#ifdef VERSION_US
void func_8005E648(s32 arg0) {
    s32 sp1C;
    s32 sp20;

    sp20 = *(s32 *)(D_80128570 + arg0 * 112 + 0x60);
    sp1C = (s32)(D_80128570 + arg0 * 112 + 8);
    _bzero(sp1C, 0x20);
    func_8005E350(sp1C, *(u8 *)(sp20 + 0x865), sp20 + 0x866, 1);
    func_8005E524((u8)arg0, sp1C);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E6B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E728.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005E8A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005EB3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005ECA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005ED78.s")
#endif

#ifdef VERSION_US
extern void func_8005EB3C(void *, s32);

void func_8005EE4C(s32 arg0) {
    func_8005EB3C((arg0 * 0x70) + 8 + D_80128570, 0xFB);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005EE88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005EF78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F04C.s")
#endif

#ifdef VERSION_US
extern u8 D_8012874D;
extern s32 D_80128748;
extern void func_8005A174(s32, s32 *);
void func_8005F0B8(s32 arg0) {
    s32 *arg0p;
    s32 temp_a0;
    s32 temp_v0;
    arg0p = &arg0;
    temp_a0 = *arg0p & 0xFF;
    temp_v0 = ~(1 << temp_a0);
    D_8012874D &= temp_v0;
    D_80128748 &= temp_v0;
    func_8005A174(temp_a0, &D_80128748);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F110.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F190.s")
#endif

#ifdef VERSION_US
void func_8005F37C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 *arg0p = &arg0;
    s32 masked = *arg0p & 0xFF;
    func_8005F190(masked, arg1, arg2, arg3, arg4, 1);
}
#endif

#ifdef VERSION_US
void func_8005F3B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8005F190(arg0 & 0xFF, arg1, arg2, arg3, arg4, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F3E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F5D4.s")
#endif

#ifdef VERSION_US
extern void func_8005F3E0(s32, s32, s32, s32, s32, s32);
void func_8005F620(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    func_8005F3E0(arg0 & 0xFF, arg1 & 0xFFFF, arg2 & 0xFF, arg3 & 0xFF, (s32) arg4, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F668.s")
#endif

#ifdef VERSION_US
extern void func_8005F668(s32, s32, s32);
extern void func_8005F808(s32, s32, s32);
void func_8005F790(s32 arg0, s32 arg1) {
    s32 *p = &arg1;
    func_8005F668(arg0, arg1 & 0xFF, 0);
}
#endif

#ifdef VERSION_US
void func_8005F7B8(s32 arg0, s32 arg1) {
    s32 *p = &arg1;
    func_8005F668(arg0, arg1 & 0xFF, 1);
}
#endif

#ifdef VERSION_US
void func_8005F7E0(s32 arg0, s32 arg1) {
    s32 *p = &arg1;
    func_8005F668(arg0, arg1 & 0xFF, 2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005F808.s")
#endif

#ifdef VERSION_US
void func_8005F9A4(s32 arg0, s32 arg1) {
    s32 *p = &arg1;
    func_8005F808(arg0, arg1 & 0xFFFF, 0);
}
#endif

#ifdef VERSION_US
void func_8005F9CC(s32 arg0, s32 arg1) {
    s32 *p = &arg1;
    func_8005F808(arg0, arg1 & 0xFFFF, 1);
}
#endif

#ifdef VERSION_US

void func_8005F9F4(s32 arg0, s32 arg1) {
    s32 *p = &arg1;
    func_8005F808(arg0, arg1 & 0xFFFF, 2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FA1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FAB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FB40.s")
#endif

#ifdef VERSION_US
extern u8 func_8005D92C(s32 index);
extern u8 D_80128570[];
void func_8005FBCC(s32 arg0, u8 arg1, u8 arg2) {
    if ((*(s32 *)(D_80128570 + arg0 * 112) & 1) != 0) {
        switch (func_8005D92C(arg0)) {
        case 5:
        case 6:
            *(u8 *)(*(s32 *)(D_80128570 + arg0 * 112 + 0x60) + 0x86B) = arg1;
            *(u8 *)(*(s32 *)(D_80128570 + arg0 * 112 + 0x60) + 0x86A) = arg2;
            break;
        case 7:
            *(u8 *)(*(s32 *)(D_80128570 + arg0 * 112 + 0x60) + 0x846) = arg1;
            *(u8 *)(*(s32 *)(D_80128570 + arg0 * 112 + 0x60) + 0x845) = arg2;
            break;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FC7C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FD24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FDB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FE58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FF0C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8005FFB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80060110.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_800601A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80060250.s")
#endif

#ifdef VERSION_US
s32 func_80060348(s32 arg0, s32 arg1) {
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_80060358(s32 arg0, s32 arg1) {
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80060368.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_80060538.s")
#endif

#ifdef VERSION_US
u8 *func_800606D8(u8 *arg0) {
    return (u8 *)"";
}
#endif

#ifdef VERSION_US
s32 func_800606E8(s32 arg0) {
    return 0;
}
#endif

#ifdef VERSION_US
u8 func_800606F4(s32 arg0) {
    u8 var_v1;
    void *temp_v0;

    temp_v0 = (arg0 * 0x70) + D_80128570;
    var_v1 = 0;
    if ((*(u8 *)((u8 *)(temp_v0) + (4))) == 7) {
        var_v1 = (*(u8 *)((u8 *)(temp_v0) + (0x49)));
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8006072C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/585D0/func_8006092C.s")
#endif
