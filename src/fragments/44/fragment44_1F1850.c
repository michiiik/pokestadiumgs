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

extern u8 D_8AF2C4F8[];
extern u32 D_8AF2C548;
void func_8AF03624(void *arg0) {
    if (--D_8AF2C548 < 0xA) {
        *(s32 *)((u8 *)arg0 + 0x4E4) = *(s32 *)(D_8AF2C4F8 + D_8AF2C548 * 8);
        *(s32 *)((u8 *)arg0 + 0x4E8) = *(s32 *)(D_8AF2C4F8 + D_8AF2C548 * 8 + 4);
        *(s32 *)((u8 *)arg0 + 0x4EC) = *(s32 *)((u8 *)arg0 + 0x4E8);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03678.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03730.s")

extern u16 D_8AF2C560;
extern u8 D_8AF2C278[];
extern f32 D_80088E50[];
extern f32 D_8AF28D4C;
void func_8AF03798(void) {
    s32 angle = D_8AF2C560;
    s32 increment;
    f32 result = D_80088E50[angle >> 4] * D_8AF28D4C + 1.0f;
    *(f32 *)(D_8AF2C278 + 0x40) = result;
    *(f32 *)(D_8AF2C278 + 0x44) = result;
    if (1) {
        increment = 0x2000;
    }
    D_8AF2C560 = angle + increment;
}

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

extern s32 D_8AF26470;
extern s32 D_8AF2BF78;
extern s32 func_8004C874(u16, u16);
extern s32 func_800472E0(s32);
s32 func_8AF03F4C(s32 arg0, void *arg1) {
    union { s32 i; s32 pad[5]; } width;
    s32 value;
    switch (arg0) {
    case 0:
        D_8AF26470 = 0x1E0;
        break;
    case 1:
        width.i = *(s8 *)((u8 *)arg1 + 0x26);
        value = func_800472E0(func_8004C874(*(u16 *)((u8 *)arg1 + 0x30), *(u16 *)((u8 *)arg1 + 0x32)));
        D_8AF26470 = *(s16 *)((u8 *)arg1 + 0xA) + value * width.i - D_8AF2BF78 - width.i;
        if (D_8AF26470 <= 0) {
            D_8AF26470 = 1;
        }
        break;
    }
    return 0;
}

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

extern s32 D_8AF2C584;
extern s32 D_8AF2C588;
extern s32 D_8AF2C58C;
extern s16 D_8AF2BA6C;
extern u8 D_8AF28A90[];
extern u8 D_8AF28A94[];
extern u8 D_8AF28A98[];
extern void func_800504BC(void *);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800495F8(s32, s32, s32, void *, s32);
extern void func_800499EC(void);
extern s32 func_8004C874(u16, u16);
void func_8AF04894(s32 arg0, u8 *arg1) {
    s16 pos[5];
    switch (arg0) {
    case 0:
        *(u16 *)(arg1 + 2) &= ~2;
        D_8AF2C584 = func_8004C874(0x37, 0x1EE);
        D_8AF2C588 = func_8004C874(0x37, 0x1EF);
        D_8AF2C58C = func_8004C874(0x37, 0x1F0);
        break;
    case 1:
        func_800504BC(pos);
        pos[3] = *(s16 *)(arg1 + 8) + pos[0];
        pos[2] = *(s16 *)(arg1 + 0xA) + pos[1];
        func_800498C4();
        func_800496A4(8, 0);
        func_8004972C(0xFF, 0xFF, 5, 0xFF);
        switch (D_8AF2BA6C) {
        case 3:
            func_800495F8(pos[3], pos[2], 1, D_8AF28A90, D_8AF2C584);
        break;
        case 4:
            func_800495F8(pos[3], pos[2], 1, D_8AF28A94, D_8AF2C588);
        break;
        case 5:
            func_800495F8(pos[3], pos[2], 1, D_8AF28A98, D_8AF2C58C);
        break;
        }
        func_800499EC();
        break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04A14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04A54.s")

extern void func_8AF0455C();
extern void func_8004E308(s32, void *, s32);
extern s32 func_8AC06D8C(s32, s32);
void func_8AF04C50(void *arg0, s32 arg1, u8 *arg2) {
    void *callback = func_8AF0455C;
    *(s32 *)((u8 *)arg0 + 0x4E8) = *(s32 *)(arg2 + 0x14);
    *(u8 **)((u8 *)arg0 + 0x528) = arg2;
    while (1) {
        s32 value = *(s32 *)(arg2 + 0x14);
        s32 found;
        if (value == 0) {
            break;
        }
        found = func_8AC06D8C(arg1, value);
        if (found != 0) {
            func_8004E308(found, callback, (s32)arg2);
        }
        arg2 += 0x34;
    }
}

extern void func_8004E308(s32, void *, s32);
extern s32 func_8AC06D8C(s32, s32);
extern s32 func_8AF044C4(s32 arg0, void *arg1);
void func_8AF04CC8(void *arg0, s32 arg1, u8 *arg2) {
    void *callback = func_8AF044C4;
    u8 *offset;
    struct Pair {s32 x; s32 y;}; *(struct Pair *)((u8 *)arg0 + 0x4E0) = *(struct Pair *)(arg2 + 4); *(u8 **)((u8 *)arg0 + 0x528) = arg2;
    while (1) {
        s32 value = *(s32 *)(arg2 + 4);
        s32 found;
        if (value == 0) break;
        offset = (u8 *)arg0 + 0x28;
        found = func_8AC06D8C(arg1, value);
        *(s32 *)(*(u8 **)(offset + 0x500) + 0x30) = found;
        if (found != 0) func_8004E308(found, callback, (s32)offset);
        arg2 += 0x34;
    }
}

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
