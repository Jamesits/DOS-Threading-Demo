#include <DOS.h>
#include "dosutil.h"
#include "debug.h"
#include "thread.h"

char far *indos_ptr = 0;
char far *crit_err_ptr = 0;
unsigned atomic_operation_level = 0;

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

void far begin_transaction() {
    ++in_kernel;
    ++atomic_operation_level;
    lprintf(INFO, "Transaction started, current level %d\n", atomic_operation_level);
    if (atomic_operation_level == 1) {
        lprintf(DEBUG, "Acquiring interrupt lock...\n");
        end_dbg(); // for flush
        disable();
    }
    --in_kernel;
}

void far end_transaction() {
    ++in_kernel;
    if (atomic_operation_level == 1) {
        enable();
        lprintf(DEBUG, "Releasing interrupt lock...\n");
    }
    lprintf(INFO, "Transaction committed, current level %d\n", atomic_operation_level);
    --atomic_operation_level;
    --in_kernel;
}

unsigned far get_transaction_level() {
    return atomic_operation_level;
}

void far clrscr() {
    system("cls");
}

void far pause() {
    system("pause");
}

void far halt() {
    asm hlt;
}
