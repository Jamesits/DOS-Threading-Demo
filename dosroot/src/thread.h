#ifndef __THREAD_H__
#define __THREAD_H__
#include <DOS.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usercode.h"

/* consts */
#define MAX_THREAD_COUNT 32
#define TCB_NAME_LEN 32

#define TIME_SLICE_MULTIPLER 2
#define DEFAULT_THREAD_STACK_SIZE 1024
#define DEFAULT_CPU_FLAGS 0x200
typedef enum THREAD_STATUS {FINISHED, RUNNING, READY, BLOCKED, INIT_BLOCKED} THREAD_STATUS;

/* thread control block */
typedef struct TCB {
    void far *stack;       /* thread stack start ptr */
    unsigned ss;                /* stack segment */
    unsigned sp;                /* thread in-stack offset */
    THREAD_STATUS state;
    struct TCB * next;
    char name[TCB_NAME_LEN];
} s_TCB;

/* stack initializer */
typedef struct int_regs {
    unsigned bp, di, si, ds, es, dx, cx, bx, ax, ip, cs, flags, off, seg;
} int_regs;

/* thread caller function type */
typedef int (far *func)(void);

/* function declaration */
int far create(char far *name, func thread_function, size_t stacklen);
int far destroy(int id);
int far thread_end_trigger();
void interrupt timeslicehandler(void);
int far get_last_running_thread_id();
int far get_next_running_thread_id();
void far set_thread_state(int id, THREAD_STATUS new_state);
void far block_myself();

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
                tcb[tcb_count].stack = 0; \
                strcpy(tcb[tcb_count].name, (X)); \
                ++tcb_count; \
                lprintf(INFO, "Converting thread %s finished.\n", (X)); \
                print_tcb(); \
                end_transaction(); \
        }
#endif
