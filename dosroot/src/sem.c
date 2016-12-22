#include <dos.h>

void wait(semaphore *sem)
{
    struct TCB **qp;

    disable();
    sem->value--;

    if (sem->value < 0) {
        qp = &(sem->wq);
        block(qp);
    }
    enable();
}

void signal(semaphore *sem)
{
    struct TCB **qp;

    disable();
    qp = &(sem->wq);
    sem->value++;

    if (sem->value <= 0) {
        wakeupFirst(qp);
    }
    enable();
}

void block(struct TCB **qp)
{
    int id;
    struct TCB *tcbtmp;

    id                  = current;
    tcb[id].state       = BLOCKED;

    if ((*qp) == NULL) (*qp) = &tcb[id];
    else {
        tcbtmp = *qp;

        while (tcbtmp->next != NULL) tcbtmp = tcbtmp->next;
        tcbtmp->next = &tcb[id];
    }

    tcb[id].next = NULL;
    swtch();
}

void wakeupFirst(struct TCB **qp)
{
    struct TCB *tcbtmp;

    if ((*qp) == NULL) return;

    tcbtmp              = *qp;
    *qp                 = (*qp)->next;
    tcbtmp->state       = READY;
    tcbtmp->next        = NULL;
}
