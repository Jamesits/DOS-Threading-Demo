#include "usercode.h"
#include "sem.h"
#include "debug.h"
#include <stdio.h>
semaphore s;

int far forever() {
    int i = 60;
    while(i--) delay(1); // {i++; lprintf(PROMPT, "%d", i);}
    return 0;
}

int far usermain() {
    lprintf(PROMPT, "DEMO multi-threading: \n");
    create("NULL", (func)forever, DEFAULT_THREAD_STACK_SIZE);
    create("FP1", (func)fp1, DEFAULT_THREAD_STACK_SIZE);
    create("FP2", (func)fp2, DEFAULT_THREAD_STACK_SIZE);

    // lprintf(PROMPT, "DEMO multi-threading with semaphore: \n");
    // init_semaphore(&s, 0);
    // create("NULL", (func)forever, DEFAULT_THREAD_STACK_SIZE);
    // create("FP1_SEM", (func)fp1_sem, DEFAULT_THREAD_STACK_SIZE);
    // create("FP2_SEM", (func)fp2_sem, DEFAULT_THREAD_STACK_SIZE);
    return 0;
}

int far fp1() {
    int i = 200;
    int j = 1;
    while(--i) {
        putchar('a');
        j += 1;
        //delay(1);
    }
    return 0;
}

int far fp2() {
    int i = 200;
    int j = 1;
    while(--i) {
        // lprintf(PROMPT, "b");
        putchar('b');
        j -= 1;
        //delay(1);
    }
    return 0;
}

int far fp1_sem() {
    int i = 200;
    int j = 1;
    wait(&s);
    while(--i) {
        lprintf(PROMPT, "a");
        j += 1;
    }
    signal(&s);
    return 0;
}

int far fp2_sem() {
    int i = 200;
    int j = 1;
    wait(&s);
    while(--i) {
        lprintf(PROMPT, "b");
        j -= 1;
    }
    signal(&s);
    return 0;
}
