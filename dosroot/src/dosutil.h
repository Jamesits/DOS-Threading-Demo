#include <dos.h>

#define GET_INDOS 0x34
#define GET_CRIT_ERR 0x5d06
#define INT_TIMER 0x8

char far *indos_ptr     = 0;
char far *crit_err_ptr  = 0;

void    InitDos(void);
int     DosBusy(void);
void    pause();

#define breakpoint() asm int 3
