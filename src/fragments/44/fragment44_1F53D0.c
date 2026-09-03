#include "global.h"


#ifdef VERSION_US
extern void func_8AF00504(s32);
void func_8AF07160(void) { func_8AF00504(27); }

extern void *D_8AF263C0;

s32 func_8AF07180(void) {
    s32 var_v1;

    var_v1 = 2;
    if ((*(u16 *)((u8 *)(D_8AF263C0) + (8))) & 0x4000) {
        var_v1 = 1;
    }
    return var_v1;
}

extern void func_800495BC(s32, s32, s32 *);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800498C4();
extern void func_800499EC();
extern u8 D_8AF28ED0;
void func_8AF071A8(void) {
    func_800498C4();
    func_800496A4(0x10, 0);
    func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
    func_800495BC(0xFA, 0x32, &D_8AF28ED0);
    func_800499EC();
}
#endif
