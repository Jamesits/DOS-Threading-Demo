#ifndef __THREAD_H__
#define __THREAD_H__
#include <DOS.h>
#include <stdio.h>
#include <string.h>
#include "usercode.h"

// #define DEBUG

/* consts */
/* 0x1C is usable */
#define TIME_INT 0x08
#define NTCB 32
#define TCB_NAME_LEN 32
#define GET_INDOS 0x34
#define GET_CRIT_ERR 0x5d06

#define TIME_SLICE_MULTIPLER 2
#define DEFAULT_THREAD_STACK_SIZE 1024
enum THREAD_STATUS {FINISHED, RUNNING, READY, BLOCKED};

#define PrintRegs() { \
    printf("AX=%04x BX=%04x CX=%04x DX=%04x CS=%04x DS=%04x SS=%04x ES=%04x SP=%04x BP=%04x\n", _AX, _BX, _CX, _DX, _CS, _DS, _SS, _ES, _SP, _BP); \
}

/* thread control block */
typedef struct TCB {
    unsigned char *stack;       /* thread stack start ptr */
    unsigned ss;                /* stack segment */
    unsigned sp;                /* thread in-stack offset */
    enum THREAD_STATUS state;
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
int far thread_end_trigger();
void interrupt timeslicehandler(void);
int main();
void print_tcb();
int get_last_running_thread_id();
int get_next_running_thread_id();
void InitDos(void);
int DosBusy(void);
#endif
