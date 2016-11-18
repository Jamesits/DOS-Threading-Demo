#include <DOS.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "debug.h"
#include "thread.h"

const char *tcb_status_text[] = {"FINISHED", "RUNNING", "READY", "BLOCKED"};
const char *loglevel_text[] = {"INFO", "DEBUG", "WARNING", "ERROR", "CRITICAL", 0};
#ifdef DEBUG_ENABLE_FILE_REDIRECTION
FILE *debug_file;
#endif

void init_dbg() {
#ifdef DEBUG_ENABLE_FILE_REDIRECTION
    debug_file = fopen(DEBUG_FILE, "w+");
    if (!debug_file) {
        fprintf(stderr, "Error opening file %s\n", DEBUG_FILE);
        exit(-1);
    }
#endif
}

void end_dbg() {
    fclose(debug_file);
}

int lprintf(loglevel level, const char *format, ...)
{
    va_list args;
    int ret;

#ifdef DEBUG_ENABLE_FILE_REDIRECTION
    if (loglevel_text[level]) fprintf(debug_file, "[%u][%s] ", (unsigned)time(NULL), loglevel_text[level]);
    va_start(args, format);
    ret = vfprintf(debug_file, format, args);
    va_end(args);
    fflush(debug_file);
#endif

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

void print_tcb() {
#ifdef DEBUG_PRINT_TCB
    int i;
    lprintf(INFO, ">>>> TCB status\n");
    lprintf(INFO, "\tLast running: %d, Next running: %d, DOS Busy: %d\n", get_last_running_thread_id(), get_next_running_thread_id(), DosBusy());
    lprintf(INFO, "\tID\tName\tStack\tSS:SP\t\tState\n");
    for (i = 0; i < tcb_count; ++i) {
        lprintf(INFO, "\t%d\t%s\t0x%X\t0x%X:0x%X\t%d:%s\n", i, tcb[i].name, tcb[i].stack, tcb[i].ss, tcb[i].sp, tcb[i].state, tcb_status_text[tcb[i].state]);
    }
#endif
}
