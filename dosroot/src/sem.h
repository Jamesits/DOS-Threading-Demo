#ifndef __SEM_H__
#define __SEM_H__
#include "thread.h"

typedef struct semaphore{
    int status;
    s_TCB *wait_queue;
} semaphore;

void init_semaphore(semaphore *s, int count);
int wait(semaphore *sem);
void signal(semaphore *s);

#define P(X) { \
    while(wait(&(X))) { \
    } \
}

#define V(X) { \
    signal(&(X)); \
}
#endif
