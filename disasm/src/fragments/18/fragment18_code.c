#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_81700020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_817000A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_81700120.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_81700190.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_817001E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_8170024C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_8170031C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_81700908.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_81700974.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_81700AF4.s")

extern u8 D_81700DC0[];
s32 func_81700B2C(s32 arg0) { s32 result = 0; if (arg0 < 4) result = *(s16 *)((u8 *)D_81700DC0 + arg0 * 36); return result; }

extern u8 D_81700DBC[];
s32 func_81700B58(s32 arg0) { s32 result = 0; if (arg0 < 4) result = (*(u16 *)((u8 *)D_81700DBC + arg0 * 36) & 2) != 0; return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_81700B8C.s")

extern u8 D_81700DB0[];
s32 func_81700C0C(s32 arg0) { s32 result = 0; if (arg0 < 4) { u8 *ptr = D_81700DB0 + arg0 * 36; if ((*(u16 *)(ptr + 0xC) & 1) && *(s16 *)(ptr + 4) == 0) { result = 1; *(s16 *)(ptr + 4) = 1; *(s16 *)(ptr + 0xE) = 0; *(s16 *)(ptr + 0x16) = 0; *(s16 *)(ptr + 0x1A) = 0xFF; } } return result; }

extern u8 D_81700DB0[];
s32 func_81700C70(s32 arg0) { s32 result = 0; if (arg0 < 4) { u8 *ptr = D_81700DB0 + arg0 * 36; if ((*(u16 *)(ptr + 0xC) & 1) && *(s16 *)(ptr + 4) == 0) { result = 1; *(s16 *)(ptr + 4) = 2; *(s16 *)(ptr + 0xE) = 10; *(s16 *)(ptr + 0x1A) = 0xFF; *(s16 *)(ptr + 0x1C) = 0xFF; *(s16 *)(ptr + 0x10) = *(s16 *)(ptr + 0x14); } } return result; }

extern u8 D_81700DB0[];
s32 func_81700CDC(s32 arg0) { s32 result=0; if(arg0<4) { u8 *ptr=D_81700DB0+arg0*36; if((*(u16 *)(ptr+12)&1)!=0 && *(s16 *)(ptr+4)==2) { result=1; *(s16 *)(ptr+4)=1; *(s16 *)(ptr+14)=0; *(s16 *)(ptr+28)=0; *(s16 *)(ptr+22)=*(s16 *)(ptr+16); } } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/18/fragment18_code/func_81700D44.s")
#endif
