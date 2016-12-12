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
    in_kernel++;
    for (i = 0; i < tcb_count; ++i) {
        if (tcb[i].state == RUNNING) {
            break;
        }
    }
    if (i == tcb_count) i = -1;
    in_kernel--;
    return i;
}

int far get_next_running_thread_id() {
    int last = get_last_running_thread_id();
    int i;
    if (last == -1) { /* system idle */
        if (tcb_count == 0) { /* no threads waiting */
            lprintf(WARNING, "System idle.\n");
            return -1;
        } else {
            for (i = 0; i < tcb_count; ++i) {
                if (tcb[i].state == READY) {
                    return i;
                }
            }
            lprintf(CRITICAL, "DEADLOCK DETECTED!\n");
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
        lprintf(WARNING, "Cannot find next ready thread.\n");
        return last;
    }
}

int far thread_end_trigger() {
    int last;
    in_kernel++;
    last = get_last_running_thread_id();
    lprintf(DEBUG, "Thread #%d end.\n", last);
    if (last >= 0) destroy(last);
    lprintf(INFO, "Thread end trigger finished.\n");
    print_tcb();
    in_kernel--;
    // geninterrupt(TIME_INT);
    return 0;
}

int far create(char far *name, func thread_function, size_t stacklen) {
    int_regs far *regs;
    in_kernel++;
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
    regs = (int_regs far *)((unsigned far *)tcb[tcb_count].stack + stacklen) - 1;
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
    in_kernel--;
    return tcb_count;
};

int far destroy(int id) {
    int i;
    in_kernel++;
    if (id >= tcb_count) {
        lprintf(CRITICAL, "Cannot destroy thread #%d", id);
        goto exit_destroy;
    }
    lprintf(DEBUG, "Destroing thread %s\n", tcb[id].name);
    free(tcb[id].stack);
    for (i = id + 1; i < MAX_THREAD_COUNT - id; ++i) {
        memcpy(tcb + i - 1, tcb + i, sizeof(s_TCB));
    }
    --tcb_count;
    lprintf(INFO, "Thread destroied.\n");
    print_tcb();
exit_destroy:
    in_kernel--;
    return 0;
};

void interrupt timeslicehandler(void) {
    int last_running_thread;
    int next_running_thread;
    (*oldtimeslicehandler)();
    lprintf(INFO, "Time slice reached.\n");
    begin_transaction();
    if (DosBusy() || in_kernel) {
        goto exit_scheduler_in_kernel;
    }
    in_kernel++;
    if(schedule_reent) {
        goto exit_scheduler_reent;
    }
    schedule_reent = 1;
    end_transaction();
    printf(INFO, "Starting scheduler...\n");
    // thread switching
    print_tcb();
    last_running_thread = get_last_running_thread_id();
    next_running_thread = get_next_running_thread_id();
    /* context switching */
    if (last_running_thread >= 0) {
        lprintf(INFO, "Saving state of thread #%d:%s\n", last_running_thread, tcb[last_running_thread].name);
        lprintf(DEBUG, "SS:SP in TCB: %Np:%Np; Current: %Np:%Np; Diff: %d:%d\n",
            tcb[last_running_thread].ss,
            tcb[last_running_thread].sp,
            _SS,
            _SP,
            tcb[last_running_thread].ss - _SS,
            tcb[last_running_thread].sp - _SP
        );
        begin_transaction();
        tcb[last_running_thread].state = READY;
        tcb[last_running_thread].ss = _SS;
        tcb[last_running_thread].sp = _SP;
        end_transaction();
    } else { /* when threads start */
    }
    if (next_running_thread >= 0) {
        lprintf(INFO, "Switching to thread #%d:%s\n", next_running_thread, tcb[next_running_thread].name);
        begin_transaction();
        tcb[next_running_thread].state = RUNNING;
        _SS = tcb[next_running_thread].ss;
        _SP = tcb[next_running_thread].sp;
        end_transaction();
    } else { /* when threads end */
        lprintf(INFO, "All threads have an end.\n");
        tcb_count = 0;
        cleanup();
    }
    print_tcb();
    // thread switching end
exit_scheduler:
    lprintf(INFO, "Switching finished.\n");
    schedule_reent = 0;
exit_scheduler_reent:
    lprintf(INFO, "Time slice handler quit.\n");
    in_kernel--;
    return;
exit_scheduler_in_kernel:
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

/* broken */
int tconvert(char *X)
{
    in_kernel++;
    lprintf(DEBUG, "Converting current process to thread #%d:%s\n", tcb_count, (X));
    if (tcb_count >= MAX_THREAD_COUNT) {
        lprintf(CRITICAL, "TCB stack full");
        return -1;
    }
    tcb[tcb_count].ss = _SS;
    tcb[tcb_count].sp = _SP;
    tcb[tcb_count].state = RUNNING;
    tcb[tcb_count].stack = 0;
    strcpy(tcb[tcb_count].name, (X));
    ++tcb_count;
    lprintf(INFO, "Converting thread %s finished.\n", (X));
    in_kernel--;
    print_tcb();
    return 0;
}
