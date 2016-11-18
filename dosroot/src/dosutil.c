#include <DOS.h>
#include "dosutil.h"

char far *indos_ptr = 0;
char far *crit_err_ptr = 0;

/* get INDOS bit and critical error bit addresses */
void far InitDos(void) {
    union REGS regs;
    struct SREGS segregs;

    regs.h.ah = GET_INDOS;
    /* invoke INT21H */
    intdosx(&regs, &regs, &segregs);
    indos_ptr = MK_FP(segregs.es, regs.x.bx);
    /* get critical error bit address */
    if (_osmajor < 3) {
        crit_err_ptr = indos_ptr + 1;
    } else if (_osmajor == 3 && _osminor == 0) {
        crit_err_ptr = indos_ptr - 1;
    } else {
        regs.x.ax = GET_CRIT_ERR;
        intdosx(&regs, &regs, &segregs);
        crit_err_ptr = MK_FP(segregs.ds, regs.x.si);
    }
}

/* get if DOS is working or critical error happened */
int far DosBusy(void) {
    if (indos_ptr && crit_err_ptr) {
        return (*indos_ptr || *crit_err_ptr);
    } else {
        return(-1);    /* InitDos() hasn't been called */
    }
}
