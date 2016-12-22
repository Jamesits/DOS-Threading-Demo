#include <dos.h>

typedef struct {
    int         value;
    struct TCB  *wq;
} semaphore;

semaphore mutex = { 1, NULL };
semaphore mutexfb = { 1, NULL };
semaphore sfb = { NBUF, NULL };
semaphore empty = { NBUF, NULL };
semaphore full = { 0, NULL };

void    wait(semaphore *sem);
void    signal(semaphore *sem);
void    block(struct TCB **qp);
void    wakeupFirst(struct TCB **qp);
