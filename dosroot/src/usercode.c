#include "usercode.h"

int far usermain() {
    create("FP1", (func)fp1, DEFAULT_THREAD_STACK_SIZE);
    create("FP2", (func)fp2, DEFAULT_THREAD_STACK_SIZE);
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
