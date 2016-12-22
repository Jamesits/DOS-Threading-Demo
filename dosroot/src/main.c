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

int timecount = 0;
int TL;
int current     = -1;
int n           = 0;

int intbuf[NBUF], buftemp;
int in = 0, out = 0;

menuitem mainmenu[] = {
	{ 1, "FIFO" },
	{ 2, "Time" },
	{ 3, "Dynamic slice" },
	{ 4, "mutex" },
	{ 5, "Proc/cusm" },
	{ 6, "buffer" },
	{ NULL, "Select: " },
};

int main(void)
{
    int select = -1;

    InitDos();
    initTCB();

    old_int8 = getvect(8);
    strcpy(tcb[0].name, "main");
    tcb[0].state        = RUNNING;
    current             = 0;

    while (select != 0) {
        select = dispmenu(mainmenu);

        switch (select) {
        case 1:
                create( "f1",   (codeptr)f1,    NSTACK);
                create( "f2",   (codeptr)f2,    NSTACK);
            clrscr();
                printf( "\ncreate f1 and f2\n");
                printf( "f1 prints 1000 a\n");
                printf( "f2 prints 100 b\n");
            swtch();
            getch();
            break;

        case 2:
            TL = 1;
            printf("Time slice = 1\n\n");
            getch();
                create( "f1",   (codeptr)f1,    NSTACK);
                create( "f2",   (codeptr)f2,    NSTACK);
                create( "f3",   (codeptr)f3,    NSTACK);
            clrscr();
                printf( "\ncreate f1, f2, f3\n");
                printf( "f1 prints 1000 a\n");
                printf( "f2 prints 100 b\n");
                printf( "f3 prints 1000 c\n");
            setvect(8, new_int8);
            swtch();
            getch();
            break;

        case 3:
            printf("Enter new time slice: ");
            scanf("%d", &TL);
            printf("Time slice = %d\n\n", TL);
            getch();
                create( "f1",   (codeptr)f1,    NSTACK);
                create( "f2",   (codeptr)f2,    NSTACK);
                create( "f3",   (codeptr)f3,    NSTACK);
            clrscr();
                printf( "\ncreate f1, f2, f3\n");
                printf( "f1 prints 1000 a\n");
                printf( "f2 prints 100 b\n");
                printf( "f3 prints 1000 c\n");
            setvect(8, new_int8);
            swtch();
            getch();
            break;

        case 4:
            n   = 0;
            TL  = 1;
                create( "f4",   (codeptr)f4,    NSTACK);
                create( "f5",   (codeptr)f5,    NSTACK);
                printf( "\ncreate f4, f5\n");
                printf( "f4 increase n 1 each time\n");
                printf( "f5 decrease n 1 each time\n");
            setvect(8, new_int8);
            swtch();
            getch();
            break;

        case 5:
            TL = 4;

                create( "prdc", (codeptr)prdc,  NSTACK);
                create( "cnsm", (codeptr)cnsm,  NSTACK);
                printf( "prdc\n");
                printf( "cnsm\n");
            getch();
            setvect(8, new_int8);
            swtch();
            getch();
            break;

        case 6:
            initBuf();
                create( "sender",       (codeptr)sender,        NSTACK);
                create( "receiver",     (codeptr)receiver,      NSTACK);
            printf("sending\n");
            getch();
            TL = 1;
            setvect(8, new_int8);
            swtch();
            getch();
            break;

        default: select = 0;
        }

        while (!finished()) ;
        setvect(8, old_int8);
    }

    free_all();

    tcb[0].name[0]      = '\0';
    tcb[0].state        = FINISHED;

    printf("\nFinished, press any key to quit...\n");
    getch();
	return 0;
}

#include "dosutil.c"
#include "kernel.c"
#include "sem.c"
#include "buffer.c"
#include "usermain.c"
#include "menu.c"
