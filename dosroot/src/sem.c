#include "sem.h"

void block(s_TCB **qp);
void wakeup_head(s_TCB **qp);

void wait(semaphore *sem) {
    s_TCB **qp;
    disable();
    sem -> status -= 1;
    if ( sem -> status < 0 ) {
        qp = &( sem -> wait_queue );
        block(qp);
    }
    enable();
}

void signal(semaphore *sem)
{
    s_TCB **qp;
    disable();
    qp = &( sem -> wait_queue );
    sem -> status += 1;
    if( sem -> status <=0 ) {
        wakeup_head(qp);
    }
    enable();
}

void block(s_TCB **qp) {
    s_TCB *ptr = *qp;
    while (ptr) {
        ptr -> state = BLOCKED;
        ptr = ptr -> next;
    }
}
void wakeup_head(s_TCB **qp) {
    (*qp) -> state = READY;
    (*qp) = (*qp) -> next;
}
