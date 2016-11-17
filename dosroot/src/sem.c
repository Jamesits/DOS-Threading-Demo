#include "sem.h"
#include "debug.h"

void block(s_TCB **qp, int thread);
void wakeup_head(s_TCB **qp);

void init_semaphore(semaphore *s, int count) {
#ifdef DEBUG_SEM
    printf("Initializing semaphore with count %d\n", count);
#endif
    s->status = count;
    s->wait_queue = NULL;
}

void wait(semaphore *sem) {
    s_TCB **qp;
    disable();
    sem -> status -= 1;
    if ( sem -> status < 0 ) {
        qp = &( sem -> wait_queue );
        block(qp, get_last_running_thread_id());
    }
#ifdef DEBUG_SEM
    printf("Semaphore waited, count left %d\n", sem -> status);
    print_tcb();
#endif
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
#ifdef DEBUG_SEM
    printf("Semaphore signaled, count left %d\n", sem -> status);
    print_tcb();
#endif
    enable();
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
