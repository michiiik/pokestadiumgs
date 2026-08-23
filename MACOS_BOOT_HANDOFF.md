# macOS boot handoff — Pokémon Stadium GS (Stadium 2)

Last updated: 2026-08-23 (session 4 — title screen on screen, screenshot-verified)

## STATUS: BOOTS TO THE TITLE SCREEN ✅ (screenshot-verified on screen)

**Seven** defects had to be fixed. The first five got the game rendering the
title screen into guest RDRAM; the last two got it onto the actual screen.

Reading the framebuffer out of RDRAM proves what the GAME rendered. It does NOT
prove anything reaches the window — those are separate claims, and for a while
this port satisfied the first while failing the second with a totally black
window. Verify with a real screenshot.

### 6. RT64's Metal swapchain had a null layer — every present was skipped

`create_window()` in `src/main/main.cpp` returned
`WindowHandle{ wmInfo.info.cocoa.window, nullptr }`. RT64's `MetalSwapChain`
constructor takes its `CA::MetalLayer` **straight from `renderWindow.view`** and
never re-derives it (not even in `resize()`), so `layer` stayed null,
`MetalSwapChain::isEmpty()` was permanently true, and
`PresentQueue::threadLoop` skipped **every present of every run**.

Confirmed on the live process:

```
(RT64::MetalSwapChain) { layer = nullptr, width = 960, height = 720,
                         drawables = size=3, each mtl = nullptr }
```

That one fact explains all of it: black windowed AND fullscreen, black with
`PSR_VIEW_RDRAM=1` (the skip happens before `viewRDRAM` is consulted), no
`[present]` or `[vifill]` lines ever while workload-side `[fb]` lines printed
fine, and `get_display_refresh_rate()` still returning 60 (that comes from the
`CocoaWindow` wrapper, which only needs the NSWindow).

A trap worth naming: `CocoaWindow` DOES derive `contentView` itself, which makes
`view = nullptr` look harmless. `MetalSwapChain` does not. Fixed by creating an
`SDL_Metal_CreateView` + `SDL_Metal_GetLayer` and passing the layer as `view`,
matching the working Stadium 1 port.

### 7. Instant present (RT64 PresentEarly) is now opt-in

`ultramodern/src/events.cpp` called `enable_instant_present()` on the first task
after game start. PresentEarly makes `State::updateScreen` early-return whenever
the VI framebuffer is already tracked by `fbManager`, skipping BOTH the
RDRAM-hash-change upload and the present push.

That is fatal here: at the title screen Stadium 2 submits **zero graphics tasks**
(`display_lists` freezes) because the art is RSP-JPEG-decoded straight into RDRAM
by `njpgdspMain` rather than drawn by the RDP — those are the ~900 "other" RSP
tasks in the progress counters, and they never reach `send_dl`. With PresentEarly
on, the window would have frozen on the last workload-driven present even after
fix 6.

Off by default, `updateScreen` runs its full path every VI tick: hash-compare
RDRAM under the VI, upload CPU/RSP-written changes into the high-res target via
`fbOperations`, and push a present on change — RT64's designed path for exactly
this game's behavior. Costs one frame of latency. `PSR_INSTANT_PRESENT=1`
restores the old behavior.

### 8. Audio microcode faults — FIXED (audio RSP tasks now run inline)

`aspMain_ps2` used to fault ~20-24 times per run with `UnhandledJumpTarget`
(`0x01F2`, `0x0119`, `0x060B`, `0xFFFFBB92` — a different garbage target each
time). Root cause: **the async SP task thread raced the game for the Acmd
buffer.**

On hardware the RSP drains the command list within the frame, so the game is
free to start rebuilding it almost immediately. Here the task thread could still
be reading list N when the game had begun overwriting it. The ucode then walked
into the middle of its own list — `r27 = 0x230` / `0xB0` bytes still remaining,
so nowhere near the end — read what was by then PCM sample data, and dispatched
on `(opcode & 0x7F) * 2` taken from a sample, landing outside the 24-entry
handler table.

Audio tasks now execute INLINE on the submitting thread in
`ultramodern/src/events.cpp`, so the list is consumed before `osSpTaskStartGo`
returns. njpgdsp/other tasks stay on the task thread — a JPEG decode is far too
long to run inline under the cooperative scheduler. `PSR_ASYNC_AUDIO=1` restores
the old behavior.

A/B on the same binary:

| | frames | audio tasks | faults | audio/1k frames |
|---|---|---|---|---|
| async (old) | 16,310 | 7,545 | **24** | 462.6 |
| inline (new) | 17,733 | 7,806 | **0** | 440.2 |

Audio throughput is unchanged (~5%, within variance), so this does not starve
audio — it removes ~20 dropped buffers per run.

Two dead ends worth recording:
- It is **not** the ucode's jump table. `$1` is `(opcode & 0x7F) * 2` read from
  the command word, so only `0x00..0x2E` are legal and the toml's 24
  `extra_indirect_branch_targets` entries are complete. Do NOT add entries, and
  do not revisit the rspboot/IMEM-offset question.
- It is **not** contention behind the 900 njpgdsp tasks. Faults occurred just as
  often before njpgdsp started (`other=0`) as during it.

### Things that were NOT the cause (don't re-investigate)

- MSAA / supersampling / `window_mode` — black at every setting.
- `viewRDRAM` — correct instinct, but unreachable behind the null-layer skip.
- Framebuffer address mismatch — `VI::fbAddress()` subtracts one row and the
  arithmetic is right in both modes (`0x769F80-0x500=0x769A80`,
  `0x7B4C80-0x280=0x7B4A00`), and the 9 `setColorImage` addresses exactly equal
  the 9 `[fb]` addresses.
- Interlace (`VI_STATUS` bit 6 set): `fbSize()` computes a healthy 640x476.
  Serrate width-halving needs `estimatedWidth < width/1.875` — 640 < 341 is false.
- `[fb]` target "thrashing": `tgt != rt` just means a larger existing target is
  reused; `halveTall` is interlace height compensation. Benign.

---

## STATUS: BOOTS TO THE TITLE SCREEN (RDRAM-level, historical)

The macOS build reaches the Pokémon Stadium title screen and holds there
(15,395 frames / ~4.3 min observed, zero assertion failures, clean SIGTERM exit).

```
[progress] display_lists=1941 screen_updates=15395 frames=15395 vi_ticks=15395
           | submit gfx=1941 aud=7648 other=900 | complete sp=10488 dp=1941
```

Five separate defects had to be fixed, in this order. Each is described below.

1. **Wrong ELF** — `runtime/generated` was recompiled from an ELF whose `.text`
   is 16 bytes larger than the ROM's, putting every address and data reference
   +0x10 off. Regenerated from the ROM-matching ELF.
2. **`src/` symlink trap** — relative `#include "../../generated/..."` resolved
   past the staged symlink into the *old* tree, mixing new function bodies with
   old section tables.
3. **AI submit wiring** — Stadium 2 writes the AI registers directly instead of
   calling `osAiSetNextBuffer`; the store site needed routing to
   `recomp_ai_submit_buffer`.
4. **Fragment registration was all-or-nothing** — see "Partial bind" below. This
   was the actual boot-stopper.
5. **Debug-only asserts were fatal** — see "NDEBUG" below.

### Verifying the title screen without screen capture

macOS Screen Recording is not granted to the terminal, so `screencapture` fails
with "could not create image from display". Read the framebuffer out of guest
RDRAM instead — no rebuild, works on a live process:

```
lldb -p <pid> --batch \
  -o "thread select <any game thread>" -o "frame select <do_recv frame>" \
  -o "expr -f hex -- ultramodern::renderer::get_vi_regs()->VI_ORIGIN_REG" \
  -o "memory read --binary --outfile /tmp/fb.bin --force --count 153600 rdram+0x007B4C80"
```

`VI_STATUS_REG & 3 == 2` means 16-bit RGBA5551 and not blanked. Decode with
**little-endian halfwords at host offset `(i*2) ^ 2`** — librecomp stores RDRAM
word-swapped, so a halfword access XORs 2, and the halfword itself is
little-endian. Getting either wrong yields a recognizable but heavily
colour-noised image; comparing mean horizontal delta across the four
xor/endian combinations picks the right one unambiguously (0.94 vs 4.38).

### Partial fragment bind (the boot-stopper)

`librecomp/src/overlays.cpp` rejected any fragment section whose `size >
sizeInRam`, on the reasoning that a recompiled section can never legitimately
exceed the loaded extent. That is too strict: a section's size covers trailing
*data*, but only its **functions** must be resident to dispatch correctly.

The reject was not free. With fragment `0x2F` (link `0x83F00000`, `size=0x500`
vs `sizeInRam=0x410`) left unregistered, an interpreted excursion through it
returned without completing its caller, which skipped the release send of the
heap-allocator binary semaphore at guest `0x800CCDB4` (`func_8000290C`). That
queue then sat at `msgCount=1, validCount=0` **forever**; every later allocation
in the game blocked behind it, and the boot wedged with `display_lists=0` while
audio — already initialized and allocation-free — happily ran at 60 Hz.

It now registers only the `FuncEntry`s ending at or before `sizeInRam` — safe by
construction, since every installed function's bytes are resident. For `0x2F`
that binds 65 of 79 funcs. Note `id=0x0` (`0x73A0` vs `0x6790`) has *all* funcs
ending by `0x604C`, so it now binds fully: the old blanket reject was discarding
a perfectly good section over trailing data.

Diagnostic worth keeping: the semaphore signature is visible directly —
`msgCount=1, validCount=0` with a thread queued means held-and-never-released.

### NDEBUG

`tools/mac_build_native.sh` now passes `-DNDEBUG` (while keeping `-O0 -g`).
N64Recomp stamps `NAN_CHECK(val) assert(val == val)` on FP ops; the game
legitimately pushes a transient NaN through `guLookAtReflectF` during boot, which
real hardware just computes with, and the assert was aborting the whole process
mid-boot. Drop `-DNDEBUG` when deliberately hunting one of these.

Also removed: a fatal `assert` in `librecomp/src/rsp.cpp` `run_task`. The layer
above (`run_rsp_task_or_warn`) is explicitly written to survive a `false` return
— it drops the task and still signals SP completion — so the assert was killing
the process for a condition the runtime already handles.

### Known remaining defect (cosmetic)

The `aspMain_ps2` audio microcode faults ~21 times per run with
`UnhandledJumpTarget`. **This is not a missing table entry** — the dispatch is
`$1 = (opcode & 0x7F) * 2` from the command word, so only `0x00..0x2E` are legal,
and the toml's 24 entries are complete. The faulting values are garbage
(`0x01F2`, `0x0119`, `0x060B`, `0xFFFFBB92` — varying per fault), and the
faulting command words decode as PCM sample data, not Acmds: the ucode is
faithfully executing a command list whose tail is audio samples. Either the guest
audio driver occasionally emits a short list, or the game rebuilds the Acmd
buffer while the SP task thread still consumes the previous one. ~0.2% of tasks;
each costs one ~16 ms audio glitch. Do NOT edit
`extra_indirect_branch_targets` or revisit the rspboot/IMEM-offset question.

---

## ROOT CAUSE FOUND — read this first

Everything below this section was written before the root cause was known, and
much of it describes symptoms, not causes. **The `generated/` tree the macOS
build was using is recompiled from the wrong ELF.**

`disasm/build/pokestadiumgs-us.elf` has a `.text` 16 bytes larger than the real
ROM's — `0xA7A90` vs `0xA7A80`. `runtime/generated` (Aug 13) was built from it,
so every address label and every absolute data reference past that point sits
**+0x10** off `baserom.z64`. `disasm-native/build/pokestadiumgs-us.elf` is the
ELF that matches the ROM byte-for-byte.

Evidence (sampled `lui` instructions in the base section, compared against
`baserom.z64` at the section's own `rom_addr`/`ram_addr` mapping):

| tree | matches at delta 0 | matches at delta +0x10 |
|---|---|---|
| `runtime/generated` | 20 / 196 | **176 / 196** |
| `recomp-work/generated` | **196 / 196** | 0 |

`runtime/generated` is the *only* bad tree. `generated.WORKING`,
`recomp-work/generated`, `recomp-lean/generated` and `recomp-jal2/generated` all
have base size `0xA7A80` and agree with the ROM.

**One-shot check for any tree** — in `recomp_overlays.inl` the base section must
read `ram_addr = 0x80000400, .size = 0x000A7A80`, and the bogus ROM-tail section
must be at `rom_addr = 0x00437610`. Equivalently, the inlined
`osAiSetNextBuffer` store `sw $a1, 0x4($t4)` must land at `0x80019624`.

### What this explains

The skew is why `osSendMesg`/`osRecvMesg` saw NULL guest queues, why the ALHeap
length underflowed to `0xFEE7C2DE`, why the audio config globals read as
garbage, and why `func_800051B0` blocked forever on a queue nobody ever sent to
— the code was reading each of those from an address 0x10 away from where the
ROM actually put it. The per-function guard patches
(`mac-native-funcs-{21,76,189}-guard.patch`) were each papering over one of
those symptoms; they are no longer applied by `tools/mac_build_native.sh`.

### The tell-tale that was missed for three sessions

Both of this repo's own post-generation tools encode the *correct* addresses:

- `tools/wire_ai_submit.py` anchors the AI store site at `0x80019624`
- `tools/reapply_generated_patches.py` anchors the ROM-tail section at `0x00437610`

Both refused to apply to `runtime/generated`, each off by exactly `0x10`. **A
post-generation anchor that does not match means the tree is wrong — never
adjust the anchor to make it apply.** (This session initially did adjust the
anchor, which "worked" and produced a still-dead build; the correct read was
that the tree, not the tool, was at fault.)

### Second bug, found while fixing the first: the `src/` symlink trap

`tools/mac_build_native.sh` used to symlink every top-level runtime directory
into the staged tree, `src/` included. But four files under `src/` include the
generated tables by **relative** path:

```c
#include "../../generated/recomp_overlays.inl"
#include "../../generated/funcs.h"
```

Through a symlinked `src/`, the compiler resolves those against the *real*
directory (`runtime/src/main`), so they land on `runtime/generated` — silently
ignoring the `source/generated` symlink. The result was a binary whose
recompiled function bodies came from the new tree but whose **section tables and
`funcs.h` came from the old, 0x10-skewed tree**. That is strictly worse than
either tree alone, and it produced no warning — only 5599 undefined
`static_5_<addr>` symbols at link time, because the two trees disagree about
which functions are static.

`src/` is now **copied**, not symlinked. If you add a staged directory whose
sources use relative includes that escape it, copy that one too.

Anything that reports "5599 undefined symbols" is this bug, not a missing
`dispatch_aliases.c` — that was an earlier misdiagnosis.

### Current build wiring

`tools/mac_build_native.sh` now stages from `$gen_dir` (env
`PS2_GENERATED_DIR`, default `generated-mac`), a GS-owned copy of
`recomp-work/generated`. `runtime/generated` is left untouched because the
Android build also references it. Both post-generation tools have been run
against `generated-mac` at their original anchors.

### State after both fixes

```
[progress] display_lists=0 screen_updates=23720 frames=23720 vi_ticks=23720 \
           | submit gfx=0 aud=23365 other=0 | complete sp=23364 dp=0
```

Compare against the old measurement further down (`aud=0 ... sp=0`). What
changed:

- **RSP tasks are submitted and complete** — audio at a steady 60/s, SP
  completion tracking it. `submit_rsp_task` was previously never called once.
- **`[PSR][audio] direct AI submit guest=0x800D4280 bytes=1984`** — the AI
  submit wiring works; real buffers reach the host and the voice ring is up.
- **The `invalid guest queue 0x00000000` flood is gone** — 0 occurrences, down
  from thousands. That spam was the 0x10 skew making the game read queue
  pointers from the wrong addresses.
- Runs 6.5+ minutes at 60 fps, window and Metal renderer up, no crash.

**Still `display_lists=0` / `gfx=0`: the game never builds a display list.**

A live backtrace (`lldb -p <pid> -o "bt all"`) shows all 8 game threads parked
in `osRecvMesg`, and Game_Thread deep in real game logic rather than stuck at
boot:

```
Game_Thread (funcs_136.c:232) -> func_80065B20 -> func_80064CE8
  -> unhandled_lookup_trampoline -> recomp_interpret_function
  -> func_80006CD0 -> func_8000290C -> osRecvMesg  [blocked]
```

It waits on guest queue **`0x800CCDB4`** (`mq_ = -2146644556`).

Two notes that correct earlier guesses in this document:

- The **interpreter tier does run** — `recomp_interpret_function` is right
  there in the live stack, carrying the unregistered fragment's code. The
  fragment-0x2F rejection is therefore not obviously fatal, and "the interpreter
  runs actual bytes" is being honoured.
- Adding a `[[input.decompressed_section_pattern]]` for `0x83F00000` does
  **not** help: the recompiler reports `found 0 wrappers in ROM`. The
  pre-existing `frag_81000000` pattern finds 0 as well — only `frag_8FF00000`
  (673 wrappers) actually matches. That block is inert; don't repeat it.

`mesgqueue.cpp` now has `PSR_QTRACE=1` first-touch queue tracing (one line the
first time a queue is sent to, one the first time a thread blocks on it).

**Result: `0x800CCDB4` IS sent to** — Game_Thread is merely idle at the instant
of the backtrace, not deadlocked. But four queues are blocked on and *never*
written. Full map (`lldb -o "bt all"` cross-referenced with the qtrace log):

| thread | waits on | via | ever sent to? |
|---|---|---|---|
| #45 | `0x800D0F60` | `func_80009E04` | **NEVER** |
| #46 | `0x800D045C` | `func_800068C4` | yes |
| #47 | `0x800CDA10` | `func_800053D4` | yes — scheduler, gets VI/SP |
| #48 | `0x80122CE0` | `func_80004F34` ← `func_80035174` | yes |
| #49 | `0x800AB3CC` | `func_80001B20` | **NEVER** |
| #50 | `0x800CDC20` | `func_80004F34` ← `func_800058B4` | **NEVER** |
| #51 | `0x800CCDB4` | `func_8000290C` ← `func_80006CD0` | yes |
| #52 | `0x80126F00` | `func_80041A78` | **NEVER** |

Registered hardware-event queues (`ultramodern_get_event_queues`, callable
straight from lldb — see below): SP=`0x800CDA10`, DP=`0x800CDA10`,
**AI=`0x00000000`**, SI=`0x800CE100`, VI=`0x800CDA10`. AI being unregistered is
expected: Stadium 2 writes the AI registers directly rather than using
`osAiSetNextBuffer`, which is exactly what the submit wiring exists for.

```
lldb -p <pid> --batch \
  -o 'expr uint32_t $q[5] = {0,0,0,0,0}' \
  -o 'expr (void)ultramodern_get_event_queues($q, 5)' \
  -o 'expr -f hex -- $q'
```

`func_800053D4` (thread #47) is the scheduler: it creates a queue, calls
`osSetEventMesg` ×3 + `osViSetEvent` ×1, then loops on `osRecvMesg` dispatching
to `func_800050D4`, `func_80005148`, `func_800051B0`, `func_800052C4`,
`func_80005388`. **None of those five contains a single `osSendMesg` call** —
each has 4 indirect-call constructs instead. So client notification here is
*indirect*, which is consistent with the toml's warning about a fragment whose
init never runs leaving a callback slot NULL.

The RSP submitters are `func_80004C14` and `static_5_80004C40`
(`osSpTaskLoad`+`osSpTaskStartGo`). They run — but are only ever handed audio
tasks.

All qtrace activity occurs during boot and then stops; steady state cycles
audio only. So the game is parked in an early state, not slowly progressing.

---

## TL;DR (pre-root-cause; retained for the measurement history)

The macOS build compiles, launches, opens a window, and is stable and
crash-free (~3% CPU). It does **not** reach the title screen.

The single sharpest measurement, from the built-in progress line:

```
[progress] display_lists=0 screen_updates=724 frames=724 vi_ticks=724 \
           | submit gfx=0 aud=0 other=0 | complete sp=0 dp=0
```

**`ultramodern::submit_rsp_task` is never called — not once, for any task
type.** The game submits zero RSP tasks, so there is no graphics work, no
audio task, and no SP/DP completion. Everything else that looks broken
downstream (no display lists, the audio thread waiting forever, the frame
counter at `0x8009487C` frozen) follows from that.

`frames`/`vi_ticks` climbing is the *runtime's* VI heartbeat, not game
progress. Do not read it as the game running.

### Two things worth knowing before continuing

1. **Do not mix generated snapshots.** `tools/mac_build_native.sh` was
   overlaying `funcs_76.c` from `generated.WORKING/` (Aug 7) while every other
   translation unit came from `generated/` (Aug 13). That alone kept Stadium 2
   from ever writing its AI registers. Fixed — the overlay now comes from
   `generated/`, and with it the game does perform one direct AI submit and
   the frame counter can tick (observed reaching 129 on one run).
2. **Behaviour is nondeterministic.** Most runs the counter stays at 1; one run
   it reached 129 and `Game_Thread` advanced to `funcs_127.c:3284`. There is a
   race here that is not yet understood.

## Build / run

```sh
cd /Users/michaegg/projects/pokemonStadiumGSRecomp
PS2_MAC_BUILD_ROOT=build-mac/safe CMAKE_BUILD_PARALLEL_LEVEL=1 \
  bash tools/mac_build_native.sh          # full stage + build (slow, from scratch)

# incremental after editing the GS runtime copy:
cmake --build build-mac/safe/ninja --target PokemonStadiumGSRecomp --parallel 1

cd build-mac/safe/ninja
PSR_AUTOBOOT=1 ./PokemonStadiumGSRecomp ../source/baserom.z64
```

ROM: US Pokémon Stadium 2, MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.

## IMPORTANT: GS now has its own N64ModernRuntime copy

**Do not edit `/Users/michaegg/psr-recomp-build/work/lib/N64ModernRuntime`.**
That tree is shared with the working Stadium 1 build; editing it broke Stadium 1
earlier in this work. It has been fully reverted and re-verified byte-for-byte
against the pristine copy in
`~/Desktop/PokemonStadium2-macos-agent-handoff-2026-08-22/build-local-ps2/lib/N64ModernRuntime`.

GS's own runtime copy now lives at:

```
/Users/michaegg/ps2-recomp-build/runtime/lib/N64ModernRuntime
```

seeded from the Android handoff snapshot, and `tools/mac_build_native.sh`
symlinks *that* into the staged source tree. All other libs (`rt64`, `SDL2`,
`adrenotools`, `recomp-ui`) are still symlinked from the Stadium 1 checkout —
only `N64ModernRuntime` is GS-owned.

Getting that copy to build needed these unrelated-to-logic fixes (all done):
- copied in the missing `thirdparty/` vendored deps (miniz/xxHash/etc.)
- ported Stadium 1's `PSR_MACOS_CONSTEVAL_GUARD` into `fmt/base.h` (Apple Clang
  `consteval` incompatibility)
- added `#include <cstddef>` to `librecomp/include/librecomp/audio_uaf_protect.hpp`
- implemented `osPiReadIo_recomp` (via `patches/mac-native-pi-runtime.patch`)
- removed the now-duplicate `__osSiRelAccess_recomp` stub from
  `tools/mac_link_shims.c`
- fixed a genuinely malformed hunk header in
  `patches/mac-native-pi-runtime-source.patch` (its line count was wrong, so it
  could never have applied)

## Fixed this session (all verified)

### 1. Scheduler: three real crash/hang bugs

In the GS runtime copy's `ultramodern/`:

- **`osRecvMesg`/`osJamMesg` missing pointer validation** — `osSendMesg` already
  guarded its guest queue address before `TO_PTR`; the other two didn't, giving
  a hard SIGBUS. Now all three guard. (`patches/mac-native-mesgqueue.patch`,
  applied to the `mac_mesgqueue.cpp` overlay.)
- **`run_next_thread` dereferenced retired thread contexts.** Now returns
  `bool`, skips dead entries, and only the genuinely-exiting call site in
  `run_game_thread` still throws.
- **`osCreateThread` didn't unlink a still-queued OSThread** before
  reinitializing it (unlike `osDestroyThread`). Now it does.

### 2. Scheduler: starvation, self-loop, and a 100% CPU busy-spin

- **Thread starvation.** The existing voluntary-preemption monitor only asks
  "has *any* context switch happened in 200 ms". That misses the real case:
  several higher-priority threads trading control among *themselves* keep that
  timer fresh while a low-priority thread starves. Added per-thread
  "queued since" tracking (`ultramodern_running_queue_oldest_wait_us`, keyed by
  guest OSThread address, microsecond resolution) plus a synchronous check on
  the running thread's own loop checkpoints. Threshold 250 µs; monitor interval
  2 ms. Gated behind the existing `PSR_DISABLE_VOLUNTARY_PREEMPTION` flag.
- **`yield_to_any_queued` could leave a thread running *and* queued.** It popped
  a target without checking liveness, re-queued itself, then called
  `resume_thread_and_wait`, which silently no-ops on a dead context. The caller
  returned still linked in `running_queue`; the next starvation check saw it as
  "queued and starving" and yielded to itself — **spinning forever at 100% CPU**.
  Now it skips dead entries, never yields to itself, and unlinks itself if the
  resume didn't actually switch.
- **`thread_queue_insert` self-loop.** Re-inserting a thread already in the same
  queue spliced it in front of itself (`added->next = *link` where `*link ==
  added_`), producing `next == self`. Every later walk then burned the 0x40000
  guard. Observed live: thread `80122B30` with `next=80122B30` and **6,260,089**
  scheduler events. Insertion is now idempotent.
- **Busy-wait removed.** `run_next_thread_and_wait`'s "nothing else runnable"
  fallback returned immediately, so `do_recv`'s `while (predicate)` loop spun at
  100% CPU and never let host-posted completions land. It now drains external
  messages with a short timeout.

**Measured effect: CPU dropped from ~120% to ~3%.**

### 3. The RDRAM corruption (root cause found and fixed)

This one explains both the earlier "Thread5" corruption *and* the message-queue
corruption, and was found with an LLDB watchpoint showing the target being
zeroed **one byte at a time, top-down** (`0x800cd9e0` → `0x000cd9e0` →
`0x0000d9e0`) — a `sb $zero` byte-clear loop.

Chain: `func_80035174 → func_80021B00 → func_80021AC0 → func_80015AB8 →
func_80011B78 → func_80011E7C → func_80010510`.

- `func_800105B8` is an `alHeapAlloc`-style bump allocator over an ALHeap with
  `base/cur/len` at `+0/+4/+8`.
- `func_80010510` allocates, then zero-fills from the returned pointer up to
  `hp->cur`.
- At runtime the arena at `0x8011EC00` held **`base=0`, `len=0xFEE7C2DE`**
  (~4.27 GB of garbage). With `base+len` enormous, the allocator's bounds check
  never failed, so it handed out ever-growing *raw offsets starting from 0* —
  physical addresses, not KSEG0 pointers.
- The zero-fill then wiped physical `0x0002DD20`–`0x0012AD40`: ~1 MB of low
  RDRAM, including the OSThread structs and OSMesgQueues at
  `0x800CD000`–`0x800CE000`. That is what was killing the scheduler mid-boot.

Why `len` is garbage: `len = *(0x8011EBD8) - used`, and `*(0x8011EBD8)` is 0, so
it underflows. Confirmed facts:
- `osMemSize` is correct (`0x00800000`, 8 MB) — not the cause.
- The ROM **deliberately** calls the audio init with zero args
  (`func_80021B00`: `or $a0,$zero,$zero` / `or $a1,$zero,$zero` in the delay
  slot), so the heap must come from that global.
- **Nothing in the entire generated codebase ever writes `0x8011EBD8`** —
  grepped for every store framing. `func_80015AB8` zero-fills the whole audio
  BSS block (`0x8011BEA0`, `0x6B91` bytes) which includes it, and nothing
  repopulates it.

**Current fix (a workaround, not the root fix):**
`patches/mac-native-funcs-21-guard.patch` + `mac-native-funcs-21-source.patch`
overlay `generated/funcs_21.c` as `mac_funcs_21.c` and force `len = 0` when
`base` is not a valid KSEG0 pointer. That makes the allocator fail through its
*own* existing failure path, and `func_80010510` already NULL-checks the result
and skips the zero-fill. **Result: `[do_send] BAD` count went from hundreds per
second to zero, and boot advances much further.** Audio is unallocated as a
consequence.

**The real fix** is to discover where the audio heap base/size are supposed to
come from. Since no recompiled code writes that global, the most likely
candidates are (a) initialized `.data` from the ROM that some load path isn't
delivering, or (b) a function that lives in a fragment that isn't being loaded
/ registered — which ties directly into the blocker below.

### 4. Resident functions were missing from (and evicted from) `func_map`

This was the fix that cleared the `get_function lookup miss: 0x80041A88` hang,
and it is a genuine runtime bug, not a workaround. Two halves:

- **Never registered.** `register_overlays()` only seeds `pc_index` for
  statically-resident sections; `func_map` is populated exclusively by
  `load_overlay`, which resident sections never go through. `func_map` is what
  `get_function()` consults for **indirect** dispatch, so every indirect call
  into main text missed. Direct calls were fine (the recompiler emits them as
  plain C calls), which is why this stayed hidden until the first indirect call
  to resident code. `init_overlays()` now registers every section that links
  inside KSEG0 RDRAM.
- **Then evicted.** Fragment unregistration erases `func_map` keys by range
  (`frag_range_erase`) and by computed alias (`section.ram_addr + offset`,
  `original_base + offset`). Some fragment sections link low — section 89 links
  at `0x80000000` — so those computed keys collide with real resident
  addresses, and a blind range erase can sweep the main text. Resident entries
  are never re-registered, so any eviction is permanent. Added a
  `resident_ranges` registry and routed **all** `func_map` erases through
  `func_map_erase_guarded()`, which refuses to evict resident addresses.

Effect: lookup miss gone, CPU 102% → 9%, and all guest OSThread structs now
read back with correct ids/states.

### 5. Rejecting invalid section bindings

`load_overlay` now refuses to bind a section at a base outside KSEG0 RDRAM.
Fires in practice:

```
[frag] REFUSING to bind section index=272 at invalid base 0x7E80BAB0 (size 0x3BC89F0)
```

## CURRENT BLOCKER

Not a crash and not a hang in the runtime — the game is alive and looping but
never draws.

Measured state after ~40 s:
- process alive, ~5-7% CPU, zero errors
- `display_lists = 0`, `run_task` never called, no fragment/asset loading
- `frames`/`vi_ticks` advancing ~60/s (runtime VI heartbeat)
- all guest threads healthy, correct ids, cleanly blocked in `osRecvMesg`;
  `Idle_ThreadEntry` in `pause_self`
- graphics events fully registered (see TL;DR)

### Audio init: now fixed (two patches), no longer the blocker

Stadium 2's audio configuration data is never delivered on this port -- every
value the audio init consumes is zero or garbage, because `func_80015AB8`
zero-fills the whole audio block (`0x8011BEA0`, `0x6B91` bytes) and **nothing
in the generated codebase repopulates it** (grepped every store framing). The
ROM deliberately calls audio init with `(a0=0, a1=0)`, so the data must come
from elsewhere -- most likely initialized `.data` a load path isn't
delivering.

Measured live, and both now worked around:

| what | where | measured | patch |
|---|---|---|---|
| ALHeap base / len | `0x8011EBD0 +0/+8` | `0` / `0xFEE7C2DE` | `mac-native-funcs-21-guard.patch` |
| voice alloc count | `s3` in `func_80013EF8` | `0x17B83` (96,643) | `mac-native-funcs-200-guard.patch` |

- **Heap seeding** gives each ALHeap a private 256 KB slice of reserved RDRAM
  at `0x80700000+`, lazily at first allocation (it must happen there, not at
  init, because the BSS clear would wipe it). This stopped the RDRAM
  corruption.
- **Voice-count clamp** caps the allocation loop at 64. Without it the loop ran
  96,643 iterations, scribbled ~96 KB past the audio block, and **never
  returned**, so the owning thread (`func_80035174`) never left audio init.

Effect, verified: `func_80013EF8`/`func_80011E7C` no longer appear in any
backtrace, `func_80035174` advanced from `funcs_142.c:6346` to `:6523`, SP
tasks are now submitted (`osSpTaskLoad`/`osSpTaskStartGo` both hit), and thread
3 is actively servicing SP/DP completions and broadcasting retrace.

**Dead end -- do not repeat:** skipping audio init entirely
(`func_80021AC0` early-return) does *not* help. `display_lists` stays 0 and the
game floods `osSendMesg`/`osRecvMesg` on never-created null queues. Patches for
it exist (`mac-native-funcs-189-*.patch`, wired into the build script) but the
staged file is reverted to pristine; delete those two patches and their
build-script blocks to remove the option entirely.

### Event -> queue map (measured)

Useful for tracing the remaining dependency chain:

```
SP(4), DP(9), PRENMI(14)  -> mq 0x800CDA20   (thread 3 services this)
SI(5)                     -> mq 0x800CE110
CPU_BREAK(10), FAULT(12)  -> mq 0x800D0F70
```

Guest retrace broadcasts go to `0x800AABB0` and `0x80122CF0` (msg `"VTRE"`).
`0x8011E0F0` saw 648,102 events and then went silent at ms=6276 while the run
continued to ms=23583 -- worth understanding why it stopped.

### The Stadium 2 AI submit hook IS missing — but it is not the immediate gate

The runtime documents a hook this project's `game.toml` does not have. From
`lib/N64ModernRuntime/librecomp/src/ai.cpp`:

> Stadium 2 has no osAiSetNextBuffer: it stores to AI_DRAM_ADDR_REG and
> AI_LEN_REG itself, and a guest store to 0xA4500000 lands in the mapping's
> slack where nothing reads it. **Its store site calls this instead**, so the
> buffer reaches the host queue on the same path osAiSetNextBuffer would use.

"This" is `recomp_ai_submit_buffer()`. Verified: it is **called from nowhere**
— not from any file in `generated/`, and not from any hook. `game.toml`
defines only 5 hooks (two fragment-registration on `func_80002210`, two
fragment-resolution on `func_800024A0`, one rental-table on `func_80006ACC`).
So this is a genuine, still-open gap and will need fixing eventually.

**However, a runtime-side bridge for it did NOT unblock boot.** Implemented in
the GS-local `librecomp/src/ai.cpp` (`recomp_ai_start_poll`): a 1 ms poller
that watches the AI_DRAM_ADDR_REG slack — which only the guest ever writes,
since `publish_ai_len` touches AI_LEN only — and forwards any buffer via
`recomp_ai_submit_buffer`. It starts on the first `osAiSetFrequency` and logs
`[ai] Stadium 2 AI submit bridge active`.

Result: the bridge runs, but **AI_DRAM_ADDR is never written**, the counter at
`0x8009487C` stays at 1, and `display_lists` stays 0. The audio thread blocks
on `0x8011E0F0` *before* it would ever submit a buffer, so audio submission is
downstream of the real stall, not the cause of it. The bridge is left in place
(cheap, and correct for when the game does get further), but it is currently
inert.

That means the open question is narrower than "audio is broken": **what is
supposed to post to `0x8011E0F0`, and why does nothing ever do so?** A
conditional breakpoint on `osSendMesg` for that queue never fires across an
entire run.

### The dependency chain (fully mapped, confirmed)

```
[missing AI hook]  ->  nothing ever posts to mq 0x8011E0F0
    (verified: a conditional breakpoint on osSendMesg with
     mq_ == 0x8011E0F0 never fires, for the entire run)

func_80035174 (thread)
  loop body: func_80021B74 -> func_80017AC0 -> func_80017B00
      osRecvMesg(mq 0x8011E0F0, NULL, OS_MESG_BLOCK)   <-- BLOCKS FOREVER
  then: *(0x8009487C) += 1  (0x80035318..0x80035324)
        b 0x8003527C  (loop)

Game_Thread -> func_800354B4 @ 0x80035544
  spin: while (*(0x8009487C) == sampled) ;             <-- never advances
        -> no asset loading, no display lists, no title screen
```

**Proof this chain is real (experiment, since reverted):** forcing that one
`osRecvMesg` to `OS_MESG_NOBLOCK` made the counter tick at ~62/s (657 -> 1030
in 6 s, exactly frame rate) and `Game_Thread` immediately advanced from
`funcs_127.c:3130` to `:3331` — into a *different* frame-wait loop. Reverted:
it is unprincipled, and with audio still unconfigured the loop then spins
sending to a never-created null queue, while `display_lists` stays 0 (there is
at least one more gate behind this one).

## Confirmed diagnosis (settled — do not re-derive)

The RSP pipeline is **not** the problem, and neither is the renderer. Measured:

- `submit_rsp_task` never called: `submit gfx=0 aud=0 other=0` for the whole run.
- The dispatcher that would call it, `func_80004C14` (which contains the only
  `osSpTaskStartGo_recomp` call sites, along with its alias
  `static_5_80004C50` in funcs_241.c), is **never entered**: an auto-continuing
  breakpoint on it recorded 0 hits across a 45 s run. Same for
  `osSpTaskStartGo` itself.

So the game never gets far enough to ask for any RSP work. Rendering, audio
tasks and SP/DP completion are all downstream of a stall that happens earlier.

The stall itself is fully characterised:

```
func_80035174 (audio thread)
  loop body blocks in osRecvMesg           <-- never returns
  then: *(0x8009487C) += 1   (0x80035318..0x80035324)

Game_Thread -> func_800354B4 @ 0x80035544
  spin: while (*(0x8009487C) == sampled) ; <-- so this never ends
        -> no asset loading, no task dispatch, no display lists
```

Caveat worth respecting: **a name breakpoint is not evidence.** Earlier in this
work a loose grep over breakpoint output produced a false "SP tasks are being
submitted" reading that was wrong. Trust the `[progress]` counters
(`submit`/`complete`), which are incremented by the real code paths.

## FOUND: the exact AI store site (the hook `ai.cpp` asks for)

Stadium 2's `osAiSetNextBuffer` equivalent is **`func_800195C0`**
(`generated/funcs_28.c`). The tail of it is:

```
0x8001962C: sw $t2, 0x0($t3)     # AI_DRAM_ADDR = t2   (t3 = lui 0xA450)
0x80019630: lui $t4, 0xA450
0x80019634: sw $a1, 0x4($t4)     # AI_LEN      = a1
0x80019638: or $v0, $zero, $zero
0x8001963C: jr $ra
```

`t2` is already KSEG0 (built as `addu $t2, $v1, $at` with `at = lui 0x8000`)
and `a1` is the byte count, so the hook the runtime documents is:

```toml
[[patches.hook]]
func = "func_800195C0"
before_vram = 0x80019638   # after both register stores, before the return
text = "recomp_ai_submit_buffer(rdram, (uint32_t)ctx->r10, (uint32_t)ctx->r5);"
```

**But adding it will not change boot behaviour, and regenerating just for this
is not worth the risk.** The runtime-side bridge already added to
`librecomp/src/ai.cpp` (`recomp_ai_start_poll`) watches the same
AI_DRAM_ADDR slack and calls the same function, so the hook is effectively
already in place. It fires exactly **once** per run — meaning `func_800195C0`
is itself only reached once, because the game stalls before submitting a
second audio buffer. The missing hook was never what gated boot.

(One caveat if you do rely on the poller: it only submits when AI_DRAM_ADDR
*changes*, so a game that legitimately re-submits the same buffer address
twice in a row would be missed. The real hook does not have that limitation.)

Regeneration remains an option for the *audio configuration data* problem, and
it can be done non-destructively: `game.toml`'s `output_func_path = "generated"`
can be pointed at a scratch directory, and a prebuilt engine already exists at
`~/ps2-recomp-build/n64recomp-2b-build/N64Recomp`, so the existing
`generated/` tree and the Android configuration never have to be touched.

## Lost-wakeup fix attempt (kept, but did NOT unblock boot)

`run_next_thread_and_wait()`'s "nothing else runnable" fallback now, after
draining external messages, parks on its own context with a **1 ms bounded
wait** instead of returning immediately. Rationale: a sender can pop us off
`blocked_on_recv` and `schedule_running_thread()` us between the emptiness
check and our return, so the resume that follows would signal a context nobody
is waiting on.

Measured result:
- **Does not fix the stall.** 3/3 runs still `display_lists=0`, `submit=0`.
- **Does fix a busy-spin.** Without it the caller's `while (predicate)` loop
  runs hot: ~103% CPU. With it: ~7%. Verified by removing and re-adding it.

Kept for the CPU win. Do not mistake it for a fix to the boot stall.

## NOT a timing race (hypothesis tested and disproven)

An earlier reading suggested a host/guest timing race: under LLDB with
auto-continuing breakpoints, `func_80021B74` showed 128 hits and
`func_80004F34` 130 in 45 s, versus a hard stall unthrottled. That looked like
a lost wakeup that the debugger's slowdown papered over.

**It is not.** Artificially throttling guest execution
(`PSR_GUEST_THROTTLE_US`, a sleep every 1024 loop checkpoints) at 0 / 50 /
500 us leaves the counter at `0x8009487C` frozen at **1** in every case, with
`display_lists=0` and `submit=0` throughout. Slowing the guest relative to the
host threads changes nothing.

So the earlier breakpoint counts were almost certainly *misattributed* — those
functions are reachable from more than one thread, and the hits need not have
come from `func_80035174`'s loop. Treat "it progresses under a debugger" as
unproven.

Practical consequence: **do not go hunting for a lost wakeup in the scheduler
changes on the strength of that observation.** The bounded self-wait in
`run_next_thread_and_wait` is still worth keeping, but only for its measured
CPU win (~103% -> ~7%), not as a race fix.

## `generated/` IS STALE relative to `game.toml` (important, unfixed)

Two of the five hooks defined in `game.toml` are **absent from the generated
code**:

| hook | in `generated/`? |
|---|---|
| `recomp_register_runtime_fragment` (func_80002210) | yes |
| rental-roster expansion (func_80006ACC) | yes |
| **`librecomp_fragment_input_push`** (func_800024A0 @ 0x800024A0) | **NO** |
| **`librecomp_fragment_resolve_exit`** (func_800024A0 @ 0x800024FC) | **NO** |

`func_800024A0` is the fragment-vaddr resolver — the Android porting handoff
(`~/Desktop/MACOS_BUILD_HANDOFF.md`) calls its instance-resolution the hardest
open correctness issue in the project, and these two hooks are exactly the
mechanism meant to address it. They are configured but not compiled in.

Timestamps agree: `game.toml` is Aug 22, `generated/` is Aug 13. Regenerating
with the current config *does* restore both hooks (verified — 0 files -> 1 file
each). **So the build is running with a resolver that is not doing what
`game.toml` says it should.** This is the same class of defect as the
`funcs_76.c` snapshot mixing, and it is still present.

### Regeneration: possible on macOS now, but the pipeline is multi-stage

Corrections to earlier advice in this document:

- A **pin-matching native macOS N64Recomp can be built** — the earlier claim
  that only a Linux binary exists was wrong. It needs the same Apple Clang
  workaround as the main build:
  ```sh
  cmake -S runtime/lib/N64ModernRuntime/N64Recomp -B /tmp/n64recomp-mac \
        -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-DFMT_USE_CONSTEVAL=0"
  cmake --build /tmp/n64recomp-mac --target N64RecompCLI   # emits ./N64Recomp
  ```
  (`N64Recomp` is the *library* target; `N64RecompCLI` builds the executable.)
- **N64Recomp alone does not reproduce `generated/`.** Its output lacks
  `dispatch_aliases.c`, which `generated/` has — that file comes from the
  post-processing scripts in `tools/` (`add_dispatch_alias.py`,
  `add_sibling_aliases.py`, ...). A naive regen therefore yields a
  *self-consistent but incomplete* tree: it defines 6941 `static_5_*` symbols
  matching its own `.inl`, but a different set than `generated/`, so linking it
  against anything built from the old tree produces thousands of undefined
  symbols.

### What the post-processing pipeline appears to be

The scripts are individually well-documented (read their docstrings), but the
*order* and full membership are not recorded anywhere I could find. Known
post-N64Recomp steps that mutate the generated tree:

- `tools/add_entry_switch.py` — gives `static_5_80021834` the interior-entry
  switch the recompiler never emits for late-synthesized section-5 statics.
  Without it, dispatch recurses infinitely (measured depth 100000) until the
  stack dies.
- `tools/add_dispatch_alias.py` — seeds the missing `func_map` alias for the
  interior entry `0x80021A2C`.
- `tools/add_sibling_aliases.py` — the three sibling PC-relative helpers
  (`$ra+0x190/0x184/0x170/0x164`).

Others in `tools/` may also belong to it (`merge_fragment_manuals.py`,
`derive_recomp_metadata.py`, `fix_abs_bss_reloc.py`, `fix_evict_extent.py`,
`fix_extent_bound.py`, ...). Note also that a fresh N64Recomp run over the
current ELF yields **6941** `static_5_*` symbols while `generated/` has
**6953**, so even the recompiler stage does not reproduce the existing tree —
the ELF or config that produced `generated/` differs from what is on disk now.

Because of that, reconstructing the pipeline blind is not safe: it silently
produces a tree that links against itself but not against the rest of the
build. Whoever owns the original generation flow should re-run it.

**To regenerate correctly, the whole pipeline must be run — N64Recomp then the
`tools/` post-processing — not just the recompiler.** That pipeline was not
reproduced in this session; the scratch attempt was deleted and the build
restored to `generated/`.

## The clearest statement of the deadlock (measured, final)

Counted with auto-continuing breakpoints over 45 s:

```
func_800051B0  (RSP task-submit path)          1305 hits
osRecvMesg on mq 0x800CDA20                    1305 hits   <-- every iteration blocks
osSendMesg on mq 0x800CDA20                       0 hits   <-- nothing EVER sends
func_80004C14 (calls osSpTaskStartGo)             0 hits
```

`0x800CDA20` is the task-request queue (it is also where SP(4), DP(9) and
PRENMI(14) events are registered). Stadium 2's scheduler thread sits on it
waiting for the game to ask for work. The game never asks, because
`Game_Thread` is still spinning on `*(0x8009487C)`, which is only ticked by
`func_80035174`, whose loop body blocks. Nothing in that cycle can start
itself.

**Priming the queue does not break the cycle** (tested, reverted): posting one
message on SP registration lets the scheduler thread run one iteration, but
`submit` stays 0 and CPU jumps to ~105%. It is waiting for a *work request*,
not a free completion slot — so a synthetic message just makes it spin.

The cycle can only be broken from the game side: something must make
`func_80035174`'s loop body return. Under a debugger it does (128 iterations),
which is why this is characterised as timing-dependent rather than a true
deadlock.

## The starvation check is load-bearing (validated by A/B)

`PSR_STARVATION_US` now isolates *only* the synchronous starvation check added
by this work, leaving the original stuck-thread monitor alone
(`PSR_STARVATION_US=0` disables it; default 250 us). Measured:

| setting | result |
|---|---|
| `PSR_STARVATION_US=250` (default) | survives; boot stalls with `display_lists=0` |
| `PSR_STARVATION_US=0` | **SIGBUS (exit 138)** at ~120 frames |

So the check is not cosmetic: without it a low-priority thread never runs and
the RDRAM corruption returns, exactly as first diagnosed. Keep it.

Two caveats to carry forward:

- With the check enabled, CPU varies **~4% to ~103% across runs of the same
  binary**, and queue snapshots differ run to run. The boot outcome is stable
  (always stalls) but the path there is not, so treat any single-run
  measurement with suspicion — several conclusions in this document came from
  single samples and two of them had to be retracted.
- `PSR_DISABLE_VOLUNTARY_PREEMPTION=1` is *not* a clean control for this: it
  disables the original monitor too, and the build dies earlier. Use
  `PSR_STARVATION_US` for A/B instead.

## Lost-wakeup window in do_recv (real, fix written, did NOT unblock)

`do_recv`'s wait loop is only safe if "check `MQ_IS_EMPTY` -> add self to
`blocked_on_recv`" is atomic with respect to senders. libultra gets that free
because game threads are cooperative. **Voluntary preemption breaks the
assumption**: a loop checkpoint between the emptiness check and the insert can
hand control to a sender, which finds `blocked_on_recv` still empty, wakes
nobody, and the receiver then sleeps on a queue that already holds its message.

A fix was written (re-check after the insert; unlink and take the message
instead of sleeping). It builds and is logically correct, but it did **not**
unblock boot — `submit` stayed 0 and CPU rose to ~103% — so it was reverted
rather than left in unvalidated. Worth re-deriving if the preemption design is
revisited, since the window is genuine.

Queue-state readings across runs are inconsistent and worth treating with
care: `mq 0x80122CF0` has been observed both as `vb=1 va=1` (full, sends being
dropped) and `vb=0 va=0` (empty, receiver blocked). CPU also varies between
~4% and ~103% run to run with identical binaries. That instability is itself
unexplained and may matter more than any single reading.

## Eliminated hypotheses (all tested — do not retry)

1. **Skipping audio init entirely** (`func_80021AC0` early-return) — no help;
   `display_lists` stays 0 and the game floods null-queue sends.
2. **The missing AI submit hook** — real, and its exact site is documented
   above, but a runtime poller already emulates it. It fires once per run,
   proving the game only reaches that code once. Not the gate.
3. **Malformed section 272** (`size=0x03BC89F0`) — genuinely bogus and now
   rejected at bind time, but rejecting it did not change boot.
4. **The RSP pipeline** — not involved at all: `submit_rsp_task` is never
   called and the dispatcher `func_80004C14` is never entered (0 hits/45 s).
5. **Lost wakeup in `run_next_thread_and_wait`** — the bounded self-wait fix
   is kept (it cuts CPU from ~103% to ~7%) but did not unblock boot.
6. **Priming the SP/task-request queue** — one synthetic message on SP
   registration; scheduler spins at ~105% CPU, `submit` stays 0. Reverted.
7. **The hardcoded PI-manager queue** (`osCreateMesgQueue(0x800CD000, ...)` in
   `mac-native-pi-runtime.patch`, inherited from an earlier session) —
   disabling it changed nothing. Restored to the tracked state.
8. **Guest-execution throttling** (`PSR_GUEST_THROTTLE_US`, 0/50/500 us) — no
   effect at any level; disproves the timing-race theory. Reverted.
9. **Closing the do_recv lost-wakeup window** — logically correct, builds,
   but `submit` stayed 0 and CPU rose to ~103%. Reverted.
10. **Regenerating with N64Recomp** — done non-destructively (scratch dir;
    `generated/`, `generated.WORKING/` and the Android cache all verified
    untouched, scratch deleted afterwards). It *does* restore the two missing
    fragment-resolver hooks, but N64Recomp alone does not reproduce
    `generated/` (no `dispatch_aliases.c`), so the result cannot be linked
    against the rest of the build. Needs the full `tools/` pipeline.
11. **Controller detection** — suspected because this port skips
   `SDL_PumpEvents` off the main thread. Ruled out: launcher mode is never
   activated (`apply_launcher_input_config` is not called under
   `PSR_AUTOBOOT`, confirmed by the absent "launcher config applied" log), so
   `get_connected_device_info` takes the legacy path where **port 0 always
   reports present**.

## Built-in progress monitoring

`tools/mac_debug_server_stub.cpp` (which replaces the Windows-only TCP debug
server on macOS) now reports the runtime's existing counters every 2 s:

```
[progress] display_lists=N screen_updates=N frames=N vi_ticks=N
```

These are incremented by live code already in the build
(`g_send_dl_count`/`g_update_screen_count` in `src/main/rt64_render_context.cpp`,
`g_vi_ticks`/`g_frame_count` in `src/main/main.cpp`), so this is pure
observation. `display_lists` is the one that actually indicates game rendering
progress. Set `PSR_PROGRESS=0` to silence.

The full TCP debug server is Windows-only here, but the Stadium 1 "rental"
checkout (`~/projects/PokemonStadiumRecomp-rental/src/main/debug_server.cpp`,
3391 lines) has a genuinely cross-platform version (`#ifdef _WIN32` / `#else`
with `netinet/in.h`, `sys/socket.h`). Porting that in would give full
interactive introspection if this investigation needs it.

## A note on a red herring

The `[clobber] RDRAM snapshot written` message is a **false positive**. The
tripwire (`mesgqueue.cpp: ps2_watch_clobber`) assumes `0x800CDA10` is an
OSMesgQueue and sanity-checks its `validCount`/`msgCount`. In reality
`0x800CDA10` is the *message buffer* for the queue at `0x800CDA20` — verified by
watchpoint: the write is a legitimate `do_send` storing message `0x66`. Don't
chase it.

Similarly, generated-code labels are uniformly `+0x10` versus the symbol
addresses in `disasm/build/pokestadiumgs-us.elf`. Everything is internally
consistent in generated-label space (section base = `0x80000400`, the
entrypoint); the ELF on disk is just a different/stale revision. Don't treat
that offset as a bug.

## Debugging techniques that worked

Conditional breakpoint + hardware watchpoint, resolving the RDRAM base at
runtime, is what cracked every one of these:

```sh
lldb --batch \
  -o 'breakpoint set -n osCreateThread -c "id == 1"' \
  -o 'settings set target.env-vars PSR_AUTOBOOT=1' \
  -o 'run ../source/baserom.z64' \
  -o 'breakpoint delete 1' \
  -o 'watchpoint set expression -w write -s 4 -- (uint8_t*)recomp_runtime_get_rdram() + 0x11EC08' \
  -o 'continue' -o 'bt' \
  ./PokemonStadiumGSRecomp
```

Notes:
- Use an LLDB command file (`-s file.lldb`) when you need many
  `continue`/`bt` pairs; shell arg expansion mangles repeated `-o` flags.
- A `script` block consumes all following `-o` commands — don't mix them.
- `--batch` stops running further `-o` commands after a *crash* signal, but
  continues after breakpoint/watchpoint stops.
- Guest word ↔ host `uint32_t` read directly (no swap needed) at 4-byte
  alignment: host addr = `rdram + (vaddr & 0x1FFFFFFF)`.

## Verification status

- [x] Builds clean from scratch
- [x] Launches, creates and shows a window
- [x] No crashes, no SIGBUS
- [x] No RDRAM corruption (`[do_send] BAD` count: 0)
- [x] CPU ~3% when idle-waiting (was ~120% spinning)
- [x] Stadium 1's shared runtime verified pristine (diffed against the Android
      snapshot; its `overlays.cpp`/`pi.cpp` differ only by *pre-existing*
      Stadium-1 work, confirmed before any edits this session)
- [ ] **Reaches title screen** — blocked on the lookup miss above
- [ ] Visual confirmation of rendered content (`screencapture` in this
      sandbox lacks Screen Recording permission; a human should look)
