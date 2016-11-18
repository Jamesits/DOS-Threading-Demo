#include <DOS.h>
#include "main.h"
#include "debug.h"
#include "thread.h"

void interrupt (*oldtimeslicehandler)(void);

void far cleanup() {
    lprintf(DEBUG, "Cleaning up...\n");
    lprintf(INFO, "Resetting time handler\n");
    setvect(TIME_INT, oldtimeslicehandler);
    lprintf(INFO, "System interrupt: 0x%Fp, Current interrupt: 0x%Fp\n", getvect(TIME_INT), oldtimeslicehandler);
    lprintf(INFO, "Force enabling interrupt...\n");
    enable();
    PrintRegs();
    lprintf(INFO, "Finished...\n");
    // destroy(0);
    end_dbg();
    exit(0);
}

int main() {
    init_dbg();
    lprintf(INFO, "Starting main()...\n");
    PrintRegs();
    lprintf(INFO, "Initializing DOS critical pointers...\n");
    InitDos();
    lprintf(INFO, "Getting INT08h...\n");
    begin_transaction();
    oldtimeslicehandler = getvect(TIME_INT);
    lprintf(INFO, "System interrupt: 0x%Fp, Current interrupt: 0x%Fp\n", getvect(TIME_INT), oldtimeslicehandler);
    setvect(TIME_INT, timeslicehandler);
    lprintf(INFO, "Object interrupt: 0x%Fp, Current interrupt: 0x%Fp\n", timeslicehandler, getvect(TIME_INT));
    // tconvert("init");
    lprintf(INFO, "Starting user program...\n");
    //usermain();
    create("sh", (func)usermain, DEFAULT_THREAD_STACK_SIZE);
    lprintf(INFO, "main() finished.\n");
    end_transaction();
    return 0;
}
