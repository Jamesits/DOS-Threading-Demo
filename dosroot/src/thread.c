#include <stdlib.h>
#include <alloc.h>
#include "thread.h"
#include "debug.h"
#include "main.h"
#include "dosutil.h"

s_TCB far tcb[MAX_THREAD_COUNT];
int far tcb_count = 0;
char schedule_reent = 0;
char in_kernel = 0;

int far get_last_running_thread_id() {
    int i;
    for (i = 0; i < tcb_count; ++i) {
        if (tcb[i].state == RUNNING) {
            return i;
        }
    }
    return -1;
}

int far get_next_running_thread_id() {
    int last = get_last_running_thread_id();
    int i;
    if (last == -1) { /* system idle */
        if (tcb_count == 0) { /* no threads waiting */
            lprintf(WARNING, "System idle.\n");
            return -1;
        } else if (tcb_count == 1 && tcb[0].state == INIT_BLOCKED) { /* only one thread */
            return 0;
        } else {
            for (i = 0; i < tcb_count; ++i) {
                if (tcb[i].state == READY) {
                    return i;
                }
            }
            lprintf(WARNING, "All threads blocked at pos 0.\n");
            return -1;
        }
    } else { /* context switching */
        for (i = last; i < tcb_count; ++i) {
            if (tcb[i].state == READY) {
                return i;
            }
        }
        for (i = 0; i <= last; ++i) {
            if (tcb[i].state == READY) {
                return i;
            }
        }
        lprintf(WARNING, "All threads blocked at pos 1.\n");
        return -1;
    }
}

int far thread_end_trigger() {
    int last;
    begin_transaction();
    in_kernel = 1;
    last = get_last_running_thread_id();
    lprintf(DEBUG, "Thread #%d end.\n", last);
    if (last >= 0) destroy(last);
    lprintf(INFO, "Thread end trigger finished.\n");
    print_tcb();
    geninterrupt(TIME_INT);
    in_kernel = 0;
    end_transaction();
    return 0;
}

int far create(char far *name, func thread_function, size_t stacklen) {
    int_regs far *regs;
    begin_transaction();
    in_kernel = 1;
    lprintf(DEBUG, "Creating thread #%d:%s\n", tcb_count, name);
    if (tcb_count >= MAX_THREAD_COUNT) {
        lprintf(ERROR, "TCB stack full!");
        goto exit_create;
    }
    tcb[tcb_count].stack = malloc(stacklen);
    if (!tcb[tcb_count].stack) {
            lprintf(ERROR, "Thread stack memory allocation failed!\n");
            goto exit_create;
    }
    regs = (int_regs far *)((unsigned far *)tcb[tcb_count].stack + stacklen);
    regs--;
    tcb[tcb_count].ss = FP_SEG(regs);
    tcb[tcb_count].sp = FP_OFF(regs);
    tcb[tcb_count].state = READY;
    strcpy(tcb[tcb_count].name, (char *)name);
    lprintf(INFO, "TCB: %d\t%s\t0x%Fp\t0x%Np:0x%Np\t%d\n", tcb_count, tcb[tcb_count].name, tcb[tcb_count].stack, tcb[tcb_count].ss, tcb[tcb_count].sp, tcb[tcb_count].state);
    regs->cs = FP_SEG(thread_function);
    regs->ip = FP_OFF(thread_function);
    regs->ds = _DS;
    regs->es = _ES;
    regs->seg = FP_SEG(thread_end_trigger);
    regs->off = FP_OFF(thread_end_trigger);
    regs->flags = DEFAULT_CPU_FLAGS;
    ++tcb_count;
    lprintf(INFO, "Creating thread %s finished.\n", name);
exit_create:
    print_tcb();
    in_kernel = 0;
    end_transaction();
    return tcb_count;
};

int far destroy(int id) {
    int i;
    begin_transaction();
    in_kernel = 1;
    if (id >= tcb_count) {
        lprintf(CRITICAL, "Cannot destroy thread #%d", id);
        goto exit_destroy;
    }
    lprintf(DEBUG, "Destroing thread %s\n", tcb[id].name);
    // tcb[id].state = FINISHED;
    free(tcb[id].stack);
    for (i = id + 1; i < MAX_THREAD_COUNT - id; ++i) {
        memcpy(tcb + i - 1, tcb + i, sizeof(s_TCB));
    }
    --tcb_count;
    lprintf(INFO, "Thread destroied.\n");
    print_tcb();
exit_destroy:
    in_kernel = 0;
    end_transaction();
    return 0;
};

void interrupt timeslicehandler(void) {
    int last_running_thread;
    int next_running_thread;

    oldtimeslicehandler();
    if (DosBusy() || in_kernel) {
        return;
    }

    begin_transaction();
    in_kernel = 1;
    lprintf(INFO, "Time slice reached.\n");
    if(schedule_reent) {
        lprintf(WARNING, "Re-entering scheduler, cancelling...\n");
        goto exit_scheduler;
    }
    schedule_reent = 1;
    if (!DosBusy()) {
        print_tcb();
        last_running_thread = get_last_running_thread_id();
        next_running_thread = get_next_running_thread_id();
        /* context switching */
        if (last_running_thread >= 0) {
            lprintf(INFO, "Saving state of thread #%d:%s\n", last_running_thread, tcb[last_running_thread].name);
            tcb[last_running_thread].state = READY;
            lprintf(DEBUG, "SS:SP:\n\tin TCB: %Np:%Np;\n\tCurrent: %Np:%Np\n\tDiff: %d:%d\n",
                tcb[last_running_thread].ss,
                tcb[last_running_thread].sp,
                _SS,
                _SP,
                tcb[last_running_thread].ss - _SS,
                tcb[last_running_thread].sp - _SP
            );
            tcb[last_running_thread].ss = _SS;
            tcb[last_running_thread].sp = _SP;
        } else { /* when threads start */
        }
        if (next_running_thread >= 0) {
            lprintf(INFO, "Switching to thread #%d:%s\n", next_running_thread, tcb[next_running_thread].name);
            tcb[next_running_thread].state = RUNNING;
            _SS = tcb[next_running_thread].ss;
            _SP = tcb[next_running_thread].sp;
        } else { /* when threads end */
            lprintf(INFO, "All threads have an end.\n");
            tcb_count = 0;
            end_transaction();
            cleanup();
        }
    }
    print_tcb();
    lprintf(INFO, "Time slice handler finished.\n");
    schedule_reent = 0;
    in_kernel = 0;
exit_scheduler:
    end_transaction();
}

void far set_thread_state(int id, THREAD_STATUS new_state) {
    lprintf(INFO, "Setting thread #%d to new state %d\n", id, new_state);
    tcb[id].state = new_state;
}

void far block_myself() {
    lprintf(WARNING, "Blocking current thread\n");
    set_thread_state(get_last_running_thread_id(), BLOCKED);
}
