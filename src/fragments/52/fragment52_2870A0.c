#include "global.h"


#ifdef VERSION_US
typedef struct { u8 pad[0xCEB8]; s32 a,b,c,d; } BE0State;
extern BE0State *D_86416C00;
void func_86408BE0(void) {
    D_86416C00->a = 0;
    D_86416C00->b = 0;
    D_86416C00->c = 0;
    D_86416C00->d = 0;
}

extern void func_80021ED8(s32);
void func_86408C1C(void) {
    if (D_86416C00->a == D_86416C00->b) {
        return;
    }
    D_86416C00->c++;
    if (D_86416C00->c <= D_86416C00->d) {
        return;
    }
    D_86416C00->a = D_86416C00->b;
    func_80021ED8(D_86416C00->a);
}

extern void func_800225C4(s32);
void func_86408CA0(s32 arg0, s32 arg1) {
    func_800225C4(arg1);
    D_86416C00->b = arg0;
    D_86416C00->c = 0;
    D_86416C00->d = arg1;
}
#endif
