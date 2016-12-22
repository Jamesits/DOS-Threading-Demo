#include <alloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>

#define NTCB    10
#define NTEXT   20
#define NBUF    5
#define NSTACK 1024

#include "dosutil.h"
#include "sem.h"
#include "buffer.h"
#include "kernel.h"
#include "usermain.h"
#include "menu.h"

int intbuf[NBUF], buftemp;
int in = 0, out = 0;

void demo_fifo() {
	pause();
    create( "f1",   (codeptr)f1,    NSTACK);
    create( "f2",   (codeptr)f2,    NSTACK);
    swtch();
    pause();
}

void demo_adjslice() {
    TL = numselection("Set time slice: ", 1, 1, 100, 1);
    create( "f1",   (codeptr)f1,    NSTACK);
    create( "f2",   (codeptr)f2,    NSTACK);
    create( "f3",   (codeptr)f3,    NSTACK);
    clrscr();
    setvect(8, new_int8);
    swtch();
    getch();
}

void demo_mutex() {
    n   = 0;
	TL = numselection("Set time slice: ", 1, 1, 100, 1);
    create( "f4",   (codeptr)f4,    NSTACK);
    create( "f5",   (codeptr)f5,    NSTACK);
    setvect(8, new_int8);
    swtch();
    getch();
}

void demo_buffer() {
	initBuf();
	TL = numselection("Set time slice: ", 1, 1, 100, 1);
    create( "send",       (codeptr)sender,      NSTACK);
    create( "recv",     (codeptr)receiver,      NSTACK);
    setvect(8, new_int8);
    swtch();
    pause();
}

void menu_quit() {
	setvect(8, old_int8);
	free_all();

    tcb[0].name[0]      = '\0';
    tcb[0].state        = FINISHED;

	clrscr();
    exit(0);
}

menu mainmenu = {
    { demo_fifo,     "FIFO"                                             },
    { demo_adjslice, "Time slice"                                       },
    { demo_mutex,    "Mutex"                                            },
    { demo_buffer,   "Messaging"                                        },
    { menu_quit,     "quit"                                             },
    { NULL,          "Press number key to select:"                      },
};

int main(void)
{
    int selection;

	// initialize DOS utilities
    InitDos();
    initTCB();

	// create init thread
    old_int8 = getvect(8);
    strcpy(tcb[0].name, "main");
    tcb[0].state        = RUNNING;
    current             = 0;

	// main menu
    while (1) {
		clrscr();
		selection = dispmenu(mainmenu, 0);

        clrscr();
        printf( "Current demo: %s\n", mainmenu[selection].description);

        mainmenu[selection].func();

        //  wait for all threads to finish
        while (!finished()) ;

        // reset
        setvect(8, old_int8);
		free_all();
    }
}

#include "dosutil.c"
#include "kernel.c"
#include "sem.c"
#include "buffer.c"
#include "usermain.c"
#include "menu.c"
