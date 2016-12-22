#define GET_INDOS 0x34
#define GET_CRIT_ERR 0x5d06

char far *indos_ptr = 0;
char far *crit_err_ptr = 0;

void InitDos(void);
int DosBusy(void);
