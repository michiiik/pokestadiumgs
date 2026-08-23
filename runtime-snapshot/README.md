# Runtime snapshot (macOS native build)

Verbatim copies of the files under `/Users/michaegg/ps2-recomp-build/runtime`
that the macOS build depends on and that carry GS-specific fixes.

**Why this exists:** that runtime tree is *not* a git repository, so every fix
below lives on one machine with no history. `tools/mac_build_native.sh` builds
against the live tree, not against this directory — these copies are here so the
work is recoverable and reviewable, nothing more.

This is a snapshot, not a patch series. It will drift from the live tree; treat
`/Users/michaegg/ps2-recomp-build/runtime` as authoritative and refresh these
copies when you change it.

## What each file carries

| file | change |
|---|---|
| `src/main/main.cpp` | `create_window()` now builds an `SDL_Metal_CreateView` + `SDL_Metal_GetLayer` and passes the layer as `WindowHandle::view`. RT64's `MetalSwapChain` reads its `CAMetalLayer` straight from that field and never re-derives it, so `nullptr` made `isEmpty()` permanently true and **every present was skipped** — a black window while the game rendered fine into RDRAM. |
| `src/main/rt64_render_context.cpp` | `PSR_VIEW_RDRAM=1` escape hatch that flips RT64's `presentQueue->viewRDRAM`, kept because it is a useful one-env sanity switch. Set from our glue so the shared `lib/rt64` stays untouched. |
| `ultramodern/src/events.cpp` | Two fixes. (1) RT64 PresentEarly (`enable_instant_present()`) is now opt-in via `PSR_INSTANT_PRESENT=1`; it early-returns for tracked framebuffers, and Stadium 2 submits zero gfx tasks at the title screen (art is RSP-JPEG-decoded into RDRAM), so the window froze. (2) Audio RSP tasks run INLINE at submit instead of on the SP task thread, closing the race where the game recycled the Acmd buffer mid-consume — 24 ucode faults per run to 0. `PSR_ASYNC_AUDIO=1` restores the old path. |
| `librecomp/src/overlays.cpp` | Fragment registration now does a PARTIAL bind: a section whose `size > sizeInRam` registers only the `FuncEntry`s that end within the resident extent instead of being rejected outright. The old all-or-nothing reject left fragment `0x2F` unregistered, and the interpreted path through it skipped a heap-mutex release — wedging the whole boot. |
| `librecomp/src/rsp.cpp` | Removed a fatal `assert` on unexpected RSP ucode exit. `run_rsp_task_or_warn()` is explicitly written to survive a `false` return (it drops the task and still signals SP completion), so the assert was killing the process for a condition the layer above already handles. |
| `librecomp/src/ai.cpp` | Stadium 2 writes the AI registers directly rather than calling `osAiSetNextBuffer`; this carries `recomp_ai_submit_buffer`. The earlier register-*poller* approach was removed — polling cannot distinguish a real submission from an AI-full refresh. |
| `ultramodern/src/mesgqueue.cpp` | `PSR_QTRACE=1` first-touch queue tracing: one line the first time a queue is sent to, one the first time a thread blocks on it. This is what identified the never-written queues during the deadlock hunt. |
| `ultramodern/src/{threads,threadqueue,scheduler_tick,scheduling}.cpp` | Scheduler/starvation work from earlier sessions (`PSR_STARVATION_US`, running-queue wait tracking, liveness guards). |
| `mac-regen-game.toml` | N64Recomp config used to regenerate `generated-mac` from the ROM-matching ELF. Note the `frag_83F00000` `decompressed_section_pattern` block in it is INERT (`found 0 wrappers in ROM`) — kept only so nobody retries that dead end. |

See `../MACOS_BOOT_HANDOFF.md` for the full diagnosis behind each of these.
