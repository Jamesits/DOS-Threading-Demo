#include "sem.h"
#include "thread.h"
#include "debug.h"

void block(s_TCB **qp, int thread);
void wakeup_head(s_TCB **qp);

void init_semaphore(semaphore *s, int count) {
    lprintf(DEBUG, "Initializing semaphore with count %d\n", count);
    s->status = count;
    s->wait_queue = NULL;
}

void wait(semaphore *sem) {
    s_TCB **qp;
    begin_transaction();
    sem -> status -= 1;
    if ( sem -> status < 0 ) {
        qp = &( sem -> wait_queue );
        block(qp, get_last_running_thread_id());
    }
    lprintf(DEBUG, "Semaphore waited, count left %d\n", sem -> status);
    end_transaction();
}

void signal(semaphore *sem)
{
    s_TCB **qp;
    begin_transaction();
    qp = &( sem -> wait_queue );
    sem -> status += 1;
    if( sem -> status <=0 ) {
        wakeup_head(qp);
    }
    lprintf(DEBUG, "Semaphore signaled, count left %d\n", sem -> status);
    end_transaction();
}

void block(s_TCB **qp, int thread) {
    s_TCB *ptr = *qp;
    if (!ptr) {
        *qp = &(tcb[thread]);
        tcb[thread].state = BLOCKED;
        tcb[thread].next = NULL;
    } else {
        while (ptr -> next) {
            // ptr -> state = BLOCKED;
            ptr = ptr -> next;
        }
        ptr -> next = &(tcb[thread]);
        tcb[thread].state = BLOCKED;
    }
}

void wakeup_head(s_TCB **qp) {
    if (*qp) {
        (*qp) -> state = READY;
        (*qp) = (*qp) -> next;
    }
}
