#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_842017D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_842018A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_842018FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_8420199C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84201AEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84201DDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84201F2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84202020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84202198.s")

extern void _bzero(void *, s32);
void func_84202294(void *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    _bzero(arg0, 0x10);
    ((u8 *)arg0)[1] = arg1;
    ((u8 *)arg0)[2] = 3;
    ((u8 *)arg0)[3] = arg2;
    ((u8 *)arg0)[4] = arg3;
    ((u8 *)arg0)[5] = arg4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_842022F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_842024CC.s")

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 value;
} F84202744Entry;
extern F84202744Entry D_84203A88[];
typedef struct {
    u8 unk00;
    u8 unk01;
    u8 count;
    u8 indices[9];
    s32 total;
} F84202744State;
void func_84202744(F84202744State *arg0) {
    s32 i;

    arg0->total = 0;
    for (i = 0; i < arg0->count; i++) {
        arg0->total += D_84203A88[arg0->indices[i]].value;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84202798.s")

typedef struct F842029A8State {
    u8 active;
    u8 pad01[4];
    u8 selected;
    u8 count;
    u8 indices[6];
} F842029A8State;
typedef struct F842029A8Record {
    u8 pad00[8];
    u8 count;
    u8 pad09[0x4D7];
} F842029A8Record;
extern F842029A8State D_84203AD0;
extern F842029A8Record *D_84203B54;
void func_842029A8(u8 arg0) {
    s32 i;

    D_84203AD0.selected = arg0;
    D_84203AD0.count = D_84203B54[arg0].count;
    for (i = 0; i < D_84203AD0.count; i++) {
        D_84203AD0.indices[i] = i;
    }
    D_84203AD0.active = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84202A20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84202B58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84202BD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84202EE4.s")

void func_84202FE4(void *arg0) { func_84202BD0(arg0); func_84202EE4(arg0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_8420300C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84203090.s")

extern u32 D_84203A40;
extern u32 func_8003570C(void);
void func_8420300C(void *arg0);
void func_84203090(void *arg0);
void func_842032AC(void) {
    s32 index;
    s32 limit;
    s32 last;

    if (*(u8 *)&D_84203AD0 != 0) {
        limit = (D_84203A40 & 0x40) ? 7 : 3;
        last = *(u8 *)&D_84203AD0 - 1;
        if (limit >= last) {
            limit = last;
        }
        index = func_8003570C() % (limit + 1);
        func_8420300C((u8 *)&D_84203AD0 + (index * 0x10 + 4));
        func_84203090((u8 *)&D_84203AD0 + (index * 0x10 + 4));
    }
}

void func_842017D0(u8);
void func_842018A8(void);
void func_84201F2C(u8);
void func_84202020(u8);
void func_84202B58(u8);
void func_84202198(u8);
void func_842032AC(void);
void func_84203360(u8 arg0) {
    if (((u8 *)D_84203B54)[arg0 * 0x4E0 + 0x49A] != 0) {
        func_842017D0(arg0);
        func_842018A8();
        func_84201F2C(arg0);
        func_84202020(arg0);
        func_84202B58(arg0);
        func_84202198(arg0);
        func_842032AC();
    }
}

extern void *D_84203B58;
extern void func_80035700(u32);
void func_842033EC(F842029A8Record *arg0, void *arg1) {
    struct {
        u32 count;
        u32 reserved;
    } state;
    u32 value;

    D_84203B54 = arg0;
    D_84203B58 = arg1;
    state.count = osGetCount();
    value = guRandom() & state.count;
    func_80035700(((value & 0xFFFF0000) >> 16) | ((value & 0xFFFF) << 16));
}

extern u8 D_842034D0;
u8 func_84203440(void) {
    return D_842034D0;
}

extern u8 D_842034D4;
u8 func_8420344C(void) {
    return D_842034D4;
}

extern u8 D_842034D8;
u8 func_84203458(void) {
    return D_842034D8;
}

extern u8 D_842034DC;
u8 func_84203464(void) {
    return D_842034DC;
}

extern u8 D_842034E0;
u8 func_84203470(void) {
    return D_842034E0;
}

extern u8 D_842034E4;
u8 func_8420347C(void) {
    return D_842034E4;
}

extern u8 D_842034EC;
u8 func_84203488(void) {
    return D_842034EC;
}

extern u8 D_842034F0;
u8 func_84203494(void) {
    return D_842034F0;
}

extern u8 D_842034E8;
u8 func_842034A0(void) {
    return D_842034E8;
}
#endif
