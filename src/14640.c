#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80013A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80013A8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80013B54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80013C40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80013EF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014190.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014208.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014280.s")

extern u8 D_8011BE90[];
extern u8 *D_80121EDC[];
void func_800142F8(s32 arg0, s32 arg1) { if (arg0 != 0xFF) { u8 *ptr = D_8011BE90 + arg0; if (ptr[0x3364] != 5) ptr[0x3364] = arg1; } }

void func_80014328(s32 arg0, s32 arg1) { if (arg0 != 0xFF) { u8 *ptr = D_8011BE90 + arg0; if (ptr[0x33C8] != 5) ptr[0x33C8] = arg1; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014358.s")

void func_800143B8(s32 arg0, s32 arg1) { if (arg0 != 0xFF) { u8 *ptr = D_8011BE90 + arg0; if (ptr[0x3300] != 5) ptr[0x3300] = arg1; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_800143E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014448.s")

extern void func_80014448(s32, void *);
extern s32 func_80014BD4(s32);
void func_800144E4(s32 arg0, s32 arg1, s32 arg2, OSMesgQueue *arg3) {
    s32 temp[2];
    if (arg1 & 2) {
        func_80014448(arg0, &temp[0]);
    }
    if (arg1 & 1) {
        func_80014BD4(arg0);
    }
    if (arg2 != 0) {
        osSendMesg(arg3, (OSMesg)(arg2 << 24), 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001454C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014638.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014708.s")

extern void func_80014708(s32, s32, s32, s32, s32);
void func_80014740(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { func_80014708(0, arg0, 0, arg2, arg3); }

void func_80014784(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { func_80014708(2, arg0, 0, arg2, arg3); }

void func_800147C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { func_80014708(1, arg0, 0, arg2, arg3); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001480C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014850.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014900.s")

s32 func_8001519C(s32 arg0);
s32 func_8001519C(s32 arg0);
void func_800149A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v1;

    temp_v1 = func_8001519C(arg0) + (arg1 * 0x10);
    if ((*(s8 *)((u8 *)(temp_v1) + (0x18))) == 5) {
        switch (arg2) {                             /* irregular */
        case 0:
            (*(s32 *)((u8 *)(temp_v1) + (0x10))) = arg3;
            return;
        case 1:
            (*(s32 *)((u8 *)(temp_v1) + (0x14))) = arg3;
            break;
        }
    }
}

s32 func_80014A18(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 func_80014AA8();
    if (*(s32 *)(D_8011BE90 + 0x2D14) != 0) {
        return 0;
    }
    *(s32 *)(*(u8 **)(D_8011BE90 + (arg0 * 4) + 0x604C) + 0xDC) = 0;
    return func_80014AA8(arg0, arg1, arg2);
}

extern s32 func_80014AA8(s32, s32, s32);
s32 func_80014A5C(s32 arg0, s32 arg1, s32 arg2) {
    if (*(s32 *)(D_8011BE90 + 0x2D14) != 0) {
        return 0;
    }
    *(s32 *)(*(u8 **)(D_8011BE90 + (arg0 * 4) + 0x604C) + 0xDC) = arg2;
    return func_80014AA8(arg0, arg1, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014AA8.s")

extern s32 func_80014E68(s32, s32, void *);
extern s32 func_8001510C(s32, s32);
extern u8 D_8011F258;
s32 func_80014BD4(s32 arg0) {
    struct { s32 pad; s32 value[2]; } sp20;
    s32 index;
    index = func_8001510C(0, arg0);
    if (((u8 *)&D_8011F258)[index] == 1) {
        return 0;
    }
    return func_80014E68(0, arg0, &sp20.value[0]);
}

void func_80014C28(s32 arg0, s32 arg1) { func_80014C48(arg0, arg1, 1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014C48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014D64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80014E68.s")

s32 func_8001519C(s32);
s32 func_8001510C(s32 arg0, s32 arg1) {
    u8 *temp_v1;
    temp_v1 = (u8 *)(u32)func_8001519C(arg0) + (arg1 << 4);
    if (*(s32 *)(temp_v1 + 0x14) == 0) {
        arg1 = *(s32 *)(temp_v1 + 0x10);
    }
    return arg1;
}

s32 func_80011250(s32, s32, s32);
s32 func_8001244C();
s32 func_80015148(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = func_8001244C();
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = func_80011250(arg0, 2, arg1);
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return 0;
}

extern s32 D_8011EA50;
extern s32 D_8011EA54;
extern s32 D_8011EA58;
s32 func_8001519C(s32 arg0) {
    s32 result = 0;
    switch (arg0) {
    case 0: result = D_8011EA50; break;
    case 1: result = D_8011EA54; break;
    case 2: result = D_8011EA58; break;
    default: break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_800151E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001544C.s")

void func_80015570(s32 a0, s32 a1, s32 a2, s32 a3) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80015584.s")

void func_80015664(s32 arg0, s32 arg1) { s32 value; func_80014E68(arg0, arg1, &value); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80015684.s")

void func_80015A10(s32 arg0) { func_80016148(arg0); func_80017070(arg0); func_80016624(arg0); }

extern s32 D_8008FA70; void func_80015A40(s32 value) { D_8008FA70 = value; }

extern s32 D_8008FA74; void func_80015A4C(s32 value) { D_8008FA74 = value; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80015A58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80015AB8.s")

extern u8 D_8011BE90[]; void func_80015E58(void) { *(s32 *)(D_8011BE90 + 0x2074) = 0; *(s32 *)(D_8011BE90 + 0x20D8) = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80015E6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001603C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_800160D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80016148.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_800162D0.s")

void func_80016354(s32 a0, s32 a1, s32 a2, s32 a3) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80016368.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001644C.s")

extern void *func_80016500(s32, s32, s32, s32, s32, s32, s32);
extern OSMesgQueue D_8011DE50;
void *func_8001647C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    void *temp_v0;
    void *sp2C;
    temp_v0 = func_80016500(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp2C = temp_v0;
    osSendMesg(&D_8011DE50, temp_v0, 0);
    (*(s32 *)((u8 *)sp2C + (0x18))) = arg0;
    return sp2C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80016500.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80016624.s")

void func_80016748(s32 arg0, s32 arg1) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80016754.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80016890.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80016A24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80016AB4.s")

void func_80016B24(s32 a0, s32 a1, s32 a2, s32 a3) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80016B38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80016C78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80017070.s")

s32 func_80017224(void *arg0, s32 arg1, void **arg2) {
    s32 i = 0;
    while (i < arg1) {
        if (*(s32 *)((u8 *)arg0 + 4) == *(s32 *)((u8 *)arg2[i] + 4)) {
            break;
        }
        i++;
    }
    if (i == arg1) {
        arg2[arg1] = arg0;
        arg1++;
    }
    return arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001726C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_800173A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_800173F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80017874.s")

void func_800179B4(void) {}
void func_800179B4_padding(void) {}
void func_800179B4_padding2(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_800179CC.s")

extern OSMesgQueue D_800D1320;
extern s32 osRecvMesg(OSMesgQueue *, OSMesg *, s32);
extern u8 D_800D1378;
void func_80017A38(void) {
    struct { s32 pad; void *value[2]; } sp20;
    s8 *temp_v0;
    if (osRecvMesg(&D_800D1320, (OSMesg *)sp20.value, 0) != -1) {
        temp_v0 = *(s8 **)((u8 *)&D_800D1378 + (((u32)sp20.value[0] >> 0x18) * 4));
        if (temp_v0 != NULL) {
            *temp_v0 = 0;
        }
    }
}

extern OSMesgQueue D_800D1320; extern OSMesg D_800D1338[]; void func_80017A90(void){osCreateMesgQueue(&D_800D1320,D_800D1338,0x10);}

extern s32 func_80017B00(void);
extern void func_80013A8C(void);
extern u32 osSetIntMask(u32);
s32 func_80017AC0(void) {
    u32 sp1C;
    s32 temp_v0;
    temp_v0 = func_80017B00();
    sp1C = osSetIntMask(1U);
    func_80013A8C();
    osSetIntMask(sp1C);
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80017B00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80018078.s")

void func_800185A8(s32 arg0, s32 arg1) { u8 *ptr = D_80121EDC[arg0]; if (arg1 == 0) arg1 = 1; ptr[1] = 2; *(s16 *)(ptr + 0x12) = arg1; *(f32 *)(ptr + 0x20) = -(*(f32 *)(ptr + 0x1C) / (f32)arg1); }

void func_800185E8(s32 arg0, s32 arg1) { if (arg1 != 0) { u8 *ptr = D_80121EDC[arg0]; ptr[1] = 1; *(s16 *)(ptr + 0x14) = arg1; *(s16 *)(ptr + 0x12) = arg1; *(f32 *)(ptr + 0x1C) = 0.0f; *(f32 *)(ptr + 0x20) = 0.0f; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80018620.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_800186B8.s")

void func_80018704(s32 arg0, s32 arg1) { func_800186B8(arg0, &arg1); }

void func_80018728(s32 arg0, s32 arg1) { func_800186B8(arg0, &arg1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001874C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001877C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_800187AC.s")

void func_80018810(void) {
    D_8011BE90[0x6315] = D_8011BE90[0x6314];
    D_8011BE90[0x6316] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80018828.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001895C.s")

extern OSMesgQueue D_8011DFC0;
u32 func_80018A10(s32 *arg0) {
    void *sp1C;

    if (osRecvMesg(&D_8011DFC0, &sp1C, 0) == -1) {
        *arg0 = 0;
        return 0U;
    }
    *arg0 = (s32) sp1C & 0xFFFFFF;
    return (u32) sp1C >> 0x18;
}

void func_80018A74(void) { func_8001480C(); }

void func_80018A94(s32 arg0, s32 *arg1, s32 *arg2) { s32 offset = arg0 * 0x14; *arg1 = (*(u8 **)(D_8011BE90 + 0x2BD8))[offset + 2]; *arg2 = (*(u8 **)(D_8011BE90 + 0x2BD8))[offset + 3]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80018ACC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80018B24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80018B78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80018C14.s")

s8 func_80018C60(s32 arg0, s32 arg1, s32 arg2)
{
  u8 *temp_v1;
  u8 *new_var2;
  int new_var;
  new_var = arg1 * 4;
  temp_v1 = D_80121EDC[arg0];
  if (((u32) (*((u32 *) temp_v1))) >> 31)
  {
    new_var2 = *((u8 **) ((temp_v1 + new_var) + 0x38));
    return *((s8 *) ((new_var2 + arg2) + 0xD0));
  }
  return -1;
}

extern u8 *D_80121EDC[]; s8 func_80018CA4(s32 arg0, s32 arg1) { return *(s8 *)(D_80121EDC[arg0] + arg1 + 0x158); }

extern s32 D_8011EBD0;
extern void GbApu_InitAllocator(s32 *, s32, s32);
void func_80018CC0(s32 arg0, s32 arg1) {
    GbApu_InitAllocator(&D_8011EBD0, arg0, arg1);
}

extern s32 D_8011EBD0; void func_80018CF0(void) { D_8011EBD0 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80018CFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_80018ED4.s")

void func_8001911C(s32 arg0, s32 arg1, s32 arg2) {
    func_80018728(((arg0 & 0xFF) << 0x10) | 0xFA000000 | ((arg1 & 0xFF) << 8) | (arg2 & 0xFF), 1);
}

void func_80019164(void) { func_80018728(0xFA000000, 0); }

void func_80019188(s32 arg0, s32 arg1) {
    func_80018728((arg1 & 0xFF) | 0xFD000000, arg0);
}

extern OSMesgQueue *D_801221B8; void func_800191BC(void) { osRecvMesg(D_801221B8, NULL, 0); osRecvMesg(D_801221B8, NULL, 1); }

extern s32 func_8001926C(s32, s32, s32, s32 *, s32 *);
s32 func_800191FC(s32 arg0, s32 arg1, s32 arg2) {
    s32 locals[4];
    if (func_8001926C(arg0, arg1, arg2, &locals[2], &locals[1]) == 0) {
        return 0;
    }
    return locals[1];
}

s32 func_80019230(s32 arg0, s32 arg1, s32 arg2) {
    s32 locals[4];
    if (func_8001926C(arg0, arg1, arg2, &locals[2], &locals[1]) == 0) {
        return 0;
    }
    return locals[2] - locals[1];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_8001926C.s")

void func_80019378(void) { func_800193B8(0); }

void func_80019398(void) { func_800193B8(2); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_800193B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/14640/func_800194A0.s")

void func_8001951C(void) { func_80018620(); }
#endif
