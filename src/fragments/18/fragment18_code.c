#include "global.h"


#ifdef VERSION_US
extern void _bzero(void *, s32);
extern s32 func_8004C8C0(s32);
extern void fragment18_main(u8 *);
extern s32 func_8170031C(u8 *);
extern s32 D_81700DA0;
extern u8 D_81700DB0[];
extern u8 D_81700E40[];
void fragment18_main(u8 *arg0) {
    _bzero(arg0, 0x24);
    *(s16 *)(arg0 + 0x00) = -1;
    *(s16 *)(arg0 + 0x02) = -1;
    *(s16 *)(arg0 + 0x04) = 0;
    *(s16 *)(arg0 + 0x06) = 0;
    *(s32 *)(arg0 + 0x08) = 0;
    *(s16 *)(arg0 + 0x0C) = 0;
    *(s16 *)(arg0 + 0x0E) = 0;
    *(s16 *)(arg0 + 0x10) = 0;
    *(s16 *)(arg0 + 0x12) = 0;
    *(s16 *)(arg0 + 0x14) = 0;
    *(s16 *)(arg0 + 0x16) = 0;
    *(s16 *)(arg0 + 0x18) = 0;
    *(s16 *)(arg0 + 0x1A) = 0xFF;
    *(s16 *)(arg0 + 0x1C) = 0;
    arg0[0x1E] = 0xFF;
    arg0[0x1F] = 0xFF;
    arg0[0x20] = 0xFF;
    arg0[0x21] = 0xFF;
    arg0[0x22] = 0xFF;
    arg0[0x23] = 0xFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_817000A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_81700120.s")

void func_81700190(void *arg0) {
    s16 temp_v0;

    (*(s16 *)((u8 *)(arg0) + (0xE))) = (s16) ((*(s16 *)((u8 *)(arg0) + (0xE))) + 1);
    temp_v0 = (*(s16 *)((u8 *)(arg0) + (0xE)));
    if (temp_v0 < 0xA) {
        (*(s16 *)((u8 *)(arg0) + (0x1C))) = (s16) ((s32) (temp_v0 * 0xFF) / 10);
        return;
    }
    (*(s16 *)((u8 *)(arg0) + (0xE))) = 0xA;
    (*(s16 *)((u8 *)(arg0) + (0x1C))) = 0xFF;
}

void func_817001E0(void *arg0)
{
  s16 temp_v0;
  s16 temp_v1;
  *((s16 *) (((u8 *) arg0) + 0xE)) = (s16) ((*((s16 *) (((u8 *) arg0) + 0xE))) + 1);
  temp_v0 = *((s16 *) (((u8 *) arg0) + 0xE));
  if (temp_v0 < 5)
  {
    temp_v1 = 0xFF - (((s32) (temp_v0 * 0xFF)) / 5);
    if (1)
    {
      *((s16 *) (((u8 *) arg0) + 0x1C)) = temp_v1;
      *((s16 *) (((u8 *) arg0) + 0x1A)) = temp_v1;
    }
    return;
  }
  *((s16 *) (((u8 *) arg0) + 4)) = 0;
  *((s16 *) (((u8 *) arg0) + 0xE)) = 0;
  *((s16 *) (((u8 *) arg0) + 0x1A)) = 0;
  *((s16 *) (((u8 *) arg0) + 0x1C)) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_8170024C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_8170031C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_81700908.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_81700974.s")

s32 func_81700AF4(s32 arg0, void *arg1) {
    typedef struct { u8 bytes[4]; } Copy4;
    if (arg0 < 4) {
        *(Copy4 *)arg1 = *(Copy4 *)(D_81700DB0 + arg0 * 0x24);
    }
    return 0;
}

extern u8 D_81700DC0[];
s32 func_81700B2C(s32 arg0) { s32 result = 0; if (arg0 < 4) result = *(s16 *)((u8 *)D_81700DC0 + arg0 * 36); return result; }

extern u8 D_81700DBC[];
s32 func_81700B58(s32 arg0) { s32 result = 0; if (arg0 < 4) result = (*(u16 *)((u8 *)D_81700DBC + arg0 * 36) & 2) != 0; return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_81700B8C.s")

extern u8 D_81700DB0[];
s32 func_81700C0C(s32 arg0) { s32 result = 0; if (arg0 < 4) { u8 *ptr = D_81700DB0 + arg0 * 36; if ((*(u16 *)(ptr + 0xC) & 1) && *(s16 *)(ptr + 4) == 0) { result = 1; *(s16 *)(ptr + 4) = 1; *(s16 *)(ptr + 0xE) = 0; *(s16 *)(ptr + 0x16) = 0; *(s16 *)(ptr + 0x1A) = 0xFF; } } return result; }

s32 func_81700C70(s32 arg0) { s32 result = 0; if (arg0 < 4) { u8 *ptr = D_81700DB0 + arg0 * 36; if ((*(u16 *)(ptr + 0xC) & 1) && *(s16 *)(ptr + 4) == 0) { result = 1; *(s16 *)(ptr + 4) = 2; *(s16 *)(ptr + 0xE) = 10; *(s16 *)(ptr + 0x1A) = 0xFF; *(s16 *)(ptr + 0x1C) = 0xFF; *(s16 *)(ptr + 0x10) = *(s16 *)(ptr + 0x14); } } return result; }

s32 func_81700CDC(s32 arg0) { s32 result=0; if(arg0<4) { u8 *ptr=D_81700DB0+arg0*36; if((*(u16 *)(ptr+12)&1)!=0 && *(s16 *)(ptr+4)==2) { result=1; *(s16 *)(ptr+4)=1; *(s16 *)(ptr+14)=0; *(s16 *)(ptr+28)=0; *(s16 *)(ptr+22)=*(s16 *)(ptr+16); } } return result; }

s32 func_81700D44(s32 arg0) { s32 result=0; if(arg0<4) { u8 *ptr=&D_81700DB0[arg0*36]; if((*(u16 *)(ptr+12)&1)!=0 && *(s16 *)(ptr+4)==2) { result=1; *(s16 *)(ptr+4)=3; *(s16 *)(ptr+14)=0; } } return result; }
#pragma C_FUNCTION_PADDING(16)
#endif
