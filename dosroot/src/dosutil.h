#ifndef __DOSUTIL_H__
#define __DOSUTIL_H__

#define GET_INDOS 0x34
#define GET_CRIT_ERR 0x5d06
/* 0x1C is usable */
#define TIME_INT 0x08

void far InitDos(void);
int far DosBusy(void);
void far begin_transaction();
void far end_transaction();
unsigned far get_transaction_level();
void far clrscr();
void far pause();

#endif
