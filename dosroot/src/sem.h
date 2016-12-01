#ifndef __SEM_H__
#define __SEM_H__
#include "thread.h"
#include "dosutil.h"

typedef struct semaphore{
    int status;
    s_TCB far *wait_queue;
} semaphore;

void far init_semaphore(semaphore far *s, int count);
int far sem_wait(semaphore far *s);
void far sem_signal(semaphore far *s);

#define P(X) while (sem_wait(&(X))) {geninterrupt(TIME_INT); delay(1);}
#define V(X) sem_signal(&(X));

#endif
