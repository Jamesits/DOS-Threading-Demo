#include <DOS.h>
#include <stdio.h>
#include <stdarg.h>
#include "debug.h"
#include "thread.h"

const char *loglevel_text[] = {"DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL", 0};

void print_tcb() {
    int i;
    printf(">>>> TCB status\n");
    printf("Last running: %d, Next running: %d, DOS Busy: %d\n", get_last_running_thread_id(), get_next_running_thread_id(), DosBusy());
    printf("ID\tName\tStack\tSS\tSP\tState\n");
    for (i = 0; i < tcb_count; ++i) {
        printf("%d\t%s\t0x%X\t0x%X\t0x%X\t%d\n", i, tcb[i].name, tcb[i].stack, tcb[i].ss, tcb[i].sp, tcb[i].state);
    }
}

int lprintf(loglevel level, const char *format, ...)
{
    va_list args;
    int ret;
    if (DEBUG_LOG_LEVEL > level) return 0;
    if (loglevel_text[level]) fprintf(DEBUG_OUTPUT_FILE, "[%s] ", loglevel_text[level]);
    va_start(args, format);
    ret = vfprintf(DEBUG_OUTPUT_FILE, format, args);
    va_end(args);
#ifdef DEBUG_FLUSH_BUFFER
    fflush(DEBUG_OUTPUT_FILE);
#endif
    return ret;
}
