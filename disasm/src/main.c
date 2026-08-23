#include "global.h"

// entry .bss
u8 entry_bss[0x400]; // unknown, start of .bss
OSThread gIdleThread;
u8 main_unk_bss1[0x400];
OSThread pThreads;
u8 main_unk_bss2[0x2000];
LEODiskID leoDiskID;

void Vi_SelectMode(s8, s8);
void Thread5_CreateThread();
void Thread3_CreateThread();
void SoftReset_CreateThread();
void rsp_init();
void crash_screen_init();
void Thread4_CreateThread();
void Util_InitMainPools();
void Game_Thread(void*);

void Idle_ThreadEntry(UNUSED void* unused) {
    osCreateViManager(0xFE);
    Vi_SelectMode(0, 1);
    osViBlack(1U);
    osViSetYScale(1.0f);
    crash_screen_init();
    rsp_init();
    Thread3_CreateThread();
    Thread4_CreateThread();
    Thread5_CreateThread();
    SoftReset_CreateThread();
    osCreateThread(&pThreads, 6, Game_Thread, NULL, &leoDiskID, 0x14);
    osStartThread(&pThreads);
    osSetThreadPri(NULL, 0);

    while (TRUE) {
        ;
    }
}

void Main(void) {
    __osInitialize_common();
    osCartRomInit();
    set_watch_lohi(0);
    Util_InitMainPools();
    osCreateThread(&gIdleThread, 1, &Idle_ThreadEntry, NULL, &pThreads, 0x64);
    osStartThread(&gIdleThread);
}
