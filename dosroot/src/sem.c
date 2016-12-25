#include <dos.h>

void wait(semaphore *sem)
{
    struct TCB **qp;

    in_kernel = 1;
    sem->value--;

    if (sem->value < 0) {
        qp = &(sem->wq);
        block(qp);
        in_kernel = 0;
        swtch();
    } else {
        in_kernel = 0;
    }
}

void signal(semaphore *sem)
{
    struct TCB **qp;

    in_kernel = 1;
    qp = &(sem->wq);
    sem->value++;

    if (sem->value <= 0) {
        wakeupFirst(qp);
    }
    in_kernel = 0;
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
