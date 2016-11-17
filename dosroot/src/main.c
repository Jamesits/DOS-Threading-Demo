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
    lprintf(INFO, "Starting...\n");
    PrintRegs();
    lprintf(INFO, "Initializing DOS critical pointers...\n");
    InitDos();
    lprintf(INFO, "Getting INT08h...\n");
    disable();
    oldtimeslicehandler = getvect(TIME_INT);
    setvect(TIME_INT, timeslicehandler);
    enable();
    lprintf(INFO, "Starting user program...\n");
    usermain();
    lprintf(INFO, "main() finished.\n");
    for(;;) {
        asm { hlt }
    }
}
