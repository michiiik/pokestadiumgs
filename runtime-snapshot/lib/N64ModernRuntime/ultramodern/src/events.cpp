// N64ModernRuntime — modifications in this file by Matthew Stanley
// (mstan fork). Per GPL-3.0 §5(a), changes are noted below; original
// file copyright remains with the original authors. See COPYING.
//
// Modified 2026 by Matthew Stanley:
//   - osSpTaskStartGo ring + sp/dp_complete counters for runner-side
//     diagnostics (commit 4e0c9fe).
//   - Submit-task counters surfaced via ultramodern_submit_*_count
//     (commit dd8137d).
//   - Framework-level libultra ring + RSP watchdog + boot fixes for
//     PokemonStadium boot sequencing.
//   - Publish HLE SP task-completion status for CPU-side SP_STATUS polling.
//
// Copyright (c) 2026 Matthew Stanley
//
// ---------------------------------------------------------------------

#include <thread>
#include <atomic>
#include <chrono>
#include <cinttypes>
#include <variant>
#include <unordered_map>
#include <utility>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <vector>

#include "blockingconcurrentqueue.h"

#include "ultramodern/ultra64.h"
#include "ultramodern/ultramodern.hpp"

#include "ultramodern/rsp.hpp"
#include "ultramodern/renderer_context.hpp"
#include "ultramodern/ultra_trace.hpp"

static ultramodern::events::callbacks_t events_callbacks{};

void ultramodern::events::set_callbacks(const ultramodern::events::callbacks_t& callbacks) {
    events_callbacks = callbacks;
}

struct SpTaskAction {
    OSTask task;
    uint64_t cosim_gfx_seq = 0;
    moodycamel::LightweightSemaphore* cosim_done = nullptr;
};

struct ScreenUpdateAction {
    ultramodern::renderer::ViRegs regs;
};

struct UpdateConfigAction {
};

using Action = std::variant<SpTaskAction, ScreenUpdateAction, UpdateConfigAction>;

struct ViState {
    const OSViMode* mode;
    PTR(void) framebuffer;
    PTR(OSMesg) mq;
    OSMesg msg;
    uint32_t state;
    uint32_t control;
    int retrace_count = 1;
};

#define VI_STATE_BLACK 0x20
#define VI_STATE_REPEATLINE 0x40

static struct {
    struct {
        std::thread thread;
        int cur_state;
        int field;
        ViState states[2];
        ultramodern::renderer::ViRegs regs;
        ultramodern::renderer::ViRegs update_screen_regs;

        ViState* get_next_state() {
            return &states[cur_state ^ 1];
        }
        ViState* get_cur_state() {
            return &states[cur_state];
        }
        void update_vi() {
            ViState* next_state = get_next_state();
            const OSViMode* next_mode = next_state->mode;
            const OSViCommonRegs* common_regs = &next_mode->comRegs;
            const OSViFieldRegs* field_regs = &next_mode->fldRegs[field];
            PTR(void) framebuffer = osVirtualToPhysical(next_state->framebuffer);
            PTR(void) origin = framebuffer + field_regs->origin;

            // Fold the software VI flags into the values being staged. A black screen
            // is produced by forcing the horizontal start to zero.
            uint32_t hStart = common_regs->hStart;
            if (next_state->state & VI_STATE_BLACK) {
                hStart = 0;
            }

            uint32_t yScale = field_regs->yScale;
            if (next_state->state & VI_STATE_REPEATLINE) {
                // libultra implements osViRepeatLine by writing a zero VI_Y_SCALE
                // and pointing VI_ORIGIN at the framebuffer start. RT64 treats a
                // zero y scale as a zero-height VI, so preserve the normal scale
                // until repeated-scanline presentation is implemented there.
                origin = framebuffer;
            }

            // TODO implement osViFade

            // Stage the VI register block for this field from the active mode.
            regs.VI_ORIGIN_REG = origin;
            regs.VI_WIDTH_REG = common_regs->width;
            regs.VI_TIMING_REG = common_regs->burst;
            regs.VI_V_SYNC_REG = common_regs->vSync;
            regs.VI_H_SYNC_REG = common_regs->hSync;
            regs.VI_LEAP_REG = common_regs->leap;
            regs.VI_H_START_REG = hStart;
            regs.VI_V_START_REG = field_regs->vStart; // TODO implement osViExtendVStart
            regs.VI_V_BURST_REG = field_regs->vBurst;
            regs.VI_INTR_REG = field_regs->vIntr;
            regs.VI_X_SCALE_REG = common_regs->xScale; // TODO implement osViSetXScale
            regs.VI_Y_SCALE_REG = yScale; // TODO implement osViSetYScale
            regs.VI_STATUS_REG = next_state->control;

            // Flip to the freshly-staged state and seed the new "next" from it.
            cur_state ^= 1;
            *get_next_state() = *get_cur_state();
        }
    } vi;
    struct {
        std::thread gfx_thread;
        std::thread task_thread;
        PTR(OSMesgQueue) mq = NULLPTR;
        OSMesg msg = (OSMesg)0;
    } sp;
    struct {
        PTR(OSMesgQueue) mq = NULLPTR;
        OSMesg msg = (OSMesg)0;
    } dp;
    struct {
        PTR(OSMesgQueue) mq = NULLPTR;
        OSMesg msg = (OSMesg)0;
    } ai;
    struct {
        PTR(OSMesgQueue) mq = NULLPTR;
        OSMesg msg = (OSMesg)0;
    } si;
    // One mutex guards every event slot, since a game may register the same queue
    // for more than one event.
    std::mutex message_mutex;
    uint8_t* rdram;
    moodycamel::BlockingConcurrentQueue<Action> action_queue{};
    moodycamel::BlockingConcurrentQueue<OSTask*> sp_task_queue{};
    moodycamel::ConcurrentQueue<OSThread*> deleted_threads{};
} events_context{};

ultramodern::renderer::ViRegs* ultramodern::renderer::get_vi_regs() {
    return &events_context.vi.update_screen_regs;
}

extern "C" void osSetEventMesg(RDRAM_ARG OSEvent event_id, PTR(OSMesgQueue) mq_, OSMesg msg) {
    std::lock_guard lock{ events_context.message_mutex };

    switch (event_id) {
        case OS_EVENT_SP:
            events_context.sp.msg = msg;
            events_context.sp.mq = mq_;
            break;
        case OS_EVENT_DP:
            events_context.dp.msg = msg;
            events_context.dp.mq = mq_;
            break;
        case OS_EVENT_AI:
            events_context.ai.msg = msg;
            events_context.ai.mq = mq_;
            break;
        case OS_EVENT_SI:
            events_context.si.msg = msg;
            events_context.si.mq = mq_;
    }
}

// Observability: expose the message-queue addresses registered for hardware
// events (osSetEventMesg / osViSetEvent). Lets a probe correlate a parked
// thread's blocked_on_recv queue against the SP/DP/AI/SI/VI event whose
// producer it is waiting on -> identifies which hardware-event delivery died.
// Order: [0]=SP [1]=DP [2]=AI [3]=SI [4]=VI(retrace).
extern "C" void ultramodern_get_event_queues(uint32_t* out, int count) {
    if (count > 0) out[0] = (uint32_t)events_context.sp.mq;
    if (count > 1) out[1] = (uint32_t)events_context.dp.mq;
    if (count > 2) out[2] = (uint32_t)events_context.ai.mq;
    if (count > 3) out[3] = (uint32_t)events_context.si.mq;
    if (count > 4) out[4] = (uint32_t)events_context.vi.get_cur_state()->mq;
}

extern "C" void osViSetEvent(RDRAM_ARG PTR(OSMesgQueue) mq_, OSMesg msg, u32 retrace_count) {
    std::lock_guard lock{ events_context.message_mutex };
    ViState* next_state = events_context.vi.get_next_state();
    next_state->mq = mq_;
    next_state->msg = msg;
    next_state->retrace_count = retrace_count;
}

uint64_t total_vis = 0;

#ifdef N64_COSIM
void set_dummy_vi(bool odd);
extern std::atomic_bool exited;

extern "C" int psr_cosim_on_quiescent_vi(
    uint8_t* rdram,
    const ultramodern_cosim_quiescence_state* state);

void sp_complete(uint32_t task_type);
void dp_complete(uint32_t task_type);

static int cosim_remaining_retraces = 1;
static bool cosim_dummy_odd = false;
static std::mutex cosim_vi_token_mutex;
static std::condition_variable cosim_vi_token_cv;
static uint32_t cosim_vi_tokens = 0;
static uint64_t cosim_next_vi_cycle = 0;
static bool cosim_vi_needs_rebase = true;
static std::atomic<uint32_t> cosim_vi_control_enabled{0};

enum class CosimRcpEventKind : uint8_t {
    SpComplete,
    DpComplete,
    ViRetrace,
    AiEvent,
};

struct CosimRcpEvent {
    uint64_t due_cycle;
    uint64_t seq;
    uint64_t gfx_seq;
    uint32_t task_type;
    PTR(OSMesgQueue) mq;
    OSMesg msg;
    CosimRcpEventKind kind;
};

constexpr uint64_t kCosimGfxSpDelay = 512;
constexpr uint64_t kCosimGfxDpDelay = 4096;
constexpr uint64_t kCosimRspSpDelay = 2048;
constexpr uint64_t kCosimCounterPerMs = 46875;
constexpr uint64_t kCosimCounterPerVi = kCosimCounterPerMs * 1000u / 60u;

static uint64_t cosim_delay_from_env(const char* name, uint64_t dflt) {
    const char* raw = std::getenv(name);
    if (raw == nullptr || *raw == '\0') {
        return dflt;
    }
    char* end = nullptr;
    const uint64_t value = std::strtoull(raw, &end, 0);
    return end != raw ? value : dflt;
}

static uint64_t cosim_gfx_sp_delay() {
    static const uint64_t value =
        cosim_delay_from_env("PSR_COSIM_GFX_SP_DELAY", kCosimGfxSpDelay);
    return value;
}

static uint64_t cosim_gfx_dp_delay() {
    static const uint64_t value =
        cosim_delay_from_env("PSR_COSIM_GFX_DP_DELAY", kCosimGfxDpDelay);
    return value;
}

static uint64_t cosim_rsp_sp_delay() {
    static const uint64_t value =
        cosim_delay_from_env("PSR_COSIM_RSP_SP_DELAY", kCosimRspSpDelay);
    return value;
}

static std::mutex cosim_rcp_mutex;
static std::vector<CosimRcpEvent> cosim_rcp_events;
static std::atomic<uint64_t> cosim_rcp_next_seq{0};
static std::atomic<uint64_t> cosim_gfx_next_seq{0};
static std::atomic<uint64_t> cosim_gfx_rendered_seq{0};
static std::atomic<uint32_t> cosim_vi_advancing{0};
static std::atomic<uint64_t> cosim_scheduled_sp{0};
static std::atomic<uint64_t> cosim_scheduled_dp{0};
static std::atomic<uint64_t> cosim_scheduled_vi{0};
static std::atomic<uint64_t> cosim_scheduled_ai{0};
static std::atomic<uint64_t> cosim_scheduled_sp_gfx{0};
static std::atomic<uint64_t> cosim_scheduled_sp_audio{0};
static std::atomic<uint64_t> cosim_scheduled_sp_other{0};
static std::atomic<uint64_t> cosim_delivered_sp{0};
static std::atomic<uint64_t> cosim_delivered_dp{0};
static std::atomic<uint64_t> cosim_delivered_vi{0};
static std::atomic<uint64_t> cosim_delivered_ai{0};
static std::atomic<uint64_t> cosim_delivered_sp_gfx{0};
static std::atomic<uint64_t> cosim_delivered_sp_audio{0};
static std::atomic<uint64_t> cosim_delivered_sp_other{0};

static void cosim_count_sp_task_type(
    uint32_t task_type,
    std::atomic<uint64_t>& gfx,
    std::atomic<uint64_t>& audio,
    std::atomic<uint64_t>& other)
{
    if (task_type == M_GFXTASK) {
        gfx.fetch_add(1, std::memory_order_relaxed);
    } else if (task_type == M_AUDTASK) {
        audio.fetch_add(1, std::memory_order_relaxed);
    } else {
        other.fetch_add(1, std::memory_order_relaxed);
    }
}

static void cosim_count_scheduled(CosimRcpEventKind kind, uint32_t task_type = 0) {
    switch (kind) {
        case CosimRcpEventKind::SpComplete:
            cosim_scheduled_sp.fetch_add(1, std::memory_order_relaxed);
            cosim_count_sp_task_type(
                task_type,
                cosim_scheduled_sp_gfx,
                cosim_scheduled_sp_audio,
                cosim_scheduled_sp_other);
            break;
        case CosimRcpEventKind::DpComplete:
            cosim_scheduled_dp.fetch_add(1, std::memory_order_relaxed);
            break;
        case CosimRcpEventKind::ViRetrace:
            cosim_scheduled_vi.fetch_add(1, std::memory_order_relaxed);
            break;
        case CosimRcpEventKind::AiEvent:
            cosim_scheduled_ai.fetch_add(1, std::memory_order_relaxed);
            break;
    }
}

static void cosim_count_delivered(const CosimRcpEvent& ev) {
    switch (ev.kind) {
        case CosimRcpEventKind::SpComplete:
            cosim_delivered_sp.fetch_add(1, std::memory_order_relaxed);
            cosim_count_sp_task_type(
                ev.task_type,
                cosim_delivered_sp_gfx,
                cosim_delivered_sp_audio,
                cosim_delivered_sp_other);
            break;
        case CosimRcpEventKind::DpComplete:
            cosim_delivered_dp.fetch_add(1, std::memory_order_relaxed);
            break;
        case CosimRcpEventKind::ViRetrace:
            cosim_delivered_vi.fetch_add(1, std::memory_order_relaxed);
            break;
        case CosimRcpEventKind::AiEvent:
            cosim_delivered_ai.fetch_add(1, std::memory_order_relaxed);
            break;
    }
}

static uint32_t cosim_vi_queue_locked() {
    ViState* cur = events_context.vi.get_cur_state();
    ViState* next = events_context.vi.get_next_state();
    if (cur->mq != NULLPTR) {
        return static_cast<uint32_t>(cur->mq);
    }
    return static_cast<uint32_t>(next->mq);
}

extern "C" void ultramodern_cosim_get_quiescence(
    ultramodern_cosim_quiescence_state* out)
{
    if (out == nullptr) {
        return;
    }
    uint32_t vi_queue = 0;
    {
        std::lock_guard lock{ events_context.message_mutex };
        vi_queue = cosim_vi_queue_locked();
    }
    ultramodern_cosim_thread_quiescence(events_context.rdram, vi_queue, out);
}

extern "C" uint32_t ultramodern_cosim_request_vi(uint32_t count) {
    if (count == 0 || !ultramodern::is_game_started()) {
        return 0;
    }
    {
        std::lock_guard lock{ cosim_vi_token_mutex };
        if (cosim_vi_needs_rebase) {
            total_vis = 0;
            cosim_remaining_retraces = 1;
            cosim_next_vi_cycle = kCosimCounterPerVi;
            cosim_vi_needs_rebase = false;
        }
        const uint32_t room = UINT32_MAX - cosim_vi_tokens;
        const uint32_t accepted = count > room ? room : count;
        cosim_vi_tokens += accepted;
        count = accepted;
    }
    cosim_vi_token_cv.notify_all();
    return count;
}

extern "C" void ultramodern_cosim_reset_vi_counter(void) {
    {
        std::lock_guard lock{ cosim_vi_token_mutex };
        cosim_vi_tokens = 0;
        cosim_vi_needs_rebase = true;
    }
    cosim_vi_control_enabled.store(1, std::memory_order_release);
    total_vis = 0;
    cosim_remaining_retraces = 1;
    cosim_next_vi_cycle = kCosimCounterPerVi;
    cosim_vi_token_cv.notify_all();
}

static void cosim_schedule_rcp_event(
    CosimRcpEventKind kind,
    uint32_t task_type,
    uint64_t delay,
    uint64_t gfx_seq = 0)
{
    const uint64_t now = ultramodern_cosim_get_time_ticks();
    const uint64_t seq = cosim_rcp_next_seq.fetch_add(1, std::memory_order_relaxed);
    const uint64_t due = now + delay;
    {
        std::lock_guard lock{ cosim_rcp_mutex };
        cosim_rcp_events.push_back(CosimRcpEvent{ due, seq, gfx_seq, task_type, NULLPTR, 0, kind });
    }
    cosim_count_scheduled(kind, task_type);
    recomp_ultra_trace_record(
        kind == CosimRcpEventKind::SpComplete ? "~cosim_sp_due" : "~cosim_dp_due",
        0,
        static_cast<uint32_t>(due),
        static_cast<uint32_t>(due >> 32),
        task_type,
        static_cast<uint32_t>(seq));
}

static void cosim_schedule_queue_event(
    CosimRcpEventKind kind,
    PTR(OSMesgQueue) mq,
    OSMesg msg,
    uint64_t delay)
{
    if (mq == NULLPTR) {
        return;
    }
    const uint64_t now = ultramodern_cosim_get_time_ticks();
    const uint64_t seq = cosim_rcp_next_seq.fetch_add(1, std::memory_order_relaxed);
    const uint64_t due = now + delay;
    {
        std::lock_guard lock{ cosim_rcp_mutex };
        cosim_rcp_events.push_back(CosimRcpEvent{ due, seq, 0, 0, mq, msg, kind });
    }
    cosim_count_scheduled(kind);
    recomp_ultra_trace_record(
        kind == CosimRcpEventKind::ViRetrace ? "~cosim_vi_due" : "~cosim_ai_due",
        0,
        static_cast<uint32_t>(due),
        static_cast<uint32_t>(due >> 32),
        static_cast<uint32_t>(mq),
        static_cast<uint32_t>(seq));
}

static bool cosim_pop_due_rcp_event(uint64_t now, CosimRcpEvent& out) {
    std::lock_guard lock{ cosim_rcp_mutex };
    size_t best = cosim_rcp_events.size();
    for (size_t i = 0; i < cosim_rcp_events.size(); i++) {
        const CosimRcpEvent& ev = cosim_rcp_events[i];
        if (ev.due_cycle > now) {
            continue;
        }
        if (best == cosim_rcp_events.size() ||
            ev.due_cycle < cosim_rcp_events[best].due_cycle ||
            (ev.due_cycle == cosim_rcp_events[best].due_cycle &&
             ev.seq < cosim_rcp_events[best].seq)) {
            best = i;
        }
    }
    if (best == cosim_rcp_events.size()) {
        return false;
    }
    const CosimRcpEvent& best_ev = cosim_rcp_events[best];
    if (best_ev.kind == CosimRcpEventKind::DpComplete &&
        best_ev.gfx_seq != 0 &&
        cosim_gfx_rendered_seq.load(std::memory_order_acquire) < best_ev.gfx_seq) {
        return false;
    }
    out = cosim_rcp_events[best];
    cosim_rcp_events.erase(cosim_rcp_events.begin() + static_cast<std::ptrdiff_t>(best));
    return true;
}

static bool cosim_next_rcp_due(uint64_t& out) {
    std::lock_guard lock{ cosim_rcp_mutex };
    if (cosim_rcp_events.empty()) {
        return false;
    }
    uint64_t best = cosim_rcp_events[0].due_cycle;
    uint64_t best_seq = cosim_rcp_events[0].seq;
    for (const CosimRcpEvent& ev : cosim_rcp_events) {
        if (ev.due_cycle < best ||
            (ev.due_cycle == best && ev.seq < best_seq)) {
            best = ev.due_cycle;
            best_seq = ev.seq;
        }
    }
    out = best;
    return true;
}

static bool cosim_next_vi_due(uint64_t& out) {
    if (cosim_vi_control_enabled.load(std::memory_order_acquire) == 0 ||
        !ultramodern::is_game_started()) {
        return false;
    }

    std::lock_guard lock{ cosim_vi_token_mutex };
    if (cosim_vi_tokens == 0) {
        return false;
    }
    out = cosim_vi_needs_rebase ? kCosimCounterPerVi : cosim_next_vi_cycle;
    return true;
}

extern "C" void ultramodern_cosim_reset_rcp_events(void) {
    {
        std::lock_guard lock{ cosim_rcp_mutex };
        cosim_rcp_events.clear();
    }
    cosim_rcp_next_seq.store(0, std::memory_order_relaxed);
    cosim_gfx_next_seq.store(0, std::memory_order_relaxed);
    cosim_gfx_rendered_seq.store(0, std::memory_order_release);
    cosim_vi_advancing.store(0, std::memory_order_release);
    cosim_scheduled_sp.store(0, std::memory_order_relaxed);
    cosim_scheduled_dp.store(0, std::memory_order_relaxed);
    cosim_scheduled_vi.store(0, std::memory_order_relaxed);
    cosim_scheduled_ai.store(0, std::memory_order_relaxed);
    cosim_scheduled_sp_gfx.store(0, std::memory_order_relaxed);
    cosim_scheduled_sp_audio.store(0, std::memory_order_relaxed);
    cosim_scheduled_sp_other.store(0, std::memory_order_relaxed);
    cosim_delivered_sp.store(0, std::memory_order_relaxed);
    cosim_delivered_dp.store(0, std::memory_order_relaxed);
    cosim_delivered_vi.store(0, std::memory_order_relaxed);
    cosim_delivered_ai.store(0, std::memory_order_relaxed);
    cosim_delivered_sp_gfx.store(0, std::memory_order_relaxed);
    cosim_delivered_sp_audio.store(0, std::memory_order_relaxed);
    cosim_delivered_sp_other.store(0, std::memory_order_relaxed);
}

extern "C" uint32_t ultramodern_cosim_rcp_event_pending(void) {
    if (cosim_vi_advancing.load(std::memory_order_acquire) != 0) {
        return 1;
    }
    std::lock_guard lock{ cosim_rcp_mutex };
    return cosim_rcp_events.empty() ? 0u : 1u;
}

static bool cosim_vi_due_now() {
    if (cosim_vi_control_enabled.load(std::memory_order_acquire) == 0 ||
        !ultramodern::is_game_started()) {
        return false;
    }

    std::lock_guard lock{ cosim_vi_token_mutex };
    if (cosim_vi_tokens == 0) {
        return false;
    }
    const uint64_t due = cosim_vi_needs_rebase ? kCosimCounterPerVi : cosim_next_vi_cycle;
    return ultramodern_cosim_get_time_ticks() >= due;
}

extern "C" uint32_t ultramodern_cosim_rcp_event_due(void) {
    if (cosim_vi_advancing.load(std::memory_order_acquire) != 0) {
        return 1;
    }
    if (cosim_vi_due_now()) {
        return 1;
    }

    const uint64_t now = ultramodern_cosim_get_time_ticks();
    std::lock_guard lock{ cosim_rcp_mutex };
    for (const CosimRcpEvent& ev : cosim_rcp_events) {
        if (ev.due_cycle > now) {
            continue;
        }
        if (ev.kind == CosimRcpEventKind::DpComplete &&
            ev.gfx_seq != 0 &&
            cosim_gfx_rendered_seq.load(std::memory_order_acquire) < ev.gfx_seq) {
            continue;
        }
        return 1;
    }
    return 0;
}

extern "C" uint32_t ultramodern_cosim_deliver_due_rcp_events(uint8_t* rdram) {
    uint32_t delivered = 0;
    for (;;) {
        CosimRcpEvent ev{};
        if (!cosim_pop_due_rcp_event(ultramodern_cosim_get_time_ticks(), ev)) {
            return delivered;
        }
        if (ev.kind == CosimRcpEventKind::SpComplete) {
            sp_complete(ev.task_type);
        } else if (ev.kind == CosimRcpEventKind::DpComplete) {
            dp_complete(ev.task_type);
        } else if (ev.kind == CosimRcpEventKind::ViRetrace) {
            s32 sent = ultramodern::post_rcp_event(PASS_RDRAM ev.mq, ev.msg, /*coalescible=*/true);
            recomp_ultra_trace_record("~vi_retrace", 0,
                (uint32_t)ev.mq, (uint32_t)ev.msg, (uint32_t)sent, 0);
        } else {
            s32 sent = ultramodern::post_rcp_event(PASS_RDRAM ev.mq, ev.msg, /*coalescible=*/false);
            recomp_ultra_trace_record("~ai_event", 0,
                (uint32_t)ev.mq, (uint32_t)ev.msg, (uint32_t)sent, 0);
        }
        cosim_count_delivered(ev);
        delivered++;
    }
}

extern "C" void ultramodern_cosim_get_rcp_event_stats(ultramodern_cosim_rcp_event_stats* out) {
    if (out == nullptr) {
        return;
    }
    std::memset(out, 0, sizeof(*out));
    out->now_cycle = ultramodern_cosim_get_time_ticks();
    out->next_seq = cosim_rcp_next_seq.load(std::memory_order_relaxed);
    out->scheduled_sp = cosim_scheduled_sp.load(std::memory_order_relaxed);
    out->scheduled_dp = cosim_scheduled_dp.load(std::memory_order_relaxed);
    out->scheduled_vi = cosim_scheduled_vi.load(std::memory_order_relaxed);
    out->scheduled_ai = cosim_scheduled_ai.load(std::memory_order_relaxed);
    out->scheduled_sp_gfx = cosim_scheduled_sp_gfx.load(std::memory_order_relaxed);
    out->scheduled_sp_audio = cosim_scheduled_sp_audio.load(std::memory_order_relaxed);
    out->scheduled_sp_other = cosim_scheduled_sp_other.load(std::memory_order_relaxed);
    out->delivered_sp = cosim_delivered_sp.load(std::memory_order_relaxed);
    out->delivered_dp = cosim_delivered_dp.load(std::memory_order_relaxed);
    out->delivered_vi = cosim_delivered_vi.load(std::memory_order_relaxed);
    out->delivered_ai = cosim_delivered_ai.load(std::memory_order_relaxed);
    out->delivered_sp_gfx = cosim_delivered_sp_gfx.load(std::memory_order_relaxed);
    out->delivered_sp_audio = cosim_delivered_sp_audio.load(std::memory_order_relaxed);
    out->delivered_sp_other = cosim_delivered_sp_other.load(std::memory_order_relaxed);
    out->vi_advancing = cosim_vi_advancing.load(std::memory_order_acquire);

    std::lock_guard lock{ cosim_rcp_mutex };
    for (const CosimRcpEvent& ev : cosim_rcp_events) {
        out->pending_total++;
        if (!out->has_next_due || ev.due_cycle < out->next_due_cycle) {
            out->next_due_cycle = ev.due_cycle;
            out->has_next_due = 1;
        }
        switch (ev.kind) {
            case CosimRcpEventKind::SpComplete:
                out->pending_sp++;
                if (ev.task_type == M_GFXTASK) {
                    out->pending_sp_gfx++;
                } else if (ev.task_type == M_AUDTASK) {
                    out->pending_sp_audio++;
                } else {
                    out->pending_sp_other++;
                }
                break;
            case CosimRcpEventKind::DpComplete:
                out->pending_dp++;
                break;
            case CosimRcpEventKind::ViRetrace:
                out->pending_vi++;
                break;
            case CosimRcpEventKind::AiEvent:
                out->pending_ai++;
                break;
        }
    }
}

extern "C" uint32_t ultramodern_cosim_advance_to_next_rcp_event(uint8_t* rdram) {
    uint32_t delivered = ultramodern_cosim_advance_due_vi(rdram, 0);
    delivered += ultramodern_cosim_deliver_due_rcp_events(rdram);
    if (delivered != 0) {
        return delivered;
    }

    uint64_t rcp_due = 0;
    const bool has_rcp_due = cosim_next_rcp_due(rcp_due);
    uint64_t vi_due = 0;
    const bool has_vi_due = cosim_next_vi_due(vi_due);
    if (!has_rcp_due && !has_vi_due) {
        return 0;
    }

    const uint64_t now = ultramodern_cosim_get_time_ticks();
    if (has_vi_due && (!has_rcp_due || vi_due <= rcp_due)) {
        if (vi_due > now) {
            ultramodern_cosim_advance_time_ticks(vi_due - now);
        }
        return ultramodern_cosim_advance_due_vi(rdram, 0);
    }

    if (rcp_due > now) {
        ultramodern_cosim_advance_time_ticks(rcp_due - now);
    }
    return ultramodern_cosim_deliver_due_rcp_events(rdram);
}

static bool ultramodern_cosim_wait_vi_token() {
    using namespace std::chrono_literals;
    std::unique_lock lock{ cosim_vi_token_mutex };
    while (!exited.load(std::memory_order_relaxed) && cosim_vi_tokens == 0) {
        cosim_vi_token_cv.wait_for(lock, 1ms);
    }
    if (exited.load(std::memory_order_relaxed)) {
        return false;
    }
    cosim_vi_tokens--;
    return true;
}

static void ultramodern_cosim_advance_vi(uint8_t* rdram) {
    cosim_vi_advancing.store(1, std::memory_order_release);
    total_vis++;

    ViState* next_state = events_context.vi.get_next_state();
    if (next_state->mode == nullptr) {
        set_dummy_vi(cosim_dummy_odd);
        cosim_dummy_odd = !cosim_dummy_odd;
    }

    events_context.action_queue.enqueue(ScreenUpdateAction{ events_context.vi.regs });
    events_context.vi.update_vi();

    {
        std::lock_guard lock{ events_context.message_mutex };
        ViState* cur_state = events_context.vi.get_cur_state();
        cosim_remaining_retraces--;
        if (cosim_remaining_retraces <= 0) {
            if (cur_state->mq != NULLPTR) {
                cosim_schedule_queue_event(
                    CosimRcpEventKind::ViRetrace,
                    cur_state->mq,
                    cur_state->msg,
                    0);
            }
            cosim_remaining_retraces = cur_state->retrace_count > 0
                ? cur_state->retrace_count
                : 1;
        }
        if (events_context.ai.mq != NULLPTR) {
            cosim_schedule_queue_event(
                CosimRcpEventKind::AiEvent,
                events_context.ai.mq,
                events_context.ai.msg,
                0);
        }
    }

    if (events_callbacks.vi_callback != nullptr) {
        events_callbacks.vi_callback();
    }
    cosim_vi_advancing.store(0, std::memory_order_release);
}

extern "C" uint32_t ultramodern_cosim_advance_due_vi(uint8_t* rdram, uint32_t allow_time_advance) {
    if (cosim_vi_control_enabled.load(std::memory_order_acquire) == 0 ||
        !ultramodern::is_game_started()) {
        return 0;
    }

    {
        std::lock_guard lock{ cosim_vi_token_mutex };
        if (cosim_vi_needs_rebase) {
            total_vis = 0;
            cosim_remaining_retraces = 1;
            cosim_next_vi_cycle = kCosimCounterPerVi;
            cosim_vi_needs_rebase = false;
        }
        if (cosim_vi_tokens == 0) {
            return 0;
        }
    }

    const uint64_t now = ultramodern_cosim_get_time_ticks();
    uint64_t due = 0;
    {
        std::lock_guard lock{ cosim_vi_token_mutex };
        due = cosim_next_vi_cycle;
    }
    if (now < due) {
        if (allow_time_advance == 0) {
            return 0;
        }
        ultramodern_cosim_advance_time_ticks(due - now);
    }

    {
        std::lock_guard lock{ cosim_vi_token_mutex };
        if (cosim_vi_tokens == 0) {
            return 0;
        }
        const uint64_t cur = ultramodern_cosim_get_time_ticks();
        if (cur < cosim_next_vi_cycle) {
            return 0;
        }
        cosim_vi_tokens--;
        cosim_next_vi_cycle += kCosimCounterPerVi;
    }

    uint8_t* target_rdram = rdram != nullptr ? rdram : events_context.rdram;
    ultramodern_cosim_advance_vi(target_rdram);
    return 1 + ultramodern_cosim_deliver_due_rcp_events(target_rdram);
}

extern "C" void ultramodern_cosim_check_vi_quiescence(uint8_t* rdram) {
    ultramodern_cosim_quiescence_state state{};
    ultramodern_cosim_get_quiescence(&state);
    if (state.quiescent) {
        (void)psr_cosim_on_quiescent_vi(rdram, &state);
    }
}
#endif


extern std::atomic_bool exited;
extern moodycamel::LightweightSemaphore graphics_shutdown_ready;

void set_dummy_vi(bool odd);

void vi_thread_func() {
    ultramodern::set_native_thread_name("VI Thread");
    // Run above every other thread: this thread's cadence is what keeps the game
    // producing fresh audio and graphics lists.
    ultramodern::set_native_thread_priority(ultramodern::ThreadPriority::Critical);
    using namespace std::chrono_literals;

    int remaining_retraces = 1;

    while (!exited) {
#ifdef N64_COSIM
        if (cosim_vi_control_enabled.load(std::memory_order_acquire) != 0) {
            std::this_thread::sleep_for(1ms);
            continue;
        }
#endif
        // Derive the absolute time of the next VI from the running VI count instead of
        // adding a fixed step each interrupt, which keeps long-term drift bounded.
        auto next = ultramodern::get_start() + (total_vis * 1000000us) / (60 * ultramodern::get_speed_multiplier());
        // A target more than a second away almost always means the host clock jumped
        // backward; in that case fire immediately rather than stalling for ages.
        if (std::chrono::floor<std::chrono::seconds>(next - std::chrono::high_resolution_clock::now()) > 1s) {
            next = std::chrono::high_resolution_clock::now();
        }
        ultramodern::sleep_until(next);
        auto time_now = ultramodern::time_since_start();
        // Re-derive the VI count from elapsed time; one tick can span several VIs if
        // the host fell behind.
        uint64_t new_total_vis = (time_now * (60 * ultramodern::get_speed_multiplier()) / 1000ms) + 1;
        total_vis = new_total_vis;

        // If the game hasn't started yet, OR has been marked started but
        // hasn't yet called osViSetMode (mode pointer still null), install
        // a dummy VI mode. The original guard (only when !is_game_started)
        // was racy: a runner that sets game_status=Running BEFORE the
        // game thread reaches its first osViSetMode call would leave
        // next_state->mode==NULL and crash update_vi() at the
        // &next_state->mode->comRegs deref.
        {
            static bool odd = false;
            ViState* next_state = events_context.vi.get_next_state();
            if (!ultramodern::is_game_started() || next_state->mode == nullptr) {
                set_dummy_vi(odd);
                odd = !odd;
            }
        }

        // Hand the current VI register state to the graphics thread as a screen update.
        // Issuing it before update_vi() matches presenting the previous frame once its
        // scanout has finished.
        events_context.action_queue.enqueue(ScreenUpdateAction{ events_context.vi.regs });

        // Advance the VI registers and flip to the next field/state.
        events_context.vi.update_vi();

        // If the game has started, handle sending VI and AI events.
        if (ultramodern::is_game_started()) {
            remaining_retraces--;

            uint8_t* rdram = events_context.rdram;
            std::lock_guard lock{ events_context.message_mutex };
            ViState* cur_state = events_context.vi.get_cur_state();
            if (remaining_retraces == 0) {
                if (cur_state->mq != NULLPTR) {
                    // VI retrace is COALESCIBLE: droppable on a full guest queue.
                    // This is what stops a 60Hz retrace flood from starving the
                    // SP/DP gfx-completion events when a game shares one queue for
                    // OS_EVENT_SP/DP/VI (the boot lost-wakeup). See post_rcp_event.
                    s32 sent = ultramodern::post_rcp_event(PASS_RDRAM cur_state->mq, cur_state->msg, /*coalescible=*/true);
                    // Always-on ring: runtime→guest VI retrace delivery (a2 = 0
                    // when posted; the drop, if any, happens later in the external
                    // drain and shows as OP_EXT_DEQ_DROP). See ultra_trace.hpp.
                    recomp_ultra_trace_record("~vi_retrace", 0,
                        (uint32_t)cur_state->mq, (uint32_t)cur_state->msg, (uint32_t)sent, 0);
                }
                remaining_retraces = cur_state->retrace_count;
            }
            if (events_context.ai.mq != NULLPTR) {
                // AI (audio DMA) completion is RELIABLE (never dropped).
                s32 sent = ultramodern::post_rcp_event(PASS_RDRAM events_context.ai.mq, events_context.ai.msg, /*coalescible=*/false);
                recomp_ultra_trace_record("~ai_event", 0,
                    (uint32_t)events_context.ai.mq, (uint32_t)events_context.ai.msg, (uint32_t)sent, 0);
            }
        }

        if (events_callbacks.vi_callback != nullptr) {
            events_callbacks.vi_callback();
        }
    }
}

// Counters at the renderer-thread side, paired with the submit_gfx
// counter at the recomp side. Stadium gates its gfx slot state
// machine on RDP-complete (unk_1E -> 2). If dp_complete_count <
// submit_gfx_count after a freeze, the renderer never finished a
// queued gfx task — i.e., RT64 stalled inside processDisplayLists.
static std::atomic<uint64_t> g_sp_complete_count{0};
static std::atomic<uint64_t> g_dp_complete_count{0};
extern "C" uint64_t ultramodern_sp_complete_count(void) { return g_sp_complete_count.load(); }
extern "C" uint64_t ultramodern_dp_complete_count(void) { return g_dp_complete_count.load(); }

// Gfx-DL in-flight tracker. Stamped before/after the BLOCKING call to
// renderer_context->send_dl() in the gfx event thread. If a DL hangs
// inside the renderer (RT64's processDisplayLists), g_current_dl_entry_seq
// > g_current_dl_exit_seq, and the stamped data_ptr/data_size identify
// exactly which DL is stuck — without needing to scrape the SP task ring
// (which can be overwhelmed by audio task submissions during a long hang).
//
// All atomics for lock-free read from the debug-server thread. data_ptr
// and data_size are stamped under the gfx-thread-only invariant that
// only ONE send_dl runs at a time, so there is no torn-read concern.
static std::atomic<uint64_t> g_current_dl_entry_seq{0};
static std::atomic<uint64_t> g_current_dl_exit_seq{0};
static std::atomic<uint64_t> g_current_dl_entry_ms{0};
static std::atomic<uint64_t> g_current_dl_exit_ms{0};
static std::atomic<uint32_t> g_current_dl_data_ptr{0};
static std::atomic<uint32_t> g_current_dl_data_size{0};
static std::atomic<uint32_t> g_current_dl_ucode_ptr{0};

extern "C" void recomp_rsp_mark_sp_task_complete(uint8_t* rdram, uint32_t task_type);

extern "C" void ultramodern_get_current_dl_state(
    uint64_t* entry_seq, uint64_t* exit_seq,
    uint64_t* entry_ms,  uint64_t* exit_ms,
    uint32_t* data_ptr,  uint32_t* data_size,
    uint32_t* ucode_ptr)
{
    if (entry_seq) *entry_seq = g_current_dl_entry_seq.load();
    if (exit_seq)  *exit_seq  = g_current_dl_exit_seq.load();
    if (entry_ms)  *entry_ms  = g_current_dl_entry_ms.load();
    if (exit_ms)   *exit_ms   = g_current_dl_exit_ms.load();
    if (data_ptr)  *data_ptr  = g_current_dl_data_ptr.load();
    if (data_size) *data_size = g_current_dl_data_size.load();
    if (ucode_ptr) *ucode_ptr = g_current_dl_ucode_ptr.load();
}

extern "C" void ultramodern_get_vi_debug_state(
    uint32_t* cur_flags, uint32_t* next_flags,
    uint32_t* cur_fb,    uint32_t* next_fb,
    uint32_t* origin,    uint32_t* h_start,
    uint32_t* y_scale,   uint32_t* status)
{
    std::lock_guard lock{ events_context.message_mutex };
    ViState* cur = events_context.vi.get_cur_state();
    ViState* next = events_context.vi.get_next_state();
    if (cur_flags)  *cur_flags = cur->state;
    if (next_flags) *next_flags = next->state;
    if (cur_fb)     *cur_fb = cur->framebuffer;
    if (next_fb)    *next_fb = next->framebuffer;
    if (origin)     *origin = events_context.vi.regs.VI_ORIGIN_REG;
    if (h_start)    *h_start = events_context.vi.regs.VI_H_START_REG;
    if (y_scale)    *y_scale = events_context.vi.regs.VI_Y_SCALE_REG;
    if (status)     *status = events_context.vi.regs.VI_STATUS_REG;
}

void sp_complete(uint32_t task_type) {
    uint8_t* rdram = events_context.rdram;
    recomp_rsp_mark_sp_task_complete(rdram, task_type);

    std::lock_guard lock{ events_context.message_mutex };
    // SP task completion is RELIABLE: it releases the gfx task in osScheduler.
    // Losing it lost-wakeups the pipeline, so it is never dropped (re-queued
    // until delivered) even if VI floods the shared queue. See post_rcp_event.
    s32 sent = ultramodern::post_rcp_event(PASS_RDRAM events_context.sp.mq, events_context.sp.msg, /*coalescible=*/false);
    recomp_ultra_trace_record("~sp_done", 0,
        (uint32_t)events_context.sp.mq, (uint32_t)events_context.sp.msg, (uint32_t)sent, task_type);
    g_sp_complete_count.fetch_add(1, std::memory_order_relaxed);
}

void dp_complete(uint32_t task_type) {
    uint8_t* rdram = events_context.rdram;
    recomp_rsp_mark_sp_task_complete(rdram, task_type);

    std::lock_guard lock{ events_context.message_mutex };
    // DP (RDP FullSync) completion is RELIABLE — same reasoning as SP above.
    s32 sent = ultramodern::post_rcp_event(PASS_RDRAM events_context.dp.mq, events_context.dp.msg, /*coalescible=*/false);
    recomp_ultra_trace_record("~dp_done", 0,
        (uint32_t)events_context.dp.mq, (uint32_t)events_context.dp.msg, (uint32_t)sent, task_type);
    g_dp_complete_count.fetch_add(1, std::memory_order_relaxed);
}

static bool run_rsp_task_or_warn(RDRAM_ARG const OSTask* task) {
    if (ultramodern::rsp::run_task(PASS_RDRAM task)) {
        return true;
    }

    // Degrade gracefully instead of killing the process when a task has no
    // registered host microcode; the caller still signals SP completion.
    static std::atomic<bool> s_warned[64] = {};
    uint32_t t = task->t.type & 63u;
    if (!s_warned[t].exchange(true)) {
        fprintf(stderr,
            "[ultramodern] no RSP microcode for task type %" PRIu32
            " -- dropping task (not fatal; further drops of this type are "
            "silent)\n", task->t.type);
        fflush(stderr);
    }
    return false;
}

void task_thread_func(uint8_t* rdram, moodycamel::LightweightSemaphore* thread_ready) {
    ultramodern::set_native_thread_name("SP Task Thread");
    ultramodern::set_native_thread_priority(ultramodern::ThreadPriority::Normal);

    // Let the thread that spawned us know we're up.
    thread_ready->signal();

    while (true) {
        // Block until a non-graphics RSP task arrives.
        OSTask* task;
        events_context.sp_task_queue.wait_dequeue(task);

        // A null task is the shutdown sentinel.
        if (task == nullptr) {
            return;
        }

        (void)run_rsp_task_or_warn(PASS_RDRAM task);

#ifndef N64_COSIM
        // Tell the game that the RSP has completed.
        sp_complete(task->t.type);
#endif
    }
}

std::atomic_uint32_t display_refresh_rate = 60;
std::atomic<float> resolution_scale = 1.0f;

uint32_t ultramodern::get_target_framerate(uint32_t original) {
    auto& config = ultramodern::renderer::get_graphics_config();

    switch (config.rr_option) {
        case ultramodern::renderer::RefreshRate::Original:
        default:
            return original;
        case ultramodern::renderer::RefreshRate::Manual:
            return config.rr_manual_value;
        case ultramodern::renderer::RefreshRate::Display:
            return display_refresh_rate.load();
    }
}

uint32_t ultramodern::get_display_refresh_rate() {
    return display_refresh_rate.load();
}

float ultramodern::get_resolution_scale() {
    return resolution_scale.load();
}

void ultramodern::trigger_config_action() {
    events_context.action_queue.enqueue(UpdateConfigAction{});
}

std::atomic<ultramodern::renderer::SetupResult> renderer_setup_result = ultramodern::renderer::SetupResult::Success;
std::atomic<ultramodern::renderer::GraphicsApi> renderer_chosen_api = ultramodern::renderer::GraphicsApi::Auto;

void gfx_thread_func(uint8_t* rdram, moodycamel::LightweightSemaphore* thread_ready, ultramodern::renderer::WindowHandle window_handle) {
    bool enabled_instant_present = false;
    using namespace std::chrono_literals;

    ultramodern::set_native_thread_name("Gfx Thread");
    ultramodern::set_native_thread_priority(ultramodern::ThreadPriority::Normal);

    auto old_config = ultramodern::renderer::get_graphics_config();

    auto renderer_context = ultramodern::renderer::create_render_context(rdram, window_handle, ultramodern::renderer::get_graphics_config().developer_mode);

    renderer_chosen_api.store(renderer_context->get_chosen_api());
    if (!renderer_context->valid()) {
        renderer_setup_result.store(renderer_context->get_setup_result());
        // Notify the caller thread that this thread is ready.
        thread_ready->signal();
        return;
    }

    if (events_callbacks.gfx_init_callback != nullptr) {
        events_callbacks.gfx_init_callback();
    }

    ultramodern::rsp::init();

    // Let the thread that spawned us know we're up.
    thread_ready->signal();

    while (!exited) {
        // Wait briefly for the next queued action.
        Action action;
        if (events_context.action_queue.wait_dequeue_timed(action, 1ms)) {
            // Dispatch on the action variant.
            if (const auto* task_action = std::get_if<SpTaskAction>(&action)) {
                // Instant present (RT64 PresentEarly) is OPT-IN on this port.
                //
                // PresentEarly makes State::updateScreen early-return whenever the
                // VI framebuffer is already "tracked" by fbManager, which skips both
                // the RDRAM-hash-change upload and the present push. That is fatal
                // for Stadium 2: at the title screen it submits ZERO graphics tasks
                // (display_lists freezes) because the art is RSP-JPEG-decoded
                // straight into RDRAM by njpgdspMain rather than drawn by the RDP.
                // With PresentEarly on, the window would sit frozen on the last
                // workload-driven present forever.
                //
                // Off by default, the full path runs every VI tick: hash-compare
                // RDRAM under the VI, upload CPU/RSP-written changes into the
                // high-res target via fbOperations, and push a present on change --
                // which is exactly RT64's designed path for this game's behavior.
                // Costs one frame of present latency. PSR_INSTANT_PRESENT=1 restores
                // the old behavior.
                static const bool instant_present_enabled = [] {
                    const char* e = std::getenv("PSR_INSTANT_PRESENT");
                    return e != nullptr && e[0] == '1';
                }();
                if (instant_present_enabled && ultramodern::is_game_started() && !enabled_instant_present) {
                    renderer_context->enable_instant_present();
                    enabled_instant_present = true;
                }
#ifndef N64_COSIM
                // Report SP completion right away so the game is free to enqueue other
                // task types. It still won't start the next graphics task until the RDP
                // also reports done, and games normally keep the RSP inputs alive until
                // then, so signalling early is safe in practice. If a title misbehaves,
                // this could instead be driven from RSP yield requests.
                sp_complete(task_action->task.t.type);
#endif
                ultramodern::measure_input_latency();

                [[maybe_unused]] auto renderer_start = std::chrono::high_resolution_clock::now();
                // Stamp the in-flight DL tracker before entering the
                // BLOCKING send_dl. If RT64 hangs inside, debug-server's
                // current_dl cmd can read these atomics to identify the
                // exact DL that's stuck (data_ptr + data_size locate the
                // raw bytes in rdram for offline analysis).
                {
                    using namespace std::chrono;
                    uint64_t ms = duration_cast<milliseconds>(
                        steady_clock::now().time_since_epoch()).count();
                    g_current_dl_entry_ms.store(ms, std::memory_order_relaxed);
                    g_current_dl_data_ptr.store(
                        (uint32_t)(uintptr_t)task_action->task.t.data_ptr,
                        std::memory_order_relaxed);
                    g_current_dl_data_size.store(
                        task_action->task.t.data_size,
                        std::memory_order_relaxed);
                    g_current_dl_ucode_ptr.store(
                        (uint32_t)(uintptr_t)task_action->task.t.ucode,
                        std::memory_order_relaxed);
                    g_current_dl_entry_seq.fetch_add(1, std::memory_order_release);
                }
                renderer_context->send_dl(&task_action->task);
#ifdef N64_COSIM
                if (task_action->cosim_gfx_seq != 0) {
                    uint64_t cur = cosim_gfx_rendered_seq.load(std::memory_order_acquire);
                    while (cur < task_action->cosim_gfx_seq &&
                           !cosim_gfx_rendered_seq.compare_exchange_weak(
                               cur,
                               task_action->cosim_gfx_seq,
                               std::memory_order_release,
                               std::memory_order_acquire)) {
                    }
                }
                if (task_action->cosim_done != nullptr) {
                    task_action->cosim_done->signal();
                }
#endif
                {
                    using namespace std::chrono;
                    uint64_t ms = duration_cast<milliseconds>(
                        steady_clock::now().time_since_epoch()).count();
                    g_current_dl_exit_ms.store(ms, std::memory_order_relaxed);
                    g_current_dl_exit_seq.fetch_add(1, std::memory_order_release);
                }
                [[maybe_unused]] auto renderer_end = std::chrono::high_resolution_clock::now();
#ifndef N64_COSIM
                dp_complete(task_action->task.t.type);
#endif
                // printf("Renderer ProcessDList time: %d us\n", static_cast<u32>(std::chrono::duration_cast<std::chrono::microseconds>(renderer_end - renderer_start).count()));
            }
            else if (const auto* screen_update_action = std::get_if<ScreenUpdateAction>(&action)) {
                events_context.vi.update_screen_regs = screen_update_action->regs;
                renderer_context->update_screen();
                display_refresh_rate = renderer_context->get_display_framerate();
                resolution_scale = renderer_context->get_resolution_scale();
            }
            else if (const auto* config_action = std::get_if<UpdateConfigAction>(&action)) {
                (void)config_action;
                auto new_config = ultramodern::renderer::get_graphics_config();
                if (renderer_context->update_config(old_config, new_config)) {
                    old_config = new_config;
                }
            }
        }
    }

    graphics_shutdown_ready.wait();
    renderer_context->shutdown();
}

#define VI_CTRL_TYPE_16             0x00002
#define VI_CTRL_TYPE_32             0x00003
#define VI_CTRL_GAMMA_DITHER_ON     0x00004
#define VI_CTRL_GAMMA_ON            0x00008
#define VI_CTRL_DIVOT_ON            0x00010
#define VI_CTRL_SERRATE_ON          0x00040
#define VI_CTRL_ANTIALIAS_MASK      0x00300
#define VI_CTRL_ANTIALIAS_MODE_1    0x00100
#define VI_CTRL_ANTIALIAS_MODE_2    0x00200
#define VI_CTRL_ANTIALIAS_MODE_3    0x00300
#define VI_CTRL_PIXEL_ADV_MASK      0x01000
#define VI_CTRL_PIXEL_ADV_1         0x01000
#define VI_CTRL_PIXEL_ADV_2         0x02000
#define VI_CTRL_PIXEL_ADV_3         0x03000
#define VI_CTRL_DITHER_FILTER_ON    0x10000

static const OSViMode dummy_mode = []() {
    OSViMode ret{};

    ret.type = 2;
    ret.comRegs.ctrl = VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 | VI_CTRL_PIXEL_ADV_3;
    ret.comRegs.width = 0x140;
    ret.comRegs.burst = 0x03E52239;
    ret.comRegs.vSync = 0x20D;
    ret.comRegs.hSync = 0xC15;
    ret.comRegs.leap = 0x0C150C15;
    ret.comRegs.hStart = 0x006C02EC;
    ret.comRegs.xScale = 0x200;
    ret.comRegs.vCurrent = 0x0;

    for (int field = 0; field < 2; field++) {
        ret.fldRegs[field].origin = 0x280;
        ret.fldRegs[field].yScale = 0x400;
        ret.fldRegs[field].vStart = 0x2501FF;
        ret.fldRegs[field].vBurst = 0xE0204;
        ret.fldRegs[field].vIntr = 0x2;
    }

    return ret;
}();

void set_dummy_vi(bool odd) {
    ViState* next_state = events_context.vi.get_next_state();
    next_state->mode = &dummy_mode;
    // Aim at a placeholder framebuffer, nudged for the odd field.
    next_state->framebuffer = 0x80700000;
    if (odd) {
        next_state->framebuffer += 0x25800;
    }
}

extern "C" void osViSwapBuffer(RDRAM_ARG PTR(void) frameBufPtr) {
    std::lock_guard lock{ events_context.message_mutex };
    events_context.vi.get_next_state()->framebuffer = frameBufPtr;
}

extern "C" void osViSetMode(RDRAM_ARG PTR(OSViMode) mode_) {
    std::lock_guard lock{ events_context.message_mutex };
    OSViMode* mode = TO_PTR(OSViMode, mode_);
    ViState* next_state = events_context.vi.get_next_state();
    next_state->mode = mode;
    next_state->control = next_state->mode->comRegs.ctrl;
}

#define OS_VI_GAMMA_ON          0x0001
#define OS_VI_GAMMA_OFF         0x0002
#define OS_VI_GAMMA_DITHER_ON   0x0004
#define OS_VI_GAMMA_DITHER_OFF  0x0008
#define OS_VI_DIVOT_ON          0x0010
#define OS_VI_DIVOT_OFF         0x0020
#define OS_VI_DITHER_FILTER_ON  0x0040
#define OS_VI_DITHER_FILTER_OFF 0x0080

extern "C" void osViSetSpecialFeatures(uint32_t func) {
    std::lock_guard lock{ events_context.message_mutex };
    ViState* next_state = events_context.vi.get_next_state();
    uint32_t& control = next_state->control;

    if (func & OS_VI_GAMMA_ON) {
        control |= VI_CTRL_GAMMA_ON;
    }
    if (func & OS_VI_GAMMA_OFF) {
        control &= ~VI_CTRL_GAMMA_ON;
    }
    if (func & OS_VI_GAMMA_DITHER_ON) {
        control |= VI_CTRL_GAMMA_DITHER_ON;
    }
    if (func & OS_VI_GAMMA_DITHER_OFF) {
        control &= ~VI_CTRL_GAMMA_DITHER_ON;
    }
    if (func & OS_VI_DIVOT_ON) {
        control |= VI_CTRL_DIVOT_ON;
    }
    if (func & OS_VI_DIVOT_OFF) {
        control &= ~VI_CTRL_DIVOT_ON;
    }
    if (func & OS_VI_DITHER_FILTER_ON) {
        // Enabling the dither filter takes the place of hardware antialiasing.
        control |= VI_CTRL_DITHER_FILTER_ON;
        control &= ~VI_CTRL_ANTIALIAS_MASK;
    }
    if (func & OS_VI_DITHER_FILTER_OFF) {
        // Turning it back off restores the antialias bits from the active mode.
        control &= ~VI_CTRL_DITHER_FILTER_ON;
        control |= next_state->mode->comRegs.ctrl & VI_CTRL_ANTIALIAS_MASK;
    }
}

extern "C" void osViBlack(uint8_t active) {
    std::lock_guard lock{ events_context.message_mutex };
    ViState* next_state = events_context.vi.get_next_state();
    uint32_t* state_out = &next_state->state;
    if (active) {
        *state_out |= VI_STATE_BLACK;
    } else {
        *state_out &= ~VI_STATE_BLACK;
    }
}

extern "C" void osViRepeatLine(uint8_t active) {
    std::lock_guard lock{ events_context.message_mutex };
    ViState* next_state = events_context.vi.get_next_state();
    uint32_t* state_out = &next_state->state;
    if (active) {
        *state_out |= VI_STATE_REPEATLINE;
    } else {
        *state_out &= ~VI_STATE_REPEATLINE;
    }
}

extern "C" void osViSetXScale(float scale) {
    if (scale != 1.0f) {
        assert(false);
    }
}

extern "C" void osViSetYScale(float scale) {
    if (scale != 1.0f) {
        assert(false);
    }
}

extern "C" PTR(void) osViGetNextFramebuffer() {
    return events_context.vi.get_next_state()->framebuffer;
}

extern "C" PTR(void) osViGetCurrentFramebuffer() {
    return events_context.vi.get_cur_state()->framebuffer;
}

// Counters: total submit_rsp_task calls by task type. Surfaced via
// status command so a frozen game can be characterized as
// "gfx tasks not being submitted by game thread" vs "submitted but
// stuck somewhere downstream of action_queue".
static std::atomic<uint64_t> g_submit_gfx{0};
static std::atomic<uint64_t> g_submit_audio{0};
static std::atomic<uint64_t> g_submit_other{0};

extern "C" uint64_t ultramodern_submit_gfx_count(void) { return g_submit_gfx.load(); }
extern "C" uint64_t ultramodern_submit_audio_count(void) { return g_submit_audio.load(); }
extern "C" uint64_t ultramodern_submit_other_count(void) { return g_submit_other.load(); }
extern "C" uint64_t ultramodern_sp_complete_count(void);
extern "C" uint64_t ultramodern_dp_complete_count(void);

void ultramodern::submit_rsp_task(RDRAM_ARG PTR(OSTask) task_) {
    OSTask* task = TO_PTR(OSTask, task_);

    // Graphics tasks are routed to the action queue serviced by the gfx thread.
    if (task->t.type == M_GFXTASK) {
        g_submit_gfx.fetch_add(1, std::memory_order_relaxed);
#ifdef N64_COSIM
        const uint64_t gfx_seq = cosim_gfx_next_seq.fetch_add(1, std::memory_order_relaxed) + 1;
        moodycamel::LightweightSemaphore render_done;
        events_context.action_queue.enqueue(SpTaskAction{ *task, gfx_seq, &render_done });
        render_done.wait();
        cosim_schedule_rcp_event(CosimRcpEventKind::SpComplete, task->t.type, cosim_gfx_sp_delay());
        cosim_schedule_rcp_event(CosimRcpEventKind::DpComplete, task->t.type, cosim_gfx_dp_delay(), gfx_seq);
#else
        events_context.action_queue.enqueue(SpTaskAction{ *task });
#endif
    }
    // Every other task type is serviced by the SP task thread.
    else {
        if (task->t.type == M_AUDTASK) g_submit_audio.fetch_add(1, std::memory_order_relaxed);
        else g_submit_other.fetch_add(1, std::memory_order_relaxed);
#ifdef N64_COSIM
        (void)run_rsp_task_or_warn(PASS_RDRAM task);
        cosim_schedule_rcp_event(CosimRcpEventKind::SpComplete, task->t.type, cosim_rsp_sp_delay());
#else
        // Audio tasks run INLINE, on the submitting thread, instead of being
        // handed to the SP task thread.
        //
        // The async path races the game for the Acmd buffer. On hardware the RSP
        // drains the command list within the frame, so the game is free to start
        // rebuilding it almost immediately; here the task thread can still be
        // reading list N when the game has begun overwriting it. The corruption
        // is real and visible: aspMain_ps2 walks into the middle of its own list
        // (r27 = 0x230 / 0xB0 bytes still remaining, so nowhere near the end),
        // reads what is by then PCM sample data, and dispatches on
        // (opcode & 0x7F) * 2 taken from a sample -- landing outside the 24-entry
        // handler table as "Unhandled jump target 0x01F2 / 0x0119 / 0xFFFFBB92".
        // ~20 faults/run, each a dropped buffer and an audible glitch.
        //
        // Note this is NOT queue contention behind the 900 njpgdsp tasks: the
        // faults occur just as often before njpgdsp starts (other=0) as during.
        //
        // Running inline closes the window completely -- the list is consumed
        // before osSpTaskStartGo returns, which is the ordering the game is
        // written against. Audio lists are short, so the submitting guest thread
        // stalls only briefly. njpgdsp/other tasks stay on the task thread; a
        // JPEG decode is far too long to run inline under the cooperative
        // scheduler. PSR_ASYNC_AUDIO=1 restores the old async behavior.
        static const bool async_audio = [] {
            const char* e = std::getenv("PSR_ASYNC_AUDIO");
            return e != nullptr && e[0] == '1';
        }();
        if (task->t.type == M_AUDTASK && !async_audio) {
            (void)run_rsp_task_or_warn(PASS_RDRAM task);
            sp_complete(task->t.type);
        }
        else {
            events_context.sp_task_queue.enqueue(task);
        }
#endif
    }
}

void ultramodern::send_si_message(RDRAM_ARG1) {
    // SI (controller/PIF) completion is RELIABLE: a thread blocks on it after
    // osContStartReadData / osPfs* ops. Never dropped. See post_rcp_event.
    s32 sent = ultramodern::post_rcp_event(PASS_RDRAM events_context.si.mq, events_context.si.msg, /*coalescible=*/false);
    recomp_ultra_trace_record("~si_done", 0,
        (uint32_t)events_context.si.mq, (uint32_t)events_context.si.msg, (uint32_t)sent, 0);
}

void ultramodern::init_events(RDRAM_ARG ultramodern::renderer::WindowHandle window_handle) {
    moodycamel::LightweightSemaphore gfx_thread_ready;
    moodycamel::LightweightSemaphore task_thread_ready;
    events_context.rdram = rdram;
    events_context.sp.gfx_thread = std::thread{ gfx_thread_func, rdram, &gfx_thread_ready, window_handle };
    events_context.sp.task_thread = std::thread{ task_thread_func, rdram, &task_thread_ready };

    // Don't let the game proceed until both SP-side threads report ready, so no RSP task
    // can arrive before there's something to service it.
    gfx_thread_ready.wait();
    task_thread_ready.wait();

    ultramodern::renderer::SetupResult setup_result = renderer_setup_result.load();
    if (setup_result != ultramodern::renderer::SetupResult::Success) {
        auto show_renderer_error = [](const std::string& msg) {
            std::string error_msg = "An error has been encountered on startup: " + msg;

            ultramodern::error_handling::message_box(error_msg.c_str());
        };

        const std::string driver_os_suffix = "\nPlease make sure your GPU drivers and your OS are up to date.";
        switch (setup_result) {
            case ultramodern::renderer::SetupResult::Success:
                break;
            case ultramodern::renderer::SetupResult::DynamicLibrariesNotFound:
                show_renderer_error("Failed to load dynamic libraries. Make sure the DLLs are next to the recomp executable.");
                break;
            case ultramodern::renderer::SetupResult::InvalidGraphicsAPI:
                show_renderer_error(ultramodern::renderer::get_graphics_api_name(renderer_chosen_api.load()) + " is not supported on this platform. Please select a different graphics API.");
                break;
            case ultramodern::renderer::SetupResult::GraphicsAPINotFound:
                show_renderer_error("Unable to initialize " + ultramodern::renderer::get_graphics_api_name(renderer_chosen_api.load()) + "." + driver_os_suffix);
                break;
            case ultramodern::renderer::SetupResult::GraphicsDeviceNotFound:
                show_renderer_error("Unable to find compatible graphics device." + driver_os_suffix);
                break;
        }
        throw std::runtime_error("Failed to initialize the renderer");
    }

    events_context.vi.thread = std::thread{ vi_thread_func };
}

void ultramodern::join_event_threads() {
    events_context.sp.gfx_thread.join();
    events_context.vi.thread.join();

    // Push the null sentinel so the SP task thread falls out of its loop and returns.
    events_context.sp_task_queue.enqueue(nullptr);
    events_context.sp.task_thread.join();
}
