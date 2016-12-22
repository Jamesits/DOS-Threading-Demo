void InitDos(void)
{
    union REGS          regs;
    struct SREGS        segregs;

    regs.h.ah = GET_INDOS;
    intdosx(&regs, &regs, &segregs);
    indos_ptr = MK_FP(segregs.es, regs.x.bx);

    if (_osmajor < 3) crit_err_ptr = indos_ptr + 1;
    else if ((_osmajor == 3) && (_osminor == 0)) crit_err_ptr = indos_ptr - 1;
    else
    {
        regs.x.ax = GET_CRIT_ERR;
        intdosx(&regs, &regs, &segregs);
        crit_err_ptr = MK_FP(segregs.ds, regs.x.si);
    }
}

int DosBusy(void)

{
    if (indos_ptr && crit_err_ptr) return *indos_ptr || *crit_err_ptr;
    else return -1;
}
