#include "global.h"


#ifdef VERSION_US
extern u8 D_8AF2C4F8[];
extern u32 D_8AF2C548;
void func_8AF035E0(void *arg0) {
    u32 count = D_8AF2C548;
    if (count < 0xA) {
        u8 *dest = D_8AF2C4F8 + count * 8;
        *(s32 *)dest = *(s32 *)((u8 *)arg0 + 0x4E4);
        *(s32 *)(dest + 4) = *(s32 *)((u8 *)arg0 + 0x4E8);
        D_8AF2C548 = count + 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03624.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03678.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03730.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03798.s")

extern void func_8AC0619C(s32 *, u16);
extern void func_8AC06220(s32 *, u16);
extern u16 D_8AF2BDC6;
extern s16 D_8AF2C094;
extern u8 D_8AF2C098;
extern u8 D_8AF2C110;
extern u8 D_8AF2C188;
extern u8 D_8AF2C200;
void func_8AF037EC(void) {
    switch (D_8AF2C094) {                           /* irregular */
    case 0:
        func_8AC0619C(&D_8AF2C188, D_8AF2BDC6);
        func_8AC06220(&D_8AF2C200, D_8AF2BDC6);
        return;
    case 1:
        func_8AC0619C(&D_8AF2C098, D_8AF2BDC6);
        func_8AC06220(&D_8AF2C110, D_8AF2BDC6);
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03878.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03B38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03B74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03BC4.s")

extern s32 D_8AF2C56C;
extern s32 D_8AF2C570;
s32 func_8AF03D34(s32 arg0, void *arg1) {
    void *inner = *(void **)((u8 *)arg1 + 0x20);
    switch (arg0) {
    case 0:
        D_8AF2C56C = *(s16 *)((u8 *)arg1 + 8);
        D_8AF2C570 = *(s16 *)((u8 *)arg1 + 0xA);
        *(s32 *)((u8 *)inner + 0x4E4) = 0;
        *(s32 *)((u8 *)inner + 0x4E8) = 0;
        *(s32 *)((u8 *)inner + 0x4EC) = 0;
        break;
    case 1:
        *(s16 *)((u8 *)arg1 + 8) = *(s32 *)((u8 *)inner + 0x4E4) + D_8AF2C56C;
        *(s16 *)((u8 *)arg1 + 0xA) = *(s32 *)((u8 *)inner + 0x4E8) + D_8AF2C570;
        break;
    }
    return 0;
}

extern void *D_8AF2BF44;

s32 func_8AF03DA8(s32 arg0, void *arg1) {
    if (arg0 != 0 && arg0 == 1) {
        if (D_8AF2BF44 != 0) {
            *(u16 *)((u8 *)arg1 + 0x30) = 0x37;
            *(u16 *)((u8 *)arg1 + 0x32) = *(s32 *)((u8 *)D_8AF2BF44 + 0x28);
            *(u16 *)((u8 *)arg1 + 2) |= 2;
        }
    }
    return 0;
}

extern void *D_8AF2BF44;

s32 func_8AF03DF0(s32 arg0, void *arg1) {
    if (arg0 != 0 && arg0 == 1) {
        if (D_8AF2BF44 != 0) {
            *(u16 *)((u8 *)arg1 + 0x30) = 0x37;
            *(u16 *)((u8 *)arg1 + 0x32) = *(s32 *)((u8 *)D_8AF2BF44 + 0x2C);
            *(u16 *)((u8 *)arg1 + 2) |= 2;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03E38.s")

extern void func_8AC00738();

s32 func_8AF03F14(s32 arg0, s32 arg1) {
    if ((arg0 != 0) && (arg0 == 1)) {
        func_8AC00738();
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03F4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03FF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04340.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04404.s")

s32 func_8AF044C4(s32 arg0, void *arg1) {
    void *inner = *(void **)((u8 *)arg1 + 0x20);
    if (arg0 != 0 && arg0 == 1) {
        if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)((u8 *)inner + 0x4B8)) {
            *(s32 *)((u8 *)arg1 + 0x28) = 0xFFFF00FF;
            *(s32 *)((u8 *)arg1 + 0x2C) = 0xFFFF00FF;
        } else {
            *(s32 *)((u8 *)arg1 + 0x28) = -1;
            *(s32 *)((u8 *)arg1 + 0x2C) = -1;
        }
    }
    return 0;
}

void func_8AF04514(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x24))) = 0xB5;
    (*(s16 *)((u8 *)(arg0) + (0x26))) = 1;
    (*(s32 *)((u8 *)(arg0) + (0x2C))) = -1;
}

void func_8AF04530(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x24))) = 0xB5;
    (*(s16 *)((u8 *)(arg0) + (0x26))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x2C))) = 0xDC0000FF;
}

void func_8AF0454C(u8 *arg0) {
    *(s16 *)(arg0 + 0x24) = 0xB6;
    *(s16 *)(arg0 + 0x26) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF0455C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04894.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04A14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04A54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04C50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04CC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04D68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04DB8.s")

extern s32 func_8AF04DB8(s32);
s32 *func_8AF04E2C(arg0, arg1)
void *arg0;
s32 arg1;
{
    s32 index;

    index = func_8AF04DB8(arg1);
    if (index == -1) {
        return NULL;
    }
    if (index >= 100) {
        return NULL;
    }
    return (s32 *)((u8 *)arg0 + index * 0xC + 0x28);
}

extern s32 func_8AC06D8C(s32, s32);
extern void func_8AC03C28(void);
extern void func_8004E308(s32, void *, s32);
void func_8AF04E8C(s32 arg0) {
    s32 result;
    s32 i;
    void *callback = func_8AC03C28;
    func_8AC06D8C(arg0, 0x706C7463);
    result = func_8AC06D8C(arg0, 0x69636E63);
    for (i = 0; i < 6; i++) {
        s32 value = func_8AC06D8C(arg0, 0x69636E30 + i);
        if (value) {
            func_8004E308(value, callback, result);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04F38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF0501C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF05C10.s")

void *func_8AF05DC8(void *arg0) {
    u8 *node;
    s32 key;
    s32 entry_key;
    void *result;

    node = *(u8 **)((u8 *)arg0 + 0x500);
    key = *(s32 *)((u8 *)arg0 + 0x4B8);
    result = NULL;
    if (node == NULL) {
        return NULL;
    }
loop:
    entry_key = *(s32 *)(node + 4);
    if (entry_key != 0) {
        if (entry_key == key) {
            result = node;
        } else {
            node += 0x34;
            goto loop;
        }
    }
    return result;
}

extern u8 D_8AF27E30[];
extern u8 D_8AF28274[];
extern u8 D_8AF284E4[];
s32 func_8AF05E14(void *arg0, s32 arg1) {
    s32 result;
    u8 *node;
    s32 state;
    s32 entry;

    result = -1;
    state = *(s32 *)((u8 *)arg0 + 0x4DC);
    switch (state) {
    default:
        break;
    case 0x59:
        node = D_8AF27E30;
        break;
    case 0x42:
        node = D_8AF28274;
        break;
    case 0x4D:
        node = D_8AF284E4;
        break;
    }
    while (1) {
        entry = *(s32 *)(node + 4);
        if (entry == 0) {
            break;
        }
        if (arg1 == entry) {
            result = *(s32 *)(node + 0x20);
            break;
        }
        node += 0x34;
    }
    return result;
}

s32 func_8AF05E94(void *arg0) {
    u8 *node;
    s32 key;
    s32 entry_key;
    s32 result;

    node = *(u8 **)((u8 *)arg0 + 0x500);
    key = *(s32 *)((u8 *)arg0 + 0x4B8);
    result = -1;
    if (node == NULL) {
        return -1;
    }
loop:
    entry_key = *(s32 *)(node + 4);
    if (entry_key != 0) {
        if (entry_key == key) {
            result = *(s32 *)(node + 0x20);
        } else {
            node += 0x34;
            goto loop;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF05EE0.s")

s32 func_8AF06404(void *arg0) {
    u8 *node;
    s32 key;
    s32 entry_key;
    s32 result;

    node = *(u8 **)((u8 *)arg0 + 0x500);
    key = *(s32 *)((u8 *)arg0 + 0x4B8);
    result = -1;
    if (node == NULL) {
        return -1;
    }
loop:
    entry_key = *(s32 *)(node + 4);
    if (entry_key != 0) {
        if (entry_key == key) {
            result = *(s32 *)(node + 0x24);
        } else {
            node += 0x34;
            goto loop;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF06450.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF065DC.s")

extern void func_800503A4(s32);
s32 *func_8AF04E2C();

void func_8AF06E74(void) {
    s32 *temp_v0;

#ifdef CC_CHECK
    temp_v0 = func_8AF04E2C((void *)0, 0);
#else
    temp_v0 = func_8AF04E2C();
#endif
    if (temp_v0 != NULL) {
        func_800503A4(*temp_v0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF06EA4.s")

s32 main_pool_alloc(s32, s32);
extern void func_80025F84(s32);
extern void func_8AC00FFC(s32);
extern s32 D_8AF2646C;
extern s32 D_8AF2C020;

void func_8AF070B4(void) {
    if (D_8AF2646C == 0) {
        func_8AC00FFC(0x47425345);
        D_8AF2646C = 1;
        D_8AF2C020 = main_pool_alloc(0x8400, 0);
    }
    func_80025F84(D_8AF2C020);
}

extern void func_8002602C();
extern void func_8AC01064(s32);
void func_8AF07110(void) {
    func_8002602C();
    if (D_8AF2646C != 0) {
        D_8AF2646C = 0;
        func_8AC01064(0x47425345);
    }
}
#endif
