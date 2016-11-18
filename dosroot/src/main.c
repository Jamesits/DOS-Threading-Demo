#include <DOS.h>
#include "main.h"
#include "debug.h"
#include "thread.h"

void interrupt (*oldtimeslicehandler)(void);

void cleanup() {
    lprintf(DEBUG, "Cleaning up...\n");
    lprintf(INFO, "Resetting time handler\n");
    setvect(TIME_INT, oldtimeslicehandler);
    enable();
    PrintRegs();
    lprintf(INFO, "Finished...\n");
    end_dbg();
    exit(0);
}

int main() {
    init_dbg();
    tconvert("init");
    lprintf(INFO, "Starting...\n");
    PrintRegs();
    lprintf(INFO, "Initializing DOS critical pointers...\n");
    InitDos();
    lprintf(INFO, "Getting INT08h...\n");
    disable();
    oldtimeslicehandler = getvect(TIME_INT);
    setvect(TIME_INT, timeslicehandler);
    lprintf(INFO, "Previous interrupt: 0x%X, custom interrupt: 0x%X, current interrupt: 0x%X\n", oldtimeslicehandler, timeslicehandler, getvect(TIME_INT));
    enable();
    lprintf(INFO, "Starting user program...\n");
    // usermain();
    create("sh", (func)usermain, DEFAULT_THREAD_STACK_SIZE);
    while(tcb_count > 0) lprintf(INFO, "main() waiting for child to end...\n");;

    lprintf(INFO, "main() finished.\n");

    return 0;
}
