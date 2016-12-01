#include "sem.h"
#include "thread.h"
#include "debug.h"
#include "dosutil.h"

void sem_block(s_TCB **qp, int thread);
void sem_wakeup_head(s_TCB **qp);

void init_semaphore(semaphore *s, int count) {
    lprintf(DEBUG, "Initializing semaphore with count %d\n", count);
    s->status = count;
    s->wait_queue = NULL;
}

void wait(semaphore *sem) {
    s_TCB **qp;
    begin_transaction();
    in_kernel = 1;
    (sem -> status) -= 1;
    if ( (sem -> status) < 0 ) {
        qp = &( sem -> wait_queue );
        sem_block(qp, get_last_running_thread_id());
    }
    lprintf(DEBUG, "Semaphore waited, count left %d\n", sem -> status);
    in_kernel = 0;
    end_transaction();
    geninterrupt(TIME_INT);
}

void signal(semaphore *sem)
{
    s_TCB **qp;
    begin_transaction();
    in_kernel = 1;
    qp = &( sem -> wait_queue );
    (sem -> status) += 1;
    if( (sem -> status) <=0 ) {
        sem_wakeup_head(qp);
    }
    lprintf(DEBUG, "Semaphore signaled, count left %d\n", sem -> status);
    in_kernel = 0;
    end_transaction();
}

void sem_block(s_TCB **qp, int thread) {
    s_TCB *ptr = *qp;
    if (!ptr) {
        *qp = &(tcb[thread]);
        set_thread_state(thread, BLOCKED);
        tcb[thread].next = NULL;
    } else {
        while (ptr -> next) {
            ptr = ptr -> next;
        }
        ptr -> next = &(tcb[thread]);
        tcb[thread].next = NULL;
        set_thread_state(thread, BLOCKED);
    }
}

void sem_wakeup_head(s_TCB **qp) {
    if (*qp) {
        (*qp) -> state = READY;
        (*qp) = (*qp) -> next;
    }
}
