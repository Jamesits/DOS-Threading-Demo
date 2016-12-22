#include <dos.h>

void initTCB()
{
    int i;

    for (i = 0; i < NTCB; i++) {
        tcb[i].name[0]          = '\0';
        tcb[i].stack            = NULL;
        tcb[i].state            = FINISHED;
        tcb[i].mq               = NULL;
        tcb[i].mutex.value      = 1;
        tcb[i].mutex.wq         = NULL;
        tcb[i].sm.value         = 0;
        tcb[i].sm.wq            = NULL;
        tcb[i].next             = NULL;
    }
}

int create(char *name, codeptr code, int stck)
{
    struct int_regs far *r;
    int i, id = -1;

    for (i = 0; i < NTCB; i++) {
        if (tcb[i].state == FINISHED) {
            id = i;
            break;
        }
    }

    if (id == -1) return -1;

    disable();

    tcb[id].stack       = (unsigned char *)malloc(stck);
    r                   = (struct int_regs *)(tcb[id].stack + stck);
    r--;
    tcb[id].ss          = FP_SEG(r);
    tcb[id].sp          = FP_OFF(r);
    r->cs               = FP_SEG(code);
    r->ip               = FP_OFF(code);
    r->es               = _DS;
    r->ds               = _DS;
    r->flags            = 0x200;
    r->seg              = FP_SEG(over);
    r->off              = FP_OFF(over);
    tcb[id].state       = READY;
    strcpy(tcb[id].name, name);
    enable();
    return id;
}

void interrupt swtch()
{
    int loop = 0;

    disable();

    tcb[current].ss     = _SS;
    tcb[current].sp     = _SP;

    if (tcb[current].state == RUNNING) tcb[current].state = READY;

    while (tcb[++current].state != READY && loop++ < NTCB - 1)
        if (current == NTCB) current = 0;

    if (tcb[current].state != READY) current = 0;
    _SS = tcb[current].ss;
    _SP = tcb[current].sp;

    tcb[current].state = RUNNING;

    timecount = 0;

    enable();
}

void destroy(int id)
{
    disable();
    free(tcb[id].stack);
    tcb[id].stack       = NULL;
    tcb[id].state       = FINISHED;
    printf("\nProcess %s terminated\n", tcb[id].name);
    tcb[id].name[0] = '\0';
    enable();
}

void over()
{
    destroy(current);
    swtch();
}

int finished()
{
    int i;

    for (i = 1; i < NTCB; i++)
        if (tcb[i].state != FINISHED) return 0;

    return 1;
}

void free_all(void)
{
    int i;

    for (i = 0; i < NTCB; i++) {
        if (tcb[i].stack) {
            tcb[i].name[0]      = '\0';
            tcb[i].state        = FINISHED;
            free(tcb[i].stack);
            tcb[i].stack = NULL;
        }
    }
}

void interrupt new_int8()

{
    (*old_int8)();
    timecount++;

    if (timecount < TL || DosBusy() || in_kernel) return;

    swtch();
}
