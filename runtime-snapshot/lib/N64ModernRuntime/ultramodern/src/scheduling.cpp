#include "ultramodern/ultramodern.hpp"

void ultramodern::schedule_running_thread(RDRAM_ARG PTR(OSThread) t_) {
    // Callers include `schedule_running_thread(thread_queue_pop(blocked_queue))`
    // in do_send/do_recv, and thread_queue_pop legitimately returns NULLPTR
    // when it finds a corrupt queue head (it severs the bad chain and reports
    // empty). Dereferencing that NULL faults, so treat "nothing to schedule"
    // as a no-op instead.
    if (t_ == NULLPTR) {
        return;
    }
    debug_printf("[Scheduling] Queueing thread %d to run\n", TO_PTR(OSThread, t_)->id);
    ultramodern::scheduler_trace_mark(PASS_RDRAM 100, ultramodern::running_queue, t_);
#ifdef N64_COSIM
    ultramodern::CosimSchedulerMutation cosim_mutation;
#endif
    thread_queue_insert(PASS_RDRAM running_queue, t_);
    TO_PTR(OSThread, t_)->state = OSThreadState::QUEUED;
}

void swap_to_thread(RDRAM_ARG PTR(OSThread) to_) {
    OSThread* to = TO_PTR(OSThread, to_);
    debug_printf("[Scheduling] Thread %d handing the CPU to thread %d\n", TO_PTR(OSThread, ultramodern::this_thread())->id, to->id);
    ultramodern::scheduler_trace_mark(PASS_RDRAM 110, ultramodern::running_queue, to_);
    // Put the currently executing thread back into the running queue so it can be
    // picked up again later.
    {
#ifdef N64_COSIM
        ultramodern::CosimSchedulerMutation cosim_mutation;
#endif
        ultramodern::thread_queue_insert(PASS_RDRAM ultramodern::running_queue, ultramodern::this_thread());
        ultramodern::scheduler_trace_mark(PASS_RDRAM 111, ultramodern::running_queue, ultramodern::this_thread());
        TO_PTR(OSThread, ultramodern::this_thread())->state = OSThreadState::QUEUED;
    }
    // Wake the target thread and block here until something wakes us back up.
    ultramodern::scheduler_trace_mark(PASS_RDRAM 112, ultramodern::running_queue, to_);
    ultramodern::resume_thread_and_wait(PASS_RDRAM to);
    ultramodern::scheduler_trace_mark(PASS_RDRAM 113, ultramodern::running_queue, to_);
}

void ultramodern::check_running_queue(RDRAM_ARG1) {
    // Nothing waiting to run means there is nothing to switch to.
    if (thread_queue_empty(PASS_RDRAM running_queue)) {
        ultramodern::scheduler_trace_mark(PASS_RDRAM 101, running_queue, NULLPTR);
        return;
    }

    // The queue is ordered by priority, so the front entry is the best candidate.
    // Only preempt the current thread if that candidate outranks it.
    PTR(OSThread) next_ = ultramodern::thread_queue_peek(PASS_RDRAM running_queue);
    OSThread* next_thread = TO_PTR(OSThread, next_);
    OSThread* self = TO_PTR(OSThread, ultramodern::this_thread());
    ultramodern::scheduler_trace_mark(PASS_RDRAM 102, running_queue, next_);
    if (next_thread->priority > self->priority) {
        ultramodern::scheduler_trace_mark(PASS_RDRAM 104, running_queue, next_);
        ultramodern::thread_queue_pop(PASS_RDRAM running_queue);
        // Hand execution to the higher priority thread.
        swap_to_thread(PASS_RDRAM next_);
    } else {
        ultramodern::scheduler_trace_mark(PASS_RDRAM 103, running_queue, next_);
    }
}

extern "C" void pause_self(RDRAM_ARG1) {
    while (true) {
        // Block until woken by an external message, then re-evaluate the queue.
        ultramodern::wait_for_external_message(PASS_RDRAM1);
        ultramodern::check_running_queue(PASS_RDRAM1);
    }
}

extern "C" void yield_self(RDRAM_ARG1) {
    ultramodern::wait_for_external_message(PASS_RDRAM1);
    ultramodern::check_running_queue(PASS_RDRAM1);
}

extern "C" void yield_self_1ms(RDRAM_ARG1) {
    ultramodern::wait_for_external_message_timed(PASS_RDRAM1, 1);
    ultramodern::check_running_queue(PASS_RDRAM1);
}
