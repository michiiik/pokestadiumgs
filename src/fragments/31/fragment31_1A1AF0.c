#include "global.h"


#ifdef VERSION_US
extern s32 D_880068B8;
void func_8822E870(void) {
    D_880068B8 = 0;
}

void func_8822E87C(void) {
    D_880068B8 = 1;
}

extern void func_88208FF0();
extern s32 D_880068B4;
extern s32 D_88234960;
extern s32 D_88804058;
void func_8822E88C(void) {
    D_880068B4 = 1;
    if ((D_88234960 == 4) && (D_88804058 != 0)) {
        func_88208FF0();
    }
}

s32 func_88802DCC(s32, s32, void (*)(), void (*)(), void (*)(), s32 *, s32, s32);
extern u8 func_882313A4;
void func_8822E8D8(s32 arg0, s32 arg1) {
    func_88802DCC(arg1, arg0, func_8822E870, func_8822E88C, func_8822E87C, &func_882313A4, 0, 0);
    D_88234960 = arg1;
    D_880068B4 = 0;
}
#endif
