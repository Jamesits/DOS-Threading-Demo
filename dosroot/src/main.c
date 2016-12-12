#include <DOS.h>
#include "dosutil.h"
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
    in_kernel++;
    printf("|%d|", in_kernel);
    init_dbg();

    lprintf(INFO, "Starting main()...\n");
    PrintRegs();

    lprintf(INFO, "Initializing DOS critical pointers...\n");
    InitDos();

printf("|%d|", in_kernel);
    lprintf(INFO, "Starting user program (early)...\n");
    //usermain();
    // breakpoint();
    lprintf(INFO, "Getting INT08h...\n");
    lprintf(INFO, "System interrupt: 0x%Fp\n", getvect(TIME_INT));
    begin_transaction();
    oldtimeslicehandler = getvect(TIME_INT);
    setvect(TIME_INT, timeslicehandler);
    end_transaction();
    lprintf(INFO, "Current interrupt: 0x%Fp\n", getvect(TIME_INT));
printf("|%d|", in_kernel);
    lprintf(DEBUG, "Converting current process to thread #%d\n", tcb_count);
    tcb[tcb_count].stack = 0;
    strcpy(tcb[tcb_count].name, "init");
    begin_transaction();
    tcb[tcb_count].ss = _SS;
    tcb[tcb_count].sp = _SP;
    tcb[tcb_count].state = RUNNING;
    end_transaction();
    ++tcb_count;
printf("|%d|", in_kernel);
    create("shell", (func)usermain, DEFAULT_THREAD_STACK_SIZE);
    lprintf(INFO, "main() init part finished.\n");
    in_kernel--;
    while(1) asm hlt;
}
