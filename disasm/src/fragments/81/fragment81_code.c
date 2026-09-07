#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84300020.s")

extern u8 D_843023A8[]; u8 func_8430009C(void) { return D_843023A8[(func_8003570C() & 3)]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_843000C8.s")

extern u8 D_843023AC[]; u8 func_843001CC(void) { u32 value = func_8003570C(); u32 remainder = value % 10; return D_843023AC[remainder]; }

void func_84300200(u8 *arg0, u8 arg1) {
    if (arg0 != 0) {
        arg0[(u8)++arg0[0]] = arg1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_8430022C.s")

u8 func_84300348(u8 *arg0) {
    return *arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84300350.s")

s32 func_843003E0(u8 *arg0, u8 arg1) {
    s32 i;

    for (i = 1; i <= arg0[0]; i++) {
        if (arg0[i] == arg1) {
            return (u8)i;
        }
    }
    return 0;
}

extern void func_84300200(u8 *, u8);
extern s32 func_843003E0(u8 *, u8);
void func_8430042C(u8 *arg0, u8 *arg1) {
    s32 i;

    if (func_843003E0(arg0, arg1[1]) != 0) {
        i = 0;
        if (arg1[2] > 0) {
            do {
                func_84300200(arg0, arg1[1]);
                i++;
            } while (i < arg1[2]);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_8430049C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_843005B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84300648.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_843006B0.s")

extern u8 func_843006B0(u8, u8);
extern u8 *D_84302C80;
extern u8 D_84302C88[];
u8 func_843007BC(u8 arg0, u8 arg1) {
    s32 i;
    u8 *p;

    if (arg1 == 0) {
        return 1;
    }
    if (func_843006B0(arg0, arg1) != 0) {
        return 1;
    }
    p = D_84302C80;
    for (i = 0; i < D_84302C88[0]; i++) {
        if (p[0] != 0 && p[1] == arg1) {
            return 1;
        }
        p += 0x58;
    }
    return 0;
}

extern u8 *D_84302C80;
extern u8 D_84302C88[];
s32 func_84300858(u8 arg0) {
    u8 *p;
    s32 i;

    p = D_84302C80;
    i = 0;
    while (i < D_84302C88[0]) {
        if (*p != 0 && *p == arg0) {
            return 0;
        }
        i++;
        p += 0x58;
    }
    return 1;
}

s32 func_800630F0(s32);
extern s32 D_84302C98;
u8 func_8006397C(u8 arg0);
u8 func_800639C0(u8 arg0);
s32 func_843008B0(u8 arg0) {
    s32 var_v1;

    var_v1 = ((1 << func_800630F0(func_8006397C(arg0) & 0xFF)) & D_84302C98) != 0;
    if (var_v1 == 0) {
        var_v1 = ((1 << func_800630F0(func_800639C0(arg0) & 0xFF)) & D_84302C98) != 0;
    }
    return var_v1;
}

extern u8 * D_84302C80;
extern u8 D_84302C88[];
s32 func_84300928(u8 arg0) {
    u8 *p;
    u8 *q;
    s32 i;
    s32 j;
    p = D_84302C80;
    i = 0;
    while (i < D_84302C88[0]) {
        j = 0;
        q = p;
        while (j < 4) {
            if (q[2] == 0) { break; }
            if (q[2] == arg0) { return 0; }
            j++;
            q++;
        }
        i++;
        p += 0x58;
    }
    return 1;
}

typedef struct {
    u16 value;
    u8 tail[0x92];
} Fragment81Row;
extern u8 D_84302566[];
extern u8 D_84302C88[];
extern u8 D_84303008[];
extern u8 D_84303108[];
extern s32 func_84300648(u8);
extern void func_84300200(u8 *, u8);
void func_843009A4(u8 arg0) {
    s32 result;
    s32 first;
    s32 limit;

    if (arg0 > 0 && arg0 < 0xFC) {
        result = func_84300648(arg0);
        first = ((Fragment81Row *)D_84302566)[D_84302C88[1]].value;
        limit = *(u16 *)(D_84302C88 + 0xE);
        if ((first < limit && result < limit) || (first >= limit && result >= limit)) {
            func_84300200(D_84303008, arg0);
        } else {
            func_84300200(D_84303108, arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84300A54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84300B30.s")

extern u8 func_8430022C(u8 *);
extern u16 D_84302CA0;
extern s32 func_800630F0(s32);
extern u8 func_8006397C(u8 arg0);
extern u8 func_800639C0(u8 arg0);
extern u8 func_84300348(u8 *arg0);
extern s32 func_84300648(u8);
extern u8 D_84302C88[];
extern u8 D_84303008[];
extern u8 D_84303108[];
u8 func_84300BE8(void) {
    u8 result;
    result = 0;
    if (func_84300348(D_84303008) > 0) result = func_8430022C(D_84303008);
    else if (func_84300348(D_84303108) > 0) result = func_8430022C(D_84303108);
    if (result != 0) {
        D_84302CA0 = func_84300648(result);
        *(u32 *)(D_84302C88 + 0x10) |= 1 << func_800630F0(func_8006397C(result) & 0xFF);
        *(u32 *)(D_84302C88 + 0x10) |= 1 << func_800630F0(func_800639C0(result) & 0xFF);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84300CC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84301094.s")

extern u8 func_84300350(u8 *, u8);
extern s32 func_8430049C(u8);
extern u8 D_84302CA2[];
extern u8 D_84302FAE[];
extern u8 D_84302FD2[];
extern u8 func_8430022C(u8 *);
extern u8 func_84300348(u8 *arg0);
extern s32 func_84300928(u8 arg0);
u8 func_843013A4(u8 *arg0) {
    u8 result;

    result = 0;
    if (func_84300348(D_84302CA2) > 0) {
        result = func_8430022C(D_84302CA2);
        func_84300350(D_84302CA2, result);
    } else if (func_84300348(D_84302FAE) > 0) {
        result = func_8430022C(D_84302FAE);
        if (func_84300928(result) == 0) {
            result = func_8430022C(D_84302FAE);
        }
        func_84300350(D_84302FAE, result);
    } else if (func_84300348(D_84302FD2) > 0) {
        result = func_8430022C(D_84302FD2);
        func_84300350(D_84302FD2, result);
    }
    func_8430049C(result);
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84301490.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_843016CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84301838.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_8430188C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84301AEC.s")

extern void func_8430188C(u8);
extern u8 func_84300CC0(void);
extern u8 func_84301094(u8 *);
extern u8 func_843013A4(u8 *);
extern u8 func_84301490(u8 *);
void func_84301BA4(u8 *arg0) {
    u8 value;

    value = arg0[0];
    switch (value) {
    case 0x84:
        arg0[2] = 0x90;
        arg0[3] = 0;
        arg0[4] = 0;
        arg0[5] = 0;
        return;
    case 0xCA:
        arg0[2] = 0x44;
        arg0[3] = 0xF3;
        arg0[4] = 0xDB;
        arg0[5] = 0xC2;
        return;
    default:
        func_8430188C(value);
        arg0[2] = func_84300CC0();
        arg0[3] = func_84301094(arg0);
        arg0[4] = func_843013A4(arg0);
        arg0[5] = func_84301490(arg0);
        return;
    }
}

extern u8 func_80062E10(u8);
void func_84301C58(u8 *arg0) {
    s32 i;
    u8 *p;
    u8 value;
    u8 result;

    p = arg0;
    i = 0;
    do {
        value = p[2];
        if (value == 0) {
            return;
        }
        result = func_80062E10(value);
        i++;
        p++;
        p[0x17] = result;
    } while (i != 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84301CB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84301DEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_843020F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84302148.s")
#endif
