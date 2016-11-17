#include "usercode.h"
#include "sem.h"
semaphore s;

int far forever() {
    int i;
    while(1) {i++;printf("%d", i);}
}

int far usermain() {
    printf("DEMO multi-threading: \n");
    fflush(stdout);
    create("NULL", (func)forever, DEFAULT_THREAD_STACK_SIZE);
    create("FP1", (func)fp1, DEFAULT_THREAD_STACK_SIZE);
    create("FP2", (func)fp2, DEFAULT_THREAD_STACK_SIZE);
    printf("\n");
    fflush(stdout);

    // printf("DEMO multi-threading with semaphore: \n");
    // fflush(stdout);
    // init_semaphore(&s, 0);
    // create("NULL", (func)forever, DEFAULT_THREAD_STACK_SIZE);
    // create("FP1_SEM", (func)fp1_sem, DEFAULT_THREAD_STACK_SIZE);
    // create("FP2_SEM", (func)fp2_sem, DEFAULT_THREAD_STACK_SIZE);
    // printf("\n");
    // fflush(stdout);
    return 0;
}

int far fp1() {
    int i = 200;
    int j = 1;
    while(--i) {
        printf("a");
        fflush(stdout);
        j += 1;
        delay(1);
    }
    return 0;
}

int far fp2() {
    int i = 200;
    int j = 1;
    while(--i) {
        printf("b");
        fflush(stdout);
        j -= 1;
        delay(1);
    }
    return 0;
}

int far fp1_sem() {
    int i = 200;
    int j = 1;
    wait(&s);
    while(--i) {
        printf("a");
        fflush(stdout);
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
        printf("b");
        fflush(stdout);
        j -= 1;
    }
    signal(&s);
    return 0;
}
