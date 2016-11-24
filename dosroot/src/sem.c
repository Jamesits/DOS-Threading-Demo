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

int wait(semaphore *sem) {
    s_TCB **qp;
    int ret;
    begin_transaction();
    in_kernel = 1;
    if ( sem -> status < 0 ) {
        qp = &( sem -> wait_queue );
        // lprintf(DEBUG, "Semaphore waiting, count left %d\n", sem -> status);
        block(qp, get_last_running_thread_id());
        ret = 1;
    } else {
        sem -> status -= 1;
        // lprintf(DEBUG, "Semaphore catched, count left %d\n", sem -> status);
        ret = 0;
    }
    in_kernel = 0;
    end_transaction();
    return ret;
}

void signal(semaphore *sem)
{
    s_TCB **qp;
    begin_transaction();
    in_kernel = 1;
    qp = &( sem -> wait_queue );
    sem -> status += 1;
    if( sem -> status >=0 ) {
        wakeup_head(qp);
    }
    // lprintf(DEBUG, "Semaphore signaled, count left %d\n", sem -> status);
    in_kernel = 0;
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
            ptr -> state = BLOCKED;
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
