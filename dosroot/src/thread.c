#include <DOS.h>
#include <stdio.h>
#include <string.h>

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
int create(char *name, func thread_function, size_t stacklen) {
    if (tcb_count >= NTCB) {
        printf("TCB stack full");
        return -1;
    }
    tcb[tcb_count].stack = malloc(stacklen);
    tcb[tcb_count].ss = FP_SEG(tcb[tcb_count].stack);
    tcb[tcb_count].sp = FP_OFF(tcb[tcb_count].stack);
    tcb[tcb_count].state = READY;
    strcpy(tcb[tcb_count].name, name);
    return tcb_count++;
};

int destroy(int id) {
    if (id >= NTCB) {
        printf("Cannot destory thread #%d", id);
        return -1;
    }
    free(tcb[id].stack);
    memcpy(tcb + id * sizeof(s_TCB), tcb + (id + 1) * sizeof(s_TCB), (NTCB - id - 1) * sizeof(s_TCB));
    --tcb_count;
    return 0;
};

void interrupt (*oldtimeslicehandler)(void);
void interrupt timeslicehandler(void) {
    printf("interrupt\n");
}

int main() {
    int i = 32767;
    oldtimeslicehandler = getvect(0x1C);
    setvect(0x1C, timeslicehandler);
    setvect(0x1C, oldtimeslicehandler);
    return 0;
}
