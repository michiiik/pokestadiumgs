#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_831000FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_831001A8.s")

extern u8 *func_8006218C(s32, s32, s32, s32);
extern s8 func_80062390(void *, s32, u8 *);
extern void func_80062304(u8 *);
extern void func_800226C0(s32);
void func_83100584(void *arg0) {
    u8 *sp18;
    u8 *temp_v0;

    temp_v0 = func_8006218C(0x18, 0, 0, 0);
    if (temp_v0 != NULL) {
        sp18 = temp_v0;
        ((u8 *)arg0)[0x2EC] = func_80062390((u8 *)arg0 + 0xCC, 8, temp_v0);
        func_80062304(sp18);
        return;
    }
    ((u8 *)arg0)[0x2EC] = 0;
}

extern void func_800226C0(s32);
typedef struct Copy831005F0 { s32 words[17]; } Copy831005F0;
void func_831005F0(void *arg0, void *arg1) {
    *(Copy831005F0 *)((u8 *)arg0 + 0x68) = *(Copy831005F0 *)arg1;
    ((u8 *)arg0)[0x64] = 1;
    func_800226C0(0xD2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_8310065C.s")

extern void func_81600F0C(void *, s32, s32, s32, s32);
extern void func_818057D0(void *, void *, void *);
void func_83100A98(void *arg0, u8 *arg1, void *arg2) {
    func_81600F0C(*(void **)(arg1 + 0x5C), 0, 0, 0x280, 0x1E0);
    func_818057D0(arg0, arg1, arg2);
}

extern void func_81700D44(s32);
extern void func_8170024C(void);
s32 func_83100AE8(void *arg0, u8 *arg1) {
    if (arg1[0x1D] == 0) {
        func_81700D44(0);
        func_81700D44(1);
    }
    func_8170024C();
    return 1;
}

extern s32 func_81600DA8(void *, void *);
extern void func_81700908(void);
extern u8 D_83102290[];
void func_83100B2C(void *arg0, u8 *arg1, void *arg2) {
    if (func_81600DA8(*(void **)(arg1 + 4), D_83102290) == 0) {
        func_81600F0C(*(void **)(arg1 + 0x5C), 0, 0, 0x280, 0x46);
    }
    func_81700908();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100B8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100BF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100CA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100D10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100DBC.s")

void func_83100E98(u8 *arg0, s32 arg1)
{
  s32 result = arg1 - 4;
  s32 limit = arg0[0xCB] - 9;
  if (limit < result)
  {
    result = limit;
  }
  if (limit = result < 0)
  {
    result = 0;
  }
  arg0[0x43] = result;
  arg0[0x40] = ((arg1 - result) & 0xFFu) + 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83100ED4.s")

extern void *func_818054D0(void *, s32);
extern s32 func_81804A20(void *);
extern s32 func_81805524(void *, u8 *);
extern s32 func_800718B8(s32);
extern u8 D_831038FF[];
s32 func_83100FA4(void *arg0, u8 *arg1) {
    u8 temp_v0;
    s32 result[2];

    func_818054D0(arg0, arg1[0x1F]);
    if ((func_81804A20(arg1) != 0) && ((*(u16 *)(arg1 + 0x14) & 0x10) != 0) &&
        (temp_v0 = arg1[0x3E], temp_v0 < 6)) {
        result[0] = 1;
        func_831005F0(arg1, func_800718B8(D_831038FF[temp_v0]));
    } else {
        result[0] = func_81805524(arg0, arg1);
    }
    return result[0];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_8310103C.s")

void func_83101090(void *arg0, s32 arg1) {
    if (arg1 == -1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 1;
        func_800226C0(3);
        return;
    }
    if (arg1 == 1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 3;
        func_800226C0(2);
        return;
    }
    if (arg1 >= 2) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 4;
        func_800226C0(2);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101104.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_831011A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101244.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101400.s")

extern void func_800226C0(s32);
void func_83101714(void *arg0, s32 arg1) {
    if (arg1 == -1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 2;
        func_800226C0(3);
        return;
    }
    if (arg1 > 0) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 4;
        func_800226C0(0x90);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101764.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101804.s")

extern void *func_818054D0(void *arg0, s32 arg1);
extern void func_81801CB8(void *arg0, void *arg1, void *arg2, s32 arg3);
void func_83101B04(void *arg0, u8 *arg1, void *arg2) {
    void *first_offset;
    void *first;
    void *second;

    first = func_818054D0(arg0, arg1[0x1C]);
    first_offset = (u8 *)first + 0x10;
    second = func_818054D0(arg0, arg1[0x1D]);
    func_81801CB8(arg2, first_offset, (u8 *)second + 0x10, *(s32 *)(arg1 + 0x2C));
}

void func_83101B60(void *arg0, s32 arg1) {
    if (arg1 == -1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 4;
        func_800226C0(3);
        return;
    }
    if (arg1 > 0) {
        if (*(u8 *)((u8 *)arg0 + 0x2EC) >= arg1) {
            *(u8 *)((u8 *)arg0 + 0x1E) = 7;
            func_800226C0(0x90);
            return;
        }
        func_800226C0(5);
    }
}

extern void func_800226C0(s32);
void func_83101BD4(void *arg0, s32 arg1) {
    if (arg1 == -1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 4;
        func_800226C0(3);
        return;
    }
    if (arg1 > 0) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 7;
        func_800226C0(0x8D);
    }
}

extern void *func_818054D0(void *arg0, s32 arg1);
extern void func_81801CB8(void *arg0, void *arg1, void *arg2, s32 arg3);
void func_83101C24(void *arg0, u8 *arg1, void *arg2) {
    void *first_offset;
    void *first;
    void *second;

    first = func_818054D0(arg0, arg1[0x1C]);
    first_offset = (u8 *)first + 0x10;
    second = func_818054D0(arg0, arg1[0x1D]);
    func_81801CB8(arg2, first_offset, (u8 *)second + 0x10, *(s32 *)(arg1 + 0x2C));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101C80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101D74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101EB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_83101F5C.s")

extern void func_800088DC(void);
extern void func_818017A8(void);
extern void func_8004C594(s32, s32);
extern void func_81805308(void *);
extern void func_80008648(void);
extern void func_83101EB0(void);
extern u8 D_831039B0[];
extern u8 D_83103A14;
extern u8 D_83103A7B;
void func_83101FFC(s32 arg0) {
    func_800088DC();
    func_818017A8();
    func_8004C594(1, D_831039B0[0x40] + D_831039B0[0x43] - 1);
    func_8004C594(2, D_83103A7B);
    func_81805308(D_831039B0);
    func_80008648();
    if (D_83103A14 > 0) {
        func_83101EB0();
    }
}

s32 func_83101F5C(s32);
extern void func_83101FFC(s32);
void func_83102080(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    do {
        temp_v0 = func_83101F5C(var_s0);
        var_s0 = temp_v0;
        func_83101FFC(temp_v0);
    } while (var_s0 != 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_831020D0.s")

extern void Gfx_FreeDisplayListBuffers();
extern void func_80008574();
extern void func_80047610();
extern void func_8004C398();

void func_831021E8(s32 arg0, s32 arg1) {
    func_80008574();
    func_8004C398();
    func_80047610();
    Gfx_FreeDisplayListBuffers();
}

extern void func_83102080(s32, s32);
extern void func_831020D0(s32, s32);
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
s32 fragment6_main(s32 arg0, s32 arg1) {
    main_pool_push_state(0x4642534C);
    func_831020D0(arg0, arg1);
    func_83102080(arg0, arg1);
    func_831021E8(arg0, arg1);
    main_pool_pop_state(0x4642534C);
    return 0;
}
#endif
