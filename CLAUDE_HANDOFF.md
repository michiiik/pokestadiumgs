# Pokemon Stadium 2 Android runtime handoff

Last updated: 2026-08-06

## Goal and current verdict

Make the US Pokemon Stadium 2 static recompilation boot and render correctly on
the AYN Thor Android device. The current APK is a real ARM64 recompilation, not
the earlier JNI probe, but it is **not playable yet**.

## THE GAME BOOTS (2026-08-07)

Pokemon Stadium 2 now launches on the AYN Thor: it reaches the menu, renders
real content at **31.8 FPS** (was 2.9), survives indefinitely with **zero
SIGSEGV**, and responds to input. Evidence:
`artifacts/ps2-running-31fps.png`.

The last blocker was that `static_5_80021834` was emitted with **no
interior-entry switch**. The recompiler only emits one when
`register_interior_dispatch_aliases` has populated `dispatch_entry_vrams`, but
that pass runs *before* the per-section statics loop synthesizes the `static_*`
functions — and section 5's hand-written resident code is entirely
late-synthesized statics, so none of them got one. The dispatch alias set
`dispatch_entry_target` and called the function, which ignored it, ran from its
prologue, and reached the same `jalr $t3` unconditionally: infinite recursion
(measured depth 100000) at two host frames per level until the stack died.

`tools/add_entry_switch.py` adds the switch for all four PC-relative helpers
(`$ra+0x190/0x184/0x170/0x164` = 0x80021A2C/A44/A54/A6C);
`tools/add_sibling_aliases.py` adds the three missing aliases.

**The durable fix still to do (emitter, not generated code):** factor the
per-function body of `register_interior_dispatch_aliases` (`main.cpp:1335`,
whose own comment names `func_80021834` as the motivating case) into a helper
taking `(context, func_index)`, and call it in the statics loop right after the
synthetic static `Function` is emplaced (~`main.cpp:2425`) and **before**
`recompile_or_stub`. Alias emission happens after the loop (`main.cpp:2481`),
so mid-loop appends are safe. Until that lands, a regenerate loses the hand
patches — re-run the `tools/` scripts. N64Recomp can be rebuilt now (see
below), so this is unblocked.

### Tried and reverted: enlarging the guest thread stack

bionic defaults `std::thread` to a 1 MB stack against desktop's 8 MB, so
"recompiled frames are bigger than guest frames" looked like a plausible cause
of the boot-time stack overflow. It is not: with the depth counter installed,
the recursion reached **100000** — unbounded, not deep-but-finite. Creating
guest threads via pthread with a 64 MB stack was implemented, measured, and
**reverted**. Don't redo it; fix the control flow instead.

## Open: crash on entering a battle or the stadium

Boot itself is stable — this only reproduces on navigating into a battle or the
stadium.

Reproducible in ~1-2 menu selections (`input tap 978 896` then `1689 680`
after boot). Pre-existing — confirmed identical with and without the guest
stack experiment:

```text
signal 11 (SIGSEGV), fault addr 0xb400006fffff1f18   <- heap-tagged pointer
  #01 ultramodern::resume_thread_and_wait(unsigned char*, OSThread_t*)+108
  #02 ultramodern::yield_to_any_queued(unsigned char*)+208
  #03 func_826040D8+1668      <- guest fragment at 0x82600000
  #04 func_82600020+3744
  #05 func_826003BC+3056
```

`resume_thread_and_wait` does
`TO_PTR(OSThread, thread_self)->context` and `resume_thread(t)` dereferences
`t->context`. **`context` is a host pointer stored inside guest RDRAM**, so any
guest write over an `OSThread` turns it into a wild pointer. `thread_queue_pop`
already validates the *thread* pointer (KSEG0 range, 4-aligned) but nothing
validated `context`.

`patches/ultramodern-live-context-guard.patch` (applied,
`tools/guard_thread_context.py`) keeps a registry of live
`UltraThreadContext*` and refuses to resume a thread whose context is not in
it, reporting once instead of faulting; `resume_thread_and_wait` then returns
rather than blocking forever on a wake that will never come.

**That guard turned the crash into a diagnosis.** `files/stderr.log` now reads:

```text
[thread] REFUSING to resume thread id=1: context 0xb400006fffffcb10 is not live
         (OSThread at guest memory was likely overwritten)
[do_send] BAD mq_=0x800CDA10 reason=mq.first/validCount-insane
          a=0xFFFF0002 b=0x00000010 c=0x00000010 msg=0x00000066 — skipping send
```

**`0x800CDA10` is the same scheduler reply queue the wrong audio microcode used
to destroy at boot.** So the OS thread/queue block at `0x800Cxxxx` is being
overwritten again — this time by battle/stadium content rather than audio. With
the guard the run survives longer (3 menu selections instead of 1) but then dies
in `osSendMesg` from `func_800187AC` ← `func_80021BBC` ← `func_8003539C` ←
`func_80008514` ← `func_826003BC` (fragment at 0x82600000).

### FIXED: an unrelocated loop bound swept all of RDRAM

**Root cause:** `D_8261A488` is an `SHN_ABS` symbol. splat's yaml declares
fragment20's `bss_size: 0x0`, but the fragment's ROM header says
`sizeInRam - fileSize = 0x5BC0`, so symbols in that undeclared bss fall outside
every section, arrive as `SHN_ABS`, and the recompiler drops their relocation
and bakes the link-time literal. In fragment 0x82600000's init:

```c
ctx->r16 = S32(U32(RELOC_HI16(65, 0X163E8)) << 16);   // start: relocated
ctx->r17 = S32(U32(0X8262) << 16);                    // end:   raw literal
...
if (ctx->r16 != ctx->r17) goto L_82604138;            // bne — never equal
```

The start walked from the fragment's runtime base (0x8015E028) while the end
stayed at 0x8261A488. Their difference is not a multiple of the 0x814 stride, so
the loop never terminated: it ran off the end of RDRAM, `MEM_H`'s
`RECOMP_MEM_MASK` wrapped it to the bottom, and it swept the whole 8 MB
repeatedly (~90 passes, each phase-shifted by `0x40000000 mod 0x814`). That is
exactly the 90-phase tiling measured in the snapshot, and why the OS block,
thread `context` pointers and 17% of the resident code image were all damaged at
once.

**Fix (applied):** `patches/n64recomp-abs-bss-fragment-reloc.patch` /
`tools/fix_abs_bss_reloc.py` — in `n64recomp-2b/src/elf.cpp`, a reloc targeting
an `SHN_ABS` symbol whose value falls inside a *relocatable* section's 1 MB
fragment slot is attributed to that section instead of being discarded. Genuine
absolutes (RSP/DP hardware registers) never share a slot with a fragment link
address, and non-relocatable sections are untouched. This was systemic —
**21313** HI16/LO16 relocs across ~60 fragments referenced `SHN_ABS` symbols in
fragment vram space — so the same latent trap is closed everywhere.

Chosen over correcting ~60 fragments' `bss_size` in the splat yaml and
rebuilding the disassembly: same effect, one contained change, no dependency on
the disasm pipeline.

**Verified:** regenerated code emits `RELOC_HI16(65, 0X1A488)`; on device the
untouched region 0x80300000-0x80660000 is all zeros (was tiled with the 0x814
pattern), zero SIGSEGV, and zero `BAD mq_` / `REFUSING to resume` markers. The
game now reaches the Pokemon VS screen.

Note the tripwire page used to find this (`tools/rdram_watchpage.py`) has been
**disarmed**: 0x80400000 lies inside the main pool (0x80134470-0x80800000), so
leaving it protected would eventually fault on a legitimate allocation. Re-arm
only for diagnosis, and prefer an address the pool has not reached.

### Fixed: fragment entry points were never declared

Every fragment starts with an 8-byte header trampoline (`j` + delay slot) that
N64Recomp does not disassemble, so there was no function at offset 0 and calls
into a freshly loaded fragment missed `func_map`. The miss handler logs and
**returns without executing**, so those fragments' init silently never ran.

All 88 `fragmentN_entry` manual funcs are now declared in `game.toml`, generated
from the ELF's `fragmentN_VRAM` symbols after verifying every fragment has
opcode 2 (`j`) at offset 0. Stadium 1 declares 77 of these; Stadium 2 declared
none. Function count rose by 88, 79 entry functions emitted.

**Verified on device:** the four entry-point misses that used to appear by the
main menu (`0x801451A0`, `0x80147C40`, `0x801514D0`, `0x80157AC0`) are gone —
the only remaining miss is the fatal `0x00000000` below.

Also hardened: `tools/reapply_generated_patches.py` and
`tools/add_entry_switch.py` now locate their target file by content instead of a
hardcoded `funcs_234.c`. Regeneration reshuffles functions between `funcs_N.c`
files and silently broke the entry-switch patch this round.

### Open: NULL function pointer before Pokemon order selection

The battle now advances to the VS screen and aborts before order selection.
This is a clean failure, not corruption — no corruption markers at all:

```text
[recomp] 0x00000000 is not in a resident static section — B3 not eligible
[interp] UNIMPLEMENTED opcode 0x00 (funct 0x01) at PC 0x00000300
[recomp] interpreter could not run 0x00000000 — aborting
[recomp] lookup-miss trampoline reached — aborting
  bad function pointer: 0x00000000
```

SIGABRT, with the guest call chain:

```text
func_8140487C+356
func_81405514+4220
func_81406F44+1864
func_814002E8+1764
func_81400468+2900
func_80064CE8+572     <- the fragment loader
func_80069370+6560
Game_Thread+1888
```

The call site loads the pointer out of another fragment's data and calls it:

```c
// 0x8140488C: lui $t9, 0x8161
ctx->r25 = S32(U32(RELOC_HI16(38, 0XBD08)) << 16);
// 0x81404890: lw  $t9, -0x42F8($t9)
ctx->r25 = MEM_W(ctx->r25, (int16_t)RELOC_LO16(38, 0XBD08));
LOOKUP_FUNC(ctx->r25)(rdram, ctx);          // r25 == 0
```

Section 38 is the fragment linked at 0x81600000 (rom 0x000D7BA0, size 0xD770).

**Established so far:**

- The ROM genuinely holds a function-pointer table at that offset (rom
  0xE38A8): `81600020 816000D4 8160006C 8160024C 8160029C 816002E8`. So the
  value is static data inside the section, not something computed.
- **Nothing writes the slot.** A search across all generated code finds ~10
  readers of `RELOC_LO16(38, 0XBD08)` and **zero stores**. So the value can only
  come from the loaded fragment image.
- `do_rom_read`'s out-of-bounds zero-fill is **ruled out** — it logs
  `[do_rom_read] OUT-OF-BOUNDS` and that string appears in none of the four
  captured runs.
- Therefore `section_addresses[38]` does not point at the fragment's real data
  when the read happens.

**What is NOT yet established** (do not repeat this mistake): the periodic
2 s RDRAM dump is useless here. The snapshot pulled after the last crash
predated the fragment loads entirely — none of the bound bases
(0x8014B7B0, 0x80157AC0, 0x801451C0) contained a `FRAGMENT` magic, and neither
the raw nor the relocated form of fragment 38's pointer table appears anywhere
in the 8 MB. That is an artifact of snapshot timing, not evidence about the bug.

**Instrumentation ready and built (not yet run — device was disconnected):** the
lookup-miss abort path now writes `rdram_abort.bin`, `trace_abort.log`, and a
`=== section bases at abort ===` table listing every loaded relocatable
section's link address and bound runtime base. That table answers the open
question directly: compare `section_addresses[38]` against where fragment 38's
header actually is in `rdram_abort.bin`.

Note `id=0x6` is superseded and re-registered at a new base
(0x801451C0 -> 0x8014B7B0) immediately before the abort, and its range overlaps
`id=0x4` (0x80157AC0..0x80160830) by 0x1460 bytes — but the slot at
0x801574B8 sits 0x608 *below* id=0x4's base, so the overlap does not explain it.

### Superseded analysis: a NULL guest pointer sweeps all of RDRAM

A write-protected tripwire page (mprotect PROT_READ on `rdram + 0x400000`,
memory nothing legitimately writes — `tools/rdram_watchpage.py`) faulted with
SEGV_ACCERR and named the writer:

```text
func_82603A90+36     <- faulting store
func_826040D8+1244
func_82600020+3744
func_826003BC+3056
func_80064CE8+572    <- the fragment loader
func_80069370+4308
Game_Thread+1888
```

So the loader invokes fragment 0x82600000's init, and that init walks all of
RDRAM writing `0xFFFF` halfwords: a repeating 0x814-byte record with 90 fixed
halfword offsets, tiling the whole 8 MB. Confirmed by three independent
measurements:

- Every damaged word in the OS block sits on that same 0x814 phase set
  (0x800CDA1C→0x250, 0x800CDA00→0x234, 0x800A828C→0x088, 0x800A82A0→0x09C).
- The pattern covers regions the game never touches and is absent from
  boot-time snapshots.
- **29470 of 171680 words of the resident code section** (0x80000400, 17%) now
  differ from the ROM *only* by having their high half set to 0xFFFF — first
  hit at 0x80000410, 0x10 past the section start.

**Why the damage reaches the bottom of RDRAM:** the write base is NULL, and the
recompiler maps a NULL guest pointer onto the start of RDRAM rather than
trapping. `MEM_W` computes
`rdram + (((reg + offset) - 0xFFFFFFFF80000000) & RECOMP_MEM_MASK)`, so for
`reg == 0` that is `(0x80000000) & 0x3FFFFFFF == 0` — i.e. guest 0x80000000.
On hardware a NULL store would fault in unmapped KUSEG; here it silently
scribbles from the bottom of RAM upward. This turns any guest NULL-pointer loop
into whole-address-space corruption, which is why the symptoms looked like four
unrelated bugs (queue fields, thread `context`, code image, untouched memory).

So this was never a scheduler, relocation, or dispatch bug. It is one NULL base
pointer inside a fragment's init path. The remaining question is why that
pointer is NULL — the leading candidate is a reference to another fragment's
data by fragment-space vaddr where that fragment is not resident, resolving
against a section base of 0.

Worth doing regardless of the specific cause: make a guest store whose base
lands in the first page of RDRAM loud instead of silent, so this class of bug
reports itself immediately.

### Fixed but not the battle crash: overlapping fragment ranges

Captured live at the moment of the battle crash (`files/stderr.log`), fragments
register at heavily **overlapping** runtime ranges:

```text
id=0x10 link=0x82000000 runtime=0x801451A0 size=0x2550   -> ..0x801476F0
id=0x6  link=0x81600000 runtime=0x801451C0 size=0xD770   -> ..0x80152930
id=0x12 link=0x82200000 runtime=0x801514D0 size=0x108A0  -> ..0x80161D70
id=0x16 link=0x82600000 runtime=0x80147C40 size=0x17EB0  -> ..0x8015FAF0
[thread] REFUSING to resume thread id=1: context ... is not live
[do_send] BAD mq_=0x800CDA10 reason=mq.first/validCount-insane a=0xFFFF0008
```

Corruption starts immediately after id=0x16 registers, and the crashing guest
function `func_826003BC` belongs to exactly that fragment (link 0x82600000).

`register_runtime_fragment` evicts only sections loaded at the **exact same
base** (`evict_prior_at_base`) or the **same id** at a different base (the
supersede path). A *different* id claiming an *overlapping* range evicts
nothing, so the stale fragment's `func_map` entries survive over memory the new
fragment now owns. A call into the overlap dispatches the wrong fragment's
code, which resolves its `RELOC_HI16` literals against its own (now wrong)
section base and writes values whose low half is correct and whose high half is
garbage — exactly the observed damage:

```text
mq->msg    0x800CD9D0 -> 0xFFFFD9D0
mq->first  0x00000008 -> 0xFFFF0008
```

Note this is *partial, word-granular* damage, unlike the boot bug's bulk
ROM-code overwrite — which is why the bulk tripwire never fired.

`patches/librecomp-fragment-binding-fixes.patch` now erases any `func_map`
entry inside `[fragment_ptr, fragment_ptr + size)` before installing a newly
registered fragment (`tools/fix_overlap_evict.py`). Entries in that range are
stale by definition once the range changes owner.

### Also found, not yet fixed: gbTower microcodes are Stadium 1's

Independently verified: **njpgdspMain is correct** — Stadium 2 carries it at ROM
`0x85E70`, byte-identical to Stadium 1's at `0x68C80` for the full `0xAF0`
text, so the unvalidated `M_NJPEGTASK` route is safe for this ROM. The missing
`M_GFXTASK` case is also moot (gfx tasks are intercepted before
`get_rsp_microcode`).

But **gbTowerMain / gbTowerColorMain are wrong**, the aspMain mistake again.
Stadium 1's bodies (S1 ROM `0xA9BE0..0xAA620` and `0xA9140..0xA9B24`) do not
appear in the Stadium 2 ROM; Stadium 2 ships **three** of its own variants at S2
ROM `0x15B3A10`, `0x15B44E0`, `0x15B50D0`. Worse, all three begin
`401A6000 C800207C` — precisely the two words `task_boot_matches` compares — so
the only remaining discriminator is `ucode_boot_size` (0xA40 / 0x9E4). S1 and S2
share a 0x3B-byte boot stub and diverge only after it, so the current check can
false-positive and run Stadium 1's body. Fix: compare a word past +0x3B (or hash
the whole boot blob) and route a non-matching GB task to a loud no-op; then
recompile Stadium 2's own variants. Also note the ps2 tree's `rsp/*.toml` still
carry Stadium 1 ROM offsets while `../baserom.z64` there is the **Stadium 2**
ROM — regenerating from them as-is would compile garbage.

This is the original corruption pattern at a later stage, and the same technique
should solve it: the tripwire on `0x800CDA10` from
`patches/librecomp-mesgqueue-diagnostics.patch` is still in the build — combine
it with an RDRAM snapshot taken when it fires and match the bytes against the
ROM (exactly as in the audio-microcode investigation) to identify the writer.
Three fragment lookup misses also remain and may be related: `0x801451A0`,
`0x801514D0`, `0x801575D0`.

## Current APK status

The current APK:

- builds, installs, and launches;
- uses the system Qualcomm Vulkan driver;
- boots to the menu and renders at **31.8 FPS**, stable and input-responsive;
- has **zero** SIGSEGV and zero lookup misses on the boot path; and
- crashes on entering a battle or the stadium (see above).

Judge a build by guest progress in `freeze_trace.log`, never by process
lifetime: one intermediate build survived 50 s while the guest had actually
stopped at 1.1 s.

**N64Recomp can now be rebuilt.** Its `lib/` submodules (ELFIO, fmt,
rabbitizer, sljit, tomlplusplus) were empty; they were populated by copying
Stadium 1's checked-out copies from
`psr-recomp-build/work/lib/N64ModernRuntime/N64Recomp/lib/`. Configure and
build with:

```bash
docker run --rm --platform linux/amd64 -v /Users/michaegg/ps2-recomp-build:/ps2 \
  -w /ps2 psr-recomp-cross:latest bash -c \
  "cmake -S /ps2/n64recomp-2b -B /ps2/n64recomp-2b-build2 -G Ninja -DCMAKE_BUILD_TYPE=Release && \
   cmake --build /ps2/n64recomp-2b-build2 --target N64Recomp --parallel 6"
```

The rebuilt binary matched the pinned one byte-for-byte in size, so the source
tracks the prebuilt generator. Generation then uses `-v .../n64recomp-2b-build2:/n64recomp`.

**stderr is captured on Android.** `SDL_main` freopens it to
`files/stderr.log`, which is where the `[reg-frag]`, `[synth-frag]` and `[pi]`
diagnostics land — they are invisible otherwise and were what finally
identified the fragment-binding failures. Pull with
`adb -s 3c43878a exec-out run-as com.pokemonstadium2recomp cat files/stderr.log`.

A known-good copy of the generated tree is at
`ps2-recomp-build/runtime/generated.WORKING` — restore it if a regenerate goes
wrong.

Audio works as of 2026-08-12 — see "Audio: WORKING" below. Note that three of
its pieces live outside `runtime/`: `rsp.hpp` and `ai.cpp` in Stadium 1's
`N64ModernRuntime` checkout, plus an edit to `generated/`. `tools/` has a script
for each and they are idempotent, so re-run all three after any regeneration or
fresh checkout of that tree.

Do not treat APK installation or a living process as success. The required
completion evidence is continued guest execution plus changing rendered frames
on the physical device.

The repository-level `README.md` and `PORTING_STATUS.md` still describe the
older probe boundary and are stale relative to this handoff.

## Important locations

### Windows

- Repository: `C:\Users\laptop\Documents\lg\pokemonStadiumGSRecomp`
- Stadium 1 reference: `C:\Users\laptop\Documents\lg\PokemonStadiumRecomp`
- ADB: `C:\projects\ddd-dl\.android-sdk\platform-tools\adb.exe`
- Device serial: `3c43878a`
- JDK: `C:\Users\laptop\.jdks\ms-17.0.17`
- Gradle: `C:\Users\laptop\.gradle\wrapper\dists\gradle-8.9-bin\90cnw93cvbtalezasaz0blq0a\gradle-8.9\bin\gradle.bat`
- Native library destination: `android\app\src\main\jniLibs\arm64-v8a\libmain.so`
- APK: `android\app\build\outputs\apk\debug\app-debug.apk`
- Current screenshot: `artifacts\ps2-current-diagnostic.png`

### Mac Mini

- SSH: `michaegg@100.67.55.120`
- Stadium 2 runtime: `/Users/michaegg/ps2-recomp-build/runtime`
- Stadium 2 generated code: `/Users/michaegg/ps2-recomp-build/recomp-jal2/generated`
- Shared Stadium 1 runtime/dependencies: `/Users/michaegg/psr-recomp-build/work`
- Android dependencies: `/Users/michaegg/psr-recomp-build/deps/android3`
- Stripped output: `/Users/michaegg/ps2-recomp-build/apk-libs/libmain.so`
- Container: `psr-recomp-cross:latest`

The Mac runtime shares N64ModernRuntime sources from the Stadium 1 tree. Those
sources contain existing custom changes and diagnostics. Do not reset or
replace the tree wholesale.

## Android identity

- Package: `com.pokemonstadium2recomp`
- Activity: `com.pokemonstadiumrecomp.probe.MainActivity`

Useful commands:

```powershell
$adb = 'C:\projects\ddd-dl\.android-sdk\platform-tools\adb.exe'
& $adb -s 3c43878a shell pidof com.pokemonstadium2recomp
& $adb -s 3c43878a shell am force-stop com.pokemonstadium2recomp
& $adb -s 3c43878a shell am start -n com.pokemonstadium2recomp/com.pokemonstadiumrecomp.probe.MainActivity
& $adb -s 3c43878a shell run-as com.pokemonstadium2recomp cat files/freeze_trace.log
& $adb -s 3c43878a shell run-as com.pokemonstadium2recomp cat files/last_error.log
```

## Work already completed

The recompilation and Android port have already progressed beyond the status
documents. The installed runtime includes fixes for:

- generated static entries and direct JAL targets;
- the invalid ROM-tail section;
- manual function `func_8007BE88`;
- runtime trampolines at `0x801451A0` and `0x806788E0`;
- trampoline lifecycle handling;
- generated and runtime callback guards;
- runtime helper semantics; and
- reliable external-message preservation in message-queue wait paths.

The relevant local patches are in `patches/`. In particular:

- `librecomp-reliable-wait-drain.patch` is a candidate functional fix and
  should remain under investigation.
- `librecomp-lookup-memory-window.patch` is diagnostic.
- `librecomp-stadium2-fragment67-dma-trace.patch` is diagnostic.
- `stadium2-freeze-trace.patch` and `stadium2-freeze-trace-thread.patch` are
  diagnostic.
- `stadium2-freeze-queue-state.patch` and
  `librecomp-external-pending-accessor.patch` are diagnostic, added
  2026-08-06, and are what produced the corruption evidence below.

Several remote sources use CRLF. Applying the patches on the Mac may require:

```bash
git apply --ignore-space-change /path/to/patch
```

## Verified softlock evidence

Before the reliable-wait-drain change, the last meaningful event was an SP task
completion at about 5.631 seconds:

```text
rsp_run_task_exit type=2
~sp_done mq=800CDA10 msg=0x64 sent=0 type=2
```

Scheduler thread `tid=3`, guest thread `0x800CD020`, remained blocked in
`osRecvMesg` on queue `0x800CDA10`. The shared runtime's normal external-event
drain preserved reliable messages, but `wait_for_external_message` and its timed
variant dequeued events and ignored a failed non-blocking `do_send`. This could
drop SP completion when the target queue was temporarily full.

`librecomp-reliable-wait-drain.patch` adds `deliver_waited_external` so that a
failed reliable delivery is requeued while only coalescible events may be
dropped.

After that change, the trace proves repeated SP and DP completion delivery and
additional guest work. For example:

```text
34296 5586 rsp_run_task_exit
34297 5586 ~sp_done mq=800CDA10 msg=00000064 type=2
34298 5586 tid=3 ~osRecvMesg.done mq=800CDA10
...
34388 5603 rsp_run_task_exit
34389 5603 ~sp_done mq=800CDA10 msg=00000064 type=2
34390 5603 tid=3 ~osRecvMesg.done mq=800CDA10
...
34565 5640 ~dp_done mq=800CDA10 msg=00000065 type=1
34566 5640 tid=3 ~osRecvMesg.done mq=800CDA10
```

The current trace then ends its meaningful activity with:

```text
34622 5652 rsp_run_task_exit type=2
34623 5652 ~sp_done mq=800CDA10 msg=00000064 type=2
```

There is no subsequent `~osRecvMesg.done` for that final event in the captured
trace, while VI retrace continues and the process remains alive. This is the
most immediate boundary to instrument. Determine whether the event is queued,
requeued, delivered to a full queue, or unable to wake/schedule `tid=3`.

The runtime already exposes message diagnostics including:

- `ultramodern_mesg_recent_copy`;
- `ultramodern_mesg_qstates_copy`; and
- `ultramodern_external_requeues`.

That instrumentation was built and run on 2026-08-06; see the next section for
what it found. The event is neither dropped nor undeliverable in the ordinary
sense — the target queue no longer exists.

## Intermittent crash evidence

One post-fix run crashed near six seconds instead of softlocking. The bad
runtime lookup target was `0x240401C6` with this relevant backtrace:

```text
recomp_handle_tailcalls
func_80007E18
func_800080B8
func_80008648
func_82901BA8
func_82902694
func_82902808
func_82900020
recomp_handle_tailcalls
func_80064CE8
func_80065B20
Game_Thread
```

At failure, `sp=0x800AA8B0` and `ra=0x240401C6`. The Game Thread stack is
legitimate: it spans the base BSS stack region ending at `&leoDiskID`, around
`0x800AA9E0`. However, the stack contained MIPS instruction words such as:

```text
800AA8AC: 240401C6
800AA8B0: 0C013264
800AA8B4: 24050004
```

That sequence matches fragment 67 ROM code around ROM offset `0x34C084`, with
relocated high halves. Fragment 67 has:

```text
rom_addr=0x0033CB00
ram_addr=0x82900000
size=0x1B220
section index=206
```

The expected relocated runtime allocation was around `0x80161090`, well above
the Game Thread stack. `Util_InitMainPools` initializes the main pool from
approximately `0x80134470` through `0x80800000`, so a normal final overlay
allocation should not overlap `0x800AA8B0`.

The temporary fragment-67 PI trace did not fire during the later stable
softlock run. Do not assume this disproves the corruption; it may be timing
dependent or the diagnostic address filter may not match the physical address
form.

## Resolved: the softlock is guest-memory corruption, not a lost wakeup

Hypothesis 1 was instrumented and answered on 2026-08-06. The result
**invalidates the old priority order**: the message-queue symptoms are
downstream of a memory overwrite. Evidence:
`artifacts/ps2-freeze-state-2026-08-06.txt`.

The instrumentation is `patches/stadium2-freeze-queue-state.patch` plus
`patches/librecomp-external-pending-accessor.patch`. It extends the
`freeze_trace.log` dump with the live guest `OSMesgQueue` and `OSThread`
structs, the never-evict per-queue and per-thread tables, the scheduler ring
tail, and the external requeue/pending counters, sampled twice (t=12s, t=15s).

### The scheduler's reply queue has been overwritten with ROM code

At the freeze, `0x800CDA10` does not contain an `OSMesgQueue`:

```text
mq 800CDA10 validCount=-1391591424 first=1007672832 msgCount=-1402011648
            msgbuf=AC780004 blocked_recv=27184E78 blocked_send=246E0008
```

Those words are MIPS instructions. The six-word sequence
`27184E78 246E0008 AD0E0000 3C0FDE00 AC6F0000 AC780004` occurs exactly once in
the ROM, at offset `0x0034D2B0` — inside fragment 67 (`0x0033CB00..0x00357D20`).
The bytes are **unrelocated**, so this is a raw copy of ROM content, not a
relocated overlay image.

Mapping ROM `0x0034D2B0` to RAM `0x800CDA10` gives a load base of
`0x800BD260`, about `0xA3E30` below the expected `~0x80161090`. A `0x1B220`
load from that base spans `0x800BD260..0x800D8480`, which covers the entire OS
thread and queue block, including `0x800CD020` (tid=3), `0x800CDA10`,
`0x800CE170` (tid=20), `0x800D045C` and `0x800D0474`.

The separately corrupted `OSThread` at `0x800AA9E0` (tid=5, the Game Thread)
is **outside** that span and its contents do not match ROM, so it is a second,
distinct corruption — consistent with the Game Thread stack overflowing into
its own thread struct.

### The reliable-wait-drain change turns the softlock into a livelock

Because the corrupted header reads as permanently full, `do_send` fails
forever and `deliver_waited_external` requeues forever:

```text
t=12s  external_requeues=6596890  external_pending=1  running_queue_head=00000000
t=15s  external_requeues=9837862  external_pending=1  running_queue_head=00000000
```

That is about 1.08M requeue attempts per second on the idle thread (tid=1,
`0x800A8280`, the only `RUNNING` thread; every other guest thread is `BLOCKED`
and the running queue is empty). This spin is the likely cause of the 2.9 FPS,
so the frame rate is a symptom of the corruption, not an independent renderer
problem. `librecomp-reliable-wait-drain.patch` is not wrong, but it converts a
hard stall into a CPU-burning one; re-evaluate it only after the overwrite is
fixed.

### Fragment 67 is read once, well before the stall

The PI path in the trace matches the documented one — chunked reads on PI
worker tid=20 (`0x800CE170`) with completion queue `0x800D0474`: a `0x18`-byte
header read at ROM `0x1033CB00`, then `0x1000`-byte chunks stepping by
`0x1000`, all at about 3952–3957 ms. The queue at `0x800CDA10` still operated
normally until about 5652 ms, and there is no second PI read of that ROM range
in the trace. So either the destination was already wrong at 3955 ms and the
damage only surfaced later, or a later untraced guest copy (the loader's
decompress/relocate step, or the `func_800047F8` handle path) moved the raw
bytes into place. This is the open question.

## Audio: WORKING (2026-08-12)

Sound plays. Confirmed on device by the user and by measurement: PCM reaching
the host peaks around 17600 with ~1056 non-zero samples per 2112-byte buffer,
and audio tasks run with **0 watchdog trips and 0 unhandled jump targets**.

It took three independent fixes. Each one alone leaves the game silent, and the
first two were only visible after the one before it was in place.

### Fix 1 — the microcode is linked for IMEM 0x000, not 0x080

Two earlier attempts prepended the rspboot at ROM `0xB70` and put the ucode at
IMEM `0x080`, mirroring Stadium 1's toml. That shifts every absolute J/JAL and
every dispatch-table PC by 0x80 and hangs the task. The correct config is the
ucode alone:

```toml
text_offset  = 0x1060      # ROM
text_size    = 0x1000
text_address = 0x04001000  # IMEM 0x000
```

Three checks pin the base at 0x000; each lands on a delay slot or mid-loop if
the base is 0x080:

| site | instruction | target at base 0x000 |
| --- | --- | --- |
| IMEM 0x0AC | `j 0x060` | `lw $26,0($29)`, head of the dispatch loop |
| IMEM 0x058 | `jal 0x0CC` | `addi $5,$31,0`, a subroutine saving `ra` |
| ucode_data | handler PC `0x1154` | `andi $3,$25,0xFFFF`, a handler head |

The old symptom and how it read: the watchdog dump had `r28=0x17C0186C` and
`r27=0x1A5818BC`, which are `DMEM[0x30]` and `DMEM[0x34]` — dispatch-table
halfwords sitting where `task->data_ptr` and `task->data_size` belong. rspboot's
`beq -> 0x08C` had landed on ucode+0x0C, skipping `ori $10,$zero,0xFC0`, so
`$10` stayed 0 and every later `lw $x, off($10)` read ucode_data instead of the
OSTask block.

`tools/build_ps2_aspmain.py` emits `aspMain.ps2.us.toml` from the ROM (including
the 24 handler PCs from `ucode_data` halfwords `+0x10..+0x3E`) and carries the
full reasoning. `tools/wire_ps2_aspmain.py` points `get_rsp_microcode` at
`aspMain_ps2`; `aspMain_skip` is still in `main.cpp`, unused, as a one-line
revert. Regenerate with `RSPRecomp aspMain.ps2.us.toml` from the runtime root —
paths in the toml resolve relative to the toml's own directory, not the cwd.

### Fix 2 — the RSP DMA could not see KSEG1 buffers

With fix 1 in, the ucode ran its real dispatch loop and immediately hit
`Unhandled jump target 0x7FFF`, ~3900 times: it was DMA'ing 968 bytes of zeros
and dispatching on opcode 0 forever.

The Acmd list was never at the address the task named. `MEM_*` resolves a guest
address as `(addr - 0x80000000) & 0x3FFFFFFF`, so **KSEG1 lands 0x20000000
above KSEG0** — the two do not alias in this runtime the way they do on
hardware. Stadium 2 hands the audio task its list through a KSEG1 pointer
(`task->data_ptr = 0xA00DF2B0`), so the CPU wrote it to `rdram+0x200DF2B0` while
`dma_rdram_to_dmem` truncated to physical `0x0DF2B0` and read a region the game
never touched.

`tools/fix_rsp_kseg1.py` adds `rsp_dram_offset()` to
`librecomp/include/librecomp/rsp.hpp`: KSEG1 is resolved the way the CPU
resolves it, every other address stays on the existing physical path, and the
in-loop wrap masks widen from 16 MB so a resolved KSEG1 offset is not truncated
back down.

This matters beyond the command list — the alist itself mixes segments. Its
mixing buffers are KSEG0 (`0x800E3CC0`) but the ENVMIX state blocks the RSP
saves and restores each frame are KSEG1 (`0xA00E9120`, `0xA00E9160`,
`0xA00E9170`, `0xA00E91B0`).

### Fix 3 — Stadium 2 has no `osAiSetNextBuffer`

With fixes 1 and 2 in, the microcode ran clean and produced audio — and the game
still played nothing. 2600+ audio tasks in 45 s and
`ultramodern::queue_audio_buffer` was never called once.

The map file has `aigetlen.o`, `aigetstat.o` and `aisetfreq.o` but **no
`aisetnextbuf.o`**. Stadium 2 has its own routine at `0x800195C0` that writes the
AI registers itself:

```text
8001961C  sw $t2, 0x0($t3)     AI_DRAM_ADDR_REG = buffer (physical)
80019624  sw $a1, 0x4($t4)     AI_LEN_REG       = byte count, starts the DMA
```

librecomp only intercepts `osAiSetNextBuffer`, so those stores went to
`rdram+0x24500000` — slack — and nothing played.

`tools/wire_ai_submit.py` declares `recomp_ai_submit_buffer` in `recomp.h`,
implements it in `librecomp/src/ai.cpp` (forwarding to
`ultramodern::queue_audio_buffer` and refreshing AI_LEN), and inserts the call
at the store site in the generated sources. It is applied to `generated/` rather
than as a `game.toml` hook so it needs no regeneration; the generated file is
located by content, not by name, because regeneration reshuffles which
`funcs_N.c` holds a function.

**Do not try to detect the submission by watching the AI_LEN mirror.**
`publish_ai_len` in `ai.cpp` writes the remaining-byte count to the very same
address the game writes its length to, so the mirror cannot distinguish a
submission from a back-pressure refresh. The store site is the only unambiguous
signal.

### Still unfixed, same class as fix 1

**gbTowerMain / gbTowerColorMain are still Stadium 1's** (see below). They are
latent today. When they are recompiled from Stadium 2's ROM, check the IMEM base
the same way rather than assuming 0x080 — that assumption is what cost two
attempts here.

## Superseded: Stadium 2 was running Stadium 1's audio microcode

Found and fixed on 2026-08-06. This was the cause of the boot stall.

`runtime/rsp/aspMain.cpp` in the Stadium 2 tree is **byte-identical** to Stadium
1's. It was recompiled from Stadium 1's ROM (`ROM[0x66BC0..0x66C40]` rspboot +
`ROM[0x68020..0x69020]` aspMain, per Stadium 1's `aspMain.us.1.0.toml`), and
`get_rsp_microcode` returns it for every `M_AUDTASK` without checking that the
task's microcode matches. Two independent checks prove Stadium 2 does not ship
that microcode:

- Stadium 1's aspMain bytes do not appear in the Stadium 2 ROM at all — not the
  full 0x1000-byte body, not even its first 16 bytes. (Stadium 1's *rspboot*
  does appear, at ROM `0xB70`; only the audio body differs.)
- The dispatch/constant header the runtime expects at `DMEM[0..0x1F]`
  (`10EC 139C 119C 1A64 …`, present in the Stadium 1 ROM at `0x7F670`) appears
  nowhere in the Stadium 2 ROM. Stadium 2's live `ucode_data` reads
  `0000 0001 0002 FFFF 0020 0800 7FFF 4000 1F80 1250 1154 1094 …` — a different
  microcode revision with a different ABI.

Running the wrong microcode made its handlers compute RDRAM addresses from the
wrong command layout and write over unrelated memory. The tripwire pinned it:
the last message-queue check passed at 5627 ms, the clobber was detected at
5630 ms, and the only thing that executed in that window was one RSP task
(`rsp_run_task_enter` 5627 → `rsp_run_task_exit` 5629) — every guest thread was
already blocked.

Stadium 2's real audio microcode is at **ROM `0x1060`** (task `ucode` vaddr
`0x80000460`, section-5 delta `0xC00`; the body starts `340A0FC0 8D420018
8D43001C …`), with `ucode_data` at **ROM `0x87AF0`** (vaddr `0x80086EF0`).

`M_AUDTASK` was routed to `aspMain_skip` for a while, which completed the task
without executing anything: audio silent, corruption stopped, and the game
rendered its intro animation instead of a flat gray silhouette. That stopgap is
no longer in use — see "Audio: WORKING" above. The guess recorded here at the
time (mirror Stadium 1's toml, combined rspboot+aspMain blob, ucode at IMEM
0x080) turned out to be **wrong** and cost two on-device attempts.

## Fragment configuration: partially ported (2026-08-06)

Three of the four missing pieces are now in `game.toml` and the recompilation
has been regenerated with them.

### Done

**1. `Memmap_RelocateFragment` registration hook.** Stadium 2's function is
`func_80002210`, found by instruction-shape matching against Stadium 1's
`Memmap_RelocateFragment` (0x80001E50, 0x260 bytes): 100% of 152 instruction
shapes match, next best candidate 7.9%, identical 0x180-byte prologue. A
temporary trace on the hook confirmed it fires with
`(id=0x19, ptr=0x801451A0)`, `(id=0x00, ptr=0x80243950)` and
`(id=0xEF, ptr=0x806788E0)`. **Verified effect:** the
`lookup miss: 0x801451A0` that used to kill the second animation is gone.

**2. `decompressed_section_pattern` for slot 0x8FF00000.** Derived from the
hook trace: id 0xEF, and Stadium's own encoding
`id = ((vram & 0x0FF00000) >> 20) - 0x10` gives 0xEF ⇔ 0x8FF00000 — the same
slot and `pers_szp_yay0` wrapper Stadium 1 uses. Synthesis now produces 2473
`frag_8FF00000` section entries (total sections 89 → 740).

**3. `collision_policy = "suffix"`** under `[output]`, required because every
variant's entry symbol is at vram 0x8FF00020.

One wrapper (ROM 0x29E2270) needed a `decompressed_section_patch`: its header
declares `sizeInRam` past the decompressed blob because its trailing BSS is not
materialized. N64Recomp treats that as malformed and aborts the entire pattern,
even though the section is bounded by `relocOffset`, which is inside the blob.
The patch clamps the field. If another wrapper ever trips this, add another
`decompressed_section_patch` the same way — or relax the `size_in_ram` half of
the check in `n64recomp-2b/src/decompressed.cpp` (~line 330), which is the
cleaner fix but needs N64Recomp rebuilt (blocked: its `lib/tomlplusplus`
submodule is not checked out).

### Regenerating — two traps that cost a build cycle each

- `recomp-jal2/baserom.z64` was a **0-byte placeholder**; earlier generations
  never read the ROM. Decompressed-pattern synthesis does. It now symlinks
  `/ps2/runtime/baserom.z64`, and the container needs
  `-v /Users/michaegg/ps2-recomp-build:/ps2` because the workspace's symlinks
  point at container-internal `/ps2/...` paths.
- **A regenerate silently drops every post-generation patch.** Two are
  load-bearing: `stadium2-exclude-rom-tail-section.patch` (removes a bogus
  62 MB trailing section) and `stadium2-generated-callback-guard.patch`.
  Without them the game stops making guest progress at ~1.1 s while the process
  stays alive — which looks like success if you only watch the process. Re-apply
  with `tools/reapply_generated_patches.py`, which matches by content rather
  than line number so it survives symbol renaming.

### Fragment binding is now complete (2026-08-06, later)

All five fragments the boot path loads now register, and there are **zero
lookup misses**. Three further fixes got there:

**4. Synthetic pool overflow — `kSyntheticPoolEnd` 0xE0000000 → 0xF0000000.**
`librecomp/src/overlays.cpp`. Stadium 2's 0x8FF00000 stream synthesizes 651
variants against Stadium 1's ~279; 139 of them landed above the old 512-bucket
pool (up to 0xE8A00000), where `is_synthetic_addr` returns false, so their
sections never became registration candidates. The runtime reported exactly
512 candidates hashed and no match. Widening to 768 buckets is backward
compatible — existing addresses keep their slot index. **Verified:** the two
fragments then registered at slots 581 and 601, both formerly out of range.

**5. Extent guard bounded by the wrong header field.** Same file. The guard
rejected any section larger than header `+0x1C`, but `+0x1C` is not reliably
the total extent. Stadium 2's id=0 fragment has `+0x18 = 0x73A0` — which
matches its recompiled section byte for byte — and `+0x1C = 0x6790`, tracking
relocOffset instead. The correct variant was being rejected as "oversized" and
left unregistered, and its trampolines at 0x802439A8/B0/D0 and 0x80243A90 then
missed func_map. Now bounded by `max(+0x18, +0x1C)`, which keeps the guard's
intent (reject sections bigger than the loaded fragment) while using the field
that actually states the extent. **Verified:** 5 registered / 0 unregistered,
up from 3 / 2.

**6. Missing interior-entry dispatch alias for 0x80021A2C.** The recompiler
emits 51794 aliases of this shape and simply never seeded this one.
`static_5_80021834` already carries `case 0x80021A2Cu: goto L_80021A2C;`, but
nothing registered the address in func_map. Added
`dispatch_alias_s5_80021A2C` plus its `FuncEntry` row at offset 0x2162C.
Note the declaration must go INSIDE `funcs.h`'s `extern "C"` block — appending
at EOF produces a mangled-symbol link error. Applied by
`tools/add_dispatch_alias.py`.

### Current state and the remaining blocker

The crash is now a clean, fully characterised one. The tombstone
(`adb logcat -b crash`) reads:

```text
signal 11 (SIGSEGV), code 2 (SEGV_ACCERR)
Cause: stack pointer is not in a rw map; likely due to stack overflow.
  #00 get_function+4
  #01 static_5_80021834+784
  #02 dispatch_alias_s5_80021A2C+32
  #03 static_5_80021834+800
  #04 dispatch_alias_s5_80021A2C+32
  ... repeating to frame 255
```

`static_5_80021834` reaches a `jr` whose target, 0x80021A2C, lies **inside
itself** — a jump-table branch. The recompiler models it as a dynamic *call*
(`get_function` then invoke), so every iteration pushes a frame instead of
looping, and the thread stack overflows after a few thousand rounds. Adding
the dispatch alias removed the lookup miss but not the recursion: the alias
re-enters the function from the top and lands back on the same path.

This is a codegen question, not a configuration one.

**Tried and rejected: regenerating without `N64RECOMP_SKIP_AGGRESSIVE_STATIC_SEEDS=1`.**
It does not help. `static_5_80021834` still exists, `0x80021A2C` is still only a
`goto` case with no function of its own, and the output balloons from 241 to
1480 files (which also moves the callback-guard target out of `funcs_69.c` and
re-adds the ROM-tail section). Reverted; `recomp-jal2/generated.preseeds.bak`
holds the good tree.

**What the guest is actually doing.** `static_5_80021834` is hand-written
assembly using the PC-relative branch-and-link idiom:

```text
80021894: bltzal/bgezal ...        ; branch-and-link to obtain PC in $ra
8002189C: addiu $t3, $ra, 0x190    ; $t3 = 0x8002189C + 0x190 = 0x80021A2C
800218A0: bgezal $zero, L_80021988
...
800219A0: addu  $t5, $ra, $zero    ; loop head
800219A4: lh    $t2, 0x0($t0)
800219A8: jalr  $t3                ; call the local helper at 0x80021A2C
800219AC: lh    $t4, 0x0($t1)      ; delay slot
```

So `$t3 = 0x80021A2C` is **correct** — the routine deliberately calls a
subroutine inside its own body, addressed relative to the PC. The three `jr $ra`
sites in the function (0x80021980, 0x80021A24, 0x80021AB8) already use
`recomp_request_tailcall` properly.

The recompiler emits that `jalr $t3` as `LOOKUP_FUNC(ctx->r11)(rdram, ctx)` —
an out-of-line func_map call — so each iteration costs a host frame. On hardware
the call returns each time and the stack is flat; here the frames accumulate,
so the helper is being re-entered before it returns. Determining why needs a
proper disassembly of the routine's bounds (roughly 0x80021834..0x80021AC0,
possibly starting earlier at the branch-and-link that seeds `$ra`) and a trace
of the return path through the `jr` at 0x80021AB8.

Likely fixes, in order of preference:

1. Teach the recompiler that an indirect-call target provably inside the
   current function should use the dispatch-entry `goto` path rather than a
   func_map call. This is the real fix but needs N64Recomp rebuilt — currently
   blocked, its `lib/tomlplusplus` submodule is not checked out. Fixing that
   checkout is a prerequisite for several other improvements too.
2. Declare the whole hand-written routine as one `manual_funcs` entry with its
   true bounds so the CFG walk keeps it intact.
3. Instrument the return path first: log `host_return_target`, the `jr` target
   at 0x80021AB8, and `tailcall_pending` on each entry to confirm whether the
   return is being converted into a tailcall that re-enters instead of
   unwinding.

Related signal: the generator warns
`Failed to determine size of jump table at 0x800A5318 for instruction at 0x800649AC`,
so jump-table recovery is incomplete in this build generally.

Until this is fixed the boot path cannot get past ~8 s, so renderer and
graphics-driver work still has nothing stable to sit on.

### Superseded: the earlier lookup-miss list

Guest execution is healthy (34,666 trace events by 5.7 s, same order as the
best pre-regenerate build) and the crash has moved later, but it still crashes.
The surviving lookup misses are:

```text
0x80243A90, 0x802439A8, 0x802439B0, 0x802439D0   (a table of j/nop trampolines)
0x8069E8F0                                        (a FRAGMENT header)
0x80021A2C
```

All classify as "no loaded code section contains this as runtime or link-time
address". The fragment at `0x8069E8F0` has `relocOffset = 0x12780`, and a
synthesized section of exactly size 0x12780 **does** exist — so the section is
present but never bound at runtime. `register_runtime_fragment` is
content-hash keyed and only runs when the game calls `Memmap_RelocateFragment`
for that fragment; the hook trace showed a registration for the fragment at
`0x806788E0` but none for `0x8069E8F0`, which sits 0x26010 further on. That
suggests the game loads several fragments as one bundle and binds them through
a path the hook does not cover.

Next step: re-add the temporary trace on the hook, log every
`(id, ptr)` plus whether `register_runtime_fragment` found a matching section,
and find how the sibling fragments at `0x8069E8F0` / `0x8024xxxx` are supposed
to be bound — most likely a second chokepoint alongside
`Memmap_RelocateFragment` (Stadium 1 covers this with the `fragmentN_entry`
manual funcs, item 4 below, which are still missing).

## Still open: `fragmentN_entry` manual funcs

With audio fixed the game reaches the first Pokemon animation and then crashes
(~8-10 s, deterministic across cold launches) when the second should appear.
The failure is a `get_function` lookup miss:

```text
=== get_function lookup miss: 0x801451A0 ===
  address classification for 0x801451A0:
    runtime code section index=15 link=0x83F00000 runtime=0x801451A0
    size=0x500 offset=0x0 load_order=16
```

The bytes there are a fragment header — `j` + `nop`, then the `FRAGMENT` magic —
already rewritten by the game to the runtime target. Nothing is registered in
`func_map` at offset 0 of that section, so the call falls through and the guest
ends up executing garbage. That is the same signature as the intermittent crash
documented earlier: fragment code appears on a thread stack, the epilogue
restores `s0`-`s4` and `ra` from it, and `jr $ra` jumps to `0x240401C6`.

Comparing `game.toml` against the working Stadium 1 tree shows Stadium 2 is
missing every piece of fragment configuration:

1. **`Memmap_RelocateFragment` registration hook.** Stadium 1's `game.toml`
   carries `[[patches.hook]] func = "Memmap_RelocateFragment"`,
   `before_vram = 0x80001E50`, `text = "recomp_register_runtime_fragment(rdram,
   ctx->r4, ctx->r5);"`. Stadium 2 has no hook at all. Fragments that arrive by
   PI DMA get registered through `load_overlays`; fragments that arrive by
   CPU-side decompression never do — which is exactly why the first animation
   works and the second does not. `recomp_unregister_runtime_fragment` *is*
   already wired (`extras.c`, `pkmnstadium_memmap_clear_fragment`), so only the
   register half is missing.
2. **`fragmentN_entry` manual funcs.** Stadium 1 declares an 8-byte manual func
   at offset 0 of every fragment section so the header trampoline is a real
   recompiled function. Stadium 2 declares one manual func in total
   (`func_8007BE88`); only 7 of its 89 sections have any function at offset 0.
   The hardcoded `add_loaded_function(0x801451A0, func_83F002F4)` in
   `patches/stadium2-runtime-trampolines.patch` is a one-off band-aid for
   exactly this gap, correct only while section 15 happens to be resident at
   that pool address.
3. **`decompressed_section` / `decompressed_section_pattern` declarations.**
   Stadium 1 declares its PERS-SZP/Yay0 slots (`frag_8D000000`, pattern
   `frag_8FF00000`) so the recompiler synthesizes sections for CPU-decompressed
   fragments. Stadium 2 declares none.

Next session's work, in order: find Stadium 2's `Memmap_RelocateFragment` vram
and add the registration hook; add the `fragmentN_entry` manual funcs; identify
Stadium 2's decompression wrapper format and slots; regenerate with
`tools/mac_generate_recomp.sh`; then drop the hardcoded trampolines. After that,
recompile the audio microcode and remove `aspMain_skip`. (That last item is done
— see "Audio: WORKING".)

Next todo after the renderer/FPS work: generate/build and validate the rental
roster patch integrated from
`C:\Users\laptop\Documents\lg\pokemonStadiumGSRecomp-worktree`. It adds
additional Pokemon to the initial rental roster through `game.toml` hooks.
Verify the table relocation and the in-game roster behavior before treating it
as complete. The source worktree's original changes were preserved.

For fast Android iteration, the installed test build applied the equivalent
logic directly to the preserved generated sources in `funcs_119.c` and
`funcs_128.c`; this avoids regenerating the oversized full source tree. The
`game.toml` hooks remain the canonical regeneration path.

Also fixed along the way: `osSetIntMask_recomp` and `__osDisableInt_recomp` were
empty and never set `v0`, so they returned whatever the previous call left there
(`patches/librecomp-int-mask-return-value.patch` now tracks the mask per guest
thread and returns the real previous value). This was **not** the boot-stall
cause — the same empty version ships in Stadium 1, which works — but it is a
genuine latent defect.

## Superseded hypotheses

1. **Prove the overwrite's author and timing.** Record `dramAddr` and `size`
   into the ultra trace ring in `osEPiStartDma_recomp`/`do_dma` — the existing
   `~pi_dma_done` events leave `a2` zero, so destinations are invisible, and
   `librecomp-stadium2-fragment67-dma-trace.patch` writes to stderr, which is
   not captured on Android. Add a cheap tripwire that samples the header word
   at `0x800CDA10` on each VI retrace and records one trace event the first
   time it stops looking like a queue. That converts "somewhere between 3955 ms
   and 5652 ms" into an exact point with surrounding trace context.
2. **Fragment-67 destination arithmetic.** With the tripwire pinning the
   moment, log the request fields at `func_80006ACC`, the PI worker dispatch,
   and the loader's destination computation in `func_800047F8` /
   `func_800042C0`. `Util_InitMainPools` runs the main pool from about
   `0x80134470` to `0x80800000`, so a base of `0x800BD260` is outside the pool
   entirely — check whether the allocator returned a failure that the loader
   used as an address.
3. **Game Thread stack overflow at `0x800AA9E0`.** Separate corruption, same
   run. Confirm the stack bound and whether the thread struct sits inside it.
4. **`osSetIntMask_recomp` semantics.** Still unaddressed and still suspect:
   the implementation is empty and does not return the previous mask in `v0`.
   It appears in the trace right up to the stall (`pc=80017AEC`). Find the
   correct implementation in an upstream or known-working local
   N64ModernRuntime before changing it.

All four are now explained by the two root causes above and need no further
investigation on their own. The overwrite was the wrong audio microcode; the
extent estimate of `0x800BD260..0x800D8480` was wrong — the actual write was
`0x800CD850..0x800CDA38` (0x1E8 bytes) onto tid=3's stack, overrunning its top
by 0x28 bytes into the reply queue.

Note when reading `artifacts/ps2-freeze-state-2026-08-06.txt`: the dump that
produced it printed the guest `state` and `flags` fields swapped, so every
thread reads `state=STOPPED`. The real values are in the `flags=` column
(`0002` = RUNNING, `0003` = BLOCKED). The patch in `patches/` is already fixed;
the captured log predates the fix.

## Relevant game paths already traced

- `func_80065B20` calls `func_80064CE8` for fragment loading.
- `func_80064CE8` calls `func_800047F8`, invokes the returned function, then
  frees the loader handle.
- `func_800047F8` reaches archive/overlay loader `func_800042C0`.
- `func_80003F74` performs chunked ROM reads through `func_80006ACC`.
- `func_80006ACC` sends a `0x2C` PI request to queue `0x800D045C`.
- PI worker `func_800068C4` dispatches request type `0xF0` to
  `func_800066EC`.
- `func_800066EC` builds an `OSIoMesg` and calls `osEPiStartDma_recomp`, using
  completion queue `0x800D0474`.

The observed request layout is:

```text
+0x00 request type 0xF0
+0x1C ROM device address
+0x20 DRAM destination
+0x24 byte count
+0x28 completion queue
```

## Build, package, and device loop

Build on the Mac using the checked-in script:

```powershell
Get-Content -Raw .\tools\mac_build_runtime.sh |
  ssh michaegg@100.67.55.120 'bash -s'
```

If PowerShell input redirection is inconvenient, run the underlying command
directly on the Mac:

```bash
export DOCKER_CONFIG=/tmp/psr-docker-config
docker run --rm --platform linux/amd64 \
  -v /Users/michaegg/ps2-recomp-build/runtime:/work \
  -v /Users/michaegg/psr-recomp-build/work/lib:/work/lib:ro \
  -v /Users/michaegg/psr-recomp-build/work/cmake:/work/cmake:ro \
  -v /Users/michaegg/psr-recomp-build/deps/android3:/android:ro \
  -w /work psr-recomp-cross:latest \
  cmake --build /work/build-android --target PokemonStadiumRecomp --parallel 4
```

**Trap: reverting a source with `shutil.copy2` ships a stale binary.** `copy2`
preserves mtime, so restoring a `.orig` backup makes the file look *older* than
its object file and ninja skips it — the build succeeds, links, installs, and
still contains the code you just removed. `touch` the file after any restore, or
write it with `open(...).write()` instead. This cost a full build/install/test
cycle during the audio work.

Strip the native library on the Mac:

```bash
docker run --rm --platform linux/amd64 \
  -v /Users/michaegg/ps2-recomp-build/runtime:/work:ro \
  -v /Users/michaegg/ps2-recomp-build/apk-libs:/out \
  psr-recomp-cross:latest \
  /out/llvm-objcopy --strip-all /work/build-android/libmain.so /out/libmain.so
```

Copy, package, install, and launch from Windows:

```powershell
scp michaegg@100.67.55.120:/Users/michaegg/ps2-recomp-build/apk-libs/libmain.so android/app/src/main/jniLibs/arm64-v8a/libmain.so

$env:JAVA_HOME = 'C:\Users\laptop\.jdks\ms-17.0.17'
& 'C:\Users\laptop\.gradle\wrapper\dists\gradle-8.9-bin\90cnw93cvbtalezasaz0blq0a\gradle-8.9\bin\gradle.bat' :app:assembleDebug --no-daemon

$adb = 'C:\projects\ddd-dl\.android-sdk\platform-tools\adb.exe'
& $adb -s 3c43878a install -r android\app\build\outputs\apk\debug\app-debug.apk
& $adb -s 3c43878a shell am force-stop com.pokemonstadium2recomp
& $adb -s 3c43878a shell am start -n com.pokemonstadium2recomp/com.pokemonstadiumrecomp.probe.MainActivity
```

Gradle may need network access even with a warm cache. Preserve the existing
ROM and generated-output exclusions; do not commit ROMs, generated recompilation
output, APKs, or machine-local configuration.

## Cleanup required after diagnosis

Once execution advances reliably and the rendered frames change, remove the
temporary diagnostics before producing a final APK:

- `librecomp-lookup-memory-window.patch` effects;
- `librecomp-stadium2-fragment67-dma-trace.patch` effects;
- `stadium2-freeze-trace.patch` effects;
- `stadium2-freeze-trace-thread.patch` effects;
- `stadium2-freeze-queue-state.patch` effects;
- `librecomp-external-pending-accessor.patch` effects;
- `stadium2-freeze-diagnostics.patch` effects (cumulative main.cpp diagnostics:
  freeze-state dump, PI-fill dump, RDRAM snapshot. The `aspMain_skip` route it
  also carries is no longer active — `get_rsp_microcode` returns `aspMain_ps2`
  now — but leave `aspMain_skip` defined as the one-line revert);
- `librecomp-mesgqueue-diagnostics.patch` effects (queue-clobber tripwire); and
- `stadium2-trampoline-trace.patch` effects.

Keep `librecomp-int-mask-return-value.patch` — it is a functional fix, not a
diagnostic.

Backups of the pre-diagnostic sources are on the Mac as
`<file>.freezestate.orig` next to `main.cpp` and `mesgqueue.cpp`.

Retain functional fixes only after validating them with repeated cold launches.
Run several force-stop/start cycles because the stack corruption has been
intermittent. The final report must distinguish build/install success from
runtime and renderer validation.
