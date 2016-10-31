#include <DOS.h>
#include <stdio.h>
#include <string.h>

#define DEBUG

/* consts */
/* 0x1C is usable */
#define TIME_INT 0x1C
#define NTCB 32
#define TCB_NAME_LEN 32
#define GET_INDOS 0x34
#define GET_CRIT_ERR 0x5d06
enum THREAD_STATUS {FINISHED, RUNNING, READY, BLOCKED};

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

/* variables */
s_TCB tcb[NTCB];
int tcb_count = 0;
void interrupt (*oldtimeslicehandler)(void);
int ss, sp, cs, ds;
char far *indos_ptr = 0;  /*该指针变量存放INDOS标志的地址*/
char far *crit_err_ptr = 0;  /*该指针变量存放严重错误标志的地址*/

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
void InitDos(void);
int DosBusy(void);

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
    printf("Last running: %d, Next running: %d, DOS Busy: %d\n", get_last_running_thread_id(), get_next_running_thread_id(), DosBusy());
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
    regs.flags = 200;
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
        tcb_count = 0;
        setvect(TIME_INT, oldtimeslicehandler);
        print_tcb();
        _SS = ss;
        _SP = sp;
        _DS = ds;
        _CS = cs + 1;
    }
#ifdef DEBUG
    printf("Time slice started again.\n");
    print_tcb();
#endif
    enable();
}

/* InitDos()函数：功能是获得INDOS标志的地址和严重错误标志的地址 */
void InitDos(void)
{
    union REGS regs;
    struct SREGS segregs;

    /* 获得 INDOS 标志的地址 */
    regs.h.ah=GET_INDOS;
    /* intdosx() ：Turbo C的库函数，其功能是调用DOS的INT21H中断*/
    intdosx(&regs,&regs,&segregs);
    /* MK_FP()：不是一个函数，只是一个宏。*/
    /*其功能是做段基址加上偏移地址的运算，也就是取实际地址。 */
    indos_ptr=MK_FP(segregs.es,regs.x.bx);

    /*获得严重错误标志的地址 */
    /*代码中用到的_osmajor、_osminor是Turbo C的全程变量，其中前者为*/
    /*DOS版本号的主要部分，后者为版本号的次要部分。*/
    if (_osmajor<3) {
        crit_err_ptr=indos_ptr+1;
    } else if (_osmajor==3 && _osminor==0) {
        crit_err_ptr=indos_ptr-1;
    } else {
    regs.x.ax=GET_CRIT_ERR;
    intdosx(&regs,&regs,&segregs);
    crit_err_ptr=MK_FP(segregs.ds,regs.x.si);
  }
}

/* DosBusy()：函数功能是获得Indos标志及严重错误标志的值，判断是否dos忙：*/
/* 如果返回值是1，表示dos忙；*/
/* 如果返回值是0，表示dos不忙；*/
/* 如果返回值是-1，表示还没有调用InitDos() */
int DosBusy(void)
{
    if (indos_ptr && crit_err_ptr) {
        return (*indos_ptr || *crit_err_ptr);
    } else {
        return(-1);    /* InitDos() hasn't been called */
    }
}


int far fp1() {
    int i = 32767;
    while(--i) {
        if (i % 10000) printf("This is fp1\n");
    }
    return 0;
}

int far fp2() {
    int i = 32767;
    while(--i) {
        if (i % 10000) printf("This is fp2\n");
    }
    return 0;
}

int main() {
    InitDos();
    create("FP1", (func)fp1, 1024);
    create("FP2", (func)fp2, 1024);
    disable();
    oldtimeslicehandler = getvect(TIME_INT);
    setvect(TIME_INT, timeslicehandler);
    // timeslicehandler();
    ss = _SS;
    sp = _SP;
    ds = _DS;
    cs = _CS;
    enable();

    while(!tcb_count) { printf("Main thread waiting for thread creation.\n"); }
    while(tcb_count) { printf("Main thread waiting for thread end.\n"); }
    setvect(TIME_INT, oldtimeslicehandler);
    return 0;
}
