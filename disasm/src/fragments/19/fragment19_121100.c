#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82300020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_8230009C.s")

extern s16 D_82305EE4;

s32 func_823000E8(void) {
    return D_82305EE4 == 0;
}


s32 func_823000F8(void) {
    return D_82305EE4 == 2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_8230010C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82300368.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_823003B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_823008CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_8230099C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82300A78.s")

extern s16 D_82305EB4;
s32 func_82300AB4(void) {
    s32 result = 0;
    if (D_82305EB4 == 0) result = 1;
    return result;
}

s32 func_82300AD4(void) {
    s32 result = 0;
    if (D_82305EB4 == 2) result = 1;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82300AF8.s")

extern s16 D_82305E68[];
void func_82300F00(void) { D_82305E68[0x74 / 2] = 0; D_82305E68[0x76 / 2] = 0; (*(f32 *)((u8 *)D_82305E68 + 0x78)) = 0.0f; }


void func_82300F1C(void) {
    D_82305E68[0x74 / 2] = 1;
    D_82305E68[0x76 / 2] = 0;
}


void func_82300F34(void) {
    D_82305E68[0x74 / 2] = 3;
    D_82305E68[0x76 / 2] = 0;
}

extern s16 D_82305EDC;
s32 func_82300F4C(void) {
    s32 result = 0;
    if (D_82305EDC == 0) result = 1;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82300F6C.s")

extern void _bzero(void *, s32);
extern u32 D_82305D88;
void func_82301088(void) {
    _bzero(&D_82305D88, 224);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_823010B0.s")

void *func_823010B0();

void *func_823010EC(s32 arg0, s32 arg1, s16 arg2) {
    void *temp_v0;

    temp_v0 = func_823010B0();
    if (temp_v0 != NULL) {
        (*(s16 *)((u8 *)(temp_v0) + (2))) = 1;
        (*(s16 *)((u8 *)(temp_v0) + (4))) = (s16) arg0;
        (*(s16 *)((u8 *)(temp_v0) + (6))) = (s16) arg1;
        (*(s16 *)((u8 *)(temp_v0) + (0xA))) = arg2;
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82301140.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_8230125C.s")

extern s16 D_82305E6E;
s32 func_82301428(void) {
    return D_82305E6E;
}

extern u16 D_82305E72;
s32 func_82301434(s32 arg0, u8 *arg1) {
    switch (arg0) {
    case 0:
        arg1[0x28] = 0x11;
        break;
    case 1:
        if (D_82305E72 & 2) {
            *(u16 *)(arg1 + 2) |= 2;
        } else {
            *(u16 *)(arg1 + 2) &= 0xFFFD;
        }
        break;
    default:
        break;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82301494.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_823014EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_823015B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82301638.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_823016B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82301814.s")

extern s16 D_82305E6A;
extern f32 D_82305EE0;
extern u8 D_82305A7A[];
s32 func_82301964(s32 arg0, u8 *arg1) {
    s16 index;
    index = D_82305E6A;
    switch (arg0) {
    case 0:
        arg1[0x28] = 0x11;
        break;
    case 1:
        if (D_82305EE0 < 1.0f) {
            *(u16 *)(arg1 + 2) &= 0xFFFD;
            break;
        }
        *(u16 *)(arg1 + 2) |= 2;
        *(s16 *)(arg1 + 0x26) = *(s16 *)(D_82305A7A + index * 36);
        break;
    default:
        break;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_823019F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82301B2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82301C80.s")

extern s32 D_82305EA4;
s32 func_82301D78(s32 arg0, s32 arg1) {
    switch (arg0) {
        case 0:
            D_82305EA4 = arg1;
            break;
        case 1:
            break;
        default:
            break;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82301DA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82301EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_823020EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82302258.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82302320.s")

extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800499EC(void);
void func_82302B44(void) {
    func_800498C4();
    func_800496A4(8, 0);
    func_8004972C(0, 0xFF, 0xFF, 0xFF);
    func_800499EC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82302B8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82302D2C.s")

extern void func_80008648();
extern void func_800088DC();
extern void func_8003C6B8(s32);
extern void func_800503A4(s32);
extern void func_81700908();
s32 func_823008CC(s32);
extern void func_8230125C();
extern s32 D_82305EA0;
extern s32 D_82305EAC;

void func_82303038(void) {
    func_800088DC();
    if (func_823008CC(0) == 0) {
        func_800503A4(D_82305EA0);
        func_81700908();
        func_82302B44();
        func_8230125C();
        func_8003C6B8(D_82305EAC);
    }
    func_823008CC(1);
    func_80008648();
}

void func_823030A4(void) {
    func_823000E8();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_823030C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82303308.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82303488.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82303508.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_8230362C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82303A04.s")

extern s16 D_82305E6C;
extern s16 D_82305E70;
s32 func_82303B5C(void) {
    s16 *p = &D_82305E6C;
    s32 var_v1 = 0;
    s32 var_a0 = 0;
    if (*p >= 0) var_v1 = *p + 1;
    if (D_82305E70 >= 0) var_a0 = D_82305E70 + 1;
    return (var_a0 << 16) | var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/19/fragment19_121100/func_82303B94.s")
#endif
