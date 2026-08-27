#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130F630.s")
#endif

void func_8130F69C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130F6A4.s")
#endif

#ifdef VERSION_US
extern u8 D_81312924[];
extern f32 func_8130F6A4(u8 *arg0, u8 *arg1, u8 *arg2);
f32 func_8130F794(u8 *arg0, u8 *arg1) {
    return func_8130F6A4(arg0, arg1, D_81312924);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130F7B8.s")
#endif

#ifdef VERSION_US
extern void func_8130F7B8(u8 *arg0, u8 *arg1);
extern void func_81609A90(u8 *arg0, u8 *arg1);
void func_8130F8B4(u8 *arg0, s32 arg1) {
    u8 sp40[8];
    u8 sp38[8];
    u8 sp30[8];
    u8 sp28[8];
    f32 sp24;
    sp24 = *(f32 *)(arg0 + 0x30);
    *(f32 *)(arg0 + 0x30) = 0.0f;
    func_8130F794(arg0, sp40);
    func_8130F7B8(arg0, sp30);
    *(f32 *)(arg0 + 0x30) = 16.0f;
    func_8130F794(arg0, sp40);
    func_8130F7B8(arg0, sp28);
    if (arg1 != 0) {
        func_81609A90(sp40, sp38);
        func_81609A90(sp30, sp28);
    } else {
        func_81609A90(sp38, sp40);
        func_81609A90(sp28, sp30);
    }
    *(f32 *)(arg0 + 0x30) = sp24;
}
#endif

#ifdef VERSION_US
extern s32 func_8130F970(void *arg0, s32 arg1);
s32 func_8130F970(void *arg0, s32 arg1) {
    if ((arg1 < 4) && (((u8 *)arg0 + arg1)[0x8C] == 2)) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x40) == 0) && (arg1 >= 4) && (arg1 < 6)) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x3C) != 0) && (arg1 >= 4) && (arg1 < 6)) {
        return 0;
    }
    if ((arg1 == 6) && (*(s32 *)((u8 *)arg0 + 0xAC) == 0)) {
        return 0;
    }
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130FA0C.s")
#endif

#ifdef VERSION_US
extern s32 func_8130F970(void *arg0, s32 arg1);
void func_8130FB58(u8 *arg0) {
    s32 i;
    *(s32 *)(arg0 + 0xA8) = 0;
    for (i = 0; i != 7; i++) {
        if (func_8130F970(arg0, i) != 0) {
            *(s32 *)(arg0 + 0xA8) = 1;
        }
    }
}
#endif

#ifdef VERSION_US
void func_8130FBC0(void *arg0) {
    s32 temp_a1;
    s32 i;
    u8 *ptr;
    if ((*(s32 *)((u8 *)arg0 + 0xA8) != 0) &&
        ((temp_a1 = *(s32 *)((u8 *)arg0 + 0x48), temp_a1 < 0) ||
         (temp_a1 >= 7) ||
         (func_8130F970(arg0, temp_a1) == 0))) {
        *(s32 *)((u8 *)arg0 + 0x48) = 0;
        i = 0;
        ptr = (u8 *)arg0;
        while (i < 4) {
            if (ptr[0x8C] == 0) {
                *(s32 *)((u8 *)arg0 + 0x48) = i;
                return;
            }
            i++;
            ptr++;
        }
        i = 0;
        while (i != 7) {
            if (func_8130F970(arg0, i) != 0) {
                *(s32 *)((u8 *)arg0 + 0x48) = i;
                return;
            }
            i++;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130FC80.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130FD10.s")
#endif

#ifdef VERSION_US
extern void func_8130F8B4(u8 *arg0, s32 arg1);
void func_8130FE28(u8 *arg0) {
    switch (arg0[0x38]) {
    case 0:
        *(f32 *)(arg0 + 0x30) = 0.0f;
    case 1:
    case 3:
    case 4:
        arg0[0x38] = 4;
        break;
    }
    func_8130F8B4(arg0, 0);
}
#endif

#ifdef VERSION_US
s32 func_8130FE8C(u8 *arg0) {
    *(f32 *)(arg0 + 0x30) = 0.0f;
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_8130FE9C(u8 *arg0) {
    arg0[0x3A]++;
    *(f32 *)(arg0 + 0x30) = 0.0f;
    return 1;
}
#endif

void func_8130FEB8(void) {
}

#ifdef VERSION_US
extern f32 func_816092FC(void);
extern void func_8130FEC0(u8 *arg0, f32 arg1);
extern f32 func_8130FF70(f32 arg0);
void func_8130FEC0(u8 *arg0, f32 arg1) {
    *(f32 *)(arg0 + 0x30) += arg1;
    if (*(f32 *)(arg0 + 0x30) >= 16.0f) {
        *(f32 *)(arg0 + 0x30) = 16.0f;
        return;
    }
    if (*(f32 *)(arg0 + 0x30) <= 0.0f) {
        *(f32 *)(arg0 + 0x30) = 0.0f;
    }
}
#endif

#ifdef VERSION_US
s32 func_8130FF18(u8 *arg0) {
    func_8130FEC0(arg0, func_816092FC());
    if (*(f32 *)(arg0 + 0x30) >= 16.0f) {
        arg0[0x38] = 3;
    }
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130FF70.s")
#endif

#ifdef VERSION_US
void func_8130FFE0(f32 arg0, f32 arg1) {
    f32 temp[2];
    temp[0] = func_8130FF70(arg1);
    func_8130FF70(temp[0] - func_8130FF70(arg0));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8131001C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_813102A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8131058C.s")
#endif

#ifdef VERSION_US
s32 func_813107A0(u8 *arg0) {
    func_8130FEC0(arg0, -func_816092FC());
    if (*(f32 *)(arg0 + 0x30) <= 0.0f) {
        arg0[0x38] = 5;
        arg0[0x3A] = 0;
    }
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_81310800.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_81310894.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_81310A14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_81310BF8.s")
#endif

#ifdef VERSION_US
extern s32 func_81600DA8(void *arg0, void *arg1);
extern void func_81310A14(s32 arg0);
extern void func_81310BF8(s32 arg0);
extern void func_81311650(s32 arg0, s32 arg1);
void func_81311030(s32 arg0, s32 arg1) {
    if (func_81600DA8((void *)arg1, (void *)(arg0 + 1)) != 0) {
        func_81310A14(arg0);
    }
    if (func_81600DA8((void *)arg1, (void *)(arg0 + 2)) != 0) {
        func_81310BF8(arg0);
    }
    func_81311650(arg0, arg1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8131109C.s")
#endif
