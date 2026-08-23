#include <cstdio>
#include <thread>
#include <cassert>
#include <string>
#include <mutex>
#include <unordered_set>

#include "ultramodern/ultra64.h"
#include "ultramodern/ultramodern.hpp"
#include "blockingconcurrentqueue.h"

#include "ultramodern/threads.hpp"
#include "ultramodern/scheduler_tick.hpp"

// Native APIs only used to set thread names for easier debugging
#ifdef _WIN32
#include <Windows.h>
#endif

static ultramodern::threads::callbacks_t threads_callbacks;

void ultramodern::threads::set_callbacks(const callbacks_t& callbacks) {
    threads_callbacks = callbacks;
}

std::string ultramodern::threads::get_game_thread_name(const OSThread* t) {
    if (threads_callbacks.get_game_thread_name == nullptr) {
        return "Game Thread " + std::to_string(t->id);
    }
    return threads_callbacks.get_game_thread_name(t);
}

extern "C" void bootproc();

thread_local bool is_main_thread = false;
// True for threads that belong to the emulated game: the initial start thread and any created via osCreateThread.
thread_local bool is_game_thread = false;
thread_local PTR(OSThread) thread_self = NULLPTR;

void ultramodern::set_main_thread() {
    ::is_game_thread = true;
    is_main_thread = true;
}

bool ultramodern::is_game_thread() {
    return ::is_game_thread;
}

#if 0
int main(int argc, char** argv) {
    ultramodern::set_main_thread();

    bootproc();
}
#endif

#if 1
void run_thread_function(uint8_t* rdram, uint64_t addr, uint64_t sp, uint64_t arg);
#else
#define run_thread_function(func, sp, arg) func(arg)
#endif

#if defined(_WIN32)
void ultramodern::set_native_thread_name(const std::string& name) {
    // Win32 expects a wide string for the debugger-visible thread description.
    std::wstring wide_name(name.begin(), name.end());
    SetThreadDescription(GetCurrentThread(), wide_name.c_str());
}

void ultramodern::set_native_thread_priority(ThreadPriority pri) {
    // Translate the engine's priority enum into a Win32 thread-priority level. The
    // actual SetThreadPriority call is intentionally left disabled below; the mapping
    // is retained so it can be re-enabled without rework.
    int win32_priority;
    switch (pri) {
        case ThreadPriority::Low:      win32_priority = THREAD_PRIORITY_BELOW_NORMAL;  break;
        case ThreadPriority::Normal:   win32_priority = THREAD_PRIORITY_NORMAL;        break;
        case ThreadPriority::High:     win32_priority = THREAD_PRIORITY_ABOVE_NORMAL;  break;
        case ThreadPriority::VeryHigh: win32_priority = THREAD_PRIORITY_HIGHEST;       break;
        case ThreadPriority::Critical: win32_priority = THREAD_PRIORITY_TIME_CRITICAL; break;
        default:
            throw std::runtime_error("Invalid thread priority!");
    }
    (void)win32_priority;
    // SetThreadPriority(GetCurrentThread(), win32_priority);
}
#elif defined(__linux__)
#include <sys/prctl.h>

void ultramodern::set_native_thread_name(const std::string& name) {
    if (name.length() > 15) {
        // Linux only accepts up to 16 characters including the null terminator for a thread name.
        debug_printf("[Thread] The thread name '%s' will be truncated to 15 characters", name.c_str());
    }

    prctl(PR_SET_NAME, name.c_str());
}

void ultramodern::set_native_thread_priority(ThreadPriority pri) {
    // TODO linux thread priority
}
#elif defined(__APPLE__)
void ultramodern::set_native_thread_name(const std::string& name) {
    if (name.length() > 15) {
        // Macs seem to only accept up to 16 characters including the null terminator for a thread name.
        debug_printf("[Thread] The thread name '%s' will be truncated to 15 characters", name.c_str());
    }

    pthread_setname_np(name.c_str());
}

void ultramodern::set_native_thread_priority(ThreadPriority pri) {}
#endif

// Live-context registry. A thread's UltraThreadContext* is stored in its
// OSThread, which is guest RDRAM, so a guest write over that struct can leave a
// stale-but-plausible pointer behind. Membership here is the only trustworthy
// answer to "may I dereference this context?".
static std::mutex live_contexts_mutex;
static std::unordered_set<UltraThreadContext*> live_contexts;

void ultramodern_context_register(UltraThreadContext* ctx) {
    std::lock_guard<std::mutex> guard{live_contexts_mutex};
    live_contexts.insert(ctx);
}

void ultramodern_context_unregister(UltraThreadContext* ctx) {
    std::lock_guard<std::mutex> guard{live_contexts_mutex};
    live_contexts.erase(ctx);
}

bool ultramodern_context_is_live(UltraThreadContext* ctx) {
    if (ctx == nullptr) {
        return false;
    }
    std::lock_guard<std::mutex> guard{live_contexts_mutex};
    return live_contexts.find(ctx) != live_contexts.end();
}

void wait_for_resumed(RDRAM_ARG UltraThreadContext* thread_context) {
    ultramodern::scheduler_trace_mark(PASS_RDRAM 120, NULLPTR, ultramodern::this_thread());
#ifdef N64_COSIM
    ultramodern_cosim_scheduler_handoff_end();
#endif
    thread_context->running.wait();
    ultramodern::scheduler_trace_mark(PASS_RDRAM 121, NULLPTR, ultramodern::this_thread());
    // Once woken, the running OSThread may no longer own the context we blocked on: a
    // replacement or a destroy can swap it out while we sleep. In that case re-enter the
    // destroy path from our own context so the cleanup actually runs.
    if (TO_PTR(OSThread, ultramodern::this_thread())->context != thread_context) {
        osDestroyThread(PASS_RDRAM NULLPTR);
    }
    {
#ifdef N64_COSIM
        ultramodern::CosimSchedulerMutation cosim_mutation;
#endif
        TO_PTR(OSThread, ultramodern::this_thread())->state = OSThreadState::RUNNING;
    }
    // Stamp the "last context switch into a game thread" timestamp.
    // The scheduler_tick monitor compares now() against this to decide
    // whether the currently-running game thread is hogging the CPU.
    ultramodern::record_context_switch();
}

bool resume_thread(RDRAM_ARG OSThread* t) {
    debug_printf("[Thread] Waking thread %d\n", t->id);
    ultramodern::scheduler_trace_mark(PASS_RDRAM 122, NULLPTR, NULLPTR);
    UltraThreadContext* ctx = t->context;
    if (!ultramodern_context_is_live(ctx)) {
        // The OSThread was overwritten by the guest (or the context was already
        // retired). Signalling it would fault; report once and let the caller
        // pick another thread.
        static std::atomic_flag reported = ATOMIC_FLAG_INIT;
        if (!reported.test_and_set()) {
            fprintf(stderr,
                "[thread] REFUSING to resume thread id=%d: context %p is not live "
                "(OSThread at guest memory was likely overwritten)\n",
                t->id, (void*)ctx);
            fflush(stderr);
        }
        return false;
    }
    ctx->running.signal();
    return true;
}

// Returns false if no live runnable thread was found (either the queue was empty,
// or every queued thread's context had already been retired). Callers that are
// themselves exiting must treat that as fatal; callers that are merely blocking
// can fall back to staying on their own stack instead of crashing.
bool run_next_thread(RDRAM_ARG1) {
    ultramodern::scheduler_trace_mark(PASS_RDRAM 123, ultramodern::running_queue, NULLPTR);
    for (;;) {
        if (ultramodern::thread_queue_empty(PASS_RDRAM ultramodern::running_queue)) {
            ultramodern::scheduler_trace_mark(PASS_RDRAM 124, ultramodern::running_queue, NULLPTR);
            return false;
        }

        PTR(OSThread) to_run_ = ultramodern::thread_queue_pop(PASS_RDRAM ultramodern::running_queue);
        OSThread* to_run = TO_PTR(OSThread, to_run_);
        UltraThreadContext* ctx = to_run->context;
        if (!ultramodern_context_is_live(ctx)) {
            // The OSThread was overwritten by the guest (or the context was already
            // retired) after it was queued as runnable. Signalling it would fault;
            // report once and try the next runnable thread instead.
            static std::atomic_flag reported = ATOMIC_FLAG_INIT;
            if (!reported.test_and_set()) {
                fprintf(stderr,
                    "[thread] SKIPPING scheduled thread id=%d: context %p is not live "
                    "(OSThread at guest memory was likely overwritten)\n",
                    to_run->id, (void*)ctx);
                fflush(stderr);
            }
            continue;
        }

        ultramodern::scheduler_trace_mark(PASS_RDRAM 125, ultramodern::running_queue, to_run_);
        debug_printf("[Scheduling] Handing control to thread %d\n", to_run->id);
        ctx->running.signal();
        return true;
    }
}

void ultramodern::run_next_thread_and_wait(RDRAM_ARG1) {
    UltraThreadContext* caller_ctx = TO_PTR(OSThread, thread_self)->context;
    ultramodern::scheduler_trace_mark(PASS_RDRAM 126, ultramodern::running_queue, ultramodern::this_thread());
    if (!run_next_thread(PASS_RDRAM1)) {
        // Nothing else is runnable right now. The caller is only blocking (not
        // exiting), so returning lets it re-check its predicate rather than
        // waiting forever to be resumed by a thread that no longer exists.
        //
        // Crucially, do NOT spin: callers here are `while (predicate) { ...
        // run_next_thread_and_wait(); }` loops, and the predicate they wait on
        // (an RSP/DP/VI/audio completion) is posted by a *host* thread through
        // the external-message path. Returning immediately would busy-wait at
        // 100% CPU and never let those messages land. Draining the external
        // queue with a short timeout both yields the CPU and delivers exactly
        // the completions that unblock the caller.
        static std::atomic_flag reported = ATOMIC_FLAG_INIT;
        if (!reported.test_and_set()) {
            fprintf(stderr, "[thread] run_next_thread_and_wait: no other runnable thread; "
                            "waiting on external messages instead\n");
            fflush(stderr);
        }
        ultramodern::wait_for_external_message_timed(PASS_RDRAM 1);

        // Then park on our OWN context with a bounded timeout rather than
        // returning straight away. Two reasons:
        //  1. It keeps the semaphore count and the queue state in step. A
        //     sender can pop us off blocked_on_recv and
        //     schedule_running_thread() us between the check above and our
        //     return; the resume that follows would otherwise signal a
        //     context nobody is waiting on.
        //  2. Without it the caller's `while (predicate)` loop spins hot --
        //     measured ~100% CPU versus ~3% with the wait in place.
        // The timeout preserves forward progress if nothing ever arrives.
        UltraThreadContext* self_ctx = TO_PTR(OSThread, thread_self)->context;
        if (self_ctx != nullptr && ultramodern_context_is_live(self_ctx)) {
            self_ctx->running.wait(1000 /* us */);
        }
        return;
    }
    wait_for_resumed(PASS_RDRAM caller_ctx);
    ultramodern::scheduler_trace_mark(PASS_RDRAM 127, ultramodern::running_queue, ultramodern::this_thread());
}

void ultramodern::resume_thread_and_wait(RDRAM_ARG OSThread *t) {
    UltraThreadContext* caller_ctx = TO_PTR(OSThread, thread_self)->context;
    ultramodern::scheduler_trace_mark(PASS_RDRAM 112, ultramodern::running_queue, ultramodern::this_thread());
    if (!resume_thread(PASS_RDRAM t)) {
        // Nothing was woken, so nothing will ever wake us: keep running rather
        // than blocking forever on our own context.
        return;
    }
    wait_for_resumed(PASS_RDRAM caller_ctx);
    ultramodern::scheduler_trace_mark(PASS_RDRAM 113, ultramodern::running_queue, ultramodern::this_thread());
}

static void run_game_thread(RDRAM_ARG PTR(OSThread) self_, PTR(thread_func_t) entrypoint, PTR(void) arg, UltraThreadContext* ctx) {
    OSThread* self = TO_PTR(OSThread, self_);
    debug_printf("[Thread] Thread created: %d\n", self->id);

    // Publish our identity into thread-local state before anything the scheduler can observe.
    thread_self = self_;
    is_game_thread = true;

    // Set the thread name
    ultramodern::set_native_thread_name(ultramodern::threads::get_game_thread_name(self));
    ultramodern::set_native_thread_priority(ultramodern::ThreadPriority::High);

    // Report that setup is done so osCreateThread can return to its caller.
    ctx->initialized.signal();

    debug_printf("[Thread] Thread waiting to be started: %d\n", self->id);

    // Park here until this context is signalled (by osStartThread, or by a destroy).
    try {
        wait_for_resumed(PASS_RDRAM ctx);
    } catch (ultramodern::thread_terminated&) {
    }

    // Only run the body if we're still the live context for this OSThread; a destroy that
    // arrived while we were parked clears it.
    if (self->context == ctx) {
        debug_printf("[Thread] Thread started: %d\n", self->id);
        try {
            // Hand off to the recompiled entrypoint with the supplied argument.
            run_thread_function(PASS_RDRAM entrypoint, self->sp, arg);
        } catch (ultramodern::thread_terminated&) {
        }
    }
    else {
        debug_printf("[Thread] Thread destroyed before being started: %d\n", self->id);
    }

    // If the body returned (or terminated) without the context having been swapped out
    // from under us, this thread ended on its own: drop our context and let the scheduler
    // advance to the next runnable thread.
    if (self->context == ctx) {
        self->context = nullptr;
        if (!run_next_thread(PASS_RDRAM1)) {
            // This thread is genuinely exiting and no other thread can be handed
            // control: there is nothing left to keep the emulation running.
            throw std::runtime_error("No runnable threads remain!\n");
        }
    }

    // Hand the context to the cleaner thread for join + delete.
    ultramodern::cleanup_thread(ctx);
}

extern "C" void osStartThread(RDRAM_ARG PTR(OSThread) t_) {
    OSThread* t = TO_PTR(OSThread, t_);
    debug_printf("[os] Start Thread %d\n", t->id);

    if (thread_self) {
        // Invoked from inside a game thread: enqueue and let the scheduler decide.
        ultramodern::schedule_running_thread(PASS_RDRAM t_);
        ultramodern::check_running_queue(PASS_RDRAM1);
    }
    else {
        // Invoked from outside the game (the initial start): wake the thread directly.
        {
#ifdef N64_COSIM
            ultramodern::CosimSchedulerMutation cosim_mutation;
#endif
            t->state = OSThreadState::QUEUED;
        }
        resume_thread(PASS_RDRAM t);
        //throw ultramodern::thread_terminated{};
    }
}

#if defined(__ANDROID__)
// pthread entry shim: std::thread cannot take a stack-size attribute, so the
// arguments run_game_thread needs are boxed and handed through a void*.
struct GuestThreadStart {
    uint8_t* rdram;
    PTR(OSThread) self;
    PTR(thread_func_t) entrypoint;
    PTR(void) arg;
    UltraThreadContext* ctx;
};

static void* guest_thread_trampoline(void* raw) {
    GuestThreadStart* start = static_cast<GuestThreadStart*>(raw);
    GuestThreadStart local = *start;
    delete start;
    run_game_thread(local.rdram, local.self, local.entrypoint, local.arg, local.ctx);
    return nullptr;
}
#endif

extern "C" void osCreateThread(RDRAM_ARG PTR(OSThread) t_, OSId id, PTR(thread_func_t) entrypoint, PTR(void) arg, PTR(void) sp, OSPri pri) {
    debug_printf("[os] Create Thread %d\n", id);
    OSThread *t = TO_PTR(OSThread, t_);

    // A game can reinitialize an OSThread struct that is still linked into a
    // scheduler queue (e.g. a prior thread at this same guest address was
    // queued as runnable but never actually popped/run before being
    // recreated). Unlink it first so the stale node doesn't keep sitting in
    // that queue under the new thread's identity — the queue would otherwise
    // later hand control to a node whose fields no longer describe the
    // thread that was queued, or (once that new thread exits) to a dead one.
    if (t->queue != NULLPTR) {
        static std::atomic_flag reported = ATOMIC_FLAG_INIT;
        if (!reported.test_and_set()) {
            fprintf(stderr,
                "[thread] osCreateThread(id=%d): target OSThread was still linked in "
                "queue 0x%08X (old id=%d); unlinking stale entry before reinit\n",
                id, (uint32_t)t->queue, t->id);
            fflush(stderr);
        }
        ultramodern::thread_queue_remove(PASS_RDRAM t->queue, t_);
    }

    {
#ifdef N64_COSIM
        ultramodern::CosimSchedulerMutation cosim_mutation;
#endif
        t->next = NULLPTR;
        t->queue = NULLPTR;
        t->priority = pri;
        t->id = id;
        t->state = OSThreadState::STOPPED;
        t->sp = sp - 0x10; // Set up the first stack frame
    }

    // Launch the host thread; it parks itself immediately (see run_game_thread) and waits
    // to be started. The context is passed in as an argument so a later clear of t->context
    // can't race the thread reading its own context.
    UltraThreadContext* ctx = new UltraThreadContext{};
    ultramodern_context_register(ctx);
    t->context = ctx;
#if defined(__ANDROID__)
    {
        // 64 MB: the deepest chain measured (Stadium 2's PC-relative dispatch
        // helper) passes depth 1000, and each level costs two recompiled
        // frames. Virtual reservation only — pages are committed on use.
        static constexpr size_t ultramodern_guest_stack_bytes = 64u * 1024u * 1024u;
        GuestThreadStart* start = new GuestThreadStart{rdram, t_, entrypoint, arg, t->context};
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, ultramodern_guest_stack_bytes);
        int rc = pthread_create(&ctx->host_thread, &attr, guest_thread_trampoline, start);
        pthread_attr_destroy(&attr);
        if (rc != 0) {
            // Fall back to the default stack rather than losing the thread.
            delete start;
            start = new GuestThreadStart{rdram, t_, entrypoint, arg, t->context};
            rc = pthread_create(&ctx->host_thread, nullptr, guest_thread_trampoline, start);
        }
        if (rc != 0) {
            delete start;
            fprintf(stderr, "[os] FATAL: could not create host thread for guest thread %d\n", t->id);
            fflush(stderr);
            std::abort();
        }
        ctx->host_thread_valid = true;
    }
#else
    ctx->host_thread = std::thread{run_game_thread, PASS_RDRAM t_, entrypoint, arg, t->context};
#endif

    // Block until the host thread reports it has initialized.
    ctx->initialized.wait();
    debug_printf("[os] Thread %d is ready to be started\n", t->id);
}

extern "C" void osStopThread(RDRAM_ARG PTR(OSThread) t_) {
    if (t_ == NULLPTR) {
        t_ = thread_self;
    }
    // The only supported case is a thread stopping itself (arg null or thread_self).
    if (t_ == thread_self) {
        ultramodern::run_next_thread_and_wait(PASS_RDRAM1);
    }
    else {
        assert(false);
    }
}

extern "C" void osDestroyThread(RDRAM_ARG PTR(OSThread) t_) {
    if (t_ == NULLPTR) {
        t_ = thread_self;
    }
    OSThread* t = TO_PTR(OSThread, t_);
    // A thread destroying itself (arg null or thread_self) unwinds via the termination exception.
    if (t_ == thread_self) {
        throw ultramodern::thread_terminated{};
    }
    // Destroying another thread: detach it from whatever queue currently holds it.
    if (t->state != OSThreadState::STOPPED) {
        ultramodern::thread_queue_remove(PASS_RDRAM t->queue, t_);
    }
    // Clear the context (guarding against a double destroy) then wake the thread; it will
    // see the cleared context on resume and terminate itself instead of running.
    UltraThreadContext* target_ctx = t->context;
    if (target_ctx != nullptr) {
        t->context = nullptr;
        target_ctx->running.signal();
    }
}

extern "C" void osSetThreadPri(RDRAM_ARG PTR(OSThread) t_, OSPri pri) {
    if (t_ == NULLPTR) {
        t_ = thread_self;
    }
    OSThread* t = TO_PTR(OSThread, t_);

    if (t->priority != pri) {
        {
#ifdef N64_COSIM
            ultramodern::CosimSchedulerMutation cosim_mutation;
#endif
            t->priority = pri;

            // A thread that is queued somewhere must be re-inserted so the queue order tracks
            // its new priority. The running thread isn't in a queue, so it's skipped.
            if (t_ != ultramodern::this_thread() && t->state != OSThreadState::STOPPED) {
                ultramodern::thread_queue_remove(PASS_RDRAM t->queue, t_);
                ultramodern::thread_queue_insert(PASS_RDRAM t->queue, t_);
            }
        }

        ultramodern::check_running_queue(PASS_RDRAM1);
    }
}

extern "C" OSPri osGetThreadPri(RDRAM_ARG PTR(OSThread) t) {
    if (t == NULLPTR) {
        t = thread_self;
    }
    return TO_PTR(OSThread, t)->priority;
}

extern "C" OSId osGetThreadId(RDRAM_ARG PTR(OSThread) t) {
    if (t == NULLPTR) {
        t = thread_self;
    }
    return TO_PTR(OSThread, t)->id;
}

PTR(OSThread) ultramodern::this_thread() {
    return thread_self;
}

static std::thread thread_cleaner_thread;
static moodycamel::BlockingConcurrentQueue<UltraThreadContext*> deleted_threads{};
extern std::atomic_bool exited;

void thread_cleaner_func() {
    using namespace std::chrono_literals;
    // A thread can't join itself, so completed contexts are funnelled here to be joined and
    // freed from a separate thread.
    while (!exited) {
        UltraThreadContext* to_delete;
        if (deleted_threads.wait_dequeue_timed(to_delete, 10ms)) {
            debug_printf("[Cleanup] Deleting thread context %p\n", to_delete);

#if defined(__ANDROID__)
            if (to_delete->host_thread_valid) {
                pthread_join(to_delete->host_thread, nullptr);
                to_delete->host_thread_valid = false;
            }
#else
            to_delete->host_thread.join();
#endif
            ultramodern_context_unregister(to_delete);
            delete to_delete;
        }
    }
}

void ultramodern::init_thread_cleanup() {
    thread_cleaner_thread = std::thread{thread_cleaner_func};
}

void ultramodern::cleanup_thread(UltraThreadContext *cur_context) {
    deleted_threads.enqueue(cur_context);
}

void ultramodern::join_thread_cleaner_thread() {
    thread_cleaner_thread.join();
}
