#include "global.h"


#ifdef VERSION_US
typedef struct TargetGraphNode TargetGraphNode;
extern void* D_80087200;

s32 func_8F200020(s32 kind, TargetGraphNode* node) {
    switch (kind) {
    case 0:
        break;
    case 1:
        /* Apply all held directions before clamping the signed coordinates. */
        if (*(u16*)((u8*)D_80087200 + 0xC) & 0x800) {
            *(s16*)((u8*)node + 0xA) -= 1;
        }
        if (*(u16*)((u8*)D_80087200 + 0xC) & 0x400) {
            *(s16*)((u8*)node + 0xA) += 1;
        }
        if (*(u16*)((u8*)D_80087200 + 0xC) & 8) {
            *(s16*)((u8*)node + 0xA) -= 10;
        }
        if (*(u16*)((u8*)D_80087200 + 0xC) & 4) {
            *(s16*)((u8*)node + 0xA) += 10;
        }
        if (*(u16*)((u8*)D_80087200 + 0xC) & 2) {
            *(s16*)((u8*)node + 8) -= 10;
        }
        if (*(u16*)((u8*)D_80087200 + 0xC) & 1) {
            *(s16*)((u8*)node + 8) += 10;
        }
        if (*(s16*)((u8*)node + 0xA) < -960) {
            *(s16*)((u8*)node + 0xA) = -960;
        } else if (*(s16*)((u8*)node + 0xA) > 0) {
            *(s16*)((u8*)node + 0xA) = 0;
        }
        if (*(s16*)((u8*)node + 8) < -640) {
            *(s16*)((u8*)node + 8) = -640;
        } else if (*(s16*)((u8*)node + 8) > 640) {
            *(s16*)((u8*)node + 8) = 640;
        }
        break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(s32);
extern s32 func_8004DC6C(s32);
extern void func_8004DCFC(u8*, s32*);
extern s32 func_8004EB58(s32, s32);
extern void func_8004E308(TargetGraphNode*, s32 (*)(s32, TargetGraphNode*), void*);
extern s32 D_8F200904;
extern s32 D_8F200908;
extern s32 D_8F20090C;

void func_8F20015C(void) {
    s32 allocation;
    s32 script;

    if (D_8F200904 != D_8F200908) {
        main_pool_pop_state(0x73636C64);
        main_pool_push_state(0x73636C64);
        script = func_8004DC6C(D_8F200908 = D_8F200904);
        func_8004DCFC((u8*)(u32)script, NULL);
        allocation = MainPool_AllocState(main_pool_get_available(), 0);
        D_8F20090C = func_8004EB58(allocation, script);
        MainPool_FinalizeAllocation(allocation);
        func_8004E308((TargetGraphNode*)(u32)D_8F20090C, func_8F200020, NULL);
    }
}
#endif

#ifdef VERSION_US
extern s16 D_8F200870;
extern s32 D_8F200874;
extern s32 D_8F200910;

void func_8F200214(void) {
    D_8F200904 = 0;
    D_8F200908 = -1;
    D_8F20090C = 0;
    D_8F200910 = 1;
    D_8F200870 = 1;
    D_8F200874 = 1;
}
#endif

void func_8F200250(void) {
}

#ifdef VERSION_US
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void Font_EnableTwoCycleTexturing(void);
extern void Font_DisableTwoCycleTexturing(void);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800497E4(s32, s32, s32, s32);
extern s32 func_8003514C(void);
extern void func_800495F8(s32, s32, s32, const char*);
extern void func_800495BC(s32, s32, const char*, ...);
extern void func_800499EC(void);
extern char D_8F200880[], D_8F200898[], D_8F2008A8[], D_8F2008C0[], D_8F2008D0[], D_8F2008E4[];

void func_8F200258(void) {
    s32 x;
    s32 y;
    s32 font;

    func_800498C4();
    font = 16;
    x = 320;
    y = 40;
    if (D_8F200870 == 0) {
        font = 2;
        x = 160;
        y = 20;
    }
    func_800496A4(font, 0);
    Font_EnableTwoCycleTexturing();
    func_8004972C(255, 255, 255, 255);
    func_800497E4(0, 0, 255, 255);
    if (func_8003514C() == 0) {
        func_800495F8(x, y, 1, D_8F200880);
    } else {
        func_800495F8(x, y, 1, D_8F200898);
    }
    Font_DisableTwoCycleTexturing();
    x = 40;
    y = 400;
    if (D_8F200870 == 0) {
        x = 20;
        y = 200;
    }
    if (func_8003514C() == 0) {
        func_800495BC(x, y, D_8F2008A8, D_8F200904);
    } else {
        func_800495BC(x, y, D_8F2008C0, D_8F200904);
    }
    x = 40;
    y = 430;
    if (D_8F200870 == 0) {
        x = 20;
        y = 215;
    }
    if (func_8003514C() == 0) {
        func_800495BC(x, y, D_8F2008D0, *(s16*)((u8*)(u32)D_8F20090C + 8), *(s16*)((u8*)(u32)D_8F20090C + 0xA));
    } else {
        func_800495BC(x, y, D_8F2008E4, *(s16*)((u8*)(u32)D_8F20090C + 8), *(s16*)((u8*)(u32)D_8F20090C + 0xA));
    }
    func_800499EC();
}
#endif

#ifdef VERSION_US
extern void BgStage_DrawFrame(void);
extern void GfxImage_FillCurrent(void *, u16);
extern void func_800503A4(u8 *);
extern void func_80008648(void);
extern u8 D_800D0510[];
void func_8F200424(void) {
    u8 *value;
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&D_800D0510, 0x5295);
    value = (u8 *)D_8F20090C;
    if (value != NULL) {
        func_800503A4(value);
    }
    func_8F200250();
    if (D_8F200874 != 0) {
        func_8F200258();
    }
    func_80008648();
}
#endif

#ifdef VERSION_US
extern s32 D_8F200900;

s32 func_8F200494(void) {
    u8* table = *(u8**)((u8*)(u32)D_8F200900 + 0x1C);
    s32 result = 0;

    if (*(u16*)((u8*)D_80087200 + 0xC) & 0x200) {
        if (--D_8F200904 < 0) {
            D_8F200904 = *(u32*)(table + 0xC) - 1;
        }
    }
    if (*(u16*)((u8*)D_80087200 + 0xC) & 0x100) {
        if (++D_8F200904 > *(u32*)(table + 0xC) - 1) {
            D_8F200904 = 0;
        }
    }
    if (*(u16*)((u8*)D_80087200 + 8) & 0x20) {
        D_8F200874 ^= 1;
    }
    if (*(u16*)((u8*)D_80087200 + 8) & 0x8000) {
        D_8F200910 = 1;
    } else if (*(u16*)((u8*)D_80087200 + 8) & 0x4000) {
        result = 1;
    } else if (*(u16*)((u8*)D_80087200 + 0xC) & 0x10) {
        result = 2;
    }
    return result;
}
#endif

#ifdef VERSION_US
extern s32 StageContext_GetFadeMode();
extern void StageFade_StartFromTransparent();
extern s32 func_8F200494();
s32 func_8F200588(s32 arg0) {
    s32 result = arg0;
    s32 temp_v0;

    switch (arg0) {
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            result = 1;
        }
        break;
    case 1:
        temp_v0 = func_8F200494();
        if (temp_v0 != 0) {
            if (temp_v0 == 1) {
                result = 2;
                StageFade_StartFromTransparent(5);
            } else if (temp_v0 == 2) {
                result = 3;
            }
        }
        break;
    case 2:
        if (StageContext_GetFadeMode() == 1) {
            result = 4;
        }
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
extern s32 StageContext_Allocate(s32, s32, s32, s32, s32, s32);
extern void func_80008514(s32);
extern void func_80008574(void);
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);

void func_8F20063C(void) {
    s32 state = 0;
    s32 running;
    s32 frames;

    do {
        main_pool_push_state(0x7265736F);
        /* The original configuration reads the signed low byte of this halfword. */
        func_80008514(StageContext_Allocate(*((s8*)&D_8F200870 + 1), 0, 2, 0, 2, 1));
        func_800086A4(2);
        StageFade_StartFromOpaque(5);
        main_pool_push_state(0x73636C64);
        do {
            if (D_8F200910 != 0) {
                D_8F200910 = 0;
                func_8F20015C();
            }
            func_80064D28();
            func_8F200424();
            state = func_8F200588(state);
            /* Preserve this case layout and the two independent loop flags. */
            switch (state) {
            case 4:
                running = 0;
                frames = 0;
                break;
            default:
                frames = 1;
                running = 1;
                break;
            case 3:
                state = 0;
                frames = 0;
                running = 1;
                D_8F200910 = 1;
                D_8F200908 = -1;
                break;
            }
        } while (frames);
        func_80008574();
        main_pool_pop_state(0x7265736F);
        if (D_8F200870 == 1) {
            D_8F200870 = 0;
        } else {
            D_8F200870 = 1;
        }
    } while (running);
}
#endif

#ifdef VERSION_US
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 func_8004C09C(s32);
extern u8* func_80047588(s32, s32);
extern u8* Asset_LoadToSegment(s32, u8*, u8*, s32);
extern u8 D_1000000[], D_446E30[], D_447D00[];
extern void func_80047610(void);
extern void func_8004C398(void);

/* Both unused incoming words retain their original stack homes. */
s32 fragment70_main(s32 arg0, s32 arg1) {
    main_pool_push_state(0x53435256);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    D_8F200900 = func_8004C09C(0x113);
    func_80047588(0x3F, 0);
    Asset_LoadToSegment(((u32)D_1000000 & 0x0F000000) >> 24, D_446E30, D_447D00, 0);
    func_8F200214();
    func_8F20063C();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x53435256);
    return 0;
}
#endif
