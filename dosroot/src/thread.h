#ifndef __THREAD_H__
#define __THREAD_H__
#include <DOS.h>
#include <stdio.h>
#include <string.h>
#include "usercode.h"

/* consts */
#define NTCB 32
#define TCB_NAME_LEN 32

#define TIME_SLICE_MULTIPLER 2
#define DEFAULT_THREAD_STACK_SIZE 1024
enum THREAD_STATUS {FINISHED, RUNNING, READY, BLOCKED};

/* thread control block */
typedef struct TCB {
    unsigned char *stack;       /* thread stack start ptr */
    unsigned ss;                /* stack segment */
    unsigned sp;                /* thread in-stack offset */
    enum THREAD_STATUS state;
    struct TCB *next;
    char name[TCB_NAME_LEN];
} s_TCB;

/* stack initializer */
struct int_regs {
    unsigned bp,di,si,ds,es,dx,cx,bx,ax,ip,cs,flags,off,seg;
};

/* thread caller function type */
typedef int (far *func)(void);

/* function declaration */
int create(char far *name, func thread_function, size_t stacklen);
int destroy(int id);
void cleanup();
int far thread_end_trigger();
void interrupt timeslicehandler(void);
int main();
void print_tcb();
int get_last_running_thread_id();
int get_next_running_thread_id();

/* variables */
extern s_TCB tcb[NTCB];
extern int tcb_count;
#endif
