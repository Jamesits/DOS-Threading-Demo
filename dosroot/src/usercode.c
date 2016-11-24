#include "usercode.h"
#include "sem.h"
#include "debug.h"
#include "dosutil.h"
#include <stdio.h>
semaphore s;

#define wait_tasks() while (current_tcb_count != tcb_count);

int far forever() {
    // int i = 60;
    // getchar();
    //cleanup();
    // while(i--) delay(1); // {i++; lprintf(PROMPT, "%d", i);}
    return 0;
}

int far usermain() {
    int current_tcb_count = tcb_count;
    clrscr();
    lprintf(PROMPT, "DEMO multi-threading: \n");
    // create("NULL", (func)forever, DEFAULT_THREAD_STACK_SIZE);
    create("FP1", (func)fp1, DEFAULT_THREAD_STACK_SIZE);
    create("FP2", (func)fp2, DEFAULT_THREAD_STACK_SIZE);
    wait_tasks();
    // cleanup();
    // pause();
    lprintf(PROMPT, "DEMO multi-threading with semaphore: \n");
    init_semaphore(&s, 0);
    // create("NULL", (func)forever, DEFAULT_THREAD_STACK_SIZE);
    create("FP1_SEM", (func)fp1_sem, DEFAULT_THREAD_STACK_SIZE);
    create("FP2_SEM", (func)fp2_sem, DEFAULT_THREAD_STACK_SIZE);
    wait_tasks();
    // return 0;
}

int far fp1() {
    int i = 600;
    int j = 1;
    while(--i) {
        putchar('a');
        j += 1;
        //delay(1);
    }
    lprintf(INFO, "FP1 finished\n");
    return 0;
}

int far fp2() {
    int i = 600;
    int j = 1;
    while(--i) {
        // lprintf(PROMPT, "b");
        putchar('b');
        j -= 1;
        //delay(1);
    }
    lprintf(INFO, "FP2 finished\n");
    return 0;
}

int far fp1_sem() {
    int i = 600;
    int j = 1;
    P(s);
    while(--i) {
        putchar('a');
        j += 1;
    }
    V(s);
    lprintf(INFO, "FP1_sem finished\n");
    return 0;
}

int far fp2_sem() {
    int i = 600;
    int j = 1;
    P(s);
    while(--i) {
        putchar('b');
        j -= 1;
    }
    V(s);
    lprintf(INFO, "FP2_sem finished\n");
    return 0;
}
