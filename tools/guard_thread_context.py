#!/usr/bin/env python3
"""Never dereference a thread context that is not known-live.

UltraThreadContext* lives in the OSThread struct, which is guest RDRAM. Both
retirement paths already null the field, so a non-null stale value means the
guest wrote over the struct — and resume_thread then signals a freed context
and takes SIGSEGV:

    #01 ultramodern::resume_thread_and_wait(...)+108
    #02 ultramodern::yield_to_any_queued(...)+208
    #03 func_826040D8+1668            <- guest fragment code

Keep a registry of live contexts and check membership before use. A thread
whose context is unknown is treated as not resumable: the scheduler moves on
instead of dying, and the event is reported once with the offending values.
"""
import os
import shutil

P = "/Users/michaegg/psr-recomp-build/work/lib/N64ModernRuntime/ultramodern/src/threads.cpp"
t = open(P, encoding="utf-8", newline="").read()
nl = "\r\n" if "\r\n" in t else "\n"


def fit(s):
    return s.replace("\n", nl)


assert "ultramodern_context_is_live" not in t, "already applied"

# --- registry -------------------------------------------------------------
reg_anchor = fit("void wait_for_resumed(RDRAM_ARG UltraThreadContext* thread_context) {")
assert t.count(reg_anchor) == 1

registry = fit("""// Live-context registry. A thread's UltraThreadContext* is stored in its
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

""")
t = t.replace(reg_anchor, registry + reg_anchor, 1)

# --- includes -------------------------------------------------------------
inc_anchor = fit("#include <string>")
assert t.count(inc_anchor) == 1
t = t.replace(inc_anchor, inc_anchor + fit("\n#include <mutex>\n#include <unordered_set>"), 1)

# --- resume_thread: refuse unknown contexts -------------------------------
resume_old = fit("""void resume_thread(RDRAM_ARG OSThread* t) {
    debug_printf("[Thread] Waking thread %d\\n", t->id);
    ultramodern::scheduler_trace_mark(PASS_RDRAM 122, NULLPTR, NULLPTR);
    t->context->running.signal();
}""")
assert t.count(resume_old) == 1, t.count(resume_old)
resume_new = fit("""bool resume_thread(RDRAM_ARG OSThread* t) {
    debug_printf("[Thread] Waking thread %d\\n", t->id);
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
                "(OSThread at guest memory was likely overwritten)\\n",
                t->id, (void*)ctx);
            fflush(stderr);
        }
        return false;
    }
    ctx->running.signal();
    return true;
}""")
t = t.replace(resume_old, resume_new, 1)

# --- resume_thread_and_wait: don't block if the resume was refused --------
raw_old = fit("""    resume_thread(PASS_RDRAM t);
    wait_for_resumed(PASS_RDRAM caller_ctx);""")
assert t.count(raw_old) == 1, t.count(raw_old)
raw_new = fit("""    if (!resume_thread(PASS_RDRAM t)) {
        // Nothing was woken, so nothing will ever wake us: keep running rather
        // than blocking forever on our own context.
        return;
    }
    wait_for_resumed(PASS_RDRAM caller_ctx);""")
t = t.replace(raw_old, raw_new, 1)

# --- register on create, unregister on delete -----------------------------
create_old = fit("    UltraThreadContext* ctx = new UltraThreadContext{};")
assert t.count(create_old) == 1
t = t.replace(create_old, create_old + fit("\n    ultramodern_context_register(ctx);"), 1)

del_old = fit("""            to_delete->host_thread.join();
            delete to_delete;""")
assert t.count(del_old) == 1
t = t.replace(del_old, fit("""            to_delete->host_thread.join();
            ultramodern_context_unregister(to_delete);
            delete to_delete;"""), 1)

if not os.path.exists(P + ".ctxguard.orig"):
    shutil.copy2(P, P + ".ctxguard.orig")
open(P, "w", encoding="utf-8", newline="").write(t)
print("OK live-context guard installed")
