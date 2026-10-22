#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305BC0.s")

void func_86305C48(void *arg0, void *arg1, f32 arg2) {
    *(f32 *)((u8 *)arg0 + 0x48) += *(f32 *)((u8 *)arg1 + 0) * arg2;
    *(f32 *)((u8 *)arg0 + 0x4C) += *(f32 *)((u8 *)arg1 + 4) * arg2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305C78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305D88.s")

extern u8 *D_863075D8;
extern void func_87C03B60(void *, void *, void *);
extern void func_800277F0(u16, void *);
void func_86305E20(u8 *arg0) {
    s8 position[2];

    if (*(s32 *)D_863075D8 == 4) {
        func_87C03B60(D_863075D8 + 0x8F5C, arg0 + 0x48, position);
        func_800277F0(0x6F04, position);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305E70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86305FD8.s")

s32 func_86305E70();
extern void func_86305FD8(s32);

void func_863060CC(s32 arg0) {
    if (func_86305E70() != 0) {
        func_86305FD8(arg0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_863060FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_863063C0.s")

extern void *D_87F119DC;

void func_86306638(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (0))) = (f32) (*(f32 *)((u8 *)(D_87F119DC) + (0x48)));
    (*(f32 *)((u8 *)(arg0) + (4))) = (f32) (*(f32 *)((u8 *)(D_87F119DC) + (0x4C)));
}


void func_8630665C(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (8))) = (f32) ((*(f32 *)((u8 *)(D_87F119DC) + (0x48))) - (*(f32 *)((u8 *)(arg0) + (0))));
    (*(f32 *)((u8 *)(arg0) + (0xC))) = (f32) ((*(f32 *)((u8 *)(D_87F119DC) + (0x4C))) - (*(f32 *)((u8 *)(arg0) + (4))));
}

extern s32 func_86304920(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_86306690(u8 *arg0, s8 *arg1) {
    if (arg1[33] != -1) {
        if (func_86304920(*(f32 *)(arg0 + 72), *(f32 *)(arg0 + 76),
                         0.0f, 180.0f, -180.0f, 0.0f, 0.0f, -180.0f, 180.0f, 0.0f) != 0) {
            arg1[32] = arg1[33];
            arg1[33] = -1;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86306710.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_27B9E0/func_86306AC0.s")

extern void func_863060FC(void **);
extern void func_86306710(void **);
extern void func_86306AC0(void **);
void func_86306CC4(void) {
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(D_87F119DC) + (0x20)));
    (*(s32 *)((u8 *)(temp_v0) + (0x1C))) = (s32) ((*(s32 *)((u8 *)(temp_v0) + (0x1C))) + 1);
    temp_v1 = (*(s32 *)((u8 *)(D_87F119DC) + (0xC)));
    if (temp_v1 & 0x10000000) {
        func_863060FC(&D_87F119DC);
        return;
    }
    if (temp_v1 & 0x20000000) {
        func_86306AC0(&D_87F119DC);
        return;
    }
    func_86306710(&D_87F119DC);
}

extern void *func_87F025B8(void *, void *);
extern void func_8003F1DC(void *);
extern void func_8003F114(void *, s32, s32, s32);
extern u32 func_8003570C(void);
extern void func_86304544(void *);

void func_86306D3C(void) {
    u8 *obj;
    u8 *data;
    s8 position[2];
    u8 *node;

    obj = func_87F025B8(D_863075D8 + 0xDB4, (void *)func_86306CC4);
    if (obj != NULL) {
        data = *(u8 **)(obj + 0x20);
        node = obj + 0x24;
        func_8003F1DC(node);
        func_8003F114(node, 0, -1, *(s32 *)(D_863075D8 + 0x100));
        *(u8 **)(obj + 0x38) = obj;
        *(s32 *)(obj + 0xC) |= 0x10000000;
        *(s16 *)(obj + 0x46) = -0x2000;
        *(f32 *)(obj + 0x4C) = 0.0f;
        *(f32 *)(obj + 0x48) = 0.0f;
        *(f32 *)(obj + 0x5C) = 0.0f;
        *(f32 *)(obj + 0x58) = 0.0f;
        *(f32 *)(obj + 0x54) = 0.0f;
        *(f32 *)(obj + 0x50) = 100.0f;
        *(f32 *)(data + 0) = 0.0f;
        *(f32 *)(data + 0x4) = *(f32 *)(obj + 0x4C);
        *(s8 *)(data + 0x20) = -1;
        *(s8 *)(data + 0x21) = -1;
        *(s32 *)(data + 0x1C) = 0;
        *(f32 *)(data + 0x10) = 0.0f;
        *(f32 *)(data + 0x14) = 0.0f;
        *(f32 *)(data + 0x18) = 0.0f;
        *(s32 *)(obj + 0x1C) = (s32)((((f32)func_8003570C() / 4294967296.0f) + 2.0f) * -48.0f);
        func_86304544(obj);
        func_87C03B60(D_863075D8 + 0x8F5C, obj + 0x48, position);
        func_800277F0(0x6F02, position);
    }
}
#endif
