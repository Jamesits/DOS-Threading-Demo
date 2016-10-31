#include <DOS.h>
#include <stdio.h>
#include <string.h>

/* 0x1C is usable */
#define TIME_INT 0x08
#define NTCB 32
enum THREAD_STATUS {FINISHED, RUNNING, READY, BLOCKED};

typedef struct TCB{
    unsigned char *stack;       /* thread stack start ptr */
    unsigned ss;                /* stack segment */
    unsigned sp;                /* thread in-stack offset */
    enum THREAD_STATUS state;
    char name[32];
} s_TCB;

struct int_regs {
    unsigned bp,di,si,ds,es,dx,cx,bx,ax,ip,cs,flags,off,seg;
};

s_TCB tcb[NTCB];
int tcb_count = 0;

typedef int (far *func)(void);
void interrupt (*oldtimeslicehandler)(void);

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
            printf("System idle.\n");
            return -1;
        } else {
            for (i = 0; i < tcb_count; ++i) {
                if (tcb[i].state == READY) {
                    return i;
                }
            }
            printf("All threads blocked.\n");
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
        printf("All threads blocked.\n");
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
    printf("Thread end.\n");
    print_tcb();
    last = get_last_running_thread_id();
    if (last >= 0) destroy(last);
    enable();
    timeslicehandler();
    return 0;
}

int create(char *name, func thread_function, size_t stacklen) {
    struct int_regs regs;
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
    print_tcb();
    return tcb_count;
};

int destroy(int id) {
    if (id >= NTCB) {
        printf("Cannot destory thread #%d", id);
        return -1;
    }
    printf("Destoring thread %s\n", tcb[id].name);
    tcb[id].state = FINISHED;
    // free(tcb[id].stack);
    // memcpy(tcb + id * sizeof(s_TCB), tcb + (id + 1) * sizeof(s_TCB), (NTCB - id - 1) * sizeof(s_TCB));
    // --tcb_count;
    print_tcb();
    return 0;
};

void interrupt timeslicehandler(void) {
    int last_running_thread;
    int next_running_thread;
    disable();
    printf("interrupt\n");
    print_tcb();
    /* context switching */
    if ((last_running_thread = get_last_running_thread_id()) >= 0) {
        tcb[last_running_thread].state = READY;
        tcb[last_running_thread].ss = _SS;
        tcb[last_running_thread].sp = _SP;
    }
    if ((next_running_thread = get_next_running_thread_id()) >= 0) {
        tcb[next_running_thread].state = RUNNING;
        _SS = tcb[next_running_thread].ss;
        _SP = tcb[next_running_thread].sp;
    }
    enable();
}

int far fp1() {
    int i = 5;
    while(--i) {
        printf("This is fp1\n");
        delay(1000);
    }
    return 0;
}

int far fp2() {
    int i = 5;
    while(--i) {
        printf("This is fp2\n");
        delay(1000);
    }
    return 0;
}

int main() {
    oldtimeslicehandler = getvect(TIME_INT);
    setvect(TIME_INT, timeslicehandler);
    create("FP1", (func)fp1, 1024);
    create("FP2", (func)fp2, 1024);
    while(!tcb_count);
    while(tcb_count);
    setvect(TIME_INT, oldtimeslicehandler);
    return 0;
}
