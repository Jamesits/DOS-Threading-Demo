#ifndef __THREAD_H__
#define __THREAD_H__
#include <DOS.h>
#include <stdio.h>
#include <string.h>
#include "usercode.h"

/* consts */
#define MAX_THREAD_COUNT 32
#define TCB_NAME_LEN 32

#define TIME_SLICE_MULTIPLER 2
#define DEFAULT_THREAD_STACK_SIZE 1024
#define DEFAULT_CPU_FLAGS 0x200
enum THREAD_STATUS {FINISHED, RUNNING, READY, BLOCKED};

/* thread control block */
typedef struct TCB {
    void far *stack;       /* thread stack start ptr */
    unsigned far ss;                /* stack segment */
    unsigned far sp;                /* thread in-stack offset */
    enum THREAD_STATUS far state;
    struct TCB * far next;
    char far name[TCB_NAME_LEN];
} s_TCB;

/* stack initializer */
struct int_regs {
    unsigned bp, di, si, ds, es, dx, cx, bx, ax, ip, cs, flags, off, seg;
};

/* thread caller function type */
typedef int (far *func)(void);

/* function declaration */
int far create(char far *name, func thread_function, size_t stacklen);
int far destroy(int id);
int far thread_end_trigger();
void interrupt timeslicehandler(void);
int far get_last_running_thread_id();
int far get_next_running_thread_id();

/* variables */
extern s_TCB far tcb[MAX_THREAD_COUNT];
extern int far tcb_count;

#define tconvert(X) \
        { \
                begin_transaction(); \
                lprintf(DEBUG, "Converting current process to thread #%d:%s\n", tcb_count, (X)); \
                if (tcb_count >= MAX_THREAD_COUNT) { \
                    lprintf(CRITICAL, "TCB stack full"); \
                    return -1; \
                } \
                tcb[tcb_count].ss = _SS; \
                tcb[tcb_count].sp = _SP; \
                tcb[tcb_count].state = RUNNING; \
                tcb[tcb_count].stack = MK_FP(tcb[tcb_count].ss, tcb[tcb_count].sp); \
                strcpy(tcb[tcb_count].name, (X)); \
                ++tcb_count; \
                lprintf(INFO, "Converting thread %s finished.\n", (X)); \
                print_tcb(); \
                end_transaction(); \
        }
#endif
