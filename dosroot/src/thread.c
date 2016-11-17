#include "thread.h"
#include "debug.h"

/* variables */
s_TCB tcb[NTCB];
int tcb_count = 0;
void interrupt (*oldtimeslicehandler)(void);
int time_slice_counter = TIME_SLICE_MULTIPLER;

/* function definition */
int get_last_running_thread_id() {
    int i;
    for (i = 0; i < tcb_count; ++i) {
        if (tcb[i].state == RUNNING) {
            return i;
        }
    }
    return -1;
}

int get_next_running_thread_id() {
    int last = get_last_running_thread_id();
    int i;
    if (last == -1) { /* system idle */
        if (tcb_count == 0) { /* no threads waiting */
#ifdef DEBUG
            printf("System idle.\n");
#endif
            return -1;
        } else {
            for (i = 0; i < tcb_count; ++i) {
                if (tcb[i].state == READY) {
                    return i;
                }
            }
#ifdef DEBUG
            printf("All threads blocked.\n");
#endif
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
#ifdef DEBUG
        printf("All threads blocked.\n");
#endif
        return -1;
    }
}

int far thread_end_trigger() {
    int last;
    disable();
#ifdef DEBUG
    // print_tcb();
#endif
    last = get_last_running_thread_id();
#ifdef DEBUG
    printf("Thread #%d end.\n", last);
#endif
    if (last >= 0) destroy(last);
#ifdef DEBUG
    // printf("Thread end trigger finished.\n");
#endif
    timeslicehandler();
    enable();
    return 0;
}

int create(char far *name, func thread_function, size_t stacklen) {
    struct int_regs regs;
    disable();
    printf("Creating thread %s\n", name);
    if (tcb_count >= NTCB) {
        printf("TCB stack full");
        return -1;
    }
    tcb[tcb_count].stack = (unsigned char *)malloc(stacklen);
    tcb[tcb_count].ss = FP_SEG(tcb[tcb_count].stack);
    tcb[tcb_count].sp = (unsigned)(FP_OFF(tcb[tcb_count].stack) + (stacklen - sizeof(regs)));
    tcb[tcb_count].state = READY;
    regs.cs = FP_SEG(thread_function);
    regs.ip = FP_OFF(thread_function);
    regs.ds = FP_SEG(tcb[tcb_count].stack);
    regs.es = FP_SEG(tcb[tcb_count].stack);
    regs.seg = FP_SEG(thread_end_trigger);
    regs.off = FP_OFF(thread_end_trigger);
    regs.flags = 0x200;
    memcpy((void *)MK_FP(tcb[tcb_count].ss, tcb[tcb_count].sp), &regs, sizeof(regs));
    strcpy(tcb[tcb_count].name, (char *)name);
    ++tcb_count;
#ifdef DEBUG
    print_tcb();
    printf("Creating thread %s finished.\n", name);
    // exit(0);
#endif
    enable();
    return tcb_count;
};

int destroy(int id) {
    int i;
    disable();
    if (id >= NTCB) {
        printf("Cannot destory thread #%d", id);
        return -1;
    }
#ifdef DEBUG
    printf("Destoring thread %s\n", tcb[id].name);
    fflush(stdout);
#endif
    tcb[id].state = FINISHED;
    free(tcb[id].stack);
    for (i = id + 1; i < NTCB - id; ++i) {
        memcpy(tcb + i - 1, tcb + i, sizeof(s_TCB));
    }
    --tcb_count;
#ifdef DEBUG
    print_tcb();
    printf("Thread destoried.\n", tcb[id].name);
#endif
    enable();
    return 0;
};

void interrupt timeslicehandler(void) {
    int last_running_thread;
    int next_running_thread;

    oldtimeslicehandler();
    if (DosBusy()) {
#ifdef DEBUG
        printf("Time slice reached and DOS busy.\n");
#endif
        return;
    };
    disable();
    last_running_thread = get_last_running_thread_id();
    next_running_thread = get_next_running_thread_id();
#ifdef DEBUG
    printf("Time slice reached.\n");
    print_tcb();
#endif
    if (!DosBusy()) {
        /* context switching */
        if (last_running_thread >= 0) {
            tcb[last_running_thread].state = READY;
            tcb[last_running_thread].ss = _SS;
            tcb[last_running_thread].sp = _SP;
        } else { /* when threads start */
        }
        if (next_running_thread >= 0) {
            tcb[next_running_thread].state = RUNNING;
            _SS = tcb[next_running_thread].ss;
            _SP = tcb[next_running_thread].sp;
        } else { /* when threads end */
#ifdef DEBUG
            printf("All threads have an end.\n");
#endif
            tcb_count = 0;
#ifdef DEBUG
            print_tcb();
            PrintRegs();
#endif
            cleanup();
        }
    }
#ifdef DEBUG
    printf("Time slice started again.\n");
    print_tcb();
#endif
    enable();
}

void cleanup() {
#ifdef DEBUG
    printf("resetting time handler\n");
#endif
print_tcb();
    setvect(TIME_INT, oldtimeslicehandler);
    fflush(stdout);
    fflush(stderr);
    enable();
    exit(0);
}

int main() {
    InitDos();
    disable();
    oldtimeslicehandler = getvect(TIME_INT);
    setvect(TIME_INT, timeslicehandler);
#ifdef DEBUG
    PrintRegs();
#endif
    enable();
    usermain();
    for(;;) {
        asm { hlt }
    }
}
