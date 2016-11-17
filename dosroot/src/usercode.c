#include "thread.h"
#include "usercode.h"

int far usermain() {
    create("FP1", (func)fp1, 1024);
    create("FP2", (func)fp2, 1024);

    return 0;
}

int far fp1() {
    int i = 200;
    int j = 1;
    enable();
    while(--i) {
        printf("This is fp1\n");
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
        printf("This is fp2\n");
        fflush(stdout);
        j -= 1;
        delay(1);
    }
    return 0;
}
