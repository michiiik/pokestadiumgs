#include "global.h"


#ifdef VERSION_US
extern u32 D_800CE040;
void SoftReset_ClearLines320(u16* buf) {
    int i, j;

    if (D_800CE040 <= 15) {
        // where is the framebuffer starting, based on the line number of the effect?
        u16* ptr = buf + D_800CE040 * 320;

        // iterate over and clear the 15 lines of the next frame during the effect.
        for (j = 0; j < 15; j++) {
            for (i = 0; i < 320; i++) {
                *ptr++ = 1;
            }
            ptr += (320 * 15); // move the framebuffer pointer to the next line to clear
                               // (down 15 lines).
        }
        osWritebackDCacheAll();
    }
}

void SoftReset_ClearLines640(u16* buf) {
    int i, j;

    if (D_800CE040 <= 15) {
        // where is the framebuffer starting, based on the line number of the effect?
        u16* ptr = buf + D_800CE040 * (640 * 2);

        // iterate over and clear the 15 lines of the next frame during the effect.
        for (j = 0; j < 15; j++) {
            for (i = 0; i < (640 * 2); i++) {
                *ptr++ = 1;
            }
            ptr += ((640 * 2) * 15); // move the framebuffer pointer to the next line to clear
                                     // (down 15 lines).
        }
        osWritebackDCacheAll();
    }
}

extern s32 D_800CE048;
extern s32 D_800CE04C;
extern s32 D_800CE050;
void func_800057DC(void) {
    if (D_800CE040 <= 15) {
        if (D_800CE040 == 0) {
            u16 color = Display_GetFramebufferClearColor();

            D_800CE048 = (color >> 11) & 31;
            D_800CE04C = (color >> 6) & 31;
            D_800CE050 = (color >> 1) & 31;
        }


        Display_ClearFramebufferLine(((((D_800CE048 * (15 - D_800CE040)) >> 4) << 11) |
                       (((D_800CE04C * (15 - D_800CE040)) >> 4) << 6) |
                       (((D_800CE050 * (15 - D_800CE040)) >> 4) << 1) | 1) &
                          0xFFFF,
                      D_800CE040);
    }
}

typedef struct {
    u8 pad0[4];
    u16 width;
    u16 *buf;
} struct_80001FE4;

extern u8 D_800CD020[];
extern u8 D_800CDA60[];
extern void __osSetFpcCsr(s32);
extern void func_80005568(void *);
extern void func_80004F34(void *);
extern struct_80001FE4 *func_80001FE4(void);
extern s32 Display_IsCurrentFramebuffer(void);

void func_800058B4(UNUSED void *arg0) {
    f32 scale;
    struct_80001FE4 *temp_v0;

    __osSetFpcCsr(0x1000C01);
    func_80005568(D_800CDA60);
    scale = 1.0f;
    while (1) {
        func_80004F34(D_800CDA60);
        if (*(s16 *)((u8 *)D_800CD020 + 0xA38) != 0) {
            if ((u32)*(s32 *)(D_800CDA60 + 0x5E0) < 16) {
                temp_v0 = func_80001FE4();
                if (temp_v0 != NULL) {
                    if (temp_v0->width == 320) {
                        SoftReset_ClearLines320(temp_v0->buf);
                    } else {
                        SoftReset_ClearLines640(temp_v0->buf);
                    }
                } else if (Display_IsCurrentFramebuffer()) {
                    func_800057DC();
                } else {
                    SoftReset_ClearLines320(osViGetCurrentFramebuffer());
                }
                (*(s32 *)(D_800CDA60 + 0x5E0))++;
            } else if (*(s32 *)(D_800CDA60 + 0x5E0) == 16) {
                osViBlack(1);
                osViSetYScale(scale);
                (*(s32 *)(D_800CDA60 + 0x5E0))++;
            }
        }
    }
}

extern void Sched_InitClientQueue(void *, s32, s32);
void SoftReset_CreateThread(void) {
    Sched_InitClientQueue(D_800CDA60, 2, 1);
    *(s32 *)(D_800CDA60 + 0x5E0) = 0;
    osCreateThread((OSThread *)D_800CDA60, 0x15, func_800058B4, NULL, &D_800CE040, 0x1E);
    osStartThread((OSThread *)D_800CDA60);
}
#endif
