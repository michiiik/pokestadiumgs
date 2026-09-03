#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000C280.s")
#endif

#ifdef VERSION_US
extern s32 func_8000DDC8(s32 arg0, s32 arg1, u16 arg2, s16 arg3, u8 *arg4);
extern s32 func_8000DE34(s32 arg0, s32 arg1, u16 arg2, s16 arg3, u8 *arg4);
extern s32 D_8008FA40;
extern u8 D_800D1220[];
extern u8 D_8011EBF0[];
void func_8000C614(s32 arg0)
{
    s32 i;
    u8 *entry;

    if (arg0 >= 8) {
        arg0 = 7;
    }
    D_8008FA40 = arg0;
    for (i = 0; i < 7; i++) {
        entry = D_800D1220 + i * 0x18;
        *(s32 *)(entry + 4) = 0;
        *(s32 *)(entry + 8) = 0;
        if (i < D_8008FA40) {
            *(s32 *)(entry + 0) = GbApu_Alloc(D_8011EBF0, 0x25D8);
            *(s32 *)(entry + 0xC) = GbApu_Alloc(D_8011EBF0, 0x280);
            if (*(s32 *)(entry + 0) != 0) {
                *(s32 *)(entry + 0x14) = *(s32 *)(entry + 0) + 0x198;
            }
        } else {
            *(s32 *)(entry + 0) = 0;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000C6D8.s")
#endif

#ifdef VERSION_US
void func_8000C800(s32 arg0, s32 arg1, s32 arg2, OSMesgQueue *arg3)
{
    if (arg0 & 0x80000000) {
        _bcopy(arg0, arg1, arg2);
        osSendMesg(arg3, (OSMesg)1, 0);
    } else {
        func_8001544C(arg0, arg1, arg2, 2);
        osSendMesg(arg3, (OSMesg)1, 0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000C85C.s")
#endif

#ifdef VERSION_US
extern u8 D_8011BE90[];
void func_8000CCF0(s32 arg0)
{
    s32 i;
    s32 offset;
    s32 target_offset;
    s32 product;
    u8 *entry;
    s32 new_var;
    u8 *target;

    i = 0;
    offset = 0;
    product = *(s32 *)(D_8011BE90 + 0x2C28) * arg0;
    target_offset = product << 5;
    while (i < *(s32 *)(D_8011BE90 + 0x2C28)) {
        entry = (u8 *)(offset + *(u32 *)(D_8011BE90 + 0x3468)) + (new_var = 0xD0);
        target = (u8 *)(target_offset + *(u32 *)(D_8011BE90 + 0x14)) + (new_var = 0);
        if ((*(u32 *)entry >> 31) != 0) {
            func_8001FC60(target, entry);
            entry[0] &= 0xFFBF;
        } else {
            target[0] &= 0xFF7F;
        }
        entry[6] = 0;
        i++;
        offset += 0x100;
        target_offset += 0x20;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000CDB8.s")
#endif

#ifdef VERSION_US
void func_8000CFB4(s32 arg0, s32 arg1)
{
    struct LocalEntry {
        u32 unk0 : 1;
        u32 unk1 : 1;
        u32 unk2 : 30;
    };
    s32 i;
    u8 *ptr;

    i = arg0 + 1;
    while (i < *(s16 *)(D_8011BE90 + 0x2BE8)) {
        ptr = (u8 *)(*(u32 *)(D_8011BE90 + 0x14) + (((*(u32 *)(D_8011BE90 + 0x2C28) * i) + arg1) << 5));
        if (((struct LocalEntry *)ptr)->unk1) {
            break;
        }
        ptr[0] &= 0xFF7F;
        i++;
    }
}
#endif

#ifdef VERSION_US
s32 func_8000D024(s32 arg0, u8 *arg1, s16 arg2)
{
    u8 *entry;

    entry = ((arg1 + (arg1[3] * 0x8C)) + (arg2 * 0x1C)) + ((0, 0x40));
    arg0 = func_8000DDC8(arg0, 0x3D0, *(u16 *)(entry + 0xE), *(s16 *)(entry + 0x10), arg1);
    if (*(s16 *)(entry + 0x12) != 0) {
        arg0 = func_8000DDC8(arg0, (*(s16 *)(entry + 0x10) + 0x3D0) & 0xFFFF, 0, *(s16 *)(entry + 0x12), arg1);
    }
    return arg0;
}
#endif

#ifdef VERSION_US
s32 func_8000D0CC(s32 arg0, u8 *arg1, s16 arg2)
{
    u8 *entry;

    entry = ((arg1 + (arg1[3] * 0x8C)) + (arg2 * 0x1C)) + ((0, 0x40));
    arg0 = func_8000DE34(arg0, 0x3D0, *(u16 *)(entry + 0xE), *(s16 *)(entry + 0x10), arg1);
    if (*(s16 *)(entry + 0x12) != 0) {
        arg0 = func_8000DE34(arg0, (*(s16 *)(entry + 0x10) + 0x3D0) & 0xFFFF, 0, *(s16 *)(entry + 0x12), arg1);
    }
    return arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D174.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D1D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D374.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D56C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D710.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000D7B8.s")
#endif

#ifdef VERSION_US
void func_8000D880(u8 *arg0, s32 arg1, s32 arg2) { *(u32 *)(arg0 + 0) = ((u32)arg1 & 0x00FFFFFF) | 0x02000000; *(u32 *)(arg0 + 4) = arg2; }
#endif

#ifdef VERSION_US
void func_8000D8A0(void) {}
void func_8000D8A0_padding(void) {}
void func_8000D8A0_padding2(void) {}
void func_8000D8A0_padding3(void) {}
void func_8000D8A0_padding4(void) {}
void func_8000D8A0_padding5(void) {}
void func_8000D8A0_padding6(void) {}
#endif

#ifdef VERSION_US
void func_8000D8D8(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  *((s32 *) (((u8 *) arg0) + 0)) = (s32) ((((arg1 & 0xFF) << 0x10) | 0x08000000) | (arg2 & 0xFFFF));
  *((s32 *) (((u8 *) arg0) + 4)) = (s32) ((arg3 << 0x10) | (arg4 & 0xFFFF));
  *((s32 *) (((u8 *) arg0) + 4)) = (s32) (((arg3 << 3) << 13) | (arg4 & 0xFFFF));
}
#endif

#ifdef VERSION_US
void func_8000D90C(void) {}
void func_8000D90C_padding(void) {}
#endif

#ifdef VERSION_US
void func_8000D91C(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  *((s32 *) (((u8 *) arg0) + 0)) = (s32) ((arg1 & 0xFFFFFF) | 0x0A000000);
  *((s32 *) (((u8 *) arg0) + 4)) = (s32) (((arg2 << 4) << 12) | (arg3 & 0xFFFF));
}
#endif

#ifdef VERSION_US
void func_8000D948(void) {}
void func_8000D948_padding(void) {}
void func_8000D948_padding2(void) {}
void func_8000D948_padding3(void) {}
#endif

#ifdef VERSION_US
void func_8000D968(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  *((s32 *) (((u8 *) arg0) + 0)) = (arg3 & 0xFFFF) | 0x11000000;
  *((s32 *) (((u8 *) arg0) + 4)) = (s32) (((arg1 << 8) << 8) | (arg2 & 0xFFFF));
}
#endif

#ifdef VERSION_US
void func_8000D98C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  *((s32 *) (((u8 *) arg0) + 0)) = (s32) ((((arg1 & 0xFF) << 0x10) | 0x12000000) | (arg2 & 0xFFFF));
  *((s32 *) (((u8 *) arg0) + 4)) = (s32) (((arg3 << 4) << 12) | (arg4 & 0xFFFF));
}
#endif

void func_8000D9C0(void) {
}

#ifdef VERSION_US
void func_8000D9C8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    (*(s32 *)((u8 *)(arg0) + (0))) = (s32) ((((arg2 >> 4) & 0xFF) << 0x10) | 0x14000000 | (arg1 & 0xFFFF));
    (*(s32 *)((u8 *)(arg0) + (4))) = arg3;
}
#endif

void func_8000D9F0(void) {
}

#ifdef VERSION_US
void func_8000D9F8(void *arg0, s32 arg1, s32 arg2)
{
  u8 *new_var;
  new_var = (u8 *) arg0;
  *((s32 *) (new_var + 0)) = 0x16000000;
 do { *((s32 *) (((u8 *) arg0) + 4)) = (s32) (((arg1 << 7) << 9) | (arg2 & 0xFFFF)); } while (0);
}
#endif

#ifdef VERSION_US
void func_8000DA14(void) {}
void func_8000DA14_padding(void) {}
void func_8000DA14_padding2(void) {}
#endif

#ifdef VERSION_US
void func_8000DA2C(u8 *arg0, s32 arg1, s32 arg2) { *(u32 *)(arg0 + 0) = 0x17000000 | (((u32)arg1 & 0xFF) << 16); *(u32 *)(arg0 + 4) = arg2; }
#endif

#ifdef VERSION_US
void func_8000DA48(u32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0[0] = ((arg1 & 0xFF) << 16) | 0x0E000000 | (arg4 & 0xFFFF);
    arg0[1] = ((arg2 & 0xFFFF) << 16) | (arg3 & 0xFFFF);
}
#endif

#ifdef VERSION_US
void func_8000DA7C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  u8 *p = arg0;
  *((u32 *) (p + 0x00)) = ((arg4 & 0xFF) << 16) | (arg3 & 0xFFFF);
  *((u32 *) (p + 0x04)) = ((arg1 << 14) << 2) | (arg2 & 0xFFFF);
}
#endif

#ifdef VERSION_US
void ParticleGfx_NoopStub2(void) {}
void func_8000DAA8_padding(void) {}
void func_8000DAA8_padding2(void) {}
void func_8000DAA8_padding3(void) {}
void func_8000DAA8_padding4(void) {}
void func_8000DAA8_padding5(void) {}
void func_8000DAA8_padding6(void) {}
void func_8000DAA8_padding7(void) {}
#endif

#ifdef VERSION_US
void func_8000DAE8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) { *(u32 *)(arg0 + 0) = 0x07000000 | (((u32)arg1 & 0xFF) << 16) | ((u32)arg2 & 0xFFFF); *(u32 *)(arg0 + 4) = arg3; }
#endif

#ifdef VERSION_US
void func_8000DB0C(u8 *arg0, s32 arg1, s32 arg2) { *(u32 *)(arg0 + 0) = 0x07020000 | ((u32)arg1 & 0xFFFF); *(u32 *)(arg0 + 4) = arg2; }
#endif

#ifdef VERSION_US
s32 func_8000DB24(s32 arg0, s32 arg1, u8 *arg2, s16 arg3)
{
    u8 *entry;

    entry = ((arg2 + (arg2[3] * 0x8C)) + (arg3 * 0x1C)) + ((0, 0x40));
    arg0 = func_8000DDC8(arg0, 0xC70, *(u16 *)(entry + 0xE), *(s16 *)(entry + 0x10), arg2);
    if (*(s16 *)(entry + 0x12) != 0) {
        arg0 = func_8000DDC8(arg0, (*(s16 *)(entry + 0x10) + 0xC70) & 0xFFFF, 0, *(s16 *)(entry + 0x12), arg2);
    }
    return arg0;
}
#endif

#ifdef VERSION_US
s32 func_8000DBD0(s32 arg0, s32 arg1, u8 *arg2, s16 arg3)
{
    u8 *entry;

    entry = ((arg2 + (arg2[3] * 0x8C)) + (arg3 * 0x1C)) + ((0, 0x158));
    arg0 = func_8000DDC8(arg0, 0xC70, *(u16 *)(entry + 0xE), *(s16 *)(entry + 0x10), arg2);
    if (*(s16 *)(entry + 0x12) != 0) {
        arg0 = func_8000DDC8(arg0, (*(s16 *)(entry + 0x10) + 0xC70) & 0xFFFF, 0, *(s16 *)(entry + 0x12), arg2);
    }
    return arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DC7C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DDC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DE34.s")
#endif

void func_8000DEA0(void) {
}

#ifdef VERSION_US
s32 func_8000DEA8(s32 arg0, s32 arg1, u8 *arg2, s16 arg3)
{
    if (arg2[4] == 1) {
        arg0 = func_8000DBD0(arg0, arg1, arg2, arg3);
    }
    return arg0;
}
#endif

#ifdef VERSION_US
s32 func_8000DEE8(s32 arg0, s32 arg1, u8 *arg2, s16 arg3)
{
    if (arg2[4] == 1) {
        if (arg2[0x18] != 0) {
            arg0 = func_8000D56C(arg0, arg1, arg2, arg3);
        } else {
            arg0 = func_8000DB24(arg0, arg1, arg2, arg3);
        }
    } else {
        arg0 = func_8000D1D8(arg0, arg1, arg2, arg3);
    }
    return arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000DF5C.s")
#endif

#ifdef VERSION_US
s32 func_8000E13C(s32 arg0, u8 *arg1, s16 arg2)
{
    u8 *entry;

    entry = ((arg1 + (arg1[3] * 0x8C)) + (arg2 * 0x1C)) + ((0, 0x158));
    arg0 = func_8000DE34(arg0, 0xC70, *(u16 *)(entry + 0xE), *(s16 *)(entry + 0x10), arg1);
    if (*(s16 *)(entry + 0x12) != 0) {
        arg0 = func_8000DE34(arg0, (*(s16 *)(entry + 0x10) + 0xC70) & 0xFFFF, 0, *(s16 *)(entry + 0x12), arg1);
    }
    return arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000E1E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000E750.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000F4E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000F794.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000F834.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/CE80/func_8000FCF0.s")
#endif
