#include <stdlib.h>
#include <alloc.h>
#include "thread.h"
#include "debug.h"
#include "main.h"

s_TCB far tcb[MAX_THREAD_COUNT];
int far tcb_count = 0;

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
        } else {
            for (i = 0; i < tcb_count; ++i) {
                if (tcb[i].state == READY) {
                    return i;
                }
            }
            lprintf(DEBUG, "All threads blocked at pos 0.\n");
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
        lprintf(DEBUG, "All threads blocked at pos 1.\n");
        return -1;
    }
}

int far thread_end_trigger() {
    int last;
    begin_transaction();
    last = get_last_running_thread_id();
    lprintf(DEBUG, "Thread #%d end.\n", last);
    if (last >= 0) destroy(last);
    lprintf(INFO, "Thread end trigger finished.\n");
    print_tcb();
    geninterrupt(TIME_INT);
    end_transaction();
    return 0;
}

int far create(char far *name, func thread_function, size_t stacklen) {
    struct int_regs regs;
    begin_transaction();
    lprintf(DEBUG, "Creating thread #%d:%s\n", tcb_count, name);
    if (tcb_count >= MAX_THREAD_COUNT) {
        lprintf(ERROR, "TCB stack full!");
        return -1;
    }
    tcb[tcb_count].stack = (unsigned char*)malloc(stacklen);
    if (!tcb[tcb_count].stack) {
            lprintf(ERROR, "Thread stack memory allocation failed!\n");
            return -1;
    }
    tcb[tcb_count].ss = FP_SEG(tcb[tcb_count].stack);
    tcb[tcb_count].sp = (unsigned)(FP_OFF(tcb[tcb_count].stack) + (stacklen - sizeof(regs)));
    tcb[tcb_count].state = READY;
    strcpy(tcb[tcb_count].name, (char *)name);
    lprintf(INFO, "TCB: %d\t%s\t0x%Fp\t0x%Np:0x%Np\t%d\n", tcb_count, tcb[tcb_count].name, tcb[tcb_count].stack, tcb[tcb_count].ss, tcb[tcb_count].sp, tcb[tcb_count].state);
    regs.cs = FP_SEG(thread_function);
    regs.ip = FP_OFF(thread_function);
    regs.ds = FP_SEG(tcb[tcb_count].stack);
    regs.es = FP_SEG(tcb[tcb_count].stack);
    regs.seg = FP_SEG(thread_end_trigger);
    regs.off = FP_OFF(thread_end_trigger);
    regs.flags = DEFAULT_CPU_FLAGS;
    movedata(FP_SEG(&regs), FP_OFF(&regs), tcb[tcb_count].ss, tcb[tcb_count].sp, sizeof(regs));
    // memcpy(MK_FP(tcb[tcb_count].ss, tcb[tcb_count].sp), &regs, sizeof(regs));
    ++tcb_count;
    lprintf(INFO, "Creating thread %s finished.\n", name);
    print_tcb();
    end_transaction();
    return tcb_count;
};

int far destroy(int id) {
    int i;
    begin_transaction();
    if (id >= MAX_THREAD_COUNT) {
        lprintf(CRITICAL, "Cannot destroy thread #%d", id);
        return -1;
    }
    lprintf(DEBUG, "Destroing thread %s\n", tcb[id].name);
    tcb[id].state = FINISHED;
    free(tcb[id].stack);
    for (i = id + 1; i < MAX_THREAD_COUNT - id; ++i) {
        memcpy(tcb + i - 1, tcb + i, sizeof(s_TCB));
    }
    --tcb_count;
    lprintf(INFO, "Thread destroied.\n", tcb[id].name);
    print_tcb();
    end_transaction();
    return 0;
};

void interrupt timeslicehandler(void) {
    int last_running_thread;
    int next_running_thread;

    oldtimeslicehandler();
    if (DosBusy()) {
        lprintf(INFO, "Time slice reached and DOS busy, skipping.\n");
        return;
    } else {
        lprintf(INFO, "Time slice reached.\n");
    };
    begin_transaction();
    print_tcb();
    last_running_thread = get_last_running_thread_id();
    next_running_thread = get_next_running_thread_id();
    if (!DosBusy()) {
        /* context switching */
        if (last_running_thread >= 0) {
            tcb[last_running_thread].state = READY;
            //tcb[last_running_thread].ss = _SS;
            //tcb[last_running_thread].sp = _SP;
        } else { /* when threads start */
        }
        if (next_running_thread >= 0) {
            tcb[next_running_thread].state = RUNNING;
            _SS = tcb[next_running_thread].ss;
            _SP = tcb[next_running_thread].sp;
        } else { /* when threads end */
            lprintf(INFO, "All threads have an end.\n");
            tcb_count = 0;
            cleanup();
        }
    }
    print_tcb();
    lprintf(INFO, "Time slice handler finished.\n");
    end_transaction();
}
