#include <dos.h>

typedef struct {
    int         value;
    struct TCB  *wq;
} semaphore;

void    wait(semaphore *sem);
void    signal(semaphore *sem);
void    block(struct TCB **qp);
void    wakeupFirst(struct TCB **qp);
