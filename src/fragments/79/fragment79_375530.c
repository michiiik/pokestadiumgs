#include "global.h"


#ifdef VERSION_US
void func_84105CA0(u8 *arg0) {}
#endif

void func_84105CA8(void) {
}

#ifdef VERSION_US
void func_84105CB0(u8 *arg0) {}
#endif

#ifdef VERSION_US
void func_84105CB8(u8 *arg0) {}
#endif

#ifdef VERSION_US
void func_84105CC0(u8 *arg0) {}
#endif

#ifdef VERSION_US
void func_84105CC8(void) {}
void func_84105CC8_padding(void) {}
void func_84105CC8_padding2(void) {}
void func_84105CC8_padding3(void) {}
#endif

void func_84105CE8(void) {
}

void func_84105CF0(void) {
}

#ifdef VERSION_US
void func_84105CF8(u8 *arg0) {}
#endif

#ifdef VERSION_US
extern u8 *D_84190150;
extern s32 D_84190154;
extern u8 *main_pool_alloc(s32, s32);
void func_84105D00(void) {
    D_84190150 = main_pool_alloc(0x300, 0);
    _bzero(D_84190150, 0x300);
    D_84190154 = 0;
}
#endif

#ifdef VERSION_US
u8 *func_84105D40(void) {
    s32 i;
    s32 index;
    u8 *ptr;
    index = D_84190154;
    ptr = D_84190150 + index * 0xC;
    for (i = 0; i < 0x40; i++) {
        if ((ptr[8] & 1) == 0) break;
        index++;
        if (index >= 0x40) {
            index = 0;
            ptr = D_84190150;
        } else ptr += 0xC;
    }
    if (i >= 0x40) ptr = NULL;
    else {
        D_84190154 = index + 1;
        if (D_84190154 >= 0x40) D_84190154 = 0;
    }
    return ptr;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_84105DD0.s")
#endif

#ifdef VERSION_US
void func_84105E20(u8 *arg0)
{
  *((s8 *) (((u8 *) arg0) + 7)) = 0;
  *((s8 *) (((u8 *) arg0) + 8)) = 0;
  *((s8 *) (((u8 *) arg0) + 5)) = 0;
  *((s8 *) (((u8 *) arg0) + 4)) = 0;
  *((s8 *) (((u8 *) arg0) + 6)) = ((s8) (*((s8 *) (((u8 *) arg0) + 7)))) & 0xFF;
}
#endif

#ifdef VERSION_US
extern void func_84105E20(u8 *);
void func_84105E3C(void) {
    u8 *ptr = D_84190150;
    s32 i = 0;
    while (i != 0x40) {
        if (ptr[8] & 1) {
            func_84105E20(ptr);
        }
        i++;
        ptr += 0xC;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_84105E9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_84105F10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_84105FC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_841063D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_84106540.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_841065E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_8410668C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_8410679C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_84106AC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_84106F34.s")
#endif

#ifdef VERSION_US
#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

M2C_UNK func_84100020(u8 *, M2C_UNK);             /* extern */
extern s32 D_84190194;
extern s32 D_841901A4;

void func_84107170(u8 *arg0, u8 *arg1) {
    u8 *temp_s1;

    temp_s1 = M2C_FIELD(arg0, u8 **, 0);
    M2C_FIELD(arg1, u8 **, 0x10) = temp_s1;
    M2C_FIELD(arg1, u8 *, 0x7C) = (u8) M2C_FIELD(arg0, u8 *, 9);
    M2C_FIELD(arg1, u16 *, 0x68) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
    M2C_FIELD(arg1, s32 *, 8) = (s32) D_84190194;
    if (M2C_FIELD(temp_s1, s32 *, 4) & 0x10) {
        func_84100020(arg1, 1);
    }
    if (M2C_FIELD(temp_s1, s32 *, 4) & 0x400) {
        func_84100020(arg1, 0x40);
    }
    if (M2C_FIELD(temp_s1, s32 *, 4) & 8) {
        func_84100020(arg1, 0x200);
    }
    if (M2C_FIELD(temp_s1, s32 *, 4) & 0x20000000) {
        func_84100020(arg1, 0x10000);
    }
    if (M2C_FIELD(temp_s1, s32 *, 4) & 4) {
        func_84100020(arg1, 0x100);
    }
    if (M2C_FIELD(temp_s1, s32 *, 4) & 0x100) {
        func_84100020(arg1, 0x400);
    }
    if (M2C_FIELD(temp_s1, s32 *, 4) & 0x10000000) {
        func_84100020(arg1, 0x20000);
    }
    if (M2C_FIELD(temp_s1, s32 *, 4) & 0x08000000) {
        func_84100020(arg1, 0x8000);
    }
    if (M2C_FIELD(temp_s1, s32 *, 4) & 0x80000000) {
        func_84100020(arg1, 0x40000);
    }
    if (M2C_FIELD(temp_s1, s32 *, 8) & 4) {
        func_84100020(arg1, 0x80000);
        D_841901A4 = 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_841072BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_841076B8.s")
#endif

#ifdef VERSION_US
extern u8 *func_84100328(void);
s32 func_841077E8(u8 *arg0) {
    u8 *obj;

    if (*(s32 *)arg0 != 0) {
        obj = func_84100328();
        if (obj == NULL) {
            return 0;
        }
        obj[0x7C] = arg0[9];
        *(s32 *)(obj + 0x10) = *(s32 *)arg0;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern u8 *func_84100328(void);
extern void fragment27_main(u32 *, u32);
extern u8 *func_84104F54(u8 *);
s32 func_84107838(u8 *arg0) {
    u8 *obj;

    if (*(s32 *)(arg0 + 0) != 0) {
        obj = func_84100328();
        if (obj == NULL) {
            return -1;
        }
        fragment27_main((u32 *)(obj + 0x14), 8);
        fragment27_main((u32 *)(obj + 0x14), 0x20);
        *(s32 *)(obj + 0x10) = *(s32 *)(arg0 + 0);
        obj[0x7C] = arg0[9];
        func_84104F54(obj);
    }
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_841078B8(u8 *arg0) {
    u8 *obj;

    if (*(s32 *)arg0 != 0) {
        obj = func_84100328();
        if (obj == NULL) {
            return -1;
        }
        fragment27_main((u32 *)(obj + 0x14), 0x7028);
        *(s32 *)(obj + 0x10) = *(s32 *)arg0;
        obj[0x7C] = arg0[9];
        *(f32 *)(obj + 0x44) = 160.0f;
        *(f32 *)(obj + 0x48) = 120.0f;
        *(f32 *)(obj + 0x20) = 160.0f;
        *(f32 *)(obj + 0x24) = 120.0f;
    }
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_84107948(u8 *arg0) {
    u8 *obj;

    if (*(s32 *)arg0 != 0) {
        obj = func_84100328();
        if (obj == NULL) {
            return 0;
        }
        obj[0x7C] = arg0[9];
        *(s32 *)(obj + 0x10) = *(s32 *)arg0;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_84107998.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375530/func_84107B68.s")
#endif
