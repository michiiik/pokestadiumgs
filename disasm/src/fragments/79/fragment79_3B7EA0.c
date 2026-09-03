#include "global.h"


#ifdef VERSION_US
extern void func_84149400(void);
extern void func_8414C18C(void);
extern void func_8414BEB0(void);
extern void func_84156814(void);
extern void func_8414C4AC(void);
void func_84148610(void) {
    func_84149400();
    func_8414C18C();
    func_8414BEB0();
    func_84156814();
    func_8414C4AC();
}

extern void func_84155A1C(void);
extern void func_84154948(u8);
extern void func_84148610(void);
void func_84148650(u8 arg0) {
    func_84155A1C();
    func_84154948(arg0);
    func_84148610();
}

extern void func_84154AD4(void);
extern void func_84156510(void);
extern void func_8414BEE8(void);
void func_84148680(void) {
    func_84154AD4();
    func_84156510();
    func_8414BEE8();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_841486B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_841487A8.s")

extern u8 *func_84154B64(u8);
extern void func_841487A8(u8 *);
extern s32 func_800643CC(s32, s32, s32);
void func_84148A4C(u8 *arg0) {
    s32 i;
    u8 *value;

    value = func_84154B64(arg0[0]);
    i = 1;
    do {
        arg0[1] = (u8)i;
        if (func_800643CC(value[0], i & 0xFF, value[0xC]) != 0) {
            func_841487A8(arg0);
        }
        i += 1;
    } while (i != 0xFC);
}

extern u8 *D_84195208[];
extern void func_841487A8(u8 *);
void func_84148AC8(u8 *arg0) {
    s32 i;

    for (i = 0; i != 4; i++) {
        arg0[1] = D_84195208[arg0[0]][i + 5];
        func_841487A8(arg0);
    }
}

extern u8 *func_841565E0(s32);
extern void func_841487A8(u8 *);
void func_84148B40(u8 *arg0) {
    s32 i = 0;
    while (i != 4) {
        u8 *value = func_841565E0(arg0[0]);
        arg0[1] = *(value + i + 1);
        if (arg0[1] > 0 && arg0[1] < 0xFC) {
            func_841487A8(arg0);
        }
        i += 1;
    }
}

extern u8 *func_84154B0C(void);
extern u8 *D_841951F8[];
u8 func_84148BB4(u8 arg0) {
    u8 index;
    s32 result;
    u8 *entry;
    u8 *ptr;
    entry = func_84154B0C() + arg0 * 0xCC;
    index = arg0;
    ptr = entry + 8;
    if (entry[0x21] & 0x10) {
        return ptr[0x25];
    }
    result = ptr[0x17];
    if (result & 1) {
        return 0x75;
    }
    if (ptr[0x18] & 0x20) {
        return 0;
    }
    if ((result & 0x12) || (ptr[0x15] & 0x20)) {
        return D_841951F8[index][1];
    }
    return 0xFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_84148C74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_84148D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_84149294.s")

extern u8 D_8419D7B0[];
extern u8 D_8419D7B1;
extern u8 D_8419D7B2;
extern u8 D_84187030;
extern u16 D_84187038;
u8 *func_841493DC(void) {
    return D_8419D7B0;
}

u8 func_841493E8(void) {
    return D_8419D7B0[0];
}

u8 func_841493F4(void) { return D_8419D7B1; }

extern u32 func_8003570C(void);
void func_84149400(void) {
    D_8419D7B2 = func_8003570C();
}

u8 func_84149424(void) { return D_8419D7B2; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_84149430.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_84149568.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_841496C0.s")

extern u8 func_80063454(u8, u8, u8, s32);
void func_8414978C(u8 *arg0) {
    u8 *ptr;
    if (arg0[1] == 0xA5) {
        return;
    }
    ptr = arg0;
    if (func_80063454(ptr[4], (*(u8 **)(ptr + 0x14))[2], (*(u8 **)(ptr + 0x14))[3],
                       ((*(u8 **)(ptr + 0x14))[0x15] & 8) != 0) == 0) {
        *(s32 *)(ptr + 0xC) = 0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_841497E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_84149928.s")

extern void func_8414978C(u8 *);
extern void func_841496C0(u8 *);
void func_84149A50(void *arg0) {
    u8 *value;
    value = arg0;
    if (value[0] & 1) {
        return;
    }
    if (value[2] == 0x26 || value[2] == 0x28 || value[2] == 0x29 || value[2] == 0x57 || value[2] == 0x58 || value[2] == 0x94) {
        func_8414978C(value);
    } else {
        func_841496C0(value);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_84149AC8.s")

extern f64 D_8418B9A0;
void func_84149C70(void *arg0) {
    u8 *value;
    value = arg0;
    if (value[2] == 0x26 || value[2] == 0x28 || value[2] == 0x29 || value[2] == 0x57 || value[2] == 0x58) {
        return;
    }
    if (value[1] == 2 || value[1] == 0xD || value[1] == 0x4B || value[1] == 0x98 || value[1] == 0xA3 || value[1] == 0xB1 || value[1] == 0xEE) {
        return;
    }
    *(s32 *)(value + 0xC) = (s32)((f64)*(s32 *)(value + 0xC) * D_8418B9A0);
}

extern void func_841497E8(void *);
extern void func_84149928(void *);
extern void func_84149A50(void *);
extern void func_84149C70(void *);
extern void func_84149AC8(void *);
void func_84149D0C(void *arg0) {
    func_841497E8(arg0);
    func_84149928(arg0);
    func_84149A50(arg0);
    func_84149C70(arg0);
    func_84149AC8(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_84149D54.s")

u8 func_84149E58(u8 *arg0) {
    if (arg0[1] == 8) {
        if ((*(u16 *)(*(u8 **)(arg0 + 8) + 0x26) & 7) == 0) {
            return 1;
        }
    }
    if ((*(u8 **)(arg0 + 8))[0x18] & 0x10) {
        if (arg0[1] == 3) {
            return 1;
        }
        if (arg0[1] == 8) {
            return 1;
        }
    }
    return 0;
}

s32 func_84149EC8(u8 *arg0) {
    u8 *value;
    value = *(u8 **)(arg0 + 8);
    if (value[0x19] & 0x20) {
        if (value[0x17] & 0x40) {
            if (arg0[0] == 0x59 || arg0[0] == 0x5A || arg0[0] == 0xDE) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
void func_84149EC8_padding(void) {}

u8 func_84149F30(u8 *arg0) {
    if (arg0[0] == 0x57) {
        if (arg0[3] == 1) {
            return 1;
        }
        if (arg0[3] == 2) {
            arg0[2] = 0x80;
        }
    }
    return 0;
}

extern void func_84124410(u8 *, u8, u8, u8 *);
void func_84149F74(u8 *arg0) {
    u8 *value = *(u8 **)(arg0 + 8);
    if (!(value[0x15] & 8)) {
        func_84124410(arg0 + 2, (*(u8 **)(arg0 + 4))[0x12], value[0x13], arg0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_84149FB8.s")

extern u8 func_80062D98(u8);
extern s32 func_84155574(u8 *, u8);
void func_8414A0C8(u8 *arg0) {
    s32 difference;
    s32 result;
    difference = (*(u8 **)(arg0 + 4))[0xC] - (*(u8 **)(arg0 + 8))[0xC];
    result = func_84155574(*(u8 **)(arg0 + 8), func_80062D98(arg0[0]));
    if (result != 0 && difference >= 0) {
        arg0[2] += difference * 2;
    } else {
        arg0[2] = 0;
    }
}

extern void func_8414A0C8(u8 *);
extern void func_84149FB8(u8 *);
void func_8414A144(u8 *arg0) {
    if (arg0[1] == 0x26) {
        func_8414A0C8(arg0);
    }
    func_84149FB8(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7EA0/func_8414A180.s")

u8 func_8414A240(void) { return D_84187030; }

extern u8 D_84187034;
u8 func_8414A24C(void) {
    return D_84187034;
}

u16 func_8414A258(void) { return D_84187038; }

extern u8 D_84187040;
u8 func_8414A264(void) {
    return D_84187040;
}

extern u8 D_84187044[];
u8 func_8414A270(u8 arg0) {
    return D_84187044[arg0];
}

extern u8 D_8418704C;
u8 func_8414A288(void) {
    return D_8418704C;
}

extern u8 D_84187054;
u8 func_8414A294(void) {
    return D_84187054;
}

extern u8 D_84187058;
u8 func_8414A2A0(void) {
    return D_84187058;
}

extern u8 D_84187050;
u8 func_8414A2AC(void) {
    return D_84187050;
}

extern u8 D_8418705C;
u8 func_8414A2B8(void) {
    return D_8418705C;
}

extern u8 D_8418703C;
u8 func_8414A2C4(void) {
    return D_8418703C;
}

extern u8 D_84187060;
u8 func_8414A2D0(void) {
    return D_84187060;
}

extern u8 D_84187064;
u8 func_8414A2DC(void) {
    return D_84187064;
}
#endif
