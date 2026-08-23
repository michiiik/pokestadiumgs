#include "global.h"

/* Audio command setup helpers.  These small routines are kept here with the
 * surrounding audio command code; their constants and stores are taken
 * directly from the US implementations at 0x800225C4--0x80022640. */
extern void func_80018728(u32 address, ...);
extern void func_800187AC(void);
extern u8 D_8009019C;
extern u8 D_800901A0;
extern u8 D_800901A4;

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80021DE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Audio_DispatchCommand.s")
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800225C4.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002260C.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002263C.s")

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80022644.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800226C0.s")
#endif

extern void func_80025294(s32 command, ...);
extern void func_8001874C(u32 command, s32 value);
extern s8 D_800901BC[];
extern s8 D_80090B80;
extern u8 D_80090200[];
extern u8 D_80090220;
extern s32 D_80090224;
extern s32 D_80090228;
extern s32 D_8009022C;
extern s32 D_8009061C[];

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80023110.s")

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800231A0.s")
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800238C4.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002390C.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80023954.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002397C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800239B4.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800239C8.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80023A10.s")

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80023A3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024180.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002421C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024480.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024864.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800248A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800248EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024974.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024D10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024D44.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024D6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024E30.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024E8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024F20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800251F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025294.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025848.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800258F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002596C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025ACC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025B54.s")
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025C50.s")

/* Audio task-control wrappers.  The US bodies are single tail-preserving
 * calls at 0x80025C9C and 0x80025D44; keeping the return values exposes the
 * completion predicates used by Audio_StopProcessing/Audio_WaitForPendingTasks. */
extern s32 func_80018C14(void);
extern s32 func_80019378(void);

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025C9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025CBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025D44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025D64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025DB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025E7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025EB0.s")

#define D_800D1990 ((u32 *)0x800D1990)
#define D_800D198C (*(u32 *)0x800D198C)
extern void func_80034DD0(void);
#define D_80090B8C (*(u8 *)0x80090B8C)
extern u32 osSetIntMask(u32 mask);

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025F84.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002602C.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026068.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026098.s")

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800260C0.s")
#endif

#ifdef VERSION_US
extern void func_80018810(void);
extern s32 func_80018ACC(void);
#define D_80090B64 (*(u8 *)0x80090B64)

/* Poll the audio command engine's pending transition. */
s32 func_80026298(void) {
    func_80018810();
    if (D_80090B64 == 0) {
        return 1;
    }
    if (func_80018ACC() == 0) {
        return 0;
    }
    D_80090B64 = 0;
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800262F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800265B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800266F8.s")
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026938.s")

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026990.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026BB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026C80.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026E08.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026ED8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026F44.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002702C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800271DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002730C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002738C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800273B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027490.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800275E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027634.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027774.s")
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800277C4.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800277F0.s")

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002781C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800278C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800279C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027A28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027BD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027E30.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027EE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027F4C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027F7C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028014.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002806C.s")
#endif

void func_8002809C(void) {
    func_80018728(0xF2000000, 0);
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800280C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800280EC.s")
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028118.s")

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028140.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002818C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028300.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028340.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800284C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028540.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Audio_SwapSoundCandidates.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Audio_FilterRecentSoundId.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800289B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Audio_RemoveRecentSoundAt.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028ADC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028CA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028CE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028D9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028E60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028EA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028ECC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A1FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A25C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A7A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A7E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A80C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A830.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A9C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A9CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A9D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002AAD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002AAFC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B1A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B1CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B2FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B43C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B47C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B490.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B5B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002BE44.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002C2A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002C2E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80030420.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80030AD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003121C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800314D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031530.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031564.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800315E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031638.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031844.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031880.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800318C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800318FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800319D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GbAudio_GetRegisterValue.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031A6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031C84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031E6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031F00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GbAudio_SampleSquare2.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80032A28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80032E40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80032F0C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033188.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800331B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800331C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800331D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800333CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033488.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800334C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003364C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033670.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800337D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800337FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033864.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003386C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033890.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033950.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800339DC.s")
#endif

void func_800339E4(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800339EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033A78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033ACC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033B04.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033BF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033C40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033C48.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033C50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033C58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033CA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033E34.s")
#endif

void func_80033ED0(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033ED8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033F14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033F20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033F5C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033F68.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033F74.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034058.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034098.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800340A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800340B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800340C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034118.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800341BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800341C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034238.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003428C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800342F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034348.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034394.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800343FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034464.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800344C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034518.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003455C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003459C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800345E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034614.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034654.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800346A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800346F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034738.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800347A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800347BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800347D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800347DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800347E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034838.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800348C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003492C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034A08.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034A50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034A94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034ABC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034C48.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034C50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034C58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034CF8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034D00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034D98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034DA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034DD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034DF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034E10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034E1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034E5C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034EA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034EB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034EC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034ED0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034EE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034EF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034F30.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034FE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Rom_DmaRead.s")
#endif

extern s32 D_80094850;
extern s32 D_80094870[];
extern s32 D_80122A40;

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035140.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003514C.s")
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035160.s")

/* Audio's scheduler thread owns the two one-entry completion queues and
 * submits the small audio task descriptors produced by the command builder.
 * The scheduler/client objects are intentionally opaque here; their layout is
 * private to the scheduler implementation.  The task copy below follows the
 * 0x68-byte slot layout used by the original thread. */
extern u8 D_80122B20[];
extern u8 D_80122B18[];
extern u8 D_80122A4C[];
extern u8 D_80122A48[];
extern u8 D_80122AB4[];
extern u8 D_80122AB0[];
extern u8 D_800CD020[];
extern s32 D_8009486C;

extern void __osSetFpcCsr(u32 value);
extern void Sched_InitClientQueue(void *client, s32 taskType, s32 priority);
extern void Sched_AddClient(void *client);
extern void Sched_WaitClientQueue(void *client);
extern void Sched_SubmitTask(void *task, s32 flags);
extern void profiler_log_thread4_time(void);
extern void Audio_InitializeTaskState(void);
extern void *Audio_BuildSchedulerTask(void);
extern void func_80025C50(s32 mode);

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/LinkAlias_func_80035174.s")
#if 0
void Audio_ThreadEntry(void *arg) {
    u8 *client = D_80122B20;
    u8 *taskQueue = D_80122A4C;
    u8 *taskMessages = D_80122A48;
    u8 *doneQueue = D_80122AB4;
    u8 *doneMessages = D_80122AB0;
    s32 *running = &D_80122A40;
    s32 *toggle = (s32 *)D_80122B18;
    s32 *taskIndex = (s32 *)D_8009486C;
    u8 *audioState = D_800CD020;

    (void)arg;
    __osSetFpcCsr(0x1000C01);
    Sched_InitClientQueue(client, 1, 1);
    Sched_AddClient(client);

    *running = 1;
    *toggle = 0;
    osCreateMesgQueue((OSMesgQueue *)taskQueue, (OSMesg *)taskMessages, 1);
    osCreateMesgQueue((OSMesgQueue *)doneQueue, (OSMesg *)doneMessages, 1);
    osSendMesg((OSMesgQueue *)taskQueue, (OSMesg)(u32)0x444F4E45, 0);
    osSendMesg((OSMesgQueue *)doneQueue, (OSMesg)(u32)0x444F4E45, 0);
    Audio_InitializeTaskState();
    func_80025C50(2);

    for (;;) {
        Sched_WaitClientQueue(client);
        profiler_log_thread4_time();

        if (*running != 0 && *(s16 *)(audioState + 0xA38) < 0x15) {
            void *builtTask = Audio_BuildSchedulerTask();

            if (builtTask != NULL) {
                u8 *source = (u8 *)builtTask;
                u8 *destination = taskMessages + (*toggle * 0x68);
                s32 i;

                for (i = 0; i < 5; i++) {
                    *(u32 *)(destination + 0x14 + i * 0xC) =
                        *(u32 *)(source + i * 0xC);
                    *(u32 *)(destination + 0x18 + i * 0xC) =
                        *(u32 *)(source + 4 + i * 0xC);
                    *(u32 *)(destination + 0x1C + i * 0xC) =
                        *(u32 *)(source + 8 + i * 0xC);
                }
                *(u32 *)(destination + 0x5C) = *(u32 *)(source + 0x3C);
                Sched_SubmitTask(destination, 0);
            }
        }

        *toggle ^= 1;
        profiler_log_thread4_time();
        *taskIndex += 1;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Thread4_CreateThread.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003539C.s")
#endif

extern s32 func_80025C9C(void);
extern s32 func_80025D44(void);

s32 Audio_StopProcessing(void) {
    func_80025C9C();
    D_80122A40 = 0;
    return 0;
}

s32 Audio_WaitForPendingTasks(void) {
    s32 completed = 0;

    while (func_80025D44() != 0) {
        completed++;
    }
    return completed;
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035424.s")
#endif

extern s32 D_80094860;
extern s32 D_80094868;

void Audio_SetProcessingEnabled(s32 enabled) {
    D_80122A40 = enabled ? 1 : 0;
}

void Audio_ResetModeSelector(void) {
    D_80094860 = -1;
}

void Audio_EnableModeFlag(void) {
    D_80094868 = 1;
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800354B4.s")
#endif

extern s32 D_80094864;

void Audio_ResetRequestId(void) {
    D_80094864 = -1;
}

extern void Audio_DispatchCommand(s32 eventId);

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/LinkAlias_func_800355E4.s")

#define D_437620 ((u8 *)0x00437620)
#define D_437670 ((u8 *)0x00437670)
#define D_80124D00 ((u32 *)0x80124D00)
#define D_80124D50 (*(u32 *)0x80124D50)
extern void *func_800042C0(u32 source, u32 end, u32 decompress,
                           u32 relocate);

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035620.s")
#if 0
void func_80035620(void) {
    u32 *source;
    u32 *destination;
    s32 i;

    main_pool_push_state(0x524F4D54);
    source = (u32 *)func_800042C0((u32)D_437620, (u32)D_437670, 0, 0);

    D_80124D00[0] = source[0];
    D_80124D00[1] = source[1];
    D_80124D00[2] = source[2];
    destination = &D_80124D00[3];
    source += 3;
    for (i = 0; i < 16; i++) {
        destination[i] = source[i];
    }

    main_pool_pop_state(0x524F4D54);
}
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800356CC.s")
#if 0
s32 func_800356CC(s32 index) {
    if (index >= 0 && index < 19) {
        return D_80124D00[index];
    }
    return 0;
}
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035700.s")
#if 0
void func_80035700(u32 seed) {
    D_80124D50 = seed;
}
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003570C.s")
#if 0
u32 func_8003570C(void) {
    D_80124D50 = D_80124D50 * 0x0019660D + 0x3C6EF35F;
    return D_80124D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Color_SetRGB.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Color_SetRGBA.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3f_SetComponents.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3f_SetComponentsDuplicate.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3f_AddInPlace.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3f_Add.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3f_SubtractInPlace.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3f_Subtract.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3f_FromVec3s.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3f_CrossProductFromPoints.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3f_CrossProduct.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035A10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3s_SetComponents.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3s_AddInPlace.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3s_Add.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3s_SubtractInPlace.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3s_Subtract.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Vec3s_FromVec3f.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_Copy.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_Identity.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_SetTranslation.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035D14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_SetRotationTranslation.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_SetRotationTranslationF.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_SetRotationAndTransformTranslation.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_SetRotationScaleTranslation.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_SetRotationAndScaledTranslation.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80036714.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_SetOrthonormalBasis.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_Multiply.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_ScaleRows.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80036D8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_TransformVec3s.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_ToFixed.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/MtxF_BuildTransform.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80037120.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Camera_ComputeEyeFromAngles.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Math_StepToS.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Math_StepToS32.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Math_StepToF.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/PackedBits_ReadSigned.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Color_RGBToHSV.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Color_RGBA8ToHSV.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Color_RGB5551ToHSV.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Color_HSVInterpolate.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Color_HSVToRGB.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Color_HSVToRGB5551.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Color_HSVToRGBA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Color_AdjustRGB5551.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Color_AdjustRGBA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_Init.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80037E3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateContainer.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateWithReference.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateCamera.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateType3.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateType4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateOrtho.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreatePerspective.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateBackground.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003820C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateFog.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800382E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80038390.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800383DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateAmbientLight.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80038474.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800384C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateShadow.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateCullDistance.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateSwitchCase.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateTranslateRotate.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateTranslate.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateAnimatedPart.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateDisplayListPart.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateModelPart.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateDisplayListMatrix.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateDisplayListMatrixFromTransform.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateScale.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateDisplayList.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateShadowTexture.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateAnchor.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoNode_CreateGroup.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoCamera_SetViewport.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoCamera_SetPerspective.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80038E14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoCamera_SetBackground.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80038F8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GraphNode_RemoveChild.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GraphNode_GetChildAtIndex.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80039070.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800390D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80039158.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80039204.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800392B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_GetRelativeMatrix.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_GetMatrix.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_ResetTransformStack.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_PushScale.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoOverlay_BuildFadeQuad.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoOverlay_DrawFadeQuad.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoOverlay_SetRotatedVertex.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoOverlay_BuildRotatingQuad.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoOverlay_DrawRotatingQuad.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoOverlay_Draw.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_ProcessNodeChildren.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003A370.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeReference.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeCamera.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeType3Pass.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003A7F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeModelPartRoot.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeOrtho.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodePerspective.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeBackground.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeClearDepth.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003AC84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeFog.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003ADA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B03C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B044.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B218.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B350.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeCullDistance.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeSwitchCase.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B5AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B600.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B690.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B6D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B9F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeDisplayListPart.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003BCB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003BEF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003BF9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeDisplayList.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeShadowTexture.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_RecordAnchorPosition.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeAnchor.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeGroup.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_NodeShadow.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_RenderRootNode.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Geo_ProcessCallbacks.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003C964.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_AdvanceFrameCounter.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_IsModelFrameCurrent.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_FindAnchorPosition.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003CA30.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003CB3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_SyncMaterialState.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003CC14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003CD58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003CD84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003CFB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_RestoreRenderMode.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_SetPrimitiveColor.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D188.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D1F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D270.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D55C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_SelectMaterialSlot.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D7B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D808.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_SubmitMaterial.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_SubmitDisplayList.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_SetMaterialParams.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_SetMaterialTexture.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003DB38.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/GeoRender_FlushMaterialSlots.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_EvaluateTranslationChannel.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_EvaluateRotationChannel.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_EvaluateScaleChannel.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_InterpolateKeyframe.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_InterpolateKeyframeTangent.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_EvaluateTranslationCurve.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_EvaluateRotationCurve.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_EvaluateScaleCurve.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_AdvanceCurveFrame.s")
#endif

#ifdef VERSION_US
extern s32 D_801263E0;

void ModelAnim_ResetCurveContext(void) {
    D_801263E0 = -1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_BeginCurveContext.s")
#endif

#ifdef VERSION_US
void ModelAnim_EndCurveContext(void) {
    if (D_801263E0 >= 0) {
        D_801263E0--;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_EvaluateJointTransform.s")
#endif

#ifdef VERSION_US
void ModelAnim_ClearTransformChannel(void *anim) {
    *(s16 *)((u8 *)anim + 0x40) = -1;
    *(void **)((u8 *)anim + 0x44) = NULL;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_BindTransformCurve.s")
#endif

#ifdef VERSION_US
s32 ModelAnim_SetSpeed(void *anim, s32 speed) {
    s32 frame = *(s32 *)((u8 *)anim + 0x48);
    *(s32 *)((u8 *)anim + 0x4C) = speed;
    return frame >> 16;
}
#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_SetFrame.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_HasCrossedFrame.s")

#ifdef VERSION_US
s32 ModelAnim_IsAnimationDone(void *anim) {
    void *record = *(void **)((u8 *)anim + 0x44);
    s32 lastFrame = ((s32)(*(u16 *)((u8 *)record + 0xA) - 1)) << 16;
    return ModelAnim_HasCrossedFrame(anim, lastFrame >> 16);
}
#endif

#ifdef VERSION_US
s32 ModelAnim_IsFinished(void *anim) {
    void *record = *(void **)((u8 *)anim + 0x44);
    s32 current = *(s32 *)((u8 *)anim + 0x48);
    s32 lastFrame = ((s32)(*(u16 *)((u8 *)record + 0xA) - 1)) << 16;
    return current >= lastFrame;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003EC54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_ResolveEventIndex.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_AdvanceEventFrame.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_ResetEventContext.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003ED18.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_EndEventContext.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_GetEventAtFrame.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_ClearEventTrack.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_BindEventTrack.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_SetEventFrame.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003EF60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003EF70.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_IsEventFrame.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_IsEventTrackNearEnd.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_IsEventTrackDone.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelRenderer_InitDisplayRoots.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F018.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F03C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelRenderer_AttachSecondaryDisplayObject.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F114.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F1DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F210.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F2C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_SetEventTrack.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F454.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F498.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F4DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F4E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/ModelAnim_GetAnimationRecord.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F54C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F5AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F6E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F818.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F84C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F864.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/PokeIcon_RequestBackgroundForObject.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F904.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F954.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F970.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F9AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_branch_and_link.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_2A.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_end.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_jump.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_branch.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_27.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_return.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_open_node.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_close_node.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/register_graph_node.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_attach_node.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_set_callback.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_container.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_reference.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_camera.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_type3.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_type4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_ortho.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_perspective.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_background.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_clear_depth.s")
#endif

void geo_layout_cmd_noop(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_fog.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_light.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_29.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_skip.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_ambient_light.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_17.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_shadow.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_cull_distance.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_switch_case.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_translate_rotate.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_translate.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_animated_part.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_display_list_part.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_model_part.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_display_list_matrix.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_scale.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_display_list.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_shadow_texture.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_anchor.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_set_node_flag4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/geo_layout_cmd_create_group.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80040E80.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80040F60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041130.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800411F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8004124C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800412B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800413A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800413E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041430.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041548.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/Fragment_ProcessGeoLayoutList.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800416C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041780.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8004186C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041A18.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041A78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041B84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041BF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041C98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041D84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041E2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041F14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041F60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041FA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041FD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800421E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800422B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8004239C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80042484.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800425C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800427B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80042808.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80042858.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800428A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800428F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/PokeIcon_WaitBackgroundLoad.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80042968.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800429A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800429D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80042A64.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/BattleAnim_LoadResourceTable.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80042ADC.s")
#endif
