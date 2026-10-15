# Session 59 failed-owner evidence

These four independent owners remain GLOBAL_ASM. This is a failed-investigation document only; keep its PR DRAFT and unmerged. No candidate in this document is accepted. The full sources, normal host-check/COMPARE=1 logs, checksum results and object disassemblies remain under work/session-59. All raw/full-TU snapshots from every session are forbidden restoration baselines. Only each failed owner and its introduced declarations were restored. All 217 previously merged owners and the verified local func_80069868 candidate were preserved; local PASS does not repair historical gate gaps.

Current master was 51220cda15dad51ebbb41c3fcf1bf56238863d9c. All open PR scopes were inspected before edits: twelve DRAFT documentation PRs, then this process's separate func_80069868 PR. No foreign owner was edited. CONTRIBUTING.md was read in full from michiiik/pokestadium master, blob d5db9d12aa0d73915b2ef33b940a0ff5266a6f98; unknown names remain address/argument/register based. No semantic names, tokens marked known, helper implementation, data, layout, compiler, CI, or verification changes were authored.

Each valid trial below reached full ROM generation and failed the retail checksum. After each owner-only restoration, a normal host-check US COMPARE=1 rebuild and explicit md5sum -c baseroms/us/checksum.md5 passed with retail MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. Final restoration retains the independent verified func_80069868 source.

Fleet local/live main afee707ab78d3f63f2f9deeadc7551ec0080eeed was checked. None of these four owners had an exact owner attempt or owner-specific fleet regional record, so no historical raw_similarity_score or normalized score exists for them. Full available current-master owner-region notes were read; the existing 8131109C and 8130FF70 evidence remains unchanged and was not retried. Sources and checkpoints 58 through 48 plus 47/46 archives were consulted; their rejects and all 28 historical gaps remain intact.

## func_84200870 — rejected, restored

**md5**: 98fb9d15ac5554db9caf9bec34ea6ce4; 432bc5c2a2f659b2ad031a1029e111a9

**recipe**: Actualpointer/u8first-result/s32second-result; canonical64474s32(u8,u16) and034A0u8(void) declaredconsistentlybeforealluses. Twoentrylocals thenonegenuinelyreusedentrylocal.

**residual**: Twoentries:all34words/everyregister/control/local39exactexceptframe48vs40. Reuse:frame40 but firstentryv1vsretailv0,byte35vs39;otherbodyexact.

**retry**: Need supported entry-pointer/byte-result/frame lifetime. No ordinary twoentry/reused/direct/scalar/array/padding/declaration/operand/prototype retries.

**restore**: Onlyowner/two newdecls restored, preserveall217merged. FullretailPASS.

### candidate-00870.c

```c
extern s32 func_80064474(u8, u16);
extern u8 func_842034A0(void);
void func_84200870(u8 *arg0) {
    u8 *var_v0;
    u8 *var_v1;
    u8 var_v1_2;
    s32 var_v0_2;

    var_v0 = *(u8 **)(arg0 + 24);
    var_v1_2 = func_80064474(var_v0[0], *(u16 *)(var_v0 + 22));
    var_v1 = *(u8 **)(arg0 + 28);
    var_v0_2 = func_80064474(var_v1[0], *(u16 *)(var_v1 + 22));
    if ((var_v1_2 != 0) && (var_v0_2 != 0) && (var_v0_2 != var_v1_2)) {
        *(u8 **)(arg0 + 16) += (*(u8 **)(arg0 + 20))[21] * func_842034A0();
    }
}
```

### candidate-00870-reuse.c

```c
extern s32 func_80064474(u8, u16);
extern u8 func_842034A0(void);
void func_84200870(u8 *arg0) {
    u8 *var_v0;
    u8 var_v1_2;
    s32 var_v0_2;

    var_v0 = *(u8 **)(arg0 + 24);
    var_v1_2 = func_80064474(var_v0[0], *(u16 *)(var_v0 + 22));
    var_v0 = *(u8 **)(arg0 + 28);
    var_v0_2 = func_80064474(var_v0[0], *(u16 *)(var_v0 + 22));
    if ((var_v1_2 != 0) && (var_v0_2 != 0) && (var_v0_2 != var_v1_2)) {
        *(u8 **)(arg0 + 16) += (*(u8 **)(arg0 + 20))[21] * func_842034A0();
    }
}
```

## func_82303D84 — rejected, restored

**md5**: 0be5712dea7e195c018294c7efdbaec4; e2939b6c8f4b90bc24674a0d25dae04f; 0f80ed33e4945eb82bbcf10358dd4690

**abi**: Actualu32incoming remainder45 then signedwordcomparisons/div5/div30; original049A8/04C88 LHUwordresult, compiled052FC same. One stale u16decl consistentlyu32 duringtrial thenrestored.

**recipe**: Entryzeroresult phi, latezeroresult phi, latezero/directformula return based on originalseparateJRtails.

**residual**: All36words/frame0; finaldirectmodel recoversbranches/tails but modv1/productv0/defaultv0 vsretailmodv0/productv1/defaultv1; earlierphi forms sharedtail anddifferentconstant/result registers.

**retry**: NeedSUPPORTED remainder/result-value lifetime; noordinaryphase/phi/direct/return0/operand/declaration/formal-overwrite retries.

**restored**: Onlyowner/oneexistinglocalprototype restored, fullUSretailPASS preserving217merged.

### candidate-3d84.c

```c
s32 func_82303D84(u32 arg0) {
    s32 var_v0 = arg0 % 45;
    s32 var_v1 = 0;

    if (var_v0 < 5) {
        return (var_v0 * 255) / 5;
    }
    if (var_v0 < 10) {
        return 255;
    }
    if (var_v0 < 40) {
        var_v1 = 255 - ((var_v0 * 255 - 2550) / 30);
    }
    return var_v1;
}
```

### candidate-3d84-late.c

```c
s32 func_82303D84(u32 arg0) {
    s32 var_v0 = arg0 % 45;
    s32 var_v1;

    if (var_v0 < 5) {
        return (var_v0 * 255) / 5;
    }
    if (var_v0 < 10) {
        return 255;
    }
    var_v1 = 0;
    if (var_v0 < 40) {
        var_v1 = 255 - ((var_v0 * 255 - 2550) / 30);
    }
    return var_v1;
}
```

### candidate-3d84-direct.c

```c
s32 func_82303D84(u32 arg0) {
    s32 var_v0 = arg0 % 45;
    s32 var_v1;

    if (var_v0 < 5) {
        return (var_v0 * 255) / 5;
    }
    if (var_v0 < 10) {
        return 255;
    }
    var_v1 = 0;
    if (var_v0 < 40) {
        return 255 - ((var_v0 * 255 - 2550) / 30);
    }
    return var_v1;
}
```

## func_88903B2C — rejected, restored

**md5**: c82fdd5499e3fe7abe58b033b4bebd6c; 3004a7b72b2af6b1e163b88acff86c97

**abi**: Noarg void wrapper; actual callback void(void) established through constructor and three original callers. Input_SetRepeatController(s32),88001900(void),Util_Free(s32) canonical. Callback captured before free, called after free.

**residual**: Raw:35vs34words,basev0/ptrv1,extra movea0,callback24vs28. Captured real base/reload after alias-store:frame40vs32; globaladdressv1materialized and additional load vs retaildirectLUI/LW; callback28/bodycorrect.

**retry**: NeedSUPPORTEDbase/globaladdress/callbackspill lifetime; noordinaryraw/captured/typedbase/qualifier/declaration/operand/helperprototype retries.

**restore**: Onlyowner/newdecls/oldexternplacement restored; fullUSretailPASS preserving217merged.

### candidate-3b2c.c

```c
extern void Input_SetRepeatController(s32);
extern void func_88001900(void);
extern void Util_Free(s32);
extern void *D_80087200;
extern s32 D_889041B4;
extern u8 D_889041B8;
void func_88903B2C(void) {
    s32 *var_v0;
    void (*var_t9)(void);

    Input_SetRepeatController((s32)D_80087200);
    func_88001900();
    var_v0 = *(s32 **)(D_889041B0 + 572);
    if (var_v0 != NULL) {
        *var_v0 = 1;
    }
    if (*(void **)(D_889041B0 + 576) == NULL) {
        D_889041B8 = 2;
        D_889041B4 = 0;
    }
    var_t9 = *(void (**)(void))(D_889041B0 + 580);
    Util_Free((s32)D_889041B0);
    var_t9();
}
```

### candidate-3b2c-base.c

```c
extern void Input_SetRepeatController(s32);
extern void func_88001900(void);
extern void Util_Free(s32);
extern void *D_80087200;
extern s32 D_889041B4;
extern u8 D_889041B8;
void func_88903B2C(void) {
    u8 *var_a0;
    s32 *var_v0;
    void (*var_t9)(void);

    Input_SetRepeatController((s32)D_80087200);
    func_88001900();
    var_a0 = D_889041B0;
    var_v0 = *(s32 **)(var_a0 + 572);
    if (var_v0 != NULL) {
        *var_v0 = 1;
        var_a0 = D_889041B0;
    }
    if (*(void **)(var_a0 + 576) == NULL) {
        D_889041B8 = 2;
        D_889041B4 = 0;
    }
    var_t9 = *(void (**)(void))(var_a0 + 580);
    Util_Free((s32)var_a0);
    var_t9();
}
```

## func_8130FC80 — rejected, restored

**md5**: f9c536f9758d83952763488d3694c3a8; 1cb13569b81a40a0fba5c44907af5965

**abi**: Original00E34/010B0 supply pointer/two wordbooleans/twopointers; canonical11CFC(void*) reset and compiledFB58(u8*)/FBC0(void*) void helpers; FA0C actualonepointer. No invented arguments.

**recipe**: Direct stores followed by supported reset-phase-before-input stores.

**residual**: Both36words/frame32. Direct matches prologue/calls but zero/inputstore scheduling and literal1t0vsretailt9/finalargt9vst0. Resetphase recovers allargument/literalregisters andcalls but moveszero3C/A0/float34 beforeincomingarg3 load insteadretailinterleaving.

**retry**: NeedSUPPORTEDzero/input-field lifetime/scheduling model; noordinarydirect/resetphase/storeorder/declaration/operand retries.

**restore**: Onlyowner/twonewdecls restored and freshmasterblobchecked; fullUSretailPASS with1054retained.

### candidate-FC80.c

```c
extern void func_81311CFC(void *);
extern void func_8130FA0C(u8 *);

void func_8130FC80(u8 *arg0, s32 arg1, s32 arg2, void *arg3, void *arg4) {
    func_81311CFC(arg0);
    arg0[56] = 0;
    arg0[57] = 0;
    *(f32 *)(arg0 + 48) = 0.0f;
    *(void **)(arg0 + 76) = arg3;
    *(void **)(arg0 + 80) = arg4;
    *(s32 *)(arg0 + 64) = arg1;
    *(s32 *)(arg0 + 172) = arg2;
    *(s32 *)(arg0 + 60) = 0;
    *(s32 *)(arg0 + 160) = 0;
    *(f32 *)(arg0 + 52) = 0.0f;
    *(s32 *)(arg0 + 168) = 1;
    func_8130FA0C(arg0);
    func_8130FB58(arg0);
    func_8130FBC0(arg0);
}
```

### candidate-FC80-reset.c

```c
extern void func_81311CFC(void *);
extern void func_8130FA0C(u8 *);

void func_8130FC80(u8 *arg0, s32 arg1, s32 arg2, void *arg3, void *arg4) {
    func_81311CFC(arg0);
    arg0[56] = 0;
    arg0[57] = 0;
    *(f32 *)(arg0 + 48) = 0.0f;
    *(f32 *)(arg0 + 52) = 0.0f;
    *(s32 *)(arg0 + 60) = 0;
    *(s32 *)(arg0 + 160) = 0;
    *(void **)(arg0 + 76) = arg3;
    *(void **)(arg0 + 80) = arg4;
    *(s32 *)(arg0 + 64) = arg1;
    *(s32 *)(arg0 + 168) = 1;
    *(s32 *)(arg0 + 172) = arg2;
    func_8130FA0C(arg0);
    func_8130FB58(arg0);
    func_8130FBC0(arg0);
}
```

## Screened without a source trial

- func_88300230: actual u16/void owner and helper886000F0 audited. The current compiled func_80042FBC declaration/definition discards the actual word result and models its second argument as a pointer although mode zero consumes a resource word. Correcting that real forwarding chain requires a separate companion ABI audit; no false prototype or owner trial was made.
- func_8AE01738: full fleet fragment46_code notes explicitly forbid tie-pool retries. The 2400-second terminal record is normalized 0.8929/raw 0.6786; a later 0/raw None no-family entry does not erase it. No trial. All other regional skip lists remain active.
- func_8411DA4C: size-only screening encountered regional 0/raw None with no concrete owner recipe. It was not attempted; this does not clear any sibling family.
- func_8830609C remains deferred for the already recorded sibling unroll/global-address prerequisites. func_84107998 remains lower priority. Shared switch interiors were never treated as independent owners.

## Evidence integrity

The separate accepted 80069868 region note retains its rejected scalar MD5 d7fd560805e14a69bff29655dc206959 and the accepted labeled array model. It is not a fifth unresolved owner. Successful local checks are not public-gate or historical retrospective proof.

The following SHA-256 manifest identifies the retained build, checksum and disassembly evidence without reproducing generated objects or ROM content:

```text
31f5279dcd40ef6ce7a21fca4e2dd45b4da087828ce39f13e93b17e4edb5ed9d  work/session-59/00870-build.log
268e728ec80d9d6285cc0c54de6ed59b7bd1e4e50e11abe3191e3c08366fc136  work/session-59/00870-checksum.txt
32087a57ae976debcb707d180bfb11ecc9c02d261773cbbc135054ceaa56dbcd  work/session-59/00870-md5.txt
c62c254c808f6b5db5f92421391a1e10fa92663fa7147fc25da120685beec410  work/session-59/00870-object.txt
32c49bdfedce8e73a38cb4d428b576e8de62b592e94e4ad7e0254ddfff695208  work/session-59/00870-reuse-build.log
268e728ec80d9d6285cc0c54de6ed59b7bd1e4e50e11abe3191e3c08366fc136  work/session-59/00870-reuse-checksum.txt
4403e21952476ff769634923c590c34f8526e52f59c8e37c07b26bcc88dca6f3  work/session-59/00870-reuse-md5.txt
6390a34f83d568077f2aa3e14c526b6f0fd1bb4ab834b3db58a5e8130f2397e8  work/session-59/00870-reuse-object.txt
8614fab849c27a8c1b607719b632fcff58fdec4164fc5cfe8b4742bf5cc3cd2a  work/session-59/3b2c-base-build.log
268e728ec80d9d6285cc0c54de6ed59b7bd1e4e50e11abe3191e3c08366fc136  work/session-59/3b2c-base-checksum.txt
0f005e33dee1e3f6a0abeeb7c0da65451995bd912a129d38b1185013fe3ee792  work/session-59/3b2c-base-md5.txt
250b25c625a8164f4bd922c848d0071aa54b5624deeca6af79c0442cf7e6dab9  work/session-59/3b2c-base-object.txt
bc4809443d9388e2d8cb4adbb4a4186851a7b3cab6d304e9e6f546d5fa22ef1d  work/session-59/3b2c-build.log
268e728ec80d9d6285cc0c54de6ed59b7bd1e4e50e11abe3191e3c08366fc136  work/session-59/3b2c-checksum.txt
b8a71fe85df1e0d8fef623a4eb05ad9f027e9101ce47699d159cbac96df778da  work/session-59/3b2c-md5.txt
4ff9434b3edc718a8c0d98e60b828f319ef3d577e21f727d521bc082da104b77  work/session-59/3b2c-object.txt
474d3ff88fcac0539c92e2a5adc0529598d1cad4a90cf548b341b936ca2fa5c9  work/session-59/3d84-build.log
268e728ec80d9d6285cc0c54de6ed59b7bd1e4e50e11abe3191e3c08366fc136  work/session-59/3d84-checksum.txt
b4b7bca055ab71e413e9024eb3d4270c1350a88e4a3d0100599a061ce1331016  work/session-59/3d84-direct-build.log
268e728ec80d9d6285cc0c54de6ed59b7bd1e4e50e11abe3191e3c08366fc136  work/session-59/3d84-direct-checksum.txt
86e6e84be3b340f1ac50969a2b290beffa032abf64201029873147bdca3179f9  work/session-59/3d84-direct-md5.txt
748df9bd62d7b17958d964cadcfc7c01d3ab2842df006a4326f5078b42082e20  work/session-59/3d84-direct-object.txt
cb299de5bb083aeb42657c4ac7ef114e4cc772bfd81788bb772ff3c6121b9ca4  work/session-59/3d84-late-build.log
268e728ec80d9d6285cc0c54de6ed59b7bd1e4e50e11abe3191e3c08366fc136  work/session-59/3d84-late-checksum.txt
49f5dc55db2b9599f8c5653332fe067a4063578f78c4368da1c20cd2dcba0645  work/session-59/3d84-late-md5.txt
0cd7e452f777db62be1f728469fa5573f6ed42681ad77b8b0140f6a546364336  work/session-59/3d84-late-object.txt
a9b18bf062662f2acfc636cdf5adbf294369924c346a89ec06f42e4428eb7624  work/session-59/3d84-md5.txt
f8853043ab4543ed0d9e2ff38e22927af6f046742a7a2126d1190a1d74bbe639  work/session-59/3d84-object.txt
39c64bd4620f748af86f991c1fe1acfd4d5a88bd43ef521760d311e457d09a7f  work/session-59/FC80-build.log
268e728ec80d9d6285cc0c54de6ed59b7bd1e4e50e11abe3191e3c08366fc136  work/session-59/FC80-checksum.txt
c6f183418342a6c69020b89460ad062c390b593db6b7ef191d82ce4ad901914f  work/session-59/FC80-md5.txt
42e0a085a914bab28f21fb1a1e384656c51cbeab1d7274e94b50112a488c15cf  work/session-59/FC80-object.txt
09bbc12bd8cfb2958f48c27c02f7060123e54b8ee9919fabc7b335251c4f0c56  work/session-59/FC80-reset-build.log
268e728ec80d9d6285cc0c54de6ed59b7bd1e4e50e11abe3191e3c08366fc136  work/session-59/FC80-reset-checksum.txt
4d7cc8bf62318501336d96e0b798e982835de686b9a764c7e9c9f9f485dea070  work/session-59/FC80-reset-md5.txt
8255239f0530b92f631ad9fd60ce508dcb2ffb75b95226f09bc6481da6f99d7f  work/session-59/FC80-reset-object.txt
27d2d9211271208627c3de871ae65c3e962a7572515eb92bacc9e9a440a8e652  work/session-59/restored-00870-build.log
3d9789b5aa96b70a1db1398dbd374b2af1422c5153ccbdd808fbf6d691044e94  work/session-59/restored-00870-checksum.txt
bb48f6771878a74a3e96ec2bce186a24fdaca0dda44d1d2a7cf5ef963a1a095b  work/session-59/restored-3b2c-build.log
3d9789b5aa96b70a1db1398dbd374b2af1422c5153ccbdd808fbf6d691044e94  work/session-59/restored-3b2c-checksum.txt
3326612e0fe6ec9962cabf8e73e95d00dee47ea15c954fe0dd945066a2c21011  work/session-59/restored-3d84-build.log
3d9789b5aa96b70a1db1398dbd374b2af1422c5153ccbdd808fbf6d691044e94  work/session-59/restored-3d84-checksum.txt
4d85e1562c5a179484a2b2f8529dc9bd6a22c0b02aa9859b5743883640eca6b6  work/session-59/restored-FC80-build.log
3d9789b5aa96b70a1db1398dbd374b2af1422c5153ccbdd808fbf6d691044e94  work/session-59/restored-FC80-checksum.txt
```
