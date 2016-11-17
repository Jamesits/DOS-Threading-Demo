#include <DOS.h>
#include <stdio.h>
#include "debug.h"
#include "thread.h"

void print_tcb() {
    int i;
    printf(">>>> TCB status\n");
    printf("Last running: %d, Next running: %d, DOS Busy: %d\n", get_last_running_thread_id(), get_next_running_thread_id(), DosBusy());
    printf("ID\tName\tStack\tSS\tSP\tState\n");
    for (i = 0; i < tcb_count; ++i) {
        printf("%d\t%s\t0x%X\t0x%X\t0x%X\t%d\n", i, tcb[i].name, tcb[i].stack, tcb[i].ss, tcb[i].sp, tcb[i].state);
    }
}
