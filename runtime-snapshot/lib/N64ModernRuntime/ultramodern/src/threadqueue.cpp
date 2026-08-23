#include <cassert>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <mutex>
#include <unordered_map>

#include "ultramodern/ultramodern.hpp"

static PTR(OSThread) running_queue_impl = NULLPTR;

extern "C" uint32_t ultramodern_running_queue_head(void) {
    return static_cast<uint32_t>(running_queue_impl);
}

// Per-thread "queued since" tracking for running_queue specifically. Keyed by
// guest OSThread address rather than id: a thread's id field can be
// overwritten in place by unrelated guest code while the struct is still
// linked in running_queue (observed during Stadium 2 boot), and id is not
// guaranteed unique/stable the way the struct's own address is.
//
// This exists so a starvation check can ask "how long has the longest
// -waiting queued thread been waiting", independent of which thread happens
// to be at the head *right now*. Tracking only "time since the current head
// changed" undercounts starvation: if any other thread is transiently
// queued and popped ahead of a low-priority thread, the head identity
// changes and back, resetting a head-based timer even though the
// low-priority thread itself has been continuously waiting the whole time.
static std::mutex g_queued_since_mutex;
static std::unordered_map<uint32_t, uint64_t> g_queued_since_us;

// Microsecond resolution, not millisecond: the corrupting write this exists
// to race against lives inside a tight per-byte clear loop that can run to
// completion in well under 1 ms of wall-clock time. A millisecond-scale
// timestamp can read as unchanged (0 ms elapsed) for the loop's entire
// duration, so the synchronous checkpoint check in scheduler_tick.cpp would
// never see it cross a >0 threshold in time. Microseconds give it a
// realistic chance.
static uint64_t queued_since_now_us() {
    using namespace std::chrono;
    return duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();
}

static void queued_since_mark(uint32_t addr) {
    std::lock_guard<std::mutex> guard(g_queued_since_mutex);
    g_queued_since_us[addr] = queued_since_now_us();
}

static void queued_since_clear(uint32_t addr) {
    std::lock_guard<std::mutex> guard(g_queued_since_mutex);
    g_queued_since_us.erase(addr);
}

// Returns how long (in microseconds) the longest-waiting thread currently
// recorded as queued in running_queue has been waiting, or 0 if none are
// tracked. Used by the voluntary-preemption path (scheduler_tick.cpp) to
// detect starvation that a "same head" check would miss.
extern "C" uint64_t ultramodern_running_queue_oldest_wait_us(void) {
    std::lock_guard<std::mutex> guard(g_queued_since_mutex);
    if (g_queued_since_us.empty()) {
        return 0;
    }
    uint64_t now = queued_since_now_us();
    uint64_t oldest = 0;
    for (const auto& kv : g_queued_since_us) {
        uint64_t waited = now - kv.second;
        if (waited > oldest) {
            oldest = waited;
        }
    }
    return oldest;
}

#ifdef N64_COSIM
extern "C" void ultramodern_cosim_check_vi_quiescence(uint8_t* rdram);

static std::atomic<uint64_t> cosim_scheduler_epoch{0};
static std::atomic<uint32_t> cosim_scheduler_active{0};
static thread_local uint32_t cosim_scheduler_depth = 0;
static thread_local bool cosim_scheduler_handoff_open = false;

extern "C" void ultramodern_cosim_scheduler_mutation_begin(void) {
    if (cosim_scheduler_depth++ == 0) {
        cosim_scheduler_active.fetch_add(1, std::memory_order_acq_rel);
        cosim_scheduler_epoch.fetch_add(1, std::memory_order_acq_rel);
    }
}

extern "C" void ultramodern_cosim_scheduler_mutation_end(void) {
    assert(cosim_scheduler_depth != 0);
    if (--cosim_scheduler_depth == 0) {
        cosim_scheduler_epoch.fetch_add(1, std::memory_order_acq_rel);
        cosim_scheduler_active.fetch_sub(1, std::memory_order_acq_rel);
    }
}

extern "C" void ultramodern_cosim_scheduler_handoff_begin(void) {
    if (!cosim_scheduler_handoff_open) {
        cosim_scheduler_handoff_open = true;
        ultramodern_cosim_scheduler_mutation_begin();
    }
}

extern "C" void ultramodern_cosim_scheduler_handoff_end(void) {
    if (cosim_scheduler_handoff_open) {
        cosim_scheduler_handoff_open = false;
        ultramodern_cosim_scheduler_mutation_end();
    }
}

extern "C" uint64_t ultramodern_cosim_scheduler_epoch(void) {
    const uint64_t epoch = cosim_scheduler_epoch.load(std::memory_order_acquire);
    const uint32_t active = cosim_scheduler_active.load(std::memory_order_acquire);
    return (epoch << 1) | (active != 0 ? 1u : 0u);
}
#endif

namespace sched_log {
    enum Op : uint32_t {
        OP_INSERT = 1,
        OP_POP = 2,
        OP_REMOVE = 3,
        OP_REMOVE_MISS = 4,
        OP_SCHEDULE_RUNNING = 100,
        OP_CHECK_EMPTY = 101,
        OP_CHECK_PEEK = 102,
        OP_CHECK_NO_SWAP = 103,
        OP_CHECK_SWAP = 104,
        OP_SWAP_ENTER = 110,
        OP_SWAP_INSERT_SELF = 111,
        OP_SWAP_WAIT_ENTER = 112,
        OP_SWAP_WAIT_RETURN = 113,
        OP_WAIT_BEGIN = 120,
        OP_WAIT_RETURN = 121,
        OP_RESUME_SIGNAL = 122,
        OP_RUN_NEXT_ENTER = 123,
        OP_RUN_NEXT_EMPTY = 124,
        OP_RUN_NEXT_TARGET = 125,
        OP_RUN_NEXT_WAIT_ENTER = 126,
        OP_RUN_NEXT_WAIT_RETURN = 127,
        OP_YIELD_ANY_ENTER = 130,
        OP_YIELD_ANY_EMPTY = 131,
        OP_YIELD_ANY_TARGET = 132,
        OP_YIELD_ANY_REQUEUE_SELF = 133,
        OP_YIELD_ANY_WAIT_ENTER = 134,
        OP_YIELD_ANY_WAIT_RETURN = 135,
    };

    struct Event {
        uint64_t seq;
        uint64_t ms;
        uint32_t op;
        uint32_t queue;
        uint32_t thread;
        uint32_t current_thread;
        uint32_t head_after;
        uint32_t next_after;
        uint16_t thread_id;
        uint16_t current_thread_id;
        int16_t priority;
        uint16_t pad;
    };

    static_assert(sizeof(Event) == 48, "scheduler queue event size changed");

    constexpr size_t RING_CAP = 65536;
    static Event ring[RING_CAP];
    static std::atomic<uint64_t> next_seq{0};
    static std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();

    uint64_t now_ms() {
        return uint64_t(std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - t0).count());
    }

    uint16_t thread_id(RDRAM_ARG PTR(OSThread) t_) {
        if (t_ == NULLPTR) {
            return 0;
        }
        return static_cast<uint16_t>(TO_PTR(OSThread, t_)->id);
    }

    int16_t thread_priority(RDRAM_ARG PTR(OSThread) t_) {
        if (t_ == NULLPTR) {
            return 0;
        }
        return static_cast<int16_t>(TO_PTR(OSThread, t_)->priority);
    }

    // Never-evict per-thread state table (indexed by OSThread id). The event
    // ring wraps under the idle/audio cycle's high event rate, so an early
    // park (a thread's last blocked_on_recv) scrolls out before a probe looks.
    // This table keeps each thread's LAST event + last message-queue block
    // permanently, so the full thread state is always queryable regardless of
    // how long the cycle has flooded the ring. (Doctrine: fix the ring to cover
    // the window, never arm-then-capture.)
    struct ThreadState {
        uint32_t valid;
        uint32_t id;
        uint32_t thread;
        int32_t  priority;
        uint32_t last_op;
        uint32_t last_queue;
        uint32_t last_head_after;
        uint64_t last_ms;
        uint32_t last_mq;     // last INSERT into a real msg queue (blocked_on_recv)
        uint64_t last_mq_ms;
        uint64_t count;
    };
    constexpr size_t MAX_TID = 1024;
    static ThreadState thread_states[MAX_TID];

    void record(RDRAM_ARG uint32_t op,
                PTR(PTR(OSThread)) queue_,
                PTR(OSThread) thread_,
                PTR(OSThread) head_after) {
        const uint64_t s = next_seq.fetch_add(1, std::memory_order_relaxed);
        Event& e = ring[s % RING_CAP];
        e.seq = s;
        e.ms = now_ms();
        e.op = op;
        e.queue = static_cast<uint32_t>(queue_);
        e.thread = static_cast<uint32_t>(thread_);
        e.current_thread = static_cast<uint32_t>(ultramodern::this_thread());
        e.head_after = static_cast<uint32_t>(head_after);
        e.next_after = thread_ != NULLPTR ? static_cast<uint32_t>(TO_PTR(OSThread, thread_)->next) : 0;
        e.thread_id = thread_id(PASS_RDRAM thread_);
        e.current_thread_id = thread_id(PASS_RDRAM ultramodern::this_thread());
        e.priority = thread_priority(PASS_RDRAM thread_);
        e.pad = 0;

        if (e.thread_id < MAX_TID && !(e.thread_id == 0 && thread_ == NULLPTR)) {
            ThreadState& ts = thread_states[e.thread_id];
            ts.valid = 1;
            ts.id = e.thread_id;
            ts.thread = e.thread;
            ts.priority = e.priority;
            ts.last_op = op;
            ts.last_queue = e.queue;
            ts.last_head_after = e.head_after;
            ts.last_ms = e.ms;
            ts.count++;
            // INSERT into a queue that is neither the running queue (0xFFFFFFFF,
            // the running_queue sentinel) nor NULL == blocking on a real msg
            // queue's blocked_on_recv list: that is what the thread is waiting on.
            if (op == OP_INSERT && e.queue != 0xFFFFFFFFu && e.queue != 0) {
                ts.last_mq = e.queue;
                ts.last_mq_ms = e.ms;
            }
        }
    }
}

extern "C" void ultramodern_sched_recent_copy(
    void* out_void, size_t cap, size_t* n_written, uint64_t* next_seq_out)
{
    using namespace sched_log;
    const uint64_t s = next_seq.load(std::memory_order_relaxed);
    if (next_seq_out) *next_seq_out = s;
    if (cap == 0 || out_void == nullptr) {
        if (n_written) *n_written = 0;
        return;
    }
    const size_t available = std::min<size_t>(s, RING_CAP);
    const size_t want = std::min(cap, available);
    Event* out = static_cast<Event*>(out_void);
    const size_t start = (s - want) % RING_CAP;
    for (size_t i = 0; i < want; i++) {
        out[i] = ring[(start + i) % RING_CAP];
    }
    if (n_written) *n_written = want;
}

extern "C" size_t ultramodern_sched_event_size(void) {
    return sizeof(sched_log::Event);
}

extern "C" size_t ultramodern_sched_thread_state_size(void) {
    return sizeof(sched_log::ThreadState);
}

// Copy the never-evict per-thread state table. Returns every thread the
// scheduler has ever touched, each with its last event + last msg-queue block.
extern "C" void ultramodern_sched_thread_states_copy(
    void* out_void, size_t cap, size_t* n_written)
{
    using namespace sched_log;
    size_t w = 0;
    if (out_void != nullptr) {
        ThreadState* out = static_cast<ThreadState*>(out_void);
        for (size_t i = 0; i < MAX_TID && w < cap; i++) {
            if (thread_states[i].valid) {
                out[w++] = thread_states[i];
            }
        }
    }
    if (n_written) *n_written = w;
}

#ifdef N64_COSIM
extern "C" void ultramodern_cosim_thread_quiescence(
    uint8_t* rdram,
    uint32_t vi_queue,
    ultramodern_cosim_quiescence_state* out)
{
    if (out == nullptr) {
        return;
    }

    ultramodern_cosim_quiescence_state s{};
    s.vi_queue = vi_queue;
    s.running_head = static_cast<uint32_t>(running_queue_impl);
    if (rdram == nullptr) {
        *out = s;
        return;
    }

    for (size_t i = 0; i < sched_log::MAX_TID; i++) {
        const sched_log::ThreadState& ts = sched_log::thread_states[i];
        if (!ts.valid) {
            continue;
        }
        if (ts.thread == NULLPTR) {
            continue;
        }
        if (ts.thread < 0x80000000u || ts.thread >= 0x80800000u) {
            continue;
        }
        PTR(OSThread) thread = static_cast<PTR(OSThread)>(ts.thread);
        OSThread* t = TO_PTR(OSThread, thread);
        if (t->context == nullptr || t->state == OSThreadState::STOPPED) {
            continue;
        }
        s.known_threads++;
        if (t->state == OSThreadState::BLOCKED) {
            const uint32_t blocked_queue = static_cast<uint32_t>(t->queue);
            if (vi_queue != 0 &&
                (blocked_queue == vi_queue || ts.last_mq == vi_queue)) {
                s.blocked_on_vi++;
            } else {
                s.blocked_on_other++;
            }
        } else if (t->state == OSThreadState::RUNNING &&
                   t->priority <= 0 &&
                   s.running_head == 0) {
            s.idle_running++;
        } else {
            s.runnable_or_unknown++;
        }
    }

    s.external_pending = ultramodern_cosim_checkpoint_external_pending();
    s.scheduler_active = cosim_scheduler_active.load(std::memory_order_acquire);
    s.quiescent =
        s.vi_queue != 0 &&
        s.running_head == 0 &&
        s.known_threads != 0 &&
        s.blocked_on_vi != 0 &&
        s.runnable_or_unknown == 0 &&
        s.external_pending == 0 &&
        s.scheduler_active == 0;
    *out = s;
}

#endif

static PTR(OSThread)* queue_to_ptr(RDRAM_ARG PTR(PTR(OSThread)) queue) {
    if (queue == ultramodern::running_queue) {
        return &running_queue_impl;
    }
    return TO_PTR(PTR(OSThread), queue);
}

static PTR(OSThread) queue_head_or_zero(RDRAM_ARG PTR(PTR(OSThread)) queue) {
    if (queue == NULLPTR) {
        return NULLPTR;
    }
    return *queue_to_ptr(PASS_RDRAM queue);
}

void ultramodern::scheduler_trace_mark(RDRAM_ARG uint32_t op,
                                       PTR(PTR(OSThread)) queue_,
                                       PTR(OSThread) thread_) {
    sched_log::record(PASS_RDRAM op, queue_, thread_, queue_head_or_zero(PASS_RDRAM queue_));
}

// A guest OSThread pointer is valid only if it is a 4-byte-aligned KSEG0 RDRAM
// address. A game that frees an OSThread while it is still linked in a runtime
// queue (e.g. Pokemon Snap's per-game-object process threads, destroyed en masse
// on scene teardown) leaves a garbage `next` in the chain; walking it unvalidated
// dereferences freed/reused memory and faults. Validate before every deref so the
// scheduler degrades gracefully instead of crashing. Strict improvement — the only
// behavior it changes is on an already-corrupt queue, where the alternative is a hard crash.
static inline bool valid_thread_ptr(PTR(OSThread) p) {
    uint32_t v = static_cast<uint32_t>(p);
    return v >= 0x80000000u && v < 0x80800000u && (v & 3u) == 0u;
}

void ultramodern::thread_queue_insert(RDRAM_ARG PTR(PTR(OSThread)) queue_, PTR(OSThread) added_) {
#ifdef N64_COSIM
    ultramodern::CosimSchedulerMutation cosim_mutation;
#endif
    // The queue is an intrusive singly-linked list kept in descending priority
    // order. Advance to the first link whose thread does not outrank the new one
    // and splice the new thread in ahead of it.
    PTR(OSThread)* link = queue_to_ptr(PASS_RDRAM queue_);
    OSThread* added = TO_PTR(OSThread, added_);
    debug_printf("[Thread Queue] thread %d -> queue 0x%08X\n", added->id, (uintptr_t)queue_);

    // Re-inserting a thread that is already linked in this same queue would
    // splice it in front of itself — `added->next = *link` where *link IS
    // added_ — producing a self-referential node. The list then never
    // terminates, every later walk burns the 0x40000 guard, and the thread
    // can never be cleanly popped. This happens for real: a blocking
    // do_recv/do_send loop re-inserts the caller on each iteration whenever
    // the wait it performs returns without actually switching threads.
    // Insertion is idempotent instead: already queued here means nothing to do.
    //
    // Validate before dereferencing: callers can reach here with a NULL guest
    // thread (ultramodern::this_thread() is NULLPTR on the main thread, which
    // still reports is_game_thread() == true), and forming a host pointer from
    // it faults.
    if (!valid_thread_ptr(added_)) {
        return;
    }
    if (added->queue == queue_) {
        return;
    }
    uint32_t guard = 0;
    while (*link && valid_thread_ptr(*link) && ++guard <= 0x40000u && TO_PTR(OSThread, *link)->priority > added->priority) {
        link = &TO_PTR(OSThread, *link)->next;
    }
    // If we stopped on a corrupt link (not NULL, not a valid pointer), sever the
    // bad tail here so we splice ahead of it rather than dereferencing garbage.
    if (*link != NULLPTR && !valid_thread_ptr(*link)) {
        *link = NULLPTR;
    }
    added->next = *link;
    added->queue = queue_;
    if (queue_ == ultramodern::running_queue) {
        added->state = OSThreadState::QUEUED;
        queued_since_mark(static_cast<uint32_t>(added_));
    } else if (queue_ != NULLPTR) {
        added->state = OSThreadState::BLOCKED;
    }
    *link = added_;
    sched_log::record(PASS_RDRAM sched_log::OP_INSERT, queue_, added_, *queue_to_ptr(PASS_RDRAM queue_));
#ifdef N64_COSIM
    if (queue_ != ultramodern::running_queue && queue_ != NULLPTR) {
        ultramodern_cosim_check_vi_quiescence(rdram);
    }
#endif

    // Trace the queue contents after the insertion.
    debug_printf("  Contains:");
    link = queue_to_ptr(PASS_RDRAM queue_);
    while (*link) {
        debug_printf("%d (%d) ", TO_PTR(OSThread, *link)->id, TO_PTR(OSThread, *link)->priority);
        link = &TO_PTR(OSThread, *link)->next;
    }
    debug_printf("\n");
}

PTR(OSThread) ultramodern::thread_queue_pop(RDRAM_ARG PTR(PTR(OSThread)) queue_) {
#ifdef N64_COSIM
    ultramodern::CosimSchedulerMutation cosim_mutation;
#endif
    // The highest-priority thread is at the head; detach and return it.
    PTR(OSThread)* head = queue_to_ptr(PASS_RDRAM queue_);
    PTR(OSThread) popped = *head;
    // Guard against a corrupt head (freed/reused OSThread) — treat as empty.
    if (!valid_thread_ptr(popped)) {
        *head = NULLPTR;
        return NULLPTR;
    }
    *head = TO_PTR(OSThread, popped)->next;
    TO_PTR(OSThread, popped)->queue = NULLPTR;
    queued_since_clear(static_cast<uint32_t>(popped));
    sched_log::record(PASS_RDRAM sched_log::OP_POP, queue_, popped, *head);
    debug_printf("[Thread Queue] popped thread %d from queue 0x%08X\n", TO_PTR(OSThread, popped)->id, (uintptr_t)queue_);
    return popped;
}

bool ultramodern::thread_queue_remove(RDRAM_ARG PTR(PTR(OSThread)) queue_, PTR(OSThread) t_) {
#ifdef N64_COSIM
    ultramodern::CosimSchedulerMutation cosim_mutation;
#endif
    // Guard against a garbage queue pointer (queue_to_ptr would build a wild host
    // pointer that faults on the first deref). The running queue is a sentinel
    // backed by a host static, so it is always valid.
    if (queue_ != ultramodern::running_queue && !valid_thread_ptr(queue_)) {
        sched_log::record(PASS_RDRAM sched_log::OP_REMOVE_MISS, queue_, t_, NULLPTR);
        return false;
    }
    debug_printf("[Thread Queue] remove thread %d from queue 0x%08X\n", TO_PTR(OSThread, t_)->id, (uintptr_t)queue_);

    // Scan the list for the target and unlink it if found.
    PTR(OSThread)* link = queue_to_ptr(PASS_RDRAM queue_);
    uint32_t guard = 0;
    while (*link != NULLPTR) {
        PTR(OSThread) cur = *link;
        if (!valid_thread_ptr(cur) || ++guard > 0x40000u) {
            // Corrupt/oversized chain (a freed/reused OSThread). Sever here so a
            // later walk of this queue can't re-fault, and report not-found.
            *link = NULLPTR;
            sched_log::record(PASS_RDRAM sched_log::OP_REMOVE_MISS, queue_, t_, NULLPTR);
            return false;
        }
        if (cur == t_) {
            *link = TO_PTR(OSThread, cur)->next;
            TO_PTR(OSThread, cur)->queue = NULLPTR;  // clear on removal, matching thread_queue_pop
            queued_since_clear(static_cast<uint32_t>(cur));
            sched_log::record(PASS_RDRAM sched_log::OP_REMOVE, queue_, t_, *queue_to_ptr(PASS_RDRAM queue_));
            return true;
        }
        link = &TO_PTR(OSThread, cur)->next;
    }

    // Target was not present in this queue.
    sched_log::record(PASS_RDRAM sched_log::OP_REMOVE_MISS, queue_, t_, *queue_to_ptr(PASS_RDRAM queue_));
    return false;
}

bool ultramodern::thread_queue_empty(RDRAM_ARG PTR(PTR(OSThread)) queue_) {
    return *queue_to_ptr(PASS_RDRAM queue_) == NULLPTR;
}

PTR(OSThread) ultramodern::thread_queue_peek(RDRAM_ARG PTR(PTR(OSThread)) queue_) {
    return *queue_to_ptr(PASS_RDRAM queue_);
}
