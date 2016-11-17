#include "thread.h"
#include "usercode.h"

int far usermain() {
    create("FP1", (func)fp1, DEFAULT_THREAD_STACK_SIZE, DEFAULT_TIME_SLICE_PRIORITY);
    create("FP2", (func)fp2, DEFAULT_THREAD_STACK_SIZE, DEFAULT_TIME_SLICE_PRIORITY);

    return 0;
}

int far fp1() {
    int i = 200;
    int j = 1;
    enable();
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
    enable();
    while(--i) {
        printf("b");
        fflush(stdout);
        j -= 1;
        delay(1);
    }
    return 0;
}
