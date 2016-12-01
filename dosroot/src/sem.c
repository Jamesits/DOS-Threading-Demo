#include <DOS.h>
#include "sem.h"
#include "thread.h"
#include "debug.h"
#include "dosutil.h"

void far sem_block(s_TCB far **qp, int thread);
void far sem_wakeup_head(s_TCB far **qp);

void far init_semaphore(semaphore far *s, int count) {
    lprintf(DEBUG, "Initializing semaphore with count %d\n", count);
    s->status = count;
    s->wait_queue = NULL;
}

int far sem_wait(semaphore far *sem) {
    s_TCB far **qp;
    int ret = 0;
    begin_transaction();
    in_kernel = 1;
    if ( (sem -> status) < 0 ) {
         qp = &( sem -> wait_queue );
         sem_block(qp, get_last_running_thread_id());
         lprintf(DEBUG, "Semaphore waited, count left %d\n", sem -> status);

         ret = 1;
    } else {
         (sem -> status) -= 1;
         lprintf(DEBUG, "Semaphore got, count left %d\n", sem -> status);
    }
    in_kernel = 0;
    end_transaction();
    return ret;
}

void far sem_signal(semaphore far *sem)
{
    s_TCB far **qp;
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

void far sem_block(s_TCB **qp, int thread) {
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

void far sem_wakeup_head(s_TCB **qp) {
    if (*qp) {
        (*qp) -> state = READY;
        (*qp) = (*qp) -> next;
    }
}
