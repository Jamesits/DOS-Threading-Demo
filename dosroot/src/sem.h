#ifndef __SEM_H__
#define __SEM_H__
#include <DOS.h>
#include "thread.h"
#include "dosutil.h"
#include "debug.h"

typedef struct semaphore{
    int status;
    s_TCB far *wait_queue;
} semaphore;

void far init_semaphore(semaphore far *s, int count);
int far sem_wait(semaphore far *s);
void far sem_signal(semaphore far *s);

#define P(X) while (sem_wait(&(X))) lprintf(INFO, "sem waiting\n");//{pswitch();}
#define V(X) sem_signal(&(X));

#endif
