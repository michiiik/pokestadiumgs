// scheduler_tick.cpp — voluntary preemption implementation. See
// scheduler_tick.hpp for the design rationale.
//
// Modifications in this file are part of N64ModernRuntime (GPL-3.0; see
// COPYING). New file added 2026 by Matthew Stanley.
//
// Copyright (c) 2026 Matthew Stanley
//
// ---------------------------------------------------------------------

#include <atomic>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "ultramodern/ultra64.h"
#include "ultramodern/ultramodern.hpp"
#include "ultramodern/scheduler_tick.hpp"

extern "C" uint32_t recomp_rsp_consume_preempt_skip_budget(void);
extern "C" uint32_t ultramodern_running_queue_head(void);
extern "C" uint64_t ultramodern_running_queue_oldest_wait_us(void);
// Defined in threads.cpp. Membership in its registry is the only trustworthy
// answer to "may I dereference/signal this context?", since an OSThread's
// context field lives in guest RDRAM and can be overwritten by the game.
bool ultramodern_context_is_live(UltraThreadContext* ctx);
#ifdef N64_COSIM
extern "C" void ultramodern_cosim_check_vi_quiescence(uint8_t* rdram);
extern "C" uint32_t ultramodern_cosim_deliver_due_rcp_events(uint8_t* rdram);
extern "C" uint32_t ultramodern_cosim_advance_due_vi(uint8_t* rdram, uint32_t allow_time_advance);
#endif

namespace {

// Read-mostly flag set by host monitor when no game-thread context
// switch has happened in kStuckThresholdMs. Cleared by the game thread
// when it services the yield. Hot path is one relaxed atomic load per
// recompiled function entry.
std::atomic<uint8_t> g_should_yield{0};

// Wallclock (steady_clock) milliseconds of the most recent context
// switch into a game thread. Stamped at wait_for_resumed return.
// Read by the host monitor.
std::atomic<uint64_t> g_last_switch_ms{0};

// Monitor thread control.
std::atomic<bool> g_monitor_exit{false};
std::atomic<bool> g_monitor_started{false};
std::thread g_monitor_thread;

// rdram stashed at init time so the no-arg slow path can pass it
// through to ultramodern primitives that take RDRAM_ARG. Single-writer
// (main thread, before any game thread spawns), many-reader (game
// threads); no sync needed beyond the relaxed-load.
uint8_t* g_rdram = nullptr;

// Threshold over which the monitor considers the current game thread
// stuck. 200 ms is well above any legitimate per-frame budget at 30 fps
// (33 ms) or 60 fps (16 ms), but small enough that stuck busy-waits
// resolve within a few hundred ms of becoming stuck.
constexpr uint64_t kStuckThresholdMs = 200;

// Threshold for the narrower per-thread starvation check (see
// ultramodern_running_queue_oldest_wait_us in threadqueue.cpp). A properly
// -scheduled system gives even a low-priority ready thread a turn within a
// frame or two (~16-33 ms at 60/30 fps); a thread still queued in
// running_queue well past that is starving even though other, higher
// -priority threads keep trading control among themselves and so look "not
// stuck" to the check above. Deliberately tighter than kStuckThresholdMs:
// the corrupting write this was added to catch (another thread overwriting
// a still-queued OSThread's fields) has been observed as little as ~150 ms
// after the thread was queued, so kStuckThresholdMs's 200 ms margin is too
// slow. Tracked per-thread (by guest address, since insert) rather than
// "time since the current queue head changed" — the latter undercounts
// starvation whenever any other thread is transiently queued/popped ahead
// of the starving one, which resets a head-based timer even though the
// starving thread itself never stopped waiting.
//
// This is checked synchronously on every loop-checkpoint hit by the
// actively-running thread (see scheduler_tick_impl's hot path), not just
// polled by the background monitor, so an aggressively small threshold is
// safe here: it only fires when something is actually sitting in
// running_queue (checked first via a lock-free head peek), which is rare
// outside exactly this kind of starvation window.
//
// Not zero, though: at zero this fires on *every* loop backedge that has
// anything queued, turning the scheduler into a full context switch per
// backedge. That still makes forward progress but is pathologically slow.
// Give normally queued work at least a full frame before overriding the
// priority scheduler. 250 us is shorter than ordinary host scheduling jitter
// and made the checkpoint force a context switch during normal preview and
// battle setup. 50 ms still leaves a wide margin before the earliest observed
// corrupting write (~150 ms).
// Env-tunable so the starvation check can be isolated from the rest of
// voluntary preemption: PSR_STARVATION_US=0 disables only this check and
// leaves the original stuck-thread monitor untouched.
static uint64_t starvation_threshold_us() {
    static const uint64_t v = []() -> uint64_t {
        const char* e = std::getenv("PSR_STARVATION_US");
        return e ? (uint64_t)std::strtoull(e, nullptr, 10) : 50000ull;
    }();
    return v;
}
static bool starvation_check_enabled() {
    static const bool on = []{
        const char* e = std::getenv("PSR_STARVATION_US");
        return !(e && std::strtoull(e, nullptr, 10) == 0ull);
    }();
    return on;
}

// Monitor wake interval. Short enough that detection latency past either
// threshold above is ~kMonitorIntervalMs.
constexpr uint64_t kMonitorIntervalMs = 2;

// Master enable. Off → monitor never sets the flag; the trace_entry hot
// path becomes a cheap load against a permanently-zero atomic.
std::atomic<bool> g_enabled{true};

constexpr uint64_t kRecompMemBase = 0xFFFFFFFF80000000ull;
constexpr uint32_t kRecompMemMask = 0x3FFFFFFFu;
constexpr uint64_t kSpStatusAddr = 0xFFFFFFFFA4040010ull;
constexpr uint32_t kSpStatusSignalMask = 0x00007F80u;
constexpr OSPri kHardwarePollPriority = 80;
constexpr uint32_t kLoopCheckpointCapacity = 256;
#ifdef N64_COSIM
constexpr uint64_t kCosimTraceEntryRetired = 4;
constexpr uint64_t kCosimTraceEntryCost = 4;
constexpr uint64_t kCosimTraceReturnRetired = 2;
constexpr uint64_t kCosimTraceReturnCost = 2;
constexpr uint64_t kCosimLoopBackedgeRetired = 2;
constexpr uint64_t kCosimLoopBackedgeCost = 2;
#endif

struct LoopCheckpointSlot {
    std::atomic<uint32_t> pc{0};
    std::atomic<uint32_t> thread{0};
    std::atomic<uint32_t> thread_id{0};
    std::atomic<uint32_t> ms{0};
    std::atomic<uint64_t> count{0};
};

LoopCheckpointSlot g_loop_checkpoints[kLoopCheckpointCapacity];

inline uint64_t now_ms() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(
        steady_clock::now().time_since_epoch()).count();
}

uint32_t load_mem_word(uint8_t* rdram, uint64_t vaddr) {
    return *reinterpret_cast<uint32_t*>(
        rdram + ((vaddr - kRecompMemBase) & kRecompMemMask));
}

void monitor_func() {
    using namespace std::chrono;
    while (!g_monitor_exit.load(std::memory_order_relaxed)) {
        std::this_thread::sleep_for(milliseconds(kMonitorIntervalMs));

        if (!g_enabled.load(std::memory_order_relaxed)) continue;

        uint64_t last = g_last_switch_ms.load(std::memory_order_relaxed);
        if (last == 0) continue; // No game thread has resumed yet.

        // Per-thread starvation check. Runs even when the "any switch
        // happened" check below finds nothing stuck, since a set of
        // higher-priority threads trading control amongst themselves keeps
        // last_switch_ms fresh while a lower-priority thread waits forever
        // somewhere in running_queue (not necessarily continuously at its
        // head — see ultramodern_running_queue_oldest_wait_us's comment).
        if (starvation_check_enabled() && ultramodern_running_queue_oldest_wait_us() > starvation_threshold_us()) {
            g_should_yield.store(1, std::memory_order_relaxed);
            continue;
        }

        if (g_should_yield.load(std::memory_order_relaxed)) continue; // Already pending.

        uint64_t now = now_ms();
        if (now - last > kStuckThresholdMs) {
            g_should_yield.store(1, std::memory_order_relaxed);
        }
    }
}

void record_loop_checkpoint(uint32_t pc) {
    if (pc == 0) {
        return;
    }

    uint32_t thread = 0;
    uint32_t thread_id = 0;
    uint8_t* rdram = g_rdram;
    if (rdram != nullptr) {
        PTR(OSThread) self = ultramodern::this_thread();
        if (self != NULLPTR) {
            OSThread* t = TO_PTR(OSThread, self);
            thread = static_cast<uint32_t>(self);
            thread_id = static_cast<uint32_t>(t->id);
        }
    }

    uint32_t slot_idx = thread_id < kLoopCheckpointCapacity ? thread_id : 0;
    LoopCheckpointSlot& slot = g_loop_checkpoints[slot_idx];
    slot.pc.store(pc, std::memory_order_relaxed);
    slot.thread.store(thread, std::memory_order_relaxed);
    slot.thread_id.store(thread_id, std::memory_order_relaxed);
    slot.ms.store(static_cast<uint32_t>(now_ms()), std::memory_order_relaxed);
    slot.count.fetch_add(1, std::memory_order_release);
}

void scheduler_tick_impl() {
    uint32_t cosim_delivered = 0;
#ifdef N64_COSIM
    if (g_rdram != nullptr) {
        cosim_delivered += ultramodern_cosim_advance_due_vi(g_rdram, 0);
        cosim_delivered += ultramodern_cosim_deliver_due_rcp_events(g_rdram);
        ultramodern_cosim_quiescence_state q{};
        ultramodern_cosim_get_quiescence(&q);
        if (q.quiescent) {
            if (ultramodern_cosim_advance_due_vi(g_rdram, 1) != 0) {
                return;
            }
            ultramodern_cosim_check_vi_quiescence(g_rdram);
            return;
        }
    }
    if (g_rdram != nullptr) {
        cosim_delivered += ultramodern_cosim_deliver_due_rcp_events(g_rdram);
        if (cosim_delivered == 0) {
            ultramodern_cosim_check_vi_quiescence(g_rdram);
        }
    }
#endif
    // Hot path: relaxed atomic loads + branches. Returns immediately
    // when no yield or externally-posted message is pending.
    if (__builtin_expect(g_should_yield.load(std::memory_order_relaxed) == 0, 1)) {
        // Synchronous starvation check, independent of the monitor thread's
        // polling. The monitor's own starvation detection (above, via
        // g_should_yield) is subject to std::thread wake-up jitter under
        // load — sleep_for(kMonitorIntervalMs) can easily overshoot by more
        // than the threshold when the host is busy, which made it miss the
        // race often enough to be unreliable. This check runs on the
        // actively-executing game thread itself, so there is no cross
        // -thread scheduling latency to lose the race to. Guarded by a
        // lock-free peek at the queue head first (the actual starvation
        // check takes a mutex) so it costs nothing once nothing is queued.
        if (g_enabled.load(std::memory_order_relaxed) &&
            ultramodern_running_queue_head() != 0 &&
            ultramodern::is_game_thread() && g_rdram != nullptr &&
            starvation_check_enabled() && ultramodern_running_queue_oldest_wait_us() > starvation_threshold_us()) {
            ultramodern::yield_to_any_queued(g_rdram);
            return;
        }
        if (cosim_delivered == 0 && !ultramodern::external_message_pending()) {
            return;
        }
        if (!ultramodern::is_game_thread()) return;
        if (g_rdram == nullptr) return;
        uint8_t* rdram = g_rdram;

        if (ultramodern::external_message_pending()) {
            ultramodern::wait_for_external_message_timed(rdram, 0);
        }
        ultramodern::check_running_queue(rdram);
        return;
    }
    // Slow path. Defensive: skip if called outside a game thread, or
    // before init_scheduler_tick stashed rdram.
    if (!ultramodern::is_game_thread()) return;
    if (g_rdram == nullptr) return;
    uint8_t* rdram = g_rdram;

    // Clear the flag *before* yielding. If we cleared it after, a
    // monitor wake during our yield could re-set it and we'd miss the
    // intended single-shot semantics.
    g_should_yield.store(0, std::memory_order_relaxed);

    // Drain one pending external message into its target OSMesgQueue.
    // Non-blocking. This is what unblocks predicate-flipping threads
    // sitting in osRecvMesg waiting for a completion event posted from
    // a host thread (audio task complete, DP/SP/VI completions, etc.).
    ultramodern::wait_for_external_message_timed(rdram, 0);

    // If an RSP signal bit is already visible to CPU-side MMIO polling,
    // let the current busy-waiting thread consume it immediately instead
    // of queueing that thread behind unrelated game work. This preserves
    // the voluntary-preemption escape hatch for unsatisfied waits while
    // avoiding starvation at the exact moment an HLE/recompiled RSP task
    // has published the predicate the loop is spinning on.
    if ((load_mem_word(rdram, kSpStatusAddr) & kSpStatusSignalMask) != 0) {
        PTR(OSThread) self = ultramodern::this_thread();
        bool high_priority_poll = self != NULLPTR &&
            TO_PTR(OSThread, self)->priority >= kHardwarePollPriority;
        if (high_priority_poll || recomp_rsp_consume_preempt_skip_budget() != 0) {
            return;
        }
    }

    // Swap to head of running_queue regardless of priority. The stuck
    // thread is by definition busy-waiting on a predicate that some
    // other thread (often same-or-lower priority) needs to flip.
    ultramodern::yield_to_any_queued(rdram);
}

} // namespace

void ultramodern::init_scheduler_tick(RDRAM_ARG1) {
    g_rdram = rdram;
    if (g_monitor_started.exchange(true, std::memory_order_relaxed)) return;
    g_monitor_exit.store(false, std::memory_order_relaxed);
    g_monitor_thread = std::thread{monitor_func};
}

void ultramodern::join_scheduler_tick() {
    if (!g_monitor_started.load(std::memory_order_relaxed)) return;
    g_monitor_exit.store(true, std::memory_order_relaxed);
    if (g_monitor_thread.joinable()) {
        g_monitor_thread.join();
    }
    g_monitor_started.store(false, std::memory_order_relaxed);
}

void ultramodern::record_context_switch() {
    g_last_switch_ms.store(now_ms(), std::memory_order_relaxed);
}

void ultramodern::yield_to_any_queued(RDRAM_ARG1) {
    ultramodern::scheduler_trace_mark(PASS_RDRAM 130, ultramodern::running_queue, ultramodern::this_thread());
    const PTR(OSThread) self_ = ultramodern::this_thread();
    // The main thread reports is_game_thread() == true but has no guest
    // OSThread (thread_self stays NULLPTR), so it has nothing to re-queue and
    // must never try to swap itself out.
    if (self_ == NULLPTR) {
        return;
    }

    for (;;) {
        if (ultramodern::thread_queue_empty(PASS_RDRAM ultramodern::running_queue)) {
            ultramodern::scheduler_trace_mark(PASS_RDRAM 131, ultramodern::running_queue, self_);
            return;
        }
        PTR(OSThread) next_ = ultramodern::thread_queue_pop(PASS_RDRAM ultramodern::running_queue);
        if (next_ == NULLPTR) {
            return;
        }
        // Yielding to ourselves is a no-op that would leave us queued while
        // still running; just drop the stale self-entry and stop.
        if (next_ == self_) {
            TO_PTR(OSThread, self_)->state = OSThreadState::RUNNING;
            return;
        }
        OSThread* next_thread = TO_PTR(OSThread, next_);
        // Only hand control to a thread whose context can actually be
        // signalled. Without this the resume below silently fails, and
        // because we have already re-queued ourselves we return still linked
        // in running_queue while running — which makes the next starvation
        // check see us as "queued and starving" and yield again, spinning
        // forever at 100% CPU instead of making progress.
        if (!ultramodern_context_is_live(next_thread->context)) {
            static std::atomic_flag reported = ATOMIC_FLAG_INIT;
            if (!reported.test_and_set()) {
                fprintf(stderr,
                    "[thread] yield_to_any_queued: dropping dead queued thread id=%d "
                    "(context %p not live)\n",
                    next_thread->id, (void*)next_thread->context);
                fflush(stderr);
            }
            continue;  // Drop it and look for a live one.
        }

        // Re-queue ourselves at the priority-ordered position then resume
        // the next thread and block on our own context. Same shape as the
        // file-static swap_to_thread in scheduling.cpp.
        {
#ifdef N64_COSIM
            ultramodern::CosimSchedulerMutation cosim_mutation;
#endif
            ultramodern::thread_queue_insert(PASS_RDRAM ultramodern::running_queue, self_);
            ultramodern::scheduler_trace_mark(PASS_RDRAM 133, ultramodern::running_queue, self_);
            TO_PTR(OSThread, self_)->state = OSThreadState::QUEUED;
        }
        ultramodern::scheduler_trace_mark(PASS_RDRAM 132, ultramodern::running_queue, next_);
        ultramodern::scheduler_trace_mark(PASS_RDRAM 134, ultramodern::running_queue, next_);
        ultramodern::resume_thread_and_wait(PASS_RDRAM next_thread);

        // If the resume never actually switched away (resume_thread_and_wait
        // returns immediately in that case), we are still linked in
        // running_queue. Unlink so we don't run while queued.
        if (TO_PTR(OSThread, self_)->queue == ultramodern::running_queue) {
            ultramodern::thread_queue_remove(PASS_RDRAM ultramodern::running_queue, self_);
        }
        TO_PTR(OSThread, self_)->state = OSThreadState::RUNNING;
        ultramodern::scheduler_trace_mark(PASS_RDRAM 135, ultramodern::running_queue, self_);
        return;
    }
}

extern "C" void ultramodern_voluntary_preemption_set_enabled(int enable) {
    g_enabled.store(enable != 0, std::memory_order_relaxed);
}

extern "C" void ultramodern_scheduler_tick(void) {
    scheduler_tick_impl();
}

extern "C" void ultramodern_scheduler_tick_vram(uint32_t pc) {
    record_loop_checkpoint(pc);
#ifdef N64_COSIM
    ultramodern_cosim_advance_cpu_cycles(kCosimLoopBackedgeRetired, kCosimLoopBackedgeCost);
#endif
    scheduler_tick_impl();
}

#ifdef N64_COSIM
extern "C" void ultramodern_cosim_trace_entry(void) {
    ultramodern_cosim_advance_cpu_cycles(kCosimTraceEntryRetired, kCosimTraceEntryCost);
    scheduler_tick_impl();
}

extern "C" void ultramodern_cosim_trace_return(void) {
    ultramodern_cosim_advance_cpu_cycles(kCosimTraceReturnRetired, kCosimTraceReturnCost);
}

extern "C" void ultramodern_cosim_trace_loop(void) {
    ultramodern_cosim_advance_cpu_cycles(kCosimLoopBackedgeRetired, kCosimLoopBackedgeCost);
    scheduler_tick_impl();
}
#endif

extern "C" uint32_t ultramodern_loop_checkpoint_capacity(void) {
    return kLoopCheckpointCapacity;
}

extern "C" int ultramodern_loop_checkpoint_get(uint32_t thread_id,
                                               ultramodern_loop_checkpoint_event* out) {
    if (out == nullptr || thread_id >= kLoopCheckpointCapacity) {
        return 0;
    }

    LoopCheckpointSlot& slot = g_loop_checkpoints[thread_id];
    uint64_t count = slot.count.load(std::memory_order_acquire);
    if (count == 0) {
        return 0;
    }

    out->pc = slot.pc.load(std::memory_order_relaxed);
    out->thread = slot.thread.load(std::memory_order_relaxed);
    out->thread_id = slot.thread_id.load(std::memory_order_relaxed);
    out->ms = slot.ms.load(std::memory_order_relaxed);
    out->count = count;
    return 1;
}
