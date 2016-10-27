#include <DOS.h>
#include <stdio.h>

#define NTCB 20
enum THREAD_STATUS {FINISHED, RUNNING, READY, BLOCKED};

typedef struct TCB{
    unsigned char *stack;  /* 线程堆栈的起始地址 */
    unsigned ss;  /* 堆栈段址 */
    unsigned sp;  /* 堆栈指针 */
    char state;  /* 线程状态 ，取值可以是FINISHED、RUNNING、READY、BLOCKED*/
    char name[10]; /* 线程的外部标识符 */
} s_TCB;

struct int_regs {
    unsigned bp,di,si,ds,es,dx,cx,bx,ax,ip,cs,flags,off,seg;
};

s_TCB tcb[NTCB];      /*NTCB是系统允许的最多任务数*/

typedef int (far *codeptr)(void); /*定义了一个函数指针类型*/
int create(char *name, codeptr code, int stck);
int destroy();

void interrupt (*oldtimeslicehandler)(void);

int fuck = 0;

void interrupt timeslicehandler(void) {
    fuck++;
    /* setvect(0x1C, oldtimeslicehandler); */
}

int main() {
    int i = 32767;
    oldtimeslicehandler = getvect(0x1C);
    setvect(0x1C, timeslicehandler);
    while (i--) {printf("%d\n", fuck);};

    return 0;
}
