#include <DOS.h>
#include <stdio.h>
#include <string.h>

#define DEBUG

/* consts */
/* 0x1C is usable */
#define TIME_INT 0x1C
#define NTCB 32
enum THREAD_STATUS {FINISHED, RUNNING, READY, BLOCKED};

/* thread control block */
typedef struct TCB{
    unsigned char *stack;       /* thread stack start ptr */
    unsigned ss;                /* stack segment */
    unsigned sp;                /* thread in-stack offset */
    enum THREAD_STATUS state;
    char name[32];
} s_TCB;

/* stack initializer */
struct int_regs {
    unsigned bp,di,si,ds,es,dx,cx,bx,ax,ip,cs,flags,off,seg;
};

/* thread caller function type */
typedef int (far *func)(void);

/* variables */
s_TCB tcb[NTCB];
int tcb_count = 0;
void interrupt (*oldtimeslicehandler)(void);
int ss, sp;

/* function declaration */
int create(char *name, func thread_function, size_t stacklen);
int destroy(int id);
int far thread_end_trigger();
void interrupt timeslicehandler(void);
int far fp1();
int far fp2();
int main();
void print_tcb();
int get_last_running_thread_id();
int get_next_running_thread_id();

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

void print_tcb() {
    int i;
    printf(">>>> TCB status\n");
    printf("Last running: %d, Next running: %d\n", get_last_running_thread_id(), get_next_running_thread_id());
    printf("ID\tName\tStack\tState\n");
    for (i = 0; i < tcb_count; ++i) {
        printf("%d\t%s\t0x%X\t%d\n", i, tcb[i].name, tcb[i].stack, tcb[i].state);
    }
}

int far thread_end_trigger() {
    int last;
    disable();
#ifdef DEBUG
    print_tcb();
#endif
    last = get_last_running_thread_id();
    printf("Thread #%d end.\n", last);
    if (last >= 0) destroy(last);
#ifdef DEBUG
    printf("Thread end trigger finished.\n");
#endif
    timeslicehandler();
    enable();
    return 0;
}

int create(char *name, func thread_function, size_t stacklen) {
    struct int_regs regs;
    disable();
    printf("Creating thread %s\n", name);
    if (tcb_count >= NTCB) {
        printf("TCB stack full");
        return -1;
    }
    tcb[tcb_count].stack = malloc(stacklen);
    tcb[tcb_count].ss = FP_SEG(tcb[tcb_count].stack);
    tcb[tcb_count].sp = FP_OFF(tcb[tcb_count].stack);
    tcb[tcb_count].state = READY;
    regs.cs = FP_SEG(thread_function);
    regs.ip = FP_OFF(thread_function);
    regs.ds = FP_SEG(tcb[tcb_count].stack);
    regs.es = FP_SEG(tcb[tcb_count].stack);
    regs.seg = FP_SEG(thread_end_trigger);
    regs.off = FP_OFF(thread_end_trigger);
    memcpy(tcb[tcb_count].stack, &regs, sizeof(regs));
    strcpy(tcb[tcb_count].name, name);
    ++tcb_count;
#ifdef DEBUG
    print_tcb();
    printf("Creating thread %s finished.\n", name);
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
    printf("Destoring thread %s\n", tcb[id].name);
    tcb[id].state = FINISHED;
    free(tcb[id].stack);
    for (i = id + 1; i < NTCB - id; ++i) {
        memcpy(tcb + i - 1, tcb + i, sizeof(s_TCB));
    }
    --tcb_count;
#ifdef DEBUG
    print_tcb();
    printf("Thread %s destoried.\n", tcb[id].name);
#endif
    enable();
    return 0;
};

void interrupt timeslicehandler(void) {
    int last_running_thread;
    int next_running_thread;
    disable();
#ifdef DEBUG
    printf("Time slice reached.\n");
    print_tcb();
#endif
    /* context switching */
    if ((last_running_thread = get_last_running_thread_id()) >= 0) {
        tcb[last_running_thread].state = READY;
        tcb[last_running_thread].ss = _SS;
        tcb[last_running_thread].sp = _SP;
    } else { /* remember when threads start */
        printf("No thread has ever been runned.\n");
        /*
        ss = _SS;
        sp = _SP;
        */
    }
    if ((next_running_thread = get_next_running_thread_id()) >= 0) {
        tcb[next_running_thread].state = RUNNING;
        _SS = tcb[next_running_thread].ss;
        _SP = tcb[next_running_thread].sp;
    } else { /* remember when threads end */
        printf("All threads have an end.\n");
        _SS = ss;
        _SP = sp;
        tcb_count = 0;
        /* setvect(TIME_INT, oldtimeslicehandler); */
    }
#ifdef DEBUG
    printf("Time slice started again.\n");
    print_tcb();
#endif
    enable();
}

int far fp1() {
    int i = 10;
    while(--i) {
        printf("This is fp1\n");
        delay(200);
    }
    return 0;
}

int far fp2() {
    int i = 10;
    while(--i) {
        printf("This is fp2\n");
        delay(200);
    }
    return 0;
}

int main() {
    create("FP1", (func)fp1, 1024);
    create("FP2", (func)fp2, 1024);
    disable();
    ss = _SS;
    sp = _SP;
    oldtimeslicehandler = getvect(TIME_INT);
    setvect(TIME_INT, timeslicehandler);
    timeslicehandler();
    enable();

    while(!tcb_count) { printf("Main thread waiting for thread creation.\n"); }
    while(tcb_count) { printf("Main thread waiting for thread end.\n"); }
    
    setvect(TIME_INT, oldtimeslicehandler);
    return 0;
}
