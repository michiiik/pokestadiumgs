#include "global.h"


void func_83200020(void) {
}

#ifdef VERSION_US
extern void func_81600F0C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_818057D0(void *arg0, void *arg1, void *arg2);
void func_83200028(void *arg0, void *arg1, void *arg2) {
    func_81600F0C(*(void **)((u8 *)arg1 + 0x38), 0, 0, 0x280, 0x1E0);
    func_818057D0(arg0, arg1, arg2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/5/fragment5_code/func_83200078.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/5/fragment5_code/func_83200484.s")
#endif

#ifdef VERSION_US
extern void _bzero(void *ptr, s32 size);
extern u8 D_83200D38[];
extern void func_81804954(void *arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4);
extern void func_81804A00(void *arg0);
extern void *func_8004D690(s32 arg0);
typedef struct {
    u8 pad00[0x1E];
    u8 active;
    u8 pad1F[0x19];
    void *resource0;
    void *resource1;
    u16 value;
    u8 width;
    u8 height;
    u8 flags;
} Frag5Resource;
void func_83200744(Frag5Resource *arg0, s32 arg1) {
    _bzero(arg0, 0x48);
    func_81804954(arg0, 0, 2, D_83200D38, arg1);
    func_81804A00(arg0);
    arg0->active = 1;
    arg0->resource0 = func_8004D690(0x18);
    arg0->resource1 = func_8004D690(0x2D);
    arg0->value = 0;
    arg0->width = 9;
    arg0->height = 0x1E;
    arg0->flags = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/5/fragment5_code/func_832007D4.s")
#endif

#ifdef VERSION_US
extern u8 D_83200DB0[];
extern void func_800088DC(void);
extern void func_818017A8(void);
extern void func_81805308(void *);
extern void func_80008648(void);
void func_832008F0(s32 arg0) {
    func_800088DC();
    func_818017A8();
    func_81805308(D_83200DB0);
    func_80008648();
}
#endif

#ifdef VERSION_US
extern s32 func_832007D4(s32 arg0);
extern void func_832008F0(s32 arg0);
void func_8320092C(s32 arg0, s32 arg1) {
    s32 state = 0;
    while (state != 4) {
        state = func_832007D4(state);
        func_832008F0(state);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/5/fragment5_code/func_8320097C.s")
#endif

#ifdef VERSION_US
extern void func_80008574(void);
extern void func_80047610(void);
extern void func_8004C398(void);
extern void func_80006D3C(void);
void func_83200A84(s32 arg0, s32 arg1) {
    func_80008574();
    func_80047610();
    func_8004C398();
    func_80006D3C();
}
#endif

#ifdef VERSION_US
extern void main_pool_push_state(s32 arg0);
extern void main_pool_pop_state(s32 arg0);
extern void func_8320097C();
extern void func_8320092C();
extern void func_83200A84(s32 arg0, s32 arg1);
s32 func_83200AC0(s32 arg0, s32 arg1) {
    main_pool_push_state(0x57445052);
    func_8320097C(arg0, arg1);
    func_8320092C(arg0, arg1);
    func_83200A84(arg0, arg1);
    main_pool_pop_state(0x57445052);
    return 0;
}
#endif
