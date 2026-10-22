#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5480/func_8AF07210.s")

#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

s32 func_80054794();                                /* extern */
extern u8 *D_8AF2C648;
extern s16 D_8AF2C654;

void func_8AF07300(void) {
    if (func_80054794() == 7) {
        switch (D_8AF2C654) {                       /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            M2C_FIELD(D_8AF2C648, s16 *, 0x32) = 0x26;
            return;
        case 1:                                     /* switch 1 */
            M2C_FIELD(D_8AF2C648, s16 *, 0x32) = 0x25;
            return;
        }
    } else {
        switch (D_8AF2C654) {                       /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            M2C_FIELD(D_8AF2C648, s16 *, 0x32) = 2;
            return;
        case 1:                                     /* switch 2 */
            M2C_FIELD(D_8AF2C648, s16 *, 0x32) = 0x30;
            return;
        }
    }
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5480/func_8AF073B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F5480/func_8AF0769C.s")

void func_8AF07954(void) { }
#endif
