#include "global.h"


#ifdef VERSION_US
extern void Util_Free(s32);
extern s32 D_880068B4;
extern s32 D_88523010;

void func_88506990(void) {
    D_880068B4 = 1;
    Util_Free(D_88523010);
}

extern void func_800226C0(s32);
extern void func_8850A0A0(s32, s32, s32, s32);
void func_885069C0(void) {
    if ((*(s32 *)((u8 *)(D_88523010) + (0x18))) != 0) {
        func_8850A0A0(0, 0x11F, 0x280, 0x65);
        func_800226C0(0x14D);
        return;
    }
    func_8850A0A0(0x28, 0x14, 0x230, 0x100);
}

extern void func_88004990(s32,s32);
void func_88506A20(void){func_8850A0A0(0,0,0x280,0x1E0);func_88004990(0,0);func_88004990(1,0);func_88004990(2,0);if(*(s32 *)((u8 *)D_88523010+0x18)!=0)func_88004990(3,0);func_88004990(4,0);func_88004990(5,0);}

extern s8 D_8800EF41;
extern u8 D_8850D6D8;
extern s8 D_8800EF40;
void func_88506AA8(void) {
    s16 temp_v1;
    s8 *var_a0;

    D_8800EF40 = (s8) (*(s16 *)((u8 *)(D_88523010) + (0x2C)));
    if ((*(s16 *)((u8 *)(D_88523010) + (0x2C))) != -1) {
        temp_v1 = (*(s16 *)((u8 *)(D_88523010) + (0x24)));
        if (temp_v1 < 2) {
            var_a0 = (temp_v1 * 0xA960) + &D_8850D6D8;
        } else {
            var_a0 = ((*(s16 *)((u8 *)(D_88523010) + (0x26))) * 0xA960) + &D_8850D6D8;
        }
        D_8800EF41 = *var_a0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C3FA0/func_88506B2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C3FA0/func_8850716C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C3FA0/func_88507370.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C3FA0/func_885075A8.s")

extern void func_88506AA8();
extern void func_8850716C();
extern void func_88507370();
extern void func_885075A8();
extern s32 D_88523018;
void func_88507724(void) {
    switch (D_88523018) {                           /* irregular */
    case 0:
        break;
    case 1:
        func_88507370();
        break;
    case 2:
        func_885075A8();
        break;
    case 3:
        func_8850716C();
        break;
    }
    func_88506AA8();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C3FA0/func_8850779C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C3FA0/func_88507FA8.s")
#endif
